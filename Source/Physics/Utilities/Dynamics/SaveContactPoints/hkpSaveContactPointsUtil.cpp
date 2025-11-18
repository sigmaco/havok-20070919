/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSaveContactPointsUtil.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpPhysicsSystemWithContacts.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSaveContactPointsEndianUtil.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Agent/CompoundAgent/BvTreeStream/hkpBvTreeStreamAgent.h>
#include <Physics/Internal/Collide/Agent3/BoxBox/hkpBoxBoxAgent3.h>
#include <Physics/Internal/Collide/Agent3/CapsuleTriangle/hkpCapsuleTriangleAgent3.h>
#include <Physics/Internal/Collide/Agent3/PredGskAgent3/hkpPredGskAgent3.h>
#include <Physics/Internal/Collide/Agent3/PredGskCylinderAgent3/hkpPredGskCylinderAgent3.h>
#include <Physics/Internal/Collide/Agent3/List3/hkpListAgent3.h>
#include <Physics/Internal/Collide/Agent3/ConvexList3/hkpConvexListAgent3.h>
#include <Physics/Internal/Collide/Agent3/CollectionCollection3/hkpCollectionCollectionAgent3.h>
#include <Physics/Internal/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h>
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>
#include <Physics/Dynamics/World/Util/hkpWorldCallbackUtil.h>
#include <Physics/Dynamics/Entity/Util/hkpEntityCallbackUtil.h>

#include <Common/Base/Container/PointerMap/hkPointerMapBase.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>




void HK_CALL hkpSaveContactPointsUtil::saveContactPoints( const hkpSaveContactPointsUtil::SavePointsInput& input, const hkpWorld* world, hkpPhysicsSystemWithContacts* sys )
{ 
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );

	const hkArray<hkpSimulationIsland*>& aIslands = world->getActiveSimulationIslands();
	const hkArray<hkpSimulationIsland*>& iIslands = world->getInactiveSimulationIslands();

	hkArray<hkpSimulationIsland*> islands;
	islands = aIslands;
	islands.insertAt(islands.getSize(), iIslands.begin(), iIslands.getSize());

	for (int i = 0; i < islands.getSize(); i++)
	{
		HK_FOR_ALL_AGENT_ENTRIES_BEGIN( islands[i]->m_agentTrack, entry );
		{
			hkpSerializedAgentNnEntry* serializedEntry = new hkpSerializedAgentNnEntry(); 
			if ( HK_SUCCESS == serializeCollisionEntry(input, entry, world->getCollisionInput(), *serializedEntry) )
			{
				sys->addContact(serializedEntry);
			}
			serializedEntry->removeReference();
		}
		HK_FOR_ALL_AGENT_ENTRIES_END;
	}
} 

void HK_CALL hkpSaveContactPointsUtil::saveContactPoints( const hkpSaveContactPointsUtil::SavePointsInput& input, const hkpEntity** entities, int numEntities, hkpPhysicsSystemWithContacts* sys )
{
	hkpWorld* world = entities[0]->getWorld();
	HK_ASSERT2(0xad765dda, world, "Attempting to save contact points of an hkpEntity that's not in an hkpWorld.");

	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );

	// Build map of entities we're interested in
	hkPointerMapBase<hkUlong> processedCollidables; processedCollidables.reserve( numEntities );

	for (int e = 0; e < numEntities; e++)
	{
		processedCollidables.insert( hkUlong(entities[e]->getLinkedCollidable()), 0 );

		const hkArray<hkpLinkedCollidable::CollisionEntry>& collisionEntries = entities[e]->getLinkedCollidable()->m_collisionEntries;

		for (int c = 0; c < collisionEntries.getSize(); c++)
		{
			const hkpLinkedCollidable::CollisionEntry& entry = collisionEntries[c];
			hkPointerMapBase<hkUlong>::Iterator it = processedCollidables.findKey( hkUlong(entry.m_partner) );
			if (!processedCollidables.isValid(it))
			{
				hkpSerializedAgentNnEntry* serializedEntry = new hkpSerializedAgentNnEntry(); 
				if ( HK_SUCCESS == serializeCollisionEntry(input, entry.m_agentEntry, world->getCollisionInput(), *serializedEntry) )
				{
					sys->addContact(serializedEntry);
				}
				serializedEntry->removeReference();
			}
		}
	}
} 

void HK_CALL hkpSaveContactPointsUtil::saveContactPoints( const hkpSaveContactPointsUtil::SavePointsInput& input, const hkpAgentNnEntry** entries, int numEntries, hkpPhysicsSystemWithContacts* sys )
{
	hkpWorld* world = hkGetRigidBody(entries[0]->m_collidable[0])->getWorld();
	HK_ASSERT2(0xad765dda, world, "Attempting to save contact points of an hkpEntity that's not in an hkpWorld.");

	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );

	for (int e = 0; e < numEntries; e++)
	{
		hkpSerializedAgentNnEntry* serializedEntry = new hkpSerializedAgentNnEntry(); 
		if ( HK_SUCCESS == serializeCollisionEntry(input, entries[e], world->getCollisionInput(), *serializedEntry) )
		{
			sys->addContact(serializedEntry);
		}
		serializedEntry->removeReference();
	}
}




