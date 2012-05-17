/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_XorOutputStream_h
#define BaseLib_XorOutputStream_h



#include "BaseLib/Streams/BinaryOutputStream.h"



namespace BaseLib {
namespace Streams {



class BL_EXPORT XorOutputStream : public BinaryOutputStream {
public:

	typedef uint64 ValueType;

	explicit XorOutputStream(ValueType newReferenceValue = 0);
	explicit XorOutputStream(const OutputStream& connectToOutputStream, ValueType newReferenceValue = 0);
	XorOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, ValueType newReferenceValue = 0);
	explicit XorOutputStream(AbstractBinaryBuffer& connectToBuffer, ValueType newReferenceValue = 0);

	virtual void writeBinary(const void* source, int byteCount) const;

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



#endif // #ifndef BaseLib_XorOutputStream_h
