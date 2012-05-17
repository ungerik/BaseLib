/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/System/RecursiveMutex.h



#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {



class BL_EXPORT RecursiveMutex : public NonCopyable {
public:

	inline static bool isThreadSafe()
	{
		return true;
	}

	inline void lock()
	{
		BL_STATIC_ASSERT_NOT_IMPLEMENTED
	}

	inline void unlock()
	{
		BL_STATIC_ASSERT_NOT_IMPLEMENTED
	}

	inline bool tryLock()
	{
		BL_STATIC_ASSERT_NOT_IMPLEMENTED
	}

	class ScopedLock {
	public:

		inline ScopedLock(RecursiveMutex& useRecursiveMutex)
			: recursiveMutex(useRecursiveMutex)
		{
			recursiveMutex.lock();
		}

		inline ~ScopedLock()
		{
			recursiveMutex.unlock();
		}

	private:

		RecursiveMutex& recursiveMutex;

	};

	class ScopedTryLock {
	public:

		inline ScopedTryLock(RecursiveMutex& useRecursiveMutex)
			: recursiveMutex(useRecursiveMutex)
		{
			locked = recursiveMutex.tryLock();
		}

		inline ~ScopedTryLock()
		{
			if (locked == true)
			{
				recursiveMutex.unlock();
			}
		}

		inline bool isLocked() const
		{
			return locked;
		}

	private:

		RecursiveMutex& recursiveMutex;
		bool locked;

	};

	RecursiveMutex();
	~RecursiveMutex();

private:

	BL_STATIC_ASSERT_NOT_IMPLEMENTED

};



} // namespace System
} // namespace BaseLib