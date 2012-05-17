/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BufferedBinaryOutputStream.h"



namespace BaseLib {
namespace Streams {



BufferedBinaryOutputStream::BufferedBinaryOutputStream(int bufferSize)
	: BinaryOutputStream()
	, cacheBuffer(bufferSize)
{
}



BufferedBinaryOutputStream::BufferedBinaryOutputStream(const OutputStream& connectToOutputStream, int bufferSize)
	: BinaryOutputStream(connectToOutputStream)
	, cacheBuffer(bufferSize)
{
}



BufferedBinaryOutputStream::BufferedBinaryOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, int bufferSize)
	: BinaryOutputStream(connectToOutputStream1, connectToOutputStream2)
	, cacheBuffer(bufferSize)
{
}



BufferedBinaryOutputStream::BufferedBinaryOutputStream(AbstractBinaryBuffer& connectToBinaryBuffer, int bufferSize)
	: BinaryOutputStream(connectToBinaryBuffer)
	, cacheBuffer(bufferSize)
{
}



void BufferedBinaryOutputStream::flush() const
{
	BinaryOutputStream::flush();
	BinaryOutputStream::writeBinary(cacheBuffer.lock(), cacheBuffer.getCurrentPositionAsInt());
	cacheBuffer.setCurrentPosition(0);
}



void BufferedBinaryOutputStream::writeBinary(const void* source, int byteCount) const
{
	BL_ASSERT(byteCount >= 0);

	const int bufferSize = getBufferSize();
	const int availableBufferSize = bufferSize - cacheBuffer.getCurrentPositionAsInt();
	if (byteCount < availableBufferSize)
	{
		cacheBuffer.writeAtCurrentPosition(source, byteCount);
	}
	else
	{
		if (byteCount < availableBufferSize + bufferSize)
		{
			cacheBuffer.writeAtCurrentPosition(source, availableBufferSize);
			flush();

			source = offsetPointer(source, availableBufferSize);
			byteCount -= availableBufferSize;

			cacheBuffer.writeAtCurrentPosition(source, byteCount);
		}
		else
		{
			flush();
			BinaryOutputStream::writeBinary(source, byteCount);
		}
	}
}



void BufferedBinaryOutputStream::setBufferSize(int newBufferSize)
{
	BL_ASSERT(newBufferSize >= 0);
	if (newBufferSize <= cacheBuffer.getCurrentPositionAsInt()) flush();
	cacheBuffer.setSize(newBufferSize);
}



} // namespace Streams
} // namespace BaseLib
