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



AbstractSetBoolPropertyFunctor::AbstractSetBoolPropertyFunctor(BoolProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetBoolPropertyFunctor::setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	bool value;

	if (numberFormat->tryParse(propertyValue, value) == true)
	{
		setPropertyAsBool(instance, value);
	}
	else
	{
		stateError(CANT_CONVERT_STRING_PROPERTY_TO_BOOL(property->getName(), propertyValue));
	}
}



void AbstractSetBoolPropertyFunctor::setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsBool(instance, propertyValue != 0/*, arrayIndex*/);
}



void AbstractSetBoolPropertyFunctor::setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsBool(instance, propertyValue != 0.0f/*, arrayIndex*/);
}



void AbstractSetBoolPropertyFunctor::setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsBool(instance, propertyValue != 0.0/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
