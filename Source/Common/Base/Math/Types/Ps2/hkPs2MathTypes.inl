/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#if defined(HK_COMPILER_HAS_INTRINSICS_PS2) 
#	include <mmintrin.h>
#	include <vu0intrin.h>
 	typedef __v4sf hkQuadReal;
#else
	struct hkQuadReal
	{
		hkUint128 m_quad;
	};
#endif

class hkVector4;
typedef const hkVector4& hkVector4Parameter;


#include <Common/Base/Fwd/hkcmath.h>
#include <Common/Base/Fwd/hkcfloat.h>

union hkQuadRealUnion
{
	hkReal r[4];
	hkQuadReal q;
};

#define HK_TRANSPOSE4_SWAP(a,b) t = a; a = b; b = t
#define HK_TRANSPOSE4(v0,v1,v2,v3) { hkReal t; \
	HK_TRANSPOSE4_SWAP( v0(1), v1(0) ); \
	HK_TRANSPOSE4_SWAP( v0(2), v2(0) ); \
	HK_TRANSPOSE4_SWAP( v0(3), v3(0) ); \
	HK_TRANSPOSE4_SWAP( v1(2), v2(1) ); \
	HK_TRANSPOSE4_SWAP( v1(3), v3(1) ); \
	HK_TRANSPOSE4_SWAP( v2(3), v3(2) ); }
	
#define HK_QUADREAL_CONSTANT(a,b,c,d) ((hkQuadRealUnion){{a,b,c,d}}).q
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
#	if defined(HK_COMPILER_HAS_INTRINSICS_PS2)
			_vaddf(m_real, vu0_field_X, vu0_vf0, x);
#	else
			asm( "	qmtc2 %1, %0 " : "=j"(this->m_real):  "r"(x)  );
			//hkQuadRealUnion u;	u.r[0] = x;		m_real = u.q;
#	endif
		}

		operator hkReal() const
		{
			//hkQuadRealUnion u;	u.q = m_real;	return u.r[0];
			float ret;
			asm( "	qmfc2 %0, %1 " : "=r"(ret):  "j"(this->m_real)  );
			return ret;
		}

		inline const hkQuadReal& getQuad() const
		{
			return m_real;
		}

	private:

		hkQuadReal m_real;
};

typedef const hkSimdReal& hkSimdRealParameter;

inline const hkSimdReal HK_CALL operator* (hkSimdReal v0, hkSimdReal v1)
{
	hkQuadReal ret;
#	if defined(HK_COMPILER_HAS_INTRINSICS_PS2)
	_vmul(ret, vu0_field_X, v0.getQuad(), v1.getQuad());
#	else
	asm("vmul.x %0, %1, %2" : "=j"(ret) : "j"(v0.getQuad()), "j"(v1.getQuad())  );
#	endif
	return ret;
}

inline const hkSimdReal HK_CALL operator- (hkSimdReal v0, hkSimdReal v1)
{
	hkQuadReal ret;
#	if defined(HK_COMPILER_HAS_INTRINSICS_PS2)
	_vsub(ret, vu0_field_X, v0.getQuad(), v1.getQuad());
#	else
	asm("vsub.x %0, %1, %2" : "=j"(ret) : "j"(v0.getQuad()), "j"(v1.getQuad())  );
#	endif
	return ret;
}

inline const hkSimdReal HK_CALL operator+ (hkSimdReal v0, hkSimdReal v1)
{
	hkQuadReal ret;
#	if defined(HK_COMPILER_HAS_INTRINSICS_PS2)
	_vadd(ret, vu0_field_X, v0.getQuad(), v1.getQuad());
#	else
	asm("vadd.x %0, %1, %2" : "=j"(ret) : "j"(v0.getQuad()), "j"(v1.getQuad())  );
#	endif
	return ret;
}

inline const hkSimdReal HK_CALL operator-(hkSimdReal v)
{
	hkQuadReal ret;
#	if defined(HK_COMPILER_HAS_INTRINSICS_PS2)
	_vsub(ret, vu0_field_X, vu0_vf0, v.getQuad());
#	else
	asm("vsub.x %0, vf0, %1" : "=j"(ret) : "j"(v.getQuad()) );
#	endif
	return ret;
}

inline const hkSimdReal HK_CALL operator/ (hkSimdReal v0, hkSimdReal v1)
{
	hkQuadReal ret;
	asm(
		"vdiv Q, %1x, %2x \n"
		"vwaitq \n"
		"vaddq.x %0, vf0, Q"
		: "=j"(ret) :
			"j"(v0.getQuad()), "j"(v1.getQuad())  );
	return ret;
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

		void setAnd( hkVector4Comparison a, hkVector4Comparison b ) { m_mask = a.m_mask & b.m_mask; }

		hkBool32 allAreSet( Mask m ) const { return (m_mask & m) == m; }
		hkBool32 anyIsSet( Mask m ) const { return m_mask & m; }

		hkBool32 allAreSet() const { return m_mask == MASK_XYZW; }
		hkBool32 anyIsSet() const { return m_mask; }

		int getMask() const { return m_mask; }
		int getMask(Mask m) const { return m_mask & m; }

	private:

		int m_mask;
		friend class hkVector4;
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
