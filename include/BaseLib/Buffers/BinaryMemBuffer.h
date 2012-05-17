/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_BinaryMemBuffer_h
#define BaseLib_Buffers_BinaryMemBuffer_h


#include "BaseLib/intern/Windows.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Buffers/AbstractBinaryBuffer.h"




namespace BaseLib {
namespace Buffers {



/**
Buffer representing a block of binary system-memory (RAM).
TODO: custom allocator
@see @ref BuffersAndStreams
*/
class BL_EXPORT BinaryMemBuffer : public AbstractBinaryBuffer {
public:

	/**
	Creates a binary buffer in system RAM.
	@param byteSize must be positive
	@param fillWithZero
	@see BinaryMemBuffer(void* useBufferAddress, int64 byteSize), getPointer()
	*/
	explicit BinaryMemBuffer(int64 byteSize = 0, bool fillWithZero = false);

	/**
	Wraps an existing memory-block with an BinaryMemBuffer instance.
	@param byteSize must be positive
	@see BinaryMemBuffer(int64 byteSize, bool fillWithZero), getPointer()
	*/
	BinaryMemBuffer(void* useBufferAddress, int64 byteCount);

	/**
	Destructor, calls close().
	*/
	virtual ~BinaryMemBuffer();

	virtual void close();

	virtual void setSize(int64 newByteSize);

	virtual int readFromPosition(int64 positionInBytes, void* destination, int byteCount) const;

	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount);

	virtual bool insertAtPosition(int64 positionInBytes, int byteCount);

	virtual bool removeAtPosition(int64 positionInBytes, int byteCount);

	virtual void* lock(int64 byteOffset = 0, int byteCount = 0);
	virtual const void* lock(int64 byteOffset = 0, int byteCount = 0) const;
	inline virtual void unlock(void* lockPointer, int64 byteOffset = 0, int byteCount = 0) {}
	inline virtual void discardLock(const void* lockPointer) const {}
	inline virtual bool isLockPerformingCopy() const { return false; }

	virtual void fillWithZero();

	/**
	Returns a pointer to the managed memory.
	*/
	inline void* getPointer()
	{
		return bufferAddress;
	}

	/**
	Returns a pointer to the managed memory.
	*/
	inline const void* getPointer() const
	{
		return bufferAddress;
	}

	void setPointer(void* newPointer);

protected:

	void* bufferAddress;

	#ifdef BL_PLATFORM_WIN32
		HANDLE heapHandle;
	#endif

};



using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;



/**
Reads from the inpust-stream until the buffer with predefined size is full.
@see OutpustStream::readBinary()
*/
inline InputStream& operator >>(InputStream& inputStream, BinaryMemBuffer& destination)
{
	inputStream.readBinary(destination.lock(), destination.getSizeAsInt());
	return inputStream;
}


/**
Writes the content of the whole buffer to an output-stream.
@see OutpustStream::writeBinary()
*/
inline OutputStream& operator <<(OutputStream& outputStream, const BinaryMemBuffer& source)
{
	outputStream.writeBinary(source.lock(), source.getSizeAsInt());
	return outputStream;
}



} // namespace Buffers
} // namespace BaseLib


#endif // #ifndef BaseLib_Buffers_BinaryMemBuffer_h
