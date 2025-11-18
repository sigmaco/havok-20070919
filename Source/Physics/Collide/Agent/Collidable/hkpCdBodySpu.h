/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_CD_BODY_SPU_H
#define HK_COLLIDE2_CD_BODY_SPU_H

#include <Physics/Collide/Shape/hkpShape.h>
#include <Common/Base/hkBase.h>

class hkpShape;
class hkMotionState;
class hkpCollidable;

// this is the spu-local padded version of hkpCdBody; it is only used on spu; for further information on this class, see hkpCdBody.h
class hkpCdBody
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT, hkpCdBody);	

		HK_FORCE_INLINE const hkTransform& getTransform() const;
		
		HK_FORCE_INLINE const hkpShape* getShape() const;

		inline const hkpCollidable* getRootCollidable() const;

		inline hkpShapeKey getShapeKey() const ;

		HK_FORCE_INLINE const hkpCdBody* getParent() const;

	public:

		explicit HK_FORCE_INLINE hkpCdBody( const hkpCdBody* parent );

		HK_FORCE_INLINE hkpCdBody( const hkpCdBody* parent, const hkMotionState* ms );

		HK_FORCE_INLINE hkpCdBody( const hkpCdBody* parent, const hkTransform* t );

		HK_FORCE_INLINE void setShape( const hkpShape* shape, hkpShapeKey key );

		HK_FORCE_INLINE const hkMotionState* getMotionState() const;

		HK_FORCE_INLINE void setMotionState( const hkMotionState* state );

		HK_FORCE_INLINE void setTransform( const hkTransform* t );

		HK_FORCE_INLINE hkpCdBody(  ){}
		
	public:

		friend class hkpCollidable;

		HK_FORCE_INLINE hkpCdBody( const hkpShape* shape, const hkMotionState* motionState );

		HK_FORCE_INLINE hkpCdBody( const hkpShape* shape, const hkTransform* t );

		HK_FORCE_INLINE hkpCdBody( const hkpCdBody& body ) {}


		hkPadSpu<const hkpShape*>       m_shape;
		hkPadSpu<hkpShapeKey>           m_shapeKey; //+overridetype(hkUint32)

#if defined (HK_PLATFORM_SPU)
	public:
#endif

		hkPadSpu<const void*> m_motion; //+nosave

#if defined (HK_PLATFORM_SPU)
	public:
#endif

		hkPadSpu<const hkpCdBody*>		 m_parent;
};


#include <Physics/Collide/Agent/Collidable/hkpCdBodySpu.inl>


#endif // HK_COLLIDE2_CD_BODY_SPU_H

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
