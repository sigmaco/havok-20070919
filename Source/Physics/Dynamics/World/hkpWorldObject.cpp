/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>

#if defined (HK_PLATFORM_HAS_SPU)
HK_COMPILE_TIME_ASSERT( (HK_OFFSET_OF( hkpWorldObject, m_collidable )& 0xf) == 0 );
#endif

hkpWorldObject::hkpWorldObject( class hkFinishLoadedObjectFlag flag )
	:	m_collidable(flag),
		m_properties(flag)
{
	if( flag.m_finishing )
	{
		m_collidable.setOwner(this);
	}
}


hkpWorldObject::hkpWorldObject( const hkpShape* shape, BroadPhaseType type )
:	m_world(HK_NULL),
	m_userData(HK_NULL),
	m_collidable( shape, (hkMotionState*)HK_NULL, type ),
	m_name(HK_NULL)
{
	m_collidable.setOwner( this );

	if (shape)
	{
		shape->addReference();
	}
}

hkWorldOperation::Result hkpWorldObject::setShape(const hkpShape* shape)
{
	HK_ASSERT2(0xad45fe22, false, "This function must be overridden in derived classes, if it's to be used.");

//	if (m_world && m_world->areCriticalOperationsLocked())
//	{
//		hkWorldOperation::SetWorldObjectShape op;
//		op.m_worldObject = this;
//		op.m_shape = shape;
//
//		m_world->queueOperation(op);
//		return hkWorldOperation::POSTPONED;
//	}
//
//	// Handle reference counting here.
//	if (getCollidable()->getShape())
//	{
//		getCollidable()->getShape()->removeReference();
//	}
//	getCollidable()->setShape(shape);
//	shape->addReference();

	return hkWorldOperation::DONE;
}


void hkpWorldObject::addProperty( hkUint32 key, hkpPropertyValue value)
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );

	for (int i = 0; i < m_properties.getSize(); ++i)
	{
		if (m_properties[i].m_key == key)
		{
			HK_ASSERT2(0x26ca3b52, 0, "You are trying to add a property to a world object, where a property of that type already exists");
			return;
		}
	}
	hkpProperty& p = m_properties.expandOne();
	p.m_value = value;
	p.m_key = key;
}

hkpPropertyValue hkpWorldObject::removeProperty(hkUint32 key)
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );

	for (int i = 0; i < m_properties.getSize(); ++i)
	{
		if (m_properties[i].m_key == key)
		{
			hkpProperty found = m_properties[i];
			m_properties.removeAtAndCopy(i);
			return found.m_value;
		}
	}

	HK_ASSERT2(0x62ee448b, 0, "You are trying to remove a property from a world object, where a property of that type does not exist");

	hkpPropertyValue returnValue;
	returnValue.m_data = 0;

	return returnValue;
}

void hkpWorldObject::editProperty( hkUint32 key, hkpPropertyValue value )
{
#ifdef HK_DEBUG_MULTI_THREADING
	if ( m_world && m_world->m_propertyMasterLock )
	{
		HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	}
#endif

	for (int i = 0; i < m_properties.getSize(); ++i)
	{
		if (m_properties[i].m_key == key)
		{
			m_properties[i].m_value = value;
			return;
		}
	}

	HK_ASSERT2(0x6c6f226b, 0, "You are trying to update a property of a world object, where a property of that type does not exist");
}

void hkpWorldObject::lockProperty( hkUint32 key )
{
	if ( !m_world || !m_world->m_propertyMasterLock )
	{
		return;
	}
	m_world->m_propertyMasterLock->enter();
}

/// unlocks a given locked property
void hkpWorldObject::unlockProperty( hkUint32 key )
{
	if ( !m_world || !m_world->m_propertyMasterLock )
	{
		return;
	}
	m_world->m_propertyMasterLock->leave();
}


void hkpWorldObject::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->addChildObject("Shape", collector->MEMORY_SHARED,  m_collidable.getShape());
	collector->addArray("CollAgtPtr",  collector->MEMORY_RUNTIME, m_collidable.m_collisionEntries);
	collector->addArray("Properties",  collector->MEMORY_ENGINE,  m_properties);
	if ( m_collidable.m_boundingVolumeData.m_childShapeAabbs )
	{
		collector->addChunk("ChildShapeAabbs", collector->MEMORY_RUNTIME, m_collidable.m_boundingVolumeData.m_childShapeAabbs, sizeof(hkAabbUint32) * m_collidable.m_boundingVolumeData.m_numChildShapeAabbs );
	}
}


void hkpWorldObject::addReference()
{
	HK_ACCESS_CHECK_WITH_PARENT( getWorld(), HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	hkReferencedObject::addReference();
}

void hkpWorldObject::removeReference()
{
	HK_ACCESS_CHECK_WITH_PARENT( getWorld(), HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	hkReferencedObject::removeReference();
}

void hkpWorldObject::addReferenceAsCriticalOperation()
{
	if (getWorld() && getWorld()->areCriticalOperationsLocked())
	{
		hkWorldOperation::AddReference op;
		op.m_worldObject = this;
		getWorld()->queueOperation(op);
		return;
	}

	HK_ACCESS_CHECK_WITH_PARENT( getWorld(), HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	hkReferencedObject::addReference();
}

void hkpWorldObject::removeReferenceAsCriticalOperation()
{
	if (getWorld() && getWorld()->areCriticalOperationsLocked())
	{
		hkWorldOperation::RemoveReference op;
		op.m_worldObject = this;
		getWorld()->queueOperation(op);
		return;
	}

	HK_ACCESS_CHECK_WITH_PARENT( getWorld(), HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	hkReferencedObject::removeReference();
}

void hkpWorldObject::markForWriteImpl( )
{
#ifdef HK_DEBUG_MULTI_THREADING
	if ( m_world )
	{
		HK_ASSERT2( 0xf0213de, !m_world->m_multiThreadCheck.isMarkedForReadRecursive(), "You cannot mark an entity read write, if it is already marked as read only by the hkpWorld::markForRead(RECURSIVE)" );
	}
	getMultiThreadCheck().markForWrite();
#endif
}

void hkpWorldObject::checkReadWrite()
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW);
}

void hkpWorldObject::checkReadOnly() const
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO);
}

/*
* Havok SDK - CLIENT RELEASE, BUILD(#20070919)
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
