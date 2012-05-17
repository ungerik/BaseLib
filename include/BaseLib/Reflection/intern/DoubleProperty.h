/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_DoubleProperty_h
#define BaseLib_Reflection_DoubleProperty_h



//#include "BaseLib/Reflection/Property.h"
//#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
class Object;



class BL_EXPORT DoubleProperty : public Property {
public:

	typedef ConstMethodFunctor0<Object, double> GetDefaultFunc;

	DoubleProperty(const BaseLib::Strings::String& propertyName, double newDefaultValue = 0.0, GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	void setValueRange(double newMinimum, double newMaximum);

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

	double getDefault(const void* instance) const;
	void setDefault(double newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

protected:

    double minimum;
    double maximum;
	ValueRangeEnumeration<DoubleProperty> valueRangeEnumeration;
	double defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;

};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_DoubleProperty_h