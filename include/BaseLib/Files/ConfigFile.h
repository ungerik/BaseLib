/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_ConfigFile_h
#define BaseLib_ConfigFile_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Common.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Streams/BinaryStreamEncoding.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Trees/AbstractTreeIterator.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::Streams::BinaryStreamEncoding;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using BaseLib::Containers::StringMap;
using BaseLib::Containers::Enumeration;
using BaseLib::Containers::Stack;



class ConfigFileTreeIterator;



class BL_EXPORT ConfigFile {
public:

	typedef StringMap<>::KeyEnumeration KeyEnumeration;

	ConfigFile();
	ConfigFile(const String& fileName);
	ConfigFile(InputStream& inputStream);

	void parse(const String& fileName);
	void parse(InputStream& inputStream);

	inline bool isEmpty() const
	{
		return entryMap.empty();
	}

	inline int getEntryCount() const
	{
		return static_cast<int>(entryMap.size());
	}

	inline bool hasKey(const String& key) const
	{
		return entryMap.find(key) != entryMap.end();
	}

	inline String getEntry(const String& key) const
	{
		StringMap<>::const_iterator i = entryMap.find(key);
		return (i != entryMap.end()) ? i->second : "";
	}

	inline void setEntry(const String& key, const String& value)
	{
		entryMap[key] = value;
	}

	inline void appendEntry(const String& key, const String& value)
	{
		StringMap<>::iterator i = entryMap.find(key);
		setEntry(key, (i != entryMap.end()) ? i->second + value : value);
	}

	inline bool removeEntry(const String& key)
	{
		return entryMap.erase(key) > 0;
	}

	void save(OutputStream& outputStream) const;
	void save(const String& fileName, BinaryStreamEncoding::StringEncoding stringEncoding = BinaryStreamEncoding::CHAR8) const;

	inline const KeyEnumeration& getKeys() const
	{
		return keyEnumeration;
	}

	ConfigFileTreeIterator* createTreeIterator();
	const ConfigFileTreeIterator* createTreeIterator() const;

	void applyToReflectionObject(BaseLib::Reflection::Object& reflectionObject);

	inline void clear()
	{
		entryMap.clear();
	}

protected:
	
	StringMap<> entryMap;
	KeyEnumeration keyEnumeration;
};



inline InputStream& operator>>(InputStream& inputStream, ConfigFile& destination)
{
	destination.parse(inputStream);
	return inputStream;
}



inline OutputStream& operator<<(OutputStream& outputStream, const ConfigFile& source)
{
	source.save(outputStream);
	return outputStream;
}



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_ConfigFile_h
