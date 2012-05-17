/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Matrix4x4_h
#define BaseLib_Math_Matrix4x4_h



#include "BaseLib/Math/Matrix3x4.h"
#include "BaseLib/Math/VectorHom3D.h"



namespace BaseLib {
namespace Math {



using BaseLib::Math::sqr;



template<typename T> struct Vector3DT;



template<typename T>
struct BL_ALIGN_SIMD(Matrix4x4T) {

	typedef typename T ValueType;

	struct Product {
		const Matrix4x4T<T>& left;
		const Matrix4x4T<T>& right;
		inline explicit Product(const Matrix4x4T<T>& l, const Matrix4x4T<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct RotationMatrix {
		const Matrix4x4T<T>& matrix;
		inline explicit RotationMatrix(const Matrix4x4T<T>& rotationMatrix)
			: matrix(rotationMatrix)
		{
		}
	};

	union
	{
		T values[4*4];
		struct {
			VectorHom3DT<T> columns[4];
		};
		struct {
			float  sx, m10, m20, m30;
			float m01,  sy, m21, m31;
			float m02, m12,  sz, m32;
			float  dx,  dy,  dz,  sw;
		};
	};

	BL_MATH_INITILIZED_CHECK_MEMBERS

	inline Matrix4x4T<T>()
	{
		setUninitialized();
	}

	inline Matrix4x4T<T>(Identity)
	{
		setIdentity();
	}

	inline Matrix4x4T<T>& operator =(Identity)
	{
		return setIdentity();
	}

	inline Matrix4x4T<T>(const Product& other)
	{
		operator =(other);
	}

	inline Matrix4x4T<T>& operator =(const Product& right)
	{
		BL_ASSERT(&right.left != this && &right.right != this);

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				value(row, column) = right.left.value(row, 0) * right.right.value(0, column) +
				                     right.left.value(row, 1) * right.right.value(1, column) +
				                     right.left.value(row, 2) * right.right.value(2, column) +
				                     right.left.value(row, 3) * right.right.value(3, column);
			}
		}

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>(const Matrix3x3T<T>& matrix3x3)
	{
		operator =(matrix3x3);
	}

