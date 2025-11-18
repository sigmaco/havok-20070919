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

#include <Common/Compat/hkHavokAllClasses.h>

namespace hkCompat_hk320_hk330a2
{

static void MalleableConstraintData(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newStrength(newObj, "strength");
	hkClassMemberAccessor oldTau(oldObj, "tau");
	if( newStrength.isOk() && oldTau.isOk() )
	{
		newStrength.asReal() = oldTau.asReal();
	}
	else
	{
		HK_ASSERT2(0xad7d77dd, false, "member not found");
	}
}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	{ 0x7ff383a1, 0x7c518cec, hkVersionUtil::VERSION_COPY, "hkRagdollConstraintData", HK_NULL }, // removed m_anglesHavok30
	{ 0x47194132, 0xdd8f8ace, hkVersionUtil::VERSION_COPY, "hkMalleableConstraintData", MalleableConstraintData }, // members removed and added: tau+dumping replaced by strength

	{ 0x448142a7, 0xb368f9bd, hkVersionUtil::VERSION_MANUAL, "hkConstraintData", HK_NULL }, // enum scope
	{ 0xda2ae69f, 0x50520e7d, hkVersionUtil::VERSION_MANUAL, "hkConstraintInstance", HK_NULL }, // enumerations added, virtual function added, members changed from protected to public
	{ 0x19e37679, 0xa03b1417, hkVersionUtil::VERSION_COPY, "hkVelocityConstraintMotor", HK_NULL }, // member added, defaults to false
	
	BINARY_IDENTICAL(0x7e6045e5, 0x472ddf28, "hkMultiSphereShape"), // enum MAX_SPHERES made anonymous
	BINARY_IDENTICAL(0xc70eb5bb, 0x7d7692dc, "hkMultiThreadLock"), // AccessType global->scoped

	{ 0x9dd3289c, 0x9dd3289c, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0x12a4e063, 0x12a4e063, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainer", HK_NULL },
	{ 0x35e1060e, 0x35e1060e, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainerNamedVariant", HK_NULL },
	{ 0x3d43489c, 0x3d43489c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },
	// enum global->local in hkxAttribute
	{ 0x1388d601, 0x914da6c1, hkVersionUtil::VERSION_MANUAL | hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x342bf1c8, 0x8b69ead5, hkVersionUtil::VERSION_MANUAL | hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL },
	{ 0x2641039e, 0xb926cec1, hkVersionUtil::VERSION_MANUAL | hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL },
	BINARY_IDENTICAL(0x8c11d1f2, 0xb330fa01, "hkPackfileHeader"), // version string 12 -> 16 chars

	{ 0xe6bd02ee, 0x9bb15af4, hkVersionUtil::VERSION_MANUAL, "hkxAnimatedFloat", HK_NULL }, // enum scope
	{ 0x1eba1f03, 0x95bd90ad, hkVersionUtil::VERSION_MANUAL, "hkxAnimatedMatrix", HK_NULL }, // enum scope
	{ 0xa9adb3a6, 0xfe98cabd, hkVersionUtil::VERSION_MANUAL, "hkxAnimatedVector", HK_NULL }, // enum scope

	{ 0,0, 0, HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	HK_NULL, // no renames
	UpdateActions,
	&hkHavok330a2ClassList
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
	hkHavok320Classes::VersionString,
	hkHavok330a2Classes::VersionString,
	update
};

} // namespace hkCompat_hk320_hk330a2

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
