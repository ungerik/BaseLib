/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Void.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_CLASS(Void, BoxedValueType)
{
}



Void::Void(ValueType)
	: BoxedValueType()
{
}



Void::ValueType Void::getValue() const
{
}



void Void::setValue(ValueType)
{
}



} // namespace Reflection
} // namespace BaseLib
