/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractSetPropertyFunctor_h
#define BaseLib_Reflection_AbstractSetPropertyFunctor_h



//#include "BaseLib/Common.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Strings::NumberFormat;



struct BL_EXPORT AbstractSetPropertyFunctor {

    virtual ~AbstractSetPropertyFunctor();
    
    virtual void setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) = 0;
    virtual void setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) = 0;
    virtual void setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) = 0;
    virtual void setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) = 0;
    virtual void setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) = 0;
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_AbstractSetPropertpyFunctor_h