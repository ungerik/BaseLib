/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Vector3D_h
#define BaseLib_Math_Vector3D_h



#include "BaseLib/Math/Vector2D.h"



namespace BaseLib {
namespace Math {



template<typename T> struct Matrix3x3T;
template<typename T> struct Matrix3x4T;
template<typename T> struct Matrix4x4T;
template<typename T> struct QuaternionT;
template<typename T> struct VectorHom3DT;



template<typename T = float>
struct Vector3DT {

	typedef typename T ValueType;

	struct Addition {
		const Vector3DT<T>& left;
		const Vector3DT<T>& right;
		inline explicit Addition(const Vector3DT<T>& l, const Vector3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Subtraction {
		const Vector3DT<T>& left;
		const Vector3DT<T>& right;
		inline explicit Subtraction(const Vector3DT<T>& l, const Vector3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Multiplication {
		const Vector3DT<T>& left;
		const Vector3DT<T>& right;
		inline explicit Multiplication(const Vector3DT<T>& l, const Vector3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct ScalarMultiplication {
		const Vector3DT<T>& left;
		const T& right;
		inline explicit ScalarMultiplication(const Vector3DT<T>& l, const T& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct CrossProduct {
		const Vector3DT<T>& left;
		const Vector3DT<T>& right;
		inline explicit CrossProduct(const Vector3DT<T>& l, const Vector3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	union {
		struct {
			T x;
			T y;
			T z;
		};
		T values[3];
	};


	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline Vector3DT<T>()
	{
		setUninitialized();
	}

	inline Vector3DT<T>(T newX, T newY, T newZ = 0)
		: x(newX)
		, y(newY)
		, z(newZ)
	{
		setInitialized();
	}

	inline explicit Vector3DT<T>(const T source[3])
		: x(source[0])
		, y(source[1])
		, z(source[2])
	{
		setInitialized();
	}

	inline explicit Vector3DT<T>(const Vector2DT<T>& vector2D)
	{
		operator =(vector2D);
	}

	inline Vector3DT<T>(const Addition& right)
	{
		operator =(right);
	}

	inline Vector3DT<T>(const Subtraction& right)
	{
		operator =(right);
	}

	inline Vector3DT<T>(const Multiplication& right)
	{
		operator =(right);
	}

	inline Vector3DT<T>(const ScalarMultiplication& right)
	{
		operator =(right);
	}

	inline Vector3DT<T>(const CrossProduct& right)
	{
		operator =(right);
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline Vector3DT<T>(const String& string)
	{
		operator =(string);
	}

	inline Vector3DT<T>& operator =(const String& right)
	{
		StringTokenizer tokenizer(right);
		if (tokenizer.hasNextToken() == true && tokenizer.nextToken().tryParse(x) == false)	x = 0;
		if (tokenizer.hasNextToken() == true && tokenizer.nextToken().tryParse(y) == false)	x = 0;
		if (tokenizer.hasNextToken() == true && tokenizer.nextToken().tryParse(z) == false)	x = 0;

		//x = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parse<T>() : 0;
		//y = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parse<T>() : 0;
		//z = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parse<T>() : 0;
		setInitialized();
		return *this;
	}

	operator String() const
	{
		assertInitialized();
		return String::createFrom(x) + ' ' + String::createFrom(y) + ' ' + String::createFrom(z);
	}
#endif

	inline Vector3DT<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline Vector3DT<T>& assignFromArray(const T source[3])
	{
		x = source[0];
		y = source[1];
		z = source[2];
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>(Zero)
	{
		setZero();
	}

	inline Vector3DT<T>& operator =(Zero)
	{
		return setZero();
	}

	inline Vector3DT<T>(UnitX)
	{
		setUnitX();
	}

	inline Vector3DT<T>& operator =(UnitX)
	{
		return setUnitX();
	}

	inline Vector3DT<T>(UnitY)
	{
		setUnitY();
	}

	inline Vector3DT<T>& operator =(UnitY)
	{
		return setUnitY();
	}

	inline Vector3DT<T>(UnitZ)
	{
		setUnitZ();
	}

	inline Vector3DT<T>& operator =(UnitZ)
	{
		return setUnitZ();
	}

	inline Vector3DT<T>& setZero()
	{
		x = 0;
		y = 0;
		z = 0;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setMinimum()
	{
		x = -std::numeric_limits<T>::max();
		y = -std::numeric_limits<T>::max();
		z = -std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setMaximum()
	{
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		z = std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setUnitX()
	{
		x = 1;
		y = 0;
		z = 0;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setUnitY()
	{
		x = 0;
		y = 1;
		z = 0;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& setUnitZ()
	{
		x = 0;
		y = 0;
		z = 1;
		setInitialized();
		return *this;
	}

	inline operator VectorHom3DT<T>() const
	{
		assertInitialized();
		return VectorHom3DT<T>(x, y, z, 1);
	}

	inline Vector3DT<T>& operator =(const Vector2DT<T>& right)
	{
		x = right.x;
		y = right.y;
		z = 0;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& operator =(const Addition& right)
	{
		x = right.left.x + right.right.x;
		y = right.left.y + right.right.y;
		z = right.left.z + right.right.z;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& operator =(const Subtraction& right)
	{
		x = right.left.x - right.right.x;
		y = right.left.y - right.right.y;
		z = right.left.z - right.right.z;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& operator =(const Multiplication& right)
	{
		x = right.left.x * right.right.x;
		y = right.left.y * right.right.y;
		z = right.left.z * right.right.z;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& operator =(const ScalarMultiplication& right)
	{
		x = right.left.x * right.right;
		y = right.left.y * right.right;
		z = right.left.z * right.right;
		setInitialized();
		return *this;
	}

	inline Vector3DT<T>& operator =(const CrossProduct& right)
	{
		BL_ASSERT(&right.left != this && &right.right != this);
		x = right.left.y * right.right.z - right.left.z * right.right.y;
		y = right.left.z * right.right.x - right.left.x * right.right.z;
		z = right.left.x * right.right.y - right.left.y * right.right.x;
		setInitialized();
		return *this;
	}

	inline T getSquareLength() const
	{
		assertInitialized();
		return x*x + y*y + z*z;
	}

	inline T getLength() const
	{
		return static_cast<T>(sqrt(getSquareLength()));
	}

	inline bool isUnitLength(T epsilon = static_cast<T>(0.001)) const
	{
		const squareLength = getSquareLength();
		return squareLength >= 1 - epsilon && squareLength <= 1 + epsilon;
	}

	inline Vector3DT<T>& negate()
	{
		assertInitialized();
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline Vector3DT<T>& normalize()
	{
		const T length = getLength();
		if (length != 0 && length != 1) operator /=(length);
		return *this;
	}

	inline bool isZero() const
	{
		assertInitialized();
		return x == 0 && y == 0 && z == 0;
	}

	inline Vector3DT<T> createOrthogonalVector(const Vector3DT<T>& upVector = UnitY()) const
	{
		assertInitialized();
		Vector3DT<T> resultNormal = crossProduct(upVector, *this);

		if (resultNormal.squareLength() < 0.0001f)
		{
			resultNormal = crossProduct(Vector3DT<T>(UnitX()), *this);

			if (resultNormal.squareLength() < 0.0001f)
			{
				resultNormal = crossProduct(Vector3DT<T>(UnitZ()), *this);
			}
		}

		return resultNormal.normalize();
	}

	inline void orthogonalVectors(Vector3DT<T>& firstNormal, Vector3DT<T>& secondNormal, const Vector3DT<T>& upVector = UnitY())
	{
		firstNormal = createOrthogonalVector(upVector);
		secondNormal = Normalization(crossProduct(*this, firstNormal));
	}

	inline Vector3DT<T>& operator +=(const Vector3DT<T>& right)
	{
		assertInitialized();
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	inline Vector3DT<T>& operator -=(const Vector3DT<T>& right)
	{
		assertInitialized();
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	inline Vector3DT<T>& operator *=(const QuaternionT<T>& right)
	{
		return operator *=(Matrix3x3T<T>(right));
		/*		
		right.rotateVector(*this);
		return *this;
		*/
	}

	inline Vector3DT<T>& operator *=(const Matrix3x3T<T>& right)
	{
		assertInitialized();
		Vector3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2);
		return *this;
	}

	inline Vector3DT<T>& operator *=(const Matrix3x4T<T>& right)
	{
		assertInitialized();
		Vector3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2) + right.value(0, 3);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2) + right.value(1, 3);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2) + right.value(2, 3);
		return *this;
	}

	inline Vector3DT<T>& operator *=(const Matrix4x4T<T>& right)
	{
		assertInitialized();
		Vector3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2) + right.value(0, 3);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2) + right.value(1, 3);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2) + right.value(2, 3);
		return *this;
	}

	inline Vector3DT<T>& operator *=(const T& right)
	{
		assertInitialized();
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	inline Vector3DT<T>& operator /=(const T& right)
	{
		BL_ASSERT(right != 0);
		assertInitialized();
		return operator *=(1 / right);
	}

	inline Vector3DT<T>& operator *=(const Vector3DT<T>& right)
	{
		assertInitialized();
		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	inline Vector3DT<T>& operator /=(const Vector3DT<T>& right)
	{
		assertInitialized();
		x /= right.x;
		y /= right.y;
		z /= right.z;
		return *this;
	}

	inline bool operator ==(const Vector3DT<T>& right) const
	{
		assertInitialized();
		return x == right.x && y == right.y && z == right.z;
	}

	inline bool operator !=(const Vector3DT<T>& right) const
	{
		return ! (operator ==(right));
	}
};



typedef Vector3DT<float> Vector3D;
typedef Vector3DT<double> Vector3Dd;



template<typename T>
inline typename const Vector3DT<T>::Addition operator +(const Vector3DT<T>& left, const Vector3DT<T>& right)
{
	return Vector3DT<T>::Addition(left, right);
}



template<typename T>
inline typename const Vector3DT<T>::Subtraction operator -(const Vector3DT<T>& left, const Vector3DT<T>& right)
{
	return Vector3DT<T>::Subtraction(left, right);
}



template<typename T>
inline typename const Vector3DT<T>::Multiplication operator *(const Vector3DT<T>& left, const Vector3DT<T>& right)
{
	return Vector3DT<T>::Multiplication(left, right);
}



template<typename T>
inline typename const Vector3DT<T>::ScalarMultiplication operator *(const Vector3DT<T>& left, const T& right)
{
	return Vector3DT<T>::ScalarMultiplication(left, right);
}



template<typename T>
inline typename const Vector3DT<T>::Multiplication operator *(const T& left, const Vector3DT<T>& right)
{
	return Vector3DT<T>::Multiplication(right, left);
}



/**
The result variable must not be passed as left or right !
(i.e. use resultVariable.clone() instead)
*/
template<typename T>
inline typename Vector3DT<T>::CrossProduct crossProduct(const Vector3DT<T>& left, const Vector3DT<T>& right)
{
	return Vector3DT<T>::CrossProduct(left, right);
}



template<typename T>
inline T dotProduct(const Vector3DT<T>& left, const Vector3DT<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}



template<typename T>
inline T angle(const Vector3DT<T>& unitVector1, const Vector3DT<T>& unitVector2)
{
	BL_ASSERT(unitVector1.isUnitLength() == true && unitVector2.isUnitLength() == true);
	return acos(dotProduct(unitVector1, unitVector2));
}



template<typename T>
inline Vector3DT<T> min(const Vector3DT<T>& vector1, const Vector3DT<T>& vector2)
{
	return Vector3DT<T>(min(vector1.x, vector2.x), min(vector1.y, vector2.y), min(vector1.z, vector2.z));
}



template<typename T>
inline Vector3DT<T> max(const Vector3DT<T>& vector1, const Vector3DT<T>& vector2)
{
	return Vector3DT<T>(max(vector1.x, vector2.x), max(vector1.y, vector2.y), max(vector1.z, vector2.z));
}



} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_Vector3D_h
