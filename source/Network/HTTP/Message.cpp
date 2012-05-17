/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/HTTP/Message.h"
#include "BaseLib/Network/HTTP/Header.h"


namespace BaseLib {
namespace Network {
namespace HTTP {




String Message::getHeaderField(const String& headerFieldName) const
{
	HeaderFields::const_iterator i = headerFields.find(headerFieldName);
	return (i != headerFields.end()) ? i->second->toString() : "";
}



void Message::setHeaderField(const String& headerFieldName, const String& newHeaderFieldValue)
{
	headerFields[headerFieldName] = HeaderField::createFromString(headerFieldName, newHeaderFieldValue);
}



} // namespace HTTP
} // namespace Network
} // namespace BaseLib