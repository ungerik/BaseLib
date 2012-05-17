/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Variant_h
#define BaseLib_Reflection_Variant_h



//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace Reflection {



class BL_EXPORT Variant : public Object {
public:

	enum Type {
		STRING,
		BOOL,
		INT,
		FLOAT,
		DOUBLE,
		BINARY, ///
		OBJECT
	};

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Reflection::Variant);

	explicit Variant(Type newType = INT);
	~Variant();

	inline Type getType() const
	{
		return type;
	}

	void setType(Type newType);

    operator BaseLib::Strings::String() const;
    operator int() const;
    operator bool() const;
    operator float() const;
    operator double() const;

	template<typename T>
	inline Variant& operator=(const T& newValue)
	{
		set(newValue);
		return *this;
	}

	Variant(const BaseLib::Strings::String& newValue);
	Variant(int newValue);
	Variant(bool newValue);
	Variant(float newValue);
	Variant(double newValue);
	Variant(Object* newValue);

	inline Object* getObject()
	{
		return type == OBJECT ? objectValue : this;
	}

	inline const Object* getObject() const
	{
		return type == OBJECT ? objectValue : this;
	}

	Variant& operator+=(const Variant& right);
	Variant& operator+=(const BaseLib::Strings::String& right);
	Variant& operator+=(int right);
	Variant& operator+=(bool right);
	Variant& operator+=(float right);
	Variant& operator+=(double right);

	///ToDo: Fehlende Operotoren hinzufügen:

private:

	union {
		BaseLib::Strings::String* stringValue;
		int intValue;
		bool boolValue;
		float floatValue;
		double doubleValue;
		const void* binaryValue; ///
		Object* objectValue;
	};

	const Property* property;
	Type type;

	void set(const BaseLib::Strings::String& newValue);
    void set(int newValue);
    void set(bool newValue);
    void set(float newValue);
    void set(double newValue);
    void set(Object* newValue);
};



} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_Variant_h