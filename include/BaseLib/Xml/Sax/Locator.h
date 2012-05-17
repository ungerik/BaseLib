/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_Sax_Locator_h
#define BaseLib_Xml_Sax_Locator_h



#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Xml {
namespace Sax {


using BaseLib::Strings::String;



// shouldReportCharacters
// shouldReportIgnorableWhitespace
// canReportComments

class BL_EXPORT Locator {
public:

	virtual ~Locator();

	/*
	int	getColumnNumber() const;
	int	getLineNumber() const;
	String getPublicId() const;
	String getSystemId() const;
	*/

	/*
	virtual String getEncoding() const;
	virtual String getXMLVersion() const;
	*/
};



} // namespace Sax
} // namespace Xml
} // namespace BaseLib


#endif // #ifndef BaseLib_Xml_Sax_Locator_h 



