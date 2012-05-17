/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_ProgramOptions_h
#define BaseLib_System_ProgramOptions_h


#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;
using BaseLib::Containers::Array;
using BaseLib::Containers::StringMap;
using BaseLib::Containers::Enumeration;



class BL_EXPORT ProgramOptions {
public:

	ProgramOptions();

	void parse(const Array<String>& argumentsArray);
	void parse(const String& arguments);
	void parse(int argc, const char * argv[]);
	void parseConfigFile(const String& configFileName);

	inline bool isDefined(const String& name) const
	{
		return options.find(name) != options.end();
	}

	String getValue(const String& name) const;

	inline const Enumeration<String>& optionNames() const
	{
		return optionEnumeration;
	}

private:

	StringMap<> options;
	StringMap<>::KeyEnumeration optionEnumeration;

	void parseKeyAndValue(const String& argument);
};



} // namespace System
} // namespace BaseLib



#endif BaseLib_System_ProgramOptions_h