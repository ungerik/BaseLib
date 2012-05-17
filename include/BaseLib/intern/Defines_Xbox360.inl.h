/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Defines.h



#if defined(_XBOX_VER) && (_XBOX_VER >= 200)

	#define BL_PLATFORM_XBOX360

	#define BL_PASS_IN_REGISTER __declspec(passinreg)

#endif

