/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_XorInputStream_h
#define BaseLib_Streams_XorInputStream_h



#include "BaseLib/Streams/BinaryInputStream.h"



namespace BaseLib {
namespace Streams {



class BL_EXPORT XorInputStream : public BinaryInputStream {
public:

	typedef uint64 ValueType;

	explicit XorInputStream(ValueType newReferenceValue = 0);
	explicit XorInputStream(const InputStream& connectToInputStream, ValueType newReferenceValue = 0);
	explicit XorInputStream(AbstractBinaryBuffer& connectToBuffer, ValueType newReferenceValue = 0);

	virtual int readBinary(void* destination, int byteCount, double timeoutSeconds) const;
	virtual void unreadBinary(const void* source, int byteCount) const; 

	inline ValueType getReferenceValue() const
	{
		return referenceValue;
	}

	inline void setReferenceValue(ValueType newReferenceValue)
	{
		referenceValue = newReferenceValue;
	}

protected:

	ValueType referenceValue;
};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_XorInputStream_h
