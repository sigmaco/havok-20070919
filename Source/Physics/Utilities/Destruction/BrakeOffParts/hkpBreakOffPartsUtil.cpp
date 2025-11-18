/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Destruction/BrakeOffParts/hkpBreakOffPartsUtil.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/Modifiers/hkpRemoveTerminalsMoppModifier.h>



hkpBreakOffPartsUtil::hkpBreakOffPartsUtil(hkpWorld* world, hkpBreakOffPartsListener* listenerInterface )
{
	m_world = world;
	m_breakOffPartsListener = listenerInterface;
	this->addReference();
	world->addContactImpulseLimitBreachedListener( this );
	world->addWorldDeletionListener( this );
	world->addEntityListener( this );
	m_criticalSection = new hkCriticalSection(1);
}

hkpBreakOffPartsUtil::~hkpBreakOffPartsUtil()
{
	if ( m_world )
	{
		m_world->removeContactImpulseLimitBreachedListener(this);
		m_world->removeEntityListener(this);
		m_world->removeWorldDeletionListener(this);
	}

	for ( int i =0; i < m_limitImpulseUtils.getSize(); i++ )
	{
		LimitContactImpulseUtil* util = m_limitImpulseUtils[i];
		util->m_entity->removeCollisionListener(util);
		util->m_entity->m_breakOffPartsUtil = HK_NULL;
		util->removeReference();
	}
	delete m_criticalSection;
}

void hkpBreakOffPartsUtil::removeKeysFromListShape( hkpEntity* entity, hkpShapeKey* keysToRemove, int numKeys)
{
	hkAabbUint32* childAabbs = entity->getCollidable()->m_boundingVolumeData.m_childShapeAabbs;
	const hkpShape* shape = entity->getCollidable()->getShape();

	switch( shape->getType() )
	{
		case HK_SHAPE_LIST:
doListShape:
			{
				hkpListShape* list = const_cast<hkpListShape*>(static_cast<const hkpListShape*>(shape));
				for (int i = 0; i < numKeys; i++ )
				{
					list->disableChild( keysToRemove[i] );
				}
				HK_ASSERT2( 0xf0345465, !childAabbs || entity->getCollidable()->m_boundingVolumeData.m_numChildShapeAabbs == list->getNumChildShapes(), "The cached number of child shapes is invalid" );
				break;
			}

		case HK_SHAPE_MOPP:
			{
				hkpMoppBvTreeShape* moppShape = const_cast<hkpMoppBvTreeShape*>(static_cast<const hkpMoppBvTreeShape*>( shape ));
				const hkpShapeCollection* collection = moppShape->getShapeCollection();
				hkArray<hkpShapeKey> keys(keysToRemove,numKeys,numKeys);

				hkpRemoveTerminalsMoppModifier modifier(moppShape->getMoppCode(), collection, keys);
				modifier.applyRemoveTerminals( const_cast<hkpMoppCode*>(moppShape->getMoppCode()) );

				if ( collection->getType() == HK_SHAPE_LIST )
				{
					shape = collection;
					goto doListShape;
				}
				break;
			}
		default:
			HK_ASSERT2( 0xf02efe56, 0, "Unsupported shape type" );
			return;
	}

	// disable cached aabbs in the entity
	if ( childAabbs )
	{
		for (int i = 0; i < numKeys; i++ )
		{
			hkAabbUint32& aabb = childAabbs[ keysToRemove[i] ];
			aabb.setInvalidY();
		}
	}
}

void hkpBreakOffPartsUtil::worldDeletedCallback( hkpWorld* world)
{
	m_world->removeContactImpulseLimitBreachedListener(this);
	m_world = HK_NULL;
	removeReference();
}

void hkpBreakOffPartsUtil::entityRemovedCallback( hkpEntity* entity )
{
	hkpBreakOffPartsUtil::LimitContactImpulseUtil* util = static_cast<hkpBreakOffPartsUtil::LimitContactImpulseUtil*>(entity->m_breakOffPartsUtil);
	if ( util )
	{
		entity->m_breakOffPartsUtil = HK_NULL;
		int index = m_limitImpulseUtils.indexOf( util );
		m_limitImpulseUtils.removeAt(index);
		util->removeReference();
	}
}

hkpBreakOffPartsUtil::LimitContactImpulseUtil::LimitContactImpulseUtil( hkpBreakOffPartsUtil* breakUtil, hkpEntity* entity ): m_entity( entity), m_breakOffPartsUtil(breakUtil)
{
	HK_ASSERT2( 0xf0323454, entity->m_breakOffPartsUtil == HK_NULL, "The m_breakOffPartsUtil util member in hkpEntity::m_collidable is already in use" );
	entity->m_breakOffPartsUtil = this;
	m_maxImpulse.m_value = hkUFloat8::MAX_VALUE-1;
}

