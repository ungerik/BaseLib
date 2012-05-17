/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_ErrorHandling_ErrorDefines_h
#define BaseLib_ErrorHandling_ErrorDefines_h



#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace ErrorHandling {




#define NAME_VALUE(argument) #argument, argument



//#define ALWAYS_ERROR_AT


#if defined(_DEBUG) || defined(ALWAYS_ERROR_AT)
	#define LINE_MAKER_(l) #l
	#define LINE_MAKER(l) LINE_MAKER_(l)
	#define ERROR_AT " Error at:\n" __FILE__ "(" LINE_MAKER(__LINE__) ")"
#else
    #define ERROR_AT " (Error)"
#endif

#ifdef BL_PLATFORM_WIN32
	#define SYSTEM_ERROR ( BaseLib::Strings::String("\n Last Windows-Error: ").append(getLastWindowsError()).append(BaseLib::Strings::String(" ")) )
#else
	#define SYSTEM_ERROR
#endif






} // namespace ErrorHandling
} // namespace BaseLib



#endif // #ifndef BaseLib_ErrorHandling_ErrorDefines_h