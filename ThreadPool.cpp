#include "ThreadPool.h"

ThreadPool::ThreadPool()
	: m_jobsLock(SDL_CreateMutex())
	, m_threadsRunningLock(SDL_CreateMutex())
	, m_readerCountLock(SDL_CreateMutex())
	, m_attemptReadLock(SDL_CreateMutex())
	, m_canWorkLock(SDL_CreateMutex())
	, m_readers(0)
	, m_jobs()
{
	setCanWork(true);
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		m_workers.push_back(new Worker(i));
		m_workers[i]->start();
	}
	int debug = 0;
}

ThreadPool::~ThreadPool()
{ 
}

void ThreadPool::incrementThreadsRunning()
{
	SDL_LockMutex(m_threadsRunningLock);
	m_threadsRunning++;
	SDL_UnlockMutex(m_threadsRunningLock);
}

void ThreadPool::decrementThreadsRunning()
{
	SDL_LockMutex(m_threadsRunningLock);
	m_threadsRunning--;
	SDL_UnlockMutex(m_threadsRunningLock);
}

int ThreadPool::getThreadsRunning()
{
	int threadsRunning;
	SDL_LockMutex(m_threadsRunningLock);
	threadsRunning = m_threadsRunning;
	SDL_UnlockMutex(m_threadsRunningLock);
	return threadsRunning;
}

void ThreadPool::addJob(std::function<void()> job)
{
	SDL_LockMutex(m_jobsLock);

	m_jobs.push(job);

	SDL_UnlockMutex(m_jobsLock);
}

void ThreadPool::start()
{
	setCanWork(true);
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		m_workers[i]->start();
	}
}

void ThreadPool::stop()
{
	std::cout << "ThreadPool stopping" << std::endl;
	SDL_LockMutex(m_jobsLock);
	std::queue<std::function<void()>>().swap(m_jobs); // clear queue
	SDL_UnlockMutex(m_jobsLock);
	setCanWork(false);
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		m_workers[i]->wait();
	}
	while (getThreadsRunning() != 0) {};
}

void ThreadPool::cleanUp()
{
	std::cout << "ThreadPool clean up " << std::endl;
	//TODO: why is 1 job for each thread still done after this
	SDL_LockMutex(m_jobsLock); 
	std::queue<std::function<void()>>().swap(m_jobs); // clear queue
	SDL_UnlockMutex(m_jobsLock);
	setCanWork(false);
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		delete m_workers[i];
	}

	SDL_DestroyMutex(m_jobsLock);
	SDL_DestroyMutex(m_threadsRunningLock);

	SDL_DestroyMutex(m_readerCountLock);
	SDL_DestroyMutex(m_attemptReadLock);
	SDL_DestroyMutex(m_canWorkLock);
}

std::queue<std::function<void()>>& ThreadPool::getJobsQueue()
{
	return m_jobs;
}

SDL_mutex* ThreadPool::getJobsLock()
{
	return m_jobsLock;
}

bool ThreadPool::getCanWork()
{
	bool b;
	//reader- writer with preference for writer
	SDL_LockMutex(m_attemptReadLock);
	SDL_LockMutex(m_readerCountLock);
	readcount++;
	if (readcount == 1)
		SDL_LockMutex(m_canWorkLock);
	SDL_UnlockMutex(m_readerCountLock);
	SDL_UnlockMutex(m_attemptReadLock);
	b = m_canWork;
		
	SDL_LockMutex(m_readerCountLock);
	readcount--;
	if (readcount == 0)
		SDL_UnlockMutex(m_canWorkLock);
	SDL_UnlockMutex(m_readerCountLock);

	return b;
}

void ThreadPool::setCanWork(bool value)
{
	//reader- writer with preference for writer
	SDL_LockMutex(m_attemptReadLock);

	SDL_LockMutex(m_canWorkLock);
	m_canWork = value;
	SDL_UnlockMutex(m_canWorkLock);

	SDL_UnlockMutex(m_attemptReadLock);
}