namespace {

class hkEntitySelectorAll : public hkpSaveContactPointsUtil::EntitySelector
{
	public:
		virtual hkBool32 isEntityOk(const hkpEntity* entity) { return true; }
};

class hkEntitySelectorListed : public hkpSaveContactPointsUtil::EntitySelector
{
	public:
		hkEntitySelectorListed(hkpEntity** entities, int numEntities)
		{
			// This is list of entities we're interested in.
			m_map.clear();
			m_map.reserve( numEntities );
			for (int e = 0; e < numEntities; e++)
			{
				m_map.insert(hkUlong(entities[e]), true);
			}
		}

		virtual hkBool32 isEntityOk(const hkpEntity* entity) 
		{
			return hkBool32( m_map.getWithDefault( hkUlong(entity), false ) );
		}

	private:
		hkPointerMapBase<hkUlong> m_map;
};

} // namespace


void HK_CALL hkpSaveContactPointsUtil::loadContactPointsInternal( const hkpSaveContactPointsUtil::LoadPointsInput& input, hkpPhysicsSystemWithContacts* sys, hkpWorld* world, hkpSaveContactPointsUtil::EntitySelector& selector )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	HK_ASSERT2(0xad85655d, !world->areCriticalOperationsLocked(), "Critical operations must be unlocked for loadingContactPoints.");

	world->lockCriticalOperations();

	hkArray<hkpSerializedAgentNnEntry*>& serializedEntries = sys->getContactsRw();
	for (int i = serializedEntries.getSize()-1; i >= 0; --i)
	{	
		hkpSerializedAgentNnEntry& serializedEntry = *serializedEntries[i];

		hkpEntity* entityA;
		hkpEntity* entityB;

		if (serializedEntry.m_useEntityIds)
		{
			entityA = input.m_getEntityFromId(serializedEntry.m_bodyAId);
			entityB = input.m_getEntityFromId(serializedEntry.m_bodyBId);
		}
		else
		{
			entityA = serializedEntry.m_bodyA;
			entityB = serializedEntry.m_bodyB;
		}

		hkpAgentNnEntry* entry = HK_NULL;

		if (entityA && entityB)
		{
			if (selector.isEntityOk(entityA) || selector.isEntityOk(entityB))
			{
				entry = hkAgentNnMachine_FindAgent(entityA->getLinkedCollidable(), entityB->getLinkedCollidable());
			}
		}

		if (entry)
		{
			if (serializedEntry.endianCheckUint32() != hkpSerializedAgentNnEntry::ENDIAN_CHECK_VALUE)
			{
				hkpSaveContactPointsEndianUtil::swapEndianTypeInCollisionEntry(world->getCollisionInput(), serializedEntry);
			}

			hkResult result = deserializeCollisionEntry(input, serializedEntry, entityA, entityB, world->getCollisionInput(), entry);
			HK_ASSERT2(0xad87666d, HK_SUCCESS == result, "Deserialization failed.");

			if (input.m_removeSerializedAgentsWhenLoaded && result)
			{
				serializedEntries[i]->removeReference();
				serializedEntries.removeAt(i);
			}
		}
	}

	world->unlockAndAttemptToExecutePendingOperations();
}


void HK_CALL hkpSaveContactPointsUtil::loadContactPoints( const hkpSaveContactPointsUtil::LoadPointsInput& input, hkpPhysicsSystemWithContacts* sys, hkpWorld* world )
{
	hkEntitySelectorAll selector;
	loadContactPointsInternal( input, sys, world, selector );
}

void HK_CALL hkpSaveContactPointsUtil::loadContactPoints( const hkpSaveContactPointsUtil::LoadPointsInput& input, hkpPhysicsSystemWithContacts* sys, hkpEntity** entities, int numEntities )
{
	hkpWorld* world = entities[0]->getWorld();
	HK_ASSERT2(0xad765dda, world, "Attempting to load contact points of an hkpEntity that's not in an hkpWorld.");

	hkEntitySelectorListed selector(entities, numEntities);
	loadContactPointsInternal( input, sys, world, selector );
}



