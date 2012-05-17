/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetFloatPropertyFunctor_h
#define BaseLib_Reflection_GetFloatPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetFloatPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/FloatProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct GetFloatPropertyFunctor : public AbstractGetFloatPropertyFunctor {

    typedef float (T::*GetPropertyFunc)() const;
    //typedef float (T::*GetArrayPropertyFunc)(int arrayIndex) const;
    GetPropertyFunc const getPropertyFunc;
    //GetArrayPropertyFunc const getArrayPropertyFunc;
 

    GetFloatPropertyFunctor<T>(FloatProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetFloatPropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


/*
    GetFloatPropertyFunctor<T>(FloatProperty* forProperty, GetArrayPropertyFunc getFunc)
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


    virtual float getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const
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



#endif // #ifndef BaseLib_Reflection_GetFloatPropertyFunctor_h
