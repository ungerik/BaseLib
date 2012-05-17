/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/Session.h"
#include "BaseLib/Network/TcpConnection.h"
#include "BaseLib/Network/UdpConnection.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/System/Time.h"


namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::System;
using namespace BaseLib;



void setupConnectionStreams(AbstractConnection& connection)
{
	connection.inputStream().setReadStringMethod(BinaryInputStream::READ_STRING_TOKEN);
	connection.inputStream().setTokenDelimiters("\0");
	connection.outputStream().setStringTerminator("\0");
}



const int Session::PING_REQUEST_MESSAGE_SIZE = 0;
const int Session::PING_RESPONSE_MESSAGE_SIZE = sizeof(bool8);
const int Session::LEAVE_SESSION_MESSAGE_SIZE = 0;
const int Session::CHECK_PASSWORD_RESPONSE_MESSAGE_SIZE = sizeof(bool8);



Session::Session(uint16 atPort, double defaultTimeout)
	: port(atPort)
	, timeout(defaultTimeout)
	, actingAsGateway(false)
	, peers()
	, gateways()
	, potentialPeerAddresses()
	, broadcastUdpConnection(defaultTimeout)
	, sessionId(0)
	, userId()
	, userName()
	, currentSessionInfo()
	, sessionPassword()
	, sessionConnections()
	, currentSendConnectionsCount(0)
	, currentSendConnections(NULL)
	, currentOutputStream()
	, currentInputConnection(NULL)
	, broadcastConnections()
	, receiveConnections()
	, lastPeerIndex(-1)
	, timeForIsAlivePing(0.0)
	, requestIdOfLastIsAlivePing(0)
	, ipAddressOfLastIsAlivePing()
	, secondsBetweenIsAlivePings(60.0)
{
	checkArgumentIsValidFloat(NAME_VALUE(defaultTimeout));
	checkArgumentMin(NAME_VALUE(defaultTimeout), 0.0);

	setupConnectionStreams(broadcastUdpConnection);	
	broadcastUdpConnection.connect(IpAddress(0xFFFFFFFF, port));
}



Session::~Session()
{
	int count = messageListenerFunctors.getCount();
	for (int i = 0; i < count; ++i)
	{
		delete messageListenerFunctors[i];
	}

	for (SessionConnections::iterator i = sessionConnections.begin(); i != sessionConnections.end(); ++i)
	{
		delete i->second;
	}

	count = broadcastConnections.getCount();
	for (int i = 0; i < count; ++i)
	{
		if (broadcastConnections[i] != &broadcastUdpConnection)
		{
			delete broadcastConnections[i];
		}
	}
}



void Session::setTimeout(double newTimeout)
{
	if (checkArgumentIsValidFloat(NAME_VALUE(newTimeout)) == true &&
		checkArgumentMin(NAME_VALUE(newTimeout), 0.0) == true &&
		newTimeout != timeout)
	{
		timeout = newTimeout;
	}
}



void Session::addPotentialPeerAddress(const String& address)
{
	if (isConnected() == false)
	{
		IpAddress ipAddress = address;
		if (ipAddress.getPort() == 0)
		{
			ipAddress.setPort(port);
		}
		potentialPeerAddresses += ipAddress;
	}
	else
	{
		stateError("Can't add potential peer addresses while connected!" ERROR_AT);
	}
}



void Session::setActingAsGateway(bool actAsGateway)
{
	if (isConnected() == false)
	{
		actingAsGateway = actAsGateway;
	}
	else
	{
		stateError("Gateway setting can only be changed when not connected!" ERROR_AT);
	}
}



