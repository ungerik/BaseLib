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



using BaseLib::Containers::Array;
using namespace BaseLib::ErrorHandling;



AbstractSetEnumPropertyFunctor::AbstractSetEnumPropertyFunctor(EnumProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetEnumPropertyFunctor::setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	EnumProperty::Enums::ConstIterator i = property->getEnums().find(propertyValue);
	if (i != property->getEnums().end())
	{
		setPropertyAsInt(instance, i->second/*, arrayIndex*/);
	}
	else
	{
        argumentError(STRING_NO_ENUM_TOKEN(property->getName(), propertyValue));        
	}
}



void AbstractSetEnumPropertyFunctor::setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	EnumProperty::Enums::ConstIterator i = property->getEnums().findValue(propertyValue);
	if (i != property->getEnums().end())
	{
		setPropertyAsIntUnchecked(instance, propertyValue); 
	}
	else
	{
		argumentError("Invalid enum-value");
	}
}



void AbstractSetEnumPropertyFunctor::setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, propertyValue == true ? 1 : 0/*, arrayIndex*/);
}



void AbstractSetEnumPropertyFunctor::setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, round<int>(propertyValue)/*, arrayIndex*/);
}



void AbstractSetEnumPropertyFunctor::setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsInt(instance, round<int>(propertyValue)/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
