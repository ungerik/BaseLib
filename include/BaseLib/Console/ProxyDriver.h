/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_ProxyDriver_h
#define BaseLib_Console_ProxyDriver_h



#include "BaseLib/Console/AbstractDriver.h"



namespace BaseLib {
namespace Console {



/**
Console driver that acts as proxy for another driver.
@see AbstractDriver
*/
class BL_EXPORT ProxyDriver : public AbstractDriver {
public:
	explicit ProxyDriver(AbstractDriver* newDriver);

	inline AbstractDriver* getDriver() const
	{
		return driver;
	}

	inline void setDriver(AbstractDriver* newDriver)
	{
		driver = newDriver;
	}

	bool waitForInput();

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

private:
	AbstractDriver* driver;

};



} // namespace Console
} // namespace BaseLib



#endif // #ifndef BaseLib_Console_ProxyDriver_h
