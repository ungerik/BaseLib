/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/PropertiesTreeIterator.h"
#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/ErrorHandling.h"




namespace BaseLib {
namespace Reflection {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Trees;
using namespace BaseLib::Streams;
using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(PropertiesTreeIterator, AbstractTreeIterator)
{
}




PropertiesTreeIterator::PropertiesTreeIterator(Object* forObject, const NumberFormat* useNumberFormat)
	: object(forObject)
	, constObject(forObject)
	, currentProperty()
	, stateStack()
	, numberFormat(useNumberFormat)
{
}



PropertiesTreeIterator::PropertiesTreeIterator(const Object* forConstObject, const NumberFormat* useNumberFormat)
	: object(NULL)
	, constObject(forConstObject)
	, currentProperty()
	, stateStack()
	, numberFormat(useNumberFormat)
{
}



AbstractTreeIterator* PropertiesTreeIterator::clone() const
{
	return (isObjectConst() == true) ?
		new PropertiesTreeIterator(constObject, numberFormat) :
		new PropertiesTreeIterator(object, numberFormat);
}



bool PropertiesTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const PropertiesTreeIterator*>(rightImplementation)->object == object &&
		static_cast<const PropertiesTreeIterator*>(rightImplementation)->constObject == constObject &&
		static_cast<const PropertiesTreeIterator*>(rightImplementation)->currentProperty == currentProperty;
}



bool PropertiesTreeIterator::isAttribute() const
{
	return currentProperty.isEmpty() == false;
}



BaseLib::Strings::String PropertiesTreeIterator::getName() const
{
	return isAttribute() == true ? currentProperty : constObject->getClass()->getName();
}



BaseLib::Strings::String PropertiesTreeIterator::getNamespace() const
{
	return Empty();
}



bool PropertiesTreeIterator::hasMetaTag(const BaseLib::Strings::String& metaTag) const
{
	return isAttribute() == true ? constObject->hasPropertyMetaTag(currentProperty, metaTag) : constObject->hasMetaTag(metaTag);
}



bool PropertiesTreeIterator::isReadable() const
{
	return isAttribute() == true ? constObject->isPropertyReadable(currentProperty) : false;
}



bool PropertiesTreeIterator::isWriteable() const
{
	return isAttribute() == true && isObjectConst() == false ? constObject->isPropertyWriteable(currentProperty) : false;
}



InputStream* PropertiesTreeIterator::createInputStream() const
{
	return NULL;
}



OutputStream* PropertiesTreeIterator::createOutputStream() const
{
	return NULL;
}



BaseLib::Strings::String PropertiesTreeIterator::getValue() const
{	
	const bool readable = 
		isAttribute() == true &&
		constObject->isPropertyReadable(currentProperty);

	return readable == true ? constObject->getProperty(currentProperty, numberFormat) : String();
}



void PropertiesTreeIterator::setValue(const BaseLib::Strings::String& newValue) const
{
	if (isAttribute() == true && object != NULL && object->isPropertyWriteable(currentProperty) == true)
	{
		object->setProperty(currentProperty, newValue, numberFormat);
	}
}



BaseLib::Strings::String PropertiesTreeIterator::getValueOfAttribute(const BaseLib::Strings::String& attributeName) const
{
	const bool readable = 
		constObject->getClass()->hasProperty(attributeName) &&
		constObject->isPropertyReadable(attributeName);

	return readable == true ? constObject->getProperty(attributeName, numberFormat) : String();
}



void PropertiesTreeIterator::setValueOfAttribute(const BaseLib::Strings::String& attributeName, const BaseLib::Strings::String& newValue) const
{
	if (isAttribute() == true && object != NULL && object->isPropertyWriteable(attributeName) == true)
	{
		object->setProperty(attributeName, newValue, numberFormat);
	}
}



BaseLib::Strings::String PropertiesTreeIterator::getType() const
{
	return isAttribute() == true ? constObject->getClass()->property(currentProperty)->getTypeAsString() : constObject->getClass()->getName();
}



bool PropertiesTreeIterator::isDefaultValue() const
{
	return isAttribute() == true ? constObject->isPropertyDefault(currentProperty) : false;
}



void PropertiesTreeIterator::setDefaultValue() const
{
	if (isAttribute() == true && isObjectConst() == false)
	{
		object->setPropertyToDefault(currentProperty);
	}
}



const Enumeration<BaseLib::Strings::String>& PropertiesTreeIterator::getValueRange() const
{
	if (isAttribute() == true)
	{
		return constObject->getPropertyValueRange(currentProperty);
	}
	else
	{
		static const EmptyEnumeration<BaseLib::Strings::String> emptyStringEnumeration;
		return emptyStringEnumeration;
	}
}



void PropertiesTreeIterator::push()
{
	stateStack.push(currentProperty);
}



void PropertiesTreeIterator::pop(bool restorePosition, bool restoreStack)
{
	if (restorePosition == true)
	{
		currentProperty = stateStack.top();
	}
	if (restoreStack == true)
	{
		stateStack.pop();
	}
}



int PropertiesTreeIterator::getAttributeCount() const
{
	return constObject->getClass()->getProperties().getCount();
}



int PropertiesTreeIterator::getAttributePosition() const
{
	if (isAttribute() == true)
	{
		int position = 0;
		const Enumeration<BaseLib::Strings::String>& propertyNames = constObject->getClass()->getPropertyNames();
		for (Enumeration<BaseLib::Strings::String>::Iterator i = propertyNames.begin(); i != propertyNames.end(); ++i, ++position)
		{
			if (currentProperty == *i)
			{
				return position;
			}
		}
		BL_ASSERT_NEVER_REACHED
	}

	return -1;
}



bool PropertiesTreeIterator::moveToAttribute(int attributePosition)
{
	int position = 0;
	const Enumeration<BaseLib::Strings::String>& propertyNames = constObject->getClass()->getPropertyNames();
	for (Enumeration<BaseLib::Strings::String>::Iterator i = propertyNames.begin(); i != propertyNames.end(); ++i, ++position)
	{
		if (position == attributePosition)
		{
			currentProperty = *i;
			return true;
		}
	}
	return false;
}



bool PropertiesTreeIterator::moveToAttribute(const BaseLib::Strings::String& attributeName)
{
	if (constObject->getClass()->hasProperty(attributeName) == true)
	{
		currentProperty = attributeName;
		return true;
	}
	else
	{
		return false;
	}
}



bool PropertiesTreeIterator::hasParent() const
{
	return isAttribute();
}



bool PropertiesTreeIterator::moveToParent()
{
	if (isAttribute() == true)
	{
		currentProperty.setLength(0);
		return true;
	}
	else
	{
		return false;
	}
}



int PropertiesTreeIterator::getChildNodeCount() const
{
	return 0;
}



int PropertiesTreeIterator::getChildNodePosition() const
{
	return -1;
}



bool PropertiesTreeIterator::moveToChildNode(int childPosition)
{
	return false;
}








} // namespace Reflection
} // namespace BaseLib
