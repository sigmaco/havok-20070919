/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#define HK_VECTOR4UTIL_mulSigns4
inline void HK_CALL hkVector4Util::mulSigns4( hkVector4& inout, const hkVector4& signs)
{
	static HK_ALIGN16( const hkUint32 signmask[4] ) = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };

	hkQuadReal temp = __vand( signs.getQuad(), *(const hkQuadReal*)&signmask );
	inout.getQuad() = __vxor( inout.getQuad(), temp );
}

#define HK_VECTOR4UTIL_dot4_4vs4
inline void HK_CALL hkVector4Util::dot4_4vs4( const hkVector4& a0, const hkVector4& b0, const hkVector4& a1, const hkVector4& b1, const hkVector4& a2, const hkVector4& b2, const hkVector4& a3, const hkVector4& b3, hkVector4& dotsOut)
{
	dotsOut.getQuad() = __vrlimi(__vmsum4fp(a0, b0), __vmsum4fp(a1,b1), 4, 0);
	dotsOut.getQuad() = __vrlimi(dotsOut.getQuad(), __vmsum4fp(a2,b2), 2, 0);
	dotsOut.getQuad() = __vrlimi(dotsOut.getQuad(), __vmsum4fp(a3,b3), 1, 0);
}

#define HK_VECTOR4UTIL_dot3_4vs4
inline void HK_CALL hkVector4Util::dot3_4vs4( const hkVector4& a0, const hkVector4& b0, const hkVector4& a1, const hkVector4& b1, const hkVector4& a2, const hkVector4& b2, const hkVector4& a3, const hkVector4& b3, hkVector4& dotsOut)
{
	dotsOut.getQuad() = __vrlimi(__vmsum3fp(a0, b0), __vmsum3fp(a1,b1), 4, 0);
	dotsOut.getQuad() = __vrlimi(dotsOut.getQuad(), __vmsum3fp(a2,b2), 2, 0);
	dotsOut.getQuad() = __vrlimi(dotsOut.getQuad(), __vmsum3fp(a3,b3), 1, 0);
}

/*
#define HK_VECTOR4UTIL_convertToUint16
inline void HK_CALL hkVector4Util::convertToUint16( const hkVector4& in, const hkVector4& offset, const hkVector4& scale, hkIntUnion64& out)
{
	HK_ALIGN16( hkInt64 result[2] );

	hkVector4 x;
	x.setAdd4(in,offset);
	x.mul4(scale);
	x.getQuad() = __vctsxs(x.getQuad() , 0 );
	x.getQuad() = __vpkswss( x.getQuad(), x.getQuad());
	__stvx(x.getQuad(), result, 0);

	out.i64 = result[0];
}

#define HK_VECTOR4UTIL_convertToUint16WithClip
inline void HK_CALL hkVector4Util::convertToUint16WithClip( const hkVector4& in, const hkVector4& offset, const hkVector4& scale, const hkVector4& min, const hkVector4& max, hkIntUnion64& out)
{
	//*

	HK_ALIGN16( hkInt64 result[2] );

	hkVector4 x;
	x.setAdd4(in,offset);
	x.mul4(scale);
	x.setMin4(x,max);
	x.setMax4(x,min);
	x.getQuad() = __vctsxs(x.getQuad() , 0 );
	x.getQuad() = __vpkswss( x.getQuad(), x.getQuad());
	__stvx(x.getQuad(), result, 0);

	out.i64 = result[0];
}
*/

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
