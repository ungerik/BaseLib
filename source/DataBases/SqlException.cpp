/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/SqlException.h"



namespace BaseLib {
namespace DataBases {




SqlException::SqlException(const Exception& causingException)
	: ArgumentException(causingException)
{
}



SqlException::SqlException(const Exception& causingException, int errorCode)
	: ArgumentException(causingException, errorCode)
{
}



SqlException::SqlException(const Exception& causingException, const String& errorDescription)
	: ArgumentException(causingException, errorDescription)
{
}



SqlException::SqlException(const Exception& causingException, const String& errorDescription, int errorCode)
	: ArgumentException(causingException, errorDescription, errorCode)
{
}



SqlException::SqlException(const String& errorDescription, int errorCode)
	: ArgumentException(errorDescription, errorCode)
{
}



} // namespace DataBases
} // namespace BaseLib