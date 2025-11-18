/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_WORLD_RAY_CAST_OUTPUT_SPU_H
#define HK_WORLD_RAY_CAST_OUTPUT_SPU_H


// This is the SPU-local padded version of hkpShapeRayCastOutput.
// It is only used on SPU.
// For further information on this class see hkpShapeRayCastOutput.h
struct hkpWorldRayCastOutput : public hkpShapeRayCastOutput
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpWorldRayCastOutput );

		HK_FORCE_INLINE hkpWorldRayCastOutput();

		HK_FORCE_INLINE void reset();
		HK_FORCE_INLINE hkBool hasHit() const;
		HK_FORCE_INLINE hkBool operator<( const hkpWorldRayCastOutput& b ) const;
		HK_FORCE_INLINE void copyToUnpaddedPpuLayout(hkpWorldRayCastOutputPpu *dest);

	public:

		hkPadSpu<const hkpCollidable*> m_rootCollidable;
};


#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutputSpu.inl>


#endif //HK_WORLD_RAY_CAST_OUTPUT_SPU_H

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
