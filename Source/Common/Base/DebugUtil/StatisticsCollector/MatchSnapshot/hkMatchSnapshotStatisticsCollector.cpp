/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/Reflection/hkClass.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Base/Memory/hkDebugMemorySnapshot.h>

// this
#include <Common/Base/DebugUtil/StatisticsCollector/MatchSnapshot/hkMatchSnapshotStatisticsCollector.h>

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                         hkAllocationSet

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

hkAllocationSet::hkAllocationSet(const void* ptr,const hkDebugMemory::PointerInfo* info):
    m_totalAllocs(1),
    m_numAllocs(1),
    m_info(info),
    m_next(HK_NULL)
{
    m_allocs[0] = ptr;
}

void hkAllocationSet::addAlloc(const void* ptr,const hkDebugMemory::PointerInfo* info)
{
    m_totalAllocs++;
    if (m_numAllocs<MAX_ALLOCS)
    {
        m_allocs[m_numAllocs++] = ptr;
    }
}

hkBool hkAllocationSet::matches(int traceDepth,const void* ptr,const hkDebugMemory::PointerInfo* info)
{
    int minTrace = m_info->numStackTrace<info->numStackTrace?m_info->numStackTrace:info->numStackTrace;
    if (traceDepth<minTrace) minTrace = traceDepth;

    /// Compare the traces
    for (int i=0;i<minTrace;i++)
    {
        if (m_info->stackTraces[i] != info->stackTraces[i]) return false;
    }
    return true;
}

void HK_CALL hkAllocationSet::_printFunc(const char* text, void* context)
{
    hkOstream* stream =(hkOstream*)context;
    (*stream) << text;
}

void HK_CALL hkAllocationSet::_concatFunc(const char* text, void* context)
{
    hkString* string =(hkString*)context;
    (*string) += text;
}


void hkAllocationSet::dump(hkMatchSnapshotStatisticsCollector& collector)
{
    const hkDebugMemory::PointerInfo* info = m_info;

    hkOstream& stream = collector.m_stream;

    if (info)
    {
		stream.printf("\n");
		stream.printf("***********************************************************\n");
		stream.printf("* %2i blocks of size %6i not included in calcStatistics *\n", m_totalAllocs, m_info->numBytes);
		stream.printf("***********************************************************\n");
    }

	stream.printf("Blocks: ");
	// Dump out the pointers we have
    for (int i=0;i<m_numAllocs;i++)
    {
        stream << m_allocs[i] <<" ";
    }
    if (m_totalAllocs>m_numAllocs) stream << "...";
    stream <<"\n";

    // Do the stack track if we can
    if (info)
    {
        if (m_numAllocs>1) { stream<<"    NOTE! Not all allocs may have exactly this trace...\n"; }
        // Do the track trace
        collector.m_tracer.dumpStackTrace( info->stackTraces, info->numStackTrace, _printFunc, (void*)&stream);
        stream<<"\n";
    }
    stream << "\n";
}

hkString
hkAllocationSet::getCallStackString(hkMatchSnapshotStatisticsCollector& collector)
{
    const hkDebugMemory::PointerInfo* info = m_info;
    if (!info)
    {
        // If we don't have the pointer there is no call stack string
        return "";
    }

    hkString string;
    collector.m_tracer.dumpStackTrace( info->stackTraces, info->numStackTrace, _concatFunc, (void*)&string);
    return string;
}

hkBool hkAllocationSet::callStackContainsString(hkMatchSnapshotStatisticsCollector& collector,const hkString& in)
{
    const hkDebugMemory::PointerInfo* info = m_info;
    if (!info)
    {
        // If we don't have the pointer - we can't match
        return false;
    }
    hkString string = getCallStackString(collector);
    // See if we find in in the string
    return hkString::strStr(string.cString(), in.cString()) != HK_NULL;
}


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                      hkReportStatisticsCollector

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


hkMatchSnapshotStatisticsCollector::hkMatchSnapshotStatisticsCollector(const hkDebugMemorySnapshot& snapshot,hkOstream& stream):
	m_stream(stream),
    m_snapshot(snapshot)
{
    // Add all of the chunks
    for (int i=0;i<snapshot.m_size;i++)
    {
        void* ptr = snapshot.m_pointers[i];
		if (ptr == HK_NULL) continue;

        hkDebugMemory::PointerInfo* info = &snapshot.m_info[i];

        m_chunks.insert(ptr,info);

        // add all of the blocks we haven't yet reached
        m_notReached.insert(ptr,1);
    }
}

