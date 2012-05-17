/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Matrix3x4_h
#define BaseLib_Math_Matrix3x4_h



#include "BaseLib/Math/Matrix3x3.h"
#include "BaseLib/Math/Vector3D.h"



namespace BaseLib {
namespace Math {



template<typename T>
struct BL_ALIGN_SIMD(Matrix3x4T) {

	typedef typename T ValueType;

	struct RotationMatrix {
		const Matrix3x4T<T>& matrix;
		inline explicit RotationMatrix(const Matrix3x4T<T>& rotationMatrix)
			: matrix(rotationMatrix)
		{
		}
	};
	
	union
	{
		T values[3*4];
		struct {
			Vector3DT<T> columns[4];
		};
		struct {
			float  sx, m10, m20;
			float m01,  sy, m21;
			float m02, m12,  sz;
			float  dx,  dy,  dz;
		};
	};

	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline Matrix3x4T<T>()
	{
		setUninitialized();
	}

	inline Matrix3x4T<T>(Identity)
	{
		setIdentity();
	}

	inline Matrix3x4T<T>& operator =(Identity)
	{
		return setIdentity();
	}

	inline Matrix3x4T<T>(const Matrix3x3T<T>& matrix3x3)
	{
		operator =(matrix3x3);
	}

	inline Matrix3x4T<T>& operator =(const Matrix3x3T<T>& rhs)
	{
		value(0, 0) = rhs.value(0, 0); value(0, 1) = rhs.value(0, 1); value(0, 2) = rhs.value(0, 2); value(0, 3) = 0;
		value(1, 0) = rhs.value(1, 0); value(1, 1) = rhs.value(1, 1); value(1, 2) = rhs.value(1, 2); value(1, 3) = 0;
		value(2, 0) = rhs.value(2, 0); value(2, 1) = rhs.value(2, 1); value(2, 2) = rhs.value(2, 2); value(2, 3) = 0;
		setInitialized();
		return *this;
	}

	inline Matrix3x4T<T>(typename const Matrix4x4T<T>::RotationMatrix& rotationMatrix)
	{
		operator =(rotationMatrix);
	}

	inline Matrix3x4T<T>& operator =(typename const Matrix4x4T<T>::RotationMatrix& rhs)
	{
		value(0, 0) = rhs.matrix.value(0, 0); value(0, 1) = rhs.matrix.value(0, 1); value(0, 2) = rhs.matrix.value(0, 2);
		value(1, 0) = rhs.matrix.value(1, 0); value(1, 1) = rhs.matrix.value(1, 1); value(1, 2) = rhs.matrix.value(1, 2);
		value(2, 0) = rhs.matrix.value(2, 0); value(2, 1) = rhs.matrix.value(2, 1); value(2, 2) = rhs.matrix.value(2, 2);
		setInitialized();
		return *this;
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline Matrix3x4T<T>(const String& string)
	{
		operator =(string);
	}

	inline Matrix3x4T<T>& operator =(const String& right)
	{
		setIdentity();
		StringTokenizer tokenizer(right);
		for (int i = 0; i < 3*4 && tokenizer.hasNextToken() == true; ++i)
		{
			values[i] = tokenizer.nextToken().parse<T>();
		}
		setInitialized();
		return *this;
	}

	operator String() const
	{
		assertInitialized();
		String string = String::createFrom(values[0]);
		for (int i = 1; i < 3*4; ++i)
		{
			string += ' ' + String::createFrom(values[i]);
		}
		return string;
	}
#endif

	inline Matrix3x4T<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline Matrix3x4T<T>& setIdentity()
	{
		value(0, 0) = 1; value(0, 1) = 0; value(0, 2) = 0; value(0, 3) = 0;
		value(1, 0) = 0; value(1, 1) = 1; value(1, 2) = 0; value(1, 3) = 0;
		value(2, 0) = 0; value(2, 1) = 0; value(2, 2) = 1; value(2, 3) = 0;
		setInitialized();
		return *this;
	}

	inline T& value(const int row, const int column)
	{
		BL_ASSERT(row >= 0 && row < 3);
		BL_ASSERT(column >= 0 && column < 4);
		return values[column * 4 + row];
	}

	inline const T& value(const int row, const int column) const
	{
		BL_ASSERT(row >= 0 && row < 3);
		BL_ASSERT(column >= 0 && column < 4);
		assertInitialized();
		return values[column * 4 + row];
	}

	inline Matrix3x4T<T>& operator *=(const Matrix3x3T<T>& rhs)
	{
		assertInitialized();
		const Matrix3x4T<T> lhs = *this;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				value(row, column) =	lhs.value(row, 0) * rhs.value(0, column) +
									lhs.value(row, 1) * rhs.value(1, column) +
									lhs.value(row, 2) * rhs.value(2, column);
			}
		}

		return *this;
	}

	inline Matrix3x4T<T>& operator *=(const Matrix3x4T<T>& rhs)
	{
		assertInitialized();
		const Matrix3x4T<T> lhs = *this;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				value(row, column) =	lhs.value(row, 0) * rhs.value(0, column) +
									lhs.value(row, 1) * rhs.value(1, column) +
									lhs.value(row, 2) * rhs.value(2, column) +
									lhs.value(row, 3) * (column == 3 ? 1 : 0);
			}
		}

