/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Common/hkpMaterial.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Common/hkpMaterial.h>



//
// Enum hkpMaterial::ResponseType
//
static const hkInternalClassEnumItem hkpMaterialResponseTypeEnumItems[] =
{
	{0, "RESPONSE_INVALID"},
	{1, "RESPONSE_SIMPLE_CONTACT"},
	{2, "RESPONSE_REPORTING"},
	{3, "RESPONSE_NONE"},
	{4, "RESPONSE_MAX_ID"},
};
static const hkInternalClassEnum hkpMaterialEnums[] = {
	{"ResponseType", hkpMaterialResponseTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpMaterialResponseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMaterialEnums[0]);

//
// Class hkpMaterial
//
HK_REFLECTION_DEFINE_SIMPLE(hkpMaterial);
const hkInternalClassMember hkpMaterial::Members[] =
{
	{ "responseType", HK_NULL, hkpMaterialResponseTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpMaterial,m_responseType), HK_NULL },
	{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMaterial,m_friction), HK_NULL },
	{ "restitution", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMaterial,m_restitution), HK_NULL }
};
extern const hkClass hkpMaterialClass;
const hkClass hkpMaterialClass(
	"hkpMaterial",
	HK_NULL, // parent
	sizeof(hkpMaterial),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpMaterialEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpMaterial::Members),
	HK_COUNT_OF(hkpMaterial::Members),
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
