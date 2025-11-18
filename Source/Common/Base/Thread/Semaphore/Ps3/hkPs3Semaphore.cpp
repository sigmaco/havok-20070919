/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>

#if (HK_CONFIG_THREAD==HK_CONFIG_MULTI_THREADED)

// Use system sync primitives as we want to signal waiting PPU threads
// when ready etc. If we use libatomic then they busy wait etc
#include <sys/synchronization.h>

//#define DEBUG_SEMAPHORE
#ifdef DEBUG_SEMAPHORE
#include <stdio.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#define HK_SEMAPHORE_DEBUG_PRINTF(...) printf( __VA_ARGS__ )
#else
#define HK_SEMAPHORE_DEBUG_PRINTF(...)
#endif

#define NO_TIMEOUT  0

hkSemaphore::hkSemaphore( int initialCount, int maxCount )
{
	if (maxCount < 1 || initialCount > maxCount) 
	{
		return;
	}
	
	/* Create the mutex */
	sys_mutex_attribute_t mutex_attr;
	sys_mutex_attribute_initialize(mutex_attr);
	mutex_attr.attr_protocol = SYS_SYNC_PRIORITY; 
	int ret = sys_mutex_create(&m_semaphore.mutex, &mutex_attr);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0, "sys_mutex_create failed with " << ret);
		return;
	}

	/* Create the condition variable associated with the mutex*/
	sys_cond_attribute_t cond_attr;
	sys_cond_attribute_initialize(cond_attr);
	ret = sys_cond_create(&m_semaphore.cond, m_semaphore.mutex, &cond_attr);
	if (ret != CELL_OK) 
	{
		sys_mutex_destroy(m_semaphore.mutex);
		HK_WARN(0x0, "sys_cond_create failed with " << ret);
		return;
	}

	/* Initialize counting variables */
	m_semaphore.curCount = initialCount;
	m_semaphore.maxCount = maxCount;
}


hkSemaphore::~hkSemaphore()
{
	int ret = sys_cond_destroy(m_semaphore.cond);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_cond_destroy failed with " << ret);
	}

	ret = sys_mutex_destroy(m_semaphore.mutex);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_destroy failed with " << ret);
	}
}

void hkSemaphore::acquire()
{
	int ret;

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: trying to get mutex lock for acquire\n", hkThread::getThreadId(), this);

	/* Mutual exclusion is required before touching cur_count */
	ret = sys_mutex_lock(m_semaphore.mutex, NO_TIMEOUT);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_lock failed with " << ret);
		return;
	}

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: got mutex lock\n", hkThread::getThreadId(), this);

	/* If cur_count is equal to or less than 0, wait until someone signals */
	while (m_semaphore.curCount <= 0) 
	{
		HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: waiting on cond\n", hkThread::getThreadId(), this);
		ret = sys_cond_wait(m_semaphore.cond, NO_TIMEOUT);

		if (ret != CELL_OK) 
		{
			HK_WARN(0x0,"sys_cond_wait failed with " << ret);
			int ret2 = sys_mutex_unlock(m_semaphore.mutex);
			if (ret2 != CELL_OK) 
			{
				HK_WARN(0x0,"sys_mutex_unlock failed with " << ret2);
			}
			return;
		}
	} 

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: got semaphore!\n", hkThread::getThreadId(), this);

	/* Decrement cur_count */
	m_semaphore.curCount--;

	HK_ASSERT2(0x0, m_semaphore.curCount >= 0, "Illegal semaphore count value.");

	/* End of the critical section */
	ret = sys_mutex_unlock(m_semaphore.mutex);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_unlock failed with " << ret);
	}

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: acquired.\n", hkThread::getThreadId(), this);

}

void hkSemaphore::release(int count)
{
	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: getting semaphore lock for release\n", hkThread::getThreadId(), this);

	/* Mutual exclusion is required before touching cur_count */
	int ret = sys_mutex_lock(m_semaphore.mutex, NO_TIMEOUT);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_lock failed with " << ret);
		return;
	}

	/* Increment cur_count */
	if (m_semaphore.curCount < m_semaphore.maxCount) 
	{
		m_semaphore.curCount += count;
		if (m_semaphore.curCount > m_semaphore.maxCount) // cap it
			m_semaphore.curCount = m_semaphore.maxCount;
	} 
	else 
	{
		HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: maxed out\n", hkThread::getThreadId(), this);

		ret = sys_mutex_unlock(m_semaphore.mutex);
		if (ret != CELL_OK) 
		{
			HK_WARN(0x0,"sys_mutex_unlock failed with " << ret);
		}
		return;
	}

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: signaling the release\n", hkThread::getThreadId(), this);

	/* Notify other threads that the semaphore is available */
	for (int s = 0; s < count; ++s)
	{
		ret = sys_cond_signal(m_semaphore.cond);
		if (ret != CELL_OK) 
		{
			HK_WARN(0x0,"sys_cond_signal failed with " << ret);
			ret = sys_mutex_unlock(m_semaphore.mutex);
			if (ret != CELL_OK) 
			{
				HK_WARN(0x0,"sys_mutex_unlock failed with " << ret);
			}
			return;
		}
	}

	/* End of the critical section */
	ret = sys_mutex_unlock(m_semaphore.mutex);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_unlock failed with " << ret);
	}

	HK_SEMAPHORE_DEBUG_PRINTF("%llu,%x]sem: released.\n", hkThread::getThreadId(), this);
}

#else // no PPU threading

hkSemaphore::hkSemaphore( int initialCount, int maxCount )
{
	//Can't have warnings etc in data types that can be statically initialized:
	// HK_WARN(0xf9178faf, "hkSemaphone being used in a single threaded PS3 environment. It will have no effect.");
}

hkSemaphore::~hkSemaphore()
{
}

void hkSemaphore::acquire()
{
}

void hkSemaphore::release(int count)
{
}

#endif

	// static function
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
