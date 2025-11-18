/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterViewXml/hctFilterViewXml.h>

#include <ContentTools/Common/Filters/FilterViewXml/hctFilterViewXmlDll.h>

#include <Common/Base/Memory/Scratchpad/hkScratchpad.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Error/hkDefaultError.h>

// Filters we want to expose in this dll:
#include <ContentTools/Common/Filters/FilterViewXml/ViewXml/hctViewXmlFilter.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>


__declspec( dllexport ) hctFilterDll* getFilterDll (HMODULE dllModule)
{
	static hctFilterViewXmlDll gFilterViewXmlDll (dllModule);

	return &gFilterViewXmlDll;
}

hctFilterViewXmlDll::hctFilterViewXmlDll (HMODULE dllModule) : 
	hctModelessFilterDll (dllModule)
{

}

/*virtual*/ int hctFilterViewXmlDll::getNumberOfFilters() const
{ 
	return 1; 
}

/*virtual*/ hctFilterDescriptor* hctFilterViewXmlDll::getFilterDescriptor (int index) const
{
	static hctFilterDescriptor* m_filterDescs[] = 
	{
		&g_viewXmlDesc,
	};

	return m_filterDescs[index];
}

/*virtual*/ void hctFilterViewXmlDll::registerClasses (hctFilterClassRegistry& classReg) const
{
	classReg.registerClasses (hkBuiltinTypeRegistry::StaticLinkedTypeInfos, hkBuiltinTypeRegistry::StaticLinkedClasses);
}

#define HK_CLASSES_FILE <Common/scenedata/classes/hkScenedataClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>

#include <Common/Compat/hkCompat_None.cxx>

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
