/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkPointerMultiMap.h>

static int rand16()
{
	static unsigned seed = 'h'+'a'+'v'+'o'+'k';
	const unsigned a = 1103515245;
	const unsigned c = 12345;
	const unsigned m = unsigned(-1) >> 1;
	seed = (a * seed + c ) & m;
	return int(seed & 0xffff);
}

static int MultiMap()
{
	hkPointerMultiMap<hkUlong> map;
	HK_TEST(map.getFirstIndex( &map ) == -1);

	typedef void* Pointer;
	hkUlong table[][5] =
	{
		{ 0x12345678, 11, 31, 21, 0 },
		{ 0x23450000, 12, 12, 42, 0 },
		{ 0x34560001, 3, 23, 0, 0 },
		{ 0x45670111, 4, 24, 24, 0 },
		{ 0x0, 0, 0, 0, 0 }
	};

	for( int i = 0; table[i][0] != 0; ++i )
	{
		for( int j = 1; table[i][j] != 0; ++j )
		{
			map.insert( Pointer(table[i][0]), table[i][j] );
		}
	}

	const int removal[][2] =
	{
		{ 2,2 },
		{ 3,3 },
		{ 3,2 },
		{ 3,1 },
		{ 0,3 },
	};
	int nrepeat = int(sizeof(removal)/(sizeof(int)*2));
	for( int repeat = 0; repeat <= nrepeat; ++repeat )
	{
		for( int i = 0; table[i][0] != 0; ++i )
		{
			int index = map.getFirstIndex(Pointer(table[i][0]));
			HK_TEST( index != -1 || table[i][1] == 0 );
			for( int j = 1; j < 5; ++j )
			{
				if( table[i][j] == 0 ) continue;
				HK_TEST( index != -1);
				hkUlong val = map.getValue(index);
				int found = 0;
				for( int k = 1; table[i][k] && found==0; ++k )
				{
					found |= ( val == table[i][k] );
				}
				HK_TEST( found != 0 );
				index = map.getNextIndex(index);
			}
			HK_TEST( index == -1);
		}

		if( repeat < nrepeat )
		{
			int row = removal[repeat][0];
			int col = removal[repeat][1];
			hkUlong val = table[row][col];
			map.removeByValue( Pointer(table[row][0]), val );
			table[row][col] = 0;
		}
	}
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < (rand16()&7); ++j )
		{
			map.insert( Pointer(table[i][0]), rand16() );
		}
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(MultiMap, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
