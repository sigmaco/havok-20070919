/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/Fwd/hkcmath.h>
#include <Common/Base/Fwd/hkcfloat.h>

#include <ppcintrinsics.h>
#include <VectorIntrinsics.h>
typedef __vector4 hkQuadReal;

#define HK_TRANSPOSE4(v0,v1,v2,v3) { \
	hkQuadReal tmp0 = __vmrghw( v0, v2 ); \
	hkQuadReal tmp1 = __vmrghw( v1, v3 ); \
	hkQuadReal tmp2 = __vmrglw( v0, v2 ); \
	hkQuadReal tmp3 = __vmrglw( v1, v3 ); \
	v0 = __vmrghw( tmp0, tmp1 ); \
	v1 = __vmrglw( tmp0, tmp1 ); \
	v2 = __vmrghw( tmp2, tmp3 ); \
	v3 = __vmrglw( tmp2, tmp3 ); }

class hkVector4;
typedef const hkVector4& hkVector4Parameter;

union hkQuadRealUnion
{
	hkReal r[4];
	hkQuadReal q;
};

extern const hkQuadReal hkQuadReal1111;
extern const hkQuadReal hkQuadReal0000;
extern const hkQuadReal hkQuadRealHalf;

#define HK_QUADREAL_CONSTANT(a,b,c,d) {a,b,c,d}

class hkSimdReal
{
	public:

		hkSimdReal()
		{
		}

		hkSimdReal(const hkQuadReal& x)
			: m_real(x)
		{
		}


		hkSimdReal(const hkReal& x)
		{
			m_real = __lvlx(&x, 0);
			m_real = __vspltw( m_real, 0 );
		}

		void set( const hkQuadReal& x ){ m_real = x; }
		void set( const hkReal& x )
		{
			m_real = __lvlx(&x, 0);
			m_real = __vspltw( m_real, 0 );
		}

		operator hkReal() const
		{
			float x;
			__stvewx( m_real, &x, 0);
			return x;
		}

		inline hkQuadReal& getQuad()
		{
			return m_real;
		}

		inline const hkQuadReal& getQuad() const
		{
			return m_real;
		}

		inline static hkSimdReal HK_CALL create( hkReal a)
		{
			hkSimdReal sr; sr.set(a);
			return sr;
		}
	private:

		hkQuadReal m_real;
};

#define HK_SIMD_REAL(a) hkSimdReal::create(a)

namespace hkMath
{
	inline hkQuadReal quadReciprocal( hkQuadReal q )
	{
		__vector4 e = __vrefp( q );
		//One round of Newton-Raphson refinement
		return __vmaddfp( __vnmsubfp( e, q, hkQuadReal1111 ), e, e);
	}

	inline hkQuadReal quadReciprocalSquareRoot( hkQuadReal q )
	{
		__vector4 estimate = __vrsqrtefp( q );
		//One round of Newton-Raphson refinement
		// Refinement (Newton-Raphson) for 1.0 / sqrt(x)
		//     y0 = reciprocal_sqrt_estimate(x)
		//     y1 = y0 + 0.5 * y0 * (1.0 - x * y0 * y0) 
		//        = y0 + y0 * (0.5 - 0.5 * x * y0 * y0)
		// (from xmvector.inl)
		hkQuadReal OneHalfV = __vmulfp(q, hkQuadRealHalf);
		hkQuadReal Reciprocal = __vmulfp(estimate, estimate);
		hkQuadReal Scale = __vnmsubfp(OneHalfV, Reciprocal, hkQuadRealHalf);
		return __vmaddfp(estimate, Scale, estimate);
	}
}

typedef const hkSimdReal& hkSimdRealParameter;

inline const hkSimdReal HK_CALL operator* (hkSimdReal v0, hkSimdReal v1)
{
	hkSimdReal res; res.getQuad() = __vmulfp( v0.getQuad(), v1.getQuad() );
	return res;
}

inline const hkSimdReal HK_CALL operator- (hkSimdReal v0, hkSimdReal v1)
{
	hkSimdReal res; res.getQuad() = __vsubfp( v0.getQuad(), v1.getQuad() );
	return res;
}

