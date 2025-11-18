/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


// on spu we simply do not care about modular code design and simply include this file here
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>


hkContactPointId hkpContactMgr::addContactPoint( const hkpCdBody& a, const hkpCdBody& b, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& output, const hkpGskCache* contactCache, hkContactPoint& cp )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	return scm->addContactPointImpl( a, b, input, output, contactCache, cp );
}

hkResult hkpContactMgr::reserveContactPoints( int numPoints )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	return scm->hkpSimpleConstraintContactMgr::reserveContactPointsImpl( numPoints );
}

void hkpContactMgr::removeContactPoint( hkContactPointId cpId, hkCollisionConstraintOwner& constraintOwner )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	scm->hkpSimpleConstraintContactMgr::removeContactPointImpl( cpId, constraintOwner );
}

void hkpContactMgr::processContact( const hkpCollidable& a, const hkpCollidable& b, const hkpProcessCollisionInput& input, hkpProcessCollisionData& collisionData )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	scm->hkpSimpleConstraintContactMgr::processContactImpl( a, b, input, collisionData );
}

hkpContactMgr::ToiAccept hkpContactMgr::addToi( const hkpCdBody& a, const hkpCdBody& b, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& output, hkTime toi, hkContactPoint& cp, const hkpGskCache* gskCache, hkReal& projectedVelocity, hkpContactPointProperties& propertiesOut )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	return scm->hkpSimpleConstraintContactMgr::addToiImpl( a, b, input, output, toi, cp, gskCache, projectedVelocity, propertiesOut  );
}

void hkpContactMgr::removeToi( const hkpCollidable& a, const hkpCollidable& b, class hkCollisionConstraintOwner& constraintOwner, hkpContactPointProperties& properties )
{
	hkpSimpleConstraintContactMgr* scm = static_cast<hkpSimpleConstraintContactMgr*>( this );
	scm->hkpSimpleConstraintContactMgr::removeToiImpl( a, b, constraintOwner, properties );
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
