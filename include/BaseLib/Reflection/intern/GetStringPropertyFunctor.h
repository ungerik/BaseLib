/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetStringPropertyFunctor_h
#define BaseLib_Reflection_GetStringPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetStringPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/StringProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct GetStringPropertyFunctor : public AbstractGetStringPropertyFunctor {

    typedef BaseLib::Strings::String (T::*GetPropertyFunc)() const;
    //typedef BaseLib::Strings::String (T::*GetArrayPropertyFunc)(int arrayIndex) const;
    GetPropertyFunc const getPropertyFunc;
    //GetArrayPropertyFunc const getArrayPropertyFunc;
 

    GetStringPropertyFunctor<T>(StringProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetStringPropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


/*
    GetStringPropertyFunctor<T>(StringProperty* forProperty, GetArrayPropertyFunc getFunc)
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


    virtual BaseLib::Strings::String getProperty(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const
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



#endif // #ifndef BaseLib_Reflection_GetStringPropertyFunctor_h
