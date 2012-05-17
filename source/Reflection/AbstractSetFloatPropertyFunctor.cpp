/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/Strings/NumberFormat.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;



AbstractSetFloatPropertyFunctor::AbstractSetFloatPropertyFunctor(FloatProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetFloatPropertyFunctor::setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	float value;
	if (numberFormat->tryParse(propertyValue, value) == true)
	{
		setPropertyAsFloat(instance, value);
	}
	else
	{
		stateError(CANT_SET_FLOAT_PROPERTY_FROM_STRING(property->getName(), propertyValue));
	}
}



void AbstractSetFloatPropertyFunctor::setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsFloat(instance, static_cast<float>(propertyValue)/*, arrayIndex*/);
}



void AbstractSetFloatPropertyFunctor::setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsFloat(instance, propertyValue == true ? 1.0f : 0.0f/*, arrayIndex*/);
}



void AbstractSetFloatPropertyFunctor::setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsFloat(instance, static_cast<float>(propertyValue)/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
