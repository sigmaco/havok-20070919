/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


/* quad, here for inlining */


inline hkQuadReal& hkVector4::getQuad()
{
	return m_quad;
}

inline const hkQuadReal& hkVector4::getQuad() const
{
	return m_quad;
}


/* construct, assign, zero */
#ifndef HK_DISABLE_VECTOR4_CONSTRUCTORS

inline hkVector4::hkVector4(hkReal x, hkReal y, hkReal z, hkReal w)
{
	/*
	hkQuadReal ans;
	_vaddf(ans, vu0_field_X, vu0_vf0, x);
	_vaddf(ans, vu0_field_Y, vu0_vf0, y);
	_vaddf(ans, vu0_field_Z, vu0_vf0, z);
	_vmulf(ans, vu0_field_W, vu0_vf0, w);
	*/
	hkQuadRealUnion u;
	u.r[0] = x;
	u.r[1] = y;
	u.r[2] = z;
	u.r[3] = w; 
	m_quad = u.q;
}

inline hkVector4::hkVector4(const hkQuadReal& q)
{
	m_quad = q;
}

inline hkVector4::hkVector4(const hkVector4& v)
{
	m_quad = v.m_quad;
}
#endif

inline void hkVector4::operator= (const hkVector4& v)
{
	m_quad = v.m_quad;
}

inline void hkVector4::set(hkReal x, hkReal y, hkReal z, hkReal w)
{
	hkQuadRealUnion u;
	u.r[0] = x;
	u.r[1] = y;
	u.r[2] = z;
	u.r[3] = w;
	m_quad = u.q;
}

inline void hkVector4::setAll(hkSimdRealParameter a)
{
	_vaddbc(m_quad, vu0_field_XYZW, hkQuadReal0000, a.getQuad(), vu0_field_X );
}

inline void hkVector4::setAll(hkReal a)
{
	hkQuadRealUnion u;
	u.r[0] = a;
	u.r[1] = a;
	u.r[2] = a;
	u.r[3] = a;
	m_quad = u.q;
}

inline void hkVector4::setAll3(hkReal a)
{
	hkQuadRealUnion u;
	u.r[0] = a;
	u.r[1] = a;
	u.r[2] = a;
	u.r[3] = a;
	m_quad = u.q;
}

