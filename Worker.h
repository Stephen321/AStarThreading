#ifndef  WORKER_H
#define WORKER_H
#include "ThreadPool.h"

class Worker
{
public:
	Worker(int workerId);
	~Worker();
	SDL_Thread* getThread() const;
	void start();
	void wait();
	static int worker(void* ptr)
	{
		std::queue<std::function<void()>>& jobs = ThreadPool::getInstance().getJobsQueue();
		ThreadPool& threadPool = ThreadPool::getInstance();
		SDL_mutex* jobsLock = threadPool.getJobsLock();
		threadPool.incrementThreadsRunning();

		while (threadPool.getCanWork())
		{
			//spin while waiting for for jobs to become availble and we can still work
			while (jobs.size() == 0 && threadPool.getCanWork()) {};
			if (threadPool.getCanWork() == false)
			{
				break;
			}

			SDL_LockMutex(jobsLock); //only one thread can read the thread at a time

			std::function<void()> job = 0;
			if (jobs.size() != 0)
			{
				job = jobs.front();
				jobs.pop();
			}

			SDL_UnlockMutex(jobsLock);
			if (job != 0)
			{
				job();
			}
		}
		ThreadPool::getInstance().decrementThreadsRunning();
		return 0;
	}
private:
	int m_workerId;
	SDL_Thread* m_thread;
};
#endif