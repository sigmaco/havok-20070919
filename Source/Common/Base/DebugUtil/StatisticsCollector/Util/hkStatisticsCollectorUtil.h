/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_STATISTICS_COLLECTOR_UTIL_H
#define HK_STATISTICS_COLLECTOR_UTIL_H

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/DebugUtil/StatisticsCollector/Util/hkStatisticsCollectorClassListener.h>
#include <Common/Base/Reflection/hkClass.h>

/// A utility class used for working out automatically 'calcStatistics' for classes. This is achieved by using the
/// reflection information held with classes. The methods will automatically recurse down contained members of an object
/// passed in finding out how much memory child classes use up.
///
/// Sometimes you have a class who contains a pointer to another class, but dow

class hkStatisticsCollectorUtil
{
	public:

        /// Uses the reflection information to write to the statistics collector the amount of memory that is being used
        /// obj must point to a hkReferencedObject derived object, and must point to the start of that object
        /// The vtable for the type must have been registered with the built in type registry (hkBuiltinTypeRegistry)
        /// Passing obj as HK_NULL is valid and will return immediately
    static void defaultCalcStatistics(void* obj, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener = HK_NULL );
        /// Uses reflection to work out memory used. obj must be a pointer to a cls object. Passing in HK_NULL as the obj, will
        /// just return not calling the collector
    static void defaultCalcStatistics(void* obj, const hkClass& cls,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener = HK_NULL );

        /// Adds only the fields at this level. Does not do a 'startObject'/'endObject' calll
    static void addClassContents(void* obj, const hkClass& cls,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener = HK_NULL );
        /// Adds only the fields at this level.
    static void addClassContents(void* obj, hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener );

        /// Adds only the fields at this level and up the tree to the parent.
    static void addClassContentsAll(void* obj, const hkClass& cls,hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener = HK_NULL);
        /// Adds only the fields at this level and up the tree to the parent. Does not do a 'startObject'/'endObject' call.
    static void addClassContentsAll(void* obj,hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener = HK_NULL);

        /// Starts a calcStatistics by doing the beginObject on collector. Returns the class it did this for
        /// NOTE! Only works on hkReferencedObject derived classes
        /// If it returns HK_NULL it means beginObject hasn't been called because type couldn't be determined
    static const hkClass* defaultBeginObject(void* obj, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener = HK_NULL );

    protected:

        /// If listener is non NULL returns it else returns default listener
    static hkStatisticsCollectorClassListener* _ensureListener(hkStatisticsCollectorClassListener* listener);

        /// The in pointer must be an hkReferencedObject pointer
    static const hkClass* _getClass(void* in);

    static void _addObjectContents(const char* fieldName,void* obj, const hkClass& cls, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener );
    static void _addArrayContents(const hkClassMember& mem,void* data,int size,hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener);
    static void _addHomogeneousArray(const hkClassMember& mem,void* data,const hkClass& cls,int size,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener);
    static void _addArrayData(const hkClassMember& mem,void* data,int size,int capacity,int objSize,hkStatisticsCollector::StatisticClass statCls,hkStatisticsCollector* collector);
    static int _getArrayElementSize(const hkClassMember& mem);
    static void _addChildObject(const char* fieldName,void* obj,const hkClass& cls,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener);
    static void _addCstring(const hkClassMember& mem,char* string,hkStatisticsCollector::StatisticClass cls,hkStatisticsCollector* collector);
};


#endif // HK_STATISTICS_COLLECTOR_UTIL_H

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
