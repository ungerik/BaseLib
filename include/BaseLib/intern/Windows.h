/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifdef _WIN32
#ifndef BaseLib_Windows_h
#define BaseLib_Windows_h



#ifdef _WIN32_WINNT
	#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0501 // Windows XP
//#define _WIN32_WINNT 0x0502 // Windows 2003

#ifdef _WIN32_FUSION
	#undef _WIN32_FUSION
#endif
#define _WIN32_FUSION 0x0100

#ifdef WINVER
	#undef WINVER
#endif
#define WINVER _WIN32_WINNT



#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define ISOLATION_AWARE_ENABLED 1



#include <windows.h>



#ifdef byte
	#undef byte
#endif



#endif // #ifndef BaseLib_Windows_h
#endif // #ifdef _WIN32
