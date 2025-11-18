/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/Action/hkpAction.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpPhysicsSystemWithContacts.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSaveContactPointsUtil.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics/Collide/Filter/hkpCollisionFilter.h>
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>

hkpPhysicsData::hkpPhysicsData()
{
	m_worldCinfo = HK_NULL;
}


void hkpPhysicsData::populateFromWorld( const hkpWorld* world, bool saveContactPoints )
{
	if ( m_worldCinfo != HK_NULL )
	{
		HK_WARN(0xd698765d, "Overwriting world cinfo" );
	}
	else
	{
		m_worldCinfo = new hkpWorldCinfo();
	}
	world->getCinfo(*m_worldCinfo);


	// systems
	world->getWorldAsSystems(m_systems);

	if (saveContactPoints)
	{
		hkpSaveContactPointsUtil::SavePointsInput input;
		hkpPhysicsSystemWithContacts* sys = new hkpPhysicsSystemWithContacts();
		hkpSaveContactPointsUtil::saveContactPoints(input, world, sys); 
		sys->setActive(false);
		m_systems.pushBack(sys);
	}
}

hkpPhysicsData::~hkpPhysicsData()
{
	if ( m_worldCinfo != HK_NULL )
	{	
		m_worldCinfo->removeReference();
	}


	for (int p=0; p < m_systems.getSize(); ++p)
	{
		m_systems[p]->removeReference();
	}
}

hkpWorld* hkpPhysicsData::createWorld(hkBool registerAllAgents)
{
	hkpWorldCinfo defaultCinfo;
	hkpWorld* w = HK_NULL;
	if (!m_worldCinfo)
	{
		w = new hkpWorld(defaultCinfo);
	}
	else
	{
		w = new hkpWorld(*m_worldCinfo);
	}

	w->markForWrite();

	if (registerAllAgents)
	{
		hkpAgentRegisterUtil::registerAllAgents( w->getCollisionDispatcher() );
	}

	for (int p=0; p < m_systems.getSize(); ++p)
	{
		w->addPhysicsSystem(m_systems[p]);

		if (m_systems[p]->hasContacts())
		{
			hkpSaveContactPointsUtil::LoadPointsInput input;
			hkpPhysicsSystemWithContacts* systemWithContacts = static_cast<hkpPhysicsSystemWithContacts*>(m_systems[p]);
			hkpSaveContactPointsUtil::loadContactPoints(input, systemWithContacts, w);  
		}
	}

	if (m_worldCinfo && m_worldCinfo->m_collisionFilter)
	{
		w->updateCollisionFilterOnWorld(HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);
	}

	w->unmarkForWrite();
	return w;
}

static void tryMoveEntity( hkpPhysicsSystem* fromSystem, hkpPhysicsSystem* toSystem, hkpEntity* entity )
{
	hkpRigidBody* rb = static_cast<hkpRigidBody*>(entity);
	const int fromIndex = fromSystem->getRigidBodies().indexOf(rb);
	const int toIndex = toSystem->getRigidBodies().indexOf(rb);
	if (  (toIndex == -1) && (fromIndex != -1) )
	{
		toSystem->setActive(toSystem->isActive() || rb->isActive());
		toSystem->addRigidBody(rb);
		fromSystem->removeRigidBody(fromIndex);
	}
}

