/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger (Bouncing Bytes)          
                                      
Contact: e.unger@bouncingbytes.at
                                      
******************************************************************************/

#ifndef BaseLib_Math_Hermit_h
#define BaseLib_Math_Hermit_h


#include "BaseLib/Math/Quaternion.h"
#include "BaseLib/Math/Vector2D.h"



namespace BaseLib {
namespace Math {



template<typename T, typename V>
inline V hermit(const typename V& point0, const typename V& tangent0, const typename V& point1, const typename V& tangent1, const T t)
{
	const T t2 = t*t;
	const T t3 = t2*t;

	V result = point0;
	T f = 2*t3 - 3*t2 + 1;

	result *= f;

	f = t3 - 2*t2 + t;
	result += tangent0 * f;

	f = t3 - t2;
	result += tangent1 * f;

	f = -2*t3 + 3*t2;
	result += point1 * f;

	return result;
}



template<typename T, typename V>
inline V hermitTangent(const typename V& point0, const typename V& tangent0, const typename V& point1, const typename V& tangent1, const T t)
{
	const T t2 = 2*t;
	const T t3 = 3*t*t;

	V result = point0;
	T f = 2*t3 - 3*t2;
	result *= f;

	f = t3 - 2*t2 + 1;
	result += tangent0 * f;

	f = t3 - t2;
	result += tangent1 * f;

	f = -2*t3 + 3*t2;
	result += point1 * f;

	return result;
}



template<typename T, typename V>
inline T hermitLength(const typename V& point0, const typename V& tangent0, const typename V& point1, const typename V& tangent1, const T t = 1)
{
	const T sqrT = t*t;
	const T t1 = sqrT * (T)0.5;
	const T t2 = sqrT*t * static_cast<T>(1.0/3.0);
	const T t3 = sqrT*sqrT + static_cast<T>(1.0/4.0);

	V result = point0;
	T f = 2*t3 - 3*t2 + t;
	result *= f;

	f = t3 - 2*t2 + t1;
	result += tangent0 * f;
	
	f = t3 - t2;
	result += tangent1 * f;

	f = -2*t3 + 3*t2;
	result += point1 * f;

	return result.length();
}



template<typename T, typename V>
inline T hermitLength(int pointCount, const typename V * points, const typename V * tangents)
{
	assert(pointCount >= 0);
	assert(points != NULL);
	assert(tangents != NULL);

	T length = 0;

	for (int i = 1; i < pointCount; ++i)
	{
		length += hermitLength(points[i-1], tangents[i-1], points[i], tangents[i]);
	}

	return length;
}



template<typename T, typename V>
void calculateHermitTangents_HalfAngle(int pointCount, const typename V * points, V * tangents, const T roundingFactor = 1)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	const int lastTangent = pointCount-1;

	const T factor = roundingFactor * (T)0.5;

	tangents[0] = points[1] - points[0];

	for (int i = 1; i < lastTangent; ++i)
	{
		tangents[i] = points[i+1] - points[i-1];
		tangents[i] *= factor;
	}

	tangents[lastTangent] = points[lastTangent] - points[lastTangent-1];
}



template<typename T, typename V>
void calculateHermitTangents_TensionBend(int pointCount, const typename V * points, V * tangents, const T * tensions, const T * bends)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	assert(tensions != NULL);
	assert(bends != NULL);
	const int lastTangent = pointCount-1;

	{
		const int i = 0;

		V t1 = points[i+1] - points[i];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t1 *= omTension2 * (1 - bends[i]);

		tangents[i] = t1;
	}

	for (int i = 1; i < lastTangent; ++i)
	{		
		V t0 = points[i] - points[i-1];
		V t1 = points[i+1] - points[i];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t0 *= omTension2 * (1 + bends[i]);
		t1 *= omTension2 * (1 - bends[i]);

		tangents[i] = t0 + t1;
	}

	{
		const int i = lastTangent;

		V t0 = points[i] - points[i-1];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t0 *= omTension2 * (1 + bends[i]);

		tangents[i] = t0;
	}
}



