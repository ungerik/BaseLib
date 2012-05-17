/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractSetStringPropertyFunctor_h
#define BaseLib_Reflection_AbstractSetStringPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractSetPropertyFunctor.h"



namespace BaseLib {
namespace Reflection {



struct BL_EXPORT AbstractSetStringPropertyFunctor : public AbstractSetPropertyFunctor {

	StringProperty* property;

	AbstractSetStringPropertyFunctor(StringProperty* forProperty);

    virtual void setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_AbstractSetStringPropertyFunctor_h
