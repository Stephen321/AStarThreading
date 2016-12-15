#include "Worker.h"

Worker::Worker(int workerId)
	: m_workerId(workerId)
	, m_thread(NULL)
{
}
Worker::~Worker()
{
	wait();
}

SDL_Thread* Worker::getThread() const
{
	return m_thread;
}

void Worker::start()
{
	m_thread = SDL_CreateThread(Worker::worker, "t" + m_workerId, (void*)NULL);
}

void Worker::wait()
{
	if (m_thread == NULL)
		return;
	int status;
	SDL_WaitThread(m_thread, &status);
	m_thread = NULL;
}

