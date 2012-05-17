/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Process_h
#define BaseLib_System_Process_h



#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;
using BaseLib::Functors::Enumerator;



class BL_EXPORT Process : public BaseLib::Reflection::Object, public NonCopyable {
public:

	static int getId();
	static void enumProcessIds(const Enumerator<int>& enumerator);

	static String getEnvironmentVariable(const String& variableName);
	static void setEnvironmentVariable(const String& variableName, const String& newValue);
	
	static void enumEnviromentVariableNames(const Enumerator<String>& enumerator);
	static void enumEnviromentVariables(const Enumerator<String>& namesEnumerator, const Enumerator<String>& valuesEnumerator);

	static String getCommandLine();

	static bool isDebuggerPresent();

	//static void getProcessors();

	static int getNumaNodeCount();
	static int getProcessorCount(int numaNodeIndex = 0);

	static void assignToProcessor(int processorIndex);

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::Process);

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_Process_h
