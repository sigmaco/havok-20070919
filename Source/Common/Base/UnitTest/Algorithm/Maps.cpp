/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

extern "C" int HK_CALL rand();

static void test_maps()
{
	for( int rep = 1; rep < 200; ++rep )
	{
		const int N = rep;

		hkPointerMap<int, int> pmap;
		hkArray<int> keys(N);

		int i;
		for( i = 0; i < N; ++i )
		{
			while(1)
			{
				int key = int( hkMath::rand01() * 1000 * rep );
				if( key && (keys.indexOf(key) == -1) )
				{
					keys[i] = key;
					break;
				}
			}
			pmap.insert(keys[i], i);	
		}

		HK_TEST( pmap.getSize() == N );
		for( i = 0; i < N; ++i )
		{
			int out = 0;
			HK_TEST( pmap.get(keys[i], &out) == HK_SUCCESS );
			HK_TEST( out == i );
		}

		{
			for( hkPointerMap<int,int>::Iterator it = pmap.getIterator();
				pmap.isValid(it);
				it = pmap.getNext(it) )
			{
				int idx = keys.indexOf( pmap.getKey(it) );
				HK_TEST( idx != -1 );
				keys.removeAt( idx );
			}
			HK_TEST( keys.getSize() == 0 );
		}

		{
			for( hkPointerMap<int,int>::Iterator it = pmap.getIterator();
				pmap.isValid(it);
				it = pmap.getNext(it) )
			{
				int val = pmap.getKey(it);
				pmap.setValue(it, val*10);
				HK_TEST( pmap.getValue(it) == val*10 );
			}
		}
	}
}

int maps_main()
{
	test_maps();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(maps_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
