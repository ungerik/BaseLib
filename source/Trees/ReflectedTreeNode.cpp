/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/ReflectedTreeNode.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(ReflectedTreeNode, DefaultTreeNode)
{
	registerProperty("reflectionObjectClass", &ReflectedTreeNode::getReflectionObjectClassNameWithNameSpace);
	registerProperty("usingClassNameSpaces", &ReflectedTreeNode::isUsingClassNameSpaces);
}



ReflectedTreeNode::ReflectedTreeNode(bool useClassNameSpaces, Object* newReflectionObject, bool subTreeIsHidden)

	: DefaultTreeNode(subTreeIsHidden)
	, nameUsesClassNameSpaces(useClassNameSpaces)
	, reflectionObject(newReflectionObject)
	, onBeforeSomeParentNodeChangesFunctor(NULL)
	, onBeforeParentNodeChangesFunctor(NULL)
	, onAfterParentNodeChangedFunctor(NULL)
	, childNodeAddedFunctor(NULL)
	, childNodeRemovedFunctor(NULL)
	, onBeforeChildrenTransactionFunctor(NULL)
	, onAfterChildrenTransactionFunctor(NULL)
	//, beginSetAttributesSequenceFunctor(NULL)
	//, endSetAttributesSequenceFunctor(NULL)
{
}



void ReflectedTreeNode::setReflectionObject(
	Object* newReflectionObject,
	ChangeParentNodeFunctor* newOnBeforeSomeParentNodeChangesFunctor,
	ChangeParentNodeFunctor* newOnBeforeParentNodeChangesFunctor,
	ChangeParentNodeFunctor* newOnAfterParentNodeChangedFunctor,
	ChildNodeAddedFunctor* newOnChildNodeAddedFunctor,
	ChildNodeRemovedFunctor* newOnChildNodeRemovedFunctor,
	Functor0<void>* newOnBeforeChildrenTransactionFunctor,
	Functor0<void>* newOnAfterChildrenTransactionFunctor/*,
	Functor0<void>* newBeginSetAttributesSequenceFunctor,
	Functor0<void>* newEndAddSetAttributesSequenceFunctor*/)
{
	reflectionObject = newReflectionObject;
	onBeforeSomeParentNodeChangesFunctor = newOnBeforeSomeParentNodeChangesFunctor;
	onBeforeParentNodeChangesFunctor = newOnBeforeParentNodeChangesFunctor;
	onAfterParentNodeChangedFunctor = newOnAfterParentNodeChangedFunctor;
	childNodeAddedFunctor = newOnChildNodeAddedFunctor;
	childNodeRemovedFunctor = newOnChildNodeRemovedFunctor;
	onBeforeChildrenTransactionFunctor = newOnBeforeChildrenTransactionFunctor;
	onAfterChildrenTransactionFunctor = newOnAfterChildrenTransactionFunctor;
	//beginSetAttributesSequenceFunctor = newBeginSetAttributesSequenceFunctor;
	//endSetAttributesSequenceFunctor = newEndAddSetAttributesSequenceFunctor;
}



void ReflectedTreeNode::deleteSelf()
{
	delete reflectionObject;
}



void ReflectedTreeNode::beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode)
{
	DefaultTreeNode::beforeSomeParentNodeChanges(treeNode, oldParentNode, newParentNode);
	if (onBeforeSomeParentNodeChangesFunctor != NULL)
	{
		(*onBeforeSomeParentNodeChangesFunctor)(treeNode, oldParentNode, newParentNode);
	}
}



void ReflectedTreeNode::setParent(TreeNode* newParent)
{
	TreeNode* const oldParent = parent;

	DefaultTreeNode::setParent(newParent); // calls beforeSomeParentNodeChanges()

	if (onAfterParentNodeChangedFunctor != NULL)
	{
		(*onAfterParentNodeChangedFunctor)(this, oldParent, newParent);
	}
}



void ReflectedTreeNode::addChild(TreeNode* newChild)
{
	DefaultTreeNode::addChild(newChild);
	if (childNodeAddedFunctor != NULL)
	{
		(*childNodeAddedFunctor)(newChild, getChildCount()-1);
	}
}



void ReflectedTreeNode::insertChild(TreeNode* newChild, int index)
{
	DefaultTreeNode::insertChild(newChild, index);
	if (childNodeAddedFunctor != NULL)
	{
		(*childNodeAddedFunctor)(newChild, index);
	}
}



