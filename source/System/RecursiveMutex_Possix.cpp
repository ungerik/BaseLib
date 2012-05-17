/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/RecursiveMutex.h"
#ifndef BL_PLATFORM_WIN32



namespace BaseLib {
namespace System {



RecursiveMutex::RecursiveMutex()
{
	BL_STATIC_ASSERT_NOT_IMPLEMENTED
}



RecursiveMutex::~RecursiveMutex()
{
	BL_STATIC_ASSERT_NOT_IMPLEMENTED
}



} // namespace System
} // namespace BaseLib



#endif // #ifndef BL_PLATFORM_WIN32