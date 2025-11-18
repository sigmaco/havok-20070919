/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Util/hkSpuUtil.h>

#if defined HK_SIMULATE_SPU_DMA_ON_CPU
#include <Common/SpuSimulator/hkSpuSimulator.h>
#endif



void hkSpuDmaManager::getFromMainMemory(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	HK_ASSERT (0xaf344953, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xad97d84f, size && !(size             & 0xf), "size must be > 0 and a multiple of 16.");
	HK_ASSERT2(0xad97d84f, size <= 0x4000                   , "size must be less than 16k, use getFromMainMemoryLarge instead.");
	HK_ASSERT2(0xad97d8dd, !(hkUlong(dstOnSpu)        & 0xf), "dstOnSpu must be 16-byte aligned. Try getFromMainMemorySmall instead.");
	HK_ASSERT2(0xad97d8de, !(hkUlong(srcInMainMemory) & 0xf), "srcInMainMemory must be 16-byte aligned. Try getFromMainMemorySmall instead.");

	HK_ASSERT(0xaf635ef2, hkUlong(dstOnSpu) > 0x100 && hkUlong(srcInMainMemory) > 0x100 );

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->getFromMainMemory( dstOnSpu, srcInMainMemory, size, mode, dmaGroupId );
	return;
}

void hkSpuDmaManager::putToMainMemory(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xaf344953, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xad6ed84f, size && !(size             & 0xf), "size must be > 0 and a multiple of 16.");
	HK_ASSERT2(0xad97d84f, size <= 0x4000                   , "size must be less than 16k, use getFromMainMemoryLarge instead.");
	HK_ASSERT2(0xad6ed8dd, !(hkUlong(srcOnSpu)        & 0xf), "srcOnSpu must be 16-byte aligned. Try getFromMainMemorySmall instead.");
	HK_ASSERT2(0xad6ed8de, !(hkUlong(dstInMainMemory) & 0xf), "dstInMainMemory must be 16-byte aligned. Try getFromMainMemorySmall instead.");

	HK_ASSERT(0xaf635ef1, hkUlong(dstInMainMemory) > 0x100 && hkUlong(srcOnSpu) > 0x100 );

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->putToMainMemory( dstInMainMemory, srcOnSpu, size, mode, dmaGroupId );
	return;
}

void hkSpuDmaManager::getFromMainMemorySmall(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xaf344953, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xad63d84f, (size == 1) || (size == 2) || (size == 4) || (size == 8), "size must be 1,2,4 or 8 bytes");
	HK_ASSERT2(0xad63d8dd, (hkUlong(dstOnSpu) & 0xf) == (hkUlong(srcInMainMemory) & 0xf), "dstOnSpu and srcInMainMemory must have same lower 4 bits.");
	HK_ASSERT2(0xad63d844, !(hkUlong(dstOnSpu) & (size -1)), "dstOnSpu and srcInMainMemory must be aligned to the size of the transfer.");

	HK_ASSERT(0xaf635ef3, hkUlong(dstOnSpu) > 0x100 && hkUlong(srcInMainMemory) > 0x100 );

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->getFromMainMemory( dstOnSpu, srcInMainMemory, size, mode, dmaGroupId );
	return;
}

void hkSpuDmaManager::putToMainMemorySmall(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xaf344953, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xad62d84f, (size == 1) || (size == 2) || (size == 4) || (size == 8), "size must be 1,2,4 or 8 bytes");
	HK_ASSERT2(0xad62d8dd, (hkUlong(srcOnSpu) & 0xf) == (hkUlong(dstInMainMemory) & 0xf), "srcOnSpu and dstInMainMemory must have same lower 4 bits.");
	HK_ASSERT2(0xad62d844, !(hkUlong(srcOnSpu) & (size -1)), "srcOnSpu and dstInMainMemory must be aligned to the size of the transfer.");

	HK_ASSERT(0xaf635ef4, hkUlong(dstInMainMemory) > 0x100 && hkUlong(srcOnSpu) > 0x100 );

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->putToMainMemory( dstInMainMemory, srcOnSpu, size, mode, dmaGroupId );
	return;
}

