/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/PointerMap/hkPointerMapBase.h>

// Quick description:
// The hash table is stored as a linear list. Initially all keys
// are zero (empty). When we insert an element, we jump to the items
// hash and scan forwards until we find the key or we come to a zero entry.
// If the hash function is good and the table is not too crowded, we're
// likely to have good performance and be cache friendly. Values for index i
// are stored at m_elem[ i + size of table ]. We should consider storing the
// values directly following the keys - that would save a cache miss if
// there arent too many hash collisions.




template < typename T >
hkPointerMapBase<T>::hkPointerMapBase()
{
	const int initialCapacity = 16;
	m_elem = hkAllocateChunk<T>(initialCapacity*2, HK_MEMORY_CLASS_ARRAY);
	m_numElems = 0;
	m_hashMod = initialCapacity - 1;

	// clear the table
	clear();
}

static inline bool isPower2(unsigned int v)
{
	return (v & (v - 1)) == 0;
}

template < typename T >
hkPointerMapBase<T>::hkPointerMapBase(void* ptr, int sizeInBytes)
{
	int maxKeys = unsigned(sizeInBytes) / (2*sizeof(T)); // unsigned div = shift
	HK_ASSERT( 0x549309be, isPower2(maxKeys) );
	m_elem = static_cast<T*>(ptr);
	m_numElems = DONT_DEALLOCATE_FLAG;
	m_hashMod = maxKeys - 1;
	HK_ASSERT( 0x549309bf, (maxKeys*hkSizeOf(T)) == (sizeInBytes/2) );
	{ for (int i = 0; i < maxKeys; i++) { m_elem[i] = T(HK_POINTERMAP_EMPTY_KEY); } }
}

template < typename T >
void hkPointerMapBase<T>::clear()
{
	int initialCapacity = m_hashMod+1;
	{ for (int i = 0; i < 2 * initialCapacity; i++) { m_elem[i] = T(HK_POINTERMAP_EMPTY_KEY); } }
	m_numElems = 0 | (m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG));
}

template < typename T >
void hkPointerMapBase<T>::swap( hkPointerMapBase& other )
{
	T* te = m_elem;
	hkUlong tn = m_numElems;
	hkUlong th = m_hashMod;
	m_elem = other.m_elem;
	m_numElems = other.m_numElems;
	m_hashMod = other.m_hashMod;
	other.m_elem = te;
	other.m_numElems = static_cast<int>(tn);
	other.m_hashMod = static_cast<int>(th);
}

template < typename T >
hkPointerMapBase<T>::~hkPointerMapBase()
{
	if( (m_numElems & DONT_DEALLOCATE_FLAG) == 0)
	{
		hkDeallocateChunk<T>( m_elem, (m_hashMod+1)*2, HK_MEMORY_CLASS_ARRAY );
	}
}

template < typename T >
void hkPointerMapBase<T>::insert( T key, T val )
{
	HK_ASSERT2(0x19291575, key != 0, "pointer map keys must be nonzero");
	// This is quite conservative. We could grow more
	// slowly at the cost of potentially longer searches.
	int numElems = m_numElems & static_cast<int>(NUM_ELEMS_MASK);
	if( (numElems + numElems) > m_hashMod )
	{
		resizeTable(m_hashMod + m_hashMod + 2);
	}
	
	T i;
	for( i = pointerHash(key, m_hashMod);
		(m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY)) && (m_elem[i] != key);
		i = (i+1) & m_hashMod )
	{
		// find free slot
	}

	// dont increment m_numElems if overwriting.
	m_numElems += (m_elem[i] != key);

	// insert key,value
	m_elem[i] = key;
	m_elem[ i + m_hashMod + 1 ] = val;
}

template < typename T >
typename hkPointerMapBase<T>::Iterator hkPointerMapBase<T>::findKey( T key ) const
{
	for( T i = pointerHash(key, m_hashMod);
		m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY);	
		i = (i+1) & m_hashMod)
	{
		if( m_elem[i] == key )
		{
			return reinterpret_cast<Iterator>( i ); // found
		}
	}
	return reinterpret_cast<Iterator>( T(m_hashMod+1) ); // not found
}


