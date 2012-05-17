/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;



InputStream::InputStream()
  : readTimeoutSeconds(0.0)
  , totalBytesRead(0)
  , connectedStream(NULL)
  , echoStream(NULL)
  , ownerOfConnectedObjects(false)
{
}



InputStream::InputStream(const InputStream& connectToInputStream)
  : readTimeoutSeconds(0.0)
  , totalBytesRead(0)
  , connectedStream(NULL)
  , echoStream(NULL)
  , ownerOfConnectedObjects(false)
{
	connectToStream(connectToInputStream);
}



InputStream::~InputStream()
{
	disconnectFromStream();
}



int InputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	BL_ASSERT(byteCount >= 0);
	BL_ASSERT(timeoutSeconds >= 0.0);

	if (connectedStream != NULL && byteCount > 0)
	{
		const int bytesRead = connectedStream->readBinary(destination, byteCount, timeoutSeconds);
		if (echoStream != NULL && bytesRead > 0) echoStream->writeBinary(destination, bytesRead);
		totalBytesRead += bytesRead;
		return bytesRead;
	}
	else
	{
		return 0;
	}
}



bool InputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	BL_ASSERT(byteCount >= 0);
	BL_ASSERT(timeoutSeconds >= 0.0);

	if (connectedStream != NULL && byteCount > 0)
	{
		const bool bytesRead = connectedStream->readBinaryComplete(destination, byteCount, timeoutSeconds);
		if (echoStream != NULL && bytesRead == true) echoStream->writeBinary(destination, byteCount);
		totalBytesRead += byteCount;
		return bytesRead;
	}
	else
	{
		return false;
	}
}



template<typename T>
bool InputStream::readTemplate(T& destination, double timeoutSeconds) const
{
	BL_ASSERT(timeoutSeconds >= 0.0);
	if (connectedStream != NULL && connectedStream->read(destination, timeoutSeconds) == true)
	{
		if (echoStream != NULL) echoStream->write(destination);
		totalBytesRead += sizeof(destination);
		return true;
	}
	else
	{
		return false;
	}
}



bool InputStream::read(bool& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(void*& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(int8& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(uint8& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(int16& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(uint16& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(int32& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(uint32& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(int64& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(uint64& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(float& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(double& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(long double& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool InputStream::read(String& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}





void InputStream::unreadBinary(const void* source, int byteCount) const
{
	BL_ASSERT(byteCount > 0);

	if (connectedStream != NULL)
	{
		connectedStream->unreadBinary(source, byteCount);
		totalBytesRead -= byteCount;
	}
	else
	{
		stateError(NO_STREAM_CONNECTED_FOR_UNREAD);
	}
}



template<typename T>
void InputStream::unreadTemplate(T source) const
{
	if (connectedStream != NULL)
	{
		connectedStream->unread(source);
		totalBytesRead -= sizeof(source);
	}
	else
	{
		stateError(NO_STREAM_CONNECTED_FOR_UNREAD);
	}
}

void InputStream::unread(bool source) const
{
	unreadTemplate(source);
}

void InputStream::unread(const void* source) const
{
	unreadTemplate(source);
}

void InputStream::unread(int8 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(uint8 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(int16 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(uint16 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(int32 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(uint32 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(int64 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(uint64 source) const
{
	unreadTemplate(source);
}

void InputStream::unread(float source) const
{
	unreadTemplate(source);
}

void InputStream::unread(double source) const
{
	unreadTemplate(source);
}

void InputStream::unread(long double source) const
{
	unreadTemplate(source);
}

void InputStream::unread(const String& source) const
{
	unreadTemplate(source);
}




void InputStream::connectToStream(const InputStream& newInputStream)
{
	connectedStream = &newInputStream;
}



void InputStream::disconnectFromStream()
{
	connectedStream = NULL;
}



void InputStream::connectOutputStream(const OutputStream& newOutputStream)
{
	echoStream = &newOutputStream;
}



void InputStream::disconnectOutputStream()
{
	if (ownerOfConnectedObjects == true)
	{
		delete connectedStream;
	}
	echoStream = NULL;
}



bool InputStream::isConnected() const
{
	return (connectedStream != NULL);
}



bool InputStream::isInputAvailable() const
{
	if (connectedStream != NULL)
	{
		return connectedStream->isInputAvailable();
	}
	else
	{
		return false;
	}
}



void InputStream::setReadTimeoutSeconds(double newReadTimeoutSeconds)
{
	BL_ASSERT(newReadTimeoutSeconds >= 0.0);
	readTimeoutSeconds = newReadTimeoutSeconds;
}



} // namespace Streams
} // namespace BaseLib