hkpBreakOffPartsUtil::LimitContactImpulseUtil* hkpBreakOffPartsUtil::getUtil( hkpEntity* entity )
{
	// search entry for entity
	LimitContactImpulseUtil* limitUtil = HK_NULL;
	{
		for ( int i = 0; i < m_limitImpulseUtils.getSize(); i++)
		{
			LimitContactImpulseUtil* u = m_limitImpulseUtils[i];
			if ( u->m_entity == entity )
			{
				limitUtil = u;
				break;
			}
		}
	}
	if ( !limitUtil )
	{
		limitUtil = new LimitContactImpulseUtil( this, entity );
		m_limitImpulseUtils.pushBack(limitUtil);
		entity->addCollisionListener( limitUtil );
	}
	return limitUtil;
}

void hkpBreakOffPartsUtil::markPieceBreakable( hkpEntity* entity, hkpShapeKey key, hkReal maxImpulse )
{
	HK_ASSERT2 ( 0xf0ffee34, entity->m_numUserDatasInContactPointProperties >= 1, "You have to set hkpEntity::m_numUserDatasInContactPointProperties to a minimum of 1 " );
	LimitContactImpulseUtil* limitUtil = getUtil( entity );
	hkUFloat8 mf = maxImpulse;
	limitUtil->setMaxImpulseForShapeKey(key, mf.m_value);
}
void hkpBreakOffPartsUtil::markEntityBreakable( hkpEntity* entity, hkReal maxImpulse )
{
	LimitContactImpulseUtil* limitUtil = getUtil( entity );
	hkUFloat8 mf = maxImpulse;
	limitUtil->m_maxImpulse = mf;
}


void hkpBreakOffPartsUtil::LimitContactImpulseUtil::contactPointAddedCallback(	hkpContactPointAddedEvent& event )
{
	hkpShapeKey key = event.m_bodyA->m_shapeKey;
	if ( m_entity->getCollidable() != event.m_bodyA->getRootCollidable() )
	{
		key = event.m_bodyB->m_shapeKey;
	}

	hkUFloat8 maxImpulse; maxImpulse.m_value = getMaxImpulseForKey(key);
	if ( !maxImpulse.m_value )
	{
		if ( m_maxImpulse.m_value == hkUFloat8::MAX_VALUE-1 )
		{
			// piece is not flagged
			return;
		}
		maxImpulse = m_maxImpulse;
		key = HK_INVALID_SHAPE_KEY;
	}

	// if the piece is flagged to be breakable, than take the one with lower force
	if ( event.m_contactPointProperties->m_maxImpulse.m_value )
	{
		// integer compare is faster
		if ( maxImpulse.m_value >= event.m_contactPointProperties->m_maxImpulse.m_value )
		{
			return;	// existing limits is already lower than my one
		}
	}

	event.m_contactPointProperties->setMaxImpulsePerStep( maxImpulse );

		// find out whether we are object A or B in the hkConstraint
	HK_ASSERT2( 0xf023ef45, event.m_internalContactMgr->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR, "This utility only works with the default contact mgr");
	hkpSimpleConstraintContactMgr* mgr = reinterpret_cast<hkpSimpleConstraintContactMgr*>(event.m_internalContactMgr);
	if ( mgr->m_constraint.getEntityA() != m_entity )
	{
		event.m_contactPointProperties->m_flags |= hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID;
	}
	else
	{
		event.m_contactPointProperties->m_flags &= ~hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID;
	}
}

static inline hkpBreakOffPartsUtil::LimitContactImpulseUtil* findUtil( const hkpContactImpulseLimitBreachedListenerInfo& bi, hkpContactPointProperties* props, hkBool& defaultValueHitOut, hkpShapeKey& key, hkUFloat8& maxImpulseOut )
{
	int id = unsigned(props->m_flags & hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID) / unsigned(hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID);
	hkpSimpleConstraintContactMgr* mgr = bi.getContactMgr();

	hkpBreakOffPartsUtil::LimitContactImpulseUtil* util = (hkpBreakOffPartsUtil::LimitContactImpulseUtil*)mgr->m_constraint.getEntity(id)->m_breakOffPartsUtil;

	int maxImpulse = props->m_maxImpulse.m_value;
	maxImpulseOut.m_value = hkInt8(maxImpulse);

	if ( !util )
	{
		return HK_NULL;
	}

	const hkpSimpleContactConstraintAtom* atom = mgr->getAtom();
	key = props->getExtendedUserData(atom, id, 0);
	{
		// lets find the object
		int maxA = util->getMaxImpulseForKey(key);
		if ( maxA == maxImpulse )
		{
			return util;
		}
	}
	if ( util->m_maxImpulse.m_value == maxImpulse )
	{
		defaultValueHitOut = true;
		return util;
	}
	return HK_NULL;
}

