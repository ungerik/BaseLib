/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Common_h
#define BaseLib_Common_h



#include "BaseLib/Types.h"
#include <memory.h>
#include <assert.h>
#include <wchar.h>



namespace BaseLib {



///////////////////////////////////////////////////////////////////////////////
// Cache functions:

inline void markCacheForOverwrite(void* address, int byteCount)
{
	BL_ASSERT_NOT_IMPLEMENTED
	#ifdef XBOX360
		BL_ASSERT_NEVER_REACHED
		__dcbz128(0, address); // TODO
	#endif
}



inline void flushCache(void* address, int byteCount)
{
	BL_ASSERT_NOT_IMPLEMENTED
	#ifdef XBOX360
		BL_ASSERT_NEVER_REACHED
		__dcbf(0, address); // TODO
	#endif
}



inline void prefetchCache(void* address, int byteCount)
{
	BL_ASSERT_NOT_IMPLEMENTED
	#ifdef XBOX360
		BL_ASSERT_NEVER_REACHED
		__dcbt(0, address); // TODO
	#endif
}



///////////////////////////////////////////////////////////////////////////////
// memCopy():

inline void memCopy(void* BL_RESTRICT destination, const void* source, int byteCount)
{
	memcpy(destination, source, byteCount);
}



inline void memCopy16Bit(void* BL_RESTRICT destination, const void* source, int wordCount)
{
	wmemcpy((wchar_t*) destination, (const wchar_t*) source, wordCount);
}



inline void memCopy32Bit(void* BL_RESTRICT destination, const void* source, int wordCount)
{
	wmemcpy((wchar_t*) destination, (const wchar_t*) source, wordCount * 2);
}



inline void memCopy64Bit(void* BL_RESTRICT destination, const void* source, int wordCount)
{
	wmemcpy((wchar_t*) destination, (const wchar_t*) source, wordCount * 4);
}



inline void memCopy128Bit(void* BL_RESTRICT destination, const void* source, int wordCount)
{
	wmemcpy((wchar_t*) destination, (const wchar_t*) source, wordCount * 8);
}



///////////////////////////////////////////////////////////////////////////////
// memSet():

template<typename T>
inline void memSet8Bit(void* BL_RESTRICT destination, T value, int byteCount)
{
	memset(destination, value, byteCount);
}



template<typename T>
inline void memSet16Bit(void* BL_RESTRICT destination, T value, int wordCount)
{
	wmemset((wchar_t*) destination, (wchar_t) value, wordCount);
}



template<typename T>
inline void memSet32Bit(void* BL_RESTRICT destination, T value, int wordCount)
{
	if (sizeof(T) < sizeof(int32))
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int32*>(destination)[i] = 0;
			static_cast<T*>(destination)[i] = value;
		}
	}
	else
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int32*>(destination)[i] = *static_cast<int32*>(&value);
		}
	}
-}



template<typename T>
inline void memSet64Bit(void* BL_RESTRICT destination, T value, int wordCount)
{
	if (sizeof(T) < sizeof(int64))
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int64*>(destination)[i] = 0;
			static_cast<T*>(destination)[i] = value;
		}
	}
	else
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int64*>(destination)[i] = *static_cast<int64*>(&value);
		}
	}
}



