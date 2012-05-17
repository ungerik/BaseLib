/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Strings {



String::~String()
{
	implementation->releaseReference();
}



String::String(StringEncoding stringEncoding, int length)
	: implementation(AbstractStringImplementation::create(stringEncoding, length))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(length)
#endif
{
}



String::String(StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(0)
#endif
{
}



String::String(Empty)
	: implementation(AbstractStringImplementation::create(getDefaultEncoding()))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(0)
#endif
{
}



String::String(int length)
	: implementation(AbstractStringImplementation::create(length))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(length)
#endif
{
}



String::String(AbstractStringImplementation* stringImplementation)
	: implementation(stringImplementation)
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(stringImplementation->getLength())
#endif
{
}



#ifndef NO_SUBSTRING_OPTIMIZATION
String::String(AbstractStringImplementation* stringImplementation, int subStringStart, int subStringRange)
	: implementation(stringImplementation)
	, start(subStringStart)
	, range(subStringRange)
{
}
#endif



String::String(const char8 * source, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, zeroTerminatedStringLength(source)))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(implementation->getLength())
#endif
{
	copyFromCharArray(source, 0, getLength());
}



String::String(const char16 * source, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, zeroTerminatedStringLength(source)))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(implementation->getLength())
#endif
{
	copyFromCharArray(source, 0, getLength());
}



String::String(const char8 * source, int length, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, length))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(length)
#endif
{
	copyFromCharArray(source, 0, length);
}



String::String(const char16 * source, int length, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, length))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(length)
#endif
{
	copyFromCharArray(source, 0, length);
}



String::String(const std::string& source, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, (int)source.size()))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(source.size())
#endif
{
	copyFromCharArray(source.data(), 0, source.size());
}



String::String(const std::wstring& source, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, (int)source.size()))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(source.size())
#endif
{
	copyFromCharArray(source.data(), 0, source.size());
}



String::String(char8 character, int count, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, count))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(count)
#endif
{
	fill(character, 0, count);
}



String::String(char16 character, int count, StringEncoding stringEncoding)
	: implementation(AbstractStringImplementation::create(stringEncoding, count))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(count)
#endif
{
	fill(character, 0, count);
}



String::String(const Char& character, int count)
	: implementation(AbstractStringImplementation::create(character.getString().getEncoding(), count))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(count)
#endif
{
	if (getEncoding() == CHAR8_ENCODING)
	{
		fill(character.operator char8(), 0, count);
	}
	else
	{
		fill(character.operator char16(), 0, count);
	}
}



String::String(const ConstChar& character, int count)
	: implementation(AbstractStringImplementation::create(character.getString().getEncoding(), count))
#ifndef NO_SUBSTRING_OPTIMIZATION
	, start(0)
	, range(count)
#endif
{
	if (getEncoding() == CHAR8_ENCODING)
	{
		fill(character.operator char8(), 0, count);
	}
	else
	{
		fill(character.operator char16(), 0, count);
	}
}


} // namespace Strings
} // namespace BaseLib

