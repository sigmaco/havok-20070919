/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Compat/hkCompat.h>
#include <Common/Compat/hkCompatUtil.h>
#include <Common/Serialize/Version/hkVersionRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>

#include <Common/Compat/hkHavokAllClasses.h>

namespace hkCompat_hk330a2_hk330b1
{

static void PositionConstraintMotor(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newMin(newObj, "minForce");
	hkClassMemberAccessor newMax(newObj, "maxForce");
	hkClassMemberAccessor oldMax(oldObj, "maxForce");

	if (newMin.isOk() && newMax.isOk() && oldMax.isOk())
	{
		newMin.asReal() = - oldMax.asReal();
		newMax.asReal() = + oldMax.asReal();
	}
	else
	{
		HK_ASSERT2(0xad7d77de, false, "member not found");
	}
}

static void VelocityConstraintMotor(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkVersionUtil::renameMember(oldObj, "maxNegForce", newObj, "minForce");
	hkVersionUtil::renameMember(oldObj, "maxPosForce", newObj, "maxForce");
}

static void SpringDamperConstraintMotor(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkVersionUtil::renameMember(oldObj, "maxNegForce", newObj, "minForce");
	hkVersionUtil::renameMember(oldObj, "maxPosForce", newObj, "maxForce");
}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }


static hkVersionUtil::ClassAction UpdateActions[] =
{
	{ 0x1c50563b, 0xead954fd, hkVersionUtil::VERSION_COPY, "hkPositionConstraintMotor", PositionConstraintMotor }, // max/min forces moved to base class
	{ 0xa03b1417, 0x94d2e665, hkVersionUtil::VERSION_COPY, "hkVelocityConstraintMotor", VelocityConstraintMotor }, // member added, defaults to false + max/min forces moved to base class
	{ 0x48377d86, 0xb29a4f46, hkVersionUtil::VERSION_COPY, "hkSpringDamperConstraintMotor", SpringDamperConstraintMotor }, // max/min forces moved to base class

	{0xbfc428d3, 0xbf0e8138, hkVersionUtil::VERSION_COPY, "hkPoweredChainData", HK_NULL }, // Array<ConstraintInfo> changed
	{0x173a57ec, 0xf88aee25, hkVersionUtil::VERSION_COPY, "hkPoweredChainDataConstraintInfo", HK_NULL }, // removed m_cfm*, moved m_bTc

	REMOVED("hkConstraintChainDriverDataTarget"),
	REMOVED("hkConstraintChainDriverData"),
	REMOVED("hkTriPatchTriangle"),

	BINARY_IDENTICAL(0xda8c7d7d, 0x82ef3c01, "hkConstraintMotor"), // enum added
	BINARY_IDENTICAL(0xb368f9bd, 0xde4be9fc, "hkConstraintData"), // enum type_chain_driver removed
	
	{ 0x9dd3289c, 0x9dd3289c, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0x12a4e063, 0x12a4e063, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainer", HK_NULL },
	{ 0x35e1060e, 0x35e1060e, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainerNamedVariant", HK_NULL },
	{ 0x3d43489c, 0x3d43489c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x8b69ead5, 0x8b69ead5, hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL },
	{ 0xb926cec1, 0xb926cec1, hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL },

	BINARY_IDENTICAL(0xb330fa01, 0xff8ce40d, "hkPackfileHeader"), // contentsClass -> contentsClassName

	{ 0,0, 0, HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	HK_NULL, // no renames
	UpdateActions,
	&hkHavok330b1ClassList
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
	hkHavok330a2Classes::VersionString,
	hkHavok330b1Classes::VersionString,
	update
};

} // namespace hkCompat_hk330a2_hk330b1

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
