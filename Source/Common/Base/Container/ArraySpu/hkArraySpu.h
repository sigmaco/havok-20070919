/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_HKARRAY_SPU_H
#define HKBASE_HKARRAY_SPU_H


#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>


class hkArraySpu
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkArraySpu );

		template <typename TYPE>
		HK_FORCE_INLINE void init( hkArray<TYPE>& arrayHeaderOnSpu, TYPE* storage, int storageCapacity );

		void putArrayToMainMemoryImpl( hkArray<char>& arrayOnSpu, void* inplaceStorageOnSpu, void* inplaceStorageOnPpu, int numInplaceCapacityOnPpu, int elemSize, int dmaGroup );

		template <typename ARRAY_TYPE>
		HK_FORCE_INLINE void putArrayToMainMemory( ARRAY_TYPE& arrayOnPpu, ARRAY_TYPE& arrayHeaderOnSpu, int dmaGroup );

		template <typename ARRAY_TYPE>
		HK_FORCE_INLINE void putArrayToMainMemoryNotInplace(ARRAY_TYPE& arrayOnPpu, ARRAY_TYPE& arrayHeaderOnSpu, int dmaGroup);

		template <typename TYPE>
		HK_FORCE_INLINE void overwriteData( TYPE* data, int numElems );

 		HK_FORCE_INLINE int getSize();

 		template <typename TYPE>
		HK_FORCE_INLINE TYPE& getValueAt (int i);

 		template <typename TYPE>
		HK_FORCE_INLINE const TYPE& getValueAt (int i) const;

 		template <typename TYPE>
		HK_FORCE_INLINE void pushBack(const TYPE& e);

		//template <typename TYPE>
		//HK_FORCE_INLINE void removeAt(int index);

 		//template <typename TYPE>
 		//HK_FORCE_INLINE TYPE& expandOne();

 		//template <typename TYPE>
 		//HK_FORCE_INLINE TYPE* begin();

	protected:

		hkPadSpu<int>	m_numElems;
		hkPadSpu<int>	m_capacity;

		hkPadSpu<void*>	m_storage;

};


#include <Common/Base/Container/ArraySpu/hkArraySpu.inl>


#endif // HKBASE_HKARRAY_SPU_H

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
