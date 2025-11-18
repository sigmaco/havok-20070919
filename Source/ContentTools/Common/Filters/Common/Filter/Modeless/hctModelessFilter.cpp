/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Monitor/hkMonitorStream.h>


hctModelessFilter::hctModelessFilter (const class hctFilterManagerInterface* owner) : hctFilterInterface (owner), m_filterThread(0)
{

}

hctModelessFilter::~hctModelessFilter ()
{
	if (m_filterThread) // if == 0, then in throws of shut down or is gone already
	{
		CloseHandle( m_filterThread );
		m_filterThread = HK_NULL; 
	}
}

struct _ThreadProcessingData
{
	hctModelessFilter* m_filter;
	hkRootLevelContainer* m_contents;

};

DWORD WINAPI _modelessFilterThreadFunc( LPVOID lpParam ) 
{ 
	_ThreadProcessingData* data = (_ThreadProcessingData*) (lpParam);
	hctModelessFilter* filter = data->m_filter;

	// setup our local thread memory
	// Initialize the thread memory for this thread, referencing the global memory instance
	hkThreadMemory threadMemory(&hkMemory::getInstance(), 16);

	// Due to the fact that all the DLLs that created the data for this preview
	// have their own TLS slot for the per thread memory etc, we have to propagate that
	// back though them all.. 
	{
		// call hkBaseSystem::initThread( &threadMemory ); on all DLLs known to manager (including this one, so we don't need to call it explicitly)
		filter->getFilterManager()->setThreadData(&threadMemory);
	}

	// Allocate stack memory for this thread 
	char* stackBuffer;
	{
		int stackSize = 2000000; // Stack size of 2 Mb.
		stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE);
		threadMemory.setStackArea( stackBuffer, stackSize);
	}

	// Allocate a monitor stream for this thread - this  enables timers.
	{
		hkMonitorStream::init(); // can alloc if we want to add timers to preview
	}

	// Do the processing
	filter->modalProcess(*data->m_contents);

	filter->getDescriptor().removeFilterFromActiveList(filter);

	threadMemory.setStackArea(0, 0);
	hkDeallocate(stackBuffer);
	hkBaseSystem::clearThreadResources();

	delete data;

	return 0;
}


/*virtual*/ void hctModelessFilter::process( hkRootLevelContainer& contents, bool batchMode )
{
	if( batchMode ) return;

	// Current state (to simulate etc with):
	hkRootLevelContainer* clonedContents = (hkRootLevelContainer*)hctFilterUtils::deepCopyObject(m_filterManager->getFilterClassRegistry(), &contents, &hkRootLevelContainerClass, m_cloneStorage);

	if (behaveAsModal())
	{
		modalProcess(*clonedContents);
		return;
	}


	// else

	// We add it before creating the thread since we need to make sure the filter is not deleted while the thread starts
	// Thread will remove itself when finished
	getDescriptor().addFilterToActiveList(this);

	// Create preview thread:
	DWORD dwThreadId;

	_ThreadProcessingData* threadData = new _ThreadProcessingData;
	threadData->m_filter = this;
	threadData->m_contents = clonedContents;

	m_filterThread = CreateThread( 
		NULL, // default security attributes
		0, // default stack size
		_modelessFilterThreadFunc,
		(LPVOID)threadData, // arg
		0, // default creation flags
		&dwThreadId); // returns the thread identifier

	if (m_filterThread == NULL) // wasn't created..
	{
		HK_WARN_ALWAYS(0xabbadea3, "Couldn't create thread for modeless filter");
	}
}

/*virtual*/ bool hctModelessFilter::behaveAsModal () const
{
	return false;
}

/*virtual*/ bool hctModelessFilter::isClosingDown () const
{
	return false;
}

bool hctModelessFilter::isThreadActive () const
{
	DWORD ec;
	return (m_filterThread && GetExitCodeThread(m_filterThread, &ec) && (ec == STILL_ACTIVE));
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
