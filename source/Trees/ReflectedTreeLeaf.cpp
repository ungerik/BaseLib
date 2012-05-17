/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/ReflectedTreeLeaf.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(ReflectedTreeLeaf, DefaultTreeLeaf)
{
	registerProperty("reflectionObjectClass", &ReflectedTreeLeaf::getReflectionObjectClassNameWithNameSpace);
	registerProperty("usingClassNameSpaces", &ReflectedTreeLeaf::isUsingClassNameSpaces);
}



ReflectedTreeLeaf::ReflectedTreeLeaf(bool useClassNameSpaces, Object* newReflectionObject)
	: DefaultTreeLeaf()
	, nameUsesClassNameSpaces(useClassNameSpaces)
	, reflectionObject(newReflectionObject)
	, onBeforeSomeParentNodeChangesFunctor(NULL)
	, onBeforeParentNodeChangesFunctor(NULL)
	, onAfterParentNodeChangedFunctor(NULL)
	//, beginSetAttributesSequenceFunctor(NULL)
	//, endSetAttributesSequenceFunctor(NULL)
{
}



void ReflectedTreeLeaf::setReflectionObject(
	Object* newReflectionObject,
	ChangeParentNodeFunctor* newOnBeforeSomeParentNodeChangesFunctor,
	ChangeParentNodeFunctor* newOnBeforeParentNodeChangesFunctor,
	ChangeParentNodeFunctor* newOnAfterParentNodeChangedFunctor/*,
	Functor0<void>* newBeginSetAttributesSequenceFunctor,
	Functor0<void>* newEndAddSetAttributesSequenceFunctor*/)
{
	reflectionObject = newReflectionObject;
	onBeforeSomeParentNodeChangesFunctor = newOnBeforeSomeParentNodeChangesFunctor;
	onBeforeParentNodeChangesFunctor = newOnBeforeParentNodeChangesFunctor;
	onAfterParentNodeChangedFunctor = newOnAfterParentNodeChangedFunctor;
	//beginSetAttributesSequenceFunctor = newBeginSetAttributesSequenceFunctor;
	//endSetAttributesSequenceFunctor = newEndAddSetAttributesSequenceFunctor;
}



void ReflectedTreeLeaf::deleteSelf()
{
	delete reflectionObject;
}



void ReflectedTreeLeaf::beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode)
{
	DefaultTreeLeaf::beforeSomeParentNodeChanges(treeNode, oldParentNode, newParentNode);
	if (onBeforeSomeParentNodeChangesFunctor != NULL)
	{
		(*onBeforeSomeParentNodeChangesFunctor)(treeNode, oldParentNode, newParentNode);
	}
}



void ReflectedTreeLeaf::setParent(TreeNode* newParent)
{
	TreeNode* const oldParent = parent;

	TreeNode::setParent(newParent); // calls beforeSomeParentNodeChanges()

	if (onAfterParentNodeChangedFunctor != NULL)
	{
		(*onAfterParentNodeChangedFunctor)(this, oldParent, newParent);
	}
}



String ReflectedTreeLeaf::getName() const
{
	return nameUsesClassNameSpaces ? getReflectionObject()->getClass()->getName() : getReflectionObject()->getClass()->getNameWithoutNameSpace();
}



const Enumeration<String>& ReflectedTreeLeaf::getAttributeNames() const
{
	return getReflectionObject()->getClass()->getPropertyNames();
}



bool ReflectedTreeLeaf::isAttributeReadable(const String& attributeName) const
{
	return getReflectionObject()->isPropertyReadable(attributeName);
}



bool ReflectedTreeLeaf::isAttributeWriteable(const String& attributeName) const
{
	return getReflectionObject()->isPropertyWriteable(attributeName);
}



bool ReflectedTreeLeaf::getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat) const
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



void ReflectedTreeLeaf::setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	getReflectionObject()->setProperty(attributeName, attributeValue, numberFormat);
}



//const InputStream* ReflectedTreeLeaf::createInputStreamForAttribute(const String& attributeName) const
//{
//	return NULL;
//}
//
//
//
//const OutputStream* ReflectedTreeLeaf::createOutputStreamForAttribute(const String& attributeName) const
//{
//	return NULL;
//}



bool ReflectedTreeLeaf::hasAttribute(const String& attributeName) const
{
	return getReflectionObject()->getClass()->hasProperty(attributeName);
}



Object* ReflectedTreeLeaf::getReflectionObject()
{
	return reflectionObject;
}



const Object* ReflectedTreeLeaf::getReflectionObject() const
{
	return reflectionObject;
}



bool ReflectedTreeLeaf::hasMetaTag(const String& metaTag) const
{
	return getReflectionObject()->hasMetaTag(metaTag);
}



bool ReflectedTreeLeaf::hasAttributeMetaTag(const String& attributeName, const String& metaTag) const
{
	return getReflectionObject()->hasPropertyMetaTag(attributeName, metaTag);
}



String ReflectedTreeLeaf::getAttributeType(const String& attributeName) const
{
	return getReflectionObject()->getClass()->property(attributeName)->getTypeAsString();
}



bool ReflectedTreeLeaf::isAttributeDefault(const String& attributeName) const
{
	return getReflectionObject()->isPropertyDefault(attributeName);
}



void ReflectedTreeLeaf::setAttributeToDefault(const String& attributeName)
{
	getReflectionObject()->setPropertyToDefault(attributeName);
}



const Enumeration<String>& ReflectedTreeLeaf::getAttributeValueRange(const String& attributeName) const
{
	return getReflectionObject()->getPropertyValueRange(attributeName);
}



void ReflectedTreeLeaf::onBeforeAttributesTransaction()
{
	//if (beginSetAttributesSequenceFunctor != NULL)
	//{
	//	(*beginSetAttributesSequenceFunctor)();
	//}
	getReflectionObject()->onBeforePropertiesTransaction();
}



void ReflectedTreeLeaf::onAfterAttributesTransaction()
{
	getReflectionObject()->onAfterPropertiesTransaction();
	//if (endSetAttributesSequenceFunctor != NULL)
	//{
	//	(*endSetAttributesSequenceFunctor)();
	//}
}



} // namespace Trees
} // namespace BaseLib


