/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_String_h
#define BaseLib_Reflection_String_h



#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Reflection {



class BL_EXPORT BoxedString : public Object {
public:

	typedef BoxedString Type;
	typedef BaseLib::Strings::String ValueType;

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Reflection::BoxedString);

	BoxedString(const ValueType& newValue);

	ValueType getValue() const;
	void setValue(const ValueType& newValue);

	inline ValueType operator ()() const
	{
		return value;
	}

	inline operator ValueType() const
	{
		return value;
	}

	inline Type& operator =(const ValueType& right)
	{
		value = right;
		return *this;
	}

	int getLength() const;
	void setLength(int newLength);

	BaseLib::Strings::StringEncoding getEncoding() const;

protected:

	ValueType value;
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_String_h