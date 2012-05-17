/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetEnumPropertyFunctor_h
#define BaseLib_Reflection_GetEnumPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetEnumPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/EnumProperty.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Array;



template<class T, typename EnumType>
struct GetEnumPropertyFunctor : public AbstractGetEnumPropertyFunctor {

    typedef EnumType (T::*GetPropertyFunc)() const;
    //typedef EnumType (T::*GetArrayPropertyFunc)(int arrayIndex) const;
    GetPropertyFunc const getPropertyFunc;
    //GetArrayPropertyFunc const getArrayPropertyFunc;
 

    GetEnumPropertyFunctor<T, EnumType>(EnumProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetEnumPropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


/*
    GetEnumPropertyFunctor<T, EnumType>(EnumProperty* forProperty, GetArrayPropertyFunc getFunc)
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






#endif // #ifndef BaseLib_Reflection_GetEnumPropertyFunctor_h
