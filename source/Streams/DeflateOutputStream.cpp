/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/DeflateOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include <zlib.h>



namespace BaseLib {
namespace Streams {



using namespace BaseLib::Buffers;
using namespace BaseLib::ErrorHandling;



DeflateOutputStream::DeflateOutputStream(double newCompressionLevel, int newMaxCompressionBufferSize)
  : BinaryOutputStream()
  , compressionLevel(static_cast<float>(newCompressionLevel))
  , maxCompressionBufferSize(newMaxCompressionBufferSize)
  , zStream(new z_stream)
{
	initZStream();
}



DeflateOutputStream::DeflateOutputStream(const OutputStream& connectToOutputStream, double newCompressionLevel, int newMaxCompressionBufferSize)
  : BinaryOutputStream(connectToOutputStream)
  , compressionLevel(static_cast<float>(newCompressionLevel))
  , maxCompressionBufferSize(newMaxCompressionBufferSize)
  , zStream(new z_stream)
{
	initZStream();
}



DeflateOutputStream::DeflateOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, double newCompressionLevel, int newMaxCompressionBufferSize)
  : BinaryOutputStream(connectToOutputStream1, connectToOutputStream2)
  , compressionLevel(static_cast<float>(newCompressionLevel))
  , maxCompressionBufferSize(newMaxCompressionBufferSize)
  , zStream(new z_stream)
{
	initZStream();
}



DeflateOutputStream::DeflateOutputStream(AbstractBinaryBuffer& connectToBuffer, double newCompressionLevel, int newMaxCompressionBufferSize)
  : BinaryOutputStream(connectToBuffer)
  , compressionLevel(static_cast<float>(newCompressionLevel))
  , maxCompressionBufferSize(newMaxCompressionBufferSize)
  , zStream(new z_stream)
{
	initZStream();
}



DeflateOutputStream::~DeflateOutputStream()
{
	deflateEnd(zStream);
	delete zStream;
}



void DeflateOutputStream::initZStream()
{
	if (compressionLevel > 1.0f || compressionLevel < 0.0f)
	{
		argumentError(ILLEGAL_COMPRESSION_LEVEL(compressionLevel));
		if (compressionLevel > 1.0f) compressionLevel = 1.0f;
		if (compressionLevel < 0.0f) compressionLevel = 0.0f;
	}

	memset(zStream, 0, sizeof(z_stream));
	int res = deflateInit(zStream, static_cast<int>(9.0f * compressionLevel + 0.5f));
	if (res != Z_OK)
	{
		resultError(ZLIB_ERROR(zStream->msg));
	}
}



void DeflateOutputStream::resetCompression()
{
	int res = deflateReset(zStream);
	if (res != Z_OK)
	{
		resultError(ZLIB_ERROR(zStream->msg));
	}

	compressionBuffer.setSize(0);
}



void DeflateOutputStream::resetCompression(double newCompressionLevel)
{
	int res = deflateEnd(zStream);
	if (res != Z_OK)
	{
		resultError(ZLIB_ERROR(zStream->msg));
	}

	compressionLevel = static_cast<float>(newCompressionLevel);
	initZStream();

	compressionBuffer.setSize(0);
}



void DeflateOutputStream::setMaxCompressionBufferSize(int newMaxCompressionBufferSize)
{
	BL_ASSERT(newMaxCompressionBufferSize > 0);
	BL_ASSERT(newMaxCompressionBufferSize <= 1024*1024);

	if (newMaxCompressionBufferSize < compressionBuffer.getSizeAsInt())
	{
		compressionBuffer.setSize(newMaxCompressionBufferSize);
	}

	maxCompressionBufferSize = newMaxCompressionBufferSize;
}



void DeflateOutputStream::writeBinary(const void* source, int byteCount) const
{
	if (byteCount > compressionBuffer.getSizeAsInt())
	{
		compressionBuffer.setSize(byteCount < maxCompressionBufferSize ? byteCount : maxCompressionBufferSize);
	}

	const int compressionBufferSize = compressionBuffer.getSizeAsInt();
	Bytef* compressionBufferPointer = static_cast<Bytef*>( compressionBuffer.lock() );

	zStream->next_in = static_cast<Bytef*>(const_cast<void*>( source ));
	zStream->avail_in = byteCount;
	zStream->next_out = compressionBufferPointer;
	zStream->avail_out = compressionBufferSize;
	
	int res = deflate(zStream, Z_FINISH);
	while (res == Z_OK)
	{
		BinaryOutputStream::writeBinary(compressionBufferPointer, compressionBufferSize - zStream->avail_out);

		zStream->next_out = compressionBufferPointer;
		zStream->avail_out = compressionBufferSize;
		res = deflate(zStream, Z_FINISH);
	}
	if (res != Z_STREAM_END)
	{
		resultError(ZLIB_ERROR(zStream->msg));
	}

	BinaryOutputStream::writeBinary(compressionBufferPointer, compressionBufferSize - zStream->avail_out);
}



} // namespace Streams
} // namespace BaseLib
