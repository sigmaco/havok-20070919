/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/Filters/Common/Options/hctFilterOptionsHeaderData.h'
#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/Filters/Common/Options/hctFilterOptionsHeaderData.h>



//
// Class hctFilterData
//
HK_REFLECTION_DEFINE_SIMPLE(hctFilterData);
static const hkInternalClassMember hctFilterDataClass_Members[] =
{
	{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctFilterData,m_id), HK_NULL },
	{ "ver", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctFilterData,m_ver), HK_NULL },
	{ "hasOptions", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctFilterData,m_hasOptions), HK_NULL }
};
extern const hkClass hctFilterDataClass;
const hkClass hctFilterDataClass(
	"hctFilterData",
	HK_NULL, // parent
	sizeof(hctFilterData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctFilterDataClass_Members),
	HK_COUNT_OF(hctFilterDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hctConfigurationData
//
HK_REFLECTION_DEFINE_SIMPLE(hctConfigurationData);
static const hkInternalClassMember hctConfigurationDataClass_Members[] =
{
	{ "configurationName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctConfigurationData,m_configurationName), HK_NULL },
	{ "numFilters", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctConfigurationData,m_numFilters), HK_NULL }
};
extern const hkClass hctConfigurationDataClass;
const hkClass hctConfigurationDataClass(
	"hctConfigurationData",
	HK_NULL, // parent
	sizeof(hctConfigurationData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctConfigurationDataClass_Members),
	HK_COUNT_OF(hctConfigurationDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hctConfigurationSetData
//
HK_REFLECTION_DEFINE_SIMPLE(hctConfigurationSetData);
static const hkInternalClassMember hctConfigurationSetDataClass_Members[] =
{
	{ "filterManagerVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctConfigurationSetData,m_filterManagerVersion), HK_NULL },
	{ "activeConfiguration", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctConfigurationSetData,m_activeConfiguration), HK_NULL }
};
extern const hkClass hctConfigurationSetDataClass;
const hkClass hctConfigurationSetDataClass(
	"hctConfigurationSetData",
	HK_NULL, // parent
	sizeof(hctConfigurationSetData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctConfigurationSetDataClass_Members),
	HK_COUNT_OF(hctConfigurationSetDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

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
