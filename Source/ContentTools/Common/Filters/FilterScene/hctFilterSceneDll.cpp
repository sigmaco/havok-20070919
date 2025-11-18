/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/hctFilterSceneDll.h>

// Filters we want to expose in this dll:
#include <ContentTools/Common/Filters/FilterScene/RemoveScale/hctRemoveScaleFilter.h>
#include <ContentTools/Common/Filters/FilterScene/SceneTransform/hctSceneTransformFilter.h>
#include <ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterFilter.h>
#include <ContentTools/Common/Filters/FilterScene/AlterMesh/hctAlterMeshFilter.h>
#include <ContentTools/Common/Filters/FilterScene/ConvertTexturesToPng/hctConvertTexturesToPNGFilter.h>
#include <ContentTools/Common/Filters/FilterScene/CreateTangents/hctCreateTangentsFilter.h>
#include <ContentTools/Common/Filters/FilterScene/RemoveTexturePaths/hctRemoveTexturePathsFilter.h>
#include <ContentTools/Common/Filters/FilterScene/FindInstances/hctFindInstancesFilter.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>

__declspec( dllexport ) hctFilterDll* getFilterDll (HMODULE dllModule)
{
	static hctFilterSceneDll gFilterSceneDll (dllModule);

	return &gFilterSceneDll;
}


hctFilterSceneDll::hctFilterSceneDll (HMODULE dllModule) : hctFilterDll (dllModule) 
{
}

/*virtual*/ int hctFilterSceneDll::getNumberOfFilters() const
{ 
	return 8; 
}

/*virtual*/ hctFilterDescriptor* hctFilterSceneDll::getFilterDescriptor (int index) const
{
	static hctFilterDescriptor* m_filterDescs[] = 
	{
		&g_removeScaleDesc,
		&g_sceneTransformDesc,
		&g_platformWriterDesc,
		&g_alterMeshDesc,
		&g_convertTexturesToPNGDesc,
		&g_createTangentsDesc,
		&g_removeTexturePathsDesc,
		&g_findInstancesDesc
	};

	return m_filterDescs[index];
}

/*virtual*/ void hctFilterSceneDll::registerClasses (hctFilterClassRegistry& classReg) const
{
	classReg.registerClasses (hkBuiltinTypeRegistry::StaticLinkedTypeInfos, hkBuiltinTypeRegistry::StaticLinkedClasses);
}


// Scene Data classes only
#define HK_CLASSES_FILE <Common/scenedata/classes/hkScenedataClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>

// NO COMPATIBILITY NEEDED
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
