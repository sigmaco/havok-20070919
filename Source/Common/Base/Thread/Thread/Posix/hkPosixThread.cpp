/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Thread/Posix/hkPosixCheck.h>
#include <pthread.h>
#include <Common/Base/Fwd/hkcstdio.h>

hkThread::hkThread()
	: m_thread(HK_NULL), m_threadId(THREAD_NOT_STARTED)
{
}

hkThread::~hkThread()
{
	stopThread();
}

void hkThread::stopThread()
{
	if( m_thread )
	{
		HK_POSIX_CHECK( pthread_join((pthread_t)m_thread, HK_NULL) );
		m_thread = HK_NULL;
	}
}


hkResult hkThread::startThread( hkThread::StartFunction func, void* arg )
{
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);	
	
	int error = pthread_create( &thread, &attr, func, arg );
	if (error)
	{
		perror("Thread Error\n" );
		return HK_FAILURE;
	}	
	m_thread = (void*)thread;
	m_threadId = THREAD_RUNNING;

	return HK_SUCCESS;
}

hkThread::Status hkThread::getStatus()
{
	return static_cast<Status>(m_threadId);
}

hkUint64 hkThread::getChildThreadId()
{
	return hkUlong(m_thread);
}

void* hkThread::getHandle()
{
	return m_thread;
}

hkUint64 hkThread::getMyThreadId()
{
	pthread_t tid = pthread_self();
	return (hkUint64)tid;
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
