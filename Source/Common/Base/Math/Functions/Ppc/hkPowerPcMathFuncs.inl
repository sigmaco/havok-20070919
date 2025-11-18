/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

namespace hkMath
{
#	define HK_MATH_sqrt
	inline hkReal HK_CALL sqrt(hkReal r)
	{
		return __fsqrts(r);
	}

	inline hkSimdReal HK_CALL sqrt(hkSimdRealParameter r)
	{
		hkReal x = r;
		hkSimdReal res; res.set(__fsqrts( x ));
		return res;
	}

#	define HK_MATH_sqrtInverse
	inline hkReal HK_CALL sqrtInverse( hkReal r )
	{
		return ( 1.0f / __fsqrts(r) );
	}

	inline hkSimdReal HK_CALL sqrtInverse(hkSimdReal r)
	{
		hkReal x = r;
		hkSimdReal res; res.set( 1.0f / __fsqrts( x ) );
		return res;
	}

#if defined(HK_PLATFORM_PS3)
#	define HK_MATH_fabs
	inline hkReal HK_CALL fabs(hkReal r)
	{
		return __fabsf(r);
	}
	// on x360 the normal fabs is the fast one
#endif

#	define HK_MATH_min2
	inline hkReal HK_CALL min2( hkReal x, hkReal y)
	{
		return (hkReal)__fsel( x - y , y , x);
	}

#	define HK_MATH_max2
	inline hkReal HK_CALL max2( hkReal x, hkReal y)
	{
		return (hkReal)__fsel( x - y , x , y);
	}

	template <typename T>
	inline T HK_CALL max2( T x, T y)
	{
		return x > y ? x : y;
	}

	template <typename T>
	inline T HK_CALL min2( T x, T y)
	{
		return x < y ? x : y;
	}

#	define HK_MATH_prefetch128
	inline void prefetch128( const void* p )
	{
#		if defined(__PPU__)
		__dcbt(p);
#		else
		__dcbt(0, p);
#		endif
	}

#	define HK_MATH_forcePrefetch
	template<int SIZE>
	inline void forcePrefetch( const void* p )
	{
#		if defined(__PPU__)
		__dcbt(p);
		if ( SIZE > 128){ __dcbt(hkAddByteOffsetConst(p,128)); }
		if ( SIZE > 256){ __dcbt(hkAddByteOffsetConst(p,256)); }
		if ( SIZE > 384){ __dcbt(hkAddByteOffsetConst(p,384)); }
#		else	// XBOX360
		__dcbt(0, p);
		if ( SIZE > 128){ __dcbt(128, p); }
		if ( SIZE > 256){ __dcbt(256, p); }
		if ( SIZE > 384){ __dcbt(384, p); }
#		endif
	}


#	define HK_MATH_fselectGreaterEqualZero
	inline hkReal fselectGreaterEqualZero( hkReal testVar, hkReal ifTrue, hkReal ifFalse)
	{
		return (hkReal)__fsel(testVar, ifTrue, ifFalse);
	}

#	define HK_MATH_fselectGreaterZero
	inline hkReal fselectGreaterZero( hkReal testVar, hkReal ifTrue, hkReal ifFalse)
	{ 
		return (hkReal)__fsel(-testVar, ifTrue, ifFalse);
	}

#	define HK_MATH_fselectEqualZero
	inline hkReal fselectEqualZero( hkReal testVar, hkReal ifTrue, hkReal ifFalse)
	{ 
		return (hkReal)__fsel( -testVar, __fsel(testVar, ifTrue, ifFalse), ifFalse );
	}
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
