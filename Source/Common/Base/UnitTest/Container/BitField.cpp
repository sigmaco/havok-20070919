/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/BitField/hkBitField.h>

static void BitField()
{
	// Testing get() & getSize() with value '0'.
	{
		hkBitField bf(8);
		HK_TEST(bf.get(1)==0);
		HK_TEST(bf.getSize()==8);
	}

    // Testing get() & getSize() with value '1'.
	{
		hkBitField bf(16,1);
		HK_TEST(bf.get(1)!=0);
		HK_TEST(bf.getSize()==16);
	}

	// Testing clear().
	{
		hkBitField bf(32,1);
		HK_TEST(bf.get(17)==1);
		bf.clear(17);
		HK_TEST(bf.get(17)==0);
		HK_TEST(bf.get(7)==1);
		HK_TEST(bf.getSize()==32);
	}

	// Testing set().
	{
		hkBitField bf(32,0);
		HK_TEST(bf.get(17)==0);
		bf.set(17);
		HK_TEST(bf.get(17)==1);
		HK_TEST(bf.get(7)==0);
	}

	// Testing assign().
	{
		hkBitField bf(32,0);
		HK_TEST(bf.get(17)==0);
		bf.assign(17,1);
		HK_TEST(bf.get(17)==1);
		HK_TEST(bf.get(7)==0);
	}

	// Testing assignAll().
	{
		hkBitField bf(16,0);
		HK_TEST(bf.get(7)==0);
		bf.assignAll(1);
		int i;
		for(i = 0; i < bf.getSize(); i++)
		{
			HK_TEST(bf.get(i)==1);
		}
	}

	// Testing setSize().
	{
		hkBitField bf(32,0);
		bf.setSize(12);
		HK_TEST(bf.getSize()==12);
		int i;
		for(i = 0; i < bf.getSize(); i++)
		{
			HK_TEST(bf.get(i)==0);
		}
	}
}

int bitfield_main()
{
	BitField();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(bitfield_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
