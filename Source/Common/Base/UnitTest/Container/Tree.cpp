/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/Tree/hkTree.h>

static void  tree()
{
    // Testing append and getdepth functionality
	{
		const int size = 4;
		hkTree<int> t;
		hkTreeBase::Iter itr = 0;
		int i;
		for(i = 0; i < size; ++i)
		{
			itr = t.append(itr,i);
		}

		if(itr)
		{
			HK_TEST(t.getDepth(itr)==3);
		}

		// Testing iterParent functionality
		{
			itr = t.iterParent(itr);
			HK_TEST(t.getDepth(itr)==2);
			itr = t.iterParent(itr);
			HK_TEST(t.getDepth(itr)==1);
			itr = t.iterParent(itr);
			HK_TEST(t.getDepth(itr)==0);
		}

	//Testing getValue and iterChildren functionality
	{
		int i = 0;
		for(hkTreeBase::Iter itr = t.iterGetRoot(); itr!=HK_NULL;
			itr = t.iterChildren(itr))
		{
			HK_TEST(t.getValue(itr)==i);
			i++;
		}
	}

	// Testing of getNumChildren()
	{
		for(hkTreeBase::Iter itr = t.iterGetRoot(); itr!=HK_NULL;
			itr = t.iterChildren(itr))
		{
			if(t.iterChildren(itr)!= HK_NULL)
			 {
				HK_TEST(t.getNumChildren(itr) == 1);
			 }
			 else
			 {
				 HK_TEST(t.getNumChildren(itr) == 0);
			 }

		}
	}
	// Testing of clear functionality
	{
			t.clear();
			HK_TEST(t.iterGetRoot()==HK_NULL);
	}

  }

	//Testing Siblings using append.
	{
		hkTree<int> t;
		hkTreeBase::Iter itr_root = t.iterGetRoot();

		for(int i = 0; i < 4; ++i)
		{
			t.append(itr_root,i+5);
		}

		int i = 5;
		for(hkTreeBase::Iter itr = t.iterGetRoot(); itr!=HK_NULL;
			itr = t.iterNext(itr))
		{
			HK_TEST(t.getValue(itr) == i);
			i++;
		}
	}

	// Testing iterNextPreOrder().
	{
		hkTree<int> t;
		hkTreeBase::Iter itr = t.iterGetRoot();

		int i;
		for(i = 0; i < 4; ++i)
		{
			t.append(itr,i+5);
		}

		i = 0;
		itr = t.iterGetRoot();
		while(itr!=HK_NULL)
		{
			HK_TEST(t.getValue(itr) == i+5);
			itr = t.iterNextPreOrder(itr);
			i++;
		}

	}

	// Testing of remove().
	{
		hkTree<int> t;
		hkTreeBase::Iter itr = t.iterGetRoot();

		//Creating Child
		for(int i = 0; i < 7; ++i)
		{
			itr = t.append(itr,i);
		}

		itr = t.iterParent(itr);
		int removed = t.getValue(itr);

		// Removing 2nd element from Last child.
		t.remove(itr);

		for(hkTreeBase::Iter itr = t.iterGetRoot(); itr!=HK_NULL;
			itr = t.iterChildren(itr))
		{
			HK_TEST(t.getValue(itr) != removed);
		}
	}
}

int tree_main()
{
	tree();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(tree_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
