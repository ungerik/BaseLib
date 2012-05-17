/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/CompoundTree.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Streams;
using namespace BaseLib::Containers;




BL_DEFINE_REFLECTION_CLASS(CompoundTree::Iterator, AbstractTreeIterator)
{
}



CompoundTree::Iterator::Iterator(CompoundTree* forCompoundTree)
	: AbstractTreeIterator()
	, compoundTree(forCompoundTree)
	, baseTreeNode(forCompoundTree->rootNode)
	, subTree(NULL)
	, subTreeIterator(NULL)
	, positionStack()
{
}



AbstractTreeIterator* CompoundTree::Iterator::clone() const
{
	return new Iterator(compoundTree);
}



bool CompoundTree::Iterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const Iterator*>(rightImplementation)->compoundTree == compoundTree &&
		static_cast<const Iterator*>(rightImplementation)->baseTreeNode == baseTreeNode &&
		static_cast<const Iterator*>(rightImplementation)->subTree == subTree;
}



bool CompoundTree::Iterator::isAttribute() const
{
	return isSubTree() == true ? subTreeIterator.isAttribute() : false;
}



bool CompoundTree::Iterator::hasMetaTag(const String& metaTag) const
{
	return isSubTree() == true ? subTreeIterator.hasMetaTag(metaTag) : false;
}



String CompoundTree::Iterator::getName() const
{
	if (isSubTree() == true)
	{
		return subTreeIterator.hasParent() == true ? subTreeIterator.getName() : subTree->rootNodeName;
	}
	else
	{
		return baseTreeNode->getName();
	}
}



String CompoundTree::Iterator::getNamespace() const
{
	return isSubTree() == true ? subTreeIterator.getNamespace() : "";//baseTreeNode->getNamespace();
}



bool CompoundTree::Iterator::isReadable() const
{
	return isSubTree() == true ? subTreeIterator.isReadable() : false;
}



bool CompoundTree::Iterator::isWriteable() const
{
	return isSubTree() == true ? subTreeIterator.isWriteable() : false;
}



InputStream* CompoundTree::Iterator::createInputStream() const
{
	if (isSubTree() == true)
	{
		return subTreeIterator.createInputStream();
	}
	else
	{
		return NULL;
	}
}



OutputStream* CompoundTree::Iterator::createOutputStream() const
{
	if (isSubTree() == true)
	{
		return subTreeIterator.createOutputStream();
	}
	else
	{
		return NULL;
	}
}



String CompoundTree::Iterator::getValue() const
{
	return (isSubTree() == true) ? subTreeIterator.getValue() : "";
}



void CompoundTree::Iterator::setValue(const String& newValue) const
{
	if (isSubTree() == true)
	{
		subTreeIterator.setValue(newValue);
	}
}



String CompoundTree::Iterator::getValueOfAttribute(int attributePosition) const
{
	return (isSubTree() == true) ? subTreeIterator.getValueOfAttribute(attributePosition) : "";
}



void CompoundTree::Iterator::setValueOfAttribute(int attributePosition, const String& newValue) const
{
	if (isSubTree() == true)
	{
		subTreeIterator.setValueOfAttribute(attributePosition, newValue);
	}
}



String CompoundTree::Iterator::getValueOfAttribute(const String& attributeName) const
{
	return (isSubTree() == true) ? subTreeIterator.getValueOfAttribute(attributeName) : "";
}



void CompoundTree::Iterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
	if (isSubTree() == true)
	{
		subTreeIterator.setValueOfAttribute(attributeName, newValue);
	}
}



String CompoundTree::Iterator::getType() const
{
	return isSubTree() == true ? subTreeIterator.getType() : "";
}



bool CompoundTree::Iterator::isDefaultValue() const
{
	return isSubTree() == true ? subTreeIterator.isDefaultValue() : false;
}



void CompoundTree::Iterator::setDefaultValue() const
{
	if (isSubTree() == true)
	{
		subTreeIterator.setDefaultValue();
	}
}



const Enumeration<String>& CompoundTree::Iterator::getValueRange() const
{
	if (isSubTree() == true)
	{
		return subTreeIterator.getValueRange();
	}
	else
	{
		const EmptyEnumeration<String> emptyStringEnumeration;
		return emptyStringEnumeration;
	}
}



