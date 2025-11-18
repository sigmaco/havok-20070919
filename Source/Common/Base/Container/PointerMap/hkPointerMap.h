/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_HKPOINTERMAP_H
#define HKBASE_HKPOINTERMAP_H

#include <Common/Base/Container/PointerMap/hkPointerMapBase.h>

/// A class to map between non-zero pointer or integer keys and arbitrary pointer/integer values.
template <typename K, typename V>
class hkPointerMap
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MAP, hkPointerMap );

			/// Iterator class
			/// All iterators are invalidated after a mutating operation. i.e. insertion,removal
		typedef hkPointerMapBase<hkUlong>::Iterator Iterator;

		hkPointerMap()
		{
		}

			/// Create pointer map initially using preallocated memory block.
		hkPointerMap(void* ptr, int sizeInBytes) : m_map(ptr, sizeInBytes)
		{
		}

			///	Insert key with associated value val. Keys are unique and non null.
			/// If key already exists it is overwritten.
		HK_FORCE_INLINE void insert( K key, V val )
		{
			m_map.insert( hkUlong(key), hkUlong(val) );
		}

			/// Return the iterator associated with key or def if not present.
		HK_FORCE_INLINE Iterator findKey( K key ) const
		{
			return m_map.findKey( hkUlong(key) );
		}

			/// Return if this map contains the given key.
		HK_FORCE_INLINE hkBool hasKey( K key ) const
		{
			return m_map.hasKey( hkUlong(key) );
		}

			/// Return the value associated with key or def if not present.
		HK_FORCE_INLINE V getWithDefault( K key, V def ) const
		{
			return (V)m_map.getWithDefault( hkUlong(key), hkUlong(def) );
		}

			/// If key present, write value into out and return HK_SUCCESS. Else return HK_FAILURE.
		hkResult get( K key, V* out ) const
		{
			hkUlong tmp;
			if( m_map.get( hkUlong(key), &tmp ) == HK_SUCCESS )
			{
				*out = V(tmp);
				return HK_SUCCESS;
			}
			return HK_FAILURE;

		}

			/// Remove pair at it.
		void remove( Iterator it )
		{
			m_map.remove( it );
		}

			/// If key present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult remove( K key )
		{
			return m_map.remove( hkUlong(key) );
		}

			/// Return the number of elements in this map.
		int getSize() const
		{
			return m_map.getSize();
		}

			/// Return the number of elements that can be stored in this map without reallocation.
		int getCapacity() const
		{
			return m_map.getCapacity();
		}

			/// Perform internal consistency check.
		hkBool isOk() const
		{
			return m_map.isOk();
		}

			/// Get an iterator over the keys of this map.
		Iterator getIterator() const
		{
			return m_map.getIterator();
		}

			/// Get the key at iterator i.
		K getKey( Iterator i ) const
		{
			return (K)m_map.getKey(i);
		}

			/// Get the value at iterator i.
		V getValue( Iterator i ) const
		{
			return (V)m_map.getValue(i);
		}

			/// Overwrite the value at iterator i.
		void setValue( Iterator i, V val )
		{
			m_map.setValue(i, hkUlong(val) );
		}

			/// Get the next iterator after i.
		Iterator getNext( Iterator i ) const
		{
			return m_map.getNext(i);
		}

			/// Return if the iterator has reached the end.
		hkBool isValid( Iterator i ) const
		{
			return m_map.isValid(i);
		}

			/// clear the table
		void clear()
		{
			m_map.clear();
		}

			/// Estimates and sets the appropriate table size for a given number of elements.
		void reserve( int numElements )
		{
			m_map.reserve(numElements);
		}

			/// Swap the internal representation with another map.
		void swap( hkPointerMap& other )
		{
			m_map.swap( other.m_map );
		}

		inline hkBool wasReallocated() const { return m_map.wasReallocated(); }

			/// Calculates number of bytes required to store specified number of keys.
		static int HK_CALL getSizeInBytesFor(int numOfKeys) { return hkPointerMapBase<hkUlong>::getSizeInBytesFor(numOfKeys); }

	private:

		hkPointerMap<K,V>& operator = (const hkPointerMap<K,V>& map) { HK_ASSERT2(0xad87a6aa, false, "This doesn't work."); }

	public:

#if !defined(HK_PLATFORM_SPU)
	protected:
#endif
		hkPointerMapBase<hkUlong> m_map;
};

#endif // HKBASE_HKPOINTERMAP_H

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