void hkSpuDmaManager::getFromMainMemoryList(void* dstOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, READ_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xaf314953, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xaf63efe3, numListEntries > 0 && numListEntries < 2048, "numListEntries must be positive and < 2048."); // feel free to remove the check for > 0 if need be ;)
	HK_ASSERT2(0xaf63efe4, (hkUlong(listOnSpu) & 0x7) == 0, "listOnSpu must be 8-byte aligned.");
	HK_CHECK_ALIGN16(dstOnSpu);

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");

#if defined (HK_DEBUG)
	//
	// check for overlaps between any of the source memory blocks in main memory
	//
	{
		for (int x=0; x<numListEntries; x++)
		{
			for (int y=x+1; y<numListEntries; y++)
			{
				hkSpuDmaListElement* entry0 = &listOnSpu[x];
				hkUlong e0StartAddress = hkUlong(entry0->m_addressInMainMemory);
				hkUlong e0EndAddress   = e0StartAddress + hkUlong(entry0->m_memoryBlockSize);

				hkSpuDmaListElement* entry1 = &listOnSpu[y];
				hkUlong e1StartAddress = hkUlong(entry1->m_addressInMainMemory);
				hkUlong e1EndAddress   = e1StartAddress + hkUlong(entry1->m_memoryBlockSize);

				HK_ASSERT2(0xad876544, e0EndAddress <= e1StartAddress || e0StartAddress >= e1EndAddress, "Invalid overlap in main memory between DMA transfer-list entries.");
			}
		}
	}
#endif

	//
	// split-up the list transfer into several individual transfers
	//
	int totalBytesTransfered = 0;
	{
		for (int i=0; i<numListEntries; i++)
		{
			hkSpuDmaListElement* entry = &listOnSpu[i];
			HK_ASSERT2(0xaf642e3e, (entry->m_memoryBlockSize & 0xf) == 0, "Size of one single memory transfer within DMA list must be a multiple of 16.");
			HK_ASSERT2(0xaf642e32, entry->m_notify == 0, "The notify-and-stall flag should not be set. Make sure to properly clear/init all flags of the list element.");
			HK_ASSERT2(0xaf645e3e, (totalBytesTransfered+entry->m_memoryBlockSize) <= spuBufferSize, "Buffer overwrite on spu during DMA list transfer.");
			hkSpuSimulator::Client::getInstance()->getFromMainMemory( dstOnSpu, (HK_CPU_PTR(void*))(entry->m_addressInMainMemory), entry->m_memoryBlockSize, mode, dmaGroupId );
			dstOnSpu = (void*)(hkUlong(dstOnSpu) + entry->m_memoryBlockSize);
			totalBytesTransfered += int(entry->m_memoryBlockSize);
		}
	}
}

void hkSpuDmaManager::putToMainMemoryList(void* srcOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, WRITE_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xaf314954, (dmaGroupId >= 0) && (dmaGroupId <= 31) );
	HK_ASSERT2(0xaf63efe6, numListEntries > 0 && numListEntries <= 2048, "numListEntries must be positive and <= 2048."); // feel free to remove the check for > 0 if need be ;)
	HK_ASSERT2(0xaf63efe7, (hkUlong(listOnSpu) & 0x7) == 0, "listOnSpu must be 8-byte aligned.");
	HK_CHECK_ALIGN16(srcOnSpu);

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");

