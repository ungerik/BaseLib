/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Array_BufferPolicy_Static_h
#define BaseLib_Containers_Array_BufferPolicy_Static_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Containers {



/**
@see Array
*/
template<typename T, int CAPACITY>
class Array_BufferPolicy_Static {
protected:

	inline Array_BufferPolicy_Static(int newCount, int newCapacity)
  		: count(newCount)
	{
		BL_ASSERT(newCount >= 0 && newCount <= CAPACITY);
	}

	inline int getCount() const
	{
		return count;
	}

	inline void setCount(int newCount)
	{
		BL_ASSERT(newCount >= 0 && newCount <= CAPACITY);
		count = newCount;
	}

	inline bool canSetCount() const
	{
		return true;
	}

	inline int getCapacity() const
	{
		return CAPACITY;
	}

	inline void setCapacity(int newCapacity)
	{
		BL_ASSERT_NEVER_REACHED
	}

	inline bool canSetCapacity() const
	{
		return false;
	}

protected:

	int count;
	T buffer[CAPACITY];
};


/*
template<class T, int CAPACITY>
class ScopedStaticArrayImplementation : public StaticArrayImplementation<T, CAPACITY> {
public:

	inline ScopedStaticArrayImplementation(int newCount, int newCapacity)
		: StaticArrayImplementation<T, CAPACITY>(newCount, newCapacity)
	{
		memset(buffer, 0, CAPACITY * sizeof(T));
	}

	inline ~ScopedStaticArrayImplementation()
	{
		for (int i = 0; i < CAPACITY; ++i)
		{
			delete buffer[i];
		}
	}

};
*/


} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Array_BufferPolicy_StaticArray_h