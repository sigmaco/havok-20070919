/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Entity/hkpEntity.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>



// External pointer and enum types
extern const hkClass hkSpuCollisionCallbackUtilClass;
extern const hkClass hkpConstraintInstanceClass;
extern const hkClass hkpEntityExtendedListenersClass;
extern const hkClass hkpEntitySpuCollisionCallbackClass;
extern const hkClass hkpMaterialClass;
extern const hkClass hkpMaxSizeMotionClass;
extern const hkClass hkpSimulationIslandClass;

//
// Enum hkpEntity::SpuCollisionCallbackEventFilter
//
static const hkInternalClassEnumItem hkpEntitySpuCollisionCallbackEventFilterEnumItems[] =
{
	{0/*0x00*/, "SPU_SEND_NONE"},
	{1/*0x01*/, "SPU_SEND_CONTACT_POINT_ADDED"},
	{2/*0x02*/, "SPU_SEND_CONTACT_POINT_PROCESS"},
	{4/*0x04*/, "SPU_SEND_CONTACT_POINT_REMOVED"},
	{3/*SPU_SEND_CONTACT_POINT_ADDED|SPU_SEND_CONTACT_POINT_PROCESS*/, "SPU_SEND_CONTACT_POINT_ADDED_OR_PROCESS"},
};
static const hkInternalClassEnum hkpEntityEnums[] = {
	{"SpuCollisionCallbackEventFilter", hkpEntitySpuCollisionCallbackEventFilterEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpEntitySpuCollisionCallbackEventFilterEnum = reinterpret_cast<const hkClassEnum*>(&hkpEntityEnums[0]);

//
// Class hkpEntity::SmallArraySerializeOverrideType
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpEntity,SmallArraySerializeOverrideType);
static const hkInternalClassMember hkpEntity_SmallArraySerializeOverrideTypeClass_Members[] =
{
	{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity::SmallArraySerializeOverrideType,m_data), HK_NULL },
	{ "size", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity::SmallArraySerializeOverrideType,m_size), HK_NULL },
	{ "capacityAndFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity::SmallArraySerializeOverrideType,m_capacityAndFlags), HK_NULL }
};
extern const hkClass hkpEntitySmallArraySerializeOverrideTypeClass;
const hkClass hkpEntitySmallArraySerializeOverrideTypeClass(
	"hkpEntitySmallArraySerializeOverrideType",
	HK_NULL, // parent
	sizeof(hkpEntity::SmallArraySerializeOverrideType),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpEntity_SmallArraySerializeOverrideTypeClass_Members),
	HK_COUNT_OF(hkpEntity_SmallArraySerializeOverrideTypeClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpEntity::SpuCollisionCallback
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpEntity,SpuCollisionCallback);
static const hkInternalClassMember hkpEntity_SpuCollisionCallbackClass_Members[] =
{
	{ "util", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity::SpuCollisionCallback,m_util), HK_NULL },
	{ "capacity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity::SpuCollisionCallback,m_capacity), HK_NULL },
	{ "eventFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity::SpuCollisionCallback,m_eventFilter), HK_NULL },
	{ "userFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity::SpuCollisionCallback,m_userFilter), HK_NULL }
};
const hkClass hkpEntitySpuCollisionCallbackClass(
	"hkpEntitySpuCollisionCallback",
	HK_NULL, // parent
	sizeof(hkpEntity::SpuCollisionCallback),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpEntity_SpuCollisionCallbackClass_Members),
	HK_COUNT_OF(hkpEntity_SpuCollisionCallbackClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpEntity::ExtendedListeners
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpEntity,ExtendedListeners);
static const hkInternalClassMember hkpEntity_ExtendedListenersClass_Members[] =
{
	{ "activationListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity::ExtendedListeners,m_activationListeners), HK_NULL },
	{ "entityListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity::ExtendedListeners,m_entityListeners), HK_NULL }
};
const hkClass hkpEntityExtendedListenersClass(
	"hkpEntityExtendedListeners",
	HK_NULL, // parent
	sizeof(hkpEntity::ExtendedListeners),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpEntity_ExtendedListenersClass_Members),
	HK_COUNT_OF(hkpEntity_ExtendedListenersClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpEntity
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpEntity);
const hkInternalClassMember hkpEntity::Members[] =
{
	{ "material", &hkpMaterialClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_material), HK_NULL },
	{ "breakOffPartsUtil", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_breakOffPartsUtil), HK_NULL },
	{ "solverData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_solverData), HK_NULL },
	{ "storageIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_storageIndex), HK_NULL },
	{ "processContactCallbackDelay", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_processContactCallbackDelay), HK_NULL },
	{ "constraintsMaster", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_constraintsMaster), HK_NULL },
	{ "constraintsSlave", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_constraintsSlave), HK_NULL },
	{ "constraintRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_constraintRuntime), HK_NULL },
	{ "simulationIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_simulationIsland), HK_NULL },
	{ "autoRemoveLevel", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_autoRemoveLevel), HK_NULL },
	{ "numUserDatasInContactPointProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_numUserDatasInContactPointProperties), HK_NULL },
	{ "uid", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_uid), HK_NULL },
	{ "spuCollisionCallback", &hkpEntitySpuCollisionCallbackClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_spuCollisionCallback), HK_NULL },
	{ "extendedListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_extendedListeners), HK_NULL },
	{ "motion", &hkpMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpEntity,m_motion), HK_NULL },
	{ "collisionListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_collisionListeners), HK_NULL },
	{ "actions", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpEntity,m_actions), HK_NULL }
};
namespace
{
	struct hkpEntity_DefaultStruct
	{
		int s_defaultOffsets[17];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkUint32 m_uid;
	};
	const hkpEntity_DefaultStruct hkpEntity_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpEntity_DefaultStruct,m_uid),-1,-1,-1,-1,-1},
		0xffffffff
	};
}
extern const hkClass hkpWorldObjectClass;

extern const hkClass hkpEntityClass;
const hkClass hkpEntityClass(
	"hkpEntity",
	&hkpWorldObjectClass, // parent
	sizeof(hkpEntity),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpEntityEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpEntity::Members),
	HK_COUNT_OF(hkpEntity::Members),
	&hkpEntity_Default,
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
