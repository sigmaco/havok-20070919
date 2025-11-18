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

namespace hkCompat_hk451r1_hk452r1
{

static void Dummy_451r1_452r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
}

static void hkbStateMachineStateInfo_451r1_452r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	// Since the versioning code does not apply the BINARY_IDENTICAL to the TransitionInfos because
	// they are in an array, we have to manually copy "transitions"
	{
		hkClassMemberAccessor oldTransitions( oldObj, "transitions" );
		hkClassMemberAccessor newTransitions( newObj, "transitions" );

		const hkClassMember& oldm = oldTransitions.getClassMember();

		HK_ASSERT( 0x560123bc, oldm.getSizeInBytes() == newTransitions.getClassMember().getSizeInBytes() );

		hkString::memCpy( newTransitions.getAddress(), oldTransitions.getAddress(), oldm.getSizeInBytes() );
	}
}

static void hkbStateMachine_451r1_452r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	// the member "startState" has been renamed "startStateId"
	{
		hkClassMemberAccessor oldStartState( oldObj, "startState" );
		hkClassMemberAccessor newStartStateId( newObj, "startStateId" );

		newStartStateId.asInt32() = oldStartState.asInt32();
	}

	// the old members "m_enterStartStateOnActivate" and "m_randomStartState" are now "m_startStateMode"
	{
		hkClassMemberAccessor oldRandomStartState( oldObj, "randomStartState" );
		hkClassMemberAccessor newStartStateMode( newObj, "startStateMode" );

		if ( oldRandomStartState.asBool() )
		{
			newStartStateMode.asInt8() = 3;
		}
		else
		{
			hkClassMemberAccessor oldEnterStartStateOnActivate( oldObj, "enterStartStateOnActivate" );

			if ( !oldEnterStartStateOnActivate.asBool() )
			{
				newStartStateMode.asInt8() = 1;
			}
		}
	}

	// Since the versioning code does not apply the BINARY_IDENTICAL to the TransitionInfos because
	// they are in an array, we have to manually copy "globalTransitions"
	{
		hkClassMemberAccessor oldGlobalTransitions( oldObj, "globalTransitions" );
		hkClassMemberAccessor newGlobalTransitions( newObj, "globalTransitions" );

		const hkClassMember& oldm = oldGlobalTransitions.getClassMember();
		
		HK_ASSERT( 0x560123bc, oldm.getSizeInBytes() == newGlobalTransitions.getClassMember().getSizeInBytes() );

		hkString::memCpy( newGlobalTransitions.getAddress(), oldGlobalTransitions.getAddress(), oldm.getSizeInBytes() );
	}
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

	REMOVED("hkVersioningExceptionsArray"),
	REMOVED("hkVersioningExceptionsArrayVersioningException"),

	{ 0x0934018a, 0x91367f03, hkVersionUtil::VERSION_COPY, "hkRemoveTerminalsMoppModifier", HK_NULL }, // derives from hkReferencedObject
	REMOVED("hkMoppModifier"), // the abstract interface class has no reflection declaration anymore

	// hkbehavior

	{ 0x98f7a7ba, 0xb36b9af6, hkVersionUtil::VERSION_COPY, "hkbBehavior", HK_NULL },
	{ 0xdc92bc5e, 0xf606246c, hkVersionUtil::VERSION_COPY, "hkbCharacter", HK_NULL },
	{ 0x61822cef, 0x9c9c743c, hkVersionUtil::VERSION_COPY, "hkbCharacterFakeQueue", HK_NULL },
	{ 0xfad6810b, 0x08f29bb1, hkVersionUtil::VERSION_COPY, "hkbClipGenerator", HK_NULL },
	{ 0x72edbbbe, 0x7b9951fd, hkVersionUtil::VERSION_COPY, "hkbClipTrigger", HK_NULL },
	// this is only reflected for HavokAssembly so it should not have been serialized
	{ 0x5e3b5ef5, 0x3f3cf022, hkVersionUtil::VERSION_COPY, "hkbContext", HK_NULL },
	// this is only reflected for HavokAssembly so it should not have been serialized
	{ 0x5254307c, 0xf04222be, hkVersionUtil::VERSION_COPY, "hkbGeneratorOutput", Dummy_451r1_452r1 },
	{ 0x5946a34a, 0xfa94f179, hkVersionUtil::VERSION_COPY, "hkbSequence", HK_NULL },
	{ 0x70d14379, 0xc1f29013, hkVersionUtil::VERSION_COPY, "hkbStateMachine", hkbStateMachine_451r1_452r1 },
	{ 0xb13b1ad2, 0xebeee2c2, hkVersionUtil::VERSION_COPY, "hkbStateMachineStateInfo", hkbStateMachineStateInfo_451r1_452r1 },
	BINARY_IDENTICAL( 0x32d21e23, 0x4d94add9, "hkbStateMachineActiveTransitionInfo" ),
	BINARY_IDENTICAL( 0x3907f10b, 0xbdcda8e5, "hkbStateMachineTransitionInfo" ),

	// these are due to adding hkAlign directives
	{ 0xd1ed2dd, 0x307efb6d, hkVersionUtil::VERSION_COPY, "hkbFootIkControlData", HK_NULL },
	{ 0x18d9e930, 0x4a4cbd47, hkVersionUtil::VERSION_COPY, "hkbFootIkControlsModifier", HK_NULL },
	{ 0xf9b1d106, 0x907d2d0b, hkVersionUtil::VERSION_COPY, "hkbHandIkControlNormalData", HK_NULL },
	{ 0xeee7f219, 0xef425baf, hkVersionUtil::VERSION_COPY, "hkbHandIkControlPositionData", HK_NULL },
	{ 0xfa3ea3d9, 0xf5ba21b, hkVersionUtil::VERSION_COPY, "hkbPoweredRagdollControlData", HK_NULL },
	{ 0x47ffe114, 0x39513036, hkVersionUtil::VERSION_COPY, "hkbPoweredRagdollControlsModifier", HK_NULL },
	{ 0x28035065, 0xa6004a7c, hkVersionUtil::VERSION_COPY, "hkbPoweredRagdollModifier", HK_NULL },
	{ 0xcdf4ebd3, 0x3526c7c9, hkVersionUtil::VERSION_COPY, "hkbRigidBodyRagdollControlData", HK_NULL }, 
	{ 0xd19288e, 0xd378741c, hkVersionUtil::VERSION_COPY, "hkbRigidBodyRagdollControlsModifier", HK_NULL },
	{ 0xdde1d1c5, 0x32aab156, hkVersionUtil::VERSION_COPY, "hkbRigidBodyRagdollModifier", HK_NULL },

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
	&hkHavok452r1ClassList
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
	hkHavok451r1Classes::VersionString,
	hkHavok452r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk451r1_hk452r1

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
