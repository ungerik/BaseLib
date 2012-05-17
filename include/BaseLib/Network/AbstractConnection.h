/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef AbstractConnection_h
#define AbstractConnection_h



#include "BaseLib/Network/Socket.h"

#ifdef _DEBUG
#include "BaseLib/Buffers/VoidBinaryBuffer.h"
#endif



namespace BaseLib {
namespace Network {



using BaseLib::Streams::BinaryOutputStream;
using BaseLib::Streams::BinaryOutputStream;



/**

Protocol:

+-----------+
| uint32    | byteCount
+-----------+
|           |
| byteCount | block-data
| bytes     |
|           |
+-----------+
*/
class BL_EXPORT AbstractConnection : public NonCopyable {
public:
	
	static AbstractConnection* create(Socket::ProtocolType protocolType, double timeout);

	virtual ~AbstractConnection();

	inline double getTimeout() const
	{
		return timeout;
	}

	virtual void setTimeout(double newTimeout);

	virtual Socket::ProtocolType getSocketProtocolType() const = 0;

	virtual void bindToPort(uint16 port) = 0;
	virtual void connect(const IpAddress& address) = 0;
	virtual void waitForConnection(uint16 port) = 0;
	virtual void waitForConnectionAsynchron(uint16 port) = 0;
	inline bool isConnected() const
	{
		return connected;
	}

	virtual void closeConnection() = 0;

	virtual IpAddress getOwnAddress() const = 0;
	virtual IpAddress getPeerAddress() const = 0;

	virtual void beginSendMessage(int messageSize) const = 0;
	inline BinaryOutputStream& outputStream()
	{
		return binaryOutputStream;
	}
	inline const BinaryOutputStream& outputStream() const
	{
		return binaryOutputStream;
	}
	virtual void endSendMessage() const = 0;
	
	virtual bool isInputAvailable() const = 0;

	virtual int beginReceiveMessage() const = 0;
	inline BinaryInputStream& inputStream()
	{
		return binaryInputStream;
	}
	inline const BinaryInputStream& inputStream() const
	{
		return binaryInputStream;
	}
	virtual void endReceiveMessage() const;
	
protected:

	double timeout;
	bool connected;

	BinaryOutputStream binaryOutputStream;
	BinaryInputStream binaryInputStream;

	#ifdef _DEBUG
	mutable int debugOutputSize;
	mutable int debugInputSize;
	mutable BaseLib::Buffers::VoidBinaryBuffer debugOutputBuffer;
	mutable BinaryOutputStream debugInputToOutputStream;
	mutable BaseLib::Buffers::VoidBinaryBuffer debugInputBuffer;
	#endif

	AbstractConnection(double defaultTimeout);

};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef AbstractConnection_h