void Session::findPeers()
{
	if (isConnected() == false)
	{
		peers.clear();
		gateways.clear();
		sessionInfos.clear();

		// Broadcast request
		UdpConnection broadcastConnection(timeout);
		broadcastConnection.connect(IpAddress(IpNumber::getBroadCastNumber(), port));
		uint16 broadcastRequestId = getNewRequestId();
		Header header(PING_REQUEST, broadcastRequestId, sessionId, userId);
		beginSendMessageInternal(broadcastConnection, header, PING_REQUEST_MESSAGE_SIZE);
		broadcastConnection.endSendMessage();

		// Receive responses for broadcast
		broadcastConnection.connect(IpAddress(0, port));
		double endTime = Time::nowInSeconds() + timeout;
		do
		{
			Thread::sleepSeconds(0.01);

			int messageSize = beginReceiveMessageInternal(broadcastConnection, header);
			if (messageSize == PING_RESPONSE_MESSAGE_SIZE && header.messageType == PING_RESPONSE)
			{
				bool8 peerIsGateway;
				broadcastConnection.inputStream() >> peerIsGateway;
				if (header.requestId == broadcastRequestId)
				{
					IpAddress peerAddress = broadcastConnection.getPeerAddress();
					peers[peerAddress] = PEER_TYPE_BROADCASTABLE_UDP;
					if (peerIsGateway == true)
					{
						gateways.insert(peerAddress);
					}
				}
				broadcastConnection.endReceiveMessage();
			}
		}
		while (Time::nowInSeconds() < endTime);

		// Try to connect potential peers directly via UDP, that haven't answered the broadcast request
		UdpConnection udpConnection(timeout);
		uint16 udpRequestId = getNewRequestId();
		foreach (PotentialPeerAddresses::Iterator, i, potentialPeerAddresses)
		{
			if (peers.find(*i) == peers.end())
			{
				udpConnection.connect(*i);
				header.requestId = udpRequestId;
				beginSendMessageInternal(udpConnection, header, 0);
				udpConnection.endSendMessage();
			}
		}
		// Receive responses from peers that were connected directly
		endTime = Time::nowInSeconds() + timeout;
		do
		{
			Thread::sleepSeconds(0.01);

			int messageSize = beginReceiveMessageInternal(udpConnection, header);
			if (messageSize == PING_RESPONSE_MESSAGE_SIZE && header.messageType == PING_RESPONSE)
			{
				bool8 peerIsGateway;
				udpConnection.inputStream() >> peerIsGateway;
				if (header.requestId == udpRequestId)
				{
					IpAddress peerAddress = udpConnection.getPeerAddress();
					peers[peerAddress] = PEER_TYPE_BROADCASTABLE_UDP;
					if (peerIsGateway == true)
					{
						gateways.insert(peerAddress);
					}
				}
				udpConnection.endReceiveMessage();
			}
		}
		while (Time::nowInSeconds() < endTime);

		// Try to connect potential peers via TCP, that haven't answered the UDP request
		TcpConnection tcpConnection(timeout);
		foreach (PotentialPeerAddresses::Iterator, i, potentialPeerAddresses)
		{
			if (peers.find(*i) == peers.end())
			{
				tcpConnection.connect(*i);
				uint16 tcpRequestId = getNewRequestId();
				header.requestId = tcpRequestId;
				beginSendMessageInternal(tcpConnection, header, 0);
				tcpConnection.endSendMessage();

				// Receive responses from peers that were connected directly
				endTime = Time::nowInSeconds() + timeout;
				do
				{
					Thread::sleepSeconds(0.01);

					int messageSize = beginReceiveMessageInternal(tcpConnection, header);
					if (messageSize == PING_RESPONSE_MESSAGE_SIZE && header.messageType == PING_RESPONSE)
					{
						bool8 peerIsGateway;
						tcpConnection.inputStream() >> peerIsGateway;
						if (header.requestId == tcpRequestId)
						{
							IpAddress peerAddress = tcpConnection.getPeerAddress();
							peers[peerAddress] = PEER_TYPE_TCP;
							if (peerIsGateway == true)
							{
								gateways.insert(peerAddress);
							}
						}
						tcpConnection.endReceiveMessage();
					}
				}
				while (Time::nowInSeconds() < endTime);
			}
		}
	}
	else
	{
		stateError("Can't find peers when connected!" ERROR_AT);
	}
}



void Session::findSessions()
{
	if (isConnected() == false)
	{
		sessionInfos.clear();

		for (uint i = 0; i < peers.size()*4; ++i)
		{
			AutoPointer<AbstractConnection> connection = createRandomConnection(Socket::TCP);

			uint16 requestId = getNewRequestId();
			Header header;
			header.messageType = ENUM_SESSIONS_REQUEST;
			header.requestId = requestId;
			header.sessionId = sessionId;
			header.userId = userId;

			beginSendMessageInternal(*connection, header, 0);
			connection->endSendMessage();

			Thread::sleepSeconds(0.05);
			int messageSize = beginReceiveMessageInternal(*connection, header);
			if (messageSize > sizeof(uint16) && header.messageType == ENUM_SESSIONS_RESPONSE && header.requestId == requestId)
			{
				// uint16 sessionCount[uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, uint16 userCount[uint16 userId, char16 * userName, char16 * ipAddress]]
				uint16 sessionCount;
				connection->inputStream() >> sessionCount;
				for (int s = 0; s < sessionCount; ++s)
				{
					uint16 sessionId;
					connection->inputStream() >> sessionId;
					SessionInfo& sessionInfo = sessionInfos[sessionId] = SessionInfo();
					connection->inputStream() >> sessionInfo.name;
					connection->inputStream() >> sessionInfo.type;
					connection->inputStream() >> sessionInfo.passwordProtected;

					uint16 userCount;
					connection->inputStream() >> userCount;
					for (int u = 0; u < userCount; ++u)
					{
						uint16 userId;
						connection->inputStream() >> userId;
						UserInfo& userInfo = sessionInfo.userInfos[userId] = UserInfo();
						connection->inputStream() >> userInfo.name;
						String ipAddressAsString;
						connection->inputStream() >> ipAddressAsString;
						userInfo.ipAddress = ipAddressAsString;
					}
				}

				connection->endReceiveMessage();
				break;
			}
			else
			{
				readMessageToVoid(connection->inputStream(), messageSize);
				connection->endReceiveMessage();
			}
		}
	}
	else
	{
		stateError("Can't find sessions when connected!" ERROR_AT);
	}
}



