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



AbstractSetDoublePropertyFunctor::AbstractSetDoublePropertyFunctor(DoubleProperty* forProperty)
	: property(forProperty)
{
}



void AbstractSetDoublePropertyFunctor::setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	double value;

	if (numberFormat->tryParse(propertyValue, value) == true)
	{
		setPropertyAsDouble(instance, value);
	}
	else
	{
		stateError(CANT_SET_FLOAT_PROPERTY_FROM_STRING(property->getName(), propertyValue));
	}
}



void AbstractSetDoublePropertyFunctor::setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsDouble(instance, static_cast<double>(propertyValue)/*, arrayIndex*/);
}



void AbstractSetDoublePropertyFunctor::setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsDouble(instance, propertyValue == true ? 1.0 : 0.0/*, arrayIndex*/);
}



void AbstractSetDoublePropertyFunctor::setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	setPropertyAsDouble(instance, static_cast<double>(propertyValue)/*, arrayIndex*/);
}





} // namespace Reflection
} // namespace BaseLib
