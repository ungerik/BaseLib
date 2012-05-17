/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Class.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Reflection/intern/Errors.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



Class::Class(const String& newName, const Class* newParent)
	: name(newName.beginsWith("::") ? newName.subString(2) : newName)
	, parent(newParent)
	, propertyMap()
	, propertyEnumeration(NULL)
	, propertyNames(NULL)
	, metaTags()
{
}



Class::~Class()
{
	foreach (PropertyMap::Iterator, i, propertyMap)
	{
		delete i->second;
	}
}



String Class::getNameWithoutNameSpace() const
{
	int pos = name.findLast("::");
	return pos != String::END ? name.subString(pos + 2) : name;
}



String Class::getNameSpace() const
{
	int pos = name.findLast("::");
	return pos != String::END ? name.subString(0, pos) : "";
}



bool Class::hasProperty(const String& propertyName) const
{
	PropertyMap::ConstIterator i = propertyMap.find(propertyName);
	return i != propertyMap.end();
}



const Enumeration<String>& Class::getPropertyNames() const
{
	if (propertyNames == NULL)
	{
		propertyNames = propertyMap.createKeyEnumeration();
	}
	return *propertyNames;
}



const Enumeration<Property*>& Class::getProperties() const
{
	if (propertyEnumeration == NULL)
	{
		propertyEnumeration = propertyMap.createValueEnumeration();
	}
	return *propertyEnumeration;
}

	
	
Property* Class::property(const String& propertyName)
{
	Property* property = getPropertyOrNull(propertyName);
	if (property == NULL)
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
	return property;
}



const Property* Class::property(const String& propertyName) const
{
	const Property* property = getPropertyOrNull(propertyName);
	if (property == NULL)
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
	return property;
}



Property* Class::getPropertyOrNull(const String& propertyName)
{
	PropertyMap::Iterator i = propertyMap.find(propertyName);
	if (i != propertyMap.end())
	{
		return i->second;
	}
	else
	{
		return NULL;
	}
}



const Property* Class::getPropertyOrNull(const String& propertyName) const
{
	PropertyMap::ConstIterator i = propertyMap.find(propertyName);
	if (i != propertyMap.end())
	{
		return i->second;
	}
	else
	{
		return NULL;
	}
}



void Class::addProperty(Property* newProperty)
{
	if (checkArgumentNotNull(newProperty) == true)
	{
		// Insert if not present:
		std::pair<PropertyMap::Iterator, bool> result = propertyMap.insert(PropertyMap::value_type(newProperty->getName(), newProperty));

		if (result.second == false)
		{
			argumentError(PROPERTY_ALREADY_REGISTERED(newProperty->getName()));
		}
	}
}



StringProperty* Class::getOrCreateStringProperty(const String& propertyName)
{
	StringProperty* stringProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		stringProperty = new StringProperty(propertyName);
		addProperty(stringProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::STRING_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		stringProperty = static_cast<StringProperty*>(abstractProperty);
	}
	return stringProperty;
}



BoolProperty* Class::getOrCreateBoolProperty(const String& propertyName)
{
	BoolProperty* boolProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		boolProperty = new BoolProperty(propertyName);
		addProperty(boolProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::BOOL_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		boolProperty = static_cast<BoolProperty*>(abstractProperty);
	}
	return boolProperty;
}



IntProperty* Class::getOrCreateIntProperty(const String& propertyName)
{
	IntProperty* intProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		intProperty = new IntProperty(propertyName);
		addProperty(intProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::INT_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		intProperty = static_cast<IntProperty*>(abstractProperty);
	}
	return intProperty;
}


FloatProperty* Class::getOrCreateFloatProperty(const String& propertyName)
{
	FloatProperty* floatProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		floatProperty = new FloatProperty(propertyName);
		addProperty(floatProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::FLOAT_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		floatProperty = static_cast<FloatProperty*>(abstractProperty);
	}
	return floatProperty;
}


DoubleProperty* Class::getOrCreateDoubleProperty(const String& propertyName)
{
	DoubleProperty* doubleProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		doubleProperty = new DoubleProperty(propertyName);
		addProperty(doubleProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::DOUBLE_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		doubleProperty = static_cast<DoubleProperty*>(abstractProperty);
	}
	return doubleProperty;
}


EnumProperty* Class::getOrCreateEnumProperty(const String& propertyName)
{
	EnumProperty* enumProperty;
	Property* abstractProperty = getPropertyOrNull(propertyName);
	if (abstractProperty == NULL)
	{
		enumProperty = new EnumProperty(propertyName);
		addProperty(enumProperty);
	}
	else
	{
		if (abstractProperty->getType() != Property::ENUM_PROPERTY)
		{
			stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
			return NULL;
		}
		enumProperty = static_cast<EnumProperty*>(abstractProperty);
	}
	return enumProperty;
}



void Class::addPropertyMetaTag(const String& propertyName, const String& metaTag)
{
	Property* abstractProperty = property(propertyName);
	if (abstractProperty != NULL)
	{
		abstractProperty->addMetaTag(metaTag);
	}
	else
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
}



void Class::removePropertyMetaTag(const String& propertyName, const String& metaTag)
{
	Property* abstractProperty = property(propertyName);
	if (abstractProperty != NULL)
	{
		abstractProperty->removeMetaTag(metaTag);
	}
	else
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
}



void Class::unregisterProperty(const String& propertyName)
{
	PropertyMap::Iterator i = propertyMap.find(propertyName);
	if (i != propertyMap.end())
	{
		delete i->second;
		propertyMap.erase(i);
	}
	else
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
}

/*
void Class::setPropertyArrayLength(const String& propertyName, int constArrayLength)
{
	Property* abstractProperty = property(propertyName);
	if (abstractProperty != NULL)
	{
		abstractProperty->setArrayFunctor(new FixedArrayLengthFunctor(constArrayLength));
	}
	else
	{
		argumentError(PROPERTY_NOT_FOUND(propertyName));
	}
}
*/


} // namespace Reflection
} // namespace BaseLib