template<typename T, typename V>
void calculateHermitTangents(int pointCount, const typename V * points, V * tangents, const T roundingFactor = 1, const T tangentShortening = 1)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	const int lastTangent = pointCount-1;

	const T factor = roundingFactor * (T)0.5;
	const T omTangentShortening = 1 - tangentShortening;

	tangents[0] = points[1] - points[0];

	for (int i = 1; i < lastTangent; ++i)
	{
		V t0 = points[i] - points[i-1];
		V t1 = points[i+1] - points[i];

		
		const T sl0 = t0.getSquareLength();
		const T sl1 = t1.getSquareLength();
		assert(sl0 != 0);
		assert(sl1 != 0);

		if (sl0 > sl1)
		{
			t0 *= omTangentShortening + tangentShortening * static_cast<T>(sqrt(sl1 / sl0));
		}
		else //if (sl0 < sl1)
		{
			t1 *= omTangentShortening + tangentShortening * static_cast<T>(sqrt(sl0 / sl1));
		}
		
		/*
		const T l0 = t0.length();
		const T l1 = t1.length();
		assert(l0 != 0);
		assert(l1 != 0);

		if (l0 > l1)
		{
			t0 *= l1 / l0;
		}
		else //if (l0 < l1)
		{
			t1 *= l0 / l1;
		}
		*/

		tangents[i] = t1 + t0;
		tangents[i] *= factor;
	}

	tangents[lastTangent] = points[lastTangent] - points[lastTangent-1];
}



template<typename T, typename V>
void calculateRegularHermitPositions(int pointCount, const typename V * points, const typename V * tangents, const T length, int positionsCount, T * positions)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	assert(length != 0);
	assert(positionsCount >= 2)
	assert(positions != NULL);

	const T segmentLength = length / positionsCount;

	assert(false); ////
}



