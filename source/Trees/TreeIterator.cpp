/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



AbstractTreeIterator* TreeIterator::getImplementation(AbstractTreeIterator& abstractTreeIterator)
{
	return (abstractTreeIterator.getClass() == CLASS) ? static_cast<TreeIterator&>(abstractTreeIterator).getImplementation() : &abstractTreeIterator;
}



const AbstractTreeIterator* TreeIterator::getImplementation(const AbstractTreeIterator& abstractTreeIterator)
{
	return (abstractTreeIterator.getClass() == CLASS) ? static_cast<const TreeIterator&>(abstractTreeIterator).getImplementation() : &abstractTreeIterator;
}



BL_DEFINE_REFLECTION_CLASS(TreeIterator, AbstractTreeIterator)
{
	registerProperty("implementation", &TreeIterator::hasImplementation);
}



TreeIterator::TreeIterator(AbstractTreeIterator* newImplementation)
	: implementation(newImplementation)
{
}



AbstractTreeIterator* TreeIterator::clone() const
{
	return new TreeIterator(implementation != NULL ? implementation->clone() : NULL);
}



bool TreeIterator::operator==(const AbstractTreeIterator& right) const
{
	return implementation != NULL ? implementation->operator==(right) : false;
}



bool TreeIterator::isAttribute() const
{
	return implementation != NULL ? implementation->isAttribute() : false;
}



String TreeIterator::getName() const
{
	return implementation != NULL ? implementation->getName() : "";
}



String TreeIterator::getNamespace() const
{
	return implementation != NULL ? implementation->getNamespace() : "";
}



bool TreeIterator::hasMetaTag(const String& metaTag) const
{
	return implementation != NULL ? implementation->hasMetaTag(metaTag) : false;
}



bool TreeIterator::isReadable() const
{
	return implementation != NULL ? implementation->isReadable() : false;
}



bool TreeIterator::isWriteable() const
{
	return implementation != NULL ? implementation->isWriteable() : false;
}



InputStream* TreeIterator::createInputStream() const
{
	return implementation != NULL ? implementation->createInputStream() : NULL;
}



OutputStream* TreeIterator::createOutputStream() const
{
	return implementation != NULL ? implementation->createOutputStream() : NULL;
}



String TreeIterator::getValue() const
{
	return implementation != NULL ? implementation->getValue() : "";
}



void TreeIterator::setValue(const String& newValue) const
{
	if (implementation != NULL)
	{
		implementation->setValue(newValue);
	}
}



String TreeIterator::getValueOfAttribute(int attributePosition) const
{
	return implementation != NULL ? implementation->getValueOfAttribute(attributePosition) : "";
}



void TreeIterator::setValueOfAttribute(int attributePosition, const String& newValue) const
{
	if (implementation != NULL)
	{
		implementation->setValueOfAttribute(attributePosition, newValue);
	}
}



String TreeIterator::getValueOfAttribute(const String& attributeName) const
{
	return implementation != NULL ? implementation->getValueOfAttribute(attributeName) : "";
}



void TreeIterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
	if (implementation != NULL)
	{
		implementation->setValueOfAttribute(attributeName, newValue);
	}
}



String TreeIterator::getType() const
{
	return implementation != NULL ? implementation->getType() : "";
}



bool TreeIterator::isDefaultValue() const
{
	return implementation != NULL ? implementation->isDefaultValue() : false;
}



void TreeIterator::setDefaultValue() const
{
	if (implementation != NULL)
	{
		implementation->setDefaultValue();
	}
}



const Enumeration<String>& TreeIterator::getValueRange() const
{
	return implementation->getValueRange();
}



String TreeIterator::getPath() const
{
	return implementation != NULL ? implementation->getPath() : "";
}



void TreeIterator::push()
{
	if (implementation != NULL)
	{
		implementation->push();
	}
}



void TreeIterator::pop(bool restorePosition, bool restoreStack)
{
	if (implementation != NULL)
	{
		implementation->pop(restorePosition, restoreStack);
	}
}



bool TreeIterator::moveTo(const String& path)
{
	return implementation != NULL ? implementation->moveTo(path) : false;
}



int TreeIterator::getNodePosition() const
{
	return implementation != NULL ? implementation->getNodePosition() : -1;
}



bool TreeIterator::moveToNodePosition(int nodePosition)
{
	return implementation != NULL ? implementation->moveToNodePosition(nodePosition) : false;
}



bool TreeIterator::moveToNextNode()
{
	return implementation != NULL ? implementation->moveToNextNode() : false;
}



