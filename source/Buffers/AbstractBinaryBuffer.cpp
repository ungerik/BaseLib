/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Buffers/AbstractBinaryBuffer.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/System/Thread.h"
#include "BaseLib/System/Time.h"



namespace BaseLib {
namespace Buffers {



using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;



AbstractBinaryBuffer::AbstractBinaryBuffer(bool fillWithZero)
  : size(0)
  , currentPosition(0)
  , allocateZeroFilled(fillWithZero)
{
}



AbstractBinaryBuffer::~AbstractBinaryBuffer()
{
}



int AbstractBinaryBuffer::getSizeAsInt() const
{
	if (size > INT_MAX)
	{
		argumentError(VALUE_TOO_LARGE(size, INT_MAX));
		return -1;
	}
	return static_cast<int>(size);
}



bool AbstractBinaryBuffer::isReadable() const
{
	return true;
}



bool AbstractBinaryBuffer::isWriteable() const
{
	return true;
}



int AbstractBinaryBuffer::getCurrentPositionAsInt() const
{
	if (currentPosition > INT_MAX)
	{
		argumentError(VALUE_TOO_LARGE(currentPosition, INT_MAX));
		return -1;
	}
	return static_cast<int>(currentPosition);
}



int AbstractBinaryBuffer::readAllFromPosition(int64 positionInBytes, void* destination) const
{
	const int64 remainingBytes = getSize() - positionInBytes;
	if (remainingBytes <= INT_MAX)
	{
		return readFromPosition(positionInBytes, destination, static_cast<int>(remainingBytes));
	}
	else
	{
		argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
		return 0;
	}
}



bool AbstractBinaryBuffer::readCompleteFromPosition(int64 positionInBytes, void* destination, int byteCount) const
{
	if (byteCount > size - positionInBytes)
	{
		if (getTimeoutForNextRead() > 0.0)
		{
			const double endTime = Time::nowInSeconds() + getTimeoutForNextRead();
			do Thread::sleepSeconds(0.01); while (Time::nowInSeconds() < endTime);
			if (byteCount > size - positionInBytes) return false;
		}
		else
		{
			return false;
		}
	}

	if (readFromPosition(positionInBytes, destination, byteCount) != byteCount)
	{
		resultError("");
		return false;
	}
	else
	{
		return true;
	}
}



int AbstractBinaryBuffer::readFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos)
{
	const int bytesRead = readFromPosition(currentPosition, destination, byteCount);
	if (moveCurrentPos == true && bytesRead > 0) moveCurrentPosition(bytesRead);
	return bytesRead;
}



int AbstractBinaryBuffer::readAllFromCurrentPosition(void* destination, bool moveCurrentPos)
{
	const int64 remainingBytes = availableBytesFromCurrentPosition();
	if (remainingBytes <= INT_MAX)
	{
		return readFromCurrentPosition(destination, static_cast<int>(remainingBytes), moveCurrentPos);
	}
	else
	{
		argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
		return 0;
	}
}



bool AbstractBinaryBuffer::readCompleteFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos)
{
	if (byteCount > availableBytesFromCurrentPosition())
	{
		if (getTimeoutForNextRead() > 0.0)
		{
			const double endTime = Time::nowInSeconds() + getTimeoutForNextRead();
			do Thread::sleepSeconds(0.01); while (Time::nowInSeconds() < endTime);
			if (byteCount > availableBytesFromCurrentPosition()) return false;
		}
		else
		{
			return false;
		}
	}

	if (readFromCurrentPosition(destination, byteCount) != byteCount)
	{
		resultError("");
		return false;
	}
	else
	{
		return true;
	}
}


} // namespace Buffers
} // namespace BaseLib
