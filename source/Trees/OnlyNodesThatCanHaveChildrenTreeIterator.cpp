/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/OnlyNodesThatCanHaveChildrenTreeIterator.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_CLASS(OnlyNodesThatCanHaveChildrenTreeIterator, AbstractTreeIterator)
{
}



OnlyNodesThatCanHaveChildrenTreeIterator::OnlyNodesThatCanHaveChildrenTreeIterator(const TreeIterator& newSource)
	: source(newSource)
{
}



AbstractTreeIterator* OnlyNodesThatCanHaveChildrenTreeIterator::clone() const
{
	return new OnlyNodesThatCanHaveChildrenTreeIterator(source);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const OnlyNodesThatCanHaveChildrenTreeIterator* rightOnlyNodesThatCanHaveChildrenTreeIterator = OnlyNodesThatCanHaveChildrenTreeIterator::castFrom(&right);
	if (rightOnlyNodesThatCanHaveChildrenTreeIterator != NULL)
	{
		return source == rightOnlyNodesThatCanHaveChildrenTreeIterator->getSource();
	}
	else
	{
		return false;
	}
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::isAttribute() const
{
	return source.isAttribute();
}



String OnlyNodesThatCanHaveChildrenTreeIterator::getName() const
{
	return source.getName();
}



String OnlyNodesThatCanHaveChildrenTreeIterator::getNamespace() const
{
	return source.getNamespace();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::hasMetaTag(const String& metaTag) const
{
	return source.hasMetaTag(metaTag);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::isReadable() const
{
	return source.isReadable();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::isWriteable() const
{
	return source.isWriteable();
}



InputStream* OnlyNodesThatCanHaveChildrenTreeIterator::createInputStream() const
{
	return source.createInputStream();
}



OutputStream* OnlyNodesThatCanHaveChildrenTreeIterator::createOutputStream() const
{
	return source.createOutputStream();
}



String OnlyNodesThatCanHaveChildrenTreeIterator::getValue() const
{
	return source.getValue();
}



void OnlyNodesThatCanHaveChildrenTreeIterator::setValue(const String& newValue) const
{
	return source.setValue(newValue);
}



String OnlyNodesThatCanHaveChildrenTreeIterator::getType() const
{
	return source.getType();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::isDefaultValue() const
{
	return source.isDefaultValue();
}



void OnlyNodesThatCanHaveChildrenTreeIterator::setDefaultValue() const
{
	source.setDefaultValue();
}



const Enumeration<String>& OnlyNodesThatCanHaveChildrenTreeIterator::getValueRange() const
{
	return source.getValueRange();
}



void OnlyNodesThatCanHaveChildrenTreeIterator::push()
{
	source.push();
}



void OnlyNodesThatCanHaveChildrenTreeIterator::pop(bool restorePosition, bool restoreStack)
{
	source.pop(restorePosition, restoreStack);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToNextNode()
{
	return false; // TODO
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToPreviousNode()
{
	return false; // TODO
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::hasAttribute(const String& attributeName) const
{
	return source.hasAttribute(attributeName);
}



int OnlyNodesThatCanHaveChildrenTreeIterator::getAttributeCount() const
{
	return source.getAttributeCount();
}



int OnlyNodesThatCanHaveChildrenTreeIterator::getAttributePosition() const
{
	return source.getAttributePosition();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToAttribute(int attributePosition)
{
	return source.moveToAttribute(attributePosition);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToAttribute(const String& attributeName)
{
	return source.moveToAttribute(attributeName);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToNextAttribute()
{
	return source.moveToNextAttribute();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToPreviousAttribute()
{
	return source.moveToPreviousAttribute();
}



void OnlyNodesThatCanHaveChildrenTreeIterator::enumAttributeNames(const Enumerator<String>& enumerator) const
{
	source.enumAttributeNames(enumerator);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::hasParent() const
{
	return source.hasParent();
}



int OnlyNodesThatCanHaveChildrenTreeIterator::getParentCount() const
{
	return source.getParentCount();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToParent()
{
	return source.moveToParent();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::canHaveChildNodes() const
{
	return source.canHaveChildNodes();
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::hasChildNodes() const
{
	return !(source.getChildNodeCount() == 0 || getChildNodeCount() == 0);
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::hasChildNode(const String& childName) const
{
	bool result = false;
	TreeIterator& unconstSource = const_cast<TreeIterator&>(source);
	unconstSource.push();
	if (unconstSource.moveToChildNode(childName) == true)
	{
		bool result = canHaveChildNodes();
	}
	unconstSource.pop();
	return result;
}



int OnlyNodesThatCanHaveChildrenTreeIterator::getChildNodeCount() const
{
	int result = 0;

	TreeIterator& unconstSource = const_cast<TreeIterator&>(source);
	unconstSource.push();
	if (unconstSource.moveToChildNode(0) == true)
	{
		int sourceChildCount = source.getChildNodeCount();
		for (int i = 0; i < sourceChildCount; ++i)
		{
			if (canHaveChildNodes() == true)
			{
				++result;
			}
			unconstSource.moveToNextNodeSibling();
		}
	}
	unconstSource.pop();
	return result;
}



int OnlyNodesThatCanHaveChildrenTreeIterator::getChildNodePosition() const
{
	if (source.isAttribute() == true)
	{
		return source.getAttributePosition();
	}
	else
	{
		int result = 0;
		TreeIterator& unconstSource = const_cast<TreeIterator&>(source);
		unconstSource.push();
		if (unconstSource.moveToChildNode(0) == true)
		{
			++result;
			while (unconstSource.moveToNextNodeSibling() == true)
			{
				++result;
			}
		}

		unconstSource.pop();
		return result;
	}

}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToChildNode(int childPosition)
{
	return false; // TODO
}



bool OnlyNodesThatCanHaveChildrenTreeIterator::moveToChildNode(const String& childName)
{
	return false; // TODO
}



void OnlyNodesThatCanHaveChildrenTreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
}



} // namespace Trees
} // namespace BaseLib
