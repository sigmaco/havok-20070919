/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_SERIALIZE_POINTER_MULTIMAP_H
#define HK_SERIALIZE_POINTER_MULTIMAP_H

#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

/// Maintains a list of values for each pointer key.
/// The implementation is quite simple and fast since
/// this object does not support removal of keys.
template <typename VALUE>
class hkPointerMultiMap
{
	protected:

		int getFreeIndex();

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT, hkPointerMultiMap);

			/// A linked list of pointer references.
			/// 'next' is the index of the next reference in the list.
		struct Value
		{
			Value(const VALUE& v, int n) : value(v), next(n) { }
			VALUE value;
			int next;
		private:
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, hkPointerMultiMap::Value );
		};

			/// Create an empty hkPointerMultiMap.
		hkPointerMultiMap() : m_freeChainStart(-1) {}

			/// Get the index of the references to p or -1.
			/// Get subsequent reference indices from Reference.next
		int getFirstIndex( void* p );

			/// Read the i'th value.
			/// Usually used with an index from getFirstIndex().
		const VALUE& getValue( int i ) const { return m_valueChain[i].value; }

			/// Get the i+1'th index.
		int getNextIndex( int i ) const { return m_valueChain[i].next; }

			/// Associate a value v with pointer p.
		void insert( void* p, const VALUE& v );

			/// A value which is associated with a not-yet-created object.
			/// When the pointer key is available, call realizePendingPointer
			/// with the return value of this method.
		int addPendingValue( const VALUE& v, int nextIndex );

			/// A pending object has been created.
		void realizePendingPointer( void* p, int index );

			/// Remove all keys and values.
		void clear();

			/// Remove value at index and return next index.
		int removeByIndex( void* key, int index );

			/// Remove value v from key and return next index.
		int removeByValue( void* key, const VALUE& v);

			/// Remove key and all its values.
		void removeKey( void* key );

	public:

			// Multiple singly-linked lists of values.
			// Start index is given by m_reverseReferences.
		hkArray<Value> m_valueChain;

			// Map of pointer to index into m_itemChain.
		hkPointerMap<void*, int> m_indexMap;

			// Chain free list
		int m_freeChainStart;
};

#include <Common/Serialize/Util/hkPointerMultiMap.inl>

#endif // HK_SERIALIZE_POINTER_MULTIMAP_H

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
