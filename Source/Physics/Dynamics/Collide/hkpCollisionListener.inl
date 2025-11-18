/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

inline hkpContactPointAddedEvent::hkpContactPointAddedEvent(	hkpDynamicsContactMgr* contactMgr,
															const hkpProcessCollisionInput* collisionInput,
															hkpProcessCollisionOutput* collisionOutput,
															const hkpCdBody* a,	const hkpCdBody* b,
															hkContactPoint* ccp, 
															const hkpGskCache* gskCache,
															hkpContactPointProperties* dcp, 
															hkReal projectedVelocity,
															Type pointType )

:	m_bodyA( a ),
	m_bodyB( b ),
	m_type( pointType ),
	m_contactPoint( ccp ),
	m_gskCache(gskCache),
	m_contactPointProperties( dcp ),
	m_projectedVelocity( projectedVelocity ),
	m_internalContactMgr( contactMgr ),
	m_collisionInput( collisionInput ),
	m_collisionOutput( collisionOutput )
{
	m_status = HK_CONTACT_POINT_ACCEPT;
}

inline hkpToiPointAddedEvent::hkpToiPointAddedEvent(	hkpDynamicsContactMgr* contactMgr,	
													const hkpProcessCollisionInput* collisionInput,
													hkpProcessCollisionOutput* collisionOutput,
													const hkpCdBody* a,	const hkpCdBody* b, 
													hkContactPoint* cp,  const hkpGskCache* gskCache, hkpContactPointProperties* cpp, 
													hkTime toi, hkReal projectedVelocity)
	:   hkpContactPointAddedEvent(  contactMgr, collisionInput, collisionOutput, a, b, cp, gskCache, cpp, projectedVelocity, TYPE_TOI), m_toi(toi)
{
}

inline hkpManifoldPointAddedEvent::hkpManifoldPointAddedEvent(	hkContactPointId contactPointId, 
																hkpDynamicsContactMgr* contactMgr,	
																const hkpProcessCollisionInput* collisionInput,
																hkpProcessCollisionOutput* collisionOutput,
																const hkpCdBody* a,	const hkpCdBody* b, 
																hkContactPoint* cp,   const hkpGskCache* gskCache, hkpContactPointProperties* cpp, 
																hkReal projectedVelocity)
	:   hkpContactPointAddedEvent(  contactMgr, collisionInput, collisionOutput, a, b, cp, gskCache, cpp, projectedVelocity, TYPE_MANIFOLD ), m_contactPointId( contactPointId )
{
	m_nextProcessCallbackDelay = 0;
}

inline hkpContactPointConfirmedEvent::hkpContactPointConfirmedEvent(	hkpContactPointAddedEvent::Type type,
																	const hkpCollidable* a, const hkpCollidable* b, 
																	const hkpSimpleContactConstraintData* data,
																	hkContactPoint* cp,	hkpContactPointProperties* cpp, 
																	hkReal rotateNormal,
																	hkReal projectedVelocity)
	:   m_collidableA(a), m_collidableB(b),
		m_contactPoint(cp),	m_contactPointProperties( cpp ),
		m_rotateNormal(rotateNormal),
		m_projectedVelocity( projectedVelocity ),
		m_type(type), m_contactData(data)
{
}

hkpContactPointRemovedEvent::hkpContactPointRemovedEvent(	hkContactPointId contactPointId, 
														hkpDynamicsContactMgr* contactMgr,	
														hkpConstraintOwner* constraintOwner,
														hkpContactPointProperties* prop, 
														hkpEntity* ca,	
														hkpEntity* cb)
	:	m_contactPointId(contactPointId),
		m_contactPointProperties(prop),
		m_entityA(ca),
		m_entityB(cb),
		m_internalContactMgr(contactMgr),
		m_constraintOwner( constraintOwner )
{
}

hkpContactProcessEvent::hkpContactProcessEvent( hkpDynamicsContactMgr* contactMgr, const hkpCollidable* ca, const hkpCollidable* cb, hkpProcessCollisionData* data)
	:	m_collidableA(ca),
		m_collidableB(cb),
		m_collisionData( data ),
		m_internalContactMgr(contactMgr)
{
}

inline hkBool hkpContactPointRemovedEvent::isToi()
{
	return m_contactPointId == HK_INVALID_CONTACT_POINT;
}

inline hkpToiPointAddedEvent& hkpContactPointAddedEvent::asToiEvent()
{
	HK_ASSERT2( 0xf043dea2, m_type == this->TYPE_TOI, "Invalid upcast from hkpContactPointAddedEvent to hkpToiPointAddedEvent" );
	return static_cast<hkpToiPointAddedEvent&>(*this);
}