hkResult HK_CALL hkpSaveContactPointsUtil::serializeCollisionEntry( const hkpSaveContactPointsUtil::SavePointsInput& input, const hkpAgentNnEntry* entry, const hkpProcessCollisionInput* collisionInput, hkpSerializedAgentNnEntry& serializedEntryOut )
{
	if (((hkpDynamicsContactMgr*)(entry->m_contactMgr))->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR &&
		((hkpSimpleConstraintContactMgr*)(entry->m_contactMgr))->m_contactConstraintData.m_atom->m_numContactPoints > 0 )
	{
		//
		// Serialize entry data
		//
		int sizeOfThisEntry;
		const hkpAgent1nTrack* dummyAgentTrack;
		const hkBool nnEntry = true;
		hkpSerializedAgentNnEntry::SerializedAgentType agentType;
		if (HK_SUCCESS == serializeEntry(entry, nnEntry, collisionInput, sizeOfThisEntry, agentType, dummyAgentTrack, serializedEntryOut.m_trackInfo))
		{
			HK_ASSERT2(0xad76454d, agentType != hkpSerializedAgentNnEntry::INVALID_AGENT_TYPE, "Ineternal error when serializing agents.");

			serializedEntryOut.m_agentType = agentType;

			// Copy entry content (for simple agents like boxbox, or predGsk)
			if (sizeOfThisEntry)
			{
				hkString::memCpy( serializedEntryOut.m_nnEntryData, entry, sizeOfThisEntry );
			}

			// Copy the contact constraint
			hkpSimpleConstraintContactMgr* mgr = (hkpSimpleConstraintContactMgr*)entry->m_contactMgr;

			// Copy id manager values.
			serializedEntryOut.m_cpIdMgr.setSize( mgr->m_contactConstraintData.m_idMgrA.m_values.getSize() );
			for (int vi = 0; vi < serializedEntryOut.m_cpIdMgr.getSize(); vi++ )
			{
				serializedEntryOut.m_cpIdMgr[vi] = mgr->m_contactConstraintData.m_idMgrA.m_values[vi];
			}

			{
				hkpSimpleContactConstraintAtom* const atom = mgr->m_contactConstraintData.m_atom;

				serializedEntryOut.m_propertiesStream.setSize(atom->m_numContactPoints * atom->getContactPointPropertiesStriding());
				hkString::memCpy(serializedEntryOut.m_propertiesStream.begin(), atom->getContactPointPropertiesStream(),atom->m_numContactPoints * atom->getContactPointPropertiesStriding());

				serializedEntryOut.m_contactPoints.setSize(atom->m_numContactPoints);
				hkString::memCpy(serializedEntryOut.m_contactPoints.begin(), atom->getContactPoints(),atom->m_numContactPoints * sizeof(hkContactPoint));
			}

			serializedEntryOut.m_atom = *mgr->m_contactConstraintData.m_atom;

			hkpRigidBody* bodyA = hkGetRigidBody(entry->m_collidable[0]);
			hkpRigidBody* bodyB = hkGetRigidBody(entry->m_collidable[1]);

			serializedEntryOut.m_useEntityIds = input.m_useEntityIds;

			if (serializedEntryOut.m_useEntityIds)
			{
				HK_ASSERT2(0xad87655d, input.m_getIdForEntity, "Callback function not specified.");
				serializedEntryOut.m_bodyAId = input.m_getIdForEntity(bodyA);
				serializedEntryOut.m_bodyBId = input.m_getIdForEntity(bodyB);
			}
			else
			{
				serializedEntryOut.m_bodyA = bodyA;
				serializedEntryOut.m_bodyB = bodyB;
				serializedEntryOut.m_bodyA->addReference();
				serializedEntryOut.m_bodyB->addReference();
			}

			return HK_SUCCESS;
		}
		else
		{
			//
			// Serialization failed -- delete partial serialization data
			//
			HK_WARN(0, "Contacts not saved");
			return HK_FAILURE;
		}

	}

	// Contact manager is not hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR or no contact points
	return HK_FAILURE;
}

