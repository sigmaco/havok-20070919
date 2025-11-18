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

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpPhantomDisplayViewer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/hkpShapeDisplayBuilder.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessFactory.h>

#include <Common/Visualize/Shape/hkDisplayGeometry.h>

#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Dynamics/Phantom/hkpPhantomType.h>
#include <Physics/Dynamics/Phantom/hkpPhantom.h>

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Visualize/Type/hkColor.h>

static const hkReal DEFAULT_PHANTOM_SIZE = 0.25f;
static const unsigned int HK_DEFAULT_PHANTOM_COLOR = hkColor::rgbFromChars( 240, 200, 0, 200 ); // Orange with Alpha

HK_SINGLETON_IMPLEMENTATION(hkpUserShapePhantomTypeIdentifier);

int hkpPhantomDisplayViewer::m_tag = 0;

void HK_CALL hkpPhantomDisplayViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpPhantomDisplayViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpPhantomDisplayViewer(contexts);
}

hkpPhantomDisplayViewer::hkpPhantomDisplayViewer(const hkArray<hkProcessContext*>& contexts)
: hkpWorldViewerBase(contexts)
{
	
}

void hkpPhantomDisplayViewer::init()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			addWorld(m_context->getWorld(i));
		}
	}
}

hkpPhantomDisplayViewer::~hkpPhantomDisplayViewer()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			removeWorld(m_context->getWorld(i));
		}
	}
}

void hkpPhantomDisplayViewer::worldRemovedCallback( hkpWorld* world )
{
	removeWorld(world);
}

void hkpPhantomDisplayViewer::worldAddedCallback( hkpWorld* world )
{
	addWorld(world);
}

void hkpPhantomDisplayViewer::removeWorld( hkpWorld* world)
{
	world->markForWrite();
	
	world->removePhantomListener( this );
	world->removeWorldPostSimulationListener( this );
	const hkArray<hkpPhantom*>& phantoms = world->getPhantoms();

	for(int i = 0; i < phantoms.getSize(); i++)
	{
		phantomRemovedCallback( phantoms[i] );
	}

	world->unmarkForWrite();
}

void hkpPhantomDisplayViewer::addWorld(hkpWorld* world)
{
	world->markForWrite();
	
	world->addPhantomListener( this );
	world->addWorldPostSimulationListener( this );

	// get all the phantoms from the world and add them
	const hkArray<hkpPhantom*>& phantoms = world->getPhantoms();

	for(int i = 0; i < phantoms.getSize(); i++)
	{
		phantomAddedCallback( phantoms[i] );
	}

	world->unmarkForWrite();
}


void hkpPhantomDisplayViewer::phantomAddedCallback( hkpPhantom* phantom )
{

	const hkpShape* shape = phantom->getCollidable()->getShape();
	const hkpPhantomType type = phantom->getType();

	// For shape phantoms we add and manage a display geometry
	hkArray<hkDisplayGeometry*> displayGeometries;
	bool isShapePhantom = (type == HK_PHANTOM_SIMPLE_SHAPE) || (type == HK_PHANTOM_CACHING_SHAPE);
	if (!isShapePhantom)
	{
		isShapePhantom = hkpUserShapePhantomTypeIdentifier::getInstance().m_shapePhantomTypes.indexOf(type) != -1;
	}

	if (isShapePhantom && (shape != HK_NULL))
	{
		hkpShapeDisplayBuilder::hkpShapeDisplayBuilderEnvironment env;
		hkpShapeDisplayBuilder shapeBuilder(env);
		shapeBuilder.buildDisplayGeometries( shape, displayGeometries);

		// Check the geometries are valid
		for(int i = (displayGeometries.getSize() - 1); i >= 0; i--)
		{
			if( (displayGeometries[i]->getType() == HK_DISPLAY_CONVEX) &&
				(displayGeometries[i]->getGeometry() == HK_NULL) )
			{
				HK_REPORT("Unable to build display geometry from hkpShape geometry data");
				displayGeometries.removeAt(i);
			}
		}

		// send the display geometeries off to the display handler
		{
			const hkpCollidable* coll = phantom->getCollidable();
			hkUlong id = (hkUlong)coll;

			// Add to our list of managed phantoms
			m_phantomShapesCreated.pushBack( phantom );

			const hkTransform& trans = coll->getTransform();

			m_displayHandler->addGeometry( displayGeometries, trans, id, m_tag, (hkUlong)shape);
			m_displayHandler->setGeometryColor( HK_DEFAULT_PHANTOM_COLOR, id, m_tag );
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

void hkpPhantomDisplayViewer::phantomRemovedCallback( hkpPhantom* phantom )
{
	// Check if we are managing a display for this object
	const int index = m_phantomShapesCreated.indexOf(phantom);

	if(index >= 0)
	{
		m_phantomShapesCreated.removeAt(index);
		
		// remove the geometry from the displayHandler
		hkUlong id = (hkUlong)phantom->getCollidable();
		m_displayHandler->removeGeometry(id, m_tag, (hkUlong)( phantom->getCollidable()->getShape() ));
	}
}

void hkpPhantomDisplayViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpPhantomDisplayViewer", this);

	// Create a list of AABBs one for each phantom in the scene
	{
		hkObjectArray<hkDisplayAABB> phantomAabbGeometries;
		const hkArray<hkpPhantom*>& phantoms = world->getPhantoms();
		phantomAabbGeometries.setSize(phantoms.getSize());

		hkArray<hkDisplayGeometry*> displayGeometries;
		displayGeometries.setSize(phantoms.getSize());
		
		for(int i = 0; i < phantoms.getSize(); i++)
		{
			hkAabb aabb;
			phantoms[i]->calcAabb(aabb);

			phantomAabbGeometries[i].setExtents(aabb.m_min, aabb.m_max);
			displayGeometries[i] = &phantomAabbGeometries[i];
		}

		// Draw the AABBs for each phantom
		m_displayHandler->displayGeometry(displayGeometries, HK_DEFAULT_PHANTOM_COLOR, m_tag);
	}

	// Update the transforms for the geometries associated with shape phantoms we are managing
	{
		for(int j = 0; j < m_phantomShapesCreated.getSize(); j++)
		{
			// Send the latest transform for the phantom shape 
			const hkpCollidable* coll = m_phantomShapesCreated[j]->getCollidable();
			const hkTransform& trans = m_phantomShapesCreated[j]->getCollidable()->getTransform();
			hkUlong id = (hkUlong)coll;
			m_displayHandler->updateGeometry(trans, id, m_tag);
		}
	}

	HK_TIMER_END();

}

void hkpUserShapePhantomTypeIdentifier::registerShapePhantomType( hkpPhantomType t )
{
	m_shapePhantomTypes.pushBack(t);
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