void hkpBreakOffPartsUtil::contactImpulseLimitBreachedCallback( const hkpContactImpulseLimitBreachedListenerInfo* breachedContacts, int numBreachedContacts )
{
	for (int i =0; i < numBreachedContacts; i++)
	{
		const hkpContactImpulseLimitBreachedListenerInfo& bi = breachedContacts[i];
		hkpRigidBody* breakingBody;
		hkpRigidBody* collidingBody;
		hkpPhysicsSystem newSystem;
		hkContactPoint* contactPoint = bi.getContactPoint();
		hkUFloat8 maxImpulse;

		//
		//	Single Threaded Section
		//
		{
			hkCriticalSectionLock lock(m_criticalSection);
			// get the shape key
			hkpShapeKey key;;

			// get the breakable object. This can be tricky if both objects are breakable.
			hkBool defaultValueHit = false;
			hkpContactPointProperties* props = bi.getContactPointProperties();
			hkpBreakOffPartsUtil::LimitContactImpulseUtil* util = findUtil( bi, props, defaultValueHit, key, maxImpulse );

			if ( !util )
			{
				continue;	// already removed
			}


			hkInplaceArray<hkpShapeKey,256> keysToRemove;

			breakingBody  = (hkpRigidBody*)util->m_entity;
			collidingBody = hkSelectOther( breakingBody, bi.getBodyA(), bi.getBodyB() );

			hkpBreakOffPartsListener::ContactImpulseLimitBreachedEvent event;

			event.m_breakingBody = breakingBody;
			event.m_collidingBody = collidingBody;
			event.m_brokenPieceKey = key;
			event.m_contactPoint = contactPoint;
			event.m_properties     = bi.getContactPointProperties();

			hkResult result = m_breakOffPartsListener->breakOffSubPart( event,	keysToRemove, newSystem  );

			if ( result == HK_FAILURE)
			{
				continue;	// don't break it off
			}

			// remove keys 
			for (int k = 0; k < keysToRemove.getSize(); k++)	{ util->removeKey( keysToRemove[k] );	}	
			if ( defaultValueHit  )                             { util->m_maxImpulse.m_value = hkUFloat8::MAX_VALUE-1; }
		}

		//
		//	Multi Threaded Section
		//

		// remove keys and update broken body
		{

			// if we have a toi, we have to recollide our current pair
			if ( bi.isToi() )
			{
				if ( !breakingBody->isFixed() )
				{
					// redo all collisions of the breaking moving body
					m_world->reintegrateAndRecollideEntities( (hkpEntity**)&breakingBody, 1, hkpWorld::RR_MODE_RECOLLIDE_NARROWPHASE );
				}
				else
				{
					// just update the pair (as soon as havok supports it) : m_world->recollideTwoEntities( breakingBody, collidingBody ); // implement this
					// For the time being we simply update the moving body (the fixed body might be huge and would give us 
					// an incredible CPU spike).
					// As a caveat there
					// might be still TOIs scheduled for the fixed breakingBody and another object.
					// In this case we just let this false TOI happen.
					m_world->reintegrateAndRecollideEntities( (hkpEntity**)&collidingBody, 1, hkpWorld::RR_MODE_RECOLLIDE_NARROWPHASE );
				}
			}
			else
			{
				// disable contact. This is only necessary if we this function is called 
				// from a simple collision response, which happens before solving. In this case
				// the contact point will still get into the solver, so we simple disable it by setting
				// the distance to infinity
				contactPoint->setDistance( HK_REAL_MAX * 0.5f );
			}
		}


		// add the new bodies
		{
			const hkArray<hkpRigidBody*>& newBodies = newSystem.getRigidBodies();
			if ( newBodies.getSize() )
			{
				m_world->addPhysicsSystem( &newSystem );
// instead we want to do collision detection if we're in a multithreded mode
// -- as in that case, the bodies don't get added to the world before the collision detection phase.
				//m_world->reintegrateAndRecollideEntities( (hkpEntity**)newBodies.begin(), newBodies.getSize() );	
			}
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