hkResult HK_CALL hkpSaveContactPointsUtil::deserializeCollisionEntry( const LoadPointsInput& input, const hkpSerializedAgentNnEntry& serializedEntryIn, hkpEntity* entityA, hkpEntity* entityB, hkpProcessCollisionInput* collisionInput, hkpAgentNnEntry* entry )
{
	HK_ASSERT(0, ((hkpDynamicsContactMgr*)(entry->m_contactMgr))->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR);

	hkpSimpleConstraintContactMgr* mgr = static_cast<hkpSimpleConstraintContactMgr*>(entry->m_contactMgr);
	hkpConstraintOwner* constraintOwner;

	{
		hkpSimulationIsland* islandA = entityA->getSimulationIsland();
		hkpSimulationIsland* islandB = entityB->getSimulationIsland();

		if (islandA == islandB)
		{
			constraintOwner = islandA;
		}
		else if (entityA->isFixed())
		{
			// don't check whether the island is fixed, cause you'll get a cache miss on the fixed island :-/
			constraintOwner = islandB;
		}
		else if (entityB->isFixed())
		{
			constraintOwner = islandA;
		}
		else
		{
			HK_ASSERT2(0x0, false, "This shoudl never happen if this utility is used outside of the deltaStep");
			// find by the location of the existing entry
			constraintOwner = hkpWorldAgentUtil::getIslandFromAgentEntry(entry, islandA, islandB);
		}
	}

	// frist clear contact points in the entry
	if ( HK_SUCCESS == destroyOldEntry(serializedEntryIn.m_agentType, collisionInput, mgr, constraintOwner, entry) )
	{
		hkpEntity* entityAInActiveEntry = hkGetRigidBody(entry->getCollidableA());
		HK_ON_DEBUG(hkpEntity* entityBInActiveEntry = hkGetRigidBody(entry->getCollidableB()));
		if ( ( entityA != entityAInActiveEntry ) ) 
		{
			HK_ASSERT2(0XAD7644DA, ( ( entityA == entityBInActiveEntry ) && ( entityB == entityAInActiveEntry ) ), "AgentNnEntry corrupted.");
			// flip the collision entry around

			HK_ASSERT2(0xad87654a, !mgr->m_constraint.getOwner(), "The constraint should have been automatically removed when destroying the agent.");
			//if (mgr->m_constraint.getOwner())
			//{
			//	hkpWorldOperationUtil::removeConstraintImmediately(bodyA->getWorld(), &mgr->m_constraint );
			//}

			// do we want to call collision filters too ??
			// flip agent entities
			hkAlgorithm::swap(entry->m_collidable[0], entry->m_collidable[1]);
			hkAlgorithm::swap(entry->m_agentIndexOnCollidable[0], entry->m_agentIndexOnCollidable[1]);
			{
				// Flip constraint entities
				hkpSimpleConstraintContactMgr* mgr = static_cast<hkpSimpleConstraintContactMgr*>(entry->m_contactMgr);
				hkpConstraintInstance& c = mgr->m_constraint;
				hkAlgorithm::swap(c.m_entities[0], c.m_entities[1]);
				if (c.m_internal)
				{
					// Only flip internal when the constraint is in the world.
					hkAlgorithm::swap((hkUlong&)(c.m_internal->m_entities[0]), (hkUlong&)(c.m_internal->m_entities[1]));
					c.m_internal->m_whoIsMaster = ! c.m_internal->m_whoIsMaster;
					// slave index stays as it was
				}
			}
		}
		else
		{
			HK_ASSERT2(0XAD7644DA, entityB == hkGetRigidBody(entry->getCollidableB()), "AgentNnEntry corrupted.");
		}



		if (HK_SUCCESS == deserializeEntry(serializedEntryIn, serializedEntryIn.m_agentType, serializedEntryIn.m_trackInfo, collisionInput, entry))
		{
			mgr->m_contactConstraintData.m_idMgrA.m_values.setSize( serializedEntryIn.m_cpIdMgr.getSize() );
			for (int vi = 0; vi < mgr->m_contactConstraintData.m_idMgrA.m_values.getSize(); vi++ )
			{
				mgr->m_contactConstraintData.m_idMgrA.m_values[vi] = serializedEntryIn.m_cpIdMgr[vi];
			}


			if ( mgr->m_contactConstraintData.m_atom->m_numContactPoints == 0 )
			{
				hkpWorld* world = hkGetRigidBody(entry->m_collidable[0])->getWorld();
				world->blockExecutingPendingOperations(true);
				world->unlockCriticalOperations();
				hkpWorldOperationUtil::addConstraintImmediately(world, &mgr->m_constraint );
				world->lockCriticalOperations();
				world->blockExecutingPendingOperations(false);
			}

			{
				// This might be not needed anymore
				hkpConstraintInfo info; info.clear();
				mgr->m_contactConstraintData.m_atom->addToConstraintInfo(info);
				mgr->m_constraint.getMasterEntity()->getSimulationIsland()->subConstraintInfo( &mgr->m_constraint, info );
			}

			hkpSimpleContactConstraintAtomUtil::deallocateAtom( mgr->m_contactConstraintData.m_atom );

			HK_ASSERT2(0xad0966dd, serializedEntryIn.m_atom.m_numContactPoints > 0, "Desieralizing a constraint with no contacts.");

			const int numContactPoints = serializedEntryIn.m_atom.m_numContactPoints;
			mgr->m_contactConstraintData.m_atom = hkpSimpleContactConstraintAtomUtil::allocateAtom( serializedEntryIn.m_atom.m_numContactPoints, serializedEntryIn.m_atom.m_numUserDatasForBodyA, serializedEntryIn.m_atom.m_numUserDatasForBodyB, serializedEntryIn.m_atom.m_maxNumContactPoints );
			mgr->m_contactConstraintData.m_atom->m_numContactPoints = hkUint16(numContactPoints);
			mgr->m_contactConstraintData.m_atom->m_info = serializedEntryIn.m_atom.m_info;

			mgr->m_constraint.m_internal->m_atoms = mgr->m_contactConstraintData.m_atom;
			mgr->m_constraint.m_internal->m_atomsSize = mgr->m_contactConstraintData.m_atom->m_sizeOfAllAtoms;


			{
				hkpConstraintInfo info; info.clear();
				mgr->m_contactConstraintData.m_atom->addToConstraintInfo(info);
				mgr->m_constraint.getMasterEntity()->getSimulationIsland()->addConstraintInfo( &mgr->m_constraint, info );

			}

			hkString::memCpy(mgr->m_contactConstraintData.m_atom->getContactPointPropertiesStream(), serializedEntryIn.m_propertiesStream.begin(), numContactPoints * mgr->m_contactConstraintData.m_atom->getContactPointPropertiesStriding());
			hkString::memCpy(mgr->m_contactConstraintData.m_atom->getContactPoints(), serializedEntryIn.m_contactPoints.begin(), numContactPoints * sizeof(hkContactPoint));

			if (input.m_zeroUserDataInContactPointProperties)
			{
				hkpContactPointPropertiesStream* properties = mgr->m_contactConstraintData.m_atom->getContactPointPropertiesStream();
				const int propertiesStriding = mgr->m_contactConstraintData.m_atom->getContactPointPropertiesStriding();
				for (int i = 0; i < mgr->m_contactConstraintData.m_atom->m_numContactPoints; i++)
				{
					hkpContactPointProperties& property = *properties->asProperties();
					property.setUserData(0);
					properties = hkAddByteOffset(properties, propertiesStriding);
				}

			}

			//
			// Fire contact point added and confirmed callbacks
			//

			hkArray<hkContactPointId> cpIds;
			mgr->getAllContactPointIds(cpIds);

			if (input.m_fireContactPointAddedCallbacks)
			{
				for (int c = 0; c < cpIds.getSize(); c++)
				{
					hkContactPointId cpId = cpIds[c];

					hkpProcessCollisionOutput dummyOutput(HK_NULL/*constraintOwner*/);

				
					const hkpCdBody* invalidCdBodyA = HK_NULL;
					const hkpCdBody* invalidCdBodyB = HK_NULL;
					if (input.m_passCollidablePointersInCollisionCallbacks)
					{
						invalidCdBodyA = entityA->getCollidable();
						invalidCdBodyB = entityB->getCollidable();
					}

					hkpGskCache* const gskCache = HK_NULL;
					const hkReal projectedVelocity = 0.0f;

					hkpManifoldPointAddedEvent event( cpId, mgr, collisionInput, &dummyOutput, invalidCdBodyA, invalidCdBodyB, mgr->getContactPoint(cpId), gskCache, mgr->getContactPointProperties(cpId), projectedVelocity);

					hkpWorld* world = entityA->getWorld();
					hkpWorldCallbackUtil ::fireContactPointAdded( world, event );
					hkpEntityCallbackUtil::fireContactPointAdded( entityA, event );
					hkpEntityCallbackUtil::fireContactPointAdded( entityB, event );

					HK_ASSERT2(0xad8751dd, event.m_status == HK_CONTACT_POINT_ACCEPT, "Deserialized contact points cannot be rejected.");
				}
			}

			if (input.m_fireContactPointConfirmedCallbacks)
			{
				for (int c = 0; c < cpIds.getSize(); c++)
				{
					hkContactPointId cpId = cpIds[c];

					// only fire confirmed callbacks for old contacts. The new contacts will have their confirmed callbacks fired from the solver normally.
					if ( ! (mgr->getContactPointProperties(cpId)->m_flags & hkContactPointMaterial::CONTACT_IS_NEW_AND_POTENTIAL) )
					{
						const hkReal rotateNormal = 0.0f;
						const hkReal projectedVelocity = 0.0f;

						hkpContactPointConfirmedEvent event( hkpContactPointAddedEvent::TYPE_MANIFOLD, 
							entityA->getCollidable(), entityB->getCollidable(), 
							&mgr->m_contactConstraintData,
							mgr->getContactPoint(cpId), 
							mgr->getContactPointProperties(cpId), 
							rotateNormal, projectedVelocity );

						hkpWorld* world = entityA->getWorld();
						hkpWorldCallbackUtil::fireContactPointConfirmed( world, event );
						hkpEntityCallbackUtil::fireContactPointConfirmed( entityA, event );
						hkpEntityCallbackUtil::fireContactPointConfirmed( entityB, event );
					}
				}
			}

			hkAgentNnMachine_InvalidateTimInAgent(entry, *collisionInput); 

			return HK_SUCCESS;
		}
	}

	return HK_FAILURE;
}