void Session::enumSessionIds(const Enumerator<int>& enumerator) const
{
	for (SessionInfos::const_iterator i = sessionInfos.begin(); i != sessionInfos.end(); ++i)
	{
		enumerator.enumerate(i->first);
	}
}



AbstractConnection* Session::createRandomConnection(Socket::ProtocolType protocolType) const
{
	int peerCount = peers.size();
	if (peerCount > 0)
	{
		int peerIndex = rand() * peerCount / RAND_MAX;
		Peers::const_iterator peerIterator = peers.begin();
		for (int i = 0; i < peerIndex && peerIterator != peers.end(); ++i, ++peerIterator);

		if (peerIterator != peers.end())
		{
			AbstractConnection* connection;
			if (protocolType == Socket::TCP || peerIterator->second == PEER_TYPE_TCP)
			{
				connection = new TcpConnection(timeout);
			}
			else
			{
				connection = new UdpConnection(timeout);
			}

			connection->connect(peerIterator->first);

			if (connection->isConnected() == true)
			{
				lastPeerIndex = peerIndex;
				setupConnectionStreams(*connection);
				return connection;
			}
			else
			{
				delete connection;
			}
		}
	}
	return NULL;
}



AbstractConnection* Session::createRandomSessionConnection(Socket::ProtocolType protocolType, uint16 idOfSession) const
{
	if (idOfSession == 0)
	{
		idOfSession = sessionId;
	}

	SessionInfos::const_iterator s = sessionInfos.find(idOfSession);
	if (s != sessionInfos.end())
	{
		const UserInfos& userInfos = s->second.userInfos;

		int userIndex = rand() * userInfos.size() / RAND_MAX;
		UserInfos::const_iterator userIterator = userInfos.begin();
		for (int i = 0; i < userIndex && userIterator != userInfos.end(); ++i, ++userIterator);
		if (userIterator != userInfos.end())
		{
			const UserInfo& userInfo = userIterator->second;
			Peers::const_iterator peerIterator = peers.find(userInfo.ipAddress);
			BL_ASSERT(peerIterator != peers.end());

			AbstractConnection* connection;			
			if (protocolType == Socket::TCP || peerIterator->second == PEER_TYPE_TCP)
			{
				connection = new TcpConnection(timeout);
			}
			else
			{
				connection = new UdpConnection(timeout);
			}

			connection->connect(userInfo.ipAddress);

			if (connection->isConnected() == true)
			{
				setupConnectionStreams(*connection);
				return connection;
			}
			else
			{
				delete connection;
			}
		}
	}
	return NULL;
}



AbstractConnection* Session::createNextConnection(Socket::ProtocolType protocolType) const
{
	int peerCount = peers.size();
	if (peerCount > 0)
	{
		int peerIndex = lastPeerIndex + 1;
		Peers::const_iterator peerIterator = peers.begin();
		for (int i = 0; i < peerIndex; ++i, ++peerIterator)
		{
			if (peerIterator == peers.end())
			{
				peerIndex = 0;
				peerIterator = peers.begin();
				break;
			}
		}

		if (peerIterator != peers.end())
		{
			AbstractConnection* connection;
			if (protocolType == Socket::TCP || peerIterator->second == PEER_TYPE_TCP)
			{
				connection = new TcpConnection(timeout);
			}
			else
			{
				connection = new UdpConnection(timeout);
			}

			connection->connect(peerIterator->first);

			if (connection->isConnected() == true)
			{
				lastPeerIndex = peerIndex;
				setupConnectionStreams(*connection);
				return connection;
			}
			else
			{
				delete connection;
			}
		}
	}
	return NULL;
}



String Session::getSessionName(int idOfSession) const
{
	SessionInfos::const_iterator i = sessionInfos.find(static_cast<uint16>(idOfSession));
	if (i != sessionInfos.end())
	{
		return i->second.name;
	}
	else
	{
		argumentError("Invalid session id!" ERROR_AT);
		return Empty();
	}
}



String Session::getSessionType(int idOfSession) const
{
	SessionInfos::const_iterator i = sessionInfos.find(static_cast<uint16>(idOfSession));
	if (i != sessionInfos.end())
	{
		return i->second.type;
	}
	else
	{
		argumentError("Invalid session id!" ERROR_AT);
		return Empty();
	}
}



bool Session::isSessionPasswordProtected(int idOfSession) const
{
	SessionInfos::const_iterator i = sessionInfos.find(static_cast<uint16>(idOfSession));
	if (i != sessionInfos.end())
	{
		return i->second.passwordProtected;
	}
	else
	{
		argumentError("Invalid session id!" ERROR_AT);
		return false;
	}
}



