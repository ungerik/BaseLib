/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_EnumProperty_h
#define BaseLib_Reflection_EnumProperty_h



//#include "BaseLib/Reflection/Property.h"
//#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"
//#include "BaseLib/Containers/StringMap.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::StringMap;
using BaseLib::Containers::Enumeration;
class Object;



class BL_EXPORT EnumProperty : public Property {
public:

	typedef StringMap<int> Enums;
	typedef ConstMethodFunctor0<Object, int> GetDefaultFunc;

	EnumProperty(const BaseLib::Strings::String& propertyName, int newDefaultValue = 0, GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	void addEnum(int enumValue, const BaseLib::Strings::String& enumName);

	inline const Enums& getEnums() const
	{
		return enums;
	}

	virtual bool isDefault(const void* instance) const;
	virtual void setToDefault(void* instance);

	int getDefault(const void* instance) const;
	void setDefault(int newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

protected:

	Enums enums;
	Enums::KeyEnumeration valueRangeEnumeration;
	int defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;

};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_EnumProperty_h