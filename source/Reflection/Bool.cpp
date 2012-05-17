/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Bool.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Bool, BoxedValueType)
{
	registerProperty("value", &Bool::getValue, &Bool::setValue);
}



Bool::Bool(ValueType newValue)
	: BoxedValueType()
	, value(newValue)
{
}



Bool::ValueType Bool::getValue() const
{
	return value;
}



void Bool::setValue(ValueType newValue)
{
	value = newValue;
}



} // namespace Reflection
} // namespace BaseLib
