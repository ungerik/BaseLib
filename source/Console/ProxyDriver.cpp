/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Console/ProxyDriver.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Console {



using namespace BaseLib::ErrorHandling;



ProxyDriver::ProxyDriver(AbstractDriver* newDriver)
  : driver(newDriver)
{
}



bool ProxyDriver::isInputAvailable() const
{
	if (driver != NULL)
	{
		return driver->isInputAvailable();
	}
	else
	{
		return false;
	}
}



char16 ProxyDriver::peekChar() const
{
	if (driver != NULL) 
	{
		return driver->peekChar();
	}
	else
	{
		stateError(PROXY_CONSOLE_HAS_NO_DRIVER("peekChar()"));
		return 0;
	}
}



char16 ProxyDriver::getChar()
{
	if (driver != NULL) 
	{
		return driver->getChar();
	}
	else
	{
		stateError(PROXY_CONSOLE_HAS_NO_DRIVER("getChar()"));
		return 0;
	}
}


/*
bool ProxyDriver::newLine()
{
	if (driver != NULL) 
	{
		return driver->newLine();
	}
	else
	{
		return false;
	}
}
*/


int ProxyDriver::write(const String& source)
{
	if (driver != NULL) 
	{
		return driver->write(source);
	}
	else
	{
		return 0;
	}
}



/*
bool ProxyDriver::write(char8 source)
{
	if (driver != NULL) 
	{
		return driver->write(source);
	}
	else
	{
		return false;
	}
}



bool ProxyDriver::write(char16 source)
{
	if (driver != NULL) 
	{
		return driver->write(source);
	}
	else
	{
		return false;
	}
}


int ProxyDriver::backSpace(int backSpaces)
{
	if (driver != NULL) 
	{
		return driver->backSpace(backSpaces);
	}
	else
	{
		return 0;
	}
}
*/

} // namespace Console
} // namespace BaseLib
