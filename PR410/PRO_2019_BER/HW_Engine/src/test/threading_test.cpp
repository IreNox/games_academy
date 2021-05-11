#include "hw/threading/thread.h"
#include "hw/threading/mutex.h"
#include "hw/threading/event.h"
#include "hw/threading/semaphore.h"
#include "hw/threading/read_write_lock.h"

#include <vector>
#include <queue>
#include <iostream>

namespace hw
{
	//////////////////////////////////////////////////////////////////////////
	// Mutex
	struct TestMutexData
	{
		Mutex				mutex;
		std::vector< int >	data;
	};

	uint32 testMutexThread( const Thread& thread )
	{
		TestMutexData* pData = (TestMutexData*)thread.getArgument();

		for( int i = 0u; i < 100000; ++i )
		{
			pData->mutex.lock();
			pData->data.push_back( i );
			pData->mutex.unlock();
		}

		return 0u;
	}

	void testMutex()
	{
		TestMutexData data;
		data.mutex.create();

		Thread thread;
		thread.create( testMutexThread, &data );

		for( int i = 0u; i < 100000; ++i )
		{
			data.mutex.lock();
			data.data.push_back( i );
			data.mutex.unlock();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Event
	struct TestEventData
	{
		Event				threadEvent;
		Mutex				dataMutex;
		std::queue< int >	data;
	};

	uint32 testEventThread( const Thread& thread )
	{
		TestEventData* pData = (TestEventData*)thread.getArgument();

		while( !thread.isQuitRequested() )
		{
			pData->threadEvent.wait();

			pData->dataMutex.lock();
			while( !pData->data.empty() )
			{
				const int i = pData->data.back();
				pData->data.pop();

				std::cout << "I: " << i << std::endl;
			}
			pData->dataMutex.unlock();
		}

		return 0u;
	}

	void testEvent()
	{
		TestEventData data;
		data.threadEvent.create();
		data.dataMutex.create();

		Thread thread;
		thread.create( testEventThread, &data );

		for( int i = 0u; i < 100000; ++i )
		{
			data.dataMutex.lock();
			data.data.push( i );
			data.dataMutex.unlock();

			data.threadEvent.signal();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Semaphore
	struct TestSemaphoreData
	{
		Semaphore			threadSemaphore;
		Mutex				dataMutex;
		std::queue< int >	data;
	};

	uint32 testSemaphoreThread( const Thread& thread )
	{
		TestSemaphoreData* pData = (TestSemaphoreData*)thread.getArgument();

		while( !thread.isQuitRequested() )
		{
			pData->threadSemaphore.decrement();

			pData->dataMutex.lock();
			const int i = pData->data.back();
			pData->data.pop();
			pData->dataMutex.unlock();

			std::cout << "I: " << i << std::endl;
		}

		return 0u;
	}

	void testSemaphore()
	{
		TestSemaphoreData data;
		data.threadSemaphore.create();
		data.dataMutex.create();

		Thread thread;
		thread.create( testEventThread, &data );

		for( int i = 0u; i < 100000; ++i )
		{
			data.dataMutex.lock();
			data.data.push( i );
			data.dataMutex.unlock();

			data.threadSemaphore.increment();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Read Write Lock
	struct TestRedWriteLockData
	{
		ReadWriteLock		lock;
		int					data;
	};

	uint32 testReadWritelockThread( const Thread& thread )
	{
		TestRedWriteLockData* pData = (TestRedWriteLockData*)thread.getArgument();

		while( !thread.isQuitRequested() )
		{
			pData->lock.lockRead();
			std::cout << "Data: " << pData->data << std::endl;
			pData->lock.unlockRead();
		}

		return 0u;
	}

	void testReadWritelock()
	{
		TestRedWriteLockData data;
		data.lock.create();

		Thread thread1;
		thread1.create( testReadWritelockThread, &data );

		Thread thread2;
		thread2.create( testReadWritelockThread, &data );

		for( int i = 0u; i < 100000; ++i )
		{
			data.lock.lockWrite();
			data.data = i;
			data.lock.unlockWrite();
		}
	}
}