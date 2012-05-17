/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_Sax_Handler_h
#define BaseLib_Xml_Sax_Handler_h



#include "BaseLib/Common.h"
#include "BaseLib/Xml/Sax/Locator.h"
#include "BaseLib/Xml/Sax/Attributes.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Xml {
namespace Sax {


using BaseLib::Strings::String;



class BL_EXPORT Handler {
public:

	virtual ~Handler();

	///virtual void setDocumentLocator(const Locator& locator);

	virtual void startDocument();
	virtual void endDocument();
	virtual void startElement(const String& uri, const String& localName, const String& qName, const Attributes& atts);
	virtual void endElement(const String& uri, const String& localName, const String& qName);
	virtual void cdataBlock(const String& value);
	virtual void characters(const String& ch);
	virtual void ignorableWhitespace(const String& ch);
	virtual void processingInstruction(const String& target, const String& data);
	virtual void comment(const String& value);
	virtual void warning(const String& message, int line, int column);
	virtual void error(const String& message, int line, int column);
	virtual void fatalError(const String& message, int line, int column);

};






} // namespace Sax
} // namespace Xml
} // namespace BaseLib


#endif // #ifndef BaseLib_Xml_Sax_Handler_h
