/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/


#include "BaseLib/Reflection/Convertable.h"



namespace BaseLib {
namespace Reflection {



/*
BL_DEFINE_REFLECTION_BASE_CLASS(BaseLib::Reflection::Convertable)
{
	registerenumproperty("type", convertable::gettype);
	registerenumpropertyvalueandname("type", string, "string");
	registerenumpropertyvalueandname("type", bool, "bool");
	registerenumpropertyvalueandname("type", int, "int");
	registerenumpropertyvalueandname("type", float, "float");
	registerenumpropertyvalueandname("type", double, "double");
}



Convertable::Convertable()
	: BaseLib::Reflection::Object()
	, value()
{
}


Convertable::operator String() const
{
	return type == STRING ? (stringValue != NULL ? *stringValue : "") : property->get(this);
}



Convertable::operator int() const
{
	return type == INT ? intValue : property->getAsInt(this);
}



Convertable::operator bool() const
{
	return type == BOOL ? boolValue : property->getAsBool(this);
}



Convertable::operator float() const
{
	return type == FLOAT ? floatValue : property->getAsFloat(this);
}



Convertable::operator double() const
{
	return type == DOUBLE ? doubleValue : property->getAsDouble(this);
}



void Convertable::setAsString(const String& propertyValue)
{
	if (type == STRING)
	{
		if (stringValue == NULL)
		{
			stringValue = new String(propertyValue);
		}
		else
		{
			*stringValue = propertyValue;
		}
	}
	else
	{
		property->set(this, propertyValue);
	}
}



void Convertable::setAsInt(int propertyValue)
{
	if (type == INT)
	{
		intValue = propertyValue;
	}
	else
	{
		property->set(this, propertyValue);
	}
}



void Convertable::setAsBool(bool propertyValue)
{
	if (type == BOOL)
	{
		boolValue = propertyValue;
	}
	else
	{
		property->set(this, propertyValue);
	}
}



void Convertable::setAsFloat(float propertyValue)
{
	if (type == FLOAT)
	{
		floatValue = propertyValue;
	}
	else
	{
		property->set(this, propertyValue);
	}
}



void Convertable::setAsDouble(double propertyValue)
{
	if (type == DOUBLE)
	{
		doubleValue = propertyValue;
	}
	else
	{
		property->set(this, propertyValue);
	}
}
*/

} // namespace Reflection
} // namespace BaseLib
