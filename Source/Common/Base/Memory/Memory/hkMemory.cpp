/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

#if HK_CONFIG_MEMORY_CLASS == HK_CONFIG_MEMORY_CLASS_ENABLED

void HK_CALL HK_ASSERT_OBJECT_SIZE_OK_FUNC(hk_size_t nbytes);
void HK_CALL HK_ASSERT_OBJECT_SIZE_OK_FUNC(hk_size_t nbytes)
{
	// object size must be representable in 15 bits.
	HK_ASSERT2(0x13aa0880,  nbytes <= (hkUint16(-1)>>1), "Object is too big");
}

hkMemory* hkMemory::s_instance;

hkInt32 hkMemory::s_fillGuardArea = hkMemory::MEMORY_FILL_GUARD_AREA;
hkInt32 hkMemory::s_fillFreeSpace = hkMemory::MEMORY_FILL_FREE_SPACE;
hkInt32 hkMemory::s_fillReturnedToUser = hkMemory::MEMORY_FILL_RETURNED_TO_USER;

hkMemory::hkMemory() : m_referenceCount(1)
{
    m_memoryUsed = 0;
	m_memoryState = hkMemory::MEMORY_STATE_OK;
	m_criticalMemoryLimit = 0x7fffffff;
}



hkMemory::~hkMemory()
{
}

// given a 4 byte aligned pointer, round it up to align and
// store the offset just before the returned pointer.
static HK_FORCE_INLINE void* HK_CALL hkMemoryRoundUp(void* pvoid, int align)
{
	HK_ASSERT2(0x38c3fe7c,  (reinterpret_cast<hkUlong>(pvoid) & 0x3) == 0, "Pointer was not 4 byte aligned");
	char* p = reinterpret_cast<char*>(pvoid);
	char* aligned = reinterpret_cast<char*>(
				HK_NEXT_MULTIPLE_OF( align,	reinterpret_cast<hkUlong>(p+1)) );
	reinterpret_cast<int*>(aligned)[-1] = (int)(aligned - p);
	return aligned;
}

// given a pointer from hkMemoryRoundUp, recover the original pointer.
static HK_FORCE_INLINE void* HK_CALL hkMemoryRoundDown(void* p)
{
	int offset = reinterpret_cast<int*>(p)[-1];
	return static_cast<char*>(p) - offset;
}



#if defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_XBOX) || defined (HK_PLATFORM_XBOX360)

#	include <Common/Base/Fwd/hkcmalloc.h>

	static void* HK_CALL hkWindowsMalloc(int size, int align)
	{
		return _aligned_malloc(size, align);
	}

	static void HK_CALL hkWindowsFree(void* p)
	{
		_aligned_free(p);
	}

	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkWindowsMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkWindowsFree;

#elif defined(HK_PLATFORM_UNIX) || defined(HK_PLATFORM_PS2) || defined( HK_PLATFORM_PSP )

#	include <Common/Base/Fwd/hkcmalloc.h>
	static void* HK_CALL hkStandardMalloc(int size, int align)
	{
		return memalign(align, size);
	}
	static void HK_CALL hkStandardFree(void* p)
	{
		free(p);
	}

	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkStandardMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkStandardFree;

#elif defined(HK_PLATFORM_GC)

#if defined(HK_PLATFORM_RVL)
#	include <revolution/mem.h>

	// Our demos use Mem2 for DemoAllocator2
	extern MEMAllocator	DemoAllocator2;

	static void* HK_CALL hkRevolutionMalloc(int size, int align)
	{
		HK_ASSERT(0x76a0c45d, sizeof(hk_size_t)==sizeof(char*));
		void* p = MEMAllocFromAllocator( &DemoAllocator2, size + align);
		return hkMemoryRoundUp(p, align);
	}

	static void HK_CALL hkRevolutionFree(void* p)
	{
		void* origp = hkMemoryRoundDown(p);
		MEMFreeToAllocator( &DemoAllocator2, origp );
	}

	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkRevolutionMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkRevolutionFree;
#else
#	define HEAP_ID 0
#	include <dolphin.h>

	static void* HK_CALL hkGameCubeMalloc(int size, int align)
	{
		HK_ASSERT(0x76a0c45d, sizeof(hk_size_t)==sizeof(char*));

		void* p = OSAllocFromHeap(HEAP_ID, size + align);
		return hkMemoryRoundUp(p, align);
	}

	static void HK_CALL hkGameCubeFree(void* p)
	{
		void* origp = hkMemoryRoundDown(p);
		OSFreeToHeap(HEAP_ID, origp);
	}

	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkGameCubeMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkGameCubeFree;
#endif

#elif defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC) || defined( HK_PLATFORM_PS3)

	static void* HK_CALL hkDarwinMalloc(int size, int align)
	{
		HK_ASSERT(0x43a08b2e, sizeof(hk_size_t)==sizeof(char*));

		void* p = new char[size + align];
		return hkMemoryRoundUp(p, align);
	}

	static HK_FORCE_INLINE void HK_CALL hkDarwinFree(void* p)
	{
		void* origp = hkMemoryRoundDown(p);
		delete [] (char*)(origp);
	}

	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkDarwinMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkDarwinFree;

#elif defined (HK_PLATFORM_PS3SPU)

	static void* HK_CALL hkNoMalloc(int size, int align)
	{
		HK_ASSERT(0,0);
		return HK_NULL;
	}

	static HK_FORCE_INLINE void HK_CALL hkNoFree(void* p)
	{
		HK_ASSERT(0,0);
	}
	void* (HK_CALL *hkSystemMalloc)(int size, int align) = hkNoMalloc;

	void (HK_CALL *hkSystemFree)(void* p) = hkNoFree;

#else

#	error no hkSystem{Malloc,Free} defined for this platform.

#endif


void HK_CALL hkMemory::replaceInstance(hkMemory* m)
{
	if ( m )
	{
		m->addReference();
	}

	if(s_instance)
	{
		s_instance->removeReference();
	}
	s_instance = m;
}

int hkMemory::getAllocatedSize( int size )
{
	if ( size > 16 )
	{
		size = HK_NEXT_MULTIPLE_OF( 16, size );
		return size+16;
	}
	return size + 8;
}

//default impl, see DebugMemory for a proper impl
hkBool hkMemory::isOk() const
{
	return true;
}

#endif //HK_CONFIG_MEMORY_CLASS == HK_CONFIG_MEMORY_CLASS_ENABLED


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
