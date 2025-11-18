/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

#include <Common/Base/Spu/Dma/Writer/hkSpuDmaWriter.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpuDmaCache.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>


#ifdef HK_PLATFORM_HAS_SPU

void spudmautils_testDmaManager();
void spudmautils_testDmaWriter();
void spudmautils_testDmaCache();



int spudmautils_main()
{
	spudmautils_testDmaManager();
	spudmautils_testDmaWriter();
	spudmautils_testDmaCache();

	return 0;
}



void spudmautils_testDmaManager()
{
	hkUint8* bufferOnPpu[2];
	hkUint8* bufferOnSpu;
	const int size = 1000000;
	bufferOnPpu[0] = hkAllocateChunk<hkUint8>(size, HK_MEMORY_CLASS_USER);
	bufferOnPpu[1] = hkAllocateChunk<hkUint8>(size, HK_MEMORY_CLASS_USER);
	bufferOnSpu    = hkAllocateChunk<hkUint8>(size, HK_MEMORY_CLASS_USER);

	//
	// test dma reading/transfer from ppu memory to spu memory
	//
	{
		//
		// fill reference buffer 0 with random data
		//
		for(int i = 0; i < size; i++)
		{
			bufferOnPpu[0][i] = hkUint8(i);
		}

		hkSpuDmaManager::getFromMainMemory(bufferOnSpu, bufferOnPpu[0], size, hkSpuDmaManager::READ_ONLY, 1);
		hkSpuDmaManager::waitForDmaCompletion( HK_DMAWAIT_BITSHIFT(1) );

		//
		// compare both buffers
		//
		int areDifferent = hkString::memCmp(bufferOnPpu[0], bufferOnSpu, size);
		HK_TEST( !areDifferent );

		hkSpuDmaManager::performFinalChecks(bufferOnSpu, bufferOnPpu[0], size);
	}

	//
	// test dma writing/transfer from spu memory back to ppu memory
	//
	{
		hkSpuDmaManager::putToMainMemory(bufferOnPpu[1], bufferOnSpu, size, hkSpuDmaManager::WRITE_NEW, 1);
		hkSpuDmaManager::waitForDmaCompletion( HK_DMAWAIT_BITSHIFT(1) );

		//
		// compare both buffers
		//
		int areDifferent = hkString::memCmp(bufferOnPpu[0], bufferOnPpu[1], size);
		HK_TEST( !areDifferent );

		hkSpuDmaManager::performFinalChecks(bufferOnPpu[1], bufferOnSpu, size);
	}

	hkDeallocateChunk(bufferOnPpu[0], size, HK_MEMORY_CLASS_USER);
	hkDeallocateChunk(bufferOnPpu[1], size, HK_MEMORY_CLASS_USER);
	hkDeallocateChunk(bufferOnSpu,    size, HK_MEMORY_CLASS_USER);
}



void spudmautils_testDmaWriter()
{
	hkUint8* bufferOnPpu[2];
	const int size = 1024*16;
	bufferOnPpu[0] = hkAllocateChunk<hkUint8>(size, HK_MEMORY_CLASS_USER);
	bufferOnPpu[1] = hkAllocateChunk<hkUint8>(size, HK_MEMORY_CLASS_USER);

	//
	// fill reference buffer 0 with random data
	//
	for(int i = 0; i < size; i++)
	{
		bufferOnPpu[0][i] = hkUint8(i);
	}

	//
	// scramble contents of working buffer 1
	//
	for(int i = 0; i < size; i++)
	{
		bufferOnPpu[1][i] = hkUint8(0xff);
	}

	//
	// perform a buffered dma-write to buffer 1 (using buffer 0 as input)
	//
	{
		HK_ALIGN16( hkUint8 buffer[2*(256+512)] );
		hkSpuDmaWriter dmaWriter;
		dmaWriter.init(bufferOnPpu[1], size, buffer, 256, 512, 0, 1);

		int currPos = 0;
		int currBlockSize = 16;
		hkBool lastIteration = false;
		while ( currPos < size )
		{

			//
			// avoid overflow
			//
			if ( (currPos + currBlockSize) > size )
			{
				currBlockSize = size - currPos;
			}

			//
			// get buffer and write to it
			//
			void* bufferSpu;
			{
				bufferSpu = dmaWriter.requestBuffer();
				hkString::memCpy(bufferSpu, bufferOnPpu[0]+currPos, currBlockSize);
			}

			//
			// transfer buffer content from spu memory to main memory
			//
			dmaWriter.finishWrite((void*)(hkUlong(bufferSpu)+currBlockSize));

			currPos += currBlockSize;

		}
	}

	//
	// compare both buffers
	//
	int areDifferent = hkString::memCmp(bufferOnPpu[0], bufferOnPpu[1], size);
	HK_TEST( !areDifferent );

	hkDeallocateChunk(bufferOnPpu[0], size, HK_MEMORY_CLASS_USER);
	hkDeallocateChunk(bufferOnPpu[1], size, HK_MEMORY_CLASS_USER);
}


