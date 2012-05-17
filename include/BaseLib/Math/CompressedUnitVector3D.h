/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Math_CompressedUnitVector3D_h
#define BaseLib_Math_CompressedUnitVector3D_h



#include "BaseLib/Math/Vector3D.h"



namespace BaseLib {
namespace Math {



template<typename T>
class CompressedUnitVector3DT {
public:

	BL_STATIC_ASSERT(std::numeric_limits<T>::is_integer == true, CompressedUnitVectorTypeMustBeInteger);
	BL_STATIC_ASSERT(std::numeric_limits<T>::is_signed == false, CompressedUnitVectorTypeMustBeUnsigned);

	typedef typename T ValueType;

	inline CompressedUnitVector3DT<T>()
	{
	}

	inline CompressedUnitVector3DT<T>(Undefined)
	{
	}

	CompressedUnitVector3DT<T>(UnitX);
	CompressedUnitVector3DT<T>(UnitY);
	CompressedUnitVector3DT<T>(UnitZ);
	CompressedUnitVector3DT<T>(UnitNegativeX);
	CompressedUnitVector3DT<T>(UnitNegativeY);
	CompressedUnitVector3DT<T>(UnitNegativeZ);

	inline CompressedUnitVector3DT<T>(float x, float y, float z)
	{
		set(x, y, z);
	}

	inline CompressedUnitVector3DT<T>(double x, double y, double z)
	{
		set(x, y, z);
	}

	inline explicit CompressedUnitVector3DT<T>(const Vector3Df& vector3D)
	{
		set(vector3D);
	}

	inline explicit CompressedUnitVector3DT<T>(const Vector3Dd& vector3D)
	{
		set(vector3D);
	}


	CompressedUnitVector3DT<T>(const CompressedUnitVector3DT<T>& other);
	CompressedUnitVector3DT<T>& operator =(const CompressedUnitVector3DT<T>& right);

	bool operator ==(const CompressedUnitVector3DT<T>& right) const;
	inline bool operator !=(const CompressedUnitVector3DT<T>& right) const
	{
		return !operator ==(right);
	}

	inline operator Vector3Df() const
	{
		return getAsVector3Df();
	}

	inline operator Vector3Dd() const
	{
		return getAsVector3Dd();
	}

	inline Vector3Df getAsVector3Df() const
	{
		Vector3Df vector;
		get(vector.x, vector.y, vector.z);
		return vector;
	}

	inline Vector3Dd getAsVector3Dd() const
	{
		Vector3Dd vector;
		get(vector.x, vector.y, vector.z);
		return vector;
	}

	inline void set(const Vector3Df& vector)
	{
		set(vector.x, vector.y, vector.z);
	}

	inline void set(const Vector3Dd& vector)
	{
		set(vector.x, vector.y, vector.z);
	}

	void set(float x, float y, float z);
	void get(float& x, float& y, float& z) const;

	void set(double x, double y, double z);
	void get(double& x, double& y, double& z) const;

	inline T getAzimuth() const
	{
		return azimuth;
	}

	inline T getElevation() const
	{
		return elevation;
	}

	inline void setAzimuth(T newAzimuth)
	{
		azimuth = newAzimuth;
	}

	inline void setElevation(T newElevation)
	{
		elevation = newElevation;
	}

private:

	static const T RANGE;
	static const double INV_RANGE_DOUBLE;
	static const float INV_RANGE_FLOAT;

	T azimuth;
	T elevation;

};



template<typename T>
const T CompressedUnitVector3DT<T>::RANGE = std::numeric_limits<T>::max() + 1;

template<typename T>
const double CompressedUnitVector3DT<T>::INV_RANGE_DOUBLE = 1.0 / CompressedUnitVector3DT<T>::RANGE;

template<typename T>
const float CompressedUnitVector3DT<T>::INV_RANGE_FLOAT = 1.0f / CompressedUnitVector3DT<T>::RANGE;





#include "BaseLib/Math/CompressedUnitVector3D_Generic.inl.h"



typedef CompressedUnitVector3DT<uint8> CompressedUnitVector3Db;
typedef CompressedUnitVector3DT<uint16> CompressedUnitVector3Ds;
typedef CompressedUnitVector3DT<uint32> CompressedUnitVector3Di;



} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_CompressedUnitVector3D_h
