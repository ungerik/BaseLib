/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_VectorHom3D_h
#define BaseLib_Math_VectorHom3D_h



#include "BaseLib/Math/Vector3D.h"



namespace BaseLib {
namespace Math {



template<typename T>
struct Vector3DT;



template<typename T = float>
struct BL_ALIGN_SIMD(VectorHom3DT) {

	typedef typename T ValueType;

	union {
		struct {
			T x;
			T y;
			T z;
			T w;
		};
		T values[4];
	};

	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline VectorHom3DT<T>()
	{
		setUninitialized();
	}

	inline VectorHom3DT<T>(T newX, T newY, T newZ = 0, T newW = 1)
		: x(newX)
		, y(newY)
		, z(newZ)
		, w(newW)
	{
		setInitialized();
	}

	inline explicit VectorHom3DT<T>(const T source[4])
		: x(source[0])
		, y(source[1])
		, z(source[2])
		, w(source[3])
	{
		setInitialized();
	}

	inline VectorHom3DT<T>(const vec4f& vec4)
	{
		operator =(vec4);
	}

	inline VectorHom3DT<T>(const vec4d& vec4)
	{
		operator =(vec4);
	}

	inline VectorHom3DT<T>& operator =(const vec4f& vec4)
	{
		x = static_cast<T>(vec4.x);
		y = static_cast<T>(vec4.y);
		z = static_cast<T>(vec4.z);
		w = static_cast<T>(vec4.w);
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& operator =(const vec4d& vec4)
	{
		x = static_cast<T>(vec4.x);
		y = static_cast<T>(vec4.y);
		z = static_cast<T>(vec4.z);
		w = static_cast<T>(vec4.w);
		setInitialized();
		return *this;
	}

	inline operator vec4f() const
	{
		vec4f vec4;
		vec4.x = static_cast<vec4f::ValueType>(x);
		vec4.y = static_cast<vec4f::ValueType>(y);
		vec4.z = static_cast<vec4f::ValueType>(z);
		vec4.w = static_cast<vec4f::ValueType>(w);
		return vec4;
	}

	inline operator vec4d() const
	{
		vec4d vec4;
		vec4.x = static_cast<vec4d::ValueType>(x);
		vec4.y = static_cast<vec4d::ValueType>(y);
		vec4.z = static_cast<vec4d::ValueType>(z);
		vec4.w = static_cast<vec4d::ValueType>(w);
		return vec4;
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline VectorHom3DT<T>(const String& string)
	{
		operator =(string);
	}

	inline VectorHom3DT<T>& operator =(const String& right)
	{
		StringTokenizer tokenizer(right);
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(x); else x = 0;
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(y); else y = 0;
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(z); else z = 0;
		if (tokenizer.hasNextToken() == true) tokenizer.nextToken().parse(w); else w = 1;
		setInitialized();
		return *this;
	}

	operator String() const
	{
		assertInitialized();
		return String::createFrom(x) + ' ' + String::createFrom(y) + ' ' + String::createFrom(z) + ' ' + String::createFrom(w);
	}
#endif

	inline VectorHom3DT<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline Vector3DT<T>& assignFromArray(const T source[4])
	{
		x = source[0];
		y = source[1];
		z = source[2];
		w = source[3];
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>(typename const Vector3DT<T>::Addition& other)
	{
		operator =(other);
	}

	inline VectorHom3DT<T>(typename const Vector3DT<T>::Subtraction& other)
	{
		operator =(other);
	}

	inline VectorHom3DT<T>& operator =(const Vector3DT<T>& right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& operator =(typename const Vector3DT<T>::Addition& right)
	{
		x = right.left.x + right.right.x;
		y = right.left.y + right.right.y;
		z = right.left.z + right.right.z;
		w = 1;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& operator =(typename const Vector3DT<T>::Subtraction& right)
	{
		x = right.left.x - right.right.x;
		y = right.left.y - right.right.y;
		z = right.left.z - right.right.z;
		w = 1;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& negate()
	{
		assertInitialized();
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline T getSquareLength() const
	{
		assertInitialized();
		const Vector3DT<T> vector3D = *this;
		return vector3D.squareLength();
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

	inline VectorHom3DT<T>& normalize()
	{
		const T length = getLength();
		if (length != 0 && length != 1) operator /=(length);
		return *this;
	}

	inline VectorHom3DT<T>(Zero)
	{
		setZero();
	}

	inline VectorHom3DT<T>& operator =(Zero)
	{
		return setZero();
	}

	inline VectorHom3DT<T>(UnitX)
	{
		setUnitX();
	}

	inline VectorHom3DT<T>& operator =(UnitX)
	{
		return setUnitX();
	}

	inline VectorHom3DT<T>(UnitY)
	{
		setUnitY();
	}

	inline VectorHom3DT<T>& operator =(UnitY)
	{
		return setUnitY();
	}

	inline VectorHom3DT<T>(UnitZ)
	{
		setUnitZ();
	}

	inline VectorHom3DT<T>& operator =(UnitZ)
	{
		return setUnitZ();
	}

	inline VectorHom3DT<T>& operator =(UnitW)
	{
		return setUnitW();
	}

	inline VectorHom3DT<T>& setZero(const T& newW = 1)
	{
		x = 0;
		y = 0;
		z = 0;
		w = newW;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& setUnitX(const T& newW = 1)
	{
		x = 1;
		y = 0;
		z = 0;
		w = newW;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& setUnitY(const T& newW = 1)
	{
		x = 0;
		y = 1;
		z = 0;
		w = newW;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& setUnitZ(const T& newW = 1)
	{
		x = 0;
		y = 0;
		z = 1;
		w = newW;
		setInitialized();
		return *this;
	}

	inline VectorHom3DT<T>& setUnitW()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
		setInitialized();
		return *this;
	}

	inline bool isZero() const
	{
		assertInitialized();
		return x == 0 && y == 0 && z == 0;
	}

	inline bool isZeroWithW() const
	{
		assertInitialized();
		return x == 0 && y == 0 && z == 0 && w == 0;
	}

	inline Vector3DT<T> createNormal() const
	{
		assertInitialized();
		Vector3DT<T> resultNormal = crossProduct(Vector3DT<T>(0, 0, 1), *this);

		if (resultNormal.isZero == true)
		{
			resultNormal.x = 1;
		}
		else
		{
			resultNormal.normalize();
		}

		return resultNormal;
	}

	inline VectorHom3DT<T>& devideByW()
	{
		assertInitialized();
		if (w != 0)
		{
			const T ooW = 1 / w;
			x *= ooW;
			y *= ooW;
			z *= ooW;
			w = 1;
		}
		return *this;
	}

	inline void copyDevidedByW() const
	{
		assertInitialized();
		VectorHom3DT<T> copy = *this;
		return copy.devideByW();
	}

	inline operator Vector3DT<T>() const
	{
		assertInitialized();
		if (w != 0)
		{
			const T ooW = 1 / w;
			return Vector3DT<T>(x * ooW, y * ooW, z * ooW);
		}
		else
		{
			return Vector3DT<T>(x, y, z);
		}
	}

	inline VectorHom3DT<T>& operator +=(const Vector3DT<T>& right)
	{
		devideByW();
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	inline VectorHom3DT<T>& operator -=(const Vector3DT<T>& right)
	{
		devideByW();
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	inline VectorHom3DT<T>& operator *=(const QuaternionT<T>& right)
	{
		return operator *=(Matrix3x3T<T>(right));
		/*
		right.rotateVector(*this);
		return *this;
		*/
	}

	inline VectorHom3DT<T>& operator *=(const Matrix3x3T<T>& right)
	{
		assertInitialized();
		VectorHom3DT<T> original = *this;		
		x = original.x * right.get(0, 0) + original.y * right.get(0, 1) + original.z * right.get(0, 2);
		y = original.x * right.get(1, 0) + original.y * right.get(1, 1) + original.z * right.get(1, 2);
		z = original.x * right.get(2, 0) + original.y * right.get(2, 1) + original.z * right.get(2, 2);
		return *this;
	}

	inline VectorHom3DT<T>& operator *=(const Matrix3x4T<T>& right)
	{
		assertInitialized();
		VectorHom3DT<T> original = *this;		
		x = original.x * right.get(0, 0) + original.y * right.get(0, 1) + original.z * right.get(0, 2) + right.get(0, 3);
		y = original.x * right.get(1, 0) + original.y * right.get(1, 1) + original.z * right.get(1, 2) + right.get(1, 3);
		z = original.x * right.get(2, 0) + original.y * right.get(2, 1) + original.z * right.get(2, 2) + right.get(2, 3);
		return *this;
	}

	inline VectorHom3DT<T>& operator *=(const Matrix4x4T<T>& right)
	{
		assertInitialized();
		VectorHom3DT<T> original = *this;		
		x = original.x * right.get(0, 0) + original.y * right.get(0, 1) + original.z * right.get(0, 2) + right.get(0, 3);
		y = original.x * right.get(1, 0) + original.y * right.get(1, 1) + original.z * right.get(1, 2) + right.get(1, 3);
		z = original.x * right.get(2, 0) + original.y * right.get(2, 1) + original.z * right.get(2, 2) + right.get(2, 3);
		w = original.x * right.get(3, 0) + original.y * right.get(3, 1) + original.z * right.get(3, 2) + right.get(3, 3);
		return *this;
	}

	inline VectorHom3DT<T>& operator *=(const T& right)
	{
		assertInitialized();
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	inline VectorHom3DT<T>& operator /=(const T& right)
	{
		BL_ASSERT(right != 0);
		assertInitialized();
		return operator *=(1 / right);
	}

	inline bool operator ==(const VectorHom3DT<T>& right) const
	{
		assertInitialized();
		return x == right.x && y == right.y && z == right.z && w == right.w;
	}

	inline bool operator !=(const VectorHom3DT<T>& right) const
	{
		return !(operator ==(right));
	}


};



typedef VectorHom3DT<float> VectorHom3D;
typedef VectorHom3DT<double> VectorHom3Dd;



template<typename T>
inline T dotProduct4D(const VectorHom3DT<T>& left, const VectorHom3DT<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w + right.w;
}



template<typename T>
inline T dotProduct(const VectorHom3DT<T>& left, const VectorHom3DT<T>& right)
{
	const Vector3DT<T> left3D = left;
	const Vector3DT<T> right3D = right;
	return dotProduct(left, right);
}



template<typename T>
inline T angle(const VectorHom3DT<T>& unitVector1, const VectorHom3DT<T>& unitVector2)
{
	BL_ASSERT(unitVector1.isUnitLength() == true && unitVector2.isUnitLength() == true);
	return acos(dotProduct(unitVector1, unitVector2));
}



} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_VectorHom3D_h
