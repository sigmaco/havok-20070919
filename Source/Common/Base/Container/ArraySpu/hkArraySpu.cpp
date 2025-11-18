/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/Container/ArraySpu/hkArraySpu.h>


void hkArraySpu::putArrayToMainMemoryImpl( hkArray<char>& arrayHeaderOnSpu, void* inplaceStorageOnSpu, void* inplaceStorageOnPpu, int numInplaceCapacityOnPpu, int elemSize, int dmaGroup )
{
	int numElems = m_numElems;
	int numBytes = numElems * elemSize;

	arrayHeaderOnSpu.m_size = numElems;

	HK_ASSERT2( 0xf034d565, (numInplaceCapacityOnPpu == 0) || (numInplaceCapacityOnPpu * elemSize >= 8), "Your inplace array size is not big enough to guarantee 16 byte alignment for non inplace arrays" );

	int capacityAndFlags = arrayHeaderOnSpu.m_capacityAndFlags;
	int capacity = capacityAndFlags & static_cast<int>(arrayHeaderOnSpu.CAPACITY_MASK);

	if ( numElems <= numInplaceCapacityOnPpu && numInplaceCapacityOnPpu > 0 )
	{
		// now our data fits into the inplace storage on ppu, simply copy data over
		hkString::memCpy4( inplaceStorageOnSpu, m_storage, (numBytes+3) >> 2 );
		if ( (capacityAndFlags & arrayHeaderOnSpu.DONT_DEALLOCATE_FLAG) == 0 )
		{
			hkThreadMemory::getInstance().deallocateChunk( arrayHeaderOnSpu.begin(), capacity * elemSize, HK_MEMORY_CLASS_ARRAY);
			capacityAndFlags = numInplaceCapacityOnPpu | arrayHeaderOnSpu.DONT_DEALLOCATE_FLAG;
		}
		arrayHeaderOnSpu.m_data = (char*)inplaceStorageOnPpu;
	}
	else
	{
		char* dataOnPpu = arrayHeaderOnSpu.begin();
		if ( numElems > capacity )
		{
			// free old array
			if( (capacityAndFlags & arrayHeaderOnSpu.DONT_DEALLOCATE_FLAG) == 0)
			{
				hkThreadMemory::getInstance().deallocateChunk( dataOnPpu, capacity * elemSize, HK_MEMORY_CLASS_ARRAY);
			}

			// double the capacity
			while ( capacity < numElems) { capacity += capacity; }

			// allocate new array
			dataOnPpu = (char*)hkThreadMemory::getInstance().allocateChunk( capacity * elemSize, HK_MEMORY_CLASS_ARRAY);
			arrayHeaderOnSpu.m_data = dataOnPpu;
			capacityAndFlags = capacity;
		}
		hkSpuDmaManager::putToMainMemory( dataOnPpu, m_storage, HK_NEXT_MULTIPLE_OF(16,numBytes), hkSpuDmaManager::WRITE_NEW, dmaGroup);
		HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT(dataOnPpu, m_storage, HK_NEXT_MULTIPLE_OF(16,numBytes));
	}
	arrayHeaderOnSpu.m_capacityAndFlags = capacityAndFlags;
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
