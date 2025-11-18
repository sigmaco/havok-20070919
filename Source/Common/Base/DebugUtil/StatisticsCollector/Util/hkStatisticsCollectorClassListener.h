/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_STATISTICS_COLLECTOR_CLASS_LISTENER_H
#define HK_STATISTICS_COLLECTOR_CLASS_LISTENER_H

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>

#include <Common/Base/Container/PointerMap/hkPointerMap.h>


class hkStatisticsCollectorClassListener:public hkSingleton<hkStatisticsCollectorClassListener>
{
	public:
        HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ENTITY);

        typedef hkStatisticsCollector::StatisticClass StatisticClass;

            /// Ctor - sets up the default map that describes the classes associated with each hkClass
        hkStatisticsCollectorClassListener();

            /// Returns what kind of hkStatisticsCollector::StaticClass should be associated with the class
            /// The default implementation looks up in the class in the map, if it finds it it returns the StatisticsClass
            /// if not it checks the parent, and so forth
        virtual StatisticClass getStatisticClass( const hkClass& cls);

            /// Looks up in the map if this class is known
        hkBool findClass(const hkClass& cls, StatisticClass& statCls);
            /// Remove a class statics definition
        void removeClass(const hkClass& cls);
            /// Set a classes definition
        void setClass(const hkClass& cls, StatisticClass statCls);

            /// Work out the class via the name of the class (not by doing the lookup)
            /// This is implemented so we can have default correct classes without linkage
        StatisticClass getByNameStatisticClass( const hkClass& cls);

            /// Has a default set of name of classes set up - returns the class they are in if known
        hkBool findByNameClass(const hkClass& cls, StatisticClass& statClsOut);

    protected:
        struct NameClass
        {
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ENTITY, hkStatisticsCollectorClassListener::NameClass );
            const char* name;
            StatisticClass cls;
        };

            // An array holding the known named classes and their StatisticClass
        static NameClass g_nameClass[];

            /// class pointers to StatisticClass types
        hkPointerMap<const hkClass*,hkUint32> m_classMap;
};

#endif // HK_STATISTICS_COLLECTOR_CLASS_LISTENER_H

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
