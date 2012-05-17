/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_SetBoolPropertyFunctor_h
#define BaseLib_Reflection_SetBoolPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractSetBoolPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/BoolProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct SetBoolPropertyFunctor : public AbstractSetBoolPropertyFunctor {

    typedef void (T::*SetPropertyFunc)(bool propertyValue);
    //typedef void (T::*SetArrayPropertyFunc)(bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    SetPropertyFunc const setPropertyFunc;
    //SetArrayPropertyFunc const setArrayPropertyFunc;
 


    SetBoolPropertyFunctor<T>(BoolProperty* forProperty, SetPropertyFunc setFunc)
		: AbstractSetBoolPropertyFunctor(forProperty)
		, setPropertyFunc(setFunc)
      //, setArrayPropertyFunc(NULL)
    {
		BL_ASSERT(setPropertyFunc != NULL);
    }


/*
    SetBoolPropertyFunctor<T>(BoolProperty* forProperty, SetArrayPropertyFunc setFunc)
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


    virtual void setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/)
    {
		//if (isArrayFunctor() == false)
		{
			BL_ASSERT(setPropertyFunc != NULL /*&& setArrayPropertyFunc == NULL && arrayIndex == 0*/);
	        (static_cast<T*>(instance)->*setPropertyFunc)(propertyValue);
		}
		/*else
		{
			BL_ASSERT(setArrayPropertyFunc != NULL && setPropertyFunc == NULL);
			(static_cast<T*>(instance)->*setArrayPropertyFunc)(propertyValue, arrayIndex);
		}*/
    }
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_SetBoolPropertyFunctor_h
