/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/Thread/hkThread.h>

#ifdef HK_PLATFORM_WIN32
#	include <Common/Base/Fwd/hkwindows.h>
#elif defined(HK_PLATFORM_XBOX360)
# 	include <xtl.h>
#endif

hkThread::hkThread()
	: m_thread(HK_NULL)
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
		CloseHandle( m_thread );
		m_thread = HK_NULL;
	}
}

hkResult hkThread::startThread( hkThread::StartFunction func, void* arg )
{
	m_thread = CreateThread(
			HK_NULL,	//LPSECURITY_ATTRIBUTES ThreadAttributes,
			0 ,			//DWORD StackSize,
			(LPTHREAD_START_ROUTINE)func,	//LPTHREAD_START_ROUTINE StartAddress,
			arg,		//LPVOID Parameter,
			0,			//DWORD CreationFlags,
			(LPDWORD)&m_threadId //LPDWORD ThreadId 
		);
	if (m_thread == HK_NULL)
	{
		return HK_FAILURE;
	}
	else
	{
		return HK_SUCCESS;
	}
}

hkThread::Status hkThread::getStatus()
{
	if (m_thread == HK_NULL)
	{
		return THREAD_NOT_STARTED;
	}
	DWORD exitCode;
	GetExitCodeThread( m_thread,&exitCode);
	if ( exitCode == STILL_ACTIVE )
	{
		return THREAD_RUNNING;
	}
	return THREAD_TERMINATED;
}


hkUint64 HK_CALL hkThread::getMyThreadId()
{
	return (hkUint64)GetCurrentThreadId();
}

hkUint64 hkThread::getChildThreadId()
{
	return m_threadId;
}

void* hkThread::getHandle()
{
	return m_thread;
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
