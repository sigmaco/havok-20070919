/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_COLLIDABLE_H
#define HK_COLLIDE2_COLLIDABLE_H

#include <Physics/Collide/Agent/Collidable/hkpCdBody.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandle.h>

#if defined(HK_PLATFORM_SPU)
#	define hkpCollidable hkCollidablePpu
#	define hkpCdBody hkCdBodyPpu
#endif

class hkAabb;
struct hkAabbUint32;
class hkpShape;
class hkTransform;

/// An hkpCollidable can collide with other hkCollidables. It has an hkpShape and a hkMotionState (or hkTransform) for that shape.
/// It also has void* owner pointer.
/// If you wish to make a collision query, you must create two hkpCollidable objects, and use the hkpCollisionDispatcher
/// to access the correct hkpCollisionAgent for the query.
/// hkpCollidable objects are automatically created by the hkdynamics system, and the owner points to either the hkpEntity
/// or hkpPhantom object in the world. See these classes for further information.
/// The collidable used to inherit from broad phase handle too, but serialization
/// can handle the multiple inheritance (of classes with data members)
class hkpCollidable : public hkpCdBody
{


#if !defined(HK_PLATFORM_SPU)

	public:

		HK_DECLARE_REFLECTION();

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO, hkpCollidable);

			/// Creates a new hkpCollidable.
			/// Note: this constructor sets the owner to be HK_NULL, call setOwner to specify the owner and type
			/// Note: this collidable can't be used for normal collision detection (processCollision)
		inline hkpCollidable( const hkpShape* shape, const hkTransform* ms, int type = 0);

			/// Creates a new hkpCollidable.
			/// Note: this constructor sets the owner to be HK_NULL, call setOwner to specify the owner and type
		inline hkpCollidable( const hkpShape* shape, const hkMotionState* ms, int type = 0);


		inline ~hkpCollidable();

			///Gets the hkpShape.
		inline const hkpShape* getShape() const;

			/// Sets the hkpShape. Note: you should be careful about setting the shape of a hkpCollidable at runtime, as if there
			/// are any collision agents that depend on it they will no longer work and crash
		inline void setShape(const hkpShape* shape);

			/// Sets the entity that owns this hkpCollidable.
			/// and the type, see hkpWorldObject::BroadPhaseType for possible types.
		inline void setOwner( void* owner );

			///Gets the entity that owns this hkpCollidable.
		inline void* getOwner() const
		{
	        return const_cast<char*>( reinterpret_cast<const char*>(this) + m_ownerOffset ); 
	    }

		void checkPerformance();

		//
		// TypedBroadPhase handle i/f:
		//
		inline const hkpTypedBroadPhaseHandle* getBroadPhaseHandle() const;
		inline       hkpTypedBroadPhaseHandle* getBroadPhaseHandle();


		HK_FORCE_INLINE hkpCollidableQualityType getQualityType() const;

			/// Sets the quality type of this collidable.
			///
			/// Note: Having two non-continuously colliding dynamic objects and fixing one of them
			/// doesn't result in continuous collision detection between the objects
			/// if the agent is already created. The current agent will be replaced
			/// by its continuous version only after the bodies separate and lose their broadphase
			/// overlap (when their agent is destroyed) and then come into proximity again
			/// (creating a new agent of type conforming to their current qualityType settings).
		HK_FORCE_INLINE void setQualityType(hkpCollidableQualityType type);

			/// Gets the current allowed penetration depth.
			/// This is a hint to the continuous physics to allow some penetration for this object
			/// to reduce CPU load. Note: this is not a hard limit but more a guideline to the engine.
			/// Depending on the qualityType, this allowed penetration can be breached sooner or later.
			/// See user guide on continuous physics for details.
		HK_FORCE_INLINE hkReal getAllowedPenetrationDepth() const;

			/// Sets the current allowed penetration depth. See getAllowedPenetrationDepth for details.
		HK_FORCE_INLINE void setAllowedPenetrationDepth( hkReal val );


	public:
			///Gets the collision filter info. This is an identifying value used by collision filters
			/// - for example, if a group filter is used, this value would encode a collision group and a system group
		HK_FORCE_INLINE hkUint32 getCollisionFilterInfo() const;

			/// Sets the collision filter info. This is an identifying value used by collision filters
			/// - for example, if a group filter is used, this value would encode a collision group and a system group
		HK_FORCE_INLINE void setCollisionFilterInfo( hkUint32 info );

			///Gets the type. The possible types are defined in hkpWorldObject::BroadPhaseType.
		HK_FORCE_INLINE int getType() const;

		hkpCollidable( class hkFinishLoadedObjectFlag flag );


