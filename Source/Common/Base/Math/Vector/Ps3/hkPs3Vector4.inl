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

#ifndef HK_PLATFORM_PS3SPU
inline hkVector4::hkVector4(const hkVector4& v)
{
	m_quad = v.m_quad;
}
#endif
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
	m_quad = vec_splat(a.getQuad(), 0);
}

inline void hkVector4::setAll(hkReal a)
{
	hkQuadRealUnion u; u.r[0] = a; // XXX si_from_float
	m_quad = vec_splat( u.q, 0 );
}

inline void hkVector4::setAll3(hkReal a)
{
	hkQuadRealUnion u; u.r[0] = a;
	m_quad = vec_splat( u.q, 0 );
}

inline void hkVector4::setZero4()
{
	m_quad = HK_QUADREAL_0000;
}

void hkVector4::setInt24W( int value )
{
#ifdef HK_PLATFORM_PS3
	// XXX optimise
	//const vector int mask = (vector int){ 0x3f00000,0x3f00000,0x3f00000,0x3f00000 };
	//const vector int w = vec_or( mask, si_rotqbyi(si_from_int(value),4) );
	//m_quad = vec_sel( m_quad, w, (vector signed int){0,0,0,-1} );

	// int load half upper // or
	// form select mask from bytes immed // select
	// generate control for word insertion 12(sp) // shuffle
	union
	{
		hkInt32 i[4];
		hkQuadReal q;
	} u;
	u.q = m_quad;
	u.i[3] = hkUint32(value) | 0x3f000000;
	m_quad = u.q;
#else
	m_quad = (hkQuadReal) spu_insert( hkUint32(value) | 0x3f000000, hkQuadUint(m_quad), 3);
#endif
}

int hkVector4::getInt24W() const 
{
#ifdef HK_PLATFORM_PS3
	union
	{
		hkInt32 i[4];
		hkQuadReal q;
	} u;
	u.q = m_quad;
	return u.i[3] & ~0x3f000000;
#else
	return si_to_int((qword)spu_and((hkQuadUint) spu_rlqwbyte(m_quad,12), (hkQuadUint)si_from_int(~0x3f000000)));
#endif
}

inline void hkVector4::storeUncached( void* dest) const
{
	vec_stl(m_quad, 0, (float*)dest);
}

inline void hkVector4::zeroElement( int i )
{
	HK_ASSERT(0x3bc36625, i>=0 && i<4);
	hkQuadRealUnion u;
	u.q = m_quad;
	u.r[i] = 0.0f;
	m_quad = u.q;
}


/* vector methods */

inline void hkVector4::add4(const hkVector4& a)
{
	m_quad = vec_add( m_quad, a.m_quad );
}

inline void hkVector4::add3clobberW(const hkVector4& va)
{
	m_quad =  vec_add( m_quad, va.m_quad );
}

inline void hkVector4::setAdd4(const hkVector4& x, const hkVector4& y)
{
	m_quad = vec_add( x.m_quad, y.m_quad );
}

inline void hkVector4::sub4(const hkVector4& a)
{
	m_quad = vec_sub( m_quad, a.m_quad );
}

inline void hkVector4::sub3clobberW(const hkVector4& va)
{
	m_quad = vec_sub( m_quad, va.m_quad );
}

inline void hkVector4::setSub4(const hkVector4& x, const hkVector4& y)
{
	m_quad = vec_sub( x.m_quad, y.m_quad );
}

inline void hkVector4::mul4(const hkVector4& v)
{
	m_quad = vec_mul( m_quad, v.m_quad );
}

inline void hkVector4::setNeg3(const hkVector4& v)
{
	const vector signed int negateMask = (vector signed int){0x80000000, 0x80000000, 0x80000000, 0x00000000};
	m_quad = vec_xor( v.m_quad, (vector float)negateMask );
}

inline void hkVector4::setMul4(hkVector4Parameter x, hkVector4Parameter y)
{
	m_quad = vec_mul( x.m_quad, y.m_quad );
}

inline void hkVector4::mul4(hkSimdRealParameter s)
{
	hkQuadReal bs = vec_splat( s.getQuad(), 0);
	m_quad = vec_mul( m_quad, bs );
}