bool TreeIterator::moveToPreviousNode()
{
	return implementation != NULL ? implementation->moveToPreviousNode() : false;
}



bool TreeIterator::hasAttribute(const String& attributeName) const
{
	return implementation != NULL ? implementation->hasAttribute(attributeName) : false;
}



int TreeIterator::getAttributeCount() const
{
	return implementation != NULL ? implementation->getAttributeCount() : 0;
}



int TreeIterator::getAttributePosition() const
{
	return implementation != NULL ? implementation->getAttributePosition() : -1;
}



bool TreeIterator::moveToAttribute(int attributePosition)
{
	return implementation != NULL ? implementation->moveToAttribute(attributePosition) : false;
}



bool TreeIterator::moveToAttribute(const String& attributeName)
{
	return implementation != NULL ? implementation->moveToAttribute(attributeName) : false;
}



bool TreeIterator::moveToNextAttribute()
{
	return implementation != NULL ? implementation->moveToNextAttribute() : false;
}



bool TreeIterator::moveToPreviousAttribute()
{
	return implementation != NULL ? implementation->moveToPreviousAttribute() : false;
}



void TreeIterator::enumAttributeNames(const Enumerator<String>& enumerator) const
{
	if (implementation != NULL)
	{
		implementation->enumAttributeNames(enumerator);
	}
}



bool TreeIterator::hasParent() const
{
	return implementation != NULL ? implementation->hasParent() : false;
}



int TreeIterator::getParentCount() const
{
	return implementation != NULL ? implementation->getParentCount() : 0;
}



bool TreeIterator::moveToParent()
{
	return implementation != NULL ? implementation->moveToParent() : false;
}



bool TreeIterator::moveToParent(int parentGeneration)
{
	return implementation != NULL ? implementation->moveToParent(parentGeneration) : false;
}



bool TreeIterator::moveToParent(const String& parentName, int count)
{
	return implementation != NULL ? implementation->moveToParent(parentName, count) : false;
}



bool TreeIterator::moveToParentOrSelf(const String& parentOrSelfName)
{
	return implementation != NULL ? implementation->moveToParentOrSelf(parentOrSelfName) : false;
}



void TreeIterator::moveToRootNode()
{
	if (implementation != NULL)
	{
		implementation->moveToRootNode();
	}
}



bool TreeIterator::canHaveChildNodes() const
{
	return implementation != NULL ? implementation->canHaveChildNodes() : false;
}



bool TreeIterator::hasChildNodes() const
{
	return implementation != NULL ? implementation->hasChildNodes() : false;
}



bool TreeIterator::hasChildNode(const String& childName) const
{
	return implementation != NULL ? implementation->hasChildNode(childName) : false;
}



int TreeIterator::getChildNodeCount() const
{
	return implementation != NULL ? implementation->getChildNodeCount() : 0;
}



int TreeIterator::getChildNodePosition() const
{
	return implementation != NULL ? implementation->getChildNodePosition() : -1;
}



bool TreeIterator::moveToChildNode(int childPosition)
{
	return implementation != NULL ? implementation->moveToChildNode(childPosition) : false;
}



bool TreeIterator::moveToChildNode(const String& childName)
{
	return implementation != NULL ? implementation->moveToChildNode(childName) : false;
}



void TreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
	if (implementation != NULL)
	{
		implementation->enumChildNodeNames(enumerator);
	}
}



bool TreeIterator::hasNextNodeSibling() const
{
	return implementation != NULL ? implementation->hasNextNodeSibling() : false;
}



bool TreeIterator::moveToNextNodeSibling(int count)
{
	return implementation != NULL ? implementation->moveToNextNodeSibling(count) : false;
}



bool TreeIterator::moveToNextNodeSibling(const String& siblingName, int count)
{
	return implementation != NULL ? implementation->moveToNextNodeSibling(siblingName, count) : false;
}



bool TreeIterator::hasPreviousNodeSibling() const
{
	return implementation != NULL ? implementation->hasPreviousNodeSibling() : false;
}



bool TreeIterator::moveToPreviousNodeSibling(int count)
{
	return implementation != NULL ? implementation->moveToPreviousNodeSibling(count) : false;
}



bool TreeIterator::moveToPreviousNodeSibling(const String& siblingName, int count)
{
	return implementation != NULL ? implementation->moveToPreviousNodeSibling(siblingName, count) : false;
}



} // namespace Trees
} // namespace BaseLib
