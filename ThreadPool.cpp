#include "ThreadPool.h"

ThreadPool::ThreadPool()
	: m_jobsAvailable(SDL_CreateSemaphore(0))
	, m_jobsLock(SDL_CreateMutex())
	, m_threadsRunningLock(SDL_CreateMutex())
	, m_canWork(true)
	, m_jobs()
{
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		m_workers.push_back(new Worker(i));
	}
	int aftercreate = 0;
}

ThreadPool::~ThreadPool()
{
	m_canWork = false;
	while (m_threadsRunning != 0)
	{

	}
	for (int i = 0; i < m_workers.size(); i++)
	{
		m_workers[i]->wait();
	}
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		delete m_workers[i];
	}
	SDL_DestroySemaphore(m_jobsAvailable);
	SDL_DestroyMutex(m_jobsLock);
	SDL_DestroyMutex(m_threadsRunningLock);
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

void ThreadPool::addJob(std::function<void()> job)
{
	SDL_LockMutex(m_jobsLock);

	m_jobs.push(job);

	SDL_UnlockMutex(m_jobsLock);

	SDL_SemPost(m_jobsAvailable);
}

void ThreadPool::restart()
{
	m_canWork = false;
	while (m_threadsRunning != 0)
	{

	}
	for (int i = 0; i < m_workers.size(); i++)
	{
		m_workers[i]->wait();
	}
	m_canWork = true;
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		m_workers[i]->start();
	}
}

std::queue<std::function<void()>>& ThreadPool::getJobsQueue()
{
	return m_jobs;
}

SDL_mutex* ThreadPool::getJobsLock()
{
	return m_jobsLock;
}

SDL_sem* ThreadPool::getJobsAvailable()
{
	return m_jobsAvailable;
}

bool & ThreadPool::getCanWork()
{
	return m_canWork;
}
