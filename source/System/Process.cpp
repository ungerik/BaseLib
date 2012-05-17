/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Process.h"
#include "BaseLib/ErrorHandling.h"
#ifdef BL_PLATFORM_WIN32
#include "BaseLib/intern/Windows.h"
#include <psapi.h>
#endif


//#include "BaseLib/Console.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;



#ifdef BL_PLATFORM_WIN32



int Process::getId()
{
	return GetCurrentProcessId();
}



void Process::enumProcessIds(const Enumerator<int>& enumerator)
{
	DWORD buffer[1024];
	DWORD bytesReturned;
	const BOOL result = EnumProcesses(buffer, sizeof(buffer), &bytesReturned);
	if (result != FALSE)
	{
		const int count = bytesReturned / sizeof(DWORD);
		for (int i = 0; i < count; ++i)
		{
			enumerator.enumerate(buffer[i]);
		}
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



void Process::setEnvironmentVariable(const String& variableName, const String& newValue)
{
	const BOOL result = SetEnvironmentVariable(variableName.getChar16CString(), newValue.getChar16CString());
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



String Process::getEnvironmentVariable(const String& variableName)
{
	char16 buffer[1024];
	const DWORD length = GetEnvironmentVariable(variableName.getChar16CString(), buffer, 1024);
	return String(buffer, length);
}



void Process::enumEnviromentVariableNames(const Enumerator<String>& enumerator)
{
	LPWCH buffer = GetEnvironmentStrings();
	int end = 0;
	for (int begin = 0; buffer[begin] != '\0'; begin = end)
	{
		while (buffer[end] != '\0')
		{
			++end;
		}
		String string(&buffer[begin], end - begin);
		//Console::trace << string << BaseLib::Streams::newLine;
		const int equalPos = string.findFirst('=');
		enumerator.enumerate(string.subString(0, equalPos));
		++end;
	}
	FreeEnvironmentStrings(buffer);
}



void Process::enumEnviromentVariables(const Enumerator<String>& namesEnumerator, const Enumerator<String>& valuesEnumerator)
{
	LPWCH buffer = GetEnvironmentStrings();
	int end = 0;
	for (int begin = 0; buffer[begin] != '\0'; begin = end)
	{
		while (buffer[end] != '\0')
		{
			++end;
		}
		String string(&buffer[begin], end - begin);
		const int equalPos = string.findFirst('=');
		namesEnumerator.enumerate(string.subString(0, equalPos));
		valuesEnumerator.enumerate(string.subString(equalPos+1));
		++end;
	}
	FreeEnvironmentStrings(buffer);
}



String Process::getCommandLine()
{
	return GetCommandLine();
}



bool Process::isDebuggerPresent()
{
	return IsDebuggerPresent() != FALSE;
}



//void Process::getProcessors() // TODO: Funktioniert nur unter Vista
//{
//	SYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer[256];
//	DWORD byteCount = sizeof(buffer);
//	const BOOL result = GetLogicalProcessorInformation(buffer, &byteCount);
//	if (result != FALSE)
//	{
//		const int count = byteCount / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
//		for (int i = 0; i < count; ++i)
//		{
//			const SYSTEM_LOGICAL_PROCESSOR_INFORMATION& info = buffer[i];
//			int x = 0; 
//		}
//	}
//	else
//	{
//		resultError(getLastWindowsError() + ERROR_AT);
//	}
//}



int Process::getNumaNodeCount()
{
	ULONG count;
	const BOOL result = GetNumaHighestNodeNumber(&count);
	if (result != FALSE)
	{
		return count + 1;
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
		return 0;
	}
}



int Process::getProcessorCount(int numaNodeIndex)
{
	ULONGLONG mask;
	const BOOL result = GetNumaNodeProcessorMask(numaNodeIndex, &mask);
	if (result != FALSE)
	{
		int count = 0;
		for (int i = 0; i < sizeof(ULONGLONG)*8; ++i)
		{
			count += static_cast<int>((mask >> i) & 1);
		}
		return count;
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
		return 0;
	}
}



void Process::assignToProcessor(int processorIndex)
{
	DWORD_PTR mask = 1 << processorIndex;
	const BOOL result = SetProcessAffinityMask(GetCurrentProcess(), mask);
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



#else
#endif



BL_DEFINE_REFLECTION_BASE_CLASS(Process)
{
}



} // namespace System
} // namespace BaseLib
