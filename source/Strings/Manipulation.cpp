/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Strings/Char8StringImplementation.h"



namespace BaseLib {
namespace Strings {




// Moved to BaseLib.cpp because of initialization order:
//std::locale defaultLocale = std::locale::classic();
//String defaultTokenDelimiters(" \b\f\n\r\t", new Char8StringImplementation());
//String defaultLineEndChars("\r\n", new Char8StringImplementation());
//char8 narrowReplaceCharacter = ' ';
//const char8 WINDOWS_LINE_END_CHARS[] = "\r\n";
//const char8 UNIX_LINE_END_CHARS[] = "\n";
//const char8 MAC_LINE_END_CHARS[] = "\r";
//const std::wstring hexDigitsW(string2wstring(hexDigits));



std::string wstring2string(const std::wstring& wideString, const std::locale& loc)
{
	const size_t length = wideString.length();
	AutoArray<char8> buffer(new char8[length]);
	std::use_facet< std::ctype<char16> >(loc).narrow(&wideString.data()[0], &wideString.data()[length], narrowReplaceCharacter, &buffer[0]);
	return std::string(&buffer[0], length);
}



std::wstring string2wstring(const std::string& str, const std::locale& loc)
{
	const size_t length = str.length();
	AutoArray<char16> buffer(new char16[length+1]);
	std::use_facet< std::ctype<char16> >(loc).widen(&str.data()[0], &str.data()[length], &buffer[0]);
	return std::wstring(&buffer[0], length);
}



/*
String wstring2string(const std::wstring& wideString, const std::locale& loc)
{
	const size_t length = wstr.length();
	mbstate_t state;
	const char16 * cwstr = wstr.c_str();
	char16 * wNext;
	AutoArray<char8> cstr(new char8[length]);
	char8 * sNext;
	std::use_facet< std::codecvt<char16, char8, mbstate_t> >(loc).out(
		state,
		&cwstr[0], &cwstr[length], wNext,
		&cstr[0], &cstr[length], sNext
	);
	return String(&cstr[0], length);
}
*/





/*
std::wstring string2wstring(const String& str, const std::locale& loc)
{
	const size_t length = str.length();
	mbstate_t state;
	const char8 * cstr = str.c_str();
	char8 * sNext;
	AutoArray<char16> cwstr(new char16[length]);
	char16 * wNext;
	std::use_facet< std::codecvt<char16, char8, mbstate_t> >(loc).in(
		state,
		&cstr[0], &cstr[length], sNext,
		&cwstr[0], &cwstr[length], wNext
	);
	return std::wstring(&cwstr[0], length);
}
*/


/*
String upperCase(const String& str, const std::locale& loc)
{
	const size_t length = str.length();
	AutoArray<char8> buffer(new char8[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<char8> >(loc).toupper(&buffer[0], &buffer[length]);
	return String(&buffer[0], length);
}



String lowerCase(const String& str, const std::locale& loc)
{
	const size_t length = str.length();
	AutoArray<char8> buffer(new char8[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<char8> >(loc).tolower(&buffer[0], &buffer[length]);
	return String(&buffer[0], length);
}



std::wstring upperCase(const std::wstring& str, const std::locale& loc)
{
	const size_t length = str.length();
	AutoArray<char16> buffer(new char16[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<char16> >(loc).toupper(&buffer[0], &buffer[length]);
	return std::wstring(&buffer[0], length);
}



std::wstring lowerCase(const std::wstring& str, const std::locale& loc)
{
	const size_t length = str.length();
	AutoArray<char16> buffer(new char16[length]);
	str.copy(&buffer[0], length);
	std::use_facet< std::ctype<char16> >(loc).tolower(&buffer[0], &buffer[length]);
	return std::wstring(&buffer[0], length);
}
*/



} // namespace Strings
} // namespace BaseLib