		return *this;
	}

	inline Matrix3x4T<T>& operator *=(const Matrix4x4T<T>& rhs)
	{
		assertInitialized();
		Matrix3x4T<T> lhs = *this;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				value(row, column) =	lhs.value(row, 0) * rhs.value(0, column) +
									lhs.value(row, 1) * rhs.value(1, column) +
									lhs.value(row, 2) * rhs.value(2, column) +
									lhs.value(row, 3) * rhs.value(3, column);
			}
		}

		return *this;
	}

	inline const T determinant() const
	{
		assertInitialized();
		BL_ASSERT_NEVER_REACHED
		return 0;
	}

	inline const T determinant3x3() const
	{
		assertInitialized();
		return
			value(0, 0) * value(1, 1) * value(2, 2) +
			value(0, 1) * value(1, 2) * value(2, 0) +
			value(0, 2) * value(1, 0) * value(2, 1) -
			value(0, 2) * value(1, 1) * value(2, 0) -
			value(0, 1) * value(1, 0) * value(2, 2) -
			value(0, 0) * value(1, 2) * value(2, 1);				
	}

	inline bool isReflective() const
	{
		return determinant3x3() < 0;
	}

	inline const RotationMatrix rotationMatrix() const
	{
		assertInitialized();
		return RotationMatrix(*this);
	}

	inline const Vector3DT<T>& getTranslation() const
	{
		assertInitialized();
		return memoryAs<Vector3DT<T> >(&dx, 0);
	}

	inline void setTranslation(const Vector3DT<T>& translationVector)
	{
		assertInitialized();
		memoryAs<Vector3DT<T> >(&dx, 0) = translationVector;
	}

	inline Vector3DT<T> getScaling() const
	{
		assertInitialized();
		return Vector3DT<T>(sx, sy, sz);
	}

	inline void setScaling(float scaling)
	{
		assertInitialized();
		sx = scaling;
		sy = scaling;
		sz = scaling;
	}

	inline void setScaling(const Vector3DT<T>& scaling)
	{
		assertInitialized();
		sx = scaling.x;
		sy = scaling.y;
		sz = scaling.z;
	}

	inline void scale(float scaling)
	{
		assertInitialized();
		sx *= scaling;
		sy *= scaling;
		sz *= scaling;
	}

	inline void scale(const Vector3DT<T>& scaling)
	{
		assertInitialized();
		sx *= scaling.x;
		sy *= scaling.y;
		sz *= scaling.z;
	}

	inline void rigidBodyInverse()
	{
		transpose3x3();
		value(0, 3) = -value(0, 3);
		value(1, 3) = -value(1, 3);
		value(2, 3) = -value(2, 3);
	}

	inline void transpose3x3()
	{
		assertInitialized();
		swap( value(1, 0), value(0, 1) );
		swap( value(2, 0), value(0, 2) );
		swap( value(2, 1), value(1, 2) );
	}

	inline const T trace() const
	{
		assertInitialized();
		return value(0, 0) + value(1, 1) + value(2, 2) + 1;
	}

	inline const T trace3() const
	{
		assertInitialized();
		return value(0, 0) + value(1, 1) + value(2, 2);
	}

	inline Matrix3x4T<T>(const XRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix3x4T<T>(const YRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix3x4T<T>(const ZRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix3x4T<T>(const YxzRotation& eulerRotation)
	{
		operator =(eulerRotation);
	}

	inline Matrix3x4T<T>& operator =(const XRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = 1; value(0, 1) = 0;      value(0, 2) = 0;      value(0, 3) = 0;
		value(1, 0) = 0; value(1, 1) = cosine; value(1, 2) = -sine;  value(1, 3) = 0;
		value(2, 0) = 0; value(2, 1) = sine;   value(2, 2) = cosine; value(2, 3) = 0;

		setInitialized();
		return *this;
	}

	inline Matrix3x4T<T>& operator =(const YRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = cosine; value(0, 1) = 0; value(0, 2) = sine;   value(0, 3) = 0;
		value(1, 0) = 0;      value(1, 1) = 1; value(1, 2) = 0;      value(1, 3) = 0;
		value(2, 0) = -sine;  value(2, 1) = 0; value(2, 2) = cosine; value(2, 3) = 0;

		setInitialized();
		return *this;
	}

	inline Matrix3x4T<T>& operator =(const ZRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = cosine; value(0, 1) = -sine;  value(0, 2) = 0; value(0, 3) = 0;
		value(1, 0) = sine;   value(1, 1) = cosine; value(1, 2) = 0; value(1, 3) = 0;
		value(2, 0) = 0;      value(2, 1) = 0;      value(2, 2) = 1; value(2, 3) = 0;

		setInitialized();
		return *this;
	}

	inline Matrix3x4T<T>& operator =(const YxzRotation& eulerRotation)
	{
		const T sinH = static_cast<T>( sin(eulerRotation.yAngle) );
		const T cosH = static_cast<T>( cos(eulerRotation.yAngle) );
		const T sinP = static_cast<T>( sin(eulerRotation.xAngle) );
		const T cosP = static_cast<T>( cos(eulerRotation.xAngle) );
		const T sinR = static_cast<T>( sin(eulerRotation.zAngle) );
		const T cosR = static_cast<T>( cos(eulerRotation.zAngle) );

		value(0, 0) = cosR*cosH-sinR*sinP*sinH; value(0, 1) = -sinR*cosP; value(0, 2) = cosR*sinH+sinR*sinP*cosH; value(0, 3) = 0;
		value(1, 0) = sinR*cosH+cosR*sinP*sinH; value(1, 1) = cosR*cosP;  value(1, 2) = sinR*sinH-cosR*sinP*cosH; value(1, 3) = 0;
		value(2, 0) = -cosP*sinH;               value(2, 1) = sinP;       value(2, 2) = cosP*cosH;				value(2, 3) = 0;

		setInitialized();
		return *this;
	}

	inline void extractEulerAngles(double& headAngle, double& pitchAngle, double& rollAngle)
	{
		assertInitialized();
		pitchAngle = arcsin(value(2, 1));

		const double f21 = abs(value(2, 1));
		if (f21 > (1.0 - 0.0001) && f21 < (1.0 + 0.0001)) // f21 == 1.0
		{
			headAngle = 0.0;
			rollAngle = atan2(value(1, 0), value(0, 0));
		}
		else
		{
			headAngle = atan2(-value(2, 0), value(2, 2));
			rollAngle = atan2(-value(0, 1), value(1, 1));
		}
	}

	inline Matrix3x4T<T>& setToCoordinateSystemBase(const Vector3DT<T>& xVector, const Vector3DT<T>& yVector, const Vector3DT<T>& zVector)
	{
		value(0, 0) = xVector.x; value(0, 1) = xVector.y; value(0, 2) = xVector.z; value(0, 3) = 0; 
		value(1, 0) = yVector.x; value(1, 1) = yVector.y; value(1, 2) = yVector.z; value(1, 3) = 0;
		value(2, 0) = zVector.x; value(2, 1) = zVector.y; value(2, 2) = zVector.z; value(2, 3) = 0;
		setInitialized();
		return *this;
	}

	
	inline Matrix3x4T<T>(const QuaternionT<T>& quaternion)
	{
		operator =(quaternion);
	}

	inline Matrix3x4T<T>& operator =(const QuaternionT<T>& rhs)
	{
		const T xx = sqr(rhs.x) * 2;
		const T yy = sqr(rhs.y) * 2;
		const T zz = sqr(rhs.z) * 2;
		const T xy = rhs.x * rhs.y * 2;
		const T xz = rhs.x * rhs.z * 2;
		const T yz = rhs.y * rhs.z * 2;
		const T wx = rhs.w * rhs.x * 2;
		const T wy = rhs.w * rhs.y * 2;
		const T wz = rhs.w * rhs.z * 2;
		
		value(0, 0) = 1 - (yy + zz);	value(0, 1) = xy - wz;		value(0, 2) = xz + wy;		value(0, 3) = 0;
		value(1, 0) = xy + wz;		value(1, 1) = 1 - (xx + zz);	value(1, 2) = yz - wx;		value(1, 3) = 0;
		value(2, 0) = xz - wy;		value(2, 1) = yz + wx;		value(2, 2) = 1 - (xx + yy);	value(2, 3) = 0;

		setInitialized();
		return *this;
	}
	
	inline Matrix3x4T<T>(const AlignVectorsRotation<T>& rotation)
	{
		operator =(rotation);
	}

	inline Matrix3x4T<T>& operator =(const AlignVectorsRotation<T>& rhs)
	{
		const Vector3DT<T> v = crossProduct(rhs.vectorA, rhs.vectorB);
		const T e = dotProduct(rhs.vectorA, rhs.vectorB);
		const T h = (1 - e) / v.squareLength();
		
		value(0, 0) = e + sqr(v.x);    value(0, 1) = h*v.x*v.y - v.z; value(0, 2) = h*v.x*v.z + v.y; value(0, 3) = 0;
		value(1, 0) = h*v.x*v.y + v.z; value(1, 1) = e + h*sqr(v.y);  value(1, 2) = h*v.y*v.z - v.x; value(1, 3) = 0;
		value(2, 0) = h*v.x*v.z - v.y; value(2, 1) = h*v.x*v.z + v.x; value(2, 2) = e + h*sqr(v.z);  value(2, 3) = 0;

		setInitialized();
		return *this;
	}

};



typedef Matrix3x4T<float> Matrix3x4f;
typedef Matrix3x4T<double> Matrix3x4d;

#ifdef BL_MATH_DOUBLE_PRECISION
	typedef Matrix3x4d Matrix3x4;
#else
	typedef Matrix3x4f Matrix3x4;
#endif



} // namespace Math
} // namespace BaseLib



namespace BaseLib {
	namespace TypeTraits {

		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix3x4f)
		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix3x4d)

	}
}



#endif // #ifndef BaseLib_Math_Matrix3x4_h
