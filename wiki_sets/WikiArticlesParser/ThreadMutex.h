/* -------------------------------------------------------------------------- */
// ThreadMutex.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _THREAD_MUTEX_
#define _THREAD_MUTEX_

#include <pthread.h>

class ThreadMutex
{
	public:
		/* Constructor. */
		ThreadMutex()
		{
			this->internalMutex = new pthread_mutex_t();
		}

		/* Destructor. */
		~ThreadMutex()
		{
			this->Unlock();
			delete this->internalMutex;
		}

		/* Take control of the mutex. */
		int Lock() const
		{
			return pthread_mutex_lock(this->internalMutex);
		}

		/* Free the mutex. */
		int Unlock() const
		{
			return pthread_mutex_unlock(this->internalMutex);
		}

	private:
		pthread_mutex_t *internalMutex;

		/* Allocation and copy constructor are private to prevent errors. */
		ThreadMutex(const ThreadMutex &threadMutex);
		ThreadMutex& operator=(const ThreadMutex &threadMutex);
};

#endif