inline void hkVector4::setZero4()
{
	_vsub(m_quad, vu0_field_XYZW, vu0_vf0, vu0_vf0);
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

inline void hkVector4::storeUncached( void* dest) const
{
	*static_cast<hkVector4*>(dest) = *this;
}


inline void hkVector4::zeroElement( int i )
{
	HK_ASSERT(0x3bc36625, i>=0 && i<4);
	if ( i == 0 )
	{
		_vsub(m_quad, vu0_field_X, vu0_vf0, vu0_vf0);
	}
	else if ( i == 1 )
	{
		_vsub(m_quad, vu0_field_Y, vu0_vf0, vu0_vf0);
	}
	else if ( i == 2 )
	{
		_vsub(m_quad, vu0_field_Z, vu0_vf0, vu0_vf0);
	}
	else //if ( i == 3 )
	{
		_vsub(m_quad, vu0_field_W, vu0_vf0, vu0_vf0);
	}
}

/* vector methods */


inline void hkVector4::add4(const hkVector4& a)
{
	_vadd(m_quad, vu0_field_XYZW, m_quad, a.m_quad);
}

inline void hkVector4::add3clobberW(const hkVector4& a)
{
	_vadd(m_quad, vu0_field_XYZ, m_quad, a.m_quad);
}

inline void hkVector4::setAdd4(const hkVector4& x, const hkVector4& y)
{
	_vadd(m_quad, vu0_field_XYZW, x.m_quad, y.m_quad);
}

inline void hkVector4::sub4(const hkVector4& a)
{
	_vsub(m_quad, vu0_field_XYZW, m_quad, a.m_quad);
}

inline void hkVector4::sub3clobberW(const hkVector4& a)
{
	_vsub(m_quad, vu0_field_XYZ, m_quad, a.m_quad);
}

inline void hkVector4::setSub4(const hkVector4& x, const hkVector4& y)
{
	_vsub(m_quad, vu0_field_XYZW, x.m_quad, y.m_quad);
}

inline void hkVector4::mul4(const hkVector4& v)
{
	_vmul(m_quad, vu0_field_XYZW, m_quad, v.m_quad);
}

inline void hkVector4::setNeg3(const hkVector4& v)
{
	_vsub(m_quad, vu0_field_XYZ, vu0_vf0, v.m_quad);
	_vmove(m_quad, vu0_field_W, v.m_quad);
}


inline void hkVector4::setMul4(const hkVector4& x, const hkVector4& y)
{
	_vmul(m_quad, vu0_field_XYZW, x.m_quad, y.m_quad);
}

inline void hkVector4::mul4(hkSimdRealParameter s)
{
	_vmulbc(m_quad, vu0_field_XYZW, m_quad, s.getQuad(), vu0_field_X);
}
inline void hkVector4::setMul4(hkSimdRealParameter r, const hkVector4& x)
{
	_vmulbc(m_quad, vu0_field_XYZW, x.m_quad, r.getQuad(), vu0_field_X);
}

inline void hkVector4::addMul4(hkSimdRealParameter r, const hkVector4& x)
{
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, m_quad, vu0_vf0, vu0_field_W);
	_vmaddbc(m_quad, vu0_field_XYZW, acc, x.m_quad, r.getQuad(), vu0_field_X);
}
inline void hkVector4::addMul4(const hkVector4& a, const hkVector4& b)
{
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, m_quad, vu0_vf0, vu0_field_W);
	_vmadd(m_quad, vu0_field_XYZW, acc, a.m_quad, b.m_quad);
}

inline void hkVector4::subMul4(hkSimdRealParameter r, const hkVector4& x)
{
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, m_quad, vu0_vf0, vu0_field_W);
	_vmsubbc(m_quad, vu0_field_XYZW, acc, x.getQuad(), r.getQuad(), vu0_field_X);
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& b, hkSimdRealParameter r)
{
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, a.m_quad, vu0_vf0, vu0_field_W);
	_vmaddbc(m_quad, vu0_field_XYZW, acc, b.getQuad(), r.getQuad(), vu0_field_X);
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& x, const hkVector4& y)
{
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, a.m_quad, vu0_vf0, vu0_field_W);
	_vmadd(m_quad, vu0_field_XYZW, acc, x.getQuad(), y.getQuad());
}

inline void hkVector4::setCross(const hkVector4& x, const hkVector4& y)
{
	hkQuadReal acc;
	_vopmula(acc, x.m_quad, y.m_quad);
	_vopmsub(m_quad, acc, y.m_quad, x.m_quad);
}

inline void hkVector4::setInterpolate4( const hkVector4& a, const hkVector4& b, hkSimdRealParameter t)
{
	hkQuadReal s_w;
	_vsubbc(s_w, vu0_field_W, vu0_vf0, t.getQuad(), vu0_field_X); // note using w
	hkQuadReal acc;
	_vmulbc(acc, vu0_field_XYZW, b.m_quad, t.getQuad(), vu0_field_X);
	_vmaddbc(m_quad, vu0_field_XYZW, acc, a.m_quad, s_w, vu0_field_W);
}

inline void hkVector4::setNeg4(const hkVector4& x)
{
	_vmulf(m_quad, vu0_field_XYZW, x.m_quad, -1.0f);
}

inline hkVector4Comparison hkVector4::compareLessThan4(const hkVector4& a) const
{	
	hkVector4Comparison ret;
	__asm__(
		"vsub.xyzw vf0, %[vec0], %[vec1]\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"cfc2 %[mask], $vi17		\n"
		"andi %[mask], %[mask], 0xf0	\n"
		"sra %[mask], %[mask], 4	\n"
		: [mask]"=r"(ret.m_mask)
		: [vec0]"j"(m_quad), [vec1]"j"(a.m_quad) );
	return ret;
}

