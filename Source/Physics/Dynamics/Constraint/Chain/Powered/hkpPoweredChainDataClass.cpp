/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Chain/Powered/hkpPoweredChainData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Chain/Powered/hkpPoweredChainData.h>



// External pointer and enum types
extern const hkClass hkpBridgeAtomsClass;
extern const hkClass hkpConstraintMotorClass;
extern const hkClass hkpPoweredChainDataConstraintInfoClass;

//
// Class hkpPoweredChainData::ConstraintInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpPoweredChainData,ConstraintInfo);
static const hkInternalClassMember hkpPoweredChainData_ConstraintInfoClass_Members[] =
{
	{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_pivotInA), HK_NULL },
	{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_pivotInB), HK_NULL },
	{ "aTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_aTc), HK_NULL },
	{ "bTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_bTc), HK_NULL },
	{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_motors), HK_NULL },
	{ "switchBodies", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData::ConstraintInfo,m_switchBodies), HK_NULL }
};
const hkClass hkpPoweredChainDataConstraintInfoClass(
	"hkpPoweredChainDataConstraintInfo",
	HK_NULL, // parent
	sizeof(hkpPoweredChainData::ConstraintInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPoweredChainData_ConstraintInfoClass_Members),
	HK_COUNT_OF(hkpPoweredChainData_ConstraintInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPoweredChainData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPoweredChainData);
static const hkInternalClassMember hkpPoweredChainDataClass_Members[] =
{
	{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_atoms), HK_NULL },
	{ "infos", &hkpPoweredChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_infos), HK_NULL },
	{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_tau), HK_NULL },
	{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_damping), HK_NULL },
	{ "cfmLinAdd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_cfmLinAdd), HK_NULL },
	{ "cfmLinMul", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_cfmLinMul), HK_NULL },
	{ "cfmAngAdd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_cfmAngAdd), HK_NULL },
	{ "cfmAngMul", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_cfmAngMul), HK_NULL },
	{ "maxErrorDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainData,m_maxErrorDistance), HK_NULL }
};
namespace
{
	struct hkpPoweredChainData_DefaultStruct
	{
		int s_defaultOffsets[9];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_cfmLinAdd;
		hkReal m_cfmLinMul;
		hkReal m_cfmAngAdd;
		hkReal m_cfmAngMul;
	};
	const hkpPoweredChainData_DefaultStruct hkpPoweredChainData_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmLinAdd),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmLinMul),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmAngAdd),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmAngMul),-1},
		0.1f*1.19209290e-07f,1.0f,0.1f*1.19209290e-07F,1.0f
	};
}
extern const hkClass hkpConstraintChainDataClass;

extern const hkClass hkpPoweredChainDataClass;
const hkClass hkpPoweredChainDataClass(
	"hkpPoweredChainData",
	&hkpConstraintChainDataClass, // parent
	sizeof(hkpPoweredChainData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPoweredChainDataClass_Members),
	HK_COUNT_OF(hkpPoweredChainDataClass_Members),
	&hkpPoweredChainData_Default,
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
