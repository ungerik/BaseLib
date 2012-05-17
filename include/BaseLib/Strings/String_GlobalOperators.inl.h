/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



BL_EXPORT bool operator ==(const String& left, const String& right);
BL_EXPORT bool operator ==(const String& left, const char8 * right);
BL_EXPORT bool operator ==(const String& left, const char16 * right);



inline bool operator ==(const char8 * left, const String& right)
{
	return operator ==(right, left);
}



inline bool operator ==(const char16 * left, const String& right)
{
	return operator ==(right, left);
}



inline bool operator !=(const String& left, const String& right)
{
	return !(left == right);
}



template<class T>
inline bool operator !=(const String& left, const T& right)
{
	return !(left == right);
}



template<class T>
inline bool operator !=(const T& left, const String& right)
{
	return !(left == right);
}



inline bool operator<(const String& left, const String& right)
{
	return left.compare(right) < 0;
}



BL_EXPORT String operator +(const String& left, const String& right);
BL_EXPORT String operator +(const String& left, const char8 * right);
BL_EXPORT String operator +(const String& left, const char16 * right);



inline String operator +(const String& left, const String::Char& right)
{
	return operator +(left, right.operator char16());
}



inline String operator +(const String& left, const String::ConstChar& right)
{
	return operator +(left, right.operator char16());
}