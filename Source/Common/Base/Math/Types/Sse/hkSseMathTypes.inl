/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <xmmintrin.h>
#define HK_TRANSPOSE4(A,B,C,D) _MM_TRANSPOSE4_PS(A,B,C,D)

typedef __m128 hkQuadReal;

class hkVector4;
typedef const hkVector4& hkVector4Parameter;

union hkQuadRealUnion
{
	hkReal r[4];
	hkQuadReal q;
};

#define HK_QUADREAL_CONSTANT(a,b,c,d) {a,b,c,d}
#define HK_SIMD_REAL(a) hkSimdReal(a)
class hkSimdReal
{
	public:

		hkSimdReal(const hkQuadReal& x)
			: m_real(x)
		{
		}

		hkSimdReal(hkReal x)
		{
			m_real = _mm_load_ss(&x);
		}

		hkSimdReal(){}

		operator hkReal() const
		{
			hkReal s;
			_mm_store_ss(&s, m_real);
			return s;
		}

		HK_FORCE_INLINE hkQuadReal broadcast() const
		{
			return _mm_shuffle_ps(m_real, m_real, 0);
		}

		HK_FORCE_INLINE const hkQuadReal& getQuad() const
		{
			return m_real;
		}

	private:

		hkQuadReal m_real;
};

typedef const hkSimdReal& hkSimdRealParameter;

inline hkSimdReal HK_CALL operator* (hkSimdRealParameter r, hkSimdRealParameter s)
{
	return _mm_mul_ss(r.getQuad(),s.getQuad());
}

inline hkSimdReal HK_CALL operator- (hkSimdRealParameter r, hkSimdRealParameter s)
{
	return _mm_sub_ss(r.getQuad(),s.getQuad());
}

inline hkSimdReal HK_CALL operator+ (hkSimdRealParameter r, hkSimdRealParameter s)
{
	return _mm_add_ss(r.getQuad(),s.getQuad());
}

inline hkSimdReal HK_CALL operator/ (hkSimdRealParameter r, hkSimdRealParameter s)
{
	return _mm_div_ss(r.getQuad(),s.getQuad());
}

inline hkSimdReal HK_CALL operator- (hkSimdRealParameter r)
{
    extern const hkQuadReal hkQuadReal0000;
	return _mm_sub_ss(hkQuadReal0000,r.getQuad());
}


	/// Result of a hkVector4 comparison.
class hkVector4Comparison
{
	public:

		enum Mask
		{
			MASK_NONE	= 0,
			MASK_X		= 1,
			MASK_Y		= 2,
			MASK_XY		= 3,

			MASK_Z		= 4,
			MASK_XZ		= 5,
			MASK_YZ		= 6,
			MASK_XYZ	= 7,

			MASK_W		= 8,
			MASK_XW		= 9,
			MASK_YW		= 10,
			MASK_XYW	= 11,

			MASK_ZW		= 12,
			MASK_XZW	= 13,
			MASK_YZW	= 14,
			MASK_XYZW	= 15
		};

		HK_FORCE_INLINE void setAnd( hkVector4Comparison a, hkVector4Comparison b ) { m_mask = _mm_and_ps( a.m_mask,b.m_mask ); }

		HK_FORCE_INLINE hkBool32 allAreSet( Mask m ) const { return (_mm_movemask_ps(m_mask) & m) == m; }
		HK_FORCE_INLINE hkBool32 anyIsSet( Mask m ) const { return _mm_movemask_ps(m_mask) & m; }

		HK_FORCE_INLINE hkBool32 allAreSet() const { return _mm_movemask_ps(m_mask) == MASK_XYZW; }
		HK_FORCE_INLINE hkBool32 anyIsSet() const { return _mm_movemask_ps(m_mask); }

		HK_FORCE_INLINE int getMask() const { return _mm_movemask_ps(m_mask); }
		HK_FORCE_INLINE int getMask(Mask m) const { return _mm_movemask_ps(m_mask) & m; }

	private:

		hkQuadReal m_mask;
		friend class hkVector4;
};

typedef const hkVector4Comparison& hkVector4ComparisonParameter;

#define HK_SIMD_COMPARE_MASK_X 1

extern const hkQuadReal hkQuadRealHalf;
extern const hkQuadReal hkQuadReal3333;

namespace hkMath
{
	inline int HK_CALL isNegative(const hkSimdReal& r0)
	{
		return _mm_movemask_ps(r0.getQuad()) & hkVector4Comparison::MASK_X;
	}

	inline hkSimdReal HK_CALL sqrt(hkSimdRealParameter r)
	{
		return _mm_sqrt_ss(r.getQuad());
	}

#	if defined(HK_ARCH_IA32) && !defined(HK_COMPILER_GCC)
#	define HK_MATH_hkToIntFast
		// Fast rounding, however last bit might be wrong
	inline int HK_CALL hkToIntFast( hkReal r ){
		int i;
		_asm {
			fld r
			fistp i
		}
		return i;
	}
#endif

#	define HK_MATH_prefetch128
	inline void prefetch128( const void* p)
	{
		_mm_prefetch( (const char*)p, _MM_HINT_NTA );
	}

#	define HK_MATH_forcePrefetch
	template<int SIZE>
	inline void forcePrefetch( const void* p )
	{
		const char* q = (const char*)p;
		_mm_prefetch( q, _MM_HINT_NTA );
		if ( SIZE > 64){  _mm_prefetch( q + 64, _MM_HINT_NTA ); }
		if ( SIZE > 128){ _mm_prefetch( q + 128, _MM_HINT_NTA ); }
		if ( SIZE > 192){ _mm_prefetch( q + 192, _MM_HINT_NTA ); }
	}

    inline hkQuadReal quadReciprocal( hkQuadReal r )
    {
		hkQuadReal e = _mm_rcp_ps( r );
		//One round of Newton-Raphson refinement
        return _mm_sub_ps(_mm_add_ps(e,e), _mm_mul_ps(_mm_mul_ps(e, r), e));
    }

    inline hkQuadReal quadReciprocalSquareRoot( hkQuadReal r )
    {
		hkQuadReal e = _mm_rsqrt_ps(r);
		hkQuadReal he = _mm_mul_ps(hkQuadRealHalf,e);
		hkQuadReal ree = _mm_mul_ps(_mm_mul_ps(r,e),e);
		return _mm_mul_ps(he, _mm_sub_ps(hkQuadReal3333, ree) );
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
