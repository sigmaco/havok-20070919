/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/Fwd/hkcstdio.h>

inline hkCriticalSection::hkCriticalSection( int spinCount, hkBool32 addToList )
 : m_list(this, spinCount, addToList)
{
	pthread_mutexattr_t attr;
	HK_POSIX_CHECK( pthread_mutexattr_init(&attr) );
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	HK_POSIX_CHECK( pthread_mutex_init(&m_mutex, &attr) );
	m_currentThread = HK_INVALID_THREAD_ID;
}

inline hkCriticalSection::~hkCriticalSection()
{
	if (haveEntered())
	{
		leave();
	}
	HK_POSIX_CHECK(pthread_mutex_destroy(&m_mutex));
}

inline void hkCriticalSection::enter()
{
	HK_POSIX_CHECK( pthread_mutex_lock(&m_mutex) );
	m_currentThread = hkThread::getMyThreadId();
}

inline bool hkCriticalSection::haveEntered ()
{
	return m_currentThread == hkThread::getMyThreadId();
}

inline bool hkCriticalSection::isEntered () const
{
	return m_currentThread != HK_INVALID_THREAD_ID;
}

inline void hkCriticalSection::leave()
{
	m_currentThread = HK_INVALID_THREAD_ID;
	HK_POSIX_CHECK( pthread_mutex_unlock(&m_mutex) );
}

inline void HK_CALL hkCriticalSection::setTimersEnabled()
{
}

inline void HK_CALL hkCriticalSection::setTimersDisabled()
{
}

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