TreeNode* ReflectedTreeNode::replaceChild(int index, TreeNode* newChild)
{
	TreeNode* result = DefaultTreeNode::replaceChild(index, newChild);
	if (childNodeRemovedFunctor != NULL)
	{
		(*childNodeRemovedFunctor)(result, index);
	}
	if (childNodeAddedFunctor != NULL)
	{
		(*childNodeAddedFunctor)(newChild, index);
	}
	return result;
}



TreeNode* ReflectedTreeNode::removeChild(int index)
{
	TreeNode* oldChild = DefaultTreeNode::removeChild(index);
	if (childNodeRemovedFunctor != NULL)
	{
		(*childNodeRemovedFunctor)(oldChild, index);
	}
	return oldChild;
}



String ReflectedTreeNode::getName() const
{
	return nameUsesClassNameSpaces ? getReflectionObject()->getClass()->getName() : getReflectionObject()->getClass()->getNameWithoutNameSpace();
}



const Enumeration<String>& ReflectedTreeNode::getAttributeNames() const
{
	return getReflectionObject()->getClass()->getPropertyNames();
}



bool ReflectedTreeNode::isAttributeReadable(const String& attributeName) const
{
	return getReflectionObject()->isPropertyReadable(attributeName);
}



bool ReflectedTreeNode::isAttributeWriteable(const String& attributeName) const
{
	return getReflectionObject()->isPropertyWriteable(attributeName);
}



bool ReflectedTreeNode::getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat) const
{
	const Reflection::Property* property = getReflectionObject()->getClass()->getPropertyOrNull(attributeName);
	if (property != NULL)
	{
		attributeValue = property->get(getReflectionObject(), numberFormat);
		return true;
	}
	else
	{
		return false;
	}
}



void ReflectedTreeNode::setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	getReflectionObject()->setProperty(attributeName, attributeValue, numberFormat);
}



//const InputStream* ReflectedTreeNode::createInputStreamForAttribute(const String& attributeName) const
//{
//	return NULL;
//}
//
//
//
//const OutputStream* ReflectedTreeNode::createOutputStreamForAttribute(const String& attributeName) const
//{
//	return NULL;
//}



bool ReflectedTreeNode::hasAttribute(const String& attributeName) const
{
	return getReflectionObject()->getClass()->hasProperty(attributeName);
}



Object* ReflectedTreeNode::getReflectionObject()
{
	return reflectionObject;
}



const Object* ReflectedTreeNode::getReflectionObject() const
{
	return reflectionObject;
}



bool ReflectedTreeNode::hasMetaTag(const String& metaTag) const
{
	return getReflectionObject()->hasMetaTag(metaTag);
}



bool ReflectedTreeNode::hasAttributeMetaTag(const String& attributeName, const String& metaTag) const
{
	return getReflectionObject()->hasPropertyMetaTag(attributeName, metaTag);
}



String ReflectedTreeNode::getAttributeType(const String& attributeName) const
{
	return getReflectionObject()->getClass()->property(attributeName)->getTypeAsString();
}



bool ReflectedTreeNode::isAttributeDefault(const String& attributeName) const
{
	return getReflectionObject()->isPropertyDefault(attributeName);
}



void ReflectedTreeNode::setAttributeToDefault(const String& attributeName)
{
	getReflectionObject()->setPropertyToDefault(attributeName);
}



const Enumeration<String>& ReflectedTreeNode::getAttributeValueRange(const String& attributeName) const
{
	return getReflectionObject()->getPropertyValueRange(attributeName);
}



void ReflectedTreeNode::onBeforeAttributesTransaction()
{
	//TreeNode::onBeforeAttributesTransaction(); // empty
	//if (beginSetAttributesSequenceFunctor != NULL)
	//{
	//	(*beginSetAttributesSequenceFunctor)();
	//}
	getReflectionObject()->onBeforePropertiesTransaction();
}



void ReflectedTreeNode::onAfterAttributesTransaction()
{
	getReflectionObject()->onAfterPropertiesTransaction();
	//if (endSetAttributesSequenceFunctor != NULL)
	//{
	//	(*endSetAttributesSequenceFunctor)();
	//}
	//TreeNode::onAfterAttributesTransaction(); // empty
}



void ReflectedTreeNode::onBeforeChildrenTransaction()
{
	//TreeNode::onBeforeChildrenTransaction(); // empty
	if (onBeforeChildrenTransactionFunctor != NULL)
	{
		(*onBeforeChildrenTransactionFunctor)();
	}
}



void ReflectedTreeNode::onAfterChildrenTransaction()
{
	if (onAfterChildrenTransactionFunctor != NULL)
	{
		(*onAfterChildrenTransactionFunctor)();
	}
	//TreeNode::onAfterChildrenTransaction();  // not empty?
}



} // namespace Trees
} // namespace BaseLib


