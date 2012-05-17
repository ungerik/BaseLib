/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/intern/Errors.h"
#include <limits.h>



namespace BaseLib {
namespace Buffers {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Utilities;



BinaryMemBuffer::BinaryMemBuffer(int64 byteSize, bool fillWithZero)
  : AbstractBinaryBuffer(fillWithZero)
  , bufferAddress(0)
#ifdef BL_PLATFORM_WIN32
  , heapHandle(0)
#endif
{
	setSize(byteSize);
}



BinaryMemBuffer::BinaryMemBuffer(void* useBufferAddress, int64 byteCount)
  : AbstractBinaryBuffer()
  , bufferAddress(useBufferAddress)
#ifdef BL_PLATFORM_WIN32
  , heapHandle(0)
#endif
{
	if (useBufferAddress != NULL)
	{
		size = byteCount;
	}
	else
	{
		setSize(byteCount);
	}
}



BinaryMemBuffer::~BinaryMemBuffer()
{
	if (heapHandle != 0)
	{
		HeapFree(heapHandle, 0, bufferAddress);
	}
}



void BinaryMemBuffer::setPointer(void* newPointer)
{
	if (heapHandle != 0)
	{
		HeapFree(heapHandle, 0, bufferAddress);
		heapHandle = 0;
	}

	bufferAddress = newPointer;
	if (bufferAddress == NULL)
	{
		size = 0;
	}
}



void BinaryMemBuffer::close()
{
}


void BinaryMemBuffer::setSize(int64 newByteSize)
{
	BL_ASSERT(newByteSize >= 0);

	// If we use a foreign momory-block don't allocate a own:
	if (heapHandle == 0 && size != 0)
	{
		size = newByteSize;
		return;		
	}

	if (newByteSize != size)
	{
		#ifdef BL_PLATFORM_WIN32
			if (newByteSize > UINT_MAX)
			{
				argumentError(INVALID_BUFFER_SIZE(newByteSize, UINT_MAX));
				return;
			}

			if (heapHandle == 0)
			{
				BL_ASSERT(size == 0);

				heapHandle = GetProcessHeap();
				if (heapHandle == 0)
				{
					resultError(String("Can't access heap !") + SYSTEM_ERROR + ERROR_AT); 
					return;
				}
			}

			const DWORD flags = allocateZeroFilled == true ? HEAP_ZERO_MEMORY : 0;

			if (size == 0)
			{
				bufferAddress = HeapAlloc(heapHandle, flags, static_cast<SIZE_T>(newByteSize));
				if (bufferAddress == 0)
				{
					resultError(String("Can't allocate from heap !") + SYSTEM_ERROR + ERROR_AT); 
					return;
				}
			}
			else
			{
				if (newByteSize > 0)
				{
					void* newBufferAddress = HeapReAlloc(heapHandle, flags, bufferAddress, static_cast<SIZE_T>(newByteSize));
					if (newBufferAddress == 0)
					{
						resultError(String("Can't reallocate from heap !") + SYSTEM_ERROR + ERROR_AT); 
						return;
					}
					
					bufferAddress = newBufferAddress;
				}
				else
				{
					BOOL res = HeapFree(heapHandle, 0, bufferAddress);
					BL_ASSERT(res != NULL);
					bufferAddress = NULL;
					heapHandle = 0;
				}
			}
		#endif

		size = newByteSize;
	}
}



int BinaryMemBuffer::readFromPosition(int64 positionInBytes, void* destination, int byteCount) const
{
	BL_ASSERT(positionInBytes >= 0);
	BL_ASSERT(destination != NULL);

	const int64 endOffset = positionInBytes + byteCount;
	if (endOffset > size)
	{
		byteCount = static_cast<int>(size - positionInBytes);
	}
	else if (endOffset < 0)
	{
		byteCount = -static_cast<int>(positionInBytes);
	}

	#ifdef BL_PLATFORM_WIN32
		if (byteCount > 0)
		{
			CopyMemory(destination, &static_cast<char*>(bufferAddress)[positionInBytes], byteCount);
		}
		else if (byteCount < 0)
		{
			CopyMemory(destination, &static_cast<char*>(bufferAddress)[positionInBytes+byteCount], -byteCount);
		}
		/* now readAllFromPosition()
		else // if (byteCount == 0)
		{
			const int64 remainingBytes = size - positionInBytes;
			if (remainingBytes <= INT_MAX)
			{
				byteCount = static_cast<int>(remainingBytes);
				CopyMemory(destination, &static_cast<char*>(bufferAddress)[positionInBytes], byteCount);
			}
			else
			{
				error(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
				return 0;
			}
		}
		*/
	#endif

	return byteCount;
}



int BinaryMemBuffer::writeAtPosition(int64 positionInBytes, const void* source, int byteCount)
{
	BL_ASSERT(source != NULL);

	if (byteCount != 0)
	{
		if (positionInBytes < 0)
		{
//			if (heapHandle == 0)
//			{
//				argumentError("writeAtPosition() not supported with negative positionInBytes for foreign memory-block!" ERROR_AT);
//				return 0;
//			}
			
			setSize(size-positionInBytes);
			#ifdef BL_PLATFORM_WIN32
				MoveMemory(bufferAddress, offsetPointer(bufferAddress, -positionInBytes), static_cast<SIZE_T>(size+positionInBytes));
			#endif
			currentPosition -= positionInBytes;
			positionInBytes = 0;
		}

		const int64 endOffset = positionInBytes + byteCount;
		if (endOffset > size)
		{
//			if (heapHandle == 0)
//			{
//				argumentError("writeAtPosition() not supported with endOffset larger than foreign memory-block!" ERROR_AT);
//				return 0;
//			}
			
			setSize(endOffset);
		}
		else if (endOffset < 0)
		{
//			if (heapHandle == 0)
//			{
//				argumentError("writeAtPosition() not supported with negative endOffset for foreign memory-block!" ERROR_AT);
//				return 0;
//			}
			
			setSize(size-endOffset);
			#ifdef BL_PLATFORM_WIN32
				MoveMemory(bufferAddress, offsetPointer(bufferAddress, -endOffset), static_cast<SIZE_T>(size+endOffset));
			#endif
			currentPosition -= endOffset;
			positionInBytes = -byteCount;
		}

		if (byteCount < 0)
		{
			byteCount = -byteCount;
			positionInBytes -= byteCount;
		}
		/*
		byteCount == 0 sollte immer bedeuten, dass keine Bytes geschrieben werden,
		und nicht dass bis zum Ende des Puffers geschrieben wird!
		else if (byteCount == 0)
		{
			const int64 remainingBytes = size - positionInBytes;
			if (remainingBytes <= INT_MAX)
			{
				byteCount = static_cast<int>(remainingBytes);
			}
			else
			{
				error(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
				return 0;
			}
		}
		*/

		#ifdef BL_PLATFORM_WIN32
			CopyMemory(&static_cast<char*>(bufferAddress)[positionInBytes], source, byteCount);
		#endif
	}

	return byteCount;
}



bool BinaryMemBuffer::insertAtPosition(int64 positionInBytes, int byteCount)
{
	BL_ASSERT(positionInBytes >= 0);
	if (byteCount != 0)
	{
		if (byteCount < 0)
		{
			byteCount = -byteCount;
			positionInBytes -= byteCount;
		}

		const int64 oldSize = size;
		setSize(size + byteCount);

		MoveMemory(offsetPointer(bufferAddress, static_cast<int>(positionInBytes) + byteCount),
					offsetPointer(bufferAddress, static_cast<int>(positionInBytes)),
					static_cast<SIZE_T>(oldSize - positionInBytes));
	}
	return true;
}



bool BinaryMemBuffer::removeAtPosition(int64 positionInBytes, int byteCount)
{
	BL_ASSERT(positionInBytes >= 0);
	if (byteCount != 0)
	{
		if (byteCount < 0)
		{
			byteCount = -byteCount;
			positionInBytes -= byteCount;
		}

		BL_ASSERT(positionInBytes >= 0);		
		if (positionInBytes < 0) positionInBytes = 0;

		BL_ASSERT(positionInBytes + byteCount <= size);
		if (positionInBytes + byteCount > size) byteCount = static_cast<int>(size - positionInBytes);

		setSize(size - byteCount);

		MoveMemory(offsetPointer(bufferAddress, static_cast<int>(positionInBytes)),
					offsetPointer(bufferAddress, static_cast<int>(positionInBytes) + byteCount),
					static_cast<SIZE_T>(size - positionInBytes));
	}
	return true;
}



void* BinaryMemBuffer::lock(int64 byteOffset, int byteCount)
{
	if (byteCount < 0)
	{
		byteCount = -byteCount;
		byteOffset -= byteCount;
	}

	BL_ASSERT(byteOffset >= 0);
	BL_ASSERT(bufferAddress != 0);
	BL_ASSERT(byteOffset+byteCount <= size);

	return offsetPointer(bufferAddress, byteOffset);
}



const void* BinaryMemBuffer::lock(int64 byteOffset, int byteCount) const
{
	return const_cast<BinaryMemBuffer*>(this)->lock(byteOffset, byteCount);
}






void BinaryMemBuffer::fillWithZero()
{
	#ifdef BL_PLATFORM_WIN32
		ZeroMemory(bufferAddress, static_cast<SIZE_T>(size));
	#endif	
}


} // namespace Buffers
} // namespace BaseLib
