/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_SetIntPropertyFunctor_h
#define BaseLib_Reflection_SetIntPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractSetIntPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/IntProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct SetIntPropertyFunctor : public AbstractSetIntPropertyFunctor {

    typedef void (T::*SetPropertyFunc)(int propertyValue);
    //typedef void (T::*SetArrayPropertyFunc)(int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    SetPropertyFunc const setPropertyFunc;
    //SetArrayPropertyFunc const setArrayPropertyFunc;
 


    SetIntPropertyFunctor<T>(IntProperty* forProperty, SetPropertyFunc setFunc)
		: AbstractSetIntPropertyFunctor(forProperty)
		, setPropertyFunc(setFunc)
		//, setArrayPropertyFunc(NULL)
    {
		BL_ASSERT(setPropertyFunc != NULL);
    }


/*
    SetIntPropertyFunctor<T>(IntProperty* forProperty, SetArrayPropertyFunc setFunc)
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


    virtual void setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/)
    {
        if (propertyValue < property->getMinimum())
        {
			BaseLib::ErrorHandling::argumentError(VALUE_FOR_PROPERTY_SMALLER_THAN_MINIUM(property->getName(), propertyValue, property->getMinimum()));
			return;
        }
        else if (propertyValue > property->getMaximum())
        {
            BaseLib::ErrorHandling::argumentError(VALUE_FOR_PROPERTY_GREATER_THAN_MINIUM(property->getName(), propertyValue, property->getMaximum()));
			return;
        }

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



#endif // #ifndef BaseLib_Reflection_SetIntPropertyFunctor_h
