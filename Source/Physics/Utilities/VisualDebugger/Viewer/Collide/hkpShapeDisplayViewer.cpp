/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpShapeDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/hkpShapeDisplayBuilder.h>

#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessFactory.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/Shape/hkDisplayConvex.h>

#if defined( HK_PLATFORM_XBOX360 ) || defined( HK_PLATFORM_PS3 ) || defined (HK_PLATFORM_WIN32 ) || defined( HK_PLATFORM_UNIX) || defined(HK_PLATFORM_MAC)
#define PLATFORM_SUPPORTS_INSTANCING 1
#endif

static const unsigned int HK_DEFAULT_OBJECT_COLOR = hkColor::rgbFromChars( 240, 240, 240, 255 );
static const unsigned int HK_DEFAULT_FIXED_OBJECT_COLOR = hkColor::rgbFromChars( 120, 120, 120, 255 );

int hkpShapeDisplayViewer::m_tag = 0;

hkProcess* HK_CALL hkpShapeDisplayViewer::create(const hkArray<hkProcessContext*>& contexts )
{
	return new hkpShapeDisplayViewer(contexts);
}

void HK_CALL hkpShapeDisplayViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}


hkpShapeDisplayViewer::hkpShapeDisplayViewer( const hkArray<hkProcessContext*>& contexts )
: hkpWorldViewerBase( contexts )
{
	m_enableShapeTransformUpdate = true;
	m_enableInstancing = false;
	m_enableDisplayCaching = false;
	m_enableDisplayCreation = true;
	m_autoGeometryCreation = true;
	m_enableAutoColor = true;

	m_timeForDisplay = -1.f;

	int nc = contexts.getSize();
	for (int i=0; i < nc; ++i)
	{
		if ( hkString::strCmp(HK_DISPLAY_VIEWER_OPTIONS_CONTEXT, contexts[i]->getType() ) ==0 )
		{
			ShapeDisplayViewerOptions* options = static_cast<ShapeDisplayViewerOptions*>(contexts[i] );
			m_enableShapeTransformUpdate = options->m_enableShapeTransformUpdate;
			break;
		}
	}
}

void hkpShapeDisplayViewer::init()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			addWorld( m_context->getWorld(i) );
		}
	}
}

hkpShapeDisplayViewer::~hkpShapeDisplayViewer()
{
	int ne = m_worldEntities.getSize();
	for (int i=(ne-1); i >= 0; --i) // backwards as remove alters array
	{
		removeWorld(i);
	}
}

void hkpShapeDisplayViewer::worldRemovedCallback( hkpWorld* world ) 
{ 
	int de = findWorld(world);
	if (de >= 0)
	{	
		removeWorld(de);
	}	
}

//World added listener. Should impl this in sub class, but call up to this one to get the listener reg'd.
void hkpShapeDisplayViewer::worldAddedCallback( hkpWorld* world )
{
	addWorld(world);	
}

void hkpShapeDisplayViewer::addWorld(hkpWorld* world)
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

void hkpShapeDisplayViewer::setInstancingEnabled( bool on )
{
#ifdef PLATFORM_SUPPORTS_INSTANCING
	m_enableInstancing = on; 
#endif
}

void hkpShapeDisplayViewer::setAutoColorMode( bool on )
{
	m_enableAutoColor = on; 
}


void hkpShapeDisplayViewer::setDisplayBodyCachingEnabled( bool on )
{
	m_enableDisplayCaching = on; 
}

void hkpShapeDisplayViewer::setDisplayBodyCreateEnabled( bool on )
{
	m_enableDisplayCreation = on;
}

void hkpShapeDisplayViewer::setAutoGeometryCreation( bool on )
{
	m_autoGeometryCreation = on;
}

