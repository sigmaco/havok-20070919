/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/hkBase.h>

#include <Physics/Dynamics/World/hkpWorld.h>

//#define HK_DISABLE_DEBUG_DISPLAY
#include <Common/Visualize/hkProcessFactory.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessHandler.h>

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldSnapshotViewer.h>
#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>

#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

int hkpWorldSnapshotViewer::m_tagPC = 0;
int hkpWorldSnapshotViewer::m_tagNative = 0;

void HK_CALL hkpWorldSnapshotViewer::registerViewer()
{
	m_tagNative = hkProcessFactory::getInstance().registerProcess( getNameNative(), createNative );
	m_tagPC = hkProcessFactory::getInstance().registerProcess( getNamePC(), createPC  );
}

hkProcess* HK_CALL hkpWorldSnapshotViewer::createNative(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpWorldSnapshotViewer(contexts, false);
}

hkProcess* HK_CALL hkpWorldSnapshotViewer::createPC(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpWorldSnapshotViewer(contexts, true);
}

hkpWorldSnapshotViewer::hkpWorldSnapshotViewer(const hkArray<hkProcessContext*>& contexts, bool convertToPC)
: hkpWorldViewerBase( contexts), m_convert(convertToPC)
{
	
}

void hkpWorldSnapshotViewer::init()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
			worldAddedCallback( m_context->getWorld(i));
	}
}

hkpWorldSnapshotViewer::~hkpWorldSnapshotViewer()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			worldRemovedCallback( m_context->getWorld(i));
		}
	}
}

void hkpWorldSnapshotViewer::step( hkReal frameTimeInMs )
{
	// step once, send the HKX file in full (in native console format, so less likely to hit any serialization issues)
	if (m_outStream)
	{
		hkArray<char> storage;
		storage.reserve(100*1024); // 100KB
		hkArrayStreamWriter sw(&storage, hkArrayStreamWriter::ARRAY_BORROW);

		const hkStructureLayout::LayoutRules& layout = m_convert? hkStructureLayout::MsvcWin32LayoutRules : hkStructureLayout::HostLayoutRules;
		
		for (int w=0; w < m_context->getNumWorlds(); ++w)
		{
			storage.setSize(0);

			hkpHavokSnapshot::save(m_context->getWorld(w), &sw, true, &layout );

			// if (m_convert)
			int snapShotLength = storage.getSize();
			if (snapShotLength < 1)
				continue;
			
			const int packetSize = (1*5) + 4 + snapShotLength;

			// the packet header
			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkpWorldSnapshotViewer::HK_SNAPSHOT);
			
			// the layout the snapshot is in
			m_outStream->write8u(layout.m_bytesInPointer);
			m_outStream->write8u(layout.m_littleEndian);
			m_outStream->write8u(layout.m_reusePaddingOptimization);
			m_outStream->write8u(layout.m_emptyBaseClassOptimization);
			
			// Snapshot itself
			m_outStream->write32(snapShotLength);
			m_outStream->writeRaw(storage.begin(), snapShotLength);
			
		//	bool streamOK = (m_outStream && m_outStream->isOk());
		}
	}

	// Now we have done the work, we can turn ourselves off.
	if (m_processHandler)
	{
		m_processHandler->deleteProcess( m_convert? m_tagPC : m_tagNative );

		//as our name has a '*' in it, the VDB clients will expect us to have deleted ourselves, so should be fine.
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
