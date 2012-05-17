/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_RecursiveMutex_h
#define BaseLib_System_RecursiveMutex_h



#include "BaseLib/System/VoidMutex.h"



#ifdef BL_NO_MULTITHREADING
	typedef VoidMutex RecursiveMutex;
#else
	#ifdef BL_PLATFORM_WIN32
		#include "BaseLib/System/RecursiveMutex_Win32.inl.h"
	#else
		#include "BaseLib/System/RecursiveMutex_Possix.inl.h"
	#endif
#endif




namespace BaseLib {
namespace System {



template<bool THREADSAFE>
struct ThreadsafeChooser;



template<>
struct ThreadsafeChooser<true> {

	typedef BaseLib::System::RecursiveMutex RecursiveMutex;
};



template<>
struct ThreadsafeChooser<false> {

	typedef VoidMutex RecursiveMutex;
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_RecursiveMutex_h
