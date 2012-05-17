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



AbstractGetEnumPropertyFunctor::AbstractGetEnumPropertyFunctor(EnumProperty* forProperty)
	: property(forProperty)
{
}



BaseLib::Strings::String AbstractGetEnumPropertyFunctor::getProperty(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	int intResult = getPropertyAsInt(instance/*, arrayIndex*/);
	EnumProperty::Enums::ConstIterator result = property->getEnums().findValue(intResult);
	if (result != property->getEnums().end())
	{
		return result->first;
	}
	else
	{
		resultError("Invalid enum-value!" ERROR_AT);
		return Empty();
	}
}



bool AbstractGetEnumPropertyFunctor::getPropertyAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	BaseLib::Strings::String stringResult = getProperty(instance/*, arrayIndex*/);
	bool result = false;
	if (stringResult.tryParse(result) == false)
	{
		stateError(CANT_CONVERT_STRING_PROPERTY_TO_BOOL(property->getName(), stringResult));
	}
	return result;
}



float AbstractGetEnumPropertyFunctor::getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return static_cast<float>(getPropertyAsInt(instance/*, arrayIndex*/));
}



double AbstractGetEnumPropertyFunctor::getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsInt(instance/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
