/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Object_h
#define BaseLib_Reflection_Object_h



#include "BaseLib/Reflection/Class.h"



namespace BaseLib {
namespace Reflection {



class BL_EXPORT Object {
public:

	static const BaseLib::Strings::String NON_SERIALIZEABLE;

	virtual ~Object();
	virtual Class* getClass() = 0;
	virtual const Class* getClass() const = 0;

	virtual bool hasMetaTag(const BaseLib::Strings::String& metaTag) const;
	virtual bool hasPropertyMetaTag(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& metaTag) const;

	virtual void onBeforePropertiesTransaction();
	virtual void onAfterPropertiesTransaction();

	virtual bool isPropertyDefault(const BaseLib::Strings::String& propertyName) const;
	virtual void setPropertyToDefault(const BaseLib::Strings::String& propertyName);
	virtual const Enumeration<BaseLib::Strings::String>& getPropertyValueRange(const BaseLib::Strings::String& propertyName) const;

	inline bool isPropertyReadable(const BaseLib::Strings::String& propertyName) const
	{
		return getClass()->property(propertyName)->isReadable();
	}

	inline bool isPropertyWriteable(const BaseLib::Strings::String& propertyName) const
	{
		return getClass()->property(propertyName)->isWriteable();
	}

	/*
    inline int getPropertyArrayLength(const BaseLib::Strings::String& propertyName) const
	{
		return getClass()->property(propertyName)->getArrayLength(this);
	}
    
	inline void setPropertyArrayLength(const BaseLib::Strings::String& propertyName, int newArrayLength)
	{
		getClass()->property(propertyName)->setArrayLength(this, newArrayLength);
	}
	*/

    inline BaseLib::Strings::String getProperty(const BaseLib::Strings::String& propertyName, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/) const
	{
		return getClass()->property(propertyName)->get(this, numberFormat/*, arrayIndex*/);
	}

    inline int getPropertyAsInt(const BaseLib::Strings::String& propertyName, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/) const
	{
		return getClass()->property(propertyName)->getAsInt(this, numberFormat/*, arrayIndex*/);
	}

    inline bool getPropertyAsBool(const BaseLib::Strings::String& propertyName, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/) const
	{
		return getClass()->property(propertyName)->getAsBool(this, numberFormat/*, arrayIndex*/);
	}

    inline float getPropertyAsFloat(const BaseLib::Strings::String& propertyName, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/) const
	{
		return getClass()->property(propertyName)->getAsFloat(this, numberFormat/*, arrayIndex*/);
	}

    inline double getPropertyAsDouble(const BaseLib::Strings::String& propertyName, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/) const
	{
		return getClass()->property(propertyName)->getAsDouble(this, numberFormat/*, arrayIndex*/);
	}

	inline void setProperty(const BaseLib::Strings::String& propertyName, const char8 * propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		setProperty(propertyName, BaseLib::Strings::String(propertyValue), numberFormat/*, arrayIndex*/);
	}

	inline void setProperty(const BaseLib::Strings::String& propertyName, const char16 * propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		setProperty(propertyName, BaseLib::Strings::String(propertyValue), numberFormat/*, arrayIndex*/);
	}

	inline void setProperty(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		getClass()->property(propertyName)->set(this, propertyValue, numberFormat/*, arrayIndex*/);
	}

    inline void setProperty(const BaseLib::Strings::String& propertyName, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		getClass()->property(propertyName)->set(this, propertyValue, numberFormat/*, arrayIndex*/);
	}

    inline void setProperty(const BaseLib::Strings::String& propertyName, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		getClass()->property(propertyName)->set(this, propertyValue, numberFormat/*, arrayIndex*/);
	}

    inline void setProperty(const BaseLib::Strings::String& propertyName, float propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		getClass()->property(propertyName)->set(this, propertyValue, numberFormat/*, arrayIndex*/);
	}

    inline void setProperty(const BaseLib::Strings::String& propertyName, double propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex = 0*/)
	{
		getClass()->property(propertyName)->set(this, propertyValue, numberFormat/*, arrayIndex*/);
	}

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_Object_h