/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_SPU_MONITOR_CACHE__H
#define HK_SPU_MONITOR_CACHE__H

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Monitor/hkMonitorStream.h>

enum ElfType
{
	HK_ELF_TYPE_INTEGRATE = 0,
	HK_ELF_TYPE_COLLIDE = 1,
	HK_ELF_TYPE_ANIMATION = 2,
	HK_ELF_TYPE_COLLISION_QUERY = 3,
	HK_ELF_TYPE_THREAD_SIMULATE = 0
};

/// This monitor cache represents a cache in main memory that a single spu can
/// use to write timers into.  The PPU and SPU calls are not locked, it is up to the
/// user of this class to make sure that SPU and PPU do not call this class concurrently.
class hkSpuMonitorCache
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS, hkSpuMonitorCache);

#if !defined(HK_PLATFORM_SPU)

		//
		// PPU functions
		//

			/// Initialize the cache with a buffer size. PPU only.
		hkSpuMonitorCache( int monitorBufSize );

			/// Deallocates the buffer.
		~hkSpuMonitorCache();

			/// Fix up the timer stream in place. Strings in the stream are replaced with
			/// strings taken from the spurs elfs loaded in main memory.
		void fixUpStringsPpu( hkUlong* spursElfsInMainMemory );

			/// Clear the ppu buffer
		void clearTimersPpu();

		const char* getTimerDataStartPpu() { return m_start; }
		const char* getTimerDataEndPpu() { return m_current; }

#else

		//
		// SPU functions
		//

			/// Init monitor streams with given static buffer on an SPU. Call this once at the start of your SPU program
		static void HK_CALL initMonitorsSpu( void* monitorCacheAddress, int spuElfId);

			/// Call this often, to send data to main memory and reset the timer data
		static HK_FORCE_INLINE void HK_CALL dmaMonitorDataToMainMemorySpu();

			/// This must be called at the end of the spu program. The PPU must wait until this call has completed before
			/// calling either of the PPU calls above.  Use a semaphore which the PPU waits on that the SPU sets on program
			/// exit to ensure this.  (Note: This is done by the hkpMultithreadingUtil.)
		static void HK_CALL finalizeMonitorsSpu( void* monitorCacheAddress );

			/// steal the monitor buffer for other purposes
		static void* stealMonitorBuffer(int size);

			/// return the stolen buffer
		static void returnStolenMonitorBuffer();

	protected:

		static void HK_CALL resetMonitorStream();

		static void dmaMonitorDataToMainMemorySpuStatic();

		void sendTimersToMainMemoryAndResetSpu( );

#endif

	protected:

		enum
		{
			MIN_SIZE_TO_DMA = 512
		};

		hkPadSpu<char*> m_current; // so it can be dma'd by itself. Assumed to be at start of struct
		hkPadSpu<char*> m_start; 	// points to the start of the cache. Setup only.
		hkPadSpu<char*> m_end; 	// points to the end of the whole cache. Do not exceed.

};

#include <Common/Base/Monitor/Spu/hkSpuMonitorCache.inl>

#endif // HK_SPU_MONITOR_CACHE__H

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
