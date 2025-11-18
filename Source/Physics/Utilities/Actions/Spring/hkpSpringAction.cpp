/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Actions/Spring/hkpSpringAction.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpSpringAction::hkpSpringAction( hkpRigidBody* entityA , hkpRigidBody* entityB , hkUlong userData )
: hkpBinaryAction( entityA, entityB, userData ),
  m_restLength(1.0f),
  m_strength(1000.0f),
  m_damping(0.1f),
  m_onCompression(true),
  m_onExtension(true)
{
}

void hkpSpringAction::setPositionsInWorldSpace( const hkVector4& pivotA, const hkVector4& pivotB )
{
	hkpRigidBody* rbA = static_cast<hkpRigidBody*>( m_entityA );
	hkpRigidBody* rbB = static_cast<hkpRigidBody*>( m_entityB );
	HK_ASSERT2(0xf568efca, rbA && rbB, "Bodies not set in spring.");

	m_positionAinA.setTransformedInversePos(rbA->getTransform(),pivotA);
	m_positionBinB.setTransformedInversePos(rbB->getTransform(),pivotB);
	hkVector4 dist;
	dist.setSub4(pivotA,pivotB);
	m_restLength = dist.length3();
}

void hkpSpringAction::setPositionsInBodySpace( const hkVector4& pivotA, const hkVector4& pivotB )
{
	hkpRigidBody* rbA = static_cast<hkpRigidBody*>( m_entityA );
	hkpRigidBody* rbB = static_cast<hkpRigidBody*>( m_entityB );
	HK_ASSERT2(0xf568efca, rbA && rbB, "Bodies not set in spring.");

	m_positionAinA = pivotA;
	m_positionBinB = pivotB;

	hkVector4 dist;
	hkVector4 pivotAW;
	hkVector4 pivotBW;

	// transform point to world space
	pivotAW.setTransformedPos(rbA->getTransform(),pivotA);
	pivotBW.setTransformedPos(rbB->getTransform(),pivotB);
	dist.setSub4(pivotAW,pivotBW);
	m_restLength = dist.length3();
}

void hkpSpringAction::applyAction( const hkStepInfo& stepInfo )
{
	hkpRigidBody* ra = static_cast<hkpRigidBody*>( m_entityA );
	hkpRigidBody* rb = static_cast<hkpRigidBody*>( m_entityB );
	HK_ASSERT2(0xf568efca, ra && rb, "Bodies not set in spring.");

	hkVector4 posA;
	posA.setTransformedPos( ra->getTransform(), m_positionAinA );
	hkVector4 posB;
	posB.setTransformedPos( rb->getTransform(), m_positionBinB );

	hkVector4 dirAB; dirAB.setSub4( posB, posA );

	hkReal	length = dirAB.length3();
	if( length < 0.001f )	// can't normalize the zero vector!
	{
		// what if rest length is not zero?
		return;
	}

	// normalise
	dirAB.mul4( 1.0f / length );

	{
		if( !m_onCompression && (length < m_restLength) )
		{
			return;
		}
		if( !m_onExtension && (length > m_restLength) )
		{
			return;
		}

		hkVector4 velA;
		ra->getPointVelocity( posA, velA );
        hkVector4 velB;
		rb->getPointVelocity( posB, velB );
		hkVector4 velAB;
		velAB.setSub4( velB, velA );

		hkReal relVel = velAB.dot3( dirAB );

		hkReal force = (relVel * m_damping) + ((length - m_restLength) * m_strength);

		m_lastForce.setMul4( -force, dirAB );
		rb->applyForce( stepInfo.m_deltaTime, m_lastForce, posB );

		m_lastForce.setMul4( force, dirAB );
		ra->applyForce( stepInfo.m_deltaTime, m_lastForce, posA );
	}
}

hkpAction* hkpSpringAction::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{
	HK_ASSERT2(0xf568efca, newEntities.getSize() == 2, "Wrong clone parameters given to a spring action (needs 2 bodies).");
	// should have two entities as we are a binary action.
	if (newEntities.getSize() != 2) return HK_NULL;

	HK_ASSERT2(0x58828b7c, newPhantoms.getSize() == 0, "Wrong clone parameters given to a spring action (needs 0 phantoms).");
	// should have no phantoms.
	if (newPhantoms.getSize() != 0) return HK_NULL;
	
	hkpSpringAction* sa = new hkpSpringAction( (hkpRigidBody*)newEntities[0], (hkpRigidBody*)newEntities[1], m_userData );
	sa->m_positionAinA = m_positionAinA;
	sa->m_positionBinB = m_positionBinB;
	sa->m_restLength = m_restLength;
	sa->m_strength = m_strength;
	sa->m_damping = m_damping;
	sa->m_onCompression = m_onCompression;
	sa->m_onExtension = m_onExtension;

	return sa;
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
