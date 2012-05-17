/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/String.h"
#include "BaseLib/Console.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Utilities/Sorting.h"
#include "BaseLib/Containers/Array.h"
#include "BaseLib/Math.h"
#include <boost/regex.hpp>



namespace BaseLib {
namespace Strings {



using namespace BaseLib::Console;
using namespace BaseLib::Math;
using BaseLib::Functors::Enumerator;



//BL_DEFINE_REFLECTION_BASE_CLASS(String)
//{
//	//registerProperty("value", &Bool::getValue, &Bool::setValue);
//	registerProperty("length", &Bool::getLength, &Bool::setLength);
//}



void String::setDefaultEncoding(StringEncoding newDefaultEncoding)
{
	if (newDefaultEncoding != STRING_DECISION_ENCODING)
	{
		defaultEncoding = newDefaultEncoding;
	}
}



bool String::isBin() const
{
	const int length = getLength();
	for (int i = 0; i < length; ++i)
	{
		if (isBinNumber(getChar8(i)) == false) return false;
	}
	return true;
}



bool String::isDec() const
{
	const int length = getLength();
	for (int i = 0; i < length; ++i)
	{
		if (isNumber(getChar8(i)) == false) return false;
	}
	return true;
}



bool String::isFloat() const
{
	const int length = getLength();
	for (int i = 0; i < length; ++i)
	{
		if (isFloatNumber(getChar8(i)) == false) return false;
	}
	return true;
}



bool String::isHex() const
{
	const int length = getLength();
	for (int i = 0; i < length; ++i)
	{
		if (isHexNumber(getChar8(i)) == false) return false;
	}
	return true;
}



void String::hexToBinary(void* resultBuffer, bool rightToLeft, int position, int length) const
{
	if (position == END) return;
	if (length == END) length = getLength() - position;
	const int halfLength = length / 2;

	if (rightToLeft == true)
	{
		const int rightIndex = length - 1;
		for (int i = rightIndex; i >= 0; --i)
		{
			const uint8 value = hexChar2Number(getChar8(position + i));
			const int halfByte = rightIndex - i;
			if (isEven(halfByte) == true)
			{
				memoryAs<uint8>(resultBuffer, halfByte / 2) = value;
			}
			else
			{
				memoryAs<uint8>(resultBuffer, halfByte / 2) |= value << 4;
			}
		}
	}
	else
	{
		for (int i = 0; i < length; ++i)
		{
			const uint8 value = hexChar2Number(getChar8(position + i));
			if (isEven(i) == true)
			{
				memoryAs<uint8>(resultBuffer, i / 2) = value << 4;
			}
			else
			{
				memoryAs<uint8>(resultBuffer, i / 2) |= value;
			}
		}
	}
}



void String::base64ToBinary(void* resultBuffer, int position, int length) const
{
	BL_ASSERT_NEVER_REACHED
}



void String::binNumberToBinary(void* resultBuffer, bool rightToLeft, int position, int length) const
{
	if (length == END) length = getLength();
	length -= position;

	int shift = 0;
	if (rightToLeft == true)
	{
		BL_ASSERT_NEVER_REACHED
		/*
		for (int i = 0; i < length; ++i, ++shift)
		{

			shift &= 7;
			uint8 value = binChar2Number(getChar8(i)) << shift;
			if (shift == 0)
			{
				memoryAs<uint8>(resultBuffer, i / 8) = value;
			}
			else
			{
				memoryAs<uint8>(resultBuffer, i / 8) |= value;
			}
		}
		*/
	}
	else
	{
		for (int i = 0; i < length; ++i, ++shift)
		{
			shift &= 7;
			const uint8 value = binChar2Number(getChar8(position + i)) << shift;
			if (shift == 0)
			{
				memoryAs<uint8>(resultBuffer, i / 8) = value;
			}
			else
			{
				memoryAs<uint8>(resultBuffer, i / 8) |= value;
			}
		}
	}
}



String String::binaryToHex(const void* sourceBuffer, int length, bool rightToLeft, StringEncoding stringEncoding)
{
/*
String::String(const void* binaryData, int byteCount, bool rightToLeft, AbstractStringImplementation* stringImplementation)
  : implementation(stringImplementation)
{
	implementation->setLength(byteCount * 2);
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		implementation->setChar(i*2, number2HexCharW(byte & 0x0F));
		implementation->setChar(i*2+1,number2HexCharW(byte >> 4));
	}
}
*/

	BL_ASSERT_NEVER_REACHED
	//implementation->setLength(length * 2);
	return Empty();
}



String String::binaryToBase64(const void* sourceBuffer, int length, StringEncoding stringEncoding)
{
	BL_ASSERT_NEVER_REACHED
	//implementation->setLength(length * 4 / 3);
	return Empty();
}



String String::binaryToBinNumber(const void* sourceBuffer, int length, StringEncoding stringEncoding)
{
	BL_ASSERT_NEVER_REACHED
	//implementation->setLength(length * 8);
	return Empty();
}



String& String::insert(String stringToInsert, int position, int count)
{
	BL_ASSERT(count >= 0);
	if (count > 0 && position != END)
	{
		const int length = stringToInsert.getLength();
		insert(position, length*count);
		for (int i = 0; i < count; ++i)
		{
			copyFromString(stringToInsert, 0, position, length);
			position += count;
		}
	}
	return *this;
}



String& String::insert(char8 charToInsert, int position, int count)
{
	BL_ASSERT(count >= 0);
	if (count > 0 && position != END)
	{
		getUnsharedImplementation();
		insert(position, count);
		return fill(charToInsert, position, count);
	}
	else
	{
		return *this;
	}
}



String& String::insert(char16 charToInsert, int position, int count)
{
	BL_ASSERT(count >= 0);
	if (count > 0 && position != END)
	{
		getUnsharedImplementation();
		insert(position, count);
		return fill(charToInsert, position, count);
	}
	else
	{
		return *this;
	}
}



String& String::insert(const Char& charToInsert, int position, int count)
{
	BL_ASSERT(count >= 0);
	if (count > 0 && position != END)
	{
		getUnsharedImplementation();
		insert(position, count);
		return fill(charToInsert, position, count);
	}
	else
	{
		return *this;
	}
}



String& String::insert(const ConstChar& charToInsert, int position, int count)
{
	BL_ASSERT(count >= 0);
	if (count > 0 && position != END)
	{
		getUnsharedImplementation();
		insert(position, count);
		return fill(charToInsert, position, count);
	}
	else
	{
		return *this;
	}
}



String& String::fill(const Char& fillerChar, int position, int length)
{
	if (getEncoding() == CHAR8_ENCODING)
	{
		return fill(fillerChar.operator char8(), position, length);
	}
	else
	{
		return fill(fillerChar.operator char16(), position, length);
	}
}



String& String::fill(const ConstChar& fillerChar, int position, int length)
{
	if (getEncoding() == CHAR8_ENCODING)
	{
		return fill(fillerChar.operator char8(), position, length);
	}
	else
	{
		return fill(fillerChar.operator char16(), position, length);
	}
}



void String::setImplementation(AbstractStringImplementation* newImplementation, bool releaseOldImplementation)
{
	BL_ASSERT(newImplementation != NULL);
	if (releaseOldImplementation == true)
	{
		implementation->releaseReference();
	}
	implementation = newImplementation;
	implementation->addReference();
}



String& String::append(char8 character, int count)
{
	if (count > 0)
	{
		const int length = getLength();
		getUnsharedImplementation(length + count);
		fill(character, length, count);
	}
	return *this;
}



String& String::append(char16 character, int count)
{
	if (count > 0)
	{
		const int length = getLength();
		getUnsharedImplementation(length + count);
		fill(character, length, count);
	}
	return *this;
}



String& String::append(const String& string, int count)
{
	if (count > 0)
	{
		const int leftSize = getLength();
		const int rightSize = string.getLength();
		getUnsharedImplementation(leftSize + rightSize*count);

		int position = leftSize;
		for (int i = 0; i < count; ++i)
		{
			copyFromString(string, 0, position, rightSize);
			position += rightSize;
		}
	}
	return *this;
}



String String::lowerCaseSubString(int position, int length) const
{	
	if (position == END) return Empty();
	if (length == END) length = getLength() - position;
	AbstractStringImplementation* newImplementation = implementation->clone(position, length);
	newImplementation->lowerCase(0, length);
	return String(newImplementation);
}



String String::upperCaseSubString(int position, int length) const
{
	if (position == END) return Empty();
	if (length == END) length = getLength() - position;
	AbstractStringImplementation* newImplementation = implementation->clone(position, length);
	newImplementation->upperCase(0, length);
	return String(newImplementation);
}



void String::replace(int position, int length, const String& replaceString)
{
	if (position == END) return;
	BL_ASSERT(length > 0);

	const int replaceLength = replaceString.getLength();

	if (replaceLength < length)
	{
		remove(position, length - replaceLength);
	}
	else if (replaceLength > length)
	{
		insert(position, replaceLength - length);
	}

	copyFromString(replaceString, 0, position, replaceLength);
}



int String::searchAndReplace(const String& searchString, const String& replaceString)
{
	const int searchStringLength = searchString.getLength();
	const int replaceStringLength = replaceString.getLength();

	BL_ASSERT(searchStringLength > 0);

	int replacements = 0;
	int position = 0;

	if (replaceStringLength < searchStringLength)
	{
		while ((position = findFirst(searchString, position)) != END)
		{
			remove(position, searchStringLength - replaceStringLength);
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}
	else if (replaceStringLength > searchStringLength)
	{
		while ((position = findFirst(searchString, position)) != END)
		{
			insert(position, replaceStringLength - searchStringLength);
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}
	else
	{
		while ((position = findFirst(searchString, position)) != END)
		{
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}

	return replacements;
}



int String::searchAndReplaceCaseInsensitive(const String& searchString, const String& replaceString)
{
	const int searchStringLength = searchString.getLength();
	const int replaceStringLength = replaceString.getLength();

	BL_ASSERT(searchStringLength > 0);

	int replacements = 0;
	int position = 0;

	if (replaceStringLength < searchStringLength)
	{
		while ((position = findFirstCaseInsensitive(searchString, position)) != END)
		{
			remove(position, replaceStringLength - searchStringLength);
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}
	else if (replaceStringLength > searchStringLength)
	{
		while ((position = findFirstCaseInsensitive(searchString, position)) != END)
		{
			insert(position, searchStringLength - replaceStringLength);
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}
	else
	{
		while ((position = findFirstCaseInsensitive(searchString, position)) != END)
		{
			copyFromString(replaceString, 0, position, replaceStringLength);
			position += replaceStringLength;
			++replacements;
		}
	}

	return replacements;
}



int String::searchAndRemove(const String& searchString)
{
	const int searchStringLength = searchString.getLength();

	BL_ASSERT(searchStringLength > 0);

	int removes = 0;
	int position = 0;

	while ((position = findFirst(searchString, position)) != END)
	{
		remove(position, searchStringLength);
		++removes;
	}

	return removes;
}



int String::searchAndRemoveCaseInsensitive(const String& searchString)
{
	const int searchStringLength = searchString.getLength();

	BL_ASSERT(searchStringLength > 0);

	int removes = 0;
	int position = 0;

	while ((position = findFirstCaseInsensitive(searchString, position)) != END)
	{
		remove(position, searchStringLength);
		++removes;
	}

	return removes;
}



int String::findFirst(char8 character, int position, int length) const
{
	if (position == END) return END;

	if (getEncoding() == CHAR16_ENCODING)
	{
		return findFirst(char2wchar(character), position, length);
	}

	if (length == END) length = getLength() - position;
	for (int endIndex = position + length; position < endIndex; ++position)
	{
		if (getChar8(position) == character) return position;
	}
	return END;
}



int String::findFirst(char16 character, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;
	for (int endIndex = position + length; position < endIndex; ++position)
	{
		if (getChar16(position) == character) return position;
	}
	return END;
}



int String::findFirst(const String& findString, int position, int length) const
{
	if (position == END) return END;

	const int findStringSize = findString.getLength();
	if (findStringSize == 1) return findFirst(findString[0], position, length);

	const int searchStringSize = getLength();
	if (length == END) length = searchStringSize - position;

	int lastPosition = position;
	if (findStringSize <= length)
	{
		if (getEncoding() == CHAR8_ENCODING && findString.getEncoding() == CHAR8_ENCODING)
		{
			int searchIndex = END;
			bool found = false;

			while (found == false)
			{
				length = length - (position - lastPosition);
				lastPosition = position;

				searchIndex = findFirst(findString[0], position, length);
				if (searchIndex == END)
					return END;

				found = true;
				for (int i = 1; i < findStringSize && searchIndex + i < searchStringSize; ++i)
				{
					if (getChar8(searchIndex + i) != findString.getChar8(i))
					{
						found = false;
						position = searchIndex + 1;
						break;
					}
				}
			}

			if (found == true)
			{
				return searchIndex;
			}
		}
		else
		{
			int searchIndex = END;
			bool found = false;

			while (found == false)
			{
				length = searchStringSize - position;

				searchIndex = findFirst(findString[0], position, length);
				if (searchIndex == END)
					return END;

				found = true;
				for (int i = 1; i < findStringSize && searchIndex + i < searchStringSize; ++i)
				{
					if (getChar16(searchIndex + i) != findString.getChar16(i))
					{
						found = false;
						position = searchIndex + 1;
						break;
					}
				}
			}

			if (found == true)
			{
				return searchIndex;
			}
		}
	}
	return END;
}



int String::findFirstCaseInsensitive(char8 character, int position, int length) const
{
	if (position == END) return END;

	if (getEncoding() == CHAR16_ENCODING)
	{
		return findFirstCaseInsensitive(char2wchar(character), position, length);
	}

	character = ::BaseLib::Strings::lowerCase(character);
	if (length == END) length = getLength() - position;
	for (int endIndex = position + length; position < endIndex; ++position)
	{
		if (getLowerCaseChar8(position) == character) return position;
	}
	return END;
}



int String::findFirstCaseInsensitive(char16 character, int position, int length) const
{
	if (position == END) return END;

	character = ::BaseLib::Strings::lowerCase(character);
	if (length == END) length = getLength() - position;
	for (int endIndex = position + length; position < endIndex; ++position)
	{
		if (getLowerCaseChar16(position) == character) return position;
	}
	return END;
}



int String::findFirstCaseInsensitive(const String& findString, int position, int length) const
{
	if (position == END) return END;

	const int findStringSize = findString.getLength();
	if (findStringSize == 1) return findFirstCaseInsensitive(findString[0], position, length);

	const int searchStringSize = getLength();
	if (length == END) length = searchStringSize - position;

	if (findStringSize <= length)
	{
		int searchIndex = findFirstCaseInsensitive(findString[0], position, length);
		if (searchIndex != END)
		{
			if (getEncoding() == CHAR8_ENCODING && findString.getEncoding() == CHAR8_ENCODING)
			{
				for (int i = 1; i < findStringSize && searchIndex + i < searchStringSize; ++i)
				{
					if (getLowerCaseChar8(searchIndex + i) != findString.getLowerCaseChar8(i)) return END;
				}
			}
			else
			{
				for (int i = 1; i < findStringSize && searchIndex + i < searchStringSize; ++i)
				{
					if (getLowerCaseChar16(searchIndex + i) != findString.getLowerCaseChar16(i)) return END;
				}
			}
			return searchIndex;
		}
	}
	return END;
}



int String::findLast(char8 character, int position, int length) const
{
	if (position == END) return END;

	if (getEncoding() == CHAR16_ENCODING)
	{
		return findLast(char2wchar(character), position, length);
	}
	else
	{
		if (length == END) length = getLength() - position;
		for (int i = position + length - 1; i >= position; --i)
		{
			if (getChar8(i) == character) return i;
		}
		return END;
	}
}



int String::findLast(char16 character, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;
	for (int i = position + length - 1; i >= position; --i)
	{
		if (getChar8(i) == character) return i;
	}
	return END;
}



int String::findLast(const String& findString, int position, int length) const
{
	if (position == END) return END;

	const int findStringSize = findString.getLength();
	if (findStringSize == 1) return findLast(findString[0], position, length);

	const int searchStringSize = getLength();
	if (length == END) length = searchStringSize - position;

	if (findStringSize <= length)
	{
		int searchIndex = findLast(findString[findStringSize-1], position, length);
		if (searchIndex != END)
		{
			if (getEncoding() == CHAR8_ENCODING && findString.getEncoding() == CHAR8_ENCODING)
			{
				for (int i = findStringSize-2; i >= 0 && searchIndex - i >= 0; --i)
				{
					if (getChar8(searchIndex - i) != findString.getChar8(findStringSize-1 - i)) return END;
				}
			}
			else
			{
				for (int i = findStringSize-2; i >= 0 && searchIndex - i >= 0; --i)
				{
					if (getChar16(searchIndex - i) != findString.getChar16(findStringSize-1 - i)) return END;
				}
			}
			return searchIndex - (findStringSize-1);
		}
	}
	return END;
}



int String::findLastCaseInsensitive(char8 character, int position, int length) const
{
	if (position == END) return END;

	if (getEncoding() == CHAR16_ENCODING)
	{
		return findLastCaseInsensitive(char2wchar(character), position, length);
	}

	character = ::BaseLib::Strings::lowerCase(character);
	if (length == END) length = getLength() - position;
	for (int i = position + length - 1; i >= position; --i)
	{
		if (getLowerCaseChar8(i) == character) return i;
	}
	return END;
}



int String::findLastCaseInsensitive(char16 character, int position, int length) const
{
	if (position == END) return END;

	character = ::BaseLib::Strings::lowerCase(character);
	if (length == END) length = getLength() - position;
	for (int i = position + length - 1; i >= position; --i)
	{
		if (getLowerCaseChar16(i) == character) return i;
	}
	return END;
}



int String::findLastCaseInsensitive(const String& findString, int position, int length) const
{
	if (position == END) return END;

	const int findStringSize = findString.getLength();
	if (findStringSize == 1) return findLastCaseInsensitive(findString[0], position, length);

	const int searchStringSize = getLength();
	if (length == END) length = searchStringSize - position;

	if (findStringSize <= length)
	{
		int searchIndex = findLastCaseInsensitive(findString[findStringSize-1], position, length);
		if (searchIndex != END)
		{
			for (int i = findStringSize-2; i >= 0 && searchIndex - i >= 0; --i)
			{
				if (getLowerCaseChar16(searchIndex - i) != findString.getLowerCaseChar16(findStringSize-1 - i)) return END;
			}
			return searchIndex - (findStringSize-1);
		}
	}
	return END;
}



int String::findFirstOf(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	if (findCharsCount <= getLength())
	{
		for (int end = position + length; position < end; ++position)
		{
			const ConstChar searchChar = (*this)[position];
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars[i]) return position;
			}
		}
	}
	else
	{
		for(int i = 0; i < findCharsCount; ++i)
		{
			const ConstChar findChar = findChars[i];
			for (int findIndex = position; findIndex < position + length; ++findIndex)
			{
				if (findChar == (*this)[findIndex]) return findIndex;
			}
		}
	}

	return END;
}



int String::findFirstNotOf(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	int findCharsCount = findChars.getLength();
	{
		for (int end = position + length; position < end; ++position)
		{
			const ConstChar searchChar = (*this)[position];
			bool found = false;
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars[i])
				{
					found = true;
					break;
				}				
			}
			if (found == false) return position;
		}
	}

	return END;
}



int String::findLastOf(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	if (findCharsCount <= getLength())
	{
		for (int findIndex = position + length-1; findIndex >= position; --findIndex)
		{
			const ConstChar searchChar = (*this)[findIndex];
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars[i]) return findIndex;
			}
		}
	}
	else
	{
		for(int i = 0; i < findCharsCount; ++i)
		{
			const ConstChar findChar = findChars[i];
			for (int findIndex = position + length-1; findIndex >= position; --findIndex)
			{
				if (findChar == (*this)[findIndex]) return findIndex;
			}
		}
	}

