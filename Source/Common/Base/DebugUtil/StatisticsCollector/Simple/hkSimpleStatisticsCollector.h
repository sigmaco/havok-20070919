/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKMONITOR_SIMPLE_STATISTICS_COLLECTOR_H
#define HKBASE_HKMONITOR_SIMPLE_STATISTICS_COLLECTOR_H

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

/// An implementation of a statistics collector. 
/// This collector creates Nodes (the same Nodes as the hkMonitorStreamAnalyzer)
/// on the fly as it sees objects. The Nodes will contain two values, the current used
/// memory and the current allocated memory. The Nodes will be in a tree structure matching
/// the structure requested by the begin/end and push/pop methods.
/// See the hkStatisticsCollector for more information
class hkSimpleStatisticsCollector: public hkReferencedObject, public hkStatisticsCollector
{
	public:

		/// Create a hkSimpleStatisticsCollector
		hkSimpleStatisticsCollector();

		/// Delete the collector. Will delete all held data (all current Node trees (snapshots) and the stack) 
		virtual ~hkSimpleStatisticsCollector();
		
		/// Begin a new section in the stream
		/// You can thus have different types of
		/// snapshot all in the same stream .
		/// For instance you may want the ENGINE
		/// only snapshot but also after that
		/// one that takes in all categories.
		void beginSnapshot( int statisticClasses );

		/// End the current snapshot.
		void commitSnapshot( );

		/// Write the stats from the current Node tree to a text stream. 
		void writeStatistics( hkOstream& outstream, int reportLevel = hkMonitorStreamAnalyzer::REPORT_SUMMARIES );
	
		/// Reset the whole collector (wipes all snapshots and the current Node tree)
		void reset();
		
		typedef hkMonitorStreamAnalyzer::Node Node;

		/// hkStatisticsCollector interface 
		virtual void beginObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object );

		/// hkStatisticsCollector interface 
		virtual void addChunk( const char* name, StatisticClass statisticClass, const void* chunkAddress, int usedSize, int allocatedSize);

		/// hkStatisticsCollector interface 
		virtual void addChildObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object );

		/// hkStatisticsCollector interface 
		virtual void endObject( );

		/// hkStatisticsCollector interface 
		virtual void pushDir( const char* dirName );

		/// hkStatisticsCollector interface 
		virtual void popDir();

	protected:

		Node* newNode( Node* parent, const char* name, int size, int allocatedSize);

	public:
		hkArray<Node*> m_snapshots;

	protected:
		hkArray<Node*> m_currentStack;
		hkPointerMap<hkReferencedObject*,int> m_knownObjects;
		int	m_enabledStatisticClasses;
};


#endif // HKBASE_HKMONITOR_SIMPLE_STATISTICS_COLLECTOR_H

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
