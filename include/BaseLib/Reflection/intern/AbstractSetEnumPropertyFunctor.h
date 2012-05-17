/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_AbstractSetEnumPropertyFunctor_h
#define BaseLib_Reflection_AbstractSetEnumPropertyFunctor_h



//#include "BaseLib/Reflection/intern/AbstractSetPropertyFunctor.h"



namespace BaseLib {
namespace Reflection {




struct BL_EXPORT AbstractSetEnumPropertyFunctor : public AbstractSetPropertyFunctor {

	EnumProperty* property;

	AbstractSetEnumPropertyFunctor(EnumProperty* forProperty);

    virtual void setProperty(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsInt(void* instance, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsBool(void* instance, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsFloat(void* instance, float propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    virtual void setPropertyAsDouble(void* instance, double propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);

    virtual void setPropertyAsIntUnchecked(void* instance, int propertyValue) = 0;

};



} // namespace Reflection
} // namespace BaseLib






#endif // #ifndef BaseLib_Reflection_AbstractSetEnumPropertyFunctor_h
