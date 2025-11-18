/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Container/Queue/hkQueue.h>


static void queue()
{
	// Testing Queue functionality
	const int element = 10;
	int data;
	{
		hkQueue<int> que;
		HK_TEST(que.getCapacity()==0);
		HK_TEST(que.getSize()==0);
		HK_TEST(que.isEmpty());
		que.enqueue(element);
		HK_TEST(que.getSize()==1);
		que.dequeue(data);
		HK_TEST(element==data);
		que.clear();
	}
	// Testing adding and removing elements from queue
	{
		hkQueue<int> que(5);
		HK_TEST(que.getCapacity()==5);
		HK_TEST(que.isEmpty());
		int i;
		for(i = 0; i < 5; ++i)
		{
			que.enqueue(i);
		}
		que.enqueueInFront(element);
		HK_TEST(que.getSize()==6);
		que.dequeue(data);
		HK_TEST(data==element);
		for(i = 0; i < 5; ++i)
		{
			que.dequeue(data);
			HK_TEST(data==i);
		}
		HK_TEST(que.isEmpty());
		que.clear();
	}
	// Testing adding elements from front into queue
	{
		hkQueue<int> que;
		que.setCapacity(3);
		que.enqueueInFront(element);
		HK_TEST(que.getCapacity()!=4);
		que.enqueue(100);
		que.enqueue(200);
		que.enqueue(300);
		HK_TEST(que.getSize()==4);
		que.dequeue(data);
		HK_TEST(data==element);
		que.clear();
		HK_TEST(que.getSize()==0);
	}
}

int queue_main()
{
	queue();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(queue_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
