/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>
HK_REFLECTION_CLASSFILE_HEADER("Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h");



// External pointer and enum types
extern const hkClass hkpBridgeConstraintAtomClass;
extern const hkClass hkpConstraintAtomClass;
extern const hkClass hkpConstraintDataClass;
extern const hkClass hkpConstraintMotorClass;
extern const hkClass hkpSimpleContactConstraintDataInfoClass;

//
// Enum hkpConstraintAtom::AtomType
//
static const hkInternalClassEnumItem hkpConstraintAtomAtomTypeEnumItems[] =
{
	{0, "TYPE_INVALID"},
	{1, "TYPE_BRIDGE"},
	{2, "TYPE_SET_LOCAL_TRANSFORMS"},
	{3, "TYPE_SET_LOCAL_TRANSLATIONS"},
	{4, "TYPE_SET_LOCAL_ROTATIONS"},
	{5, "TYPE_BALL_SOCKET"},
	{6, "TYPE_STIFF_SPRING"},
	{7, "TYPE_LIN"},
	{8, "TYPE_LIN_SOFT"},
	{9, "TYPE_LIN_LIMIT"},
	{10, "TYPE_LIN_FRICTION"},
	{11, "TYPE_LIN_MOTOR"},
	{12, "TYPE_2D_ANG"},
	{13, "TYPE_ANG"},
	{14, "TYPE_ANG_LIMIT"},
	{15, "TYPE_TWIST_LIMIT"},
	{16, "TYPE_CONE_LIMIT"},
	{17, "TYPE_ANG_FRICTION"},
	{18, "TYPE_ANG_MOTOR"},
	{19, "TYPE_RAGDOLL_MOTOR"},
	{20, "TYPE_PULLEY"},
	{21, "TYPE_OVERWRITE_PIVOT"},
	{22, "TYPE_CONTACT"},
	{23, "TYPE_MODIFIER_SOFT_CONTACT"},
	{24, "TYPE_MODIFIER_MASS_CHANGER"},
	{25, "TYPE_MODIFIER_VISCOUS_SURFACE"},
	{26, "TYPE_MODIFIER_MOVING_SURFACE"},
	{27, "TYPE_MAX"},
};

//
// Enum hkpConstraintAtom::CallbackRequest
//
static const hkInternalClassEnumItem hkpConstraintAtomCallbackRequestEnumItems[] =
{
	{0, "CALLBACK_REQUEST_NONE"},
	{1, "CALLBACK_REQUEST_NEW_CONTACT_POINT"},
	{2, "CALLBACK_REQUEST_SETUP_PPU_ONLY"},
	{4, "CALLBACK_REQUEST_SETUP_CALLBACK"},
};
static const hkInternalClassEnum hkpConstraintAtomEnums[] = {
	{"AtomType", hkpConstraintAtomAtomTypeEnumItems, 28, HK_NULL, 0 },
	{"CallbackRequest", hkpConstraintAtomCallbackRequestEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConstraintAtomAtomTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintAtomEnums[0]);
extern const hkClassEnum* hkpConstraintAtomCallbackRequestEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintAtomEnums[1]);

//
// Class hkpConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpConstraintAtom);
static const hkInternalClassMember hkpConstraintAtomClass_Members[] =
{
	{ "type", HK_NULL, hkpConstraintAtomAtomTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpConstraintAtom,m_type), HK_NULL }
};
const hkClass hkpConstraintAtomClass(
	"hkpConstraintAtom",
	HK_NULL, // parent
	sizeof(hkpConstraintAtom),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConstraintAtomEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkpConstraintAtomClass_Members),
	HK_COUNT_OF(hkpConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpBridgeConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpBridgeConstraintAtom);
static const hkInternalClassMember hkpBridgeConstraintAtomClass_Members[] =
{
	{ "buildJacobianFunc", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpBridgeConstraintAtom,m_buildJacobianFunc), HK_NULL },
	{ "constraintData", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpBridgeConstraintAtom,m_constraintData), HK_NULL }
};

