/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_StdioDriver_h
#define BaseLib_Console_StdioDriver_h



#include "BaseLib/Console/AbstractDriver.h"
#include <stdio.h>



namespace BaseLib {
namespace Console {



/**
Console-driver that uses standard i/o via files.
Can be used for i/o redirection/piping.
@see AbstractDriver
*/
class BL_EXPORT StdioDriver : public AbstractDriver {
public:

	StdioDriver(FILE* forInputFile, FILE* forOutputFile);

	virtual bool isInputAvailable() const;
	virtual char16 peekChar() const;

	virtual char16 getChar();

	virtual int write(const String& source);

protected:

	FILE* inputFile;
	FILE* outputFile;

};



} // namespace Console
} // namespace BaseLib



#endif // #ifndef BaseLib_Console_StdioDriver_h
