/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Monitor/Spu/hkSpuMonitorCache.h>

#if !defined(HK_PLATFORM_SPU)

	#define ELF_OFFSET (0x3000 - 0x100)

	hkSpuMonitorCache::hkSpuMonitorCache( int monitorBufSize )
	{
		m_start = hkAlignedAllocate<char>(128, monitorBufSize, HK_MEMORY_CLASS_DEMO );
		m_end = m_start + monitorBufSize;
		m_current = m_start;
	}

	hkSpuMonitorCache::~hkSpuMonitorCache()
	{
		hkAlignedDeallocate<char>( m_start );
	}

	void hkSpuMonitorCache::clearTimersPpu()
	{
		m_current = m_start;
	}


	void hkSpuMonitorCache::fixUpStringsPpu( hkUlong* spursElfsInMainMemory )
	{
		int capturedDataSize = int(m_current - m_start);

		if (capturedDataSize > 0)
		{
			char* currentSpu = m_start;
			char* endSpu = m_current;

			int currentElf = -1;

			while ( currentSpu < endSpu )
			{
				hkMonitorStream::Command* command = reinterpret_cast<hkMonitorStream::Command*>(currentSpu);

				if ((hkUlong)command->m_commandAndMonitor < 10)
				{
					int* elfId = (int*)command;
					currentElf = *elfId;
					currentSpu = (char*)(elfId + 1);
					continue;
				}

				HK_ASSERT(0, currentElf != -1);

				const char* mainMemoryTimerPtr = command->m_commandAndMonitor + spursElfsInMainMemory[currentElf] - ELF_OFFSET;

				switch( mainMemoryTimerPtr[0] )
				{
				case 'S':		// split list
				case 'E':		// timer end
				case 'l':		// list end
				case 'T':		// timer begin
					{
						hkMonitorStream::TimerCommand* spuTimerCommand = reinterpret_cast<hkMonitorStream::TimerCommand*>( currentSpu );
						spuTimerCommand->m_commandAndMonitor = mainMemoryTimerPtr;
						currentSpu = (char*)(spuTimerCommand + 1);

						break;
					}

				case 'L':		// timer list begin
					{

						hkMonitorStream::TimerBeginListCommand* spuTimerCommand = reinterpret_cast<hkMonitorStream::TimerBeginListCommand*>( currentSpu );
						spuTimerCommand->m_commandAndMonitor = mainMemoryTimerPtr;
						spuTimerCommand->m_nameOfFirstSplit = spuTimerCommand->m_nameOfFirstSplit + spursElfsInMainMemory[currentElf]  - ELF_OFFSET;
						currentSpu = (char*)(spuTimerCommand + 1);
						break;
					}

				case 'M':
					{
						hkMonitorStream::AddValueCommand* spuAddValueCommand = reinterpret_cast<hkMonitorStream::AddValueCommand*>( currentSpu );
						spuAddValueCommand->m_commandAndMonitor = mainMemoryTimerPtr;
						currentSpu = (char*)(spuAddValueCommand + 1);
						break;
					}
				case 'P':
				case 'p':
				case 'N':
					{
						hkMonitorStream::Command* spuTimerCommand = reinterpret_cast<hkMonitorStream::Command*>( currentSpu );
						spuTimerCommand->m_commandAndMonitor = mainMemoryTimerPtr;
						currentSpu = (char*)(spuTimerCommand + 1);
						break;
					}

				default:
					HK_ASSERT2(0xf0231454, 0, "Inconsistent Monitor capture data" ); 	
					break;
				}
			}
		}
	}


#else // #if defined(HK_PLATFORM_SPU)

	#define LOCAL_MONITOR_BUFFER_SIZE (1024*4)

	// 2 4KB monitor buffers. We need to allocate this buffer even if monitors are disabled as we use it as a temp buffer in the hkpCollectionCollectionAgent3.
	HK_ALIGN( unsigned int localMonitorStream[LOCAL_MONITOR_BUFFER_SIZE * 2 / sizeof(unsigned int)], 128 );

#if (HK_CONFIG_MONITORS == HK_CONFIG_MONITORS_ENABLED)

	#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

