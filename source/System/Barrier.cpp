/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Barrier.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



#ifdef BL_PLATFORM_WIN32



Barrier::Barrier()
{
}



#else
#endif



} // namespace System
} // namespace BaseLib
