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



AbstractGetStringPropertyFunctor::AbstractGetStringPropertyFunctor(StringProperty* forProperty)
	: property(forProperty)
{
}



int AbstractGetStringPropertyFunctor::getPropertyAsInt(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	BaseLib::Strings::String stringResult = getProperty(instance/*, arrayIndex*/);
	stringResult.lowerCase();
	
	int result = 0;
	if (numberFormat->tryParse(stringResult, result) == false)
	{
		bool resultAsBool;
		if (numberFormat->tryParse(stringResult, resultAsBool) == true)
		{
			return resultAsBool;
		}
		else
		{
			stateError(CANT_CONVERT_STRING_PROPERTY_TO_INT(property->getName(), stringResult));
		}
	}
	return result;
}



bool AbstractGetStringPropertyFunctor::getPropertyAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	BaseLib::Strings::String stringResult = getProperty(instance/*, arrayIndex*/);

	bool result = false;
	if (numberFormat->tryParse(stringResult, result) == false)
	{
		stateError(CANT_CONVERT_STRING_PROPERTY_TO_BOOL(property->getName(), stringResult));
	}
	return result;
}



float AbstractGetStringPropertyFunctor::getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	BaseLib::Strings::String stringResult = getProperty(instance/*, arrayIndex*/);
	stringResult.lowerCase();

	float result = 0.0f;
	if (numberFormat->tryParse(stringResult, result) == false)
	{
		bool resultAsBool;
		if (numberFormat->tryParse(stringResult, resultAsBool) == true)
		{
			return resultAsBool;
		}
		else
		{
			stateError(CANT_CONVERT_STRING_PROPERTY_TO_FLOAT(property->getName(), stringResult));
		}
	}
	return result;
}



double AbstractGetStringPropertyFunctor::getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (numberFormat == NULL) numberFormat = NumberFormat::getDefault();
	BaseLib::Strings::String stringResult = getProperty(instance/*, arrayIndex*/);
	stringResult.lowerCase();

	double result = 0.0;
	if (numberFormat->tryParse(stringResult, result) == false)
	{
		stateError(CANT_CONVERT_STRING_PROPERTY_TO_FLOAT(property->getName(), stringResult));
	}
	return result;
}



} // namespace Reflection
} // namespace BaseLib
