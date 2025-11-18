/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/Memory/hctSceneExportMemory.h>

extern void*	(*hkSystemMalloc)(int size, int align);
extern void		(*hkSystemFree) (void* p);

#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/Scratchpad/hkScratchpad.h>
#include <Common/Base/System/Io/StreambufFactory/hkDefaultStreambufFactory.h>
#include <Common/Base/System/hkBaseSystem.h>

class EmptyScratchpad : public hkScratchpad
{
public:

	EmptyScratchpad() : hkScratchpad(0,0) { }
};


static char* stackBuffer;

void hkSceneExportMemory::threadSafeBaseSystemInit()
{ 
	// Initialize the base system
	hkMemory* mem = new hkPoolMemory();
	hkThreadMemory *thrMem = new hkThreadMemory(mem,16);
	hkBaseSystem::init( mem, thrMem, (hkErrorReportFunction)(printf) );
	
	// Since init() adds a reference to both mem and thrMem, remove these references
	mem->removeReference();
	thrMem->removeReference();

	// We now initialize the stack area to 1Mb (fast temporary memory to be used by the engine).
	int stackSize = 0x100000;
	stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE );
	hkThreadMemory::getInstance().setStackArea( stackBuffer, stackSize);

    hkScratchpad::replaceInstance( new EmptyScratchpad() );

	// These asserts are no longer useful - we're using a fake scratchpad.
	hkError::getInstance().setEnabled( 0x20ad62c3, false );
	hkError::getInstance().setEnabled( 0x651498c4, false );

	hkMonitorStream::init();
}

void hkSceneExportMemory::threadSafeBaseSystemQuit()
{
	hkDeallocate(stackBuffer);
	hkBaseSystem::quit();	
}

void hkSceneExportMemory::getBaseSystemInfo( hctBaseDll::BaseSystemInfo& baseSystemInfo )
{
	baseSystemInfo.m_memory = &hkMemory::getInstance();
	baseSystemInfo.m_threadMemory = &hkThreadMemory::getInstance();
	baseSystemInfo.m_streamBufFactory = &hkStreambufFactory::getInstance();
	baseSystemInfo.m_error = &hkError::getInstance();
	baseSystemInfo.m_scratchPad = &hkScratchpad::getInstance();
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
