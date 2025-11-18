/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/WheelCollide/RayCast/hkpVehicleRaycastWheelCollide.h>
#include <Physics/Collide/Filter/hkpCollisionFilter.h>

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>

hkpVehicleRaycastWheelCollide::hkpVehicleRaycastWheelCollide()
{
	m_wheelCollisionFilterInfo = 0;
	m_alreadyUsed = false;
	m_phantom = HK_NULL;
}

void hkpVehicleRaycastWheelCollide::init( const hkpVehicleInstance* vehicle )
{
	HK_ASSERT2(0x70660634, m_phantom == HK_NULL, "init() will create a new phantom. The phantom must be HK_NULL when init is called");
	// Initialise the phantom
	hkAabb aabb;
	calcWheelsAABB( vehicle, aabb );

	hkAabb pci;
	pci.m_min = aabb.m_min;
	pci.m_max = aabb.m_max;
	m_phantom = new hkpAabbPhantom(pci, m_wheelCollisionFilterInfo);
	m_rejectRayChassisListener.m_chassis = vehicle->getChassis()->getCollidable();
	m_phantom->addPhantomOverlapListener( &m_rejectRayChassisListener );
}

hkpVehicleWheelCollide* hkpVehicleRaycastWheelCollide::clone( const hkArray<hkpPhantom*>& newPhantoms ) const
{
	hkpVehicleRaycastWheelCollide* newC = new hkpVehicleRaycastWheelCollide();
	newC->m_phantom = (hkpAabbPhantom*) newPhantoms[0];
	newC->m_phantom->addReference();

	newC->m_phantom->removePhantomOverlapListener(const_cast<hkpRejectRayChassisListener*>(&this->m_rejectRayChassisListener));
	newC->m_phantom->addPhantomOverlapListener(&newC->m_rejectRayChassisListener);
	
	return newC;
}

void hkpVehicleRaycastWheelCollide::getPhantoms( hkArray<hkpPhantom*>& phantomsOut )
{
	phantomsOut.pushBack( m_phantom );
}

hkpVehicleRaycastWheelCollide::~hkpVehicleRaycastWheelCollide()
{
	// Vehicle has a phantom yet? 
	if( m_phantom != HK_NULL ) 
	{
		// cant remove m_rejectRayChassisListener from phantom's overlap listeners list
		// because if the objects were serialized they can already be destroyed (cleanup procedure)
		// this is suggested as a temporary solution, need to find a better way
		if ( m_memSizeAndFlags != 0 && m_phantom->m_memSizeAndFlags != 0)
		{
			m_phantom->removePhantomOverlapListener( &m_rejectRayChassisListener );
		}
		m_phantom->removeReference();
	}
}


void hkpVehicleRaycastWheelCollide::calcWheelsAABB( const hkpVehicleInstance* vehicle, hkAabb& aabbOut )
{
	aabbOut.m_min.setMin4( vehicle->m_wheelsInfo[0].m_hardPointWs, vehicle->m_wheelsInfo[0].m_rayEndPointWs );
	aabbOut.m_max.setMax4( vehicle->m_wheelsInfo[0].m_hardPointWs, vehicle->m_wheelsInfo[0].m_rayEndPointWs );

	for (int w_it=1; w_it<vehicle->m_data->m_numWheels; w_it ++)
	{
		const hkpVehicleInstance::WheelInfo &wheel_info = vehicle->m_wheelsInfo[w_it];// note is non-const &
		aabbOut.m_min.setMin4( aabbOut.m_min, wheel_info.m_rayEndPointWs );
		aabbOut.m_min.setMin4( aabbOut.m_min, wheel_info.m_hardPointWs );
		aabbOut.m_max.setMax4( aabbOut.m_max, wheel_info.m_rayEndPointWs );
		aabbOut.m_max.setMax4( aabbOut.m_max, wheel_info.m_hardPointWs );
	}
}

void hkpVehicleRaycastWheelCollide::castSingleWheel(const hkpVehicleInstance::WheelInfo& wheelInfo, hkpVehicleInstance* vehicle, hkpWorldRayCastOutput& output)
{
	hkpWorldRayCastInput input;
	input.m_from = wheelInfo.m_hardPointWs;
	input.m_to = wheelInfo.m_rayEndPointWs;
	input.m_enableShapeCollectionFilter = true;
	input.m_filterInfo = m_wheelCollisionFilterInfo;
	m_phantom->castRay( input, output );
}

void hkpVehicleRaycastWheelCollide::calcSingleWheelGroundFriction( hkpVehicleInstance* vehicle, hkInt8 wheelInfoNum, const hkpWorldRayCastOutput& worldRayCastOutput, hkReal& frictionOut ) const
{
	// User can implement a custom friction calculation using this method
	// Output parameter is frictionOut
}


void hkpVehicleRaycastWheelCollide::updatePhantom( hkpVehicleInstance* vehicle )
{
	hkAabb aabb;
	calcWheelsAABB( vehicle, aabb );

		// we know that we are the only user of the phantom right now
	m_phantom->markForWrite();
	m_phantom->setAabb( aabb );
	m_phantom->unmarkForWrite();
}

