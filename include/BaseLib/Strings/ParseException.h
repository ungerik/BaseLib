/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_ParseException_h
#define BaseLib_Strings_ParseException_h



#include "BaseLib/Common.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Strings {



using BaseLib::ErrorHandling::Exception;



class BL_EXPORT ParseException : public Exception {
public 
	ParseException(const Exception& causingException);
	ParseException(const Exception& causingException, int errorCode);
	ParseException(const Exception& causingException, const String& errorDescription);
	ParseException(const Exception& causingException, const String& errorDescription, int errorCode);
    ParseException(const String& errorDescription, int errorCode = 0);
};



} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_ParseException_h
