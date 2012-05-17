/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_BufferedBinaryOutputStream_h
#define BaseLib_Streams_BufferedBinaryOutputStream_h


#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"



namespace BaseLib {
namespace Streams {


using BaseLib::Buffers::BinaryMemBuffer;



/**
Buffers binary output data for complete block-writes.
Every write operation is buffered until the cach-buffer is full.
When full, the cache-buffer gets written as complete binary block with writeBinary()
@see @ref BuffersAndStreams, BinaryOutputStream, BinaryInputStream, setBufferSize()
*/
class BL_EXPORT BufferedBinaryOutputStream : public BinaryOutputStream {
public:

	/**
	Default buffer-size used for every new instance.
	@see getBufferSize(), setBufferSize()
	*/
	static int defaultBufferSize;

	explicit BufferedBinaryOutputStream(int bufferSize = defaultBufferSize);
	explicit BufferedBinaryOutputStream(const OutputStream& connectToOutputStream, int bufferSize = defaultBufferSize);
	BufferedBinaryOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, int bufferSize = defaultBufferSize);
	explicit BufferedBinaryOutputStream(AbstractBinaryBuffer& connectToBinaryBuffer, int bufferSize = defaultBufferSize);

	virtual void writeBinary(const void* source, int byteCount) const;

	/**
	Returns the size of the cache-buffer.
	@see setBufferSize()
	*/
	inline int getBufferSize() const
	{
		return cacheBuffer.getSizeAsInt();
	}

	/**
	Sets the size of the cache-buffer.
	@see getBufferSize()
	*/
	void setBufferSize(int newBufferSize);

	/*inline BinaryMemBuffer& getCacheBuffer() { return cacheBuffer; }
	inline const BinaryMemBuffer& getCacheBuffer() const { return cacheBuffer; }*/

	virtual void flush() const;

protected:

	mutable BinaryMemBuffer cacheBuffer;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_BufferedBinaryOutputStream_h
