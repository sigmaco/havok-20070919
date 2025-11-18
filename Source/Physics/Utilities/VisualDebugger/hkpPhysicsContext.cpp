/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>
#include <Physics/Dynamics/World/Listener/hkpWorldDeletionListener.h>
#include <Physics/Dynamics/Constraint/hkpConstraintData.h>

#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpBroadphaseViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpMidphaseViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpConstraintViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpActiveContactPointViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpInactiveContactPointViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpToiContactPointViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpPhantomDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpRigidBodyCentreOfMassViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpRigidBodyInertiaViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpShapeDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpConvexRadiusViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpSweptTransformDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpSimulationIslandViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Utilities/hkpMousePickingViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldMemoryViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldSnapshotViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Vehicle/hkpVehicleViewer.h>

//#define HK_DESTRUCTION_LIBRARY_INCLUDED

#if defined HK_DESTRUCTION_LIBRARY_INCLUDED
#	include <Physics/Destruction/StructuralIntegrity/hkdIntegrityViewer.h>
#endif

#include <Common/Visualize/hkVisualDebugger.h>

void HK_CALL hkpPhysicsContext::registerAllPhysicsProcesses()
{
	hkpBroadphaseViewer::registerViewer();
	hkpMidphaseViewer::registerViewer();
	hkpRigidBodyCentreOfMassViewer::registerViewer();
	hkpConstraintViewer::registerViewer();
	hkpConvexRadiusViewer::registerViewer();
	hkpActiveContactPointViewer::registerViewer();
	hkpInactiveContactPointViewer::registerViewer();
	hkpToiContactPointViewer::registerViewer();
	hkpRigidBodyInertiaViewer::registerViewer();
	hkpMousePickingViewer::registerViewer();
	hkpPhantomDisplayViewer::registerViewer();
	hkpShapeDisplayViewer::registerViewer();
	hkpSimulationIslandViewer::registerViewer();
	hkpSweptTransformDisplayViewer::registerViewer();
	hkpVehicleViewer::registerViewer();
	hkpWorldMemoryViewer::registerViewer();
	hkpWorldSnapshotViewer::registerViewer();
#if defined HK_DESTRUCTION_LIBRARY_INCLUDED
	hkdIntegrityViewer::registerViewer();
#endif
}

hkpPhysicsContext::hkpPhysicsContext()
{
	
}

hkpPhysicsContext::~hkpPhysicsContext()
{
	for (int w=(m_worlds.getSize()-1); w >=0 ; --w)
	{
		removeWorld( m_worlds[w] );
	}
}

void hkpPhysicsContext::setOwner(hkVisualDebugger* vdb)
{
	if (m_owner)
	{
		for (int wi=0;wi < m_worlds.getSize(); ++wi)
			removeFromInspection(m_worlds[wi]);	
	}

	m_owner = vdb;

	if (vdb)
	{
		for (int i=0;i < m_worlds.getSize(); ++i)
			addForInspection( m_worlds[i] );	
	}
}

void hkpPhysicsContext::removeWorld( hkpWorld* oldWorld )
{
	int wi = m_worlds.indexOf(oldWorld);
	if (wi >= 0)
	{
		oldWorld->removeWorldDeletionListener(this);
		for (int i=0; i < m_addListeners.getSize(); ++i)
		{
			m_addListeners[i]->worldRemovedCallback(oldWorld);
		}
		m_worlds.removeAt(wi);

		removeFromInspection( oldWorld );
	}
}

void hkpPhysicsContext::addWorld( hkpWorld* newWorld )
{
	// make sure we don't have it already
	if (m_worlds.indexOf(newWorld) < 0)
	{
		newWorld->addWorldDeletionListener(this);
		m_worlds.pushBack(newWorld);

		for (int i=0; i < m_addListeners.getSize(); ++i)
		{
			m_addListeners[i]->worldAddedCallback( newWorld );
		}

		addForInspection( newWorld );
	}
}

// XXX get this from a reg so that we don't have to always affect the code footprint..
extern const hkClass hkpEntityClass;
extern const hkClass hkpPhantomClass;
extern const hkClass hkpActionClass;
extern const hkClass hkpConstraintInstanceClass;

