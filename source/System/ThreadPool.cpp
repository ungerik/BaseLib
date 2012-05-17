/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/ThreadPool.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



ThreadPool::ThreadPool(int minThreadCount, int maxThreadCount)
	: minimumThreadCount(minThreadCount)
	, maximumThreadCount(maxThreadCount)
	, threads()
	, threadsMutex()
	, jobQueue()
	, jobQueueMutex()
	, workingJobsCount(0)
	, workingJobsCountMutex()
{
	if (checkArgumentPositive(NAME_VALUE(minThreadCount)) == true &&
		checkArgumentMin(NAME_VALUE(maxThreadCount), minThreadCount) == true)
	{
		for (int i = 0; i < minThreadCount; ++i)
		{
			createAndStartWorkerThread();
		}
	}
}



ThreadPool::~ThreadPool()
{
	const int count = threads.getCount();
	for (int i = 0; i < count; ++i)
	{
		delete threads[i];
	}
}



void ThreadPool::createAndStartWorkerThread()
{
	RecursiveMutex::ScopedLock lock(threadsMutex);
	WorkerThread* workerThread = new WorkerThread(*this);
	threads += workerThread;
	workerThread->start();
}



void ThreadPool::stopAndDestroyWorkerThread(WorkerThread* workerThread)
{
	BL_ASSERT(workerThread != NULL);
	RecursiveMutex::ScopedLock lock(threadsMutex);
	threads.removeFirst(workerThread);
	delete workerThread;
}



void ThreadPool::setMinimumThreadCount(int newMinimumThreadCount)
{
	if (checkArgumentPositive(NAME_VALUE(newMinimumThreadCount)) == true &&
		checkArgumentMax(NAME_VALUE(newMinimumThreadCount), maximumThreadCount))
	{
		RecursiveMutex::ScopedLock workingJobsCountLock(workingJobsCountMutex);
		minimumThreadCount = newMinimumThreadCount;

		const int count = minimumThreadCount - threads.getCount();
		for (int i = 0; i < count; ++i)
		{
			createAndStartWorkerThread();
		}
	}
}



void ThreadPool::setMaximumThreadCount(int newMaximumThreadCount)
{
	if (checkArgumentMin(NAME_VALUE(newMaximumThreadCount), minimumThreadCount))
	{
		RecursiveMutex::ScopedLock workingJobsCountLock(workingJobsCountMutex);
		maximumThreadCount = newMaximumThreadCount;
	}
}



void ThreadPool::pushJob(const Thread::RunFunctor& jobFunctor)
{
	RecursiveMutex::ScopedLock jobQueueLock(jobQueueMutex);
	RecursiveMutex::ScopedLock workingJobsCountLock(workingJobsCountMutex);

	jobQueue.push(jobFunctor.clone());

	if (workingJobsCount < maximumThreadCount)
	{
		createAndStartWorkerThread();
	}
}



Thread::RunFunctor* ThreadPool::popJob()
{
	RecursiveMutex::ScopedLock jobQueueLock(jobQueueMutex);
	if (jobQueue.empty() == false)
	{
		Thread::RunFunctor* jobFunctor = jobQueue.front();
		jobQueue.pop();
		return jobFunctor;
	}
	else
	{
		return NULL;
	}
}



///////////////////////////////////////////////////////////////////////////////



ThreadPool::WorkerThread::WorkerThread(ThreadPool& forThreadPool)
	: threadPool(forThreadPool)
	, running(true)
{
}



ThreadPool::WorkerThread::~WorkerThread()
{
	running = false;
	join();
}



void ThreadPool::WorkerThread::run()
{
	do
	{
		Thread::RunFunctor* jobFunctor = threadPool.popJob();
		if (jobFunctor != NULL)
		{
			{
				RecursiveMutex::ScopedLock lock(threadPool.workingJobsCountMutex);
				++threadPool.workingJobsCount;
			}

			(*jobFunctor)();

			{
				RecursiveMutex::ScopedLock lock(threadPool.workingJobsCountMutex);
				--threadPool.workingJobsCount;

				if (threadPool.workingJobsCount > threadPool.maximumThreadCount)
				{
					threadPool.stopAndDestroyWorkerThread(this);
				}
			}
		}
		else
		{
			Thread::yield();
		}
	}
	while (running == true);
}



} // namespace System
} // namespace BaseLib
