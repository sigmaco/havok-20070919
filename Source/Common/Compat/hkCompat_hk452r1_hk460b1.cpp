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

namespace hkCompat_hk452r1_hk460b1
{

	// hkRagdollInstance : new m_boneToRigidBodyMap array should be initialized to [0,1,2,3,4...]
	static void RagdollInstance_hk452r1_hk460b1( hkVariant& ,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor rigidBodies(newObj, "rigidBodies");
		const int numRigidBodides = rigidBodies.asSimpleArray().size;

		hkClassMemberAccessor boneToRigidBodyMap (newObj, "boneToRigidBodyMap");
		hkArray<int>* arr = reinterpret_cast<hkArray<int>*> (boneToRigidBodyMap.getAddress());

		arr->setSize(numRigidBodides);
		for (int i=0; i<numRigidBodides; ++i)
		{
			(*arr)[i] = i;
		}
	}

	// hkContactPointMaterial friction type has changed to hkUFloat8
	static void hkContactPointMaterial_hk452r1_hk460b1(	hkVariant& oldObj,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor oldFriction(oldObj, "friction");
		hkClassMemberAccessor newFriction(newObj, "friction");

		int value = oldFriction.asInt16();
		hkReal fValue = value * (1.0f/256.0f);
		hkUFloat8 nValue = fValue;
		newFriction.asInt8() = nValue.m_value;
	}

	// enabledChildren
	static void hkListShape_hk452r1_hk460b1(	hkVariant& ,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor newEnabled(newObj, "enabledChildren");
		hkInt32* enabled = &newEnabled.asInt32();
		for (int i = 0; i < 256/32; i++)
		{
			enabled[i] = unsigned(-1);
		}
	}

	static void hkExtendedMeshShape_hk452r1_hk460b1(	hkVariant& oldObj,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor oldTriangleSubparts(oldObj,	"m_trianglesSubparts");
		hkClassMemberAccessor newTriangleSubparts(newObj,	"m_trianglesSubparts");

		hkClassMemberAccessor oldShapesSubparts(oldObj,		"m_shapesSubparts");
		hkClassMemberAccessor newShapesSubparts(newObj,		"m_shapesSubparts");

		newTriangleSubparts.asSimpleArray() = oldTriangleSubparts.asSimpleArray();
		newShapesSubparts.asSimpleArray() = oldShapesSubparts.asSimpleArray();
	}

	static void hkPackedConvexVerticesShape_hk452r1_hk460b1(	hkVariant& oldObj,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		// They're actually identical 
	}

	// this struct is identical to hkbHandIkModifier::Hand.
	struct DummyHand
	{
		hkVector4 m_elbowAxisLS;
		hkVector4 m_backHandNormalInHandSpace; 
		hkReal m_cosineMaxElbowAngle;
		hkReal m_cosineMinElbowAngle;
		hkInt16 m_handIndex;
	};


