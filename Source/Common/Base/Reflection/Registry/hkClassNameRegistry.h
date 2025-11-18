/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_CLASS_NAME_REGISTRY_H
#define HK_CLASS_NAME_REGISTRY_H

#include <Common/Base/Container/StringMap/hkStringMap.h>
#include <Common/Base/Reflection/hkClass.h>

class hkClass;

/// Associates string type names with hkClass objects.
class hkClassNameRegistry : public hkSingleton<hkClassNameRegistry>
{
	public:

		hkClassNameRegistry() {}

			/// Register a class possibly under a different name.
			/// If name is null, the class name is used.
			/// The name is not copied and must be valid for the lifetime
			/// of this object.
		virtual void registerClass( const hkClass* klass, const char* name = HK_NULL )
		{
			m_map.insert( name ? name : klass->getName(), klass );
		}

			/// Get a class by name or HK_NULL if it was not registered.
		virtual const hkClass* getClassByName( const char* className ) const
		{
			return m_map.getWithDefault( className, HK_NULL );
		}

			/// Register a null terminated list of classes.
		virtual void registerList( const hkClass* const * classes)
		{
			const hkClass* const * ci = classes;
			while(*ci != HK_NULL)
			{
				registerClass( *ci );
				++ci;
			}
		}

			/// Merges all entries from "mergeFrom" (potentially overwriting current entries).
		virtual void merge(const hkClassNameRegistry& mergeFrom)
		{
			hkStringMap<const hkClass*>::Iterator iter = mergeFrom.m_map.getIterator();
			while (mergeFrom.m_map.isValid(iter))
			{
				m_map.insert( mergeFrom.m_map.getKey(iter), mergeFrom.m_map.getValue(iter) );
				iter = mergeFrom.m_map.getNext(iter);
			}
		}

	private:

		hkStringMap<const hkClass*> m_map;
};

#endif // HK_CLASS_NAME_REGISTRY_H

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
