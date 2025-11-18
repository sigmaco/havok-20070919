/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

#if HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED
#	if !defined(HK_PLATFORM_PS3) && !defined(HK_PLATFORM_PS3SPU)
#		if defined HK_TIME_CRITICAL_SECTION_LOCKS
			HK_THREAD_LOCAL( int ) hkCriticalSection__m_timeLocks; // init to 0 (false) per thread
#		endif
#	elif defined(HK_PLATFORM_PS3)
		HK_COMPILE_TIME_ASSERT( sizeof(sys_mutex_t) == sizeof(hkUint32) );
#	endif
#	if !defined(HK_PLATFORM_PS3SPU)
		hkCriticalSection hkCriticalSection::SectionList::s_listHead(0, false);
#	endif
#endif

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
