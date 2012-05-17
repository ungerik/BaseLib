/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



~String();



explicit String(StringEncoding stringEncoding, int length);
explicit String(StringEncoding stringEncoding = getDefaultEncoding());
String(Empty);
explicit String(int length);
String(AbstractStringImplementation* stringImplementation);
#ifndef NO_SUBSTRING_OPTIMIZATION
	String(AbstractStringImplementation* stringImplementation, int subStringStart, int subStringRange);
#endif
String(const char8 * source, StringEncoding stringEncoding = CHAR8_ENCODING);
String(const char16 * source, StringEncoding stringEncoding = CHAR16_ENCODING);
String(const char8 * source, int length, StringEncoding stringEncoding = CHAR8_ENCODING);
String(const char16 * source, int length, StringEncoding stringEncoding = CHAR16_ENCODING);
String(const std::string& source, StringEncoding stringEncoding = CHAR8_ENCODING);
String(const std::wstring& source, StringEncoding stringEncoding = CHAR16_ENCODING);
String(char8 character, int count = 1, StringEncoding stringEncoding = CHAR8_ENCODING);
String(char16 character, int count = 1, StringEncoding stringEncoding = CHAR16_ENCODING);
String(const Char& character, int count = 1);
String(const ConstChar& character, int count = 1);



template<class SourceIterator>
String(const SourceIterator& beginIterator, const SourceIterator& endIterator, StringEncoding stringEncoding = getDefaultEncoding())
	: implementation(AbstractStringImplementation::create(stringEncoding, false))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(0)
#endif
{	
	int currentSize = 0;
	for (SourceIterator i = beginIterator; i != endIterator; ++i)
	{
		++currentSize;
		if (implementation->getLength() < currentSize) implementation->setLength(currentSize);
		implementation->setChar(currentSize-1, *i);
	}
	if (implementation->getLength() != currentSize) implementation->setLength(currentSize);
	#ifndef NO_SUBSTRING_OPTIMIZATION
		range = currentSize;
	#endif
}



inline String(const String& source)
	: implementation(const_cast<AbstractStringImplementation*>(source.getImplementation()))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(source.start)
	, range(source.range)
#endif
{
	implementation->addReference();
}

