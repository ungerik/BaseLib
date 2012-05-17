/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/String.h"
#include "BaseLib/Strings/Char8StringImplementation.h"
#include "BaseLib/Strings/Char16StringImplementation.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Strings {



#define locale defaultLocale



Char16StringImplementation::Char16StringImplementation(int length/*, std::locale& newLocale*/)
	: bufferLength(length)
	, buffer(static_cast<char16 *>(malloc((length+1)*sizeof(char16))))
	, char8Buffer(NULL)
	//, locale(newLocale)
{
	BL_ASSERT(buffer != NULL);
	buffer[bufferLength] = 0;
}



Char16StringImplementation::~Char16StringImplementation()
{
	free(char8Buffer);
	free(buffer);
}



StringEncoding Char16StringImplementation::getEncoding() const
{
	return CHAR16_ENCODING;
}



AbstractStringImplementation* Char16StringImplementation::clone(int position, int length) const
{
	BL_ASSERT(position >= 0 && length >= 0);
	Char16StringImplementation* newClone = new Char16StringImplementation(length);
	newClone->copyFromCharArray(&buffer[position], 0, std::min(length, bufferLength));
	return newClone;
}


/*
std::locale& Char16StringImplementation::getLocale() const
{
	return locale;
}
*/

int Char16StringImplementation::getByteSize() const
{
	return bufferLength * sizeof(char16);
}



int Char16StringImplementation::getCharacterByteSize() const
{
	return 2;
}



int Char16StringImplementation::getLength() const
{
	return bufferLength;
}



void Char16StringImplementation::setLength(int newLength)
{
	BL_ASSERT(newLength >= 0);
	buffer = static_cast<char16 *>(realloc(buffer, (newLength+1)*sizeof(char16)));
	bufferLength = newLength;
	buffer[bufferLength] = 0;
}



void Char16StringImplementation::insert(int position, int length)
{
	BL_ASSERT(position >= 0 && position <= bufferLength && length >= 0);
	int tailLength = bufferLength - position;
	setLength(bufferLength + length);
	wmemmove(&buffer[position + length], &buffer[position], tailLength);
}



void Char16StringImplementation::remove(int position, int length)
{
	BL_ASSERT(position >= 0 && position < bufferLength && length >= 0 && bufferLength - length >= 0);
	int end = position + length;
	wmemmove(&buffer[position], &buffer[end], bufferLength - end);
	setLength(bufferLength - length);
}



char8 Char16StringImplementation::getChar8(int position) const
{
	return wchar2char(getChar16(position));
}



char8 Char16StringImplementation::getLowerCaseChar8(int position) const
{
	return std::use_facet< std::ctype<char8> >(locale).tolower(getChar8(position));
}



char8 Char16StringImplementation::getUpperCaseChar8(int position) const
{
	return std::use_facet< std::ctype<char8> >(locale).toupper(getChar8(position));
}



void Char16StringImplementation::setChar(int position, char8 newChar)
{
	setChar(position, char2wchar(newChar));
}



char16 Char16StringImplementation::getChar16(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return buffer[position];
}



char16 Char16StringImplementation::getLowerCaseChar16(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return std::use_facet< std::ctype<char16> >(locale).tolower(buffer[position]);
}



char16 Char16StringImplementation::getUpperCaseChar16(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return std::use_facet< std::ctype<char16> >(locale).toupper(buffer[position]);
}



void Char16StringImplementation::setChar(int position, char16 newChar)
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	buffer[position] = newChar;
}



char32 Char16StringImplementation::getChar32(int position) const
{
	return getChar16(position);
}



char32 Char16StringImplementation::getLowerCaseChar32(int position) const
{
	return getLowerCaseChar16(position);
}



char32 Char16StringImplementation::getUpperCaseChar32(int position) const
{
	return getUpperCaseChar16(position);
}



void Char16StringImplementation::setChar(int position, char32 newChar)
{
	setChar(position, (char16)newChar);
}



void Char16StringImplementation::fill(char8 fillerChar, int position, int length)
{
	fill(char2wchar(fillerChar), position, length);
}



void Char16StringImplementation::fill(char16 fillerChar, int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	wmemset(&buffer[position], fillerChar, length);
}



void Char16StringImplementation::lowerCase(int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	std::use_facet< std::ctype<char16> >(locale).tolower(&buffer[position], &buffer[position+length]);
}



void Char16StringImplementation::upperCase(int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	std::use_facet< std::ctype<char16> >(locale).toupper(&buffer[position], &buffer[position+length]);
}



void Char16StringImplementation::copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length)
{
	BL_ASSERT(sourcePosition >= 0 && sourcePosition + length <= source->getLength());
	BL_ASSERT(destPosition >= 0 && destPosition + length <= bufferLength);
	if (source->getEncoding() == CHAR16_ENCODING)
	{
		memCopy16Bit(&buffer[destPosition], &source->getChar16Array()[sourcePosition], length);
	}
	else
	{
		BL_ASSERT(source->getEncoding() == CHAR8_ENCODING);
		const char8 * sourceArray = source->getChar8Array();
		std::use_facet< std::ctype<char16> >(locale).widen(&sourceArray[sourcePosition], &sourceArray[sourcePosition+length], &buffer[destPosition]);
	}
}



void Char16StringImplementation::copyFromCharArray(const char8 * source, int destStartPosition, int length)
{
	BL_ASSERT(destStartPosition >= 0 && length >= 0 && destStartPosition + length <= bufferLength);
	std::use_facet< std::ctype<char16> >(locale).widen(&source[0], &source[length], &buffer[destStartPosition]);
}



void Char16StringImplementation::copyToCharArray(char8 * destination, int sourceStartPosition, int length) const
{
	 // bufferLength+1 as length allowed -> copies terminating 0
	BL_ASSERT(sourceStartPosition >= 0 && length >= 0 && sourceStartPosition + length <= bufferLength+1);
	std::use_facet< std::ctype<char16> >(locale).narrow(&buffer[sourceStartPosition], &buffer[sourceStartPosition+length], narrowReplaceCharacter, &destination[0]);
}



void Char16StringImplementation::copyFromCharArray(const char16 * source, int destStartPosition, int length)
{
	BL_ASSERT(destStartPosition >= 0 && length >= 0 && destStartPosition + length <= bufferLength);
	memCopy16Bit(&buffer[destStartPosition], &source[0], length);
}



void Char16StringImplementation::copyToCharArray(char16 * destination, int sourceStartPosition, int length) const
{
	 // bufferLength+1 as length allowed -> copies terminating 0
	BL_ASSERT(sourceStartPosition >= 0 && length >= 0 && sourceStartPosition + length <= bufferLength+1);
	memCopy16Bit(&destination[0], &buffer[sourceStartPosition], length);
}



const void * Char16StringImplementation::getPointer() const
{
	return buffer;
}



const char8 * Char16StringImplementation::getChar8Array() const
{
	return getChar8CString();
}



const char16 * Char16StringImplementation::getChar16Array() const
{
	return buffer;
}



const char8 * Char16StringImplementation::getChar8CString() const
{
	const int size1 = bufferLength + 1;
	char8Buffer = static_cast<char8 *>(realloc(char8Buffer, size1*sizeof(char8)));
	copyToCharArray(char8Buffer, 0, size1);
	return char8Buffer;
}



const char16 * Char16StringImplementation::getChar16CString() const
{
	return buffer;
}



int Char16StringImplementation::hash(int position, int length) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



} // namespace Strings
} // namespace BaseLib
