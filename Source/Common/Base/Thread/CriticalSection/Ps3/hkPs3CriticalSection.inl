/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <sys/timer.h>
	//
	// PS3
	//
inline hkCriticalSection::hkCriticalSection( int spinCount, hkBool32 addToList )
	: m_list(this, spinCount, addToList)
{
#if defined(HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT)
	sys_mutex_attribute_t mutex_attr;
	sys_mutex_attribute_initialize(mutex_attr);
	mutex_attr.attr_protocol = SYS_SYNC_PRIORITY; 
	int ret = sys_mutex_create(&m_ppuMutex, &mutex_attr);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0, "sys_mutex_create failed with " << ret);
		return;
	}
#endif
	m_currentThread = HK_INVALID_THREAD_ID;
	{
		HK_ON_DEBUG( ret = ) cellSyncMutexInitialize(&m_mutex);
		HK_ASSERT(0x0, ret == CELL_OK);
	}
#if defined(HK_PLATFORM_HAS_SPU)
	m_this = this;
#endif
}

inline hkCriticalSection::~hkCriticalSection()
{
#if defined(HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT) 
	int ret = sys_mutex_destroy(m_ppuMutex);
	if (ret != CELL_OK) 
	{
		HK_WARN(0x0,"sys_mutex_destroy failed with " << ret);
	}
#endif
}

inline bool hkCriticalSection::haveEntered()
{
	return ( m_currentThread == hkThread::getMyThreadId() );
}

inline bool hkCriticalSection::isEntered() const
{
	return m_currentThread != HK_INVALID_THREAD_ID;
}

inline void hkCriticalSection::setTimersEnabled()
{
}

inline void hkCriticalSection::setTimersDisabled()
{
}

inline void hkCriticalSection::enter()
{
	// will busy wait as is a low level mutex

	const hkUint64 tid = hkThread::getMyThreadId();
	bool haveLock = m_currentThread == tid;

	if (!haveLock) // don't have it already 
	{
#		if defined(HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT)
			sys_mutex_lock(m_ppuMutex, 0 /*== no timeout*/); // get outer lock
#		endif

		while( cellSyncMutexTryLock(&m_mutex) != CELL_OK )
		{
			sys_timer_usleep(1);
		}
		m_currentThread = tid; //we own it now.
		m_recursiveLockCount = 1;
	}
	else
	{
		m_recursiveLockCount++;
	}
}

inline void hkCriticalSection::leave()
{
	// only leave if we have the lock
#ifdef HK_DEBUG
	const hkUint64 tid = hkThread::getMyThreadId();
	HK_ASSERT2(0x0, m_currentThread == tid, "Releasing lock that you don't hold");
#endif

	m_recursiveLockCount--;
	HK_ASSERT2(0x0, m_recursiveLockCount >= 0, "hkCriticalSection::leave() without matching ::enter!" );

	if (m_recursiveLockCount == 0) // actually release it
	{
		m_currentThread = HK_INVALID_THREAD_ID; //we no longer own it.

		// unlock inner
		cellSyncMutexUnlock(&m_mutex);

		// unlock outer
#	if defined(HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT)
		/*int ret = */ sys_mutex_unlock(m_ppuMutex);
#	endif
	}
}


hkUint32 HK_CALL hkCriticalSection::atomicExchangeAdd(hkUint32* var, int value)
{
	return cellAtomicAdd32(var, value);
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
