/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/AbstractConnection.h"
#include "BaseLib/Network/TcpConnection.h"
#include "BaseLib/Network/UdpConnection.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



AbstractConnection* AbstractConnection::create(Socket::ProtocolType protocolType, double timeout)
{
	switch (protocolType)
	{
		case Socket::TCP:
			return new TcpConnection(timeout);

		case Socket::UDP:
			return new UdpConnection(timeout);

		default:
			BL_ASSERT_NEVER_REACHED
			return NULL;
	}
}



AbstractConnection::AbstractConnection(double defaultTimeout)
	: timeout(defaultTimeout)
	, connected(false)
	, binaryOutputStream()
	, binaryInputStream()
	#ifdef _DEBUG
	, debugOutputSize(0)
	, debugInputSize(0)
	, debugOutputBuffer()
	, debugInputToOutputStream()
	, debugInputBuffer()
	#endif
{
	#ifdef _DEBUG
	debugInputBuffer.setSize(0xFFFFFFFF);
	debugInputToOutputStream.connectToBinaryBuffer(debugInputBuffer);
	#endif
}



AbstractConnection::~AbstractConnection()
{
}



void AbstractConnection::setTimeout(double newTimeout)
{
	if (checkArgumentMin(NAME_VALUE(newTimeout), 0.0) == true &&
		checkArgumentIsValidFloat(NAME_VALUE(newTimeout)) == true)
	{
		timeout = newTimeout;
		binaryInputStream.setReadTimeoutSeconds(newTimeout);
	}
}



void AbstractConnection::endReceiveMessage() const
{
	#ifdef _DEBUG
	int bytesRead = debugInputBuffer.getCurrentPositionAsInt();
	if (bytesRead != debugInputSize)
	{
		ioError("Bytes read (" + String::createFrom(bytesRead) + ") are not equal to the count passed at beginReceiveMessage (" + String::createFrom(debugInputSize) + ")!" ERROR_AT);
	}
	#endif
}



} // namespace Network
} // namespace BaseLib
