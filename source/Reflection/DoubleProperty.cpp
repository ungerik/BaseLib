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



DoubleProperty::DoubleProperty(const String& propertyName, double newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, minimum(-DBL_MAX)
	, maximum(+DBL_MAX)
	, valueRangeEnumeration()
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
	valueRangeEnumeration.setProperty(this);
}



Property::Type DoubleProperty::getType() const
{
	return DOUBLE_PROPERTY;
}



const Enumeration<String>& DoubleProperty::getValueRange() const
{
	return valueRangeEnumeration;
}



void DoubleProperty::setValueRange(double newMinimum, double newMaximum)
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



bool DoubleProperty::isDefault(const void* instance) const
{
	return getAsDouble(instance) == getDefault(instance);
}



void DoubleProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



double DoubleProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<DoubleProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void DoubleProperty::setDefault(double newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void DoubleProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}



} // namespace Reflection
} // namespace BaseLib
