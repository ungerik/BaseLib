/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_HTTP_Header_h
#define BaseLib_HTTP_Header_h


#include "BaseLib/Strings/String.h"


namespace BaseLib {
namespace Network {
namespace HTTP {



using BaseLib::Strings::String;



class HeaderField {
public:

	static const char ACCEPT[];


	static HeaderField* createFromString(const String& headerFieldName, const String& headerFieldValue);

	virtual ~HeaderField();
	virtual String toString() const = 0;
};


class UnknownHeaderField : public HeaderField {
public:

	UnknownHeaderField(const String& newString);

	virtual String toString() const;

protected:
	String string;
};


} // namespace HTTP
} // namespace Network
} // namespace BaseLib


#endif // #ifndef BaseLib_HTTP_Header_h
