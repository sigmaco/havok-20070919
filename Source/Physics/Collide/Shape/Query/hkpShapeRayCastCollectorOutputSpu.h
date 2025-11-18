/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SHAPE_RAY_CAST_COLLECTOR_OUTPUT_SPU_H
#define HK_SHAPE_RAY_CAST_COLLECTOR_OUTPUT_SPU_H


#include <Physics/Collide/Shape/hkpShape.h>


// This is the SPU-local padded version of hkpShapeRayCastCollectorOutput.
// It is only used on SPU.
// For further information on this class see hkpShapeRayCastCollectorOutput.h
struct hkpShapeRayCastCollectorOutput
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastCollectorOutput );

		HK_FORCE_INLINE hkpShapeRayCastCollectorOutput();

		HK_FORCE_INLINE void reset();
		HK_FORCE_INLINE hkBool hasHit() const;
		HK_FORCE_INLINE void copyToUnpaddedPpuLayout(hkpShapeRayCastCollectorOutputPpu *dest);

	public:

		hkVector4			m_normal;
		hkPadSpu<hkReal>	m_hitFraction;
		hkPadSpu<int>		m_extraInfo;
};


#include <Physics/Collide/Shape/Query/hkpShapeRayCastCollectorOutputSpu.inl>


#endif //HK_SHAPE_RAY_CAST_COLLECTOR_OUTPUT_SPU_H

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
