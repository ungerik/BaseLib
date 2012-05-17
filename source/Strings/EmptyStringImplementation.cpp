/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/String.h"
#include "BaseLib/Strings/EmptyStringImplementation.h"
#include "BaseLib/Strings/Char16StringImplementation.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Strings {


// Moved to BaseLib.cpp because of initialization order:
//const char8 * EmptyStringImplementation::EMPTY_CHAR8_CSTRING = {0};
//const char16 * EmptyStringImplementation::EMPTY_CHAR16_CSTRING = {0};
//
//EmptyStringImplementation EmptyStringImplementation::CHAR8_SINGLETON(CHAR8_ENCODING);
//EmptyStringImplementation EmptyStringImplementation::CHAR16_SINGLETON(CHAR16_ENCODING);



EmptyStringImplementation* EmptyStringImplementation::getChar8Instance()
{
	CHAR8_SINGLETON.addReference();
	return &CHAR8_SINGLETON;
}



EmptyStringImplementation* EmptyStringImplementation::getChar16Instance()
{
	CHAR16_SINGLETON.addReference();
	return &CHAR16_SINGLETON;
}



EmptyStringImplementation::EmptyStringImplementation(StringEncoding stringEncoding)
	: encoding(stringEncoding)
{
}



StringEncoding EmptyStringImplementation::getEncoding() const
{
	return encoding;
}



AbstractStringImplementation* EmptyStringImplementation::clone(int position, int length) const
{
	BL_ASSERT(position == 0 && length == 0);
	return new EmptyStringImplementation(encoding);
}


int EmptyStringImplementation::getByteSize() const
{
	return 0;
}



int EmptyStringImplementation::getCharacterByteSize() const
{
	return encoding == CHAR8_ENCODING ? 1 : 2;
}



int EmptyStringImplementation::getLength() const
{
	return 0;
}



void EmptyStringImplementation::setLength(int newLength)
{
	BL_ASSERT(newLength == 0);
}



void EmptyStringImplementation::insert(int position, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::remove(int position, int length)
{
	BL_ASSERT(length == 0);
}



char8 EmptyStringImplementation::getChar8(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char8 EmptyStringImplementation::getLowerCaseChar8(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char8 EmptyStringImplementation::getUpperCaseChar8(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



void EmptyStringImplementation::setChar(int position, char8 newChar)
{
	BL_ASSERT_NEVER_REACHED
}



char16 EmptyStringImplementation::getChar16(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char16 EmptyStringImplementation::getLowerCaseChar16(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char16 EmptyStringImplementation::getUpperCaseChar16(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



void EmptyStringImplementation::setChar(int position, char16 newChar)
{
	BL_ASSERT_NEVER_REACHED
}



char32 EmptyStringImplementation::getChar32(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char32 EmptyStringImplementation::getLowerCaseChar32(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



char32 EmptyStringImplementation::getUpperCaseChar32(int position) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



void EmptyStringImplementation::setChar(int position, char32 newChar)
{
	BL_ASSERT_NEVER_REACHED
}



void EmptyStringImplementation::fill(char8 fillerChar, int position, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::fill(char16 fillerChar, int position, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::lowerCase(int position, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::upperCase(int position, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::copyFromCharArray(const char8 * source, int destStartPosition, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::copyToCharArray(char8 * destination, int sourceStartPosition, int length) const
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::copyFromCharArray(const char16 * source, int destStartPosition, int length)
{
	BL_ASSERT(length == 0);
}



void EmptyStringImplementation::copyToCharArray(char16 * destination, int sourceStartPosition, int length) const
{
	BL_ASSERT(length == 0);
}



const void * EmptyStringImplementation::getPointer() const
{
	return EMPTY_CHAR16_CSTRING;
}



const char8 * EmptyStringImplementation::getChar8Array() const
{
	return EMPTY_CHAR8_CSTRING;
}



const char16 * EmptyStringImplementation::getChar16Array() const
{
	return EMPTY_CHAR16_CSTRING;
}



const char8 * EmptyStringImplementation::getChar8CString() const
{
	return EMPTY_CHAR8_CSTRING;
}



const char16 * EmptyStringImplementation::getChar16CString() const
{
	return EMPTY_CHAR16_CSTRING;
}



int EmptyStringImplementation::hash(int position, int length) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



AbstractStringImplementation* EmptyStringImplementation::getUnsharedInstance()
{
	return create(encoding, false);
}



AbstractStringImplementation* EmptyStringImplementation::getUnsharedInstance(int start, int length)
{
	return create(encoding, length, false);
}



} // namespace Strings
} // namespace BaseLib
