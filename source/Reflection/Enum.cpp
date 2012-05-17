/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Enum.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Enum, BoxedValueType)
{
	registerProperty("value", &Enum::getValue, &Enum::setValue);
}



Enum::Enum(int newValue)
	: BoxedValueType()
	, value(newValue)
{
}



int Enum::getValue() const
{
	return value;
}



void Enum::setValue(int newValue)
{
	value = newValue;
}



} // namespace Reflection
} // namespace BaseLib
