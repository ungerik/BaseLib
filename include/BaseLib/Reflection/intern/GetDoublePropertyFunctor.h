/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetDoublePropertyFunctor_h
#define BaseLib_Reflection_GetDoublePropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetDoublePropertyFunctor.h"
//#include "BaseLib/Reflection/intern/DoubleProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct GetDoublePropertyFunctor : public AbstractGetDoublePropertyFunctor {

	typedef double (T::*GetPropertyFunc)() const;
    //typedef double (T::*GetArrayPropertyFunc)(int arrayIndex) const;
    GetPropertyFunc const getPropertyFunc;
    //GetArrayPropertyFunc const getArrayPropertyFunc;
 

    GetDoublePropertyFunctor<T>(DoubleProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetDoublePropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


/*
    GetDoublePropertyFunctor<T>(DoubleProperty* forProperty, GetArrayPropertyFunc getFunc)
      : property(forProperty)
	  , getPropertyFunc(NULL)
      , getArrayPropertyFunc(getFunc)
    {
		BL_ASSERT(getArrayPropertyFunc != NULL);
    }



	inline bool isArrayFunctor() const
	{
		return getArrayPropertyFunc != NULL;
	}
*/


    virtual double getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const
    {
		//if (isArrayFunctor() == false)
		{
			BL_ASSERT(getPropertyFunc != NULL /*&& getArrayPropertyFunc == NULL && arrayIndex == 0*/);
	        return (static_cast<const T*>(instance)->*getPropertyFunc)();
		}
		/*else
		{
			BL_ASSERT(getArrayPropertyFunc != NULL && getPropertyFunc == NULL);
	        return (static_cast<const T*>(instance)->*getArrayPropertyFunc)(arrayIndex);
		}*/
    }

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_GetDoublePropertyFunctor_h