	return END;
}



int String::findLastNotOf(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	int findCharsCount = findChars.getLength();
	{
		for (int findIndex = position + length-1; findIndex >= position; --findIndex)
		{
			const ConstChar searchChar = (*this)[findIndex];
			bool found = false;
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars[i])
				{
					found = true;
					break;
				}				
			}
			if (found == false) return findIndex;
		}
	}

	return END;
}



int String::findFirstOfCaseInsensitive(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	if (findCharsCount <= getLength())
	{
		for (int end = position + length; position < end; ++position)
		{
			const char16 searchChar = getLowerCaseChar16(position);
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars.getLowerCaseChar16(i)) return position;
			}
		}
	}
	else
	{
		for(int i = 0; i < findCharsCount; ++i)
		{
			const char16 findChar = findChars.getLowerCaseChar16(i);
			for (int findIndex = position; findIndex < position + length; ++findIndex)
			{
				if (findChar == getLowerCaseChar16(findIndex)) return findIndex;
			}
		}
	}

	return END;
}



int String::findFirstNotOfCaseInsensitive(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	{
		for (int end = position + length; position < end; ++position)
		{
			const char16 searchChar = getLowerCaseChar16(position);
			bool found = false;
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars.getLowerCaseChar16(i))
				{
					found = true;
					break;
				}				
			}
			if (found == false) return position;
		}
	}

	return END;
}



