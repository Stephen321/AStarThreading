#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "SDL_thread.h"
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include "WorldConstants.h"

//class Job
//{
//public:
//	typedef void(*ExecuteFunc)(void*);
//	Job(ExecuteFunc func)
//		: m_func(func)
//	{
//
//	}
//	Job(void* data, ExecuteFunc func)
//		: m_data(data)
//		, m_func(func)
//	{
//
//	}
//	virtual void execute() 
//	{
//		if (m_func == 0)
//			return;
//		m_func(m_data);
//	}
//protected:
//	void* m_data;
//	ExecuteFunc m_func;
//};
//
//class AStarJob : public Job
//{
//public:
//	typedef void(*AStarFunc)(Character*, const Vector2i&, const Vector2i&);
//	AStarJob(Character* _character, const Vector2i& _start, const Vector2i& _end)
//		: Job((ExecuteFunc)&AStar::setCharacterPath)
//		, character(_character)
//		, start(_start)
//		, end(_end)
//	{
//	}
//
//	void execute() override
//	{
//		((AStarFunc)m_func)(character, start, end);
//	}
//private:
//	Character* character;
//	Vector2i start;
//	Vector2i end;
//};

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
	SDL_bool getCanWork();
	void addJob(std::function<void()> job);
	void restart();
	void incrementThreadsRunning();
	void decrementThreadsRunning();
	ThreadPool(ThreadPool const&) = delete;
	void operator=(ThreadPool const&) = delete;
private:
	ThreadPool();
	~ThreadPool();
	SDL_sem * m_jobsAvailable;
	SDL_mutex* m_jobsLock;
	SDL_mutex* m_threadsRunningLock;
	SDL_sem* m_canWorkSem;
	SDL_bool m_canWork;
	int m_threadsRunning;
	std::vector<Worker*> m_workers;
	std::queue<std::function<void()>> m_jobs; //queue of function pointers left to do
};

class Worker
{
public:
	Worker(int workerId)
		: m_workerId(workerId)
	{
		m_thread = SDL_CreateThread(Worker::worker, "t" + m_workerId, (void*)NULL);
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

	void start()
	{
		m_thread = SDL_CreateThread(Worker::worker, "t" + m_workerId, (void*)NULL);
	}

	void wait()
	{
		int status;
		SDL_WaitThread(m_thread, &status);
		m_thread = NULL;
		std::cout << "Thread " << SDL_ThreadID() << " waited with status: " << status << std::endl;
	}

	static int worker(void* ptr)
	{
		std::queue<std::function<void()>>& jobs = ThreadPool::getInstance().getJobsQueue();
		SDL_sem* jobsAvailable = ThreadPool::getInstance().getJobsAvailable();
		SDL_mutex* jobsLock = ThreadPool::getInstance().getJobsLock();
		//bool& canWork = ThreadPool::getInstance().getCanWork();
		ThreadPool::getInstance().incrementThreadsRunning();
		while (true)//ThreadPool::getInstance().getCanWork())
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
		ThreadPool::getInstance().decrementThreadsRunning();

		return 0;
	}
private:
	int m_workerId;
	SDL_Thread* m_thread;
};
#endif

