/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>


// moved from the .inl to the .cxx for inline void hkVector4::setInt24W( int value )
HK_COMPILE_TIME_ASSERT( sizeof(int) == sizeof(hkReal) );


void hkVector4::setTransformedPos(const hkTransform& t, const hkVector4& v)
{
	_setTransformedPos(t,v);
}

void hkVector4::setTransformedInversePos(const hkTransform& t, const hkVector4& v)
{
	_setTransformedInversePos(t,v);
}

void hkVector4::setTransformedPos(const hkQsTransform& t, const hkVector4& v)
{
	_setTransformedPos(t,v);
}

void hkVector4::setTransformedInversePos(const hkQsTransform& t, const hkVector4& v)
{
	_setTransformedInversePos(t,v);
}

void hkVector4::setRotatedDir(const hkRotation& t, const hkVector4& v)
{
	_setRotatedDir(t,v);
}

void hkVector4::setRotatedInverseDir(const hkRotation& t, const hkVector4& v)
{
	_setRotatedInverseDir(t,v);
}

static hkBool hkVector4isOk(const hkReal* f, int n)
{
	for(int i=0; i<n; ++i)
	{
		if( hkMath::isFinite(f[i]) == false )
		{
			return false;
		}
	}
	return true;
}

hkBool hkVector4::isOk3() const
{
	const hkReal* f = reinterpret_cast<const hkReal*>(this);
	return hkVector4isOk(f, 3);
}

hkBool hkVector4::isOk4() const
{
	const hkReal* f = reinterpret_cast<const hkReal*>(this);
	return hkVector4isOk(f, 4);
}

#if !defined(HK_PLATFORM_SPU)

hkBool hkVector4::isNormalized3(hkReal eps) const
{
	if( isOk3() )
	{
		hkReal len = this->lengthSquared3();
		return hkMath::fabs( len - 1.0f ) < eps;
	}
	return false;
}

hkBool hkVector4::isNormalized4(hkReal eps) const
{
	if( isOk4() )
	{
		hkReal len = this->lengthSquared4();
		return hkMath::fabs( len - 1.0f ) < eps;
	}
	return false;
}
#endif // !defined(HK_PLATFORM_SPU)

void hkVector4::setMul3( const hkMatrix3& a, const hkVector4& b)
{
	this->_setMul3( a, b );
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
