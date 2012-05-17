/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetIntPropertyFunctor_h
#define BaseLib_Reflection_GetIntPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetIntPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/IntProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct GetIntPropertyFunctor : public AbstractGetIntPropertyFunctor {

    typedef int (T::*GetPropertyFunc)() const;
    //typedef int (T::*GetArrayPropertyFunc)(int arrayIndex) const;
    GetPropertyFunc const getPropertyFunc;
    //GetArrayPropertyFunc const getArrayPropertyFunc;
 

    GetIntPropertyFunctor<T>(IntProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetIntPropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


/*
    GetIntPropertyFunctor<T>(IntProperty* forProperty, GetArrayPropertyFunc getFunc)
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


    virtual int getPropertyAsInt(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const
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



#endif // #ifndef BaseLib_Reflection_GetIntPropertyFunctor_h
