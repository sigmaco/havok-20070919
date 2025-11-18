/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/DebugUtil/StatisticsCollector/Simple/hkSimpleStatisticsCollector.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

hkSimpleStatisticsCollector::hkSimpleStatisticsCollector()
{
	Node* node = new Node( HK_NULL, "/", hkMonitorStreamAnalyzer::Node::NODE_TYPE_DIRECTORY );
	m_currentStack.pushBack(node);
}

void hkSimpleStatisticsCollector::beginSnapshot( int statisticClasses )
{
	m_knownObjects.clear();
	m_enabledStatisticClasses = statisticClasses;
}

void hkSimpleStatisticsCollector::commitSnapshot(  )
{
	m_snapshots.pushBack(m_currentStack[0]);
	m_currentStack.clear();
	Node* node = new Node( HK_NULL, "/", hkMonitorStreamAnalyzer::Node::NODE_TYPE_DIRECTORY );
	m_currentStack.pushBack(node);
	m_knownObjects.clear();
}

void hkSimpleStatisticsCollector::writeStatistics( hkOstream& outstream, int reportLevel )
{
	hkMonitorStreamAnalyzer::writeStatisticsDetails( outstream, m_snapshots, 1, 0,reportLevel);
}

void hkSimpleStatisticsCollector::reset()
{

}
	
hkSimpleStatisticsCollector::Node* hkSimpleStatisticsCollector::newNode( Node* parent, const char* name, int size, int allocSize)
{
	if ( allocSize == 0 )
	{
		allocSize = size;
	}
	
	if ( !name ) name = "?";

	Node* node = new Node( parent, name, hkMonitorStreamAnalyzer::Node::NODE_TYPE_DIRECTORY );

	int allocatedSize = (allocSize==0)? 0 : hkMemory::getInstance().getAllocatedSize( allocSize);
	node->m_value[0] = hkReal(size);
	node->m_value[1] = hkReal(allocatedSize);
	node->m_count[0] = 1;
	node->m_count[1] = 1;
	return node;
}

void hkSimpleStatisticsCollector::beginObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object )
{
	//
	//	If a name is given, override my parents name
	//
	if ( name )
	{
		Node* cwd  = m_currentStack.back();
		cwd->m_name = name;
	}

//	//Node* root = m_snapshots.back();
//	Node* cwd  = m_currentStack.back();
//
//	int size = object->m_object_memsize;
//	Node* node = newNode( cwd, name, size, size );
//
//	m_currentStack.pushBack( node );
}

void hkSimpleStatisticsCollector::addChunk( const char* name, StatisticClass statisticClass, const void* chunkAddress, int usedSize, int allocSize)
{
	if ( !( statisticClass & m_enabledStatisticClasses) )
	{
		return;
	}

	if ( usedSize == 0 && allocSize == 0 )
	{
		return;
	}

	Node* cwd  = m_currentStack.back();
	/*Node* node =*/ newNode( cwd, name, usedSize, allocSize );
}

void hkSimpleStatisticsCollector::addChildObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object )
{

	//
	//	Check for existing objects
	//
	if ( !object )
	{
		return;
	}
	
	int isKnown = m_knownObjects.getWithDefault( const_cast<hkReferencedObject*>(object), 0 );
	if (isKnown != 0)
	{
		return;
	}

	m_knownObjects.insert( const_cast<hkReferencedObject*>(object), 1 );

	int size = MASK_MEMSIZE & object->m_memSizeAndFlags;

	if ( !( statisticClass & m_enabledStatisticClasses) )
	{
		size = 0;
	}

	
	Node* cwd  = m_currentStack.back();
	Node* node = newNode( cwd, name, size, size );

	m_currentStack.pushBack( node );
	
	object->calcStatistics( this );

	m_currentStack.popBack();

	if ( size == 0)
	{
		if ( !node->m_children.getSize() )
		{
			node->m_parent->m_children.popBack();
			delete node;
			node = HK_NULL;
		}
	}

	//
	//	check for inserting a self and adding children to myself
	//
	if ( node && node->m_children.getSize() )
	{
		if ( size )
		{
			Node* self =	newNode( node, "self", size, size );
			node->m_children.popBack();
			node->m_children.insertAt(0, self );
		}

		node->m_value[0] = 0;
		node->m_value[1] = 0;
		for (int c = 0; c < node->m_children.getSize(); c++)
		{
			Node* child = node->m_children[c];
			node->m_value[0] += child->m_value[0];
			node->m_value[1] += child->m_value[1];
		}
	}
}

void hkSimpleStatisticsCollector::pushDir( const char* dirName )
{
	Node* cwd  = m_currentStack.back();
	Node* node = newNode( cwd, dirName, 0, 0 );

	m_currentStack.pushBack( node );
}

hkSimpleStatisticsCollector::~hkSimpleStatisticsCollector()
{
	while (m_currentStack.getSize())
	{
		delete m_currentStack.back();
		m_currentStack.popBack();
	}

	while ( m_snapshots.getSize() )
	{
		delete m_snapshots.back();
		m_snapshots.popBack();
	}
}

void hkSimpleStatisticsCollector::popDir()
{
	Node* node = m_currentStack.back();
	m_currentStack.popBack();

	if ( !node->m_children.getSize() )
	{
		node->m_parent->m_children.popBack();
		delete node;
		node = HK_NULL;
		return;
	}

	//
	//	check for inserting a self and adding children to mysels
	//
	if ( node->m_children.getSize() )
	{
		node->m_value[0] = 0;
		node->m_value[1] = 0;
		for (int c = 0; c < node->m_children.getSize(); c++)
		{
			Node* child = node->m_children[c];
			node->m_value[0] += child->m_value[0];
			node->m_value[1] += child->m_value[1];
		}
	}

}


void hkSimpleStatisticsCollector::endObject( )
{
//	m_currentStack.popBack();
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
