/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Fwd/hkcstring.h>


using namespace std;


#if !defined(HK_PLATFORM_PS3SPU)

HK_COMPILE_TIME_ASSERT( sizeof(void*)==sizeof(char*) );

// hack to force this to be out of line
void hkSmallArrayUtil::_reserve(void* array, int numElem, int sizeElem)
{
	HK_ASSERT2(0x3b67c014, numElem >= 0, "Number of elements must not be negative");
	HK_ASSERT2(0x243bf8d1, sizeElem >= 0, "The size of an element must not be negative");

	typedef hkSmallArray<char> hkAnyArray;

	char* p = static_cast<char*>(hkThreadMemory::getInstance().allocateChunk(numElem*sizeElem, HK_MEMORY_CLASS_ARRAY));
	hkAnyArray* self = reinterpret_cast< hkAnyArray* >(array);
	::memcpy(p, self->m_data, self->m_size*sizeElem);
	//cannot call self->releaseMemory(), because we're lying about the size of each element.
	if( (self->m_capacityAndFlags & hkAnyArray::DONT_DEALLOCATE_FLAG) == 0)
	{
		hkThreadMemory::getInstance().deallocateChunk( self->m_data, self->getCapacity()*sizeElem, HK_MEMORY_CLASS_ARRAY);
	}
	
	self->m_data = p;
	self->m_capacityAndFlags = hkUint16( numElem | (self->m_capacityAndFlags & hkAnyArray::LOCKED_FLAG)); // prop the locked flag? (even though we have realloced..)
}
#endif


// hack to force this to be out of line
void hkSmallArrayUtil::_reserveMore(void* array, int sizeElem)
{
#if !defined(HK_PLATFORM_SPU)
	HK_ASSERT2(0x5828d5cf, sizeElem >= 0, "The size of an element must not be negative");

	typedef hkSmallArray<char> hkAnyArray;
	hkAnyArray* self = reinterpret_cast< hkAnyArray* >(array);
	int numElem = (self->m_size ? self->m_size*2 : 1);

	char* p = static_cast<char*>(hkThreadMemory::getInstance().allocateChunk(numElem*sizeElem, HK_MEMORY_CLASS_ARRAY));
	::memcpy(p, self->m_data, self->m_size*sizeElem);
	//cannot call self->releaseMemory(), because we're lying about the size of each element.
	if( (self->m_capacityAndFlags & hkAnyArray::DONT_DEALLOCATE_FLAG) == 0)
	{
		hkThreadMemory::getInstance().deallocateChunk( self->m_data, self->getCapacity()*sizeElem, HK_MEMORY_CLASS_ARRAY);
	}
	
	self->m_data = p;
	self->m_capacityAndFlags = hkUint16(numElem | (self->m_capacityAndFlags & hkAnyArray::LOCKED_FLAG)); // prop the locked flag? (even though we have realloced..)
#endif
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
