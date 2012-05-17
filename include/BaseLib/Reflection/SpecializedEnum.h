/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_SpecializedEnum_h
#define BaseLib_Reflection_SpecializedEnum_h



#include "BaseLib/Reflection/BoxedValueType.h"



namespace BaseLib {
namespace Reflection {



template<typename E>
class BL_EXPORT SpecializedEnum : public BoxedValueType {
public:

	typedef SpecializedEnum<E> Type;
	typedef E ValueType;

	SpecializedEnum(ValueType newValue)
		: Enum(newValue)
	{
	}

	inline ValueType getEnumValue() const
	{
		return static_cast<ValueType>(value);
	}

	inline ValueType operator ()() const
	{
		return getEnumValue();
	}

	inline operator ValueType() const
	{
		return getEnumValue();
	}

	inline Type& operator =(const ValueType& right)
	{
		value = right;
		return *this;
	}

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_SpecializedEnum_h