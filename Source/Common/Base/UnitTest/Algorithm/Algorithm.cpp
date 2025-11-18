/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

static void algorithm()
{
	const int orig_x = 55;
	const int orig_y = 28;
	int x = orig_x;
	int y = orig_y;
	hkAlgorithm::swap(x,y);
	HK_TEST(orig_x==y);
	HK_TEST(orig_y==x);
}

static void array()
{
	int i;
	{
		hkArray<int> a;
		HK_TEST(a.getSize()==0);
		HK_TEST(a.isEmpty());
	}

	{
		hkArray<int> b(10);
		HK_TEST(b.getSize()==10);
		HK_TEST(!b.isEmpty());
		b.popBack();
		HK_TEST(b.getSize()==9);

		b.clear();
		HK_TEST(b.getSize()==0);
		HK_TEST(b.isEmpty());
		HK_TEST(b.getCapacity()!=0);
	}

	{
		hkArray<int> c(5, 99);
		HK_TEST(c.getSize()==5);
		for(i=0; i<c.getSize(); ++i)
		{
			HK_TEST(c[i]==99);
		}
		c.clearAndDeallocate();
		HK_TEST(c.getSize()==0);
		HK_TEST(c.getCapacity()==0);
	}

	{
		int p[] = { 0,1,2,3,4,5,6,7,8,9,10 };
		hkArray<int> d(p, 10, 10);
		d.removeAt(5);
		HK_TEST(d.getSize()==9);
		HK_TEST(d[5]!=5);
	}

	{
		hkArray<int> d(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i;
		}
		d.removeAt(5);
		HK_TEST(d.getSize()==9);
		HK_TEST(d[5]!=5);
		HK_TEST(d[4]==4);
		HK_TEST(d[6]==6);
	}

	{
		hkArray<int> d;
		d.setSize(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i;
		}
		d.removeAtAndCopy(5);
		HK_TEST(d.getSize()==9);
		HK_TEST(d[4]==4);
		HK_TEST(d[5]==6);
		HK_TEST(d[6]==7);
		HK_TEST(d.indexOf(4)==4);
		HK_TEST(d.indexOf(5)==-1);
		HK_TEST(d.indexOf(6)==5);
	}

	{
		hkArray<int> d(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i%5;
		}
		HK_TEST(d.indexOf(3)==3);
		HK_TEST(d.lastIndexOf(3)==8);
	}

	{
		hkArray<int> d;
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
		}
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkArray<int> d;
		d.reserve(10);
		for(i=0; i<10; ++i)
		{
			d.pushBackUnchecked(i);
		}
		HK_TEST(d.getSize()==10);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkArray<int> d;
		d.reserveExactly(10);
		for(i=0; i<10; ++i)
		{
			d.pushBackUnchecked(i);
		}
		HK_TEST(d.getSize()==10);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkArray<int> d;
		d.reserveExactly(10);
		for(i=0; i<10; ++i)
		{
			d.pushBackUnchecked(i);
		}
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkArray<int> d;
		d.reserveExactly(10);
		d.setSizeUnchecked(5);
		HK_TEST(d.getSize()==5);
		HK_TEST(d.getCapacity()>=10);
	}

	{
		hkArray<int> d;
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
		}
		d.insertAt(0,99);
		HK_TEST(d.getSize()==11);
		HK_TEST(d[0]==99);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i+1] == i);
		}
	}

	{
		hkArray<int> d;
		hkArray<int> e;
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
			e.pushBack(-i);
		}
		d.insertAt(3,e.begin(), e.getSize());
		HK_TEST(d.getSize()==20);
		HK_TEST(d[2]==2);
		HK_TEST(d[3]==0);
		HK_TEST(d[4]==-1);
		HK_TEST(d[12]==-9);
		HK_TEST(d[13]==3);
		HK_TEST(d[14]==4);
		HK_TEST(d[19]==9);

		d.swap(e);
	}

	{
		hkInplaceArray<int, 10> a;
		HK_TEST(a.getCapacity()>=10);
		for(i=0; i<20; ++i)
		{
			a.pushBack(i);
		}
		HK_TEST(a.getSize()==20);
		HK_TEST(a.getCapacity()>=20);

	}
}

int htl_main()
{
	algorithm();
	array();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(htl_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
