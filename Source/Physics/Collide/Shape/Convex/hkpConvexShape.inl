/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

 
#if !defined(HK_PLATFORM_SPU)
inline hkpConvexShape::hkpConvexShape(hkpShapeType type, hkReal radius) : hkpSphereRepShape( type )
{
	HK_ASSERT2(0x20b67de1, radius >= 0, "hkpConvexShape should not have a negative radius");
	m_radius = radius;
}
#endif

inline hkReal hkpConvexShape::getRadius() const
{
	return m_radius;
}

inline void hkpConvexShape::setRadius(hkReal radius)
{
	HK_ASSERT2(0x20b67de1, radius >= 0, "hkpConvexShape should not have a negative radius");
	m_radius = radius;
}

void hkpConvexShape::getSupportingVertex( hkVector4Parameter direction, hkpCdVertex& supportingVertexOut ) const
{
#if defined (HK_PLATFORM_SPU)
	(*getShapeFunctions(getType()).m_getSupportingVertexFunc)(this, direction, supportingVertexOut );
#else
	this->getSupportingVertexImpl( direction, supportingVertexOut );
#endif
}

void hkpConvexShape::convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkpCdVertex* vertixArrayOut) const
{
#if defined (HK_PLATFORM_SPU)
	(*getShapeFunctions(getType()).m_convertVertexIdsToVertices)( this, ids, numIds, vertixArrayOut );
#else
	this->convertVertexIdsToVerticesImpl( ids, numIds, vertixArrayOut );
#endif
}

hkpConvexShape::WeldResult hkpConvexShape::weldContactPoint(	hkpVertexId* featurePoints, hkUint8& numFeaturePoints, 
															hkVector4& contactPointWs, const hkTransform* thisObjTransform, 
															const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const
{
#if defined (HK_PLATFORM_SPU)
	return (WeldResult)(*getShapeFunctions(getType()).m_weldContactPointFunc)(	this, featurePoints, numFeaturePoints, 
																				contactPointWs, thisObjTransform, 
																				collidingShape, collidingTransform, separatingNormalInOut  );
#else
	return (WeldResult)this->weldContactPointImpl(	featurePoints, numFeaturePoints, 
													contactPointWs, thisObjTransform, 
													collidingShape, collidingTransform, separatingNormalInOut );
#endif

}

void hkpConvexShape::getCentre( hkVector4& centreOut ) const
{
#if defined (HK_PLATFORM_SPU)
	return (*getShapeFunctions(getType()).m_getCentreFunc)( this, centreOut );
#else
	return this->getCentreImpl( centreOut );
#endif

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
