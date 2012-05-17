/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractGetBoolPropertyFunctor_h
#define BaseLib_Reflection_AbstractGetBoolPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetPropertyFunctor.h"



namespace BaseLib {
namespace Reflection {



struct BL_EXPORT AbstractGetBoolPropertyFunctor : public AbstractGetPropertyFunctor {

	BoolProperty* property;

	AbstractGetBoolPropertyFunctor(BoolProperty* forProperty);

    virtual BaseLib::Strings::String getProperty(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual int getPropertyAsInt(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual float getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual double getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_AbstractGetBoolPropertyFunctor_h