void hkpShapeDisplayViewer::entityAddedCallback( hkpEntity* entity )
{
	const hkpShape* shapeInProperty = reinterpret_cast<const hkpShape*>( entity->getProperty( HK_PROPERTY_DISPLAY_SHAPE ).getPtr() );
	if (entity->hasProperty(HK_PROPERTY_DISPLAY_SHAPE) && shapeInProperty == HK_NULL)
	{
		return;
	}
	if( entity->getCollidable()->getShape() == HK_NULL && shapeInProperty == HK_NULL )
	{
		return;
	}

	// if we are a local viewer (not a vdb viewer) then we 
	// will ignore the bodies that have a display ptr already.
	bool isLocalViewer =  (m_inStream == HK_NULL) && (m_outStream == HK_NULL);		
	if (isLocalViewer)
	{
		hkpPropertyValue v = entity->getProperty(HK_PROPERTY_DISPLAY_PTR);
		if (v.getPtr())
			return;
	}

	// figure out the right world list for it
	// We should have the world in our list
	hkpWorld* world = entity->getWorld();
	int index = findWorld(world);
	if (index >= 0)
	{
		WorldToEntityData* wed = m_worldEntities[index];

	
		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);

		const hkpShape* shape = shapeInProperty;
		if (!shape)
		{
			shape = rigidBody->getCollidable()->getShape();
		}

		bool displayGeomAlreadyCreated = false;
		if (m_enableDisplayCaching )
		{
			hkUlong shapeAlreadyUsed = m_cachedShapes.getWithDefault( shape, 0);
			displayGeomAlreadyCreated = shapeAlreadyUsed > 0;
			if (!shapeAlreadyUsed)
			{
				m_cachedShapes.insert(shape, 1);
			}
		}

		hkUlong instanceID = 0;
		if (m_enableInstancing)
		{
			instanceID = m_instancedShapeToGeomID.getWithDefault( shape, 0);
		}

		// create an array of display geometries from the collidable - use default display settings
		hkInplaceArray<hkDisplayGeometry*,8> displayGeometries;
		bool deleteRawGeoms = true;
	
		if (!instanceID && !displayGeomAlreadyCreated && m_enableDisplayCreation && m_autoGeometryCreation)
		{
			hkGeometry* sharedGeom = reinterpret_cast<hkGeometry*>(rigidBody->getProperty(HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY_NO_DELETE).getPtr());
			hkGeometry* onceOffGeom = reinterpret_cast<hkGeometry*>(rigidBody->getProperty(HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY).getPtr());
			if (sharedGeom || onceOffGeom )
			{
				deleteRawGeoms = sharedGeom? false : true;
				if (onceOffGeom)
				{
					rigidBody->removeProperty( HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY );
				}
				hkDisplayGeometry* dg = new hkDisplayConvex(sharedGeom? sharedGeom : onceOffGeom);
				dg->getTransform().setIdentity();
				displayGeometries.pushBackUnchecked( dg );
			} 
			else
			{
				hkpShapeDisplayBuilder::hkpShapeDisplayBuilderEnvironment env;
				hkpShapeDisplayBuilder shapeBuilder(env);

				shapeBuilder.buildDisplayGeometries( shape, displayGeometries );

				for(int i = (displayGeometries.getSize() - 1); i >= 0; i--)
				{
					if( (displayGeometries[i]->getType() == HK_DISPLAY_CONVEX) &&
						(displayGeometries[i]->getGeometry() == HK_NULL) )
					{
						HK_REPORT("Unable to build display geometry from hkpShape geometry data");
						displayGeometries.removeAt(i);
					}
				}

				if ( shapeInProperty )
				{
					shapeInProperty->removeReference();
					entity->removeProperty( HK_PROPERTY_DISPLAY_SHAPE );
				}
			}
		}

		// send the display geometries off to the display handler
		hkUlong id = getId( rigidBody );
		wed->entitiesCreated.pushBack( id );
		if (!instanceID && ( (displayGeometries.getSize() > 0) || displayGeomAlreadyCreated || !m_autoGeometryCreation /* precreated */ ) )
		{
			m_displayHandler->addGeometry( displayGeometries, rigidBody->getTransform(), id, m_tag, (hkUlong)shape );

			if (m_enableInstancing)
			{
				m_instancedShapeToGeomID.insert( shape, id ); 
				m_instancedShapeToUsageCount.insert( shape, 1 );
			}

			int color = rigidBody->getProperty( HK_PROPERTY_DEBUG_DISPLAY_COLOR ).getInt();
			if ( (0 == color) && m_enableAutoColor)
			{
				if( rigidBody->isFixed() )
				{
					color = HK_DEFAULT_FIXED_OBJECT_COLOR;
				}
				else
				{
					color = HK_DEFAULT_OBJECT_COLOR;
				}
			}
			if (color)
			{
				m_displayHandler->setGeometryColor( color, id, m_tag );
			}
		}
		else if (instanceID)
		{
			hkUlong numUsingInstance = m_instancedShapeToUsageCount.getWithDefault( shape, 1 );
			numUsingInstance++;
			m_instancedShapeToUsageCount.insert( shape, numUsingInstance );
			m_displayHandler->addGeometryInstance( instanceID, rigidBody->getTransform(), id, m_tag , (hkUlong)shape);

		}

		
		// delete intermediate display geometries - we could cache these for duplication (but should enable instancing if that is noticeable anyway)
		{
			for( int i = 0; i < displayGeometries.getSize(); ++i )
			{
				if (!deleteRawGeoms)
				{
					displayGeometries[i]->m_geometry = HK_NULL;	
				}

				delete displayGeometries[i];
			}
		}
	}
}

