/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/
/*
#ifndef BaseLib_Containers_ScopedArray_h
#define BaseLib_Containers_ScopedArray_h



#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Containers {



template<class T>
class ScopedArray : public Array<T, ScopedDynamicArrayImplementation<T> > {
public:

	typedef Array<T, ScopedDynamicArrayImplementation<T> > A;

	explicit inline ScopedArray(int newLength = 0)
		: A(newLength)
	{
	}

	explicit inline ScopedArray(const T& value)
		: A(value, 1)
	{
	}

	inline ScopedArray(const T * values, int newLength)
		: A(values, newLength)
	{
	}

	inline ScopedArray(const A& other)
		: A(other)
	{
	}

	template<class I>
	inline ScopedArray(const I& beginRange, const I& endRange)
		: A(beginRange, endRange)
	{
	}

	inline void append(const T& value, int count = 1)
	{
		BL_ASSERT(count == 1 || count == 0);
		A::append(value, count);
	}

	inline void insert(const T& value, const int index = 0, const int count = 1)
	{
		BL_ASSERT(count == 1 || count == 0);
		A::insert(value, index, count);
	}

	inline void remove(int index = 0, int count = 1)
	{
		int oldLenght = getLength();
		int newLength = oldLenght - count;
		memmove(&buffer[index], &buffer[index+count], (newLength - index) * sizeof(T));
		if (canSetLength() == true)
		{
			setLength(newLength);
		}
	}

	inline void assign(const T& value, int beginIndex, int endIndex)
	{
		BL_ASSERT(beginIndex == endIndex-1 || beginIndex == endIndex);
		A::assign(value, beginIndex, endIndex);
	}

};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_ScopedArray_h
*/