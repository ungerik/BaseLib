/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_AbstractBinaryBuffer_h
#define BaseLib_Buffers_AbstractBinaryBuffer_h



#include "BaseLib/Common.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Types.h"



namespace BaseLib {
namespace Buffers {



/**
Abstract base-class for buffers with binary data.
@see @ref BuffersAndStreams
*/
class BL_EXPORT AbstractBinaryBuffer {
public:

	/**
	Destructor.
	Derived constructors must call close().
	*/
	virtual ~AbstractBinaryBuffer();

	/**
	Closes the buffer for reading and writing.
	@see flush()
	*/
	virtual void close() = 0;

	/**
	Returns the size of the buffer in bytes as int64.
	@see isEmpty()
	*/
	inline int64 getSize() const { return size;	}

	/**
	Returns the size of the buffer in bytes as int.
	*/
	int getSizeAsInt() const;

	/**
	Resizes the buffer.
	@see getSize()
	*/
	virtual void setSize(int64 newByteSize) = 0;

	/**
	Return true if the size is zero.
	@see getSize()
	*/
	inline bool isEmpty() const
	{
		return getSize() == 0;
	}

	/**
	Returns if the buffer is readable.
	@see readFromPosition()
	*/
	virtual bool isReadable() const;

	/**
	Returns if the buffer is writeable.
	@see writeAtPosition()
	*/
	virtual bool isWriteable() const;

	/**
	Returns the current position of the read/write cursor as int64 in bytes.
	@see getCurrentPositionAsInt(), setCurrentPosition()
	*/
	inline int64 getCurrentPosition() const
	{
		return currentPosition;
	}

	/**
	Returns the current position of the read/write cursor as int in bytes.
	@see getCurrentPosition(), setCurrentPosition()
	*/
	int getCurrentPositionAsInt() const;

	/**
	Sets the current position of the read/write cursor in bytes.
	@see getCurrentPosition()
	*/
	virtual void setCurrentPosition(int64 newCurrentPositionInBytes)
	{
		currentPosition = newCurrentPositionInBytes;
	}

	/**
	Moves the current position of the read/write cursor by an ammount of bytes.
	@see setCurrentPosition(), getCurrentPosition()
	*/
	inline void moveCurrentPosition(int64 byteCount)
	{
		setCurrentPosition(getCurrentPosition() + byteCount);
	}

	/**
	Returns the distance in bytes from the current read/write cursor position to the end of the buffer.
	@see setCurrentPosition(), getCurrentPosition(), moveCurrentPosition()
	*/
	virtual int64 availableBytesFromCurrentPosition() const
	{
		return getSize() - getCurrentPosition();
	}

	/**
	Returns if reading from the current position of the read/write cursor is possible.
	Does not move the current read/write position
	@see availableBytesFromCurrentPosition(), isReadable()
	*/
	inline bool readFromCurrentPositionPossible() const
	{
		return isReadable() == true && availableBytesFromCurrentPosition() > 0;
	}

	/**
	Reads from a specified position in the buffer.
	Does not move the current read/write position
	@param positionInBytes must be positive
	@param destination must not be null
	@param byteCount if negative, the bytes are read before the position 
	@returns number of bytes read
	@see readAllFromPosition(), readCompleteFromPosition(), readFromCurrentPosition()
	*/
	virtual int readFromPosition(int64 positionInBytes, void* destination, int byteCount) const = 0;

	/**
	Reads all available bytes from a specified position in the buffer.
	Does not move the current read/write position
	@param positionInBytes must be positive
	@param destination must not be null
	@returns number of bytes read
	@see availableBytesFromCurrentPosition(), readCompleteFromPosition(), readAllFromCurrentPosition()
	*/
	virtual int readAllFromPosition(int64 positionInBytes, void* destination) const;

	/**
	Tries to read all available bytes from a specified position in the buffer with a timeout.
	Does not move the current read/write position
	@param positionInBytes must be positive
	@param destination must not be null
	@param byteCount if negative, the bytes are read before the position 
	@returns true if all bytes have been read within the timeout duration
	@see readAllFromPosition(), readFromPosition(), setTimeoutForNextRead(), readCompleteFromCurrentPosition()
	*/
	virtual bool readCompleteFromPosition(int64 positionInBytes, void* destination, int byteCount) const;

