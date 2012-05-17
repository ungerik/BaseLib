/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_AbstractStringImplementation_h
#define BaseLib_Strings_AbstractStringImplementation_h



#include "BaseLib/Common.h"
//#include <locale>



namespace BaseLib {
namespace Strings {



enum StringEncoding {
	UTF16_ENCODING = -16, // not implemented, yet!
	UTF8_ENCODING = -8, // not implemented, yet!
	STRING_DECISION_ENCODING = 0,
	CHAR8_ENCODING = 8,
	CHAR16_ENCODING = 16,
	CHAR32_ENCODING = 32 // not implemented, yet!
};



extern BL_EXPORT StringEncoding defaultStringEncoding;


class BL_EXPORT AbstractStringImplementation {
public:

	struct BL_EXPORT Factory {

		virtual ~Factory();
		virtual AbstractStringImplementation* create(StringEncoding stringEncoding);
		virtual AbstractStringImplementation* create(StringEncoding stringEncoding, int length, bool emptyOptimization);
	};

	static Factory* getDefaultFactory();

	static Factory* getFactory();
	static void setFactory(Factory* newFactory);

	inline static AbstractStringImplementation* create(StringEncoding stringEncoding, int length, bool emptyOptimization = true)
	{
		return getFactory()->create(stringEncoding, length, emptyOptimization);
	}

	inline static AbstractStringImplementation* create(StringEncoding stringEncoding, bool emptyOptimization)
	{
		return getFactory()->create(stringEncoding, 0, emptyOptimization);
	}

	inline static AbstractStringImplementation* create(StringEncoding stringEncoding)
	{
		return getFactory()->create(stringEncoding);
	}

	inline static AbstractStringImplementation* create(int length)
	{
		return getFactory()->create(STRING_DECISION_ENCODING, length, true);
	}

	inline static AbstractStringImplementation* create()
	{
		return getFactory()->create(STRING_DECISION_ENCODING, 0, true);
	}


/*	inline static AbstractStringImplementation* create(int length = 0, StringEncoding stringEncoding = STRING_DECISION_ENCODING)
	{
		return getFactory()->create(length, stringEncoding);
	}*/

	virtual ~AbstractStringImplementation();
	
	virtual AbstractStringImplementation* clone(int position, int length) const = 0;

	inline AbstractStringImplementation* clone() const
	{
		return clone(0, getLength());
	}

	virtual StringEncoding getEncoding() const = 0;

	//virtual std::locale& getLocale() const = 0;

	virtual int getByteSize() const = 0;
	virtual int getCharacterByteSize() const = 0;

	virtual int getLength() const = 0;

	virtual void setLength(int newLength) = 0;
	virtual void insert(int position, int length) = 0;
	virtual void remove(int position, int length) = 0;

	virtual char8 getChar8(int position) const = 0;
	virtual char8 getLowerCaseChar8(int position) const = 0;
	virtual char8 getUpperCaseChar8(int position) const = 0;
	virtual void setChar(int position, char8 newChar) = 0;

	virtual char16 getChar16(int position) const = 0;
	virtual char16 getLowerCaseChar16(int position) const = 0;
	virtual char16 getUpperCaseChar16(int position) const = 0;
	virtual void setChar(int position, char16 newChar) = 0;

	virtual char32 getChar32(int position) const = 0;
	virtual char32 getLowerCaseChar32(int position) const = 0;
	virtual char32 getUpperCaseChar32(int position) const = 0;
	virtual void setChar(int position, char32 newChar) = 0;

	virtual void fill(char8 fillerChar, int position, int length) = 0;
	virtual void fill(char16 fillerChar, int position, int length) = 0;

	virtual void lowerCase(int position, int length) = 0;
	virtual void upperCase(int position, int length) = 0;

	virtual void copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length) = 0;

	virtual void copyFromCharArray(const char8 * source, int destStartPosition, int length) = 0;
	virtual void copyToCharArray(char8 * destination, int sourceStartPosition, int length) const = 0; // size+1 as length allowed -> copies terminating 0

	virtual void copyFromCharArray(const char16 * source, int destStartPosition, int length) = 0;
	virtual void copyToCharArray(char16 * destination, int sourceStartPosition, int length) const = 0; // size+1 as length allowed -> copies terminating 0

	virtual const void * getPointer() const = 0;

	virtual const char8 * getChar8Array() const = 0;
	virtual const char16 * getChar16Array() const = 0;

	virtual const char8 * getChar8CString() const = 0;
	virtual const char16 * getChar16CString() const = 0;

	virtual int hash(int position, int length) const = 0;
	
	virtual AbstractStringImplementation* getUnsharedInstance();
	virtual AbstractStringImplementation* getUnsharedInstance(int start, int length);

	inline AbstractStringImplementation* getUnsharedInstance(int length)
	{
		return getUnsharedInstance(0, length);
	}

	void addReference();
	void releaseReference();

protected:

	static Factory* factory;
	static Factory defaultFactory;

	int referenceCount;

	AbstractStringImplementation();

};



} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_AbstractStringImplementation_h
