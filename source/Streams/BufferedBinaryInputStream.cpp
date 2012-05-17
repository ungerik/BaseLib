/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BufferedBinaryInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;



BufferedBinaryInputStream::BufferedBinaryInputStream(int bufferSize)
  : BinaryInputStream()
  , cacheBuffer(bufferSize)
  , inputEndPosition(0)
  , readCompleteBuffer(NULL)
  , readCompleteBufferSize(0)
{
}



BufferedBinaryInputStream::BufferedBinaryInputStream(const InputStream& connectToInputStream, int bufferSize)
  : BinaryInputStream(connectToInputStream)
  , cacheBuffer(bufferSize)
  , inputEndPosition(0)
  , readCompleteBuffer(NULL)
  , readCompleteBufferSize(0)
{
}



BufferedBinaryInputStream::BufferedBinaryInputStream(AbstractBinaryBuffer& connectToBinaryBuffer, int bufferSize)
  : BinaryInputStream(connectToBinaryBuffer)
  , cacheBuffer(bufferSize)
  , inputEndPosition(0)
  , readCompleteBuffer(NULL)
  , readCompleteBufferSize(0)
{
}



BufferedBinaryInputStream::~BufferedBinaryInputStream()
{
	free(readCompleteBuffer);
}



int BufferedBinaryInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	if (checkArgumentMin(NAME_VALUE(byteCount), 0) == false || checkArgumentMin(NAME_VALUE(timeoutSeconds), 0.0) == false) 
	{
		return 0;
	}
	else
	{
		const int bufferSize = getBufferSize();
		int currentPosition = cacheBuffer.getCurrentPositionAsInt();
		void* cacheBufferPointer = cacheBuffer.getPointer();

		// If we are at the end of the filled cache-buffer,
		// then try to refill the cache-buffer again:
		if (currentPosition >= inputEndPosition)
		{
			if (BinaryInputStream::isInputAvailable() == false)
			{
				return 0;
			}
			double startTime = Time::nowInSeconds();
			inputEndPosition = BinaryInputStream::readBinary(cacheBufferPointer, bufferSize, timeoutSeconds);
			timeoutSeconds -= Time::nowInSeconds() - startTime;
			if (timeoutSeconds < 0.0) timeoutSeconds = 0.0;
			currentPosition = 0;
			cacheBuffer.setCurrentPosition(currentPosition);
		}

		int bytesAvailable = inputEndPosition - currentPosition;
		if (byteCount <= bytesAvailable)
		{
			// If more bytes available than requested, copy to destination
			// (cacheBuffer moves the current position):
			int bytesRead = cacheBuffer.readFromCurrentPosition(destination, byteCount);
			totalBytesRead += bytesRead;
			return bytesRead;
		}
		else
		{
			// If there are not enough bytes available, read all available bytes,
			// then look how we can do the rest:
			int bytesRead = cacheBuffer.readFromCurrentPosition(destination, bytesAvailable);
			BL_ASSERT(bytesRead == bytesAvailable && cacheBuffer.getCurrentPositionAsInt() == inputEndPosition);
			destination = offsetPointer(destination, bytesRead);
			byteCount -= bytesRead;

			if (byteCount < bufferSize)
			{
				// If the rest of the bytes to read fit into the buffer,
				// read them into the buffer and copy to the destination:
				inputEndPosition = BinaryInputStream::readBinary(cacheBufferPointer, bufferSize, timeoutSeconds);
				cacheBuffer.setCurrentPosition(0);

				bytesRead += cacheBuffer.readFromCurrentPosition(destination, byteCount);
				totalBytesRead += bytesRead;
				return bytesRead;
			}
			else
			{
				// If the rest of the bytes doesn't fit into the buffer,
				// read them directly to the destination without using the buffer:
				bytesRead += BinaryInputStream::readBinary(destination, byteCount, timeoutSeconds);
				totalBytesRead += bytesRead;
				return bytesRead;
			}
		}
	}
}



