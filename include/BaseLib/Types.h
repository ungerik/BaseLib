/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Types_h
#define BaseLib_Types_h



#include "BaseLib/Defines.h"



namespace BaseLib {



#ifdef byte
	#undef byte
#endif



#ifdef BL_PRIMITIVE_TYPES_USE_TYPEDEF

	typedef char char8;
	//typedef unsigned char uchar8;
	typedef wchar_t char16;
	typedef unsigned int char32;

	typedef signed char int8;
	typedef unsigned char uint8;

	typedef short int16;
	typedef unsigned short uint16;

	typedef int int32;
	typedef unsigned int uint32;

	#ifdef _MSC_VER
		//typedef signed __int8 int8;
		//typedef unsigned __int8 uint8;

		//typedef signed __int16 int16;
		//typedef unsigned __int16 uint16;

		//typedef signed __int32 int32;
		//typedef unsigned __int32 uint32;

		typedef signed __int64 int64;
		typedef unsigned __int64 uint64;
	#else
		typedef signed long long int int64;
		typedef unsigned long long int uint64;
	#endif

	typedef bool bool8;
	typedef int16 bool16;
	typedef int32 bool32;
	typedef int64 bool64;

	typedef float float32;
	typedef double float64;

	typedef unsigned int uint;
	typedef int pint;
	typedef unsigned int puint;

	typedef uint8 byte;

#else

	#ifdef BL_PRIMITIVE_TYPES_USE_VERBOSE_TYPES
		///
	#else
		#define char8 char
		#define char16 unsigned short

		#define int8 char 
		#define uint8 unsigned char 

		#define int16 short
		#define uint16 unsigned short

		#define int32 signed int 
		#define uint32 unsigned int 

		#define int64 __int64
		#define uint64 unsigned __int64
	#endif

		#define bool8 bool 
		#define bool16 int16 
		#define bool32 int32 
		#define bool64 int64 

		#define float32 float 
		#define float64 double 