inline void hkVector4::setMul4(hkSimdRealParameter s, const hkVector4& x)
{
	hkQuadReal bs = vec_splat( s.getQuad(), 0);
	m_quad = vec_mul( x.m_quad, bs );
}

inline void hkVector4::addMul4(hkSimdRealParameter s, const hkVector4& x)
{
	hkQuadReal bs = vec_splat( s.getQuad(), 0);
	m_quad = vec_madd( x.m_quad, bs, m_quad );
}
inline void hkVector4::addMul4(hkVector4Parameter x, hkVector4Parameter y)
{
	m_quad = vec_madd( x.m_quad, y.m_quad, m_quad );
}

inline void hkVector4::subMul4(hkSimdRealParameter s, const hkVector4& x)
{
	hkQuadReal bs = vec_splat( s.getQuad(), 0);
	m_quad = vec_nmsub( x.m_quad, bs, m_quad );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& b, hkSimdRealParameter s)
{
	hkQuadReal bs = vec_splat( s.getQuad(), 0);
	m_quad = vec_madd( b.m_quad, bs, a.m_quad );
}

inline void hkVector4::setAddMul4(const hkVector4& a, const hkVector4& x, const hkVector4& y)
{
	m_quad = vec_madd( x.m_quad, y.m_quad, a.m_quad );
}

inline void hkVector4::setCross(const hkVector4& x, const hkVector4& y)
{
	const vector unsigned char perm1203 = (vector unsigned char){4,5,6,7, 8,9,10,11, 0,1,2,3, 12,13,14,15};
	const vector unsigned char perm2013 = (vector unsigned char){8,9,10,11, 0,1,2,3, 4,5,6,7, 12,13,14,15};

	hkQuadReal x1203 = vec_perm( x.m_quad, x.m_quad, perm1203 );
	hkQuadReal y2013 = vec_perm( y.m_quad, y.m_quad, perm2013 );
	hkQuadReal cross0 = vec_mul( x1203, y2013 );

	hkQuadReal x2013 = vec_perm( x.m_quad, x.m_quad, perm2013 );
	hkQuadReal y1203 = vec_perm( y.m_quad, y.m_quad, perm1203 );
	m_quad = vec_nmsub( x2013, y1203, cross0 );
}

inline void hkVector4::setInterpolate4( const hkVector4& x, const hkVector4& y, hkSimdRealParameter t)
{
	hkQuadReal bt = vec_splat( t.getQuad(), 0 );
	hkQuadReal bs = vec_sub( (hkQuadReal){1,1,1,1}, bt );

	hkQuadReal bsa = vec_mul( bs, x.m_quad );
	m_quad = vec_madd( bt, y.m_quad, bsa);
}

inline void hkVector4::setNeg4(const hkVector4& x)
{
	m_quad = vec_sub( HK_QUADREAL_0000, x.m_quad);
}

inline void hkVector4::setNeg4If(int condition)
{
	vector unsigned int mask = condition ? (vector unsigned int){0x80000000,0x80000000,0x80000000,0x80000000} : (vector unsigned int){0}; 
	m_quad = vec_xor( m_quad, hkQuadReal(mask) );
}

inline hkVector4Comparison hkVector4::compareLessThan4(hkVector4Parameter a) const
{	
	hkVector4Comparison ret;
#if defined(__PPU__)
	ret.m_mask = (vector unsigned int)vec_cmplt(m_quad, a.m_quad);
#elif defined(__SPU__)
	ret.m_mask = spu_cmpgt(a.m_quad, m_quad);
#endif
	return ret;
}

