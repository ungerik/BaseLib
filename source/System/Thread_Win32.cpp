/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Thread.h"
#ifdef BL_PLATFORM_WIN32
#include "BaseLib/ErrorHandling.h"
#include <process.h>


/*
http://opengroup.org/onlinepubs/007908799/xsh/pthread.h.html 
XP: GetNumaNodeProcessorMask()
Vista: GetLogicalProcessorInformation()
MemoryBarrier()
InterlockedExchangePointer()
_aligned_malloc()
http://developer.amd.com/assets/GDC2007_Multicore_JB.pdf
http://developer.amd.com/assets/AMD_Designing_for_N_cores.pdf
http://developer.amd.com/articlex.jsp?id=106
*/



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



void setThreadName(DWORD id, LPCSTR szThreadName)
{
    // Microsoft Visual Studio 2003 and 2005 allow 
    // see: http://msdn2.microsoft.com/en-us/library/xcb2z8hs(vs.80).aspx
    const DWORD MS_VC_EXCEPTION = 0x406D1388u;

    struct THREADNAME_INFO {
        DWORD dwType; // Must be 0x1000.
        LPCSTR szName; // Pointer to name (in user addr space).
        DWORD dwThreadID; // Thread ID (-1=caller thread).
        DWORD dwFlags; // Reserved for future use, must be zero.
    };

    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = szThreadName;
    info.dwThreadID = id;
    info.dwFlags = 0;

    __try
    {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(DWORD), (DWORD*) &info);
    }
    __except(EXCEPTION_CONTINUE_EXECUTION)
    {
    }
}



Thread::LocalStorage::LocalStorage()
	: index(TlsAlloc())
{
	if (index == TLS_OUT_OF_INDEXES)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



Thread::LocalStorage::~LocalStorage()
{
	BOOL result = TlsFree(index);
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



void* Thread::LocalStorage::get() const
{
	return TlsGetValue(index);
}



void Thread::LocalStorage::set(void* pointer)
{
	BOOL result = TlsSetValue(index, pointer);
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



void Thread::sleepSeconds(double seconds)
{
	Sleep(static_cast<int>(seconds * 1000));
}



void Thread::yield()
{
	SwitchToThread();
	// sched_yield();
}



void Thread::initialize()
{
	handle = (HANDLE)_beginthreadex(NULL, 0, threadFunction, this, CREATE_SUSPENDED, &id);
	if (handle != NULL)
	{
		completionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (completionEvent != NULL)
		{
			if (name.isEmpty() == false)
			{
				setThreadName(id, name.getChar8CString());
			}
			state = CREATED;
		}
		else
		{
			resultError(getLastWindowsError() + ERROR_AT);
			state = INVALID;
		}
	}
	else
	{
		resultError("Error while creating thread!" ERROR_AT);
		state = INVALID;
	}
}



Thread::~Thread()
{
	CloseHandle(completionEvent);
	CloseHandle(handle);
}



void Thread::start()
{
	if (state >= COMPLETED)
	{
		BL_ASSERT_NEVER_REACHED // TODO: Funktioniert resume, oder muss neu initialisiert werden?
	}

	const DWORD result = ResumeThread(handle);
	if (result != -1)
	{
		state = STARTED;
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



void Thread::setState(State newState)
{
	if (newState == COMPLETED)
	{
		BOOL result = SetEvent(completionEvent);
		if (result == FALSE)
		{
			resultError(getLastWindowsError() + ERROR_AT);
		}
	}
	state = newState;
}



bool Thread::isCurrentThread() const
{
	return GetCurrentThreadId() == id;
}



void Thread::setPriority(int newPriority)
{
	const BOOL result = SetThreadPriority(handle, newPriority);
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



int Thread::getPriority() const
{
	const int result = GetThreadPriority(handle);
	if (result != THREAD_PRIORITY_ERROR_RETURN)
	{
		return result;
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
		return 0;
	}
}



void Thread::assignToProcessor(int processorIndex)
{
	SetThreadIdealProcessor(handle, processorIndex);
}



void Thread::join()
{
	const DWORD result = WaitForSingleObject(completionEvent, INFINITE);
	if (result != WAIT_FAILED)
	{
		state = JOINED;
	}
	else
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32