const hkClass hkpBridgeConstraintAtomClass(
	"hkpBridgeConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpBridgeConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpBridgeConstraintAtomClass_Members),
	HK_COUNT_OF(hkpBridgeConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpBridgeAtoms
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpBridgeAtoms);
static const hkInternalClassMember hkpBridgeAtomsClass_Members[] =
{
	{ "bridgeAtom", &hkpBridgeConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBridgeAtoms,m_bridgeAtom), HK_NULL }
};
extern const hkClass hkpBridgeAtomsClass;
const hkClass hkpBridgeAtomsClass(
	"hkpBridgeAtoms",
	HK_NULL, // parent
	sizeof(hkpBridgeAtoms),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpBridgeAtomsClass_Members),
	HK_COUNT_OF(hkpBridgeAtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSimpleContactConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSimpleContactConstraintAtom);
static const hkInternalClassMember hkpSimpleContactConstraintAtomClass_Members[] =
{
	{ "sizeOfAllAtoms", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_sizeOfAllAtoms), HK_NULL },
	{ "numContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_numContactPoints), HK_NULL },
	{ "numReservedContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_numReservedContactPoints), HK_NULL },
	{ "numUserDatasForBodyA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_numUserDatasForBodyA), HK_NULL },
	{ "numUserDatasForBodyB", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_numUserDatasForBodyB), HK_NULL },
	{ "contactPointPropertiesStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_contactPointPropertiesStriding), HK_NULL },
	{ "maxNumContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_maxNumContactPoints), HK_NULL },
	{ "info", &hkpSimpleContactConstraintDataInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpSimpleContactConstraintAtom,m_info), HK_NULL }
};

extern const hkClass hkpSimpleContactConstraintAtomClass;
const hkClass hkpSimpleContactConstraintAtomClass(
	"hkpSimpleContactConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpSimpleContactConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleContactConstraintAtomClass_Members),
	HK_COUNT_OF(hkpSimpleContactConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpBallSocketConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpBallSocketConstraintAtom);

extern const hkClass hkpBallSocketConstraintAtomClass;
const hkClass hkpBallSocketConstraintAtomClass(
	"hkpBallSocketConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpBallSocketConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	HK_NULL,
	0,
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStiffSpringConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpStiffSpringConstraintAtom);
static const hkInternalClassMember hkpStiffSpringConstraintAtomClass_Members[] =
{
	{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringConstraintAtom,m_length), HK_NULL }
};

extern const hkClass hkpStiffSpringConstraintAtomClass;
const hkClass hkpStiffSpringConstraintAtomClass(
	"hkpStiffSpringConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpStiffSpringConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintAtomClass_Members),
	HK_COUNT_OF(hkpStiffSpringConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSetLocalTransformsConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSetLocalTransformsConstraintAtom);
static const hkInternalClassMember hkpSetLocalTransformsConstraintAtomClass_Members[] =
{
	{ "transformA", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalTransformsConstraintAtom,m_transformA), HK_NULL },
	{ "transformB", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalTransformsConstraintAtom,m_transformB), HK_NULL }
};

extern const hkClass hkpSetLocalTransformsConstraintAtomClass;
const hkClass hkpSetLocalTransformsConstraintAtomClass(
	"hkpSetLocalTransformsConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpSetLocalTransformsConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSetLocalTransformsConstraintAtomClass_Members),
	HK_COUNT_OF(hkpSetLocalTransformsConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSetLocalTranslationsConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSetLocalTranslationsConstraintAtom);
static const hkInternalClassMember hkpSetLocalTranslationsConstraintAtomClass_Members[] =
{
	{ "translationA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalTranslationsConstraintAtom,m_translationA), HK_NULL },
	{ "translationB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalTranslationsConstraintAtom,m_translationB), HK_NULL }
};

extern const hkClass hkpSetLocalTranslationsConstraintAtomClass;
const hkClass hkpSetLocalTranslationsConstraintAtomClass(
	"hkpSetLocalTranslationsConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpSetLocalTranslationsConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSetLocalTranslationsConstraintAtomClass_Members),
	HK_COUNT_OF(hkpSetLocalTranslationsConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSetLocalRotationsConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSetLocalRotationsConstraintAtom);
static const hkInternalClassMember hkpSetLocalRotationsConstraintAtomClass_Members[] =
{
	{ "rotationA", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalRotationsConstraintAtom,m_rotationA), HK_NULL },
	{ "rotationB", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSetLocalRotationsConstraintAtom,m_rotationB), HK_NULL }
};

extern const hkClass hkpSetLocalRotationsConstraintAtomClass;
const hkClass hkpSetLocalRotationsConstraintAtomClass(
	"hkpSetLocalRotationsConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpSetLocalRotationsConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSetLocalRotationsConstraintAtomClass_Members),
	HK_COUNT_OF(hkpSetLocalRotationsConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpOverwritePivotConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpOverwritePivotConstraintAtom);
static const hkInternalClassMember hkpOverwritePivotConstraintAtomClass_Members[] =
{
	{ "copyToPivotBFromPivotA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpOverwritePivotConstraintAtom,m_copyToPivotBFromPivotA), HK_NULL }
};

extern const hkClass hkpOverwritePivotConstraintAtomClass;
const hkClass hkpOverwritePivotConstraintAtomClass(
	"hkpOverwritePivotConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpOverwritePivotConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpOverwritePivotConstraintAtomClass_Members),
	HK_COUNT_OF(hkpOverwritePivotConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpLinConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpLinConstraintAtom);
static const hkInternalClassMember hkpLinConstraintAtomClass_Members[] =
{
	{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinConstraintAtom,m_axisIndex), HK_NULL }
};

extern const hkClass hkpLinConstraintAtomClass;
const hkClass hkpLinConstraintAtomClass(
	"hkpLinConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpLinConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpLinConstraintAtomClass_Members),
	HK_COUNT_OF(hkpLinConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpLinSoftConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpLinSoftConstraintAtom);
static const hkInternalClassMember hkpLinSoftConstraintAtomClass_Members[] =
{
	{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinSoftConstraintAtom,m_axisIndex), HK_NULL },
	{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinSoftConstraintAtom,m_tau), HK_NULL },
	{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinSoftConstraintAtom,m_damping), HK_NULL }
};

extern const hkClass hkpLinSoftConstraintAtomClass;
const hkClass hkpLinSoftConstraintAtomClass(
	"hkpLinSoftConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpLinSoftConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpLinSoftConstraintAtomClass_Members),
	HK_COUNT_OF(hkpLinSoftConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpLinLimitConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpLinLimitConstraintAtom);
static const hkInternalClassMember hkpLinLimitConstraintAtomClass_Members[] =
{
	{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinLimitConstraintAtom,m_axisIndex), HK_NULL },
	{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinLimitConstraintAtom,m_min), HK_NULL },
	{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinLimitConstraintAtom,m_max), HK_NULL }
};

extern const hkClass hkpLinLimitConstraintAtomClass;
const hkClass hkpLinLimitConstraintAtomClass(
	"hkpLinLimitConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpLinLimitConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpLinLimitConstraintAtomClass_Members),
	HK_COUNT_OF(hkpLinLimitConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkp2dAngConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkp2dAngConstraintAtom);
static const hkInternalClassMember hkp2dAngConstraintAtomClass_Members[] =
{
	{ "freeRotationAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkp2dAngConstraintAtom,m_freeRotationAxis), HK_NULL }
};

extern const hkClass hkp2dAngConstraintAtomClass;
const hkClass hkp2dAngConstraintAtomClass(
	"hkp2dAngConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkp2dAngConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkp2dAngConstraintAtomClass_Members),
	HK_COUNT_OF(hkp2dAngConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpAngConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpAngConstraintAtom);
static const hkInternalClassMember hkpAngConstraintAtomClass_Members[] =
{
	{ "firstConstrainedAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngConstraintAtom,m_firstConstrainedAxis), HK_NULL },
	{ "numConstrainedAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngConstraintAtom,m_numConstrainedAxes), HK_NULL }
};

extern const hkClass hkpAngConstraintAtomClass;
const hkClass hkpAngConstraintAtomClass(
	"hkpAngConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpAngConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpAngConstraintAtomClass_Members),
	HK_COUNT_OF(hkpAngConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpAngLimitConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpAngLimitConstraintAtom);
static const hkInternalClassMember hkpAngLimitConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngLimitConstraintAtom,m_isEnabled), HK_NULL },
	{ "limitAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngLimitConstraintAtom,m_limitAxis), HK_NULL },
	{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngLimitConstraintAtom,m_minAngle), HK_NULL },
	{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngLimitConstraintAtom,m_maxAngle), HK_NULL },
	{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngLimitConstraintAtom,m_angularLimitsTauFactor), HK_NULL }
};
namespace
{
	struct hkpAngLimitConstraintAtom_DefaultStruct
	{
		int s_defaultOffsets[5];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_angularLimitsTauFactor;
	};
	const hkpAngLimitConstraintAtom_DefaultStruct hkpAngLimitConstraintAtom_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpAngLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
		1.0
	};
}

extern const hkClass hkpAngLimitConstraintAtomClass;
const hkClass hkpAngLimitConstraintAtomClass(
	"hkpAngLimitConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpAngLimitConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpAngLimitConstraintAtomClass_Members),
	HK_COUNT_OF(hkpAngLimitConstraintAtomClass_Members),
	&hkpAngLimitConstraintAtom_Default,
	HK_NULL, // attributes
	0
	);

//
// Class hkpTwistLimitConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpTwistLimitConstraintAtom);
static const hkInternalClassMember hkpTwistLimitConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_isEnabled), HK_NULL },
	{ "twistAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_twistAxis), HK_NULL },
	{ "refAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_refAxis), HK_NULL },
	{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_minAngle), HK_NULL },
	{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_maxAngle), HK_NULL },
	{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTwistLimitConstraintAtom,m_angularLimitsTauFactor), HK_NULL }
};
namespace
{
	struct hkpTwistLimitConstraintAtom_DefaultStruct
	{
		int s_defaultOffsets[6];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_angularLimitsTauFactor;
	};
	const hkpTwistLimitConstraintAtom_DefaultStruct hkpTwistLimitConstraintAtom_Default =
	{
		{-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpTwistLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
		1.0
	};
}

extern const hkClass hkpTwistLimitConstraintAtomClass;
const hkClass hkpTwistLimitConstraintAtomClass(
	"hkpTwistLimitConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpTwistLimitConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTwistLimitConstraintAtomClass_Members),
	HK_COUNT_OF(hkpTwistLimitConstraintAtomClass_Members),
	&hkpTwistLimitConstraintAtom_Default,
	HK_NULL, // attributes
	0
	);

//
// Enum hkpConeLimitConstraintAtom::MeasurementMode
//
static const hkInternalClassEnumItem hkpConeLimitConstraintAtomMeasurementModeEnumItems[] =
{
	{0, "ZERO_WHEN_VECTORS_ALIGNED"},
	{1, "ZERO_WHEN_VECTORS_PERPENDICULAR"},
};
static const hkInternalClassEnum hkpConeLimitConstraintAtomEnums[] = {
	{"MeasurementMode", hkpConeLimitConstraintAtomMeasurementModeEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConeLimitConstraintAtomMeasurementModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConeLimitConstraintAtomEnums[0]);

//
// Class hkpConeLimitConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpConeLimitConstraintAtom);
static const hkInternalClassMember hkpConeLimitConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_isEnabled), HK_NULL },
	{ "twistAxisInA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_twistAxisInA), HK_NULL },
	{ "refAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_refAxisInB), HK_NULL },
	{ "angleMeasurementMode", HK_NULL, hkpConeLimitConstraintAtomMeasurementModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_angleMeasurementMode), HK_NULL },
	{ "memOffsetToAngleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_memOffsetToAngleOffset), HK_NULL },
	{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_minAngle), HK_NULL },
	{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_maxAngle), HK_NULL },
	{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConeLimitConstraintAtom,m_angularLimitsTauFactor), HK_NULL }
};
namespace
{
	struct hkpConeLimitConstraintAtom_DefaultStruct
	{
		int s_defaultOffsets[8];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkUint8 m_memOffsetToAngleOffset;
		hkReal m_angularLimitsTauFactor;
	};
	const hkpConeLimitConstraintAtom_DefaultStruct hkpConeLimitConstraintAtom_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpConeLimitConstraintAtom_DefaultStruct,m_memOffsetToAngleOffset),-1,-1,HK_OFFSET_OF(hkpConeLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
		1,1.0
	};
}