int String::findLastOfCaseInsensitive(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	if (findCharsCount <= getLength())
	{
		for (int findIndex = position + length-1; findIndex >= position; --findIndex)
		{
			const char16 searchChar = getLowerCaseChar16(findIndex);
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars.getLowerCaseChar16(i)) return findIndex;
			}
		}
	}
	else
	{
		for(int i = 0; i < findCharsCount; ++i)
		{
			const char16 findChar = findChars.getLowerCaseChar16(i);
			for (int findIndex = position + length-1; findIndex >= position; --findIndex)
			{
				if (findChar == getLowerCaseChar16(findIndex)) return findIndex;
			}
		}
	}

	return END;
}



int String::findLastNotOfCaseInsensitive(const String& findChars, int position, int length) const
{
	if (position == END) return END;

	if (length == END) length = getLength() - position;

	const int findCharsCount = findChars.getLength();
	{
		for (int findIndex = position + length-1; findIndex >= position; --findIndex)
		{
			const ConstChar searchChar = (*this)[findIndex];
			bool found = false;
			for(int i = 0; i < findCharsCount; ++i)
			{
				if (searchChar == findChars[i])
				{
					found = true;
					break;
				}				
			}
			if (found == false) return findIndex;
		}
	}

	return END;
}



String& String::trimFrontAndTail(const String& charsToTrim)
{
	const int frontChars = findFirstNotOf(charsToTrim);
	if (frontChars != END)
	{
		return trimFrontAndTailBy(frontChars, getLength() - (findLastNotOf(charsToTrim)+1));
	}
	else
	{
		setLength(0);
		return *this;
	}
}



