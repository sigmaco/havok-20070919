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

namespace hkCompat_hk450b1_hk450r1
{

static void Motion_450b1_450r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor oldDeactivationNumInactiveFrames(oldObj, "deactivationNumInactiveFrames");
	hkClassMemberAccessor newDeactivationNumInactiveFrames(newObj, "deactivationNumInactiveFrames");

	HK_ASSERT( 0x1d0e56c0, oldDeactivationNumInactiveFrames.getClassMember().getCstyleArraySize() ==
							newDeactivationNumInactiveFrames.getClassMember().getCstyleArraySize() );
	for( int i = 0; i < newDeactivationNumInactiveFrames.getClassMember().getCstyleArraySize(); ++i )
	{
		newDeactivationNumInactiveFrames.asUint16(i) = static_cast<hkUint16>(oldDeactivationNumInactiveFrames.asUint8(i));
	}
}

static void Entity_450b1_450r1(
							   hkVariant& oldObj,
							   hkVariant& newObj,
							   hkObjectUpdateTracker& tracker)
{
	hkClassMemberAccessor oldMotion(oldObj, "motion");
	hkClassMemberAccessor newMotion(newObj, "motion");
	hkVariant oldMotionVariant = {oldMotion.object().getAddress(), &oldMotion.object().getClass()};
	hkVariant newMotionVariant = {newMotion.object().getAddress(), &newMotion.object().getClass()};

	Motion_450b1_450r1(oldMotionVariant, newMotionVariant, tracker);
}

static void ShouldNeverBeCalled_450b1_450r1(
											hkVariant& oldObj,
											hkVariant& newObj,
											hkObjectUpdateTracker& tracker)
{
	HK_ERROR( 0x50c1bb4a, "the object being versioned should not be present in a 4.5.0 b1 file" );
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

	// base
	BINARY_IDENTICAL(0xe1ac568b, 0xc6528005, "hkClass"), // changes in hkClassMember
	BINARY_IDENTICAL(0xd2665ef8, 0xebd682cb, "hkClassMember"), // added ALIGN_8 and ALIGN_16 enum values to Flags
	{ 0x4f93f28d, 0x809cf9d2, hkVersionUtil::VERSION_COPY, "hkMonitorStreamFrameInfo", HK_NULL }, // moved new members to the end

	// collide
	{ 0xfd7a7ad1, 0x2c06d878, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShape", HK_NULL },// Removed padding
	BINARY_IDENTICAL(0xcdc68ad6, 0xf1805598, "hkCollidable"), // m_ownerOffset // +nosave
	BINARY_IDENTICAL(0x386f6de0, 0xa539881b, "hkTypedBroadPhaseHandle"), // m_ownerOffset // +nosave
	{ 0xa878ccce, 0x80df0f90, hkVersionUtil::VERSION_COPY, "hkListShapeChildInfo", HK_NULL }, // Added m_numChildShapes
	{ 0x4a1f744e, 0xaa85f8c7, hkVersionUtil::VERSION_COPY, "hkListShape", HK_NULL }, // hkListShape::ChildInfo changed
	{ 0xf487d278, 0x2efdea58, hkVersionUtil::VERSION_COPY, "hkMoppEmbeddedShape", HK_NULL }, // Added extrusion

	// internal
	BINARY_IDENTICAL(0xfa5860da, 0x940569dc, "hkBroadPhaseHandle"), // m_id // +nosave

	// dynamics
	BINARY_IDENTICAL(0x1eea19cd, 0x4688e4c7, "hkEntitySpuCollisionCallback"), // added SPU_SEND_NONE enum value to SpuCollisionCallbackEventFilter
	{ 0xe9b10b82, 0x694e0fc1, hkVersionUtil::VERSION_COPY, "hkEntity", Entity_450b1_450r1 }, // m_motion member copies (hkMotion)
	BINARY_IDENTICAL(0xfcb91d3a, 0x66e8c84a, "hkWorldObject"), // changes in hkCollidable and hkTypedBroadPhaseHandle
		// hkWorldCinfo: added m_deactivationNumInactiveFramesSelectFlag0, m_deactivationNumInactiveFramesSelectFlag01 and m_deactivationIntegrateCounter
	{ 0x678213fa, 0x105bba8, hkVersionUtil::VERSION_COPY, "hkWorldCinfo", HK_NULL },
		// hkMotion: m_deactivationNumInactiveFrames is array of hkUint16
	{ 0x66989e6a, 0xb891f43f, hkVersionUtil::VERSION_COPY, "hkMotion", Motion_450b1_450r1 },

	// hkbehavior



	{ 0x6c68f22d, 0x19a6a186, hkVersionUtil::VERSION_COPY, "hkbHandIkModifier", HK_NULL }, 

	// these just appeared in "b1" which was not actually a Spectrum release, so there is no need to version them
	{ 0x86f25ce8, 0xae09c91c, hkVersionUtil::VERSION_COPY, "hkbVariableBindingSetBinding", ShouldNeverBeCalled_450b1_450r1 }, 
	{ 0xc0ed78f6, 0xf66f90bf, hkVersionUtil::VERSION_COPY, "hkbVariableBindingSet", ShouldNeverBeCalled_450b1_450r1 }, 

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
	&hkHavok450r1ClassList
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
	hkHavok450b1Classes::VersionString,
	hkHavok450r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk450b1_hk450r1

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
