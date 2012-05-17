/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/UdpConnection.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



UdpConnection::UdpConnection(double defaultTimeout)
	: AbstractConnection(defaultTimeout)
	, socket(Socket::UDP)
	, peerAddress()
	, sendBuffer()
{
	socket.setReadTimeoutSeconds(timeout);
	binaryOutputStream.connectToBinaryBuffer(sendBuffer);
	binaryInputStream.connectToStream(socket.inputStream());

	#ifdef _DEBUG
	binaryOutputStream.connectToBinaryBuffer(debugOutputBuffer);
	binaryInputStream.connectOutputStream(debugInputToOutputStream);;
	#endif
}



UdpConnection::~UdpConnection()
{
}



Socket::ProtocolType UdpConnection::getSocketProtocolType() const
{
	return Socket::UDP;
}



void UdpConnection::bindToPort(uint16 port)
{
	socket.bind(port);
	connected = true;
}



void UdpConnection::connect(const IpAddress& address)
{
	connected = socket.connect(address);
}



void UdpConnection::waitForConnection(uint16 port)
{
	socket.bind(port);
	connected = true;
}



void UdpConnection::waitForConnectionAsynchron(uint16 port)
{
	socket.bind(port);
	connected = true;
}



void UdpConnection::closeConnection()
{
	socket.close();
	connected = false;
}



IpAddress UdpConnection::getOwnAddress() const
{
	return socket.getAddress();
}



IpAddress UdpConnection::getPeerAddress() const
{
	return peerAddress;
}



void UdpConnection::beginSendMessage(int messageSize) const
{
	sendBuffer.setCurrentPosition(0);
	binaryOutputStream << static_cast<uint32>(messageSize);

	#ifdef _DEBUG
	debugOutputBuffer.setCurrentPosition(0);
	debugOutputSize = messageSize;
	#endif
}



void UdpConnection::endSendMessage() const
{
	#ifdef _DEBUG
	int bytesWritten = debugInputBuffer.getCurrentPositionAsInt();
	if (bytesWritten != debugInputSize)
	{
		ioError("Bytes written (" + String::createFrom(bytesWritten) + ") are not equal the count passed at beginReceiveMessage (" + String::createFrom(debugInputSize) + ")!" ERROR_AT);
	}
	#endif

	socket.sendAll(sendBuffer.getPointer(), sendBuffer.getCurrentPositionAsInt(), timeout);
}



bool UdpConnection::isInputAvailable() const
{
	return socket.getBytesAvailable() > 0;
}



int UdpConnection::beginReceiveMessage() const
{
	uint32 messageSize = 0;
	if (connected == true && socket.getBytesAvailable() >= sizeof(uint32))
	{
		binaryInputStream >> messageSize;
		// Teilt connect bei UDP die daten bei receive auf unterschiedliche sockets mit identischem port auf?
		//IpAddress fromAddress;
		//socket.receiveFrom(&messageSize, sizeof(messageSize), fromAddress);
}

	#ifdef _DEBUG
	debugInputBuffer.setCurrentPosition(0);
	debugInputSize = messageSize;
	#endif

	return messageSize;
}



} // namespace Network
} // namespace BaseLib
