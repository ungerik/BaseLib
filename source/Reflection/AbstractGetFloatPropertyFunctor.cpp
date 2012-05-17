/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/Strings/NumberFormat.h"
#include "BaseLib/Math.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::Utilities;
using namespace BaseLib::Math;



AbstractGetFloatPropertyFunctor::AbstractGetFloatPropertyFunctor(FloatProperty* forProperty)
	: property(forProperty)
{
}



BaseLib::Strings::String AbstractGetFloatPropertyFunctor::getProperty(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	float floatResult = getPropertyAsFloat(instance/*, arrayIndex*/);
	return numberFormat->format(floatResult);
}



int AbstractGetFloatPropertyFunctor::getPropertyAsInt(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	float floatResult = getPropertyAsFloat(instance/*, arrayIndex*/);
	return round<int>(floatResult);
}



bool AbstractGetFloatPropertyFunctor::getPropertyAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	float floatResult = getPropertyAsFloat(instance/*, arrayIndex*/);
	return floatResult != 0.0f && floatResult != NAN;
}



double AbstractGetFloatPropertyFunctor::getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return getPropertyAsFloat(instance/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
