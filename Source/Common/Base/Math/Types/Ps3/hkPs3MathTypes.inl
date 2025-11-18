/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/Fwd/hkcmath.h>
#include <Common/Base/Fwd/hkcfloat.h>

enum hkVector4Shuffle
{
	HK_VECTOR4_SHUF_X = 0x00010203,
	HK_VECTOR4_SHUF_Y = 0x04050607,
	HK_VECTOR4_SHUF_Z = 0x08090a0b,
	HK_VECTOR4_SHUF_W = 0x0c0d0e0f,
	HK_VECTOR4_SHUF_A = 0x10111213,
	HK_VECTOR4_SHUF_B = 0x14151617,
	HK_VECTOR4_SHUF_C = 0x18191a1b,
	HK_VECTOR4_SHUF_D = 0x1c1d1e1f,
	HK_VECTOR4_SHUF__ = 0x00000000
};
#define HK_VECTOR4_SHUF_0 HK_VECTOR4_SHUF_X
#define HK_VECTOR4_SHUF_1 HK_VECTOR4_SHUF_Y
#define HK_VECTOR4_SHUF_2 HK_VECTOR4_SHUF_Z
#define HK_VECTOR4_SHUF_3 HK_VECTOR4_SHUF_W

#define HK_VECTOR4_SHUFFLE(_a,_b,_c,_d) ((vector unsigned char)(vector unsigned int){HK_VECTOR4_SHUF_##_a, HK_VECTOR4_SHUF_##_b, HK_VECTOR4_SHUF_##_c,HK_VECTOR4_SHUF_##_d })

#define HK_QUADREAL_0000 ((hkQuadReal){0,0,0,0})

#if defined(__PPU__)
#	include <altivec.h>
	typedef vector float hkQuadReal;
	typedef vector signed int hkQuadInt;
	typedef vector unsigned int hkQuadUint;
#	define vec_rotl(_a,_n) vec_sld(_a,_a,_n)
#	define vec_nonzero_x(_a) vec_any_ne(vec_splat(_a, 0),HK_QUADREAL_0000)
#	define vec_mul(_a,_b) vec_madd(_a,_b,HK_QUADREAL_0000)
#else
#	include <vmx2spu.h>
	typedef vector float hkQuadReal;
	typedef vector signed int hkQuadInt;
	typedef vector unsigned int hkQuadUint;
#	define vec_mul	spu_mul
#	define vec_rotl	spu_rlqwbyte
#	define vec_nonzero_x(_a) si_to_int((qword)_a)
#endif

#define HK_TRANSPOSE4(v0,v1,v2,v3) { \
	hkQuadReal tmp0 = vec_mergeh( v0.getQuad(), v2.getQuad() ); \
	hkQuadReal tmp1 = vec_mergeh( v1.getQuad(), v3.getQuad() ); \
	hkQuadReal tmp2 = vec_mergel( v0.getQuad(), v2.getQuad() ); \
	hkQuadReal tmp3 = vec_mergel( v1.getQuad(), v3.getQuad() ); \
	v0 = vec_mergeh( tmp0, tmp1 ); \
	v1 = vec_mergel( tmp0, tmp1 ); \
	v2 = vec_mergeh( tmp2, tmp3 ); \
	v3 = vec_mergel( tmp2, tmp3 ); }

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

		hkSimdReal()
		{
		}

		hkSimdReal(const hkQuadReal& x)
			: m_real(x)
		{
		}

		hkSimdReal(hkReal x)
		{
#if defined(HK_PLATFORM_PS3SPU)
			m_real = (vec_float4)si_from_float(x);
#else
			hkQuadRealUnion u;
			u.r[0] = x;
			m_real = u.q;
#endif
		}

		void set(hkReal x)
		{
			hkQuadRealUnion u;
			u.r[0] = x;
			m_real = u.q;
		}


		operator hkReal() const
		{
			hkQuadRealUnion u;
			u.q = m_real;
			return u.r[0];
		}

		inline const hkQuadReal& getQuad() const
		{
			return m_real;
		}

	private:

		hkQuadReal m_real;
};

typedef const hkSimdReal hkSimdRealParameter;

#define HK_SIMD_REAL(a) hkSimdReal(a)

#if defined(__PPU__)
#	include <ppu_intrinsics.h>
#	include <Common/Base/Math/Functions/Ppc/hkPowerPcMathFuncs.inl>
	namespace hkMath
	{
#		define HK_MATH_ceil
		hkReal ceil(hkReal);
#		define HK_MATH_sin
		hkReal sin(hkReal);
#		define HK_MATH_cos
		hkReal cos(hkReal);
#		define HK_MATH_floor
		hkReal floor(hkReal);
	}
#endif

#if defined(__SPU__)
	namespace hkMath
	{
#		define HK_MATH_intInRange
		inline int intInRange( int value, int lowInclusive, int highExclusive )
		{
			vec_uint4 v = (vec_uint4)si_from_int(value);
			vec_uint4 l = (vec_uint4)si_from_int(lowInclusive);
			vec_uint4 h = (vec_uint4)si_from_int(highExclusive); // a <= b  means  !(a > b)
			return si_to_int( (qword) spu_andc( spu_cmpgt(h,v), spu_cmpgt(l,v) ) );
		}
	}
#endif