// This converts the system into:
// One system for unconstrained fixed rigid bodies
// One system for unconstrained keyframed bodies
// One system for unconstrained moving bodies
// One system per group of constrained bodies (such as a ragdoll)
// One system to contain all the phantoms in the input system
// The user data pointer of the input system is set to the user data for all systems created
void hkpPhysicsData::splitPhysicsSystems(const hkpPhysicsSystem* inputSystemConst, SplitPhysicsSystemsOutput& output )
{
	hkpPhysicsSystem* inputSystem = new hkpPhysicsSystem();
	{
		for (int i = 0; i < inputSystemConst->getRigidBodies().getSize(); ++i)
		{
			inputSystem->addRigidBody( inputSystemConst->getRigidBodies()[i] );
		}
	}
	{
		for (int i = 0; i < inputSystemConst->getActions().getSize(); ++i)
		{
			inputSystem->addAction( inputSystemConst->getActions()[i] );
		}
	}
	{
		for (int i = 0; i < inputSystemConst->getConstraints().getSize(); ++i)
		{
			inputSystem->addConstraint( inputSystemConst->getConstraints()[i] );
		}
	}
	{
		for (int i = 0; i < inputSystemConst->getPhantoms().getSize(); ++i)
		{
			inputSystem->addPhantom( inputSystemConst->getPhantoms()[i] );
		}
	}

	const hkArray<hkpRigidBody*>& rigidBodies = inputSystem->getRigidBodies();

	//
	// First system is an array of rigid bodies
	//
	hkpPhysicsSystem* fixedSystem = new hkpPhysicsSystem();
	fixedSystem->setName("Fixed Rigid Bodies");
	fixedSystem->setUserData(inputSystem->getUserData());
	{
		int i = 0;
		fixedSystem->setActive(false);
		while (i < rigidBodies.getSize())
		{
			if (rigidBodies[i]->isFixed())
			{
				fixedSystem->addRigidBody(rigidBodies[i]);
				inputSystem->removeRigidBody(i);
			}
			else
			{
				i++;
			}
		}
	}
	if ( fixedSystem->getRigidBodies().getSize() != 0 )
	{
		output.m_unconstrainedFixedBodies = fixedSystem;
	}
	else
	{
		delete fixedSystem;
		output.m_unconstrainedFixedBodies = HK_NULL;
	}


	//
	// Separate out all the constrained systems into separate physics systems, and unconstrained bodies into another system
	//
	hkpPhysicsSystem* ballisticSystem = new hkpPhysicsSystem();
	ballisticSystem->setName("Unconstrained Rigid Bodies");
	ballisticSystem->setUserData(inputSystem->getUserData());
	ballisticSystem->setActive(false);

	hkpPhysicsSystem* keyframedSystem = new hkpPhysicsSystem();
	keyframedSystem->setName("Keyframed Rigid Bodies");
	keyframedSystem->setUserData(inputSystem->getUserData());
	keyframedSystem->setActive(false);

	const hkArray<hkpConstraintInstance*>& constraints = inputSystem->getConstraints();
	const hkArray<hkpAction*>& actions = inputSystem->getActions();


	while ( rigidBodies.getSize() > 0 )
	{
		//
		// Create a new system with the first rigid body in the rigidBodies list, and move all linked 
		// rigid bodies, actions and constraints into the system
		//

		hkpPhysicsSystem* currentSystem = new hkpPhysicsSystem();
		currentSystem->setName("Constrained System");
		currentSystem->setUserData(inputSystem->getUserData());

		currentSystem->setActive(rigidBodies[0]->isActive());
		currentSystem->addRigidBody(rigidBodies[0]);
		inputSystem->removeRigidBody(0);

		//
		// Very slow, but simple loop 
		// - keep iterating until we find no more constraints or actions linking to the currentSystem
		//
		bool newBodyAdded = true;
		while (newBodyAdded)
		{
			newBodyAdded = false;
			for (int j = 0; j < currentSystem->getRigidBodies().getSize(); ++j)
			{
				hkpRigidBody* currentRb = currentSystem->getRigidBodies()[j];
				{
					int i = 0;
					while (i < constraints.getSize())
					{
						// (casts are for gcc)
						if ( (constraints[i]->getEntityA() == (const hkpEntity*)currentRb) || (constraints[i]->getEntityB() == (const hkpEntity*)currentRb) )
						{
							newBodyAdded = true;
							currentSystem->addConstraint(constraints[i]);
							hkpEntity* otherBody = constraints[i]->getOtherEntity(currentRb);
							if((otherBody!=HK_NULL) && (!otherBody->isFixed()))
							{
								tryMoveEntity( inputSystem, currentSystem, otherBody );
							}
							inputSystem->removeConstraint(i);
						}
						else
						{
							i++;
						}
					}
				}
				{
					int i = 0;
					while (i < actions.getSize())
					{
						hkArray<hkpEntity*> entities;
						actions[i]->getEntities( entities );
						bool actionMoved = false;
						for (int k  = 0; k < entities.getSize(); k++)
						{
							if (entities[k] == (const hkpEntity*)currentRb)
							{
								newBodyAdded = true;
								currentSystem->addAction(actions[i]);
								inputSystem->removeAction(i);
								actionMoved = true;

								for (int l  = 0; l < entities.getSize(); l++)
								{
									if ( entities[l] != (const hkpEntity*)currentRb )
									{
										if (!entities[l]->isFixed())
										{
											tryMoveEntity(inputSystem, currentSystem, entities[l]);
										}
									}
								}
							}
						}
						if (!actionMoved)
						{
							i++;
						}
					}
				}
			}
		}
		//
		// If the entity is not linked to any other, add it to the keyframed or ballistic system
		//
		if ((currentSystem->getConstraints().getSize() == 0) && (currentSystem->getActions().getSize() == 0))
		{
			hkpRigidBody* rb = currentSystem->getRigidBodies()[0];
			// EXP-811 : RBs not yet added to the world will return False for isActive() - but we want to treat them as active
			const bool rbActive = (rb->getSimulationIsland()==HK_NULL) || rb->isActive();

			if (rb->getMotionType() == hkpMotion::MOTION_KEYFRAMED)
			{
				keyframedSystem->setActive(keyframedSystem->isActive() || rbActive);
				keyframedSystem->addRigidBody(rb);
			}
			else
			{
				ballisticSystem->setActive(ballisticSystem->isActive() || rbActive);
				ballisticSystem->addRigidBody(rb);
			}
			delete currentSystem;
		}
		else
		{
			output.m_constrainedSystems.pushBack(currentSystem);
		}
	}
	HK_ASSERT(0xaa928746, inputSystem->getConstraints().getSize() == 0);
	HK_ASSERT(0xaa928746, inputSystem->getActions().getSize() == 0);
	

	if ( keyframedSystem->getRigidBodies().getSize() != 0 )
	{
		output.m_unconstrainedKeyframedBodies = keyframedSystem;
	}
	else
	{
		delete keyframedSystem;
		output.m_unconstrainedKeyframedBodies = HK_NULL;
	}

	if ( ballisticSystem->getRigidBodies().getSize() != 0 )
	{
		output.m_unconstrainedMovingBodies = ballisticSystem;
	}
	else
	{
		delete ballisticSystem;
		output.m_unconstrainedMovingBodies = HK_NULL;
	}

	const hkArray<hkpPhantom*>& phantoms = inputSystem->getPhantoms();
	if (phantoms.getSize() > 0)
	{
		hkpPhysicsSystem* phantomSystem = new hkpPhysicsSystem();
		phantomSystem->setName("Phantoms");
		phantomSystem->setUserData(inputSystem->getUserData());

		output.m_phantoms = phantomSystem;

		for (int i = 0; i < phantoms.getSize(); ++i)
		{
			phantomSystem->addPhantom(phantoms[i]);
		}

	}
	else
	{
		output.m_phantoms = HK_NULL;
	}

	delete inputSystem;
}


// Look for a physics system by name (case insensitive)
hkpPhysicsSystem* hkpPhysicsData::findPhysicsSystemByName (const char* name) const
{
	for (int i=0; i < m_systems.getSize(); i++)
	{
		const char* sysName = m_systems[i]->getName();

		if (sysName && (hkString::strCasecmp(sysName, name)==0))
		{
			return m_systems[i];
		}
	}

	return HK_NULL;
}

// Look for a rigid body by name (case insensitive)
hkpRigidBody*  hkpPhysicsData::findRigidBodyByName (const char* name) const
{
	for (int s=0; s<m_systems.getSize(); s++)
	{
		hkpPhysicsSystem* system = m_systems[s];

		for (int r=0; r<system->getRigidBodies().getSize(); r++)
		{
			hkpRigidBody* rb = system->getRigidBodies()[r];
			const char* rbName = rb->getName();

			if (rbName && (hkString::strCasecmp(rbName, name)==0))
			{
				return rb;
			}
		}
	}

	return HK_NULL;

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
