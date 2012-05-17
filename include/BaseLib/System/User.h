/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_User_h
#define BaseLib_System_User_h



#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace System {



namespace User {



using BaseLib::Strings::String;



BL_EXPORT String getName();
BL_EXPORT String getHomeDirectory();



} // namespace User



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_User_h