inline hkBool hkpContactPointAddedEvent::isToi() const
{
	return m_type == this->TYPE_TOI;

}


inline hkpManifoldPointAddedEvent& hkpContactPointAddedEvent::asManifoldEvent()
{
	HK_ASSERT2( 0xf043dea2, m_type == this->TYPE_MANIFOLD, "Invalid upcast from hkpContactPointAddedEvent to hkpManifoldPointAddedEvent" );
	return static_cast<hkpManifoldPointAddedEvent&>(*this);
}

inline hkBool hkpContactPointConfirmedEvent::isToi() const 
{
	return m_type == hkpContactPointAddedEvent::TYPE_TOI;
}

hkpContactPointProperties* hkpContactPointAddedEvent::getContactPointProperties() 
{
	HK_ASSERT2(0xad8755aa, !isToi() && m_internalContactMgr->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
#if !defined (HK_PLATFORM_SPU)
	return m_contactPointProperties;
#else
	return (m_contactPointProperties.val());
#endif
}

#if ! defined (HK_PLATFORM_SPU)
int hkpContactPointAddedEvent::getExtendedUserDataBodyIndex( const hkpEntity* entity )
{
	HK_ASSERT2(0xad875caa, !isToi() && m_internalContactMgr->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
	const hkpSimpleConstraintContactMgr* mgr = static_cast<const hkpSimpleConstraintContactMgr*>(m_internalContactMgr);
	if ( mgr->m_constraint.getEntityA() == entity )
	{
		return 0;
	}
	return 1;
}


int hkpContactPointAddedEvent::getNumExtendedUserDatas(int bodyIdx) const 
{
	HK_ASSERT2(0xad8755aa, !isToi() && m_internalContactMgr->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR , "Unsupported manager or event type.");
	const hkpSimpleContactConstraintAtom* atom = static_cast<const hkpSimpleConstraintContactMgr*>(m_internalContactMgr)->getAtom();
	return m_contactPointProperties->getNumExtendedUserDatas(atom, bodyIdx);
}

hkUint32& hkpContactPointAddedEvent::getExtendedUserData(int bodyIdx, int i) 
{
	HK_ASSERT2(0xad8755aa, i < getNumExtendedUserDatas(bodyIdx), "Index out of range.");
	const hkpSimpleContactConstraintAtom* atom = static_cast<const hkpSimpleConstraintContactMgr*>(m_internalContactMgr)->getAtom();
	return m_contactPointProperties->getExtendedUserData(atom, bodyIdx, i);
}
#endif

hkpContactPointProperties* hkpContactPointConfirmedEvent::getContactPointProperties()
{
	HK_ASSERT2(0xad8755aa, !isToi() && getContactMgr()->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
	return m_contactPointProperties;
}

#if ! defined (HK_PLATFORM_SPU)
int hkpContactPointConfirmedEvent::getExtendedUserDataBodyIndex( const hkpEntity* entity )
{
	HK_ASSERT2(0xad87534a, !isToi() && getContactMgr()->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
	const hkpSimpleConstraintContactMgr* mgr = static_cast<const hkpSimpleConstraintContactMgr*>(getContactMgr());
	if ( mgr->m_constraint.getEntityA() == entity )
	{
		return 0;
	}
	return 1;
}

int hkpContactPointConfirmedEvent::getNumExtendedUserDatas(int bodyIdx) const
{
	HK_ASSERT2(0xad8755aa, !isToi() && getContactMgr()->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
	const hkpSimpleContactConstraintAtom* atom = static_cast<const hkpSimpleConstraintContactMgr*>(getContactMgr())->getAtom();
	return m_contactPointProperties->getNumExtendedUserDatas(atom, bodyIdx);
}

hkUint32& hkpContactPointConfirmedEvent::getExtendedUserData(int bodyIdx, int i) 
{
	HK_ASSERT2(0xad8755ab, !isToi() && getContactMgr()->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "Unsupported manager or event type.");
	HK_ASSERT2(0xad8755aa, i < getNumExtendedUserDatas(bodyIdx), "Index out of range.");
	const hkpSimpleContactConstraintAtom* atom = static_cast<const hkpSimpleConstraintContactMgr*>(getContactMgr())->getAtom();
	return m_contactPointProperties->getExtendedUserData(atom, bodyIdx, i);
}
#endif

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