	static void hkbHandIkModifier_hk452r1_hk460b1(	hkVariant& oldObj,	hkVariant& newObj,	hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor oldElbowAxisLS(oldObj, "elbowAxisLS");
		hkClassMemberAccessor oldBackHandNormalInHandSpace(oldObj, "backHandNormalInHandSpace");
		hkClassMemberAccessor oldCosineMaxElbowAngle(oldObj, "cosineMaxElbowAngle");
		hkClassMemberAccessor oldCosineMinElbowAngle(oldObj, "cosineMinElbowAngle");
		hkClassMemberAccessor newHands(newObj, "hands");

		// The idea here is that rather than using the tracker to track the memory for the array, we'll just
		// take advantage of the fact that hkArrays can already understand when they've done a heap
		// allocation as opposed to being in a packfile.

		// cast the array to the identical Dummy type
		hkArray<DummyHand>* newHandsArrayPtr = static_cast<hkArray<DummyHand>*>(newHands.getAddress());

		// call the placement constructor on the hands array to initialize it
		new (newHandsArrayPtr) hkArray<DummyHand>();

		// grow the array to size 2 (on the heap)
		newHandsArrayPtr->setSize(2);

		// copy the data from individual c-style arrays to the array of Hands
		(*newHandsArrayPtr)[0].m_elbowAxisLS = (hkVector4&)(oldElbowAxisLS.asVector4(0));
		(*newHandsArrayPtr)[1].m_elbowAxisLS = (hkVector4&)(oldElbowAxisLS.asVector4(1));

		(*newHandsArrayPtr)[0].m_backHandNormalInHandSpace = (hkVector4&)(oldBackHandNormalInHandSpace.asVector4(0));
		(*newHandsArrayPtr)[1].m_backHandNormalInHandSpace = (hkVector4&)(oldBackHandNormalInHandSpace.asVector4(1));

		(*newHandsArrayPtr)[0].m_cosineMaxElbowAngle = oldCosineMaxElbowAngle.asReal(0);
		(*newHandsArrayPtr)[1].m_cosineMaxElbowAngle = oldCosineMaxElbowAngle.asReal(1);

		(*newHandsArrayPtr)[0].m_cosineMinElbowAngle = oldCosineMinElbowAngle.asReal(0);
		(*newHandsArrayPtr)[1].m_cosineMinElbowAngle = oldCosineMinElbowAngle.asReal(1);

		(*newHandsArrayPtr)[0].m_handIndex = 0;
		(*newHandsArrayPtr)[1].m_handIndex = 1;
	}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define SKIPPED(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_SKIPPED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	// hkbase
	BINARY_IDENTICAL( 0xc6528005, 0x731c1b21, "hkClass" ), // changed hkClassMember
	BINARY_IDENTICAL( 0xebd682cb, 0xe0747dde, "hkClassMember" ), // enum hkClassMember::Type TYPE_FLAGS added

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
	{ 0x2c8afd32, 0x154948e8, hkVersionUtil::VERSION_COPY, "hkRagdollInstance", RagdollInstance_hk452r1_hk460b1 }, // New m_boneToRigidBodyMap member
	{ 0x14c48684, 0xafa2377e, hkVersionUtil::VERSION_COPY, "hkEntity", HK_NULL },	// m_breakOffPartsUtil added
	{ 0xed923a6e, 0x2ec055b9, hkVersionUtil::VERSION_COPY, "hkContactPointMaterial", hkContactPointMaterial_hk452r1_hk460b1 }, // maxImpulse added
	{ 0xaa85f8c7, 0x090cd72e, hkVersionUtil::VERSION_COPY, "hkListShape", hkListShape_hk452r1_hk460b1 }, // enabled added
	{ 0x80df0f90, 0x6d1dc26a, hkVersionUtil::VERSION_COPY, "hkListShapeChildInfo", HK_NULL},

	{ 0x2c06d878, 0x5cbac904, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShape", hkExtendedMeshShape_hk452r1_hk460b1 },
	{ 0x3add78e, 0x4f54c5ac, hkVersionUtil::VERSION_COPY, "hkMoppBvTreeShape", HK_NULL },

	{ 0xf967278c, 0x3e554e42, hkVersionUtil::VERSION_COPY, "hkPackedConvexVerticesShape", hkPackedConvexVerticesShape_hk452r1_hk460b1 }, // Fixed serialization of  hkPackedConvexVerticesShape fir XML HVK-3848 
	{ 0xd6ea9f63, 0x3749cfce, hkVersionUtil::VERSION_COPY, "hkVehicleData", HK_NULL }, // HVK-3880: mass clipping added to the vehicle friction solver

	{ 0x3b79c63, 0xcfa67b5f, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeShapesSubpart", HK_NULL }, // Padding added
	{ 0xae96f6a3, 0x1d62d58d, hkVersionUtil::VERSION_COPY, "hkExtendedMeshShapeTrianglesSubpart", HK_NULL }, // Welding changes
	{ 0xdf9760a, 0xd296d43b, hkVersionUtil::VERSION_COPY, "hkMeshShapeSubpart", HK_NULL }, // Welding changes
	{ 0xcd463d32, 0xb2b41feb, hkVersionUtil::VERSION_COPY, "hkWeldingUtility", HK_NULL }, // Welding changes
	{ 0x5bef2a7, 0x2d292fcc, hkVersionUtil::VERSION_COPY, "hkMeshShape", HK_NULL }, // Welding changes

	BINARY_IDENTICAL(0x24b3d6bc, 0xd97d1004, "hkSkeletalAnimation"), // renamed enum to avoid name clash

	REMOVED("hkVersioningExceptionsArray"),
	REMOVED("hkVersioningExceptionsArrayVersioningException"),
	REMOVED("hkMoppModifier"), // the abstract interface class has no reflection declaration anymore

	// hkbehavior
	{ 0x924950d0, 0xc6656965, hkVersionUtil::VERSION_COPY, "hkbBlenderGeneratorChild", HK_NULL },
	{ 0xbd1b0c10, 0x93ff2b59, hkVersionUtil::VERSION_COPY, "hkbBlenderGenerator", HK_NULL }, 
	{ 0x3f3cf022, 0x4333653e, hkVersionUtil::VERSION_COPY, "hkbContext", HK_NULL }, 
	{ 0x840d47d6, 0xe27a0994, hkVersionUtil::VERSION_COPY, "hkbDemoConfig", HK_NULL },
	{ 0xf04222be, 0x9589e4fc, hkVersionUtil::VERSION_COPY, "hkbGeneratorOutput", HK_NULL },
	{ 0x19a6a186, 0x02b2f4ff, hkVersionUtil::VERSION_COPY, "hkbHandIkModifier", hkbHandIkModifier_hk452r1_hk460b1 },
	{ 0xad81cd2d, 0xc6acc99a, hkVersionUtil::VERSION_COPY, "hkbReachModifier", HK_NULL },
	{ 0xae09c91c, 0xfc005983, hkVersionUtil::VERSION_COPY, "hkbVariableBindingSetBinding", HK_NULL },
	{ 0xf66f90bf, 0x7d6e4cea, hkVersionUtil::VERSION_COPY, "hkbVariableBindingSet", HK_NULL },
	REMOVED("hkbHandIkControlNormalData"),
	REMOVED("hkbHandIkControlPositionData"),

	// fx
	{ 0x6451059e, 0x9e73639b, hkVersionUtil::VERSION_COPY, "hkFxClothBodySubsystemCollection", HK_NULL }, // added bendLinks and hingeLinks simple arrays
	{ 0xfc4417b2, 0x9d54b954, hkVersionUtil::VERSION_COPY, "hkFxParticleBodySubSystemCollection", HK_NULL }, // changes in hkFxParticle
	{ 0xfb2932ed, 0xb2818c53, hkVersionUtil::VERSION_COPY, "hkFxParticle", HK_NULL }, // added m_mass
	{ 0x14c4f745, 0x6e9d6e54, hkVersionUtil::VERSION_COPY, "hkFxPhysicsCollection", HK_NULL }, // changes in hkFxParticleBodySubSystemCollection and hkFxClothBodySubsystemCollection

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
	&hkHavok460b1ClassList
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
	hkHavok452r1Classes::VersionString,
	hkHavok460b1Classes::VersionString,
	update
};

} // namespace hkCompat_hk452r1_hk460b1

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