void hkpVehicleRaycastWheelCollide::collideWheels(const hkReal deltaTime, hkpVehicleInstance* vehicle, CollisionDetectionWheelOutput* cdInfoOut )
{
	// Check if the phantom has been added to the world.
	HK_ASSERT2(0x676876e3, m_phantom->getWorld() != HK_NULL, "The phantom for the wheelCollide component must be added to the world before using a hkpVehicleInstance.");

	updatePhantom( vehicle );

	for (hkInt8 w_it=0; w_it< vehicle->m_data->m_numWheels; w_it ++)
	{
		CollisionDetectionWheelOutput& cd_wheelInfo = cdInfoOut[w_it];

		const hkpVehicleInstance::WheelInfo& wheel_info = vehicle->m_wheelsInfo[w_it];
		//
		// RAY CAST
		//
		hkpWorldRayCastOutput output;
		castSingleWheel( wheel_info, vehicle, output );

		const hkReal    spr_length   = vehicle->m_suspension->m_wheelParams[w_it].m_length;
		const hkReal	wheel_radius = vehicle->m_data->m_wheelParams[w_it].m_radius;


		// wheel on track?
		if (output.hasHit())
		{
			cd_wheelInfo.m_contactPoint.setNormal( output.m_normal );
			for( int i = 0; i < hkpShapeRayCastOutput::MAX_HIERARCHY_DEPTH && output.m_shapeKeys[i] != HK_INVALID_SHAPE_KEY; ++i )
			{
				cd_wheelInfo.m_contactShapeKey = output.m_shapeKeys[i];
			}

			hkpRigidBody* groundRigidBody = hkGetRigidBody(output.m_rootCollidable);
			HK_ASSERT2(0x1f3b75d4,  groundRigidBody, 
				"Your car raycast hit a phantom object. If you don't want this to happen, disable collisions between the wheel raycast phantom and phantoms.\
				\nTo do this, change hkpVehicleRaycastWheelCollide::m_wheelCollisionFilterInfo or hkpCollisionFilter::isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b )");

			cd_wheelInfo.m_contactBody = groundRigidBody; 

			hkReal hitDistance = output.m_hitFraction * (spr_length + wheel_radius);
			cd_wheelInfo.m_currentSuspensionLength = hitDistance - wheel_radius;

			hkVector4 contactPointWsPosition; contactPointWsPosition.setAddMul4( wheel_info.m_hardPointWs, wheel_info.m_suspensionDirectionWs, hitDistance);
			cd_wheelInfo.m_contactPoint.setPosition( contactPointWsPosition );

			//
			//	friction
			//
			hkReal groundfriction = cd_wheelInfo.m_contactBody->getMaterial().getFriction();
			calcSingleWheelGroundFriction( vehicle, w_it, output, groundfriction );
			cd_wheelInfo.m_contactFriction = groundfriction;

			hkReal denominator = cd_wheelInfo.m_contactPoint.getNormal().dot3( wheel_info.m_suspensionDirectionWs );
			HK_ASSERT(0x66b55978,  denominator < 0.f );

			//
			// calculate the suspension velocity
			// 
			hkVector4	 chassis_velocity_at_contactPoint;
			vehicle->getChassis()->getPointVelocity(cd_wheelInfo.m_contactPoint.getPosition(), chassis_velocity_at_contactPoint);

			hkVector4 groundVelocityAtContactPoint;
			groundRigidBody->getPointVelocity( cd_wheelInfo.m_contactPoint.getPosition(), groundVelocityAtContactPoint);

			hkVector4 chassisRelativeVelocity; chassisRelativeVelocity.setSub4( chassis_velocity_at_contactPoint, groundVelocityAtContactPoint);

			hkReal projVel = cd_wheelInfo.m_contactPoint.getNormal().dot3( chassisRelativeVelocity );

			if ( denominator >= - vehicle->m_data->m_normalClippingAngle)
			{
				cd_wheelInfo.m_suspensionRelativeVelocity = 0.0f;
				cd_wheelInfo.m_clippedInvContactDotSuspension = 1.0f / vehicle->m_data->m_normalClippingAngle;
			}
			else
			{
				hkReal inv = -1.f / denominator;
				cd_wheelInfo.m_suspensionRelativeVelocity = projVel * inv;
				cd_wheelInfo.m_clippedInvContactDotSuspension = inv;
			}

		}
		else	// Not in contact : position wheel in a nice (rest length) position
		{
			cd_wheelInfo.m_contactBody = HK_NULL; 
			cd_wheelInfo.m_currentSuspensionLength = spr_length;
			cd_wheelInfo.m_suspensionRelativeVelocity = 0.0f;
			cd_wheelInfo.m_contactPoint.setPosition( wheel_info.m_rayEndPointWs );

			hkVector4 contactPointWsNormal; contactPointWsNormal.setNeg4( wheel_info.m_suspensionDirectionWs );
			cd_wheelInfo.m_contactPoint.setNormal( contactPointWsNormal );
			cd_wheelInfo.m_contactFriction = 0.0f;
			cd_wheelInfo.m_clippedInvContactDotSuspension = 1.0f;
		}
	}
}

hkpRejectRayChassisListener::hkpRejectRayChassisListener()
{
	m_chassis = HK_NULL;
}

hkpRejectRayChassisListener::~hkpRejectRayChassisListener()
{
	if ( m_chassis != HK_NULL )
	{
		// remove reference?
		//m_chassis->removeReference();
	}		
}


void hkpRejectRayChassisListener::collidableAddedCallback(  const hkpCollidableAddedEvent& event )
{
	if ( event.m_collidable == m_chassis )
	{
		event.m_collidableAccept = HK_COLLIDABLE_REJECT;
	}
}

void hkpRejectRayChassisListener::collidableRemovedCallback( const hkpCollidableRemovedEvent& event )
{
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
