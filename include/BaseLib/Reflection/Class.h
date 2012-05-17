/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Class_h
#define BaseLib_Reflection_Class_h



namespace BaseLib {
	namespace Strings {
		//class String;
		class NumberFormat;
	}
}



//namespace BaseLib {
//	namespace Containers {
//		template<class T> class StringMap;
//	}
//}



#include <set>
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Functors/Functor1.h"
#include "BaseLib/Containers/Enumeration.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/intern/Errors.h"
#include "BaseLib/Reflection/intern/AbstractGetPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetPropertyFunctor.h"
#include "BaseLib/Reflection/intern/ValueRangeEnumeration.h"
#include "BaseLib/Reflection/Property.h"
#include "BaseLib/Reflection/intern/BoolProperty.h"
#include "BaseLib/Reflection/intern/IntProperty.h"
#include "BaseLib/Reflection/intern/FloatProperty.h"
#include "BaseLib/Reflection/intern/DoubleProperty.h"
#include "BaseLib/Reflection/intern/StringProperty.h"
#include "BaseLib/Reflection/intern/EnumProperty.h"
#include "BaseLib/Reflection/intern/AbstractGetStringPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractGetIntPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractGetBoolPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractGetEnumPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractGetFloatPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractGetDoublePropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetStringPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetIntPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetBoolPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetEnumPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetFloatPropertyFunctor.h"
#include "BaseLib/Reflection/intern/AbstractSetDoublePropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetStringPropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetIntPropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetBoolPropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetEnumPropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetFloatPropertyFunctor.h"
#include "BaseLib/Reflection/intern/GetDoublePropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetStringPropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetIntPropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetBoolPropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetEnumPropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetFloatPropertyFunctor.h"
#include "BaseLib/Reflection/intern/SetDoublePropertyFunctor.h"



