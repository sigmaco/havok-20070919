/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
//#include <hkcollide/hkpCollide.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Collide/Agent/Collidable/hkpCdPoint.h>
#include <Physics/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Physics/Collide/Agent/Query/hkpCdBodyPairCollector.h>

#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

#include <Physics/Collide/Agent/hkpCollisionAgentConfig.h>

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics/Internal/UnitTest/Agent/Gjk/hkpGjkConvexConvexAgent.h>
#include <Physics/Internal/Collide/Gjk/hkpGjk.h>



void HK_CALL hkpGjkConvexConvexAgent::registerAgent(hkpCollisionDispatcher* dispatcher)
{
	hkpCollisionDispatcher::AgentFuncs af;
	af.m_createFunc          = createConvexConvexAgent;
	af.m_getPenetrationsFunc  = staticGetPenetrations;
	af.m_getClosestPointFunc = staticGetClosestPoints;
	af.m_linearCastFunc      = staticLinearCast;
	af.m_isFlipped           = false;
	af.m_isPredictive		 = false;

	dispatcher->registerCollisionAgent( af, HK_SHAPE_CONVEX, HK_SHAPE_CONVEX);
}


hkpCollisionAgent* HK_CALL hkpGjkConvexConvexAgent::createConvexConvexAgent(	const hkpCdBody& bodyA, const hkpCdBody& bodyB, 
																const hkpCollisionInput& input, hkpContactMgr* contactMgr)
{
	hkpGjkConvexConvexAgent* agent = new hkpGjkConvexConvexAgent( contactMgr);
	return agent;
}


void hkpGjkConvexConvexAgent::cleanup( hkCollisionConstraintOwner& constraintOwner )
{
	hkpClosestPointManifold::cleanup( m_bridgeManifold.m_contactPoints, m_bridgeManifold.m_numPoints, m_contactMgr, constraintOwner );
	delete this;
}


hkBool hkpGjkConvexConvexAgent::getClosestPoint(  const hkpCdBody& bodyA,	const hkpCdBody& bodyB, const hkpCollisionInput& input,
											   struct hkpExtendedGskOut& output)

{
	const hkpConvexShape* shapeA = static_cast<const hkpConvexShape*>(bodyA.getShape());
	const hkpConvexShape* shapeB = static_cast<const hkpConvexShape*>(bodyB.getShape());

	hkBool foundPoint = false;
	HK_INTERNAL_TIMER_BEGIN( "gjk", this );
	{
		// Get the relative transform for the two bodies for the collision detector
		hkTransform aTb;	aTb.setMulInverseMul( bodyA.getTransform(), bodyB.getTransform());
	
		// Call the collision detector
		const hkpGskStatus gjkStatus = hkpGjk::GJK(shapeA, shapeB, aTb, m_cache, output);

		if(gjkStatus == HK_GSK_OK)
		{
			// convert contact normal to world space...
			
			output.m_normalInWorld.setRotatedDir( bodyA.getTransform().getRotation(), output.m_normalInA);

			const hkReal dist = output.m_distance - shapeA->getRadius() - shapeB->getRadius();
			output.m_distance = dist;

			if(output.m_distance < input.getTolerance())
			{
				//HK_ASSERT(0x1e376cff, (!input.m_config->m_useTims) || (m_oldNormal(3)<=0.f));
				
				// adjust the contact points by the radius
				output.m_pointAinA.addMul4(-shapeA->getRadius(), output.m_normalInA);
				hkVector4 pointBinA; pointBinA.setAddMul4( output.m_pointAinA, output.m_normalInA, -dist );
				output.m_pointBinB._setTransformedInversePos(aTb, pointBinA);
				foundPoint = true;
			} 
			else
			{
				m_oldNormal = output.m_normalInWorld;
				m_oldNormal(3) = dist;
			}
		}

	}
	HK_INTERNAL_TIMER_END();

	return foundPoint;
}

hkBool hkpGjkConvexConvexAgent::staticGetClosestPoint(  const hkpCdBody& bodyA,	const hkpCdBody& bodyB, const hkpCollisionInput& input,
												     hkpGjkCache& cache, struct hkpExtendedGskOut& output)

{
	HK_INTERNAL_TIMER_BEGIN( "gjk", this );

	const hkpConvexShape* shapeA = static_cast<const hkpConvexShape*>(bodyA.getShape());
	const hkpConvexShape* shapeB = static_cast<const hkpConvexShape*>(bodyB.getShape());

	hkBool foundPoint = false;
	{
		// Get the relative transform for the two bodies for the collision detector
		hkTransform aTb;	aTb.setMulInverseMul( bodyA.getTransform(), bodyB.getTransform());
	
		// Call the collision detector
		const hkpGskStatus gjkStatus = hkpGjk::GJK(shapeA, shapeB, aTb, cache, output);

		if(gjkStatus == HK_GSK_OK)
		{
			// convert contact normal to world space...
			output.m_normalInWorld.setRotatedDir( bodyA.getTransform().getRotation(), output.m_normalInA);

			const hkReal dist = output.m_distance - shapeA->getRadius() - shapeB->getRadius();
			output.m_distance = dist;

			if(output.m_distance < input.getTolerance())
			{
				// adjust the contact points by the radius
				output.m_pointAinA.addMul4(-shapeA->getRadius(), output.m_normalInA);
				hkVector4 pointBinA; pointBinA.setAddMul4( output.m_pointAinA, output.m_normalInA, -dist );
				output.m_pointBinB._setTransformedInversePos(aTb, pointBinA);

				foundPoint = true;
			} 
		}
	}
	HK_INTERNAL_TIMER_END();

	return foundPoint;
}


