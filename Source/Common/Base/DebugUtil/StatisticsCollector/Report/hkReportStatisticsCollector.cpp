/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

#include <Common/Base/Reflection/hkClass.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

// this
#include <Common/Base/DebugUtil/StatisticsCollector/Report/hkReportStatisticsCollector.h>

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                        hkStatisticClassCount

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

hkStatisticClassCount::hkStatisticClassCount()
{
    reset();
}

void
hkStatisticClassCount::add(hkStatisticsCollector::StatisticClass type,int amount)
{
    m_total += amount;
    // Accumulate by class
    for (int i=0;i<COUNT_SIZE;i++)
    {
        if (type&(1<<i)) { m_count[i] += amount; }
    }
}

void
hkStatisticClassCount::reset()
{
    m_total = 0;
    for (int i=0;i<COUNT_SIZE;i++) { m_count[i] = 0; }
}

const char*
hkStatisticClassCount::_toCstring(StatisticClass type)
{
    switch (type)
    {
		case hkStatisticsCollector::MEMORY_ALL: return "All";
        case hkStatisticsCollector::MEMORY_SHARED: return "Shared";
        case hkStatisticsCollector::MEMORY_INSTANCE: return "Instance";
        case hkStatisticsCollector::MEMORY_ENGINE: return "Engine";
        case hkStatisticsCollector::MEMORY_RUNTIME: return "Runtime";
        case hkStatisticsCollector::MEMORY_APPLICATION: return"Application";
        default: return "Unknown";
    }
}

void
hkStatisticClassCount::dump(hkOstream& out)
{
	int numSet = 0;
	for (int i=0;i<COUNT_SIZE;i++)
	{
		if (m_count[i]) numSet++;
	}
	if (numSet == 0)
	{
		out <<"None\n";
		return;
	}
	if (numSet >1) { out <<"Total:"<<m_total<<"\n"; }
    for (int i=0;i<COUNT_SIZE;i++)
    {
        if (m_count[i])
        {
            out << _toCstring((StatisticClass)(1<<i)) << ":" << m_count[i] <<"\n";
        }
    }
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                      hkReportStatisticsCollector

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


hkReportStatisticsCollector::hkReportStatisticsCollector(hkOstream& stream):
    m_stream(stream),
    m_started(false)
{
}

void
hkReportStatisticsCollector::beginObject( const char* name, StatisticClass statCls, const hkReferencedObject* obj )
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth)
    {
        m_ignoreDepth++;
        return;
    }
    if (_isKnown(obj))
    {
        m_ignoreDepth = 1;
        return;
    }

    // add to known
    _addKnown(obj);

    // Output that we have an object
    _tab();

    m_stream << "*OBJECT_START* - ";

    // FInd the type
	hkVtableClassRegistry* reg = hkBuiltinTypeRegistry::getInstance().getVtableClassRegistry();
    const hkClass* cls = reg->getClassFromVirtualInstance((void*)obj);

    if (cls) _addCount(cls,statCls);

    m_stream << (cls?cls->getName():"Unknown") << "@" << obj <<" ";

    if (name) m_stream << "Field: "<<name;

    m_stream << " StatCls:  ";
    _streamAsText(statCls);

    m_stream << "\n";

    // We are down a depth
    m_depth++;
}

void
hkReportStatisticsCollector::addChunk( const char* name, StatisticClass statCls, const void* chunkAddress, int usedSize, int allocatedSize)
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth) { return; }

    // Accumulate

    m_used.add(statCls,usedSize);
    m_alloc.add(statCls,allocatedSize);
    m_num.add(statCls,1);

    // Dump out

    _tab();
    m_stream <<"*CHUNK* - ";
    if (name) m_stream << "Field: "<<name;
    m_stream << " StatCls:  ";
    _streamAsText(statCls);

    m_stream << "Addr: "<<chunkAddress<<" size: "<< usedSize<<" allocSize:" << allocatedSize;

    m_stream << "\n";
}


void
hkReportStatisticsCollector::addChildObject( const char* name, StatisticClass statCls, const hkReferencedObject* obj )
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth) { return; }
    if (_isKnown(obj)||obj==HK_NULL) { return; }


    _tab();

	m_stream <<"*CHILD* - ";

	// FInd the type
	hkVtableClassRegistry* reg = hkBuiltinTypeRegistry::getInstance().getVtableClassRegistry();
	const hkClass* cls = reg->getClassFromVirtualInstance((void*)obj);

	m_stream << (cls?cls->getName():"Unknown") << "@" << obj <<" ";

	if (name) m_stream << "Field: "<<name;

    m_stream << " StatCls:  ";
    _streamAsText(statCls);
	m_stream << "\n";

    m_depth++;

    if (obj->m_memSizeAndFlags != 0)
    {
        // We need to add the memory of the object itself
        int usedSize = obj->m_memSizeAndFlags&obj->MASK_MEMSIZE;
        // Work out the allocated space
        int allocatedSize = hkMemory::getInstance().getAllocatedSize(usedSize);
        // Add the chunk
        addChunk( "ObjAlloc", statCls, (const void*)obj,usedSize, allocatedSize);
    }

    // Recurse
    obj->calcStatistics(this);

    m_depth--;
}

