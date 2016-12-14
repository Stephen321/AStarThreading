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
	void addJob(std::function<void()> job); //using mutex 
	void start();
	void stop();
	void cleanUp(); 
	int getThreadsRunning(); //using mutex
	void incrementThreadsRunning(); //using mutex
	void decrementThreadsRunning(); //using mutex
	bool getCanWork();				//using mutex
	void setCanWork(bool value);	//using mutex

	ThreadPool(ThreadPool const&) = delete;
	void operator=(ThreadPool const&) = delete;
private:
	ThreadPool();
	~ThreadPool();

	SDL_mutex* m_jobsLock;
	SDL_mutex* m_threadsRunningLock;
	bool m_canWork;
	int m_threadsRunning;
	int m_readers;

	int readcount = 0; //(initial value = 0)
	SDL_mutex* m_readerCountLock;
	SDL_mutex* m_attemptReadLock;
	SDL_mutex* m_canWorkLock;

	std::vector<Worker*> m_workers;
	std::queue<std::function<void()>> m_jobs; //queue of function pointers left to do
};

class Worker
{
public:
	Worker(int workerId)
		: m_workerId(workerId)
	{
	}
	~Worker()
	{
		wait();
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
		std::cout << "Thread " << SDL_GetThreadID(m_thread) << " waited with status: " << status << std::endl;
		m_thread = NULL;
	}

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
		}
		ThreadPool::getInstance().decrementThreadsRunning();
		return 0;
	}
private:
	int m_workerId;
	SDL_Thread* m_thread;
};
#endif

