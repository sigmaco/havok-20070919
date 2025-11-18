/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h>



//
// Class hkpVehicleDriverInputAnalogStatus
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpVehicleDriverInputAnalogStatus);
static const hkInternalClassMember hkpVehicleDriverInputAnalogStatusClass_Members[] =
{
	{ "positionX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDriverInputAnalogStatus,m_positionX), HK_NULL },
	{ "positionY", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDriverInputAnalogStatus,m_positionY), HK_NULL },
	{ "handbrakeButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDriverInputAnalogStatus,m_handbrakeButtonPressed), HK_NULL },
	{ "reverseButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDriverInputAnalogStatus,m_reverseButtonPressed), HK_NULL }
};
extern const hkClass hkpVehicleDriverInputStatusClass;

extern const hkClass hkpVehicleDriverInputAnalogStatusClass;
const hkClass hkpVehicleDriverInputAnalogStatusClass(
	"hkpVehicleDriverInputAnalogStatus",
	&hkpVehicleDriverInputStatusClass, // parent
	sizeof(hkpVehicleDriverInputAnalogStatus),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleDriverInputAnalogStatusClass_Members),
	HK_COUNT_OF(hkpVehicleDriverInputAnalogStatusClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleDefaultAnalogDriverInput
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpVehicleDefaultAnalogDriverInput);
static const hkInternalClassMember hkpVehicleDefaultAnalogDriverInputClass_Members[] =
{
	{ "slopeChangePointX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultAnalogDriverInput,m_slopeChangePointX), HK_NULL },
	{ "initialSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultAnalogDriverInput,m_initialSlope), HK_NULL },
	{ "deadZone", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultAnalogDriverInput,m_deadZone), HK_NULL },
	{ "autoReverse", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleDefaultAnalogDriverInput,m_autoReverse), HK_NULL }
};
extern const hkClass hkpVehicleDriverInputClass;

extern const hkClass hkpVehicleDefaultAnalogDriverInputClass;
const hkClass hkpVehicleDefaultAnalogDriverInputClass(
	"hkpVehicleDefaultAnalogDriverInput",
	&hkpVehicleDriverInputClass, // parent
	sizeof(hkpVehicleDefaultAnalogDriverInput),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultAnalogDriverInputClass_Members),
	HK_COUNT_OF(hkpVehicleDefaultAnalogDriverInputClass_Members),
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
