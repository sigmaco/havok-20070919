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
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Compat/hkHavokAllClasses.h>

static void AssertQFormat_330r1_400b1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	HK_ASSERT2(0xad7d7743, false, "Quantisation format has changed. This is not versioned");
}

static void WaveletSkeletalAnimation_330r1_400b1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newQFormat(newObj, "qFormat");
	hkClassMemberAccessor oldQFormat(oldObj, "qFormat");

	if (newQFormat.isOk() && oldQFormat.isOk())
	{
		const hkClass& oldQFormatClass = oldQFormat.getClassMember().getStructClass();
		hkClassMemberAccessor oldBitWidth( oldQFormat.asRaw(), oldQFormatClass, "bitWidth");

		const hkClass& newQFormatClass = newQFormat.getClassMember().getStructClass();
		hkClassMemberAccessor newMaxBitWidth( newQFormat.asRaw(), newQFormatClass, "maxBitWidth");

		if(oldBitWidth.isOk() && newMaxBitWidth.isOk())
		{
			newMaxBitWidth.asInt8() = oldBitWidth.asInt8();
		}
	}
	else
	{
		HK_ASSERT2(0xad7d77de, false, "member not found");
	}
}

namespace
{
	template <typename T>
	struct SimpleArray
	{
		T* data;
		int size;
	};
}

static void DeltaCompressedSkeletalAnimation_330r1_400b1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newQFormat(newObj, "qFormat");
	hkClassMemberAccessor oldQFormat(oldObj, "qFormat");

	hkClassMemberAccessor newTotalBlockSize(newObj, "totalBlockSize");

	if (newQFormat.isOk() && oldQFormat.isOk() && newTotalBlockSize.isOk())
	{
		const hkClass& oldQFormatClass = oldQFormat.getClassMember().getStructClass();
		hkClassMemberAccessor oldBitWidth( oldQFormat.asRaw(), oldQFormatClass, "bitWidth");

		const hkClass& newQFormatClass = newQFormat.getClassMember().getStructClass();
		hkClassMemberAccessor newMaxBitWidth( newQFormat.asRaw(), newQFormatClass, "maxBitWidth");

		if(oldBitWidth.isOk() && newMaxBitWidth.isOk())
		{
			newMaxBitWidth.asInt8() = oldBitWidth.asInt8();
		}

		{
			hkClassMemberAccessor newBlockSize(newObj, "blockSize");
			hkClassMemberAccessor newPreserved( newQFormat.asRaw(), newQFormatClass, "preserved");
			int spaceRequired = newPreserved.asInt8() * sizeof(hkReal);
			int bitSpaceRequired = newMaxBitWidth.asInt8() * ( newBlockSize.asInt32() - newPreserved.asInt8() );
			int byteSpaceRequired = ( bitSpaceRequired + 7 ) / 8;
			hkUint32 totalSize = spaceRequired + byteSpaceRequired;

			hkClassMemberAccessor newOffset( newQFormat.asRaw(), newQFormatClass, "offset");
			SimpleArray<hkReal>& newOffsetArray = *(SimpleArray<hkReal>*)newOffset.asRaw();
			int numD = newOffsetArray.size;

			newTotalBlockSize.asInt32() = totalSize*numD;
		}
	}
	else
	{
		HK_ASSERT2(0xad7d77de, false, "member not found");
	}
}

static void RootLevelContainerNamedVariant_330r1_400b1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor className(newObj, "className");
	hkClassMemberAccessor oldVariant(oldObj, "variant");

	if (className.isOk() && oldVariant.isOk())
	{
		char* variantClassName = hkString::strDup(oldVariant.asVariant().m_class->getName());
			tracker.addAllocation(variantClassName);
			className.asCstring() = variantClassName;
		}
	else
	{
		HK_ASSERT2(0xad7d77de, false, "member not found");
	}
}

