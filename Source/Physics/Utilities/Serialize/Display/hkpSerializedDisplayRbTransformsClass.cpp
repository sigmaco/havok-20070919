/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/Serialize/Display/hkpSerializedDisplayRbTransforms.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/Serialize/Display/hkpSerializedDisplayRbTransforms.h>



// External pointer and enum types
extern const hkClass hkpRigidBodyClass;
extern const hkClass hkpSerializedDisplayRbTransformsDisplayTransformPairClass;

//
// Class hkpSerializedDisplayRbTransforms::DisplayTransformPair
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpSerializedDisplayRbTransforms,DisplayTransformPair);
static const hkInternalClassMember hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members[] =
{
	{ "rb", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSerializedDisplayRbTransforms::DisplayTransformPair,m_rb), HK_NULL },
	{ "localToDisplay", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedDisplayRbTransforms::DisplayTransformPair,m_localToDisplay), HK_NULL }
};
const hkClass hkpSerializedDisplayRbTransformsDisplayTransformPairClass(
	"hkpSerializedDisplayRbTransformsDisplayTransformPair",
	HK_NULL, // parent
	sizeof(hkpSerializedDisplayRbTransforms::DisplayTransformPair),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members),
	HK_COUNT_OF(hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSerializedDisplayRbTransforms
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSerializedDisplayRbTransforms);
static const hkInternalClassMember hkpSerializedDisplayRbTransformsClass_Members[] =
{
	{ "transforms", &hkpSerializedDisplayRbTransformsDisplayTransformPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSerializedDisplayRbTransforms,m_transforms), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpSerializedDisplayRbTransformsClass;
const hkClass hkpSerializedDisplayRbTransformsClass(
	"hkpSerializedDisplayRbTransforms",
	&hkReferencedObjectClass, // parent
	sizeof(hkpSerializedDisplayRbTransforms),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayRbTransformsClass_Members),
	HK_COUNT_OF(hkpSerializedDisplayRbTransformsClass_Members),
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
