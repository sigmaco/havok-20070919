/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

hctFilterDll::hctFilterDll (HMODULE dllModule) : hctBaseDll (dllModule), m_previousMemoryManager (HK_NULL)
{

}

/*virtual*/  void hctFilterDll::pushMemoryManager (hkMemory* newMemory)
{
	HK_ASSERT2(0xabbaade9, !m_previousMemoryManager, "Cannot push more than one memory manager");

	m_previousMemoryManager = &hkMemory::getInstance();
	m_previousMemoryManager->addReference(); // Add ref

	hkMemory::replaceInstance(newMemory); 

}

/*virtual*/  void hctFilterDll::popMemoryManager ()
{
	HK_ASSERT2(0xabbaadea, m_previousMemoryManager, "No memory manager to pop");

	hkMemory::replaceInstance(m_previousMemoryManager);

	m_previousMemoryManager->removeReference();
	m_previousMemoryManager=HK_NULL;
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