hkResult HK_CALL hkpSaveContactPointsUtil::serializeEntry( const hkpAgentEntry* entry, hkBool isNnEntry, const hkpProcessCollisionInput* input, int& sizeOfThisEntryOut, enum hkpSerializedAgentNnEntry::SerializedAgentType& agentTypeOut, const hkpAgent1nTrack*& agent1nTrackOut, hkpSerializedTrack1nInfo& trackInfoOut )
{
	agent1nTrackOut = HK_NULL;
	const hkpAgentData* agentData;
	hkAgent3::StreamCommand command = static_cast<hkAgent3::StreamCommand>(entry->m_streamCommand);

	switch ( command )
	{
		// The non-stream agent should be removed
	case hkAgent3::STREAM_CALL_AGENT:
		{
			HK_ASSERT2(0xad7654dd, false, "Agent2 technology not supported by hkpSaveContactPointsUtil. Unregister agent2 agents, to save contact points between hkRigidBodies.");
			return HK_FAILURE;
		}
	case hkAgent3::STREAM_CALL_WITH_TIM_FLIPPED:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. NnEntry cannot be flipped.");
			// fall through
		}
	case hkAgent3::STREAM_CALL_WITH_TIM:
		{
			agentData = hkAddByteOffsetConst( entry, isNnEntry ? hkSizeOf( hkpAgentNnMachineTimEntry ) : hkSizeOf( hkpAgent1nMachineTimEntry ) ); 
			goto continueConvertEntryToSerialized;
		}
	case hkAgent3::STREAM_CALL_FLIPPED:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. NnEntry cannot be flipped.");
			// fall through
		}
	case hkAgent3::STREAM_CALL:
		{
			agentData = hkAddByteOffsetConst( entry, isNnEntry ? hkSizeOf( hkpAgentNnMachinePaddedEntry ) : hkSizeOf( hkpAgent1nMachinePaddedEntry ) );
continueConvertEntryToSerialized:

			hkAgent3::ProcessFunc func = input->m_dispatcher->getAgent3ProcessFunc( entry->m_agentType );
			agentTypeOut = getSerializedAgentType(func);

			switch(agentTypeOut)
			{
				case hkpSerializedAgentNnEntry::BOX_BOX_AGENT3:
				case hkpSerializedAgentNnEntry::CAPSULE_TRIANGLE_AGENT3:
				case hkpSerializedAgentNnEntry::PRED_GSK_AGENT3:
				case hkpSerializedAgentNnEntry::PRED_GSK_CYLINDER_AGENT3:
					{
						agentTypeOut = getSerializedAgentType(func);
						// moved up hkString::memCpy( entryOut.m_nnEntryData, entry, HK_AGENT3_AGENT_SIZE);
						HK_ASSERT2(0xad7644dd, entry->m_size == HK_AGENT3_AGENT_SIZE || !isNnEntry, "Top level (nn) entry must be of HK_AGENT3_AGENT_SIZE.");
						sizeOfThisEntryOut = entry->m_size;
						return HK_SUCCESS;
					}
				case hkpSerializedAgentNnEntry::CONVEX_LIST_AGENT3:
					{
						agentTypeOut = getSerializedAgentType(func);
						// moved up hkString::memCpy( entryOut.m_nnEntryData, entry, HK_AGENT3_AGENT_SIZE);
						HK_ASSERT2(0xad7644dd, entry->m_size == HK_AGENT3_AGENT_SIZE || !isNnEntry, "Top level (nn) entry must be of HK_AGENT3_AGENT_SIZE.");
						sizeOfThisEntryOut = entry->m_size;
						if (!hkPredGskAgent3::getGskFlag(agentData, hkpGskCache::GSK_FLAGS_CONVEX_LIST_IN_GSK_MODE))
						{
							// Serialize 1nTrack
							agent1nTrackOut = hkConvexListAgent3::getAgent1nTrack(entry, agentData);
							return serialize1nTrack(agent1nTrackOut->m_sectors, input, trackInfoOut);
						}
						return HK_SUCCESS;
					}
				case hkpSerializedAgentNnEntry::LIST_AGENT3:
				case hkpSerializedAgentNnEntry::BV_TREE_AGENT3:
				case hkpSerializedAgentNnEntry::COLLECTION_COLLECTION_AGENT3:
					{
						sizeOfThisEntryOut = entry->m_size; 
						agentTypeOut = getSerializedAgentType(func);
						agent1nTrackOut = reinterpret_cast<const hkpAgent1nTrack*>(agentData);
						return serialize1nTrack(agent1nTrackOut->m_sectors, input, trackInfoOut);
					}
				default:
					{
						HK_ASSERT2(0xad54baa1, false, "Unsupported agent3 type. Unregister some agent3 agents.");
						return HK_FAILURE;
					}
			}
		}
	
	case hkAgent3::STREAM_NULL:
	case hkAgent3::STREAM_END:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. Stream null & stream end commands not supported for NnEntries.");
			sizeOfThisEntryOut = sizeof( hkpAgent1nMachinePaddedEntry );
			return HK_SUCCESS;
			break;
		}

	}

	return HK_SUCCESS;

}

