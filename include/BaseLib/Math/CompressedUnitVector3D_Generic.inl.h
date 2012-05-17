/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Math/CompressedUnitVector3D.h



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitX)
	: azimuth(0)
	, elevation(0)
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitY)
	: azimuth(RANGE / 4) // TODO: Precalculated constant
	, elevation(0)
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitZ)
	: azimuth(0)
	, elevation(RANGE / 4) // TODO: Precalculated constant
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitNegativeX)
	: azimuth(RANGE / 2) // TODO: Precalculated constant
	, elevation(0)
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitNegativeY)
	: azimuth(RANGE * 3 / 4) // TODO: Precalculated constant
	, elevation(0)
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(UnitNegativeZ)
	: azimuth(0)
	, elevation(RANGE * 3 / 4) // TODO: Precalculated constant
{
}



template<typename T>
inline CompressedUnitVector3DT<T>::CompressedUnitVector3DT(const CompressedUnitVector3DT<T>& other)
	: azimuth(other.getAzimuth())
	, elevation(other.getElevation())
{
}



template<typename T>
inline CompressedUnitVector3DT<T>& CompressedUnitVector3DT<T>::operator =(const CompressedUnitVector3DT<T>& right)
{
	azimuth = other.getAzimuth();
	elevation = other.getElevation();
	return *this;
}



template<typename T>
inline bool CompressedUnitVector3DT<T>::operator ==(const CompressedUnitVector3DT<T>& right) const
{
	return azimuth == other.getAzimuth() && elevation == other.getElevation();
}



template<typename T>
inline void CompressedUnitVector3DT<T>::set(float x, float y, float z)
{
	azimuth = static_cast<T>(atan2(y, x) * RANGE / TWO_PI_F); // TODO: Make robust // TODO: Premultiply
	elevation = static_cast<T>(atan(z) * RANGE / TWO_PI_F);
}



template<typename T>
inline void CompressedUnitVector3DT<T>::get(float& x, float& y, float& z) const
{
	const float floatAzimuth = static_cast<float>(azimuth) * INV_RANGE_FLOAT * TWO_PI_F; // TODO: Premultiply
	const float floatElevation = static_cast<float>(elevation) * INV_RANGE_FLOAT * TWO_PI_F;
	const float cosElevation = cos(floatElevation);

	x = cos(floatAzimuth) * cosElevation;
	y = sin(floatAzimuth) * cosElevation;
	z = sin(floatElevation);
}



template<typename T>
inline void CompressedUnitVector3DT<T>::set(double x, double y, double z)
{
	azimuth = static_cast<T>(atan2(y, x) * RANGE / TWO_PI); // TODO: Make robust // TODO: Premultiply
	elevation = static_cast<T>(atan(z) * RANGE / TWO_PI);
}



template<typename T>
inline void CompressedUnitVector3DT<T>::get(double& x, double& y, double& z) const
{
	const double floatAzimuth = static_cast<double>(azimuth) * INV_RANGE_DOUBLE * TWO_PI; // TODO: Premultiply
	const double floatElevation = static_cast<double>(elevation) * INV_RANGE_DOUBLE * TWO_PI;
	const double cosElevation = cos(floatElevation);

	x = cos(floatAzimuth) * cosElevation;
	y = sin(floatAzimuth) * cosElevation;
	z = sin(floatElevation);
}
