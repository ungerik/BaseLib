/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_IntProperty_h
#define BaseLib_Reflection_IntProperty_h



//#include "BaseLib/Reflection/Property.h"
//#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
class Object;



class BL_EXPORT IntProperty : public Property {
public:

	typedef ConstMethodFunctor0<Object, int> GetDefaultFunc;

	IntProperty(const BaseLib::Strings::String& propertyName, int newDefaultValue = 0, GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	void setValueRange(int newMinimum, int newMaximum);

	inline double getMinimum() const
	{
		return minimum;
	}

	inline double getMaximum() const
	{
		return maximum;
	}

	virtual bool isDefault(const void* instance) const;
	virtual void setToDefault(void* instance);

	int getDefault(const void* instance) const;
	void setDefault(int newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

protected:

    int minimum;
    int maximum;
	ValueRangeEnumeration<IntProperty> valueRangeEnumeration;
	int defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;

};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_IntProperty_h