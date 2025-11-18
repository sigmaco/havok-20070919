/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <ContentTools/Common/Filters/Common/hctBaseDll.h>

#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/Scratchpad/hkScratchpad.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>


/*static*/ unsigned int  hctBaseDll::getCurrentDllVersion ()
{
	return HCT_CURRENT_VERSION;
}

hctBaseDll::hctBaseDll (HMODULE dllModule) : m_dllModule(dllModule)
{

}

/*virtual*/ HMODULE hctBaseDll::getDllModule() const
{
	return m_dllModule;
}

/*virtual*/ unsigned int hctBaseDll::getDllVersion() const
{
	return getCurrentDllVersion();
}

/*virtual*/ void hctBaseDll::initDll (const BaseSystemInfo* baseSystemInfo )
{
	extern hkBool hkBaseSystemIsInitialized;

	hkMemory::replaceInstance(baseSystemInfo->m_memory);

	hkThreadMemory::replaceInstance(baseSystemInfo->m_threadMemory);

	if (baseSystemInfo->m_streamBufFactory) baseSystemInfo->m_streamBufFactory->addReference();
	hkStreambufFactory::replaceInstance(baseSystemInfo->m_streamBufFactory);

	if (baseSystemInfo->m_error) baseSystemInfo->m_error->addReference();
	hkError::replaceInstance(baseSystemInfo->m_error);

	if (baseSystemInfo->m_scratchPad) baseSystemInfo->m_scratchPad->addReference();
	hkScratchpad::replaceInstance(baseSystemInfo->m_scratchPad);

	hkBaseSystem::initSingletons();

	hkMonitorStream::init();

	hkMultiThreadCheck::staticInit();

	hkBaseSystemIsInitialized = true;
}

/*virtual*/ void hctBaseDll::quitDll ()
{
	hkBaseSystem::quit();
}

/*virtual*/ void hctBaseDll::initThread (hkThreadMemory* threadMemory )
{
	hkBaseSystem::initThread (threadMemory);
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
