/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

void hkSweptTransform::approxTransformAt( hkTime time, hkTransform& transformOut ) const
{
	_approxTransformAt(time, transformOut );
}

void hkSweptTransform::initSweptTransform( const hkVector4& position, const hkQuaternion& rotation )
{
	m_centerOfMass0.setXYZ0( position ); // w base time
	m_centerOfMass1.setXYZ0( position ); // invDeltaTime

	m_rotation0 = rotation;
	m_rotation1 = rotation;
	m_centerOfMassLocal.setZero4();
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