void hkpShapeDisplayViewer::entityRemovedCallback( hkpEntity* entity )
{
	const hkpShape* shapeInProperty = reinterpret_cast<const hkpShape*>( entity->getProperty( HK_PROPERTY_DISPLAY_SHAPE ).getPtr() );
	if( (shapeInProperty == HK_NULL) && (entity->getCollidable()->getShape() == HK_NULL))
	{
		return;
	}

	hkpWorld* world = entity->getWorld();
	int worldIndex = findWorld(world);
	if (worldIndex >= 0)
	{
		WorldToEntityData* wed = m_worldEntities[worldIndex];

		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);
		const hkpShape* shape = shapeInProperty;
		if (!shape)
		{
			shape = rigidBody->getCollidable()->getShape();
		}

		hkUlong id = getId( rigidBody );

		// remove the geometry from the displayHandler
		m_displayHandler->removeGeometry(id, m_tag, (hkUlong)shape);

		if (m_enableInstancing)
		{
			hkUlong currentNum = m_instancedShapeToUsageCount.getWithDefault( shape, 0);
			HK_ASSERT(0x0, currentNum > 0);
			currentNum--;
			if (currentNum == 0)
			{
				m_instancedShapeToGeomID.remove( shape ); // no longer an instanced display for it.
				m_instancedShapeToUsageCount.remove( shape );
			}
			else
			{
				m_instancedShapeToUsageCount.insert( shape, currentNum );
			}
		}

		// remove the id from the list of 'owned' created entities
		const int index = wed->entitiesCreated.indexOf(id);
		if(index >= 0)
		{
			wed->entitiesCreated.removeAt(index);
		}
	}
}

void hkpShapeDisplayViewer::clearCache()
{
	m_cachedShapes.clear();
}


void hkpShapeDisplayViewer::synchronizeTransforms(hkDebugDisplayHandler* displayHandler, hkpWorld* world )
{
	hkReal timeForDisplay = m_timeForDisplay > 0 ? m_timeForDisplay : world->getCurrentTime() ;

	displayHandler->lockForUpdate();

	// update the transform for all active entities (in all the active simulation islands)
	{
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();

		for(int i = 0; i < activeIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& activeEntities = activeIslands[i]->getEntities();
			for(int j = 0; j < activeEntities.getSize(); j++)
			{
				hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(activeEntities[j]);
				hkUlong id = getId( rigidBody );
				
				hkTransform transform;
				rigidBody->approxTransformAt( timeForDisplay, transform );
				displayHandler->updateGeometry(transform, id, m_tag);
			}
		}
	}

	// update the transform for all inactive entities (in all the inactive simulation islands)
	if(0)
	{
		const hkArray<hkpSimulationIsland*>& inactiveIslands = world->getInactiveSimulationIslands();

		for(int i = 0; i < inactiveIslands.getSize(); i++)
		{
			const hkArray<hkpEntity*>& inactiveEntities = inactiveIslands[i]->getEntities();
			for(int j = 0; j < inactiveEntities.getSize(); j++)
			{
				hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(inactiveEntities[j]);
				hkUlong id = getId( rigidBody );
				displayHandler->updateGeometry(rigidBody->getTransform(), id, m_tag);
			}
		}
	}

	// update the transform for all fixed entities 
	if(0)
	{
		const hkArray<hkpEntity*>& fixedEntities = world->getFixedIsland()->getEntities();
		for(int j = 0; j < fixedEntities.getSize(); j++)
		{
			hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(fixedEntities[j]);
			hkUlong id = getId( rigidBody );
			displayHandler->updateGeometry(rigidBody->getTransform(), id, m_tag);
		}
	}

	displayHandler->unlockForUpdate();

}

void hkpShapeDisplayViewer::synchronizeTransforms(hkpWorld* world )
{
	synchronizeTransforms( m_displayHandler, world );
}

void hkpShapeDisplayViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpShapeDisplayViewer", this);

	if ( !m_enableShapeTransformUpdate)
	{
		HK_TIMER_END();
		return;
	}

	synchronizeTransforms( m_displayHandler, world );

	HK_TIMER_END();
}

void hkpShapeDisplayViewer::removeAllGeometries(int worldIndex)
{
	WorldToEntityData* wed = m_worldEntities[worldIndex];
	for(int i = 0; i < wed->entitiesCreated.getSize(); i++)
	{
		const hkpShape* s = ((hkpCollidable*)wed->entitiesCreated[i])->getShape();
		m_displayHandler->removeGeometry(wed->entitiesCreated[i], m_tag, (hkUlong)s);
	}
	wed->entitiesCreated.setSize(0);
}

int hkpShapeDisplayViewer::findWorld( hkpWorld* world )
{
	int ne = m_worldEntities.getSize();
	for (int i=0; i < ne; ++i)
	{
		if (m_worldEntities[i]->world == world)
			return i;
	}
	return -1;
}

void hkpShapeDisplayViewer::removeWorld( int i )
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

void hkpShapeDisplayViewer::inactiveEntityMovedCallback( hkpEntity* entity )
{
	hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(entity);
	hkUlong id = getId( rigidBody );
	m_displayHandler->updateGeometry(rigidBody->getTransform(), id, m_tag);
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