		#define uint unsigned int
		#define pint int
		#define puint unsigned int
#endif



BL_STATIC_ASSERT(sizeof(char8)*8 == 8, Type_char8_MustHaveSizeOf8Bits);
BL_STATIC_ASSERT(sizeof(char16)*8 == 16, Type_char16_MustHaveSizeOf16Bits);
BL_STATIC_ASSERT(sizeof(char32)*8 == 32, Type_char32_MustHaveSizeOf32Bits);
BL_STATIC_ASSERT(sizeof(int8)*8 == 8, Type_int8_MustHaveSizeOf8Bits);
BL_STATIC_ASSERT(sizeof(uint8)*8 == 8, Type_uint8_MustHaveSizeOf8Bits);
BL_STATIC_ASSERT(sizeof(int16)*8 == 16, Type_int16_MustHaveSizeOf16Bits);
BL_STATIC_ASSERT(sizeof(uint16)*8 == 16, Type_uint16_MustHaveSizeOf16Bits);
BL_STATIC_ASSERT(sizeof(int32)*8 == 32, Type_int32_MustHaveSizeOf32Bits);
BL_STATIC_ASSERT(sizeof(uint32)*8 == 32, Type_uint32_MustHaveSizeOf32Bits);
BL_STATIC_ASSERT(sizeof(int64)*8 == 64, Type_int64_MustHaveSizeOf64Bits);
BL_STATIC_ASSERT(sizeof(uint64)*8 == 64, Type_uint64_MustHaveSizeOf64Bits);
BL_STATIC_ASSERT(sizeof(bool8)*8 == 8, Type_bool8_MustHaveSizeOf8Bits);
BL_STATIC_ASSERT(sizeof(bool16)*8 == 16, Type_bool16_MustHaveSizeOf16Bits);
BL_STATIC_ASSERT(sizeof(bool32)*8 == 32, Type_bool32_MustHaveSizeOf32Bits);
BL_STATIC_ASSERT(sizeof(bool64)*8 == 64, Type_bool64_MustHaveSizeOf64Bits);
BL_STATIC_ASSERT(sizeof(float32)*8 == 32, Type_float32_MustHaveSizeOf32Bits);
BL_STATIC_ASSERT(sizeof(float64)*8 == 64, Type_float64_MustHaveSizeOf64Bits);
BL_STATIC_ASSERT(sizeof(uint) == sizeof(unsigned int), Type_uint_MustHaveSizeOf_unsigned_int);
BL_STATIC_ASSERT(sizeof(pint) == sizeof(void*), Type_pint_MustHaveSizeOfPointer);
BL_STATIC_ASSERT(sizeof(puint) == sizeof(void*), Type_puint_MustHaveSizeOfPointer);
BL_STATIC_ASSERT(sizeof(byte) == 1, Type_byte_MustHaveSizeOf1Byte);



extern const bool8 BOOL8_MIN;
extern const bool8 BOOL8_MAX;
extern const bool16 BOOL16_MIN;
extern const bool16 BOOL16_MAX;
extern const bool32 BOOL32_MIN;
extern const bool32 BOOL32_MAX;
extern const bool64 BOOL64_MIN;
extern const bool64 BOOL64_MAX;

extern const float32 FLOAT32_MIN;
extern const float32 FLOAT32_MAX;
extern const float64 FLOAT64_MIN;
extern const float64 FLOAT64_MAX;

extern const uint UINT_MIN;
//extern const uint UINT_MAX;
extern const pint PINT_MIN;
extern const pint PINT_MAX;
extern const puint PUINT_MIN;
extern const puint PUINT_MAX;

extern const byte BYTE_MIN;
extern const byte BYTE_MAX;

extern const char8 CHAR8_MIN;
extern const char8 CHAR8_MAX;
//extern const uchar8 UCHAR8_MIN;
//extern const uchar8 UCHAR8_MAX;
extern const char16 CHAR16_MIN;
extern const char16 CHAR16_MAX;
extern const char32 CHAR32_MIN;
extern const char32 CHAR32_MAX;

extern const int8 INT8_MIN;
extern const int8 INT8_MAX;
extern const uint8 UINT8_MIN;
extern const uint8 UINT8_MAX;

extern const int16 INT16_MIN;
extern const int16 INT16_MAX;
extern const uint16 UINT16_MIN;
extern const uint16 UINT16_MAX;

extern const int32 INT32_MIN;
extern const int32 INT32_MAX;
extern const uint32 UINT32_MIN;
extern const uint32 UINT32_MAX;

extern const int64 INT64_MIN;
extern const int64 INT64_MAX;
extern const uint64 UINT64_MIN;
extern const uint64 UINT64_MAX;



///////////////////////////////////////////////////////////////////////////////
// Marker classes:

struct Empty {};
struct Undefined {};



class BL_EXPORT NonCopyable {
protected:

