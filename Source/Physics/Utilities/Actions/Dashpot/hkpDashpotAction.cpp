/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/Utilities/Actions/Dashpot/hkpDashpotAction.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpDashpotAction::hkpDashpotAction(hkpRigidBody* entityA, hkpRigidBody* entityB , hkUlong userData ) 
: hkpBinaryAction( entityA, entityB, userData ),
  m_strength(0.1f),
  m_damping(0.01f)
{
	m_point[0].setZero4();
	m_point[1].setZero4();
}

const hkVector4 & hkpDashpotAction::getImpulse()
{
	return m_impulse;
}


void hkpDashpotAction::applyAction(const hkStepInfo& stepInfo)
{
	HK_TIMER_BEGIN("Dashpot", HK_NULL);

	const hkReal dtscale = 151; // to keep constants sensible around 1
	hkReal dt = dtscale * (stepInfo.m_deltaTime);
	
	hkpRigidBody* ra = static_cast<hkpRigidBody*>( m_entityA );
	hkpRigidBody* rb = static_cast<hkpRigidBody*>( m_entityB );
	HK_ASSERT2(0xf568efca, ra && rb, "Bodies not set in dashpot.");

	hkVector4 pa;

	pa.setTransformedPos(ra->getTransform(),m_point[0]);
	const hkVector4& va = ra->getLinearVelocity();

	hkVector4 pb;

	pb.setTransformedPos(rb->getTransform(),m_point[1]);
	const hkVector4& vb = rb->getLinearVelocity();

	//m_impulse = (dt * m_strength) * ( pa - pb ) +  * ( va - vb ) Below
    {
      hkVector4 pab;
	  hkVector4 vab;
	
	  pab.setSub4(pa,pb);
	  vab.setSub4(va,vb);

	  m_impulse.setMul4(dt * m_strength, pab);
	  vab.mul4(dt * m_damping);
	  m_impulse.add4(vab);
	}

	/*
	DISPLAY2(showPoint,	pa, 0xffffffff );
	DISPLAY2(showPoint,	pb, 0xffffffff );
	DISPLAY3(showLine,	pb, pb+m_impulse,	0xffff0000 );
    */

	{ 
		hkVector4 negImpulse;
		negImpulse.setMul4(-1,m_impulse);
		ra->applyPointImpulse(negImpulse, pa); 
	}
	
	{ 
		rb->applyPointImpulse( m_impulse, pb); 
	}

	HK_TIMER_END();
}

// hkpAction clone interface.
hkpAction* hkpDashpotAction::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{
	HK_ASSERT2(0xf568efca, newEntities.getSize() == 2, "Wrong clone parameters given to a spring action (needs 2 bodies).");
	// should have two entities as we are a binary action.
	if (newEntities.getSize() != 2) return HK_NULL;

	HK_ASSERT2(0x736ad5a4, newPhantoms.getSize() == 0, "Wrong clone parameters given to a spring action (needs 0 phantoms).");
	// should have no phantoms.
	if (newPhantoms.getSize() != 0) return HK_NULL;

	hkpDashpotAction* sa = new hkpDashpotAction( (hkpRigidBody*)newEntities[0], (hkpRigidBody*)newEntities[1], m_userData );
	sa->m_point[0] = m_point[0];
	sa->m_point[1] = m_point[1];
	sa->m_strength = m_strength;
	sa->m_damping = m_damping;
	sa->m_impulse = m_impulse;

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
