/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>


#if defined(HK_XBOX_USE_PERFLIB) && defined(HK_PLATFORM_XBOX360)
hkUlong g_hkXbox360PerfSampleRegAddr = 0x8FFF1230; // 0x30 = 6*8 == reg 6 == LHS cycles in a PB0T0 setup
#endif 


HK_THREAD_LOCAL( hkMonitorStream* ) hkMonitorStream__m_instance;


#if (HK_CONFIG_MONITORS == HK_CONFIG_MONITORS_ENABLED)

	#if !defined(HK_PLATFORM_PS3SPU)

		void hkMonitorStream::init() 
		{
		#if defined(HK_PLATFORM_SPU)
			static hkMonitorStream _instance;
			hkMonitorStream* instance = &_instance;
		#else
			hkMonitorStream* instance = new hkMonitorStream();
		#endif
			HK_THREAD_LOCAL_SET( hkMonitorStream__m_instance, instance );
			instance->m_isBufferAllocatedOnTheHeap = false;
			instance->m_start = HK_NULL;
			instance->m_capacity = HK_NULL;
			instance->m_end = HK_NULL;
			instance->m_capacityMinus16 = HK_NULL;
		}

		void hkMonitorStream::quit()
		{
			if ( getStart() && isBufferAllocatedOnTheHeap() )
			{
				hkDeallocate(getStart());
			}
			delete HK_THREAD_LOCAL_GET( hkMonitorStream__m_instance );
		}

		void HK_CALL hkMonitorStream::resize( int newSize )
		{

			if ( newSize == getCapacity() - getStart() )
			{
				return;
			}

			if (newSize > 0)
			{
				if ( getStart() && isBufferAllocatedOnTheHeap() )
				{
					hkDeallocate(getStart());
				}

				m_isBufferAllocatedOnTheHeap = true;
				m_start = hkAllocate<char>(newSize, HK_MEMORY_CLASS_MONITOR);
				m_end = m_start;
				m_capacity = m_start + newSize;
				m_capacityMinus16 = m_capacity - 32;
			}
			else
			{
				quit();
			}
		}

	#endif

	void HK_CALL hkMonitorStream::setStaticBuffer( char* buffer, int bufferSize )
	{
	#if !defined(HK_PLATFORM_PS3SPU)
		if ( isBufferAllocatedOnTheHeap() )
		{
			resize(0);
		}
	#endif

		m_isBufferAllocatedOnTheHeap = false;
		m_start = buffer ;
		m_end = buffer;
		m_capacity = m_start + bufferSize;
		m_capacityMinus16 = m_capacity - 32 ;
	}

	void HK_CALL hkMonitorStream::reset()
	{
		m_end = m_start;
	}

#else // #if (HK_CONFIG_MONITORS == HK_CONFIG_MONITORS_DISABLED)

	void hkMonitorStream::init() 
	{
		// we need this so that hkMonitorStream::getInstance() will return a valid pointer
		static hkMonitorStream _instance;
		HK_THREAD_LOCAL_SET( hkMonitorStream__m_instance, &_instance );
	}

	void hkMonitorStream::quit()
	{
	}

	void HK_CALL hkMonitorStream::setStaticBuffer( char* buffer, int bufferSize )
	{
	}

	void HK_CALL hkMonitorStream::reset()
	{
	}

	void HK_CALL hkMonitorStream::resize( int newSize )
	{
	}

#endif


#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
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