extern const hkClass hkpConeLimitConstraintAtomClass;
const hkClass hkpConeLimitConstraintAtomClass(
	"hkpConeLimitConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpConeLimitConstraintAtom),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConeLimitConstraintAtomEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpConeLimitConstraintAtomClass_Members),
	HK_COUNT_OF(hkpConeLimitConstraintAtomClass_Members),
	&hkpConeLimitConstraintAtom_Default,
	HK_NULL, // attributes
	0
	);

//
// Class hkpAngFrictionConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpAngFrictionConstraintAtom);
static const hkInternalClassMember hkpAngFrictionConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngFrictionConstraintAtom,m_isEnabled), HK_NULL },
	{ "firstFrictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngFrictionConstraintAtom,m_firstFrictionAxis), HK_NULL },
	{ "numFrictionAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngFrictionConstraintAtom,m_numFrictionAxes), HK_NULL },
	{ "maxFrictionTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngFrictionConstraintAtom,m_maxFrictionTorque), HK_NULL }
};

extern const hkClass hkpAngFrictionConstraintAtomClass;
const hkClass hkpAngFrictionConstraintAtomClass(
	"hkpAngFrictionConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpAngFrictionConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpAngFrictionConstraintAtomClass_Members),
	HK_COUNT_OF(hkpAngFrictionConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpAngMotorConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpAngMotorConstraintAtom);
static const hkInternalClassMember hkpAngMotorConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_isEnabled), HK_NULL },
	{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_motorAxis), HK_NULL },
	{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_initializedOffset), HK_NULL },
	{ "previousTargetAngleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_previousTargetAngleOffset), HK_NULL },
	{ "correspondingAngLimitSolverResultOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_correspondingAngLimitSolverResultOffset), HK_NULL },
	{ "targetAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_targetAngle), HK_NULL },
	{ "motor", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpAngMotorConstraintAtom,m_motor), HK_NULL }
};

extern const hkClass hkpAngMotorConstraintAtomClass;
const hkClass hkpAngMotorConstraintAtomClass(
	"hkpAngMotorConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpAngMotorConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpAngMotorConstraintAtomClass_Members),
	HK_COUNT_OF(hkpAngMotorConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpRagdollMotorConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpRagdollMotorConstraintAtom);
static const hkInternalClassMember hkpRagdollMotorConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollMotorConstraintAtom,m_isEnabled), HK_NULL },
	{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollMotorConstraintAtom,m_initializedOffset), HK_NULL },
	{ "previousTargetAnglesOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollMotorConstraintAtom,m_previousTargetAnglesOffset), HK_NULL },
	{ "targetFrameAinB", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollMotorConstraintAtom,m_targetFrameAinB), HK_NULL },
	{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, HK_OFFSET_OF(hkpRagdollMotorConstraintAtom,m_motors), HK_NULL }
};

