/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::Strings;



BoolProperty::BoolProperty(const String& propertyName, bool newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
}



Property::Type BoolProperty::getType() const
{
	return BOOL_PROPERTY;
}



const Enumeration<String>& BoolProperty::getValueRange() const
{
	const static String values[] = {"false", "true"};
	const static StringArrayEnumeration valueRange(values, 2);
	return valueRange;
}



bool BoolProperty::isDefault(const void* instance) const
{
	return getAsBool(instance) == getDefault(instance);
}



void BoolProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



bool BoolProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<BoolProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void BoolProperty::setDefault(bool newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void BoolProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}



} // namespace Reflection
} // namespace BaseLib