static void RootLevelContainer_330r1_400b1(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newNamedVariant(newObj, "namedVariants");
	hkClassMemberAccessor oldNamedVariant(oldObj, "namedVariants");

	if( newNamedVariant.isOk() && oldNamedVariant.isOk() )
	{
		hkClassMemberAccessor::SimpleArray& newNamedVariantArray = newNamedVariant.asSimpleArray();
		hkClassMemberAccessor::SimpleArray& oldNamedVariantArray = oldNamedVariant.asSimpleArray();
		for( int i = 0; i < newNamedVariantArray.size; ++i )
		{
			const hkClass& oldNamedVariantClass = oldNamedVariant.object().getClass();
			void* oldNamedVariantObj = static_cast<char*>(oldNamedVariantArray.data) + i*oldNamedVariantClass.getObjectSize();
			const hkClass& newNamedVariantClass = newNamedVariant.object().getClass();
			void* newNamedVariantObj = static_cast<char*>(newNamedVariantArray.data) + i*newNamedVariantClass.getObjectSize();
			hkVariant oldVariant = {oldNamedVariantObj, &oldNamedVariantClass};
			hkVariant newVariant = {newNamedVariantObj, &newNamedVariantClass};
			RootLevelContainerNamedVariant_330r1_400b1( oldVariant, newVariant, tracker );
		}
	}
	else
	{
		HK_ASSERT2( 0xad7d77de, false, "member not found" );
	}
}

static void ShapeContainer_330r1_400b1(
	hkVariant& oldObj, const char* oldname,
	hkVariant& newObj, const char* newname,
	hkObjectUpdateTracker& tracker)
{
	// old {hkShape*} -> new {vtable*, hkShape*}
	hkClassMemberAccessor oldChildShape(oldObj, oldname);
	hkClassMemberAccessor newChildShape(newObj, newname);
	newChildShape.asPointer(1) = oldChildShape.asPointer(0);
	tracker.objectPointedBy( newChildShape.asPointer(1), hkAddByteOffset(newChildShape.asRaw(),sizeof(void*)) );
}

