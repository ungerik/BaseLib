/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Array_BufferPolicy_Dynamic_h
#define BaseLib_Containers_Array_BufferPolicy_Dynamic_h



#include "BaseLib/Common.h"
#include "BaseLib/Math/Common.h"



namespace BaseLib {
namespace Containers {



using BaseLib::Math::max;



/**
@see Array
*/
template<typename T, int CAPACITY> // CAPACITY is unused, only for compatibility with other policies
class Array_BufferPolicy_Dynamic {
protected:

	inline Array_BufferPolicy_Dynamic(int newCount, int newCapacity)
		: capacity(newCapacity)
		, count(newCount)
		, buffer(NULL)
	{
		BL_ASSERT(newCount >= 0 && newCount <= newCapacity);
		BL_ASSERT(newCapacity >= 0);
		if (newCapacity > 0)
		{
			buffer = static_cast<T *>(malloc(newCapacity*sizeof(T)));
			if (BaseLib::TypeTraits::IsValueType<T>::VALUE == false)
			{
				construct(0, count);
			}
		}
	}

	inline ~Array_BufferPolicy_Dynamic()
	{
		if (BaseLib::TypeTraits::IsValueType<T>::VALUE == false)
		{
			destruct(0, count);
		}
		free(buffer);
	}

	inline int getCount() const
	{
		return count;
	}

	inline void setCount(int newCount)
	{
		BL_ASSERT(newCount >= 0);
		if (newCount != count)
		{
			if (newCount > capacity)
			{
				setCapacity(max(newCount, capacity * 2));
			}
			
			if (BaseLib::TypeTraits::IsValueType<T>::VALUE == false)
			{
				if (newCount > count)
				{
					construct(count, newCount);
				}
				else
				{
					destruct(newCount, count);
				}
			}

			count = newCount;
		}
	}

	inline bool canSetCount() const
	{
		return true;
	}

	inline int getCapacity() const
	{
		return capacity;
	}

	inline bool setCapacity(int newCapacity)
	{
		BL_ASSERT(newCapacity >= 0);
		if (newCapacity != capacity)
		{
			if (newCapacity < count)
			{
				setCount(newCapacity);
			}
			capacity = newCapacity;
			T * oldBuffer = buffer;
			buffer = static_cast<T *>(realloc(buffer, capacity*sizeof(T)));
			return buffer != oldBuffer;
		}
		else
		{
			return false;
		}
	}

	inline bool canSetCapacity() const
	{
		return true;
	}

protected:

	int count;
	int capacity;
	T * buffer;

	void construct(int begin, int end)
	{
		int i;
		try
		{
			for (i = begin; i < end; ++i)
			{
				new(&buffer[i]) T();
			}
		}
		catch (...)
		{
			destruct(0, i);
			throw;
		}
	}

	void destruct(int begin, int end)
	{
		for (int i = begin; i < end; ++i)
		{
			(&buffer[i])->~T();
		}
	}
};


/*
template<class T>
class ScopedDynamicArrayImplementation : public DynamicArrayImplementation<T> {
public:

	inline ScopedDynamicArrayImplementation(int newCount, int newCapacity)
  		: DynamicArrayImplementation<T>(newCount, newCapacity)
	{
	}

	inline ~ScopedDynamicArrayImplementation()
	{
	}

};
*/

} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Array_BufferPolicy_Dynamic_h