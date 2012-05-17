/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/HTTP/Header.h"



namespace BaseLib {
namespace Network {
namespace HTTP {

	

const char HeaderField::ACCEPT[] = "Accept";



HeaderField* HeaderField::createFromString(const String& headerFieldName, const String& headerFieldValue)
{
	return new UnknownHeaderField(headerFieldValue); ///
}



HeaderField::~HeaderField()
{
}




UnknownHeaderField::UnknownHeaderField(const String& newString)
  : string(newString)
{
}



String UnknownHeaderField::toString() const
{
	return string;
}



} // namespace HTTP
} // namespace Network
} // namespace BaseLib