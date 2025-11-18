/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/hkBase.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpRigidBodyCentreOfMassViewer.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessFactory.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/Type/hkColor.h>

int hkpRigidBodyCentreOfMassViewer::m_tag = 0;

hkProcess* HK_CALL hkpRigidBodyCentreOfMassViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpRigidBodyCentreOfMassViewer(contexts);
}

void HK_CALL hkpRigidBodyCentreOfMassViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkpRigidBodyCentreOfMassViewer::hkpRigidBodyCentreOfMassViewer(const hkArray<hkProcessContext*>& contexts)
: hkpWorldViewerBase( contexts )
{
}

void hkpRigidBodyCentreOfMassViewer::init()
{
	if (m_context)
	{
		for( int i=0; i < m_context->getNumWorlds(); ++i)
		{
			addWorld( m_context->getWorld(i) );
		}
	}
}

hkpRigidBodyCentreOfMassViewer::~hkpRigidBodyCentreOfMassViewer()
{
	if (m_context)
	{
		for( int i=0; i < m_context->getNumWorlds(); ++i)
		{
			removeWorld( m_context->getWorld(i) );
		}
	}
}

void hkpRigidBodyCentreOfMassViewer::worldRemovedCallback( hkpWorld* world )
{
	removeWorld(world);
}

void hkpRigidBodyCentreOfMassViewer::worldAddedCallback( hkpWorld* world )
{
	addWorld(world);
}

void hkpRigidBodyCentreOfMassViewer::removeWorld(hkpWorld* world)
{
	world->markForWrite();
	
	world->removeEntityListener( this );
	world->removeWorldPostSimulationListener( this );
	
	// get all the active entities from the active simulation islands
	{
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();

		for(int i = 0; i < activeIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = activeIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				entityRemovedCallback( activeEntities[j] );
			}
		}
	}

	// get all the inactive entities from the inactive simulation islands
	{
		const hkArray<hkpSimulationIsland*>& inactiveIslands = world->getInactiveSimulationIslands();

		for(int i = 0; i < inactiveIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = inactiveIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				entityRemovedCallback( activeEntities[j] );
			}
		}
	}

	// get all the fixed bodies in the world
	if (world->getFixedIsland())
	{
		const hkArray<hkpEntity*>& fixedEntities = world->getFixedIsland()->getEntities();
		for(int j = 0; j < fixedEntities.getSize(); j++)
		{
			entityRemovedCallback( fixedEntities[j] );
		}
	}

	world->unmarkForWrite();
}

void hkpRigidBodyCentreOfMassViewer::addWorld(hkpWorld* world)
{
	world->markForWrite();
	
	world->addEntityListener( this );
	world->addWorldPostSimulationListener( this );

	// get all the active entities from the active simulation islands
	{
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();

		for(int i = 0; i < activeIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = activeIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				entityAddedCallback( activeEntities[j] );
			}
		}
	}

	// get all the inactive entities from the inactive simulation islands
	{
		const hkArray<hkpSimulationIsland*>& inactiveIslands = world->getInactiveSimulationIslands();

		for(int i = 0; i < inactiveIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = inactiveIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				entityAddedCallback( activeEntities[j] );
			}
		}
	}


	// get all the fixed bodies in the world
	if (world->getFixedIsland())
	{
		const hkArray<hkpEntity*>& fixedEntities = world->getFixedIsland()->getEntities();
		for(int j = 0; j < fixedEntities.getSize(); j++)
		{
			entityAddedCallback( fixedEntities[j] );
		}
	}

	world->unmarkForWrite();
}

void hkpRigidBodyCentreOfMassViewer::entityAddedCallback( hkpEntity* entity )
{
//	if(entity->getType() == HK_RIGID_BODY)
//	{
		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);
		m_entitiesCreated.pushBack(rigidBody);
//	}
}

void hkpRigidBodyCentreOfMassViewer::entityRemovedCallback( hkpEntity* entity )
{
//	if( entity->getType() == HK_RIGID_BODY )
//	{
		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);

		// remove the id from the list of 'owned' created entities
		const int index = m_entitiesCreated.indexOf(rigidBody);
	//	HK_ASSERT2(0x4bba802b, index != -1, "Trying to remove body which hkpRigidBodyCentreOfMassViewer does not think has been added!");
		if(index >= 0)
		{
			m_entitiesCreated.removeAt(index);
		}
//	}

}

void hkpRigidBodyCentreOfMassViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpRigidBodyCentreOfMassViewer", this);

	for(int i = 0; i < m_entitiesCreated.getSize(); i++)
	{
		const hkReal mass = m_entitiesCreated[i]->getMass();
		if(mass != 0.0f)
		{
			HK_TIMER_BEGIN("getMassAndLines", this);
			hkVector4 centreOfMass = m_entitiesCreated[i]->getCenterOfMassInWorld();

			hkVector4 xAxis, yAxis, zAxis;

			xAxis.setAdd4(centreOfMass, m_entitiesCreated[i]->getTransform().getRotation().getColumn(0));
			yAxis.setAdd4(centreOfMass, m_entitiesCreated[i]->getTransform().getRotation().getColumn(1));
			zAxis.setAdd4(centreOfMass, m_entitiesCreated[i]->getTransform().getRotation().getColumn(2));
			HK_TIMER_END();
			HK_TIMER_BEGIN("display3lines", this);
			m_displayHandler->displayLine(centreOfMass, xAxis, hkColor::RED, m_tag);
			m_displayHandler->displayLine(centreOfMass, yAxis, hkColor::GREEN, m_tag);
			m_displayHandler->displayLine(centreOfMass, zAxis, hkColor::BLUE, m_tag);
			HK_TIMER_END();
		}
	}

	HK_TIMER_END();

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
