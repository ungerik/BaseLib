/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/Gateway.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



Gateway::Gateway(AbstractConnection* useReceiveConnection)
	: receiveConnection(useReceiveConnection)
	, sendConnections()
	, transferBuffer()
{
	checkArgumentNotNull(NAME_VALUE(useReceiveConnection));
}



Gateway::~Gateway()
{
	foreach (Connections::iterator, i, sendConnections)
	{
		delete i->second;
	}
}



void Gateway::addSendConnection(int targetUserId, AbstractConnection* sendConnection)
{
	if (checkArgumentMin(NAME_VALUE(targetUserId), 0) == true &&
		checkArgumentNotNull(NAME_VALUE(sendConnection)) == true)
	{
		sendConnections[targetUserId] = sendConnection;
	}
}



void Gateway::removeSendConnection(int targetUserId)
{
	Connections::iterator i = sendConnections.find(targetUserId);
	if (i != sendConnections.end())
	{
		sendConnections.erase(i);
	}
	else
	{
		argumentError("Can't find connection for targetUserId=" + String::createFrom(targetUserId) + "!" ERROR_AT);
	}
}



void Gateway::transferMessages() const
{
	if (receiveConnection != NULL)
	{
		int messageSize = receiveConnection->beginReceiveMessage();
		while (messageSize >= sizeof(uint16))
		{
			uint16 targetUserId;
			receiveConnection->inputStream() >> targetUserId;

			Connections::const_iterator i = sendConnections.find(targetUserId);
			if (i != sendConnections.end())
			{
				messageSize -= sizeof(targetUserId);
				BL_ASSERT(messageSize >= 0);
				if (messageSize > transferBuffer.getSizeAsInt())
				{
					transferBuffer.setSize(messageSize);
				}

				if (receiveConnection->inputStream().readBinaryComplete(transferBuffer.getPointer(), messageSize, receiveConnection->getTimeout()) == true)
				{
					i->second->beginSendMessage(messageSize);
					i->second->outputStream().writeBinary(transferBuffer.getPointer(), messageSize);
					i->second->endSendMessage();
				}
				else
				{
					ioError("Receive operation for target user with id=" + String::createFrom(targetUserId) + " timed out!" ERROR_AT);
				}
			}
			else
			{
				stateError("Send-connection to target user with id=" + String::createFrom(targetUserId) + " not found!" ERROR_AT);
			}
		}
	}
}



} // namespace Network
} // namespace BaseLib
