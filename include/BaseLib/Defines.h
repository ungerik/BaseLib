/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Defines_h
#define BaseLib_Defines_h



#include <stddef.h>



namespace BaseLib {



///////////////////////////////////////////////////////////////////////////////
// Export statements:

#ifdef STATIC
	#define BL_EXPORT
#else
	#ifdef BASELIB_EXPORTS
		#define BL_EXPORT __declspec( dllexport )
	#else
		#define BL_EXPORT __declspec( dllimport )
	#endif
#endif



///////////////////////////////////////////////////////////////////////////////
// Debug:

#if defined(_DEBUG)
	#define BL_DEBUG
#else
	#define BL_RELEASE
#endif



///////////////////////////////////////////////////////////////////////////////
// Compiler:

#if defined(_MSC_VER)
	#define BL_COMPILER_MSVC
	#ifdef __CPPRTTI
		#define COMPILED_WITH_RTTI
	#endif

#elif defined(__GCC__)
	#define BL_COMPILER_GCC)

#elif defined(__SNC__)
	#define BL_COMPILER_SNC

#elif defined(__CWCC__)
	#define BL_COMPILER_MWCW

#endif



///////////////////////////////////////////////////////////////////////////////
// CPU family:

#if defined(BL_COMPILER_MSVC)
	#if defined(_M_IX86)
		#define BL_CPU_X86

	#elif defined(_M_X64)
		#define BL_CPU_X64

	#elif defined(_M_IA64)
		#define BL_CPU_IA64

	#elif defined(_M_PPC)
		#define BL_CPU_PPC

	#endif
#endif

// TODO
//#define BL_CPU_PPC
//#define BL_CPU_PPC64
//#define BL_CPU_SPE
//#define BL_ARM9
//#define BL_XSCALE
//#define BL_ARM11



///////////////////////////////////////////////////////////////////////////////
// CPU bit and endian:

#if defined(BL_CPU_X64) || defined(BL_CPU_PPC64)
	#define BL_CPU_64BIT
#else
	#define BL_CPU_32BIT
#endif

#if defined(BL_CPU_PPC)
	#define BL_CPU_BIG_ENDIAN
#else
	#define BL_CPU_SMALL_ENDIAN
#endif



///////////////////////////////////////////////////////////////////////////////
// CPU extensions:

#define BL_CPU_EXT_FPU // TODO

#ifdef BL_CPU_X64
	#define BL_CPU_EXT_MMX
	#define BL_CPU_EXT_SSE
	#define BL_CPU_EXT_SSE2
#else if (defined(BL_CPU_X86)
	#define BL_CPU_EXT_MMX
	#ifdef BL_COMPILER_MSVC
		#if (_M_IX86_FP == 1)
			#define BL_CPU_EXT_SSE
		#else if (_M_IX86_FP == 2)
			#define BL_CPU_EXT_SSE2
		#endif
	#endif
#endif

//#define BL_CPU_EXT_SSE3 // todo
//#define BL_CPU_EXT_SSE4
//#define BL_CPU_EXT_SSE5


//#define BL_CPU_EXT_ALTIVEC
//#define BL_CPU_EXT_VMX128
//#define BL_CPU_EXT_SPE



///////////////////////////////////////////////////////////////////////////////
// Platform:

#include "BaseLib/intern/Defines_Linux.inl.h"
#include "BaseLib/intern/Defines_MacOS.inl.h"
#include "BaseLib/intern/Defines_PS2.inl.h"
#include "BaseLib/intern/Defines_PS3.inl.h"
#include "BaseLib/intern/Defines_PSP.inl.h"
#include "BaseLib/intern/Defines_Wii.inl.h"
#include "BaseLib/intern/Defines_Win32.inl.h"
#include "BaseLib/intern/Defines_Xbox.inl.h"
#include "BaseLib/intern/Defines_Xbox360.inl.h"



///////////////////////////////////////////////////////////////////////////////
// Inline assembler:

#ifdef BL_COMPILER_GCC
	#define BL_ASM(a) do { __asm("a") } while (false)
#else
	#define BL_ASM(a) do { __asm {a} } while (false)
#endif



#if defined(BL_CPU_X86) || defined(BL_CPU_X64)
	#define BL_NOP BL_ASM(nop);
	#define BL_BREAKPOINT BL_ASM(int 3);
#else
	#define BL_NOP
	#define BL_BREAKPOINT
#endif



///////////////////////////////////////////////////////////////////////////////
// Packing:

#ifdef BL_COMPILER_MSVC
	#define BL_PACKED
	#define BL_BEGIN_PACKED #pragma pack(push, 0)
	#define BL_END_PACKED #pragma pack(pop)
#else
	#define BL_PACKED __attribute__((packed))
	#define BL_BEGIN_PACKED
	#define BL_END_PACKED
#endif



///////////////////////////////////////////////////////////////////////////////
// Argument passing:

#ifdef BL_COMPILER_MSVC
	#define BL_RESTRICT __restrict
#else
	#define BL_RESTRICT __restrict__
#endif


#ifndef BL_PASS_IN_REGISTER
	#define BL_PASS_IN_REGISTER
#endif


#ifdef BL_COMPILER_MSVC
	#define BL_PURE
#else
	#define BL_PURE __attribute__((pure))
#endif



///////////////////////////////////////////////////////////////////////////////
// Memory alignment:

#ifndef BL_CACHE_LINE_SIZE
	#define BL_CACHE_LINE_SIZE 32
#endif

#ifndef BL_SIMD_ALIGN_SIZE
	#define BL_SIMD_ALIGN_SIZE 16
#endif


#ifdef BL_COMPILER_MSVC
	#define BL_ALIGN(Type, bytes) __declspec(align(bytes)) Type
	#define BL_ALIGNMENT_OF(Type) __alignof(Type)
#else // GCC, MWCW, SNC
	#define BL_ALIGN(Type, bytes) Type __attribute__((aligned(bytes)))
	#define BL_ALIGNMENT_OF(Type) __alignof__(Type)
#endif

#define BL_ALIGN_4(object) BL_ALIGN(object, 4)
#define BL_ALIGN_8(object) BL_ALIGN(object, 8)
#define BL_ALIGN_16(object) BL_ALIGN(object, 16)
#define BL_ALIGN_32(object) BL_ALIGN(object, 32)
#define BL_ALIGN_128(object) BL_ALIGN(object, 128)
#define BL_ALIGN_TO_CACHE(object) BL_ALIGN(object, BL_CACHE_LINE_SIZE)
#define BL_ALIGN_SIMD(object) BL_ALIGN(object, BL_SIMD_ALIGN_SIZE)



///////////////////////////////////////////////////////////////////////////////
// For each:

#define foreach(IteratorType, iterator, container) for (IteratorType iterator = container.begin(); iterator != container.end(); ++iterator)

#define foreachReverse(IteratorType, iterator, container) for (IteratorType iterator = container.reverseBegin(); iterator != container.reverseEnd(); ++iterator)




///////////////////////////////////////////////////////////////////////////////
// Exception handling:

#ifdef BL_COMPILER_MSVC
	#ifndef _CPPUNWIND
		#define BL_NO_EXCEPTIONS
	#endif
#endif



///////////////////////////////////////////////////////////////////////////////
// Mark virtual methods as override:

#ifdef override
	#undef override
#endif

#define override virtual



///////////////////////////////////////////////////////////////////////////////
// Assert on/off:

#ifdef BL_DEBUG
	#define BL_USE_ASSERTS
#endif

#define BL_USE_STATIC_ASSERTS



///////////////////////////////////////////////////////////////////////////////
// User configuration:

#include "BaseLib/config/UserConfig.h"



///////////////////////////////////////////////////////////////////////////////
// Asserts:

namespace PrivateStaticAssert {

