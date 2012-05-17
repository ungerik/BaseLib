/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Thread.h"
#ifndef BL_PLATFORM_WIN32
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



/*
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
*/



void Thread::sleepSeconds(double seconds)
{
	sleep(static_cast<int>(seconds * 1000));
}



void Thread::yield()
{
	sched_yield();
}



void Thread::initialize()
{
	/*
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
	*/
}



Thread::~Thread()
{
	//CloseHandle(completionEvent);
	//CloseHandle(handle);
}



void Thread::start()
{
	//if (state >= COMPLETED)
	//{
	//	BL_ASSERT_NEVER_REACHED // TODO: Funktioniert resume, oder muss neu initialisiert werden?
	//}

	//const DWORD result = ResumeThread(handle);
	//if (result != -1)
	//{
	//	state = STARTED;
	//}
	//else
	//{
	//	resultError(getLastWindowsError() + ERROR_AT);
	//}
}



void Thread::setState(State newState)
{
	//if (newState == COMPLETED)
	//{
	//	BOOL result = SetEvent(completionEvent);
	//	if (result == FALSE)
	//	{
	//		resultError(getLastWindowsError() + ERROR_AT);
	//	}
	//}
	//state = newState;
}



bool Thread::isCurrentThread() const
{
	return true; //GetCurrentThreadId() == id;
}



void Thread::setPriority(int newPriority)
{
	//const BOOL result = SetThreadPriority(handle, newPriority);
	//if (result == FALSE)
	//{
	//	resultError(getLastWindowsError() + ERROR_AT);
	//}
}



int Thread::getPriority() const
{
	//const int result = GetThreadPriority(handle);
	//if (result != THREAD_PRIORITY_ERROR_RETURN)
	//{
	//	return result;
	//}
	//else
	//{
	//	resultError(getLastWindowsError() + ERROR_AT);
	//	return 0;
	//}

	return 0;
}



void Thread::assignToProcessor(int processorIndex)
{
	//SetThreadIdealProcessor(handle, processorIndex);
}



void Thread::join()
{
	//const DWORD result = WaitForSingleObject(completionEvent, INFINITE);
	//if (result != WAIT_FAILED)
	//{
	//	state = JOINED;
	//}
	//else
	//{
	//	resultError(getLastWindowsError() + ERROR_AT);
	//}
}



} // namespace System
} // namespace BaseLib


#endif // #ifndef BL_PLATFORM_WIN32
