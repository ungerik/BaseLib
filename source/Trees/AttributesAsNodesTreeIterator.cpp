/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/AttributesAsNodesTreeIterator.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_CLASS(AttributesAsNodesTreeIterator, AbstractTreeIterator)
{
}



AttributesAsNodesTreeIterator::AttributesAsNodesTreeIterator(const TreeIterator& newSource)
	: source(newSource)
{
}



AbstractTreeIterator* AttributesAsNodesTreeIterator::clone() const
{
	return new AttributesAsNodesTreeIterator(source);
}



bool AttributesAsNodesTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const AttributesAsNodesTreeIterator* rightAttributesAsNodesTreeIterator = AttributesAsNodesTreeIterator::castFrom(&right);
	if (rightAttributesAsNodesTreeIterator != NULL)
	{
		return source == rightAttributesAsNodesTreeIterator->getSource();
	}
	else
	{
		return false;
	}
}



bool AttributesAsNodesTreeIterator::isAttribute() const
{
	return false;
}



String AttributesAsNodesTreeIterator::getName() const
{
	if (source.isAttribute() == true)
	{
		return source.getName() + '=' + source.getValue();
	}
	else
	{
		return source.getName();
	}
}



String AttributesAsNodesTreeIterator::getNamespace() const
{
	return source.getNamespace();
}



bool AttributesAsNodesTreeIterator::hasMetaTag(const String& metaTag) const
{
	return source.hasMetaTag(metaTag);
}



bool AttributesAsNodesTreeIterator::isReadable() const
{
	return source.isReadable();
}



bool AttributesAsNodesTreeIterator::isWriteable() const
{
	return source.isWriteable();
}



InputStream* AttributesAsNodesTreeIterator::createInputStream() const
{
	return source.createInputStream();
}



OutputStream* AttributesAsNodesTreeIterator::createOutputStream() const
{
	return source.createOutputStream();
}



String AttributesAsNodesTreeIterator::getValue() const
{
	return source.getValue();
}



void AttributesAsNodesTreeIterator::setValue(const String& newValue) const
{
	return source.setValue(newValue);
}



String AttributesAsNodesTreeIterator::getType() const
{
	return source.getType();
}



bool AttributesAsNodesTreeIterator::isDefaultValue() const
{
	return source.isDefaultValue();
}



void AttributesAsNodesTreeIterator::setDefaultValue() const
{
	source.setDefaultValue();
}



const Enumeration<String>& AttributesAsNodesTreeIterator::getValueRange() const
{
	return source.getValueRange();
}



void AttributesAsNodesTreeIterator::push()
{
	source.push();
}



void AttributesAsNodesTreeIterator::pop(bool restorePosition, bool restoreStack)
{
	source.pop(restorePosition, restoreStack);
}



bool AttributesAsNodesTreeIterator::moveToNextNode()
{
	if (source.moveToNextAttribute() == true)
	{
		return true;
	}
	else
	{
		return source.moveToNextNode();
	}
}



bool AttributesAsNodesTreeIterator::moveToPreviousNode()
{
	if (source.moveToPreviousAttribute() == true)
	{
		return true;
	}
	else
	{
		return source.moveToPreviousNode();
	}
}



bool AttributesAsNodesTreeIterator::hasAttribute(const String& attributeName) const
{
	return false;
}



int AttributesAsNodesTreeIterator::getAttributeCount() const
{
	return 0;
}



int AttributesAsNodesTreeIterator::getAttributePosition() const
{
	return -1;
}



bool AttributesAsNodesTreeIterator::moveToAttribute(int attributePosition)
{
	return false;
}



bool AttributesAsNodesTreeIterator::moveToAttribute(const String& attributeName)
{
	return false;
}



bool AttributesAsNodesTreeIterator::moveToNextAttribute()
{
	return false;
}



bool AttributesAsNodesTreeIterator::moveToPreviousAttribute()
{
	return false;
}



void AttributesAsNodesTreeIterator::enumAttributeNames(const Enumerator<String>& enumerator) const
{
}



bool AttributesAsNodesTreeIterator::hasParent() const
{
	return source.hasParent();
}



int AttributesAsNodesTreeIterator::getParentCount() const
{
	return source.getParentCount();
}



bool AttributesAsNodesTreeIterator::moveToParent()
{
	return source.moveToParent();
}



bool AttributesAsNodesTreeIterator::canHaveChildNodes() const
{
	return source.canHaveChildNodes();
}



bool AttributesAsNodesTreeIterator::hasChildNodes() const
{
	return source.isAttribute() == false && (source.hasChildNodes() == true || source.getAttributeCount() > 0);
}



bool AttributesAsNodesTreeIterator::hasChildNode(const String& childName) const
{
	return source.hasChildNode(childName) || source.hasAttribute(childName);
}



int AttributesAsNodesTreeIterator::getChildNodeCount() const
{
	return source.isAttribute() == true ? 0 : source.getChildNodeCount() + source.getAttributeCount();
}



int AttributesAsNodesTreeIterator::getChildNodePosition() const
{
	if (source.isAttribute() == true)
	{
		return source.getAttributePosition();
	}
	else
	{
		TreeIterator& unconstSource = const_cast<TreeIterator&>(source);
		unconstSource.push();
		unconstSource.moveToParent();
		int parentAttributeCount = unconstSource.getAttributeCount();
		unconstSource.pop();

		return parentAttributeCount + source.getChildNodePosition();
	}
}



bool AttributesAsNodesTreeIterator::moveToChildNode(int childPosition)
{
	if (childPosition < source.getAttributeCount())
	{
		return source.moveToAttribute(childPosition);
	}
	else
	{
		return source.moveToChildNode(childPosition - source.getAttributeCount());
	}
}



bool AttributesAsNodesTreeIterator::moveToChildNode(const String& childName)
{
	String name = childName.subString(0, childName.findFirst('='));
	bool foundAttribute = source.moveToAttribute(name);

	if (foundAttribute == true)
	{
		return true;
	}
	else
	{
		return source.moveToChildNode(childName);
	}
}



void AttributesAsNodesTreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
	if (source.isAttribute() == false)
	{
		TreeIterator& unconstSource = const_cast<TreeIterator&>(source);
		unconstSource.push();
		while (unconstSource.moveToNextAttribute() == true)
		{
			enumerator.enumerate(source.getName() + '=' + source.getValue());
		}
		unconstSource.pop();
	}
	source.enumChildNodeNames(enumerator);
}



} // namespace Trees
} // namespace BaseLib
