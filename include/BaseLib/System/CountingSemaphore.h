/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_CountingSemaphore_h
#define BaseLib_System_CountingSemaphore_h



#include "BaseLib/intern/Windows.h"
#include "BaseLib/Types.h"



namespace BaseLib {
namespace System {



class BL_EXPORT CountingSemaphore : public NonCopyable {
public:

	class ScopedLock {
	public:

		inline ScopedLock(CountingSemaphore& useCountingSemaphore)
			: countingSemaphore(useCountingSemaphore)
		{
			countingSemaphore.aquire();
		}

		inline ~ScopedLock()
		{
			countingSemaphore.release();
		}

	private:
		CountingSemaphore& countingSemaphore;
	};

	class ScopedTryLock {
	public:

		inline ScopedTryLock(CountingSemaphore& useCountingSemaphore)
			: countingSemaphore(useCountingSemaphore)
		{
			locked = countingSemaphore.tryAquire();
		}

		inline ~ScopedTryLock()
		{
			if (locked == true)
			{
				countingSemaphore.release();
			}
		}

		inline bool isLocked() const
		{
			return locked;
		}

	private:
		CountingSemaphore& countingSemaphore;
		bool locked;
	};

	CountingSemaphore(int initialCount = 1, int maxCount = 1000000);
	~CountingSemaphore();

	void aquire();
	bool tryAquire();

	void release();

private:

#ifdef BL_PLATFORM_WIN32
	HANDLE handle;
#else
#endif
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_CountingSemaphore_h
