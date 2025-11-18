/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

#if 0
static int constructor_calls;
static int destructor_calls;

class FooSingleton : public hkSingleton<FooSingleton>
{
	public:

		FooSingleton()
			: m_value(99)
		{
			++constructor_calls;
		}

		~FooSingleton()
		{
			m_value = -99;
			++destructor_calls;
		}

		int m_value;

};

class BarSingleton0 : public hkSingleton<BarSingleton0>
{
	public:

		BarSingleton0() { }
		~BarSingleton0()
		{
		}
};

class BarSingleton1 : public hkSingleton<BarSingleton1>
{
	public:

		BarSingleton1() { }
		~BarSingleton1()
		{
		}
};

static hkReferencedObject* FooSingletonCreate()
{
	if( &BarSingleton0::getInstance()==HK_NULL)
	{
		return HK_NULL;
	}
	return new FooSingleton();
}

static hkReferencedObject* BarSingletonCreate0()
{
	if( &BarSingleton1::getInstance()==HK_NULL)
	{
		return HK_NULL;
	}
	return new BarSingleton0();
}

static hkReferencedObject* BarSingletonCreate1()
{
/*	if( &BarSingleton0::getInstance()==HK_NULL)
	{
		return HK_NULL;
	}*/

	return new BarSingleton1();
}

int singleton_main()
{
	constructor_calls = 0;
	destructor_calls = 0;

	hkBaseSystem::init();
	{
		HK_TEST(FooSingleton::getInstance().m_value == 99);
		FooSingleton::getInstance().m_value = 8;

		HK_TEST(constructor_calls==1);
		HK_TEST(destructor_calls==0);
	}
	hkBaseSystem::quit();

	HK_TEST(constructor_calls==1);
	HK_TEST(destructor_calls==1);

	hkBaseSystem::init();
	{
		HK_TEST(FooSingleton::getInstance().m_value == 99);

		HK_TEST(constructor_calls==2);
		HK_TEST(destructor_calls==1);
	}
	hkBaseSystem::quit();

	HK_TEST(constructor_calls==2);
	HK_TEST(destructor_calls==2);

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(singleton_main,     "Fast", "Test/Test/UnitTest/UnitTest/UnitTest/Base/",     __FILE__    );

// order is important!
HK_SINGLETON_IMPLEMENTATION(BarSingleton1, BarSingletonCreate1);
HK_SINGLETON_IMPLEMENTATION(FooSingleton, FooSingletonCreate);
HK_SINGLETON_IMPLEMENTATION(BarSingleton0, BarSingletonCreate0);

#endif

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
