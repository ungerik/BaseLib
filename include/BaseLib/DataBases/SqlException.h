/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_SqlException_h
#define BaseLib_DataBases_SqlException_h



#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace DataBases {



using BaseLib::Strings::String;



class BL_EXPORT SqlException : public BaseLib::ErrorHandling::ArgumentException {
public:

	SqlException(const Exception& causingException);
	SqlException(const Exception& causingException, int errorCode);
	SqlException(const Exception& causingException, const String& errorDescription);
	SqlException(const Exception& causingException, const String& errorDescription, int errorCode);
    SqlException(const String& errorDescription, int errorCode = 0);


};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_SqlException_h
