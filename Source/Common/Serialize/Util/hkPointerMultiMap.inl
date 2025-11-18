/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
template <typename VALUE>
int hkPointerMultiMap<VALUE>::getFreeIndex()
{
	int i;
	if( m_freeChainStart != -1 )
	{
		i = m_freeChainStart;
		m_freeChainStart = m_valueChain[m_freeChainStart].next;
	}
	else
	{
		i = m_valueChain.getSize();
		m_valueChain.expandOne();
	}
	return i;
}

template <typename VALUE>
int hkPointerMultiMap<VALUE>::getFirstIndex( void* p )
{
	return m_indexMap.getWithDefault(p, -1);
}

template <typename VALUE>
void hkPointerMultiMap<VALUE>::insert( void* p, const VALUE& value )
{
	int chainIndex = m_indexMap.getWithDefault(p, -1);
	int thisIndex = getFreeIndex();
	Value& ref = m_valueChain[thisIndex];
	ref.value = value;
	ref.next = chainIndex;
	m_indexMap.insert( p, thisIndex );
}

template <typename VALUE>
int hkPointerMultiMap<VALUE>::addPendingValue( const VALUE& value, int nextIndex )
{
	int thisIndex = getFreeIndex();
	Value& v = m_valueChain[thisIndex];
	v.value = value;
	v.next = nextIndex;
	return thisIndex;
}

template <typename VALUE>
void hkPointerMultiMap<VALUE>::realizePendingPointer( void* p, int index )
{
	HK_ASSERT(0x66e29b43, m_indexMap.hasKey(p) == false );
	HK_ASSERT(0x71031385, m_valueChain[index].next || 1 ); // assert index ok
	m_indexMap.insert(p, index);
}

template <typename VALUE>
void hkPointerMultiMap<VALUE>::clear()
{
	m_valueChain.clear();
	m_indexMap.clear();
	m_freeChainStart = -1;
}

template <typename VALUE>
int hkPointerMultiMap<VALUE>::removeByIndex( void* key, int removeIndex )
{
#ifdef HK_DEBUG
	{
		int i = m_indexMap.getWithDefault( key, -2 );
		HK_ASSERT2(0, i != -2, "key is not in map");
		while( i != -1 && i != removeIndex )
		{
			i = m_valueChain[i].next;
		}
		HK_ASSERT2(0, i != -1, "value is not accessible from key");
	}
#endif
	// to remove from singly linked list, overwrite
	// current with next and actually remove next.
	int freeIndex = m_valueChain[removeIndex].next; // elem to add to free list
	if( freeIndex != -1 )
	{
		m_valueChain[removeIndex] = m_valueChain[freeIndex];
	}
	else // last element in chain, look at head
	{
		hkPointerMap<void*, int>::Iterator it = m_indexMap.findKey(key);
		freeIndex = m_indexMap.getValue(it);
		if( freeIndex != removeIndex ) // not the last value
		{
			m_valueChain[removeIndex] = m_valueChain[freeIndex];
			m_indexMap.setValue(it, removeIndex);
		}
		else // last value
		{
			m_indexMap.setValue(it, -1);
			removeIndex = -1;
		}
	}
	m_valueChain[freeIndex].next = m_freeChainStart;
	m_freeChainStart = freeIndex;
	return removeIndex;
}

template <typename VALUE>
int hkPointerMultiMap<VALUE>::removeByValue( void* key, const VALUE& v )
{
	for( int i = getFirstIndex(key);
			i != -1;
			i = getNextIndex(i) )
	{
		if( getValue(i) == v )
		{
			return removeByIndex(key, i);
		}
	}
	HK_ASSERT2(0, 0, "value not in map");
	return -1;
}

template <typename VALUE>
void hkPointerMultiMap<VALUE>::removeKey( void* key )
{
	hkPointerMap<void*, int>::Iterator it = m_indexMap.findKey(key);
	HK_ASSERT(0, m_indexMap.isValid(it) );
	int start = m_indexMap.getValue(it);
	m_indexMap.remove(it);
	if( start != -1 )
	{
		int end = start;
		while( m_valueChain[end].next != -1 )
		{
			end = m_valueChain[end].next;
		}
		m_valueChain[end].next = m_freeChainStart;
		m_freeChainStart = start;
	}
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