String& String::trimFrontAndTail(const String& charsToTrimAtFront, const String& charsToTrimAtTail)
{
	const int frontChars = findFirstNotOf(charsToTrimAtFront);
	const int tailChars = findLastNotOf(charsToTrimAtTail);
	if (frontChars != END || tailChars != END)
	{
		return trimFrontAndTailBy(frontChars, getLength() - (tailChars+1));
	}
	else
	{
		setLength(0);
		return *this;
	}
}



String& String::trimFront(const String& charsToTrim)
{
	int frontChars = findFirstNotOf(charsToTrim);
	if (frontChars == END) frontChars = getLength();
	return trimFrontBy(frontChars);
}



String& String::trimTail(const String& charsToTrim)
{
	setLength(findLastNotOf(charsToTrim)+1);
	return *this;
}



String& String::trimFrontAndTailCaseInsensitive(const String& charsToTrim)
{
	const int frontChars = findFirstNotOf(charsToTrim);
	if (frontChars != END)
	{
		return trimFrontAndTailBy(frontChars, getLength()-1 - findLastNotOf(charsToTrim));
	}
	else
	{
		setLength(0);
		return *this;
	}
}



String& String::trimFrontAndTailCaseInsensitive(const String& charsToTrimAtFront, const String& charsToTrimAtTail)
{
	const int frontChars = findFirstNotOf(charsToTrimAtFront);
	if (frontChars != END)
	{
		return trimFrontAndTailBy(frontChars, getLength()-1 - findLastNotOf(charsToTrimAtTail));
	}
	else
	{
		setLength(0);
		return *this;
	}
}



