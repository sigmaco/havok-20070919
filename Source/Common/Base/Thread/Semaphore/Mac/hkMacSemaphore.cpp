/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>
#include <pthread.h>
#include <Common/Base/Fwd/hkcstdio.h>

//#define DEBUG_SEMAPHORE
#ifdef DEBUG_SEMAPHORE
#include <stdio.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#define HK_SEMAPHORE_DEBUG_PRINTF(...) printf( __VA_ARGS__ )
#else
#define HK_SEMAPHORE_DEBUG_PRINTF(...)
#endif

#define CHECK( A ) if( A != 0 ) { perror(#A); HK_BREAKPOINT(0);} else

hkSemaphore::hkSemaphore( int initialCount, int maxCount )
{
	HK_SEMAPHORE_DEBUG_PRINTF("%llu Semaphore: Getting Created\n", hkThread::getMyThreadId());
	
	if (maxCount < 1 || initialCount > maxCount)
	{
		return;
	}

	pthread_mutexattr_t mutex_attr;
	CHECK(pthread_mutexattr_init(&mutex_attr) );
	CHECK( pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT) );
	CHECK( pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE) ); 
	CHECK(pthread_mutex_init(&m_semaphore.mutex, &mutex_attr) );

	pthread_condattr_t cond_attr;
	CHECK( pthread_condattr_init(&cond_attr) );
	CHECK( pthread_cond_init(&m_semaphore.cond, &cond_attr) );

	m_semaphore.curCount = initialCount;
	m_semaphore.maxCount = maxCount;
}

hkSemaphore::~hkSemaphore()
{
	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: Getting Deleted\n", hkThread::getMyThreadId());
	CHECK( pthread_cond_destroy(&m_semaphore.cond));
	CHECK( pthread_mutex_destroy(&m_semaphore.mutex));
	//CHECK( sem_close( m_semaphore ) );
}

void hkSemaphore::acquire()
{
	HK_SEMAPHORE_DEBUG_PRINTF("%llu] Sem: trying to get mutex lock for acquire\n", hkThread::getMyThreadId());

	int ret = pthread_mutex_lock(&m_semaphore.mutex) ;
	if (ret != 0)
		perror("Error getting lock \n");	

	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: got mutex lock\n", hkThread::getMyThreadId());

	while( m_semaphore.curCount <= 0 )
	{
		HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: waiting on cond\n", hkThread::getMyThreadId());

		int ret = pthread_cond_wait( &m_semaphore.cond, &m_semaphore.mutex);
		//an error
		if (ret != 0)
		{
			perror("pthread_cond_wait failed" );
			HK_WARN(0x0, "pthread_cond_wait failed with " << ret);
			CHECK( pthread_mutex_unlock(&m_semaphore.mutex) );
			return;
		}//if					
	}//while

	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: acquired semaphore!\n", hkThread::getMyThreadId(), this);

	m_semaphore.curCount--;

	HK_ASSERT2(0x0, m_semaphore.curCount >= 0, "Illegal semaphore count value.");

	CHECK( pthread_mutex_unlock(&m_semaphore.mutex) );

	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: acquired.\n", hkThread::getMyThreadId());
}

void hkSemaphore::release(int count)
{
	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: getting semaphore lock for release\n", hkThread::getMyThreadId());

	CHECK(	pthread_mutex_lock(&m_semaphore.mutex)	);

	if (m_semaphore.curCount < m_semaphore.maxCount)
	{
		m_semaphore.curCount += count;
		if (m_semaphore.curCount > m_semaphore.maxCount) //Copied from PS3semaphore
		{
			m_semaphore.curCount = m_semaphore.maxCount;
		}	
	}
	else
	{
		HK_WARN(0x0, "Semaphore maxed out");
		CHECK( pthread_mutex_unlock(&m_semaphore.mutex) );
		return;
	}
	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: signaling the release\n", hkThread::getMyThreadId());

	for( int i = 0; i < count; ++i )
	{
		int ret = pthread_cond_signal(&m_semaphore.cond);
		if (ret != 0)
		{
			HK_WARN(0x0, "Pthread cond signal failed" << ret);
			CHECK( pthread_mutex_unlock(&m_semaphore.mutex) );
		}						
	}
	CHECK( pthread_mutex_unlock(&m_semaphore.mutex) ); 
	HK_SEMAPHORE_DEBUG_PRINTF("%llu Sem: released.\n", hkThread::getMyThreadId());
}

void hkSemaphore::acquire(hkSemaphore* semaphore)
{
	semaphore->acquire();
}

		// static function
void hkSemaphore::release(hkSemaphore* semaphore, int count)
{
	semaphore->release(count);
}



/*
* Havok SDK - PUBLIC RELEASE, BUILD(#20070919)
*
* Confidential Information of Havok.  (C) Copyright 1999-2007 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available from salesteam@havok.com.
*
*/
