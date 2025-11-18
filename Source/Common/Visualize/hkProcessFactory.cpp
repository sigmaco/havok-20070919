/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/hkProcess.h>
#include <Common/Visualize/hkProcessFactory.h>
#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

hkProcessFactory::hkProcessFactory()
: m_freeTag(0)
{
	m_criticalSection = new hkCriticalSection(2000);
}

hkProcessFactory::~hkProcessFactory()
{
	delete m_criticalSection;
}

int hkProcessFactory::registerProcess(const char* viewerName, hkProcessCreationFunction creationFunction)
{
	//HK_VISUAL_DEBUGGER_INFO(1, "Registering viewer \"" << viewerName << "\"");

	ProcessIdPair* pair = HK_NULL;

	m_criticalSection->enter();

	// check viewer is not already registered
	for(int i = 0; i < m_name2creationFunction.getSize(); i++)
	{
		if( m_name2creationFunction[i].m_name == viewerName )
		{
			pair = &m_name2creationFunction[i];

			if ( m_name2creationFunction[i].m_processCreationFunction != creationFunction )
			{
				HK_ASSERT2(0x7ce319a1,  0, "You are trying to register two different process with the same name - only the first instance will be used" );
			}
			break;
		}
	}

	if( pair == HK_NULL )
	{
		pair = m_name2creationFunction.expandBy(1);
		pair->m_name = viewerName;
		pair->m_processCreationFunction = creationFunction;
		pair->m_tag = m_freeTag++;
	}

	m_criticalSection->leave();

	return pair->m_tag;
}

const char* hkProcessFactory::getProcessName(int id)
{
	m_criticalSection->enter();
	const char* name = m_name2creationFunction[id].m_name.cString();
	m_criticalSection->leave();
	return name;
}

int hkProcessFactory::getProcessId(const char* name)
{
	m_criticalSection->enter();
	for(int i = 0; i < m_name2creationFunction.getSize(); i++)
	{
		hkString& pname = m_name2creationFunction[i].m_name;
		if( pname == name )
		{
			m_criticalSection->leave();
			return i;
		}
	}
	m_criticalSection->leave();
	return -1;
}

hkProcess* hkProcessFactory::createProcess(int tag, hkArray<hkProcessContext*>& contexts)
{
	hkCriticalSectionLock lock( m_criticalSection );
	
	HK_ASSERT2(0x7ce319a2, (tag >=0) && (tag < m_freeTag) && 
		(tag < m_name2creationFunction.getSize()), "VDB: Process tag out of range");

	hkProcess* p = m_name2creationFunction[tag].m_processCreationFunction(contexts);

	return p;
}

hkProcess* hkProcessFactory::createProcess(const char* processName, hkArray<hkProcessContext*>& contexts)
{
	hkCriticalSectionLock lock( m_criticalSection );
	int id = getProcessId(processName);
	return id < 0? HK_NULL : createProcess(id, contexts);
}

#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#endif

HK_SINGLETON_IMPLEMENTATION(hkProcessFactory); 

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
