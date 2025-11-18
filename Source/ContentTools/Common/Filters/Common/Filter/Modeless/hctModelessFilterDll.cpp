/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <Common/Base/Memory/Scratchpad/hkScratchpad.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>

hctModelessFilterDll::hctModelessFilterDll (HMODULE dllModule) : hctFilterDll (dllModule)
{

}

/*virtual*/ void hctModelessFilterDll::pushMemoryManager (hkMemory*)
{
	// We can't replace the memory manager during processing due to the non-modal dialogs
}

/*virtual*/ void hctModelessFilterDll::popMemoryManager ()
{
	// We can't replace the memory manager during processing due to the non-modal dialogs
}

/*static*/ void hctModelessFilterDll::errorReportFunction(const char* buf, void *obj)
{
	// just output to the debug stream and try to carry on..
	OutputDebugString( buf );
}

/*virtual*/ void hctModelessFilterDll::initDll (const BaseSystemInfo* baseSystemInfo )
{

	hkMemory::replaceInstance(baseSystemInfo->m_memory);

	hkThreadMemory::replaceInstance(baseSystemInfo->m_threadMemory);

	if (baseSystemInfo->m_streamBufFactory) baseSystemInfo->m_streamBufFactory->addReference();
	hkStreambufFactory::replaceInstance(baseSystemInfo->m_streamBufFactory);

	//  We don't use the manager's error handler as this is a modeless filter
	hkError::replaceInstance ( new hkDefaultError (errorReportFunction, HK_NULL)  );

	// Disable stack warning
	hkError::getInstance().setEnabled( 0x01983bb7, false );

	if (baseSystemInfo->m_scratchPad) baseSystemInfo->m_scratchPad->addReference();
	hkScratchpad::replaceInstance(baseSystemInfo->m_scratchPad);

	hkBaseSystem::initSingletons();

	hkMonitorStream::init();

	hkMultiThreadCheck::staticInit();

	extern hkBool hkBaseSystemIsInitialized;
	hkBaseSystemIsInitialized = true;
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
