/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//#define HK_VECTOR4UTIL_transformPoints
//inline void	HK_CALL hkVector4Util::transformPoints( const hkTransform& t, const hkVector4* vectorsIn, int numVectors, hkVector4* vectorsOut )
//{
//	HK_ASSERT2( 0xf0237abd, numVectors > 0, "At least one element required");
//
//	__asm__(
//		".set		push				\n"			// save assembler options
//		".set		noreorder			\n"			// suppress reordering
//		"lv.q		c000,  0 + %0		\n"			// load the matrix
//		"lv.q		c010, 16 + %0		\n"
//		"lv.q		c020, 32 + %0		\n"
//		"lv.q		c030, 48 + %0		\n"
//		".set		pop					\n"			// restore assembler options
//		:											// no outputs
//		: "m" (t) 
//		);
//
//	// transform each of the vectors
//	do
//	{
//		__asm__(
//			".set		push				\n"			// save assembler options
//			".set		noreorder			\n"			// suppress reordering
//			"lv.q		c100, %1			\n"
//			"vone.s		s103				\n"
//			"vtfm4.q	c110, e000, c100	\n"
//			"sv.q		c110, %0			\n"
//			".set		pop					\n"			// restore assembler options
//			: "=m" (*vectorsOut)
//			: "m" (*vectorsIn) 
//			);
//
//		vectorsOut++;
//		vectorsIn++;
//	}
//	while ( --numVectors > 0 );
//}

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
