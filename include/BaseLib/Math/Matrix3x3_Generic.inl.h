/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Math/Matrix3x3.h



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T()
{
	setUninitialized();
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(Identity)
{
	setIdentity();
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(Identity)
{
	return setIdentity();
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(typename const Matrix4x4T<T>::RotationMatrix& rotationMatrix)
{
	operator =(rotationMatrix);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(typename const Matrix4x4T<T>::RotationMatrix& rhs)
{
	value(0, 0) = rhs.matrix.value(0, 0); value(0, 1) = rhs.matrix.value(0, 1); value(0, 2) = rhs.matrix.value(0, 2);
	value(1, 0) = rhs.matrix.value(1, 0); value(1, 1) = rhs.matrix.value(1, 1); value(1, 2) = rhs.matrix.value(1, 2);
	value(2, 0) = rhs.matrix.value(2, 0); value(2, 1) = rhs.matrix.value(2, 1); value(2, 2) = rhs.matrix.value(2, 2);
	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(typename const Matrix3x4T<T>::RotationMatrix& rotationMatrix)
{
	operator =(rotationMatrix);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(typename const Matrix3x4T<T>::RotationMatrix& rhs)
{
	value(0, 0) = rhs.matrix.value(0, 0); value(0, 1) = rhs.matrix.value(0, 1); value(0, 2) = rhs.matrix.value(0, 2);
	value(1, 0) = rhs.matrix.value(1, 0); value(1, 1) = rhs.matrix.value(1, 1); value(1, 2) = rhs.matrix.value(1, 2);
	value(2, 0) = rhs.matrix.value(2, 0); value(2, 1) = rhs.matrix.value(2, 1); value(2, 2) = rhs.matrix.value(2, 2);
	setInitialized();
	return *this;
}



#ifndef BL_MATH_WITHOUT_STRINGS



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const String& string)
{
	operator =(string);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const String& right)
{
	setIdentity();
	StringTokenizer tokenizer(right);
	for (int i = 0; i < 3*3 && tokenizer.hasNextToken() == true; ++i)
	{
		tokenizer.nextToken().parse(values[i]);
	}
	setInitialized();
	return *this;
}



template<typename T>
Matrix3x3T<T>::operator String() const
{
	assertInitialized();
	String string = String::createFrom(values[0]);
	for (int i = 1; i < 3*3; ++i)
	{
		string += ' ' + String::createFrom(values[i]);
	}
	return string;
}



#endif



template<typename T>
inline Matrix3x3T<T> Matrix3x3T<T>::clone() const
{
	assertInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::setIdentity()
{
	value(0, 0) = 1; value(0, 1) = 0; value(0, 2) = 0;
	value(1, 0) = 0; value(1, 1) = 1; value(1, 2) = 0;
	value(2, 0) = 0; value(2, 1) = 0; value(2, 2) = 1;
	setInitialized();
	return *this;
}



template<typename T>
inline T& Matrix3x3T<T>::value(const int row, const int column)
{
	BL_ASSERT(row >= 0 && row < 3);
	BL_ASSERT(column >= 0 && column < 3);
	return values[column * 3 + row];
}



template<typename T>
inline const T& Matrix3x3T<T>::value(const int row, const int column) const
{
	BL_ASSERT(row >= 0 && row < 3);
	BL_ASSERT(column >= 0 && column < 3);
	assertInitialized();
	return values[column * 3 + row];
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator *=(const Matrix3x3T<T>& rhs)
{
	assertInitialized();
	Matrix3x3T<T> lhs = *this;

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



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::multiplyLeft(const Matrix3x3T<T>& lhs)
{
	*this = lhs * this->clone();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const Product& other)
{
	operator =(other);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const Product& rhs)
{
	BL_ASSERT(&rhs.lhs != this && &rhs.rhs != this);

	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			value(row, column) =	lhs.value(row, 0) * rhs.value(0, column) +
								lhs.value(row, 1) * rhs.value(1, column) +
								lhs.value(row, 2) * rhs.value(2, column);
		}
	}

	setInitialized();
	return *this;
}



template<typename T>
inline Vector3DT<T> Matrix3x3T<T>::getScaling() const
{
	assertInitialized();
	return Vector3DT<T>(sx, sy, sz);
}



template<typename T>
inline void Matrix3x3T<T>::setScaling(float scaling)
{
	assertInitialized();
	sx = scaling;
	sy = scaling;
	sz = scaling;
}



template<typename T>
inline void Matrix3x3T<T>::setScaling(const Vector3DT<T>& scaling)
{
	assertInitialized();
	sx = scaling.x;
	sy = scaling.y;
	sz = scaling.z;
}



template<typename T>
inline void Matrix3x3T<T>::scale(float scaling)
{
	assertInitialized();
	sx *= scaling;
	sy *= scaling;
	sz *= scaling;
}



template<typename T>
inline void Matrix3x3T<T>::scale(const Vector3DT<T>& scaling)
{
	assertInitialized();
	sx *= scaling.x;
	sy *= scaling.y;
	sz *= scaling.z;
}



template<typename T>
inline const T Matrix3x3T<T>::determinant() const
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



template<typename T>
inline const T Matrix3x3T<T>::subDeterminant(int row, int column) const
{
	BL_ASSERT(row >= 0 && row < 3);
	BL_ASSERT(column >= 0 && column < 3);
	assertInitialized();

	const int row0 = (row == 0) ? 1 : 0;
	const int row1 = (row == 2) ? 1 : 2;
	const int column0 = (column == 0) ? 1 : 0;
	const int column1 = (column == 2) ? 1 : 2;

	return value(row0, column0) * value(row1, column1) - value(row0, column1) * value(row1, column0);
}



template<typename T>
inline bool Matrix3x3T<T>::isReflective() const
{
	return determinant() < 0;
}



template<typename T>
inline void Matrix3x3T<T>::adjoint()
{
	assertInitialized();
	const Matrix3x3T<T> matrix3x3 = *this;

	value(0, 0) = +matrix3x3.subDeterminant(0, 0); value(0, 1) = -matrix3x3.subDeterminant(0, 1); value(0, 2) = +matrix3x3.subDeterminant(0, 2);
	value(1, 0) = -matrix3x3.subDeterminant(1, 0); value(0, 1) = +matrix3x3.subDeterminant(1, 1); value(1, 2) = -matrix3x3.subDeterminant(1, 2);
	value(2, 0) = +matrix3x3.subDeterminant(2, 0); value(0, 1) = -matrix3x3.subDeterminant(2, 1); value(2, 2) = +matrix3x3.subDeterminant(2, 2);
}



template<typename T>
inline void Matrix3x3T<T>::transpose()
{
	assertInitialized();
	swap( value(1, 0), value(0, 1) );
	swap( value(2, 0), value(0, 2) );
	swap( value(2, 1), value(1, 2) );
}



template<typename T>
inline T Matrix3x3T<T>::trace() const
{
	assertInitialized();
	return value(0, 0) + value(1, 1) + value(2, 2);
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const XRotation& rotation)
{
	operator =(rotation);
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const YRotation& rotation)
{
	operator =(rotation);
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const ZRotation& rotation)
{
	operator =(rotation);
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const YxzRotation& eulerRotation)
{
	operator =(eulerRotation);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const XRotation& rotation)
{
	const T cosine = static_cast<T>( cos(rotation.angle) );
	const T sine = static_cast<T>( sin(rotation.angle) );

	value(0, 0) = 1; value(0, 1) = 0;      value(0, 2) = 0;      
	value(1, 0) = 0; value(1, 1) = cosine; value(1, 2) = -sine;  
	value(2, 0) = 0; value(2, 1) = sine;   value(2, 2) = cosine; 

	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const YRotation& rotation)
{
	const T cosine = static_cast<T>( cos(rotation.angle) );
	const T sine = static_cast<T>( sin(rotation.angle) );

	value(0, 0) = cosine; value(0, 1) = 0; value(0, 2) = sine;   
	value(1, 0) = 0;      value(1, 1) = 1; value(1, 2) = 0;      
	value(2, 0) = -sine;  value(2, 1) = 0; value(2, 2) = cosine; 

	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const ZRotation& rotation)
{
	const T cosine = static_cast<T>( cos(rotation.angle) );
	const T sine = static_cast<T>( sin(rotation.angle) );

	value(0, 0) = cosine; value(0, 1) = -sine;  value(0, 2) = 0; 
	value(1, 0) = sine;   value(1, 1) = cosine; value(1, 2) = 0; 
	value(2, 0) = 0;      value(2, 1) = 0;      value(2, 2) = 1; 

	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const YxzRotation& eulerRotation)
{
	const T sinH = static_cast<T>( sin(eulerRotation.yAngle) );
	const T cosH = static_cast<T>( cos(eulerRotation.yAngle) );
	const T sinP = static_cast<T>( sin(eulerRotation.xAngle) );
	const T cosP = static_cast<T>( cos(eulerRotation.xAngle) );
	const T sinR = static_cast<T>( sin(eulerRotation.zAngle) );
	const T cosR = static_cast<T>( cos(eulerRotation.zAngle) );

	value(0, 0) = cosR*cosH-sinR*sinP*sinH; value(0, 1) = -sinR*cosP; value(0, 2) = cosR*sinH+sinR*sinP*cosH; 
	value(1, 0) = sinR*cosH+cosR*sinP*sinH; value(1, 1) = cosR*cosP;  value(1, 2) = sinR*sinH-cosR*sinP*cosH; 
	value(2, 0) = -cosP*sinH;               value(2, 1) = sinP;       value(2, 2) = cosP*cosH; 

	setInitialized();
	return *this;
}



template<typename T>
inline void Matrix3x3T<T>::extractEulerAngles(double& headAngle, double& pitchAngle, double& rollAngle)
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



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::setToCoordinateSystemBase(const Vector3DT<T>& xVector, const Vector3DT<T>& yVector, const Vector3DT<T>& zVector)
{
	value(0, 0) = xVector.x; value(0, 1) = xVector.y; value(0, 2) = xVector.z;
	value(1, 0) = yVector.x; value(1, 1) = yVector.y; value(1, 2) = yVector.z;
	value(2, 0) = zVector.x; value(2, 1) = zVector.y; value(2, 2) = zVector.z;
	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const QuaternionT<T>& quaternion)
{
	operator =(quaternion);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const QuaternionT<T>& rhs)
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
	
	value(0, 0) = 1 - (yy + zz);	value(0, 1) = xy - wz;		value(0, 2) = xz + wy;
	value(1, 0) = xy + wz;		value(1, 1) = 1 - (xx + zz);	value(1, 2) = yz - wx;
	value(2, 0) = xz - wy;		value(2, 1) = yz + wx;		value(2, 2) = 1 - (xx + yy);

	setInitialized();
	return *this;
}



template<typename T>
inline Matrix3x3T<T>::Matrix3x3T(const AlignVectorsRotation<T>& rotation)
{
	operator =(rotation);
}



template<typename T>
inline Matrix3x3T<T>& Matrix3x3T<T>::operator =(const AlignVectorsRotation<T>& rhs)
{
	const T e = dotProduct(rhs.vectorA, rhs.vectorB);
	if (e != 1)
	{
		const Vector3DT<T> v = crossProduct(rhs.vectorA, rhs.vectorB);
		const T h = (1 - e) / v.squareLength();
		
		value(0, 0) = e + sqr(v.x);    value(0, 1) = h*v.x*v.y - v.z; value(0, 2) = h*v.x*v.z + v.y;
		value(1, 0) = h*v.x*v.y + v.z; value(1, 1) = e + h*sqr(v.y);  value(1, 2) = h*v.y*v.z - v.x;
		value(2, 0) = h*v.x*v.z - v.y; value(2, 1) = h*v.x*v.z + v.x; value(2, 2) = e + h*sqr(v.z);
		setInitialized();
	}
	else
	{
		setIdentity();
	}

	return *this;
}
