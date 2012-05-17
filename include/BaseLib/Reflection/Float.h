/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Float_h
#define BaseLib_Reflection_Float_h



#include "BaseLib/Reflection/BoxedValueType.h"



namespace BaseLib {
namespace Reflection {



class BL_EXPORT Float : public BoxedValueType {
public:

	typedef Float Type;
	typedef float ValueType;

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Reflection::Float, BoxedValueType);

	Float(ValueType newValue);

	ValueType getValue() const;
	virtual void setValue(ValueType newValue);

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

protected:

	ValueType value;
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_Float_h