struct CachedObjectInfo
{
	CachedObjectInfo(const hkVector4* inMainMem, const hkVector4* inCache) : m_objectInMainMemory(inMainMem), m_objectInCache(inCache) {}
	const hkVector4* m_objectInMainMemory;
	const hkVector4* m_objectInCache;
};


void spudmautils_testDmaCache()
{

// have also counters for statistics.
	hkPseudoRandomGenerator generator(345);

	// have a big array for 'main memory' image
	hkArray<hkVector4> mainMemory;
	{
		for ( int i = 0; i < 1000; i++)
		{
			 generator.getRandomVector11(mainMemory.expandOne());
		}
	}

	// have a big array for 'local image' pointers.
	hkArray<CachedObjectInfo> cachedObjectInfos;

	hkSpuDmaCache<hkVector4, 64, 128> cache;
	cache.init(0, 4);


	int sumOverflowElements = 0;
	int numOverflowChecks = 0;
	int numPlacementsIntoCacheRows = 0;
	int numPlacementsIntoOverflowBuffer = 0;

	// have a for (i = .. ) loop and generate 'main memory' indices with a hashin alg.
	for ( int i = 0; i < 5; i++)
	{

		if (i%2 == 0)
		{
			// copy stuff to cache (say 100 elems.)
			for ( int k = 0; k < 100; k++ )
			{
				int idx = generator.getRand32() % mainMemory.getSize();
				const hkVector4* cachedObject = cache.getFromMainMemory(&mainMemory[idx]);
				cache.waitForDmaCompletion( cachedObject );
				cachedObjectInfos.pushBack( CachedObjectInfo( &mainMemory[idx], cachedObject ) );

				
				sumOverflowElements += cache.getNumOverflowCacheLinesUsed();
				numOverflowChecks++;

				( cache.didTheObjectGoToOverflowBuffer(cachedObject) ? numPlacementsIntoOverflowBuffer : numPlacementsIntoCacheRows )++;

			}
		}
		else
		{
			// or remove say (the first 50 elems.)
			for ( int k = 0; k < 50; k++ )
			{
				int idx = generator.getRand32() % cachedObjectInfos.getSize();
				const hkVector4* cachedObject = cachedObjectInfos[idx].m_objectInCache;
				cache.releaseObjectAt( cachedObject );
				cachedObjectInfos.removeAt(idx);
			}
			
		}

		// test if all cached images are ok
		{
			for (int i = 0; i < cachedObjectInfos.getSize(); i++)
			{
				const hkVector4& a = *cachedObjectInfos[i].m_objectInMainMemory;
				const hkVector4& b = *cachedObjectInfos[i].m_objectInCache;
				for(int coord = 0; coord < 3; coord++)
				{
					HK_TEST( a(coord) == b(coord) );
				}
			}
		}
	}

	// remove all & check if all cache elements are unlocked
	{
		{
			for ( int k = 0; k < cachedObjectInfos.getSize(); k++ )
			{
				const hkVector4* cachedObject = cachedObjectInfos[k].m_objectInCache;
				cache.releaseObjectAt( cachedObject );
			}

			cachedObjectInfos.clear();
		}

		HK_TEST( cache.areAllCacheLinesUnlocked() );
	}

	cache.exit();



	//---------------------

	// upon every 'fetch to cache' check whether the image went to cache rows or overflow buffer.
	// --- make it a utility funct hkSpuDmaCacheUtil::whereDidMyObjectGo(cache*, addressOnSpu*);
	//  -- also check average size of the overflow buffer usage -- again a util.
	// 
}


#else

int spudmautils_main()
{
	return 0;
}

#endif

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(spudmautils_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
