/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Array_BufferPolicy_ConstCount_h
#define BaseLib_Containers_Array_BufferPolicy_ConstCount_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Containers {



/**
@see Array
*/
template<typename T, int CAPACITY>
class Array_BufferPolicy_ConstCount {
protected:

	inline Array_BufferPolicy_ConstCount(int newCount, int newCapacity)
	{
		BL_ASSERT(newCount == CAPACITY && newCapacity == CAPACITY);
	}

	inline int getCount() const
	{
		return CAPACITY;
	}

	inline void setCount(int newCount)
	{
		BL_ASSERT_NEVER_REACHED
	}

	inline bool canSetCount() const
	{
		return false;
	}

	inline int getCapacity() const
	{
		return CAPACITY;
	}

	inline bool setCapacity(int newCapacity)
	{
		BL_ASSERT_NEVER_REACHED
		return false;
	}

	inline bool canSetCapacity() const
	{
		return false;
	}

protected:

	T buffer[CAPACITY];
};


/*
template<class T, int CAPACITY>
class ScopedFixedLengthArrayImplementation : public FixedLengthArrayImplementation<T, CAPACITY> {
public:

	inline ScopedFixedLengthArrayImplementation(int newLength, int newCapacity)
		: FixedLengthArrayImplementation<T, CAPACITY>(newLength, newCapacity)
	{
		memset(buffer, 0, CAPACITY * sizeof(T));
	}

	inline ~ScopedFixedLengthArrayImplementation()
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



#endif // #ifndef BaseLib_Containers_Array_BufferPolicy_ConstCount_h