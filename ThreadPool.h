#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "SDL_thread.h"
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include "WorldConstants.h"

class Worker;
class ThreadPool //singleton
{
public:
	static ThreadPool& getInstance()
	{
		static ThreadPool instance;
		return instance;
	}
	std::queue<std::function<void()>>& getJobsQueue();
	SDL_mutex* getJobsLock();
	SDL_sem* getJobsAvailable();
	void addJob(std::function<void()> job);
	ThreadPool(ThreadPool const&) = delete;
	void operator=(ThreadPool const&) = delete;
private:
	ThreadPool();
	~ThreadPool();
	SDL_sem * m_jobsAvailable;
	SDL_mutex* m_jobsLock;
	std::vector<Worker*> m_workers;
	std::queue<std::function<void()>> m_jobs; //queue of function pointers left to do
};

class Worker
{
public:
	Worker(int workerId)
	{
		m_thread = SDL_CreateThread(Worker::worker, "t" + workerId, (void*)NULL);
	}
	~Worker()
	{
		int status = 0;
		//how to destroy threads what loop forever
		//SDL_WaitThread(m_thread, &status);
		std::cout << "Thread destructed with status: " << status << std::endl;
	}

	SDL_Thread* getThread() const
	{
		return m_thread;
	}

	static int worker(void* ptr)
	{
		std::queue<std::function<void()>>& jobs = ThreadPool::getInstance().getJobsQueue();
		SDL_sem* jobsAvailable = ThreadPool::getInstance().getJobsAvailable();
		SDL_mutex* jobsLock = ThreadPool::getInstance().getJobsLock();

		while (true)
		{
			SDL_SemWait(jobsAvailable); //wait until there is a job available


			SDL_LockMutex(jobsLock); //only one thread can read the thread at a time
			
			std::function<void()> job  = 0;
			if (jobs.size() != 0)
			{
				job = jobs.front();
				jobs.pop();
			}

			SDL_UnlockMutex(jobsLock);

			if (job != 0)
			{
				job();
				std::cout << "T " << SDL_ThreadID() << "J"  << std::endl;
			}

			//std::cout << "hi from " << SDL_ThreadID() << std::endl;
		}

		return 0;
	}
private:
	SDL_Thread* m_thread;
};
#endif

