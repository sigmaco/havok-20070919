/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <pthread.h>
#include <stdio.h>	

#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
#	include <Common/Base/Monitor/hkMonitorStream.h>
#endif


#define CHECK( A ) if( A != 0 ) { perror(#A); HK_BREAKPOINT(0);} else

inline hkCriticalSection::hkCriticalSection( int spinCount, hkBool32 addToList )
	: m_list(this, spinCount, addToList)
{
	pthread_mutexattr_t attr;
	CHECK( pthread_mutexattr_init(&attr) );
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	CHECK( pthread_mutex_init(&m_mutex, &attr ) ); //&attr
	m_currentThread = HK_INVALID_THREAD_ID;
}

inline hkCriticalSection::~hkCriticalSection()
{	
	CHECK( pthread_mutex_destroy(&m_mutex) );
}

inline bool hkCriticalSection::haveEntered()
{
	return m_currentThread == hkThread::getMyThreadId();
}

inline bool hkCriticalSection::isEntered() const
{
	return m_currentThread != HK_INVALID_THREAD_ID;
}

// Removed in 4.5 Release?
/*inline int hkCriticalSection::tryEnter()
{
	//trylock returns 0 if successful
	if ( pthread_mutex_trylock(&m_mutex) == 0   )
	{
		m_currentThread = hkThread::getMyThreadId();
		return 1;
	}
	return 0;
}*/


inline void hkCriticalSection::setTimersEnabled()
{
#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
	HK_THREAD_LOCAL_SET(hkCriticalSection__m_timeLocks, 1);
#endif
}
inline void hkCriticalSection::setTimersDisabled()
{
#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
	HK_THREAD_LOCAL_SET(hkCriticalSection__m_timeLocks, 0);
#endif
}


#ifndef HK_TIME_CRITICAL_SECTION_LOCKS
	inline void hkCriticalSection::enter()
	{
		pthread_mutex_lock(&m_mutex );
		m_currentThread = hkThread::getMyThreadId();
	}

	inline void hkCriticalSection::leave()
	{
		m_currentThread = HK_INVALID_THREAD_ID;
		pthread_mutex_unlock(&m_mutex);
						
	}
#else // HK_TIME_CRITICAL_SECTION_LOCKS

	inline void hkCriticalSection::enter()
	{
		if ( pthread_mutex_trylock(&m_mutex) == 0 )
		{
			//lock acquired
		}
		else
		{
			//Busy wait
			if ( HK_THREAD_LOCAL_GET(hkCriticalSection__m_timeLocks) )
			{
				HK_TIMER_BEGIN("CriticalLock", HK_NULL);
				pthread_mutex_lock(&m_mutex );				
				HK_TIMER_END();
			}
			else
			{
				pthread_mutex_lock(&m_mutex );				
			}
		}
		m_currentThread = hkThread::getMyThreadId();
	}

	inline void hkCriticalSection::leave()
	{
		m_currentThread = HK_INVALID_THREAD_ID;
		pthread_mutex_unlock(&m_mutex);		
	}
#endif // HK_TIME_CRITICAL_SECTION_LOCKS



hkUint32 HK_CALL hkCriticalSection::atomicExchangeAdd(hkUint32* var, int value)
{
	hkUint32 r = *var;
	*var += value;
	return r;
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