	inline NonCopyable() {}
	inline ~NonCopyable() {}

private:
	NonCopyable(const NonCopyable&);
	void operator =(const NonCopyable&);
};



class BL_EXPORT StaticClass : public NonCopyable {
private:
	StaticClass();
};



template<bool VAL>
struct BoolResult {
	typedef bool ValueType;
	static const ValueType VALUE = VAL;
};



struct TrueResult : BoolResult<true> {
};



struct FalseResult : BoolResult<false> {
};



namespace TypeTraits {



template<typename T>
struct IsIntegralType : FalseResult {
};

#define BL_DEFINE_ISINTEGRALTYPE(T) \
	template<> struct IsIntegralType<T> : TrueResult {}; \
	template<> struct IsIntegralType<const T> : TrueResult {}; \
	template<> struct IsIntegralType<volatile T> : TrueResult {}; \
	template<> struct IsIntegralType<const volatile T> : TrueResult {};

BL_DEFINE_ISINTEGRALTYPE(int8)
BL_DEFINE_ISINTEGRALTYPE(int16)
BL_DEFINE_ISINTEGRALTYPE(int32)
BL_DEFINE_ISINTEGRALTYPE(int64)
BL_DEFINE_ISINTEGRALTYPE(uint8)
BL_DEFINE_ISINTEGRALTYPE(uint16)
BL_DEFINE_ISINTEGRALTYPE(uint32)
BL_DEFINE_ISINTEGRALTYPE(uint64)
BL_DEFINE_ISINTEGRALTYPE(float32)
BL_DEFINE_ISINTEGRALTYPE(float64)
BL_DEFINE_ISINTEGRALTYPE(bool)
BL_DEFINE_ISINTEGRALTYPE(char8)
//BL_DEFINE_ISINTEGRALTYPE(char16)
//BL_DEFINE_ISINTEGRALTYPE(char32)
BL_DEFINE_ISINTEGRALTYPE(void*)



template<typename T>
struct IsValueType : FalseResult {
};

#define BL_DEFINE_ISVALUETYPE(T) \
	template<> struct IsValueType<T> : TrueResult {}; \
	template<> struct IsValueType<const T> : TrueResult {}; \
	template<> struct IsValueType<volatile T> : TrueResult {}; \
	template<> struct IsValueType<const volatile T> : TrueResult {};

BL_DEFINE_ISVALUETYPE(int8)
BL_DEFINE_ISVALUETYPE(int16)
BL_DEFINE_ISVALUETYPE(int32)
BL_DEFINE_ISVALUETYPE(int64)
BL_DEFINE_ISVALUETYPE(uint8)
BL_DEFINE_ISVALUETYPE(uint16)
BL_DEFINE_ISVALUETYPE(uint32)
BL_DEFINE_ISVALUETYPE(uint64)
BL_DEFINE_ISVALUETYPE(float32)
BL_DEFINE_ISVALUETYPE(float64)
BL_DEFINE_ISVALUETYPE(bool)
BL_DEFINE_ISVALUETYPE(char8)
//BL_DEFINE_ISVALUETYPE(char16)
//BL_DEFINE_ISVALUETYPE(char32)
BL_DEFINE_ISVALUETYPE(void*)



} // namespace TypeTraits



class BL_EXPORT Interface {
public:
	virtual ~Interface();

protected:
	inline Interface() {}
};



struct BL_ALIGN_SIMD(vec4f) {

	typedef float32 ValueType;

	union {
		struct {
			ValueType x;
			ValueType y;
			ValueType z;
			ValueType w;
		};
		struct {
			ValueType r;
			ValueType g;
			ValueType b;
			ValueType a;
		};
		ValueType values[4];
	};
};

namespace TypeTraits {
	BL_DEFINE_ISVALUETYPE(vec4f)
}


struct BL_ALIGN_SIMD(vec4d) {

	typedef float64 ValueType;

	union {
		struct {
			ValueType x;
			ValueType y;
			ValueType z;
			ValueType w;
		};
		struct {
			ValueType r;
			ValueType g;
			ValueType b;
			ValueType a;
		};
		ValueType values[4];
	};
};

namespace TypeTraits {
	BL_DEFINE_ISVALUETYPE(vec4d)
}



struct BL_ALIGN_SIMD(vec4i) {

	typedef int32 ValueType;

	union {
		struct {
			ValueType x;
			ValueType y;
			ValueType z;
			ValueType w;
		};
		struct {
			ValueType r;
			ValueType g;
			ValueType b;
			ValueType a;
		};
		ValueType values[4];
	};
};

namespace TypeTraits {
	BL_DEFINE_ISVALUETYPE(vec4i)
}



template<class T>
class Singleton : public NonCopyable {
public:

	typedef T SingletonType;

	static inline T& getSingleton()
	{
		return *(singleton != NULL ? singleton : new T());
	}

	static inline T* getSingletonOrNull()
	{
		return singleton;
	}

protected:

	inline Singleton<T>()
	{
		BL_ASSERT(singleton == NULL);
		//if (checkArgumentNull(NAME_VALUE(singleton)) == false)
		//{
		//	delete singleton;
		//}
		singleton = static_cast<T*>(this);
	}

	inline ~Singleton<T>()
	{
		BL_ASSERT(singleton != NULL);
		singleton = NULL;
	}

private:

	static T* singleton;

};



template<class T>
typename Singleton<T>::SingletonType* Singleton<T>::singleton = NULL;



} // namespace BaseLib



#endif // #ifndef BaseLib_Types_h