	template<bool>
	struct CompileTimeCheck {
		inline CompileTimeCheck(...)
		{
		}
	};

	template<>
	struct CompileTimeCheck<false> {
	};
}

#ifdef BL_USE_STATIC_ASSERTS
	#define BL_STATIC_ASSERT(test, errorMessage) \
		class STATIC_ASSERT_##errorMessage { \
			struct ERROR_##errorMessage {}; \
			typedef PrivateStaticAssert::CompileTimeCheck<!!(test)> Check; \
			void testFunction() \
			{ \
				Check check = Check(ERROR_##errorMessage()); \
				sizeof(check); \
			} \
		}
#else
	#define BL_STATIC_ASSERT(test, errorMessage)
#endif

#define BL_STATIC_ASSERT_NOT_IMPLEMENTED BL_STATIC_ASSERT(false, "Not implemented!");



#define BL_WSTRING_HELPER(s) L##s
#define BL_WSTRING(s) BL_WSTRING_HELPER(s)



#ifdef BL_USE_ASSERTS
	#define BL_VERBOSE_ASSERT(test, errorMessage) (void)( (!!(test)) || (_wassert(BL_WSTRING(errorMessage), BL_WSTRING(__FILE__), __LINE__), 0) )		
#else
	#define BL_VERBOSE_ASSERT(test, errorMessage)
#endif

#define BL_ASSERT(test) BL_VERBOSE_ASSERT(test, "Assertion failed: " BL_WSTRING(#test))

#define BL_ASSERT_NEVER_REACHED BL_VERBOSE_ASSERT(false, "Never should reach this code!");

#define BL_ASSERT_NOT_IMPLEMENTED BL_VERBOSE_ASSERT(false, "Not implemented!");



///////////////////////////////////////////////////////////////////////////////
// Exception handling:

#ifdef BL_NO_EXCEPTIONS
	#define try if (true)
	#define catch(e) for (e; false; )
	#define throw
#endif



} // namespace BaseLib



#endif // #ifndef BaseLib_Defines_h