#if defined (HK_PLATFORM_PS3SPU)
	#include <spu_intrinsics.h>
#endif

	// A structure to allow dma of monitors to main memory
	HK_ALIGN( char monitorCacheBuf[sizeof(hkSpuMonitorCache)], 128 );

	static hkSpuMonitorCache* s_monitorCache = HK_NULL;
	static void* s_monitorCacheAddress = HK_NULL;

	static hkPadSpu<char*> s_localMonitorStreams[2] = { HK_NULL, HK_NULL };
	static hkPadSpu<int> s_monitorCacheDmaGroups[2] = { 29, 30 };
	static int s_currentSpuMonitorCache = 0;
	static int s_spuElfId = -1;


	void hkSpuMonitorCache::dmaMonitorDataToMainMemorySpuStatic()
	{
		HK_ASSERT2(0x2fea9752, s_monitorCache != HK_NULL, "You must call hkInitMonitorsSpu() before calling dmaMonitorDataToMainMemorySpu" );
		s_monitorCache->sendTimersToMainMemoryAndResetSpu();
	}

	void hkSpuMonitorCache::resetMonitorStream()
	{
		hkMonitorStream& instance = hkMonitorStream::getInstance();
		instance.reset();
		if ( instance.memoryAvailable() )
		{
			int* id = (int*)instance.getEnd();
			*id = s_spuElfId;
			instance.setEnd( (char*)(id + 1));
		}

	}

	void hkSpuMonitorCache::sendTimersToMainMemoryAndResetSpu()
	{
		// If we have hit the limit of the SPU buffer, replace with an overflow marker. Do not dma the incomplete timers
		// to the PPU.
		hkMonitorStream& instance = hkMonitorStream::getInstance();
		if ( !instance.memoryAvailable() )
		{
			resetMonitorStream();
			HK_MONITOR_ADD_VALUE("SPU timer buffer overflow", 1, HK_MONITOR_TYPE_INT);
		}

			// align the end
		while ((((hkUlong)instance.getCurrentMonitorDataSize()) & 0x0f) != 0)
		{
			HK_MONITOR_NOP();
		}

		// Check and pad for alignment (16bytes for general DMA)
		// the timer commands are all multiples of 4 localMonitorBufferSize, so we need at most 3 more cmds (NOPs, each 4 byte ptrs on SPU)
		// This is not for the transfer now, but for transfers after this one 
		// that will tag on where this one ends.

		int freeBytesInMainMemory = int(m_end - m_current );
		int dataSize = instance.getCurrentMonitorDataSize();

		// If we are out of space in the main memory buffer, give up replace timers with an overflow marker
		// completely stop getting timer info
		if (dataSize > freeBytesInMainMemory )
		{
			// stop getting timers all together
			hkSpuDmaManager::waitForAllDmaCompletion();
			instance.setStaticBuffer( s_localMonitorStreams[s_currentSpuMonitorCache], 0 );
			return;
//			resetMonitorStream();
// 			HK_MONITOR_ADD_VALUE("SPU main memory timer buffer overflow", 1, HK_MONITOR_TYPE_INT);
		}

		{
			if ( dataSize )
			{
				hkSpuDmaManager::putToMainMemory( m_current, instance.getStart(), dataSize, hkSpuDmaManager::WRITE_NEW, s_monitorCacheDmaGroups[s_currentSpuMonitorCache] );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( m_current, instance.getStart(), dataSize );
			}

			s_currentSpuMonitorCache ^= 1;

			// Make sure the other buffer is no longer being dma'd and swap the buffers
			hkSpuDmaManager::waitForDmaCompletion( s_monitorCacheDmaGroups[s_currentSpuMonitorCache] );

			instance.setStaticBuffer( s_localMonitorStreams[s_currentSpuMonitorCache], LOCAL_MONITOR_BUFFER_SIZE );

			m_current = m_current + dataSize;
		}

		// Now the memory has been dma'd, reset.
		resetMonitorStream();
	}

	void* hkSpuMonitorCache::stealMonitorBuffer(int size)
	{
		if ( s_localMonitorStreams[0] )
		{
			HK_ASSERT( 0xf03fefde, hkAddByteOffset(s_localMonitorStreams[0].val(),LOCAL_MONITOR_BUFFER_SIZE) == s_localMonitorStreams[1].val() && size <= LOCAL_MONITOR_BUFFER_SIZE*2);
			s_monitorCache->sendTimersToMainMemoryAndResetSpu();
			hkSpuDmaManager::waitForAllDmaCompletion();
		}
		return localMonitorStream;
	}

	void hkSpuMonitorCache::returnStolenMonitorBuffer()
	{
		if ( s_localMonitorStreams[0] )
		{
			HK_ASSERT( 0xf03feeee, hkMonitorStream::getInstance().getCurrentMonitorDataSize() == sizeof(int));
			resetMonitorStream();
		}
	}

	void hkSpuMonitorCache::initMonitorsSpu( void* monitorCacheAddress, int spuElfId )
	{
		if (monitorCacheAddress != 0)
		{
			/// Note: If monitors are not enabled, doing nothing will leave the hkMonitorStream variables at 0, which disables monitors.
			/// On spu the BSS section is guaranteed to be 0.

			// Initialize the monitors to point to the local buffers
#if defined (HK_PLATFORM_PS3SPU)
			// This seems to cause problems with the SPURS task policy module, so disabling this for now
			// Timers will wrap around every 26 seconds (if the decrementer is not reset elsewhere).
			//spu_writech(SPU_WrDec, 0);
#endif
			hkMonitorStream::getInstance().setStaticBuffer( (char*)localMonitorStream, LOCAL_MONITOR_BUFFER_SIZE);

			s_localMonitorStreams[0] = ((char*)localMonitorStream);
			s_localMonitorStreams[1] = ((char*)localMonitorStream) + LOCAL_MONITOR_BUFFER_SIZE;
			s_currentSpuMonitorCache = 0;

			hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion( &monitorCacheBuf, (const void*)hkUlong(monitorCacheAddress), sizeof(hkSpuMonitorCache), hkSpuDmaManager::READ_COPY );
			HK_SPU_DMA_PERFORM_FINAL_CHECKS( monitorCacheAddress, &monitorCacheBuf, sizeof(hkSpuMonitorCache) );

			s_monitorCache = (hkSpuMonitorCache*)&monitorCacheBuf;
			s_monitorCacheAddress = (void*)monitorCacheAddress;
			s_spuElfId = spuElfId;

			resetMonitorStream();
		}
	}


	void hkSpuMonitorCache::finalizeMonitorsSpu( void* monitorCacheAddress )
	{
		if (monitorCacheAddress != 0)
		{
			dmaMonitorDataToMainMemorySpuStatic();
			hkSpuDmaManager::putToMainMemoryAndWaitForCompletion( monitorCacheAddress, &(s_monitorCache->m_current), sizeof( s_monitorCache->m_current ), hkSpuDmaManager::WRITE_NEW );
			
			// Make sure the timer pointer has been written before the elf ends and a new elf dmas it
			hkSpuDmaManager::waitForAllDmaCompletion();

			HK_SPU_DMA_PERFORM_FINAL_CHECKS(monitorCacheAddress, &(s_monitorCache->m_current), sizeof( s_monitorCache->m_current ) );
		}
	}

#else // #if (HK_CONFIG_MONITORS == HK_CONFIG_MONITORS_DISABLED)

	void hkSpuMonitorCache::dmaMonitorDataToMainMemorySpuStatic()
	{
	}

	void hkSpuMonitorCache::sendTimersToMainMemoryAndResetSpu()
	{
	}

	void hkSpuMonitorCache::initMonitorsSpu( void* monitorCacheAddress, int spuElfId )
	{
	}

	void hkSpuMonitorCache::finalizeMonitorsSpu( void* monitorCacheAddress )
	{
	}

	void* hkSpuMonitorCache::stealMonitorBuffer(int size)
	{
		return localMonitorStream;
	}

	void hkSpuMonitorCache::returnStolenMonitorBuffer()
	{
	}

	void hkSpuMonitorCache::resetMonitorStream()
	{
	}

#endif

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
