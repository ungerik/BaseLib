/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_Quaternion_h
#define BaseLib_Math_Quaternion_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Math {



#ifndef BL_MATH_WITHOUT_STRINGS
	using BaseLib::Strings::String;
	using BaseLib::Strings::StringTokenizer;
#endif



struct XRotation {
	const double& angle;
	inline explicit XRotation(const double& rotationAngle)
		: angle(rotationAngle)
	{
	}
};



struct YRotation {
	const double& angle;
	inline explicit YRotation(const double& rotationAngle)
		: angle(rotationAngle)
	{
	}
};



struct ZRotation {
	const double& angle;
	inline explicit ZRotation(const double& rotationAngle)
		: angle(rotationAngle)
	{
	}
};



struct YxzRotation {
	const double& yAngle;
	const double& xAngle;
	const double& zAngle;
	inline explicit YxzRotation(const double& headAngle, const double& pitchAngle, const double& rollAngle)
		: yAngle(headAngle)
		, xAngle(pitchAngle)
		, zAngle(rollAngle)
	{
	}
};



template<typename T> struct Vector3DT;
template<typename T> struct VectorHom3DT;
template<typename T> struct Matrix3x3T;
template<typename T> struct Matrix3x4T;
template<typename T> struct Matrix4x4T;



template<typename T = float>
struct BL_ALIGN_SIMD(QuaternionT) {

	typedef typename T ValueType;