String& String::trimFrontCaseInsensitive(const String& charsToTrim)
{
	int frontChars = findFirstNotOf(charsToTrim);
	if (frontChars == END) frontChars = getLength();
	return trimFrontBy(frontChars);
}



String& String::trimTailCaseInsensitive(const String& charsToTrim)
{
	return setLength(findLastNotOf(charsToTrim)+1);
}



String& String::trimFrontAndTailBy(int frontChars, int tailChars)
{
	BL_ASSERT(frontChars >= 0 && tailChars >= 0);
	trimTailBy(tailChars);
	trimFrontBy(frontChars);
	return *this;
}



bool String::equalsCaseInsensitive(const String& compareString) const
{
	//return lowerCaseString() == string.lowerCaseString();

	const int size = getLength();
	if (size != compareString.getLength()) return false;

	if (getEncoding() == CHAR16_ENCODING || compareString.getEncoding() == CHAR16_ENCODING)
	{
		for (int i = 0; i < size; ++i)
		{
			if (getLowerCaseChar16(i) != compareString.getLowerCaseChar16(i)) return false;
		}
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			if (getLowerCaseChar8(i) != compareString.getLowerCaseChar8(i)) return false;
		}
	}
	return true;
}



bool String::beginsWith(const String& compareString, int compareStringPosition, int compareStringLength) const
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	
	if (compareStringLength > getLength()) return false;

	if (getEncoding() == CHAR8_ENCODING && compareString.getEncoding() == CHAR8_ENCODING)
	{
		for (int i = 0; i < compareStringLength; ++i)
		{
			if (getChar8(i) != compareString.getChar8(i + compareStringPosition)) return false;
		}
	}
	else
	{
		for (int i = 0; i < compareStringLength; ++i)
		{
			if (getChar16(i) != compareString.getChar16(i + compareStringPosition)) return false;
		}
	}
	return true;
}



bool String::endsWith(const String& compareString, int compareStringPosition, int compareStringLength) const
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	
	const int length = getLength();
	const int deltaLength = length - compareStringLength;
	if (deltaLength < 0) return false;

	const int compareStringDelta = compareStringPosition - deltaLength;

	if (getEncoding() == CHAR8_ENCODING && compareString.getEncoding() == CHAR8_ENCODING)
	{
		for (int i = deltaLength; i < length; ++i)
		{
			if (getChar8(i) != compareString.getChar8(i + compareStringDelta)) return false;
		}
	}
	else
	{
		for (int i = deltaLength; i < length; ++i)
		{
			if (getChar16(i) != compareString.getChar16(i + compareStringDelta)) return false;
		}
	}
	return true;
}



bool String::beginsCaseInsensitiveWith(const String& compareString, int compareStringPosition, int compareStringLength) const
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	
	if (compareStringLength > getLength()) return false;

	if (getEncoding() == CHAR8_ENCODING && compareString.getEncoding() == CHAR8_ENCODING)
	{
		for (int i = 0; i < compareStringLength; ++i)
		{
			if (getLowerCaseChar8(i) != compareString.getLowerCaseChar8(i + compareStringPosition)) return false;
		}
	}
	else
	{
		for (int i = 0; i < compareStringLength; ++i)
		{
			if (getLowerCaseChar16(i) != compareString.getLowerCaseChar16(i + compareStringPosition)) return false;
		}
	}
	return true;
}



bool String::endsCaseInsensitiveWith(const String& compareString, int compareStringPosition, int compareStringLength) const
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	
	const int length = getLength();
	const int deltaLength = length - compareStringLength;
	if (deltaLength < 0) return false;

	const int compareStringDelta = compareStringPosition - deltaLength;

	if (getEncoding() == CHAR8_ENCODING && compareString.getEncoding() == CHAR8_ENCODING)
	{
		for (int i = deltaLength; i < length; ++i)
		{
			if (getLowerCaseChar8(i) != compareString.getLowerCaseChar8(i + compareStringDelta)) return false;
		}
	}
	else
	{
		for (int i = deltaLength; i < length; ++i)
		{
			if (getLowerCaseChar16(i) != compareString.getLowerCaseChar16(i + compareStringDelta)) return false;
		}
	}
	return true;
}



void String::ensureBeginsWith(const String& compareString, int compareStringPosition, int compareStringLength)
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	const int originalCompareStringPosition = compareStringPosition;
	while (beginsWith(compareString, compareStringPosition, compareStringLength) == false && compareStringLength > 0)
	{
		++compareStringPosition;
		--compareStringLength;
		if (beginsWith(compareString, compareStringPosition, compareStringLength) == true)
		{
			insert(compareString.subString(originalCompareStringPosition, compareStringPosition - originalCompareStringPosition));
			return;
		}
	}
}



void String::ensureEndsWith(const String& compareString, int compareStringPosition, int compareStringLength)
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	const int originalCompareStringPosition = compareStringPosition;
	const int originalCompareStringLength = compareStringLength;
	while (endsWith(compareString, compareStringPosition, compareStringLength) == false && compareStringLength > 0)
	{
		--compareStringLength;
		if (endsWith(compareString, compareStringPosition, compareStringLength) == true)
		{
			append(compareString.subString(originalCompareStringPosition + compareStringLength, originalCompareStringLength - compareStringLength));
			return;
		}
	}
}



