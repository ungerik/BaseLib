/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BinaryInputStream.h"
#include "BaseLib/Buffers/AbstractBinaryBuffer.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/System/Thread.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Utilities/AutoArray.h"
#include <algorithm>



namespace BaseLib {
namespace Streams {


	
using BaseLib::Utilities::AutoArray;
using namespace BaseLib::Containers;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;



BinaryInputStream::BinaryInputStream()
	: InputStream()
	, BinaryStreamEncoding()
	, readStringMethod(READ_STRING_UNTIL_NO_INPUT_AVAILABLE)
	, tokenDelimiters(defaultTokenDelimiters)
	, connectedBinaryBuffer(NULL)
{
}



BinaryInputStream::BinaryInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, BinaryStreamEncoding()
	, readStringMethod(READ_STRING_UNTIL_NO_INPUT_AVAILABLE)
	, tokenDelimiters(defaultTokenDelimiters)
	, connectedBinaryBuffer(NULL)
{
}



BinaryInputStream::BinaryInputStream(AbstractBinaryBuffer& connectToBuffer)
	: InputStream()
	, BinaryStreamEncoding()
	, readStringMethod(READ_STRING_UNTIL_NO_INPUT_AVAILABLE)
	, tokenDelimiters(defaultTokenDelimiters)
	, connectedBinaryBuffer(NULL)
{
	connectToBinaryBuffer(connectToBuffer);
}



BinaryInputStream::~BinaryInputStream()
{
	disconnectFromBinaryBuffer();
}



int BinaryInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	if (checkArgumentNotNull(NAME_VALUE(destination)) == true &&
		checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		if (connectedBinaryBuffer != NULL)
		{
			connectedBinaryBuffer->setTimeoutForNextRead(timeoutSeconds);
			const int bytesRead = connectedBinaryBuffer->readFromCurrentPosition(destination, byteCount);
			if (echoStream != NULL && bytesRead > 0) echoStream->writeBinary(destination, bytesRead);
			totalBytesRead += bytesRead;
			return bytesRead;
		}
		else
		{
			return InputStream::readBinary(destination, byteCount, timeoutSeconds);
		}
	}
	else
	{
		return 0;
	}
}



bool BinaryInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	if (checkArgumentNotNull(NAME_VALUE(destination)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true &&
		checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		if (connectedBinaryBuffer != NULL)
		{
			connectedBinaryBuffer->setTimeoutForNextRead(timeoutSeconds);
			const bool readCompleted = connectedBinaryBuffer->readCompleteFromCurrentPosition(destination, byteCount);
			if (echoStream != NULL && readCompleted == true) echoStream->writeBinary(destination, byteCount);
			totalBytesRead += byteCount;
			return readCompleted;
		}
		else
		{
			return InputStream::readBinaryComplete(destination, byteCount, timeoutSeconds);
		}
	}
	else
	{
		return false;
	}
}



#define READBINARYBYTE return readBinary(&destination, 1, timeoutSeconds) == 1;


bool BinaryInputStream::read(bool& destination, double timeoutSeconds) const { READBINARYBYTE }
bool BinaryInputStream::read(int8& destination, double timeoutSeconds) const { READBINARYBYTE }
bool BinaryInputStream::read(uint8& destination, double timeoutSeconds) const { READBINARYBYTE }



#define READBINARY bool result = readBinaryComplete(&destination, sizeof(destination), timeoutSeconds); correctEndian(destination); return result;



bool BinaryInputStream::read(void*& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(int16& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(uint16& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(int32& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(uint32& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(int64& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(uint64& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(float& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(double& destination, double timeoutSeconds) const { READBINARY }
bool BinaryInputStream::read(long double& destination, double timeoutSeconds) const { READBINARY }



bool BinaryInputStream::read(String& destination, double timeoutSeconds) const
{
	if (checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		switch(readStringMethod)
		{
			case READ_STRING_UNTIL_NO_INPUT_AVAILABLE:
				return readStringUntilNoInputAvailable(destination, timeoutSeconds);

			case READ_STRING_TOKEN:
				return readStringToken(destination, timeoutSeconds);

			case READ_STRING_WITH_LENGTH:
				return readStringWithLength(destination, timeoutSeconds);

			default:
				BL_ASSERT_NEVER_REACHED
		}
	}
	return false;
}



void BinaryInputStream::unreadBinary(const void* source, int byteCount) const
{
	if (checkArgumentNotNull(NAME_VALUE(source)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true)
	{
		if (connectedStream != NULL)
		{
			connectedStream->unreadBinary(source, byteCount);
		}
		else if (connectedBinaryBuffer != NULL)
		{
			connectedBinaryBuffer->writeAtCurrentPosition(source, -byteCount);
		}
		else
		{
			stateError(NO_STREAM_OR_BUFFER_CONNECTED_FOR_UNREAD);
		}
	}
}



#define UNREADBINARY { correctEndian(source); unreadBinary(&source, sizeof(source)); }

void BinaryInputStream::unread(bool source) const UNREADBINARY
void BinaryInputStream::unread(const void* source) const UNREADBINARY
void BinaryInputStream::unread(int8 source) const UNREADBINARY
void BinaryInputStream::unread(uint8 source) const UNREADBINARY
void BinaryInputStream::unread(int16 source) const UNREADBINARY
void BinaryInputStream::unread(uint16 source) const UNREADBINARY
void BinaryInputStream::unread(int32 source) const UNREADBINARY
void BinaryInputStream::unread(uint32 source) const UNREADBINARY
void BinaryInputStream::unread(int64 source) const UNREADBINARY
void BinaryInputStream::unread(uint64 source) const UNREADBINARY
void BinaryInputStream::unread(float source) const UNREADBINARY
void BinaryInputStream::unread(double source) const UNREADBINARY
void BinaryInputStream::unread(long double source) const UNREADBINARY



void BinaryInputStream::unread(const String& source) const
{
	if (shouldUseUnicode(source) == true)
	{
		unreadBinary(source.getChar16CString(), source.getLength()*sizeof(char16));
	}
	else
	{
		unreadBinary(source.getChar8CString(), source.getLength()*sizeof(char8));
	}
}



bool BinaryInputStream::readStringUntilNoInputAvailable(String& destination, double timeoutSeconds) const
{
	if (checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		const double endTime = Time::nowInSeconds() + timeoutSeconds;
		while (isInputAvailable() == false)
		{
			if (timeoutSeconds == 0.0) return false;
			timeoutSeconds = endTime - Time::nowInSeconds();
			if (timeoutSeconds < 0.0) return false;
			Thread::sleepSeconds(0.01);
		}

		if (shouldUseUnicode(destination) == true)
		{
			uint16 c;
			bool hasInput = read(c, 0.0);
			BL_ASSERT(hasInput == true);
			destination.setLength(0);

			do
			{
				destination += static_cast<char16>(c);
				if (timeoutSeconds != 0.0)
				{
					timeoutSeconds = endTime - Time::nowInSeconds();
					if (timeoutSeconds < 0.0) break;
				}
				hasInput = read(c, timeoutSeconds);
			}
			while (hasInput == true);
		}
		else
		{
			uint8 c;
			bool hasInput = read(c, 0.0);
			BL_ASSERT(hasInput == true);
			destination.setLength(0);

			do
			{
				destination += static_cast<char8>(c);
				if (timeoutSeconds != 0.0)
				{
					timeoutSeconds = endTime - Time::nowInSeconds();
					if (timeoutSeconds < 0.0) break;
				}
				hasInput = read(c, timeoutSeconds);
			}
			while (hasInput == true);
		}

		if (echoStream != NULL) echoStream->write(destination);
		return true;
	}
	else
	{
		return false;
	}
}



bool BinaryInputStream::readStringToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const
{
	if (checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		// Wait timeoutSeconds if not input is available:
		const double endTime = Time::nowInSeconds() + timeoutSeconds;
		while (isInputAvailable() == false)
		{
			if (timeoutSeconds == 0.0) return false;
			timeoutSeconds = endTime - Time::nowInSeconds();
			if (timeoutSeconds < 0.0) return false;
			Thread::sleepSeconds(0.01);
		}

		if (shouldUseUnicode(destination) == true)
		{
			// Read first character because we know input is available:
			uint16 c;
			bool hasInput = read(c, 0.0);
			BL_ASSERT(hasInput == true);

			bool isDelimiter = (tokenDelimiters.findFirst(c) != String::END);

			// Read all delimiters:
			while (isDelimiter == true && hasInput == true)
			{
				if (timeoutSeconds != 0.0)
				{
					timeoutSeconds = endTime - Time::nowInSeconds();
					if (timeoutSeconds < 0.0)
					{
						hasInput = false;
						break;
					}
				}
				hasInput = read(c, timeoutSeconds);
				isDelimiter = (tokenDelimiters.findFirst(c) != String::END);
			}

			if (hasInput == true)
			{
				// Read token:
				BL_ASSERT(isDelimiter == false);
				String result;
				while (hasInput == true && isDelimiter == false)
				{
					result += c;
					if (timeoutSeconds != 0.0)
					{
						timeoutSeconds = endTime - Time::nowInSeconds();
						if (timeoutSeconds < 0.0) break;
					}
					hasInput = read(c, timeoutSeconds);
					isDelimiter = (tokenDelimiters.findFirst(c) != String::END);
				}
				destination = result;
				if (echoStream != NULL) echoStream->write(destination);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			// Read first character because we know input is available:
			uint8 c;
			bool hasInput = read(c, 0.0);
			BL_ASSERT(hasInput == true);

			bool isDelimiter = (tokenDelimiters.findFirst(static_cast<char8>(c)) != String::END);

			// Read all delimiters:
			while (isDelimiter == true && hasInput == true)
			{
				if (timeoutSeconds != 0.0)
				{
					timeoutSeconds = endTime - Time::nowInSeconds();
					if (timeoutSeconds < 0.0)
					{
						hasInput = false;
						break;
					}
				}
				hasInput = read(c, timeoutSeconds);
				isDelimiter = (tokenDelimiters.findFirst(static_cast<char8>(c)) != String::END);
			}

			if (hasInput == true)
			{
				// Read token:
				BL_ASSERT(isDelimiter == false);
				String result;
				while (hasInput == true && isDelimiter == false)
				{
					result += static_cast<char8>(c);
					if (timeoutSeconds != 0.0)
					{
						timeoutSeconds = endTime - Time::nowInSeconds();
						if (timeoutSeconds < 0.0) break;
					}
					hasInput = read(c, timeoutSeconds);
					isDelimiter = (tokenDelimiters.findFirst(static_cast<char8>(c)) != String::END);
				}
				destination = result;
				if (echoStream != NULL) echoStream->write(destination);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}



bool BinaryInputStream::readStringWithLength(String& destination, double timeoutSeconds) const
{
	if (checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		if (destination.isEmpty() == true) return true;

		int length = destination.getLength();

		if (shouldUseUnicode(destination) == true)
		{
			AutoArray<char16> buffer(new char16[length]);
			bool result = readBinaryComplete(buffer, length*sizeof(char16), timeoutSeconds);
			if (result == true)
			{
				for (int i = 0; i < length; ++i) correctEndian(buffer[i]);
				destination.copyFromCharArray(buffer, 0, length);
				if (echoStream != NULL) echoStream->write(destination);
			}
			return result;
		}
		else
		{
			AutoArray<char8> buffer(new char8[length]);
			bool result = readBinaryComplete(buffer, length*sizeof(char8), timeoutSeconds);
			if (result == true)
			{
				destination.copyFromCharArray(buffer, 0, length);
				if (echoStream != NULL) echoStream->write(destination);
			}
			return result;
		}
	}
	else
	{
		return false;
	}
}



bool BinaryInputStream::isConnected() const
{
	return (connectedBinaryBuffer != NULL || InputStream::isConnected() == true);
}



void BinaryInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedBinaryBuffer != NULL) disconnectFromBinaryBuffer();
	InputStream::connectToStream(newInputStream);
}



void BinaryInputStream::connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedBinaryBuffer = &newBuffer;
}



void BinaryInputStream::disconnectFromBinaryBuffer()
{
	if (ownerOfConnectedObjects == true)
	{
		delete connectedBinaryBuffer;
	}
	connectedBinaryBuffer = NULL;
}



bool BinaryInputStream::isInputAvailable() const
{
	bool result = InputStream::isInputAvailable();

	if (result == false && connectedBinaryBuffer != NULL)
	{
		result = connectedBinaryBuffer->readFromCurrentPositionPossible();
	}

	return result;
}



} // namespace Streams
} // namespace BaseLib
