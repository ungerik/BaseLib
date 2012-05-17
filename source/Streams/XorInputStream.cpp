/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/XorInputStream.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/System/Thread.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::System;



XorInputStream::XorInputStream(ValueType newReferenceValue)
	: BinaryInputStream()
	, referenceValue(newReferenceValue)
{
}



XorInputStream::XorInputStream(const InputStream& connectToInputStream, ValueType newReferenceValue)
	: BinaryInputStream(connectToInputStream)
	, referenceValue(newReferenceValue)
{
}



XorInputStream::XorInputStream(AbstractBinaryBuffer& connectToBuffer, ValueType newReferenceValue)
	: BinaryInputStream(connectToBuffer)
	, referenceValue(newReferenceValue)
{
}



int XorInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	int bytesRead = 0;
	if (checkArgumentNotNull(NAME_VALUE(destination)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true &&
		checkArgumentIsValidFloat(NAME_VALUE(timeoutSeconds)) == true &&
		checkArgumentPositive(NAME_VALUE(timeoutSeconds)) == true)
	{
		const double endTime = Time::nowInSeconds() + timeoutSeconds;
		while (bytesRead < byteCount)
		{
			uint8 value;
			if (BinaryInputStream::readBinary(&value, 1, timeoutSeconds) == 1)
			{
				value ^= memoryAs<uint8>(&referenceValue, (totalBytesRead-1) & (sizeof(ValueType)-1));
				memoryAs<uint8>(destination, bytesRead) = value;
				++bytesRead;
			}
			else
			{
				const double now = Time::nowInSeconds();
				if (now < endTime)
				{
					timeoutSeconds = endTime - now;
					Thread::yield();
				}
				else
				{
					break;
				}
			}
		}
	}
	return bytesRead;
}



void XorInputStream::unreadBinary(const void* source, int byteCount) const
{
	BL_ASSERT_NEVER_REACHED // TODO Implementation
}



} // namespace Streams
} // namespace BaseLib
