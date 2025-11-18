/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/Suspension/hkpVehicleSuspension.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/Suspension/hkpVehicleSuspension.h>



// External pointer and enum types
extern const hkClass hkpVehicleSuspensionSuspensionWheelParametersClass;

//
// Class hkpVehicleSuspension::SuspensionWheelParameters
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleSuspension,SuspensionWheelParameters);
static const hkInternalClassMember hkpVehicleSuspension_SuspensionWheelParametersClass_Members[] =
{
	{ "hardpointCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleSuspension::SuspensionWheelParameters,m_hardpointCs), HK_NULL },
	{ "directionCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleSuspension::SuspensionWheelParameters,m_directionCs), HK_NULL },
	{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleSuspension::SuspensionWheelParameters,m_length), HK_NULL }
};
const hkClass hkpVehicleSuspensionSuspensionWheelParametersClass(
	"hkpVehicleSuspensionSuspensionWheelParameters",
	HK_NULL, // parent
	sizeof(hkpVehicleSuspension::SuspensionWheelParameters),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleSuspension_SuspensionWheelParametersClass_Members),
	HK_COUNT_OF(hkpVehicleSuspension_SuspensionWheelParametersClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleSuspension
//

static const hkInternalClassMember hkpVehicleSuspensionClass_Members[] =
{
	{ "wheelParams", &hkpVehicleSuspensionSuspensionWheelParametersClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleSuspension,m_wheelParams), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpVehicleSuspensionClass;
const hkClass hkpVehicleSuspensionClass(
	"hkpVehicleSuspension",
	&hkReferencedObjectClass, // parent
	sizeof(hkpVehicleSuspension),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleSuspensionClass_Members),
	HK_COUNT_OF(hkpVehicleSuspensionClass_Members),
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
