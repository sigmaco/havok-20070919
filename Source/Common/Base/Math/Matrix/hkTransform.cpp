/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

#if !defined (HK_PLATFORM_SPU)
void hkTransform::get4x4ColumnMajor(hkReal* d) const
{
	const hkReal* p = &m_rotation(0,0);
	for (int i = 0; i<4; i++)
	{
		d[0] = p[0];
		d[1] = p[1];
		d[2] = p[2];
		d[3] = 0.0f;
		d+= 4;
		p+= 4;
	}
	d[-1] = 1.0f;
}

void hkTransform::set4x4ColumnMajor(const hkReal* p)
{
	hkReal* d = &m_rotation(0,0);
	for (int i = 0; i<4; i++)
	{
		d[0] = p[0];
		d[1] = p[1];
		d[2] = p[2];
		d[3] = 0.0f;
		d+= 4;
		p+= 4;
	}
	d[-1] = 1.0f;
}
#endif



void hkTransform::setInverse( const hkTransform& t )
{
	m_rotation.setTranspose( t.getRotation() ); 

	hkVector4 tr;	tr.setNeg4(t.getTranslation()); 
	m_translation._setRotatedDir( m_rotation, tr);
}


// aTc = aTb * bTc
void hkTransform::setMul( const hkTransform& aTb, const hkTransform& bTc )
{
	HK_ASSERT(0x4763da71,  this != &aTb );

	hkVector4Util::rotatePoints( aTb.getRotation(), &bTc.getRotation().getColumn(0), 4, &this->getRotation().getColumn(0) );
	m_translation.add4( aTb.m_translation);
}

void hkTransform::setMulInverseMul( const hkTransform& bTa, const hkTransform &bTc )
{
	hkVector4Util::rotateInversePoints( bTa.getRotation(), &bTc.getRotation().getColumn(0), 3, &this->getRotation().getColumn(0) );
	hkVector4 h; h.setSub4(bTc.m_translation, bTa.m_translation );
	m_translation._setRotatedInverseDir( bTa.m_rotation, h);
}

#if !defined (HK_PLATFORM_SPU)
void hkTransform::setMulEq( const hkTransform& b )
{
	hkTransform at = *this;
	setMul( at, b );
}

hkBool hkTransform::isOk() const
{
	const hkReal* r = reinterpret_cast<const hkReal*>(this);
	for(int i=0; i<16; ++i)
	{
		if( hkMath::isFinite(r[i]) == false )
		{
			return false;
		}
	}
	return true;
}
#endif

#if !defined (HK_PLATFORM_SPU)
void hkTransform::setMulMulInverse( const hkTransform &wTa, const hkTransform &wTb )
{

	hkTransform h;
	h.setInverse( wTb );
	this->setMul( wTa, h );	
}
#endif

HK_ALIGN16( hkReal hkTransformIdentity[] ) =
{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
};

#if !defined (HK_PLATFORM_SPU)
hkBool hkTransform::isApproximatelyEqual( const hkTransform& t, hkReal zero ) const
{
	return		m_rotation.isApproximatelyEqual( t.getRotation(), zero )
		&&	m_translation.equals3( t.getTranslation(), zero );
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
