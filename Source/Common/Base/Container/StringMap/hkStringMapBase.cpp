/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/StringMap/hkStringMapBase.h>

#define HASH_EMPTY hkUlong(-1)

// Quick description:
// The hash table is stored as a linear list. Initially all keys
// are 0xff (empty). When we insert an element, we jump to the items
// hash and scan forwards until we find the key or we come to an empty entry.
// If the hash function is good and the table is not too crowded, we're
// likely to have good performance and be cache friendly.
// The first third of m_elem are the hashes, the second third the string pointers
// and the final third, the value pointers.

#define ELEM_HASH(i) (m_elem[i])
#define ELEM_KEY(i)  (m_elem[i+m_hashMod+1])
#define ELEM_VAL(i)  (m_elem[i+m_hashMod+m_hashMod+2])

#define NOT_EQUAL(i,hash,key) \
	((ELEM_HASH(i) != hash) || (hkString::strCmp( key, (const char*)ELEM_KEY(i) ) != 0))
#define EQUAL(i,hash,key) \
	((ELEM_HASH(i) == hash) && (hkString::strCmp( key, (const char*)ELEM_KEY(i) ) == 0))

static HK_FORCE_INLINE hkUlong stringHash(const char* key)
{
	hkUlong hash = 0;
	for( int i = 0; key[i] != HK_NULL; ++i )
	{
		hash = 31 * hash + key[i];
	}
	return hash & (hkUlong(-1)>>1); // reserve -1 for empty
}

hkStringMapBase::hkStringMapBase()
{
	const int initialCapacity = 16;
	m_elem = hkAllocateChunk<hkUlong>(initialCapacity*3, HK_MEMORY_CLASS_ARRAY);
	hkString::memSet( m_elem, 0xff, hkSizeOf(hkUlong) * initialCapacity );
	m_numElems = 0;
	m_hashMod = initialCapacity - 1;
}

hkStringMapBase::~hkStringMapBase()
{
	hkDeallocateChunk<hkUlong>( m_elem, (m_hashMod+1)*3, HK_MEMORY_CLASS_ARRAY );
}

hkStringMapBase* hkStringMapBase::operator=(const hkStringMapBase* other)
{
	// Deallocate our storage
	hkDeallocateChunk<hkUlong>( m_elem, (m_hashMod+1)*3, HK_MEMORY_CLASS_ARRAY );
	
	// Copy other storage
	this->m_hashMod = other->m_hashMod;
	this->m_numElems = other->m_numElems;
	m_elem = hkAllocateChunk<hkUlong>( (m_hashMod+1)*3, HK_MEMORY_CLASS_ARRAY);

	hkString::memCpy(m_elem, other->m_elem, (m_hashMod+1)*3);

	HK_ASSERT( 0x74305156, this->isOk());
	return this;
}

hkStringMapBase::Iterator hkStringMapBase::getIterator() const
{
	int i;
	for( i = 0; i <= m_hashMod; ++i )
	{
		if( ELEM_HASH(i) != HASH_EMPTY )
		{
			break;
		}
	}
	return reinterpret_cast<Iterator>( hkUlong(i) );
}

