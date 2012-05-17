/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



inline String& operator =(Empty)
{
	setLength(0);
	return *this;
}



inline String& operator =(const String& right)
{
	BL_ASSERT(implementation != NULL);
	//if (implementation != NULL)
	{
		implementation->releaseReference();
	}
	implementation = const_cast<AbstractStringImplementation*>(right.getImplementation());
	BL_ASSERT(implementation != NULL);
	//if (implementation != NULL)
	{	
		implementation->addReference();
	}

	#ifndef NO_SUBSTRING_OPTIMIZATION
		start = right.start;
		range = right.range;
	#endif

	return *this;
}



String& operator=(const char8 * right);
String& operator=(const char16 * right);
String& operator=(const std::string& right);
String& operator=(const std::wstring& right);
String& operator=(char8 right);
String& operator=(char16 right);
String& operator=(const Char& right);
String& operator=(const ConstChar& right);



// Type conversion operators:

inline operator std::string() const
{
	return std::string(getChar8Array(), getLength());
}



inline operator std::wstring() const
{
	return std::wstring(getChar16Array(), getLength());
}



inline Char operator [](int position)
{
	return Char(*this, position);
}



inline ConstChar operator [](int position) const
{
	return ConstChar(*this, position);
}



String& operator +=(const String& right);
String& operator +=(char8 right);
String& operator +=(char16 right);



inline String& operator +=(const Char& right)
{
	return operator +=(right.operator char16());
}



inline String& operator +=(const ConstChar& right)
{
	return operator +=(right.operator char16());
}
