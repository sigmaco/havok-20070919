/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/TyreMarks/hkpTyremarksInfo.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/TyreMarks/hkpTyremarksInfo.h>



// External pointer and enum types
extern const hkClass hkpTyremarkPointClass;
extern const hkClass hkpTyremarksWheelClass;

//
// Class hkpTyremarkPoint
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpTyremarkPoint);
static const hkInternalClassMember hkpTyremarkPointClass_Members[] =
{
	{ "pointLeft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarkPoint,m_pointLeft), HK_NULL },
	{ "pointRight", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarkPoint,m_pointRight), HK_NULL }
};
const hkClass hkpTyremarkPointClass(
	"hkpTyremarkPoint",
	HK_NULL, // parent
	sizeof(hkpTyremarkPoint),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTyremarkPointClass_Members),
	HK_COUNT_OF(hkpTyremarkPointClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpTyremarksWheel
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpTyremarksWheel);
static const hkInternalClassMember hkpTyremarksWheelClass_Members[] =
{
	{ "currentPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarksWheel,m_currentPosition), HK_NULL },
	{ "numPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarksWheel,m_numPoints), HK_NULL },
	{ "tyremarkPoints", &hkpTyremarkPointClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpTyremarksWheel,m_tyremarkPoints), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

const hkClass hkpTyremarksWheelClass(
	"hkpTyremarksWheel",
	&hkReferencedObjectClass, // parent
	sizeof(hkpTyremarksWheel),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTyremarksWheelClass_Members),
	HK_COUNT_OF(hkpTyremarksWheelClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpTyremarksInfo
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpTyremarksInfo);
static const hkInternalClassMember hkpTyremarksInfoClass_Members[] =
{
	{ "minTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarksInfo,m_minTyremarkEnergy), HK_NULL },
	{ "maxTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTyremarksInfo,m_maxTyremarkEnergy), HK_NULL },
	{ "tyremarksWheel", &hkpTyremarksWheelClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpTyremarksInfo,m_tyremarksWheel), HK_NULL }
};

extern const hkClass hkpTyremarksInfoClass;
const hkClass hkpTyremarksInfoClass(
	"hkpTyremarksInfo",
	&hkReferencedObjectClass, // parent
	sizeof(hkpTyremarksInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTyremarksInfoClass_Members),
	HK_COUNT_OF(hkpTyremarksInfoClass_Members),
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