template < typename T >
hkResult hkPointerMapBase<T>::get( T key, T* out ) const
{
	Iterator it = findKey(key);
	if( isValid(it) )
	{
		*out = getValue(it);
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

template < typename T >
T hkPointerMapBase<T>::getWithDefault( T key, T def ) const
{
	for( T i = pointerHash(key, m_hashMod);
		m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY);	
		i = (i+1) & m_hashMod)
	{
		if( m_elem[i] == key )
		{
			return (T)m_elem[i+m_hashMod+1];
		}
	}
	return def;
}

template < typename T >
void hkPointerMapBase<T>::remove( Iterator it )
{
	HK_ASSERT(0x5a6d564c, isValid(it));
	T i = reinterpret_cast<T>(it);

	// remove it
	--m_numElems;
	m_elem[i] = T(HK_POINTERMAP_EMPTY_KEY);

	// find lowest element of this unbroken run
	T lo = ( i + m_hashMod ) & m_hashMod;
	while( m_elem[lo] != T(HK_POINTERMAP_EMPTY_KEY) )
	{
		lo = ( lo + m_hashMod ) & m_hashMod;
	}
	lo = ( lo + 1 ) & m_hashMod;

	// the slot which has become empty
	T empty = i;
	
	// shift up, closing any gaps we find
	for(i = (i + 1) & m_hashMod;
		m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY); // end of run
		i = (i + 1) & m_hashMod )
	{
		T hash = pointerHash( m_elem[i], m_hashMod );

		// Three cases to consider here. 
		// a) The normal case where lo <= empty < i.
		// b) The case where i has wrapped around.
		// c) The case where both i and empty have wrapped around.
		// The initial case will be a. (Or b if the last slot is freed).
		// and may progress to b, and finally c.
		// The algorithm will terminate before 'i' reaches 'lo'
		// otherwise the table would have no free slots.
		
		// 'normal'      'i wrapped'   'i and empty wrapped'
		// ===== lo      ===== i       ===== empty
		// ===== empty   ===== lo      ===== i 
		// ===== i       ===== empty   ===== lo     

		
		if( ( i >= lo ) && ( hash > empty ) )
		{
			continue;					
		}
		else if( ( i < empty ) && ( hash > empty || hash <= i ) )
		{
			continue;
		}
		else if( /*i > empty && */ ( hash > empty && hash < lo ) )
		{
			continue;
		}
		HK_ASSERT(0x45e3d455,  i != empty ); // by design
		HK_ASSERT(0x5ef0d6c0,  i != lo ); // table became full?!

		// copy up
		m_elem[empty] = m_elem[i];
		m_elem[empty+m_hashMod+1] = m_elem[i+m_hashMod+1];
		// source slot is now free
		m_elem[i] = T(HK_POINTERMAP_EMPTY_KEY);
		empty = i;
	}
}

template < typename T >
hkResult hkPointerMapBase<T>::remove( T key )
{
	Iterator it = findKey(key);
	if( isValid(it) )
	{
		remove(it);
		return HK_SUCCESS;
	}
	return HK_FAILURE;	
}

template < typename T >
void hkPointerMapBase<T>::reserve( int numElements )
{
	// Make sure that the actual table size is not going to be less than twice the current number of elements
	HK_ASSERT(0x4d0c5314, numElements > 0 && (m_numElems & static_cast<int>(NUM_ELEMS_MASK)) * 2 < numElements * 3 );
	// Reserve 3 times as much space as the expected number of elements
	numElements *= 3;
	// The size needs to be a power of two
	int size = 4;
	while (size < numElements) { size *= 2; }
	
	resizeTable( size );
}

template < typename T >
void hkPointerMapBase<T>::resizeTable(int newcap)
{
	HK_ASSERT2(0x57c91b4a,  m_numElems < newcap, "table size is not big enough" );
	HK_ASSERT2(0x6c8f2576,  HK_NEXT_MULTIPLE_OF(2, newcap) == newcap, "table size should be a power of 2" );
	
	int dontDeallocate = m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG);
	int oldcap = m_hashMod+1;
	T* oldelem = m_elem;
	m_elem = hkAllocateChunk<T>(newcap*2, HK_MEMORY_CLASS_ARRAY); // space for values too
	{ for (int i = 0; i < newcap; i++) { m_elem[i] = T(HK_POINTERMAP_EMPTY_KEY); } } // dont bother to zero values, only keys
	m_numElems = 0;
	m_hashMod = newcap - 1;

	for( int i = 0; i < oldcap; ++i )
	{
		if( oldelem[i] != T(HK_POINTERMAP_EMPTY_KEY) )
		{
			insert( oldelem[i], oldelem[i+oldcap] );
		}
	}

	if (dontDeallocate == 0)
	{
		hkDeallocateChunk<T>( oldelem, oldcap*2, HK_MEMORY_CLASS_ARRAY );
	}
}

template < typename T >
hkBool hkPointerMapBase<T>::isOk() const
{
	// is count consistent?
	int count = 0;
	int i;
	for( i = 0; i <= m_hashMod; ++i )
	{
		count += m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY);
	}
	HK_ASSERT(0x26f64ec4,  count == (m_numElems & static_cast<int>(NUM_ELEMS_MASK)) );

	// is element reachable from its hash?
	for( i = 0; i <= m_hashMod; ++i )
	{
		if( m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY) )
		{
			T j = pointerHash( m_elem[i], m_hashMod );
			while( m_elem[j] != m_elem[i] )
			{
				j = (j + 1) & m_hashMod;
				HK_ASSERT(0x4f6528df,  m_elem[j] != T(HK_POINTERMAP_EMPTY_KEY) );
			}
		} 
	}
	return true;
}

template < typename T >
int hkPointerMapBase<T>::getSizeInBytesFor(int numOfKeys)
{
	// adjust the number to the power of 2
	int requiredNum = 4;
	while (requiredNum < numOfKeys) { requiredNum *= 2; }
	// calculate the table size in bytes:
	// (key,value) * (num keys) * (fill factor)
	return (sizeof(T)*2) * requiredNum * 2;
}


#if !defined(_MSC_VER) || (_MSC_VER != 1300) // Proceeding template instatiation is not required and not liked by .Net 7.0
  template < typename T > class hkPointerMapBase<T>::MustEndWithSemiColon {};
#endif

template class hkPointerMapBase<hkUlong>;
#if HK_POINTER_SIZE == 4
template class hkPointerMapBase<hkUint64>;
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
