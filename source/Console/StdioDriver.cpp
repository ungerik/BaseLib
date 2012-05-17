/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Console/StdioDriver.h"
#include "BaseLib/intern/Errors.h"
#include <conio.h>


namespace BaseLib {
namespace Console {



using namespace BaseLib::ErrorHandling;



StdioDriver::StdioDriver(FILE* forInputFile, FILE* forOutputFile)
  : inputFile(forInputFile)
  , outputFile(forOutputFile)
{
	BL_ASSERT(inputFile != NULL && outputFile != NULL);
}



bool StdioDriver::isInputAvailable() const
{
	return _kbhit() != 0; /// !!! Wie fragt man ob beim stdin Inputstream inputAvailable ist ??? (so nicht)
}



char16 StdioDriver::peekChar() const
{
	const int c = ungetwc(fgetwc(inputFile), inputFile);
	if (c != WEOF)
	{
		return static_cast<char16>(c);
	}
	else
	{
		resultError(STDIO_CONSOLE_ERROR(String("peekChar(): ") + strerror(ferror(inputFile))));
		clearerr(inputFile);
		return 0;
	}
}



char16 StdioDriver::getChar()
{
	const int c = fgetwc(inputFile);
	if (c != WEOF)
	{
		return static_cast<char16>(c);
	}
	else
	{
		resultError(STDIO_CONSOLE_ERROR(String("getChar(): ") + strerror(ferror(inputFile))));
		clearerr(inputFile);
		return 0;
	}
}



int StdioDriver::write(const String& source)
{
	int res;
	if (source.getEncoding() == CHAR16_ENCODING)
	{
		res = fputws(source.getChar16CString(), outputFile);
	}
	else
	{
		BL_ASSERT(source.getEncoding() == CHAR8_ENCODING);
		res = fputs(source.getChar8CString(), outputFile);
	}

	if (res >= 0)
	{
		fflush(outputFile);
		return static_cast<int>( source.getLength() );
	}
	else
	{
		resultError(STDIO_CONSOLE_ERROR(String("write(): ") + strerror(ferror(outputFile))));
		clearerr(outputFile);
		return 0;
	}
}


} // namespace Console
} // namespace BaseLib