inline hkVector4Comparison hkVector4::compareEqual4(hkVector4Parameter a) const
{	
	hkVector4Comparison ret;
#if defined(__PPU__)
	ret.m_mask = (vector unsigned int)vec_cmpeq(m_quad, a.m_quad);
#elif defined(__SPU__)
	ret.m_mask = spu_cmpeq(a.m_quad, m_quad);
#endif
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanEqual4(hkVector4Parameter a) const
{
	hkVector4Comparison ret;
#if defined(__PPU__)
	ret.m_mask = (vector unsigned int)vec_cmple(m_quad, a.m_quad);
#elif defined(__SPU__)
	vector unsigned int mask = spu_cmpgt(m_quad, a.m_quad); // a<=b == !(a>b)
	ret.m_mask = spu_nor(mask, mask);
#endif
	return ret;
}

inline hkVector4Comparison hkVector4::compareLessThanZero4() const
{
	hkVector4Comparison ret;
#if defined(__PPU__)
	ret.m_mask = (vector unsigned int)vec_cmplt(m_quad, HK_QUADREAL_0000);
#elif defined(__SPU__)
	ret.m_mask = spu_cmpgt(HK_QUADREAL_0000, m_quad);
#endif
	return ret;
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
	m_quad = vec_sel( a.m_quad, b.m_quad, (vector unsigned int)comp.m_mask );
}

inline void hkVector4::setAbs4(const hkVector4& x)
{
	m_quad = vec_andc( x.m_quad, (vector float)(vector signed int){0x80000000,0x80000000,0x80000000,0x80000000} );
}

inline void hkVector4::setMin4(const hkVector4& a, const hkVector4& b)
{
	m_quad = vec_min( a.m_quad, b.m_quad );
}

inline void hkVector4::setMax4(const hkVector4& a, const hkVector4& b)
{
	m_quad = vec_max( a.m_quad, b.m_quad );
}


/* matrix3, rotation, quaternion, transform */

inline void hkVector4::_setMul3(const hkMatrix3& m, const hkVector4& v)
{
	const hkQuadReal row0 = vec_splat( v.m_quad, 0 );
	const hkQuadReal row1 = vec_splat( v.m_quad, 1 );
	const hkQuadReal row2 = vec_splat( v.m_quad, 2 );

	const hkQuadReal dot0 = vec_mul ( row0, m.getColumn(0).m_quad );
	const hkQuadReal dot1 = vec_madd( row1, m.getColumn(1).m_quad, dot0 );
	const hkQuadReal dot2 = vec_madd( row2, m.getColumn(2).m_quad, dot1 );
	m_quad = dot2;
}

inline void hkVector4::_setMul4(const hkMatrix3& r, const hkVector4& v)
{
	_setMul3(r,v);
}

inline void hkVector4::_setRotatedDir(const hkRotation& t, const hkVector4& v)
{
	_setMul3(t,v);
}

#define HK_TRANSPOSE3(_a,_b,_c) { \
	hkQuadReal _s, _t; \
	_s = vec_mergeh( _a, _c ); \
	_t = vec_mergel( _a, _c ); \
	_a = vec_mergeh( _s, _b ); \
	_c = vec_perm  ( _t, _b, HK_VECTOR4_SHUFFLE(X,C,Y,_) ); \
	_b = vec_perm  ( _s, _b, HK_VECTOR4_SHUFFLE(Z,B,W,_) ); }

inline void hkVector4::_setRotatedInverseDir(const hkRotation& r, const hkVector4& v)
{
	hkQuadReal a = r.getColumn(0).getQuad();
	hkQuadReal b = r.getColumn(1).getQuad();
	hkQuadReal c = r.getColumn(2).getQuad();
	HK_TRANSPOSE3(a,b,c);

	const hkQuadReal dot0 = vec_mul(  vec_splat(v.m_quad,0), a );
	const hkQuadReal dot1 = vec_madd( vec_splat(v.m_quad,1), b, dot0 );
	const hkQuadReal dot2 = vec_madd( vec_splat(v.m_quad,2), c, dot1 );
	m_quad = dot2;
}

inline void hkVector4::_setTransformedPos(const hkTransform& t, const hkVector4& v)
{
	const hkQuadReal row0 = vec_splat( v.m_quad, 0 );
	const hkQuadReal dot0 = vec_madd( row0, t.getColumn(0).m_quad, t.getColumn(3).m_quad );
	const hkQuadReal row1 = vec_splat( v.m_quad, 1 );
	const hkQuadReal dot1 = vec_madd( row1, t.getColumn(1).m_quad, dot0 );
	const hkQuadReal row2 = vec_splat( v.m_quad, 2 );
	const hkQuadReal dot2 = vec_madd( row2, t.getColumn(2).m_quad, dot1 );
	m_quad = dot2;
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
	hkVector4 scaled; scaled.setMul4(b, a.m_scale);
	hkVector4 rotated; rotated.setRotatedDir( a.m_rotation, scaled );
	setAdd4( rotated, a.m_translation );
}

