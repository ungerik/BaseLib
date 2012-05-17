/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_GetBoolPropertyFunctor_h
#define BaseLib_Reflection_GetBoolPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetBoolPropertyFunctor.h"



namespace BaseLib {
namespace Reflection {



template<class T>
struct GetBoolPropertyFunctor : public AbstractGetBoolPropertyFunctor {

    typedef bool (T::*GetPropertyFunc)() const;
    //typedef bool (T::*GetArrayPropertyFunc)(int arrayIndex) const;
	GetPropertyFunc const getPropertyFunc;
	//GetArrayPropertyFunc const getArrayPropertyFunc;



    GetBoolPropertyFunctor<T>(BoolProperty* forProperty, GetPropertyFunc getFunc)
		: AbstractGetBoolPropertyFunctor(forProperty)
		, getPropertyFunc(getFunc)
      //, getArrayPropertyFunc(NULL)
    {
		BL_ASSERT(getPropertyFunc != NULL);
    }


    virtual bool getPropertyAsBool(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const
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



#endif // #ifndef BaseLib_Reflection_GetBoolPropertyFunctor_h
