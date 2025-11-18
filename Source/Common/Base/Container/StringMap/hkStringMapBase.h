/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_STRINGMAPBASE_H
#define HKBASE_STRINGMAPBASE_H

// A class to map strings to pointers/pointer size integers.
class hkStringMapBase
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MAP, hkStringMapBase );

			/// Iterator class
			/// All iterators are invalidated after a mutating operation. i.e. insertion,removal
		typedef class Dummy* Iterator;

			/// Create an empty String map.
		hkStringMapBase();

			/// Destroy a String map.
		~hkStringMapBase();

			/// Get an iterator over the keys of this map.
		Iterator getIterator() const;

			/// Get the key at iterator i.
		char* getKey( Iterator i ) const;

			/// Get the value at iterator i.
		hkUlong getValue( Iterator i ) const;

			/// Overwrite the value at iterator i.
		void setValue( Iterator i, hkUlong v );

			/// Get the next iterator after i.
		Iterator getNext( Iterator i ) const;

			/// Return if the iterator has reached the end.
		hkBool isValid( Iterator i ) const;

			/// Insert key with associated value val.
			/// If key already exists it is overwritten. The string storage is not
			/// copied and must exist for the lifetime of the key.
		void insert( const char* key, hkUlong val );

			/// Get an iterator at 'key'. Check if key was found with isValid().
		Iterator findKey( const char* key ) const;

			/// Shortcut for isValid(findKey(key)).
		hkBool hasKey( const char* key ) const { return isValid(findKey(key)); }

			/// Return the value associated with key or def if not present.
		hkUlong getWithDefault( const char* key, hkUlong def ) const;

			/// If key present, write value into out and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult get( const char* key, hkUlong* out ) const;
		
			/// Remove pair at iterator.
		void remove( Iterator it );

			/// If key present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult remove( const char* key );

			/// Return the number of keys.
		int getSize() const { return m_numElems; }
	
			/// Perform an internal consistency check.
		hkBool isOk() const;

			/// Assignment operator. Will copy the memory chunk.
		hkStringMapBase* operator=(const hkStringMapBase* other);

			/// Remove all keys from the map.
		void clear();

			/// Swap all data with another map.
		void swap( hkStringMapBase& other );

	protected:
			
		void resizeTable(int capacity);

	protected:

		hkUlong* m_elem;
		int m_numElems;
		int m_hashMod; // capacity - 1
};

#endif // HKBASE_STRINGMAPBASE_H

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