inline void hkVector4::_setTransformedInversePos(const hkQsTransform& a, const hkVector4& b)
{
	hkQuadReal estimate = vec_re( a.m_scale.m_quad );

	hkVector4 untrans; untrans.setSub4( b, a.m_translation );
	hkVector4 unrotate; unrotate.setRotatedInverseDir( a.m_rotation, untrans );

	hkQuadReal invScale = vec_madd( vec_nmsub( estimate, a.m_scale.m_quad, hkQuadReal1111), estimate, estimate );
	m_quad = vec_mul( unrotate.m_quad, invScale );
}

inline hkSimdReal hkVector4::dot3(const hkVector4& x) const
{
	hkQuadReal square; square = vec_mul( m_quad, x.m_quad );
	hkQuadReal pairs = vec_add(  square, vec_rotl( square, 8 ) );
	return vec_add( pairs, vec_rotl( square, 4 ) );
}

inline hkReal hkVector4::dot3fpu(const hkVector4& a) const
{
	hkQuadRealUnion x; x.q =   m_quad;
	hkQuadRealUnion y; y.q = a.m_quad;
	return x.r[0]*y.r[0] + x.r[1]*y.r[1] + x.r[2]*y.r[2];
}

inline hkSimdReal hkVector4::dot4(const hkVector4& x) const
{
	hkQuadReal square = vec_mul( m_quad, x.m_quad );
	hkQuadReal pairs = vec_add( square, vec_rotl( square, 8 ) );
	return vec_add( pairs, vec_rotl( pairs, 4 ) );
}

inline hkSimdReal hkVector4::dot4xyz1(const hkVector4& x) const
{
	hkQuadReal square; square = vec_mul( m_quad, x.m_quad );
	hkQuadReal pairs = vec_add(  square, vec_rotl( square, 8 ) );
	hkQuadReal d3 = vec_add( pairs, vec_rotl( square, 4 ) );
	return vec_add( d3, vec_splat( m_quad, 3 ) );
}

inline hkSimdReal hkVector4::horizontalAdd3() const
{
	hkQuadReal pairs = vec_add(  m_quad, vec_rotl( m_quad, 8 ) );
	return vec_add( pairs, vec_rotl( m_quad, 4 ) );
}

inline hkSimdReal hkVector4::horizontalAdd4() const
{
	hkQuadReal pairs = vec_add( m_quad, vec_rotl( m_quad, 8 ) );
	return vec_add( pairs, vec_rotl( pairs, 4 ) );
}

inline hkSimdReal hkVector4::length3() const
{
	hkQuadReal squared = this->dot3(*this).getQuad();
	// cmp immediate // spu_andc
		// <todo.a> have unchecked version
	if( vec_nonzero_x( squared ) )
	{
		return vec_mul( squared, hkMath::quadReciprocalSquareRoot(squared) );
	}
	return HK_QUADREAL_0000;
}

inline hkSimdReal hkVector4::lengthSquared3() const
{
	return this->dot3(*this);
}

inline hkSimdReal hkVector4::lengthInverse3() const
{
	hkQuadReal squared = this->dot3(*this).getQuad();
	if( vec_nonzero_x( squared ) )
	{
		return hkMath::quadReciprocalSquareRoot( squared );
	}
	return HK_QUADREAL_0000;
}

inline hkSimdReal hkVector4::length4() const
{
	hkQuadReal squared = this->dot4(*this).getQuad();
	if( vec_nonzero_x( squared ) )
	{
		return vec_mul( squared, hkMath::quadReciprocalSquareRoot(squared) );
	}
	return HK_QUADREAL_0000;
}

inline hkSimdReal hkVector4::lengthSquared4() const
{
	return this->dot4(*this);
}

