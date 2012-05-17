/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Xml/Sax/Attributes.h"
//#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Xml {
namespace Sax {



enum AttributeArray {
	LOCALNAME_OFFSET = 0,
	PREFIX_OFFSET = 1,
	URI_OFFSET = 2,
	VALUE_OFFSET = 3,
	END_OFFSET = 4,
	ATTRIBUTE_SIZE = 5
};


/*
Attributes::Attributes(const unsigned char** atts)
	: attributes(atts)
	, length(-1)
{
	if (atts != NULL)
	{
		while (attributes[(length+1)*2] != NULL) ++length;
	}
	else
	{
		length = 0;
	}
}
*/



Attributes::Attributes(int count, const unsigned char** atts)
	: attributes(atts)
	, length(count)
{
}



int Attributes::getIndex(const String& qName) const
{
	for (int index = 0; index < length; ++index)
	{
		if (getQName(index) == qName) return index;
	}
	return -1;
}



int Attributes::getIndex(const String& uri, const String& localName) const
{
	return (uri.isEmpty() == true) ? getIndex(localName) : getIndex(uri + ":" + localName);
}



String Attributes::getQName(int index) const
{
	if (index >= 0 && index < length)
	{
		String localName = getLocalName(index);
		const char8* uri = reinterpret_cast<const char8*>(attributes[index*ATTRIBUTE_SIZE + URI_OFFSET]);
		return (uri != NULL) ? String(uri) + ':' + localName : localName;
	}
	else
	{
		return Empty();
	}
}



String Attributes::getLocalName(int index) const
{
	return (index >= 0 && index < length) ? reinterpret_cast<const char8*>(attributes[index*ATTRIBUTE_SIZE + LOCALNAME_OFFSET]) : "";

	/*
	String qName = getQName(index);
	return qName.subString(qName.findFirst(':') + 1);
	*/
}



String Attributes::getURI(int index) const
{
	const char8* uri = reinterpret_cast<const char8*>(attributes[index*ATTRIBUTE_SIZE + URI_OFFSET]);
	return (index >= 0 && index < length && uri != NULL) ? uri : "";

	/*
	String qName = getQName(index);
	int pos = qName.findFirst(':');
	return (pos != -1) ? qName.subString(0, pos) : "";
	*/
}


/*
String Attributes::getType(int index) const
{
}



String Attributes::getType(const String& qName) const
{
}



String Attributes::getType(const String& uri, const String& localName) const
{
	return (uri.isEmpty() == true) ? getType(localName) : getType(uri + ":" + localName);
}
*/



String Attributes::getValue(int index) const
{
	if (index >= 0 && index < length)
	{
		const char8* valueBegin = reinterpret_cast<const char8*>(attributes[index*ATTRIBUTE_SIZE + VALUE_OFFSET]);
		const char8* valueEnd = reinterpret_cast<const char8*>(attributes[index*ATTRIBUTE_SIZE + END_OFFSET]);
		return String(valueBegin, valueEnd);
	}
	else
	{
		return Empty();
	}
}



String Attributes::getValue(const String& qName) const
{
	return getValue(getIndex(qName));
}



String Attributes::getValue(const String& uri, const String& localName) const
{
	return (uri.isEmpty() == true) ? getValue(localName) : getValue(uri + ":" + localName);
}




} // namespace Sax
} // namespace Xml
} // namespace BaseLib
