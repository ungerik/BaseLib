/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/Strings/NumberFormat.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Math.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;



AbstractSetIntPropertyFunctor::AbstractSetIntPropertyFunctor(IntProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetIntPropertyFunctor::setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	int value;
	if (numberFormat->tryParse(propertyValue, value) == true)
	{
		setPropertyAsInt(instance, value);
	}
	else
	{
		bool boolValue;
		if (numberFormat->tryParse(propertyValue, boolValue) == true)
		{
			setPropertyAsBool(instance, boolValue);
		}
		else
		{
			stateError(CANT_SET_FLOAT_PROPERTY_FROM_STRING(property->getName(), propertyValue));
		}		
	}
}



void AbstractSetIntPropertyFunctor::setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, propertyValue == true ? 1 : 0/*, arrayIndex*/);
}



void AbstractSetIntPropertyFunctor::setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, round<int>(propertyValue)/*, arrayIndex*/);
}



void AbstractSetIntPropertyFunctor::setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, round<int>(propertyValue)/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
