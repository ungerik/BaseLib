/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Strings {



String& String::operator =(const char8 * right)
{
	int length = zeroTerminatedStringLength(right);
	getUnsharedImplementation(length)->copyFromCharArray(right, 0, length);
	return *this;
}



String& String::operator =(const char16 * right)
{
	int length = zeroTerminatedStringLength(right);
	getUnsharedImplementation(length)->copyFromCharArray(right, 0, length);
	return *this;
}



String& String::operator =(const std::string& right)
{
	int length = right.length();
	getUnsharedImplementation(length)->copyFromCharArray(right.data(), 0, length);
	return *this;
}



String& String::operator =(const std::wstring& right)
{
	int length = right.length();
	getUnsharedImplementation(length)->copyFromCharArray(right.data(), 0, length);
	return *this;
}



String& String::operator =(char8 right)
{
	getUnsharedImplementation(1)->setChar(0, right);
	return *this;
}



String& String::operator =(char16 right)
{
	getUnsharedImplementation(1)->setChar(0, right);
	return *this;
}



String& String::operator =(const Char& right)
{
	getUnsharedImplementation(1)->setChar(0, right.operator char16());
	return *this;
}



String& String::operator =(const ConstChar& right)
{
	getUnsharedImplementation(1)->setChar(0, right.operator char16());
	return *this;
}



String& String::operator +=(const String& right)
{
	int rightSize = right.getLength();
	if (rightSize > 0)
	{
		int leftSize = getLength();	
		getUnsharedImplementation(leftSize + rightSize);
		copyFromString(right, 0, leftSize, rightSize);
	}
	return *this;
}



String& String::operator +=(char8 right)
{
	int leftSize = getLength();
	getUnsharedImplementation(leftSize + 1)->setChar(leftSize, right);
	return *this;
}



String& String::operator+=(char16 right)
{
	int leftSize = getLength();
	getUnsharedImplementation(leftSize + 1)->setChar(leftSize, right);
	return *this;
}



} // namespace Strings
} // namespace BaseLib

