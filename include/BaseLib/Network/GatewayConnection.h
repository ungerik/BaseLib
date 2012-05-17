/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef GatewayConnection_h
#define GatewayConnection_h



#include "BaseLib/Network/AbstractConnection.h"



namespace BaseLib {
namespace Network {



/**

Protocol:

+-----------+
| uint32    | byteCount
+-----------+
| uint16    | targetUserId
+-----------+
|           |
| byteCount | message-data
| - 2 bytes |
|           |
+-----------+
*/
class BL_EXPORT GatewayConnection : public AbstractConnection {
public:

	GatewayConnection(AbstractConnection* useSendConnection, AbstractConnection* useReceiveConnection, int forTargetUserId);
	~GatewayConnection();

	inline AbstractConnection* getSendConnection()
	{
		return sendConnection;
	}
	inline const AbstractConnection* getSendConnection() const
	{
		return sendConnection;
	}

	inline AbstractConnection* getReceiveConnection()
	{
		return receiveConnection;
	}
	inline const AbstractConnection* getReceiveConnection() const
	{
		return receiveConnection;
	}

	inline int getTargetUserId() const
	{
		return targetUserId;
	}

	virtual Socket::ProtocolType getSocketProtocolType() const;

	virtual void bindToPort(uint16 port);
	virtual void connect(const IpAddress& address);
	virtual void waitForConnection(uint16 port);
	virtual void waitForConnectionAsynchron(uint16 port);
	virtual void closeConnection();

	virtual IpAddress getOwnAddress() const;
	virtual IpAddress getPeerAddress() const;

	virtual void beginSendMessage(int messageSize) const;
	virtual void endSendMessage() const;
	
	virtual int beginReceiveMessage() const;
	virtual void endReceiveMessage() const;


protected:

	AutoPointer<AbstractConnection> sendConnection;
	AutoPointer<AbstractConnection> receiveConnection;
	uint16 targetUserId;

};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef GatewayConnection_h