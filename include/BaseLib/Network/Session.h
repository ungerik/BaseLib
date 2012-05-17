/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Network_Session_h
#define BaseLib_Network_Session_h



#include "BaseLib/Network/AbstractConnection.h"
#include "BaseLib/Network/UdpConnection.h"
#include "BaseLib/Network/TcpConnection.h"
#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/Functors/Functor3.h"
#include <map>
#include <set>



namespace BaseLib {
namespace Network {



using BaseLib::Functors::Enumerator;
using BaseLib::Functors::Functor3;
using BaseLib::Functors::FunctionFunctor3;
using BaseLib::Functors::MethodFunctor3;
using BaseLib::Containers::Array;



/**

Protocol:

+-----------+
| uint32    | byteCount
+-----------+
| int16     | messageType
+-----------+
| int16     | requestId
+-----------+
| uint16    | sessionId
+-----------+
| uint16    | userId
+-----------+
|           |
| byteCount | sessionMessage
| -6 bytes  | 
|           |
+-----------+

*/
class BL_EXPORT Session : public NonCopyable {
public:

	//                     userId messageSize messageDataInputStream
	typedef Functor3<void, int,   int,        const BinaryInputStream&> MessageListenerFunctor;

	typedef FunctionFunctor3<void, int, int, const BinaryInputStream&> MessageListenerFunctionFunctor;

	template<class C>
	class BL_EXPORT MessageListenerMethodFunctor : public MethodFunctor3<C, void, int, int, const BinaryInputStream&> {
	public:
		MessageListenerMethodFunctor(C* atObject, Method forMethod)
			: MethodFunctor3(atObject, forMethod)
		{
		}
	};

	Session(uint16 port, double defaultTimeout = 1.0);
	~Session();

	inline double getTimeout() const
	{
		return timeout;
	}

	void setTimeout(double newTimeout);

	// While not connected

	void addPotentialPeerAddress(const String& address);
	inline bool isActingAsGateway() const
	{
		return actingAsGateway;
	}
	void setActingAsGateway(bool actAsGateway = true);

	void findPeers();
	void findSessions();
	void enumSessionIds(const Enumerator<int>& enumerator) const;
	String getSessionName(int idOfSession) const;
	String getSessionType(int idOfSession) const;
	bool isSessionPasswordProtected(int idOfSession) const;

	void joinSession(int idOfSession, const String& ownUserName, const String& password = Empty());
	void startSession(const String& sessionName, const String& sessionType, const String& sessionPassword, const String& ownUserName);

	inline bool isConnected() const
	{
		return sessionId != 0 && userId != 0;
	}

	// While connected

	double getSessionTimeInSeconds() const;
	int getSessionId() const; // 0 if not joined
	String getSessionName() const;
	String getSessionType() const;

	inline int getUserId() const
	{
		return userId;
	}
	inline String getUserName() const
	{
		return userName;
	}

	void enumSessionUserIds(const Enumerator<int>& enumerator) const;
	String getSessionUserName(int forUserId) const;

	int beginSendMessage(int targetUserId, int messageType, int messageSize) const; // returns requestId
	int beginBroadcastMessage(int messageType, int messageSize) const; // returns requestId
	BinaryOutputStream& outputStream();
	const BinaryOutputStream& outputStream() const;
	void endSendMessage() const;

	bool beginReceiveMessage(int& sourceUserId, int& requestId, int& messageType, int& messageSize) const;
	BinaryInputStream& inputStream();
	const BinaryInputStream& inputStream() const;
	void readMessageToVoid(int messageSize) const;
	void endReceiveMessage() const;

	void setMessageListener(int messageType, const MessageListenerFunctor& functor);
	void receiveMessages() const;
	void receiveMessages(double maxTime) const;

	void kickSessionUser(int userId);
	void bannSessionUser(int userId);
	void leaveSession();

	inline double getSecondsBetweenIsAlivePings() const
	{
		return secondsBetweenIsAlivePings;
	}

	void setSecondsBetweenIsAlivePings(double newSecondsBetweenIsAlivePings);

private:


	// Peers

	typedef Array<IpAddress> PotentialPeerAddresses;
	PotentialPeerAddresses potentialPeerAddresses;

	enum PeerType {
		PEER_TYPE_BROADCASTABLE_UDP,
		PEER_TYPE_NON_BROADCASTABLE_UDP,
		PEER_TYPE_TCP
	};
	typedef std::map<IpAddress, PeerType> Peers;
	Peers peers;

	typedef std::set<IpAddress> Gateways;
	Gateways gateways;

	struct UserInfo {
		String name;
		IpAddress ipAddress;

