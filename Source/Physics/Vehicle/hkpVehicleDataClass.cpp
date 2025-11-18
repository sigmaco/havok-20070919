/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/hkpVehicleData.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/hkpVehicleData.h>



// External pointer and enum types
extern const hkClass hkpVehicleDataWheelComponentParamsClass;
extern const hkClass hkpVehicleFrictionDescriptionClass;

//
// Class hkpVehicleData::WheelComponentParams
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleData,WheelComponentParams);
static const hkInternalClassMember hkpVehicleData_WheelComponentParamsClass_Members[] =
{
	{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_radius), HK_NULL },
	{ "mass", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_mass), HK_NULL },
	{ "width", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_width), HK_NULL },
	{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_friction), HK_NULL },
	{ "viscosityFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_viscosityFriction), HK_NULL },
	{ "maxFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_maxFriction), HK_NULL },
	{ "slipAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_slipAngle), HK_NULL },
	{ "forceFeedbackMultiplier", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_forceFeedbackMultiplier), HK_NULL },
	{ "maxContactBodyAcceleration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_maxContactBodyAcceleration), HK_NULL },
	{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData::WheelComponentParams,m_axle), HK_NULL }
};
const hkClass hkpVehicleDataWheelComponentParamsClass(
	"hkpVehicleDataWheelComponentParams",
	HK_NULL, // parent
	sizeof(hkpVehicleData::WheelComponentParams),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleData_WheelComponentParamsClass_Members),
	HK_COUNT_OF(hkpVehicleData_WheelComponentParamsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpVehicleData);
static const hkInternalClassMember hkpVehicleDataClass_Members[] =
{
	{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_gravity), HK_NULL },
	{ "numWheels", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_numWheels), HK_NULL },
	{ "chassisOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_chassisOrientation), HK_NULL },
	{ "torqueRollFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_torqueRollFactor), HK_NULL },
	{ "torquePitchFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_torquePitchFactor), HK_NULL },
	{ "torqueYawFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_torqueYawFactor), HK_NULL },
	{ "extraTorqueFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_extraTorqueFactor), HK_NULL },
	{ "maxVelocityForPositionalFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_maxVelocityForPositionalFriction), HK_NULL },
	{ "chassisUnitInertiaYaw", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_chassisUnitInertiaYaw), HK_NULL },
	{ "chassisUnitInertiaRoll", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_chassisUnitInertiaRoll), HK_NULL },
	{ "chassisUnitInertiaPitch", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_chassisUnitInertiaPitch), HK_NULL },
	{ "frictionEqualizer", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_frictionEqualizer), HK_NULL },
	{ "normalClippingAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_normalClippingAngle), HK_NULL },
	{ "maxFrictionSolverMassRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_maxFrictionSolverMassRatio), HK_NULL },
	{ "wheelParams", &hkpVehicleDataWheelComponentParamsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_wheelParams), HK_NULL },
	{ "numWheelsPerAxle", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_numWheelsPerAxle), HK_NULL },
	{ "frictionDescription", &hkpVehicleFrictionDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_frictionDescription), HK_NULL },
	{ "chassisFrictionInertiaInvDiag", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_chassisFrictionInertiaInvDiag), HK_NULL },
	{ "alreadyInitialised", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleData,m_alreadyInitialised), HK_NULL }
};
namespace
{
	struct hkpVehicleData_DefaultStruct
	{
		int s_defaultOffsets[19];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_maxFrictionSolverMassRatio;
	};
	const hkpVehicleData_DefaultStruct hkpVehicleData_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpVehicleData_DefaultStruct,m_maxFrictionSolverMassRatio),-1,-1,-1,-1,-1},
		30.0
	};
}
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpVehicleDataClass;
const hkClass hkpVehicleDataClass(
	"hkpVehicleData",
	&hkReferencedObjectClass, // parent
	sizeof(hkpVehicleData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleDataClass_Members),
	HK_COUNT_OF(hkpVehicleDataClass_Members),
	&hkpVehicleData_Default,
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
