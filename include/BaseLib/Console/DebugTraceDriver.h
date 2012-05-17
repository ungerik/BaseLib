/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_DebugTraceDriver_h
#define BaseLib_Console_DebugTraceDriver_h



#include "BaseLib/Console/AbstractDriver.h"



namespace BaseLib {
namespace Console {



class BL_EXPORT DebugTraceDriver : public AbstractDriver {
public:

	DebugTraceDriver();

	virtual bool isInputAvailable() const;
	virtual char16 peekChar() const;

	virtual char16 getChar();

	virtual int write(const String& source);
};



} // namespace Console
} // namespace BaseLib



#endif // #ifndef BaseLib_Console_DebugTraceDriver_h
