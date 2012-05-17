/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/intern/Windows.h"
#include "BaseLib/System/DynamicLinkLibrary.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Files/LocalFile.h"
#include <psapi.h>



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;
using namespace BaseLib::Files;



DynamicLinkLibrary::DynamicLinkLibrary(const String& libraryFileName, const String& searchPaths, const bool unloadWhenDestroyed)
	: fileName(libraryFileName)
	, paths(searchPaths)
	, dllHandle(NULL)
	, unloadedWhenDestroyed(unloadWhenDestroyed)
{
	load();
}



DynamicLinkLibrary::~DynamicLinkLibrary()
{
	if (unloadedWhenDestroyed == true && isLoaded() == true)
	{
		unload();
	}
}



void DynamicLinkLibrary::load()
{
	if (isLoaded() == false)
	{
		#ifdef BL_PLATFORM_WIN32		
			if (fileName.getEncoding() == CHAR8_ENCODING)
			{
				dllHandle = LoadLibraryA(fileName.getChar8CString());
			}
			else
			{
				dllHandle = LoadLibraryW(fileName.getChar16CString());
			}

			if (dllHandle == NULL)
			{
				String usedFileName = fileName;
				if (fileName.endsCaseInsensitiveWith(".dll") == false &&
					fileName.endsCaseInsensitiveWith(".exe") == false)
				{
					usedFileName += ".dll";
				}
				usedFileName = LocalFile::find(usedFileName, paths);
				if (usedFileName.isEmpty() == true)
				{
					ioError("Can't find library: " + fileName + " !" ERROR_AT);
					return;
				}

				if (usedFileName.getEncoding() == CHAR8_ENCODING)
				{
					dllHandle = LoadLibraryA(usedFileName.getChar8CString());
				}
				else
				{
					dllHandle = LoadLibraryW(usedFileName.getChar16CString());
				}

				if (dllHandle == NULL)
				{
					resultError("Windows error while loading library " + fileName + ": " + getLastWindowsError() + ERROR_AT);				
				}
			}
		#else
			BL_ASSERT_NEVER_REACHED
		#endif
	}
	else
	{
		stateError("Dynamic Link Library " + fileName + " is alread loaded!");
	}
}



void DynamicLinkLibrary::unload()
{
	if (isLoaded() == true)
	{
		#ifdef BL_PLATFORM_WIN32
			if (FreeLibrary(dllHandle) != FALSE)
			{
				dllHandle = NULL;
			}
			else
			{
				resultError("Windows error while unloading library " + fileName + ": " + getLastWindowsError() + ERROR_AT);				
			}
		#else
		#endif
	}
	else
	{
		stateError("Dynamic Link Library " + fileName + " is not loaded!" ERROR_AT);
	}
}



void* DynamicLinkLibrary::getFunctionAddress(const String& functionName) const
{
	if (isLoaded() == true)
	{
		#ifdef BL_PLATFORM_WIN32
			return GetProcAddress(dllHandle, functionName.getChar8CString());
		#else
			return NULL;
		#endif
	}
	else
	{
		stateError("Dynamic Link Library " + fileName + " is not loaded!" ERROR_AT);
		return NULL;
	}
}



String DynamicLinkLibrary::getLoadedPath() const
{
	if (isLoaded() == true)
	{
		char16 buffer[1024];
		DWORD result = GetModuleFileNameExW(GetCurrentProcess(), dllHandle, buffer, 1024);
		if (result != 0)
		{
			return buffer;
		}
		else
		{
			resultError(getLastWindowsError() + ERROR_AT);
			return Empty();
		}
	}
	else
	{
		stateError("Dynamic Link Library " + fileName + " is not loaded!" ERROR_AT);
		return Empty();
	}
}





} // namespace System
} // namespace BaseLib
