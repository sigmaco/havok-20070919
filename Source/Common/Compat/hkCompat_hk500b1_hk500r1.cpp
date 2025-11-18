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
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/BitField/hkBitField.h>

#include <Common/Compat/hkHavokAllClasses.h>

namespace hkCompat_hk500b1_hk500r1
{

	static void Update_hkbPoseMatchingGenerator( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		// the type on m_mode changed so I need to manually copy it
		hkClassMemberAccessor oldMember( oldObj, "mode" );
		hkClassMemberAccessor newMember( newObj, "mode" );

		newMember.asInt8() = oldMember.asInt8();
	}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	// common
	{ 0x8bdd3e9a, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT, "hkaBoneAttachment", HK_NULL },
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
	{ 0x1388d601, 0x1388d601, hkVersionUtil::VERSION_VARIANT, "hkCustomAttributesAttribute", HK_NULL },
	{ 0xbff19005, 0xbff19005, hkVersionUtil::VERSION_VARIANT, "hkCustomAttributes", HK_NULL },
	{ 0x131a9935, 0x802f9dfd, hkVersionUtil::VERSION_COPY, "hkpRagdollConstraintData", HK_NULL},
	{ 0x9886816b, 0x50801cf8, hkVersionUtil::VERSION_COPY, "hkpRagdollLimitsData", HK_NULL},
	{ 0x90870729, 0x054c1db0, hkVersionUtil::VERSION_COPY, "hkpRagdollConstraintDataAtoms", HK_NULL},
	{ 0x83026d13, 0x92e9ef7c, hkVersionUtil::VERSION_COPY, "hkpRagdollLimitsDataAtoms", HK_NULL},
	{ 0xfc507545, 0x2b21d9bc, hkVersionUtil::VERSION_COPY, "hkpConeLimitConstraintAtom", HK_NULL},
	{ 0x97aa3ab6, 0x3f87178f, hkVersionUtil::VERSION_COPY, "hkpExtendedMeshShape", HK_NULL}, // padding for 4xxx
	{ 0x86b4c959, 0xad62b3cc, hkVersionUtil::VERSION_COPY, "hkpSampledHeightFieldShape", HK_NULL}, // projection type added
	{ 0x79de6a0b, 0x2838ba79, hkVersionUtil::VERSION_COPY, "hkpSerializedAgentNnEntry", HK_NULL}, // added version number for the serialized data streams
	BINARY_IDENTICAL( 0x0b11a993, 0xfc41dc67, "hkClass"), // classmember changes, flags changed
	BINARY_IDENTICAL( 0xe96acec5, 0x258a78ee, "hkClassMember"), // enum Range removed

	// behavior
	{ 0x7d0e0bec, 0x96e3a767, hkVersionUtil::VERSION_COPY, "hkbBalanceModifier", HK_NULL },
	{ 0xb9c1cfd6, 0x4694cfa5, hkVersionUtil::VERSION_COPY, "hkbBalanceRadialSelectorGenerator", HK_NULL },
	{ 0x294881d1, 0xa4253200, hkVersionUtil::VERSION_COPY, "hkbBehavior", HK_NULL },
	{ 0x8b4fc105, 0xa33104be, hkVersionUtil::VERSION_COPY, "hkbCharacterData", HK_NULL },
	{ 0xa4d94a55, 0x25e7e488, hkVersionUtil::VERSION_COPY, "hkbCharacterSetup", HK_NULL },
	{ 0x24816b59, 0x7361d9bd, hkVersionUtil::VERSION_COPY, "hkbClipGenerator", HK_NULL },
	{ 0x0c7cbf64, 0x87967f10, hkVersionUtil::VERSION_COPY, "hkbCustomTestGenerator" },
	{ 0xe7f21435, 0x55261c70, hkVersionUtil::VERSION_COPY, "hkbCustomTestGeneratorStruck" },
	REMOVED("hkbDrawPoseModifier"),
	{ 0xac0f445b, 0x0ea734e9, hkVersionUtil::VERSION_COPY, "hkbFootIkModifier", HK_NULL },
	{ 0x3e142425, 0x93aa61e2, hkVersionUtil::VERSION_COPY, "hkbFootIkModifierLeg", HK_NULL },
	{ 0x58683835, 0xefef656e, hkVersionUtil::VERSION_COPY, "hkbMirrorModifier", HK_NULL },
	{ 0x3ac3f80c, 0xa1476024, hkVersionUtil::VERSION_COPY, "hkbPoseMatchingGenerator", Update_hkbPoseMatchingGenerator },

	{ 0, 0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	{ "hkbBehavior", "hkbBehaviorGraph" },
	{ "hkbBehaviorData", "hkbBehaviorGraphData" },
	{ "hkbBehaviorStringData", "hkbBehaviorGraphStringData" },
	{ HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&hkHavok500r1ClassList
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
	hkHavok500b1Classes::VersionString,
	hkHavok500r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk500b1_hk500r1

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
