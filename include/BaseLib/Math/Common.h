/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Core_h
#define BaseLib_Math_Core_h



#include "BaseLib/Types.h"
#include <math.h>
#ifndef BL_MATH_WITHOUT_STRINGS
	#include "BaseLib/Strings/StringTokenizer.h"
#endif



namespace BaseLib {
namespace Math {



#ifndef BL_MATH_WITHOUT_STRINGS
	using BaseLib::Strings::String;
	using BaseLib::Strings::StringTokenizer;
#endif



struct Zero {};
struct UnitX {};
struct UnitY {};
struct UnitZ {};
struct UnitW {};
struct UnitNegativeX {};
struct UnitNegativeY {};
struct UnitNegativeZ {};
struct UnitNegativeW {};
struct Identity {};
struct Minimum {};
struct Maximum {};



#ifdef BL_MATH_INITILIZED_CHECK
	#define BL_MATH_INITILIZED_CHECK_MEMBERS \
		inline void assertInitialized() const \
		{ \
			if (isInitialized() == false) \
			{ \
				notInitializedError(); \
			} \
		} \
		inline void notInitializedError() const \
		{ \
			abort(); \
		} \
		inline bool isInitialized() const \
		{ \
			for (int i = 0; i < sizeof(values)/sizeof(T); ++i) \
			{ \
				if (values[i] == NAN) return false; \
			} \
			return true; \
		} \
		inline void setInitialized() \
		{ \
		} \
		inline void setUninitialized() \
		{ \
			for (int i = 0; i < sizeof(values)/sizeof(T); ++i) \
			{ \
				values[i] = NAN; \
			} \
		}
#else
	#define BL_MATH_INITILIZED_CHECK_MEMBERS \
		inline void assertInitialized() const \
		{ \
		} \
		inline void notInitializedError() const \
		{ \
			abort(); \
		} \
		inline bool isInitialized() const \
		{ \
			return true; \
		} \
		inline void setInitialized() \
		{ \
		} \
		inline void setUninitialized() \
		{ \
		}
#endif



const float64 PI = 3.1415926535897932384626433832795028841971693993751;
const float32 PI_F = static_cast<float32>(PI);

const float64 INVERSE_PI = 1.0 / PI;
const float32 INVERSE_PI_F = static_cast<float32>(INVERSE_PI);

const float64 HALF_PI = PI / 2.0;
const float32 HALF_PI_F = static_cast<float32>(HALF_PI);

const float64 QUARTER_PI = PI / 4.0;
const float32 QUARTER_PI_F = static_cast<float32>(QUARTER_PI);

const float64 TWO_PI = PI * 2.0;
const float32 TWO_PI_F = static_cast<float32>(TWO_PI);

const float64 FOUR_PI = PI * 4.0;
const float32 FOUR_PI_F = static_cast<float32>(FOUR_PI);



inline bool isOdd(uint64 value)
{
	return (value & 1) != 0;
}



inline bool isEven(uint64 value)
{
	return (value & 1) == 0;
}



template<typename T>
inline T roundDownToEven(T value)
{
	return (std::numeric_limits<T>::is_integer == true) ? value & (~1) : static_cast<T>(floor(value * 0.5) * 2.0);
}



template<typename T>
inline T roundUpToEven(T value)
{
	return (std::numeric_limits<T>::is_integer == true) ? (isOdd(value) ? value+1 : value) : static_cast<T>(ceil(value * 0.5) * 2.0);
}



template<typename T>
inline T round(float value)
{
	return static_cast<T>( (std::numeric_limits<T>::is_integer == true) ? value + 0.5f : floorf(value + 0.5f) );
}



template<typename T>
inline T round(double value)
{
	return static_cast<T>( (std::numeric_limits<T>::is_integer == true) ? value + 0.5 : floor(value + 0.5) );
}



template<typename T>
inline T round(long double value)
{
	return static_cast<T>( (std::numeric_limits<T>::is_integer == true) ? value + 0.5 : floor(value + 0.5) );
}



#ifndef BL_NO_X87_ASM_ROUND



template<>
inline int8 round(float value)
{
	int16 result;
	BL_ASM(fld value);
	BL_ASM( fistp result);
	return static_cast<int8>(result);
}

template<>
inline uint8 round(float value)
{
	int16 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint8>(result);
}

template<>
inline int16 round(float value)
{
	int16 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint16 round(float value)
{
	int32 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint16>(result);
}

template<>
inline int32 round(float value)
{
	int32 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint32 round(float value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint32>(result);
}

template<>
inline int64 round(float value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint64 round(float value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint64>(result);
}

template<>
inline float round(float value)
{
	float result;
	BL_ASM( fld value );
	BL_ASM( frndint );
	BL_ASM( fstp result );
	return result;
}

template<>
inline double round(float value)
{
	double result;
	BL_ASM( fld value );
	BL_ASM( frndint );
	BL_ASM( fstp result );
	return result;
}

template<>
inline int8 round(double value)
{
	int16 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<int8>(result);
}

template<>
inline uint8 round(double value)
{
	int16 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint8>(result);
}

template<>
inline int16 round(double value)
{
	int16 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint16 round(double value)
{
	int32 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint16>(result);
}

template<>
inline int32 round(double value)
{
	int32 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint32 round(double value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint32>(result);
}

template<>
inline int64 round(double value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return result;
}

template<>
inline uint64 round(double value)
{
	int64 result;
	BL_ASM( fld value );
	BL_ASM( fistp result );
	return static_cast<uint64>(result);
}

template<>
inline float round(double value)
{
	float result;
	BL_ASM( fld value );
	BL_ASM( frndint );
	BL_ASM( fstp result );
	return result;
}

template<>
inline double round(double value)
{
	double result;
	BL_ASM( fld value );
	BL_ASM( frndint );
	BL_ASM( fstp result );
	return result;
}

#endif // #ifndef BL_NO_X87_ASM_ROUND








/*
unfertig:
void bitCopy(void* dest, int destBitOffset, const void* source, int sourceBitOffset, int bitCount);
void bitCopy(void* dest, const void* source, int sourceBitOffset, int bitCount);
void bitCopy(void* dest, int destBitOffset, const void* source, int bitCount);
*/


template<typename T>
inline bool isPowerOf2(T value)
{
/*
better:

bool IsPowerOfTwo(ulong x)
{
    return (x & (x - 1)) == 0;
}
*/

	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);

	bool bitFound = false;

	for (int i = 0; i < sizeof(value)*8; ++i)
	{
		if ((value & 1) != 0)
		{
			if (bitFound == false)
			{
				bitFound = true;
			}
			else
			{
				return false;
			}
		}
		value >>= 1;
	}

	return bitFound;
}



template<typename T>
inline T roundDownToPowerOf2(T value)
{
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);
	if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(value >= 0);

	for (int i = sizeof(T)*8-1; i >= 0; --i)
	{
		const T mask = 1 << i;

		if ((value & mask) != 0)
		{
			return mask;
		}
	}

	return 0;
}



template<typename T>
inline T roundUpToPowerOf2(T value)
{
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);
	if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(value >= 0);

	int i = 1;
	while (i < value) i <<= 1;
	return i;
}



template<typename T>
inline T log2(T value)
{
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, NO_INTEGER);
	if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(value >= 0);

	for (int i = sizeof(int32)*8-1; i >= 0; --i)
	{
		const int mask = 1 << i;

		if ((value & mask) != 0)
		{
			return i;
		}
	}

	return 0;
}



template<typename T>
inline T exp2(T exponent)
{
	if (std::numeric_limits<T>::is_integer == true)
	{
		if (std::numeric_limits<T>::is_signed == true) BL_ASSERT(exponent >= 0);

		return static_cast<T>(1 << static_cast<int>(exponent));
	}
	else
	{
		return static_cast<T>(pow(2.0, static_cast<double>(exponent)));
	}
}



template<typename T>
inline T sqr(T value)
{
	return value * value;
}



#ifdef min
	#undef min
#endif

#ifdef max
	#undef max
#endif



template<typename R, typename T>
inline R clamp(T value)
{
	BL_STATIC_ASSERT(std::numeric_limits<R>::is_integer == true, NO_INTEGER);
	BL_STATIC_ASSERT(sizeof(R) <= sizeof(T), RESULT_TYPE_LARGER_THAN_ARGUMENT);
	const R maximum = std::numeric_limits<R>::max();
	if (value > maximum) return maximum;
	const R minimum = std::numeric_limits<R>::min();
	if (value < minimum) return minimum;
	return static_cast<R>(value);
}



template<typename T>
inline const T& min(const T& firstObject, const T& secondObject)
{
	return firstObject < secondObject ? firstObject : secondObject;
}



template<typename T>
inline const T& min(const T& firstObject, const T& secondObject, const T& thirdObject)
{
	return min(min(firstObject, secondObject), thirdObject);
}



template<typename T>
inline const T& min(const T& firstObject, const T& secondObject, const T& thirdObject, const T& fourthObject)
{
	return min(min(min(firstObject, secondObject), thirdObject), fourthObject);
}



template<typename T>
inline T min(const T * values, int valueCount)
{
	T minimum = values[0];
	for (int i = 1; i < valueCount; ++i)
	{
		minimum = min(values[i], minimum);
	}
	return minimum;
}



template<typename T>
inline const T& max(const T& firstObject, const T& secondObject)
{
	return firstObject > secondObject ? firstObject : secondObject;
}



template<typename T>
inline const T& max(const T& firstObject, const T& secondObject, const T& thirdObject)
{
	return max(max(firstObject, secondObject), thirdObject);
}



template<typename T>
inline const T& max(const T& firstObject, const T& secondObject, const T& thirdObject, const T& fourthObject)
{
	return max(max(max(firstObject, secondObject), thirdObject), fourthObject);
}



template<typename T>
inline T max(const T * values, int valueCount)
{
	BL_ASSERT(valueCount > 0);
	T maximum = values[0];
	for (int i = 1; i < valueCount; ++i)
	{
		maximum = max(values[i], maximum);
	}
	return maximum;
}



template<typename T>
inline T clamp(T value, T minimum, T maximum)
{
	BL_ASSERT(minimum <= maximum);
	return min(maximum, max(minimum, value));
}



inline float frac(float value)
{
	return value - floorf(value);
}



inline double frac(double value)
{
	return value - floor(value);
}


template<typename T>
inline T sign(T value)
{
	return (value > 0) ? +1 : ((value < 0) ? -1 : 0);
}



template<typename T>
inline bool isValidFloatNumber(T value)
{
	return
		value != +std::numeric_limits<T>::infinity() &&
		value != -std::numeric_limits<T>::infinity() &&
		value != std::numeric_limits<T>::signaling_NaN() &&
		value != std::numeric_limits<T>::quiet_NaN();
}



struct BL_EXPORT NaN {
		
	template<typename T>
	inline operator T() const
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

};



template<typename T>
inline bool operator ==(T left, const NaN& right)
{
	//return left == std::numeric_limits<T>::signaling_NaN() || left == std::numeric_limits<T>::quiet_NaN();
	return _isnan(left) != 0;
}



template<typename T>
inline bool operator ==(const NaN& left, T right)
{
	return _isnan(right) != 0;
}



template<typename T>
inline bool operator !=(T left, const NaN& right)
{
	//return left != std::numeric_limits<T>::signaling_NaN() && left != std::numeric_limits<T>::quiet_NaN();
	return _isnan(left) == 0;
}



template<typename T>
inline bool operator !=(const NaN& left, T right)
{
	return _isnan(right) == 0;
}



#ifdef NAN
	#undef NAN
#endif



extern BL_EXPORT const NaN NAN;



template<typename T>
inline bool equalsWithEpsilon(T left, T right, T epsilon)
{
	return left <= right + epsilon && left >= right - epsilon;
}



template<typename T>
inline bool inRange(T value, T minimum, T maximum)
{
	return value >= minimum && value <= maximum;
}



template<typename T>
inline T invSqrt(T value)
{
	return static_cast<T>(1.0) / sqrt(value);
}



template<typename T>
class Scalar01T : public ValueType {
public:

	inline Scalar01T()
	{
	}

	inline explicit Scalar01T(T newValue)
		: value(newValue)
	{
		assertValueInRange0to1();
	}

	inline void assertValueInRange0to1() const
	{
		#ifdef BL_MATH_RANGE_CHECK
			BL_ASSERT(isInRange() == true);
		#endif
	}

	inline bool isInRange() const
	{
		return inRange(value, static_cast<T>(0), static_cast<T>(1));
	}

	inline operator T()
	{
		return value;
	}

	inline Scalar01T<T>& operator =(const Scalar01T<T>& right)
	{
		value = right.operator T();
		return *this;
	}

private:

	T value;
};



typedef Scalar01T<float> Scalar01f;
typedef Scalar01T<double> Scalar01d;

#ifdef BL_MATH_DOUBLE_PRECISION
	typedef Scalar01d Scalar01;
#else
	typedef Scalar01f Scalar01;
#endif



} // namespace Math
} // namespace BaseLib



#endif // BaseLib_Math_Core_h