void String::ensureBeginsCaseInsensitiveWith(const String& compareString, int compareStringPosition, int compareStringLength)
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	const int originalCompareStringPosition = compareStringPosition;
	while (beginsCaseInsensitiveWith(compareString, compareStringPosition, compareStringLength) == false && compareStringLength > 0)
	{
		++compareStringPosition;
		--compareStringLength;
		if (beginsCaseInsensitiveWith(compareString, compareStringPosition, compareStringLength) == true)
		{
			insert(compareString.subString(originalCompareStringPosition, compareStringPosition - originalCompareStringPosition));
			return;
		}
	}
}



void String::ensureEndsCaseInsensitiveWith(const String& compareString, int compareStringPosition, int compareStringLength)
{
	if (compareStringLength == END)
	{
		compareStringLength = compareString.getLength() - compareStringPosition;
	}
	const int originalCompareStringPosition = compareStringPosition;
	const int originalCompareStringLength = compareStringLength;
	while (endsCaseInsensitiveWith(compareString, compareStringPosition, compareStringLength) == false && compareStringLength > 0)
	{
		--compareStringLength;
		if (endsCaseInsensitiveWith(compareString, compareStringPosition, compareStringLength) == true)
		{
			append(compareString.subString(originalCompareStringPosition + compareStringLength, originalCompareStringLength - compareStringLength));
			return;
		}
	}
}



int String::compare(const String& compareString) const
{
	const int lLength = getLength();
	const int rLength = compareString.getLength();
	const int count = min(lLength, rLength);
	if (getEncoding() == CHAR8_ENCODING && compareString.getEncoding() == CHAR8_ENCODING)
	{
		for (int i = 0; i < count; ++i)
		{
			const char8 l = getChar8(i);
			const char8 r = compareString.getChar8(i);
			if (l < r) return -1;
			if (l > r) return +1;
		}
		return BaseLib::Utilities::compare(lLength, rLength);
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			const char16 l = getChar16(i);
			const char16 r = compareString.getChar16(i);
			if (l < r) return -1;
			if (l > r) return +1;
		}
		return BaseLib::Utilities::compare(lLength, rLength);
	}
}



String& String::copyFromString(const String& source, int sourcePosition, int destPosition, int length)
{
	if (length == END)
	{
		length = min(getLength() - destPosition, source.getLength() - sourcePosition);
	}
	if (length > 0)
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			sourcePosition += source.start;
		#endif
		getUnsharedImplementation()->copyFromStringImplementation(source.getImplementation(), sourcePosition, destPosition, length);
	}
	return *this;
}



typedef Array<RegExMatch*>   RegExMatches;



template<typename T>
void createMatches(const T& what, RegExMatches& matches)
{
	const int count = (int)what.size();
	for (int i = 0; i < count; ++i)
	{
		String text  = what[i].str();
		int    start = what.position(i);
		int    end   = start + what[i].length();

		RegExMatch* match = new RegExMatch(text, start, end);
		matches.append(match);
	}
}



template<typename T>
void createMatches(const T& what, Enumerator<RegExMatch*>& matches)
{
	const int count = (int)what.size();
	for (int i = 0; i < count; ++i)
	{
		String text  = what[i].str();
		int    start = what.position(i);
		int    end   = start + what[i].length();

		RegExMatch* match = new RegExMatch(text, start, end);
		matches.enumerate(match);
	}
}



bool String::regExMatch(const String& expression, Enumerator<RegExMatch*>& matches) const
{
	boost::cmatch what;
	const char8* chars = getChar8CString();
	bool retVal = regex_match(chars, what, boost::regex(expression.getChar8Array()));

	createMatches<boost::cmatch>(what, matches);

	return retVal;
}



// Returns first occurence
bool String::regExSearch(const String& expression, Enumerator<RegExMatch*>& matches) const
{
	boost::cmatch what;
	const char8* chars = getChar8CString();
	bool retVal = regex_search(chars, what, boost::regex(expression.getChar8Array()));

	createMatches<boost::cmatch>(what, matches);

	return retVal;
}



// Returns all occurences
//bool String::regExSearch(const String& expression, RegExMultipleMatches& results) const
bool String::regExSearch(const String& expression, BaseLib::Functors::Enumerator<BaseLib::Containers::Enumeration<RegExMatch*>*>& results) const
{
	int numMatches = 0;
	const char8* chars = getChar8CString();

	const std::string stdString = *this;
	std::string::const_iterator start = stdString.begin();
	std::string::const_iterator end = stdString.end();
	
	boost::smatch what;
	boost::match_flag_type flags = boost::match_default;

	while (boost::regex_search(start, end, what, boost::regex(expression.getChar8Array()), flags))
	{

		RegExMatches* matches = new RegExMatches();
		createMatches(what, *matches);

		///results.append(matches); // TODO: Funktioniert nicht. Vermutlich aufgrund impliziter Typumwandlung
		results.enumerate(matches->createEnumeration(true));

		// update search position:
		start = what[0].second;

		++numMatches;

		// update flags:
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}

	return numMatches > 0;
}



String String::regExReplace(const String& expression, const String& replace)
{	
	return regex_replace(std::basic_string<BaseLib::char8>(getChar8CString()), boost::regex(expression.getChar8Array()), replace.getChar8CString());
}



} // namespace Strings
} // namespace BaseLib




#ifndef BL_NO_ICU



#include <unicode/unum.h>



