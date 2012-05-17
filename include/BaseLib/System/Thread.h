/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Thread_h
#define BaseLib_System_Thread_h



#include "BaseLib/Utilities/AutoPointer.h"
#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Reflection/Object.h"
#include "BaseLib/System/RecursiveMutex.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {



using BaseLib::Utilities::AutoPointer;
using BaseLib::Functors::Functor0;
using BaseLib::Functors::FunctionFunctor0;
using BaseLib::Functors::MethodFunctor0;
using BaseLib::Strings::String;



class BL_EXPORT Thread : public BaseLib::Reflection::Object, public NonCopyable {
public:

	class LocalStorage {
	public:
		LocalStorage();
		~LocalStorage();

		void* get() const;
		void set(void* pointer);

	private:
		#ifdef BL_PLATFORM_WIN32
			DWORD index;
		#else
			pthread_key_t key;
		#endif
	};

	typedef Functor0<void> RunFunctor;
	typedef FunctionFunctor0<void> FunctionRunFunctor;
	template<class C>
	struct MethodRunFunctor : MethodFunctor0<C, void> {
		MethodRunFunctor<C>(C* atObject, Method forMethod)
			: MethodFunctor0<C, void>(atObject, forMethod)
		{
		}
	};

	enum State {
		INVALID,
		CREATED,
		STARTED,
		//SUSPENDED,
		COMPLETED,
		JOINED
	};
	
    static void sleepSeconds(double seconds);
    static void yield();

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::Thread);

protected:

	Thread();

public:

    explicit Thread(const RunFunctor& newRunFunctor, const String& name = Empty());

	virtual ~Thread();

	const String& getName() const
	{
		return name;
	}

	void start();

	bool isCurrentThread() const;

	void setPriority(int newPriority);
	int getPriority() const;

	void assignToProcessor(int processorIndex);

	inline State getState() const
	{
		return state;
	}

    inline bool operator ==(const Thread& other) const
	{
		return id == other.getId();
	}
    inline bool operator !=(const Thread& other) const
	{
		return !operator ==(other);
	}

	inline int getId() const
	{
		return id;
	}

    void join();

	inline static int32 atomicIncrement(volatile int32& value)
	{
		#ifdef BL_PLATFORM_WIN32
			return InterlockedIncrement((volatile LONG*) &value);
		#else
			BL_STATIC_ASSERT_NOT_IMPLEMENTED
		#endif
	}

	inline static int64 atomicIncrement(volatile int64& value)
	{
		#ifdef BL_PLATFORM_WIN32
			#if WINVER >= 0x0502
				return InterlockedIncrement64((volatile LONGLONG*) &value);
			#else
				RecursiveMutex::ScopedLock lock(atomicFunctionsMutex);
				return ++value;
			#endif
		#else
			BL_STATIC_ASSERT_NOT_IMPLEMENTED
		#endif
	}

	inline static int32 atomicDecrement(volatile int32& value)
	{
		#ifdef BL_PLATFORM_WIN32
			return InterlockedDecrement((volatile LONG*) &value);
		#else
			BL_STATIC_ASSERT_NOT_IMPLEMENTED
		#endif
	}

	inline static int64 atomicDecrement(volatile int64& value)
	{
		#ifdef BL_PLATFORM_WIN32
			#if WINVER >= 0x0502
				return InterlockedDecrement64((volatile LONGLONG*) &value);
			#else
				RecursiveMutex::ScopedLock lock(atomicFunctionsMutex);
				return --value;
			#endif
		#else
			BL_STATIC_ASSERT_NOT_IMPLEMENTED
		#endif
	}

protected:

	virtual void run();

private:

	static RecursiveMutex atomicFunctionsMutex;

	AutoPointer<RunFunctor> runFunctor;
	State state;
	String name;

#ifdef BL_PLATFORM_WIN32
	HANDLE handle;
	uint32 id;
	HANDLE completionEvent;

	static uint32 __stdcall threadFunction(void* arguments);

	void setState(State newState);

	void initialize();

	void setName(const String& newName);
#else
	pthread_t id;
#endif

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_Thread_h
