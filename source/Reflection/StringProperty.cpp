/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



StringProperty::StringProperty(const String& propertyName, const String& newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, minimumLength(0)
	, maximumLength(INT_MAX)
	, valueRangeEnumeration()
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
	valueRangeEnumeration.setProperty(this);
}



Property::Type StringProperty::getType() const
{
	return STRING_PROPERTY;
}



const Enumeration<String>& StringProperty::getValueRange() const
{
	return valueRangeEnumeration;
}



void StringProperty::setValueRange(int newMinimum, int newMaximum)
{
	if (newMinimum < 0)
	{
		argumentError("Minimum-length(" + String::createFrom(newMinimum) + ") of string must be greater/equal 0 for property " + getName() + " !" ERROR_AT);
	}
	else
	{
		minimumLength = newMinimum;
	}

	if (newMaximum < newMinimum)
	{
		argumentError("Maximum-length (" + String::createFrom(newMaximum) + ") of string smaller than minimum-length (" + String::createFrom(newMinimum) + ") for property " + getName() + " !" ERROR_AT);
	}
	else
	{
		maximumLength = newMaximum;
	}
}



bool StringProperty::isDefault(const void* instance) const
{
	return get(instance) == getDefault(instance);
}



void StringProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



String StringProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<StringProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void StringProperty::setDefault(const String& newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void StringProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}



} // namespace Reflection
} // namespace BaseLib
