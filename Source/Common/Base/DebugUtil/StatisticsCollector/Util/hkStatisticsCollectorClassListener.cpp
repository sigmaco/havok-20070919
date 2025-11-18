/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Base/Reflection/hkClassMemberAccessor.h>
#include <Common/Base/Reflection/hkClass.h>

#include <Common/Base/Memory/Memory/hkMemory.h>

#include <Common/Base/DebugUtil/StatisticsCollector/Util/hkStatisticsCollectorClassListener.h>

/* static */hkStatisticsCollectorClassListener::NameClass
hkStatisticsCollectorClassListener::g_nameClass[] =
{
    {"hkpTyremarksInfo",hkStatisticsCollector::MEMORY_INSTANCE},
};

hkStatisticsCollectorClassListener::hkStatisticsCollectorClassListener()
{
}

void
hkStatisticsCollectorClassListener::removeClass(const hkClass& cls)
{
    hkPointerMap<const hkClass*,hkUint32>::Iterator iter = m_classMap.findKey(&cls);
    if (m_classMap.isValid(iter)) { m_classMap.remove(iter); }
}

void
hkStatisticsCollectorClassListener::setClass(const hkClass& cls, StatisticClass statCls)
{
    hkPointerMap<const hkClass*,hkUint32>::Iterator iter = m_classMap.findKey(&cls);
    if (m_classMap.isValid(iter))
	{
        m_classMap.setValue(iter,(hkUint32)statCls);
	}
	else
	{
        m_classMap.insert(&cls,(hkUint32)statCls);
	}
}

hkBool
hkStatisticsCollectorClassListener::findClass(const hkClass& cls, hkStatisticsCollector::StatisticClass& statClsOut)
{
    // Look it up in a map
	// Chain to the map
    hkPointerMap<const hkClass*,hkUint32>::Iterator iter = m_classMap.findKey(&cls);
    if (m_classMap.isValid(iter))
	{
        statClsOut = (hkStatisticsCollector::StatisticClass)(m_classMap.getValue(iter));
        return true;
	}
    return false;
}

hkStatisticsCollector::StatisticClass
hkStatisticsCollectorClassListener::getStatisticClass( const hkClass& cls)
{
    /// Okay lets see if we can find the class
    const hkClass* cur = &cls;

    do
    {
        hkPointerMap<const hkClass*,hkUint32>::Iterator iter = m_classMap.findKey(cur);
        if (m_classMap.isValid(iter))
        {
            return (hkStatisticsCollector::StatisticClass)(m_classMap.getValue(iter));
        }
            /// Try the parent
        cur = cur->getParent();
    }
	while (cur);

    return getByNameStatisticClass(cls);
}

hkStatisticsCollector::StatisticClass
hkStatisticsCollectorClassListener::getByNameStatisticClass( const hkClass& cls)
{
    /// Okay lets see if we can find the class
    const hkClass* cur = &cls;
    do
    {
        hkStatisticsCollector::StatisticClass statCls;
        if (findByNameClass(cls, statCls)) { return statCls; }
            /// Try the parent
        cur = cur->getParent();
    }
	while (cur);

	// If doesn't have a vtable then it can't be shared easily - so assume its per instance
	return cls.hasVtable()?hkStatisticsCollector::MEMORY_SHARED:hkStatisticsCollector::MEMORY_INSTANCE;    
}

hkBool
hkStatisticsCollectorClassListener::findByNameClass(const hkClass& cls, hkStatisticsCollector::StatisticClass& statClsOut)
{
    int size = (int)(sizeof(g_nameClass)/sizeof(g_nameClass[0]));

    for (int i=0;i<size;i++)
    {
        if (hkString::strCmp(g_nameClass[i].name,cls.getName())==0)
        {
            statClsOut = g_nameClass[i].cls;
            return true;
        }
    }

    return false;
}

HK_SINGLETON_IMPLEMENTATION(hkStatisticsCollectorClassListener);


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
