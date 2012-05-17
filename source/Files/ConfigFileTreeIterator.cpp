/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/ConfigFileTreeIterator.h"
#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/Streams/NullInputStream.h"
#include "BaseLib/Streams/NullOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Streams;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Trees;
using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(ConfigFileTreeIterator, AbstractTreeIterator)
{
}




ConfigFileTreeIterator::ConfigFileTreeIterator(ConfigFile* forConfigFile, const NumberFormat* useNumberFormat)
	: configFile(forConfigFile)
	, constConfigFile(forConfigFile)
	, currentKey()
	, stateStack()
	, numberFormat(useNumberFormat)
{
}



ConfigFileTreeIterator::ConfigFileTreeIterator(const ConfigFile* forConstObject, const NumberFormat* useNumberFormat)
	: configFile(NULL)
	, constConfigFile(forConstObject)
	, currentKey()
	, stateStack()
	, numberFormat(useNumberFormat)
{
}



AbstractTreeIterator* ConfigFileTreeIterator::clone() const
{
	return (isConfigFileConst() == true) ?
		new ConfigFileTreeIterator(constConfigFile) :
		new ConfigFileTreeIterator(configFile);
}



bool ConfigFileTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = BaseLib::Trees::TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const ConfigFileTreeIterator*>(rightImplementation)->configFile == configFile &&
		static_cast<const ConfigFileTreeIterator*>(rightImplementation)->constConfigFile == constConfigFile &&
		static_cast<const ConfigFileTreeIterator*>(rightImplementation)->currentKey == currentKey;
}



bool ConfigFileTreeIterator::isAttribute() const
{
	return currentKey.isEmpty() == false;
}



String ConfigFileTreeIterator::getName() const
{
	return isAttribute() == true ? currentKey : "ConfigFile";
}



String ConfigFileTreeIterator::getNamespace() const
{
	return Empty();
}



bool ConfigFileTreeIterator::hasMetaTag(const String& metaTag) const
{
	return false;
}



bool ConfigFileTreeIterator::isReadable() const
{
	return isAttribute();
}



bool ConfigFileTreeIterator::isWriteable() const
{
	return isAttribute() == true && configFile != NULL;
}



InputStream* ConfigFileTreeIterator::createInputStream() const
{
	return NULL;
}



OutputStream* ConfigFileTreeIterator::createOutputStream() const
{
	return NULL;
}



String ConfigFileTreeIterator::getValue() const
{	
	return isReadable() == true ? constConfigFile->getEntry(currentKey) : "";
}



void ConfigFileTreeIterator::setValue(const String& newValue) const
{
	if (isWriteable() == true)
	{
		configFile->setEntry(currentKey, newValue);
	}
}



String ConfigFileTreeIterator::getValueOfAttribute(const String& attributeName) const
{
	return constConfigFile->hasKey(attributeName) == true ? constConfigFile->getEntry(attributeName) : "";
}



void ConfigFileTreeIterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
	if (configFile != NULL && configFile->hasKey(attributeName) == true)
	{
		configFile->setEntry(attributeName, newValue);
	}
}



String ConfigFileTreeIterator::getType() const
{
	return isAttribute() == true ? "string" : "";
}



bool ConfigFileTreeIterator::isDefaultValue() const
{
	return false;
}



void ConfigFileTreeIterator::setDefaultValue() const
{
}



const Enumeration<String>& ConfigFileTreeIterator::getValueRange() const
{
	static const EmptyEnumeration<String> emptyStringEnumeration;
	return emptyStringEnumeration;
}



void ConfigFileTreeIterator::push()
{
	stateStack.push(currentKey);
}



void ConfigFileTreeIterator::pop(bool restorePosition, bool restoreStack)
{
	if (restorePosition == true)
	{
		currentKey = stateStack.top();
	}
	if (restoreStack == true)
	{
		stateStack.pop();
	}
}



int ConfigFileTreeIterator::getAttributeCount() const
{
	return constConfigFile->getEntryCount();
}



int ConfigFileTreeIterator::getAttributePosition() const
{
	if (isAttribute() == true)
	{
		int position = 0;
		const Enumeration<String>& keys = constConfigFile->getKeys();
		for (Enumeration<String>::Iterator i = keys.begin(); i != keys.end(); ++i, ++position)
		{
			if (currentKey == *i)
			{
				return position;
			}
		}
		BL_ASSERT_NEVER_REACHED
	}

	return -1;
}



bool ConfigFileTreeIterator::moveToAttribute(int attributePosition)
{
	int position = 0;
	const Enumeration<String>& keys = constConfigFile->getKeys();
	for (Enumeration<String>::Iterator i = keys.begin(); i != keys.end(); ++i, ++position)
	{
		if (position == attributePosition)
		{
			currentKey = *i;
			return true;
		}
	}
	return false;
}



bool ConfigFileTreeIterator::moveToAttribute(const String& attributeName)
{
	if (constConfigFile->hasKey(attributeName) == true)
	{
		currentKey = attributeName;
		return true;
	}
	else
	{
		return false;
	}
}



bool ConfigFileTreeIterator::hasParent() const
{
	return isAttribute();
}



bool ConfigFileTreeIterator::moveToParent()
{
	if (isAttribute() == true)
	{
		currentKey.setLength(0);
		return true;
	}
	else
	{
		return false;
	}
}



int ConfigFileTreeIterator::getChildNodeCount() const
{
	return 0;
}



int ConfigFileTreeIterator::getChildNodePosition() const
{
	return -1;
}



bool ConfigFileTreeIterator::moveToChildNode(int childPosition)
{
	return false;
}




} // namespace Files
} // namespace BaseLib
