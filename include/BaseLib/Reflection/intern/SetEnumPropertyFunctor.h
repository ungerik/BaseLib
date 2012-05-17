/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_SetEnumPropertyFunctor_h
#define BaseLib_Reflection_SetEnumPropertyFunctor_h


//#include "BaseLib/Reflection/intern/AbstractSetEnumPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/EnumProperty.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Array;



template<class T, typename EnumType>
struct SetEnumPropertyFunctor : public AbstractSetEnumPropertyFunctor {

    typedef void (T::*SetPropertyFunc)(EnumType propertyValue);
    //typedef void (T::*SetArrayPropertyFunc)(EnumType propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    SetPropertyFunc const setPropertyFunc;
    //SetArrayPropertyFunc const setArrayPropertyFunc;
 


    SetEnumPropertyFunctor<T, EnumType>(EnumProperty* forProperty, SetPropertyFunc setFunc)
		: AbstractSetEnumPropertyFunctor(forProperty)
		, setPropertyFunc(setFunc)
		//, setArrayPropertyFunc(NULL)
    {
		BL_ASSERT(setPropertyFunc != NULL);
    }


/*
    SetEnumPropertyFunctor<T, EnumType>(EnumProperty* forProperty, SetArrayPropertyFunc setFunc)
      : property(forProperty)
	  , setPropertyFunc(NULL)
      , setArrayPropertyFunc(setFunc)
    {
		BL_ASSERT(setArrayPropertyFunc != NULL);
    }



	inline bool isArrayFunctor() const
	{
		return setArrayPropertyFunc != NULL;
	}
*/


	virtual void setPropertyAsIntUnchecked(void* instance, int propertyValue)
	{
		//if (isArrayFunctor() == false)
		{
			BL_ASSERT(setPropertyFunc != NULL /*&& setArrayPropertyFunc == NULL && arrayIndex == 0*/);
	        (static_cast<T*>(instance)->*setPropertyFunc)(static_cast<EnumType>(propertyValue));
		}
		/*else
		{
			BL_ASSERT(setArrayPropertyFunc != NULL && setPropertyFunc == NULL);
			(static_cast<T*>(instance)->*setArrayPropertyFunc)(static_cast<EnumType>(propertyValue), arrayIndex);
		}*/
	}
};



} // namespace Reflection
} // namespace BaseLib






#endif // #ifndef BaseLib_Reflection_SetEnumPropertyFunctor_h
