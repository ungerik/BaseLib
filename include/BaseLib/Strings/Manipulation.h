/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_Manipulation_h
#define BaseLib_Strings_Manipulation_h



#include "BaseLib/intern/Windows.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Utilities/AutoArray.h"
#include <locale>



#define STRING_LENGTH(s) (sizeof(s)/sizeof(s[0]))
#define CSTRING_LENGTH(s) (sizeof(s)/sizeof(s[0])-1)



namespace BaseLib {
namespace Strings {



using BaseLib::Utilities::AutoArray;
using namespace BaseLib::Utilities;



extern BL_EXPORT std::locale defaultLocale;



extern BL_EXPORT String defaultTokenDelimiters;
extern BL_EXPORT String defaultLineEndChars;
extern BL_EXPORT char8 narrowReplaceCharacter;

extern BL_EXPORT const char8 WINDOWS_LINE_END_CHARS[];
extern BL_EXPORT const char8 UNIX_LINE_END_CHARS[];
extern BL_EXPORT const char8 MAC_LINE_END_CHARS[];



inline char8 wchar2char(char16 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char16> >(loc).narrow(c, ' ');
}



inline char16 char2wchar(char8 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char16> >(loc).widen(c);
}



BL_EXPORT std::string wstring2string(const std::wstring& wideString, const std::locale& loc = std::locale::classic());



inline char8 * wstring2string(const char16 * wideString, char8 * buffer, size_t length, const std::locale& loc = std::locale::classic())
{
	std::use_facet< std::ctype<char16> >(loc).narrow(&wideString[0], &wideString[length], ' ', &buffer[0]);
	return buffer;
}



inline char8 * wstring2string(const std::wstring& wideString, char8 * buffer, const std::locale& loc = std::locale::classic())
{
	return wstring2string(wideString.c_str(), buffer, wideString.length(), loc);
}



BL_EXPORT std::wstring string2wstring(const std::string& str, const std::locale& loc = std::locale::classic());



inline char16 * string2wstring(const char8 * str, char16 * buffer, size_t length, const std::locale& loc = std::locale::classic())
{
	std::use_facet< std::ctype<char16> >(loc).widen(&str[0], &str[length], &buffer[0]);
	return buffer;
}



inline char16 * string2wstring(const std::string& str, char16 * buffer, const std::locale& loc = std::locale::classic())
{
	return string2wstring(str.c_str(), buffer, str.length(), loc);
}



template<typename T>
inline std::basic_string<T> makeString(const std::string& str, const std::locale& loc = std::locale::classic());



template<>
inline std::basic_string<char8> makeString(const std::string& str, const std::locale& loc)
{
	return str;
}



template<>
inline std::basic_string<char16> makeString(const std::string& str, const std::locale& loc)
{
	return string2wstring(str, loc);
}



template<typename T>
inline std::basic_string<T> makeString(const std::wstring& str, const std::locale& loc = std::locale::classic());



template<>
inline std::basic_string<char8> makeString(const std::wstring& wstr, const std::locale& loc)
{
	return wstring2string(wstr, loc);
}



template<>
inline std::basic_string<char16> makeString(const std::wstring& wstr, const std::locale& loc)
{
	return wstr;
}



inline char8 upperCase(char8 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char8> >(loc).toupper(c);
}



inline char8 lowerCase(char8 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char8> >(loc).tolower(c);
}



inline char16 upperCase(char16 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char16> >(loc).toupper(c);
}



inline char16 lowerCase(char16 c, const std::locale& loc = std::locale::classic())
{
	return std::use_facet< std::ctype<char16> >(loc).tolower(c);
}



template<typename T>
std::basic_string<T> upperCase(const std::basic_string<T>& str, const std::locale& loc = std::locale::classic())
{
	const size_t length = str.length();
	AutoArray<T> buffer(new T[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<T> >(loc).toupper(&buffer[0], &buffer[length]);
	return std::basic_string<T>(&buffer[0], length);
}



template<typename T>
std::basic_string<T> lowerCase(const std::basic_string<T>& str, const std::locale& loc = std::locale::classic())
{
	const size_t length = str.length();
	AutoArray<T> buffer(new T[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<T> >(loc).tolower(&buffer[0], &buffer[length]);
	return std::basic_string<T>(&buffer[0], length);
}



template<typename T>
std::basic_string<T> upperCase(const T * str, const std::locale& loc = std::locale::classic())
{
	return upperCase(std::basic_string<T>(str), loc);
}



template<typename T>
std::basic_string<T> lowerCase(const T * str, const std::locale& loc = std::locale::classic())
{
	return lowerCase(std::basic_string<T>(str), loc);
}


/*
String upperCase(const String& str, const std::locale& loc = std::locale::classic());
String lowerCase(const String& str, const std::locale& loc = std::locale::classic());
std::wstring upperCase(const std::wstring& str, const std::locale& loc = std::locale::classic());
std::wstring lowerCase(const std::wstring& str, const std::locale& loc = std::locale::classic());
*/


inline bool isNumber(const String& ws);



inline bool isNumber(char8 c)
{
	return (c >= '0' && c <= '9') || c == '+' || c == '-';
}



inline bool isNumber(char16 c)
{
	return isNumber( wchar2char(c) );
}



inline bool isFloatNumber(char8 c)
{
	return isNumber(c) || c == '.' || c == 'e';
}



inline bool isFloatNumber(char16 c)
{
	return isFloatNumber( wchar2char(c) );
}



inline int8 char2Number(char8 c)
{
	BL_ASSERT(isNumber(c) == true);
	return c - '0';
}



inline char8 number2Char(int number)
{
	BL_ASSERT(number >= 0 && number <= 9);
	return static_cast<char8>(number) + '0';
}



inline bool isHexNumber(char8 c)
{
	return isNumber(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}



const char8 hexDigits[] = "0123456789ABCDEF";
extern BL_EXPORT const std::wstring hexDigitsW;



inline int8 hexChar2Number(char8 c)
{
	if (c < 'A')
	{
		return char2Number(c);
	}
	else if (c <= 'F')
	{
		return c - 'A' + 0xA;
	}
	else
	{
		BL_ASSERT(c >= 'a' && c <= 'f');
		return c - 'a' + 0xA;
	}
}



inline char8 number2HexChar(int number)
{
	BL_ASSERT(number >= 0x0 && number <= 0xF);
	return hexDigits[number];
}



inline char16 number2HexCharW(int number)
{
	BL_ASSERT(number >= 0x0 && number <= 0xF);
	return hexDigitsW[number];
}



/**
Converts binary-data to a hex-string.
*/
inline std::string bin2hex(const void* binaryData, int byteCount, bool rightToLeft = false)
{
	std::string hexString(byteCount*2, '\0');
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		hexString[i*2] = number2HexChar(byte & 0x0F);
		hexString[i*2+1] = number2HexChar(byte >> 4);
	}
	return hexString;
}



/**
Converts binary-data to a hex-string.
*/
inline std::wstring bin2hexW(const void* binaryData, int byteCount, bool rightToLeft = false)
{
	std::wstring hexString(byteCount*2, '\0');
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		hexString[i*2] = number2HexCharW(byte & 0x0F);
		hexString[i*2+1] = number2HexCharW(byte >> 4);
	}
	return hexString;
}



/**
Converts binary-data to a hex-string.
*/
inline char * bin2hex(const void* binaryData, int byteCount, char * hexString, bool rightToLeft = false)
{
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		hexString[i*2] = number2HexChar(byte & 0x0F);
		hexString[i*2+1] = number2HexChar(byte >> 4);
	}
	return hexString;
}



/**
Converts a hex-string to binary-data.
*/
inline int hex2bin(const char * hexString, void* resultBuffer)
{
	int i;
	for (i = 0; hexString[i*2] != '\0' && hexString[i*2+1] != '\0'; ++i)
	{
		memoryAs<uint8>(resultBuffer, i)
			= (hexChar2Number(hexString[i*2]) << 4) | hexChar2Number(hexString[i*2+1]);
	}
	return i;
}



inline bool isBinNumber(char8 c)
{
	return (c == '0' || c == '1');
}



const char16 binDigitsW[2] = { char2wchar('0'), char2wchar('1') };



inline bool isBinNumber(char16 c)
{
	return (c == binDigitsW[0] || c == binDigitsW[1]);
}



inline bool isBinNumber(const std::string& binNumberString)
{
	//int length = binNumberString.getLength();
	int length = (int)binNumberString.size();
	for (int i = 0; i < length; ++i)
	{
		if (isBinNumber(binNumberString[i]) == false) return false;
	}
	return true;
}



inline int8 binChar2Number(char8 c)
{
	BL_ASSERT(isBinNumber(c) == true);
	return c - '0';
}



inline int8 binChar2Number(char16 c)
{
	BL_ASSERT(isBinNumber(c) == true);
	return binChar2Number(wchar2char(c));
}



inline char8 number2BinChar(int number)
{
	BL_ASSERT(number == 0 || number == 1);
	return number + '0';
}



inline char16 number2BinCharW(int number)
{
	BL_ASSERT(number == 0 || number == 1);
	return char2wchar(number2BinChar(number));
}



/**
Converts binary-data to a bin-string.
*/
inline std::string bin2binString(const void* binaryData, int byteCount, bool rightToLeft = false)
{
	std::string binString(byteCount*8, '\0');
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		int index = i * 8;
		binString[index++] = number2BinChar(byte & 0x01);
		binString[index++] = number2BinChar(byte & 0x02);
		binString[index++] = number2BinChar(byte & 0x04);
		binString[index++] = number2BinChar(byte & 0x08);
		binString[index++] = number2BinChar(byte & 0x10);
		binString[index++] = number2BinChar(byte & 0x20);
		binString[index++] = number2BinChar(byte & 0x40);
		binString[index  ] = number2BinChar(byte & 0x80);
	}
	return binString;
}



/**
Converts binary-data to a bin-string.
*/
inline std::wstring bin2binStringW(const void* binaryData, int byteCount, bool rightToLeft = false)
{
	std::wstring binString(byteCount*8, '\0');
	for (int i = 0; i < byteCount; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : byteCount-1 - i);
		int index = i * 8;
		binString[index++] = number2BinCharW(byte & 0x01);
		binString[index++] = number2BinCharW(byte & 0x02);
		binString[index++] = number2BinCharW(byte & 0x04);
		binString[index++] = number2BinCharW(byte & 0x08);
		binString[index++] = number2BinCharW(byte & 0x10);
		binString[index++] = number2BinCharW(byte & 0x20);
		binString[index++] = number2BinCharW(byte & 0x40);
		binString[index  ] = number2BinCharW(byte & 0x80);
	}
	return binString;
}



/**
Converts binary-data to a bin-string.
*/
inline char * bin2binString(const void* binaryData, int size, char * binString, bool rightToLeft = false)
{
	for (int i = 0; i < size; ++i)
	{
		uint8 byte = memoryAs<uint8>(binaryData, rightToLeft == false ? i : size-1 - i);
		int index = i * 8;
		binString[index++] = number2BinChar(byte & 0x01);
		binString[index++] = number2BinChar(byte & 0x02);
		binString[index++] = number2BinChar(byte & 0x04);
		binString[index++] = number2BinChar(byte & 0x08);
		binString[index++] = number2BinChar(byte & 0x10);
		binString[index++] = number2BinChar(byte & 0x20);
		binString[index++] = number2BinChar(byte & 0x40);
		binString[index  ] = number2BinChar(byte & 0x80);
	}
	return binString;
}



/**
Converts a bin-string to binary-data.
*/
inline int binString2bin(const std::string& binString, void* resultBuffer, bool rightToLeft = false)
{
	const int size = (int)binString.length() / 8;
	for (int i = 0; i < size; ++i)
	{
		int index = i * 8;
		memoryAs<uint8>(resultBuffer, (rightToLeft == false) ? (i) : (size-1 - i) )
			= (binChar2Number(binString[index++]) << 7)
			| (binChar2Number(binString[index++]) << 6)
			| (binChar2Number(binString[index++]) << 5)
			| (binChar2Number(binString[index++]) << 4)
			| (binChar2Number(binString[index++]) << 3)
			| (binChar2Number(binString[index++]) << 2)
			| (binChar2Number(binString[index++]) << 1)
			| binChar2Number(binString[index]);
	}
	return size;
}



/**
Converts a bin-string to binary-data.
*/
inline int binString2bin(const std::wstring& binString, void* resultBuffer, bool rightToLeft = false)
{
	return binString2bin(wstring2string(binString), resultBuffer, rightToLeft);
}



/**
Converts a bin-string to binary-data.
*/
inline int binString2bin(const char * binString, void* resultBuffer)
{
	/*
	int size;
	for (int i = 0; binString[i] != '\0' && binString[i+1] != '\0'; ++i)
	{
		int index = i * 8;
		memoryAs<uint8>(resultBuffer, i)
			= (binChar2Number(binString[index++]) << 7)
			| (binChar2Number(binString[index++]) << 6)
			| (binChar2Number(binString[index++]) << 5)
			| (binChar2Number(binString[index++]) << 4)
			| (binChar2Number(binString[index++]) << 3)
			| (binChar2Number(binString[index++]) << 2)
			| (binChar2Number(binString[index++]) << 1)
			| binChar2Number(binString[index]);

	}
	return size;
	*/
	BL_ASSERT_NEVER_REACHED
	return 0;
}



/**
Removes special chars at the end and beginning of a string.
*/
template<typename T>
inline std::basic_string<T> trimString(const std::basic_string<T>& str, const std::basic_string<T>& charsToTrim)
{
	const size_t first = str.find_first_not_of(charsToTrim);
	return (first != std::basic_string<T>::npos) ? str.substr(first, str.find_last_not_of(charsToTrim)+1 - first) : std::basic_string<T>();
}




/**
Removes a special char at the end and beginning of a string.
*/
template<typename T>
inline std::basic_string<T> trimString(const std::basic_string<T>& str, const typename std::basic_string<T>::value_type charToTrim)
{
	const size_t first = str.find_first_not_of(charToTrim);
	return (first != std::basic_string<T>::npos) ? str.substr(first, str.find_last_not_of(charToTrim)+1 - first) : std::basic_string<T>();
}



/**
Removes special chars at the beginning of a string.
*/
template<typename T>
inline std::string trimStringBeginning(const std::string& str, const std::string& charsToTrim)
{
	const size_t first = str.find_first_not_of(charsToTrim);
	return (first != std::string::npos) ? str.substr(first, str.length() - first) : std::string();
}



/**
Removes special chars at the beginning of a unicode-string.
*/
template<typename T>
inline std::basic_string<T> trimStringBeginning(const std::basic_string<T>& str, const std::basic_string<T>& charsToTrim)
{
	const size_t first = str.find_first_not_of(charsToTrim);
	return (first != std::basic_string<T>::npos) ? str.substr(first, str.length() - first) : std::basic_string<T>();
}




/**
Removes special chars at the end of a string.
*/
template<typename T>
inline std::basic_string<T> trimStringEnd(const std::basic_string<T>& str, const std::basic_string<T>& charsToTrim)
{
	const size_t last = str.find_last_not_of(charsToTrim);
	return (last != std::basic_string<T>::npos) ? str.substr(0, last+1) : std::basic_string<T>();
}



/**
Removes a special char at the end of a unicode-string.
*/
template<typename T>
inline std::basic_string<T> trimStringEnd(const std::basic_string<T>& str, const typename std::basic_string<T>::value_type charToTrim)
{
	const size_t last = str.find_last_not_of(charToTrim);
	return (last != std::basic_string<T>::npos) ? str.substr(0, last+1) : std::basic_string<T>();
}



/**
Romoves a given count of chars at the end and beginning of a unicode-string.
*/
template<typename T>
inline std::basic_string<T> trimString(const std::basic_string<T>& str, const size_t charsAtBeginning, const size_t charsAtEnd)
{
	return str.substr(charsAtBeginning, str.length() - charsAtBeginning - charsAtEnd);
}



/**
Romoves a given count of chars at the beginning of a unicode-string.
*/
template<typename T>
inline std::basic_string<T> trimStringBeginning(const std::basic_string<T>& str, const size_t charsAtBeginning = 1)
{
	return str.substr(charsAtBeginning);
}



/**
Romoves a given count of chars at the end of a unicode-string.
*/
template<typename T>
inline std::basic_string<T> trimStringEnd(const std::basic_string<T>& str, const size_t charsAtEnd = 1)
{
	return str.substr(0, str.length() - charsAtEnd);
}



template<typename T>
inline bool stringEndsWith(const std::basic_string<T>& str, const std::basic_string<T>& end)
{
	const size_t strLength = str.length();
	const size_t endLength = end.length();
	return (endLength <= strLength) ? (str.substr(strLength - endLength) == end) : false;
}



template<typename T>
inline bool stringEndsCaseInsensitiveWith(const std::basic_string<T>& str, const std::basic_string<T>& end)
{
	const size_t strLength = str.length();
	const size_t endLength = end.length();
	return (endLength <= strLength) ? (lowerCase(str.substr(strLength - endLength)) == lowerCase(end)) : false;
}



template<typename T>
inline bool stringBeginsWith(const std::basic_string<T>& str, const std::basic_string<T>& begin)
{
	const size_t strLength = str.length();
	const size_t endLength = begin.length();
	return (endLength <= strLength) ? (str.substr(0, endLength) == begin) : false;
}



template<typename T>
inline bool stringBeginsCaseInsensitiveWith(const std::basic_string<T>& str, const std::basic_string<T>& begin)
{
	const size_t strLength = str.length();
	const size_t endLength = begin.length();
	return (endLength <= strLength) ? (lowerCase(str.substr(0, endLength)) == lowerCase(begin)) : false;
}



template<typename T>
inline bool stringEndsWith(const std::basic_string<T>& str, typename std::basic_string<T>::value_type end)
{
	const size_t strLength = str.length();
	return (strLength != 0) ? (str[strLength-1] == end) : false;
}



template<typename T>
inline bool stringEndsCaseInsensitiveWith(const std::basic_string<T>& str, typename std::basic_string<T>::value_type end)
{
	const size_t strLength = str.length();
	return (strLength != 0) ? (lowerCase(str[strLength-1]) == lowerCase(end)) : false;
}



template<typename T>
inline bool stringBeginsWith(const std::basic_string<T>& str, typename std::basic_string<T>::value_type begin)
{
	return (str.empty() == false) ? (str[0] == begin) : false;
}



template<typename T>
inline bool stringBeginsCaseInsensitiveWith(const std::basic_string<T>& str, typename std::basic_string<T>::value_type begin)
{
	return (str.empty() == false) ? (lowerCase(str[0]) == lowerCase(begin)) : false;
}



template<class T>
inline std::basic_string<T> nextToken(const std::basic_string<T>& tokenString, size_t& offset, const std::basic_string<T>& delimiter = makeString<T>(defaultTokenDelimiters))
{
	size_t delimiterOffset = tokenString.find_first_of(delimiter, offset);
	size_t tokenOffset = offset;
	offset = tokenString.find_first_not_of(delimiter, delimiterOffset);
	return tokenString.substr(tokenOffset, delimiterOffset);
}



template<class Container>
inline typename Container::value_type implodeString(const typename Container::const_iterator& begin, const typename Container::const_iterator& end)
{
	typename Container::value_type result;
	for (typename Container::const_iterator i = begin; i != end; ++i)	result += *i;
	return result;
}



template<class Container>
inline typename Container::value_type implodeString(const Container& stringContainer)
{
	return implodeString(stringContainer.begin(), stringContainer.end());
}



template<class Container>
inline typename Container::value_type implodeString(const typename Container::const_iterator& begin, const typename Container::const_iterator& end, const typename Container::value_type& separator)
{
	if (begin == end) return std::string();

	typename Container::value_type result = *begin;
	for (typename Container::const_iterator i = begin+1; i != end; ++i) result += separator + *i;
	return result;
}



template<class Container>
inline typename Container::value_type implodeString(const Container& stringContainer, const typename Container::value_type& separator)
{
	return implodeString(stringContainer.begin(), stringContainer.end(), separator);
}



template<class Container>
Container& explodeString(const typename Container::value_type tokenString, const typename Container::value_type delimiter = makeString<Container::value_type::value_type>(defaultTokenDelimiters), Container& container = Container())
{
	size_t offset = 0;
	do
	{
		container.push_back( nextToken(tokenString, offset, delimiter) );
	}
	while (offset != std::string::npos);
	return container;
}



} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_Manipulation_h