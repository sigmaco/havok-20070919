/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>
#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

static int vtableCheck()
{
	const hkTypeInfo* const * ti = hkBuiltinTypeRegistry::getInstance().StaticLinkedTypeInfos;
	const hkClass* const * ci = hkBuiltinTypeRegistry::getInstance().StaticLinkedClasses;
	while( *ti != HK_NULL && *ci != HK_NULL )
	{
		int c = (*ci)->hasVtable() ? 1 : 0;
		int t = (*ti)->getVtable() ? 1 : 0;
		HK_TEST2( c == t, "Class " << (*ci)->getName() << " failed vtable check." );
		++ti;
		++ci;
	}
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(vtableCheck, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
