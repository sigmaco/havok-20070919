/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_VTABLE_CLASS_REGISTRY_H
#define HK_VTABLE_CLASS_REGISTRY_H

#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

/// Registry of vtables to hkClass instances.
class hkVtableClassRegistry : public hkSingleton<hkVtableClassRegistry>
{
	public:

		hkVtableClassRegistry() {}

			/// Associate vtable with the given hkClass.
		virtual void registerVtable( const void* vtable, const hkClass* klass )
		{
			HK_ASSERT2(0x2e231c83, vtable!=HK_NULL, "Nonvirtual classes should not be registered");
			m_map.insert(vtable, klass);
		}

			/// Get the class from an object instance which has a vtable.
		virtual const hkClass* getClassFromVirtualInstance( const void* obj ) const
		{
			return m_map.getWithDefault( *reinterpret_cast<const void*const*>(obj), HK_NULL );
		}

			/// Register each vtable from "infos" with the corresponding class from "classes".
			/// The list is terminated by the first null info or class.
		void registerList( const hkTypeInfo* const * infos, const hkClass* const * classes);

			/// Merges all entries from "copyFrom". (potentially overwriting local entries)
		void merge(const hkVtableClassRegistry& mergeFrom);

	protected:

		hkPointerMap<const void*, const hkClass*> m_map;
};

#endif // HK_VTABLE_CLASS_REGISTRY_H

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
