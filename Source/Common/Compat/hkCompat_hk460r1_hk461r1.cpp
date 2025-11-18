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

namespace hkHavok460r1Classes
{
	extern hkClass hkExtendedMeshShapeClass;
	extern hkClass hkSphereShapeClass;
	extern hkClass hkMassChangerModifierConstraintAtomClass;
}

namespace hkCompat_hk460r1_hk461r1
{
	// This function searches and updates all found meta data (hkClass) for
	// three classes as they were modified between Complete and
	// Spectrum 460r1 releases:
	//  - hkExtendedMeshShape
	//  - hkSphereShape
	//  - hkMassChangerModifierConstraintAtom
	// NOTE: The 460r1 class manifest reflects meta data for Spectrum 460r1 release.
	//
	static void UpdateMetadataFor460r1CompleteObjects(hkArray<hkVariant>& objectsInOut)
	{
		for( int i=0; i < objectsInOut.getSize(); ++i )
		{
			const hkClass* klass = objectsInOut[i].m_class;
			HK_ASSERT(0x54e32125, klass);
			const char* klassName = klass->getName();
			if( hkString::strCmp(klassName, "hkExtendedMeshShape") == 0 )
			{
				objectsInOut[i].m_class = &hkHavok460r1Classes::hkExtendedMeshShapeClass;
				HK_ASSERT2(0x54e32126, klass->getSignature() == objectsInOut[i].m_class->getSignature(), "The hkExtendedMeshShape object is corrupt and no versioning can be done.");
			}
			else if( hkString::strCmp(klassName, "hkSphereShape") == 0 )
			{
				objectsInOut[i].m_class = &hkHavok460r1Classes::hkSphereShapeClass;
			}
			else if( hkString::strCmp(klassName, "hkMassChangerModifierConstraintAtom") == 0 )
			{
				objectsInOut[i].m_class = &hkHavok460r1Classes::hkMassChangerModifierConstraintAtomClass;
			}
		}
	}
	static void Nop(hkVariant&, hkVariant&, hkObjectUpdateTracker&) {}

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

	// physics
	{ 0x5f31ebc7, 0x795d9fa, hkVersionUtil::VERSION_COPY, "hkSphereShape", Nop }, // Fixed padding for dma, HVK-4027

	// behavior
	{ 0x822a7bef, 0x6f02f92a, hkVersionUtil::VERSION_COPY, "hkbBlendingTransitionEffect", HK_NULL }, // new members
	{ 0xf61504a2, 0xb5cd4e89, hkVersionUtil::VERSION_COPY, "hkbStateMachine", HK_NULL }, // new members
	{ 0x9dca84ac, 0xfea091e8, hkVersionUtil::VERSION_COPY, "hkbStateMachineStateInfo", HK_NULL }, // new members
	{ 0xbdcda8e5, 0x35f9d035, hkVersionUtil::VERSION_COPY, "hkbStateMachineTransitionInfo", HK_NULL }, // new members

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
	&hkHavok461r1ClassList
};

static hkResult HK_CALL update(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker )
{
	UpdateMetadataFor460r1CompleteObjects(objectsInOut);
	return hkVersionUtil::updateSingleVersion( objectsInOut, tracker, hkVersionUpdateDescription );
}

extern const hkVersionRegistry::Updater hkVersionUpdater;
const hkVersionRegistry::Updater hkVersionUpdater =
{
	hkHavok460r1Classes::VersionString,
	hkHavok461r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk460r1_hk461r1

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
