/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_VoidMutex_h
#define BaseLib_System_VoidMutex_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace System {



class BL_EXPORT VoidMutex : public NonCopyable {
public:

	inline static bool isThreadSafe()
	{
		return false;
	}

	inline void lock()
	{
	}

	inline void unlock()
	{
	}

	inline bool tryLock()
	{
		return true;
	}

	class ScopedLock {
	public:

		inline ScopedLock(VoidMutex& useVoidMutex)
		{
		}
	};

	class ScopedTryLock {
	public:

		inline ScopedTryLock(VoidMutex& useVoidMutex)
		{
		}

		inline bool isLocked() const
		{
			return true;
		}

	};

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_VoidMutex_h
