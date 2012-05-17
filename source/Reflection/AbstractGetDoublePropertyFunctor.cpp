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



using namespace BaseLib::Utilities;
using namespace BaseLib::Math;



AbstractGetDoublePropertyFunctor::AbstractGetDoublePropertyFunctor(DoubleProperty* forProperty)
	: property(forProperty)
{
}



BaseLib::Strings::String AbstractGetDoublePropertyFunctor::getProperty(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	double doubleResult = getPropertyAsDouble(instance/*, arrayIndex*/);
	return numberFormat->format(doubleResult);
}



int AbstractGetDoublePropertyFunctor::getPropertyAsInt(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	double doubleResult = getPropertyAsDouble(instance/*, arrayIndex*/);
	return round<int>(doubleResult);
}



bool AbstractGetDoublePropertyFunctor::getPropertyAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	double doubleResult = getPropertyAsDouble(instance/*, arrayIndex*/);
	return doubleResult != 0.0;
}



float AbstractGetDoublePropertyFunctor::getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	return static_cast<float>(getPropertyAsDouble(instance/*, arrayIndex*/));
}



} // namespace Reflection
} // namespace BaseLib