inline hkVector4Comparison hkVector4::compareEqual4(const hkVector4& a) const
{	
	hkVector4Comparison ret;
	__asm__(
		"vsub.xyzw vf0, %[vec0], %[vec1]\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"cfc2 %[mask], $vi17		\n"
		"andi %[mask], %[mask], 0xf	\n"
		: [mask]"=r"(ret.m_mask)
		: [vec0]"j"(m_quad), [vec1]"j"(a.m_quad) );
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanEqual4(const hkVector4 &a) const
{
	hkVector4Comparison ret;
	register int temp;
	__asm__(
		"vsub.xyzw vf0, %[vec0], %[vec1]\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"vnop				\n"
		"cfc2 %[temp], $vi17		\n"
		"sra %[mask], %[temp], 4	\n"
		"or %[mask], %[mask], %[temp]	\n"
		"andi %[mask], %[mask], 0x0f	\n"
			: [mask]"=&r"(ret.m_mask), [temp]"=&r"(temp)
			: [vec0]"j"(m_quad), [vec1]"j"(a.m_quad) );
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanZero4() const
{
	return compareLessThan4( hkVector4::getZero() );
}

inline hkBool32 hkVector4::allLessThan3(hkVector4Parameter a) const
{
	return compareLessThan4(a).allAreSet(hkVector4Comparison::MASK_XYZ);
}

inline hkBool32 hkVector4::allLessThan4(hkVector4Parameter a) const
{
	return compareLessThan4(a).allAreSet();
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

inline void hkVector4::setAbs4(const hkVector4& x)
{
	_vabs(m_quad, vu0_field_XYZW, x.m_quad);
}

inline void hkVector4::setMin4(const hkVector4& a, const hkVector4& b)
{
	_vmini(m_quad, vu0_field_XYZW, a.getQuad(), b.getQuad());
}

inline void hkVector4::setMax4(const hkVector4& a, const hkVector4& b)
{
	_vmax(m_quad, vu0_field_XYZW, a.getQuad(), b.getQuad());
}


/* matrix3, rotation, quaternion, transform */


inline void hkVector4::_setMul3(const hkMatrix3& m, const hkVector4& v)
{
	hkQuadReal acc;
	_vmulbc ( acc,    vu0_field_XYZW,      m.getColumn(0).m_quad, v.m_quad, vu0_field_X);
	_vmaddbc( acc,    vu0_field_XYZW, acc, m.getColumn(1).m_quad, v.m_quad, vu0_field_Y);
	_vmaddbc( m_quad, vu0_field_XYZW, acc, m.getColumn(2).m_quad, v.m_quad, vu0_field_Z);
}



inline void hkVector4::_setMul4(const hkMatrix3& r, const hkVector4& v)
{
	_setMul3(r,v);
}

inline void hkVector4::_setRotatedDir(const hkRotation& t, const hkVector4& v)
{
	_setMul3(t,v);
}
 

inline void hkVector4::_setRotatedInverseDir(const hkRotation& r, const hkVector4& v)
{
	hkQuadReal res;
	_vsub ( res, vu0_field_XYZW, vu0_vf0, vu0_vf0 );

	hkQuadReal dp0;
	_vmul ( dp0, vu0_field_XYZ,      r.getColumn(0).m_quad, v.m_quad);
	_vaddbc(dp0, vu0_field_X, dp0, dp0, vu0_field_Y);
	_vaddbc(res, vu0_field_X, dp0, dp0, vu0_field_Z);

	hkQuadReal dp1;
	_vmul ( dp1, vu0_field_XYZ,      r.getColumn(1).m_quad, v.m_quad);
	_vaddbc(dp1, vu0_field_Y, dp1, dp1, vu0_field_X);
	_vaddbc(res, vu0_field_Y, dp1, dp1, vu0_field_Z);

	hkQuadReal dp2;
	_vmul ( dp2, vu0_field_XYZ,      r.getColumn(2).m_quad, v.m_quad);
	_vaddbc(dp2, vu0_field_Z, dp2, dp2, vu0_field_X);
	_vaddbc(res, vu0_field_Z, dp2, dp2, vu0_field_Y);

	m_quad = res;
}


inline void hkVector4::_setTransformedPos(const hkTransform& t, const hkVector4& v)
{
	hkQuadReal acc;
	_vmulbc ( acc,    vu0_field_XYZW,      t.getRotation().getColumn(0).m_quad, v.m_quad, vu0_field_X);
	_vmaddbc( acc,    vu0_field_XYZW, acc, t.getRotation().getColumn(1).m_quad, v.m_quad, vu0_field_Y);
	_vmaddbc( acc,    vu0_field_XYZW, acc, t.getRotation().getColumn(2).m_quad, v.m_quad, vu0_field_Z);
	_vmaddbc( m_quad, vu0_field_XYZW, acc, t.getTranslation().m_quad, vu0_vf0, vu0_field_W);
}

inline void hkVector4::_setMul4xyz1(const hkTransform& t, const hkVector4& v)
{
	_setTransformedPos( t, v );
}


inline void hkVector4::_setTransformedInversePos(const hkTransform& t, const hkVector4& v)
{
	hkVector4 trans;
	trans.setSub4( v, t.getTranslation() );
	_setRotatedInverseDir( t.getRotation(), trans );
}

inline void hkVector4::_setTransformedPos(const hkQsTransform& a, const hkVector4& b)
{
	hkVector4 temp(b);
	temp.mul4(a.m_scale);
	setRotatedDir(a.m_rotation, temp);
	add4(a.m_translation);
}

inline void hkVector4::_setTransformedInversePos(const hkQsTransform& a, const hkVector4& b)
{
	hkVector4 temp(b);
	temp.sub4(a.m_translation);
	setRotatedInverseDir(a.m_rotation, temp);

	hkVector4 invScale; invScale.set(1.0f/a.m_scale(0), 1.0f/a.m_scale(1), 1.0f/a.m_scale(2));
	mul4(invScale);
}

inline hkSimdReal hkVector4::dot3(const hkVector4& x) const
{
/*
	hkQuadReal ret;
	_vmul  (ret, vu0_field_XYZ, m_quad, x.m_quad);
	_vaddbc(ret, vu0_field_X, ret, ret, vu0_field_Y);
	_vaddbc(ret, vu0_field_X, ret, ret, vu0_field_Z);	
*/	

	register hkQuadReal squared, t0, acc;
	hkQuadReal ret;
		
	_vmul	(squared, vu0_field_XYZ, m_quad, x.m_quad);
	_vaddbc	(t0, vu0_field_X, vu0_vf0, vu0_vf0, vu0_field_W );
	_vaddbc(acc, vu0_field_X, squared, squared, vu0_field_Y );
	_vmaddbc(ret, vu0_field_X, acc, t0, squared, vu0_field_Z );

	return ret;
}

inline hkReal hkVector4::dot3fpu(const hkVector4& a) const
{
	const hkVector4& t = *this;
	return (t(0) * a(0)) + ( t(1) * a(1) ) + ( t(2) * a(2) );
}

inline hkSimdReal hkVector4::dot4(const hkVector4& x) const
{
/*
	hkQuadReal t0, t1, t2, ret;
   	_vmul(t0, vu0_field_XYZW, m_quad, x.m_quad);
	_vaddbc(t1, vu0_field_X, t0, t0, vu0_field_Y);
	_vaddbc(t2, vu0_field_X, t1, t0, vu0_field_Z);
	_vaddbc(ret, vu0_field_X, t2, t0, vu0_field_W);
*/	
	
	hkQuadReal t0, ret;
   	_vmul(ret, vu0_field_XYZW, m_quad, x.m_quad);
	_vaddbc(t0, vu0_field_W, ret, ret, vu0_field_Z);
	_vaddbc(ret, vu0_field_X, ret, ret, vu0_field_Y);
	_vaddbc(ret, vu0_field_X, ret, t0, vu0_field_W);	
	
	return ret;
}


inline hkSimdReal hkVector4::dot4xyz1(const hkVector4& x) const
{
	hkQuadReal t0, ret;
   	_vmul(ret, vu0_field_XYZW, m_quad, x.m_quad);
	_vaddbc(t0, vu0_field_W, m_quad, ret, vu0_field_Z);
	_vaddbc(ret, vu0_field_X, ret, ret, vu0_field_Y);
	_vaddbc(ret, vu0_field_X, ret, t0, vu0_field_W);	
	
	return ret;
}

inline hkSimdReal hkVector4::horizontalAdd3() const
{
	hkQuadReal t0, ret;
	_vaddbc(t0,  vu0_field_X, m_quad, m_quad, vu0_field_Y);
	_vaddbc(ret, vu0_field_X, t0,     m_quad, vu0_field_Z);
	return ret;
}

inline hkSimdReal hkVector4::horizontalAdd4() const
{
	hkQuadReal t0, t1, ret;
	_vaddbc(t0,  vu0_field_X, m_quad, m_quad, vu0_field_Y);
	_vaddbc(t1,  vu0_field_X, m_quad, t0,     vu0_field_Z);
	_vaddbc(ret, vu0_field_X, m_quad, t1,     vu0_field_W);
	return ret;
}


inline hkSimdReal hkVector4::length3() const
{
	hkSimdReal l3 = this->dot3(*this);
	return hkMath::sqrt( l3 );
}

inline hkSimdReal hkVector4::lengthSquared3() const
{
	return this->dot3(*this);
}

inline hkSimdReal hkVector4::lengthInverse3() const
{
	hkSimdReal l3 = this->dot3(*this);
	return hkMath::sqrtInverse( l3 );
}

inline hkSimdReal hkVector4::length4() const
{
	hkSimdReal l2 = this->dot4(*this);
	return hkMath::sqrt( l2 );
}

inline hkSimdReal hkVector4::lengthSquared4() const
{
	return this->dot4(*this);
}

inline hkSimdReal hkVector4::lengthInverse4() const
{
	hkSimdReal l2 = this->dot4(*this);
	return hkMath::sqrtInverse( l2 );
}

inline void hkVector4::normalize3()
{
	hkSimdReal l2 = this->dot3(*this);
	hkSimdReal scale = hkMath::sqrtInverse( l2 );
	this->setMul4(scale, *this);
}
inline hkSimdReal hkVector4::normalizeWithLength3()
{
	hkSimdReal l2 = this->dot3(*this);
	hkSimdReal scale = hkMath::sqrtInverse( l2 );
	this->setMul4(scale, *this);
	hkQuadReal ret;
	_vmul(ret, vu0_field_X, l2.getQuad(), scale.getQuad());
	return ret;
}

inline void hkVector4::normalize4()
{
	hkSimdReal l2 = this->dot4(*this);
	hkSimdReal scale = hkMath::sqrtInverse( l2 );
	this->setMul4(scale, *this);
}
inline hkSimdReal hkVector4::normalizeWithLength4()
{
	hkSimdReal l2 = this->dot4(*this);
	hkSimdReal scale = hkMath::sqrtInverse( l2 );
	this->setMul4(scale, *this);
	hkQuadReal ret;
	_vmul(ret, vu0_field_X, l2.getQuad(), scale.getQuad());
	return ret;
}

inline void hkVector4::fastNormalize3()
{
	normalize3();
}
inline hkSimdReal hkVector4::fastNormalizeWithLength3()
{
	return normalizeWithLength3();
}



/* operator () */

inline hkReal& hkVector4::operator() (int i)
{
	HK_ASSERT(0x74f24d6e, i>=0 && i<4); HK_PHYSICS_LE;
	return reinterpret_cast<hkReal*>(&m_quad)[i];
}

inline const hkReal& hkVector4::operator() (int i) const
{
	HK_ASSERT(0x7897e9b7, i>=0 && i<4); HK_PHYSICS_LE;
	return reinterpret_cast<const hkReal*>(&m_quad)[i];
}

inline void hkVector4::setXYZW(const hkVector4& xyz, const hkVector4& w)
{
	_vmove(m_quad, vu0_field_XYZ, xyz.m_quad);
	_vmove(m_quad, vu0_field_W,   w.m_quad);
}

inline void hkVector4::setW(const hkVector4& w)
{
	_vmove(m_quad, vu0_field_W,   w.m_quad);
}

inline void hkVector4::setXYZ(const hkVector4& xyz)
{
	_vmove(m_quad, vu0_field_XYZ,   xyz.m_quad);
}

inline void hkVector4::setXYZ0(const hkVector4& xyz)
{
	_vmove(m_quad, vu0_field_XYZ, xyz.m_quad);
	_vmove(m_quad, vu0_field_W,   vu0_vf0);
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
	// this looks ugly but is needed when this function is out of line (debug mode)
	// when inlined in release it compiles to one statement
	HK_ASSERT(0x757b177f, i>=0 && i<4);HK_PHYSICS_LE;
	if( i == 0 )
	{
		hkQuadReal ret;
		_vaddbc(ret, vu0_field_X, vu0_vf0, m_quad, vu0_field_X );
		return ret;
	}
	else if( i == 1 )
	{
		hkQuadReal ret;
		_vaddbc(ret, vu0_field_X, vu0_vf0, m_quad, vu0_field_Y );
		return ret;
	}
	else if( i == 2 )
	{
		hkQuadReal ret;
		_vaddbc(ret, vu0_field_X, vu0_vf0, m_quad, vu0_field_Z );
		return ret;
	}
	else //if( i == 3 )
	{
		hkQuadReal ret;
		_vaddbc(ret, vu0_field_X, vu0_vf0, m_quad, vu0_field_W );
		return ret;
	}
}

inline void hkVector4::broadcast(int i)
{
	HK_ASSERT(0x70c2a74a, i>=0 && i<4);
	if( i == 0 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, m_quad, vu0_field_X );
	}
	else if( i == 1 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, m_quad, vu0_field_Y );
	}
	else if( i == 2 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, m_quad, vu0_field_Z );
	}
	else //if( i == 3 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, m_quad, vu0_field_W );
	}
}

