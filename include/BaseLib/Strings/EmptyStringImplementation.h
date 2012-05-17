/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_EmptyStringImplementation_h
#define BaseLib_Strings_EmptyStringImplementation_h



#include "BaseLib/Strings/AbstractStringImplementation.h"



namespace BaseLib {
namespace Strings {



class BL_EXPORT EmptyStringImplementation : public AbstractStringImplementation {
public:

	static EmptyStringImplementation* getChar8Instance();
	static EmptyStringImplementation* getChar16Instance();

	EmptyStringImplementation(StringEncoding stringEncoding);

	virtual StringEncoding getEncoding() const;
	
	virtual AbstractStringImplementation* clone(int position, int length) const;

	//virtual std::locale& getLocale() const;

	virtual int getByteSize() const;
	virtual int getCharacterByteSize() const;

	virtual int getLength() const;

	virtual void setLength(int newLength);
	virtual void insert(int position, int length);
	virtual void remove(int position, int length);

	virtual char8 getChar8(int position) const;
	virtual char8 getLowerCaseChar8(int position) const;
	virtual char8 getUpperCaseChar8(int position) const;
	virtual void setChar(int position, char8 newChar);

	virtual char16 getChar16(int position) const;
	virtual char16 getLowerCaseChar16(int position) const;
	virtual char16 getUpperCaseChar16(int position) const;
	virtual void setChar(int position, char16 newChar);

	virtual char32 getChar32(int position) const;
	virtual char32 getLowerCaseChar32(int position) const;
	virtual char32 getUpperCaseChar32(int position) const;
	virtual void setChar(int position, char32 newChar);

	virtual void fill(char8 fillerChar, int position, int length);
	virtual void fill(char16 fillerChar, int position, int length);

	virtual void lowerCase(int position, int length);
	virtual void upperCase(int position, int length);

	virtual void copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length);

	virtual void copyFromCharArray(const char8 * source, int destStartPosition, int length);
	virtual void copyToCharArray(char8 * destination, int sourceStartPosition, int length) const;

	virtual void copyFromCharArray(const char16 * source, int destStartPosition, int length);
	virtual void copyToCharArray(char16 * destination, int sourceStartPosition, int length) const;

	virtual const void * getPointer() const;

	virtual const char8 * getChar8Array() const;
	virtual const char16 * getChar16Array() const;

	virtual const char8 * getChar8CString() const;
	virtual const char16 * getChar16CString() const;

	virtual int hash(int position, int length) const;

	virtual AbstractStringImplementation* getUnsharedInstance();
	virtual AbstractStringImplementation* getUnsharedInstance(int start, int length);

protected:

	static const char8 * EMPTY_CHAR8_CSTRING;
	static const char16 * EMPTY_CHAR16_CSTRING;

	static EmptyStringImplementation CHAR8_SINGLETON;
	static EmptyStringImplementation CHAR16_SINGLETON;

	StringEncoding encoding;

};



} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_EmptyStringImplementation_h