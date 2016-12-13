#include "ThreadPool.h"

ThreadPool::ThreadPool()
	: m_jobsAvailable(SDL_CreateSemaphore(0))
	, m_jobsLock(SDL_CreateMutex())
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
	for (int i = 0; i < WorldConstants::WORKER_COUNT; i++)
	{
		delete m_workers[i];
	}
}

void ThreadPool::addJob(std::function<void()> job)
{
	SDL_LockMutex(m_jobsLock);

	m_jobs.push(job);

	SDL_UnlockMutex(m_jobsLock);

	SDL_SemPost(m_jobsAvailable);
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