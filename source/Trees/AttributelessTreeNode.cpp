/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/AttributelessTreeNode.h"
///#include "BaseLib/Streams/StringInputStream.h"
#include "BaseLib/intern/Errors.h"



#define ATTRIBUTE_NOT_FOUND(a) ("Attribute '" + a + "' not found!" ERROR_AT)



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(AttributelessTreeNode, DefaultTreeNode)
{
}



AttributelessTreeNode::AttributelessTreeNode(const String& nodeName, bool subTreeIsHidden)
	: DefaultTreeNode(subTreeIsHidden)
	, name(nodeName)
{
}



String AttributelessTreeNode::getName() const
{
	return name;
}

	
	
const Enumeration<String>& AttributelessTreeNode::getAttributeNames() const
{
	static const EmptyEnumeration<String> attributeNames;
	return attributeNames;
}



bool AttributelessTreeNode::isAttributeReadable(const String& attributeName) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	return false;
}



bool AttributelessTreeNode::isAttributeWriteable(const String& attributeName) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	return false;
}



bool AttributelessTreeNode::getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat) const
{
	return false;
}



void AttributelessTreeNode::setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
}



bool AttributelessTreeNode::hasAttribute(const String& attributeName) const
{
	return false;
}



bool AttributelessTreeNode::hasMetaTag(const String& metaTag) const
{
	return false;
}



bool AttributelessTreeNode::hasAttributeMetaTag(const String& attributeName, const String& metaTag) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	return false;
}



void AttributelessTreeNode::addMetaTag(const String& metaTag)
{
}



void AttributelessTreeNode::removeMetaTag(const String& metaTag)
{
}



void AttributelessTreeNode::addAttributeMetaTag(const String& attributeName, const String& metaTag)
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
}



void AttributelessTreeNode::removeAttributeMetaTag(const String& attributeName, const String& metaTag)
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
}



String AttributelessTreeNode::getAttributeType(const String& attributeName) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	return Empty();
}



bool AttributelessTreeNode::isAttributeDefault(const String& attributeName) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	return false;
}



void AttributelessTreeNode::setAttributeToDefault(const String& attributeName)
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
}



const Enumeration<String>& AttributelessTreeNode::getAttributeValueRange(const String& attributeName) const
{
	argumentError(ATTRIBUTE_NOT_FOUND(attributeName));
	static const EmptyEnumeration<String> result;
	return result;
}



} // namespace Trees
} // namespace BaseLib
