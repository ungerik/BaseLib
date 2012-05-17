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



IntProperty::IntProperty(const String& propertyName, int newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, minimum(INT_MIN)
	, maximum(INT_MAX)
	, valueRangeEnumeration()
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
	valueRangeEnumeration.setProperty(this);
}



Property::Type IntProperty::getType() const
{
	return INT_PROPERTY;
}



const Enumeration<String>& IntProperty::getValueRange() const
{
	return valueRangeEnumeration;
}



void IntProperty::setValueRange(int newMinimum, int newMaximum)
{
	if (newMinimum < newMaximum)
	{
		minimum = newMinimum;
		maximum = newMaximum;
	}
	else
	{
		argumentError("Minimum (" + String::createFrom(newMinimum) + ") greater than maximum (" + String::createFrom(newMaximum) + ") for property " + getName() + " !" ERROR_AT);
	}
}



bool IntProperty::isDefault(const void* instance) const
{
	return getAsInt(instance) == getDefault(instance);
}



void IntProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



int IntProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<IntProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void IntProperty::setDefault(int newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void IntProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}



} // namespace Reflection
} // namespace BaseLib