template<typename T>
inline void memSet128Bit(void* BL_RESTRICT destination, T value, int wordCount)
{
	if (sizeof(T) < sizeof(int64)*2)
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int64*>(destination)[i*2+0] = 0;
			static_cast<int64*>(destination)[i*2+1] = 0;
			static_cast<T*>(destination)[i] = value;
		}
	}
	else
	{
		for (int i = 0; i < wordCount; ++i)
		{
			static_cast<int64*>(destination)[i*2+0] = static_cast<int64*>(&value)[0];
			static_cast<int64*>(destination)[i*2+1] = static_cast<int64*>(&value)[1];
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
// Bit-fields:

#define BL_DEFINE_BIT_GETTER_FUNCTION(variable, bit, name) \
	inline bool is##name() { return (variable & (1 << bit)) != 0; }

#define BL_DEFINE_BIT_GETTER(variable, bit, name) \
	inline bool is##name() const { return (variable & (1 << bit)) != 0; }

#define BL_DEFINE_BIT_SETTER(variable, bit, name) \
	inline void set##name(bool value) \
	{ \
		if (value == true) \
			variable |= (1 << bit); \
		else \
			valiable &= ~(1 << bit); \
	}

#define BL_DEFINE_BIT_GETTER_AND_SETTER(variable, bit, name) \
	BL_DEFINE_BIT_GETTER(variable, bit, name) \
	BL_DEFINE_BIT_SETTER(variable, bit, name)

#define BL_DEFINE_BIT_GETTER_AND_SETTER_FUNCTIONS(variable, bit, name) \
	BL_DEFINE_BIT_GETTER_FUNCTION(variable, bit, name) \
	BL_DEFINE_BIT_SETTER(variable, bit, name)



///////////////////////////////////////////////////////////////////////////////
// Swap:


/**
Swaps two values.
*/
template<typename T>
inline void swap(T& a, T& b)
{
	const T temp = a;
	a = b;
	b = temp;
}



///////////////////////////////////////////////////////////////////////////////
// Pointer casting:

/**
Returns a modified pointer.
*/
template<typename T, typename I>
inline T* offsetPointer(T* baseAddress, I byteOffset)
{
	return reinterpret_cast<T*>(&static_cast<byte *>(static_cast<void*>(baseAddress))[byteOffset]);
}



/**
Returns a modified pointer.
*/
template<typename T, typename I>
inline const T* offsetPointer(const T* baseAddress, I byteOffset)
{
	return reinterpret_cast<const T*>(&static_cast<const byte *>(static_cast<const void*>(baseAddress))[byteOffset]);
}



/**
Returns the offset of a pointer from another pointer.
*/
inline pint pointerOffset(const void* offsetedPointer, const void* basePointer)
{
	return reinterpret_cast<pint>(offsetedPointer) - reinterpret_cast<pint>(basePointer);
}


/**
Returns a memory-location casted to a type.
@param baseAddress Base-address of the memory-location
@param byteOffset Byte-offset from the base-address
*/
template<typename T, typename I>
inline T& memoryAs(void* baseAddress, I byteOffset = 0)
{
	return *offsetPointer(reinterpret_cast<T*>(baseAddress), byteOffset);
}



/**
Returns a memory-location casted to a type.
@param baseAddress Base-address of the memory-location
@param byteOffset Byte-offset from the base-address
*/
template<typename T, typename I>
inline const T& memoryAs(const void* baseAddress, I byteOffset = 0)
{
	return *offsetPointer(reinterpret_cast<const T*>(baseAddress), byteOffset);
}



///////////////////////////////////////////////////////////////////////////////
// Endian:

#ifdef SMALL_ENDIAN
	#undef SMALL_ENDIAN
#endif
#ifdef BIG_ENDIAN
	#undef BIG_ENDIAN
#endif



enum Endian {
	SMALL_ENDIAN,
	BIG_ENDIAN
};



extern const Endian SYSTEM_ENDIAN;



/**
Swaps the endian.
*/
template<typename T>
inline T swapEndian(const T& value)
{
	if (sizeof(T) > 1)
	{
		T result;
		for (int lo = 0; lo < sizeof(T)/2; ++lo)
		{
			const int hi = sizeof(T)-1 - lo;
			memoryAs<byte>(&result, lo) = memoryAs<byte>(&value, hi);
			memoryAs<byte>(&result, hi) = memoryAs<byte>(&value, lo);
		}
		return result;
	}
	else
	{
		return value;
	}
}


#ifdef BL_CPU_SMALL_ENDIAN
	/**
	Converts from system endian to small endian.
	*/
	template<typename T>
	inline T& smallEndian(T& value)
	{
		return value;
	}

	/**
	Converts from system endian to small endian.
	*/
	template<typename T>
	inline const T& smallEndian(const T& value)
	{
		return value;
	}
#else
	/**
	Converts from system endian to small endian.
	*/
	template<typename T>
	inline T smallEndian(T& value)
	{
		return swapEndian(value);
	}

	/**
	Converts from system endian to small endian.
	*/
	template<typename T>
	inline const T smallEndian(const T& value)
	{
		return swapEndian(value);
	}
#endif


#ifdef BL_CPU_SMALL_ENDIAN
	/**
	Converts from system endian to big endian.
	*/
	template<typename T>
	inline T bigEndian(T& value)
	{
		return swapEndian(value);
	}

	/**
	Converts from system endian to big endian.
	*/
	template<typename T>
	inline const T bigEndian(const T& value)
	{
		return swapEndian(value);
	}
#else
	/**
	Converts from system endian to big endian.
	*/
	template<typename T>
	inline T& bigEndian(T& value)
	{
		return value;
	}

	/**
	Converts from system endian to big endian.
	*/
	template<typename T>
	inline const T& bigEndian(const T& value)
	{
		return value;
	}
#endif



} // namespace BaseLib



#endif // BaseLib_Common_h

