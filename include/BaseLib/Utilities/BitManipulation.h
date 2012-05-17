/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_BitManipulation_h
#define BaseLib_Utilities_BitManipulation_h



#include "BaseLib/intern/Windows.h"
#include <limits>
#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {




/**
Returns a number where one specified bit is set.
*/
template<typename T>
inline T bit(const T bitToSet)
{
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);
	if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(bitToSet >= 0);
	BL_ASSERT(bitToSet < sizeof(T)*8);

	return 1 << bitToSet;
}



/**
Returns a number where n lower bits are set.
*/
template<typename T>
inline T bits(const T bitsToSet)
{
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);
	if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(bitsToSet >= 0);
	BL_ASSERT(bitsToSet <= sizeof(T)*8);

	if (bitsToSet < sizeof(T)*8)
	{
		return bit(bitsToSet) - 1;
	}
	else
	{
		return static_cast<T>(-1);
	}
}



/**
Returns the high-half of a variable.
*/
inline uint8& hi(uint16& value)
{
	return reinterpret_cast<uint8*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint8& lo(uint16& value)
{
	return reinterpret_cast<uint8*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline uint16& hi(uint32& value)
{
	return reinterpret_cast<uint16*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint16& lo(uint32& value)
{
	return reinterpret_cast<uint16*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline uint32& hi(uint64& value)
{
	return reinterpret_cast<uint32*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint32& lo(uint64& value)
{
	return reinterpret_cast<uint32*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline uint8& hi(int16& value)
{
	return reinterpret_cast<uint8*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint8& lo(int16& value)
{
	return reinterpret_cast<uint8*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline uint16& hi(int32& value)
{
	return reinterpret_cast<uint16*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint16& lo(int32& value)
{
	return reinterpret_cast<uint16*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline uint32& hi(int64& value)
{
	return reinterpret_cast<uint32*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline uint32& lo(int64& value)
{
	return reinterpret_cast<uint32*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint8& hi(const uint16& value)
{
	return reinterpret_cast<const uint8*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint8& lo(const uint16& value)
{
	return reinterpret_cast<const uint8*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint16& hi(const uint32& value)
{
	return reinterpret_cast<const uint16*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint16& lo(const uint32& value)
{
	return reinterpret_cast<const uint16*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint32& hi(const uint64& value)
{
	return reinterpret_cast<const uint32*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint32& lo(const uint64& value)
{
	return reinterpret_cast<const uint32*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint8& hi(const int16& value)
{
	return reinterpret_cast<const uint8*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint8& lo(const int16& value)
{
	return reinterpret_cast<const uint8*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint16& hi(const int32& value)
{
	return reinterpret_cast<const uint16*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint16& lo(const int32& value)
{
	return reinterpret_cast<const uint16*>(&value)[0];
}



/**
Returns the high-half of a variable.
*/
inline const uint32& hi(const int64& value)
{
	return reinterpret_cast<const uint32*>(&value)[1];
}



/**
Returns the low-half of a variable.
*/
inline const uint32& lo(const int64& value)
{
	return reinterpret_cast<const uint32*>(&value)[0];
}



/**
Returns a pointer as int.
@param pointer Pointer
*/
inline pint& ptr2int(void*& pointer)
{
	return memoryAs<pint>(&pointer, 0);
}



/**
Returns a pointer as int.
@param pointer Pointer
*/
inline const pint& ptr2int(void* const& pointer)
{
	return memoryAs<pint>(&pointer, 0);
}


/**
Returns a pointer as int.
@param pointer Pointer
*/
inline pint& ptr2int(const void*& pointer)
{
	return memoryAs<pint>(&pointer, 0);
}



/**
Returns a pointer as int.
@param pointer Pointer
*/
inline const pint& ptr2int(const void* const& pointer)
{
	return memoryAs<pint>(&pointer, 0);
}



/**
Returns a int as pointer.
@param integer Integer
*/
inline void*& int2ptr(int& integer)
{
	return memoryAs<void*>(&integer, 0);
}


/**
Returns a int as pointer.
@param integer Integer
*/
inline const void*& int2constptr(int& integer)
{
	return memoryAs<const void*>(&integer, 0);
}



/**
Returns a int as pointer.
@param integer Integer
*/
inline void* const& int2ptr(const int& integer)
{
	return memoryAs<void*>(&integer, 0);
}


/**
Returns a int as pointer.
@param integer Integer
*/
inline const void* const& int2constptr(const int& integer)
{
	return memoryAs<const void*>(&integer, 0);
}


/**
@todo doku
*/
struct BL_EXPORT HashData {

	HashData(const void* newData, int newByteCount)
		: data(newData)
		, byteCount(newByteCount)
	{
	}

	const void* data;
	int byteCount;
};



/**
@todo doku
*/
template<class T>
inline HashData getHashData(const T& data)
{
	return HashData(&data, sizeof(T));
}



inline int hash(const void* data, int bytes)
{
	BL_ASSERT_NEVER_REACHED
	return 0;
}



template<typename T>
inline int hash(const T& value)
{
	return hash(&value, sizeof(value));
}



/**
@todo doku
*/
BL_EXPORT uint32 crc32(void * buffer, int length, uint32 crc = 0);



#ifdef BL_PLATFORM_WIN32

	inline const LARGE_INTEGER& makeLargeInt(const int64& value)
	{
		return *reinterpret_cast<const LARGE_INTEGER*>(static_cast<const void*>(&value));
	}

	inline LARGE_INTEGER& makeLargeInt(int64& value)
	{
		return *reinterpret_cast<LARGE_INTEGER*>(static_cast<void*>(&value));
	}

#endif



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_BitManipulation_h

