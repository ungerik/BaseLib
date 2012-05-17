/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/ConfigFile.h"
#include "BaseLib/Files/ConfigFileTreeIterator.h"
#include "BaseLib/Files/LocalFile.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Streams/BufferedBinaryInputStream.h"
#include "BaseLib/Streams/BufferedBinaryOutputStream.h"
#include "BaseLib/Streams/TextInputStream.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {


using namespace BaseLib::Buffers;
using namespace BaseLib::Streams;
using namespace BaseLib::ErrorHandling;



ConfigFile::ConfigFile()
	: entryMap()
	, keyEnumeration(&entryMap)
{
}



ConfigFile::ConfigFile(const String& fileName)
	: entryMap()
	, keyEnumeration(&entryMap)
{
	parse(fileName);
}



ConfigFile::ConfigFile(InputStream& inputStream)
	: entryMap()
	, keyEnumeration(&entryMap)
{
	parse(inputStream);
}



void ConfigFile::parse(const String& fileName)
{
	BinaryFileBuffer fileBuffer(fileName, true, false);
	/*Buffered*/BinaryInputStream inputStream(fileBuffer);
	parse(inputStream);
}



void ConfigFile::parse(InputStream& inputStream)
{
	TextInputStream textInputStream(inputStream);
	textInputStream.setReadStringMethod(TextInputStream::READ_LINE);

	while (textInputStream.isInputAvailable() == true)
	{
		String line;
		textInputStream >> line;
		line.trimFrontAndTail();
		if (line.isEmpty() == false)
		{
			if (line.beginsWith('#') == false && line.beginsWith(';') == false && line.beginsWith("//") == false)
			{
				const int pos = line.findLast('=');
				if (pos != String::END)
				{
					bool append = false;
					String key = line.subString(0, pos);
					if (key.endsWith('+') == true)
					{
						key.trimTailBy(1);
						append = true;
					}
					String value = line.subString(pos+1);

					key.trimTail();
					value.trimFront();

					if (append == true)
					{
						appendEntry(key, value);
					}
					else
					{
						setEntry(key, value);
					}
				}
				else
				{
					ioError("Error while parsing config-file", "BaseLib::ConfigFile::parse()");
				}
			}
			else
			{
				///ToDo: memorize comments
			}
		}
	}
}



void ConfigFile::save(const String& fileName, BinaryStreamEncoding::StringEncoding stringEncoding) const
{
	LocalFile::removeIfExists(fileName);
	BinaryFileBuffer fileBuffer(fileName, false, true);
	BufferedBinaryOutputStream outputStream(fileBuffer);
	outputStream.setStringEncoding(stringEncoding);
	save(outputStream);
	outputStream.flush();
}



void ConfigFile::save(OutputStream& outputStream) const
{
	for (StringMap<>::ConstIterator i = entryMap.begin(); i != entryMap.end(); ++i)
	{
		outputStream << i->first << "=" << i->second << newLine;
	}
}



ConfigFileTreeIterator* ConfigFile::createTreeIterator()
{
	return new ConfigFileTreeIterator(this);
}



const ConfigFileTreeIterator* ConfigFile::createTreeIterator() const
{
	return new ConfigFileTreeIterator(this);
}



void ConfigFile::applyToReflectionObject(BaseLib::Reflection::Object& reflectionObject)
{
	foreach (StringMap<>::Iterator, i, entryMap)
	{
		reflectionObject.setProperty(i->first, i->second);
	}
}



} // namespace Files
} // namespace BaseLib