bool BufferedBinaryInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	if (checkArgumentMin(NAME_VALUE(byteCount), 0) == false || checkArgumentMin(NAME_VALUE(timeoutSeconds), 0.0) == false)
	{
		return false;
	}
	else
	{
		// For reading a given number of bytes completly, we have to use an intermediate buffer
		// to be able to undo the read if it wasn't complete:
		if (readCompleteBuffer == NULL)
		{
			readCompleteBuffer = malloc(byteCount);
			readCompleteBufferSize = byteCount;
		}
		else if (readCompleteBufferSize < byteCount)
		{
			readCompleteBuffer = realloc(readCompleteBuffer, byteCount);
			readCompleteBufferSize = byteCount;
		}

		const int bytesRead = readBinary(readCompleteBuffer, byteCount, timeoutSeconds);
		if (bytesRead == byteCount)
		{
			memCopy(destination, readCompleteBuffer, byteCount);
			return true;
		}
		else
		{
			unreadBinary(readCompleteBuffer, bytesRead);
			return false;
		}
	}
}



void BufferedBinaryInputStream::unreadBinary(const void* source, int byteCount) const
{
	if (byteCount >= 0)
	{
		const int bufferSize = getBufferSize();
		const int currentPosition = cacheBuffer.getCurrentPositionAsInt();
		void* cacheBufferPointer = cacheBuffer.getPointer();

		if (byteCount > bufferSize)
		{
			// Unread buffer content:
			const int validBytes = inputEndPosition - currentPosition;
			BinaryInputStream::unreadBinary(offsetPointer(cacheBufferPointer, currentPosition), validBytes);
			cacheBuffer.setCurrentPosition(0);

			// Unread bytes to unread that don't fit into the buffer:
			BinaryInputStream::unreadBinary(offsetPointer(source, bufferSize),	byteCount - bufferSize);

			// Fill buffer with remaining bytes to unread:
			cacheBuffer.writeAtCurrentPosition(source, bufferSize, false);
			inputEndPosition = bufferSize;
		}
		else
		{
			const int validBytes = inputEndPosition - currentPosition;
			const int bytesFree = bufferSize - validBytes;
			if (byteCount <= bytesFree)
			{
				// If we have enough spare bytes before the currentPosition and after inputEndPosition,
				// move the valid buffer-content from currentPosition to 0 + byteCount position
				// and write the byteCount bytes to unread before this block:
				memmove(
					offsetPointer(cacheBufferPointer, byteCount),
					offsetPointer(cacheBufferPointer, currentPosition), 
					validBytes);

				// Write unread-content to the beginning:
				cacheBuffer.setCurrentPosition(0);
				cacheBuffer.writeAtCurrentPosition(source, byteCount, false);

				inputEndPosition = byteCount + validBytes;
			}
			else
			{
				// If we don't have enough spare bytes before the currentPosition and after inputEndPosition,
				// unread the odd buffer content, move the rest of the valid content to the offset byteCount
				// and write the byteCount bytes to unread before this block:
				BL_ASSERT(byteCount + validBytes > bufferSize);
				const int bytesToUnreadToSource = byteCount + validBytes - bufferSize;
				const int bytesToKeep = validBytes - bytesToUnreadToSource;
				BL_ASSERT(byteCount + bytesToKeep == bufferSize);

				BinaryInputStream::unreadBinary(
					offsetPointer(cacheBufferPointer, currentPosition + bytesToKeep),
					bytesToUnreadToSource);

				memmove(
					offsetPointer(cacheBufferPointer, byteCount),
					offsetPointer(cacheBufferPointer, currentPosition),
					bytesToKeep);

				cacheBuffer.setCurrentPosition(0);
				cacheBuffer.writeAtCurrentPosition(source, byteCount, false);

				inputEndPosition = byteCount + bytesToKeep;
			}
		}

		totalBytesRead -= byteCount;
	}
}



