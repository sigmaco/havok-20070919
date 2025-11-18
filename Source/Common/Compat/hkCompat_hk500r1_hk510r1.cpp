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

namespace hkCompat_hk500r1_hk510r1
{

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

	// behavior
	{ 0x7361d9bd, 0x68c5f6dd, hkVersionUtil::VERSION_COPY, "hkbClipGenerator", HK_NULL },
	{ 0x7b9951fd, 0x57a677e8, hkVersionUtil::VERSION_COPY, "hkbClipTrigger", HK_NULL },
	{ 0xe27a0994, 0xe25d0a56, hkVersionUtil::VERSION_COPY, "hkbDemoConfig", HK_NULL },
	{ 0xbbd4f75d, 0x95ff3258, hkVersionUtil::VERSION_COPY, "hkbGeneratorTransitionEffect", HK_NULL },
	{ 0xb75c0503, 0x70729011, hkVersionUtil::VERSION_COPY, "hkbLookAtModifier", HK_NULL },
	{ 0xa1476024, 0xf2ee1f3a, hkVersionUtil::VERSION_COPY, "hkbPoseMatchingGenerator", HK_NULL },

	// physics
	{ 0x2838ba79, 0x496cceaa, hkVersionUtil::VERSION_COPY, "hkpSerializedAgentNnEntry", HK_NULL },
	{ 0x371b03fa, 0x679da309, hkVersionUtil::VERSION_COPY, "hkpSimpleContactConstraintAtom", HK_NULL },


	{ 0, 0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	{ HK_NULL, HK_NULL }
};

hkVersionRegistry::ClassList classList =
{
	HAVOK_SDK_VERSION_STRING,
	const_cast<hkClass*const*>(hkBuiltinTypeRegistry::StaticLinkedClasses),
	-1,
	true
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&classList
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
	hkHavok500r1Classes::VersionString,
	HAVOK_SDK_VERSION_STRING,
	update
};

} // namespace hkCompat_hk500r1_hk510r1

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
