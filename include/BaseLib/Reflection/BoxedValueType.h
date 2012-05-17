/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_BoxedValueType_h
#define BaseLib_Reflection_BoxedValueType_h



//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Strings::String;



class BL_EXPORT BoxedValueType : public Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Reflection::BoxedValueType);

	bool isDefaultValue() const;
	void setValueToDefault();

	String getType() const;

    inline BaseLib::Strings::String getValueAsString() const
	{
		return getProperty("value");
	}

    inline int getValueAsInt() const
	{
		return getPropertyAsInt("value");
	}

    inline bool getValueAsBool() const
	{
		return getPropertyAsBool("value");
	}

    inline float getValueAsFloat() const
	{
		return getPropertyAsFloat("value");
	}

    inline double getValueAsDouble() const
	{
		return getPropertyAsDouble("value");
	}

	virtual void setValue(const String& newValue)
	{
		setProperty("value", newValue);
	}

    virtual void setValue(int newValue)
	{
		setProperty("value", newValue);
	}

    virtual void setValue(bool newValue)
	{
		setProperty("value", newValue);
	}

    virtual void setValue(float newValue)
	{
		setProperty("value", newValue);
	}

    virtual void setValue(double newValue)
	{
		setProperty("value", newValue);
	}

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_BoxedValueType_h