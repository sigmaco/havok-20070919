/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

inline const hkpConvexShape* hkpConvexTranslateShape::getChildShape() const 
{
#if defined(HK_PLATFORM_SPU)
	// fetch child shape if it is not yet present in spu's local shape buffer
	// (if m_childShapeSize == 0 the child shape already follows this shape consecutively in memory, otherwise we need to dma it in right after this shape)
	if ( m_childShapeSize > 0 )
	{
		getChildShapeFromPpu();
	}
	return (this+1);
#else
	return static_cast<const hkpConvexShape*>(m_childShape.getChild());
#endif
}

inline const hkVector4& hkpConvexTranslateShape::getTranslation() const 
{ 
	return m_translation; 
}

inline hkVector4& hkpConvexTranslateShape::getTranslation()
{ 
	return m_translation; 
}

inline void hkpConvexTranslateShape::initializeSpu( const hkpConvexShape* childShape, const hkVector4& translation, hkReal radius )
{
	m_type = HK_SHAPE_CONVEX_TRANSLATE;
	m_childShape = childShape; 
	m_radius = radius;
	m_translation = translation;
	m_translation(3) = 0;
	m_childShapeSize = 0;
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
