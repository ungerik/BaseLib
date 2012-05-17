/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Double.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Double, BoxedValueType)
{
	registerProperty("value", &Double::getValue, &Double::setValue);
}



Double::Double(ValueType newValue)
	: BoxedValueType()
	, value(newValue)
{
}



Double::ValueType Double::getValue() const
{
	return value;
}



void Double::setValue(ValueType newValue)
{
	value = newValue;
}



} // namespace Reflection
} // namespace BaseLib