static void ChildPointerToShapeContainer_330r1_400b1(hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
{
	ShapeContainer_330r1_400b1(oldObj, "childShape", newObj, "childShape", tracker );
}
static void BvTreeShape_330r1_400b1(hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
{
	ShapeContainer_330r1_400b1(oldObj, "shapeCollection", newObj, "child", tracker );
}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

namespace hkCompat_hk330r1_hk400b1
{

hkVersionUtil::ClassAction UpdateActions[] =
{


	// common
	BINARY_IDENTICAL( 0x9e4ee5d9, 0xa52796eb, "hkClass" ), // classmember changed
	BINARY_IDENTICAL( 0x0afe235f, 0x2e50284b, "hkClassMember" ), // enum type_cstring added

	{ 0x65e259ea, 0xd486cfd9, hkVersionUtil::VERSION_COPY, "hkMonitorStreamFrameInfo", HK_NULL },
	{ 0x9dd3289c, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_COPY, "hkBoneAttachment", HK_NULL },
	{ 0x12a4e063, 0xf598a34e, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_COPY, "hkRootLevelContainer", RootLevelContainer_330r1_400b1 },
	{ 0x35e1060e, 0x853a899c, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_COPY, "hkRootLevelContainerNamedVariant", RootLevelContainerNamedVariant_330r1_400b1 }, // className
	{ 0x3d43489c, 0x3d43489c, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_INPLACE, "hkxMaterial", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_INPLACE, "hkxAttribute", HK_NULL },
	{ 0x8b69ead5, 0x1667c01c, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_MANUAL, "hkxAttributeGroup", HK_NULL }, // groupType -> name
	{ 0xb926cec1, 0x0a62c79f, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_MANUAL, "hkxNode", HK_NULL }, // pointed types changed
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL }, // 

	// physics
	{ 0xe15f41a4, 0x3ace2c22, hkVersionUtil::VERSION_COPY, "hkPhysicsSystem", HK_NULL }, // active flag added
	{ 0x66a50433, 0x0bf27438, hkVersionUtil::VERSION_COPY, "hkStorageMeshShapeSubpartStorage", HK_NULL },
	{ 0x1cd2a3e1, 0x51a73ef8, hkVersionUtil::VERSION_COPY, "hkMeshShapeSubpart", HK_NULL },

	// shape container
	{ 0x7c89c64b, 0xe3aed0af, hkVersionUtil::VERSION_COPY, "hkCapsuleShape", HK_NULL }, // enum rayhit added
	{ 0xcc8a20a1, 0x9c9970c7, hkVersionUtil::VERSION_COPY, "hkBvShape", ChildPointerToShapeContainer_330r1_400b1 }, // ShapeContainer
	{ 0x687e5738, 0xf45137d5, hkVersionUtil::VERSION_COPY, "hkBvTreeShape", BvTreeShape_330r1_400b1 }, // ShapeContainer
	{ 0xc9d47c1f, 0x2a85c23c, hkVersionUtil::VERSION_COPY, "hkConvexTransformShape", ChildPointerToShapeContainer_330r1_400b1 }, // ShapeContainer
	{ 0xd5ccc442, 0x47bccef9, hkVersionUtil::VERSION_COPY, "hkConvexTranslateShape", ChildPointerToShapeContainer_330r1_400b1 }, // ShapeContainer
	{ 0xab51d583, 0xaf9f656a, hkVersionUtil::VERSION_COPY, "hkTransformShape", ChildPointerToShapeContainer_330r1_400b1 }, // ShapeContainer
	{ 0xf5aa2dc6, 0xa1a981e1, hkVersionUtil::VERSION_COPY, "hkMeshShape", HK_NULL }, // padding added
	{ 0x6bf97880, 0x091dd90f, hkVersionUtil::VERSION_COPY, "hkShapeCollection", HK_NULL }, // ShapeContainer
	{ 0xa7ff561d, 0x96076622, hkVersionUtil::VERSION_COPY, "hkConstrainedSystemFilter", HK_NULL }, // extra interface
	{ 0xcd195550, 0x0049fef3, hkVersionUtil::VERSION_COPY, "hkVehicleInstance", HK_NULL },

	// animation
	{ 0x7aa3635d, 0x309d43f9, hkVersionUtil::VERSION_COPY, "hkWaveletSkeletalAnimationQuantizationFormat", AssertQFormat_330r1_400b1 },
	{ 0x7aa3635d, 0x309d43f9, hkVersionUtil::VERSION_COPY, "hkDeltaCompressedSkeletalAnimationQuantizationFormat", AssertQFormat_330r1_400b1 },
	{ 0xce906bbf, 0xfd1fe320, hkVersionUtil::VERSION_COPY, "hkWaveletSkeletalAnimation", WaveletSkeletalAnimation_330r1_400b1 }, // added new array, renamed member
	{ 0x2c3bd732, 0xfdee6f42, hkVersionUtil::VERSION_COPY, "hkDeltaCompressedSkeletalAnimation", DeltaCompressedSkeletalAnimation_330r1_400b1 }, // added new array, renamed member
	{ 0xc3144962, 0xeddacc32, hkVersionUtil::VERSION_COPY, "hkSkeletonMapper", HK_NULL }, // added enum ConstraintSource
	
	REMOVED("hkTriPatchTriangle"),

	{ 0,0, 0, HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	HK_NULL, // no renames
	UpdateActions,
	&hkHavok400b1ClassList
};

inline static const hkClass* findClassFromObject(const void* object, hkArray<hkVariant>& objects)
{
	for (int i = 0; i < objects.getSize(); ++i)
	{
		if (objects[i].m_object == object)
		{
			return objects[i].m_class;
		}
	}
	return HK_NULL;
}

inline static void updateRootLevelContainer(hkRootLevelContainer& container, hkArray<hkVariant>& objects)
{
	for (int i = 0; i < container.m_numNamedVariants; ++i)
	{
		hkRootLevelContainer::NamedVariant& namedVariant = container.m_namedVariants[i];
		const hkVariant& variant = namedVariant.getVariant();
		if (namedVariant.getTypeName() == HK_NULL)
		{
			const hkClass* klass = findClassFromObject(variant.m_object, objects);
			HK_ASSERT(0x15a09058, klass != HK_NULL);
			namedVariant.set(const_cast<char*>(namedVariant.getName()), variant.m_object, klass);
			const_cast<hkVariant*>(&variant)->m_class = HK_NULL;
		}
		HK_ASSERT(0x6087f47f, namedVariant.getTypeName() != HK_NULL);
	}
}

inline static hkRootLevelContainer* setTypeNameForNamedVariants(hkArray<hkVariant>& objects)
{
	for (int i = 0; i < objects.getSize(); ++i)
	{
		if (hkString::strCmp(objects[i].m_class->getName(), "hkRootLevelContainer") == 0)
		{
			updateRootLevelContainer(*static_cast<hkRootLevelContainer*>(objects[i].m_object), objects);
		}
	}
	return HK_NULL;
}

static hkResult HK_CALL update(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker )
{
	if( hkVersionUtil::updateSingleVersion( objectsInOut, tracker, hkVersionUpdateDescription ) == HK_SUCCESS )
	{
		setTypeNameForNamedVariants(objectsInOut);
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

extern const hkVersionRegistry::Updater hkVersionUpdater;
const hkVersionRegistry::Updater hkVersionUpdater =
{
	hkHavok330r1Classes::VersionString,
	hkHavok400b1Classes::VersionString,
	update
};

} // namespace hkCompat_hk330r1_hk400b1

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
