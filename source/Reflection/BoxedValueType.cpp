/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/BoxedValueType.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_BASE_CLASS(BoxedValueType)
{
	registerProperty("isDefaultValue", &BoxedValueType::isDefaultValue);
	registerProperty("type", &BoxedValueType::getType);
}



bool BoxedValueType::isDefaultValue() const
{
	return isPropertyDefault("value");
}



void BoxedValueType::setValueToDefault()
{
	setPropertyToDefault("value");
}



String BoxedValueType::getType() const
{
	return getClass()->getNameWithoutNameSpace();
}



} // namespace Reflection
} // namespace BaseLib
