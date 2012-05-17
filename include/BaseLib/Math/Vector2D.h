/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Vector2D_h
#define BaseLib_Math_Vector2D_h



#include "BaseLib/Math/Common.h"



namespace BaseLib {
namespace Math {



template<typename T> struct Vector3DT;



template<typename T>
struct Vector2DT {

	typedef typename T ValueType;

	struct Addition {
		const Vector2DT<T>& left;
		const Vector2DT<T>& right;
		inline explicit Addition(const Vector2DT<T>& l, const Vector2DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Subtraction {
		const Vector2DT<T>& left;
		const Vector2DT<T>& right;
		inline explicit Subtraction(const Vector2DT<T>& l, const Vector2DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Multiplication {
		const Vector2DT<T>& left;
		const Vector2DT<T>& right;
		inline explicit Multiplication(const Vector2DT<T>& l, const Vector2DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct ScalarMultiplication {
		const Vector2DT<T>& left;
		const T& right;
		inline explicit ScalarMultiplication(const Vector2DT<T>& l, const T& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Division {
		const Vector2DT<T>& left;
		const Vector2DT<T>& right;
		inline explicit Division(const Vector2DT<T>& l, const Vector2DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	union {
		struct {
			T x;
			T y;
		};
		T values[2];
	};

	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline Vector2DT<T>()
	{
		setUninitialized();
	}

	inline Vector2DT<T>(T newX, T newY)
		: x(newX)
		, y(newY)
	{
		setInitialized();
	}

	inline explicit Vector2DT<T>(const T sourceArray[2])
		: x(sourceArray[0])
		, y(sourceArray[1])
	{
		setInitialized();
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline Vector2DT<T>(const String& string)
		: x(0)
		, y(0)
	{
		operator =(string);
	}

	inline Vector2DT<T>& operator =(const String& right)
	{
		StringTokenizer tokenizer(right);
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(x); else x = 0;
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(y); else y = 0;
		setInitialized();
		return *this;
	}

	operator String() const
	{
		assertInitialized();
		return String::createFrom(x) + ' ' + String::createFrom(y);
	}
#endif

	inline Vector2DT<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline Vector2DT<T>& assignFromArray(const T source[2])
	{
		x = source[0];
		y = source[1];
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>(Zero)
	{
		setZero();
	}

	inline Vector2DT<T>& operator =(Zero)
	{
		return setZero();
	}

	inline Vector2DT<T>(UnitX)
	{
		setUnitX();
	}

	inline Vector2DT<T>& operator =(UnitX)
	{
		return setUnitX();
	}

	inline Vector2DT<T>(UnitY)
	{
		setUnitY();
	}

	inline Vector2DT<T>& operator =(UnitY)
	{
		return setUnitY();
	}

	inline Vector2DT<T>& setZero()
	{
		x = 0;
		y = 0;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setMinimum()
	{
		x = -std::numeric_limits<T>::max();
		y = -std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setMaximum()
	{
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& setUnitX()
	{
		x = 1;
		y = 0;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& setUnitY()
	{
		x = 0;
		y = 1;
		setInitialized();
		return *this;
	}

	inline operator Vector3DT<T>() const
	{
		assertInitialized();
		return Vector3DT<T>(x, y, 0);
	}

	inline Vector2DT<T>(const Addition& other)
	{
		operator =(other);
	}

	inline Vector2DT<T>(const Subtraction& other)
	{
		operator =(other);
	}

	inline Vector2DT<T>(const Multiplication& other)
	{
		operator =(other);
	}

	inline Vector2DT<T>(const ScalarMultiplication& other)
	{
		operator =(other);
	}

	inline Vector2DT<T>(const Division& other)
	{
		operator =(other);
	}

	inline Vector2DT<T>& operator =(const Addition& right)
	{
		x = right.left.x + right.right.x;
		y = right.left.y + right.right.y;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& operator =(const Subtraction& right)
	{
		x = right.left.x - right.right.x;
		y = right.left.y - right.right.y;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& operator =(const Multiplication& right)
	{
		x = right.left.x * right.right.x;
		y = right.left.y * right.right.y;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& operator =(const ScalarMultiplication& right)
	{
		x = right.left.x * right.right;
		y = right.left.y * right.right;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& operator =(const Division& right)
	{
		x = right.left.x / right.right.x;
		y = right.left.y / right.right.y;
		setInitialized();
		return *this;
	}

	inline Vector2DT<T>& operator -()
	{
		assertInitialized();
		x = -x;
		y = -y;
		return *this;
	}

	inline T getSquareLength() const
	{
		assertInitialized();
		return x*x + y*y;
	}

	inline T getLength() const
	{
		return sqrt(getSquareLength());
	}

	inline bool isUnitLength(T squareEpsilon = static_cast<T>(0.001)) const
	{
		const T squareLength = getSquareLength();
		return inRange(squareLength, 1 - squareEpsilon, 1 + squareEpsilon);
	}

	inline Vector2DT<T>& normalize()
	{
		const T squareLength = getSquareLength();
		return (squareLength != 0 && squareLength != 1) ? operator *=(invSqrt(squareLength)) : *this;
	}

	inline Vector2DT<T>& rotate(T angle)
	{
		assertInitialized();
		const T sinus = sin(angle);
		const T cosinus = cos(angle);
		const T xNew = x * cosinus - y * sinus;
		const T yNew = x * sinus + y * cosinus;
		x = xNew;
		y = yNew;
		return *this;
	}

	inline Vector2DT<T>& rotateAround(const Vector2DT<T>& rotationCenter, T angle)
	{
		operator -=(rotationCenter);
		rotate(angle);
		operator +=(rotationCenter)
		return *this;
	}

	inline Vector2DT<T>& rotate90DegreesLeft() const
	{
		assertInitialized();
		const T oldX = x;
		x = -y;
		y = oldX;
		return *this;
	}

	inline Vector2DT<T>& rotate90DegreesRight() const
	{
		assertInitialized();
		const T oldX = x;
		x = y;
		y = -oldX;
		return *this;
	}

	inline bool isZero() const
	{
		assertInitialized();
		return x == 0 && y == 0;
	}

	inline T directionAngle() const
	{
		assertInitialized();
		return atan2(y, x);
	}

	inline Vector2DT<T>& operator +=(const Vector2DT<T>& right)
	{
		assertInitialized();
		x += right.x;
		y += right.y;
		return *this;
	}

	inline Vector2DT<T>& operator -=(const Vector2DT<T>& right)
	{
		assertInitialized();
		x -= right.x;
		y -= right.y;
		return *this;
	}

	inline Vector2DT<T>& operator *=(const Vector2DT<T>& right)
	{
		assertInitialized();
		x *= right.x;
		y *= right.y;
		return *this;
	}

	inline Vector2DT<T>& operator /=(const Vector2DT<T>& right)
	{
		assertInitialized();
		x /= right.x;
		y /= right.y;
		return *this;
	}

	inline Vector2DT<T>& operator *=(const T& right)
	{
		assertInitialized();
		x *= right;
		y *= right;
		return *this;
	}

	inline Vector2DT<T>& operator /=(const T& right)
	{
		BL_ASSERT(right != 0);
		assertInitialized();
		return operator *=(1 / right);
	}

	inline bool operator ==(const Vector2DT<T>& right) const
	{
		assertInitialized();
		return x == right.x && y == right.y;
	}

	inline bool operator !=(const Vector2DT<T>& right) const
	{
		return !(operator ==(right));
	}
};



typedef Vector2DT<float> Vector2Df;
typedef Vector2DT<double> Vector2Dd;

#ifdef BL_MATH_DOUBLE_PRECISION
	typedef Vector2Dd Vector2D;
#else
	typedef Vector2Df Vector2D;
#endif



template<typename T>
inline typename Vector2DT<T>::Addition operator +(const Vector2DT<T>& left, const Vector2DT<T>& right)
{
	return Vector2DT<T>::Addition(left, right);
}



template<typename T>
inline typename Vector2DT<T>::Subtraction operator -(const Vector2DT<T>& left, const Vector2DT<T>& right)
{
	return Vector2DT<T>::Subtraction(left, right);
}



template<typename T>
inline typename Vector2DT<T>::Multiplication operator *(const Vector2DT<T>& left, const Vector2DT<T>& right)
{
	return Vector2DT<T>::Multiplication(left, right);
}



template<typename T>
inline typename Vector2DT<T>::ScalarMultiplication operator *(const Vector2DT<T>& left, const T& right)
{
	return Vector2DT<T>::ScalarMultiplication(left, right);
}



template<typename T>
inline typename Vector2DT<T>::Sivision operator /(const Vector2DT<T>& left, const Vector2DT<T>& right)
{
	return Vector2DT<T>::Sivision(left, right);
}



template<typename T>
inline T dotProduct(const Vector2DT<T>& left, const Vector2DT<T>& right)
{
	return left.x * right.x + left.y * right.y;
}



template<typename T>
inline T angle(const Vector2DT<T>& unitVector1, const Vector2DT<T>& unitVector2)
{
	BL_ASSERT(unitVector1.isUnitLength() == true && unitVector2.isUnitLength() == true);
	return acos(dotProduct(unitVector1, unitVector2));
}



template<typename T>
inline bool isLeftWinding(const Vector2DT<T>& vector1, const Vector2DT<T>& vector2)
{
	const T angle1 = vector1.directionAngle();
	const T angle2 = vector2.clone().rotate(-angle1).directionAngle();
	return angle2 > static_cast<T>(0);
}



template<typename T>
inline bool isRightWinding(const Vector2DT<T>& vector1, const Vector2DT<T>& vector2)
{
	const T angle1 = vector1.directionAngle();
	const T angle2 = vector2.clone().rotate(-angle1).directionAngle();
	return angle2 < static_cast<T>(0);
}



template<typename T>
inline Vector2DT<T> min(const Vector2DT<T>& vector1, const Vector2DT<T>& vector2)
{
	return Vector2DT<T>(min(vector1.x, vector2.x), min(vector1.y, vector2.y));
}



template<typename T>
inline Vector2DT<T> max(const Vector2DT<T>& vector1, const Vector2DT<T>& vector2)
{
	return Vector2DT<T>(max(vector1.x, vector2.x), max(vector1.y, vector2.y));
}



} // namespace Math
} // namespace BaseLib



namespace BaseLib {
	namespace TypeTraits {

		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Vector2Df)
		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Vector2Dd)

	}
}



#endif // #ifndef BaseLib_Math_Vector2D_h
