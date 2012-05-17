/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Buffers/VoidBinaryBuffer.h"



namespace BaseLib {
namespace Buffers {



using namespace BaseLib::Math;



void VoidBinaryBuffer::close()
{
}



void VoidBinaryBuffer::setSize(int64 newByteSize)
{
	size = newByteSize;
}



int VoidBinaryBuffer::readFromPosition(int64 positionInBytes, void* destination, int byteCount) const
{
	return static_cast<int>(min(size - positionInBytes, (int64)byteCount));
}



int VoidBinaryBuffer::writeAtPosition(int64 positionInBytes, const void* source, int byteCount)
{
	size = max(size, positionInBytes + byteCount);
	return byteCount;
}



bool VoidBinaryBuffer::insertAtPosition(int64 positionInBytes, int byteCount)
{
	size = max(size, positionInBytes + byteCount);
	return true;
}



bool VoidBinaryBuffer::removeAtPosition(int64 positionInBytes, int byteCount)
{
	if (byteCount <= size - positionInBytes)
	{
		size -= byteCount;
		return true;
	}
	else
	{
		return false;
	}
}



void* VoidBinaryBuffer::lock(int64 byteOffset, int byteCount)
{
	return NULL;
}



const void* VoidBinaryBuffer::lock(int64 byteOffset, int byteCount) const
{
	return NULL;
}



void VoidBinaryBuffer::unlock(void* lockPointer, int64 byteOffset, int byteCount)
{
}



void VoidBinaryBuffer::discardLock(const void* lockPointer) const
{
}



bool VoidBinaryBuffer::isLockPerformingCopy() const
{
	return false;
}



void VoidBinaryBuffer::fillWithZero()
{
}



} // namespace Buffers
} // namespace BaseLib