void hkpGjkConvexConvexAgent::processCollision(	const hkpCdBody& bodyA,	const hkpCdBody& bodyB, 
												const hkpProcessCollisionInput& input,	hkpProcessCollisionOutput& result)
{
	HK_ASSERT2(0x2eb06fae,  m_contactMgr, HK_MISSING_CONTACT_MANAGER_ERROR_TEXT );

	HK_TIMER_BEGIN( "gjk", HK_NULL );

	hkVector4 timInfo;
	hkSweptTransformUtil::calcTimInfo( *bodyA.getMotionState(), *bodyB.getMotionState(), input.m_stepInfo.m_deltaTime, timInfo);

	if ( m_oldNormal(3) > input.getTolerance() )
	{
		m_oldNormal(3) -= timInfo.dot4xyz1( m_oldNormal );
		if ( m_oldNormal(3) > input.getTolerance() )
		{
			goto END;
		}
	}

	{
		hkpExtendedGskOut output;

		if( getClosestPoint(bodyA,bodyB, input, output) )
		{
			hkpClosestPointManifold::addPoint( bodyA, bodyB, input, result, output, input.getTolerance(), m_contactMgr, *result.m_constraintOwner.val(), m_bridgeManifold.m_contactPoints, m_bridgeManifold.m_numPoints );

			const hkReal epsilon = .001f;
			hkpClosestPointManifold::getPoints( bodyA, bodyB, input, output.m_distance - epsilon, m_bridgeManifold.m_contactPoints, m_bridgeManifold.m_numPoints, result, m_contactMgr, *result.m_constraintOwner.val() ); 
		}
		else
		{
			m_bridgeManifold.cleanup( m_bridgeManifold.m_contactPoints, m_bridgeManifold.m_numPoints, m_contactMgr, *result.m_constraintOwner.val() );
		}
	}
END:
	HK_TIMER_END();
}


void hkpGjkConvexConvexAgent::getClosestPoints(	const hkpCdBody& bodyA,	const hkpCdBody& bodyB, 
						const hkpCollisionInput& input,		hkpCdPointCollector& pointDetails)
{
	HK_TIMER_BEGIN("gjk", HK_NULL);

	hkpExtendedGskOut output;

	if( staticGetClosestPoint(bodyA, bodyB, input, m_cache, output) )
	{
		hkpCdPoint event( bodyA, bodyB );

		event.m_contact.getPosition()._setTransformedPos( bodyB.getTransform(), output.m_pointBinB );
		event.m_contact.setSeparatingNormal( output.m_normalInWorld, output.m_distance );

		pointDetails.addCdPoint( event );
	}

	HK_TIMER_END();
}

void hkpGjkConvexConvexAgent::staticGetClosestPoints(	const hkpCdBody& bodyA,	const hkpCdBody& bodyB, 
						const hkpCollisionInput& input,		hkpCdPointCollector& pointDetails)
{
	HK_TIMER_BEGIN("cvx cvx", HK_NULL);

	hkpExtendedGskOut output;
	hkpGjkCache cache;

	if( staticGetClosestPoint(bodyA, bodyB, input, cache, output) )
	{
		hkpCdPoint event( bodyA, bodyB );

		event.m_contact.getPosition()._setTransformedPos( bodyB.getTransform(), output.m_pointBinB );
		event.m_contact.setSeparatingNormal( output.m_normalInWorld, output.m_distance );

		pointDetails.addCdPoint( event );
	}

	HK_TIMER_END();
}


void hkpGjkConvexConvexAgent::getPenetrations(const  hkpCdBody& bodyA,const 	hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector )
{
	HK_TIMER_BEGIN("cvx cvx", HK_NULL);

	const hkpConvexShape* shapeA = static_cast<const hkpConvexShape*>(bodyA.getShape());
	const hkpConvexShape* shapeB = static_cast<const hkpConvexShape*>(bodyB.getShape());
	

	// Get the relative transform for the two bodies for the collision detector
	hkTransform aTb;
	aTb.setMulInverseMul( bodyA.getTransform(), bodyB.getTransform());

	// Call the collision detector
	hkpGskOut output;
	hkpGskStatus gjkStatus = hkpGjk::GJK(shapeA, shapeB, aTb, m_cache, output);

	HK_TIMER_END();

	if(gjkStatus == HK_GSK_OK)
	{
		const hkReal dist = output.m_distance - shapeA->getRadius() - shapeB->getRadius();
		if ( dist < 0.0f )
		{
			collector.addCdBodyPair( bodyA, bodyB );
		}
	}
}


void hkpGjkConvexConvexAgent::staticGetPenetrations(const  hkpCdBody& bodyA,const 	hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector )
{
	HK_TIMER_BEGIN("cvx cvx", HK_NULL);

	const hkpConvexShape* shapeA = static_cast<const hkpConvexShape*>(bodyA.getShape());
	const hkpConvexShape* shapeB = static_cast<const hkpConvexShape*>(bodyB.getShape());
	

	// Get the relative transform for the two bodies for the collision detector
	hkTransform aTb;
	aTb.setMulInverseMul( bodyA.getTransform(), bodyB.getTransform());


	// Call the collision detector

	hkpGskOut output;
	hkpGjkCache cache;
	hkpGskStatus gjkStatus = hkpGjk::GJK(shapeA, shapeB, aTb, cache, output);

	HK_TIMER_END();

	if(gjkStatus == HK_GSK_OK)
	{
		const hkReal dist = output.m_distance - shapeA->getRadius() - shapeB->getRadius();
		if ( dist < 0.0f )
		{
			collector.addCdBodyPair( bodyA, bodyB );
		}
	}
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