inline const hkSimdReal HK_CALL operator+ (hkSimdReal v0, hkSimdReal v1)
{
	hkSimdReal res; res.getQuad() = __vaddfp( v0.getQuad(), v1.getQuad() );
	return res;
}

inline const hkSimdReal HK_CALL operator/ (hkSimdReal v0, hkSimdReal v1)
{
	__vector4 v1Recip = hkMath::quadReciprocal(v1.getQuad());
	hkSimdReal res; res.getQuad() = __vmulfp( v0.getQuad(), v1Recip );
	return res;
}

inline const hkSimdReal HK_CALL operator- (hkSimdReal v0)
{
	hkSimdReal res; res.getQuad() = __vsubfp( hkQuadReal0000, v0.getQuad() );
	return res;
}

#define HK_SIMD_COMPARE_MASK_X 8

	/// Result of a hkVector4 comparison.
class hkVector4Comparison
{
	public:

		enum Mask
		{
			MASK_NONE	= 0,
	        MASK_W		= 1,
	        MASK_Z		= 2,
	        MASK_ZW		= 3,
        
	        MASK_Y		= 4,
	        MASK_YW		= 5,
	        MASK_YZ		= 6,
	        MASK_YZW	= 7,
        
	        MASK_X		= 8,
	        MASK_XW		= 9,
	        MASK_XZ		= 10,
	        MASK_XZW	= 11,
        
	        MASK_XY		= 12,
	        MASK_XYW	= 13,
	        MASK_XYZ	= 14,
	        MASK_XYZW	= 15
		};

		static const hkQuadReal s_maskFromBits[MASK_XYZW+1];
		static const hkQuadReal s_invMaskFromBits[MASK_XYZW+1];

		HK_FORCE_INLINE void setAnd( hkVector4Comparison a, hkVector4Comparison b ) 
		{
			m_mask = __vand( a.m_mask,b.m_mask );
		}

		HK_FORCE_INLINE hkBool32 allAreSet( Mask m ) const
		{
			unsigned cr6;
			__vector4 a = __vor(m_mask, s_invMaskFromBits[m]);
			__vcmpequwR(a, __vspltisw(-1), &cr6 );
			return cr6 & (1<<7);
		}
		HK_FORCE_INLINE hkBool32 anyIsSet( Mask m ) const
		{
			unsigned cr6;
			__vector4 a = __vand(m_mask, s_maskFromBits[m]);
			__vcmpequwR(a, __vspltisw(0), &cr6 );
			return ~cr6 & (1<<7);
		}

		HK_FORCE_INLINE hkBool32 allAreSet() const
		{
			unsigned cr6;
			__vcmpequwR(m_mask, __vspltisw(-1), &cr6 );
			return cr6 & (1<<7);
		}
		HK_FORCE_INLINE hkBool32 anyIsSet() const
		{
			unsigned cr6;
			__vcmpequwR(m_mask, __vspltisw(0), &cr6 );
			return ~cr6 & (1<<7);
		}

		HK_FORCE_INLINE int getMask() const
		{
			hkQuadReal one4 = {{ 1.0f, 1.0f, 1.0f, 1.0f }};
			hkQuadReal bitSelect = {{ 8.0f, 4.0f, 2.0f, 1.0f }};

			hkQuadReal result = m_mask;
			result = __vand( result, one4 );
			result = __vmsum4fp( result, bitSelect );
			result = __vctsxs( result, 0 );

			return (int)result.u[0];
		}
		HK_FORCE_INLINE int getMask(Mask m) const { return getMask() & m; }

	private:

		hkQuadReal m_mask;
		friend class hkVector4;
};

#include <Common/Base/Math/Functions/Ppc/hkPowerPcMathFuncs.inl>

// An indication of which registers are used on Xbox 360
// We use registers in the range HK_USED_VMX_TOP to HK_USED_VMX_BOTTOM inclusive
#define HK_NUM_USED_VMX_REGS	17
#define HK_USED_VMX_TOP			95
#define HK_USED_VMX_BOTTOM		(HK_USED_VMX_TOP - HK_NUM_USED_VMX_REGS)

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