	struct Product {
		const QuaternionT<T>& left;
		const QuaternionT<T>& right;
		inline explicit Product(const QuaternionT<T>& l, const QuaternionT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct ProductProduct {
		const Product& left;
		const QuaternionT<T>& right;
		inline explicit ProductProduct(const Product& l, const QuaternionT<T>& r)
			: right(r)
			, left(l)
		{
		}
	};

	struct Slerp {
		const QuaternionT<T>& quaternion1;
		const QuaternionT<T>& quaternion2;
		const double& factor;
		inline explicit Slerp(const QuaternionT<T>& from, const QuaternionT<T>& to, const double& t)
			: quaternion1(from)
			, quaternion2(to)
			, factor(t)
		{
		}
	};

	struct Inverse {
		const QuaternionT<T>& quaternion;
		inline explicit Inverse(const QuaternionT<T>& argument)
			: quaternion(argument)
		{
		}
	};

	struct Negation {
		const QuaternionT<T>& quaternion;
		inline explicit Negation(const QuaternionT<T>& argument)
			: quaternion(argument)
		{
		}
	};

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

	inline QuaternionT<T>()
	{
		setUninitialized();
	}

	inline QuaternionT<T>(T newX, T newY, T newZ, T newW)
		: x(newX)
		, y(newY)
		, z(newZ)
		, w(newW)
	{
		setInitialized();
	}

	inline explicit QuaternionT<T>(const T source[4])
		: x(source[0])
		, y(source[1])
		, z(source[2])
		, w(source[3])
	{
		setInitialized();
	}

	inline QuaternionT<T>(const Vector3DT<T>& rotationAxis, T rotationAngle)
	{
		rotation(rotationAxis, rotationAngle);
	}

	inline QuaternionT<T>& rotation(const Vector3DT<T>& rotationAxis, T rotationAngle)
	{
		rotationAngle *= 0.5;
		const T s = sin(rotationAngle);
		x = rotationAxis.x * s;
		y = rotationAxis.y * s;
		z = rotationAxis.z * s;
		w = cos(rotationAngle);
		normalize();
		setInitialized();
		return *this;
	}

	inline void calculateRotationAxisAndAngle(Vector3DT<T>& rotationAxis, T& rotationAngle) const
	{
		assertInitialized();
		const T cosAngle = w;
		const T sinAngle = sqrt(1 - sqr(cosAngle));
		rotationAngle = acos(cosAngle);

		const T ooSinAngle = fabs(sinAngle) < 0.0005 ? 1 : 1 / sinAngle;
		rotationAxis.x = x * ooSinAngle;
		rotationAxis.y = y * ooSinAngle;
		rotationAxis.z = z * ooSinAngle;
	}

	inline QuaternionT<T>(const vec4f& vec4)
	{
		operator =(vec4);
	}

	inline QuaternionT<T>(const vec4d& vec4)
	{
		operator =(vec4);
	}

	inline QuaternionT<T>& operator =(const vec4f& vec4)
	{
		x = static_cast<T>(vec4.x);
		y = static_cast<T>(vec4.y);
		z = static_cast<T>(vec4.z);
		w = static_cast<T>(vec4.w);
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>& operator =(const vec4d& vec4)
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
	inline QuaternionT<T>(const String& string)
	{
		operator =(string);
	}

	inline QuaternionT<T>& operator =(const String& right)
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

	inline QuaternionT<T> clone() const
	{
		assertInitialized();
		return *this;
	}

	inline QuaternionT<T>& assignFromArray(const T source[4])
	{
		x = source[0];
		y = source[1];
		z = source[2];
		w = source[3];
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>(Identity)
	{
		identity();
	}

	inline QuaternionT<T>& operator =(Identity)
	{
		return identity();
	}

	inline QuaternionT<T>& identity()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>& negate()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}	

	inline static bool isShortestRotation(const QuaternionT<T>& orientation1, const QuaternionT<T>& orientation2)
	{
		return dotProduct(orientation1, orientation2) >= 0;
	}

	inline void makeShortestRotation(const QuaternionT<T>& otherOrientation)
	{
		assertInitialized();
		if (isShortestRotation(*this, otherOrientation) == false)
		{
			negate();
		}
	}

	inline QuaternionT<T>& operator *=(const QuaternionT<T>& right)
	{
		assertInitialized();
		const QuaternionT<T> left = *this;
		*this = left * right;
		return *this;
	}

	inline QuaternionT<T>& multiplyLeft(const QuaternionT<T>& rotation)
	{
		*this = rotation * this->clone();
		return *this;
	}

	inline QuaternionT<T>(const Negation& other)
	{
		operator =(other);
	}

	inline QuaternionT<T>& operator =(const Negation& negation)
	{
		BL_ASSERT(&negation.quaternion != this);
		*this = negation.quaternion;
		setInitialized();
		return negate();
	}

	inline QuaternionT<T>(const Product& product)
	{
		operator =(product);
	}

	inline QuaternionT<T>& operator =(const Product& product)
	{
		BL_ASSERT(&product.left != this && &product.right != this);
		x = product.left.w * product.right.x + product.left.x*product.right.w + product.left.y*product.right.z - product.left.z*product.right.y;
		y = product.left.w * product.right.y + product.left.y*product.right.w + product.left.z*product.right.x - product.left.x*product.right.z;
		z = product.left.w * product.right.z + product.left.z*product.right.w + product.left.x*product.right.y - product.left.y*product.right.x;
		w = product.left.w * product.right.w - product.left.x*product.right.x - product.left.y*product.right.y - product.left.z*product.right.z;
		setInitialized();
		normalize();
		return *this;
	}

	inline QuaternionT<T>(const ProductProduct& productProduct)
	{
		operator =(productProduct);
	}

	inline QuaternionT<T>& operator =(const ProductProduct& productProduct)
	{
		operator =(productProduct.left);
		operator *=(productProduct.right);
		return *this;
	}

	inline QuaternionT<T>(const Matrix3x3T<T>& rotationMatrix)
	{
		operator =(rotationMatrix);
	}

	inline QuaternionT<T>& operator =(const Matrix3x3T<T>& right)
	{
		const T tr = right.trace();

		//if (tr > 0)
		{
			T s = (T)sqrt(tr + 1);
			w = s * (T)0.5;
			s = (T)0.5 / s;

			x = (right.value(2, 1) - right.value(1, 2)) * s;
			y = (right.value(0, 2) - right.value(2, 0)) * s;
			z = (right.value(1, 0) - right.value(0, 1)) * s;
		}
		/*else 
		{
			const int nxt[] = {1, 2, 0};

			int i = (right.value(1, 1) > right.value(0, 0)) ? 1 : 0;
			if (right.value(2, 2) > right.value(i, i)) i = 2;

			int j = nxt[i];
			int k = nxt[j];

			T s = (T)sqrt((right.value(i, i) - (right.value(j, j) + right.value(k, k))) + 1);

			asArray()[i] = s * (T)0.5;

			if (s != 0) s = (T)0.5 / s;
		
			asArray()[3] = (right.value(k, j) - right.value(j, k)) * s;
			asArray()[j] = (right.value(j, i) - right.value(i, j)) * s;
			asArray()[k] = (right.value(k, i) - right.value(i, k)) * s;
		}*/

		setInitialized();
		normalize();
		return *this;
	}

	inline QuaternionT<T>(const Matrix3x4T<T>& rotationMatrix)
	{
		operator =(rotationMatrix);
	}

	inline QuaternionT<T>& operator =(const Matrix3x4T<T>& right)
	{
		const T tr = right.trace();

		//if (tr > 0)
		{
			T s = (T)sqrt(tr);
			w = s * (T)0.5;
			s = (T)0.5 / s;

			x = (right.value(2, 1) - right.value(1, 2)) * s;
			y = (right.value(0, 2) - right.value(2, 0)) * s;
			z = (right.value(1, 0) - right.value(0, 1)) * s;
		}
		/*else
		{
			const int nxt[] = {1, 2, 0};

			int i = (right.value(1, 1) > right.value(0, 0)) ? 1 : 0;
			if (right.value(2, 2) > right.value(i, i)) i = 2;

			int j = nxt[i];
			int k = nxt[j];

			T s = (T)sqrt((right.value(i, i) - (right.value(j, j) + right.value(k, k))) + 1);

			asArray()[i] = s * (T)0.5;

			if (s != 0) s = (T)0.5 / s;
		
			asArray()[3] = (right.value(k, j) - right.value(j, k)) * s;
			asArray()[j] = (right.value(j, i) - right.value(i, j)) * s;
			asArray()[k] = (right.value(k, i) - right.value(i, k)) * s;
		}*/

		setInitialized();
		normalize();
		return *this;
	}

	inline QuaternionT<T>(const Matrix4x4T<T>& rotationMatrix)
	{
		operator =(rotationMatrix);
	}

	inline QuaternionT<T>& operator =(const Matrix4x4T<T>& right)
	{
		const T tr = right.trace();

		//if (tr > 0)
		{
			T s = (T)sqrt(tr);
			w = s * (T)0.5;
			s = (T)0.5 / s;

			x = (right.value(2, 1) - right.value(1, 2)) * s;
			y = (right.value(0, 2) - right.value(2, 0)) * s;
			z = (right.value(1, 0) - right.value(0, 1)) * s;
		}
		/*else
		{
			const int nxt[] = {1, 2, 0};

			int i = (right.value(1, 1) > right.value(0, 0)) ? 1 : 0;
			if (right.value(2, 2) > right.value(i, i)) i = 2;

			int j = nxt[i];
			int k = nxt[j];

			T s = (T)sqrt((right.value(i, i) - (right.value(j, j) + right.value(k, k))) + 1);

			asArray()[i] = s * (T)0.5;

			if (s != 0) s = (T)0.5 / s;
		
			asArray()[3] = (right.value(k, j) - right.value(j, k)) * s;
			asArray()[j] = (right.value(j, i) - right.value(i, j)) * s;
			asArray()[k] = (right.value(k, i) - right.value(i, k)) * s;
		}*/

		setInitialized();
		normalize();
		return *this;
	}

	inline QuaternionT<T>(const XRotation& rotation)
	{
		operator =(rotation);
	}

	inline QuaternionT<T>(const YRotation& rotation)
	{
		operator =(rotation);
	}

	inline QuaternionT<T>(const ZRotation& rotation)
	{
		operator =(rotation);
	}

	inline QuaternionT<T>(const YxzRotation& eulerRotation)
	{
		operator =(eulerRotation);
	}

	inline QuaternionT<T>& operator =(const XRotation& rotation)
	{
		const T angle = static_cast<T>(rotation.angle * 0.5);
		x = sin(angle);
		y = 0;
		z = 0;
		w = cos(angle);
		BL_ASSERT(isUnitQuaternion() == true);
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>& operator =(const YRotation& rotation)
	{
		const T angle = static_cast<T>(rotation.angle * 0.5);
		x = 0;
		y = sin(angle);
		z = 0;
		w = cos(angle);
		BL_ASSERT(isUnitQuaternion() == true);
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>& operator =(const ZRotation& rotation)
	{
		const T angle = static_cast<T>(rotation.angle * 0.5);
		x = 0;
		y = 0;
		z = sin(angle);
		w = cos(angle);
		BL_ASSERT(isUnitQuaternion() == true);
		setInitialized();
		return *this;
	}

	inline QuaternionT<T>& operator =(const YxzRotation& eulerRotation)
	{
		QuaternionT<T> qY = YRotation(eulerRotation.yAngle);
		QuaternionT<T> qX = XRotation(eulerRotation.xAngle);
		QuaternionT<T> qZ = ZRotation(eulerRotation.zAngle);

		*this = qY * qX * qZ;

		setInitialized();
		return *this;
	}

	inline QuaternionT<T>(const Slerp& slerp)
	{
		operator =(slerp);
	}

	inline QuaternionT<T>& operator =(const Slerp& right)
	{
		const T d = acos(right.quaternion1.x*right.quaternion2.x + right.quaternion1.y*right.quaternion2.y + right.quaternion1.z*right.quaternion2.z + right.quaternion1.w*right.quaternion2.w);
		const T ooSinD = 1 / sin(d);

		const T f1 = sin(d*(1- right.factor)) * ooSinD;
		const T f2 = sin(d*right.factor) * ooSinD;

		x = right.quaternion1.x * f1 + right.quaternion2.x * f2;
		y = right.quaternion1.y * f1 + right.quaternion2.y * f2;
		z = right.quaternion1.z * f1 + right.quaternion2.z * f2;
		w = right.quaternion1.w * f1 + right.quaternion2.w * f2;

		setInitialized();
		normalize();
		return *this;
	}

	inline const T norm() const
	{
		assertInitialized();
		return x*x + y*y + z*z + w*w;
	}

	inline QuaternionT<T>& s3ToR4()
	{
		assertInitialized();
		const T f = 1 / sqrt(2*(1-w));

		x *= f;
		y *= f;
		z *= f;
		w = (1-w) * f;

		return *this;
	}

	inline QuaternionT<T>& r4ToS3()
	{
		assertInitialized();
		const T ooNorm = 1 / norm();
		const T w2n = 2*w*ooNorm;

		x *= w2n;		
		y *= w2n;		
		z *= w2n;		
		w = (x*x + y*y + z*z - w*w) * ooNorm;

		return normalize();
	}

	inline QuaternionT<T>& inverse()
	{
		///BL_ASSERT(isUnitQuaternion() == true);
		return conjugate();
		/*
		// Inverse of non unit-quaternion:
		const T f = -1 / norm();
		x *= f;
		y *= f;
		z *= f;
		w *= -f;
		return *this;
		*/
	}

	inline QuaternionT<T>& conjugate()
	{
		assertInitialized();
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline QuaternionT<T>(const Inverse& inverse)
	{
		operator =(inverse);
	}

	inline QuaternionT<T>& operator =(const Inverse& right)
	{
		*this = right.quaternion;
		setInitialized();
		inverse();
		return *this;
	}

	inline void rotateVector(Vector3DT<T>& vector) const 
	{		
		assertInitialized();
		const QuaternionT<T> quaternionVector(vector.x, vector.y, vector.z, 0);
		//const QuaternionT<T> halfRotation = slerp(QuaternionT<T>(Identity()), *this, 0.5);
		//const QuaternionT<T> inverseHalfRotation = ::NextReality::inverse(halfRotation);
		//const QuaternionT<T> result = halfRotation * quaternionVector * inverseHalfRotation;

		const QuaternionT<T> result = *this * quaternionVector * clone().inverse();

		vector.x = result.x;
		vector.y = result.y;
		vector.z = result.z;
		
		/*
		Matrix3x3T<T> rotationMatrix = *this;
		vector *= rotationMatrix;
		*/
	}

	inline const bool isUnitQuaternion(const double tolerance = 0.001) const
	{
		const double n = norm();
		return (n > (1.0 - tolerance) && n < (1.0 + tolerance));
	}

	inline QuaternionT<T>& normalize()
	{
		const T n = norm();
		if (n != 1 && n != 0)
		{
			const T ool = 1 / sqrt(n);
			x *= ool;
			y *= ool;
			z *= ool;
			w *= ool;
		}
		return *this;
	}

	inline bool operator ==(const QuaternionT<T>& right) const
	{
		assertInitialized();
		return x == right.x && y == right.y && z == right.z && w == right.w;
	}

	inline bool operator !=(const QuaternionT<T>& right) const
	{
		return !operator ==(right);
	}

	inline QuaternionT<T>(const Vector3DT<T>& from, const Vector3DT<T>& to)
	{
		alignVectorsRotation(from, to);
	}

	inline QuaternionT<T>& alignVectorsRotation(const Vector3DT<T>& from, const Vector3DT<T>& to)
	{
		Vector3DT<T> cr = crossProduct(from, to);
		const T sr = static_cast<T>(sqrt(2 * (1 + dotProduct(from, to))));
		cr /= sr;

		x = cr.x;
		y = cr.y;
		z = cr.z;
		w = sr * static_cast<T>(0.5);

		setInitialized();
		normalize();
		return *this;
	}
};



typedef QuaternionT<float> Quaternion;
typedef QuaternionT<double> Quaterniond;



template<typename T>
inline typename QuaternionT<T>::Product operator *(const QuaternionT<T>& left, const QuaternionT<T>& right)
{
	return QuaternionT<T>::Product(left, right);
}



template<typename T>
inline typename QuaternionT<T>::ProductProduct operator *(typename const QuaternionT<T>::Product& left, const QuaternionT<T>& right)
{
	return QuaternionT<T>::ProductProduct(left, right);
}



template<typename T>
inline typename QuaternionT<T>::Slerp slerp(const QuaternionT<T>& from, const QuaternionT<T>& to, const double& t)
{
	return QuaternionT<T>::Slerp(from, to, t);
}



template<typename T>
inline typename QuaternionT<T>::Inverse inverse(const QuaternionT<T>& argument)
{
	return QuaternionT<T>::Inverse(argument);
}



template<typename T>
inline typename QuaternionT<T>::Negation _negate(const QuaternionT<T>& argument)
{
	return QuaternionT<T>::Negation(argument);
}



template<typename T>
inline T dotProduct(const QuaternionT<T>& left, const QuaternionT<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w + right.w;
}












} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_Quaternion_h
