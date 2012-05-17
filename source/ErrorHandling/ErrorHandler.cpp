/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/ErrorHandling/ErrorHandler.h"
#include "BaseLib/Console.h"



namespace BaseLib {
namespace ErrorHandling {



using namespace BaseLib::Console;

	

ErrorHandler::ErrorHandler()
	: mutex()
	, writingLog(true)
#ifdef BL_NO_EXCEPTIONS
	, throwingException(false)
#else
	, throwingException(true)
#endif
{
	addOutputStream(Console::trace);
	addOutputStream(Console::err);
}




} // namespace ErrorHandling
} // namespace BaseLib