/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_InstanceListed_h
#define BaseLib_Utilities_InstanceListed_h



#include "BaseLib/System/RecursiveMutex.h"
#include <set>



namespace BaseLib {
namespace Utilities {



template<class T, bool THREADSAFE = true>
class InstanceListed {
private:

	typedef std::set<T*> Instances;
	typedef typename BaseLib::System::ThreadsafeChooser<THREADSAFE>::RecursiveMutex Mutex;

public:

	typedef typename Instances::iterator Iterator;

	inline static bool isThreadSafe()
	{
		return THREADSAFE;
	}

	inline static int getInstanceCount()
	{
		Mutex::ScopedLock lock(mutex);
		return instances.getCount();
	}

	inline static void lockInstanceList()
	{
		mutex.lock();
	}

	inline static void unlockInstanceList()
	{
		mutex.unlock();
	}

	inline static bool tryLockInstanceList()
	{
		return mutex.tryLock();
	}

	inline static Iterator beginInstances() // Not threadsafe. Use iterators within lockInstanceList() and unlockInstanceList()
	{
		return instances.begin();
	}

	inline static Iterator endInstances() // Not threadsafe. Use iterators within lockInstanceList() and unlockInstanceList()
	{
		return instances.end();
	}

	static void deleteAllInstances()
	{
		Mutex::ScopedLock lock(mutex);
		BL_ASSERT(deletingAllInstances == false);
		deletingAllInstances = true;
		try
		{
			foreach (Iterator, i, instances)
			{
				delete *i;
			}
			instances.clear();
			deletingAllInstances = false;
		}
		catch (...)
		{
			deletingAllInstances = false;
			throw;
		}
	}

	inline InstanceListed()
	{
		Mutex::ScopedLock lock(mutex);
		instances.insert(static_cast<T*>(this));
	}

	inline ~InstanceListed()
	{
		Mutex::ScopedLock lock(mutex);
		if (deletingAllInstances == false)
		{
			instances.erase(static_cast<T*>(this));
		}
	}

private:

	static Instances instances;
	static Mutex mutex;
	static bool deletingAllInstances;
};



template<class T, bool THREADSAFE>
typename InstanceListed<T, THREADSAFE>::Instances InstanceListed<T, THREADSAFE>::instances;



template<class T, bool THREADSAFE>
typename InstanceListed<T, THREADSAFE>::Mutex InstanceListed<T, THREADSAFE>::mutex;



template<class T, bool THREADSAFE>
bool InstanceListed<T, THREADSAFE>::deletingAllInstances = false;



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_InstanceListed_h

