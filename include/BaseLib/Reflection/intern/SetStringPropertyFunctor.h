/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_SetStringPropertyFunctor_h
#define BaseLib_Reflection_SetStringPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractSetStringPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/StringProperty.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct SetStringPropertyFunctor : public AbstractSetStringPropertyFunctor {

    typedef void (T::*SetPropertyFunc)(const BaseLib::Strings::String& propertyValue);
    //typedef void (T::*SetArrayPropertyFunc)(const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    SetPropertyFunc const setPropertyFunc;
    //SetArrayPropertyFunc const setArrayPropertyFunc;
 

    SetStringPropertyFunctor<T>(StringProperty* forProperty, SetPropertyFunc setFunc)
		: AbstractSetStringPropertyFunctor(forProperty)
		, setPropertyFunc(setFunc)
		//, setArrayPropertyFunc(NULL)
    {
		BL_ASSERT(setPropertyFunc != NULL);
    }


	/*
    SetStringPropertyFunctor<T>(StringProperty* forProperty, SetArrayPropertyFunc setFunc)
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



    virtual void setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/)
    {
        if (propertyValue.getLength() < property->getMinimum())
        {
            BaseLib::ErrorHandling::argumentError(STRING_FOR_PROPERTY_TOO_SHORT(property->getName(), propertyValue.getLength(), property->getMinimum()));
			return;
        }
        else if (propertyValue.getLength() > property->getMaximum())
        {
            BaseLib::ErrorHandling::argumentError(STRING_FOR_PROPERTY_TOO_LONG(property->getName(), propertyValue.getLength(), property->getMaximum()));
			return;
        }

		//if (isArrayFunctor() == false)
		{
			BL_ASSERT(setPropertyFunc != NULL /*&& setArrayPropertyFunc == NULL && arrayIndex == 0*/);
			(static_cast<T*>(instance)->*setPropertyFunc)(propertyValue);
		}
		/*else
		{
			BL_ASSERT(setArrayPropertyFunc != NULL);
			(static_cast<T*>(instance)->*setArrayPropertyFunc)(propertyValue, arrayIndex);
		}*/
    }
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_SetStringPropertyFunctor_h
