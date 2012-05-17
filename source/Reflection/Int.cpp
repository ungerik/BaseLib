/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Int.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Int, BoxedValueType)
{
	registerProperty("value", &Int::getValue, &Int::setValue);
}



Int::Int(ValueType newValue)
	: BoxedValueType()
	, value(newValue)
{
}



Int::ValueType Int::getValue() const
{
	return value;
}



void Int::setValue(ValueType newValue)
{
	value = newValue;
}



} // namespace Reflection
} // namespace BaseLib
