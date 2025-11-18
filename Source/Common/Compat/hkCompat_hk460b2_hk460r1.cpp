/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Compat/hkCompat.h>
#include <Common/Compat/hkCompatUtil.h>
#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Serialize/Version/hkVersionRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/Version/hkObjectUpdateTracker.h>
#include <Common/Base/Math/hkMath.h>
#include <Common/Base/Container/BitField/hkBitField.h>

#include <Common/Compat/hkHavokAllClasses.h>

namespace hkCompat_hk460b2_hk460r1
{
	static void hkSerializedAgentNnEntry_hk460b2_hk460r1( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		HK_ASSERT2(0x54e32127, false, "Versioning is not implemented yet.");
	}

	static void hkSerializedContactPointPropertiesBlock_hk460b2_hk460r1( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		HK_ASSERT2(0x54e32128, false, "Versioning is not implemented yet.");
	}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	// common
	{ 0x8bdd3e9a, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0xf598a34e, 0xf598a34e, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainer", HK_NULL },
	{ 0x853a899c, 0x853a899c, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainerNamedVariant", HK_NULL }, 
	{ 0xf2ec0c9c, 0xf2ec0c9c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x1667c01c, 0x1667c01c, hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL }, 
	{ 0x06af1b5a, 0x06af1b5a, hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL },
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },
	{ 0x72e8e849, 0x72e8e849, hkVersionUtil::VERSION_VARIANT, "hkxMesh", HK_NULL },
	{ 0x912c8863, 0x912c8863, hkVersionUtil::VERSION_VARIANT, "hkxMeshSection", HK_NULL },
	{ 0x64e9a03c, 0x64e9a03c, hkVersionUtil::VERSION_VARIANT, "hkxMeshUserChannelInfo", HK_NULL },
	{ 0x445a443a, 0x445a443a, hkVersionUtil::VERSION_VARIANT, "hkxAttributeHolder", HK_NULL },

	// hkbehavior

	{ 0xb36b9af6, 0x563dba83, hkVersionUtil::VERSION_COPY, "hkbBehavior", HK_NULL },
	{ 0x4d94add9, 0x20cc25f6, hkVersionUtil::VERSION_COPY, "hkbStateMachineActiveTransitionInfo", HK_NULL },
	{ 0xc1f29013, 0xf61504a2, hkVersionUtil::VERSION_COPY, "hkbStateMachine", HK_NULL },

	// hkconstraintsolver

	BINARY_IDENTICAL(0x4e7b027c, 0x86c62c9c, "hkMassChangerModifierConstraintAtom"), // fixed size padding (no save)

	// hkcollide

		// hkExtendedMeshShape: Complete 46r1 has 0x29ebe708 signature
	{ 0x7d392dbc, 0x97aa3ab6, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShape", HK_NULL }, // added m_embeddedTrianglesSubpart
	{ 0x4f54c5ac, 0xeb33369b, hkVersionUtil::VERSION_COPY, "hkMoppBvTreeShape", HK_NULL }, // reorder members
	{ 0x15110a40, 0x5f31ebc7, hkVersionUtil::VERSION_COPY, "hkSphereShape", HK_NULL }, // fixed size padding (no save)

	// hkutilities
	{ 0xbd2ac814, 0xcbeca93e, hkVersionUtil::VERSION_COPY, "hkSerializedAgentNnEntry", hkSerializedAgentNnEntry_hk460b2_hk460r1 },
	{ 0xd699c965, 0xfaa46bcc, hkVersionUtil::VERSION_COPY, "hkSerializedContactPointPropertiesBlock", hkSerializedContactPointPropertiesBlock_hk460b2_hk460r1 },

	{ 0, 0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	{ HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&hkHavok460r1ClassList
};

static hkResult HK_CALL update(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker )
{
	return hkVersionUtil::updateSingleVersion( objectsInOut, tracker, hkVersionUpdateDescription );
}

extern const hkVersionRegistry::Updater hkVersionUpdater;
const hkVersionRegistry::Updater hkVersionUpdater =
{
	hkHavok460b2Classes::VersionString,
	hkHavok460r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk460b2_hk460r1

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
