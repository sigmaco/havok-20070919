/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/Brake/Default/hkpVehicleDefaultBrake.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/Brake/Default/hkpVehicleDefaultBrake.h>



// External pointer and enum types
extern const hkClass hkpVehicleDefaultBrakeWheelBrakingPropertiesClass;

//
// Class hkpVehicleDefaultBrake::WheelBrakingProperties
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleDefaultBrake,WheelBrakingProperties);
static const hkInternalClassMember hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members[] =
{
	{ "maxBreakingTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultBrake::WheelBrakingProperties,m_maxBreakingTorque), HK_NULL },
	{ "minPedalInputToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultBrake::WheelBrakingProperties,m_minPedalInputToBlock), HK_NULL },
	{ "isConnectedToHandbrake", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultBrake::WheelBrakingProperties,m_isConnectedToHandbrake), HK_NULL }
};
const hkClass hkpVehicleDefaultBrakeWheelBrakingPropertiesClass(
	"hkpVehicleDefaultBrakeWheelBrakingProperties",
	HK_NULL, // parent
	sizeof(hkpVehicleDefaultBrake::WheelBrakingProperties),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members),
	HK_COUNT_OF(hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleDefaultBrake
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpVehicleDefaultBrake);
static const hkInternalClassMember hkpVehicleDefaultBrakeClass_Members[] =
{
	{ "wheelBrakingProperties", &hkpVehicleDefaultBrakeWheelBrakingPropertiesClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultBrake,m_wheelBrakingProperties), HK_NULL },
	{ "wheelsMinTimeToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultBrake,m_wheelsMinTimeToBlock), HK_NULL }
};
extern const hkClass hkpVehicleBrakeClass;

extern const hkClass hkpVehicleDefaultBrakeClass;
const hkClass hkpVehicleDefaultBrakeClass(
	"hkpVehicleDefaultBrake",
	&hkpVehicleBrakeClass, // parent
	sizeof(hkpVehicleDefaultBrake),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultBrakeClass_Members),
	HK_COUNT_OF(hkpVehicleDefaultBrakeClass_Members),
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