#define FAST_READ(T) \
	const int currentPosition = cacheBuffer.getCurrentPositionAsInt(); \
	const int newPosition = currentPosition + sizeof(destination); \
	if (newPosition <= inputEndPosition) \
	{ \
		destination = memoryAs<T>(cacheBuffer.getPointer(), currentPosition); \
		cacheBuffer.setCurrentPosition(newPosition); \
		totalBytesRead += sizeof(destination); \
		return true; \
	} \
	else \
	{ \
		return readBinaryComplete(&destination, sizeof(destination), timeoutSeconds); \
	}


bool BufferedBinaryInputStream::read(bool& destination, double timeoutSeconds) const { FAST_READ(bool) }
bool BufferedBinaryInputStream::read(void*& destination, double timeoutSeconds) const { FAST_READ(void*) }
bool BufferedBinaryInputStream::read(int8& destination, double timeoutSeconds) const
{
	const int currentPosition = cacheBuffer.getCurrentPositionAsInt(); 
	const int newPosition = currentPosition + sizeof(destination); 
	if (newPosition <= inputEndPosition) 
	{ 
		destination = memoryAs<int8>(cacheBuffer.getPointer(), currentPosition); 
		cacheBuffer.setCurrentPosition(newPosition); 
		totalBytesRead += sizeof(destination); 
		return true; 
	} 
	else 
	{ 
		return readBinaryComplete(&destination, sizeof(destination), timeoutSeconds); 
	}
}
bool BufferedBinaryInputStream::read(uint8& destination, double timeoutSeconds) const { FAST_READ(uint8) }
bool BufferedBinaryInputStream::read(int16& destination, double timeoutSeconds) const { FAST_READ(int16) }
bool BufferedBinaryInputStream::read(uint16& destination, double timeoutSeconds) const { FAST_READ(uint16) }
bool BufferedBinaryInputStream::read(int32& destination, double timeoutSeconds) const { FAST_READ(int32) }
bool BufferedBinaryInputStream::read(uint32& destination, double timeoutSeconds) const { FAST_READ(uint32) }
bool BufferedBinaryInputStream::read(int64& destination, double timeoutSeconds) const { FAST_READ(int64) }
bool BufferedBinaryInputStream::read(uint64& destination, double timeoutSeconds) const { FAST_READ(uint64) }
bool BufferedBinaryInputStream::read(float& destination, double timeoutSeconds) const { FAST_READ(float) }
bool BufferedBinaryInputStream::read(double& destination, double timeoutSeconds) const { FAST_READ(double) }
bool BufferedBinaryInputStream::read(long double& destination, double timeoutSeconds) const { FAST_READ(long double) }



void BufferedBinaryInputStream::setBufferSize(int newBufferSize)
{
	if (checkArgumentMin(NAME_VALUE(newBufferSize), 0) == true)
	{
		cacheBuffer.setSize(newBufferSize);
		inputEndPosition = BaseLib::Math::min(inputEndPosition, newBufferSize);
	}
}



bool BufferedBinaryInputStream::isInputAvailable() const
{
	bool result = cacheBuffer.getCurrentPositionAsInt() < inputEndPosition;

	if (result == false)
	{
		result = BinaryInputStream::isInputAvailable();
	}

	return result;
}



void BufferedBinaryInputStream::connectToStream(const InputStream& newInputStream)
{
	BinaryInputStream::connectToStream(newInputStream);
	resetBuffer();
}



void BufferedBinaryInputStream::connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer)
{
	BinaryInputStream::connectToBinaryBuffer(newBuffer);
	resetBuffer();
}



void BufferedBinaryInputStream::resetBuffer()
{
	cacheBuffer.setCurrentPosition(0);
	inputEndPosition = 0;
	free(readCompleteBuffer);
	readCompleteBuffer = NULL;
	readCompleteBufferSize = 0;
}



} // namespace Streams
} // namespace BaseLib
