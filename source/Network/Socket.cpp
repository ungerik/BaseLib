/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Network/Socket.h"
#include "BaseLib/Buffers/AbstractBinaryBuffer.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Utilities/AutoArray.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::Buffers;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Functors;
using namespace BaseLib::Utilities;
using BaseLib::Utilities::AutoArray;



class BinarySocketBuffer : public DefaultBinaryBuffer {
public:

	BinarySocketBuffer() {}

	explicit BinarySocketBuffer(Socket* newSocket)
		: DefaultBinaryBuffer(false)
	    , socket(newSocket)
		, readTimeoutSeconds(0.0)
	{
		BL_ASSERT(socket != NULL);
	}

	virtual void close()
	{
		socket->close();
	}

	virtual int readFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos = true)
	{
		return socket->receive(destination, byteCount);
	}

	virtual bool readCompleteFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos)
	{
		if (readTimeoutSeconds == 0.0)
		{
			if (readFromCurrentPositionPossible() == true)
			{
				if (readFromCurrentPosition(destination, byteCount) != byteCount)
				{
					ioError("");
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			double timeout = readTimeoutSeconds;
			int bytesToRead = byteCount;
			const double endTime = Time::nowInSeconds() + timeout;
			AutoArray<int8> buffer(new int8[byteCount]);	

			do
			{
				bytesToRead -= readFromCurrentPosition(buffer, bytesToRead);
				timeout = endTime - Time::nowInSeconds();
				if (timeout > 0.0) Thread::sleepSeconds(0.01);
			}
			while (bytesToRead > 0 && timeout > 0.0);

			if (bytesToRead == 0)
			{
				memCopy(destination, buffer, byteCount);
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount) // position is ignored
	{
		return socket->send(source, byteCount);
	}

	virtual double getTimeoutForNextRead() const
	{
		return readTimeoutSeconds;
	}

	virtual void setTimeoutForNextRead(double newReadTimeoutSeconds)
	{
		BL_ASSERT(newReadTimeoutSeconds >= 0.0);
		readTimeoutSeconds = newReadTimeoutSeconds;
	}

	virtual void setCurrentPosition(int newCurrentPosition) // position is ignored
	{
	}

	virtual int64 availableBytesFromCurrentPosition() const
	{
		return socket->getBytesAvailable();
	}

private:
	Socket* socket;
	double readTimeoutSeconds; ///

};




///////////////////////////////////////////////////////////////////////////////




Socket::Socket(ProtocolType newProtocolType, uint16 bindToPort)
	: protocolType(newProtocolType)
	, handle(INVALID_SOCKET)
	, port(0)
	, readTimeoutSeconds(0.0)
	, binarySocketBuffer(NULL)
	, binaryInputStream(NULL)
	, binaryOutputStream(NULL)
	, stringEncoding(BinaryStreamEncoding::STRING_IMPLEMENTATION)
	, endian(BinaryStreamEncoding::STREAM_IS_SMALL_ENDIAN)
	, acceptThread(NULL)
	, acceptCallbackFunctor(NULL)
	, acceptAsynchronResult(NULL)
	, blocking(true)
{
	useBaseLibNetworking();

	if (protocolType == TCP)
	{
		handle = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	else
	{
		BL_ASSERT(protocolType == UDP);
		handle = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}


	if (handle != INVALID_SOCKET)
	{
		if (bindToPort != 0)
		{
			bind(bindToPort);
		}
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
	}
}



Socket::Socket(int newHandle, ProtocolType newProtocolType)
	: protocolType(newProtocolType)
	, handle(newHandle)
	, port(0)
	, readTimeoutSeconds(0.0)
	, binarySocketBuffer(NULL)
	, binaryInputStream(NULL)
	, binaryOutputStream(NULL)
	, stringEncoding(BinaryStreamEncoding::STRING_IMPLEMENTATION)
	, endian(BinaryStreamEncoding::STREAM_IS_SMALL_ENDIAN)
	, acceptThread(NULL)
	, acceptCallbackFunctor(NULL)
	, acceptAsynchronResult(NULL)
	, blocking(true)
{
	useBaseLibNetworking();
}



Socket::~Socket()
{
	delete binarySocketBuffer;
	close();
}



void Socket::close()
{
	if (isHandleValid() == true)
	{
		if (closesocket(handle) != 0)
		{
			ioError(LAST_SOCKET_ERROR);
		}

		handle = INVALID_SOCKET;

		releaseBaseLibNetworking();
	}
}


void Socket::bind(uint16 portNumber)
{
	sockaddr_in addr;
    addr.sin_family = AF_INET;       
    addr.sin_port = bigEndian(portNumber);     
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

	if (::bind(handle, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0)
	{
		port = portNumber;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
	}
}



bool Socket::connect(const IpAddress& ipAddress)
{
	sockaddr addr;
	return (::connect(handle, ipAddress.makeSockAddr(addr), sizeof(addr)) == 0);
}



IpAddress Socket::getAddress() const
{
	sockaddr addr;
	int len = sizeof(addr);
	if (getsockname(handle, &addr, &len) == 0)
	{
		return addr;
	}
	else
	{
		return IpAddress();
	}	
}



IpAddress Socket::getPeerAddress() const
{
	sockaddr addr;
	int len = sizeof(addr);
	if (getpeername(handle, &addr, &len) == 0)
	{
		return addr;
	}
	else
	{
		return IpAddress();
	}	
}



void Socket::listen()
{
	if (::listen(handle, SOMAXCONN) != 0)
	{
		ioError(LAST_SOCKET_ERROR);
	}
}



//void Socket::listenAsynchron()
//{
//	listenAsynchronCallbackFunctor = NULL;
//	listenThread = Thread::create(this, &Socket::listenAsynchronThreadFunction);
//}
//
//
//
//void Socket::listenAsynchron(const CallbackFunctor& callbackFunctor)
//{
//	listenAsynchronCallbackFunctor = callbackFunctor.clone();
//	listenThread = Thread::create(this, &Socket::listenAsynchronThreadFunction);
//}
//
//
//
//
//void Socket::listenAsynchronThreadFunction()
//{
//	listen();
//	listenThread = NULL;
//	if (listenAsynchronCallbackFunctor != NULL)
//	{
//		(*listenAsynchronCallbackFunctor)();
//		listenAsynchronCallbackFunctor = NULL;
//	}
//}
//
//
//
//bool Socket::isListeningAsynchron() const
//{
//	return listenThread != NULL;
//}
//
//
//
//void Socket::endListenAsynchron()
//{
//	listenThread = NULL;
//}



Socket* Socket::accept()
{
	const int newHandle = ::accept(handle, NULL, NULL);
	if (newHandle != INVALID_SOCKET)
	{
		return new Socket(newHandle, protocolType);
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return NULL;
	}
}



void Socket::acceptAsynchron()
{
	acceptCallbackFunctor = NULL;
	acceptThread = new Thread(MethodFunctor0<Socket, void>(this, &Socket::acceptAsynchronThreadFunction)); // TODO: Optmieren
}



void Socket::acceptAsynchron(const AcceptCallbackFunctor& callbackFunctor)
{
	acceptCallbackFunctor = callbackFunctor.clone();
	acceptThread = new Thread(MethodFunctor0<Socket, void>(this, &Socket::acceptAsynchronThreadFunction)); // TODO: Optmieren
}



void Socket::acceptAsynchronThreadFunction()
{
	acceptAsynchronResult = accept();
	acceptThread = NULL;
	if (acceptCallbackFunctor != NULL)
	{
		(*acceptCallbackFunctor)(acceptAsynchronResult);
	}
}



int Socket::send(const void* source, int bytesToSend) const
{
	BL_ASSERT(bytesToSend >= 0);
	const int bytesSent = ::send(handle, static_cast<const char*>(source), bytesToSend, 0);
	if (bytesSent != SOCKET_ERROR)
	{
		return bytesSent;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



void Socket::sendAll(const void* source, int bytesToSend, double timeout) const
{
	BL_ASSERT(bytesToSend >= 0);
	BL_ASSERT(timeout >= 0.0);

	const double endTime = Time::nowInSeconds() + timeout;

	int bytesSent = send(source, bytesToSend);

	if (bytesSent != bytesToSend)
	{
		BL_ASSERT(bytesSent < bytesToSend);
		bytesSent = send(source, bytesToSend);
		source = offsetPointer(source, bytesSent);
		bytesToSend -= bytesSent;

		do
		{
			if (Time::nowInSeconds() > endTime)
			{
				ioError(SOCKET_SEND_TIMEOUT);
				return;
			}
			bytesSent = send(source, bytesToSend);
			source = offsetPointer(source, bytesSent);
			bytesToSend -= bytesSent;
		}
		while (bytesSent < bytesToSend);
	}
}



int Socket::getBytesAvailable(double timeout) const
{
	int result = getBytesAvailable();

	if (result == 0 && timeout > 0.0)
	{
		const double endTime = Time::nowInSeconds() + timeout;

		do
		{
			Thread::sleepSeconds(0.01);
			result = getBytesAvailable();
			timeout = endTime - Time::nowInSeconds();
		}
		while (result == 0 && timeout > 0.0);
	}

    return result;
}



int Socket::receive(void* destination, int destinationSize, double timeout) const
{
	BL_ASSERT(destinationSize >= 0);
	BL_ASSERT(timeout >= 0.0);

	if (destinationSize == 0) return 0;

	getBytesAvailable(timeout);

	const int bytesRead = recv(handle, static_cast<char*>(destination), destinationSize, 0);
	if (bytesRead != SOCKET_ERROR)
	{
		return bytesRead;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



int Socket::peek(void* destination, int destinationSize) const
{
	BL_ASSERT(destinationSize >= 0);

	if (destinationSize == 0) return 0;

	const int bytesRead = recv(handle, static_cast<char*>(destination), destinationSize, MSG_PEEK);
	if (bytesRead != SOCKET_ERROR)
	{
		return bytesRead;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



int Socket::sendTo(const void* source, int bytesToSend, const IpAddress& toAddress) const
{
	BL_ASSERT(bytesToSend >= 0);
	sockaddr addr;
	const int bytesSent = ::sendto(handle, static_cast<const char*>(source), bytesToSend, 0, toAddress.makeSockAddr(addr), sizeof(addr));
	if (bytesSent != SOCKET_ERROR)
	{
		return bytesSent;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



void Socket::sendAllTo(const void* source, int bytesToSend, const IpAddress& toAddress, double timeout) const
{
	BL_ASSERT(bytesToSend >= 0);
	BL_ASSERT(timeout >= 0.0);

	const double endTime = Time::nowInSeconds() + timeout;

	int bytesSent = sendTo(source, bytesToSend, toAddress);

	if (bytesSent != bytesToSend)
	{
		BL_ASSERT(bytesSent < bytesToSend);
		bytesSent = sendTo(source, bytesToSend, toAddress);
		source = offsetPointer(source, bytesSent);
		bytesToSend -= bytesSent;

		do
		{
			if (Time::nowInSeconds() > endTime)
			{
				ioError(SOCKET_SEND_TIMEOUT);
				return;
			}
			bytesSent = sendTo(source, bytesToSend, toAddress);
			source = offsetPointer(source, bytesSent);
			bytesToSend -= bytesSent;
		}
		while (bytesSent < bytesToSend);
	}
}



int Socket::receiveFrom(void* destination, int destinationSize, IpAddress& fromAddress, double timeout) const
{
	BL_ASSERT(destinationSize > 0);
	BL_ASSERT(timeout >= 0.0);

	if (getBytesAvailable() == 0 && timeout > 0.0)
	{
		const double endTime = Time::nowInSeconds() + timeout;
		do
		{
			Thread::sleepSeconds(0.01);
			if (Time::nowInSeconds() >= endTime) return 0;
		}
		while (getBytesAvailable() == 0);
	}

	sockaddr addr;
	int addrLen = sizeof(addr);
	const int bytesRead = recvfrom(handle, static_cast<char *>(destination), destinationSize, 0, &addr, &addrLen);
	if (bytesRead != SOCKET_ERROR)
	{
		fromAddress = addr;
		return bytesRead;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



int Socket::peekFrom(void* destination, int destinationSize, IpAddress& fromAddress) const
{
	BL_ASSERT(destinationSize > 0);
	sockaddr addr;
	int addrLen = sizeof(addr);
	const int bytesRead = recvfrom(handle, static_cast<char *>(destination), destinationSize, MSG_PEEK, &addr, &addrLen);
	if (bytesRead != SOCKET_ERROR)
	{
		fromAddress = addr;
		return bytesRead;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



BinaryInputStream& Socket::inputStream()
{
	if (binaryInputStream == NULL)
	{
		if (binarySocketBuffer == NULL) binarySocketBuffer = new BinarySocketBuffer(this);
		binaryInputStream = new BinaryInputStream(*binarySocketBuffer);
	}
	return *binaryInputStream;
}



BinaryOutputStream& Socket::outputStream()
{
	if (binaryOutputStream == NULL)
	{
		if (binarySocketBuffer == NULL) binarySocketBuffer = new BinarySocketBuffer(this);
		binaryOutputStream = new BinaryOutputStream(*binarySocketBuffer);
	}
	return *binaryOutputStream;
}



const BinaryInputStream& Socket::inputStream() const
{
	return const_cast<Socket*>(this)->inputStream();
}



const BinaryOutputStream& Socket::outputStream() const
{
	return const_cast<Socket*>(this)->outputStream();
}



void Socket::setReadTimeoutSeconds(double newReadTimeoutSeconds)
{
	BL_ASSERT(newReadTimeoutSeconds >= 0.0);
	readTimeoutSeconds = newReadTimeoutSeconds;
}



int Socket::getBytesAvailable() const
{
	unsigned long byteCount;
	return (ioctlsocket(handle, FIONREAD, &byteCount) == 0) ? byteCount : 0;
}



int Socket::getMaxMessageSize() const
{
	int size;
	int optionSize = sizeof(size);
	if (getsockopt(handle, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&size, &optionSize) == 0)
	{
		return size;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



int Socket::getReceiveBufferSize() const
{
	int size;
	int optionSize = sizeof(size);
	if (getsockopt(handle, SOL_SOCKET, SO_RCVBUF, (char *)&size, &optionSize) == 0)
	{
		return size;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



bool Socket::setReceiveBufferSize(int size)
{
	BL_ASSERT(size > 0);
	return (setsockopt(handle, SOL_SOCKET, SO_RCVBUF, (const char *)&size, sizeof(size)) == 0);
}



int Socket::getSendBufferSize() const
{
	int size;
	int optionSize = sizeof(size);
	if (getsockopt(handle, SOL_SOCKET, SO_SNDBUF, (char *)&size, &optionSize) == 0)
	{
		return size;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return 0;
	}
}



bool Socket::setSendBufferSize(int size)
{
	BL_ASSERT(size > 0);
	return (setsockopt(handle, SOL_SOCKET, SO_SNDBUF, (const char *)&size, sizeof(size)) == 0);
}



bool Socket::isBroadcastEnabled() const
{
	int enabled;
	int optionSize = sizeof(enabled);
	if (getsockopt(handle, SOL_SOCKET, SO_BROADCAST, (char *)&enabled, &optionSize) == 0)
	{
		return (enabled != 0);
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return false;
	}
}



void Socket::setBroadcastEnabled(bool enableBroadcast)
{
	int enable = enableBroadcast;
	if (setsockopt(handle, SOL_SOCKET, SO_BROADCAST, (const char *)&enable, sizeof(enable)) != 0)
	{
		ioError(LAST_SOCKET_ERROR);
	}
}



bool Socket::isBlocking() const
{
	return blocking;
}



void Socket::setBlocking(bool enableBlocking)
{
	unsigned long enable = enableBlocking;
	if (ioctlsocket(handle, FIONBIO, &enable) == 0)
	{
		blocking = enableBlocking;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
	}
}



} // namespace Network
} // namespace BaseLib
