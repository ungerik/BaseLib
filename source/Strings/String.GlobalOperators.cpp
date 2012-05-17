/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Strings {



bool operator ==(const String& left, const String& right)
{
	int size = left.getLength();
	if (size != right.getLength()) return false;

	if (left.getEncoding() == CHAR8_ENCODING && right.getEncoding() == CHAR8_ENCODING)
	{
		const char8 * leftArray = left.getChar8Array();
		const char8 * rightArray = right.getChar8Array();

		for (int i = 0; i < size; ++i)
		{
			if (leftArray[i] != rightArray[i]) return false;
		}
	}
	else
	{
		const char16 * leftArray = left.getChar16Array();
		const char16 * rightArray = right.getChar16Array();

		for (int i = 0; i < size; ++i)
		{
			if (leftArray[i] != rightArray[i]) return false;
		}
	}
	return true;
}



bool operator ==(const String& left, const char8 * right)
{
	int length = left.getLength();
	const char8 * leftArray = left.getChar8Array();

	for (int i = 0; i < length; ++i) 
	{
		if (leftArray[i] != right[i]) return false;
	}
	return right[length] == 0;
}



bool operator ==(const String& left, const char16 * right)
{
	int length = left.getLength();
	const char16 * leftArray = left.getChar16Array();

	for (int i = 0; i < length; ++i)
	{
		if (leftArray[i] != right[i]) return false;
	}
	return right[length] == 0;
}



String operator +(const String& left, const String& right)
{
	int leftLength = left.getLength();
	int rightLength = right.getLength();

	String result(left.getEncoding(), leftLength + rightLength);
	result.copyFromString(left, 0, 0, leftLength);
	result.copyFromString(right, 0, leftLength, rightLength);

	return result;
}



String operator +(const String& left, const char8 * right)
{
	int leftSize = left.getLength();
	int rightSize = zeroTerminatedStringLength(right);

	String result(left.getEncoding(), leftSize + rightSize);
	result.copyFromString(left, 0, 0, leftSize);
	result.copyFromCharArray(right, leftSize, rightSize);

	return result;
}



String operator +(const String& left, const char16 * right)
{
	int leftSize = left.getLength();
	int rightSize = zeroTerminatedStringLength(right);

	String result(left.getEncoding(), leftSize + rightSize);
	result.copyFromString(left, 0, 0, leftSize);
	result.copyFromCharArray(right, leftSize, rightSize);

	return result;
}



} // namespace Strings
} // namespace BaseLib

