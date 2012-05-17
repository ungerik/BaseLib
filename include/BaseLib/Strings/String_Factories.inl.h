/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



//static String createFrom(void* value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(const void* value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(bool value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(uint32 value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(int32 value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(uint64 value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(int64 value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(float value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(double value, StringEncoding stringEncoding = getDefaultEncoding());
static String createFrom(long double value, StringEncoding stringEncoding = getDefaultEncoding());



static String createFrom(const String& string, ...);




inline static String createFrom(const String& value, StringEncoding stringEncoding)
{
	if (stringEncoding == STRING_DECISION_ENCODING)
	{
		return value;
	}
	else
	{
		return String(stringEncoding) = value;
	}
}



template<class T>
static String implode(const T& begin, const T& end, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		result += *i;
	}
	return result;
}



template<class T>
inline static String implode(const T& stringContainer, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implode(stringContainer.begin(), stringContainer.end(), stringEncoding);
}



template<class T>
String static implode(const T& begin, const T& end, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		if (i != begin) result += separator;
		result += *i;
	}
	return result;
}



template<class T>
inline static String implode(const T& stringContainer, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implode(stringContainer.begin(), stringContainer.end(), separator, stringEncoding);
}



template<class T>
static String implodeWithCreateFrom(const T& begin, const T& end, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		result += String::createFrom(*i);
	}
	return result;
}



template<class T>
inline static String implodeWithCreateFrom(const T& stringContainer, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implodeWithCreateFrom(stringContainer.begin(), stringContainer.end(), stringEncoding);
}



template<class T>
String static implodeWithCreateFrom(const T& begin, const T& end, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		if (i != begin) result += separator;
		result += String::createFrom(*i);
	}
	return result;
}



template<class T>
inline static String implodeWithCreateFrom(const T& stringContainer, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implodeWithCreateFrom(stringContainer.begin(), stringContainer.end(), separator, stringEncoding);
}



template<class T>
static String implodeWithStaticCast(const T& begin, const T& end, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		result += static_cast<const String&>(*i);
	}
	return result;
}



template<class T>
inline static String implodeWithStaticCast(const T& stringContainer, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implodeWithCast(stringContainer.begin(), stringContainer.end(), stringEncoding);
}



template<class T>
String static implodeWithStaticCast(const T& begin, const T& end, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	String result(stringEncoding);
	for (T i = begin; i != end; ++i)
	{
		if (i != begin) result += separator;
		result += static_cast<const String&>(*i);
	}
	return result;
}



template<class T>
inline static String implodeWithStaticCast(const T& stringContainer, const String& separator, StringEncoding stringEncoding = getDefaultEncoding())
{
	return implodeWithStaticCast(stringContainer.begin(), stringContainer.end(), separator, stringEncoding);
}

