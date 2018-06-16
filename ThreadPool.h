#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "SDL_thread.h"
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include "Debug.h"
#include "WorldConstants.h"

class Worker;
class ThreadPool //singleton
{
public:
	static ThreadPool& getInstance()
	{
		static ThreadPool instance; //thread safe since c++11
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

	SDL_mutex* m_readerCountLock;
	SDL_mutex* m_attemptReadLock;
	SDL_mutex* m_canWorkLock;

	std::vector<Worker*> m_workers;
	std::queue<std::function<void()>> m_jobs; //queue of function pointers left to do
};
#include "Worker.h"
#endif

