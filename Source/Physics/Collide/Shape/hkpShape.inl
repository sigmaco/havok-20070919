/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

hkpShape::hkpShape( hkpShapeType type )
{
	m_userData = 0;
	m_type = type;
}

HK_CLASSALIGN16(class) hkAlignedShape: public hkpShape{
	hkAlignedShape();
};

hkpShapeType hkpShape::getType() const
{
	return static_cast<const hkAlignedShape*>(this)->m_type;
}

inline hkUlong hkpShape::getUserData() const
{
	return m_userData;
}

inline void hkpShape::setUserData( hkUlong data )
{
	m_userData = data;
}
		
void hkpShape::getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const
{
#if defined (HK_PLATFORM_SPU)
	(*m_shapeFunctions[m_type].m_getAabbFunc)(this, localToWorld, tolerance, out );
#else
	getAabbImpl( localToWorld, tolerance, out );
#endif
}

hkBool hkpShape::castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const
{
#if defined (HK_PLATFORM_SPU)
	return (*m_shapeFunctions[m_type].m_castRay)( this, input, output );
#else
	return castRayImpl( input, output );
#endif
}

#if defined (HK_PLATFORM_SPU)
hkUint32 hkpShape::getCollisionFilterInfo( hkpShapeKey key ) const
{
	return (*m_shapeFunctions[m_type].m_getCollisionFilterInfoFunc)( this, key );
}

const hkpShape* hkpShape::getChildShape( hkpShapeKey key, ShapeBuffer& buffer ) const
{
	return (*m_shapeFunctions[m_type].m_getChildShapeFunc)( this, key, buffer );
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
