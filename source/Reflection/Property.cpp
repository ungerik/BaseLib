/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



Property::Property(const String& propertyName)
	: name(propertyName)
	, persistent(true)
//	, arrayFunctor(NULL)
	, getterFunctor(NULL)
	, setterFunctor(NULL)
//	, propertyDescription()
//	, invisibleInPropertyExplorer(false)
	, metaTags()
{
}



Property::~Property()
{
}



String Property::getTypeAsString() const
{
	switch (getType())
	{
		case STRING_PROPERTY: return "string";
		case ENUM_PROPERTY: return "enum";
		case BOOL_PROPERTY: return "bool";
		case INT_PROPERTY: return "int";
		case FLOAT_PROPERTY: return "float";
		case DOUBLE_PROPERTY: return "double";
		default: return BaseLib::Strings::String();
	}
}



String Property::get(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getGetterFunctor() != NULL)
		{
			return getGetterFunctor()->getProperty(instance/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_READABLE(name));
		}
	}

	return Empty();
}



int Property::getAsInt(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getGetterFunctor() != NULL)
		{
			return getGetterFunctor()->getPropertyAsInt(instance/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_READABLE(name));
		}
	}

	return 0;
}



bool Property::getAsBool(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getGetterFunctor() != NULL)
		{
			return getGetterFunctor()->getPropertyAsBool(instance/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_READABLE(name));
		}
	}

	return false;
}



float Property::getAsFloat(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getGetterFunctor() != NULL)
		{
			return getGetterFunctor()->getPropertyAsFloat(instance/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_READABLE(name));
		}
	}

	return 0.0f;
}



double Property::getAsDouble(const void* instance, const NumberFormat* numberFormat/*, int arrayIndex*/) const
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getGetterFunctor() != NULL)
		{
			return getGetterFunctor()->getPropertyAsDouble(instance/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_READABLE(name));
		}
	}

	return 0.0;
}



void Property::set(void* instance, const String& propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getSetterFunctor() != NULL)
		{
			return getSetterFunctor()->setProperty(instance, propertyValue/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_WRITEABLE(name));
		}
	}
}



void Property::set(void* instance, int propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getSetterFunctor() != NULL)
		{
			return getSetterFunctor()->setPropertyAsInt(instance, propertyValue/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_WRITEABLE(name));
		}
	}
}



void Property::set(void* instance, bool propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getSetterFunctor() != NULL)
		{
			return getSetterFunctor()->setPropertyAsBool(instance, propertyValue/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_WRITEABLE(name));
		}
	}
}



void Property::set(void* instance, float propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getSetterFunctor() != NULL)
		{
			return getSetterFunctor()->setPropertyAsFloat(instance, propertyValue/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_WRITEABLE(name));
		}
	}
}



void Property::set(void* instance, double propertyValue, const NumberFormat* numberFormat/*, int arrayIndex*/)
{
	if (checkArgumentNotNull(NAME_VALUE(instance)) == true)
	{
		if (getSetterFunctor() != NULL)
		{
			return getSetterFunctor()->setPropertyAsDouble(instance, propertyValue/*, arrayIndex*/);
		}
		else
		{
			stateError(PROPERTY_NOT_WRITEABLE(name));
		}
	}
}



bool Property::hasMetaTag(const String& metaTag) const
{
	if (metaTag == NON_SERIALIZEABLE)
	{
		return getterFunctor == NULL || setterFunctor == NULL || metaTags.find(metaTag) != metaTags.end();
	}
	else
	{
		return metaTags.find(metaTag) != metaTags.end();
	}
}



void Property::addMetaTag(const String& metaTag)
{
	metaTags.insert(metaTag);
}



void Property::removeMetaTag(const String& metaTag)
{
	metaTags.erase(metaTag);
}



/*
bool Property::isFixedArrayLength() const
{
	return getArrayFunctor()->isFixedArrayLength();
}



int Property::getArrayLength(const void* instance) const
{
	checkArgumentNotNull(NAME_VALUE(instance));
	return getArrayFunctor()->getArrayLength(instance);
}



void Property::setArrayLength(void* instance, int newArrayLength) const
{
	checkArgumentNotNull(NAME_VALUE(instance));
	getArrayFunctor()->setArrayLength(instance, newArrayLength);
}
*/


} // namespace Reflection
} // namespace BaseLib
