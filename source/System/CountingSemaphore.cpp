/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/CountingSemaphore.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



#ifdef BL_PLATFORM_WIN32



CountingSemaphore::CountingSemaphore(int initialCount, int maxCount)
	: handle(CreateSemaphore(NULL, initialCount, maxCount, NULL))
{
	if (handle == NULL)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



CountingSemaphore::~CountingSemaphore()
{
	CloseHandle(handle);
}



void CountingSemaphore::aquire()
{
	DWORD result = WaitForSingleObject(handle, INFINITE);
	if (result == WAIT_FAILED)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



bool CountingSemaphore::tryAquire()
{
	DWORD result = WaitForSingleObject(handle, 0);
	if (result == WAIT_OBJECT_0)
	{
		return true;
	}
	else if (result == WAIT_FAILED)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
	return false;
}



void CountingSemaphore::release()
{
	BOOL result = ReleaseSemaphore(handle, 1, NULL);
	if (result == FALSE)
	{
		resultError(getLastWindowsError() + ERROR_AT);
	}
}



#else
#endif



} // namespace System
} // namespace BaseLib
