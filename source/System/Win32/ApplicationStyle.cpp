/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Defines.h"
#ifdef BL_PLATFORM_WIN32



#include "BaseLib/System/Win32/ApplicationStyle.h"
#include "BaseLib/System/DynamicLinkLibrary.h"
#include <uxtheme.h>



namespace BaseLib {
namespace System {
namespace Win32 {



using namespace BaseLib::System;
using namespace BaseLib::Utilities;



AutoPointer<DynamicLinkLibrary> uxThemeDll = NULL;

typedef DWORD (WINAPI *GetThemeAppPropertiesFunc)();
typedef void (WINAPI *SetThemeAppPropertiesFunc)(DWORD dwFlags);

GetThemeAppPropertiesFunc GetThemeAppProperties = NULL;
SetThemeAppPropertiesFunc SetThemeAppProperties = NULL;



bool checkUxThemeDll()
{
	if (uxThemeDll == NULL)
	{
		uxThemeDll = new DynamicLinkLibrary("uxtheme.dll");
		if (uxThemeDll->isLoaded() == true)
		{
			GetThemeAppProperties = (GetThemeAppPropertiesFunc)uxThemeDll->getFunctionAddress("GetThemeAppProperties");
			SetThemeAppProperties = (SetThemeAppPropertiesFunc)uxThemeDll->getFunctionAddress("SetThemeAppProperties");			
		}
	}

	return GetThemeAppProperties != NULL && SetThemeAppProperties != NULL;
}



bool ApplicationStyle::isStyleUsedForNonClientAreas()
{
	if (checkUxThemeDll() == true)
	{
		return (GetThemeAppProperties() & STAP_ALLOW_NONCLIENT) != 0;
	}
	else
	{
		return false;
	}
}



bool ApplicationStyle::isStyleUsedForControls()
{
	if (checkUxThemeDll() == true)
	{
		return (GetThemeAppProperties() & STAP_ALLOW_CONTROLS) != 0;
	}
	else
	{
		return false;
	}
}



bool ApplicationStyle::isStyleUsedForWebContent()
{
	if (checkUxThemeDll() == true)
	{
		return (GetThemeAppProperties() & STAP_ALLOW_WEBCONTENT) != 0;
	}
	else
	{
		return false;
	}
}



void ApplicationStyle::setStyleUsedForNonClientAreas(bool useStyle)
{
	if (checkUxThemeDll() == true)
	{
		DWORD flags = GetThemeAppProperties();
		if (useStyle == true)
		{
			flags |= STAP_ALLOW_NONCLIENT;
		}
		else
		{
			flags &= ~STAP_ALLOW_NONCLIENT;
		}
		SetThemeAppProperties(flags);
	}
}



void ApplicationStyle::setStyleUsedForControls(bool useStyle)
{
	if (checkUxThemeDll() == true)
	{
		DWORD flags = GetThemeAppProperties();
		if (useStyle == true)
		{
			flags |= STAP_ALLOW_CONTROLS;
		}
		else
		{
			flags &= ~STAP_ALLOW_CONTROLS;
		}
		SetThemeAppProperties(flags);
	}
}



void ApplicationStyle::setStyleUsedForWebContent(bool useStyle)
{
	if (checkUxThemeDll() == true)
	{
		DWORD flags = GetThemeAppProperties();
		if (useStyle == true)
		{
			flags |= STAP_ALLOW_WEBCONTENT;
		}
		else
		{
			flags &= ~STAP_ALLOW_WEBCONTENT;
		}
		SetThemeAppProperties(flags);
	}
}



} // namespace Win32
} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32
