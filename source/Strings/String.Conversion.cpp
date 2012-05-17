/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/String.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Strings/NumberFormat.h"
#include <boost/lexical_cast.hpp>
#include <stdarg.h>



#ifndef BL_NO_ICU
	#include <unicode/unum.h>
#endif



namespace BaseLib {
namespace Strings {



using namespace BaseLib::ErrorHandling;
#ifndef BL_NO_ICU
	#define CANT_CREATE_STRING_FROM_VALUE(status) (String("Can't create string from value because of error: ") + String(u_errorName(status)) + ERROR_AT)
#else
	#define CANT_CREATE_STRING_FROM_VALUE ("Can't create string from value!" + ERROR_AT)
#endif
#define ICU_BUFFER_LENGTH 32



String String::createFrom(const void* value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format((int64)value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(bool value, StringEncoding stringEncoding)
{
	return value == true ? "true" : "false";

	//try
	//{
	//	return String(boost::lexical_cast<std::string>(value), stringEncoding);
	//}
	//catch (...)
	//{
	//	argumentError(CANT_CREATE_STRING_FROM_VALUE);
	//	return Empty();
	//}
}



String String::createFrom(uint32 value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(int32 value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(uint64 value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(int64 value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(float value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(double value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(long double value, StringEncoding stringEncoding)
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->format(value, stringEncoding);
	#else
		try
		{
			return String(boost::lexical_cast<std::string>(value), stringEncoding);
		}
		catch (...)
		{
			argumentError(CANT_CREATE_STRING_FROM_VALUE);
			return Empty();
		}
	#endif
}



String String::createFrom(const String& string, ...)
{
	va_list	argumentList;
	va_start(argumentList, string);
	if (string.getEncoding() == CHAR8_ENCODING)
	{
		char8 buffer[1024*16];
		sprintf_s(buffer, 1024*16, string.getChar8CString(), argumentList);
		return String(buffer);
	}
	else
	{
		char16 buffer[1024*16];
		swprintf(buffer, 1024*16, string.getChar16CString(), argumentList);
		return String(buffer);
	}

	return string;
}



void* String::parsePointer(int start, int length) const
{
	#ifndef BL_NO_ICU

	#else
	#endif
		try
		{
			return boost::lexical_cast<void*>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse pointer from value '" + *this + "' !" + ERROR_AT);
			return false;
		}
}



bool String::parseBool(int start, int length) const
{
	try
	{
		//return boost::lexical_cast<bool>(subString(start, length).operator std::string());
		if (equalsCaseInsensitive("false") == true)
		{
			return false;
		}
		else if (equalsCaseInsensitive("true") == true)
		{
			return true;
		}
		else
		{
			return parseDouble() != 0.0;
		}
	}
	catch (...)
	{
		argumentError("Can't parse bool from value '" + *this + "' !" + ERROR_AT);
		return false;
	}
}



uint String::parseUint(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseUint(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<uint>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse unsigned int from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



int String::parseInt(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseInt(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<int>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse int from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



uint8 String::parseUint8(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseUint8(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<uint8>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse uint8 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



int8 String::parseInt8(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseInt8(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<int8>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse int8 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



uint16 String::parseUint16(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseUint16(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<uint16>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse uint16 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



int16 String::parseInt16(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseInt16(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<int16>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse int16 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



uint32 String::parseUint32(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseUint32(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<uint32>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse uint32 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



int32 String::parseInt32(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseInt32(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<int32>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse int32 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



uint64 String::parseUint64(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseUint64(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<uint64>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse uint64 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



int64 String::parseInt64(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseInt64(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<int64>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse int64 from value '" + *this + "' !" + ERROR_AT);
			return 0;
		}
	#endif
}



float String::parseFloat(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseFloat(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<float>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse float from value '" + *this + "' !" + ERROR_AT);
			return 0.0f;
		}
	#endif
}



double String::parseDouble(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseDouble(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<double>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse double from value '" + *this + "' !" + ERROR_AT);
			return 0.0;
		}
	#endif
}



long double String::parseLongDouble(int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->parseLongDouble(*this, start, length);
	#else
		try
		{
			return boost::lexical_cast<long double>(subString(start, length).operator std::string());
		}
		catch (...)
		{
			argumentError("Can't parse long double from value '" + *this + "' !" + ERROR_AT);
			return 0.0;
		}
	#endif
}



bool String::tryParse(const void*& result, int start, int length) const
{
	try
	{
		result = boost::lexical_cast<void*>(subString(start, length).operator std::string());
		return true;
	}
	catch (...)
	{
		return false;
	}
}



bool String::tryParse(bool& result, int start, int length) const
{
	try
	{
		//result = boost::lexical_cast<bool>(subString(start, length).operator std::string());

		if (equalsCaseInsensitive("false") == true)
		{
			result = false;
		}
		else if (equalsCaseInsensitive("true") == true)
		{
			result = true;
		}
		else
		{
			result = parseDouble() != 0.0;
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}



bool String::tryParse(uint8& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<uint8>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}


bool String::tryParse(int8& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<int8>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(uint16& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<uint16>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(int16& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<int16>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(uint32& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<uint32>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(int32& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<int32>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(uint64& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<uint64>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(int64& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<int64>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(float& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<float>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(double& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<double>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}



bool String::tryParse(long double& result, int start, int length) const
{
	#ifndef BL_NO_ICU
		return NumberFormat::getDefault()->tryParse(*this, result, start, length);
	#else
		try
		{
			result = boost::lexical_cast<long double>(subString(start, length).operator std::string());
			return true;
		}
		catch (...)
		{
			return false;
		}
	#endif
}






} // namespace Strings
} // namespace BaseLib