/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_BinaryFileBuffer_h
#define BaseLib_Buffers_BinaryFileBuffer_h



#include "BaseLib/intern/Windows.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Buffers/AbstractBinaryBuffer.h"



namespace BaseLib {
namespace Buffers {



using BaseLib::Streams::OutputStream;
using BaseLib::Streams::InputStream;
using BaseLib::Strings::String;


/**
Buffer representing a binary file.
Implementation of AbstractBinaryBuffer
@see @ref AbstractBinaryBuffer, BuffersAndStreams
*/
class BL_EXPORT BinaryFileBuffer : public AbstractBinaryBuffer {
public:

	/**
	Constructor.
	@param fileName path of the file
	@param read the file will be read
	@param write the file will be written
	@see getFileName(), isReadable(), isWriteable()
	*/
	explicit BinaryFileBuffer(const String& newFileName, bool read = true, bool write = true);

	/**
	Destructor, calls close().
	*/
	virtual ~BinaryFileBuffer();

	virtual bool isReadable() const
	{
		return readAllowed;
	}
	virtual bool isWriteable() const
	{
		return writeAllowed;
	}

	virtual void setSize(int64 newByteSize);

	virtual void setCurrentPosition(int64 newCurrentPosition);

	virtual int readFromPosition(int64 positionInBytes, void* destination, int byteCount) const;
	virtual int readFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos = true);

	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount);

	virtual bool insertAtPosition(int64 positionInBytes, int byteCount);

	virtual bool removeAtPosition(int64 positionInBytes, int byteCount);

	virtual void* lock(int64 byteOffset = 0, int byteCount = 0);
	virtual const void* lock(int64 byteOffset = 0, int byteCount = 0) const;
	virtual void unlock(void* lockPointer, int64 byteOffset = 0, int byteCount = 0);
	virtual void discardLock(const void* lockPointer) const;
	virtual bool isLockPerformingCopy() const { return true; }

	void fillWithZero();

	/**
	Returns if the file is open for reading or writing
	@see close(), isReadable(), isWriteable()
	*/
	inline bool isOpen() const
	{
		return fileHandle != INVALID_HANDLE_VALUE;
	}

	virtual void flush();

	virtual void close();

	/**
	Returns the file name.
	*/
	inline const String& getFileName()
	{
		return fileName;
	}

protected:
	
	/**
	Path of file.
	*/
	const String fileName;

	#ifdef BL_PLATFORM_WIN32
		HANDLE fileHandle;
	#endif

	bool readAllowed;
	bool writeAllowed;

	/**
	Size in bytes of data-clusters used for big data manipulations.
	*/
	static const int BinaryFileBuffer::CLUSTER_SIZE;

	/**
	Move all bytes of the buffer back by byteOffset bytes.
	Used create space for writing before the beginning of the buffer.
	*/
	void moveBytesBack(int64 byteOffset);
};



inline InputStream& operator <<(InputStream& inputStream, BinaryFileBuffer& destination)
{
	void* buffer = destination.lock();
	const int bytesRead = inputStream.readBinary(buffer, destination.getSizeAsInt());
	if (bytesRead > 0)
	{
		destination.unlock(buffer);
	}
	else
	{
		destination.discardLock(buffer);
	}
	return inputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, const BinaryFileBuffer& source)
{
	const void* buffer = source.lock();
	outputStream.writeBinary(buffer, source.getSizeAsInt());
	source.discardLock(buffer);
	return outputStream;
}



} // namespace Buffers
} // namespace BaseLib



#endif BaseLib_Buffers_BinaryFileBuffer_h
