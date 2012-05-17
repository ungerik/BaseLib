/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/XorOutputStream.h"
#include "BaseLib/ErrorHandling.h"


namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;



XorOutputStream::XorOutputStream(ValueType newReferenceValue)
	: BinaryOutputStream()
	, referenceValue(newReferenceValue)
{
}



XorOutputStream::XorOutputStream(const OutputStream& connectToOutputStream, ValueType newReferenceValue)
	: BinaryOutputStream(connectToOutputStream)
	, referenceValue(newReferenceValue)
{
}



XorOutputStream::XorOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, ValueType newReferenceValue)
	: BinaryOutputStream(connectToOutputStream1, connectToOutputStream2)
	, referenceValue(newReferenceValue)
{
}



XorOutputStream::XorOutputStream(AbstractBinaryBuffer& connectToBuffer, ValueType newReferenceValue)
	: BinaryOutputStream(connectToBuffer)
	, referenceValue(newReferenceValue)
{
}



void XorOutputStream::writeBinary(const void* source, int byteCount) const
{
	if (checkArgumentNotNull(NAME_VALUE(source)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true)
	{
		const int count = byteCount / sizeof(ValueType);
		const int remainder = byteCount % sizeof(ValueType);
		for (int i = 0; i < count; ++i)
		{
			ValueType value = memoryAs<ValueType>(source, 0);
			value ^= referenceValue;			
			BL_ASSERT((value ^ referenceValue) == memoryAs<ValueType>(source, 0));
			BinaryOutputStream::writeBinary(&value, sizeof(value));
			source = offsetPointer(source, sizeof(value));
		}

		for (int i = 0; i < remainder; ++i)
		{
			uint8 value = memoryAs<uint8>(source, 0);
			value ^= memoryAs<uint8>(&referenceValue, i);
			BL_ASSERT((value ^ memoryAs<uint8>(&referenceValue, i)) == memoryAs<uint8>(source, 0));
			BinaryOutputStream::writeBinary(&value, sizeof(value));
			source = offsetPointer(source, sizeof(value));
		}
	}
}



} // namespace Streams
} // namespace BaseLib
