/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_h
#define BaseLib_Console_h



/**
@page Console

@section console Console

Base for console i/o is the class AbstractDriver.
There are different implementations, that are used for default instances.
- BaseLib::Console::systemConsole: System console of the application.
- BaseLib::Console::stdioConsole: Console using stdin, stdout.
- BaseLib::Console::stderrConsole: Console using stdin, stderr.
- BaseLib::Console::debugTraceConsole: Writes into the debug-output.
- BaseLib::Console::defaultConsole: Defaults to systemConsole.
- BaseLib::Console::errorConsole: Defaults to stderrConsole.

There are read(), write(), getChar() and peekChar() methods.
Alternatively the BaseLib::Streams::InputStream and BaseLib::Streams::OutputStream of a console-implementation
can be used via BaseLib::Console::AbstractDriver::getInputStream() and BaseLib::Console::AbstractDriver::getOutputStream().

For the predefined default console-instances there are also
predefined variables for their streams:
- BaseLib::Console::in: InputStream of defaultConsole.
- BaseLib::Console::out: OutputStream of stdioConsole.
- BaseLib::Console::err: OutputStream of stderrConsole.
- BaseLib::Console::trace: OutputStream of debugTraceConsole.

You can define your own stream-variables if you whish to use other drivers.

For example:
@code
using namespace BaseLib;

int i;
Console::in >> i;

Console::out << i << " some Text." << BaseLib::Streams::newLine;
Console::trace << "Marker 1" << BaseLib::Streams::newLine;
@endcode
*/



#include "BaseLib/Console/DebugTraceDriver.h"
#include "BaseLib/Console/AbstractDriver.h"
#include "BaseLib/Console/ProxyDriver.h"
#include "BaseLib/Console/StdioDriver.h"
#include "BaseLib/Console/SystemDriver.h"



namespace BaseLib {
namespace Console {



extern BL_EXPORT SystemDriver systemConsole; ///< System console of the application.
extern BL_EXPORT StdioDriver stdioConsole; ///< Console using stdin, stdout.
extern BL_EXPORT StdioDriver stderrConsole; ///< Console using stdin, stderr.
extern BL_EXPORT DebugTraceDriver debugTraceConsole; ///< Writes into the debug-output.

extern BL_EXPORT ProxyDriver defaultConsole; ///< Defaults to systemConsole.
extern BL_EXPORT ProxyDriver errorConsole; ///< Defaults to stderrConsole.

extern BL_EXPORT InputStream& in; ///< InputStream of defaultConsole.
extern BL_EXPORT OutputStream& out; ///< OutputStream of stdioConsole.
extern BL_EXPORT OutputStream& err; ///< OutputStream of stderrConsole.
extern BL_EXPORT OutputStream& trace; ///< OutputStream of debugTraceConsole.


/**
Waits durationInSeconds for the next input from a console.
*/
BL_EXPORT bool waitForInput(double durationInSeconds = 1000000.0, const AbstractDriver& driver = defaultConsole);



} // namespace Console
} // namespace BaseLib


#endif // #ifndef BaseLib_Console_h