// in the end this would only be used for the nn entry
hkResult HK_CALL hkpSaveContactPointsUtil::destroyOldEntry( const hkpSerializedAgentNnEntry::SerializedAgentType agentType, hkpProcessCollisionInput* input, hkpDynamicsContactMgr* mgr, hkpConstraintOwner* constraintOwner, hkpAgentNnEntry* nnEntry )
{
	hkAgent3::StreamCommand command = static_cast<hkAgent3::StreamCommand>(nnEntry->m_streamCommand);
	hkpAgentData* agentData;

	switch ( command )
	{
	case hkAgent3::STREAM_CALL_WITH_TIM:
		{
			agentData = hkAddByteOffset( nnEntry, hkSizeOf( hkpAgentNnMachineTimEntry ) );
			goto continueSetNnEntryFromSerialized;
		}
	case hkAgent3::STREAM_CALL:
		{
			agentData = hkAddByteOffset( nnEntry, hkSizeOf( hkpAgentNnMachinePaddedEntry ) );
continueSetNnEntryFromSerialized:

			hkAgent3::ProcessFunc func = input->m_dispatcher->getAgent3ProcessFunc( nnEntry->m_agentType );
			hkpSerializedAgentNnEntry::SerializedAgentType oldAgentType = getSerializedAgentType(func);

			if (oldAgentType != agentType || agentType == hkpSerializedAgentNnEntry::INVALID_AGENT_TYPE)
			{
				HK_ASSERT2(0xad76444d, false, "Agent types don't match.");
				return HK_FAILURE;
			}

			// Destroy old agent
			hkAgent3::DestroyFunc destroyFunc = input->m_dispatcher->getAgent3DestroyFunc( nnEntry->m_agentType );
			destroyFunc(nnEntry, agentData, mgr, *constraintOwner, input->m_dispatcher);

			return HK_SUCCESS;
		}
	case hkAgent3::STREAM_CALL_AGENT:
		{
			HK_ASSERT2(0x0, false, "Agent2 agents not supported.");
			return HK_FAILURE;
		}
	default:
		{
			HK_ASSERT2(0x0, false, "Unhandled command in stream.");
			return HK_FAILURE;
		}
	}
}