void Session::joinSession(int idOfSession, const String& ownUserName, const String& password)
{
	if (checkState(NAME_VALUE(isConnected())) == false)
	{
		AutoPointer<AbstractConnection> connection = createRandomSessionConnection(Socket::TCP, idOfSession);
		if (connection != NULL)
		{
			uint16 requestId = getNewRequestId();
			Header header(CHECK_PASSWORD_REQUEST, requestId, sessionId, userId);
			beginSendMessageInternal(*connection, header, (password.getLength()+1) * sizeof(char16));
			connection->outputStream() << password;
			connection->endSendMessage();

			int messageSize = beginReceiveMessageInternal(*connection, header);
			bool8 validPassword = false;
			if (header.messageType == CHECK_PASSWORD_RESPONSE && header.requestId == requestId && messageSize == CHECK_PASSWORD_RESPONSE_MESSAGE_SIZE)
			{
				connection->inputStream() >> validPassword;
			}
			connection->endReceiveMessage();

			if (validPassword == true)
			{
				sessionPassword = password;
				sessionId = idOfSession;
				userId = getUnusedUserId();
				userName = ownUserName;

				SessionInfos::iterator s = sessionInfos.find(sessionId);
				BL_ASSERT(s != sessionInfos.end());
				currentSessionInfo = s->second;
				UserInfos& userInfos = currentSessionInfo.userInfos;
				for (UserInfos::iterator u = userInfos.begin(); u != userInfos.end(); ++u)
				{
					const UserInfo& userInfo = u->second;
					PeerType peerType = peers[userInfo.ipAddress];
					if (peerType != PEER_TYPE_BROADCASTABLE_UDP)
					{
						AbstractConnection* connection;
						if (peerType == PEER_TYPE_NON_BROADCASTABLE_UDP)
						{
							connection = new UdpConnection(timeout);
						}
						else 
						{
							BL_ASSERT(peerType == PEER_TYPE_TCP);
							connection = new TcpConnection(timeout);
						}
						connection->connect(userInfo.ipAddress);
						sessionConnections[userId] = connection;
						broadcastConnections += connection;
						receiveConnections += connection;

						// TODO: 2 Connections, jeweils von einer Seite her, sollte nur eine Connection sein!!
					}
				}

				Header header(JOINING_SESSION_MESSAGE, getNewRequestId(), sessionId, userId);
				int messageSize = 0; ///
				int count = broadcastConnections.getCount();
				for (int i = 0; i < count; ++i)
				{
					beginSendMessageInternal(*broadcastConnections[i], header, messageSize);
					broadcastConnections[i]->outputStream() << userName;
					broadcastConnections[i]->endSendMessage();
				}
			}
		}
	}
}



void Session::startSession(const String& sessionName, const String& sessionType, const String& sessionPassword, const String& ownUserName)
{
	userName = ownUserName;
	userId = 1;

	sessionId = getUnusedSessionId();
	currentSessionInfo.name = sessionName;
	currentSessionInfo.type = sessionType;
	currentSessionInfo.passwordProtected = sessionPassword.isEmpty() == false;
	currentSessionInfo.userInfos[userId] = UserInfo(userName, IpAddress(IpNumber("localhost"), port));

	Header header(NEW_SESSION_STARTED_MESSAGE, getNewRequestId(), sessionId, userId);
	BinaryMemBuffer buffer;
	BinaryOutputStream bufferStream(buffer);
	// uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, char16 * startingUserName
	bufferStream << sessionId;
	bufferStream << sessionName;
	bufferStream << sessionType;
	bufferStream << (sessionPassword.isEmpty() == false);
	bufferStream << userName;

	for (Peers::iterator p = peers.begin(); p != peers.end(); ++p)
	{
		const IpAddress& peerIpAddres = p->first;
		const PeerType peerType = p->second;
		const Socket::ProtocolType protocolType = peerType == PEER_TYPE_TCP ? Socket::TCP : Socket::UDP;

		AutoPointer<AbstractConnection> connection = AbstractConnection::create(protocolType, timeout);
		BL_ASSERT(connection != NULL);

		beginSendMessageInternal(*connection, header, buffer.getSizeAsInt());
		connection->outputStream() << buffer;
		connection->endSendMessage();
	}
}



double Session::getSessionTimeInSeconds() const
{
	notImplementedError();
	return Time::nowInSeconds(); ///
}



int Session::getSessionId() const
{
	return sessionId;
}



String Session::getSessionName() const
{
	return currentSessionInfo.name;
}



String Session::getSessionType() const
{
	return currentSessionInfo.type;
}



void Session::enumSessionUserIds(const Enumerator<int>& enumerator) const
{
	const UserInfos& userInfos = currentSessionInfo.userInfos;
	for (UserInfos::const_iterator u = userInfos.begin(); u != userInfos.end(); ++u)
	{
		enumerator.enumerate(u->first);
	}
}



String Session::getSessionUserName(int forUserId) const
{
	const UserInfos& userInfos = currentSessionInfo.userInfos;
	for (UserInfos::const_iterator u = userInfos.begin(); u != userInfos.end(); ++u)
	{
		if (u->first == forUserId)
		{
			return u->second.name;
		}
	}
	return Empty();
}



