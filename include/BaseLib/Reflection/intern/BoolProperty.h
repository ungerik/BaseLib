/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_BoolProperty_h
#define BaseLib_Reflection_BoolProperty_h



//#include "BaseLib/Reflection/Property.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
using BaseLib::Utilities::AutoPointer;
class Object;



class BL_EXPORT BoolProperty : public Property {
public:

	typedef ConstMethodFunctor0<Object, bool> GetDefaultFunc;

	BoolProperty(const BaseLib::Strings::String& propertyName, bool newDefaultValue = false, GetDefaultFunc* newGetDefaultFunc = NULL);

	virtual Type getType() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;

	virtual bool isDefault(const void* instance) const;
	virtual void setToDefault(void* instance);

	bool getDefault(const void* instance) const;
	void setDefault(bool newDefaultValue);
	void setDefault(GetDefaultFunc* newGetDefaultFunc);

private:

	bool defaultValue;
	AutoPointer<GetDefaultFunc> getDefaultFunc;
};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_BoolProperty_h
