/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
extern const hkQuadReal hkQuadReal1111;
namespace hkMath
{
#	define HK_MATH_sqrt
	inline hkReal HK_CALL sqrt(hkReal r)
	{
		hkReal res;
		__asm__ ("sqrt.s  %0, %1"
				: "=f" (res)
				: "f"  (r) );
		return res;
	}

#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	inline hkSimdReal HK_CALL sqrt(hkSimdRealParameter sr)
	{
		hkReal r = sqrt( hkReal(sr) );
	
		//_vsqrt(q, r.getQuad(), vu0_field_X);
		//_vwaitq();
		return r;
	}
#endif

#	define HK_MATH_sqrtInverse
	inline hkReal HK_CALL sqrtInverse(hkReal r, hkReal denominator=1.0f)
	{
		hkReal res;
		__asm__ ("rsqrt.s  %0, %1, %2"
				: "=f" (res)
				: "f"  (denominator), "f" (r) );
		return res;
	}

#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	inline hkSimdReal HK_CALL sqrtInverse(hkSimdReal r)
	{
		hkReal q;
		q = sqrtInverse( hkReal(r) );
	
		//_vrsqrt( q, vu0_vf0, vu0_field_W, r.getQuad(), vu0_field_X );
		//_vwaitq();
		return q;
	}

	inline hkQuadReal quadReciprocal( hkQuadReal q )
	{
		hkQuadReal ret;
		asm(
			"vdiv Q, %1x, %2x		\n"
			"vwaitq					\n"
			"vaddq.x %0, vf0, Q		\n"
			"vdiv Q, %1y, %2y		\n"
			"vwaitq					\n"
			"vaddq.y %0, vf0, Q		\n"
			"vdiv Q, %1z, %2z		\n"
			"vwaitq					\n"
			"vaddq.z %0, vf0, Q		\n"
			"vdiv Q, %1w, %2w		\n"
			"vwaitq					\n"
			"vaddq.w %0, vf0, Q		\n"
				: "=&j"(ret)
				: "j"(hkQuadReal1111), "j"(q)  );
		return ret;
	}
#endif

#	define HK_MATH_fabs
	inline hkReal HK_CALL fabs(hkReal r)
	{
		hkReal res;
		__asm__ ("abs.s  %0, %1"
				: "=f" (res)
				: "f"  (r) );
		return res;
	}

#	define HK_MATH_prefetch128
	inline void prefetch128( const void* p )
	{
		__asm__ __volatile__("pref 0, 0(%0)"
							:
							: "r" (p) );
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