inline hkSimdReal hkVector4::lengthInverse4() const
{
	hkQuadReal squared = this->dot4(*this).getQuad();
	if( vec_nonzero_x( squared) )
	{
			return hkMath::quadReciprocalSquareRoot( squared );
	}
	return HK_QUADREAL_0000;
}

inline void hkVector4::normalize3()
{
	hkQuadReal linverse = vec_splat( this->lengthInverse3().getQuad(), 0 );
	m_quad = vec_mul( m_quad, linverse );
}

inline hkSimdReal hkVector4::normalizeWithLength3()
{
	hkQuadReal squared = this->dot3(*this).getQuad();
	if( vec_nonzero_x( squared ) )
	{
		hkQuadReal linverse1 = hkMath::quadReciprocalSquareRoot( squared );
		hkQuadReal linverse = vec_splat( linverse1, 0 );
		m_quad = vec_mul( m_quad, linverse );
		return vec_mul( squared, linverse );
	}
	return HK_QUADREAL_0000;
}

inline void hkVector4::normalize4()
{
	hkQuadReal linverse = vec_splat( this->lengthInverse4().getQuad(), 0 );
	m_quad = vec_mul( m_quad, linverse );
}

inline hkSimdReal hkVector4::normalizeWithLength4()
{
	hkQuadReal squared = this->dot4(*this).getQuad();
	if( vec_nonzero_x( squared ) )
	{
		hkQuadReal linverse1 = hkMath::quadReciprocalSquareRoot( squared );
		hkQuadReal linverse = vec_splat( linverse1, 0 );
		m_quad = vec_mul( m_quad, linverse );
		return vec_mul( squared, linverse );
	}
	return HK_QUADREAL_0000;
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

#define HK_SELECT_W_MASK (vector unsigned int){0,0,0,0xffffffff}

inline void hkVector4::setXYZW(const hkVector4& xyz, const hkVector4& w)
{
	m_quad = vec_sel(xyz.m_quad, w.m_quad, HK_SELECT_W_MASK);
}

inline void hkVector4::setW(const hkVector4& w)
{
	m_quad = vec_sel(m_quad, w.m_quad, HK_SELECT_W_MASK);
}

inline void hkVector4::setXYZ(const hkVector4& xyz)
{
	m_quad = vec_sel(xyz.m_quad, m_quad, HK_SELECT_W_MASK);
}

inline void hkVector4::setXYZ0(const hkVector4& v)
{
	m_quad = vec_sel(v.m_quad, HK_QUADREAL_0000, HK_SELECT_W_MASK);
}

inline void hkVector4::setReciprocal4(const hkVector4& vec)
{
	m_quad = hkMath::quadReciprocal(vec.m_quad);
}

inline void hkVector4::setSqrtInverse4(const hkVector4& v)
{
	m_quad = hkMath::quadReciprocalSquareRoot(v.m_quad);
}

HK_ALWAYS_INLINE hkSimdReal hkVector4::getSimdAt(int i) const
{
	HK_PHYSICS_LE;
	switch(i)
	{
		case 0:
			return m_quad;
		case 1:
			return vec_splat(m_quad, 1);
		case 2:
			return vec_splat(m_quad, 2);
		default:
			return vec_splat(m_quad, 3);
	}
}

HK_ALWAYS_INLINE void hkVector4::broadcast(int i)
{
	switch(i)
	{
		case 0:
			m_quad = vec_splat(m_quad, 0);
			break;
		case 1:
			m_quad = vec_splat(m_quad, 1);
			break;
		case 2:
			m_quad = vec_splat(m_quad, 2);
			break;
		default:
			m_quad = vec_splat(m_quad, 3);
			break;
	}
}

HK_ALWAYS_INLINE void hkVector4::setBroadcast(hkVector4Parameter v, int i)
{
	switch(i)
	{
		case 0:
			m_quad = vec_splat(v.m_quad, 0);
			break;
		case 1:
			m_quad = vec_splat(v.m_quad, 1);
			break;
		case 2:
			m_quad = vec_splat(v.m_quad, 2);
			break;
		default:
			m_quad = vec_splat(v.m_quad, 3);
			break;
	}
}

HK_ALWAYS_INLINE void hkVector4::setBroadcast3clobberW(hkVector4Parameter v, int i)
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