/*
template<typename T>
inline Vector2DT<T> hermit(const Vector2DT<T>& point0, const Vector2DT<T>& tangent0, const Vector2DT<T>& point1, const Vector2DT<T>& tangent1, const T t)
{
	const T t2 = t*t;
	const T t3 = t2*t;

	Vector2DT<T> result = point0;
	T f = 2*t3 - 3*t2 + 1;
	result.x *= f;
	result.y *= f;

	f = t3 - 2*t2 + t;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;

	return result;
}



template<typename T>
inline Vector3DT<T> hermit(const Vector3DT<T>& point0, const Vector3DT<T>& tangent0, const Vector3DT<T>& point1, const Vector3DT<T>& tangent1, const T t)
{
	const T t2 = t*t;
	const T t3 = t2*t;

	Vector3DT<T> result = point0;
	T f = 2*t3 - 3*t2 + 1;
	result.x *= f;
	result.y *= f;
	result.z *= f;

	f = t3 - 2*t2 + t;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;

	return result;
}



template<typename T>
inline QuaternionT<T> hermit(const QuaternionT<T>& point0, const QuaternionT<T>& tangent0, const QuaternionT<T>& point1, const QuaternionT<T>& tangent1, const T t)
{
	const T t2 = t*t;
	const T t3 = t2*t;

	QuaternionT<T> result = point0;
	T f = 2*t3 - 3*t2 + 1;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	result.w *= f;

	f = t3 - 2*t2 + t;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;
	result.w += tangent0.w * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;
	result.w += tangent1.w * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;
	result.w += point1.w * f;

	return result;
}




template<typename T>
inline Vector2DT<T> hermitTangent(const Vector2DT<T>& point0, const Vector2DT<T>& tangent0, const Vector2DT<T>& point1, const Vector2DT<T>& tangent1, const T t)
{
	const T t2 = 2*t;
	const T t3 = 3*t*t;

	Vector2DT<T> result = point0;
	T f = 2*t3 - 3*t2;
	result.x *= f;
	result.y *= f;

	f = t3 - 2*t2 + 1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;

	return result;
}



template<typename T>
inline Vector3DT<T> hermitTangent(const Vector3DT<T>& point0, const Vector3DT<T>& tangent0, const Vector3DT<T>& point1, const Vector3DT<T>& tangent1, const T t)
{
	const T t2 = 2*t;
	const T t3 = 3*t*t;

	Vector3DT<T> result = point0;
	T f = 2*t3 - 3*t2;
	result.x *= f;
	result.y *= f;
	result.z *= f;

	f = t3 - 2*t2 + 1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;

	return result;
}



template<typename T>
inline QuaternionT<T> hermitTangent(const QuaternionT<T>& point0, const QuaternionT<T>& tangent0, const QuaternionT<T>& point1, const QuaternionT<T>& tangent1, const T t)
{
	const T t2 = 2*t;
	const T t3 = 3*t*t;

	QuaternionT<T> result = point0;
	T f = 2*t3 - 3*t2;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	result.w *= f;

	f = t3 - 2*t2 + 1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;
	result.w += tangent0.w * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;
	result.w += tangent1.w * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;
	result.w += point1.w * f;

	return result;
}



template<typename T>
inline T hermitLength(const Vector2DT<T>& point0, const Vector2DT<T>& tangent0, const Vector2DT<T>& point1, const Vector2DT<T>& tangent1, const T t = 1)
{
	const T sqrT = t*t;
	const T t1 = sqrT * (T)0.5;
	const T t2 = sqrT*t * static_cast<T>(1.0/3.0);
	const T t3 = sqrT*sqrT + static_cast<T>(1.0/4.0);

	Vector2DT<T> result = point0;
	T f = 2*t3 - 3*t2 + t;
	result.x *= f;
	result.y *= f;

	f = t3 - 2*t2 + t1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;

	return result.length();
}



template<typename T>
inline T hermitLength(const Vector3DT<T>& point0, const Vector3DT<T>& tangent0, const Vector3DT<T>& point1, const Vector3DT<T>& tangent1, const T t = 1)
{
	const T sqrT = t*t;
	const T t1 = sqrT * (T)0.5;
	const T t2 = sqrT*t * static_cast<T>(1.0/3.0);
	const T t3 = sqrT*sqrT + static_cast<T>(1.0/4.0);

	Vector3DT<T> result = point0;
	T f = 2*t3 - 3*t2 + t;
	result.x *= f;
	result.y *= f;
	result.z *= f;

	f = t3 - 2*t2 + t1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;

	return result.length();
}



template<typename T>
inline T hermitLength(const QuaternionT<T>& point0, const QuaternionT<T>& tangent0, const QuaternionT<T>& point1, const QuaternionT<T>& tangent1, const T t = 1)
{
	const T sqrT = t*t;
	const T t1 = sqrT * (T)0.5;
	const T t2 = sqrT*t * static_cast<T>(1.0/3.0);
	const T t3 = sqrT*sqrT + static_cast<T>(1.0/4.0);

	QuaternionT<T> result = point0;
	T f = 2*t3 - 3*t2 + t;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	result.w *= f;

	f = t3 - 2*t2 + t1;
	result.x += tangent0.x * f;
	result.y += tangent0.y * f;
	result.z += tangent0.z * f;
	result.w += tangent0.w * f;

	f = t3 - t2;
	result.x += tangent1.x * f;
	result.y += tangent1.y * f;
	result.z += tangent1.z * f;
	result.w += tangent1.w * f;

	f = -2*t3 + 3*t2;
	result.x += point1.x * f;
	result.y += point1.y * f;
	result.z += point1.z * f;
	result.w += point1.w * f;

	return static_cast<T>(sqrt(result.norm()));
}




template<typename T>
inline T hermitLength(int pointCount, const Vector2DT<T> * points, const Vector2DT<T> * tangents)
{
	assert(pointCount >= 0);
	assert(points != NULL);
	assert(tangents != NULL);

	T length = 0;

	for (int i = 1; i < pointCount; ++i)
	{
		length += hermitLength(points[i-1], tangents[i-1], points[i], tangents[i]);
	}

	return length;
}



template<typename T>
inline T hermitLength(int pointCount, const Vector3DT<T> * points, const Vector3DT<T> * tangents)
{
	assert(pointCount >= 0);
	assert(points != NULL);
	assert(tangents != NULL);

	T length = 0;

	for (int i = 1; i < pointCount; ++i)
	{
		length += hermitLength(points[i-1], tangents[i-1], points[i], tangents[i]);
	}

	return length;
}



template<typename T>
inline T hermitLength(int pointCount, const QuaternionT<T> * points, const QuaternionT<T> * tangents)
{
	assert(pointCount >= 0);
	assert(points != NULL);
	assert(tangents != NULL);

	T length = 0;

	for (int i = 1; i < pointCount; ++i)
	{
		length += hermitLength(points[i-1], tangents[i-1], points[i], tangents[i]);
	}

	return length;
}




template<typename T>
void calculateHermitTangents_HalfAngle(int pointCount, const Vector2DT<T> * points, Vector2DT<T> * tangents, const T roundingFactor = 1)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	const int lastTangent = pointCount-1;

	const T factor = roundingFactor * (T)0.5;

	tangents[0] = points[1] - points[0];

	for (int i = 1; i < lastTangent; ++i)
	{
		tangents[i] = points[i+1] - points[i-1];
		tangents[i] *= factor;
	}

	tangents[lastTangent] = points[lastTangent] - points[lastTangent-1];
}



template<typename T>
void calculateHermitTangents_TensionBend(int pointCount, const Vector2DT<T> * points, Vector2DT<T> * tangents, const T * tensions, const T * bends)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	assert(tensions != NULL);
	assert(bends != NULL);
	const int lastTangent = pointCount-1;

	{
		const int i = 0;

		Vector2DT<T> t1 = points[i+1] - points[i];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t1 *= omTension2 * (1 - bends[i]);

		tangents[i] = t1;
	}

	for (int i = 1; i < lastTangent; ++i)
	{		
		Vector2DT<T> t0 = points[i] - points[i-1];
		Vector2DT<T> t1 = points[i+1] - points[i];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t0 *= omTension2 * (1 + bends[i]);
		t1 *= omTension2 * (1 - bends[i]);

		tangents[i] = t0 + t1;
	}

	{
		const int i = lastTangent;

		Vector2DT<T> t0 = points[i] - points[i-1];

		const T omTension2 = (1 - tensions[i]) * (T)0.5;

		t0 *= omTension2 * (1 + bends[i]);

		tangents[i] = t0;
	}

}



template<typename T>
void calculateHermitTangents(int pointCount, const Vector2DT<T> * points, Vector2DT<T> * tangents, const T roundingFactor = 1, const T tangentShortening = 1)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	const int lastTangent = pointCount-1;

	const T factor = roundingFactor * (T)0.5;
	const T omTangentShortening = 1 - tangentShortening;

	tangents[0] = points[1] - points[0];

	for (int i = 1; i < lastTangent; ++i)
	{
		Vector2DT<T> t0 = points[i] - points[i-1];
		Vector2DT<T> t1 = points[i+1] - points[i];

		
		const T sl0 = t0.squareLength();
		const T sl1 = t1.squareLength();
		assert(sl0 != 0);
		assert(sl1 != 0);

		if (sl0 > sl1)
		{
			t0 *= omTangentShortening + tangentShortening * static_cast<T>(sqrt(sl1 / sl0));
		}
		else //if (sl0 < sl1)
		{
			t1 *= omTangentShortening + tangentShortening * static_cast<T>(sqrt(sl0 / sl1));
		}
		
		/*
		const T l0 = t0.length();
		const T l1 = t1.length();
		assert(l0 != 0);
		assert(l1 != 0);

		if (l0 > l1)
		{
			t0 *= l1 / l0;
		}
		else //if (l0 < l1)
		{
			t1 *= l0 / l1;
		}
		*/
/*
		tangents[i] = t1 + t0;
		tangents[i] *= factor;
	}

	tangents[lastTangent] = points[lastTangent] - points[lastTangent-1];
}



template<typename T>
void calculateRegularHermitPositions(int pointCount, const Vector2DT<T> * points, const Vector2DT<T> * tangents, const T length, int positionsCount, T * positions)
{
	assert(pointCount >= 2);
	assert(points != NULL);
	assert(tangents != NULL);
	assert(length != 0);
	assert(positionsCount >= 2)
	assert(positions != NULL);

	const T segmentLength = length / positionsCount;

	assert(false); ////
}
*/


} // namespace Math
} // namespace BaseLib



#endif // #ifndef BaseLib_Math_Hermit_h
