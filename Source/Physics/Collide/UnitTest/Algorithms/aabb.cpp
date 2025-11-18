/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

int aabb_main()
{
	hkVector4 zero; zero.setZero4();
	hkVector4 v0, v1, v2;
	v0.set(100,200,300);
	v1.set(200,300,400);
	v2.set(50,100,350);

	hkAabb a0( zero, v0);
	hkAabb a1( zero, v1);
	hkAabb a2( v2, v1);

	HK_TEST( a0.isValid() );
	HK_TEST( a1.isValid() );
	HK_TEST( a2.isValid() );

	hkAabb a3;
	a3.m_min = v2;
	a3.m_max = v0;
	HK_TEST( a3.isValid() == false);

	HK_TEST( a1.contains(a0) == true );
	HK_TEST( a0.contains(a1) == false);

	HK_TEST( a1.contains(a2) == true );
	HK_TEST( a2.contains(a1) == false);
	HK_TEST( a0.contains(a2) == false);
	HK_TEST( a2.contains(a0) == false);
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(aabb_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
