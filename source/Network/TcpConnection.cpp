/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/TcpConnection.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



TcpConnection::TcpConnection(double defaultTimeout)
	: AbstractConnection(defaultTimeout)
	, socket(NULL)
{
}



TcpConnection::~TcpConnection()
{
}



Socket::ProtocolType TcpConnection::getSocketProtocolType() const
{
	return Socket::TCP;
}



void TcpConnection::bindToPort(uint16 port)
{
	ensureSocketExists();
	socket->bind(port);
}



void TcpConnection::connect(const IpAddress& address)
{
	ensureSocketExists();
	connected = socket->connect(address);
}



void TcpConnection::waitForConnection(uint16 port)
{
	ensureSocketExists();
	socket->bind(port);
	socket->listen();
	socket = socket->accept();
	connected = true;
}



void TcpConnection::waitForConnectionAsynchron(uint16 port)
{
	ensureSocketExists();
	socket->bind(port);
	socket->listen();
	socket->acceptAsynchron(Socket::AcceptCallbackMethodFunctor<TcpConnection>(this, &TcpConnection::waitForConnectionAsynchronCallback));
}



void TcpConnection::waitForConnectionAsynchronCallback(Socket* newSocket)
{
	if (newSocket != NULL)
	{
		socket = newSocket;
		connected = true;
	}
}



void TcpConnection::closeConnection()
{
	if (socket != NULL)
	{
		binaryOutputStream.disconnectFromStream(socket->outputStream());
		binaryInputStream.disconnectFromStream();

		#ifdef _DEBUG
		binaryOutputStream.disconnectFromBinaryBuffer(debugOutputBuffer);
		binaryInputStream.disconnectOutputStream();
		#endif

		delete socket;
		socket = NULL;
	}
	connected = false;
}



IpAddress TcpConnection::getOwnAddress() const
{
	return socket != NULL ? socket->getAddress() : IpAddress();
}



IpAddress TcpConnection::getPeerAddress() const
{
	return socket != NULL ? socket->getPeerAddress() : IpAddress();
}



void TcpConnection::beginSendMessage(int messageSize) const
{
	if (socket != NULL && connected == true)
	{
		binaryOutputStream << static_cast<uint32>(messageSize);
	}

	#ifdef _DEBUG
	debugOutputBuffer.setCurrentPosition(0);
	debugOutputSize = messageSize;
	#endif
}



void TcpConnection::endSendMessage() const
{
	#ifdef _DEBUG
	int bytesWritten = debugInputBuffer.getCurrentPositionAsInt();
	if (bytesWritten != debugInputSize)
	{
		ioError("Bytes written (" + String::createFrom(bytesWritten) + ") are not equal the count passed at beginReceiveMessage (" + String::createFrom(debugInputSize) + ")!" ERROR_AT);
	}
	#endif
}



bool TcpConnection::isInputAvailable() const
{
	return socket != NULL && socket->getBytesAvailable() > 0;
}



int TcpConnection::beginReceiveMessage() const
{
	uint32 messageSize = 0;
	if (socket != NULL && connected == true)
	{
		binaryInputStream.read(messageSize, timeout);
	}

	#ifdef _DEBUG
	debugInputBuffer.setCurrentPosition(0);
	debugInputSize = messageSize;
	#endif

	return messageSize;
}



void TcpConnection::ensureSocketExists()
{
	if (socket == NULL)
	{
		socket = new Socket(Socket::TCP);
		socket->setReadTimeoutSeconds(timeout);
		binaryOutputStream.connectToStream(socket->outputStream());
		binaryInputStream.connectToStream(socket->inputStream());
		#ifdef _DEBUG
		binaryOutputStream.connectToBinaryBuffer(debugOutputBuffer);
		binaryInputStream.connectOutputStream(debugInputToOutputStream);
		#endif
	}
}



} // namespace Network
} // namespace BaseLib
