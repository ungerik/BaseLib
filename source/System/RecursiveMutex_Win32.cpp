/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/RecursiveMutex.h"
#ifdef BL_PLATFORM_WIN32



namespace BaseLib {
namespace System {



RecursiveMutex::RecursiveMutex()
{
	InitializeCriticalSection(&criticalSection);
}



RecursiveMutex::~RecursiveMutex()
{
	DeleteCriticalSection(&criticalSection);
}



} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32