void hkMatchSnapshotStatisticsCollector::addCallStackIgnoreString(const hkString& in)
{
    if (m_callStackIgnoreStrings.indexOf(in)>=0)
    {
        return;
    }
    m_callStackIgnoreStrings.pushBack(in);
}


void hkMatchSnapshotStatisticsCollector::addReached( const hkDebugMemorySnapshot& snapshot)
{
    for (int i=0;i<snapshot.m_size;i++)
    {
        void* ptr = snapshot.m_pointers[i];
        if (ptr == HK_NULL) continue;

        hkPointerMap<const void*,int>::Iterator iter = m_notReached.findKey(ptr);
        if (m_notReached.isValid(iter))
        {
            /// Well we reached it now
            m_notReached.setValue(iter,0);
        }
    }
}

void hkMatchSnapshotStatisticsCollector::addChunk( const char* name, StatisticClass statCls, const void* chunkAddress, int usedSize, int allocatedSize)
{
    if (chunkAddress == HK_NULL) return;

    // Lookup
    hkPointerMap<const void*,int>::Iterator iter = m_notReached.findKey(chunkAddress);
    if (m_notReached.isValid(iter))
    {
        /// Well we reached it now
        m_notReached.setValue(iter,0);
        return;
    }
    if (name) m_stream <<name<<" ";
    m_stream  <<"Unknown chunk: "<< chunkAddress<<" "<<usedSize<<"\n";

	_dumpStackTraceForUnknown(chunkAddress);
}

void hkMatchSnapshotStatisticsCollector::_dumpStackTraceForUnknown(const void* ptr)
{
	hkMemory* mem = &hkMemory::getInstance();
	if (mem->isDebugMemory())
	{
		hkDebugMemory* debugMem = static_cast<hkDebugMemory*>(mem);
		hkDebugMemory::PointerInfo info;
		if (debugMem->getPointerInfo(ptr,info))
		{
            m_stream <<"Stack dump of allocation:\n";

			m_tracer.dumpStackTrace( info.stackTraces, info.numStackTrace, _printFunc, (void*)&m_stream);
			m_stream<<"\n";
		}
        else
        {
            m_stream <<"Could not find a matching allocation in hkDebugMemory!\n";
            m_stream <<"Stack dump of current call stack (_NOT_ allocation) follows:\n";
            hkUlong trace[MAX_TRACE];
            int numTrace = m_tracer.getStackTrace( trace,MAX_TRACE);
            m_tracer.dumpStackTrace( trace, numTrace, _printFunc, (void*)&m_stream);
        }
	}
}

hkBool hkMatchSnapshotStatisticsCollector::_notReachable(const void* ptr)
{
	hkPointerMap<const void*,int>::Iterator iter = m_notReached.findKey(ptr);
	return !m_notReached.isValid(iter);
}


void hkMatchSnapshotStatisticsCollector::addChildObject( const char* name, StatisticClass statCls, const hkReferencedObject* obj )
{
    if (_isKnown(obj)||obj==HK_NULL) { return; }

	// See if we know this

	if (_notReachable((const void*)obj))
	{
        // FInd the type
        hkVtableClassRegistry* reg = hkBuiltinTypeRegistry::getInstance().getVtableClassRegistry();
        const hkClass* cls = reg->getClassFromVirtualInstance((void*)obj);

        m_stream << "Unknown chunk : "<<(cls?cls->getName():"Unknown") << "@" << obj <<"\n";
		_dumpStackTraceForUnknown((const void*)obj);
	}
	else
	{
		// We need to add this objects memory
		if (obj->m_memSizeAndFlags != 0)
		{
			// We need to add the memory of the object itself
			int usedSize = obj->m_memSizeAndFlags&obj->MASK_MEMSIZE;
			// Work out the allocated space
			int allocatedSize = hkMemory::getInstance().getAllocatedSize(usedSize);
			// Add the chunk
			addChunk( "ObjAlloc", statCls, (const void*)obj,usedSize, allocatedSize);
		}
	}
    // Recurse
    obj->calcStatistics(this);
}

void hkMatchSnapshotStatisticsCollector::beginObject( const char* name, StatisticClass statCls, const hkReferencedObject* obj )
{
    if (_isKnown(obj)||obj==HK_NULL) { return; }
    _addKnown(obj);
}