// in the end this would only be used for the nn entry
hkResult HK_CALL hkpSaveContactPointsUtil::deserializeEntry( const hkpSerializedAgentNnEntry& serializedEntryIn, const hkpSerializedAgentNnEntry::SerializedAgentType agentType, const hkpSerializedTrack1nInfo& serializedTrack, hkpProcessCollisionInput* input, hkpAgentNnEntry* nnEntry )
{
	hkAgent3::StreamCommand command = static_cast<hkAgent3::StreamCommand>(nnEntry->m_streamCommand);
	hkpAgentData* agentData;

	switch ( command )
	{
	case hkAgent3::STREAM_CALL_WITH_TIM:
		{
			agentData = hkAddByteOffset( nnEntry, hkSizeOf( hkpAgentNnMachineTimEntry ) );
			goto continueSetNnEntryFromSerialized;
		}
	case hkAgent3::STREAM_CALL:
		{
			agentData = hkAddByteOffset( nnEntry, hkSizeOf( hkpAgentNnMachinePaddedEntry ) );
continueSetNnEntryFromSerialized:

			hkAgent3::ProcessFunc func = input->m_dispatcher->getAgent3ProcessFunc( nnEntry->m_agentType );
			hkpSerializedAgentNnEntry::SerializedAgentType oldAgentType = getSerializedAgentType(func);

			if (oldAgentType != agentType)
			{
				HK_ASSERT2(0xad76444d, false, "Agent types don't match.");
				return HK_FAILURE;
			}

			switch(agentType)
			{
				case hkpSerializedAgentNnEntry::BOX_BOX_AGENT3:
				case hkpSerializedAgentNnEntry::CAPSULE_TRIANGLE_AGENT3:
				case hkpSerializedAgentNnEntry::PRED_GSK_AGENT3:
				case hkpSerializedAgentNnEntry::PRED_GSK_CYLINDER_AGENT3:
					{
						// Copy entry
						hkString::memCpy( nnEntry + 1, serializedEntryIn.m_nnEntryData + sizeof(hkpAgentNnEntry), HK_AGENT3_AGENT_SIZE - sizeof(hkpAgentNnEntry));

						// Copy data from nnEntry 'header'
						hkpAgentNnEntry* serializedEntry = (hkpAgentNnEntry*)serializedEntryIn.m_nnEntryData;
						nnEntry->m_numContactPoints = serializedEntry->m_numContactPoints;
						nnEntry->m_size = serializedEntry->m_size;

						return HK_SUCCESS;
					}
				case hkpSerializedAgentNnEntry::CONVEX_LIST_AGENT3:
					{
						// Copy entry
						hkString::memCpy( nnEntry + 1, serializedEntryIn.m_nnEntryData + sizeof(hkpAgentNnEntry), HK_AGENT3_AGENT_SIZE - sizeof(hkpAgentNnEntry));

						// Copy data from nnEntry 'header'
						hkpAgentNnEntry* serializedEntry = (hkpAgentNnEntry*)serializedEntryIn.m_nnEntryData;
						nnEntry->m_numContactPoints = serializedEntry->m_numContactPoints;
						nnEntry->m_size = serializedEntry->m_size;

						if (!hkPredGskAgent3::getGskFlag(agentData, hkpGskCache::GSK_FLAGS_CONVEX_LIST_IN_GSK_MODE))
						{
							// Deserialize 1nTrack
							hkpAgent1nTrack* agent1nTrack = hkConvexListAgent3::getAgent1nTrack(nnEntry, agentData);
							new (agent1nTrack) hkpAgent1nTrack();
							return deserialize1nTrack(serializedTrack, input, agent1nTrack->m_sectors);
						}

						return HK_SUCCESS;
					}
				case hkpSerializedAgentNnEntry::LIST_AGENT3:
				case hkpSerializedAgentNnEntry::BV_TREE_AGENT3:
				case hkpSerializedAgentNnEntry::COLLECTION_COLLECTION_AGENT3:
					{
						// Copy entry
						hkString::memCpy( nnEntry + 1, serializedEntryIn.m_nnEntryData + sizeof(hkpAgentNnEntry), HK_AGENT3_AGENT_SIZE - sizeof(hkpAgentNnEntry));

						// <ag.todo.a> assert that vbTrees & listAgent's agent1nTrack are at the expected location

						// Deserialize track
						hkpAgent1nTrack* agent1nTrack = static_cast<hkpAgent1nTrack*>(agentData);
						new (agent1nTrack) hkpAgent1nTrack();
						return deserialize1nTrack(serializedTrack, input, agent1nTrack->m_sectors);
					}
				default:
					{
						HK_ASSERT2(0xad7644dd, false, "Invalid data in serialized hkpAgentNnEntry.");
						return HK_FAILURE;
					}
			}
		}
	case hkAgent3::STREAM_CALL_AGENT:
		{
			HK_ASSERT2(0x0, false, "Agent2 agents not supported.");
			return HK_FAILURE;
		}
	default:
		{
			HK_ASSERT2(0x0, false, "Unhandled command in stream.");
			return HK_FAILURE;
		}
	}
}

