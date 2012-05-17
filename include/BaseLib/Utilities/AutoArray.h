/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_AutoArray_h
#define BaseLib_Utilities_AutoArray_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {



template<typename T>
class AutoArray {
public:

	friend AutoArray<T>;

	typedef T ValueType;

	inline AutoArray(T* newArray = NULL)
		: array(newArray)
	{
	}

	inline AutoArray(AutoArray<T>& other)
		: array(other.array)
	{
		other.array = NULL;
	}

	inline ~AutoArray()
	{
		delete[] array;
	}

	inline AutoArray<T>& operator =(AutoArray<T>& right)
	{
		delete[] array;
		array = right.array;
		right.array = NULL;
		return *this;
	}

	inline AutoArray<T>& operator =(T* right)
	{
		delete[] array;
		array = right;
		return *this;
	}

	inline operator T*() const
	{
		return array;
	}

	//inline operator const T*() const
	//{
	//	return array;
	//}

	inline void swap(AutoArray<T>& other)
	{
		T* temp = array;
		array = other.array;
		other.array = temp;
	}

private:

	T* array;

};



template<typename T>
inline void swap(AutoArray<T>& left, AutoArray<T>& right)
{
	left.swap(right);
}



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_AutoArray_h