#endif

	public:

		struct BoundingVolumeData
		{
				HK_DECLARE_REFLECTION();
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpCollidable::BoundingVolumeData );

				BoundingVolumeData();

				HK_FORCE_INLINE const hkAabbUint32& getAabbUint32() const { return reinterpret_cast<const hkAabbUint32&>(m_min); }
				HK_FORCE_INLINE       hkAabbUint32& getAabbUint32()		  { return reinterpret_cast<      hkAabbUint32&>(m_min); }

				HK_FORCE_INLINE void invalidate() { m_min[0] = 1; m_max[0] = 0; }
				HK_FORCE_INLINE bool isValid() const { return m_min[0] <= m_max[0]; }

			public:
				hkUint32		m_min[3];
				hkUint8			m_expansionMin[3];
				hkUint8			m_expansionShift;
				hkUint32		m_max[3];
				hkUint8			m_expansionMax[3];
				hkUint8			m_padding;
				hkUint16		m_numChildShapeAabbs;
				hkAabbUint32*	m_childShapeAabbs;
		};


		enum ForceCollideOntoPpuReasons
		{
			/// Requested by hkpRigidBodyCinfo::m_forceCollideOntoPpu.
			FORCE_PPU_USER_REQUEST = 1,	

			/// Requested by the shape, e.g. hkHeightFieldShapes cannot go to the spu. See the PS3-specific documentation for what shapes are supported on spu.
			FORCE_PPU_SHAPE_REQUEST = 2,

			/// Some constraint modifiers like hkpSoftContactUtil require getting collision callbacks on the ppu, therefore forcing the collision detection for the modified objects to stay on the ppu.
			FORCE_PPU_MODIFIER_REQUEST = 4,
		};

	protected:

			/// This is used by hkDynamics to point to the hkpRigidBody.
			/// Check the type before doing casts.
			/// Note: You can use hkGetRigidBody(hkpCollidable*) to get a type checked owner
			/// (defined in file <hkdynamics/entity/hkpRigidBody.h> )
			/// It is an offset from 'this' to the owner as it assumes that if
			/// a collidable has an owner, the collidable is a member of that owner.
			/// Stored as an offset so that the serialization can handle it 'as is'.
		hkInt8 m_ownerOffset; // +nosave

	public:

			/// Ps3 only: If this flag is non zero, all collision agents attached to this body will run on the ppu only
			/// This is a bitfield using ForceCollideOntoPpuReasons. 
		hkUint8   m_forceCollideOntoPpu;

			// The shape size to be downloaded to the spu, must be a multiple of 16
		hkUint16 m_shapeSizeOnSpu;			//+nosave

		class hkpTypedBroadPhaseHandle m_broadPhaseHandle;

	public:

		struct BoundingVolumeData m_boundingVolumeData;

			// Should be set to the allowed penetration depth
		hkReal m_allowedPenetrationDepth;
};


#if !defined(HK_PLATFORM_SPU)
#	include <Physics/Collide/Agent/Collidable/hkpCollidable.inl>
#else
#	undef hkpCdBody
#	undef hkpCollidable
#	include <Physics/Collide/Agent/Collidable/hkpCollidableSpu.h>
#endif

#endif // HK_COLLIDE2_COLLIDABLE_H

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