hkResult HK_CALL hkpSaveContactPointsUtil::serialize1nTrack( const hkArray<hkpAgent1nSector*>& sectorsIn, const hkpProcessCollisionInput* input, hkpSerializedTrack1nInfo& trackInfoOut)
{
	trackInfoOut.m_sectors.reserve( sectorsIn.getSize() );

	for (int i = 0; i < sectorsIn.getSize(); ++i)
	{
		hkpAgent1nSector* readSector = sectorsIn[i];
		hkpAgentData* readData = readSector->getBegin();
		hkpAgentData* readEnd = readSector->getEnd();

		// Make sure the sector is ok
		while (readData < readEnd)
		{
			hkpAgentEntry* entry = reinterpret_cast<hkpAgentEntry*>(readData);
			const hkpAgent1nTrack* agent1nTrack = HK_NULL;
			const hkBool nonNnEntry = false;
			hkpSerializedAgentNnEntry::SerializedAgentType dummyAgentType;

			int sizeOfThisEntry = 0;
			hkpSerializedSubTrack1nInfo* newSubTrackInfo = new hkpSerializedSubTrack1nInfo();

			if ( HK_SUCCESS == serializeEntry(entry, nonNnEntry, input, sizeOfThisEntry, dummyAgentType, agent1nTrack, *newSubTrackInfo) )
			{
				if ( ! newSubTrackInfo->isEmpty())
				{
					HK_ASSERT(0x0, agent1nTrack);
					newSubTrackInfo->m_sectorIndex = i; 
					newSubTrackInfo->m_offsetInSector = (int)hkGetByteOffset(readSector->getBegin(), agent1nTrack);

					trackInfoOut.m_subTracks.pushBack(newSubTrackInfo);
				}
				else
				{
					delete newSubTrackInfo;
				}

				readData = hkAddByteOffset(readData, sizeOfThisEntry );
			}
			else
			{
				delete newSubTrackInfo;
				return HK_FAILURE;
			}

		}
		trackInfoOut.m_sectors.expandOne();
		trackInfoOut.m_sectors[i] = new hkpAgent1nSector();
		*trackInfoOut.m_sectors[i] = *readSector;
		HK_ASSERT2(0XAD7655DD, trackInfoOut.m_sectors[i]->m_bytesAllocated <= 512, "Sector corrupted.");
	}
	return HK_SUCCESS;
}

hkResult HK_CALL hkpSaveContactPointsUtil::deserialize1nTrack( const hkpSerializedTrack1nInfo& serializedTrack, hkpProcessCollisionInput* input, hkArray<hkpAgent1nSector*>& sectorsOut)
{
	HK_ASSERT2(0xad764aaa, sectorsOut.isEmpty(), "Output sectors are not empty.");

	//  Copy sectors
	sectorsOut.setSize(serializedTrack.m_sectors.getSize());
	for (int s = 0; s < serializedTrack.m_sectors.getSize(); s++)
	{
		sectorsOut[s] = new hkpAgent1nSector();
		*sectorsOut[s] = *serializedTrack.m_sectors[s];
		HK_ASSERT2(0XAD7655DD, sectorsOut[s]->m_bytesAllocated <= 512, "Sector corrupted.");
	}

	// Deserialize sub tracks
	for (int t = 0; t < serializedTrack.m_subTracks.getSize(); t++ )
	{
		const hkpSerializedSubTrack1nInfo& subTrack = *serializedTrack.m_subTracks[t];
		hkpAgent1nTrack* track = (hkpAgent1nTrack*)hkAddByteOffset( sectorsOut[subTrack.m_sectorIndex]->getBegin(), subTrack.m_offsetInSector );
		new (track) hkpAgent1nTrack();
		if ( HK_FAILURE == deserialize1nTrack(subTrack, input, track->m_sectors ) )
		{
			HK_ASSERT2(0xad8752dd, false, "Internal error / Unrecoverable error?");
			return HK_FAILURE;
		}
	}
	return HK_SUCCESS;
}



//__________________________________________________________________________________________________
//
// New helper functions
//__________________________________________________________________________________________________


hkpSerializedAgentNnEntry::SerializedAgentType HK_CALL hkpSaveContactPointsUtil::getSerializedAgentType(hkAgent3::ProcessFunc func)
{
	     if ( func == hkBoxBoxAgent3::process )						{ return hkpSerializedAgentNnEntry::BOX_BOX_AGENT3; } 
	else if ( func == hkCapsuleTriangleAgent3::process )			{ return hkpSerializedAgentNnEntry::CAPSULE_TRIANGLE_AGENT3; }
	else if ( func == hkPredGskAgent3::process )					{ return hkpSerializedAgentNnEntry::PRED_GSK_AGENT3; }
	else if ( func == hkPredGskCylinderAgent3::process )			{ return hkpSerializedAgentNnEntry::PRED_GSK_CYLINDER_AGENT3; }
	else if ( func == hkConvexListAgent3::process )					{ return hkpSerializedAgentNnEntry::CONVEX_LIST_AGENT3; }
	else if ( func == hkListAgent3::process )						{ return hkpSerializedAgentNnEntry::LIST_AGENT3; }
	else if ( func == hkBvTreeAgent3::process )						{ return hkpSerializedAgentNnEntry::BV_TREE_AGENT3; }
	else if ( func == hkpCollectionCollectionAgent3::process )		{ return hkpSerializedAgentNnEntry::COLLECTION_COLLECTION_AGENT3; }
	else 
	{
		return hkpSerializedAgentNnEntry::INVALID_AGENT_TYPE;
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
