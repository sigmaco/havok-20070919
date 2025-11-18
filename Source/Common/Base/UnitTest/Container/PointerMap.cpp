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

static void test_pointermap()
{
	const int  N = 11;

	//Testing getKey(),getValue()and hasKey() functionality
	{
		hkPointerMap<int, int> pmap;

		for(int i = 1; i < N; ++i)
		{
			pmap.insert(i, i+100);
		}

		// Testing isOk() functionality
		{
			HK_TEST( pmap.isOk() == true );
		}

		for(int i = 1; i < N; ++i)
		{
			hkPointerMap<int,int>::Iterator it = pmap.findKey(i);
			HK_TEST( pmap.getKey(it) == i );
			HK_TEST( pmap.getValue(it) == (i+100) );
			HK_TEST( pmap.hasKey(i) );
		}

		// Testing get() functionality
		{
			for(int i = 1; i < N; ++i )
			{
				int out = 0;
				HK_TEST( pmap.get(i, &out) == HK_SUCCESS );
				HK_TEST( out==(i+100) );
			}

			for(int j = 11; j < 20; ++j )
			{
				int out = 0;
				HK_TEST( pmap.get(j, &out) == HK_FAILURE );
				HK_TEST( out==0 );
			}
		}
	}

	// Testing getWithDefault(), getCapacity(), getSizeInBytesFor
	{
		hkPointerMap<int, int> pmap;

		// Testing default Capacity
		{
			int basecapacity = pmap.getCapacity();
			HK_TEST( basecapacity == 16 );
		}
		// Testing getSizeInBytesFor() functionality
		{
			int sizeInBytes = hkPointerMap<int,int>::getSizeInBytesFor(17);
			// (key,value) * (num keys) * (fill factor) = 16
			// Here required number would be 32
			// In multiples of 2 and greater than 16
			int requiredSize = 32 * 16;
			HK_TEST( sizeInBytes == requiredSize );

			sizeInBytes = hkPointerMap<int,int>::getSizeInBytesFor(31);
			HK_TEST( sizeInBytes == requiredSize );

			sizeInBytes = hkPointerMap<int,int>::getSizeInBytesFor(33);
			requiredSize = 64 * 16;
			HK_TEST( sizeInBytes == requiredSize );
		}

		// Testing getCapacity() functionality
		{
			for(int i = 1; i < 100; ++i)
			{
				int value = i + 50;
				pmap.insert(i, value);
			}
			int capacity = pmap.getCapacity();
			int sizeInBytes = hkPointerMap<int,int>::getSizeInBytesFor(100);
			int calc_capacity = sizeInBytes / (2 * sizeof(int));
			HK_TEST( capacity == calc_capacity );
		}
		// Testing getWithDefault() functionality
		{
			for(int i = 1; i < 100; ++i)
			{
				int def = 0;
				int value = i + 50;
				HK_TEST( pmap.getWithDefault(i,def) == value );
				HK_TEST( def == 0 );
			}
			for(int i = 100; i < 105; ++i)
			{
				int def = 0;
				HK_TEST( pmap.getWithDefault(i,def) == def );
			}
		}
		// Testing setValue() functionality
		{
			for( hkPointerMap<int,int>::Iterator it1 = pmap.getIterator();
				pmap.isValid(it1);
				it1 = pmap.getNext(it1) )
			{
				pmap.setValue(it1, 100);
			}

			for( hkPointerMap<int,int>::Iterator it1 = pmap.getIterator();
				pmap.isValid(it1);
				it1 = pmap.getNext(it1) )
			{
				HK_TEST( pmap.getValue(it1) == 100 );
			}
			HK_TEST( pmap.isOk() );
		}
		// Testing wasReallocateed() functionality
		{
			HK_TEST( pmap.wasReallocated() );
			pmap.clear();
			pmap.reserve(20);
			HK_TEST( pmap.wasReallocated() );
			pmap.insert(1, 1);
			HK_TEST( pmap.wasReallocated() );
		}
	}
	//Testing swap()functionality
	{
		hkPointerMap<int, int> pmap1;
		for(int i = 1; i < N; ++i)
		{
			pmap1.insert(i, i+100);
		}

		hkPointerMap<int, int> pmap2;
		const int limit = 21;

		for(int i = N; i < limit; ++i)
		{
			pmap2.insert(i, i+100);
		}

		pmap1.swap(pmap2);

		// Verifying pmap1 with pmap2 values
		{
			int i = N;
			for( hkPointerMap<int,int>::Iterator it1 = pmap1.getIterator();
				pmap1.isValid(it1);
				it1 = pmap1.getNext(it1) )
			{
				HK_TEST( pmap1.getKey(it1) == i );
				HK_TEST( pmap1.getValue(it1) == (i+100) );
				++i;
			}
		}

		// Verifying pmap2 with pmap1 values
		{
			int i = 1;
			for( hkPointerMap<int,int>::Iterator it2 = pmap2.getIterator();
				pmap2.isValid(it2);
				it2 = pmap2.getNext(it2) )
			{
				HK_TEST( pmap2.getKey(it2) == i);
				HK_TEST( pmap2.getValue(it2) == (i+100) );
				++i;
			}
		}
	}

	// Testing Remove() via iterator.
	{
		hkPointerMap<int, int> pmap1;
		for(int i = 1; i < N; ++i)
		{
			pmap1.insert(i, i+100);
		}

		int key = 0;
		for( hkPointerMap<int,int>::Iterator it1 = pmap1.getIterator();
			pmap1.isValid(it1);
			it1 = pmap1.getNext(it1) )
		{
			int num = pmap1.getSize();
			key = pmap1.getKey(it1);
			pmap1.remove(it1);
			HK_TEST( pmap1.getSize() == num-1 );
			break;
		}

		int out = 0;
		HK_TEST( pmap1.get(key, &out) == HK_FAILURE );
		HK_TEST(out == 0);
	}

	// Testing Remove() via Key.
	{
		hkPointerMap<int, int> pmap1;
		for(int i = 1; i < N; ++i)
		{
			pmap1.insert(i, i+100);
		}

		int num = pmap1.getSize();
		HK_TEST( pmap1.remove(7) == HK_SUCCESS );
		HK_TEST( pmap1.getSize() == num-1 );

		int out = 0;
		HK_TEST( pmap1.get(7, &out) == HK_FAILURE );
		HK_TEST(out == 0);
	}

	// Testing of clear() functionality
	{
		hkPointerMap<int, int> pmap1;
		for(int i = 1; i < N; ++i)
		{
			pmap1.insert(i, i+100);
		}

		pmap1.clear();
		HK_TEST( pmap1.getSize() == 0 );
	}
}


int pointermap_main()
{
	test_pointermap();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(pointermap_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
