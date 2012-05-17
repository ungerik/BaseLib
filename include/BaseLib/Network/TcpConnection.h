/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef TcpConnection_h
#define TcpConnection_h



#include "BaseLib/Network/AbstractConnection.h"



namespace BaseLib {
namespace Network {



class BL_EXPORT TcpConnection : public AbstractConnection {
public:

	TcpConnection(double defaultTimeout);
	virtual ~TcpConnection();

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

	virtual bool isInputAvailable() const;

	virtual int beginReceiveMessage() const;
	
protected:

	AutoPointer<Socket> socket;

	void ensureSocketExists();
	void waitForConnectionAsynchronCallback(Socket* newSocket);

};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef TcpConnection_h