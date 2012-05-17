/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/GatewayConnection.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



GatewayConnection::GatewayConnection(AbstractConnection* useSendConnection, AbstractConnection* useReceiveConnection, int forTargetUserId)
	: AbstractConnection(useSendConnection != NULL ? useSendConnection->getTimeout() : 0.0)
	, sendConnection(useSendConnection)
	, receiveConnection(useReceiveConnection)
	, targetUserId(forTargetUserId)
{
	checkArgumentMin(NAME_VALUE(forTargetUserId), 0);
	if (checkArgumentNotNull(NAME_VALUE(useSendConnection)) == true)
	{
		binaryOutputStream = useSendConnection->outputStream();
		connected = true;
	}
	if (checkArgumentNotNull(NAME_VALUE(useReceiveConnection)) == true)
	{
		binaryInputStream = useReceiveConnection->inputStream();
	}
}



GatewayConnection::~GatewayConnection()
{
}



Socket::ProtocolType GatewayConnection::getSocketProtocolType() const
{
	return sendConnection != NULL ? sendConnection->getSocketProtocolType() : Socket::TCP;
}	



void GatewayConnection::bindToPort(uint16 port)
{
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		receiveConnection->bindToPort(port);
	}
}



void GatewayConnection::connect(const IpAddress& address)
{
	if (checkStateNotNull(NAME_VALUE(sendConnection)) == true)
	{
		sendConnection->connect(address);
	}
}



void GatewayConnection::waitForConnection(uint16 port)
{
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		receiveConnection->waitForConnection(port);
	}
}



void GatewayConnection::waitForConnectionAsynchron(uint16 port)
{
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		receiveConnection->waitForConnectionAsynchron(port);
	}
}



void GatewayConnection::closeConnection()
{
	if (checkStateNotNull(NAME_VALUE(sendConnection)) == true)
	{
		sendConnection->closeConnection();
	}
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		receiveConnection->closeConnection();
	}
	connected = false;
}



IpAddress GatewayConnection::getOwnAddress() const
{
	return receiveConnection != NULL ? receiveConnection->getPeerAddress() : IpAddress();
}



IpAddress GatewayConnection::getPeerAddress() const
{
	return sendConnection != NULL ? sendConnection->getPeerAddress() : IpAddress();
}



void GatewayConnection::beginSendMessage(int messageSize) const
{
	if (checkStateNotNull(NAME_VALUE(sendConnection)) == true)
	{
		sendConnection->beginSendMessage(sizeof(uint16) + messageSize);
		sendConnection->outputStream() << targetUserId;
	}
}



void GatewayConnection::endSendMessage() const
{
	if (checkStateNotNull(NAME_VALUE(sendConnection)) == true)
	{
		sendConnection->endSendMessage();
	}
}



int GatewayConnection::beginReceiveMessage() const
{
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		return receiveConnection->beginReceiveMessage();
	}
	else
	{
		return 0;
	}
}



void GatewayConnection::endReceiveMessage() const
{
	AbstractConnection::endReceiveMessage();
	if (checkStateNotNull(NAME_VALUE(receiveConnection)) == true)
	{
		receiveConnection->endSendMessage();
	}
}



} // namespace Network
} // namespace BaseLib