extern const hkClass hkpRagdollMotorConstraintAtomClass;
const hkClass hkpRagdollMotorConstraintAtomClass(
	"hkpRagdollMotorConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpRagdollMotorConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpRagdollMotorConstraintAtomClass_Members),
	HK_COUNT_OF(hkpRagdollMotorConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpLinFrictionConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpLinFrictionConstraintAtom);
static const hkInternalClassMember hkpLinFrictionConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinFrictionConstraintAtom,m_isEnabled), HK_NULL },
	{ "frictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinFrictionConstraintAtom,m_frictionAxis), HK_NULL },
	{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinFrictionConstraintAtom,m_maxFrictionForce), HK_NULL }
};

extern const hkClass hkpLinFrictionConstraintAtomClass;
const hkClass hkpLinFrictionConstraintAtomClass(
	"hkpLinFrictionConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpLinFrictionConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpLinFrictionConstraintAtomClass_Members),
	HK_COUNT_OF(hkpLinFrictionConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpLinMotorConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpLinMotorConstraintAtom);
static const hkInternalClassMember hkpLinMotorConstraintAtomClass_Members[] =
{
	{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_isEnabled), HK_NULL },
	{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_motorAxis), HK_NULL },
	{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_initializedOffset), HK_NULL },
	{ "previousTargetPositionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_previousTargetPositionOffset), HK_NULL },
	{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_targetPosition), HK_NULL },
	{ "motor", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpLinMotorConstraintAtom,m_motor), HK_NULL }
};

