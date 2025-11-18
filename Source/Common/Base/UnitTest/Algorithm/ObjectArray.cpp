/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/Array/hkObjectArray.h>

static int constructs;
static int destructs;
extern "C" int HK_CALL rand();

struct Foo : public hkReferencedObject
{
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

	Foo()
	{
		m_value = rand();
		++constructs;
	}
	Foo(int n)
	{
		m_value = n;
		++constructs;
	}
	

	~Foo()
	{
		++destructs;
	}
	Foo( const Foo& f)
		: hkReferencedObject(f)
	{
		m_value = f.m_value;
		++constructs;
	}
	void operator=(const Foo& f)
	{
		m_value = f.m_value;
		++constructs; 
		++destructs; 
	}

	hkBool operator==(const Foo& f) const 
	{ 
		return m_value == f.m_value; 
	}
	hkBool operator!=(const Foo& f) const
	{ 
		return m_value != f.m_value;
	}


	int m_value;
};

static void object_array()
{
	constructs = 0;
	destructs = 0;

	int i;
	{
		hkObjectArray<Foo> a;
		HK_TEST(a.getSize()==0);
		HK_TEST(a.isEmpty());
		HK_TEST(constructs==0);
		HK_TEST(destructs==0);
	}

	constructs = 0;
	destructs = 0;
	
	{
		hkObjectArray<Foo> b(10);
		HK_TEST(constructs==10);
		HK_TEST(destructs==0);
		HK_TEST(b.getSize()==10);
		HK_TEST(!b.isEmpty());

		b.popBack();
		HK_TEST(constructs==10);
		HK_TEST(destructs==1);
		HK_TEST(b.getSize()==9);

		b.clear();
		HK_TEST(constructs==10);
		HK_TEST(destructs==10);
		HK_TEST(b.getSize()==0);
		HK_TEST(b.isEmpty());
		HK_TEST(b.getCapacity()!=0);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> a;
		a.reserve(5);
		HK_TEST(constructs==0);
		HK_TEST(destructs==0);
		a.setSize(3);
		HK_TEST(constructs==3);
		HK_TEST(destructs==0);
		a.setSize(4);
		HK_TEST(constructs==4);
		HK_TEST(destructs==0);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> a;
		a.reserve(10);
		HK_TEST(constructs==0);
		HK_TEST(destructs==0);
		a.setSize(5);
		HK_TEST(constructs==5);
		HK_TEST(destructs==0);
		a.setSize(15);
		HK_TEST(constructs==20);
		HK_TEST(destructs==5);
	}

	constructs = 0;
	destructs = 0;

	{
		Foo initial = 99;
		hkObjectArray<Foo> c(5, initial);
		HK_TEST(c.getSize()==5);
		for(i=0; i<c.getSize(); ++i)
		{
			HK_TEST(c[i]==initial);
		}
		HK_TEST(constructs==6); // 5 + 1 for initial
		HK_TEST(destructs==0);

		c.clearAndDeallocate();
		HK_TEST(constructs==6);
		HK_TEST(destructs==5);
		HK_TEST(c.getSize()==0);
		HK_TEST(c.getCapacity()==0);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> d(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i;
		}
		HK_TEST(constructs - destructs == 10);
		
		d.removeAt(5);
		HK_TEST(constructs - destructs == 9);
		HK_TEST(d.getSize()==9);
		HK_TEST(d[5]!=5);
		HK_TEST(d[4]==4);
		HK_TEST(d[6]==6);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> d(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i;
		}
		HK_TEST(constructs - destructs == 10);
		
		d.removeAtAndCopy(5);
		HK_TEST(constructs - destructs == 9);
		HK_TEST(d.getSize()==9);
		HK_TEST(d[5]==6);
		HK_TEST(d[4]==4);
		HK_TEST(d[6]==7);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> d;
		d.setSize(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i;
		}
		HK_TEST(constructs - destructs == 10);
		d.removeAtAndCopy(5);
		HK_TEST(constructs - destructs == 9);

		HK_TEST(d.getSize()==9);
		HK_TEST(d[4]==4);
		HK_TEST(d[5]==6);
		HK_TEST(d[6]==7);
		HK_TEST(d.indexOf(4)==4);
		HK_TEST(d.indexOf(5)==-1);
		HK_TEST(d.indexOf(6)==5);
	}

	{
		hkObjectArray<Foo> d(10);
		for(i=0; i<d.getSize(); ++i)
		{
			d[i] = i%5;
		}
		HK_TEST(d.indexOf(3)==3);
		HK_TEST(d.lastIndexOf(3)==8);
	}

	{
		hkObjectArray<Foo> d;
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
		hkObjectArray<Foo> d;
		d.reserve(10);
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
		}
		HK_TEST(d.getSize()==10);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkObjectArray<Foo> d;
		d.reserve(10);
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
		}
		HK_TEST(d.getSize()==10);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i]==i);
		}
	}

	{
		hkObjectArray<Foo> d;
		d.reserve(10);
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
		hkObjectArray<Foo> d;
		d.reserve(10);
		d.setSize(5);
		HK_TEST(d.getSize()==5);
		HK_TEST(d.getCapacity()>=10);
	}

	constructs = 0;
	destructs = 0;

	{
		hkObjectArray<Foo> d;
		d.expandBy(1);
		d.expandBy(1);
		HK_TEST(constructs - destructs == 2);
	}
/*
	{
		hkObjectArray<Foo> d;
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
		}
		Foo foo = 99;
		d.insertAt(0, foo);
		HK_TEST(d.getSize()==11);
		HK_TEST(d[0]==foo);
		for(i=0; i<10; ++i)
		{
			HK_TEST(d[i+1] == i);
		}
	}
*/
/*
	{
		hkObjectArray<Foo> d;
		hkObjectArray<Foo> e;
		for(i=0; i<10; ++i)
		{
			d.pushBack(i);
			e.pushBack(-i);
		}
		d.insertAt(3,e);
		HK_TEST(d.getSize()==20);
		HK_TEST(d[2]==2);
		HK_TEST(d[3]==0);
		HK_TEST(d[4]==-1);
		HK_TEST(d[12]==-9);
		HK_TEST(d[13]==3);
		HK_TEST(d[14]==4);
		HK_TEST(d[19]==9);
	} 
*/
	{
		hkObjectArray< hkArray<int> > a;
		a.setSize(10);
	}
	{
		hkObjectArray< hkObjectArray<Foo> > a;
		a.setSize(10);
	}

}

int object_array_main()
{
	object_array();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(object_array_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
