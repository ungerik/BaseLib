/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Defines.h



#ifdef _WIN32

	#define BL_PLATFORM_WIN32

	// TODO
	//#define BL_PLATFORM_LINUX
	//#define BL_PLATFORM_MACOS
	//#define BL_PLATFORM_PS2
	//#define BL_PLATFORM_PS3
	//#define BL_PLATFORM_PSP
	//#define BL_PLATFORM_WII
	//#define BL_PLATFORM_NDS
	//#define BL_PLATFORM_NGAGE
	//#define BL_PLATFORM_S40
	//#define BL_PLATFORM_S60 



	#if defined(BL_CPU_X86) || defined(BL_CPU_X64)
		#define BL_CACHE_LINE_SIZE 32
	#endif



	#if defined(BL_CPU_X86) || defined(BL_CPU_X64)
		#define BL_SIMD_ALIGN_SIZE 16
	#endif



#endif



