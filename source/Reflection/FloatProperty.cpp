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



FloatProperty::FloatProperty(const String& propertyName, float newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, minimum(-FLT_MAX)
	, maximum(+FLT_MAX)
	, valueRangeEnumeration()
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
	valueRangeEnumeration.setProperty(this);
}



Property::Type FloatProperty::getType() const
{
	return FLOAT_PROPERTY;
}



const Enumeration<String>& FloatProperty::getValueRange() const
{
	return valueRangeEnumeration;
}



void FloatProperty::setValueRange(float newMinimum, float newMaximum)
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



bool FloatProperty::isDefault(const void* instance) const
{
	return getAsFloat(instance) == getDefault(instance);
}



void FloatProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



float FloatProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<FloatProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void FloatProperty::setDefault(float newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void FloatProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}




} // namespace Reflection
} // namespace BaseLib
