/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/Variant.h"
#include "BaseLib/ErrorHandling.h"
#include <memory.h>



namespace BaseLib {
namespace Reflection {



using namespace BaseLib::Math;



BL_DEFINE_REFLECTION_BASE_CLASS(BaseLib::Reflection::Variant)
{
	registerEnumProperty("type", &Variant::getType, &Variant::setType);
	registerEnumPropertyValueAndName("type", STRING, "string");
	registerEnumPropertyValueAndName("type", BOOL, "bool");
	registerEnumPropertyValueAndName("type", INT, "int");
	registerEnumPropertyValueAndName("type", FLOAT, "float");
	registerEnumPropertyValueAndName("type", DOUBLE, "double");
	registerEnumPropertyValueAndName("type", OBJECT, "object");
}



Variant::Variant(Type newType)
	: Object()
	, type(static_cast<Type>(-1))
{
	doubleValue = 0;
	setType(newType);
}



Variant::~Variant()
{
	if (type == STRING)
	{
		delete stringValue;
	}
}



void Variant::setType(Type newType)
{
	if (newType != type)
	{
		if (type == STRING)
		{
			delete stringValue;
		}

		switch (newType)
		{
			case STRING:
				const_cast<Class&>(CLASS).registerProperty("value", &Variant::operator BaseLib::Strings::String, &Variant::set);
				stringValue = NULL;
				break;

			case INT:
				const_cast<Class&>(CLASS).registerProperty("value", &Variant::operator int, &Variant::set);
				break;

			case BOOL:
				const_cast<Class&>(CLASS).registerProperty("value", &Variant::operator bool, &Variant::set);
				break;

			case FLOAT:
				const_cast<Class&>(CLASS).registerProperty("value", &Variant::operator float, &Variant::set);
				break;

			case DOUBLE:
				const_cast<Class&>(CLASS).registerProperty("value", &Variant::operator double, &Variant::set);
				break;

			case OBJECT:
				const_cast<Class&>(CLASS).unregisterProperty("value");
				objectValue = NULL;
				break;
		}

		property = newType != OBJECT ? CLASS.property("value") : NULL;
		type = newType;
	}
}



Variant::operator BaseLib::Strings::String() const
{
	if (type == STRING)
	{
		return stringValue != NULL ? *stringValue : BaseLib::Strings::String();
	}
	else
	{
		if (type != OBJECT)
		{
			return property->get(this);
		}
		else
		{
			return objectValue != NULL ? objectValue->getClass()->getName() : "NULL (Object)";
		}
	}
}



Variant::operator int() const
{
	return type == INT ? intValue : (type != OBJECT ? property->getAsInt(this) : 0);
}



Variant::operator bool() const
{
	return type == BOOL ? boolValue : (type != OBJECT ? property->getAsBool(this) : false);
}



Variant::operator float() const
{
	return type == FLOAT ? floatValue : (type != OBJECT ? property->getAsFloat(this) : std::numeric_limits<float>::quiet_NaN());
}



Variant::operator double() const
{
	return type == DOUBLE ? doubleValue : (type != OBJECT ? property->getAsDouble(this) : std::numeric_limits<double>::quiet_NaN());
}



void Variant::set(const BaseLib::Strings::String& newValue)
{
	setType(STRING);
	if (stringValue == NULL)
	{
		stringValue = new BaseLib::Strings::String(newValue);
	}
	else
	{
		*stringValue = newValue;
	}
}



void Variant::set(int newValue)
{
	setType(INT);
	intValue = newValue;
}



void Variant::set(bool newValue)
{
	setType(BOOL);
	boolValue = newValue;
}



void Variant::set(float newValue)
{
	setType(FLOAT);
	floatValue = newValue;
}



void Variant::set(double newValue)
{
	setType(DOUBLE);
	doubleValue = newValue;
}



Variant::Variant(const BaseLib::Strings::String& newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	stringValue = NULL;
	setType(STRING);
	stringValue = new BaseLib::Strings::String(newValue);
}



Variant::Variant(int newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	doubleValue = 0;
	setType(INT);
	intValue = newValue;
}



Variant::Variant(bool newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	doubleValue = 0;
	setType(BOOL);
	boolValue = newValue;
}



Variant::Variant(float newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	doubleValue = 0;
	setType(FLOAT);
	floatValue = newValue;
}



Variant::Variant(double newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	doubleValue = 0;
	setType(DOUBLE);
	doubleValue = newValue;
}



Variant::Variant(Object* newValue)
	: Object()
	, type(static_cast<Type>(-1))
{
	objectValue = NULL;
	setType(OBJECT);
	objectValue = newValue;
}



Variant& Variant::operator +=(const Variant& right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String(right);
			}
			else
			{
				*stringValue += right.operator BaseLib::Strings::String();
			}
			break;

		case INT:
			intValue += right.operator int();
			break;

		case BOOL:
			boolValue |= right.operator bool();
			break;

		case FLOAT:
			floatValue += right.operator float();
			break;

		case DOUBLE:
			doubleValue += right.operator double();
			break;
	}
	return *this;
}



Variant& Variant::operator +=(const BaseLib::Strings::String& right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String(right);
			}
			else
			{
				*stringValue += right;
			}
			break;

		case INT:
			intValue += right.parseInt();
			break;

		case BOOL:
			boolValue |= right.parseBool();
			break;

		case FLOAT:
			floatValue += right.parseFloat();
			break;

		case DOUBLE:
			doubleValue += right.parseDouble();
			break;
	}
	return *this;
}



Variant& Variant::operator +=(int right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String();
			}
			*stringValue += BaseLib::Strings::String::createFrom(right);
			break;

		case INT:
			intValue += right;
			break;

		case BOOL:
			boolValue |= right != 0;
			break;

		case FLOAT:
			floatValue += right;
			break;

		case DOUBLE:
			doubleValue += right;
			break;
	}
	return *this;
}



Variant& Variant::operator +=(bool right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String();
			}
			*stringValue += BaseLib::Strings::String::createFrom(right);
			break;

		case INT:
			intValue += right;
			break;

		case BOOL:
			boolValue |= right;
			break;

		case FLOAT:
			floatValue += right;
			break;

		case DOUBLE:
			doubleValue += right;
			break;
	}
	return *this;
}



Variant& Variant::operator +=(float right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String();
			}
			*stringValue += BaseLib::Strings::String::createFrom(right);
			break;

		case INT:
			intValue += round<int>(right);
			break;

		case BOOL:
			boolValue |= right != 0;
			break;

		case FLOAT:
			floatValue += right;
			break;

		case DOUBLE:
			doubleValue += right;
			break;
	}
	return *this;
}



Variant& Variant::operator +=(double right)
{
	switch (type)
	{
		case STRING:
			if (stringValue == NULL)
			{
				stringValue = new BaseLib::Strings::String();
			}
			*stringValue += BaseLib::Strings::String::createFrom(right);
			break;

		case INT:
			intValue += round<int>(right);
			break;

		case BOOL:
			boolValue |= right != 0;
			break;

		case FLOAT:
			floatValue += static_cast<float>(right);
			break;

		case DOUBLE:
			doubleValue += right;
			break;
	}
	return *this;
}



} // namespace Reflection
} // namespace BaseLib
