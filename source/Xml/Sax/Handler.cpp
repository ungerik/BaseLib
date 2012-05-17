/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Xml/Sax/Handler.h"



namespace BaseLib {
namespace Xml {
namespace Sax {



Handler::~Handler()
{
}


/*
void Handler::setDocumentLocator(const Locator& locator)
{
}
*/


void Handler::startDocument()
{
}



void Handler::endDocument()
{
}



void Handler::startElement(const String& uri, const String& localName, const String& qName, const Attributes& atts)
{
}



void Handler::endElement(const String& uri, const String& localName, const String& qName)
{
}



void Handler::cdataBlock(const String& value)
{
}



void Handler::characters(const String& ch)
{
}



void Handler::processingInstruction(const String& target, const String& data)
{
}



void Handler::comment(const String& value)
{
}



void Handler::warning(const String& message, int line, int column)
{
}



void Handler::error(const String& message, int line, int column)
{
}



void Handler::fatalError(const String& message, int line, int column)
{
}



void Handler::ignorableWhitespace(const String& ch)
{
}



} // namespace Sax
} // namespace Xml
} // namespace BaseLib
