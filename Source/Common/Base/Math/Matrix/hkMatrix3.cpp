/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

#if !defined (HK_PLATFORM_SPU)
hkBool hkMatrix3::isOk() const
{
	const hkReal* f = reinterpret_cast<const hkReal*>(this);
	for(int i=0; i<12; ++i)
	{
		if( hkMath::isFinite(f[i]) == false )
		{
			return false;
		}
	}
	return true;
}
#endif

#if !defined (HK_PLATFORM_SPU)
const hkMatrix3& hkMatrix3::getIdentity()
{
	return hkTransform::getIdentity().getRotation();
}
#endif

#if !defined (HK_PLATFORM_SPU)
void hkMatrix3::transpose()
{
	hkMatrix3& m = *this;
	hkAlgorithm::swap( m(0,1), m(1,0) );
	hkAlgorithm::swap( m(0,2), m(2,0) );
	hkAlgorithm::swap( m(1,2), m(2,1) );
}
#endif

void hkMatrix3_setMulMat3Mat3( hkMatrix3* THIS, const hkMatrix3& aTb, const hkMatrix3& bTc )
{
	HK_ASSERT(0x6d9d1d43,  THIS != &aTb );
	hkVector4Util::rotatePoints( aTb, &bTc.getColumn(0), 3, &THIS->getColumn(0) );
}

#if !defined (HK_PLATFORM_SPU)
void hkMatrix3_invertSymmetric( hkMatrix3& thisMatrix )
{
	thisMatrix.invertSymmetric();
}
#endif

void hkMatrix3::setTranspose( const hkMatrix3& s )
{
	hkMatrix3& d = *this;
	d(0,0) = s(0,0);
	d(1,1) = s(1,1);
	d(2,2) = s(2,2);
	d(3,0) = 0.0f;
	d(3,1) = 0.0f;
	d(3,2) = 0.0f;
	d(1,0) = s(0,1);	
	d(0,1) = s(1,0);	
	d(2,0) = s(0,2);	
	d(0,2) = s(2,0);	
	d(2,1) = s(1,2);	
	d(1,2) = s(2,1);	
}

// aTc = aTb * bTc
void hkMatrix3::setMul( const hkMatrix3& aTb, const hkMatrix3& bTc )
{
	HK_ASSERT(0x6d9d1d43,  this != &aTb );
	hkVector4Util::rotatePoints( aTb, &bTc.getColumn(0), 3, &this->getColumn(0) );
}

void hkMatrix3::changeBasis(const hkRotation& r)
{
	hkRotation temp;
	temp.setMulInverse(*this, r);
	this->setMul(r, temp);
}

void hkMatrix3::setMulInverse( const hkMatrix3& aTb, const hkRotation& cTb )
{
	HK_ASSERT(0xf032e412,  this != &aTb );
	hkRotation bTc; bTc.setTranspose(cTb);
	hkVector4Util::rotatePoints( aTb, &bTc.getColumn(0), 3, &this->getColumn(0) );
}

#if !defined (HK_PLATFORM_SPU)
void hkMatrix3::setMul( hkSimdRealParameter scale, const hkMatrix3& a)
{
	getColumn(0).setMul4(scale, a.getColumn(0));
	getColumn(1).setMul4(scale, a.getColumn(1));
	getColumn(2).setMul4(scale, a.getColumn(2));
}

void hkMatrix3::addMul( hkSimdRealParameter scale, const hkMatrix3& a)
{
	HK_ASSERT(0x53e345d4,  this != &a);
	getColumn(0).addMul4(scale, a.getColumn(0));
	getColumn(1).addMul4(scale, a.getColumn(1));
	getColumn(2).addMul4(scale, a.getColumn(2));
}


#endif


#if !defined (HK_PLATFORM_SPU)
hkBool hkMatrix3::isApproximatelyEqual( const hkMatrix3& m, hkReal zero) const
{
	return	   m_col0.equals3( m.getColumn(0), zero )
			&& m_col1.equals3( m.getColumn(1), zero )
			&& m_col2.equals3( m.getColumn(2), zero );
}
#endif

#if !defined (HK_PLATFORM_SPU)
void hkMatrix3::setCrossSkewSymmetric( const hkVector4& r )
{
	getColumn(0).set(  0   ,  r(2), -r(1) );
	getColumn(1).set( -r(2),     0, +r(0) );
	getColumn(2).set(  r(1), -r(0),     0 );
}


hkResult hkMatrix3::invert(hkReal epsilon)
{
	hkVector4 r0; r0.setCross( getColumn(1), getColumn(2) );
    hkVector4 r1; r1.setCross( getColumn(2), getColumn(0) );
    hkVector4 r2; r2.setCross( getColumn(0), getColumn(1) );

    hkSimdReal determinant = getColumn(0).dot3(r0);
    
    if( hkMath::fabs(determinant) > epsilon * epsilon * epsilon)
	{
		hkSimdReal dinv = hkSimdReal(1.0f) / determinant;
		getColumn(0).setMul4(dinv, r0);
		getColumn(1).setMul4(dinv, r1);
		getColumn(2).setMul4(dinv, r2);
		hkMatrix3& m = *this;
		hkAlgorithm::swap( m(0,1), m(1,0) );
		hkAlgorithm::swap( m(0,2), m(2,0) );
		hkAlgorithm::swap( m(1,2), m(2,1) );
		return HK_SUCCESS;	
    }
	else
	{
		return HK_FAILURE;
	}    
}

void hkMatrix3::invertSymmetric()
{
	hkVector4 r0; r0.setCross( getColumn(1), getColumn(2) );
    hkVector4 r1; r1.setCross( getColumn(2), getColumn(0) );
    hkVector4 r2; r2.setCross( getColumn(0), getColumn(1) );

    hkReal determinant = getColumn(0).dot3(r0);
	const hkReal eps = HK_REAL_EPSILON*HK_REAL_EPSILON*HK_REAL_EPSILON;
	determinant = hkMath::max2( eps, determinant );

    
	hkSimdReal dinv = 1.0f / determinant;

	getColumn(0).setMul4(dinv, r0);
	getColumn(1).setMul4(dinv, r1);
	getColumn(2).setMul4(dinv, r2);
}


void hkMatrix3::add( const hkMatrix3& a )
{
	getColumn(0).add4( a.getColumn(0) );
	getColumn(1).add4( a.getColumn(1) );
	getColumn(2).add4( a.getColumn(2) );
}

void hkMatrix3::sub( const hkMatrix3& a )
{
	getColumn(0).sub4( a.getColumn(0) );
	getColumn(1).sub4( a.getColumn(1) );
	getColumn(2).sub4( a.getColumn(2) );
}

void hkMatrix3::mul( const hkMatrix3& a )
{

	hkMatrix3 temp;
	temp.setMul( *this, a );
	*this = temp;
}

void hkMatrix3::mul( hkSimdRealParameter scale)
{
	getColumn(0).mul4(scale);
	getColumn(1).mul4(scale);
	getColumn(2).mul4(scale);
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
