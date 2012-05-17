/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Streams/NullInputStream.h"
#include "BaseLib/Streams/NullOutputStream.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Streams;



BL_DEFINE_REFLECTION_CLASS(TreeNode::Iterator, AbstractTreeIterator)
{
}



TreeNode::Iterator::Iterator(TreeNode* forTreeNode, const String& attribute, const NumberFormat* useNumberFormat)
	: currentTreeNode(forTreeNode)
	, currentConstTreeNode(forTreeNode)
	, currentAttribute(attribute)
	, positionStack()
	, numberFormat(useNumberFormat)
{
}



TreeNode::Iterator::Iterator(const TreeNode* forConstTreeNode, const String& attribute, const NumberFormat* useNumberFormat)
	: currentTreeNode(NULL)
	, currentConstTreeNode(forConstTreeNode)
	, currentAttribute(attribute)
	, positionStack()
	, numberFormat(useNumberFormat)
{
}



void TreeNode::Iterator::setCurrentTreeNode(TreeNode* newCurrentTreeNode)
{
	currentTreeNode = newCurrentTreeNode;
	currentConstTreeNode = newCurrentTreeNode;
	if (currentConstTreeNode != NULL && currentConstTreeNode->hasAttribute(currentAttribute) == false)
	{
		currentAttribute.setLength(0);
	}
}



void TreeNode::Iterator::setCurrentTreeNode(const TreeNode* newCurrentConstTreeNode)
{
	currentTreeNode = NULL;
	currentConstTreeNode = newCurrentConstTreeNode;
	if (currentConstTreeNode != NULL && currentConstTreeNode->hasAttribute(currentAttribute) == false)
	{
		currentAttribute.setLength(0);
	}
}



AbstractTreeIterator* TreeNode::Iterator::clone() const
{
	return isTreeNodeConst() == true ?
		new Iterator(currentConstTreeNode, currentAttribute, numberFormat) :
		new Iterator(currentTreeNode, currentAttribute, numberFormat);
}



void TreeNode::Iterator::setCurrentAttribute(const String& newCurrentAttribute)
{
	if (currentConstTreeNode == NULL || (currentConstTreeNode != NULL && currentConstTreeNode->hasAttribute(newCurrentAttribute) == true))
	{
		currentAttribute = newCurrentAttribute;
	}
}




bool TreeNode::Iterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const Iterator*>(rightImplementation)->currentTreeNode == currentTreeNode &&
		static_cast<const Iterator*>(rightImplementation)->currentConstTreeNode == currentConstTreeNode &&
		static_cast<const Iterator*>(rightImplementation)->currentAttribute == currentAttribute;
}



bool TreeNode::Iterator::isAttribute() const
{
	return currentAttribute.isEmpty() == false;
}



String TreeNode::Iterator::getName() const
{
	if (currentConstTreeNode != NULL)
	{
		return (isAttribute() == true) ? currentAttribute : currentConstTreeNode->getName();
	}
	else
	{
		return Empty();
	}
}



String TreeNode::Iterator::getNamespace() const
{
	return Empty();
}



bool TreeNode::Iterator::hasMetaTag(const String& metaTag) const
{
	if (currentConstTreeNode != NULL)
	{
		if  (isAttribute() == true)
		{
			return currentConstTreeNode->hasAttributeMetaTag(currentAttribute, metaTag);
		}
		else
		{
			return currentConstTreeNode->hasMetaTag(metaTag);
		}
	}
	else
	{
		return false;
	}
}



bool TreeNode::Iterator::isReadable() const
{
	return isAttribute() == true && currentConstTreeNode != NULL && currentConstTreeNode->isAttributeReadable(currentAttribute);
}



bool TreeNode::Iterator::isWriteable() const
{
	return isAttribute() == true && currentTreeNode != NULL && currentTreeNode->isAttributeWriteable(currentAttribute);
}



InputStream* TreeNode::Iterator::createInputStream() const
{
	if (isReadable() == true)
	{
		return NULL; ///
	}
	else
	{
		return NULL;
	}
}



OutputStream* TreeNode::Iterator::createOutputStream() const
{
	if (isWriteable() == true)
	{
		return NULL; ///
	}
	else
	{
		return NULL;
	}
}



String TreeNode::Iterator::getValue() const
{
	return isReadable() == true ? currentConstTreeNode->getAttribute(currentAttribute, numberFormat) : String();
}



void TreeNode::Iterator::setValue(const String& newValue) const
{
	if (isWriteable() == true)
	{
		currentTreeNode->setAttribute(currentAttribute, newValue, numberFormat);
	}
}



String TreeNode::Iterator::getValueOfAttribute(const String& attributeName) const
{
	const bool readable = 
		currentConstTreeNode != NULL && 
		currentConstTreeNode->hasAttribute(attributeName) &&
		currentConstTreeNode->isAttributeReadable(attributeName);

	return readable == true ? currentConstTreeNode->getAttribute(attributeName, numberFormat) : String();
}



void TreeNode::Iterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
	if (currentTreeNode != NULL && 
		currentTreeNode->hasAttribute(attributeName) &&
		currentTreeNode->isAttributeWriteable(attributeName))
	{
		currentTreeNode->setAttribute(attributeName, newValue, numberFormat);
	}
}



String TreeNode::Iterator::getType() const
{
	if (currentConstTreeNode != NULL)
	{
		return (isAttribute() == true) ? currentConstTreeNode->getAttributeType(currentAttribute) : currentConstTreeNode->getName();
	}
	else
	{
		return Empty();
	}
}



