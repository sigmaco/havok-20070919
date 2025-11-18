/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_REPORT_STATISTICS_COLLECTOR_H
#define HK_REPORT_STATISTICS_COLLECTOR_H

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

class hkStatisticClassCount
{
    public:
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkStatisticClassCount);
	typedef hkStatisticsCollector::StatisticClass StatisticClass;

    enum { COUNT_SIZE = hkStatisticsCollector::MAX_STATISTICS_CLASS_BIT };
        /// Ctor
    hkStatisticClassCount();
        /// Add a usage
    void add(hkStatisticsCollector::StatisticClass type,int amount);
        /// Dump the details
    void dump(hkOstream& out);
        /// Resets the count
    void reset();

	static const char* _toCstring(StatisticClass type);

    int m_total;
    int m_count[COUNT_SIZE];
};


class hkReportStatisticsCollector: public hkReferencedObject, public hkStatisticsCollector
{
	public:
            /// Ctor
        hkReportStatisticsCollector(hkOstream& stream);
            /// Dtor
        ~hkReportStatisticsCollector() { _clear(); }

            /// Called before any reporting
        void start();
            /// Called at the end of reporting - will give a summary
        void end();

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

        hkBool _isKnown(const hkReferencedObject* obj);
        void _addKnown(const hkReferencedObject* obj);

        void _streamAsText(StatisticClass type);
        void _addCount(const hkClass* cls,StatisticClass statCls);

		void _dumpClassCount();
        void _tab();

            /// True if we hit an object we don't want to traverse down as we've seen it before
        int m_ignoreDepth;

            /// Stream to write out to
        hkOstream& m_stream;
            /// The current recursion depth
        int m_depth;

        hkBool m_started;

        void _clear();

            /// Known objects
		hkPointerMap<const hkReferencedObject*,int> m_knownObjects;
            /// Amount of times a type is hit
        hkPointerMap<const hkClass*,hkStatisticClassCount*> m_typeCount;

        hkStatisticClassCount m_used;
        hkStatisticClassCount m_alloc;
        hkStatisticClassCount m_num;
};


#endif // HK_REPORT_STATISTICS_COLLECTOR_H

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
