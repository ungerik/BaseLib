/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractGetDoublePropertyFunctor_h
#define BaseLib_Reflection_AbstractGetDoublePropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractGetPropertyFunctor.h"



namespace BaseLib {
namespace Reflection {



struct BL_EXPORT AbstractGetDoublePropertyFunctor : public AbstractGetPropertyFunctor {

	DoubleProperty* property; 

	AbstractGetDoublePropertyFunctor(DoubleProperty* forProperty);

    virtual BaseLib::Strings::String getProperty(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual int getPropertyAsInt(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual bool getPropertyAsBool(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    virtual float getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_AbstractGetDoublePropertyFunctor_h
