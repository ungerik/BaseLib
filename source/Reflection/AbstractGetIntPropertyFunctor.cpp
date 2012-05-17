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



AbstractGetIntPropertyFunctor::AbstractGetIntPropertyFunctor(IntProperty* forProperty)
	: property(forProperty)
{
}



BaseLib::Strings::String AbstractGetIntPropertyFunctor::getProperty(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	int intResult = getPropertyAsInt(instance/*, arrayIndex*/);
	return numberFormat->format(intResult);
}



bool AbstractGetIntPropertyFunctor::getPropertyAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	int intResult = getPropertyAsInt(instance/*, arrayIndex*/);
	return intResult != 0;
}



float AbstractGetIntPropertyFunctor::getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return static_cast<float>(getPropertyAsInt(instance/*, arrayIndex*/));
}



double AbstractGetIntPropertyFunctor::getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsInt(instance/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