hkBool hkMatchSnapshotStatisticsCollector::_isKnown(const hkReferencedObject* obj)
{
    hkPointerMap<const hkReferencedObject*,int>::Iterator iter = m_knownObjects.findKey(obj);
    return m_knownObjects.isValid(iter);
}

void hkMatchSnapshotStatisticsCollector::_addKnown(const hkReferencedObject* obj)
{
    hkPointerMap<const hkReferencedObject*,int>::Iterator iter = m_knownObjects.findKey(obj);
    if (m_knownObjects.isValid(iter)) { return; }
    m_knownObjects.insert(obj,1);
}

void HK_CALL hkMatchSnapshotStatisticsCollector::_printFunc(const char* text, void* context)
{
    hkOstream* stream =(hkOstream*)context;
    (*stream) << text;
}



void hkMatchSnapshotStatisticsCollector::dumpRemaining()
{
	m_stream << "\n\n";
    m_stream << "*********************************************************************\n";
	m_stream << "* Dump of allocations which weren't included in the calcStatistics: *\n";
	m_stream << "*********************************************************************\n";
	m_stream << "\n\n";

    hkPointerMap<const void*,int>::Iterator notReachedIter = m_notReached.getIterator();

	const int traceDepth = 8;

    hkPointerMap<int,hkAllocationSet*> sizeToSetMap;
    while (m_notReached.isValid(notReachedIter))
    {
        const void* ptr = m_notReached.getKey(notReachedIter);
        int notReached = m_notReached.getValue(notReachedIter);

        if (notReached)
        {
            // Get the block
            hkPointerMap<const void*,const hkDebugMemory::PointerInfo*>::Iterator chunkIter = m_chunks.findKey(ptr);
            if (m_chunks.isValid(chunkIter))
            {
                const hkDebugMemory::PointerInfo* info = m_chunks.getValue(chunkIter);

                /// Try adding to the map
                hkPointerMap<int,hkAllocationSet*>::Iterator iter = sizeToSetMap.findKey(info->numBytes);
                if (sizeToSetMap.isValid(iter))
                {
                    // Lets search down the list
                    hkAllocationSet* cur = sizeToSetMap.getValue(iter);
                    while (cur)
                    {
                        if (cur->matches(traceDepth,ptr,info))
                        {
                            cur->addAlloc(ptr,info);
                            break;
                        }
                        cur = cur->m_next;
                    }
                    if (cur == HK_NULL)
                    {
                        hkAllocationSet* alloc = new hkAllocationSet(ptr,info);
                        // Put in linked list
                        alloc->m_next = sizeToSetMap.getValue(iter);
                        sizeToSetMap.setValue(iter,alloc);
                    }
                }
                else
                {
                    hkAllocationSet* alloc = new hkAllocationSet(ptr,info);
                    sizeToSetMap.insert(info->numBytes,alloc);
                }

               /* m_stream << ptr << " " << info->numBytes << " was not reached.\n";
                // Do the track trace
                m_tracer.dumpStackTrace( info->stackTraces, info->numStackTrace, _printFunc, (void*)&m_stream);
                m_stream<<"\n"; */
            }
            else
            {
                m_stream << ptr << " was not reached.\n";
            }
        }
        notReachedIter = m_notReached.getNext(notReachedIter);
    }

	{
		// Okay lets sort the allocations by size, and dump them out
		hkArray<hkAllocationSet*> allocs;
		hkPointerMap<int,hkAllocationSet*>::Iterator iter = sizeToSetMap.getIterator();
		while (sizeToSetMap.isValid(iter))
		{
			allocs.pushBack(sizeToSetMap.getValue(iter));
			iter = sizeToSetMap.getNext(iter);
		}
		// Sort them
		hkSort(allocs.begin(),allocs.getSize(),_compareAllocs);

		for (int allocI=0;allocI<allocs.getSize();allocI++)
		{
			hkAllocationSet* alloc = allocs[allocI];

            do
            {
                hkBool found = false;
                if (m_callStackIgnoreStrings.getSize() > 0)
                {
                    hkString callString = alloc->getCallStackString(*this);

                    // See if it has matching strings
                    for (int stringI = 0; stringI < m_callStackIgnoreStrings.getSize(); stringI++)
                    {
                        if (hkString::strStr(callString.cString(), m_callStackIgnoreStrings[stringI].cString()))
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    alloc->dump(*this);
                }

                hkAllocationSet* next = alloc->m_next;
                delete alloc;
                    /// Onto next of same size
                alloc = next;
            }
            while (alloc);
		}
	}
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
