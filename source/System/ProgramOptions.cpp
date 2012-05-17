/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/ProgramOptions.h"
#include "BaseLib/Files/ConfigFile.h"
#include "BaseLib/Strings/StringTokenizer.h"
//#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Functors/Adder.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::Functors;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Files;
using namespace BaseLib::Strings;



ProgramOptions::ProgramOptions()
	: options()
	, optionEnumeration(&options)
{
}



void ProgramOptions::parseKeyAndValue(const String& argument)
{
	int equalIndex = argument.findFirst('=');
	String key = argument.subString(0, equalIndex);
	String value = equalIndex != String::END ? argument.subString(equalIndex+1) : "";
	options[key] = value;
}



void ProgramOptions::parse(const Array<String>& argumentsArray)
{
	int argumentCount = argumentsArray.getCount();
	for (int i = 0; i < argumentCount; ++i)
	{
		const String argument = argumentsArray[i];
		if (argument.beginsWith("--") == true)
		{
			parseKeyAndValue(argument.subString(2));
		}
		else if (argument.beginsWith('/') == true)
		{
			parseKeyAndValue(argument.subString(1));
		}
		else if (argument.beginsWith('-') == true)
		{
			for (int i = 1; i < argument.getLength(); ++i)
			{
				options[String(argument[i])] = Empty();
			}
		}
		else
		{
			parseKeyAndValue(argument);
		}
	}
}



void ProgramOptions::parse(const String& arguments)
{
	Array<String> argumentsArray;
	StringTokenizer(arguments).tokenizeTo<Adder>(argumentsArray);
}



void ProgramOptions::parse(int argc, const char * argv[])
{
	Array<String> argumentsArray(argc-1);
	for (int i = 1; i < argc; ++i)
	{
		argumentsArray[i] = argv[i];
	}
	parse(argumentsArray);
}



void ProgramOptions::parseConfigFile(const String& configFileName)
{
	ConfigFile configFile(configFileName);
	configFile.getEntryCount();
	foreach (Enumeration<String>::Iterator, i, configFile.getKeys())
	{
		options[*i] = configFile.getEntry(*i);
	}
}



String ProgramOptions::getValue(const String& name) const
{
	StringMap<>::ConstIterator i = options.find(name);
	if (i != options.end())
	{
		return i->second;
	}
	else
	{
		argumentError("No option with name '" + name + "' found!" ERROR_AT);
		return Empty();
	}
}



} // namespace System
} // namespace BaseLib
