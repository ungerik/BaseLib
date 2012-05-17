/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef Reflection_ArrayLengthFunctor_h
#define Reflection_ArrayLengthFunctor_h



//#include "BaseLib/Common.h"



namespace BaseLib {
namespace Reflection {


/*
struct BL_EXPORT AbstractArrayLengthFunctor {

	virtual ~AbstractArrayLengthFunctor();
	virtual bool isFixedArrayLength() const = 0;
	virtual int getArrayLength(const void* instance) const = 0;
	virtual void setArrayLength(void* instance, int newLength) = 0;

};



struct BL_EXPORT FixedArrayLengthFunctor : public AbstractArrayLengthFunctor {

	static FixedArrayLengthFunctor one;

	const int arrayLength;

	FixedArrayLengthFunctor(int newArrayLength);

	virtual bool isFixedArrayLength() const;
	virtual int getArrayLength(const void* instance) const;
	virtual void setArrayLength(void* instance, int newLength);

};



template<class T>
struct ArrayLengthFunctor : public AbstractArrayLengthFunctor {

    typedef int (T::*GetArrayLengthFunc)() const;
    typedef void (T::*SetArrayLengthFunc)(int newSize);
	GetArrayLengthFunc const getArrayLengthFunc;
	SetArrayLengthFunc const setArrayLengthFunc;


	ArrayLengthFunctor<T>(GetArrayLengthFunc getLengthFunc, SetArrayLengthFunc setLengthFunc)
	  : getArrayLengthFunc(getLengthFunc)
	  , setArrayLengthFunc(setLengthFunc)
	{
		BL_ASSERT(getArrayLengthFunc != NULL);
	}



	virtual bool isFixedArrayLength() const
	{
		return setArrayLengthFunc == NULL;
	}



	virtual int getArrayLength(const void* instance) const
	{
		if (checkArgumentNotNull(instance) == true && checkStateNotNull(getArrayLengthFunc) == true)
		{
			return (static_cast<const T*>(instance)->*getArrayLengthFunc)();
		}
		else
		{
			return -1;
		}
	}



	virtual void setArrayLength(void* instance, int newLength)
	{
		if (isFixedArrayLength() == false)
		{
			if (checkArgumentNotNull(instance) == true)
			{
				(static_cast<T*>(instance)->*setArrayLengthFunc)(newSize);
			}
		}
		else
		{
			stateError(ARRAY_LENGTH_IS_READ_ONLY);
		}
	}

};
*/


} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef Reflection_ArrayLengthFunctor_h