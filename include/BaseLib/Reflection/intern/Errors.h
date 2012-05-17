/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_ReflectionErrors_h
#define BaseLib_ReflectionErrors_h



//#include "BaseLib/ErrorHandling.h"



#define PROPERTY_NOT_FOUND(p) ( BaseLib::Strings::String("Property \"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\" not found !") + ERROR_AT )
#define PROPERTY_ALREADY_REGISTERED(p) ( BaseLib::Strings::String("Property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" already registered !") + ERROR_AT )
#define PROPERTY_INDEX_OUT_OF_RANGE(i, low, high)  ( BaseLib::Strings::String("Property-index ") + BaseLib::Strings::String::createFrom(i) + BaseLib::Strings::String(" out of range [") + BaseLib::Strings::String::createFrom(low) + BaseLib::Strings::String("..") + BaseLib::Strings::String::createFrom(high) + BaseLib::Strings::String("]!") + ERROR_AT )
#define STRING_FOR_PROPERTY_TOO_LONG(p, l, maxl) ( BaseLib::Strings::String("std::string for property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String("too long (string length: ") + BaseLib::Strings::String::createFrom(l) + BaseLib::Strings::String(", allowed length: ") + BaseLib::Strings::String::createFrom(maxl) + BaseLib::Strings::String(") !") + ERROR_AT )
#define STRING_FOR_PROPERTY_TOO_SHORT(p, l, maxl) ( BaseLib::Strings::String("std::string for property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String("too long (string length: ") + BaseLib::Strings::String::createFrom(l) + BaseLib::Strings::String(", allowed length: ") + BaseLib::Strings::String::createFrom(maxl) + BaseLib::Strings::String(") !") + ERROR_AT )
#define STRING_NO_ENUM_TOKEN(p, s) ( BaseLib::Strings::String("std::string \"") + s + BaseLib::Strings::String("\" for enum property ") + p + BaseLib::Strings::String("is not a valid enum-token !") + ERROR_AT )
#define STRING_NO_BOOLEAN_CONSTANT(p, s) ( BaseLib::Strings::String("std::string \"") + s + BaseLib::Strings::String("\" for boolean property ") + p + BaseLib::Strings::String("is not a boolean constant !") + ERROR_AT )
#define VALUE_FOR_PROPERTY_SMALLER_THAN_MINIUM(p, val, minval) ( BaseLib::Strings::String("Value ") + BaseLib::Strings::String::createFrom(val) + BaseLib::Strings::String(" for property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" smaller than allowed minimum of ") + BaseLib::Strings::String::createFrom(minval) + BaseLib::Strings::String(" !") + ERROR_AT )
#define VALUE_FOR_PROPERTY_GREATER_THAN_MINIUM(p, val, maxval) ( BaseLib::Strings::String("Value ") + BaseLib::Strings::String::createFrom(val) + BaseLib::Strings::String(" for property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" greater than allowed maximum of ") + BaseLib::Strings::String::createFrom(maxval) + BaseLib::Strings::String(" !") + ERROR_AT )
#define CANT_REGISTER_ENUM_FOR_NON_ENUM_PROPERTY(p, ev, en) ( BaseLib::Strings::String("Can't register enum (value: ") + BaseLib::Strings::String::createFrom(ev) + BaseLib::Strings::String(", name: ") + BaseLib::Strings::String(en) + BaseLib::Strings::String(") for non enum property ") + BaseLib::Strings::String(p) + ERROR_AT )
#define CANT_SET_INT_PROPERTY_FROM_STRING(p, s) ( BaseLib::Strings::String("Can't convert the string \"")  + BaseLib::Strings::String(s) + BaseLib::Strings::String("\" to set the int-property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" !") + ERROR_AT )
#define CANT_SET_FLOAT_PROPERTY_FROM_STRING(p, s) ( BaseLib::Strings::String("Can't convert the string \"")  + BaseLib::Strings::String(s) + BaseLib::Strings::String("\" to set the float-property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" !") + ERROR_AT )
#define CANT_CONVERT_STRING_PROPERTY_TO_INT(p, s) ( BaseLib::Strings::String("Can't convert the string \"")  + BaseLib::Strings::String(s) + BaseLib::Strings::String("\" from int-property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" to an int-value!") + ERROR_AT )
#define CANT_CONVERT_STRING_PROPERTY_TO_BOOL(p, s) ( BaseLib::Strings::String("Can't convert the string \"")  + BaseLib::Strings::String(s) + BaseLib::Strings::String("\" from int-property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" to an bool-value!") + ERROR_AT )
#define CANT_CONVERT_STRING_PROPERTY_TO_FLOAT(p, s) ( BaseLib::Strings::String("Can't convert the string \"")  + BaseLib::Strings::String(s) + BaseLib::Strings::String("\" from int-property ") + BaseLib::Strings::String(p) + BaseLib::Strings::String(" to an float-value!") + ERROR_AT )
#define DIFFERENT_GET_SET_PROPERTY_TYPES(g, s) ( BaseLib::Strings::String("Setter and getter functors have different property-types (\"") + BaseLib::Strings::String(g) + BaseLib::Strings::String("\" and \"") + BaseLib::Strings::String("\") !") + ERROR_AT )
#define CANT_MIX_ENUM_AND_OTHER_TYPE_FOR_GET_SET_PROPERTY(p) ( BaseLib::Strings::String("Can't mix enum- and an other type for get/set property-functors of property:\"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\" !") + ERROR_AT)
#define CANT_MIX_ARRAY_WITH_NORMAL_PROPERTY(p) ( BaseLib::Strings::String("Can't mix array- and normal property-type (property:\"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\") !") + ERROR_AT )
#define PROPERTY_NOT_WRITEABLE(p) ( BaseLib::Strings::String("Property \"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\" is not writeable !") + ERROR_AT )
#define PROPERTY_NOT_READABLE(p) ( BaseLib::Strings::String("Property \"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\" is not readable !") + ERROR_AT )
#define ARRAY_LENGTH_IS_READ_ONLY ( BaseLib::Strings::String("Array-length of property is read-only !") + ERROR_AT )
#define NO_ARRAY_PROPERTY(p) ( BaseLib::Strings::String("Property \"") + BaseLib::Strings::String(p) + BaseLib::Strings::String("\" is not an array !") + ERROR_AT )
#define AGGREGATION_MEMBER_NAME_ALREADY_REGISTERED(n) ( BaseLib::Strings::String("Aggregation-member name \"") + BaseLib::Strings::String(n) + BaseLib::Strings::String("\" alreade registered!") + ERROR_AT )
#define AGGREGATION_MEMBER_NOT_FOUND(n) ( BaseLib::Strings::String("Aggregation-member \"") + BaseLib::Strings::String(n) + BaseLib::Strings::String("\" not found!") + ERROR_AT )
#define AGGREGATION_MEMBER_NOT_READABLE(n) ( BaseLib::Strings::String("Aggregation-member \"") + BaseLib::Strings::String(n) + BaseLib::Strings::String("\" not readable!") + ERROR_AT )
#define AGGREGATION_MEMBER_NOT_WRITEABLE(n) ( BaseLib::Strings::String("Aggregation-member \"") + BaseLib::Strings::String(n) + BaseLib::Strings::String("\" not writeable!") + ERROR_AT )
#define ATTEMPT_TO_REGISTER_DIFFERENT_PROPERTY_TYPE(p) ( BaseLib::Strings::String("Attempt to register different property-type for property ") + BaseLib::Strings::String(p) + " !" ERROR_AT )

#endif // #ifndef BaseLib_ReflectionErrors_h
