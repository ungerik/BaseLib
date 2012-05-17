/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Console.h"
#include "BaseLib/System/Thread.h"
#include "BaseLib/System/Time.h"


namespace BaseLib {
namespace Console {



using namespace BaseLib::System;


// Moved to BaseLib.cpp because of initialization order:
//SystemDriver systemConsole;
//StdioDriver stdioConsole(stdin, stdout);
//StdioDriver stderrConsole(stdin, stderr);

//ProxyDriver defaultConsole(&systemConsole);
//ProxyDriver errorConsole(&stderrConsole);

//TextInputStream& in = systemConsole.inputStream();
//TextOutputStream& out = stdioConsole.outputStream();
//TextOutputStream& err = errorConsole.outputStream();




bool waitForInput(double durationInSeconds, const AbstractDriver& driver)
{
	BL_ASSERT(durationInSeconds >= 0.0);
	const double endTime = Time::nowInSeconds() + durationInSeconds;

	if (durationInSeconds == 0.0)
	{
		return driver.isInputAvailable();
	}
	else
	{
		while (driver.isInputAvailable() == false)
		{
			if (Time::nowInSeconds() > endTime) return false;
			Thread::sleepSeconds(0.01);
		}
		return true;
	}
}



} // namespace Console
} // namespace BaseLib
