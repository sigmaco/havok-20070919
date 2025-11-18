/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/Array/hkSmallArray.h>

static void small_array()
{
	//Testing getSize() & isempty().
	{
		hkSmallArray<int> a;
		HK_TEST(a.getSize() == 0);
		HK_TEST(a.isEmpty());
		HK_TEST(a.getCapacity() == 0);
	}

	//Testing popback().
	{
		hkSmallArray<int> d;
		for(int i = 0; i < 10; ++i)
		{
			d.pushBack(i);
		}
		HK_TEST(d.getSize() == 10);
		d.popBack();
		HK_TEST(d.getSize() == 9);
		d.popBack(2);
		HK_TEST(d.getSize() == 7);
		for(int i = 0; i < d.getSize(); ++i)
		{
			HK_TEST(d[i] == i);
		}
	}

	//Testing removeAt().
	{
		hkSmallArray<int> d(10);
		for(int i = 0; i < d.getSize(); ++i)
		{
			d[i] = i;
		}
		d.removeAt(5);
		HK_TEST(d.getSize() == 9);
		for(int i = 0; i < d.getSize(); ++i)
		{
			if(i!=5)
			{
				HK_TEST(d[i] == i);
			}
			else
			{
				HK_TEST(d[i]!=i);
				HK_TEST(d[i] == 9);
			}
		}
	}

	//Testing removeAtAndCopy()& indexOf().
	{
		int i;
		hkSmallArray<int> d(10);
		for(i = 0; i < d.getSize(); ++i)
		{
			d[i] = i;
		}
		d.removeAtAndCopy(5);
		HK_TEST(d.getSize() == 9);
		for(i=0; i<d.getSize(); ++i)
		{
			if(i<5)
			{
				HK_TEST(d[i]  ==  i);
			}
			else
			{
				HK_TEST(d[i] == (i+1));
			}
		}
		HK_TEST(d.indexOf(4) == 4);
		HK_TEST(d.indexOf(5) == -1);
		HK_TEST(d.indexOf(6) == 5);
	}

	//Testing indexOf().
	{
		hkSmallArray<int> d(10);
		int i;
		for(i = 0; i < d.getSize(); ++i)
		{
			d[i] = i%5;
		}
		for(i = 0; i < d.getSize(); ++i)
		{
			if(i<5)
			{
				HK_TEST(d.indexOf(i) == i);
			}
			else
			{
				HK_TEST(d.indexOf(i) == -1);
			}
		}
	}

	//Testing reserve().
	{
		hkSmallArray<int> d;
		d.reserve(10);
		for(int i = 0; i < 10; ++i)
		{
			d.pushBack(i);
		}
		HK_TEST(d.getSize() == 10);
		for(int i = 0; i < 10; ++i)
		{
			HK_TEST(d[i] == i);
		}
	}

	//Testing insertAt()with 2 parameter.
	{
		hkSmallArray<int> d;
		for(int i = 0; i < 10; ++i)
		{
			d.pushBack(i);
		}
		// inserting at start of array
		d.insertAt(0,99);
		HK_TEST(d.getSize() == 11);
		HK_TEST(d[0] == 99);
		for(int i = 0; i < 10; ++i)
		{
			HK_TEST(d[i+1]  ==  i);
		}
		// inserting at middle of array
		d.insertAt(5,100);
		HK_TEST(d.getSize() == 12);
		HK_TEST(d[4] == 3);
		HK_TEST(d[5] == 100);
		HK_TEST(d[6] == 4);
		HK_TEST(d[11] == 9);
		// inserting at end of array
		d.insertAt(12,100);
		HK_TEST(d.getSize() == 13);
		HK_TEST(d[11] == 9);
		HK_TEST(d[12] == 100);
	}

	//Testing insertAt() with 3 parameter.
	{
		hkSmallArray<int> d;
		hkSmallArray<int> e;
		for(int i = 0; i < 10; ++i)
		{
			d.pushBack(i);
			e.pushBack(-i);
		}
		d.insertAt(3,e.begin(), e.getSize());
		HK_TEST(d.getSize() == 20);
		HK_TEST(d[2] == 2);
		HK_TEST(d[3] == 0);
		HK_TEST(d[4] == -1);
		HK_TEST(d[12] == -9);
		HK_TEST(d[13] == 3);
		HK_TEST(d[14] == 4);
		HK_TEST(d[19] == 9);
	}

	//Testing expandOne().
	{
		hkSmallArray<int> d;
		for(int i = 0; i < 10; ++i)
		{
			d.pushBack(i);
		}
		HK_TEST(d.getSize() == 10);
		int ref = d.expandOne();
		HK_TEST(d.getSize() == 11);
		HK_TEST(d[10] ==  ref);
    }

	//Testing back() & copyBackwards().
	{
        hkSmallArray<int> d;
        for(int i = 0; i < 10;i++)
		{
			d.pushBack(i);
		}
        HK_TEST(d.back() == d[9]);
        d.back()=20;
    	HK_TEST(d[9] == 20);

        hkSmallArray<int> e;
        for(int i = 10; i < 20; i++)
		{
			e.pushBack(i);
		}

		hkSmallArray<int>::copyBackwards(&e[0],&d[0],10);

		for(int i = 9; i >= 0; --i)
        {
			HK_TEST(e[i] == d[i]);
        }
 	}

	// Testing iterator functionality
	{
		hkSmallArray<int> d;
        for(int i = 0; i < 10; i++)
		{
			d.pushBack(i);
		}
		int* itr_begin = d.begin();
		int* itr_end = d.end();
		int* itr = HK_NULL;
		int i = 0;
		for(itr = itr_begin; itr != itr_end; itr++)
		{
			HK_TEST(itr[0] == d[i]);
			itr[0] = i + 10;
			HK_TEST(d[i] == (i + 10));
			i++;
		}

		const int* citr_begin = d.begin();
		const int* citr_end = d.end();
		const int* citr = HK_NULL;

		i = 0;
		for(citr = citr_begin; citr != citr_end; citr++)
		{
			HK_TEST(citr[0] == (d[i]));
			i++;
		}
	}

	//Testing clearAndDeallocate().
	{
		hkSmallArray<int> c(5);
		HK_TEST(c.getSize() == 5);
		for(int i = 0; i < 5; i++)
		{
			c.pushBack(i);
		}
		c.clearAndDeallocate();
		HK_TEST(c.getSize() == 0);
		HK_TEST(c.getCapacity() == 0);
	}
}

int smallarray_main()
{
	small_array();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(smallarray_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
