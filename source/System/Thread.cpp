/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Thread.h"
#include "BaseLib/ErrorHandling.h"


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



RecursiveMutex Thread::atomicFunctionsMutex;



uint32 Thread::threadFunction(void* arguments)
{
	Thread* thread = static_cast<Thread*>(arguments);
	thread->run();
	thread->setState(COMPLETED);
	return 0;
}



BL_DEFINE_REFLECTION_BASE_CLASS(Thread)
{
	registerProperty("id", &Thread::getId);
	registerEnumProperty("state", &Thread::getState);
	registerEnumPropertyValueAndName("state", INVALID, "invalid");
	registerEnumPropertyValueAndName("state", CREATED, "created");
	registerEnumPropertyValueAndName("state", STARTED, "started");
	//registerEnumPropertyValueAndName("state", SUSPENDED, "suspended");
	registerEnumPropertyValueAndName("state", COMPLETED, "completed");
	registerEnumPropertyValueAndName("state", JOINED, "joined");
}



Thread::Thread()
	: Object()
	, name()
	, state(INVALID)
	, runFunctor(NULL)
	, handle(NULL)
	, id(0)
	, completionEvent(NULL)
{
	initialize();
}



Thread::Thread(const RunFunctor& newRunFunctor, const String& name)
	: Object()
	, name()
	, state(INVALID)
	, runFunctor(newRunFunctor.clone())
	, handle(NULL)
	, id(0)
	, completionEvent(NULL)
{
	initialize();
}



void Thread::run()
{
	if (runFunctor != NULL)
	{
		(*runFunctor)();
	}
}



} // namespace System
} // namespace BaseLib
