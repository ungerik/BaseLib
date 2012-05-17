/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Xml/XmlTreeLoader.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Xml {



using namespace BaseLib::Strings;



XmlTreeLoader::XmlTreeLoader(const String& xmlFileName, CreateNodeFunctionPointer createNodeFunctionPointer, const NumberFormat* useNumberFormat)
	: TreeNode::AbstractFactory(createNodeFunctionPointer, useNumberFormat)
	, fileName(xmlFileName)
{
}



XmlTreeLoader::XmlTreeLoader(const String& xmlFileName, CreateNodeFunctor& newCreateNodeFunctor, const NumberFormat* useNumberFormat)
	: TreeNode::AbstractFactory(newCreateNodeFunctor, useNumberFormat)
	, fileName(xmlFileName)
{
}



bool XmlTreeLoader::buildTreeImplementation(bool ignoreText)
{
	Sax::Parser parser(fileName);
	parser.setReportingCharacters(ignoreText == false);
	return parser.parse(*this);
}



void XmlTreeLoader::startElement(const String& uri, const String& localName, const String& qName, const Sax::Attributes& atts)
{
	beginNode(qName);
	onBeforeAttributesTransaction();
	const int attributeCount = atts.getLength();
	for (int i = 0; i < attributeCount; ++i)
	{
		setNodeAttribute(atts.getLocalName(i), atts.getValue(i));
	}
	onAfterAttributesTransaction();
	onBeforeChildrenTransaction();
}



/*
void XmlTreeLoader::cdataBlock(const String& value)
{
}
*/



void XmlTreeLoader::characters(const String& ch)
{
	if (ch.findFirstNotOf(defaultTokenDelimiters) != String::END)
	{
		appendNodeAttribute("data", ch);
	}
}



void XmlTreeLoader::endElement(const String& uri, const String& localName, const String& qName)
{
	onAfterChildrenTransaction();
	endNode();
}



} // namespace Xml
} // namespace BaseLib