namespace BaseLib {
namespace Reflection {



//#ifndef DEFAULT_MAX_STRINGPROPERTY_LENGTH
//    #define DEFAULT_MAX_STRINGPROPERTY_LENGTH INT_MAX
//#endif



#ifndef BL_REFLECTION_CLASS_EXPORT
	#define BL_REFLECTION_CLASS_EXPORT
#endif



#define BL_DECLARE_REFLECTION_BASE_CLASS(C) \
	class BL_REFLECTION_CLASS_EXPORT Class : public ::BaseLib::Reflection::Class { \
	public: \
		typedef C ReflectedType; \
		Class(const ::BaseLib::Strings::String& name = #C, const ::BaseLib::Reflection::Class* parent = NULL); \
	}; \
	\
	static Class CLASS; \
	\
	virtual ::BaseLib::Reflection::Class* getClass(); \
	virtual const ::BaseLib::Reflection::Class* getClass() const; \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object* object) \
	{ \
		return (object != NULL && object->getClass() >= CLASS) ? static_cast<C*>(object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object* object) \
	{ \
		return (object != NULL && object->getClass() >= CLASS) ? static_cast<const C*>(object) : NULL; \
	} \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<C*>(&object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<const C*>(&object) : NULL; \
	}



#define BL_DECLARE_REFLECTION_CLASS(C, P) \
	class BL_REFLECTION_CLASS_EXPORT Class : public P::Class { \
	public: \
		typedef C ReflectedType; \
		Class(const ::BaseLib::Strings::String& name = #C, const ::BaseLib::Reflection::Class* parent = &P::CLASS); \
	}; \
	static Class CLASS; \
	\
	virtual ::BaseLib::Reflection::Class* getClass(); \
	virtual const ::BaseLib::Reflection::Class* getClass() const; \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<C*>(object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<const C*>(object) : NULL; \
	} \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<C*>(&object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<const C*>(&object) : NULL; \
	}



#define BL_DEFINE_REFLECTION_BASE_CLASS(C) \
	C::Class C::CLASS; \
	\
	::BaseLib::Reflection::Class* C::getClass() { return &CLASS; } \
	const ::BaseLib::Reflection::Class* C::getClass() const { return &CLASS; } \
	\
	C::Class::Class(const ::BaseLib::Strings::String& name, const ::BaseLib::Reflection::Class* parent) \
		: ::BaseLib::Reflection::Class(name, parent)



#define BL_DEFINE_REFLECTION_CLASS(C, P) \
	C::Class C::CLASS; \
	\
	::BaseLib::Reflection::Class* C::getClass() { return &CLASS; } \
	const ::BaseLib::Reflection::Class* C::getClass() const { return &CLASS; } \
	\
	C::Class::Class(const ::BaseLib::Strings::String& name, const ::BaseLib::Reflection::Class* parent) \
		: P::Class(name, parent)



// For classes in BaseLib with reflection:



#define BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(C) \
	class BL_EXPORT Class : public ::BaseLib::Reflection::Class { \
	public: \
		typedef C ReflectedType; \
		Class(const ::BaseLib::Strings::String& name = #C, const ::BaseLib::Reflection::Class* parent = NULL); \
	}; \
	\
	static Class CLASS; \
	\
	virtual ::BaseLib::Reflection::Class* getClass(); \
	virtual const ::BaseLib::Reflection::Class* getClass() const; \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<C*>(object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<const C*>(object) : NULL; \
	} \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<C*>(&object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<const C*>(&object) : NULL; \
	}



#define BL_DECLARE_REFLECTION_BASELIB_CLASS(C, P) \
	class BL_EXPORT Class : public P::Class { \
	public: \
		typedef C ReflectedType; \
		Class(const ::BaseLib::Strings::String& name = #C, const ::BaseLib::Reflection::Class* parent = &P::CLASS); \
	}; \
	\
	static Class CLASS; \
	\
	virtual ::BaseLib::Reflection::Class* getClass(); \
	virtual const ::BaseLib::Reflection::Class* getClass() const; \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<C*>(object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object* object) \
	{ \
		return object != NULL && *object->getClass() >= CLASS ? static_cast<const C*>(object) : NULL; \
	} \
	\
	inline static C* castFrom(::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<C*>(&object) : NULL; \
	} \
	inline static const C* castFrom(const ::BaseLib::Reflection::Object& object) \
	{ \
		return object.getClass() >= CLASS ? static_cast<const C*>(&object) : NULL; \
	}



using BaseLib::Containers::Enumeration;
using BaseLib::Containers::StringMap;
//using namespace BaseLib::ErrorHandling;



class Variant;
//template<typename T> class Convertable;



class BL_EXPORT Class : public NonCopyable {

	friend Variant;

public:

	static const BaseLib::Strings::String NON_SERIALIZEABLE;

	Class(const BaseLib::Strings::String& newName, const Class* newParent = NULL);
	virtual ~Class();

	inline const BaseLib::Strings::String& getName() const
	{
		return name;
	}

	BaseLib::Strings::String getNameWithoutNameSpace() const;
	BaseLib::Strings::String getNameSpace() const;

	inline const Class* getParent() const
	{
		return parent;
	}

	bool hasProperty(const BaseLib::Strings::String& propertyName) const;
	const Enumeration<BaseLib::Strings::String>& getPropertyNames() const;
	const Enumeration<Property*>& getProperties() const;
	Property* property(const BaseLib::Strings::String& propertyName);
	const Property* property(const BaseLib::Strings::String& propertyName) const;
	Property* getPropertyOrNull(const BaseLib::Strings::String& propertyName);
	const Property* getPropertyOrNull(const BaseLib::Strings::String& propertyName) const;

	inline bool hasMetaTag(const BaseLib::Strings::String& metaTag) const
	{
		return metaTags.find(metaTag) != metaTags.end();
	}

private:

	BaseLib::Strings::String name;
	const Class* parent;

	typedef StringMap<Property*> PropertyMap;
	PropertyMap propertyMap;
	mutable AutoPointer< Enumeration<Property*> > propertyEnumeration;
	mutable AutoPointer< Enumeration<BaseLib::Strings::String> > propertyNames;

	typedef std::set<BaseLib::Strings::String> MetaTags;
	MetaTags metaTags;

protected:

	void addProperty(Property* newProperty);

	StringProperty* Class::getOrCreateStringProperty(const BaseLib::Strings::String& propertyName);
	BoolProperty* Class::getOrCreateBoolProperty(const BaseLib::Strings::String& propertyName);
	IntProperty* Class::getOrCreateIntProperty(const BaseLib::Strings::String& propertyName);
	FloatProperty* Class::getOrCreateFloatProperty(const BaseLib::Strings::String& propertyName);
	DoubleProperty* Class::getOrCreateDoubleProperty(const BaseLib::Strings::String& propertyName);
	EnumProperty* Class::getOrCreateEnumProperty(const BaseLib::Strings::String& propertyName);

	void addPropertyMetaTag(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& metaTag);
	void removePropertyMetaTag(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& metaTag);

	void unregisterProperty(const BaseLib::Strings::String& propertyName);

	// --------------------------------
	// Factory:
	// --------------------------------


	#define registerAtFactoryWithName(factory, name) if (this == ReflectedType::CLASS) factory.addFunctor<ReflectedType>(name)

	#define registerAtFactoryWithoutNameSpace(factory) registerAtFactoryWithName(factory, getNameWithoutNameSpace())

	#define registerAtFactoryWithNameSpace(factory) registerAtFactoryWithName(factory, getName())

	// --------------------------------
	// StringProperty:
	// --------------------------------

    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, BaseLib::Strings::String (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(const BaseLib::Strings::String& propertyValue))
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setGetterFunctor(new GetStringPropertyFunctor<T>(stringProperty, getPropertyFunc));
			stringProperty->setSetterFunctor(new SetStringPropertyFunctor<T>(stringProperty, setPropertyFunc));
		}
	}

	// get string:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, BaseLib::Strings::String (T::*getPropertyFunc)() const)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setGetterFunctor(new GetStringPropertyFunctor<T>(stringProperty, getPropertyFunc));
		}
	}

	// set string:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(const BaseLib::Strings::String& propertyValue))
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setSetterFunctor(new SetStringPropertyFunctor<T>(stringProperty, setPropertyFunc));
		}
	}

