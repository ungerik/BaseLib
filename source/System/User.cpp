/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Defines.h"
#include "BaseLib/intern/Windows.h"
#ifdef BL_PLATFORM_WIN32
	#define SECURITY_WIN32
	#include <security.h>
#endif
#include "BaseLib/System/User.h"
#include "BaseLib/System/Process.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::Strings;



String User::getName()
{
	#ifdef BL_PLATFORM_WIN32
		char16 buffer[256];
		ULONG size = sizeof(buffer);
		if (GetUserNameEx(NameDisplay, buffer, &size) != 0)
		{
			return String(buffer, size);
		}
		else
		{
			return Empty();
		}
	#else
		return Process::getEnvironmentVariable("LOGNAME");
	#endif
}



String User::getHomeDirectory()
{
	#ifdef BL_PLATFORM_WIN32
		return Process::getEnvironmentVariable("USERPROFILE") + '/';
	#else
		return Process::getEnvironmentVariable("HOME") + '/';
	#endif
}



} // namespace System
} // namespace BaseLib
