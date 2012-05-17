/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_VectorPad3D_h
#define BaseLib_Math_VectorPad3D_h



#include "BaseLib/Math/Vector3D.h"



namespace BaseLib {
namespace Math {



template<typename T = float>
struct BL_ALIGN_SIMD(VectorPad3DT) {

	typedef typename T ValueType;

	struct Addition {
		const VectorPad3DT<T>& left;
		const VectorPad3DT<T>& right;
		inline explicit Addition(const VectorPad3DT<T>& l, const VectorPad3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Subtraction {
		const VectorPad3DT<T>& left;
		const VectorPad3DT<T>& right;
		inline explicit Subtraction(const VectorPad3DT<T>& l, const VectorPad3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Multiplication {
		const VectorPad3DT<T>& left;
		const VectorPad3DT<T>& right;
		inline explicit Multiplication(const VectorPad3DT<T>& l, const VectorPad3DT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct ScalarMultiplication {
		const VectorPad3DT<T>& left;
		const T& right;
		inline explicit ScalarMultiplication(const VectorPad3DT<T>& l, const T& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct CrossProduct {
		const VectorPad3DT<T>& left;
		const VectorPad3DT<T>& right;
		inline explicit CrossProduct(const VectorPad3DT<T>& l, const VectorPad3DT<T>& r)
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
			T _pad;
		};
		T values[3];
	};


	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline VectorPad3DT<T>()
	{
		setUninitialized();
	}

	inline VectorPad3DT<T>(T newX, T newY, T newZ = 0)
		: x(newX)
		, y(newY)
		, z(newZ)
	{
		setInitialized();
	}

	inline explicit VectorPad3DT<T>(const T source[3])
		: x(source[0])
		, y(source[1])
		, z(source[2])
	{
		setInitialized();
	}

	inline explicit VectorPad3DT<T>(const Vector2DT<T>& vector2D)
	{
		operator =(vector2D);
	}

	inline explicit VectorPad3DT<T>(const Vector3DT<T>& vector3D)
	{
		operator =(vector3D);
	}

	inline VectorPad3DT<T>(const Addition& right)
	{
		operator =(right);
	}

	inline VectorPad3DT<T>(const Subtraction& right)
	{
		operator =(right);
	}

	inline VectorPad3DT<T>(const Multiplication& right)
	{
		operator =(right);
	}

	inline VectorPad3DT<T>(const ScalarMultiplication& right)
	{
		operator =(right);
	}

	inline VectorPad3DT<T>(const CrossProduct& right)
	{
		operator =(right);
	}

	inline VectorPad3DT<T>(const vec4f& vec4)
	{
		operator =(vec4);
	}

	inline VectorPad3DT<T>(const vec4d& vec4)
	{
		operator =(vec4);
	}

	inline VectorPad3DT<T>& operator =(const vec4f& vec4)
	{
		x = static_cast<T>(vec4.x);
		y = static_cast<T>(vec4.y);
		z = static_cast<T>(vec4.z);
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const vec4d& vec4)
	{
		x = static_cast<T>(vec4.x);
		y = static_cast<T>(vec4.y);
		z = static_cast<T>(vec4.z);
		setInitialized();
		return *this;
	}

	inline operator vec4f() const
	{
		vec4f vec4;
		vec4.x = static_cast<vec4f::ValueType>(x);
		vec4.y = static_cast<vec4f::ValueType>(y);
		vec4.z = static_cast<vec4f::ValueType>(z);
		return vec4;
	}

	inline operator vec4d() const
	{
		vec4d vec4;
		vec4.x = static_cast<vec4d::ValueType>(x);
		vec4.y = static_cast<vec4d::ValueType>(y);
		vec4.z = static_cast<vec4d::ValueType>(z);
		return vec4;
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline VectorPad3DT<T>(const String& string)
	{
		operator =(string);
	}

	inline VectorPad3DT<T>& operator =(const String& right)
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

	inline VectorPad3DT<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& assignFromArray(const T source[3])
	{
		x = source[0];
		y = source[1];
		z = source[2];
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>(Zero)
	{
		setZero();
	}

	inline VectorPad3DT<T>& operator =(Zero)
	{
		return setZero();
	}

	inline VectorPad3DT<T>(UnitX)
	{
		setUnitX();
	}

	inline VectorPad3DT<T>& operator =(UnitX)
	{
		return setUnitX();
	}

	inline VectorPad3DT<T>(UnitY)
	{
		setUnitY();
	}

	inline VectorPad3DT<T>& operator =(UnitY)
	{
		return setUnitY();
	}

	inline VectorPad3DT<T>(UnitZ)
	{
		setUnitZ();
	}

	inline VectorPad3DT<T>& operator =(UnitZ)
	{
		return setUnitZ();
	}

	inline VectorPad3DT<T>& setZero()
	{
		x = 0;
		y = 0;
		z = 0;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& setMinimum()
	{
		x = -std::numeric_limits<T>::max();
		y = -std::numeric_limits<T>::max();
		z = -std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& setMaximum()
	{
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		z = std::numeric_limits<T>::max();
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& setUnitX()
	{
		x = 1;
		y = 0;
		z = 0;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& setUnitY()
	{
		x = 0;
		y = 1;
		z = 0;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& setUnitZ()
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

	inline VectorPad3DT<T>& operator =(const Vector2DT<T>& right)
	{
		x = right.x;
		y = right.y;
		z = 0;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const Vector3DT<T>& right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const Addition& right)
	{
		x = right.left.x + right.right.x;
		y = right.left.y + right.right.y;
		z = right.left.z + right.right.z;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const Subtraction& right)
	{
		x = right.left.x - right.right.x;
		y = right.left.y - right.right.y;
		z = right.left.z - right.right.z;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const Multiplication& right)
	{
		x = right.left.x * right.right.x;
		y = right.left.y * right.right.y;
		z = right.left.z * right.right.z;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const ScalarMultiplication& right)
	{
		x = right.left.x * right.right;
		y = right.left.y * right.right;
		z = right.left.z * right.right;
		setInitialized();
		return *this;
	}

	inline VectorPad3DT<T>& operator =(const CrossProduct& right)
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

	inline bool isUnitLength(const T epsilon = static_cast<T>(0.001)) const
	{
		const squareLength = getSquareLength();
		return squareLength >= 1 - epsilon && squareLength <= 1 + epsilon;
	}

	inline VectorPad3DT<T>& negate()
	{
		assertInitialized();
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline VectorPad3DT<T>& normalize()
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

	//inline VectorPad3DT<T> createOrthogonalVector(const VectorPad3DT<T>& upVector = UnitY()) const
	//{
	//	assertInitialized();
	//	VectorPad3DT<T> resultNormal = crossProduct(upVector, *this);

	//	if (resultNormal.squareLength() < 0.0001f)
	//	{
	//		resultNormal = crossProduct(VectorPad3DT<T>(UnitX()), *this);

	//		if (resultNormal.squareLength() < 0.0001f)
	//		{
	//			resultNormal = crossProduct(VectorPad3DT<T>(UnitZ()), *this);
	//		}
	//	}

	//	return resultNormal.normalize();
	//}

	//inline void orthogonalVectors(VectorPad3DT<T>& firstNormal, VectorPad3DT<T>& secondNormal, const VectorPad3DT<T>& upVector = UnitY())
	//{
	//	firstNormal = createOrthogonalVector(upVector);
	//	secondNormal = Normalization(crossProduct(*this, firstNormal));
	//}

	inline VectorPad3DT<T>& operator +=(const VectorPad3DT<T>& right)
	{
		assertInitialized();
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	inline VectorPad3DT<T>& operator -=(const VectorPad3DT<T>& right)
	{
		assertInitialized();
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	inline VectorPad3DT<T>& operator *=(const QuaternionT<T>& right)
	{
		return operator *=(Matrix3x3T<T>(right));
		/*		
		right.rotateVector(*this);
		return *this;
		*/
	}

	inline VectorPad3DT<T>& operator *=(const Matrix3x3T<T>& right)
	{
		assertInitialized();
		VectorPad3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2);
		return *this;
	}

	inline VectorPad3DT<T>& operator *=(const Matrix3x4T<T>& right)
	{
		assertInitialized();
		VectorPad3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2) + right.value(0, 3);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2) + right.value(1, 3);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2) + right.value(2, 3);
		return *this;
	}

	inline VectorPad3DT<T>& operator *=(const Matrix4x4T<T>& right)
	{
		assertInitialized();
		VectorPad3DT<T> original = *this;		
		x = original.x * right.value(0, 0) + original.y * right.value(0, 1) + original.z * right.value(0, 2) + right.value(0, 3);
		y = original.x * right.value(1, 0) + original.y * right.value(1, 1) + original.z * right.value(1, 2) + right.value(1, 3);
		z = original.x * right.value(2, 0) + original.y * right.value(2, 1) + original.z * right.value(2, 2) + right.value(2, 3);
		return *this;
	}

	inline VectorPad3DT<T>& operator *=(const T& right)
	{
		assertInitialized();
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	inline VectorPad3DT<T>& operator /=(const T& right)
	{
		BL_ASSERT(right != 0);
		assertInitialized();
		return operator *=(1 / right);
	}

	inline VectorPad3DT<T>& operator *=(const VectorPad3DT<T>& right)
	{
		assertInitialized();
		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	inline VectorPad3DT<T>& operator /=(const VectorPad3DT<T>& right)
	{
		assertInitialized();
		x /= right.x;
		y /= right.y;
		z /= right.z;
		return *this;
	}

	inline bool operator ==(const VectorPad3DT<T>& right) const
	{
		assertInitialized();
		return x == right.x && y == right.y && z == right.z;
	}

	inline bool operator !=(const VectorPad3DT<T>& right) const
	{
		return ! (operator ==(right));
	}
};



typedef VectorPad3DT<float> VectorPad3Df;
typedef VectorPad3DT<double> VectorPad3Dd;



template<typename T>
inline typename const VectorPad3DT<T>::Addition operator +(const VectorPad3DT<T>& left, const VectorPad3DT<T>& right)
{
	return VectorPad3DT<T>::Addition(left, right);
}



template<typename T>
inline typename const VectorPad3DT<T>::Subtraction operator -(const VectorPad3DT<T>& left, const VectorPad3DT<T>& right)
{
	return VectorPad3DT<T>::Subtraction(left, right);
}



template<typename T>
inline typename const VectorPad3DT<T>::Multiplication operator *(const VectorPad3DT<T>& left, const VectorPad3DT<T>& right)
{
	return VectorPad3DT<T>::Multiplication(left, right);
}



template<typename T>
inline typename const VectorPad3DT<T>::ScalarMultiplication operator *(const VectorPad3DT<T>& left, const T& right)
{
	return VectorPad3DT<T>::ScalarMultiplication(left, right);
}



template<typename T>
inline typename const VectorPad3DT<T>::Multiplication operator *(const T& left, const VectorPad3DT<T>& right)
{
	return VectorPad3DT<T>::Multiplication(right, left);
}



/**
The result variable must not be passed as left or right !
(i.e. use resultVariable.clone() instead)
*/
template<typename T>
inline typename VectorPad3DT<T>::CrossProduct crossProduct(const VectorPad3DT<T>& left, const VectorPad3DT<T>& right)
{
	return VectorPad3DT<T>::CrossProduct(left, right);
}



template<typename T>
inline typename VectorPad3DT<T>::Normalization normalize(const VectorPad3DT<T>& argument)
{
	return VectorPad3DT<T>::Normalization(argument);
}



template<typename T>
inline T dotProduct(const VectorPad3DT<T>& left, const VectorPad3DT<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}



template<typename T>
inline T angle(const VectorPad3DT<T>& unitVector1, const VectorPad3DT<T>& unitVector2)
{
	BL_ASSERT(unitVector1.isUnitLength() == true && unitVector2.isUnitLength() == true);
	return acos(dotProduct(unitVector1, unitVector2));
}



template<typename T>
inline VectorPad3DT<T> min(const VectorPad3DT<T>& vector1, const VectorPad3DT<T>& vector2)
{
	return VectorPad3DT<T>(min(vector1.x, vector2.x), min(vector1.y, vector2.y), min(vector1.z, vector2.z));
}



template<typename T>
inline VectorPad3DT<T> max(const VectorPad3DT<T>& vector1, const VectorPad3DT<T>& vector2)
{
	return VectorPad3DT<T>(max(vector1.x, vector2.x), max(vector1.y, vector2.y), max(vector1.z, vector2.z));
}



} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_VectorPad3D_h
