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



Char8StringImplementation::Char8StringImplementation(int length)
	: bufferLength(length)
	, buffer(static_cast<char8 *>(malloc((length+1)*sizeof(char8))))
	, char16Buffer(NULL)
{
	BL_ASSERT(buffer != NULL);
	buffer[bufferLength] = 0;
}



Char8StringImplementation::~Char8StringImplementation()
{
	free(char16Buffer);
	free(buffer);
}



StringEncoding Char8StringImplementation::getEncoding() const
{
	return CHAR8_ENCODING;
}



AbstractStringImplementation* Char8StringImplementation::clone(int position, int length) const
{
	BL_ASSERT(position >= 0 && length >= 0);
	Char8StringImplementation* newClone = new Char8StringImplementation(length);
	newClone->copyFromCharArray(&buffer[position], 0, std::min(length, bufferLength));
	return newClone;
}


int Char8StringImplementation::getByteSize() const
{
	return bufferLength * sizeof(char8);
}



int Char8StringImplementation::getCharacterByteSize() const
{
	return 1;
}



int Char8StringImplementation::getLength() const
{
	return bufferLength;
}



void Char8StringImplementation::setLength(int newLength)
{
	BL_ASSERT(newLength >= 0);
	buffer = static_cast<char8 *>(realloc(buffer, (newLength+1)*sizeof(char8)));
	bufferLength = newLength;
	buffer[bufferLength] = 0;
}



void Char8StringImplementation::insert(int position, int length)
{
	BL_ASSERT(position >= 0 && position <= bufferLength && length >= 0);
	int tailLength = bufferLength - position;
	setLength(bufferLength + length);
	memmove(&buffer[position + length], &buffer[position], tailLength);
}



void Char8StringImplementation::remove(int position, int length)
{
	BL_ASSERT(position >= 0 && position < bufferLength && length >= 0 && bufferLength - length >= 0);
	int end = position + length;
	memmove(&buffer[position], &buffer[end], bufferLength - end);
	setLength(bufferLength - length);
}



char8 Char8StringImplementation::getChar8(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return buffer[position];
}



char8 Char8StringImplementation::getLowerCaseChar8(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return std::use_facet< std::ctype<char8> >(locale).tolower(buffer[position]);
}



char8 Char8StringImplementation::getUpperCaseChar8(int position) const
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	return std::use_facet< std::ctype<char8> >(locale).toupper(buffer[position]);
}



void Char8StringImplementation::setChar(int position, char8 newChar)
{
	BL_ASSERT(position >= 0 && position < bufferLength);
	buffer[position] = newChar;
}



char16 Char8StringImplementation::getChar16(int position) const
{
	return char2wchar(getChar8(position));
}



char16 Char8StringImplementation::getLowerCaseChar16(int position) const
{
	return std::use_facet< std::ctype<char16> >(locale).tolower(getChar16(position));
}



char16 Char8StringImplementation::getUpperCaseChar16(int position) const
{
	return std::use_facet< std::ctype<char16> >(locale).toupper(getChar16(position));
}



void Char8StringImplementation::setChar(int position, char16 newChar)
{
	setChar(position, wchar2char(newChar));
}



char32 Char8StringImplementation::getChar32(int position) const
{
	return getChar16(position);
}



char32 Char8StringImplementation::getLowerCaseChar32(int position) const
{
	return getLowerCaseChar16(position);
}



char32 Char8StringImplementation::getUpperCaseChar32(int position) const
{
	return getUpperCaseChar16(position);
}



void Char8StringImplementation::setChar(int position, char32 newChar)
{
	setChar(position, (char16)newChar);
}



void Char8StringImplementation::fill(char8 fillerChar, int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	memset(&buffer[position], fillerChar, length);
}



void Char8StringImplementation::fill(char16 fillerChar, int position, int length)
{
	fill(wchar2char(fillerChar), position, length);
}



void Char8StringImplementation::lowerCase(int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	std::use_facet< std::ctype<char8> >(locale).tolower(&buffer[position], &buffer[position+length]);
}



void Char8StringImplementation::upperCase(int position, int length)
{
	BL_ASSERT(position >= 0 && length >= 0 && position + length <= bufferLength);
	std::use_facet< std::ctype<char8> >(locale).toupper(&buffer[position], &buffer[position+length]);
}



void Char8StringImplementation::copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length)
{
	BL_ASSERT(sourcePosition >= 0 && sourcePosition + length <= source->getLength());
	BL_ASSERT(destPosition >= 0 && destPosition + length <= bufferLength);
	if (source->getEncoding() == CHAR16_ENCODING)
	{
		const char16 * sourceArray = source->getChar16Array();
		std::use_facet< std::ctype<char16> >(locale).narrow(&sourceArray[sourcePosition], &sourceArray[sourcePosition+length], narrowReplaceCharacter, &buffer[destPosition]);
	}
	else
	{
		BL_ASSERT(source->getEncoding() == CHAR8_ENCODING);
		memCopy(&buffer[destPosition], &source->getChar8Array()[sourcePosition], length);
	}
}



void Char8StringImplementation::copyFromCharArray(const char8 * source, int destStartPosition, int length)
{
	BL_ASSERT(destStartPosition >= 0 && length >= 0 && destStartPosition + length <= bufferLength);
	memCopy(&buffer[destStartPosition], &source[0], length);
}



void Char8StringImplementation::copyToCharArray(char8 * destination, int sourceStartPosition, int length) const
{
	 // bufferLength+1 as length allowed -> copies terminating 0
	BL_ASSERT(sourceStartPosition >= 0 && length >= 0 && sourceStartPosition + length <= bufferLength+1);
	memCopy(&destination[0], &buffer[sourceStartPosition], length);
}



void Char8StringImplementation::copyFromCharArray(const char16 * source, int destStartPosition, int length)
{
	BL_ASSERT(destStartPosition >= 0 && length >= 0 && destStartPosition + length <= bufferLength);
	std::use_facet< std::ctype<char16> >(locale).narrow(&source[0], &source[length], narrowReplaceCharacter, &buffer[destStartPosition]);
}



void Char8StringImplementation::copyToCharArray(char16 * destination, int sourceStartPosition, int length) const
{
	 // bufferLength+1 as length allowed -> copies terminating 0
	BL_ASSERT(sourceStartPosition >= 0 && length >= 0 && sourceStartPosition + length <= bufferLength+1);

	if (sourceStartPosition + length == bufferLength+1) // Workaround for: widen(0) != 0
	{
		std::use_facet< std::ctype<char16> >(locale).widen(&buffer[sourceStartPosition], &buffer[sourceStartPosition+length-1], &destination[0]);
		destination[length-1] = 0;
	}
	else
	{
		std::use_facet< std::ctype<char16> >(locale).widen(&buffer[sourceStartPosition], &buffer[sourceStartPosition+length], &destination[0]);
	}
}



const void * Char8StringImplementation::getPointer() const
{
	return buffer;
}



const char8 * Char8StringImplementation::getChar8Array() const
{
	return buffer;
}



const char16 * Char8StringImplementation::getChar16Array() const
{
	return getChar16CString();
}



const char8 * Char8StringImplementation::getChar8CString() const
{
	return buffer;
}



const char16 * Char8StringImplementation::getChar16CString() const
{
	const int size1 = bufferLength + 1;
	char16Buffer = static_cast<char16 *>(realloc(char16Buffer, size1*sizeof(char16)));
	copyToCharArray(char16Buffer, 0, size1);
	return char16Buffer;
}



int Char8StringImplementation::hash(int position, int length) const
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



} // namespace Strings
} // namespace BaseLib