	/**
	Reads from the current position of the read/write cursor.
	@param destination must not be null
	@param byteCount if negative, the bytes are read before the position 
	@param moveCurrentPos if true, the current position is moved by the number of bytes read
	@returns number of bytes read
	@see readAllFromCurrentPosition(), readCompleteFromCurrentPosition(), getCurrentPosition(), readFromPosition()
	*/
	virtual int readFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos = true);

	/**
	Reads all available bytes from the current position of the read/write cursor.
	@param destination must not be null
	@param moveCurrentPos if true, the current position is moved by the number of bytes read
	@returns number of bytes read
	@see readFromCurrentPosition(), readCompleteFromCurrentPosition(), getCurrentPosition(), readFromPosition()
	*/
	virtual int readAllFromCurrentPosition(void* destination, bool moveCurrentPos = true);

	/**
	Tries to read all available bytes from the current position of the read/write cursor with a timeout.
	@param destination must not be null
	@param byteCount if negative, the bytes are read before the position 
	@param moveCurrentPos if true, the current position is moved by the number of bytes read
	@returns number of bytes read
	@see readAllFromCurrentPosition(), readFromCurrentPosition(), getCurrentPosition(), readFromPosition()
	*/
	virtual bool readCompleteFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos = true);

	/**
	Writes to a specified position in the buffer.
	@param positionInBytes can be netative or greater than the buffer size
	@param source must not be null
	@param byteCount if negative, the bytes are written before the position 
	@returns number of bytes written
	@see writeAtCurrentPosition(), readFromPosition()
	*/
	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount) = 0;

	/**
	Writes to the current position of the read/write cursor in the buffer.
	@param positionInBytes can be netative or greater than the buffer size
	@param source must not be null
	@param byteCount if negative, the bytes are written before the position 
	@param moveCurrentPos if true, the current position is moved by the number of bytes written
	@returns number of bytes written
	@see writeAtPosition(), readFromCurrentPosition()
	*/
	inline int writeAtCurrentPosition(const void* source, int byteCount, bool moveCurrentPos = true)
	{
		const int bytesWritten = writeAtPosition(currentPosition, source, byteCount);
		if (bytesWritten > 0 && moveCurrentPos == true)
		{
			moveCurrentPosition(byteCount >= 0 ? bytesWritten : byteCount);
		}
		return bytesWritten;
	}

	/**
	Inserts a gap at a specified position in the buffer.
	All bytes from the position to the buffer-end get moved by the size of the gap.
	Nothing gets written to the gap.
	@param positionInBytes must be within zero an the size of the buffer
	@param byteCount if negative, the bytes are inserted before the position 
	@returns true if the gap was inserted
	@see writeAtCurrentPosition(), readFromPosition(), removeAtPosition()
	*/
	virtual bool insertAtPosition(int64 positionInBytes, int byteCount) = 0;

	/**
	Inserts a gap at the current position of the read/write cursor in the buffer.
	All bytes from the position to the buffer-end get moved by the size of the gap.
	Nothing gets written to the gap.
	@param byteCount if negative, the bytes are written before the position 
	@param moveCurrentPos if true, the current position is moved by the number of bytes written
	@returns number of bytes written
	@see writeAtPosition(), readFromCurrentPosition(), removeAtCurrentPosition()
	*/
	inline bool insertAtCurrentPosition(int byteCount, bool moveCurrentPos = true)
	{
		const bool result = insertAtPosition(currentPosition, byteCount);
		if (result == true && moveCurrentPos == true)
		{
			moveCurrentPosition(byteCount);
		}
		return result;
	}

	/**
	Removes a range of bytes at a specified position from the buffer.
	@param positionInBytes must be within zero an the size of the buffer
	@param byteCount if negative, the bytes are inserted before the position 
	@returns true if the gap was inserted
	@see removeAtCurrentPosition(), insertAtPosition()
	*/
	virtual bool removeAtPosition(int64 positionInBytes, int byteCount) = 0;

	/**
	Removes a range of bytes at the current position of the read/write cursor from the buffer.
	@param byteCount if negative, the bytes are written before the position 
	@param moveCurrentPos if true, the current position is moved by the number of bytes written
	@returns number of bytes written
	@see removeAtPosition(), insertAtCurrentPosition()
	*/
	inline bool removeAtCurrentPosition(int byteCount, bool moveCurrentPos = true)
	{
		const bool result = removeAtPosition(currentPosition, byteCount);
		if (result == true && moveCurrentPos == true && byteCount < 0)
		{
			moveCurrentPosition(byteCount);
		}
		return result;
	}

	/**
	Locks a range of the buffer, and returns a pointer to that range.
	The content of the memory-block referenced by the pointer can be modified.
	If isLockPerformingCopy() returns true, the content of the changed memory-block
	will be copied back to the original buffer memory when unlock() is called.
	If discardLock() is called instead of unlock() nothing gets copied back.
	If isLockPerformingCopy() returns false, the lock() returns the real address of the buffer-memory,
	so every change to this memory effects directly the buffer content.
	So unlock() and discardLock() have no effect.
	@param byteOffset offset of the beginning of the range in bytes, has to be positive
	@param byteCount if zero the whole range to the end of the buffer gets locked, if negative the range before byteOffset gets locked 
	@returns address of the locked memory-block
	@see unlock(), discardLock(), isLockPerformingCopy()
	*/
	virtual void* lock(int64 byteOffset = 0, int byteCount = 0) = 0;

	/**
	Locks a range of the buffer, and returns a pointer to that range.
	The content of the memory-block referenced by the pointer can be modified.
	If isLockPerformingCopy() returns true, the content of the changed memory-block
	will be copied back to the original buffer memory when unlock() is called.
	If discardLock() is called instead of unlock() nothing gets copied back.
	If isLockPerformingCopy() returns false, the lock() returns the real address of the buffer-memory,
	so every change to this memory effects directly the buffer content.
	So unlock() and discardLock() have no effect.
	@param byteOffset offset of the beginning of the range in bytes, has to be positive
	@param byteCount if zero the whole range to the end of the buffer gets locked, if negative the range before byteOffset gets locked 
	@returns address of the locked memory-block
	@see unlock(), discardLock(), isLockPerformingCopy()
	*/
	virtual const void* lock(int64 byteOffset = 0, int byteCount = 0) const = 0;

	/**
	Unlocks a locked range of the buffer and copies changes back if necessary.
	If isLockPerformingCopy() returns true, the content of the changed memory-block
	will be copied back to the original buffer memory when unlock() is called.
	If discardLock() is called instead of unlock() nothing gets copied back.
	If isLockPerformingCopy() returns false, the lock() returns the real address of the buffer-memory,
	so every change to this memory effects directly the buffer content.
	So unlock() and discardLock() have no effect.
	@param lockPointer pointer returned by lock()
	@param byteOffset offset of the beginning of the range in bytes, has to be positive
	@param byteCount if zero the whole range to the end of the buffer gets unlocked, if negative the range before byteOffset gets unlocked 
	@see lock(), discardLock(), isLockPerformingCopy()
	*/
	virtual void unlock(void* lockPointer, int64 byteOffset = 0, int byteCount = 0) = 0;

	/**
	Unlocks a locked range of the buffer and copies nothing back.
	If isLockPerformingCopy() returns true, the content of the changed memory-block
	will be copied back to the original buffer memory when unlock() is called.
	If discardLock() is called instead of unlock() nothing gets copied back.
	If isLockPerformingCopy() returns false, the lock() returns the real address of the buffer-memory,
	so every change to this memory effects directly the buffer content.
	So unlock() and discardLock() have no effect.
	@param lockPointer pointer returned by lock()
	@param byteOffset offset of the beginning of the range in bytes, has to be positive
	@param byteCount if zero the whole range to the end of the buffer gets unlocked, if negative the range before byteOffset gets unlocked 
	@see lock(), unlock(), isLockPerformingCopy()
	*/
	virtual void discardLock(const void* lockPointer) const = 0;

	/**
	Returns if unlock() will have to copy changes back to the buffer.
	@return If isLockPerformingCopy() returns true, the content of the changed memory-block
	will be copied back to the original buffer memory when unlock() is called. If discardLock() is called instead of unlock() nothing gets copied back.	If isLockPerformingCopy() returns false, the lock() returns the real address of the buffer-memory,so every change to this memory effects directly the buffer content. So unlock() and discardLock() have no effect.
	@see lock(), unlock(), discardLock()
	*/
	virtual bool isLockPerformingCopy() const = 0;

	/**
	Fills the whole buffer with zeros.
	@see isAllocateFilledWithZero(), setAllocateFilledWithZero()
	*/
	virtual void fillWithZero() = 0;

	/**
	Returns if new allocated memory gets filled with zeros.
	@see fillWithZero(), setAllocateFilledWithZero()
	*/
	inline bool isAllocateFilledWithZero()
	{
		return allocateZeroFilled;
	}

	/**
	Sets if new allocated memory gets filled with zeros.
	@see fillWithZero(), isAllocateFilledWithZero()
	*/
	inline void setAllocateFilledWithZero(bool newAllocateZeroFilled)
	{
		allocateZeroFilled = newAllocateZeroFilled;
	}

	/**
	Returns the timeout in seconds used for the next read operation.
	@note Not all implementations of AbstractBinaryBuffer must support read-timeouts.
	@see setTimeoutForNextRead()
	*/
	virtual double getTimeoutForNextRead() const
	{
		return 0.0;
	}

	/**
	Sets the timeout in seconds for the next read operation.
	@note Not all implementations of AbstractBinaryBuffer must support read-timeouts.
	@see getTimeoutForNextRead()
	*/
	virtual void setTimeoutForNextRead(double newReadTimeoutSeconds)
	{
	}

	/**
	Flushes the content of the buffer if necessary.
	@see close()
	*/
	virtual void flush()
	{
	}

