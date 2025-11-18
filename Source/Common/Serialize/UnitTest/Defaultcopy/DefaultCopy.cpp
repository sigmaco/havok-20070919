/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Serialize/UnitTest/Defaultcopy/DefaultCopy.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Serialize/Copier/hkObjectCopier.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>

static inline int vec_equal(const hkVector4& v, hkReal a, hkReal b, hkReal c, hkReal d)
{
	return v(0) == a && v(1) == b && v(2) == c && v(3) == d;
}

static int NestedCopy()
{
	Modified_WithNested mod;
	hkString::memSet( &mod, 0, sizeof(mod));

	Original_WithNested old;
	hkObjectCopier copier(hkStructureLayout::HostLayoutRules, hkStructureLayout::HostLayoutRules);
	hkRelocationInfo reloc;
	hkOstream dataOut( &mod, sizeof(Modified_WithNested), false );
	copier.copyObject( &old, Original_WithNestedClass, dataOut.getStreamWriter(), Modified_WithNestedClass, reloc );

	HK_TEST( mod.m_foo == old.m_foo );
	HK_TEST( mod.m_foo2 == 0 );
	HK_TEST( mod.m_nested.m_pad[0] == 0 );
	HK_TEST( mod.m_nested.m_pad[1] == 0 );
	HK_TEST( mod.m_nested.m_enabled2 == true );
	HK_TEST( mod.m_nested.m_radius == old.m_nested.m_radius );
	HK_TEST( mod.m_bar == mod.m_bar );
	HK_TEST( mod.m_bar2 == 0 );
	return 0;
}

static int DefaultCopy()
{
	Modified_DefaultCopy mod;
	hkString::memSet( &mod, 0, sizeof(mod) );

	hkVersionUtil::copyDefaults( &mod, Original_DefaultCopyClass, Modified_DefaultCopyClass );

	HK_TEST( mod.m_int0 == 100 );
	HK_TEST( mod.m_bool0 == true);
	HK_TEST( mod.m_bool1 == false);
	HK_TEST( mod.m_bool2 == true);
	HK_TEST( mod.m_value8 == Modified_DefaultCopy::VALUE_THIRD);
	HK_TEST( 0 != vec_equal(mod.m_vec0, 0,0,0,0) );
	HK_TEST( 0 != vec_equal(mod.m_vec1, 44,55,66,77) );
	HK_TEST( 0 != vec_equal(mod.m_vec2, 88,99,11,0) );

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(DefaultCopy, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );
HK_TEST_REGISTER(NestedCopy, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
