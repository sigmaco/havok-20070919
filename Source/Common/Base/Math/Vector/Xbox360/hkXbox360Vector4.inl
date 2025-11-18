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
	m_quad = __vspltw( a.getQuad(), 0 );
}

inline void hkVector4::setAll(hkReal a)
{
	m_quad.v[0] = a;
	m_quad = __vspltw( m_quad , 0 );
}

inline void hkVector4::setAll3(hkReal a)
{
	m_quad.v[0] = a;
	m_quad = __vspltw( m_quad , 0 );
}

inline void hkVector4::setZero4()
{
	m_quad = __vxor( m_quad, m_quad );
}

void hkVector4::setInt24W( int value )
{
	hkUint32 *wComponent = reinterpret_cast<hkUint32*>( &m_quad.v[3] );
	*wComponent = hkUint32(value) | 0x3f000000;
}

// Gets the .w component as an integer with 24 bit resolution (for real experts only).
int hkVector4::getInt24W( ) const 
{
	return (reinterpret_cast<const hkUint32*>(this))[3] & ~0x3f000000;
}

inline void hkVector4::storeUncached( void* dest) const
{
	*static_cast<hkVector4*>(dest) = *this;
}

inline void hkVector4::zeroElement( int i )
{
	__vector4 zero = __vspltisw(0);
	     if ( i == 0)	m_quad = __vrlimi( m_quad, zero, 8, 0 );
		 else if ( i == 1)	m_quad = __vrlimi( m_quad, zero, 4, 0 );
		 else if ( i == 2)	m_quad = __vrlimi( m_quad, zero, 2, 0 );
		 else             	m_quad = __vrlimi( m_quad, zero, 1, 0 );

	HK_ASSERT(0x3bc36625, i>=0 && i<4);
//	m_quad.v[i] = 0.0f;
}



/* vector methods */

inline void hkVector4::add4(const hkVector4& a)
{
	m_quad = __vaddfp( m_quad, a.m_quad );
}

inline void hkVector4::add3clobberW(const hkVector4& a)
{
	m_quad =  __vaddfp( m_quad, a.m_quad );
}

inline void hkVector4::setAdd4(const hkVector4& x, const hkVector4& y)
{
	m_quad = __vaddfp( x.m_quad, y.m_quad );
}

inline void hkVector4::sub4(const hkVector4& a)
{
	m_quad = __vsubfp( m_quad, a.m_quad );
}

inline void hkVector4::sub3clobberW(const hkVector4& a)
{
	m_quad = __vsubfp( m_quad, a.m_quad );
}

inline void hkVector4::setSub4(const hkVector4& x, const hkVector4& y)
{
	m_quad = __vsubfp( x.m_quad, y.m_quad );
}

inline void hkVector4::mul4(const hkVector4& v)
{
	m_quad = __vmulfp( m_quad, v.m_quad );
}

inline void hkVector4::setNeg3(const hkVector4& v)
{
	static HK_ALIGN16( const hkUint32 negateMask[4] ) = { 0x80000000, 0x80000000, 0x80000000, 0x00000000 };
	m_quad = __vxor( v.m_quad, *(hkQuadReal*)&negateMask );
}

inline void hkVector4::setMul4(const hkVector4& x, const hkVector4& y)
{
	m_quad = __vmulfp( x.m_quad, y.m_quad );
}

inline void hkVector4::mul4(hkSimdRealParameter s)
{
	m_quad = __vmulfp( m_quad, s.getQuad() );
}

inline void hkVector4::setMul4(hkSimdRealParameter r, const hkVector4& x)
{
	m_quad = __vmulfp( x.m_quad, r.getQuad() );
}

inline void hkVector4::addMul4(hkSimdRealParameter r, const hkVector4& x)
{
	m_quad = __vmaddfp( x.m_quad, r.getQuad(), m_quad );
}

inline void hkVector4::addMul4(const hkVector4& x, const hkVector4& y)
{
	m_quad = __vmaddfp( x.m_quad, y.m_quad, m_quad );
}

inline void hkVector4::subMul4(hkSimdRealParameter r, const hkVector4& x)
{
	m_quad = __vnmsubfp( x.m_quad, r.getQuad(), m_quad );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& b, hkSimdRealParameter r)
{
	m_quad = __vmaddfp( b.m_quad, r.getQuad(), a.m_quad );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& x, const hkVector4& y)
{
	m_quad = __vmaddfp( x.m_quad, y.m_quad, a.m_quad );
}

