/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Matrix3x3_h
#define BaseLib_Math_Matrix3x3_h



#include "BaseLib/Math/Vector3D.h"
#include "BaseLib/Math/Quaternion.h"



namespace BaseLib {
namespace Math {



template<typename T>
struct AlignVectorsRotation {
	const Vector3DT<T>& vectorA;
	const Vector3DT<T>& vectorB;
	inline explicit AlignVectorsRotation(const Vector3DT<T>& from, const Vector3DT<T>& to)
		: vectorA(from)
		, vectorB(to)
	{
	}
};



template<typename T> struct Matrix4x4T;
template<typename T> struct Matrix3x4T;



template<typename T>
struct BL_ALIGN_SIMD(Matrix3x3T) {

	typedef typename T ValueType;

	struct Product {
		const Matrix3x3T<T>& lhs;
		const Matrix3x3T<T>& rhs;
		inline explicit Product(const Matrix3x3T<T>& l, const Matrix3x3T<T>& r)
			: rhs(r)
			, lhs(l)
		{
		}
	};

	union
	{
		T values[3*3];
		struct {
			Vector3DT<T> columns[3];
		};
		struct {
			float  sx, m10, m20;
			float m01,  sy, m21;
			float m02, m12,  sz;
		};
	};

	BL_MATH_INITILIZED_CHECK_MEMBERS

	Matrix3x3T<T>();

	Matrix3x3T<T>(Identity);

	Matrix3x3T<T>& operator =(Identity);

	Matrix3x3T<T>(typename const Matrix4x4T<T>::RotationMatrix& rotationMatrix);

	Matrix3x3T<T>& operator =(typename const Matrix4x4T<T>::RotationMatrix& rhs);

	Matrix3x3T<T>(typename const Matrix3x4T<T>::RotationMatrix& rotationMatrix);

	Matrix3x3T<T>& operator =(typename const Matrix3x4T<T>::RotationMatrix& rhs);

#ifndef BL_MATH_WITHOUT_STRINGS
	Matrix3x3T<T>(const String& string);

	Matrix3x3T<T>& operator =(const String& right);

	operator String() const;
#endif

	Matrix3x3T<T> clone() const;

	Matrix3x3T<T>& setIdentity();

	T& value(const int row, const int column);

	const T& value(const int row, const int column) const;

	Matrix3x3T<T>& operator *=(const Matrix3x3T<T>& rhs);

	Matrix3x3T<T>& multiplyLeft(const Matrix3x3T<T>& lhs);

	Matrix3x3T<T>(const Product& other);

	Matrix3x3T<T>& operator =(const Product& rhs);

	Vector3DT<T> getScaling() const;

	void setScaling(float scaling);

	void setScaling(const Vector3DT<T>& scaling);

	void scale(float scaling);

	void scale(const Vector3DT<T>& scaling);

	const T determinant() const;

	const T subDeterminant(int row, int column) const;

	bool isReflective() const;

	void adjoint();

	void transpose();

	T trace() const;

	Matrix3x3T<T>(const XRotation& rotation);

	Matrix3x3T<T>(const YRotation& rotation);

	Matrix3x3T<T>(const ZRotation& rotation);

	Matrix3x3T<T>(const YxzRotation& eulerRotation);

	Matrix3x3T<T>& operator =(const XRotation& rotation);

	Matrix3x3T<T>& operator =(const YRotation& rotation);

	Matrix3x3T<T>& operator =(const ZRotation& rotation);

	Matrix3x3T<T>& operator =(const YxzRotation& eulerRotation);

	void extractEulerAngles(double& headAngle, double& pitchAngle, double& rollAngle);

	Matrix3x3T<T>& setToCoordinateSystemBase(const Vector3DT<T>& xVector, const Vector3DT<T>& yVector, const Vector3DT<T>& zVector);

	Matrix3x3T<T>(const QuaternionT<T>& quaternion);

	Matrix3x3T<T>& operator =(const QuaternionT<T>& rhs);

	Matrix3x3T<T>(const AlignVectorsRotation<T>& rotation);

	Matrix3x3T<T>& operator =(const AlignVectorsRotation<T>& rhs);

};



typedef Matrix3x3T<float> Matrix3x3f;
typedef Matrix3x3T<double> Matrix3x3d;

#ifdef BL_MATH_DOUBLE_PRECISION
	typedef Matrix3x3d Matrix3x3;
#else
	typedef Matrix3x3f Matrix3x3;
#endif



template<typename T>
inline const AlignVectorsRotation<T> alignVectorsRotation(const Vector3DT<T>& from, const Vector3DT<T>& to)
{
	return AlignVectorsRotation<T>(from, to);
}



template<typename T>
inline typename Matrix3x3T<T>::Product operator*(const Matrix3x3T<T>& lhs, const Matrix3x3T<T>& rhs)
{
	return Matrix3x3T<T>::Product(lhs, rhs);
}



#include "BaseLib/Math/Matrix3x3_Generic.inl.h"



} // namespace Math
} // namespace BaseLib



namespace BaseLib {
	namespace TypeTraits {

		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix3x3f)
		BL_DEFINE_ISVALUETYPE(::BaseLib::Math::Matrix3x3d)

	}
}



#endif // #ifndef BaseLib_Math_Matrix3x3_h
