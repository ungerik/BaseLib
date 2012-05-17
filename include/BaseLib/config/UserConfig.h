/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_UserConfig_h
#define BaseLib_UserConfig_h



// Put your configurations here...

#define BL_DEFAULT_STRING_IMPLEMENTATION_IS_UNICODE
#define BL_NO_EMPTY_STRING_OPTIMIZATION

// #define BL_NO_MULTITHREADING
// #define BL_MATH_WITHOUT_STRINGS

#ifdef BL_DEBUG
	#define BL_MATH_INITILIZED_CHECK
	#define BL_MATH_RANGE_CHECK
#endif

// #define BL_NO_ICU // Doesn't work yet. Need a replacement for NumberFormat first

/*
Define BL_NO_X87_ASM_ROUND if you want to use the generic C++ round functions above
instead of the specialized x87 Assember versions below
*/
//#define BL_NO_X87_ASM_ROUND


#define BL_PRIMITIVE_TYPES_USE_TYPEDEF
//#define BL_PRIMITIVE_TYPES_USE_VERBOSE_TYPES


//#define BL_MATH_DOUBLE_PRECISION


#endif // #ifndef BaseLib_UserConfig_h
