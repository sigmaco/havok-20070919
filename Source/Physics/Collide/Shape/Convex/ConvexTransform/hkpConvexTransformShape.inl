/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

inline const hkpConvexShape* hkpConvexTransformShape::getChildShape() const 
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

inline hkTransform& hkpConvexTransformShape::getTransform() 
{ 
	return m_transform; 
}

inline const hkTransform& hkpConvexTransformShape::getTransform() const 
{ 
	return m_transform; 
}

inline int hkpConvexTransformShape::calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const
{
	// only cascades that will fit in total into one of the spu's shape buffers are allowed to be uploaded onto spu.

	int maxAvailableBufferSizeForChild = spuBufferSizeLeft - sizeof(*this);

	int childSize = m_childShape.getChild()->calcSizeForSpu(input, maxAvailableBufferSizeForChild);
	if ( childSize < 0 || childSize > maxAvailableBufferSizeForChild )
	{
		// early out if cascade will not fit into spu's shape buffer
		return -1;
	}

	// if child is consecutive in memory, set flag and return total size
	if ( hkUlong(m_childShape.getChild()) == hkUlong((this+1)) )
	{
		m_childShapeSize = 0;
		return sizeof(*this) + childSize;
	}

	// the spu will need this value to properly dma the child shape in one go
	m_childShapeSize = childSize;

	// if child is not consecutive in memory, restart size calculation with just us
	return sizeof(*this);
}

inline void hkpConvexTransformShape::initializeSpu( const hkpConvexShape* childShape, const hkTransform& transform, hkReal radius )
{
	m_type = HK_SHAPE_CONVEX_TRANSFORM;
	m_childShape = childShape; 
	m_radius = radius;
	m_transform = transform;
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
