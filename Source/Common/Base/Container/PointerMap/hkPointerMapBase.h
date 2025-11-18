/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_HKPOINTERMAPBASE_H
#define HKBASE_HKPOINTERMAPBASE_H

// A class to map pointer size integers (hkUlong) to pointer size integers.
// Note that the key may not be zero.
template <typename T>
class hkPointerMapBase
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MAP, hkPointerMapBase );

			/// Iterator type.
			/// All iterators are invalidated after a mutating operation. i.e. insertion,removal
		typedef class Dummy* Iterator;

			/// Create an empty pointer map.
		hkPointerMapBase();

			/// Create pointer map using preallocated block of memory.
			/// The numOfExistingKeys indicates how many keys already exist in the
			/// provided memory block, if equal to 0 the memory will be zeroed.
		hkPointerMapBase(void* ptr, int sizeInBytes);

			/// Destroy a pointer map.
		~hkPointerMapBase();
		
			/// Get an iterator over the keys of this map.
		Iterator getIterator() const;

			/// Get the key at iterator i.
		T getKey( Iterator i ) const;

			/// Get the value at iterator i.
		T getValue( Iterator i ) const;

			/// Overwrite the value at iterator i.
		void setValue( Iterator i, T val );

			/// Get the next iterator after i.
		Iterator getNext( Iterator i ) const;

			/// Return if the iterator has not reached the end.
		hkBool isValid( Iterator i ) const;

			/// Insert key with associated value val. Keys are unique and non zero.
			/// If key already exists it is overwritten.
		void insert( T key, T val );

			/// Get an iterator at 'key'. Check if key was found with isValid().
		Iterator findKey( T key ) const;

			/// Shortcut for isValid(findKey(key)).
		hkBool hasKey( T key ) const { return isValid(findKey(key)); }

		/// Return the value associated with key or def if not present.
		T getWithDefault( T key, T def ) const;

			/// If key present, write value into out and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult get( T key, T* out ) const;

			/// Remove pair at iterator.
		void remove( Iterator it );

			/// If key present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult remove( T key );

			/// Return the number of keys.
		int getSize() const { return m_numElems & static_cast<int>(NUM_ELEMS_MASK); }

			/// Return the number of keys possible to store without reallocation.
		int getCapacity() const { return (m_hashMod + 1) & static_cast<int>(NUM_ELEMS_MASK); }

			/// Perform an internal consistency check.
		hkBool isOk() const;

			/// Remove all keys from the map.
		void clear();

			/// Swap all data with another map.
		void swap(hkPointerMapBase& other);

			// Estimates and sets the appropriate table size for a given number of elements.
		void reserve( int numElements );

		inline hkBool wasReallocated() const { return ( (m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG)) == 0 ); }

		static int HK_CALL getSizeInBytesFor(int numOfKeys);

#if defined(HK_PLATFORM_SPU)
			/// Return the value associated with key or def if not present.
		T getWithDefaultSpu( T key, T def ) const;
#endif

	protected:
		static HK_FORCE_INLINE T HK_CALL pointerHash(T addr, int mod);

		void resizeTable(int capacity);

	protected:

		// Internal flags, set in constructor.
		enum
		{
			NUM_ELEMS_MASK = int(0x7FFFFFFF),
			DONT_DEALLOCATE_FLAG = int(0x80000000) // Indicates that the storage is not the array's to delete
		};

		T* m_elem;
		int m_numElems; // high bits are flags
		int m_hashMod; // capacity - 1
};

#define HK_POINTERMAP_EMPTY_KEY -1

// Iterators are actually integer indices into m_elem
template < typename T >
HK_FORCE_INLINE T hkPointerMapBase<T>::pointerHash(T addr, int mod )
{
	// We ignore the lowest four bits on the address, since most addresses will be 16-byte aligned
	// knuths multiplicative golden hash
	return ((addr >> 4) * 2654435761U) & mod;
}

template < typename T >
inline typename hkPointerMapBase<T>::Iterator hkPointerMapBase<T>::getIterator() const
{
	int i;
	for( i = 0; i <= m_hashMod; ++i )
	{
		if( m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY) )
		{
			break;
		}
	}
	return reinterpret_cast<Iterator>( T(i) );
}

template < typename T >
inline T hkPointerMapBase<T>::getKey(Iterator it) const
{
	int i = static_cast<int>( reinterpret_cast<T>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	return m_elem[i];
}

template < typename T >
inline T hkPointerMapBase<T>::getValue(Iterator it) const
{
	int i = static_cast<int>( reinterpret_cast<T>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	return m_elem[i+m_hashMod+1];
}

template < typename T >
inline void hkPointerMapBase<T>::setValue(Iterator it, T val)
{
	int i = static_cast<int>( reinterpret_cast<T>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);
	m_elem[i+m_hashMod+1] = val;
}

template < typename T >
inline typename hkPointerMapBase<T>::Iterator hkPointerMapBase<T>::getNext( Iterator it ) const
{
	int i = static_cast<int>( reinterpret_cast<T>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod);

	for( i += 1; i <= m_hashMod; ++i )
	{
		if( m_elem[i] != T(HK_POINTERMAP_EMPTY_KEY) )
		{
			break;
		}
	}
	return reinterpret_cast<Iterator>( T(i) );
}

template < typename T >
inline hkBool hkPointerMapBase<T>::isValid( Iterator it ) const
{
	// range [0, hashMod] is valid
	// hashMod+1 invalid
	// anything else is bad input
	int i = static_cast<int>( reinterpret_cast<T>(it) );
	HK_ASSERT(0x7f305156, i>=0 && i<=m_hashMod+1);
	return i <= m_hashMod;
}

#endif // HKBASE_HKPOINTERMAPBASE_H

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
