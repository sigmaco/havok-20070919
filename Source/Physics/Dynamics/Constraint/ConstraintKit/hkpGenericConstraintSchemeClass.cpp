/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/ConstraintKit/hkpGenericConstraintScheme.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/ConstraintKit/hkpGenericConstraintScheme.h>



// External pointer and enum types
extern const hkClass hkpConstraintInfoClass;
extern const hkClass hkpConstraintModifierClass;
extern const hkClass hkpConstraintMotorClass;
extern const hkClass hkpGenericConstraintDataSchemeintClass;

//
// Class hkpGenericConstraintDataScheme::ConstraintInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpGenericConstraintDataScheme,ConstraintInfo);
static const hkInternalClassMember hkpGenericConstraintDataScheme_ConstraintInfoClass_Members[] =
{
	{ "maxSizeOfSchema", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme::ConstraintInfo,m_maxSizeOfSchema), HK_NULL },
	{ "sizeOfSchemas", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme::ConstraintInfo,m_sizeOfSchemas), HK_NULL },
	{ "numSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme::ConstraintInfo,m_numSolverResults), HK_NULL },
	{ "numSolverElemTemps", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme::ConstraintInfo,m_numSolverElemTemps), HK_NULL }
};
extern const hkClass hkpGenericConstraintDataSchemeConstraintInfoClass;
const hkClass hkpGenericConstraintDataSchemeConstraintInfoClass(
	"hkpGenericConstraintDataSchemeConstraintInfo",
	HK_NULL, // parent
	sizeof(hkpGenericConstraintDataScheme::ConstraintInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpGenericConstraintDataScheme_ConstraintInfoClass_Members),
	HK_COUNT_OF(hkpGenericConstraintDataScheme_ConstraintInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpGenericConstraintDataScheme
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpGenericConstraintDataScheme);
static const hkInternalClassMember hkpGenericConstraintDataSchemeClass_Members[] =
{
	{ "info", &hkpGenericConstraintDataSchemeConstraintInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpGenericConstraintDataScheme,m_info), HK_NULL },
	{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme,m_data), HK_NULL },
	{ "commands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme,m_commands), HK_NULL },
	{ "modifiers", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpGenericConstraintDataScheme,m_modifiers), HK_NULL },
	{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpGenericConstraintDataScheme,m_motors), HK_NULL }
};
extern const hkClass hkpGenericConstraintDataSchemeClass;
const hkClass hkpGenericConstraintDataSchemeClass(
	"hkpGenericConstraintDataScheme",
	HK_NULL, // parent
	sizeof(hkpGenericConstraintDataScheme),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpGenericConstraintDataSchemeClass_Members),
	HK_COUNT_OF(hkpGenericConstraintDataSchemeClass_Members),
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
