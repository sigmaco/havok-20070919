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
#include <Common/Base/hkBase.h>

int sort_main()
{
	const int NTEST = 2000;
	const int ASIZE = 1000;
	const int MAX = 100000;

	for(int i=0; i<NTEST; ++i)
	{
		int array[ASIZE];
		const int n = int(hkMath::randRange( 0, hkReal(ASIZE) ));
		int j;

		for(j=0; j<n; ++j)
		{
			array[j] = (int)hkMath::randRange(1, (float)MAX);
		}

		if (i&1)
		{
			hkAlgorithm::quickSort(array, n);
		} 
		else
		{
			hkAlgorithm::heapSort(array, n);
		}
		
		for(j=0; j<n-1; ++j)
		{
			if(array[j] > array[j+1])
			{
				break;
			}
		}

		if( n > 0)
		{
			HK_TEST2(j == n-1, " sort failed on iteration " << i << " element "<< j << (i&1?"(quicksort)":"(heapsort)") );
		}

	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(sort_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );



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