protected:

	/**
	Constructor.
	@param fillWithZero
	@see setAllocateFilledWithZero(), fillWithZero, ~AbstractBinaryBuffer(), close()
	*/
	explicit AbstractBinaryBuffer(bool fillWithZero = false);

	/**
	Current size of the buffer in bytes.
	*/
	int64 size;

	/**
	Current position of the read/write cursor in the buffer in bytes.
	*/
	int64 currentPosition;

	/**
	Determines if new allocated memory gets filled with zeros.
	*/
	bool allocateZeroFilled;
};



using BaseLib::Streams::OutputStream;


/**
Writes the content of the buffer into a stream.
*/
inline OutputStream& operator <<(OutputStream& lhs, AbstractBinaryBuffer& right)
{
	void* buffer = right.lock();
	lhs.writeBinary(buffer, right.getSizeAsInt());
	right.discardLock(buffer);

	return lhs;
}



/**
Empty implementation of AbstractBinaryBuffer.
All virtual methods implemented with BL_ASSERT_NEVER_REACHED
@see AbstractBinaryBuffer
*/
class BL_EXPORT DefaultBinaryBuffer : public AbstractBinaryBuffer {
public:

	explicit DefaultBinaryBuffer(bool fillWithZero = false) : AbstractBinaryBuffer(fillWithZero) {}

