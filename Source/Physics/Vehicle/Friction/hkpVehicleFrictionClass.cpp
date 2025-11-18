/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/Friction/hkpVehicleFriction.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/Friction/hkpVehicleFriction.h>



// External pointer and enum types
extern const hkClass hkpVehicleFrictionDescriptionAxisDescriptionClass;
extern const hkClass hkpVehicleFrictionStatusAxisStatusClass;

//
// Class hkpVehicleFrictionDescription::AxisDescription
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleFrictionDescription,AxisDescription);
static const hkInternalClassMember hkpVehicleFrictionDescription_AxisDescriptionClass_Members[] =
{
	{ "frictionCircleYtab", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 16, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_frictionCircleYtab), HK_NULL },
	{ "xStep", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_xStep), HK_NULL },
	{ "xStart", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_xStart), HK_NULL },
	{ "wheelSurfaceInertia", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelSurfaceInertia), HK_NULL },
	{ "wheelSurfaceInertiaInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelSurfaceInertiaInv), HK_NULL },
	{ "wheelChassisMassRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelChassisMassRatio), HK_NULL },
	{ "wheelRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelRadius), HK_NULL },
	{ "wheelRadiusInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelRadiusInv), HK_NULL },
	{ "wheelDownForceFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelDownForceFactor), HK_NULL },
	{ "wheelDownForceSumFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription::AxisDescription,m_wheelDownForceSumFactor), HK_NULL }
};
const hkClass hkpVehicleFrictionDescriptionAxisDescriptionClass(
	"hkpVehicleFrictionDescriptionAxisDescription",
	HK_NULL, // parent
	sizeof(hkpVehicleFrictionDescription::AxisDescription),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionDescription_AxisDescriptionClass_Members),
	HK_COUNT_OF(hkpVehicleFrictionDescription_AxisDescriptionClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleFrictionDescription
//
HK_REFLECTION_DEFINE_SIMPLE(hkpVehicleFrictionDescription);
static const hkInternalClassMember hkpVehicleFrictionDescriptionClass_Members[] =
{
	{ "wheelDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription,m_wheelDistance), HK_NULL },
	{ "chassisMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription,m_chassisMassInv), HK_NULL },
	{ "axleDescr", &hkpVehicleFrictionDescriptionAxisDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpVehicleFrictionDescription,m_axleDescr), HK_NULL }
};
extern const hkClass hkpVehicleFrictionDescriptionClass;
const hkClass hkpVehicleFrictionDescriptionClass(
	"hkpVehicleFrictionDescription",
	HK_NULL, // parent
	sizeof(hkpVehicleFrictionDescription),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionDescriptionClass_Members),
	HK_COUNT_OF(hkpVehicleFrictionDescriptionClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleFrictionStatus::AxisStatus
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleFrictionStatus,AxisStatus);
static const hkInternalClassMember hkpVehicleFrictionStatus_AxisStatusClass_Members[] =
{
	{ "forward_slip_velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_forward_slip_velocity), HK_NULL },
	{ "side_slip_velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_side_slip_velocity), HK_NULL },
	{ "skid_energy_density", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_skid_energy_density), HK_NULL },
	{ "side_force", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_side_force), HK_NULL },
	{ "delayed_forward_impulse", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_delayed_forward_impulse), HK_NULL },
	{ "sideRhs", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_sideRhs), HK_NULL },
	{ "forwardRhs", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_forwardRhs), HK_NULL },
	{ "relativeSideForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_relativeSideForce), HK_NULL },
	{ "relativeForwardForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus::AxisStatus,m_relativeForwardForce), HK_NULL }
};
const hkClass hkpVehicleFrictionStatusAxisStatusClass(
	"hkpVehicleFrictionStatusAxisStatus",
	HK_NULL, // parent
	sizeof(hkpVehicleFrictionStatus::AxisStatus),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionStatus_AxisStatusClass_Members),
	HK_COUNT_OF(hkpVehicleFrictionStatus_AxisStatusClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleFrictionStatus
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpVehicleFrictionStatus);
static const hkInternalClassMember hkpVehicleFrictionStatusClass_Members[] =
{
	{ "axis", &hkpVehicleFrictionStatusAxisStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpVehicleFrictionStatus,m_axis), HK_NULL }
};
extern const hkClass hkpVehicleFrictionStatusClass;
const hkClass hkpVehicleFrictionStatusClass(
	"hkpVehicleFrictionStatus",
	HK_NULL, // parent
	sizeof(hkpVehicleFrictionStatus),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionStatusClass_Members),
	HK_COUNT_OF(hkpVehicleFrictionStatusClass_Members),
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
