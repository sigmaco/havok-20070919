/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_SERIALIZE_RENAMED_CLASSNAME_REGISTRY_H
#define HK_SERIALIZE_RENAMED_CLASSNAME_REGISTRY_H

#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

class hkRenamedClassNameRegistry : public hkClassNameRegistry
{
	protected:

		void registerRenames( const hkVersionUtil::ClassRename* renames )
		{
			if( renames )
			{
				for( const hkVersionUtil::ClassRename* r = renames; r->oldName != HK_NULL; ++r )
				{
					m_renames.insert( r->oldName, r->newName );
				}
			}		
		}

	public:

		hkRenamedClassNameRegistry( const hkVersionUtil::ClassRename* renames, const hkClass*const* classes )
		{
			registerList( classes );
			registerRenames( renames );
		}

		/// This takes an existing reg and just queries into it
		hkRenamedClassNameRegistry( const hkVersionUtil::ClassRename* renames, const hkClassNameRegistry* origList )
		{
			HK_ASSERT( 0x3212345, origList );
			merge(*origList);
			registerRenames( renames );
		}

		virtual const hkClass* getClassByName( const char* oldname ) const
		{
			const char* name = m_renames.getWithDefault( oldname, oldname );
			return hkClassNameRegistry::getClassByName(name);
		}

		const char* getRename( const char* oldName )
		{
			return m_renames.getWithDefault(oldName, HK_NULL);
		}

		hkStringMap<const char*> m_renames;

};

#endif // HK_SERIALIZE_RENAMED_CLASSNAME_REGISTRY_H

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