	inline Matrix4x4T<T>& operator =(const Matrix3x3T<T>& right)
	{
		value(0, 0) = right.value(0, 0); value(0, 1) = right.value(0, 1); value(0, 2) = right.value(0, 2); value(0, 3) = 0;
		value(1, 0) = right.value(1, 0); value(1, 1) = right.value(1, 1); value(1, 2) = right.value(1, 2); value(1, 3) = 0;
		value(2, 0) = right.value(2, 0); value(2, 1) = right.value(2, 1); value(2, 2) = right.value(2, 2); value(2, 3) = 0;
		value(3, 0) = 0;                 value(3, 1) = 0;                 value(3, 2) = 0;                 value(3, 3) = 1;
		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>(const Matrix3x4T<T>& matrix3x3)
	{
		operator =(matrix3x3);
	}

	inline Matrix4x4T<T>& operator =(const Matrix3x4T<T>& right)
	{
		value(0, 0) = right.value(0, 0); value(0, 1) = right.value(0, 1); value(0, 2) = right.value(0, 2); value(0, 3) = right.value(0, 3);
		value(1, 0) = right.value(1, 0); value(1, 1) = right.value(1, 1); value(1, 2) = right.value(1, 2); value(1, 3) = right.value(1, 3);
		value(2, 0) = right.value(2, 0); value(2, 1) = right.value(2, 1); value(2, 2) = right.value(2, 2); value(2, 3) = right.value(2, 3);
		value(3, 0) = 0;                 value(3, 1) = 0;                 value(3, 2) = 0;                 value(3, 3) = 1;
		setInitialized();
		return *this;
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

	inline void setTranslation(float xTranslation, float yTranslation)
	{
		assertInitialized();
		dx = xTranslation;
		dy = yTranslation;
	}

	inline void setTranslation(float xTranslation, float yTranslation, float zTranslation)
	{
		assertInitialized();
		dx = xTranslation;
		dy = yTranslation;
		dz = zTranslation;
	}

	inline void translate(const Vector3DT<T>& translationVector)
	{
		assertInitialized();
		memoryAs<Vector3DT<T> >(&dx, 0) += translationVector;
	}

	inline void translate(float xTranslation, float yTranslation)
	{
		assertInitialized();
		dx += xTranslation;
		dy += yTranslation;
	}

	inline void translate(float xTranslation, float yTranslation, float zTranslation)
	{
		assertInitialized();
		dx += xTranslation;
		dy += yTranslation;
		dz += zTranslation;
	}

	inline VectorHom3DT<T> getScaling() const
	{
		assertInitialized();
		return VectorHom3DT<T>(sx, sy, sz, sw);
	}

	inline void setScaling(float scaling)
	{
		assertInitialized();
		sx = scaling;
		sy = scaling;
		sz = scaling;
	}

	inline void setScaling(float xScaling, float yScaling)
	{
		assertInitialized();
		sx = xScaling;
		sy = yScaling;
	}

	inline void setScaling(float xScaling, float yScaling, float zScaling)
	{
		assertInitialized();
		sx = xScaling;
		sy = yScaling;
		sz = zScaling;
	}

	inline void setScaling(const Vector3DT<T>& scaling)
	{
		assertInitialized();
		sx = scaling.x;
		sy = scaling.y;
		sz = scaling.z;
	}

	inline void setScaling(const VectorHom3DT<T>& scaling)
	{
		assertInitialized();
		sx = scaling.x;
		sy = scaling.y;
		sz = scaling.z;
		sw = scaling.w;
	}

	inline void scale(float scaling)
	{
		assertInitialized();
		sx *= scaling;
		sy *= scaling;
		sz *= scaling;
	}

	inline void scale(float xScaling, float yScaling)
	{
		assertInitialized();
		sx *= xScaling;
		sy *= yScaling;
	}

	inline void scale(float xScaling, float yScaling, float zScaling)
	{
		assertInitialized();
		sx *= xScaling;
		sy *= yScaling;
		sz *= zScaling;
	}

	inline void scale(const Vector3DT<T>& scaling)
	{
		assertInitialized();
		sx *= scaling.x;
		sy *= scaling.y;
		sz *= scaling.z;
	}

	inline void scale(const VectorHom3DT<T>& scaling)
	{
		assertInitialized();
		sx *= scaling.x;
		sy *= scaling.y;
		sz *= scaling.z;
		sw *= scaling.w;
	}

#ifndef BL_MATH_WITHOUT_STRINGS
	inline Matrix4x4T<T>(const String& string)
	{
		operator =(string);
	}

	inline Matrix4x4T<T>& operator =(const String& right)
	{
		setIdentity();
		StringTokenizer tokenizer(right);
		for (int i = 0; i < 4*4 && tokenizer.hasNextToken() == true; ++i)
		{
			tokenizer.nextToken().parse(values[i]);
		}
		setInitialized();
		return *this;
	}

	operator String() const
	{
		assertInitialized();
		String string = String::createFrom(values[0]);
		for (int i = 1; i < 4*4; ++i)
		{
			string += ' ' + String::createFrom(values[i]);
		}
		return string;
	}
#endif

	inline Matrix4x4T<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& setIdentity()
	{
		value(0, 0) = 1; value(0, 1) = 0; value(0, 2) = 0; value(0, 3) = 0;
		value(1, 0) = 0; value(1, 1) = 1; value(1, 2) = 0; value(1, 3) = 0;
		value(2, 0) = 0; value(2, 1) = 0; value(2, 2) = 1; value(2, 3) = 0;
		value(3, 0) = 0; value(3, 1) = 0; value(3, 2) = 0; value(3, 3) = 1;
		setInitialized();
		return *this;
	}

	inline T& value(const int row, const int column)
	{
		BL_ASSERT(row >= 0 && row < 4);
		BL_ASSERT(column >= 0 && column < 4);
		return values[column * 4 + row];
	}

	inline const T& value(const int row, const int column) const
	{
		BL_ASSERT(row >= 0 && row < 4);
		BL_ASSERT(column >= 0 && column < 4);
		assertInitialized();
		return values[column * 4 + row];
	}

	inline const T trace() const
	{
		assertInitialized();
		return value(0, 0) + value(1, 1) + value(2, 2) + value(3, 3);
	}

	inline const T trace3() const
	{
		assertInitialized();
		return value(0, 0) + value(1, 1) + value(2, 2);
	}

	inline Matrix4x4T<T>(const XRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix4x4T<T>(const YRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix4x4T<T>(const ZRotation& rotation)
	{
		operator =(rotation);
	}

	inline Matrix4x4T<T>(const YxzRotation& eulerRotation)
	{
		operator =(eulerRotation);
	}

	inline Matrix4x4T<T>& operator =(const XRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = 1; value(0, 1) = 0;      value(0, 2) = 0;      value(0, 3) = 0;
		value(1, 0) = 0; value(1, 1) = cosine; value(1, 2) = -sine;  value(1, 3) = 0;
		value(2, 0) = 0; value(2, 1) = sine;   value(2, 2) = cosine; value(2, 3) = 0;
		value(3, 0) = 0; value(3, 1) = 0;      value(3, 2) = 0;      value(3, 3) = 1;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& operator =(const YRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = cosine; value(0, 1) = 0; value(0, 2) = sine;   value(0, 3) = 0;
		value(1, 0) = 0;      value(1, 1) = 1; value(1, 2) = 0;      value(1, 3) = 0;
		value(2, 0) = -sine;  value(2, 1) = 0; value(2, 2) = cosine; value(2, 3) = 0;
		value(3, 0) = 0;      value(3, 1) = 0; value(3, 2) = 0;      value(3, 3) = 1;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& operator =(const ZRotation& rotation)
	{
		const T cosine = static_cast<T>( cos(rotation.angle) );
		const T sine = static_cast<T>( sin(rotation.angle) );

		value(0, 0) = cosine; value(0, 1) = -sine;  value(0, 2) = 0; value(0, 3) = 0;
		value(1, 0) = sine;   value(1, 1) = cosine; value(1, 2) = 0; value(1, 3) = 0;
		value(2, 0) = 0;      value(2, 1) = 0;      value(2, 2) = 1; value(2, 3) = 0;
		value(3, 0) = 0;      value(3, 1) = 0;      value(3, 2) = 0; value(3, 3) = 1;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& operator =(const YxzRotation& eulerRotation)
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
		value(3, 0) = 0;						  value(3, 1) = 0;		  value(3, 2) = 0;						value(3, 3) = 1;

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

	inline const T determinant() const
	{
		assertInitialized();
		BL_ASSERT_NOT_IMPLEMENTED
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

	inline void transpose()
	{
		transpose3x3();
		swap( value(3, 0), value(0, 3) );
		swap( value(3, 1), value(1, 3) );
		swap( value(3, 2), value(2, 3) );
	}

	inline void transpose3x3()
	{
		assertInitialized();
		swap( value(1, 0), value(0, 1) );
		swap( value(2, 0), value(0, 2) );
		swap( value(2, 1), value(1, 2) );
	}

	inline void adjoint3x3()
	{
		assertInitialized();
		const Matrix3x3T<T> matrix3x3 = rotationMatrix();

		value(0, 0) = +matrix3x3.subDeterminant(0, 0); value(0, 1) = -matrix3x3.subDeterminant(0, 1); value(0, 2) = +matrix3x3.subDeterminant(0, 2);
		value(1, 0) = -matrix3x3.subDeterminant(1, 0); value(0, 1) = +matrix3x3.subDeterminant(1, 1); value(1, 2) = -matrix3x3.subDeterminant(1, 2);
		value(2, 0) = +matrix3x3.subDeterminant(2, 0); value(0, 1) = -matrix3x3.subDeterminant(2, 1); value(2, 2) = +matrix3x3.subDeterminant(2, 2);
	}

	inline void normalTransformation()
	{
		inverse();
		transpose();
	}

	inline void rigidBodyInverse()
	{
		transpose3x3();
		value(0, 3) = -value(0, 3);
		value(1, 3) = -value(1, 3);
		value(2, 3) = -value(2, 3);
	}

	inline void normalTransformationRotTransUniscale()
	{
		adjoint3x3();
		transpose3x3();
	}

	inline Matrix4x4T<T>& operator *=(const Matrix3x3T<T>& right)
	{
		assertInitialized();
		const Matrix3x3T<T> left = rotationMatrix();

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				value(row, column) =
					left.value(row, 0) * right.value(0, column) +
					left.value(row, 1) * right.value(1, column) +
					left.value(row, 2) * right.value(2, column);
			}
		}

		return *this;
	}

	inline Matrix4x4T<T>& operator *=(const Matrix3x4T<T>& right)
	{
		assertInitialized();
		const Matrix4x4T<T> left = *this;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				value(row, column) =
					left.value(row, 0) * right.value(0, column) +
					left.value(row, 1) * right.value(1, column) +
					left.value(row, 2) * right.value(2, column) +
					left.value(row, 3) * (column == 3 ? 1 : 0);
			}
		}

		return *this;
	}

	inline Matrix4x4T<T>& operator *=(const Matrix4x4T<T>& right)
	{
		assertInitialized();
		const Matrix4x4T<T> left = *this;
		return (*this = left * right);
	}

	inline Matrix4x4T<T>& setToCoordinateSystemBase(const Vector3DT<T>& xVector, const Vector3DT<T>& yVector, const Vector3DT<T>& zVector)
	{
		value(0, 0) = xVector.x; value(0, 1) = xVector.y; value(0, 2) = xVector.z; value(0, 3) = 0; 
		value(1, 0) = yVector.x; value(1, 1) = yVector.y; value(1, 2) = yVector.z; value(1, 3) = 0;
		value(2, 0) = zVector.x; value(2, 1) = zVector.y; value(2, 2) = zVector.z; value(2, 3) = 0;
		value(3, 0) = 0;         value(3, 1) = 0;         value(3, 2) = 0;         value(3, 3) = 1;
		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>(const QuaternionT<T>& quaternion)
	{
		operator =(quaternion);
	}

	inline Matrix4x4T<T>& operator =(const QuaternionT<T>& right)
	{
		const T xx = sqr(right.x) * 2;
		const T yy = sqr(right.y) * 2;
		const T zz = sqr(right.z) * 2;
		const T xy = right.x * right.y * 2;
		const T xz = right.x * right.z * 2;
		const T yz = right.y * right.z * 2;
		const T wx = right.w * right.x * 2;
		const T wy = right.w * right.y * 2;
		const T wz = right.w * right.z * 2;
		
		value(0, 0) = 1 - (yy + zz); value(0, 1) = xy - wz;       value(0, 2) = xz + wy;       value(0, 3) = 0;
		value(1, 0) = xy + wz;       value(1, 1) = 1 - (xx + zz); value(1, 2) = yz - wx;       value(1, 3) = 0;
		value(2, 0) = xz - wy;       value(2, 1) = yz + wx;       value(2, 2) = 1 - (xx + yy); value(2, 3) = 0;
		value(3, 0) = 0;             value(3, 1) = 0;             value(3, 2) = 0;             value(3, 3) = 1;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>(const AlignVectorsRotation<T>& rotation)
	{
		operator =(rotation);
	}

	inline Matrix4x4T<T>& operator =(const AlignVectorsRotation<T>& right)
	{
		const Vector3DT<T> v = crossProduct(right.vectorA, right.vectorB);
		const T e = dotProduct(right.vectorA, right.vectorB);
		const T h = (1 - e) / v.squareLength();
		
		value(0, 0) = e + sqr(v.x);    value(0, 1) = h*v.x*v.y - v.z; value(0, 2) = h*v.x*v.z + v.y; value(0, 3) = 0;
		value(1, 0) = h*v.x*v.y + v.z; value(1, 1) = e + h*sqr(v.y);  value(1, 2) = h*v.y*v.z - v.x; value(1, 3) = 0;
		value(2, 0) = h*v.x*v.z - v.y; value(2, 1) = h*v.x*v.z + v.x; value(2, 2) = e + h*sqr(v.z);  value(2, 3) = 0;
		value(3, 0) = 0;               value(3, 1) = 0;               value(3, 2) = 0;               value(3, 3) = 1;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& perspectiveProjection(T left, T right, T bottom, T top, T znear, T zfar)
	{
		const T near2 = znear + znear;
		const T oo_far_near = 1 / (zfar - znear);

		value(0, 0) = near2 / (right-left); value(0, 1) = 0;                       value(0, 2) = (right+left) / (right-left); value(0, 3) = 0;
		value(1, 0) = 0;                    value(1, 1) = near2 / (top - bottom);  value(1, 2) = (top+bottom) / (top-bottom); value(1, 3) = 0;
		value(2, 0) = 0;                    value(2, 1) = 0;                       value(2, 2) = -(zfar+znear) * oo_far_near; value(2, 3) = -2*zfar*znear * oo_far_near;
		value(3, 0) = 0;                    value(3, 1) = 0;                       value(3, 2) = -1;                          value(3, 3) = 0;

		setInitialized();
		return *this;
	}

	inline Matrix4x4T<T>& orthogonalProjection(T left, T right, T bottom, T top, T znear, T zfar)
	{
		const T oo_right_left = 1 / (right - left);
		const T oo_top_bottom = 1 / (top - bottom);
		const T oo_far_near = 1 / (zfar - znear);

		value(0, 0) = 2 * oo_right_left; value(0, 1) = 0;                 value(0, 2) = 0;                value(0, 3) = -(right+left) * oo_right_left;
		value(1, 0) = 0;                 value(1, 1) = 2 * oo_top_bottom; value(1, 2) = 0;                value(1, 3) = -(top+bottom) * oo_top_bottom;
		value(2, 0) = 0;                 value(2, 1) = 0;                 value(2, 2) = -2 * oo_far_near; value(2, 3) = -(zfar+znear) * oo_far_near;
		value(3, 0) = 0;                 value(3, 1) = 0;                 value(3, 2) = 0;                value(3, 3) = 1;

		setInitialized();
		return *this;
	}

};



typedef Matrix4x4T<float> Matrix4x4f;
typedef Matrix4x4T<double> Matrix4x4d;

#ifdef BL_MATH_DOUBLE_PRECISION
	typedef Matrix4x4d Matrix4x4;
#else
	typedef Matrix4x4f Matrix4x4;
#endif



template<typename T>
inline typename Matrix4x4T<T>::Product operator *(const Matrix4x4T<T>& left, const Matrix4x4T<T>& right)
{
	return Matrix4x4T<T>::Product(left, right);
}




} // namespace Math
} // namespace BaseLib



namespace BaseLib {
	namespace TypeTraits {

		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix4x4f)
		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix4x4d)

	}
}



#endif // #ifndef BaseLib_Math_Matrix4x4_h
