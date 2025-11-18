/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


template <typename TYPE>
void hkArraySpu::init( hkArray<TYPE>& arrayHeaderOnSpu, TYPE* storage, int storageCapacity)
{
	m_storage	= storage;
	m_capacity	= storageCapacity;
	m_numElems	= arrayHeaderOnSpu.getSize();

	const int numBytes = arrayHeaderOnSpu.getSize() * sizeof(TYPE);

		// cast to an inplace array so we can properly get the m_storage variable
		// and check for inplace array
	hkInplaceArray<TYPE,1>& ipa = reinterpret_cast<hkInplaceArray<TYPE,1>& >(arrayHeaderOnSpu);
	if ( ipa.stillInplaceUsingMask() )
	{
		// the compiler should optimize the ifs to the correct form
		if ( (sizeof(TYPE) & 0xf) == 0)
		{
			hkString::memCpy16( storage, &ipa.m_storage[0], numBytes >> 4 );
		}
		else
		{
			hkString::memCpy4( storage, &ipa.m_storage[0], (numBytes+3) >> 2 );
		}
		return;
	}
	else
	{
		// simply get the data using slow dma transfers
		hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion( storage, arrayHeaderOnSpu.begin(), HK_NEXT_MULTIPLE_OF(16,numBytes), hkSpuDmaManager::READ_COPY );
		HK_SPU_DMA_PERFORM_FINAL_CHECKS(arrayHeaderOnSpu.begin(), storage, HK_NEXT_MULTIPLE_OF(16,numBytes));
	}
}


template <typename ARRAY_TYPE>
void hkArraySpu::putArrayToMainMemory(ARRAY_TYPE& arrayOnPpu, ARRAY_TYPE& arrayHeaderOnSpu, int dmaGroup)
{
	hkArray<char>& arrayOnSpu = reinterpret_cast<hkArray<char>& >(arrayHeaderOnSpu);
	putArrayToMainMemoryImpl( arrayOnSpu, &arrayHeaderOnSpu.m_storage[0], &arrayOnPpu.m_storage[0], sizeof(arrayOnPpu.m_storage)/sizeof(arrayOnPpu.m_storage[0]), sizeof(arrayOnPpu.m_storage[0]), dmaGroup );
}


template <typename ARRAY_TYPE>
void hkArraySpu::putArrayToMainMemoryNotInplace(ARRAY_TYPE& arrayOnPpu, ARRAY_TYPE& arrayHeaderOnSpu, int dmaGroup)
{
	hkArray<char>& arrayOnSpu = reinterpret_cast<hkArray<char>& >(arrayHeaderOnSpu);
	putArrayToMainMemoryImpl( arrayOnSpu, HK_NULL, HK_NULL, 0, sizeof(*arrayOnPpu.m_data), dmaGroup );
}


template <typename TYPE>
void hkArraySpu::overwriteData( TYPE* data, int numElems)
{
	m_storage = data;
	m_numElems = numElems;
}


int hkArraySpu::getSize()
{
	return m_numElems;
}


template <typename TYPE>
TYPE& hkArraySpu::getValueAt(int i)
{
	HK_ASSERT(0xaf4e9c6c,  i >= 0 && i < m_numElems );
	TYPE* elems = reinterpret_cast<TYPE*>(m_storage.val());
	return elems[i];
}


template <typename TYPE>
const TYPE& hkArraySpu::getValueAt(int i) const
{
	HK_ASSERT(0xaf4718f3,  i >= 0 && i < m_numElems );
	const TYPE* elems = reinterpret_cast<const TYPE*>(m_storage);
	return elems[i];
}


template <typename TYPE>
void hkArraySpu::pushBack(const TYPE& t)
{
	if ( m_numElems == m_capacity )
	{
		HK_ASSERT2(0xaf354ee1, false, "Inplace array overflow.");
	}
	TYPE* elems = reinterpret_cast<TYPE*>(m_storage.val());
	elems[m_numElems] = t;
	m_numElems = m_numElems + 1;
}


/*
template <typename TYPE>
void hkArraySpu::removeAt(int index)
{
	TYPE* elems = reinterpret_cast<TYPE*>(m_storage);
	m_numElems = m_numElems - 1;
	elems[index] = elems[m_numElems];
}
*/


/*
template <typename TYPE>
TYPE& hkArraySpu::expandOne()
{
	TYPE* elem = reinterpret_cast<TYPE*>(hkAddByteOffset(m_storage, m_numElems * sizeof(TYPE)));
	m_numElems = m_numElems + 1;
	return *elem;
}
*/


/*
template <typename TYPE>
TYPE* hkArraySpu::begin() 
{
	TYPE* elems = reinterpret_cast<TYPE*>(m_storage);
	return elems;
}
*/

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
