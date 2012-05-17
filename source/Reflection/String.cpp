/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#include "BaseLib/Reflection/String.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Reflection {



BL_DEFINE_REFLECTION_BASE_CLASS(BoxedString)
{
	registerProperty("value", &BoxedString::getValue, &BoxedString::setValue);
	registerProperty("length", &BoxedString::getLength, &BoxedString::setLength);
	registerEnumProperty("encoding", &BoxedString::getEncoding);
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::UTF8_ENCODING, "UTF8");
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::UTF16_ENCODING, "UTF16");
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::STRING_DECISION_ENCODING, "String Decision");
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::CHAR8_ENCODING, "CHAR8");
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::CHAR16_ENCODING, "CHAR16");
	registerEnumPropertyValueAndName("encoding", BaseLib::Strings::CHAR32_ENCODING, "CHAR32");
}



BoxedString::BoxedString(const ValueType& newValue)
	: value(newValue)
{
}



BoxedString::ValueType BoxedString::getValue() const
{
	return value;
}



void BoxedString::setValue(const ValueType& newValue)
{
	value = newValue;
}



int BoxedString::getLength() const
{
	return value.getLength();
}



void BoxedString::setLength(int newLength)
{
	value.setLength(newLength);
}



BaseLib::Strings::StringEncoding BoxedString::getEncoding() const
{
	return value.getEncoding();
}



} // namespace Reflection
} // namespace BaseLib