inline void hkVector4::setCross(const hkVector4& x, const hkVector4& y)
{
	// bit correspondence for vpermwi128 is ( x: 7|6, y: 5|4, z: 3|2, w: 1|0 )

	const unsigned int permutationA = 0x63;									// ( 1, 2, 0, 3 )
	const unsigned int permutationB = 0x87;									// ( 2, 0, 1, 3 )

	hkQuadReal temp0 = __vpermwi( x.m_quad, permutationA );
	hkQuadReal temp1 = __vpermwi( y.m_quad, permutationB );
	hkQuadReal cross0 = __vmulfp( temp0, temp1 );

	temp0 = __vpermwi( x.m_quad, permutationB );
	temp1 = __vpermwi( y.m_quad, permutationA );
	hkQuadReal cross1 = __vmulfp( temp0, temp1 );

	m_quad = __vsubfp( cross0, cross1 );
}

inline void hkVector4::setInterpolate4( const hkVector4& a, const hkVector4& b, hkSimdRealParameter t)
{
	hkQuadReal x = __vspltw( t.getQuad(), 0 );
	hkQuadReal s = __vsubfp( hkQuadReal1111, x );

	hkQuadReal temp = __vmulfp( s, a.m_quad );
	m_quad = __vmaddfp( x, b.m_quad, temp );
}

inline void hkVector4::setNeg4(const hkVector4& x)
{
	static HK_ALIGN16( const hkUint32 negateMask[4] ) = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
	m_quad = __vxor( x.m_quad, *(const hkQuadReal*)&negateMask );
}

inline hkVector4Comparison hkVector4::compareLessThan4(hkVector4Parameter a) const
{	
	hkVector4Comparison ret;
	ret.m_mask = __vcmpgtfp( a.m_quad, m_quad );
	return ret;
}