int Session::beginSendMessage(int targetUserId, int messageType, int messageSize) const
{
	if (checkArgumentMin(NAME_VALUE(messageType), 1) == true &&
		checkArgumentMin(NAME_VALUE(messageSize), 1) == true)
	{
		SessionConnections::const_iterator i = sessionConnections.find(targetUserId);
		if (i != sessionConnections.end())
		{
			while (currentSendConnectionsCount > 0)
			{
				Thread::yield();
			}
			currentSendConnectionsCount = 1;
			currentSendConnections = &i->second;
			BL_ASSERT(currentOutputStream.isConnected() == false);
			currentOutputStream.disconnectFromAllStreams();
			currentOutputStream.connectToStream(currentSendConnections[0]->outputStream());
			Header header(messageType, getNewRequestId(), sessionId, userId);
			beginSendMessageInternal(*currentSendConnections[0], header, messageSize);
			return header.requestId;
		}
		else
		{
			argumentError("No user with id=" + String::createFrom(targetUserId) + " !" ERROR_AT);
		}
	}
	return 0;
}



int Session::beginBroadcastMessage(int messageType, int messageSize) const
{
	if (checkArgumentMin(NAME_VALUE(messageType), 1) == true &&
		checkArgumentMin(NAME_VALUE(messageSize), 1) == true)
	{
		while (currentSendConnectionsCount > 0)
		{
			Thread::yield();
		}
		currentSendConnectionsCount = broadcastConnections.getCount();
		currentSendConnections = &broadcastConnections[0];
		BL_ASSERT(currentOutputStream.isConnected() == false);
		currentOutputStream.disconnectFromAllStreams();
		Header header(messageType, getNewRequestId(), sessionId, userId);
		for (int i = 0; i < currentSendConnectionsCount; ++i)
		{
			currentOutputStream.connectToStream(currentSendConnections[i]->outputStream());
			beginSendMessageInternal(*currentSendConnections[i], header, messageSize);
		}
		return header.requestId;
	}
	return 0;
}



BinaryOutputStream& Session::outputStream()
{
	return currentOutputStream;	
}



const BinaryOutputStream& Session::outputStream() const
{
	return currentOutputStream;	
}



void Session::endSendMessage() const
{
	currentOutputStream.disconnectFromAllStreams();
	for (int i = 0; i < currentSendConnectionsCount; ++i)
	{
		currentSendConnections[i]->endSendMessage();
	}
	currentSendConnections = NULL;
	currentSendConnectionsCount = 0;
}



bool Session::beginReceiveMessage(int& sourceUserId, int& requestId, int& messageType, int& messageSize) const
{
	if (currentInputConnection == NULL)
	{
		for (ConnectionsArray::ConstIterator i = receiveConnections.begin(); i != receiveConnections.end(); ++i)
		{
			currentInputConnection = *i;
			Header header;
			messageSize = beginReceiveMessageInternal(*currentInputConnection, header);

			if (messageSize < 0)
			{
				currentInputConnection = NULL;
				continue;
			}

			if (header.messageType >= 0)
			{
				sourceUserId = header.userId;
				requestId = header.requestId;
				messageType = header.messageType;
				return true;
			}
			else
			{
				const_cast<Session*>(this)->handleIsAlivePing(messageSize, header);
				const_cast<Session*>(this)->respondToSessionMessages(messageSize, header);
				currentInputConnection->endReceiveMessage();
			}
		}
	}

	return false;
}



void Session::handleIsAlivePing(int messageSize, const Header& header)
{
	double time = Time::nowInSeconds();
	if (time > timeForIsAlivePing)
	{
		AutoPointer<AbstractConnection> isAlivePingConnection = createRandomConnection(Socket::UDP);
		if (isAlivePingConnection != NULL)
		{
			ipAddressOfLastIsAlivePing = isAlivePingConnection->getPeerAddress();
			requestIdOfLastIsAlivePing = getNewRequestId();
			Header header(PING_REQUEST, requestIdOfLastIsAlivePing, sessionId, userId);
			beginSendMessageInternal(*isAlivePingConnection, header, PING_REQUEST_MESSAGE_SIZE);
			isAlivePingConnection->endSendMessage();
		}
		timeForIsAlivePing = time + secondsBetweenIsAlivePings;
	}
	else if (
		header.messageType == PING_RESPONSE &&
		messageSize == PING_RESPONSE_MESSAGE_SIZE &&
		header.requestId == requestIdOfLastIsAlivePing &&
		currentInputConnection->getPeerAddress() == ipAddressOfLastIsAlivePing)
	{
		requestIdOfLastIsAlivePing = 0;
	}

	if (requestIdOfLastIsAlivePing != 0 && time > (timeForIsAlivePing - secondsBetweenIsAlivePings + timeout))
	{
		removePeer(ipAddressOfLastIsAlivePing);

		AutoPointer<AbstractConnection> isAlivePingConnection = createNextConnection(Socket::UDP);
		if (isAlivePingConnection != NULL)
		{
			ipAddressOfLastIsAlivePing = isAlivePingConnection->getPeerAddress();
			requestIdOfLastIsAlivePing = getNewRequestId();
			Header header(PING_REQUEST, requestIdOfLastIsAlivePing, sessionId, userId);
			beginSendMessageInternal(*isAlivePingConnection, header, PING_REQUEST_MESSAGE_SIZE);
			isAlivePingConnection->endSendMessage();
		}
		timeForIsAlivePing = time + secondsBetweenIsAlivePings;
	}
}



