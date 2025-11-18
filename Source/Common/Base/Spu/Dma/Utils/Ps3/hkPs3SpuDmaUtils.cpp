/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

#if defined(HK_PLATFORM_PS3SPU)
HK_COMPILE_TIME_ASSERT( sizeof(hkSpuDmaListElement) == sizeof(CellDmaListElement) );
#endif

hkInt32 hkSpuDmaUtils::incrementInt32InMainMemory( HK_CPU_PTR(hkInt32*) variable, int increment, int dmaGroupId )
{
	// synchronize the alignment between both memory locations
	HK_ALIGN16( hkInt32 buffer[4]);
	hkInt32* copy = hkAddByteOffset( &buffer[0], hkUlong(variable)&0xf);

	hkSpuDmaManager::getFromMainMemorySmall(copy, variable, sizeof(copy[0]), hkSpuDmaManager::READ_WRITE, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );

	copy[0] += increment;

	hkSpuDmaManager::putToMainMemorySmall(variable, copy, sizeof(copy[0]), hkSpuDmaManager::WRITE_BACK, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );

	HK_SPU_DMA_PERFORM_FINAL_CHECKS( variable, copy, sizeof(copy[0]));

	return copy[0];
}


void hkSpuDmaUtils::setInt32InMainMemory( HK_CPU_PTR(hkInt32*) variable, hkInt32 value, int dmaGroupId )
{
	HK_ALIGN16( hkInt32 buffer[4]);
	hkInt32* copy = hkAddByteOffset( &buffer[0], hkUlong(variable)&0xf);
	copy[0] = value;
	hkSpuDmaManager::putToMainMemorySmall(variable, copy, sizeof(copy[0]), hkSpuDmaManager::WRITE_NEW, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( variable, copy, sizeof(copy[0]));
}

hkInt32 HK_CALL hkSpuDmaUtils::getInt32FromMainMemory( HK_CPU_PTR(hkInt32*) variable, int dmaGroupId )
{
	HK_ALIGN16( hkInt32 buffer[4]);
	hkInt32* copy = hkAddByteOffset( &buffer[0], hkUlong(variable)&0xf);
	hkSpuDmaManager::getFromMainMemorySmall(copy, variable, sizeof(copy[0]), hkSpuDmaManager::READ_COPY, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( variable, copy, sizeof(copy[0]));
	return copy[0];
}


void* hkSpuDmaUtils::getPntrFromMainMemory( HK_CPU_PTR(void**) variable, int dmaGroupId  )
{
	HK_ALIGN16( void* buffer[4]);
	void** copy = hkAddByteOffset( &buffer[0], hkUlong(variable)&0xf);
	hkSpuDmaManager::getFromMainMemorySmall(copy, variable, sizeof(copy[0]), hkSpuDmaManager::READ_COPY, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( variable, copy, sizeof(copy[0]));
	return copy[0];
}


void hkSpuDmaUtils::setFloat32InMainMemory( HK_CPU_PTR(float*) dstInMainMemory, hkReal value, int dmaGroupId  )
{
	HK_ALIGN16( hkReal buffer[4]);
	hkReal* copy = hkAddByteOffset( &buffer[0], hkUlong(dstInMainMemory)&0xf);
	copy[0] = value;
	hkSpuDmaManager::putToMainMemorySmall(dstInMainMemory, copy, sizeof(copy[0]), hkSpuDmaManager::WRITE_NEW, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( dstInMainMemory, copy, sizeof(copy[0]));
}

// void hkSpuDmaUtils::setFloat16InMainMemory( HK_CPU_PTR(hkHalf*) dstInMainMemory, hkReal f, int dmaGroupId  )
// {
// 	HK_ALIGN16( hkHalf buffer[8]);
// 	hkHalf* copy = hkAddByteOffset( &buffer[0], hkUlong(dstInMainMemory)&0xf);
// 	copy[0] = f;
// 	hkSpuDmaManager::putToMainMemorySmall(dstInMainMemory, copy, sizeof(copy[0]), hkSpuDmaManager::WRITE_NEW, dmaGroupId);
// 	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
// 	HK_SPU_DMA_PERFORM_FINAL_CHECKS( dstInMainMemory, copy, sizeof(copy[0]));
// }


void hkSpuDmaUtils::setChar8InMainMemory( HK_CPU_PTR(hkChar*) dstInMainMemory, hkChar value, int dmaGroupId  )
{
	HK_ALIGN16( hkChar buffer[16]);
	hkChar* copy = hkAddByteOffset( &buffer[0], hkUlong(dstInMainMemory)&0xf);
	copy[0] = value;
	hkSpuDmaManager::putToMainMemorySmall(dstInMainMemory, copy, sizeof(copy[0]), hkSpuDmaManager::WRITE_NEW, dmaGroupId);
	hkSpuDmaManager::waitForDmaCompletion( dmaGroupId );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( dstInMainMemory, copy, sizeof(copy[0]));
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