    void registerPropertyLengthRange(const BaseLib::Strings::String& propertyName, int minLength, int maxLength)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setValueRange(minLength, maxLength);
		}
	}

    void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, const BaseLib::Strings::String& defaultValue)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setDefault(defaultValue);
		}
	}

	void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, StringProperty::GetDefaultFunc* getDefaultFunc)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setDefault(getDefaultFunc);
		}
	}

	// --------------------------------
	// IntProperty:
	// --------------------------------

	// get/set int:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, int (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(int propertyValue))
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setGetterFunctor(new GetIntPropertyFunctor<T>(intProperty, getPropertyFunc));
			intProperty->setSetterFunctor(new SetIntPropertyFunctor<T>(intProperty, setPropertyFunc));
		}
	}

	// get int:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, int (T::*getPropertyFunc)() const)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setGetterFunctor(new GetIntPropertyFunctor<T>(intProperty, getPropertyFunc));
		}
	}

	// set int:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(int propertyValue))
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setSetterFunctor(new SetIntPropertyFunctor<T>(intProperty, setPropertyFunc));
		}
	}

    void registerPropertyValueRange(const BaseLib::Strings::String& propertyName, int minValue, int maxValue)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setValueRange(minValue, maxValue);
		}
	}

    void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, int defaultValue)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setDefault(defaultValue);
		}
	}

	void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, IntProperty::GetDefaultFunc* getDefaultFunc)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setDefault(getDefaultFunc);
		}
	}

	// --------------------------------
	// BoolProperty:
	// --------------------------------

	// get/set bool:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, bool (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(bool propertyValue))
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setGetterFunctor(new GetBoolPropertyFunctor<T>(boolProperty, getPropertyFunc));
			boolProperty->setSetterFunctor(new SetBoolPropertyFunctor<T>(boolProperty, setPropertyFunc));
		}
	}

	// get bool:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, bool (T::*getPropertyFunc)() const)
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setGetterFunctor(new GetBoolPropertyFunctor<T>(boolProperty, getPropertyFunc));
		}
	}

	// set bool:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(bool propertyValue))
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setSetterFunctor(new SetBoolPropertyFunctor<T>(boolProperty, setPropertyFunc));
		}
	}

    void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, bool defaultValue)
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setDefault(defaultValue);
		}
	}

	void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, BoolProperty::GetDefaultFunc* getDefaultFunc)
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setDefault(getDefaultFunc);
		}
	}

	// --------------------------------
	// EnumProperty:
	// --------------------------------

	// get/set enum:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, E (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(E propertyValue))
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setGetterFunctor(new GetEnumPropertyFunctor<T, E>(enumProperty, getPropertyFunc));
			enumProperty->setSetterFunctor(new SetEnumPropertyFunctor<T, E>(enumProperty, setPropertyFunc));
		}
	}

	// get enum:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, E (T::*getPropertyFunc)() const)
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setGetterFunctor(new GetEnumPropertyFunctor<T, E>(enumProperty, getPropertyFunc));
		}
	}

	// set enum:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(E propertyValue))
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setSetterFunctor(new SetEnumPropertyFunctor<T, E>(enumProperty, setPropertyFunc));
		}
	}

    #define registerEnumPropertyValue(propertyName, enumValue) ( registerEnumPropertyValueAndName(propertyName, enumValue, #enumValue) )

    template<typename E>
    void registerEnumPropertyValueAndName(const BaseLib::Strings::String& propertyName, E enumValue, BaseLib::Strings::String enumName)
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			int pos = enumName.findLast("::");
			if (pos != BaseLib::Strings::String::END)
			{
				enumName = enumName.subString(pos+2);
			}
			enumProperty->addEnum(enumValue, enumName);
		}
	}

    void registerEnumPropertyDefaultValue(const BaseLib::Strings::String& propertyName, int defaultValue)
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setDefault(defaultValue);
		}
	}

    void registerEnumPropertyDefaultValue(const BaseLib::Strings::String& propertyName, EnumProperty::GetDefaultFunc* getDefaultFunc)
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setDefault(getDefaultFunc);
		}
	}

	// --------------------------------
	// FloatProperty:
	// --------------------------------

	// get/set float:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, float (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(float propertyValue))
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setGetterFunctor(new GetFloatPropertyFunctor<T>(floatProperty, getPropertyFunc));
			floatProperty->setSetterFunctor(new SetFloatPropertyFunctor<T>(floatProperty, setPropertyFunc));
		}
	}

	// get float:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, float (T::*getPropertyFunc)() const)
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setGetterFunctor(new GetFloatPropertyFunctor<T>(floatProperty, getPropertyFunc));
		}
	}

	// set float:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(float propertyValue))
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setSetterFunctor(new SetFloatPropertyFunctor<T>(floatProperty, setPropertyFunc));
		}
	}

    void registerPropertyValueRange(const BaseLib::Strings::String& propertyName, float minValue, float maxValue)
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setValueRange(minValue, maxValue);
		}
	}

    void registerProperty(const BaseLib::Strings::String& propertyName, float defaultValue)
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setDefault(defaultValue);
		}
	}

    void registerProperty(const BaseLib::Strings::String& propertyName, FloatProperty::GetDefaultFunc* getDefaultFunc)
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setDefault(getDefaultFunc);
		}
	}

    void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, float defaultValue)
	{
		FloatProperty* floatProperty = getOrCreateFloatProperty(propertyName);
		if (floatProperty != NULL)
		{
			floatProperty->setDefault(defaultValue);
		}
	}

	// --------------------------------
	// DoubleProperty:
	// --------------------------------

	// get/set double:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, double (T::*getPropertyFunc)() const, void (T::*setPropertyFunc)(double propertyValue))
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setGetterFunctor(new GetDoublePropertyFunctor<T>(doubleProperty, getPropertyFunc));
			doubleProperty->setSetterFunctor(new SetDoublePropertyFunctor<T>(doubleProperty, setPropertyFunc));
		}
	}

	// get double:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, double (T::*getPropertyFunc)() const)
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setGetterFunctor(new GetDoublePropertyFunctor<T>(doubleProperty, getPropertyFunc));
		}
	}

	// set double:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(double propertyValue))
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setSetterFunctor(new SetDoublePropertyFunctor<T>(doubleProperty, setPropertyFunc));
		}
	}

    void registerPropertyValueRange(const BaseLib::Strings::String& propertyName, double minValue, double maxValue)
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setValueRange(minValue, maxValue);
		}
	}

    void registerProperty(const BaseLib::Strings::String& propertyName, double defaultValue)
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setDefault(defaultValue);
		}
	}

    void registerProperty(const BaseLib::Strings::String& propertyName, DoubleProperty::GetDefaultFunc* getDefaultFunc)
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setDefault(getDefaultFunc);
		}
	}

    void registerPropertyDefaultValue(const BaseLib::Strings::String& propertyName, double defaultValue)
	{
		DoubleProperty* doubleProperty = getOrCreateDoubleProperty(propertyName);
		if (doubleProperty != NULL)
		{
			doubleProperty->setDefault(defaultValue);
		}
	}

};



