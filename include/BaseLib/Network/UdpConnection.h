/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef UdpConnection_h
#define UdpConnection_h



#include "BaseLib/Network/AbstractConnection.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"



namespace BaseLib {
namespace Network {



using BaseLib::Buffers::BinaryMemBuffer;



class BL_EXPORT UdpConnection : public AbstractConnection {
public:

	UdpConnection(double defaultTimeout);
	virtual ~UdpConnection();

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

	Socket socket;
	mutable IpAddress peerAddress;
	mutable BinaryMemBuffer sendBuffer;

};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef UdpConnection_h