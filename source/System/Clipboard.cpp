/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/intern/Windows.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/System/Clipboard.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



bool Clipboard::isEmpty()
{
	#ifdef BL_PLATFORM_WIN32

	OpenClipboard(NULL);
	HANDLE handle = GetClipboardData(CF_TEXT);
	String e = getLastWindowsError(); ///
	CloseClipboard();
	return handle == NULL;

	#endif
}



void Clipboard::makeEmpty()
{
	#ifdef BL_PLATFORM_WIN32

	OpenClipboard(NULL);
	EmptyClipboard();
	String e = getLastWindowsError(); ///
	CloseClipboard();

	#endif
}



String Clipboard::getText()
{
	#ifdef BL_PLATFORM_WIN32

	OpenClipboard(NULL);
	HANDLE handle = GetClipboardData(CF_UNICODETEXT);
	CloseClipboard();

	if (handle != NULL)
	{
		const char16 * mem = static_cast<const char16 *>(GlobalLock(handle));
		int length = zeroTerminatedStringLength(mem);
		String newString(CHAR16_ENCODING);
		newString.copyFromCharArray(mem, 0, length);
		GlobalUnlock(handle);
		return newString;
	}
	else
	{
		return String(CHAR16_ENCODING);
	}

	#endif
}



void Clipboard::setText(const String& newText)
{
	#ifdef BL_PLATFORM_WIN32

	int res;
	HANDLE h;

	int length = newText.getLength();
	HGLOBAL memHandle;
	UINT format;

	if (newText.getEncoding() == CHAR16_ENCODING)
	{
		int byteCount = (length+1) * sizeof(char16);
		memHandle = GlobalAlloc(GMEM_MOVEABLE, byteCount);
		void* mem = GlobalLock(memHandle);
		CopyMemory(mem, newText.getChar16CString(), byteCount);
		res = GlobalUnlock(memHandle);
		format = CF_UNICODETEXT;
	}
	else
	{
		BL_ASSERT(newText.getEncoding() == CHAR8_ENCODING);
		int byteCount = (length+1) * sizeof(char8);
		memHandle = GlobalAlloc(GMEM_MOVEABLE, byteCount);
		void* mem = GlobalLock(memHandle);
		CopyMemory(mem, newText.getChar16CString(), byteCount);
		res = GlobalUnlock(memHandle);
		format = CF_TEXT;
	}

	res = OpenClipboard(NULL);
	h = SetClipboardData(format, memHandle);
	String e = getLastWindowsError();
	res = CloseClipboard();

	#endif
}



} // namespace System
} // namespace BaseLib
