/* -------------------------------------------------------------------------- */
// ThreadLocking.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _THREAD_LOCKING_
#define _THREAD_LOCKING_

#include "ThreadMutex.h"

/* Automatically locks and unlocks a mutex when creating an instance 
 * of this class and destroying it. */
class ThreadLocking
{
	public:
		/* Constructor
		 * mutex: ThreadMutex to lock. */
		ThreadLocking(const ThreadMutex &mutex)
		{
			this->mutex = &mutex;
			this->mutex->Lock();
		}

		/* Destructor */
		~ThreadLocking()
		{
			this->mutex->Unlock();
		}

	private:
		const ThreadMutex* mutex;

		/* Allocation and copy constructor are private to prevent errors. */
		ThreadLocking(const ThreadLocking &threadLocking);
		ThreadLocking& operator=(const ThreadLocking &threadLocking);
};

#endif
