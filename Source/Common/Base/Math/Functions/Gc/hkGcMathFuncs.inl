/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#if defined(HK_COMPILER_MWERKS)
#	define HK_FSQRTE(ret,val) asm { frsqrte ret, val }
#	define HK_FABSF __fabs
#elif defined(HK_COMPILER_GCC)
#	define HK_FSQRTE(ret,val) asm("frsqrte %0, %1": "=f"(ret): "f"(val))
#	define HK_FABSF fabsf
#else
#   error unknown compiler
#endif

namespace hkMath
{
#	define HK_MATH_sqrtInverse
	inline hkReal HK_CALL sqrtInverse(hkReal r)
	{
		// Handle Singularity
		if( r <= 0.0f )
		{
			const unsigned int hkINFINITY = 0x7f800000; //IEEE 754 version
			union
			{
				hkReal f;
				unsigned int i;
			} val;

			val.i = hkINFINITY;
			return val.f;
		}

		register long double val = (long double) r;
		register long double ret;
		HK_FSQRTE(ret, val);

		// Perform 1 newton-raphson iteration
		hkReal newval, oldval;
		oldval = static_cast<hkReal>(ret);
		newval = 0.5f * oldval * (3.0f - r * oldval * oldval); //1st iteration

		return newval;
	}

#	define HK_MATH_sqrt
	inline hkReal HK_CALL sqrt(hkReal r)
	{
		// Handle Singularity
		if( r <= 0.0f )
		{
			return 0.0f;
		}

		// Get sqrtInverse(r)
		register long double val = (long double) r;
		register long double ret;
		HK_FSQRTE(ret, val);

		// Perform 1 newton-raphson iteration
		hkReal newval, oldval;
		oldval = static_cast<hkReal>(ret);
		newval = 0.5f * oldval * (3.0f - r * oldval * oldval); //1st iteration
		
		// Return r*sqrtInverse(r)
		return static_cast<hkReal>(r*newval);
	}

#	define HK_MATH_fabs
	inline hkReal HK_CALL fabs(hkReal r)
	{
		return static_cast<hkReal>(HK_FABSF(r));
	}

#	define HK_MATH_floor
	inline hkReal HK_CALL floor(hkReal r)
	{
		return static_cast<hkReal>(floor(r));
	}
}

#undef HK_FSQRTE
#undef HK_FABSF


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
