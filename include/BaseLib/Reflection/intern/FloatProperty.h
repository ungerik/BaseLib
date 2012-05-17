/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_FloatProperty_h
#define BaseLib_Reflection_FloatProperty_h



//#include "BaseLib/Reflection/Property.h"
//#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
class Object;



class BL_EXPORT FloatProperty : public Property {
public:

	typedef ConstMethodFunctor0<Object, float> GetDefaultFunc;

	FloatProperty(const BaseLib::Strings::String& propertyName, float newDefaultValue = 0.0f, GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	void setValueRange(float newMinimum, float newMaximum);

	inline float getMinimum() const
	{
		return minimum;
	}

	inline float getMaximum() const
	{
		return maximum;
	}

	virtual bool isDefault(const void* instance) const;
	virtual void setToDefault(void* instance);

	float getDefault(const void* instance) const;
	void setDefault(float newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

protected:

    float minimum;
    float maximum;
	ValueRangeEnumeration<FloatProperty> valueRangeEnumeration;
	float defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;

};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_FloatProperty_h