void CompoundTree::Iterator::push()
{
	positionStack.push(State(baseTreeNode, subTree, subTreeIterator));
}



void CompoundTree::Iterator::pop(bool restorePosition, bool restoreStack)
{
	if (restorePosition == true)
	{
		const State& state = positionStack.top();
		baseTreeNode = state.baseTreeNode;
		subTree = state.subTree;
		subTreeIterator = state.subTreeIterator; // OPTIMIZE -> copy by value!
	}
	if (restoreStack == true)
	{
		positionStack.pop();
	}
}



int CompoundTree::Iterator::getAttributeCount() const
{
	return isSubTree() == true ? subTreeIterator.getAttributeCount() : 0;
}



int CompoundTree::Iterator::getAttributePosition() const
{
	return isSubTree() == true ? subTreeIterator.getAttributePosition() : -1;
}



bool CompoundTree::Iterator::moveToAttribute(int attributePosition)
{
	return isSubTree() == true ? subTreeIterator.moveToAttribute(attributePosition) : false;
}



bool CompoundTree::Iterator::hasParent() const
{
	return isSubTree() == true ? true : baseTreeNode->getParent() != NULL;
}



bool CompoundTree::Iterator::moveToParent()
{
	if (isSubTree() == true)
	{
		if (subTreeIterator.hasParent() == true)
		{
			return subTreeIterator.moveToParent();
		}
		else
		{
			// baseTreeNode is already the parent
			subTree = NULL;
			subTreeIterator.setImplementation(NULL);
			return true;
		}
	}
	else
	{
		TreeNode* parentNode = baseTreeNode->getParent();
		if (parentNode != NULL)
		{
			baseTreeNode = parentNode;
			return true;
		}
		else
		{
			return false;
		}
	}
}



int CompoundTree::Iterator::getChildNodeCount() const
{
	if (isSubTree() == true)
	{
		return subTreeIterator.getChildNodeCount();
	}
	else
	{
		int childNodeCount = baseTreeNode->getChildCount();

		typedef CompoundTree::SubTrees::ValueEnumeration SubTreesEnumeration;
		SubTreesEnumeration subTreesEnumeration(&compoundTree->subTrees);
		foreach (SubTreesEnumeration::Iterator, i, subTreesEnumeration)
		{
			if ((*i)->parentNode == baseTreeNode)
			{
				++childNodeCount;
			}
		}

		return childNodeCount;
	}
}



int CompoundTree::Iterator::getChildNodePosition() const
{
	if (isSubTree() == true)
	{
		if (subTreeIterator.hasParent() == true)
		{
			return subTreeIterator.getChildNodePosition();
		}
		else
		{
			int childNodePosition = baseTreeNode->getChildCount();

			typedef CompoundTree::SubTrees::ValueEnumeration SubTreesEnumeration;
			SubTreesEnumeration subTreesEnumeration(&compoundTree->subTrees);
			foreach (SubTreesEnumeration::Iterator, i, subTreesEnumeration)
			{
				if ((*i)->parentNode == baseTreeNode)
				{
					if (*i == subTree)
					{
						return childNodePosition;
					}
					++childNodePosition;
				}
			}

			return childNodePosition;
		}
	}
	else
	{
		return baseTreeNode->getChildIndexAtParent();
	}
}



bool CompoundTree::Iterator::moveToChildNode(int childPosition)
{
	if (childPosition < 0)
	{
		return false;
	}

	if (isSubTree() == true)
	{
		return subTreeIterator.moveToChildNode(childPosition);
	}
	else
	{
		int childCounter = baseTreeNode->getChildCount();
		if (childPosition < childCounter)
		{
			baseTreeNode = baseTreeNode->getChild(childPosition);
			return true;
		}
		else
		{
			typedef CompoundTree::SubTrees::ValueEnumeration SubTreesEnumeration;
			SubTreesEnumeration subTreesEnumeration(&compoundTree->subTrees);
			foreach (SubTreesEnumeration::Iterator, i, subTreesEnumeration)
			{
				if ((*i)->parentNode == baseTreeNode)
				{
					if (childCounter == childPosition)
					{
						subTree = *i;
						subTreeIterator = subTree->tree->getTreeIteratorForRootNode();
						return true;
					}
					++childCounter;
				}
			}

			return false;
		}
	}
}






} // namespace Trees
} // namespace BaseLib
