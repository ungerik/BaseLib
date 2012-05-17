/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Float.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Float, BoxedValueType)
{
	registerProperty("value", &Float::getValue, &Float::setValue);
}



Float::Float(ValueType newValue)
	: BoxedValueType()
	, value(newValue)
{
}



Float::ValueType Float::getValue() const
{
	return value;
}



void Float::setValue(ValueType newValue)
{
	value = newValue;
}



} // namespace Reflection
} // namespace BaseLib
