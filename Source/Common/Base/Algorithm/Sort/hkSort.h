/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_HKALGORITHM_H
#define HKBASE_HKALGORITHM_H

#include <Common/Base/hkBase.h>

namespace hkAlgorithm
{

	/// swap the elements
	template<typename T>
	HK_FORCE_INLINE void HK_CALL swap(T& x, T& y)
	{
		T t(x);
		x = y;
		y = t;
	}


	/// swap the 16 byte aligned elements
	template<typename T>
	HK_FORCE_INLINE void HK_CALL swap16(T& x, T& y)
	{
		HK_ALIGN16( T t ) = x;
		x = y;
		y = t;
	}


	/// function object that routes calls to operator<
	template<typename T>
	class less
	{
		public:

			HK_FORCE_INLINE hkBool operator() ( const T& a, const T& b )
			{
				return ( a < b );
			}
	};


	/// heap sort.  you supply the functor, see hkAlgorithm::less for an example functor.
	template<typename T, typename L>
	void HK_CALL heapSort(T *pArr, int iSize, L cmpLess);


	/// Heap sort for the elements of the specified array.
	///
	/// \param *pArr		A pointer to the array to sort.
	/// \param iSize		The size of the array pointed to by *pArr.
	///
	template<typename T>
	void HK_CALL heapSort(T *pArr, int iSize)
	{
		heapSort( pArr, iSize, less<T>() );
	}

	// used by heapSort
	template<typename T, typename L>
	void HK_CALL downHeap(T *pArr, int k, int n, L cmpLess);


	/// quick sort.  you supply the functor, see hkAlgorithm::less for an example functor.
	template<typename T, typename L>
	HK_FORCE_INLINE	void HK_CALL quickSort(T *pArr, int iSize, L cmpLess);


	/// Quick sort for the elements of the specified array.
	///
	/// \param *pArr		A pointer to the data to sort.
	/// \param iSize		The size of the array pointed to by *pArr.
	///
	template<typename T>
	HK_FORCE_INLINE	void HK_CALL quickSort(T *pArr, int iSize)
	{
		quickSort( pArr, iSize, less<T>() );
	}

	template< typename T, typename L >
	void HK_CALL quickSortRecursive(T *pArr, int d, int h, L cmpLess);

        /// Quick sort using an explicit stack for efficiency reasons.
	template<typename T>
    HK_FORCE_INLINE void HK_CALL explicitStackQuickSort(T *pArr, int iSize)
	{
        explicitStackQuickSort( pArr, iSize, less<T>() );
	}
}

#if defined(HK_PS2) //|| defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_PS3SPU)
	#define hkSort hkAlgorithm::heapSort
#else
    #define hkSort hkAlgorithm::quickSort
    //#define hkSort hkAlgorithm::explicitStackQuickSort
#endif

#include <Common/Base/Algorithm/Sort/hkSort.inl>

#endif // HKBASE_HKALGORITHM_H

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
