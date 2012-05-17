/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/Strings/NumberFormat.h"



namespace BaseLib {
namespace Reflection {



AbstractGetBoolPropertyFunctor::AbstractGetBoolPropertyFunctor(BoolProperty* forProperty)
	: property(forProperty)
{
}



BaseLib::Strings::String AbstractGetBoolPropertyFunctor::getProperty(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	const bool boolResult = getPropertyAsBool(instance/*, arrayIndex*/);
	return numberFormat->format(boolResult);
}



int AbstractGetBoolPropertyFunctor::getPropertyAsInt(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsBool(instance/*, arrayIndex*/);
}



float AbstractGetBoolPropertyFunctor::getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsBool(instance/*, arrayIndex*/);
}



double AbstractGetBoolPropertyFunctor::getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsBool(instance/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