void
hkReportStatisticsCollector::endObject( )
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth)
    {
        m_ignoreDepth--;
        return;
    }

    m_depth--;
    _tab();
    m_stream << "*OBJECT_END*";
    m_stream << "\n";
}

void
hkReportStatisticsCollector::pushDir( const char* dirName )
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth) { return; }

    _tab();
    m_stream <<"*DIR_START* - "<<dirName;
    m_stream << "\n";
    m_depth++;
}

void
hkReportStatisticsCollector::popDir()
{
    HK_ASSERT(0x45345335,m_started);
    if (m_ignoreDepth) { return; }

    m_depth--;
    _tab();
    m_stream <<"*DIR_END*";
    m_stream << "\n";
}

void
hkReportStatisticsCollector::start()
{
    HK_ASSERT(0x03242323,m_started==false);
    m_started = true;

    m_depth = 0;
    m_ignoreDepth = 0;

    m_used.reset();
    m_alloc.reset();
    m_num.reset();

    _clear();
}

void
hkReportStatisticsCollector::end()
{
    HK_ASSERT(0x03242323,m_started==true);
    m_started = false;

    m_stream <<"\n";

	_dumpClassCount();

    m_stream <<"\n";
    m_stream <<"Num allocs\n";
    m_stream <<"----------\n";
    m_num.dump(m_stream);

	m_stream <<"\n";
    m_stream <<"Alloc (bytes)\n";
    m_stream <<"-------------\n";
    m_alloc.dump(m_stream);

	m_stream <<"\n";
    m_stream <<"Used (bytes)\n";
    m_stream <<"------------\n";
	m_used.dump(m_stream);

    // Make sure its empty
    _clear();
}


void
hkReportStatisticsCollector::_streamAsText(StatisticClass typeIn)
{
    if (typeIn == MEMORY_ALL)
    {
        m_stream<<"All ";
        return;
    }

    int type = typeIn;

    hkBool prev = false;
    for (int bit = 1;bit<MEMORY_LAST;bit+=bit)
    {
        if (bit&type)
        {
            if (prev) { m_stream<<"|"; }
			m_stream << hkStatisticClassCount::_toCstring((StatisticClass)bit);
            prev = true;
        }
    }
    m_stream << ' ';
}

hkBool
hkReportStatisticsCollector::_isKnown(const hkReferencedObject* obj)
{
    hkPointerMap<const hkReferencedObject*,int>::Iterator iter = m_knownObjects.findKey(obj);
    return m_knownObjects.isValid(iter);
}

void
hkReportStatisticsCollector::_addKnown(const hkReferencedObject* obj)
{
    hkPointerMap<const hkReferencedObject*,int>::Iterator iter = m_knownObjects.findKey(obj);
    if (m_knownObjects.isValid(iter)) { return; }
    m_knownObjects.insert(obj,1);
}

void
hkReportStatisticsCollector::_clear()
{
    m_knownObjects.clear();

    // Okay we should now have a map of all of the face face intersections
    hkPointerMap<const hkClass*,hkStatisticClassCount*>::Iterator iter = m_typeCount.getIterator();
    while (m_typeCount.isValid(iter))
    {
        hkStatisticClassCount* count = m_typeCount.getValue(iter);
        delete count;
        iter = m_typeCount.getNext(iter);
    }
    m_typeCount.clear();
}

void
hkReportStatisticsCollector::_dumpClassCount()
{
	hkPointerMap<const hkClass*,hkStatisticClassCount*>::Iterator iter = m_typeCount.getIterator();
    while (m_typeCount.isValid(iter))
    {
        const hkClass* cls = m_typeCount.getKey(iter);
        hkStatisticClassCount* count = m_typeCount.getValue(iter);

        m_stream << cls->getName() << "\n";
		count->dump(m_stream);

        iter = m_typeCount.getNext(iter);
    }
}

void
hkReportStatisticsCollector::_addCount(const hkClass* cls,StatisticClass statCls)
{
    hkPointerMap<const hkClass*,hkStatisticClassCount*>::Iterator iter = m_typeCount.findKey(cls);
    hkStatisticClassCount* count;
    if (m_typeCount.isValid(iter))
    {
        count = m_typeCount.getValue(iter);
    }
    else
    {
        count = new hkStatisticClassCount;
        m_typeCount.insert(cls,count);
    }
    count->add(statCls,1);
}

void
hkReportStatisticsCollector::_tab()
{
    for (int i=0;i<m_depth;i++) { m_stream << "  "; }
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
