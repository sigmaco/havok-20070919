/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#define HK_MATRIX3_setZero
inline void hkMatrix3::setZero()
{
	__asm__ (
		".set		push			\n"				// save assembler options
		".set		noreorder		\n"				// suppress reordering
		"vmzero.q	e000			\n"				// set to identity
		"sv.q		c000,  0 + %0	\n"
		"sv.q		c010, 16 + %0	\n"
		"sv.q		c020, 32 + %0	\n"	
		".set		pop				\n"				// restore assembler options
		: "=m" (*this)
		);
}
//#define HK_MATRIX3_setDiagonal
//inline void hkMatrix3::setDiagonal( hkReal m00, hkReal m11, hkReal m22 )
//{	
//	__asm__ (
//		".set		push			\n"				// save assembler options
//		".set		noreorder		\n"				// suppress reordering
//		"vmzero.q	e000			\n"				// set to identity
//		"mfc1		$8, %1			\n"				// m00 -> s000
//		"mtv		$8, s000		\n"
//		"sv.q		c000,  0 + %0	\n"
//		"mfc1		$8, %2			\n"				// m11 -> s011
//		"mtv		$8, s011		\n"	
//		"sv.q		c010, 16 + %0	\n"
//		"mfc1		$8, %3			\n"				// m22 -> s022
//		"mtv		$8, s022		\n"
//		"sv.q		c020, 32 + %0	\n"	
//		".set		pop				\n"				// restore assembler options
//		: "=m" (*this)
//		: "f" (m00), "f" (m11), "f" (m22)
//		: "$8"
//		);	
//}

#define HK_MATRIX3_setIdentity
inline void hkMatrix3::setIdentity()
{	
	__asm__ (
		".set		push			\n"				// save assembler options
		".set		noreorder		\n"				// suppress reordering
		"vmidt.q	e000			\n"				// set to identity
		"sv.q		c000,  0 + %0	\n"
		"sv.q		c010, 16 + %0	\n"
		"sv.q		c020, 32 + %0	\n"
		".set		pop				\n"				// restore assembler options
		: "=m" (*this)
		);
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