		UserInfo(const String& newName = Empty(), const IpAddress& newIpAddress = IpAddress())
			: name(newName)
			, ipAddress(newIpAddress)
		{
		}
	};
	typedef std::map<uint16, UserInfo> UserInfos;

	struct SessionInfo {
		String name;
		String type;
		bool passwordProtected;

		UserInfos userInfos;

		SessionInfo(const String& newName = Empty(), const String& newType = Empty(), bool isPasswordProtected = false)
			: name(newName)
			, type(newType)
			, passwordProtected(isPasswordProtected)
			, userInfos()
		{
		}
	};
	typedef std::map<uint16, SessionInfo> SessionInfos;
	mutable SessionInfos sessionInfos;

	double timeForIsAlivePing;
	uint16 requestIdOfLastIsAlivePing;
	IpAddress ipAddressOfLastIsAlivePing;
	double secondsBetweenIsAlivePings;


	// Self

	uint16 port;
	double timeout;
	bool actingAsGateway;

	inline uint16 getNewRequestId() const
	{
		static uint16 requestId = 0;
		return requestId++;
	}


	int sessionId;
	int userId;
	String userName;
	SessionInfo currentSessionInfo;
	String sessionPassword;

	// Messages

	static const int PING_REQUEST_MESSAGE_SIZE;
	static const int PING_RESPONSE_MESSAGE_SIZE;
	static const int LEAVE_SESSION_MESSAGE_SIZE;
	static const int CHECK_PASSWORD_RESPONSE_MESSAGE_SIZE;

	enum MessageType {
		PING_REQUEST = -1, // void
		PING_RESPONSE = -2, // bool8 isGateway
		ENUM_SESSIONS_REQUEST = -3, // void
		ENUM_SESSIONS_RESPONSE = -4, // uint16 sessionCount[uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, uint16 userCount[uint16 userId, char16 * userName, char16 * ipAddress]]
		CHECK_PASSWORD_REQUEST = -5, // char16 * password
		CHECK_PASSWORD_RESPONSE = -6, // bool8 passwordOk
		JOINING_SESSION_MESSAGE = -7, // char16 * userName
		LEAVING_SESSION_MESSAGE = -8, // void
		NEW_SESSION_STARTED_MESSAGE = -9 // uint16 sessionId, char16 * sessionName, char16 * sessionType, bool8 passwordProtected, char16 * startingUserName
	};

	UdpConnection broadcastUdpConnection;
	mutable AbstractConnection* currentInputConnection;

	typedef std::map<int, AbstractConnection*> SessionConnections; // int -> userId
	SessionConnections sessionConnections;

	typedef Array<AbstractConnection*> ConnectionsArray;
	ConnectionsArray broadcastConnections;
	ConnectionsArray receiveConnections;

	typedef Array<MessageListenerFunctor*> MessageListenerFunctors;
	MessageListenerFunctors messageListenerFunctors;

	mutable int currentSendConnectionsCount;
	mutable const AbstractConnection* const* currentSendConnections;
	mutable BinaryOutputStream currentOutputStream;


	// Utility

	struct Header {
		int16 messageType;
		uint16 requestId;
		uint16 sessionId;
		uint16 userId;

		Header(int16 newMessageType = 0, uint16 newRequestId = 0, uint16 newSessionId = 0, uint16 newUserId = 0)
			: messageType(newMessageType)
			, requestId(newRequestId)
			, sessionId(newSessionId)
			, userId(newUserId)
		{
		}
	};

	mutable int lastPeerIndex;
	AbstractConnection* createRandomSessionConnection(Socket::ProtocolType protocolType, uint16 idOfSession = 0) const;
	AbstractConnection* createRandomConnection(Socket::ProtocolType protocolType) const;
	AbstractConnection* createNextConnection(Socket::ProtocolType protocolType) const;
	bool isAddressInPeersMap(const IpAddress& ipAddress) const;
	void removePeer(int peerIndex);
	void removePeer(const IpAddress& peerIpAddress);
	void removeUserConnections(uint16 userIdToRemove, const IpAddress& peerIpAddress);
	void handleIsAlivePing(int messageSize, const Header& header);
	void respondToSessionMessages(int messageSize, Header& header);

	void beginSendMessageInternal(const AbstractConnection& connection, const Header& header, uint32 messageSize) const;
	int beginReceiveMessageInternal(const AbstractConnection& connection, Header& header) const;
	void readMessageToVoid(const BinaryInputStream& inputStream, int messageSize) const;

	uint16 getUnusedUserId() const;
	uint16 getUnusedSessionId() const;
 
};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef BaseLib_Network_Session_h