#if defined (HK_DEBUG)
	//
	// check for overlaps between any of the destination memory blocks in main memory
	//
	{
		for (int x=0; x<numListEntries; x++)
		{
			for (int y=x+1; y<numListEntries; y++)
			{
				hkSpuDmaListElement* entry0 = &listOnSpu[x];
				hkUlong e0StartAddress = hkUlong(entry0->m_addressInMainMemory);
				hkUlong e0EndAddress   = e0StartAddress + hkUlong(entry0->m_memoryBlockSize);

				hkSpuDmaListElement* entry1 = &listOnSpu[y];
				hkUlong e1StartAddress = hkUlong(entry1->m_addressInMainMemory);
				hkUlong e1EndAddress   = e1StartAddress + hkUlong(entry1->m_memoryBlockSize);

				HK_ASSERT2(0xad876554, e0EndAddress <= e1StartAddress || e0StartAddress >= e1EndAddress, "Invalid overlap in main memory between DMA transfer-list entries.");

			}
		}
	}
#endif

	//
	// split-up the list transfer into several individual transfers
	//
	int totalBytesTransfered = 0;
	{
		for (int i=0; i<numListEntries; i++)
		{
			hkSpuDmaListElement* entry = &listOnSpu[i];
			HK_ASSERT2(0xaf645e33, (totalBytesTransfered+entry->m_memoryBlockSize) <= spuBufferSize, "Buffer overread on spu during DMA list transfer.");
			HK_ASSERT2(0xaf645e32, entry->m_notify == 0, "The notify-and-stall flag should not be set. Make sure to properly clear/init all flags of the list element.");
			HK_ASSERT2(0xaf342e3e, (entry->m_memoryBlockSize & 0xf) == 0, "Size of one single memory transfer within DMA list must be a multiple of 16.");
			hkSpuSimulator::Client::getInstance()->putToMainMemory((HK_CPU_PTR(void*))(entry->m_addressInMainMemory), srcOnSpu, entry->m_memoryBlockSize, mode, dmaGroupId );
			srcOnSpu = (void*)(hkUlong(srcOnSpu) + entry->m_memoryBlockSize);
			totalBytesTransfered += int(entry->m_memoryBlockSize);
		}
	}
}

void hkSpuDmaManager::waitForDmaCompletion(int dmaGroupId)
{
	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->waitDmaGroup( HK_DMAWAIT_BITSHIFT(dmaGroupId) );
}

void hkSpuDmaManager::waitForDmaCompletionUsingBitfield(int dmaGroupMask)
{
	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->waitDmaGroup( dmaGroupMask );
}

void hkSpuDmaManager::waitForAllDmaCompletion()
{
	HK_ASSERT2(0xaf8374ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->waitDmaGroup( 0xffffffff );
}

hkUint32 hkSpuDmaManager::atomicExchangeAdd(hkUint32* varOnPpu, int increment)
{
	HK_ASSERT2(0xaf8374ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	return hkSpuSimulator::Client::getInstance()->atomicExchangeAdd( varOnPpu, increment );
}

void hkSpuDmaManager::performFinalChecks(const HK_CPU_PTR(void*) ppu, const void* spu, int size )
{
	HK_ASSERT2(0xaf8374ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->performFinalChecks( ppu, spu, size);
}

void hkSpuDmaManager::tryToPerformFinalChecks(const HK_CPU_PTR(void*) ppu, const void* spu, int size )
{
	HK_ASSERT2(0xaf8374ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->tryToPerformFinalChecks( ppu, spu, size);
}

void hkSpuDmaManager::deferFinalChecksUntilWait(const HK_CPU_PTR(void*) ppu, const void* spu, int size )
{
	HK_ASSERT2(0xaf8374ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->deferFinalChecksUntilWait( ppu, spu, size);
}

void hkSpuDmaManager::abortDebugTracking(const HK_CPU_PTR(void*) ppu, const void* spu, int size )
{
	HK_ASSERT2(0xaf8274ff, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->abortDmaRequest( ppu, spu, size);
}

void hkSpuDmaManager::convertReadOnlyToReadWrite(void* ppu, const void* spu, int size)
{
	HK_ASSERT2(0xaf8324f1, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->convertReadOnlyToReadWrite( ppu, spu, size);
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
