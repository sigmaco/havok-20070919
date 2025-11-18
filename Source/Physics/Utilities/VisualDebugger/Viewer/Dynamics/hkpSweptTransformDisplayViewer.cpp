/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpSweptTransformDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/hkpShapeDisplayBuilder.h>

#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessFactory.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Visualize/Type/hkColor.h>

static const unsigned int HK_DEFAULT_SWEPT_TRANSFORM_COLOR_T0 = hkColor::rgbFromChars( 200, 200, 255,  80 );
static const unsigned int HK_DEFAULT_SWEPT_TRANSFORM_COLOR_T1 = hkColor::rgbFromChars( 200, 255, 200, 150 );
//static const unsigned int HK_DEFAULT_FIXED_OBJECT_COLOR = hkColor::rgbFromChars( 120, 120, 120, 255 );

#define HK_DISPLAY_TRANSFORM1

int hkpSweptTransformDisplayViewer::m_tag = 0;

hkProcess* HK_CALL hkpSweptTransformDisplayViewer::create(const hkArray<hkProcessContext*>& contexts )
{
	return new hkpSweptTransformDisplayViewer(contexts);
}

void HK_CALL hkpSweptTransformDisplayViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkpSweptTransformDisplayViewer::hkpSweptTransformDisplayViewer( const hkArray<hkProcessContext*>& contexts )
: hkpWorldViewerBase( contexts )
{
	
}

void hkpSweptTransformDisplayViewer::init()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			addWorld( m_context->getWorld(i) );
		}
	}
}

hkpSweptTransformDisplayViewer::~hkpSweptTransformDisplayViewer()
{
	int ne = m_worldEntities.getSize();
	for (int i=(ne-1); i >= 0; --i) // backwards as remove alters array
	{
		removeWorld(i);
	}
}

void hkpSweptTransformDisplayViewer::worldRemovedCallback( hkpWorld* world ) 
{ 
	int de = findWorld(world);
	if (de >= 0)
	{	
		removeWorld(de);
	}	
}

//World added listener. Should impl this in sub class, but call up to this one to get the listener reg'd.
void hkpSweptTransformDisplayViewer::worldAddedCallback( hkpWorld* world )
{
	addWorld(world);	
}

void hkpSweptTransformDisplayViewer::addWorld(hkpWorld* world)
{
	world->markForWrite();

	world->addEntityListener( this );
	world->addWorldPostSimulationListener( this );

	WorldToEntityData* wed = new WorldToEntityData;
	wed->world = world;
	m_worldEntities.pushBack(wed);

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
	{
		const hkArray<hkpEntity*>& fixedEntities = world->getFixedIsland()->getEntities();
		for(int j = 0; j < fixedEntities.getSize(); j++)
		{
			entityAddedCallback( fixedEntities[j] );
		}
	}

	world->unmarkForWrite();
}

void hkpSweptTransformDisplayViewer::entityAddedCallback( hkpEntity* entity )
{
	if(entity->getCollidable()->getShape() == HK_NULL)
	{
		return;
	}

	// figure out the right world list for it
	// We should defo have the world in our list
	hkpWorld* world = entity->getWorld();
	int index = findWorld(world);
	if (index >= 0)
	{
		WorldToEntityData* wed = m_worldEntities[index];

	
		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);

		// create an array of display geometries from the collidable - use default display settings
		hkArray<hkDisplayGeometry*> displayGeometries;
		{
			hkpShapeDisplayBuilder::hkpShapeDisplayBuilderEnvironment env;
			hkpShapeDisplayBuilder shapeBuilder(env);
			shapeBuilder.buildDisplayGeometries( rigidBody->getCollidable()->getShape(), displayGeometries);

			for(int i = (displayGeometries.getSize() - 1); i >= 0; i--)
			{
				if( (displayGeometries[i]->getType() == HK_DISPLAY_CONVEX) &&
					(displayGeometries[i]->getGeometry() == HK_NULL) )
				{
					HK_REPORT("Unable to build display geometry from hkpShape geometry data");
					displayGeometries.removeAt(i);
				}
			}
		}

		// send the display geometeries off to the display handler
		if (displayGeometries.getSize() > 0)
		{
			if( rigidBody->isFixed() )
			{
//				hkUint64 id = (hkUlong)(rigidBody->getCollidable()) + 1;
//
//				wed->entitiesCreated.pushBack( id );
//				m_displayHandler->addGeometry( displayGeometries, rigidBody->getTransform(), id, m_tag );
//
//#if 1 // toggle to reintroduce random colors
//				m_displayHandler->setGeometryColor( HK_DEFAULT_FIXED_OBJECT_COLOR, id, m_tag );
			}
			else
			{
				hkUlong id = (hkUlong)(rigidBody->getCollidable()) + 1;

				wed->entitiesCreated.pushBack( id );
				
				hkTransform t0; hkSweptTransformUtil::calcTransAtT0( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t0 );
				hkTransform t1; hkSweptTransformUtil::calcTransAtT1( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t1 );

				m_displayHandler->addGeometry( displayGeometries, t0, id, m_tag, 0 );

				m_displayHandler->setGeometryColor( HK_DEFAULT_SWEPT_TRANSFORM_COLOR_T0, id, m_tag );

#if defined HK_DISPLAY_TRANSFORM1

				id = (hkUlong)(rigidBody->getCollidable()) + 2;

				wed->entitiesCreated.pushBack( id );
				
				m_displayHandler->addGeometry( displayGeometries, t1, id, m_tag, 0 );

				m_displayHandler->setGeometryColor( HK_DEFAULT_SWEPT_TRANSFORM_COLOR_T1, id, m_tag );

#endif // defined HK_DISPLAY_TRANSFORM1
			}
//#endif
		}

		// delete intermediate display geometries - we could cache these for duplication - TODO
		{
			for( int i = 0; i < displayGeometries.getSize(); ++i )
			{
				delete displayGeometries[i];
			}
		}
	}
}

