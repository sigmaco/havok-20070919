/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#define HK_VECTOR4_setRotatedInverseDir
#define HK_VECTOR4_setRotatedDir

/* quad, here for inlining */

inline hkQuadReal& hkVector4::getQuad()
{
	return m_quad;
}

inline const hkQuadReal& hkVector4::getQuad() const
{
	return m_quad;
}


#ifndef HK_DISABLE_VECTOR4_CONSTRUCTORS

/* construct, assign, zero */
inline hkVector4::hkVector4(hkReal a, hkReal b, hkReal c, hkReal d)
{
	hkQuadRealUnion u;
	u.r[0] = a;
	u.r[1] = b;
	u.r[2] = c;
	u.r[3] = d;
	m_quad = u.q;
}


inline hkVector4::hkVector4(const hkQuadReal& q)
	: m_quad(q)
{
}

inline hkVector4::hkVector4( const hkVector4& v)
{
	m_quad = v.m_quad;
}
#endif

inline void hkVector4::operator= (const hkVector4& v)
{
	m_quad = v.m_quad;
}


inline void hkVector4::set(hkReal a, hkReal b, hkReal c, hkReal d)
{
	hkQuadRealUnion u;
	u.r[0] = a;
	u.r[1] = b;
	u.r[2] = c;
	u.r[3] = d;
	m_quad = u.q;
}

inline void hkVector4::setAll(hkReal a)
{
	asm("qmtc2 %1, %0  \n"			\
		"vaddax ACC, vf0, %0 \n"	\
		"vmsubw %0, vf0, vf0" : "=j"(m_quad) : "r" (a) );
}

inline void hkVector4::setAll(hkSimdRealParameter a)
{
	asm("vaddax ACC, vf0, %1 \n"	\
		"vmsubw %0, vf0, vf0" : "=j"(m_quad): "j"(a.getQuad()) );
}

inline void hkVector4::setAll3(hkReal a)
{
	asm("qmtc2 %1, %0  \n"			\
		"vaddx %0, vf0, %0" : "=j"(m_quad) : "r" (a) );
}

inline void hkVector4::setZero4()
{
	asm("vsub.xyzw %0, vf0, vf0" : "=j"(m_quad) );
}

void hkVector4::setInt24W( int value )
{
	(reinterpret_cast<hkUint32*>(this))[3] = value;
}

// Gets the .w component as an integer with 24 bit resolution (for real experts only).
int hkVector4::getInt24W( ) const
{
	return (reinterpret_cast<const hkUint32*>(this))[3];
}

// PS2 does not snoop the bus, therefor bypassing the cache may corrupt the data
inline void hkVector4::storeUncached( void* dest) const
{
	*static_cast<hkVector4*>(dest) = *this;
}

inline void hkVector4::zeroElement( int i )
{
	HK_ASSERT(0x5d269078, i>=0 && i<4);
	if ( i == 0 )
	{
		asm ("vmulx.x %0, vf0, vf0" : "+j"(m_quad) );
	}
	else if ( i == 1 )
	{
		asm("vmulx.y %0, vf0, vf0" : "+j"(m_quad) );
	}
	else if ( i == 2 )
	{
		asm("vmulx.z %0, vf0, vf0" : "+j"(m_quad) );
	}
	else //if ( i == 3 )
	{
		asm("vmulx.w %0, vf0, vf0" : "+j"(m_quad) );
	}
}


/* vector methods */

