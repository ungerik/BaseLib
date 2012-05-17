/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_VoidBinaryBuffer_h
#define BaseLib_Buffers_VoidBinaryBuffer_h



#include "BaseLib/Buffers/AbstractBinaryBuffer.h"



namespace BaseLib {
namespace Buffers {


/**
Void buffer with size zero.
Implementation of AbstractBinaryBuffer
@see @ref AbstractBinaryBuffer, BuffersAndStreams
*/
class BL_EXPORT VoidBinaryBuffer : public AbstractBinaryBuffer {
public:

	virtual void close();

	/**
	Has no effect, the buffer remains void.
	*/
	virtual void setSize(int64 newByteSize);

	virtual int readFromPosition(int64 positionInBytes, void* destination, int byteCount) const;
	virtual int writeAtPosition(int64 positionInBytes, const void* source, int byteCount);
	virtual bool insertAtPosition(int64 positionInBytes, int byteCount);
	virtual bool removeAtPosition(int64 positionInBytes, int byteCount);

	virtual void* lock(int64 byteOffset = 0, int byteCount = 0);
	virtual const void* lock(int64 byteOffset = 0, int byteCount = 0) const;
	virtual void unlock(void* lockPointer, int64 byteOffset = 0, int byteCount = 0);
	virtual void discardLock(const void* lockPointer) const;
	virtual bool isLockPerformingCopy() const;
	virtual void fillWithZero();

};



} // namespace Buffers
} // namespace BaseLib



#endif // #ifndef BaseLib_Buffers_VoidBinaryBuffer_h