void hkpPhysicsContext::addForInspection(hkpWorld* w)
{
	if (m_owner && w)
	{
		w->lock();

		w->addEntityListener(this);
		w->addPhantomListener(this);
		w->addActionListener(this);
		w->addConstraintListener(this);

		// easiest to get the world to give us the info
		// (world itself is not a valid ptr for inspection
		//  as it has no class.. literally ;)
		hkpPhysicsSystem* sys = w->getWorldAsOneSystem();
		const hkArray<hkpRigidBody*>& rbs = sys->getRigidBodies();
		for (int ri=0; ri < rbs.getSize(); ++ri)
			entityAddedCallback( const_cast<hkpRigidBody*>(rbs[ri]) );
		
		const hkArray<hkpPhantom*>& phantoms = sys->getPhantoms();
		for (int pi=0; pi < phantoms.getSize(); ++pi)
			phantomAddedCallback( const_cast<hkpPhantom*>(phantoms[pi]) );

		const hkArray<hkpAction*>& actions = sys->getActions();
		for (int ai=0; ai < actions.getSize(); ++ai)
			actionAddedCallback( const_cast<hkpAction*>(actions[ai]) );

		const hkArray<hkpConstraintInstance*>& constraints = sys->getConstraints();
		for (int ci=0; ci < constraints.getSize(); ++ci)
			constraintAddedCallback( const_cast<hkpConstraintInstance*>(constraints[ci]) );

		sys->removeReference();	

		w->unlock();
	}
}

void hkpPhysicsContext::removeFromInspection(hkpWorld* w)
{
	if (m_owner && w)
	{
		w->removeEntityListener(this);
		w->removePhantomListener(this);
		w->removeActionListener(this);
		w->removeConstraintListener(this);

		hkpPhysicsSystem* sys = w->getWorldAsOneSystem();
		const hkArray<hkpRigidBody*>& rbs = sys->getRigidBodies();
		for (int ri=0; ri < rbs.getSize(); ++ri)
			entityRemovedCallback(const_cast<hkpRigidBody*>(rbs[ri]) );

		const hkArray<hkpPhantom*>& phantoms = sys->getPhantoms();
		for (int pi=0; pi < phantoms.getSize(); ++pi)
			phantomRemovedCallback(const_cast<hkpPhantom*>(phantoms[pi]) );

		const hkArray<hkpAction*>& actions = sys->getActions();
		for (int ai=0; ai < actions.getSize(); ++ai)
			actionRemovedCallback(const_cast<hkpAction*>(actions[ai]) );

		const hkArray<hkpConstraintInstance*>& constraints = sys->getConstraints();
		for (int ci=0; ci < constraints.getSize(); ++ci)
			constraintRemovedCallback(const_cast<hkpConstraintInstance*>(constraints[ci]) );

		sys->removeReference();
	}
}

int hkpPhysicsContext::findWorld(hkpWorld* world)
{
	return m_worlds.indexOf(world);
}

void hkpPhysicsContext::worldDeletedCallback( hkpWorld* world )
{
	removeWorld(world);
}

void hkpPhysicsContext::entityAddedCallback( hkpEntity* entity )
{
	if (m_owner)
		m_owner->addTrackedObject(entity, hkpEntityClass, "Entities");
}

void hkpPhysicsContext::entityRemovedCallback( hkpEntity* entity )
{
	if (m_owner)
		m_owner->removeTrackedObject(entity);
}

void hkpPhysicsContext::phantomAddedCallback( hkpPhantom* phantom )
{
	if (m_owner)
		m_owner->addTrackedObject(phantom, hkpPhantomClass, "Phantoms");
}

void hkpPhysicsContext::phantomRemovedCallback( hkpPhantom* phantom )
{
	if (m_owner)
		m_owner->removeTrackedObject(phantom);
}

void hkpPhysicsContext::constraintAddedCallback( hkpConstraintInstance* constraint )
{
	if (m_owner && constraint->getData() && constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT)
	{
		m_owner->addTrackedObject(constraint, hkpConstraintInstanceClass, "Constraints");
	}
}

void hkpPhysicsContext::constraintRemovedCallback( hkpConstraintInstance* constraint )
{
	if (m_owner && constraint->getData() && constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT)
		m_owner->removeTrackedObject(constraint);
}

void hkpPhysicsContext::actionAddedCallback( hkpAction* action )
{
	if (m_owner)
		m_owner->addTrackedObject(action, hkpActionClass, "Actions");
}

void hkpPhysicsContext::actionRemovedCallback( hkpAction* action )
{
	if (m_owner)
		m_owner->removeTrackedObject(action);
}


void hkpPhysicsContext::addWorldAddedListener( hkpPhysicsContextWorldListener* cb )
{
	if (m_addListeners.indexOf(cb)< 0)
	{
		m_addListeners.pushBack( cb );
	}
}

void hkpPhysicsContext::removeWorldAddedListener( hkpPhysicsContextWorldListener* cb )
{
	int index = m_addListeners.indexOf(cb);
	if (index >= 0 )
	{
		m_addListeners.removeAt( index );
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