	virtual void setSize(int64 newByteSize)	{ BL_ASSERT_NEVER_REACHED }
	virtual int readFromPosition(int64 positionInBytes, void* destination, int byteCount = 0) const	{ BL_ASSERT_NEVER_REACHED return 0;	}
	virtual bool readCompleteFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos = true) { BL_ASSERT_NEVER_REACHED return false; }
	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount) { BL_ASSERT_NEVER_REACHED return 0; }
	virtual int writeAtCurrentPosition(const void* source, int byteCount, bool moveCurrentPos = true) { BL_ASSERT_NEVER_REACHED return 0; }
	virtual bool insertAtPosition(int64 positionInBytes, int byteCount) { BL_ASSERT_NEVER_REACHED return false; }
	virtual bool insertAtCurrentPosition(int byteCount, bool moveCurrentPos = true) { BL_ASSERT_NEVER_REACHED return false; }
	virtual bool removeAtPosition(int64 positionInBytes, int byteCount) { BL_ASSERT_NEVER_REACHED return false; }
	virtual bool removeAtCurrentPosition(int byteCount, bool moveCurrentPos = true) { BL_ASSERT_NEVER_REACHED return false; }
	virtual void* lock(int64 byteOffset = 0, int byteCount = 0) { BL_ASSERT_NEVER_REACHED return NULL; }
	virtual const void* lock(int64 byteOffset = 0, int byteCount = 0) const { BL_ASSERT_NEVER_REACHED return NULL; }
	virtual void unlock(void* lockPointer, int64 byteOffset = 0, int byteCount = 0) { BL_ASSERT_NEVER_REACHED }
	virtual void discardLock(const void* lockPointer) const { BL_ASSERT_NEVER_REACHED }
	virtual bool isLockPerformingCopy() const { BL_ASSERT_NEVER_REACHED return false; }
	virtual void fillWithZero() { BL_ASSERT_NEVER_REACHED }
};



} // namespace Buffers
} // namespace BaseLib



#endif // #ifndef BaseLib_Buffers_AbstractBinaryBuffer_h