bool TreeNode::Iterator::isDefaultValue() const
{
	if (isAttribute() == true && currentConstTreeNode != NULL)
	{
		return currentConstTreeNode->isAttributeDefault(currentAttribute);
	}
	else 
	{
		return false;
	}
}



void TreeNode::Iterator::setDefaultValue() const
{
	if (isAttribute() == true && currentTreeNode != NULL)
	{
		currentTreeNode->setAttributeToDefault(currentAttribute);
	}
}



const Enumeration<String>& TreeNode::Iterator::getValueRange() const
{
	if (isAttribute() == true && currentConstTreeNode != NULL)
	{
		return currentConstTreeNode->getAttributeValueRange(currentAttribute);
	}
	else 
	{
		return AbstractTreeIterator::getValueRange();
	}
}



void TreeNode::Iterator::push()
{
	positionStack.push(State(currentTreeNode, currentConstTreeNode, currentAttribute));
}



void TreeNode::Iterator::pop(bool restorePosition, bool restoreStack)
{
	if (restorePosition == true)
	{
		State& stackState = positionStack.top();
		currentTreeNode = stackState.treeNode;
		currentConstTreeNode = stackState.constTreeNode;
		currentAttribute = stackState.attribute;
	}
	if (restoreStack == true)
	{
		positionStack.pop();
	}
}



bool TreeNode::Iterator::hasAttribute(const String& attributeName) const
{
	return (currentConstTreeNode != NULL) ? currentConstTreeNode->hasAttribute(attributeName) : false;
}



int TreeNode::Iterator::getAttributeCount() const
{
	return (currentConstTreeNode != NULL) ? currentConstTreeNode->getAttributeNames().getCount() : 0;
}



int TreeNode::Iterator::getAttributePosition() const
{ 
	if (isAttribute() == true && currentConstTreeNode != NULL)
	{
		int result = 0;
		const Enumeration<String>& attributeNames = currentConstTreeNode->getAttributeNames();
		for (Enumeration<String>::Iterator i = attributeNames.begin(); i != attributeNames.end(); ++i, ++result)
		{
			if (*i == currentAttribute)
			{
				return result;
			}
		}
	}

	return -1;
}



bool TreeNode::Iterator::moveToAttribute(int attributePosition)
{
	if (attributePosition >= 0 && currentConstTreeNode != NULL)
	{
		int pos = 0;
		const Enumeration<String>& attributeNames = currentConstTreeNode->getAttributeNames();
		for (Enumeration<String>::Iterator i = attributeNames.begin(); i != attributeNames.end() && pos <= attributePosition; ++i, ++pos)
		{
			if (pos == attributePosition)
			{
				currentAttribute = *i;
				return true;
			}
		}
	}

	return false;
}



bool TreeNode::Iterator::moveToAttribute(const String& attributeName)
{
	if (currentConstTreeNode != NULL && currentConstTreeNode->hasAttribute(attributeName) == true)
	{
		currentAttribute = attributeName;
		return true;
	}
	else
	{
		return false;
	}
}



void TreeNode::Iterator::enumAttributeNames(const Enumerator<String>& enumerator) const
{
	if (currentConstTreeNode != NULL)
	{
		currentConstTreeNode->getAttributeNames().enumerate(enumerator);
	}
}



bool TreeNode::Iterator::hasParent() const
{
	return (currentConstTreeNode != NULL) ? (isAttribute() == true || currentConstTreeNode->getParent() != NULL) : false;
}



bool TreeNode::Iterator::moveToParent()
{
	if (isAttribute() == true)
	{
		currentAttribute = Empty();
		return true;
	}
	else if (currentConstTreeNode != NULL)
	{
		const TreeNode* parentTreeNode = currentConstTreeNode->getParent();
		if (parentTreeNode != NULL)
		{
			if (currentTreeNode != NULL) currentTreeNode = const_cast<TreeNode*>(parentTreeNode);		
			currentConstTreeNode = parentTreeNode;
			currentAttribute = Empty();
			return true;
		}
	}
	return false;
}



void TreeNode::Iterator::moveToRootNode()
{
	if (currentConstTreeNode != NULL)
	{
		currentConstTreeNode = &currentConstTreeNode->getRootNode();
		if (currentTreeNode != NULL) currentTreeNode = const_cast<TreeNode*>(currentConstTreeNode);		
		currentAttribute = Empty();
	}
}



int TreeNode::Iterator::getChildNodeCount() const
{
	return (currentConstTreeNode != NULL) ? currentConstTreeNode->getChildCount() : 0;
}



int TreeNode::Iterator::getChildNodePosition() const
{
	return (currentConstTreeNode != NULL) ? currentConstTreeNode->getChildIndexAtParent() : -1;
}



bool TreeNode::Iterator::moveToChildNode(int childPosition)
{
	if (currentConstTreeNode != NULL && childPosition >= 0 && childPosition < currentConstTreeNode->getChildCount())
	{
		currentConstTreeNode = currentConstTreeNode->getChild(childPosition);
		if (currentTreeNode != NULL) currentTreeNode = const_cast<TreeNode*>(currentConstTreeNode);		
		currentAttribute = Empty();
		return true;
	}
	else
	{
		return false;
	}
}




} // namespace Trees
} // namespace BaseLib
