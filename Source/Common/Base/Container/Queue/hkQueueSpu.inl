/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

template <typename T>
inline hkBool hkQueue<T>::isEmpty() const
{
	return m_elementsInUse == 0;
}


template <typename T>
inline int hkQueue<T>::getSize() const
{
	return m_elementsInUse;
}


template <typename T>
inline int hkQueue<T>::getCapacity() const
{
	return m_capacity;
}


template <typename T>
inline void hkQueue<T>::clear()
{
	m_head = 0;
	m_tail = 0;
	m_elementsInUse = 0;
}

// Places a new element to the back of the queue and expand storage if necessary.
template <typename T>
inline void hkQueue<T>::enqueue( const T& element )
{
	HK_ASSERT2(0x81fa7245, m_elementsInUse < m_capacity, "Trying to add an element to a fixed size queue which is full");
	if( m_tail == m_capacity )
	{
		m_tail = 0;
	}
	void* ppuAddr = &m_data[m_tail];
	hkSpuDmaManager::putToMainMemoryAndWaitForCompletion( ppuAddr, &element, sizeof(element), hkSpuDmaManager::WRITE_NEW );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( ppuAddr, &element, sizeof(element) );
	m_tail++;

	m_elementsInUse++;
}

// Places a new element to the back of the queue and expand storage if necessary.
template <typename T>
inline void hkQueue<T>::enqueueInFront( const T& element )
{
	HK_ASSERT2(0x81fa7245, m_elementsInUse < m_capacity, "Trying to add an element to a fixed size queue which is full");

	if( m_head == 0 )
	{
		m_head = m_capacity;
	}

	void* ppuAddr = &m_data[--m_head];
	hkSpuDmaManager::putToMainMemoryAndWaitForCompletion( ppuAddr, &element, sizeof(element), hkSpuDmaManager::WRITE_NEW);
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( ppuAddr, &element, sizeof(element));
	m_elementsInUse++;
}


template <typename T>
inline void hkQueue<T>::dequeue( T& data )
{
	HK_ASSERT(0xf032ed23, m_elementsInUse );

	const void* ppuAddr = &m_data[m_head];
	hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion( &data, ppuAddr, sizeof(data), hkSpuDmaManager::READ_COPY );
	HK_SPU_DMA_PERFORM_FINAL_CHECKS( ppuAddr, &data, sizeof(data));

	if( ++m_head == m_capacity )
	{
		m_head = 0;
	}
	m_elementsInUse--;
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