extern const hkQuadReal hkQuadRealHalf;
extern const hkQuadReal hkQuadReal1111;

namespace hkMath
{
	inline hkQuadReal quadReciprocal( hkQuadReal v )
	{
		vector float estimate = vec_re( v );
		//One round of Newton-Raphson refinement
		return vec_madd( vec_nmsub( estimate, v, hkQuadReal1111 ), estimate, estimate );
	}

	inline hkQuadReal quadReciprocalSquareRoot( hkQuadReal r )
	{
		hkQuadReal est = vec_rsqrte( r );
		//One round of Newton-Raphson refinement
		hkQuadReal est2 = vec_mul( est, est );
		hkQuadReal halfEst = vec_mul( est, hkQuadRealHalf );
		hkQuadReal slope = vec_nmsub( r, est2, hkQuadReal1111 );
		return vec_madd( slope, halfEst, est);
	}

	inline int isNegative(hkSimdReal r0)
	{
#if defined(__PPU__)
		return vec_any_lt( vec_splat(r0.getQuad(),0), HK_QUADREAL_0000 );
#else
		return si_to_int( (qword)spu_cmpgt(HK_QUADREAL_0000, r0.getQuad()) );
#endif
	}
}

class hkVector4;

#ifndef HK_PLATFORM_SPU
typedef const hkVector4& hkVector4Parameter;
#else
typedef const hkVector4 hkVector4Parameter;
#endif

inline const hkSimdReal HK_CALL operator* (hkSimdReal v0, hkSimdReal v1)
{
	return vec_madd(v0.getQuad(), v1.getQuad(), HK_QUADREAL_0000 );
}

inline const hkSimdReal HK_CALL operator- (hkSimdReal v0, hkSimdReal v1)
{
	return vec_sub( v0.getQuad(), v1.getQuad() );
}

inline const hkSimdReal HK_CALL operator+ (hkSimdReal v0, hkSimdReal v1)
{
	return vec_add( v0.getQuad(), v1.getQuad() );
}

inline const hkSimdReal HK_CALL operator/ (hkSimdReal v0, hkSimdReal v1)
{
	return vec_madd( v0.getQuad(), hkMath::quadReciprocal(v1.getQuad()), HK_QUADREAL_0000 );
}

inline const hkSimdReal HK_CALL operator- (hkSimdReal v0)
{
	return vec_sub( HK_QUADREAL_0000, v0.getQuad() );
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
		

#if defined(__PPU__)
		static const vec_uint4 s_invMaskFromBits[MASK_XYZW+1];
		static const vec_uint4 s_maskFromBits[MASK_XYZW+1];

		HK_FORCE_INLINE void setAnd( hkVector4Comparison a, hkVector4Comparison b ) { m_mask = vec_and(a.m_mask, b.m_mask); }

		HK_FORCE_INLINE hkBool32 allAreSet( Mask m ) const
		{
			vec_uint4 a = vec_or(s_invMaskFromBits[m], m_mask);
			return vec_all_eq( a, (vec_uint4)vec_splat_s32(-1) );
		}
		HK_FORCE_INLINE hkBool32 anyIsSet( Mask m ) const
		{
			vec_uint4 a = vec_and( s_maskFromBits[m], m_mask );
			return vec_any_ne( a, (vec_uint4)vec_splat_s32(0));
		}

		HK_FORCE_INLINE hkBool32 allAreSet() const
		{
			return vec_all_ne(m_mask, (vec_uint4)vec_splat_s32(0));
		}
		HK_FORCE_INLINE hkBool32 anyIsSet() const
		{
			return vec_any_ne(m_mask, (vec_uint4)vec_splat_s32(0));
		}

		HK_FORCE_INLINE int getMask() const
		{
			vec_uint4 spread = vec_and( m_mask, (vec_uint4){8,4,2,1} );
			union { vector signed int vi; int i[4]; } u;
			u.vi = vec_sums( (vector signed int)spread, (vector signed int)(0));
			return u.i[3];
		}
		HK_FORCE_INLINE int getMask(Mask m) const { return getMask() & m; }

#elif defined(__SPU__)

		HK_FORCE_INLINE void setAnd( hkVector4Comparison a, hkVector4Comparison b ) { m_mask = vec_and(a.m_mask, b.m_mask); }

	
		HK_FORCE_INLINE int getMask() const { return si_to_int( (qword)spu_gather(m_mask) ); }
		HK_FORCE_INLINE int getMask(Mask m) const { return si_to_int( (qword)spu_gather(m_mask) ) & m; }

		HK_FORCE_INLINE hkBool32 allAreSet( Mask m ) const { return (si_to_int( (qword)spu_gather(m_mask) ) & m) == m; }
		HK_FORCE_INLINE hkBool32 anyIsSet( Mask m ) const { return si_to_int( (qword)spu_gather(m_mask) ) & m; }

		HK_FORCE_INLINE hkBool32 allAreSet() const { return si_to_int( (qword)spu_gather(m_mask) ) == MASK_XYZW; }
		HK_FORCE_INLINE hkBool32 anyIsSet() const { return si_to_int( (qword)spu_gather(m_mask) ); }

#endif

	private:

		friend class hkVector4;
		vec_uint4 m_mask;
};

typedef hkVector4Comparison hkVector4ComparisonParameter;

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