void hkpSweptTransformDisplayViewer::entityRemovedCallback( hkpEntity* entity )
{
	if( entity->getCollidable()->getShape() == HK_NULL )
	{
		return;
	}

	hkpWorld* world = entity->getWorld();
	int worldIndex = findWorld(world);
	if (worldIndex >= 0)
	{
		WorldToEntityData* wed = m_worldEntities[worldIndex];

		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);
		hkUlong id = (hkUlong)rigidBody->getCollidable() + 1;

		// remove the geometry from the displayHandler
		m_displayHandler->removeGeometry(id, m_tag, 0);

		// remove the id from the list of 'owned' created entities
		const int index = wed->entitiesCreated.indexOf(id);
		if(index >= 0)
		{
			wed->entitiesCreated.removeAt(index);
		}

#if defined HK_DISPLAY_TRANSFORM1
		id = (hkUlong)rigidBody->getCollidable() + 2;

		// remove the geometry from the displayHandler
		m_displayHandler->removeGeometry(id, m_tag, 0);

		// remove the id from the list of 'owned' created entities
		const int index2 = wed->entitiesCreated.indexOf(id);
		if(index2 >= 0)
		{
			wed->entitiesCreated.removeAt(index2);
		}
#endif // defined HK_DISPLAY_TRANSFORM1


	}
}



void hkpSweptTransformDisplayViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpSweptTransformDisplayViewer", this);

	// update the transform for all active entities (in all the active simulation islands)
	{
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();

		for(int i = 0; i < activeIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = activeIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(activeEntities[j]);
				//if ( nextFrameTime == rigidBody->getRigidMotion()->getMotionState()->getSweptTransform().getBaseTime() )
				{
					hkTransform t0; hkSweptTransformUtil::calcTransAtT0( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t0 );
					hkUlong id = hkUlong( rigidBody->getCollidable() ) + 1;
					m_displayHandler->updateGeometry(t0, id, m_tag);
				}

#if defined HK_DISPLAY_TRANSFORM1
				{
					hkTransform t1; hkSweptTransformUtil::calcTransAtT1( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t1 );
					hkUlong id = hkUlong( rigidBody->getCollidable() ) + 2;
					m_displayHandler->updateGeometry(t1, id, m_tag);
				}
#endif // defined HK_DISPLAY_TRANSFORM1

			}
		}
	}

	HK_TIMER_END();
}

void hkpSweptTransformDisplayViewer::removeAllGeometries(int worldIndex)
{
	WorldToEntityData* wed = m_worldEntities[worldIndex];
	for(int i = 0; i < wed->entitiesCreated.getSize(); i++)
	{
		m_displayHandler->removeGeometry(wed->entitiesCreated[i], m_tag, 0);
	}
	wed->entitiesCreated.setSize(0);
}

int hkpSweptTransformDisplayViewer::findWorld( hkpWorld* world )
{
	int ne = m_worldEntities.getSize();
	for (int i=0; i < ne; ++i)
	{
		if (m_worldEntities[i]->world == world)
			return i;
	}
	return -1;
}

void hkpSweptTransformDisplayViewer::removeWorld( int i )
{
	m_worldEntities[i]->world->markForWrite();
	
		m_worldEntities[i]->world->removeEntityListener( this );
		m_worldEntities[i]->world->removeWorldPostSimulationListener( this );
		removeAllGeometries(i);
		
	m_worldEntities[i]->world->unmarkForWrite();

	delete m_worldEntities[i];
	m_worldEntities.removeAt(i);
	// other base listeners handled in worldviewerbase
}

void hkpSweptTransformDisplayViewer::inactiveEntityMovedCallback( hkpEntity* entity )
{
	hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);
	{
		hkTransform t0; hkSweptTransformUtil::calcTransAtT0( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t0 );
		hkUlong id =  (hkUlong)rigidBody->getCollidable() + 1;
		m_displayHandler->updateGeometry(t0, id, m_tag);
	}
	
#if defined HK_DISPLAY_TRANSFORM1
	{
		hkUlong id =  (hkUlong)rigidBody->getCollidable() + 2;
		hkTransform t1; hkSweptTransformUtil::calcTransAtT1( rigidBody->getRigidMotion()->getMotionState()->getSweptTransform(), t1 );
		m_displayHandler->updateGeometry(t1, id, m_tag);
	}
#endif // defined HK_DISPLAY_TRANSFORM1

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