inline hkVector4Comparison hkVector4::compareEqual4(hkVector4Parameter a) const
{	
	hkVector4Comparison ret;
	ret.m_mask = __vcmpeqfp( a.m_quad, m_quad );
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanEqual4(hkVector4Parameter a) const
{
	hkVector4Comparison ret;
	ret.m_mask = __vcmpgefp( a.m_quad, m_quad );
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanZero4() const
{
	hkVector4Comparison ret;
	ret.m_mask = __vcmpgtfp( __vspltisw(0),  m_quad );
	return ret;

}

inline hkBool32 hkVector4::allLessThan3(hkVector4Parameter a) const
{
	return compareLessThan4(a).allAreSet( hkVector4Comparison::MASK_XYZ );
}

inline hkBool32 hkVector4::allLessThan4(hkVector4Parameter a) const
{
	unsigned cr6;
	__vcmpgtfpR( a.m_quad, m_quad, &cr6);
	return hkBool32(cr6 & (1<<7));
}

inline void hkVector4::select32( hkVector4Parameter a, hkVector4Parameter b, const hkVector4Comparison& comp)
{
	m_quad = __vsel( a.m_quad, b.m_quad, comp.m_mask );
}

inline void hkVector4::setAbs4(const hkVector4& x)
{
	static HK_ALIGN16( const hkUint32 positiveMask[4] ) = { 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff };
	m_quad = __vand( x.m_quad, *(const hkQuadReal*)&positiveMask );
}

inline void hkVector4::setMin4(const hkVector4& a, const hkVector4& b)
{
	m_quad = __vminfp( a.m_quad, b.m_quad );
}

inline void hkVector4::setMax4(const hkVector4& a, const hkVector4& b)
{
	m_quad = __vmaxfp( a.m_quad, b.m_quad );
}


/* matrix3, rotation, quaternion, transform */

inline void hkVector4::_setMul3(const hkMatrix3& m, const hkVector4& v)
{
	const hkQuadReal v0 = __vspltw( v.m_quad, 0 );
	const hkQuadReal v1 = __vspltw( v.m_quad, 1 );
	const hkQuadReal v2 = __vspltw( v.m_quad, 2 );

	const hkQuadReal r0 = __vmulfp( m.getColumn(0).m_quad, v0 );
	const hkQuadReal r1 = __vmaddfp( m.getColumn(1).m_quad, v1, r0 );
	m_quad = __vmaddfp( m.getColumn(2).m_quad, v2, r1 );
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
	const __vector4& vv = v.getQuad();

	const hkQuadReal& col0 = r.getColumn(0).getQuad();
	const hkQuadReal& col1 = r.getColumn(1).getQuad();
	const hkQuadReal& col2 = r.getColumn(2).getQuad();

	__vector4 vx = __vmsum3fp( col0, vv );
	__vector4 vy = __vmsum3fp( col1, vv );
	__vector4 vz = __vmsum3fp( col2, vv );

	const __vector4 vxz = __vmrghw( vx, vz );
	const __vector4 vyw = __vmrghw( vy, hkQuadReal0000 );
	m_quad = __vmrghw( vxz, vyw );
}

inline void hkVector4::_setTransformedPos(const hkTransform& t, const hkVector4& v)
{
	const hkQuadReal v0 = __vspltw( v.m_quad, 0 );
	const hkQuadReal v1 = __vspltw( v.m_quad, 1 );
	const hkQuadReal v2 = __vspltw( v.m_quad, 2 );

	const hkRotation& r = t.getRotation();
	const hkQuadReal r0 = __vmulfp( r.getColumn(0).m_quad, v0 );
	const hkQuadReal r1 = __vmaddfp( r.getColumn(1).m_quad, v1, r0 );
	const hkQuadReal r2 = __vmaddfp( r.getColumn(2).m_quad, v2, r1 );

	m_quad = __vaddfp( r2, t.getTranslation().m_quad );
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


inline void hkVector4::setReciprocal4(const hkVector4& vec)
{
	m_quad = hkMath::quadReciprocal(vec.m_quad);
}

inline void hkVector4::setSqrtInverse4(const hkVector4& vec)
{
	m_quad = hkMath::quadReciprocalSquareRoot(vec.m_quad);
}

inline void hkVector4::_setTransformedInversePos(const hkQsTransform& a, const hkVector4& b)
{
	hkVector4 temp(b);
	temp.sub4(a.m_translation);
	setRotatedInverseDir(a.m_rotation, temp);

	hkVector4 invScale; invScale.setReciprocal4( a.m_scale );
	mul4(invScale);
}

inline hkSimdReal hkVector4::dot3(const hkVector4& x) const
{
	hkSimdReal res; res.getQuad() = __vmsum3fp( m_quad, x.m_quad );
	return res;
}

inline hkReal hkVector4::dot3fpu(const hkVector4& a) const
{
	const hkVector4& t = *this;
	return (t(0) * a(0)) + ( t(1) * a(1) ) + ( t(2) * a(2) );
}

inline hkSimdReal hkVector4::dot4(const hkVector4& x) const
{
	hkSimdReal res; res.getQuad() =  __vmsum4fp( m_quad, x.m_quad );
	return res;
}

inline hkSimdReal hkVector4::dot4xyz1(const hkVector4& x) const
{
	hkSimdReal res; res.getQuad() =  __vaddfp( __vspltw(m_quad, 3), __vmsum3fp( m_quad, x.m_quad ));
	return res;
}

inline hkSimdReal hkVector4::horizontalAdd3() const
{
	hkSimdReal res; res.getQuad() =  __vmsum3fp( m_quad, hkQuadReal1111 );
	return res;
}

inline hkSimdReal hkVector4::horizontalAdd4() const
{
	hkSimdReal res; res.getQuad() =  __vmsum4fp( m_quad, hkQuadReal1111 );
	return res;
}

inline hkSimdReal hkVector4::length3() const
{
	hkQuadReal temp = __vmsum3fp( m_quad, m_quad );
	hkSimdReal res; res.set(hkMath::sqrt( temp.v[0] ));
	return res;
}

inline hkSimdReal hkVector4::lengthSquared3() const
{
	hkSimdReal res; res.getQuad() =  __vmsum3fp( m_quad, m_quad );
	return res;
}

inline hkSimdReal hkVector4::lengthInverse3() const
{
	hkQuadReal temp = __vmsum3fp( m_quad, m_quad );
	hkSimdReal res; res.set( hkMath::sqrtInverse( temp.v[0] ) );
	return res;
}

inline hkSimdReal hkVector4::length4() const
{
	hkQuadReal temp = __vmsum4fp( m_quad, m_quad );
	hkSimdReal res; res.set( hkMath::sqrt( temp.v[0] ) );
	return res;
}

inline hkSimdReal hkVector4::lengthSquared4() const
{
	hkSimdReal res; res.getQuad() = __vmsum4fp( m_quad, m_quad );
	return res;
}

inline hkSimdReal hkVector4::lengthInverse4() const
{
	hkQuadReal temp = __vmsum4fp( m_quad, m_quad );
	hkSimdReal res;
	res.set( hkMath::sqrtInverse( temp.v[0] ) );
	return res;
}

inline void hkVector4::normalize3()
{
	hkQuadReal temp = __vmsum3fp( m_quad, m_quad );
	hkQuadReal scale; scale.v[0] = hkMath::sqrtInverse( temp.v[0] );
	scale = __vspltw( scale, 0 );
	m_quad = __vmulfp( m_quad, scale );
}

inline hkSimdReal hkVector4::normalizeWithLength3()
{
	hkQuadReal len2 = __vmsum3fp( m_quad, m_quad );
	hkQuadReal scale; scale.v[0] = hkMath::sqrtInverse( len2.v[0] );
	scale = __vspltw( scale, 0 );
	m_quad = __vmulfp( m_quad, scale );

	hkSimdReal res; res.getQuad() =  __vmulfp( scale, len2 );
	return res;
}

inline void hkVector4::normalize4()
{
	hkQuadReal temp = __vmsum4fp( m_quad, m_quad );
	hkQuadReal scale; scale.v[0] = hkMath::sqrtInverse( temp.v[0] );
	scale = __vspltw( scale, 0 );
	m_quad = __vmulfp( m_quad, scale );
}

inline hkSimdReal hkVector4::normalizeWithLength4()
{
	hkQuadReal len2 = __vmsum4fp( m_quad, m_quad );
	hkQuadReal scale; scale.v[0] = hkMath::sqrtInverse( len2.v[0] );
	scale = __vspltw( scale, 0 );
	m_quad = __vmulfp( m_quad, scale );

	hkSimdReal res; res.getQuad() = __vmulfp( scale, len2 );
	return res;
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

#define HK_VECTOR4_COMBINE_XYZ_W(xyz, w, out) out = __vrlimi( xyz, w, 1, 0 );

inline void hkVector4::setXYZW(const hkVector4& xyz, const hkVector4& w)
{
	HK_VECTOR4_COMBINE_XYZ_W(xyz.m_quad, w.m_quad, m_quad);
}

inline void hkVector4::setW(const hkVector4& w)
{
	HK_VECTOR4_COMBINE_XYZ_W(m_quad, w.m_quad, m_quad);
}

inline void hkVector4::setXYZ(const hkVector4& xyz)
{
	HK_VECTOR4_COMBINE_XYZ_W(xyz.m_quad, m_quad, m_quad);
}

inline void hkVector4::setXYZ0(const hkVector4& v)
{
	const __vector4 vZero = __vspltisw(0);
	HK_VECTOR4_COMBINE_XYZ_W(v.m_quad, vZero, m_quad);
}



inline hkSimdReal hkVector4::getSimdAt(int i) const
{
	HK_ASSERT(0x757b177f, i>=0 && i<4);HK_PHYSICS_LE;
	hkSimdReal res;
	switch(i)
	{
		case 0:
			 res.getQuad() =  __vspltw( m_quad, 0 );
			 return res;
		case 1:
			res.getQuad() =  __vspltw( m_quad, 1 );
			return res;
		case 2:
			res.getQuad() =  __vspltw( m_quad, 2 );
			return res;
		case 3:
		default:
			res.getQuad() =  __vspltw( m_quad, 3 );
			return res;
	}
}


inline void hkVector4::setBroadcast(const hkVector4& v, int i)
{
	HK_ASSERT(0x22d97e3c, i>=0 && i<4);
	if( i == 0 )
	{
		m_quad = __vspltw( v.m_quad, 0 );
	}
	else if( i == 1 )
	{
		m_quad = __vspltw( v.m_quad, 1 );
	}
	else if( i == 2 )
	{
		m_quad = __vspltw( v.m_quad, 2 );
	}
	else //if( i == 3 )
	{
		m_quad = __vspltw( v.m_quad, 3 );
	}
}

inline void hkVector4::broadcast(int i)
{
	this->setBroadcast( *this, i );
}


inline void hkVector4::setBroadcast3clobberW(const hkVector4& v, int i)
{
	setBroadcast( v, i );
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
