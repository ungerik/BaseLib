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



using namespace BaseLib::ErrorHandling;



AbstractSetStringPropertyFunctor::AbstractSetStringPropertyFunctor(StringProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetStringPropertyFunctor::setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	setProperty(instance, numberFormat->format(propertyValue)/*, arrayIndex*/);
}



void AbstractSetStringPropertyFunctor::setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	setProperty(instance, numberFormat->format(propertyValue)/*, arrayIndex*/);
}



void AbstractSetStringPropertyFunctor::setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	setProperty(instance, numberFormat->format(propertyValue)/*, arrayIndex*/);
}



void AbstractSetStringPropertyFunctor::setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	setProperty(instance, numberFormat->format(propertyValue)/*, arrayIndex*/);
}



} // namespace Reflection
} // namespace BaseLib
