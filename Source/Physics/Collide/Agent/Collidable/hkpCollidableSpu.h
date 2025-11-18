/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_COLLIDABLE_SPU_H
#define HK_COLLIDE2_COLLIDABLE_SPU_H

class hkpShape;
class hkTransform;

// this is the spu-local padded version of hkpCollidable; it is only used on spu; for further information on this class, see hkpCollidable.h
class hkpCollidable : public hkpCdBody
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpCollidable );

		inline hkpCollidable( const hkpShape* shape, const hkTransform* ms);

		inline hkpCollidable( const hkpShape* shape, const hkMotionState* ms);

		inline ~hkpCollidable();

		inline const hkpShape* getShape() const;

		inline void setShape(const hkpShape* shape);

		inline void setOwner( void* owner );

		inline void* getOwner() const
		{
	        return m_owner;
	    }


		HK_FORCE_INLINE hkpCollidableQualityType getQualityType() const;

		HK_FORCE_INLINE hkReal getAllowedPenetrationDepth() const;

		HK_FORCE_INLINE void setAllowedPenetrationDepth( hkReal val );


	public:

		HK_FORCE_INLINE hkUint32 getCollisionFilterInfo() const;

		HK_FORCE_INLINE void setCollisionFilterInfo( hkUint32 info );

	public:

		hkPadSpu<void*>		m_owner;
		hkPadSpu<hkReal>	m_allowedPenetrationDepth;

			// data from broadphase handle
		hkPadSpu<int>		m_objectQualityType;
		hkPadSpu<hkUint32>	m_collisionFilterInfo;

		hkCollidablePpu::BoundingVolumeData m_boundingVolumeData;
		hkUint32 m_padding[3]; // safety padding as we memCpy16 stuff from the ppu variant into here

};


#include <Physics/Collide/Agent/Collidable/hkpCollidableSpu.inl>


#endif // HK_COLLIDE2_COLLIDABLE_SPU_H

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