struct ClassRef {

	const Class& ref;
	
	inline ClassRef(const Class* pointer)
		: ref(*pointer)
	{
	}

	inline ClassRef(const Class& reference)
		: ref(reference)
	{
	}

	inline operator const Class*() const
	{
		return &ref;
	}
};



inline bool operator ==(const ClassRef& left, const ClassRef& right)
{
	return &right.ref == &left.ref;
}



inline bool operator !=(const ClassRef& left, const ClassRef& right)
{
	return !(right == left);
}



inline bool operator <(const ClassRef& left, const ClassRef& right)
{
	if (left != right && right.ref.getParent() != NULL)
	{
		const Class* rightParent = right.ref.getParent();
		while (rightParent->getParent() != NULL && left.ref != rightParent)
		{
			rightParent = rightParent->getParent();
		}
		return &left.ref == rightParent;
	}
	else
	{
		return false;
	}
}



inline bool operator >(const ClassRef& left, const ClassRef& right)
{
	return right < left;
}



inline bool operator >=(const ClassRef& left, const ClassRef& right)
{
	return left == right || left > right;
}



inline bool operator <=(const ClassRef& left, const ClassRef& right)
{
	return left == right || left < right;
}



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_Class_h



	// --------------------------------
	// ArrayLength:
	// --------------------------------

	/*
    template<class T>
    void registerPropertyArrayLength(const BaseLib::Strings::String& propertyName, int (T::*getArrayLengthFunc)() const, void (T::*setArrayLengthFunc)(int newSize) = NULL)
	{
		Property* abstractProperty = property(propertyName);
		if (abstractProperty != NULL)
		{
			abstractProperty->setArrayFunctor(new ArrayLengthFunctor<T>(getArrayLengthFunc, setArrayLengthFunc));
		}
		else
		{
			argumentError(PROPERTY_NOT_FOUND(propertyName));
		}
	}
	
    void setPropertyArrayLength(const BaseLib::Strings::String& propertyName, int constArrayLength);
	*/


	/*
	// get/set string-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, BaseLib::Strings::String (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(const BaseLib::Strings::String& propertyValue, int index), int minLength = 0, int maxLength = DEFAULT_MAX_STRINGPROPERTY_LENGTH)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setValueRange(minLength, maxLength);
			stringProperty->setGetterFunctor(new GetStringPropertyFunctor<T>(stringProperty, getPropertyFunc));
			stringProperty->setSetterFunctor(new SetStringPropertyFunctor<T>(stringProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get string-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, BaseLib::Strings::String (T::*getPropertyFunc)(int index) const)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setGetterFunctor(new GetStringPropertyFunctor<T>(stringProperty, getPropertyFunc));
		}
	}
	*/

	/*
	// set string-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(const BaseLib::Strings::String& propertyValue, int index), int minLength = 0, int maxLength = DEFAULT_MAX_STRINGPROPERTY_LENGTH)
	{
		StringProperty* stringProperty = getOrCreateStringProperty(propertyName);
		if (stringProperty != NULL)
		{
			stringProperty->setValueRange(minLength, maxLength);
			stringProperty->setSetterFunctor(new SetStringPropertyFunctor<T>(stringProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get/set int-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, int (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(int propertyValue, int index), int minValue = INT_MIN, int maxValue = INT_MAX)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setValueRange(minValue, maxValue);
			intProperty->setGetterFunctor(new GetIntPropertyFunctor<T>(intProperty, getPropertyFunc));
			intProperty->setSetterFunctor(new SetIntPropertyFunctor<T>(intProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get int-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, int (T::*getPropertyFunc)(int index) const)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setGetterFunctor(new GetIntPropertyFunctor<T>(intProperty, getPropertyFunc));
		}
	}
	*/

	/*
	// set int-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(int propertyValue, int index), int minValue = INT_MIN, int maxValue = INT_MAX)
	{
		IntProperty* intProperty = getOrCreateIntProperty(propertyName);
		if (intProperty != NULL)
		{
			intProperty->setValueRange(minValue, maxValue);
			intProperty->setSetterFunctor(new SetIntPropertyFunctor<T>(intProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get/set bool-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, bool (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(bool propertyValue, int index))
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setGetterFunctor(new GetBoolPropertyFunctor<T>(boolProperty, getPropertyFunc));
			boolProperty->setSetterFunctor(new SetBoolPropertyFunctor<T>(boolProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get bool-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, bool (T::*getPropertyFunc)(int index) const)
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setGetterFunctor(new GetBoolPropertyFunctor<T>(boolProperty, getPropertyFunc));
		}
	}
	*/

	/*
	// set bool-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(bool propertyValue, int index))
	{
		BoolProperty* boolProperty = getOrCreateBoolProperty(propertyName);
		if (boolProperty != NULL)
		{
			boolProperty->setSetterFunctor(new SetBoolPropertyFunctor<T>(boolProperty, setPropertyFunc));
		}
	}
	*/


	/*
	// get/set enum-array:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, E (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(E propertyValue, int index))
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setGetterFunctor(new GetEnumPropertyFunctor<T, E>(enumProperty, getPropertyFunc));
			enumProperty->setSetterFunctor(new SetEnumPropertyFunctor<T, E>(enumProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get enum-array:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, E (T::*getPropertyFunc)(int index) const)
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setGetterFunctor(new GetEnumPropertyFunctor<T, E>(enumProperty, getPropertyFunc));
		}
	}
	*/

	/*
	// set enum-array:
    template<class T, typename E>
    void registerEnumProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(E propertyValue, int index))
	{
		EnumProperty* enumProperty = getOrCreateEnumProperty(propertyName);
		if (enumProperty != NULL)
		{
			enumProperty->setSetterFunctor(new SetEnumPropertyFunctor<T, E>(enumProperty, setPropertyFunc));
		}
	}
	*/

	/*
	// get/set float-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, float (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(float propertyValue, int index), float minValue = -FLT_MAX, float maxValue = FLT_MAX)
	{
		FloatProperty* floatProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			floatProperty = new FloatProperty(propertyName);
			addProperty(floatProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			floatProperty = static_cast<FloatProperty*>(abstractProperty);
		}
		floatProperty->setValueRange(minValue, maxValue);
		floatProperty->setGetterFunctor(new GetFloatPropertyFunctor<T>(floatProperty, getPropertyFunc));
		floatProperty->setSetterFunctor(new SetFloatPropertyFunctor<T>(floatProperty, setPropertyFunc));
	}
	*/

	/*
	// get float-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, float (T::*getPropertyFunc)(int index) const, float minValue = -FLT_MAX, float maxValue = FLT_MAX)
	{
		FloatProperty* floatProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			floatProperty = new FloatProperty(propertyName);
			addProperty(floatProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			floatProperty = static_cast<FloatProperty*>(abstractProperty);
		}
		floatProperty->setGetterFunctor(new GetFloatPropertyFunctor<T>(floatProperty, getPropertyFunc));
	}
	*/

	/*
	// set float-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(float propertyValue, int index), float minValue = -FLT_MAX, float maxValue = FLT_MAX)
	{
		FloatProperty* floatProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			floatProperty = new FloatProperty(propertyName);
			addProperty(floatProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			floatProperty = static_cast<FloatProperty*>(abstractProperty);
		}
		floatProperty->setValueRange(minValue, maxValue);
		floatProperty->setSetterFunctor(new SetFloatPropertyFunctor<T>(floatProperty, setPropertyFunc));
	}
	*/

	/*
	// get/set double-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, double (T::*getPropertyFunc)(int index) const, void (T::*setPropertyFunc)(double propertyValue, int index), double minValue = -DBL_MAX, double maxValue = DBL_MAX)
	{
		DoubleProperty* doubleProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			doubleProperty = new DoubleProperty(propertyName);
			addProperty(doubleProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			doubleProperty = static_cast<DoubleProperty*>(abstractProperty);
		}
		doubleProperty->setValueRange(minValue, maxValue);
		doubleProperty->setGetterFunctor(new GetDoublePropertyFunctor<T>(doubleProperty, getPropertyFunc));
		doubleProperty->setSetterFunctor(new SetDoublePropertyFunctor<T>(doubleProperty, setPropertyFunc));
	}
	*/

	/*
	// get double-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, double (T::*getPropertyFunc)(int index) const, double minValue = -DBL_MAX, double maxValue = DBL_MAX)
	{
		DoubleProperty* doubleProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			doubleProperty = new DoubleProperty(propertyName);
			addProperty(doubleProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			doubleProperty = static_cast<DoubleProperty*>(abstractProperty);
		}
		doubleProperty->setGetterFunctor(new GetDoublePropertyFunctor<T>(doubleProperty, getPropertyFunc));
	}
	*/

	/*
	// set double-array:
    template<class T>
    void registerProperty(const BaseLib::Strings::String& propertyName, void (T::*setPropertyFunc)(double propertyValue, int index), double minValue = -DBL_MAX, double maxValue = DBL_MAX)
	{
		DoubleProperty* doubleProperty;
		Property* abstractProperty = getPropertyOrNull(propertyName);
		if (abstractProperty == NULL)
		{
			doubleProperty = new DoubleProperty(propertyName);
			addProperty(doubleProperty);
		}
		else
		{
			if (abstractProperty->getType() != Property::INT_PROPERTY)
			{
				stateError(ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(propertyName));
				return;
			}
			doubleProperty = static_cast<DoubleProperty*>(abstractProperty);
		}
		doubleProperty->setValueRange(minValue, maxValue);
		doubleProperty->setSetterFunctor(new SetDoublePropertyFunctor<T>(doubleProperty, setPropertyFunc));
	}
	*/

