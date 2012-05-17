/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/



#include "BaseLib/Console/SystemDriver.h"
#include "BaseLib/intern/Errors.h"
#include <conio.h>


namespace BaseLib {
namespace Console {


using namespace BaseLib;
using namespace BaseLib::ErrorHandling;



bool SystemDriver::isInputAvailable() const
{
	return _kbhit() != 0;
}



char16 SystemDriver::peekChar() const
{
	const wint_t c = _ungetwch( _getwch() );
	if (c != WEOF)
	{
		return static_cast<char16>(c);
	}
	else
	{
		resultError(STANDARD_CONSOLE_ERROR("peekChar()"));
		return 0;
	}
}



char16 SystemDriver::getChar()
{
	return static_cast<char16>( _getwch() );
}


/*
bool SystemDriver::newLine()
{
	return (_putch('\r') != EOF) && (_putch('\n') != EOF);
}
*/


int SystemDriver::write(const String& source)
{
	return (_cputws(source.getChar16CString()) == 0) ? static_cast<int>(source.getLength()) : 0;
}


/*
bool SystemDriver::write(char8 source)
{
	return (_putch(source) == source);
}



bool SystemDriver::write(char16 source)
{
	return (_putwch(source) == source);
}


int SystemDriver::backSpace(int backSpaces)
{
	for (int i = 0; i < backSpaces; ++i)
	{
		_putch(8);
		_putch(' ');
		_putch(8);
	}
	return backSpaces;
}
*/



} // namespace Console
} // namespace BaseLib
