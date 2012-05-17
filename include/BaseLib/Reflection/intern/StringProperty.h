/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_StringProperty_h
#define BaseLib_Reflection_StringProperty_h



//#include "BaseLib/Reflection/Property.h"
//#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
class Object;



class BL_EXPORT StringProperty : public Property {
public:

	typedef ConstMethodFunctor0<Object, BaseLib::Strings::String> GetDefaultFunc;

	StringProperty(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& newDefaultValue = Empty(), GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	void setValueRange(int newMinimum, int newMaximum);

	inline int getMinimum() const
	{
		return minimumLength;
	}

	inline int getMaximum() const
	{
		return maximumLength;
	}

	virtual bool isDefault(const void* instance) const;
	virtual void setToDefault(void* instance);

	BaseLib::Strings::String getDefault(const void* instance) const;
	void setDefault(const BaseLib::Strings::String& newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

protected:

    int minimumLength;
    int maximumLength;
	ValueRangeEnumeration<StringProperty> valueRangeEnumeration;
	BaseLib::Strings::String defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;

};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_StringProperty_h