inline void hkVector4::add4(const hkVector4& v)
{
	asm("vadd.xyzw %0, %0, %1" : "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::add3clobberW(const hkVector4& v)
{
	asm("vadd.xyz %0, %0, %1" : "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::setAdd4(const hkVector4& v0, const hkVector4& v1)
{
	asm("vadd.xyzw %0, %1, %2" : "=j"(m_quad) : "j"(v0.m_quad), "j"(v1.m_quad) );
}

inline void hkVector4::sub4(const hkVector4& v)
{
	asm("vsub.xyzw %0, %0, %1" : "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::sub3clobberW(const hkVector4& v)
{
	asm("vsub.xyz %0, %0, %1" : "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::setSub4(const hkVector4& v0, const hkVector4& v1)
{
	asm("vsub.xyzw %0, %1, %2" : "=j"(m_quad) : "j"(v0.m_quad), "j"(v1.m_quad) );
}

inline void hkVector4::mul4(const hkVector4& v)
{
	asm("vmul.xyzw %0, %0, %1" : "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::setNeg3(const hkVector4& v)
{
	asm("vsub.xyz %0, vf0, %1  # 0 - result \n": "+j"(m_quad) : "j"(v.m_quad) );
	asm("vmove.w  %0, %1       # 0 - result \n": "+j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::setMul4(const hkVector4& v0, const hkVector4& v1)
{
	asm("vmul.xyzw %0, %1, %2" : "=j"(m_quad) : "j"(v0.m_quad), "j"(v1.m_quad)  );
}

inline void hkVector4::mul4(hkSimdRealParameter s)
{
	asm("vmulx.xyzw %0, %0, %1" : "+j"(m_quad) : "j"(s.getQuad()) );
}

inline void hkVector4::setMul4(hkSimdRealParameter s, const hkVector4& v)
{
	asm("vmulx.xyzw %0, %2, %1" : "=j"(m_quad) : "j"(s.getQuad()), "j"(v.m_quad) );
}

inline void hkVector4::addMul4(hkSimdRealParameter s, const hkVector4& v)
{
	asm(
"		vmulaw.xyzw ACC, %0, vf0	\n"
"		vmaddx.xyzw %0, %2, %1	"
	: "+j"(m_quad) : "j"(s.getQuad()), "j"(v.m_quad) );
}
inline void hkVector4::addMul4(const hkVector4& a, const hkVector4& b)
{
	asm(
"		vmulaw.xyzw ACC, %0, vf0	\n"
"		vmadd.xyzw %0, %2, %1	"
	: "+j"(m_quad) : "j"(a.m_quad), "j"(b.m_quad) );
}

inline void hkVector4::subMul4(hkSimdRealParameter s, const hkVector4& v)
{
	asm(
"		vmulaw.xyzw ACC, %0, vf0	\n"
"		vmsubx.xyzw %0, %2, %1	"
	: "+j"(m_quad) : "j"(s.getQuad()), "j"(v.m_quad) );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& b, hkSimdRealParameter r)
{
	asm(
"		vmulaw.xyzw ACC, %1, vf0	\n"
"		vmaddx.xyzw %0, %3, %2	"
	: "=j"(m_quad) : "j"( a.getQuad()), "j"(r.getQuad()), "j"(b.m_quad) );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& x, const hkVector4& y)
{
	asm(
"		vmulaw.xyzw ACC, %1, vf0	\n"
"		vmadd.xyzw %0, %2, %3	"
	: "=j"(m_quad) : "j"(a.m_quad), "j"(x.m_quad), "j"(y.m_quad) );
}

inline void hkVector4::setCross(const hkVector4& v1, const hkVector4& v2)
{
	asm( 
	"	vopmula.xyz	ACC, %1, %2		# %0 = cross(%1, %2)	\n"
	"	vopmsub.xyz %0,  %2, %1	"
	: "=j"(m_quad) : "j"(v1.m_quad), "j"(v2.m_quad) );
}

inline void hkVector4::setInterpolate4(const hkVector4& v0, const hkVector4& v1, hkSimdRealParameter t)
{
	// this = (1.0f-t)*v0 + t*v1 == v0 - t*v0 + t*v1

	asm(
"		vmulaw.xyzw 	ACC, %2, vf0	# v0		 	\n"
"		vmsubax.xyzw 	ACC, %2, %1		# - t*v0		\n"
"		vmaddx.xyzw 	%0, %3, %1		# + t*v1		"
	: "=j"(m_quad) : "j"(t.getQuad()), "j"(v0.m_quad), "j"(v1.m_quad) );
}

inline hkVector4Comparison hkVector4::compareLessThan4(const hkVector4& a) const
{
	hkVector4Comparison ret;
	asm (
	"	vsub.xyzw   vf0, %1, %2	# %1 = this - a		\n"	
	"	vnop					\n"
	"	vnop					\n"
	"	vnop					\n"
	"	vnop					\n"
	"	cfc2 %0, $vi17		\n"	
	"	andi %0, %0, 0xf0	\n"	
	"	sra %0, %0, 4		"
: "=r"(ret.m_mask) : "j"( m_quad ), "j"( a.m_quad ) );
	return ret;
}

inline hkVector4Comparison hkVector4::compareEqual4(const hkVector4& a) const
{
	hkVector4Comparison ret;
	asm (
		"	vsub.xyzw   vf0, %1, %2	# %1 = this - a		\n"	
		"	vnop					\n"
		"	vnop					\n"
		"	vnop					\n"
		"	vnop					\n"
		"	cfc2 %0, $vi17		\n"	
		"	andi %0, %0, 0xf	\n"	
		: "=r"(ret.m_mask) : "j"( m_quad ), "j"( a.m_quad ) );
	return ret;
}
inline hkVector4Comparison hkVector4::compareLessThanEqual4(const hkVector4& a) const
{
	hkVector4Comparison ret;
	register int temp;

	asm (
	"	vsub.xyzw   vf0, %2, %3	# %2 = this - a		\n"	
	"	vnop					\n"
	"	vnop					\n"
	"	vnop					\n"
	"	vnop					\n"
	"	cfc2 %1, $vi17		\n"
	"	sra  %0, %1, 4		\n"
	"	or   %0, %0, %1		\n"
	"	andi %0, %0, 0x0f	"
: "=r"(ret.m_mask), "=r"(temp) : "j"( m_quad ), "j"( a.m_quad ) );	

	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanZero4() const
{
	hkVector4 zero; zero.setZero4();
	return compareLessThan4( zero );
}

inline hkBool32 hkVector4::allLessThan3(hkVector4Parameter a) const
{
	return compareLessThan4(a).allAreSet(hkVector4Comparison::MASK_XYZ);
}

inline hkBool32 hkVector4::allLessThan4(hkVector4Parameter a) const
{
	return compareLessThan4(a).allAreSet();
}

inline void hkVector4::setNeg4(const hkVector4& v)
{

	// vf0 = (0,0,0,1) so zero the acc by vf0 * vf0(x)
	// then our result uses multiply subract operator
	// result = 0 - result*1   where 1 is from vf0.w
	asm(
	"	vmulax.xyzw ACC, vf0, vf0	# zero ACC				\n"
	"	vmsubw.xyzw %0,	 %1, vf0    # 0 - result = -result	"
		: "=j"(m_quad) : "j"(v.m_quad) );

}


inline void hkVector4::setAbs4(const hkVector4& v)
{
	asm( "vabs.xyzw %0, %1" : "=j"(m_quad) : "j"(v.m_quad) );
}

inline void hkVector4::setMin4(const hkVector4& v0, const hkVector4& v1)
{
	asm( "vmini.xyzw %0, %1, %2" : "=j"(m_quad) : "j"(v0.m_quad), "j"(v1.m_quad) );
}

inline void hkVector4::setMax4(const hkVector4& v0, const hkVector4& v1)
{
	asm( "vmax.xyzw %0, %1, %2" : "=j"(m_quad) : "j"(v0.m_quad), "j"(v1.m_quad) );
}



/* length and distance */

inline hkSimdReal hkVector4::dot3(const hkVector4& a) const
{
	hkQuadReal result;
	register hkQuadReal t0;
	asm(
	"	vmul.xyz 	%0, %2, %3														\n"
	"	vaddw.x 	%1, vf0, vf0	# tricky: make %1 = ( 1,0,0,0 )					\n"
	"	vadday.x 	ACC, %0, %0 	# now y*y + x*x is in ACC.x						\n"
	"	vmaddz.x 	%0, %1, %0 		# result.x = ACC.x + %3.x * %0.z = yy+xx+1*zz 	"
	: "=&j"(result), "=&j"(t0) : "j"( m_quad ), "j"( a.m_quad ) );

	return result;
}

inline hkReal hkVector4::dot3fpu(const hkVector4& v) const
{
	register float d;
	register float t0;
	register float t1;
	register float t2;
	register float t3;
	__asm__ __volatile__ (
	".set noreorder\n"
	"	lwc1	%0, 0x0(%5)	# t0 = x\n"
	"	lwc1	%1, 0x0(%6)	# t1 = v.x\n"
	"	lwc1	%2, 0x4(%5)	# t2 = y\n"
	"	mula.s	%0, %1		# A = t0 * t1\n"
	"	lwc1	%3, 0x4(%6)	# t3 = v.y\n"
	"	lwc1	%0, 0x8(%5)	# t0 = z\n"
	"	madda.s	%2, %3		# A += t2 * t3\n"
	"	lwc1	%1, 0x8(%6)	# t1 = v.z\n"
	"	madd.s	%4, %0, %1	# d = A + t0 * t1\n"
	".set reorder\n"
	: "=&f"(t0), "=&f"(t1), "=&f"(t2), "=&f"(t3), "=f"(d) : "r"(this), "r"(&v) );
	return d;
}

inline hkSimdReal hkVector4::dot4(const hkVector4& a) const
{
	hkQuadReal result;
	register hkQuadReal temp;
	asm( 
	"	vmul.xyzw	%0,   %2,   %3										\n"
	"	vaddw.x 	%1x,  vf0x, vf0w	# %1 = ( 1,0,0,0 )				\n"
	"	vadday.x	ACCx, %0x,  %0y		# ACC.x = x*x + y*y				\n"
	"	vmaddaz.x	ACCx, %1x,  %0z		# ACC.x = ACC.x + 1*z*z			\n"
	"	vmaddw.x	%0x,  %1x,  %0w		# result.x = ACC.x + 1*w*w		"
	: "=&j"(result), "=&j"(temp): "j"( m_quad ), "j"( a.m_quad ) );

	return result;
}

inline hkSimdReal hkVector4::dot4xyz1(const hkVector4& a) const
{
	hkQuadReal result;
	register hkQuadReal temp;
	asm( 
	"	vmul.xyzw	%0,   %2,   %3										\n"
	"	vaddw.x 	%1x,  vf0x, vf0w	# %1 = ( 1,0,0,0 )				\n"
	"	vadday.x	ACCx, %0x,  %0y		# ACC.x = x*x + y*y				\n"
	"	vmaddaz.x	ACCx, %1x,  %0z		# ACC.x = ACC.x + 1*z*z			\n"
	"	vmaddw.x	%0x,  %1x,  %2w		# result.x = ACC.x + 1*w		"
	: "=&j"(result), "=&j"(temp): "j"( m_quad ), "j"( a.m_quad ) );
	return result;
}

inline hkSimdReal hkVector4::horizontalAdd3() const
{

	hkQuadReal result;
	asm( 
	"	vaddy.x  	%0, %1, %1 	\n"
	"	vaddz.x  	%0, %0, %1 	"
	: "=&j"(result) : "j"( m_quad ) );

	return result;
}

inline hkSimdReal hkVector4::horizontalAdd4() const
{
	hkQuadReal result;
	register hkQuadReal temp; 
	asm( 
	"	vaddz.w		%1, %2, %2 	\n"
	"	vaddy.x		%0, %2, %2 	\n"
	"	vaddw.x		%0, %0, %1	"
	: "=&j"(result), "=&j"(temp) : "j"( m_quad ) );

	return result;
}

#define ME_NO_SQRT 0
/*
	Excerpt from /usr/local/sce/1st_read/notice.txt
   The above problem can be avoided by not locating the divide
    instructions in the following points:

       1. Two steps of the branch destination instructions
       2. Three steps following the branch instruction (including
	  the branch delay slot)
       3. One step instruction immediately after the SYNC.P
       4. The first two steps of the VU0 micro code
*/

inline hkSimdReal hkVector4::length3() const
{
#if ME_NO_SQRT
	hkSimdReal l3 = this->dot3(*this);
	return hkMath::sqrt( l3 );
#else
	register hkQuadReal dots;
	asm("vmul.xyz %0, %1, %1" : "=j"(dots) : "j"(m_quad) ); // x2,y2,z2,?
	register hkQuadReal temp0;
	asm("vaddw.x %0, vf0, vf0" : "=j"(temp0) ); // 1,?,?,?
	asm("vadday.x ACC, %0, %0\n"
		"vmaddz.x %0, %1, %0" : "+j"(dots) : "j"(temp0) ); // x2+y2+z2,?,?,?
	hkQuadReal result;
	asm("vsqrt Q, %1x\n"
		"vwaitq\n"
		"vaddq.x %0, vf0, Q\n"
		"vnop\n"
		"vnop\n" : "=j"(result) : "j"(dots) ); // len3,?,?,?
	return result;
#endif
}


inline hkSimdReal hkVector4::lengthSquared3() const
{
	return this->dot3(*this);
}


inline hkSimdReal hkVector4::lengthInverse3() const
{
#if ME_NO_SQRT
	hkSimdReal l3 = this->dot3(*this);
	return hkMath::sqrtInverse(l3);
#else
	hkQuadReal result;
	register hkQuadReal t0;

	// rsqrt( dot3)
	asm(
"		vmul.xyz 	%0, %2, %2														\n"
"		vaddw.x 	%1, vf0, vf0	# tricky: make %3 = ( 1,0,0,0 )					\n"
"		vadday.x 	ACC, %0, %0 	# now y*y + x*x is in ACC.x						\n"
"		vmaddz.x 	%0, %1, %0 		# result.x = ACC.x + %3.x * %0.z = yy+xx+1*zz 	\n"
"		vrsqrt		Q, vf00w, %0x													\n"
"		vwaitq																		\n"
"		vaddq.x		%0, vf0, Q														\n"
"		vnop																		\n"
"		vnop																		"
	: "+j"(result), "+j"(t0) : "j"( m_quad ) );

	return result;
#endif
}


inline hkSimdReal hkVector4::length4() const
{
#if ME_NO_SQRT
	hkSimdReal l2 = this->dot4(*this);
	return hkMath::sqrt( l2 );
#else
	hkQuadReal result;
	register hkQuadReal temp;

	// sqrt( dot4 )
	asm(
"		vmul.xyzw	%0,   %2,   %2										\n"
"		vaddw.x 	%1x,  vf0x, vf0w	# %1 = ( 1,0,0,0 )				\n"
"		vadday.x	ACCx, %0x,  %0y		# ACC.x = x*x + y*y				\n"
"		vmaddaz.x	ACCx, %1x,  %0z		# ACC.x = ACC.x + 1*z*z			\n"
"		vmaddw.x	%0x,  %1x,  %0w		# result.x = ACC.x + 1*w*w		\n"
"		vsqrt		Q, %0x												\n"
"		vwaitq															\n"
"		vaddq.x		%0, vf0, Q											\n"
"		vnop															\n"
"		vnop															"
	: "+j"(result), "+j"(temp): "j"( m_quad ) );

	return result;
#endif
}


inline hkSimdReal hkVector4::lengthSquared4() const
{
	return this->dot4(*this);
}


inline hkSimdReal hkVector4::lengthInverse4() const
{
#if ME_NO_SQRT
	hkSimdReal l2 = this->dot4(*this);
	return hkMath::sqrtInverse(l2);
#else
	hkQuadReal result;
	register hkQuadReal temp;

	// rsqrt( dot4 )
	asm(
"		vmul.xyzw	%0,   %2,   %2										\n"
"		vaddw.x 	%1x,  vf0x, vf0w	# %1 = ( 1,0,0,0 )				\n"
"		vadday.x	ACCx, %0x,  %0y		# ACC.x = x*x + y*y				\n"
"		vmaddaz.x	ACCx, %1x,  %0z		# ACC.x = ACC.x + 1*z*z			\n"
"		vmaddw.x	%0x,  %1x,  %0w		# result.x = ACC.x + 1*w*w		\n"
"		vrsqrt		Q, vf00w, %0x										\n"
"		vwaitq															\n"
"		vaddq.x		%0, vf0, Q											\n"
"		vnop															\n"
"		vnop															"
	: "+j"(result), "+j"(temp): "j"( m_quad ) );

	return result;
#endif
}


inline void hkVector4::normalize3()
{
#if ME_NO_SQRT
	this->mul4( this->lengthInverse3() );
#else
	register hkQuadReal t0, t1;

	// this*rsqrt( dot3)
	asm(
"		vmul.xyz 	%1, %0, %0														\n"
"		vaddw.x 	%2, vf0, vf0	# tricky: make %3 = ( 1,0,0,0 )					\n"
"		vadday.x 	ACC, %1, %1 	# now y*y + x*x is in ACC.x						\n"
"		vmaddz.x 	%1, %2, %1 		# result.x = ACC.x + %3.x * %0.z = yy+xx+1*zz 	\n"
"		vrsqrt		Q, vf00w, %1x													\n"
"		vwaitq																		\n"
"		vmulq.xyz	%0, %0, Q														\n"
"		vnop																		\n"
"		vnop																		"
	: "+j"( m_quad ), "=&j"(t0), "=&j"(t1) );

#endif
}


inline hkSimdReal hkVector4::normalizeWithLength3()
{
#if ME_NO_SQRT

	hkReal len = this->length3();
	hkReal invLen = 1.0f / len;
	this->mul4( invLen );
	return len;

#else
	hkQuadReal result;
	register hkQuadReal t0,t1;

	asm(
"		vmul.xyz 	%2, %0, %0														\n"
"		vaddw.x 	%3, vf0, vf0	# tricky: make %3 = ( 1,0,0,0 )					\n"
"		vadday.x 	ACC, %2, %2 	# now y*y + x*x is in ACC.x						\n"
"		vmaddz.x 	%2, %3, %2 		# result.x = ACC.x + %3.x * %0.z = yy+xx+1*zz 	\n"
"		vrsqrt		Q, vf0w, %2x													\n"
"		vwaitq																		\n"
"		vmulq.xyz	%0, %0, Q														\n"
"		vmulq.x		%1x, %2x, Q														\n"
"		vnop																		"
	: "+j"( m_quad ), "=&j"(result), "=&j"(t0) , "=&j"(t1) );

	return result;

#endif
}


inline void hkVector4::normalize4()
{
#if ME_NO_SQRT
	this->mul4( this->lengthInverse4() );
#else

	register hkQuadReal t0, t1;

	// this*rsqrt( dot4)
	asm(
"		vmul.xyzw	%1,   %0,   %0										\n"
"		vaddw.x 	%2x,  vf0x, vf0w	# %1 = ( 1,0,0,0 )				\n"
"		vadday.x	ACCx, %1x,  %1y		# ACC.x = x*x + y*y				\n"
"		vmaddaz.x	ACCx, %2x,  %1z		# ACC.x = ACC.x + 1*z*z			\n"
"		vmaddw.x	%1x,  %2x,  %1w		# result.x = ACC.x + 1*w*w		\n"
"		vrsqrt		Q, vf00w, %1x										\n"
"		vwaitq															\n"
"		vmulq.xyzw	%0, %0, Q											\n"
"		vnop															\n"
"		vnop															"
	: "+j"( m_quad ), "=&j"(t0), "=&j"(t1) );

#endif
}


inline hkSimdReal hkVector4::normalizeWithLength4()
{
#if ME_NO_SQRT
	hkReal len = this->length4();
	this->mul4( hkSimdReal((1.0f)/len) );
	return len;
#else
	hkQuadReal result;
	register hkQuadReal t0,t1;

	asm(
"		vmul.xyzw 	%2, %0, %0														\n"
"		vaddw.x 	%3, vf0, vf0	#												\n"
"		vadday.x 	ACCx, %2x, %2y 	#												\n"
"		vmaddaz.x	ACCx, %3x, %2z  #												\n"
"		vmaddw.x 	%2x,  %3x, %2w	#											 	\n"
"		vrsqrt		Q, vf0w, %2x													\n"
"		vwaitq																		\n"
"		vmulq.xyzw	%0, %0, Q														\n"
"		vmulq.x		%1x, %2x, Q														\n"
"		vnop																		"
	: "+j"( m_quad ), "=&j"(result), "=&j"(t0) , "=&j"(t1) );

	return result;
#endif
}


inline void hkVector4::fastNormalize3()
{
	normalize3();
}
inline hkSimdReal hkVector4::fastNormalizeWithLength3()
{
	return normalizeWithLength3();
}


/* operator (),[] */

inline hkReal& hkVector4::operator() (int i)
{
	HK_ASSERT(0x5e279256, i>=0 && i<4); HK_PHYSICS_LE;
	return ((hkReal*)(&m_quad))[i];
}

inline const hkReal& hkVector4::operator() (int i) const
{
	HK_ASSERT(0x6bdd5c81, i>=0 && i<4); HK_PHYSICS_LE;
	return ((const hkReal*)(&m_quad))[i];
}

inline void hkVector4::select32( hkVector4Parameter a, hkVector4Parameter b, const hkVector4Comparison& comp)
{

	int m = comp.getMask();
	hkVector4& t = *this;
	t(0) = (m & hkVector4Comparison::MASK_X) ? b(0) : a(0);
	t(1) = (m & hkVector4Comparison::MASK_Y) ? b(1) : a(1);
	t(2) = (m & hkVector4Comparison::MASK_Z) ? b(2) : a(2);
	t(3) = (m & hkVector4Comparison::MASK_W) ? b(3) : a(3);
}

inline void hkVector4::setXYZW(const hkVector4& xyz, const hkVector4& w)
{
	asm("vmove.xyz %0,%1" : "=j"(m_quad) : "j"(xyz.m_quad));
	asm("vmove.w   %0,%1" : "+j"(m_quad) : "j"(w.m_quad));
}

inline void hkVector4::setW(const hkVector4& w)
{
	asm("vmove.w   %0,%1" : "+j"(m_quad) : "j"(w.m_quad));
}

inline void hkVector4::setXYZ(const hkVector4& xyz)
{
	asm("vmove.xyz %0,%1" : "+j"(m_quad) : "j"(xyz.m_quad));
}

inline void hkVector4::setXYZ0(const hkVector4& xyz)
{
	asm("vsub.xyzw %0, vf0, vf0" : "=j"(m_quad) );
	asm("vmove.xyz %0,%1" : "+j"(m_quad) : "j"(xyz.m_quad));
}

inline void hkVector4::setReciprocal4(const hkVector4& vec)
{
	m_quad = hkMath::quadReciprocal(vec.m_quad);
}

inline void hkVector4::setSqrtInverse4(const hkVector4& v)
{
	hkQuadRealUnion u; u.q = v;
	u.r[0] = hkMath::sqrtInverse(u.r[0]);
	u.r[1] = hkMath::sqrtInverse(u.r[1]);
	u.r[2] = hkMath::sqrtInverse(u.r[2]);
	u.r[3] = hkMath::sqrtInverse(u.r[3]);
	m_quad = u.q;
}

inline hkSimdReal hkVector4::getSimdAt(int i) const
{
	HK_ASSERT(0x2aac5117, i>=0 && i<4);HK_PHYSICS_LE;

	hkQuadReal result;

	if ( i == 0 )
	{
		return m_quad;
	}
	else if ( i == 1 )
	{
		asm("vaddy.x %0, vf0, %1 \n"	: "=j"(result): "j"(m_quad) );
	}
	else if ( i == 2 )
	{
		asm("vaddz.x %0, vf0, %1 \n"	: "=j"(result): "j"(m_quad) );
	}
	else //if ( i == 3 )
	{
		asm("vaddw.x %0, vf0, %1 \n"	: "=j"(result): "j"(m_quad) );
	}
	
	return result;
}

inline void hkVector4::broadcast(int i)
{
	HK_ASSERT2(0x326b6c1f, i>=0 && i<4, "index error in broadcast");

	if ( i == 0 )
	{
		asm("vaddax ACC, vf0, %0 \n"	\
			"vmsubw %0, vf0, vf0" : "+j"(m_quad) );
	}
	else if ( i == 1 )
	{
		asm("vadday ACC, vf0, %0 \n"	\
			"vmsubw %0, vf0, vf0" : "+j"(m_quad) );
	}
	else if ( i == 2 )
	{
		asm("vaddaz ACC, vf0, %0 \n"	\
			"vmsubw %0, vf0, vf0" : "+j"(m_quad) );
	}
	else //if ( i == 3 )
	{
		asm("vaddaw ACC, vf0, %0 \n"	\
			"vmsubw %0, vf0, vf0" : "+j"(m_quad) );
	}

}

inline void hkVector4::setBroadcast(const hkVector4& v, int i)
{
	HK_ASSERT2(0x5129cb63, i>=0 && i<4, "index error in broadcast");

	if ( i == 0 )
	{
		asm("vaddax ACC, vf0, %1 \n"	\
			"vmsubw %0, vf0, vf0" : "=j"(m_quad): "j"(v.m_quad) );
	}
	else if ( i == 1 )
	{
		asm("vadday ACC, vf0, %1 \n"	\
			"vmsubw %0, vf0, vf0" : "=j"(m_quad): "j"(v.m_quad) );
	}
	else if ( i == 2 )
	{
		asm("vaddaz ACC, vf0, %1 \n"	\
			"vmsubw %0, vf0, vf0" : "=j"(m_quad): "j"(v.m_quad) );
	}
	else //if ( i == 3 )
	{
		asm("vaddaw ACC, vf0, %1 \n"	\
			"vmsubw %0, vf0, vf0" : "=j"(m_quad): "j"(v.m_quad) );
	}

}

inline void hkVector4::setBroadcast3clobberW(const hkVector4& v, int i)
{
	HK_ASSERT2(0x5129cb63, i>=0 && i<4, "index error in broadcast");

	if ( i == 0 )
	{
		asm("vaddx %0, vf0, %1 \n"	: "=j"(m_quad): "j"(v.m_quad) );
	}
	else if ( i == 1 )
	{
		asm("vaddy %0, vf0, %1 \n"	: "=j"(m_quad): "j"(v.m_quad) );
	}
	else if ( i == 2 )
	{
		asm("vaddz %0, vf0, %1 \n"	: "=j"(m_quad): "j"(v.m_quad) );
	}
	else //if ( i == 3 )
	{
		asm("vaddw %0, vf0, %1 \n"	: "=j"(m_quad): "j"(v.m_quad) );
	}

}

#undef ME_NO_SQRT

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
