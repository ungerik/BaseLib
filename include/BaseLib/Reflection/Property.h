/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Property_h
#define BaseLib_Reflection_Property_h



//#include "BaseLib/Reflection/intern/AbstractGetPropertyFunctor.h"
//#include "BaseLib/Reflection/intern/AbstractSetPropertyFunctor.h"
////#include "BaseLib/Reflection/intern/ArrayLengthFunctor.h"
//#include "BaseLib/Strings/String.h"
//#include "BaseLib/Containers/Enumeration.h"
//#include "BaseLib/Functors/Functor0.h"
//#include "BaseLib/Functors/Functor1.h"
//#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
	namespace Strings {
		class NumberFormat;
	}
}



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;
using BaseLib::Functors::ConstMethodFunctor0;
using BaseLib::Strings::NumberFormat;



class BL_EXPORT Property : public NonCopyable {
public:

	enum Type {
		STRING_PROPERTY,
		ENUM_PROPERTY,
		BOOL_PROPERTY,
		INT_PROPERTY,
		FLOAT_PROPERTY,
		DOUBLE_PROPERTY
	};

	static const BaseLib::Strings::String NON_SERIALIZEABLE;

	Property(const BaseLib::Strings::String& propertyName);
	virtual ~Property();

	virtual Type getType() const = 0;

	BaseLib::Strings::String getTypeAsString() const;

	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const = 0;

	inline const BaseLib::Strings::String& getName() const
	{
		return name;
	}

	inline void setGetterFunctor(AbstractGetPropertyFunctor* newGetterFunctor)
	{
		getterFunctor = newGetterFunctor;
	}

	inline void setSetterFunctor(AbstractSetPropertyFunctor* newSetterFunctor)
	{
		setterFunctor = newSetterFunctor;
	}

	inline AbstractGetPropertyFunctor* getGetterFunctor()
	{
		return getterFunctor;
	}

	inline const AbstractGetPropertyFunctor* getGetterFunctor() const
	{
		return getterFunctor;
	}

	inline  AbstractSetPropertyFunctor* getSetterFunctor()
	{
		return setterFunctor;
	}

	inline const AbstractSetPropertyFunctor* getSetterFunctor() const
	{
		return setterFunctor;
	}

	inline bool isReadable() const
	{
		return getGetterFunctor() != NULL;
	}

	inline bool isWriteable() const
	{
		return getSetterFunctor() != NULL;
	}

	/*
	inline AbstractArrayLengthFunctor* getArrayFunctor() const
	{
		return arrayFunctor != NULL ? arrayFunctor : &FixedArrayLengthFunctor::one;
	}
	inline void setArrayFunctor(AbstractArrayLengthFunctor* newArrayFunctor)
	{
		arrayFunctor = newArrayFunctor;
	}
	*/

    BaseLib::Strings::String get(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    int getAsInt(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    bool getAsBool(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    float getAsFloat(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;
    double getAsDouble(const void* instance, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/) const;

	void set(void* instance, const BaseLib::Strings::String& propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    void set(void* instance, int propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    void set(void* instance, bool propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    void set(void* instance, float propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);
    void set(void* instance, double propertyValue, const NumberFormat* numberFormat = NULL/*, int arrayIndex*/);

	bool hasMetaTag(const BaseLib::Strings::String& metaTag) const;
	void addMetaTag(const BaseLib::Strings::String& metaTag);
	void removeMetaTag(const BaseLib::Strings::String& metaTag);

	virtual bool isDefault(const void* instance) const = 0;
	virtual void setToDefault(void* instance) = 0;


	/*
    bool isFixedArrayLength() const;
    int getArrayLength(const void* instance) const;
    void setArrayLength(void* instance, int newArrayLength) const;
	*/

private:

	BaseLib::Utilities::AutoPointer<AbstractGetPropertyFunctor> getterFunctor;
	BaseLib::Utilities::AutoPointer<AbstractSetPropertyFunctor> setterFunctor;
	//AutoPointer<AbstractArrayLengthFunctor> arrayFunctor;
	const BaseLib::Strings::String name;
	bool persistent;

	typedef std::set<BaseLib::Strings::String> MetaTags;
	MetaTags metaTags;
};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_Property_h