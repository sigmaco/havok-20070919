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
	
#include <Common/Compat/hkHavokAllClasses.h>

static void hkExtendedMeshShapeShapesSubpart_hk410b1_hk410r1(
										hkVariant& oldObj,
										hkVariant& newObj,
										hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newNumChildShapes(newObj,		"numChildShapes");
	hkClassMemberAccessor oldNumShapes(oldObj,	"numShapes");

	if( newNumChildShapes.isOk() && oldNumShapes.isOk() )
	{
		newNumChildShapes.asInt32() = oldNumShapes.asInt32() = 0;
	}
}

static void hkExtendedMeshShapeTrianglesSubpart_hk410b1_hk410r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newNumTriangleShapes(newObj,		"numTriangleShapes");
	hkClassMemberAccessor oldNumShapes(oldObj,	"numShapes");

	if( newNumTriangleShapes.isOk() && oldNumShapes.isOk() )
	{
		newNumTriangleShapes.asInt32() = oldNumShapes.asInt32() = 0;
	}
}

static void hkExtendedMeshSubpartsArray_hk410b1_hk410r1(
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

static void hkExtendedMeshShape_hk410b1_hk410r1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker)
{
	hkExtendedMeshSubpartsArray_hk410b1_hk410r1(
					hkClassMemberAccessor(oldObj, "trianglesSubparts"),
					hkClassMemberAccessor(newObj, "trianglesSubparts"),
					tracker,
					hkExtendedMeshShapeTrianglesSubpart_hk410b1_hk410r1);

	hkExtendedMeshSubpartsArray_hk410b1_hk410r1(
					hkClassMemberAccessor(oldObj, "shapesSubparts"),
					hkClassMemberAccessor(newObj, "shapesSubparts"),
					tracker,
					hkExtendedMeshShapeShapesSubpart_hk410b1_hk410r1);
}

namespace hkCompat_hk410b1_hk410r1
{

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	//hkExtended Mesh Shape
	{ 0x22cb60f2, 0x03b79c63, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeShapesSubpart", hkExtendedMeshShapeShapesSubpart_hk410b1_hk410r1 },
	{ 0x573ee2c4, 0xb782ddda, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeTrianglesSubpart", hkExtendedMeshShapeTrianglesSubpart_hk410b1_hk410r1 },
	{ 0xbfeecff5, 0x32dd318e, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeSubpart", HK_NULL },
	{ 0xa22a9842, 0x4c103864, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShape", hkExtendedMeshShape_hk410b1_hk410r1 },

	// common
	{ 0x8bdd3e9a, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0xf598a34e, 0xf598a34e, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainer", HK_NULL },
	{ 0x853a899c, 0x853a899c, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainerNamedVariant", HK_NULL }, 
	{ 0x3d43489c, 0x3d43489c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x1667c01c, 0x1667c01c, hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL }, 
	{ 0x0a62c79f, 0x0a62c79f, hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL }, 
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },

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
	&hkHavok410r1ClassList
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
	hkHavok410b1Classes::VersionString,
	hkHavok410r1Classes::VersionString,
	update
};

} // namespace hkCompat_hk410b1_hk410r1

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
