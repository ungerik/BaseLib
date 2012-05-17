/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_XmlTreeLoader_h
#define BaseLib_Xml_XmlTreeLoader_h



#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Trees/DataTreeNode.h"
#include "BaseLib/Xml/Sax.h"



namespace BaseLib {
namespace Xml {



using BaseLib::Trees::TreeNode;
using BaseLib::Trees::DataTreeNode;
using BaseLib::Strings::String;
using BaseLib::Strings::NumberFormat;



class BL_EXPORT XmlTreeLoader : public TreeNode::AbstractFactory, protected Sax::Handler {
public:
	
	XmlTreeLoader(const String& xmlFileName, CreateNodeFunctionPointer createNodeFunctionPointer = &DataTreeNode::create, const NumberFormat* useNumberFormat = &NumberFormat::getEnglish());
	XmlTreeLoader(const String& xmlFileName, CreateNodeFunctor& newCreateNodeFunctor, const NumberFormat* useNumberFormat = &NumberFormat::getEnglish());

protected:

	String fileName;

	// From TreeNode::AbstractFactory
	virtual bool buildTreeImplementation(bool ignoreText);

	// From Sax::Handler
	virtual void startElement(const String& uri, const String& localName, const String& qName, const Sax::Attributes& atts);
	//virtual void cdataBlock(const String& value);
	virtual void characters(const String& ch);
	virtual void endElement(const String& uri, const String& localName, const String& qName);
};



} // namespace Xml
} // namespace BaseLib



#endif // #ifndef BaseLib_Xml_XmlTreeLoader_h
