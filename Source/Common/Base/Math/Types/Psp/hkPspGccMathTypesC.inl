/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// define this method to override the default
//#define HK_MATH_TYPES_hkFloor
//hkReal HK_CALL hkMath::hkFloor(hkReal r)
//{
//	hkReal result;
//	__asm__ (
//		".set		push			\n"				// save assembler options
//		".set		noreorder		\n"				// suppress reordering
//		"mtv		%1, s000		\n"
//		"vf2id.s	s000, s000, 0	\n"
//		"vi2f.s		s000, s000, 0	\n"
//		"sv.s       s000,  0 + %0	\n"
//		".set		pop				\n"				// restore assembler options
//		: "=m" (result)
//		: "r" (r) 
//		);
//	return result;				
//}

#define HK_MATH_TYPES_hkFloorToInt
int HK_CALL hkMath::hkFloorToInt(hkReal r)
{
	int result;
	__asm__ (
		".set		push			\n"				// save assembler options
		".set		noreorder		\n"				// suppress reordering
		"mtv		%1, s000		\n"
		"vf2id.s	s000, s000, 0	\n"
		"sv.s 		s000, 0 + %0	\n"
		".set		pop				\n"				// restore assembler options
		: "=m" (result)
		: "r" (r) 
		);
	return result;				
}

#define HK_MATH_TYPES_hkFloatToInt
int HK_CALL hkMath::hkFloatToInt(hkReal r)
{
	return int(r); //performs a truncation
}

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
