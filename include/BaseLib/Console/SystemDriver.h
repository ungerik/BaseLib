/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_SystemDriver_h
#define BaseLib_Console_SystemDriver_h



#include "BaseLib/Console/AbstractDriver.h"



namespace BaseLib {
namespace Console {



/**
Console-driver that uses the lowest level console API.
It's not useable for i/o redirection/piping.
For this use StdioDriver instead.
@see AbstractDriver
*/
class BL_EXPORT SystemDriver : public AbstractDriver {
public:
	virtual bool isInputAvailable() const;
	virtual char16 peekChar() const;

	virtual char16 getChar();

	//virtual bool newLine();
	virtual int write(const String& source);
	/*
	virtual bool write(char8 source);
	virtual bool write(char16 source);
	virtual int backSpace(int backSpaces);
	*/
};



} // namespace Console
} // namespace BaseLib



#endif // #ifndef BaseLib_Console_SystemDriver_h
