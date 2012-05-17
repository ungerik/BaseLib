/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::Strings;



Object::~Object()
{
}



void Object::onBeforePropertiesTransaction()
{
}



void Object::onAfterPropertiesTransaction()
{
}



bool Object::hasMetaTag(const String& metaTag) const
{
	return getClass()->hasMetaTag(metaTag);
}



bool Object::hasPropertyMetaTag(const String& propertyName, const String& metaTag) const
{
	return getClass()->property(propertyName)->hasMetaTag(metaTag);
}



bool Object::isPropertyDefault(const String& propertyName) const
{
	return getClass()->property(propertyName)->isDefault(this);
}



void Object::setPropertyToDefault(const String& propertyName)
{
	getClass()->property(propertyName)->setToDefault(this);
}



const Enumeration<String>& Object::getPropertyValueRange(const String& propertyName) const
{
	return getClass()->property(propertyName)->getValueRange();
}



} // namespace Reflection
} // namespace BaseLib
