/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Utilities/StlHelper.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;
using namespace BaseLib::Utilities;



EnumProperty::EnumProperty(const String& propertyName, int newDefaultValue, GetDefaultFunc* newGetDefaultFunc)
	: Property(propertyName)
	, enums()
	, valueRangeEnumeration(&enums)
	, defaultValue(newDefaultValue)
	, getDefaultFunc(newGetDefaultFunc)
{
}



Property::Type EnumProperty::getType() const
{
	return ENUM_PROPERTY;
}



const Enumeration<String>& EnumProperty::getValueRange() const
{
	return valueRangeEnumeration;
}



void EnumProperty::addEnum(int enumValue, const String& enumName)
{
	// Insert if not present:
	bool result = getSecond(enums.insert(Enums::value_type(enumName, enumValue)));

	if (result == false)
	{
		argumentError("Enum " + enumName + " ("+ String::createFrom(enumValue) + ") is already registered!" ERROR_AT);
	}
}



bool EnumProperty::isDefault(const void* instance) const
{
	return getAsInt(instance) == getDefault(instance);
}



void EnumProperty::setToDefault(void* instance)
{
	set(instance, getDefault(instance));
}



int EnumProperty::getDefault(const void* instance) const
{
	if (getDefaultFunc != NULL)
	{
		const_cast<EnumProperty*>(this)->getDefaultFunc->setObject(static_cast<const Object*>(instance));
		return (*getDefaultFunc)();
	}
	else
	{
		return defaultValue;
	}
}



void EnumProperty::setDefault(int newDefaultValue)
{
	defaultValue = newDefaultValue;
	getDefaultFunc = NULL;
}



void EnumProperty::setDefault(GetDefaultFunc* newGetDefaultFunc)
{
	getDefaultFunc = newGetDefaultFunc;
}



} // namespace Reflection
} // namespace BaseLib