inline void hkVector4::setBroadcast(const hkVector4& v, int i)
{
	HK_ASSERT(0x22d97e3c, i>=0 && i<4);
	if( i == 0 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, v.m_quad, vu0_field_X );
	}
	else if( i == 1 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, v.m_quad, vu0_field_Y );
	}
	else if( i == 2 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, v.m_quad, vu0_field_Z );
	}
	else //if( i == 3 )
	{
		_vaddbc(m_quad, vu0_field_XYZW, getZero().m_quad, v.m_quad, vu0_field_W );
	}
}

inline void hkVector4::setBroadcast3clobberW(const hkVector4& v, int i)
{
  HK_ASSERT(0x22d27e3c, i>=0 && i<4);
  if( i == 0 )
  {
     _vaddbc(m_quad, vu0_field_XYZW, vu0_vf0, v.m_quad, vu0_field_X );
  }
  else if( i == 1 )
  {
     _vaddbc(m_quad, vu0_field_XYZW, vu0_vf0, v.m_quad, vu0_field_Y );
  }
  else if( i == 2 )
  {
     _vaddbc(m_quad, vu0_field_XYZW, vu0_vf0, v.m_quad, vu0_field_Z );
  }
  else //if( i == 3 )
  {
     _vaddbc(m_quad, vu0_field_XYZW, vu0_vf0, v.m_quad, vu0_field_W );
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
