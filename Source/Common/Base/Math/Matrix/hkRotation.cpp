/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

void hkRotation::set(const hkQuaternion& qi)
{

	HK_ASSERT2(0x1ff88f0e, qi.isOk(), "hkQuaternion not normalized/invalid!");
	const hkVector4& q = qi.m_vec;

	hkReal x2 = q(0) + q(0);
	hkReal y2 = q(1) + q(1);
	hkReal z2 = q(2) + q(2);

	hkReal xx = q(0)*x2;
	hkReal xy = q(0)*y2;
	hkReal xz = q(0)*z2;
	hkReal yy = q(1)*y2;
	hkReal yz = q(1)*z2;
	hkReal zz = q(2)*z2;

	hkReal wx = q(3)*x2;
	hkReal wy = q(3)*y2;
	hkReal wz = q(3)*z2;

	getColumn(0).set(1.0f-(yy+zz),	xy+wz,			xz-wy);
	getColumn(1).set(xy-wz,			1.0f-(xx+zz),	yz+wx);
	getColumn(2).set(xz+wy,			yz-wx,			1.0f-(xx+yy));
}

void hkRotation::setAxisAngle(const hkVector4& axis, hkReal angle)
{
	hkQuaternion q;
	q.setAxisAngle( axis, angle );
	this->set(q);
}

#if !defined (HK_PLATFORM_SPU)
hkBool hkRotation::isOrthonormal( hkReal epsilon ) const
{
	// Check length of cols is 1

	const hkReal dot0 = m_col0.dot3(m_col0);
	if( hkMath::fabs( dot0 - 1.0f) > epsilon)
	{
		return false;
	}

	const hkReal dot1 = m_col1.dot3(m_col1);
	if( hkMath::fabs( dot1 - 1.0f) > epsilon)
	{
		return false;
	}

	const hkReal dot2 = m_col2.dot3(m_col2);
	if( hkMath::fabs( dot2 - 1.0f) > epsilon)
	{
		return false;
	}

	// Check orthonormal and not reflection

	hkVector4 col0CrossCol1;
	col0CrossCol1.setCross(m_col0, m_col1);

	return col0CrossCol1.equals3(m_col2, epsilon) != false;
}

void hkRotation::renormalize()
{
#if 0
	// Graphics Gems I, p464
	// may be faster depending on the number of terms used
	hkMatrix3 correction; correction.setIdentity();
	hkMatrix3 residual; residual.setMulInverse( *this, *this );
	residual.sub( correction );
	const hkReal factors[] = { 1.0f/2, 3.0f/8, 5.0f/16, 35.0f/128, -65.0f/256, 231.0f/1024, -429/2048 };
	const int numFactors = sizeof(factors)/sizeof(hkReal);
	for( int i = 0; i < numFactors; ++i )
	{
		correction.addMul( factors[i], residual );
		residual.mul(residual);
	}
	this->mul(correction);
#endif
	hkQuaternion q; q.setAndNormalize(*this);
	this->set(q);
}
#endif

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
