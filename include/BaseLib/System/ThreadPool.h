/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_ThreadPool_h
#define BaseLib_System_ThreadPool_h



#include "BaseLib/System/Thread.h"
#include "BaseLib/System/RecursiveMutex.h"
#include "BaseLib/Containers/Array.h"
#include <queue>



namespace BaseLib {
namespace System {



using BaseLib::Containers::Array;



/**
Manages a defined thread count.
There are always between minimumThreadCount and maximumThreadCount
threads running. The user of this class cann push jobs into the job-queue via pushJob().
These jobs get poped from the queue by the running threads, that execute the
functor that was passed for the job.
When a job is finished, the threads waits until it can pop a new job from the queue.
If minimumThreadCount < maximumThreadCount then new threads are created when
there are more jobs waiting in the queue than threads are available.
If there are more jobs in the queue than maximumThreadCount, then they have
to wait for thread to finish its former job.
*/
class BL_EXPORT ThreadPool : public NonCopyable {
public:
	
	ThreadPool(int minThreadCount = 0, int maxThreadCount = 8);

	~ThreadPool();

	inline int getMinimumThreadCount() const
	{
		RecursiveMutex::ScopedLock workingJobsCountLock(workingJobsCountMutex);
		return minimumThreadCount;
	}
	void setMinimumThreadCount(int newMinimumThreadCount);

	inline int getMaximumThreadCount() const
	{
		RecursiveMutex::ScopedLock workingJobsCountLock(workingJobsCountMutex);
		return maximumThreadCount;
	}
	void setMaximumThreadCount(int newMaximumThreadCount);

	inline bool isJobPoolEmpty() const
	{
		RecursiveMutex::ScopedLock lock(jobQueueMutex);
		return jobQueue.empty();
	}

	inline int getWorkingJobsCount() const
	{
		RecursiveMutex::ScopedLock lock(workingJobsCountMutex);
		return workingJobsCount;
	}

	void pushJob(const Thread::RunFunctor& jobFunctor);



    //void joinAll();

private:

	friend class WorkerThread;

	class WorkerThread : public Thread {
	public:

		WorkerThread(ThreadPool& forThreadPool);
		virtual ~WorkerThread();

	protected:
		virtual void run();

	private:
		ThreadPool& threadPool;
		bool running;
	};

	int minimumThreadCount;
	int maximumThreadCount;
	typedef Array<Thread*> Threads;
	Threads threads;
	mutable RecursiveMutex threadsMutex;
	typedef std::queue<Thread::RunFunctor*> JobQueue;
	JobQueue jobQueue;
	mutable RecursiveMutex jobQueueMutex;
	int workingJobsCount;
	mutable RecursiveMutex workingJobsCountMutex;

	Thread::RunFunctor* popJob();

	void createAndStartWorkerThread();
	void stopAndDestroyWorkerThread(WorkerThread* workerThread);
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_ThreadPool_h
