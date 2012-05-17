/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/DataTreeNode.h"
///#include "BaseLib/Streams/StringInputStream.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(DataTreeNode, DefaultTreeNode)
{
}



TreeNode* DataTreeNode::create(const String& nodeName)
{
	return new DataTreeNode(nodeName);
}



DataTreeNode::DataTreeNode(const String& nodeName, bool subTreeIsHidden)
	: DefaultTreeNode(subTreeIsHidden)
	, attributes()
	, attributeNames(&attributes)
	, name(nodeName)
	, metaTags()
	, attributesMetaTags()
{
}



String DataTreeNode::getName() const
{
	return name;
}

	
	
const Enumeration<String>& DataTreeNode::getAttributeNames() const
{
	return attributeNames;
}



bool DataTreeNode::isAttributeReadable(const String& attributeName) const
{
	return true;
}



bool DataTreeNode::isAttributeWriteable(const String& attributeName) const
{
	return true;
}



bool DataTreeNode::getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat) const
{
	Attributes::ConstIterator i = attributes.find(attributeName);
	if (i != attributes.end())
	{
		attributeValue = i->second;
		return true;
	}
	else
	{
		return false;
	}
}



void DataTreeNode::setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	attributes[attributeName] = attributeValue;
}



//const InputStream* DataTreeNode::createInputStreamForAttribute(const String& attributeName) const
//{
//	return NULL; //return new StringInputStream(;
//}
//
//
//
//const OutputStream* DataTreeNode::createOutputStreamForAttribute(const String& attributeName) const
//{
//	return NULL;
//}



bool DataTreeNode::hasAttribute(const String& attributeName) const
{
	return attributes.find(attributeName) != attributes.end();
}



bool DataTreeNode::hasMetaTag(const String& metaTag) const
{
	return metaTags.find(metaTag) != metaTags.end();
}



bool DataTreeNode::hasAttributeMetaTag(const String& attributeName, const String& metaTag) const
{
	return false;
	/*
	AttributesMetaTags::const_iterator a = attributesMetaTags.find(attributeName); ///?
	return a != attributesMetaTags.end() && a->count(metaTag) != 0;
	*/
}



void DataTreeNode::addMetaTag(const String& metaTag)
{
	metaTags.insert(metaTag);
}



void DataTreeNode::removeMetaTag(const String& metaTag)
{
	metaTags.erase(metaTag);
}



void DataTreeNode::addAttributeMetaTag(const String& attributeName, const String& metaTag)
{
	/*AttributesMetaTags::iterator a = attributesMetaTags.find(attributeName); ///?
	return a != attributesMetaTags.end() && a->insert(metaTag);*/
}



void DataTreeNode::removeAttributeMetaTag(const String& attributeName, const String& metaTag)
{
	/*AttributesMetaTags::iterator a = attributesMetaTags.find(attributeName); ///?
	return a != attributesMetaTags.end() && a->erase(metaTag);*/
}



String DataTreeNode::getAttributeType(const String& attributeName) const
{
	return "string";
}



bool DataTreeNode::isAttributeDefault(const String& attributeName) const
{
	return getAttribute(attributeName, NULL).isEmpty() == true;
}



void DataTreeNode::setAttributeToDefault(const String& attributeName)
{
	setAttribute(attributeName, String(), NULL);
}



const Enumeration<String>& DataTreeNode::getAttributeValueRange(const String& attributeName) const
{
	static EmptyEnumeration<String> result;
	return result;
}



} // namespace Trees
} // namespace BaseLib