char* hkStringMapBase::getKey(Iterator it) const
{
	int i = static_cast<int>( reinterpret_cast<hkUlong>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	return (char*)ELEM_KEY(i);
}

hkUlong hkStringMapBase::getValue(Iterator it) const
{
	int i = static_cast<int>( reinterpret_cast<hkUlong>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	return ELEM_VAL(i);
}

void hkStringMapBase::setValue(Iterator it, hkUlong val)
{
	int i = static_cast<int>( reinterpret_cast<hkUlong>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	ELEM_VAL(i) = val;
}

hkStringMapBase::Iterator hkStringMapBase::getNext( Iterator it ) const
{
	int i = static_cast<int>( reinterpret_cast<hkUlong>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);

	for( i += 1; i <= m_hashMod; ++i )
	{
		if( ELEM_HASH(i) != HASH_EMPTY )
		{
			break;
		}
	}
	return reinterpret_cast<Iterator>( hkUlong(i) );
}

hkBool hkStringMapBase::isValid( Iterator it ) const
{
	int i = static_cast<int>( reinterpret_cast<hkUlong>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod+1);
	return i <= m_hashMod;
}

void hkStringMapBase::insert( const char* key, hkUlong val )
{
	hkUlong hash = stringHash(key);
	HK_ASSERT(0x3665dd06, hash != HASH_EMPTY);
	// This is quite conservative. We could grow more
	// slowly at the cost of potentially longer searches.
	if( (m_numElems + m_numElems ) > m_hashMod )
	{
		resizeTable(m_hashMod + m_hashMod + 2);
	}
	hkUlong i = hash & m_hashMod;
	while(1) // find free slot
	{
		if(ELEM_HASH(i) == HASH_EMPTY)
		{
			m_numElems += 1;
			break;
		}
		else if( NOT_EQUAL(i, hash, key) )
		{
			i = (i+1) & m_hashMod;
		}
		else // overwrite a key
		{
			break;
		}
	}
	
	// insert key,value
	ELEM_HASH(i) = hash;
	ELEM_KEY(i)  = reinterpret_cast<hkUlong>(key);
	ELEM_VAL(i)  = val;
}

hkStringMapBase::Iterator hkStringMapBase::findKey( const char* key ) const
{
	hkUlong hash = stringHash(key);
	for(	hkUlong i = hash & m_hashMod;
			ELEM_HASH(i) != HASH_EMPTY;
			i = (i+1) & m_hashMod )
	{
		if( EQUAL(i,hash,key) )
		{
			return reinterpret_cast<Iterator>(i);
		}
	}
	return reinterpret_cast<Iterator>( hkUlong(m_hashMod+1) ); // not found
}

hkResult hkStringMapBase::get( const char* key, hkUlong* out ) const
{
	Iterator it = findKey(key);
	if( isValid(it) )
	{
		*out = getValue(it);
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

hkUlong hkStringMapBase::getWithDefault( const char* key, hkUlong def ) const
{
	hkUlong ret = def;
	get(key, &ret);
	return ret;
}

void hkStringMapBase::remove( Iterator it )
{
	hkUlong i = reinterpret_cast<hkUlong>(it);

	// remove it
	--m_numElems;
	ELEM_HASH(i) = HASH_EMPTY;

	// find lowest element of this unbroken run
	hkUlong lo = ( i + m_hashMod ) & m_hashMod;
	while( ELEM_HASH(lo) != HASH_EMPTY )
	{
		lo = ( lo + m_hashMod ) & m_hashMod;
	}
	lo = ( lo + 1 ) & m_hashMod;

	// the slot which has become empty
	hkUlong empty = i;
	
	// sift up, closing any gaps we find
	for( i = (i + 1) & m_hashMod;
		ELEM_HASH(i) != HASH_EMPTY;
		i = (i+1) & m_hashMod )
	{
		hkUlong hmod = ELEM_HASH(i) & m_hashMod;

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
		
		if( ( i >= lo ) && ( hmod > empty ) )
		{
			continue;					
		}
		else if( ( i < empty ) && ( hmod > empty || hmod <= i ) )
		{
			continue;
		}
		else if( /*i > empty && */ ( hmod > empty && hmod < lo ) )
		{
			continue;
		}
		HK_ASSERT(0x3278358f,  i != empty ); // by design
		HK_ASSERT(0x7e3aeff8,  i != lo ); // table became full?!

		// copy up
		ELEM_HASH(empty) = ELEM_HASH(i);
		ELEM_KEY(empty)  = ELEM_KEY(i);
		ELEM_VAL(empty)  = ELEM_VAL(i);
		// source slot is now free
		ELEM_HASH(i) = HASH_EMPTY;
		empty = i;
	}
}

hkResult hkStringMapBase::remove( const char* key )
{
	Iterator it = findKey(key);
	if( isValid(it) )
	{
		remove(it);
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

void hkStringMapBase::resizeTable(int newcap)
{
	HK_ASSERT2(0x1fdccddd,  m_numElems < newcap, "table size is not big enough" );
	HK_ASSERT2(0x18d91741,  HK_NEXT_MULTIPLE_OF(2, newcap) == newcap, "table size should be a power of 2" );

	int oldcap = m_hashMod+1;
	hkUlong* oldelem = m_elem;
	m_elem = hkAllocateChunk<hkUlong>(newcap*3, HK_MEMORY_CLASS_ARRAY); // space for values too
	hkString::memSet( m_elem, 0xff, hkSizeOf(hkUlong) * newcap ); // dont bother to zero values
	m_numElems = 0;
	m_hashMod = newcap - 1;

	for( int i = 0; i < oldcap; ++i )
	{
		if( oldelem[i] != HASH_EMPTY)
		{
			insert( (const char*)(oldelem[i+oldcap]), oldelem[i+oldcap+oldcap] );
		}
	}

	hkDeallocateChunk<hkUlong>( oldelem, oldcap*3, HK_MEMORY_CLASS_ARRAY );
}

hkBool hkStringMapBase::isOk() const
{
	// is count consistent?
	int count = 0;
	int i;
	for( i = 0; i <= m_hashMod; ++i )
	{
		count += ELEM_HASH(i) != HASH_EMPTY;
	}
	HK_ASSERT(0x11c13481,  count == m_numElems );

	// is element reachable from its hash?
	for( i = 0; i <= m_hashMod; ++i )
	{
		if( ELEM_HASH(i) != HASH_EMPTY )
		{
			hkUlong hash = ELEM_HASH(i);
			const char* key = (const char*)ELEM_KEY(i);
			hkUlong j = hash & m_hashMod;
			while( NOT_EQUAL(j, hash, key) )
			{
				j = (j + 1) & m_hashMod;
				HK_ASSERT(0x5ec0df1b,  ELEM_HASH(j) != HASH_EMPTY );
			}
		} 
	}
	return true;
}

void hkStringMapBase::clear()
{
	for( int i = 0; i < m_hashMod+1; ++i )
	{
		m_elem[i] = hkUlong(-1);
	}
	m_numElems = 0;
}

void hkStringMapBase::swap( hkStringMapBase& other )
{
	hkUlong* te = m_elem;
	hkUlong tn = m_numElems;
	hkUlong th = m_hashMod;
	m_elem = other.m_elem;
	m_numElems = other.m_numElems;
	m_hashMod = other.m_hashMod;
	other.m_elem = te;
	other.m_numElems = static_cast<int>(tn);
	other.m_hashMod = static_cast<int>(th);
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