void Session::respondToSessionMessages(int messageSize, Header& header)
{
	switch (header.messageType)
	{
		case PING_REQUEST:
		{
			const IpAddress& peerAddress = currentInputConnection->getPeerAddress();
			if (peers.find(peerAddress) == peers.end())
			{
				if (currentInputConnection->getSocketProtocolType() == Socket::TCP)
				{
					peers[peerAddress] = PEER_TYPE_TCP;
				}
				else
				{
					peers[peerAddress] = PEER_TYPE_NON_BROADCASTABLE_UDP;
				}

				// TODO: test for PEER_TYPE_NON_BROADCASTABLE_UDP
			}

			header.messageType = PING_RESPONSE;
			header.sessionId = sessionId;
			header.userId = userId;
			beginSendMessageInternal(*currentInputConnection, header, sizeof(bool8));
			currentInputConnection->outputStream() << actingAsGateway;
			currentInputConnection->endSendMessage();
			return;
		}

		case ENUM_SESSIONS_REQUEST:
		{
			header.messageType = ENUM_SESSIONS_RESPONSE;
			header.sessionId = sessionId;
			header.userId = userId;

			BinaryMemBuffer buffer;
			BinaryOutputStream bufferStream(buffer);

			// uint16 sessionCount[uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, uint16 userCount[uint16 userId, char16 * userName, char16 * ipAddress]]
			bufferStream << static_cast<uint16>(sessionInfos.size());
			for (SessionInfos::const_iterator s = sessionInfos.begin(); s != sessionInfos.end(); ++s)
			{
				bufferStream << s->first;
				bufferStream << s->second.name;
				bufferStream << s->second.type;
				bufferStream << s->second.passwordProtected;

				const UserInfos& userInfos = s->second.userInfos;
				bufferStream << static_cast<uint16>(userInfos.size());
				for (UserInfos::const_iterator u = userInfos.begin(); u != userInfos.end(); ++u)
				{
					bufferStream << u->first;
					bufferStream << u->second.name;
					bufferStream << u->second.ipAddress.operator String();
				}
			}

			beginSendMessageInternal(*currentInputConnection, header, buffer.getSizeAsInt());
			currentInputConnection->outputStream() << buffer;
			currentInputConnection->endSendMessage();
			return;
		}

		case CHECK_PASSWORD_REQUEST:
		{
			header.messageType = CHECK_PASSWORD_RESPONSE;
			header.sessionId = sessionId;
			header.userId = userId;

			String requestPassword;
			currentInputConnection->inputStream() >> requestPassword;

			bool8 response = (header.sessionId == sessionId && requestPassword == sessionPassword);

			beginSendMessageInternal(*currentInputConnection, header, CHECK_PASSWORD_RESPONSE_MESSAGE_SIZE);
			currentInputConnection->outputStream() << response;
			currentInputConnection->endSendMessage();
			return;
		}

		case JOINING_SESSION_MESSAGE:
		{
			if (header.sessionId == sessionId && sessionId != 0)
			{
				const IpAddress& peerAddress = currentInputConnection->getPeerAddress();
				AbstractConnection* connection;
				if (currentInputConnection->getSocketProtocolType() == Socket::TCP)
				{
					if (peers.find(peerAddress) == peers.end())
					{
						peers[peerAddress] = PEER_TYPE_TCP;
					}
					connection = new TcpConnection(timeout);
				}
				else
				{
					if (peers.find(peerAddress) == peers.end())
					{
						peers[peerAddress] = PEER_TYPE_NON_BROADCASTABLE_UDP;
					}
					connection = new UdpConnection(timeout);
				}
				// TODO: test for PEER_TYPE_NON_BROADCASTABLE_UDP
				connection->connect(peerAddress);
				sessionConnections[header.userId] = connection;
				
				broadcastConnections += connection;

				if (connection->getSocketProtocolType() == Socket::TCP)
				{
					receiveConnections += connection;
				}

				String newUserId;
				currentInputConnection->inputStream() >> newUserId;

				sessionInfos[sessionId].userInfos[userId] = UserInfo(newUserId, peerAddress);
			}
			return;
		}

		case LEAVING_SESSION_MESSAGE:
		{
			//for (int i = 0; i < currentSendConnectionsCount; ++i)
			//{
			//	if (
			//}
			while (currentSendConnectionsCount > 0) // TODO: Lock eigentlich nur für die zu entfernende Verbindung notwendig
			{
				Thread::yield();
			}

			removeUserConnections(header.userId, currentInputConnection->getPeerAddress());
		}

		case NEW_SESSION_STARTED_MESSAGE:
		{
			// uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, char16 * startingUserName
			uint16 newSessionId;
			String newSessionName;
			String newSessionType;
			bool8 passwordProtected;
			String startingUserName;

			currentInputConnection->inputStream() >> newSessionId;
			currentInputConnection->inputStream() >> newSessionName;
			currentInputConnection->inputStream() >> newSessionType;
			currentInputConnection->inputStream() >> passwordProtected;
			currentInputConnection->inputStream() >> startingUserName;

			sessionInfos[newSessionId] = SessionInfo(newSessionName, newSessionType, passwordProtected);
			sessionInfos[newSessionId].userInfos[1] = UserInfo(startingUserName, currentInputConnection->getPeerAddress());
		}

		default:
			readMessageToVoid(messageSize);
	}
}