BaseLib::Strings::String getIcuError(UErrorCode errorCode)
{
	switch (errorCode)
	{
		case U_USING_FALLBACK_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A resource bundle lookup returned a fallback result (not an error).";
		//case U_ERROR_WARNING_START: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of information results (semantically successful).";
		case U_USING_DEFAULT_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A resource bundle lookup returned a result from the root locale (not an error).";
		case U_SAFECLONE_ALLOCATED_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A SafeClone operation required allocating memory (informational only).";
		case U_STATE_OLD_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": ICU has to use compatibility layer to construct the service.";
		case U_STRING_NOT_TERMINATED_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": An output string could not be NUL-terminated because output length==destCapacity.";
		case U_SORT_KEY_TOO_SHORT_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Number of levels requested in getBound is higher than the number of levels in the sort key.";
		case U_AMBIGUOUS_ALIAS_WARNING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This converter alias can go to different converter implementations.";
		case U_DIFFERENT_UCA_VERSION: return BaseLib::Strings::String(u_errorName(errorCode)) + ": ucol_open encountered a mismatch between UCA version and collator image version, so the collator was constructed from rules.";
		case U_ERROR_WARNING_LIMIT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This must always be the last warning value to indicate the limit for UErrorCode warnings (last warning code +1).";
		case U_ZERO_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": No error, no warning.";
		case U_ILLEGAL_ARGUMENT_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of codes indicating failure.";
		case U_MISSING_RESOURCE_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The requested resource cannot be found.";
		case U_INVALID_FORMAT_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Data format is not what is expected.";
		case U_FILE_ACCESS_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The requested file cannot be found.";
		case U_INTERNAL_PROGRAM_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Indicates a bug in the library code.";
		case U_MESSAGE_PARSE_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Unable to parse a message (message format).";
		case U_MEMORY_ALLOCATION_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Memory allocation error.";
		case U_INDEX_OUTOFBOUNDS_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Trying to access the index that is out of bounds.";
		case U_PARSE_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Equivalent to Java ParseException.";
		case U_INVALID_CHAR_FOUND: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Character conversion: Unmappable input sequence.";
		case U_TRUNCATED_CHAR_FOUND: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Character conversion: Incomplete input sequence.";
		case U_ILLEGAL_CHAR_FOUND: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Character conversion: Illegal input sequence/combination of input units.";
		case U_INVALID_TABLE_FORMAT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Conversion table file found, but corrupted.";
		case U_INVALID_TABLE_FILE: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Conversion table file not found.";
		case U_BUFFER_OVERFLOW_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A result would not fit in the supplied buffer.";
		case U_UNSUPPORTED_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Requested operation not supported in current context.";
		case U_RESOURCE_TYPE_MISMATCH: return BaseLib::Strings::String(u_errorName(errorCode)) + ": An operation is requested over a resource that does not support it.";
		case U_ILLEGAL_ESCAPE_SEQUENCE: return BaseLib::Strings::String(u_errorName(errorCode)) + ": ISO-2022 illlegal escape sequence.";
		case U_UNSUPPORTED_ESCAPE_SEQUENCE: return BaseLib::Strings::String(u_errorName(errorCode)) + ": ISO-2022 unsupported escape sequence.";
		//case U_NO_SPACE_AVAILABL: return BaseLib::Strings::String(u_errorName(errorCode)) + ": No space available for in-buffer expansion for Arabic shaping.";
		case U_CE_NOT_FOUND_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Currently used only while setting variable top, but can be used generally.";
		case U_PRIMARY_TOO_LONG_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": User tried to set variable top to a primary that is longer than two bytes.";
		case U_STATE_TOO_OLD_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": ICU cannot construct a service from this state, as it is no longer supported.";
		case U_TOO_MANY_ALIASES_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": There are too many aliases in the path to the requested resource.";
		case U_ENUM_OUT_OF_SYNC_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UEnumeration out of sync with underlying collection.";
		case U_INVARIANT_CONVERSION_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Unable to convert a UChar* string to char* with the invariant converter.";
		case U_INVALID_STATE_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Requested operation can not be completed with ICU in its current state.";
		case U_COLLATOR_VERSION_MISMATCH: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Collator version is not compatible with the base version.";
		case U_USELESS_COLLATOR_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Collator is options only and no base is specified.";
		case U_NO_WRITE_PERMISSION: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Attempt to modify read-only or constant data.";
		case U_STANDARD_ERROR_LIMIT 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This must always be the last value to indicate the limit for standard errors.";
		case U_BAD_VARIABLE_DEFINITION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Missing '$' or duplicate variable name.";
		//case U_PARSE_ERROR_START 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of Transliterator errors.";
		case U_MALFORMED_RULE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Elements of a rule are misplaced.";
		case U_MALFORMED_SET 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A UnicodeSet pattern is invalid.";
		case U_MALFORMED_SYMBOL_REFERENCE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_MALFORMED_UNICODE_ESCAPE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A Unicode escape pattern is invalid.";
		case U_MALFORMED_VARIABLE_DEFINITION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A variable definition is invalid.";
		case U_MALFORMED_VARIABLE_REFERENCE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A variable reference is invalid.";
		case U_MISMATCHED_SEGMENT_DELIMITERS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_MISPLACED_ANCHOR_START 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A start anchor appears at an illegal position.";
		case U_MISPLACED_CURSOR_OFFSET 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A cursor offset occurs at an illegal position.";
		case U_MISPLACED_QUANTIFIER 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A quantifier appears after a segment close delimiter.";
		case U_MISSING_OPERATOR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A rule contains no operator.";
		case U_MISSING_SEGMENT_CLOSE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_MULTIPLE_ANTE_CONTEXTS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one ante context.";
		case U_MULTIPLE_CURSORS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one cursor.";
		case U_MULTIPLE_POST_CONTEXTS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one post context.";
		case U_TRAILING_BACKSLASH 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A dangling backslash.";
		case U_UNDEFINED_SEGMENT_REFERENCE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A segment reference does not correspond to a defined segment.";
		case U_UNDEFINED_VARIABLE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A variable reference does not correspond to a defined variable.";
		case U_UNQUOTED_SPECIAL 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A special character was not quoted or escaped.";
		case U_UNTERMINATED_QUOTE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A closing single quote is missing.";
		case U_RULE_MASK_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A rule is hidden by an earlier more general rule.";
		case U_MISPLACED_COMPOUND_FILTER 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A compound filter is in an invalid location.";
		case U_MULTIPLE_COMPOUND_FILTERS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one compound filter.";
		case U_INVALID_RBT_SYNTAX 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A ::id rule was passed to the RuleBasedTransliterator parser.";
		case U_INVALID_PROPERTY_PATTERN 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_MALFORMED_PRAGMA 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A 'use' pragma is invlalid.";
		case U_UNCLOSED_SEGMENT 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A closing ')' is missing.";
		case U_ILLEGAL_CHAR_IN_SEGMENT 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_VARIABLE_RANGE_EXHAUSTED 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Too many stand-ins generated for the given variable range.";
		case U_VARIABLE_RANGE_OVERLAP 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The variable range overlaps characters used in rules.";
		case U_ILLEGAL_CHARACTER 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A special character is outside its allowed context.";
		case U_INTERNAL_TRANSLITERATOR_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Internal transliterator system error.";
		case U_INVALID_ID 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A ::id rule specifies an unknown transliterator.";
		case U_INVALID_FUNCTION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": A fn() rule specifies an unknown transliterator.";
		case U_PARSE_ERROR_LIMIT 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The limit for Transliterator errors.";
		case U_UNEXPECTED_TOKEN 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Syntax error in format pattern.";
		//case U_FMT_PARSE_ERROR_START 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of format library errors.";
		case U_MULTIPLE_DECIMAL_SEPARATORS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one decimal separator in number pattern.";
		case U_MULTIPLE_EXPONENTIAL_SYMBOLS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one exponent symbol in number pattern.";
		case U_MALFORMED_EXPONENTIAL_PATTERN 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Grouping symbol in exponent pattern.";
		case U_MULTIPLE_PERCENT_SYMBOLS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one percent symbol in number pattern.";
		case U_MULTIPLE_PERMILL_SYMBOLS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one permill symbol in number pattern.";
		case U_MULTIPLE_PAD_SPECIFIERS 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": More than one pad symbol in number pattern.";
		case U_PATTERN_SYNTAX_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Syntax error in format pattern.";
		case U_ILLEGAL_PAD_POSITION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Pad symbol misplaced in number pattern.";
		case U_UNMATCHED_BRACES 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Braces do not match in message pattern.";
		case U_UNSUPPORTED_PROPERTY 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_UNSUPPORTED_ATTRIBUTE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UNUSED as of ICU 2.4.";
		case U_FMT_PARSE_ERROR_LIMIT 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The limit for format library errors.";
		case U_BRK_INTERNAL_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": An internal error (bug) was detected.";
		//case U_BRK_ERROR_START 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of codes indicating Break Iterator failures.";
		case U_BRK_HEX_DIGITS_EXPECTED 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Hex digits expected as part of a escaped char in a rule.";
		case U_BRK_SEMICOLON_EXPECTED 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Missing ';' at the end of a RBBI rule.";
		case U_BRK_RULE_SYNTAX 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Syntax error in RBBI rule.";
		case U_BRK_UNCLOSED_SET 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": UnicodeSet witing an RBBI rule missing a closing ']'.";
		case U_BRK_ASSIGN_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Syntax error in RBBI rule assignment statement.";
		case U_BRK_VARIABLE_REDFINITION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": RBBI rule $Variable redefined.";
		case U_BRK_MISMATCHED_PAREN 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Mis-matched parentheses in an RBBI rule.";
		case U_BRK_NEW_LINE_IN_QUOTED_STRING 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Missing closing quote in an RBBI rule.";
		case U_BRK_UNDEFINED_VARIABLE 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Use of an undefined $Variable in an RBBI rule.";
		case U_BRK_INIT_ERROR 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Initialization failure.";
		case U_BRK_RULE_EMPTY_SET 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Rule contains an empty Unicode Set.";
		case U_BRK_UNRECOGNIZED_OPTION 	: return BaseLib::Strings::String(u_errorName(errorCode)) + ": !!option in RBBI rules not recognized.";
		//case U_BRK_MALFORMED_RULE_TA: return BaseLib::Strings::String(u_errorName(errorCode)) + ": The {nnn} tag on a rule is mal formed.";
		case U_BRK_ERROR_LIMIT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This must always be the last value to indicate the limit for Break Iterator failures.";
		case U_REGEX_INTERNAL_ERROR: return BaseLib::Strings::String(u_errorName(errorCode)) + ": An internal error (bug) was detected.";
		//case U_REGEX_ERROR_START: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Start of codes indicating Regexp failures.";
		case U_REGEX_RULE_SYNTAX: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Syntax error in regexp pattern.";
		case U_REGEX_INVALID_STATE: return BaseLib::Strings::String(u_errorName(errorCode)) + ": RegexMatcher in invalid state for requested operation.";
		case U_REGEX_BAD_ESCAPE_SEQUENCE: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Unrecognized backslash escape sequence in pattern.";
		case U_REGEX_PROPERTY_SYNTAX: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Incorrect Unicode property.";
		case U_REGEX_UNIMPLEMENTED: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Use of regexp feature that is not yet implemented.";
		case U_REGEX_MISMATCHED_PAREN: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Incorrectly nested parentheses in regexp pattern.";
		case U_REGEX_NUMBER_TOO_BIG: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Decimal number is too large.";
		case U_REGEX_BAD_INTERVAL: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Error in {min,max} interval.";
		case U_REGEX_MAX_LT_MIN: return BaseLib::Strings::String(u_errorName(errorCode)) + ": In {min,max}, max is less than min.";
		case U_REGEX_INVALID_BACK_REF: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Back-reference to a non-existent capture group.";
		case U_REGEX_INVALID_FLAG: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Invalid value for match mode flags.";
		case U_REGEX_LOOK_BEHIND_LIMIT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Look-Behind pattern matches must have a bounded maximum length.";
		case U_REGEX_SET_CONTAINS_STRING: return BaseLib::Strings::String(u_errorName(errorCode)) + ": Regexps cannot have UnicodeSets containing strings.";
		case U_REGEX_ERROR_LIMIT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This must always be the last value to indicate the limit for regexp errors.";
		case U_ERROR_LIMIT: return BaseLib::Strings::String(u_errorName(errorCode)) + ": This must always be the last value to indicate the limit for UErrorCode (last error code +1).";
		default:
			return u_errorName(errorCode);
	}
}



#endif // #ifndef BL_NO_ICU
