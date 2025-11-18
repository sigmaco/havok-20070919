/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Vehicle/hkpVehicleInstance.h'
#include <Physics/Vehicle/hkpVehicle.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Vehicle/hkpVehicleInstance.h>



// External pointer and enum types
extern const hkClass hkContactPointClass;
extern const hkClass hkpRigidBodyClass;
extern const hkClass hkpTyremarksInfoClass;
extern const hkClass hkpVehicleAerodynamicsClass;
extern const hkClass hkpVehicleBrakeClass;
extern const hkClass hkpVehicleDataClass;
extern const hkClass hkpVehicleDriverInputClass;
extern const hkClass hkpVehicleDriverInputStatusClass;
extern const hkClass hkpVehicleEngineClass;
extern const hkClass hkpVehicleFrictionStatusClass;
extern const hkClass hkpVehicleInstanceWheelInfoClass;
extern const hkClass hkpVehicleSteeringClass;
extern const hkClass hkpVehicleSuspensionClass;
extern const hkClass hkpVehicleTransmissionClass;
extern const hkClass hkpVehicleVelocityDamperClass;
extern const hkClass hkpVehicleWheelCollideClass;

//
// Class hkpVehicleInstance::WheelInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpVehicleInstance,WheelInfo);
static const hkInternalClassMember hkpVehicleInstance_WheelInfoClass_Members[] =
{
	{ "contactPoint", &hkContactPointClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_contactPoint), HK_NULL },
	{ "contactFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_contactFriction), HK_NULL },
	{ "contactBody", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_contactBody), HK_NULL },
	{ "contactShapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_contactShapeKey), HK_NULL },
	{ "hardPointWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_hardPointWs), HK_NULL },
	{ "rayEndPointWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_rayEndPointWs), HK_NULL },
	{ "currentSuspensionLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_currentSuspensionLength), HK_NULL },
	{ "suspensionDirectionWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_suspensionDirectionWs), HK_NULL },
	{ "spinAxisCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_spinAxisCs), HK_NULL },
	{ "spinAxisWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_spinAxisWs), HK_NULL },
	{ "steeringOrientationCs", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_steeringOrientationCs), HK_NULL },
	{ "spinVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_spinVelocity), HK_NULL },
	{ "spinAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_spinAngle), HK_NULL },
	{ "skidEnergyDensity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_skidEnergyDensity), HK_NULL },
	{ "sideForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_sideForce), HK_NULL },
	{ "forwardSlipVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_forwardSlipVelocity), HK_NULL },
	{ "sideSlipVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance::WheelInfo,m_sideSlipVelocity), HK_NULL }
};
const hkClass hkpVehicleInstanceWheelInfoClass(
	"hkpVehicleInstanceWheelInfo",
	HK_NULL, // parent
	sizeof(hkpVehicleInstance::WheelInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleInstance_WheelInfoClass_Members),
	HK_COUNT_OF(hkpVehicleInstance_WheelInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpVehicleInstance
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpVehicleInstance);
static const hkInternalClassMember hkpVehicleInstanceClass_Members[] =
{
	{ "data", &hkpVehicleDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_data), HK_NULL },
	{ "driverInput", &hkpVehicleDriverInputClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_driverInput), HK_NULL },
	{ "steering", &hkpVehicleSteeringClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_steering), HK_NULL },
	{ "engine", &hkpVehicleEngineClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_engine), HK_NULL },
	{ "transmission", &hkpVehicleTransmissionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_transmission), HK_NULL },
	{ "brake", &hkpVehicleBrakeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_brake), HK_NULL },
	{ "suspension", &hkpVehicleSuspensionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_suspension), HK_NULL },
	{ "aerodynamics", &hkpVehicleAerodynamicsClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_aerodynamics), HK_NULL },
	{ "wheelCollide", &hkpVehicleWheelCollideClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_wheelCollide), HK_NULL },
	{ "tyreMarks", &hkpTyremarksInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_tyreMarks), HK_NULL },
	{ "velocityDamper", &hkpVehicleVelocityDamperClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_velocityDamper), HK_NULL },
	{ "wheelsInfo", &hkpVehicleInstanceWheelInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_wheelsInfo), HK_NULL },
	{ "frictionStatus", &hkpVehicleFrictionStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_frictionStatus), HK_NULL },
	{ "deviceStatus", &hkpVehicleDriverInputStatusClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_deviceStatus), HK_NULL },
	{ "isFixed", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_BOOL, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_isFixed), HK_NULL },
	{ "wheelsTimeSinceMaxPedalInput", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_wheelsTimeSinceMaxPedalInput), HK_NULL },
	{ "tryingToReverse", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_tryingToReverse), HK_NULL },
	{ "torque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_torque), HK_NULL },
	{ "rpm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_rpm), HK_NULL },
	{ "mainSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_mainSteeringAngle), HK_NULL },
	{ "wheelsSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_wheelsSteeringAngle), HK_NULL },
	{ "isReversing", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_isReversing), HK_NULL },
	{ "currentGear", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_currentGear), HK_NULL },
	{ "delayed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_delayed), HK_NULL },
	{ "clutchDelayCountdown", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpVehicleInstance,m_clutchDelayCountdown), HK_NULL }
};
extern const hkClass hkpUnaryActionClass;

extern const hkClass hkpVehicleInstanceClass;
const hkClass hkpVehicleInstanceClass(
	"hkpVehicleInstance",
	&hkpUnaryActionClass, // parent
	sizeof(hkpVehicleInstance),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpVehicleInstanceClass_Members),
	HK_COUNT_OF(hkpVehicleInstanceClass_Members),
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