void Session::removePeer(int peerIndex)
{
	Peers::iterator peerIterator = peers.begin();
	for (int i = 0; i < peerIndex; ++i, ++peerIterator);
	if (peerIterator != peers.end())
	{
		IpAddress peerIpAddress = peerIterator->first;

		// Peers
		peers.erase(peerIterator);

		// Gateways
		gateways.erase(peerIpAddress);

		// Sessions
		uint16 userIdToRemove = 0;
		for (SessionInfos::iterator sessionIterator = sessionInfos.begin(); sessionIterator != sessionInfos.end(); ++sessionIterator)
		{
			UserInfos& userInfos = sessionIterator->second.userInfos;
			for (UserInfos::iterator userIterator = userInfos.begin(); userIterator != userInfos.end(); ++userIterator)
			{
				if (userIterator->second.ipAddress == peerIpAddress)
				{
					userIdToRemove = userIterator->first;
					userInfos.erase(userIterator);
					break;
				}
			}
		}
		
		// Connections
		removeUserConnections(userIdToRemove, peerIpAddress);
	}
}



void Session::removePeer(const IpAddress& peerIpAddress)
{
	// Peers
	peers.erase(peerIpAddress);

	// Gateways
	gateways.erase(peerIpAddress);

	// Sessions
	uint16 userIdToRemove = 0;
	for (SessionInfos::iterator sessionIterator = sessionInfos.begin(); sessionIterator != sessionInfos.end(); ++sessionIterator)
	{
		UserInfos& userInfos = sessionIterator->second.userInfos;
		for (UserInfos::iterator userIterator = userInfos.begin(); userIterator != userInfos.end(); ++userIterator)
		{
			if (userIterator->second.ipAddress == peerIpAddress)
			{
				userIdToRemove = userIterator->first;
				userInfos.erase(userIterator);
				break;
			}
		}
	}

	// Connections
	removeUserConnections(userIdToRemove, peerIpAddress);
}



void Session::removeUserConnections(uint16 userIdToRemove, const IpAddress& peerIpAddress)
{
	SessionConnections::iterator c = sessionConnections.find(userIdToRemove);
	if (c != sessionConnections.end())
	{
		delete c->second;
		sessionConnections.erase(c);

		int count = broadcastConnections.getCount();
		for (int i = 0; i < count; ++i)
		{
			if (broadcastConnections[i]->getPeerAddress() == peerIpAddress)
			{
				delete broadcastConnections[i];
				broadcastConnections.remove(i);
				break;
			}
		}
		count = receiveConnections.getCount();
		for (int i = 0; i < count; ++i)
		{
			if (receiveConnections[i]->getPeerAddress() == peerIpAddress)
			{
				delete receiveConnections[i];
				receiveConnections.remove(i);
				break;
			}
		}
	}
}


uint16 Session::getUnusedUserId() const
{
	SessionInfos::const_iterator s = sessionInfos.find(sessionId);
	if (s != sessionInfos.end())
	{
		uint16 result = 0;
		const UserInfos& userInfos = s->second.userInfos;
		for (UserInfos::const_iterator u = userInfos.begin(); u != userInfos.end(); ++u)
		{
			result = max(u->first, result);
		}
		return result + 1;
	}
	else
	{
		return 0;
	}
}



uint16 Session::getUnusedSessionId() const
{
	uint16 result = 0;
	for (SessionInfos::const_iterator i = sessionInfos.begin(); i != sessionInfos.end(); ++i)
	{
		result = max(i->first, result);
	}
	return result + 1;
}



BinaryInputStream& Session::inputStream()
{
	if (currentInputConnection != NULL)
	{
		return currentInputConnection->inputStream();
	}
	else
	{
		static BinaryInputStream dummyInputStream;
		return dummyInputStream;
	}
}