extern const hkClass hkpLinMotorConstraintAtomClass;
const hkClass hkpLinMotorConstraintAtomClass(
	"hkpLinMotorConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpLinMotorConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpLinMotorConstraintAtomClass_Members),
	HK_COUNT_OF(hkpLinMotorConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPulleyConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpPulleyConstraintAtom);
static const hkInternalClassMember hkpPulleyConstraintAtomClass_Members[] =
{
	{ "fixedPivotAinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintAtom,m_fixedPivotAinWorld), HK_NULL },
	{ "fixedPivotBinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintAtom,m_fixedPivotBinWorld), HK_NULL },
	{ "ropeLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintAtom,m_ropeLength), HK_NULL },
	{ "leverageOnBodyB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintAtom,m_leverageOnBodyB), HK_NULL }
};

extern const hkClass hkpPulleyConstraintAtomClass;
const hkClass hkpPulleyConstraintAtomClass(
	"hkpPulleyConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpPulleyConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintAtomClass_Members),
	HK_COUNT_OF(hkpPulleyConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpModifierConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpModifierConstraintAtom);
static const hkInternalClassMember hkpModifierConstraintAtomClass_Members[] =
{
	{ "modifierAtomSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpModifierConstraintAtom,m_modifierAtomSize), HK_NULL },
	{ "childSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpModifierConstraintAtom,m_childSize), HK_NULL },
	{ "child", &hkpConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpModifierConstraintAtom,m_child), HK_NULL },
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpModifierConstraintAtom,m_pad), HK_NULL }
};

extern const hkClass hkpModifierConstraintAtomClass;
const hkClass hkpModifierConstraintAtomClass(
	"hkpModifierConstraintAtom",
	&hkpConstraintAtomClass, // parent
	sizeof(hkpModifierConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpModifierConstraintAtomClass_Members),
	HK_COUNT_OF(hkpModifierConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSoftContactModifierConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSoftContactModifierConstraintAtom);
static const hkInternalClassMember hkpSoftContactModifierConstraintAtomClass_Members[] =
{
	{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSoftContactModifierConstraintAtom,m_tau), HK_NULL },
	{ "maxAcceleration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSoftContactModifierConstraintAtom,m_maxAcceleration), HK_NULL }
};

extern const hkClass hkpSoftContactModifierConstraintAtomClass;
const hkClass hkpSoftContactModifierConstraintAtomClass(
	"hkpSoftContactModifierConstraintAtom",
	&hkpModifierConstraintAtomClass, // parent
	sizeof(hkpSoftContactModifierConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSoftContactModifierConstraintAtomClass_Members),
	HK_COUNT_OF(hkpSoftContactModifierConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpMassChangerModifierConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpMassChangerModifierConstraintAtom);
static const hkInternalClassMember hkpMassChangerModifierConstraintAtomClass_Members[] =
{
	{ "factorA", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMassChangerModifierConstraintAtom,m_factorA), HK_NULL },
	{ "factorB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMassChangerModifierConstraintAtom,m_factorB), HK_NULL },
	{ "pad16", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMassChangerModifierConstraintAtom,m_pad16), HK_NULL }
};

extern const hkClass hkpMassChangerModifierConstraintAtomClass;
const hkClass hkpMassChangerModifierConstraintAtomClass(
	"hkpMassChangerModifierConstraintAtom",
	&hkpModifierConstraintAtomClass, // parent
	sizeof(hkpMassChangerModifierConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpMassChangerModifierConstraintAtomClass_Members),
	HK_COUNT_OF(hkpMassChangerModifierConstraintAtomClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpViscousSurfaceModifierConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpViscousSurfaceModifierConstraintAtom);

extern const hkClass hkpViscousSurfaceModifierConstraintAtomClass;
const hkClass hkpViscousSurfaceModifierConstraintAtomClass(
	"hkpViscousSurfaceModifierConstraintAtom",
	&hkpModifierConstraintAtomClass, // parent
	sizeof(hkpViscousSurfaceModifierConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	HK_NULL,
	0,
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpMovingSurfaceModifierConstraintAtom
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpMovingSurfaceModifierConstraintAtom);
static const hkInternalClassMember hkpMovingSurfaceModifierConstraintAtomClass_Members[] =
{
	{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMovingSurfaceModifierConstraintAtom,m_velocity), HK_NULL }
};

extern const hkClass hkpMovingSurfaceModifierConstraintAtomClass;
const hkClass hkpMovingSurfaceModifierConstraintAtomClass(
	"hkpMovingSurfaceModifierConstraintAtom",
	&hkpModifierConstraintAtomClass, // parent
	sizeof(hkpMovingSurfaceModifierConstraintAtom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpMovingSurfaceModifierConstraintAtomClass_Members),
	HK_COUNT_OF(hkpMovingSurfaceModifierConstraintAtomClass_Members),
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
