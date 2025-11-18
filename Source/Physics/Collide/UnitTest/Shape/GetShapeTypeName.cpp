/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Collide/Shape/hkpShapeType.h>

int test_get_shape_type_name()
{
	const char* lastGood = HK_NULL;

	for (int t = HK_FIRST_SHAPE_TYPE; t < HK_SHAPE_MAX_ID; t++)
	{
		const char* name = hkGetShapeTypeName((hkpShapeType)t);

		HK_TEST2(name != HK_NULL, "hkpShapeType " << t << " is unknown." << hkendl << "You must add support for it in hkGetShapeTypeName(). It comes after " << lastGood << " in the hkpShapeType enum.");

		lastGood = name ? name : lastGood;
	}

	

	return 0;
}


#if defined( HK_COMPILER_MWERKS )
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER( test_get_shape_type_name , "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