const BinaryInputStream& Session::inputStream() const
{
	if (currentInputConnection != NULL)
	{
		return currentInputConnection->inputStream();
	}
	else
	{
		static BinaryInputStream dummyInputStream;
		return dummyInputStream;
	}
}



void Session::endReceiveMessage() const
{
	if (currentInputConnection != NULL)
	{
		currentInputConnection->endReceiveMessage();
		currentInputConnection = NULL;
	}
}



void Session::setMessageListener(int messageType, const MessageListenerFunctor& functor)
{
	if (checkArgumentRange(NAME_VALUE(messageType), 0, (int)INT16_MAX) == true)
	{
		int arrayLength = messageListenerFunctors.getCount();
		if (messageType >= arrayLength)
		{
			messageListenerFunctors.setCount(messageType + 1);
			for (int i = arrayLength; i < messageType; ++i)
			{
				messageListenerFunctors[i] = NULL;
			}
		}

		messageListenerFunctors[messageType] = functor.clone();
	}
}



void Session::receiveMessages() const
{
	int sourceUserId;
	int requestId;
	int messageType;
	int messageSize;
	while (beginReceiveMessage(sourceUserId, requestId, messageType, messageSize) == true)
	{
		BL_ASSERT(messageType >= 0);
		if (messageType < messageListenerFunctors.getCount())
		{
			(*messageListenerFunctors[messageType])(sourceUserId, messageSize, inputStream());
		}
		else
		{
			readMessageToVoid(messageSize);
		}
		endReceiveMessage();
	}		
}



void Session::receiveMessages(double maxTime) const
{
	double endTime = Time::nowInSeconds() + maxTime;
	int sourceUserId;
	int requestId;
	int messageType;
	int messageSize;
	while (Time::nowInSeconds() < endTime && beginReceiveMessage(sourceUserId, requestId, messageType, messageSize) == true)
	{
		BL_ASSERT(messageType >= 0);
		if (messageType < messageListenerFunctors.getCount())
		{
			(*messageListenerFunctors[messageType])(sourceUserId, messageSize, inputStream());
		}
		else
		{
			readMessageToVoid(messageSize);
		}
		endReceiveMessage();
	}		
}



void Session::readMessageToVoid(int messageSize) const
{
	readMessageToVoid(inputStream(), messageSize);
}



void Session::kickSessionUser(int userId)
{
	notImplementedError();
}



void Session::bannSessionUser(int userId)
{
	notImplementedError();
}



void Session::leaveSession()
{
	if (checkState(NAME_VALUE(isConnected())) == true)
	{
		while (currentSendConnectionsCount > 0)
		{
			Thread::yield();
		}
		currentSendConnectionsCount = broadcastConnections.getCount();
		Header header(LEAVING_SESSION_MESSAGE, getNewRequestId(), sessionId, userId);
		for (int i = 0; i < broadcastConnections.getCount(); ++i)
		{
			beginSendMessageInternal(*broadcastConnections[i], header, LEAVE_SESSION_MESSAGE_SIZE);
			broadcastConnections[i]->endSendMessage();
		}
		currentSendConnectionsCount = 0;
		sessionId = 0;
		userId = 0;
		userName = Empty();
		currentSessionInfo.name = Empty();
		currentSessionInfo.type = Empty();
		currentSessionInfo.passwordProtected = false;
		currentSessionInfo.userInfos.clear();
		sessionConnections.clear();
		broadcastConnections.setCount(0);
		receiveConnections.setCount(0);
	}
}



void Session::beginSendMessageInternal(const AbstractConnection& connection, const Header& header, uint32 messageSize) const
{
	BL_ASSERT(messageSize >= 0);
	connection.beginSendMessage(messageSize + sizeof(Header));
	connection.outputStream() << header.messageType;
	connection.outputStream() << header.requestId;
	connection.outputStream() << header.sessionId;
	connection.outputStream() << header.userId;
}



int Session::beginReceiveMessageInternal(const AbstractConnection& connection, Header& header) const
{
	int messageSize = connection.beginReceiveMessage();
	if (messageSize >= sizeof(Header))
	{
		connection.inputStream() >> header.messageType;
		connection.inputStream() >> header.requestId;
		connection.inputStream() >> header.sessionId;
		connection.inputStream() >> header.userId;
	}
	return messageSize - sizeof(Header);
}



void Session::readMessageToVoid(const BinaryInputStream& inputStream, int messageSize) const
{
	static BinaryMemBuffer buffer(messageSize);
	if (buffer.getSizeAsInt() < messageSize)
	{
		buffer.setSize(messageSize);
	}
	inputStream.readBinaryComplete(buffer.getPointer(), messageSize, timeout);
}



void Session::setSecondsBetweenIsAlivePings(double newSecondsBetweenIsAlivePings)
{
	if (checkArgumentGreater(NAME_VALUE(newSecondsBetweenIsAlivePings), timeout) == true)
	{
		secondsBetweenIsAlivePings = newSecondsBetweenIsAlivePings;
	}
}


} // namespace Network
} // namespace BaseLib
