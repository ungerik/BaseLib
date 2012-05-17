/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_AutoPointer_h
#define BaseLib_Utilities_AutoPointer_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {


template<typename T>
class AutoPointer {
public:



#ifndef BL_COMPILER_GCC
	friend AutoPointer<T>;
#endif



	typedef T ValueType;

	inline AutoPointer(T* newPointer = NULL)
		: pointer(newPointer)
	{
	}

	inline AutoPointer(AutoPointer<T>& other)
		: pointer(other.pointer)
	{
		other.pointer = NULL;
	}

	inline ~AutoPointer()
	{
		delete pointer;
	}

	inline AutoPointer<T>& operator =(AutoPointer<T>& right)
	{
		delete pointer;
		pointer = right.pointer;
		right.pointer = NULL;
		return *this;
	}

	inline AutoPointer<T>& operator =(T* right)
	{
		delete pointer;
		pointer = right;
		return *this;
	}

	inline operator T*() const
	{
		return pointer;
	}

	inline T* getPointer() const
	{
		return pointer;
	}

	inline void swap(AutoPointer<T>& other)
	{
		T* temp = pointer;
		pointer = other.pointer;
		other.pointer = temp;
	}

	inline T* operator ->() const
	{
		return pointer;
	}

	//inline const T* operator ->() const
	//{
	//	return pointer;
	//}

private:

	T* pointer;

};



template<typename T>
inline void swap(AutoPointer<T>& left, AutoPointer<T>& right)
{
	left.swap(right);
}



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_AutoPointer_h

