/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Console/DebugTraceDriver.h"
#include "BaseLib/intern/Errors.h"
#include <conio.h>


namespace BaseLib {
namespace Console {



using namespace BaseLib;
using namespace BaseLib::ErrorHandling;



DebugTraceDriver::DebugTraceDriver()
	: AbstractDriver()
{
}



bool DebugTraceDriver::isInputAvailable() const
{
	return false;
}



char16 DebugTraceDriver::peekChar() const
{
	notImplementedError("DebugTraceDriver returns no input!" ERROR_AT);
	return 0;
}



char16 DebugTraceDriver::getChar()
{
	notImplementedError("DebugTraceDriver returns no input!" ERROR_AT);
	return 0;
}



int DebugTraceDriver::write(const String& source)
{
	if (source.getEncoding() == CHAR16_ENCODING)
	{
		OutputDebugStringW(source.getChar16CString());
	}
	else
	{
		OutputDebugStringA(source.getChar8CString());
	}
	return source.getLength();
}




} // namespace Console
} // namespace BaseLib
