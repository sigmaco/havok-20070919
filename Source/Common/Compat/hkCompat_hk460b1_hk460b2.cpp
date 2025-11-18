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

namespace hkCompat_hk460b1_hk460b2
{
	static void WorldObject_hk460b1_hk460b2( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		hkVersionUtil::renameMember(oldObj, "multithreadLock", newObj, "multiThreadCheck");
	}

	static void MaterialStriding_hk460b1_hk460b2( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor oldStriding( oldObj, "materialIndexStriding" );
		hkClassMemberAccessor newStriding( newObj, "materialIndexStriding" );

		HK_ASSERT2(0x54543212, oldStriding.asInt32() < hkUint16(-1), "Striding out of range" );
		newStriding.asInt16() = (hkUint16)oldStriding.asInt32();
	}

	static void hkExtendedMeshSubpartsArray_hk460b1_hk460b2(
		const hkClassMemberAccessor& oldObjMem,
		const hkClassMemberAccessor& newObjMem,
		hkObjectUpdateTracker& tracker, hkVersionUtil::VersionFunc versionFuncPtr)
	{
		hkClassMemberAccessor::SimpleArray& oldArray = oldObjMem.asSimpleArray();
		hkClassMemberAccessor::SimpleArray& newArray = newObjMem.asSimpleArray();
		HK_ASSERT( 0xad78555b, oldArray.size == newArray.size );
		hkVariant oldVariant = {HK_NULL, &oldObjMem.object().getClass()};
		hkVariant newVariant = {HK_NULL, &newObjMem.object().getClass()};
		hkInt32 oldSize = oldVariant.m_class->getObjectSize();
		hkInt32 newSize = newVariant.m_class->getObjectSize();
		for( int i = 0; i < oldArray.size; ++i )
		{
			oldVariant.m_object = static_cast<char*>(oldArray.data) + oldSize*i;
			newVariant.m_object = static_cast<char*>(newArray.data) + newSize*i;
			(versionFuncPtr)(oldVariant, newVariant, tracker);
		}
	}

	static void hkExtendedMeshShape_hk460b1_hk460b2(
		hkVariant& oldObj,
		hkVariant& newObj,
		hkObjectUpdateTracker& tracker)
	{
		hkExtendedMeshSubpartsArray_hk460b1_hk460b2(
			hkClassMemberAccessor(oldObj, "trianglesSubparts"),
			hkClassMemberAccessor(newObj, "trianglesSubparts"),
			tracker,
			MaterialStriding_hk460b1_hk460b2);

		hkExtendedMeshSubpartsArray_hk460b1_hk460b2(
			hkClassMemberAccessor(oldObj, "shapesSubparts"),
			hkClassMemberAccessor(newObj, "shapesSubparts"),
			tracker,
			MaterialStriding_hk460b1_hk460b2);
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
	{ 0x66e8c84a, 0x0582a274, hkVersionUtil::VERSION_COPY, "hkWorldObject", WorldObject_hk460b1_hk460b2 }, // m_multithreadLock renamed

	{ 0x0bf27438, 0x3b2f0b51, hkVersionUtil::VERSION_COPY, "hkStorageExtendedMeshShapeMeshSubpartStorage", hkExtendedMeshShape_hk460b1_hk460b2 }, 
	{ 0x5cbac904, 0x7d392dbc, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShape", hkExtendedMeshShape_hk460b1_hk460b2 }, 
	{ 0xcfa67b5f, 0x137ad522, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeShapesSubpart", MaterialStriding_hk460b1_hk460b2 },
	{ 0x1d62d58d, 0x3375309c, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeTrianglesSubpart", MaterialStriding_hk460b1_hk460b2 }, 
	{ 0x32dd318e, 0x7c9435c7, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeSubpart", MaterialStriding_hk460b1_hk460b2 }, 


	BINARY_IDENTICAL( 0x2d0d9c11, 0xf0612556, "hkConstraintInstance"), // added cloning enum

	// base
	BINARY_IDENTICAL( 0x7497262b, 0x1c3c8820, "hkMultiThreadLock" ), // renamed member and enums

	// behavior
	{ 0xebeee2c2, 0x9dca84ac, hkVersionUtil::VERSION_COPY, "hkbStateMachineStateInfo", HK_NULL }, // added m_inPackfile
	{ 0, 0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	{ "hkMultiThreadLock", "hkMultiThreadCheck" },
	{ HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&hkHavok460b2ClassList
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
	hkHavok460b1Classes::VersionString,
	hkHavok460b2Classes::VersionString,
	update
};

} // namespace hkCompat_hk460b1_hk460b2

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
