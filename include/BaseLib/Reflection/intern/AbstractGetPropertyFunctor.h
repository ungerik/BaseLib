/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractGetPropertyFunctor_h
#define BaseLib_Reflection_AbstractGetPropertyFunctor_h



//#include "BaseLib/Common.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Strings::NumberFormat;



struct BL_EXPORT AbstractGetPropertyFunctor {

    virtual ~AbstractGetPropertyFunctor();

    virtual BaseLib::Strings::String getProperty(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const = 0;
    virtual int getPropertyAsInt(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const = 0;
    virtual bool getPropertyAsBool(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const = 0;
    virtual float getPropertyAsFloat(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const = 0;
    virtual double getPropertyAsDouble(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const = 0;

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_AbstractGetPropertpyFunctor_h