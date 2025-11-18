/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

	//
	// Win32
	//

#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
#	include <Common/Base/Monitor/hkMonitorStream.h>
#endif

#pragma warning(push)
#pragma warning(disable:4355) // "this" in init list

// Win32 style only impl here for the moment.
inline hkCriticalSection::hkCriticalSection( int spinCount, hkBool32 addToList )
	: m_list(this, spinCount, addToList)
{
#if defined(HK_COMPILER_MSVC) && (HK_COMPILER_MSVC_VERSION < 1300)
	InitializeCriticalSection( &m_section );
#else // VC7 and higher
	InitializeCriticalSectionAndSpinCount( &m_section, spinCount );
#endif
	m_currentThread = HK_INVALID_THREAD_ID;
#	ifdef HK_PLATFORM_HAS_SPU
	m_this = this;
#	endif
}
#pragma warning(pop)

inline hkCriticalSection::~hkCriticalSection()
{
	DeleteCriticalSection(&m_section );
}

inline bool hkCriticalSection::haveEntered()
{
	return m_currentThread == hkThread::getMyThreadId();
}

inline bool hkCriticalSection::isEntered() const
{
	return m_currentThread != HK_INVALID_THREAD_ID;
}

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
		EnterCriticalSection(&m_section );
		m_currentThread = hkThread::getMyThreadId();
	}

	inline void hkCriticalSection::leave()
	{
		m_currentThread = HK_INVALID_THREAD_ID;
		LeaveCriticalSection(&m_section );
	}
#else // HK_TIME_CRITICAL_SECTION_LOCKS

#if defined HK_SIMULATE_SPU_DMA_ON_CPU
#include <Common/SpuSimulator/hkSpuSimulator.h>
#endif

	inline void hkCriticalSection::enter()
	{
#if defined(HK_PLATFORM_SPU)
		// this is only allowed to be called by the simulated spu to access its own critical sections, eg. memory system
		HK_ASSERT2( 0xf0342323, this->m_this == this, "Call enter(*ppuAddress) instead" );
#endif
		if ( TryEnterCriticalSection(&m_section) )
		{
		}
		else
		{
			if ( HK_THREAD_LOCAL_GET(hkCriticalSection__m_timeLocks) )
			{
				HK_TIMER_BEGIN("CriticalLock", HK_NULL);
				EnterCriticalSection( &m_section );
				HK_TIMER_END();
			}
			else
			{
				EnterCriticalSection( &m_section );
			}
		}
		m_currentThread = hkThread::getMyThreadId();
	}

	inline void hkCriticalSection::leave()
	{
#if defined(HK_PLATFORM_SPU)
		HK_ASSERT2( 0xf0342324, this->m_this == this, "Call leave(*ppuAddress) instead" );
#endif
		m_currentThread = HK_INVALID_THREAD_ID;
		LeaveCriticalSection(&m_section );
	}
#endif // HK_TIME_CRITICAL_SECTION_LOCKS


hkUint32 HK_CALL hkCriticalSection::atomicExchangeAdd(hkUint32* var, int increment)
{
	return InterlockedExchangeAdd( (LONG*)var, increment);
}


#if defined( HK_PLATFORM_SPU )
inline void hkCriticalSection::enter(HK_CPU_PTR(hkCriticalSection*) sectionOnPpu)
{
	hkSpuSimulator::Client::getInstance()->enterCriticalSection(sectionOnPpu);
}

inline void hkCriticalSection::leave(HK_CPU_PTR(hkCriticalSection*) sectionOnPpu)
{
	hkSpuSimulator::Client::getInstance()->leaveCriticalSection(sectionOnPpu);
}
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
