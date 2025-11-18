/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

namespace hkMath
{	
	// Note: PSP VFPU works in hecto-gradians.

#	define HK_MATH_sqrt
	inline hkReal HK_CALL sqrt( hkReal x )
	{
		hkReal result;
		__asm__(
			".set		push				\n"			// save assembler options
			".set		noreorder			\n"			// suppress reordering
			"mtv		%1, s000			\n"
			"vsqrt.s	s000, s000			\n"
			"sv.s		s000, 0 + %0		\n"		
			".set		pop					\n"			// restore assembler options
			: "=m" (result)								// outputs
			: "r" (x)
			);
		return result;
	}
	
#	define HK_MATH_sin
	inline hkReal HK_CALL sin( hkReal r )
	{
		hkReal result;
		__asm__(
			".set		push				\n"			// save assembler options
			".set		noreorder			\n"			// suppress reordering
			"mtv		%1, s000			\n"
			"vcst.s		s001, 0x05			\n"			// 2/PI constant
			"vmul.s		s000, s000, s001	\n"
			"vsin.s		s000, s000			\n"
			"sv.s		s000, 0 + %0		\n"				
			".set		pop					\n"			// restore assembler options
			: "=m" (result)								// outputs
			: "r" (r)
			);
		return result;
	}

#	define HK_MATH_cos
	inline hkReal HK_CALL cos( hkReal r )
	{
		hkReal result;
		__asm__(
			".set		push				\n"			// save assembler options
			".set		noreorder			\n"			// suppress reordering
			"mtv		%1, s000			\n"
			"vcst.s		s001, 0x05			\n"			// 2/PI constant
			"vmul.s		s000, s000, s001	\n"
			"vcos.s		s000, s000			\n"
			"sv.s		s000, 0 + %0		\n"				
			".set		pop					\n"			// restore assembler options
			: "=m" (result)								// outputs
			: "r" (r) 
			);
		return result;
	}

#	define HK_MATH_acos
	inline hkReal HK_CALL acos(hkReal r)
	{
		HK_ASSERT(0x41278654, ( ( r < 1.001f ) && ( r > -1.001f ) ) );
		if( ( r >= 1.0f ) || ( r <= -1.0f ) )
		{
			r = ( r>0 )	? 0 : 3.14159265358979f;
			return r;
		}
		
		hkReal result;
	
		__asm__ (
			".set		push				\n"				// save assembler options
			".set		noreorder			\n"				// suppress reordering
			"lv.s		s000, %1			\n"
			"vasin.s	s000, s000			\n"
			"vcst.s		s001, 0x08			\n"				// PI/2 constant
			"vocp.s		s000, s000			\n"				// 1 - asin(r)
			"vmul.s		s000, s000, s001	\n"
			"sv.s		s000, 0 + %0		\n"
			".set		pop					\n"				// restore assembler options
			: "=m" (result)
			: "m" (r)
			);
	
		return result;
	}
	
#	define HK_MATH_asin
	inline hkReal HK_CALL asin(hkReal r)
	{
		HK_ASSERT(0x286a6f5f, ( ( r < 1.001f ) && ( r > -1.001f ) ) );
		if( ( r >= 1.0f ) || ( r <= -1.0f ) )
		{
			r = ( r>0 )	? 0.5f * 3.14159265358979f : -0.5f * 3.14159265358979f;
			return r;
		}
	
		hkReal result;
		__asm__ (
			".set		push				\n"				// save assembler options
			".set		noreorder			\n"				// suppress reordering
			"lv.s		s000, %1			\n"
			"vasin.s	s000, s000			\n"
			"vcst.s		s001, 0x08			\n"				// PI/2 constant
			"vmul.s		s000, s000, s001	\n"
			"sv.s		s000, 0 + %0		\n"
			".set		pop					\n"				// restore assembler options
			: "=m" (result)
			: "m" (r)
			);
		return result;
	}

#	define HK_MATH_sqrtInverse
	inline hkReal HK_CALL sqrtInverse( hkReal r )
	{
		hkReal result;
		__asm__(
			".set		push				\n"			// save assembler options
			".set		noreorder			\n"			// suppress reordering
			"mtv		%1, s000			\n"
			"vrsq.s		s000, s000			\n"
			"sv.s		s000, 0 + %0		\n"				
			".set		pop					\n"			// restore assembler options
			: "=m" (result)								// outputs
			: "r" (r) 
			);
		return result;			
	}

#	define HK_MATH_floor
	inline hkReal HK_CALL floor( hkReal r )
	{
		hkReal result;
		__asm__ (
			".set		push			\n"				// save assembler options
			".set		noreorder		\n"				// suppress reordering
			"mtv		%1, s000		\n"
			"vf2id.s	s000, s000, 0	\n"
			"vi2f.s		s000, s000, 0	\n"
			"sv.s		s000, 0 + %0	\n"			
			".set		pop				\n"				// restore assembler options
			: "=m" (result)
			: "r" (r) 
			);
		return result;			
	}
	
#	define HK_MATH_hkToIntFast
	inline int HK_CALL hkToIntFast(hkReal r)
	{
		return int(r); //performs a truncation
	}


} /* namespace hkMath */

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
