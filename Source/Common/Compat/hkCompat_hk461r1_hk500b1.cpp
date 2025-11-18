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

namespace hkCompat_hk461r1_hk500b1
{
	static void NoActionTaken (hkVariant&, hkVariant&, hkObjectUpdateTracker&)
	{
	}

	static void Update_hkClassMember( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		hkClassMemberAccessor oldFlags(oldObj, "flags");
		hkClassMemberAccessor newFlags(oldObj, "flags"); // actually a hkFlags<...,hkUint16>
		newFlags.asUint16() = oldFlags.asUint16();
	}

	static void Update_hkClass( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		HK_ASSERT2(0, false, "The meta-data must be update before the versioning process.");

		hkClassMemberAccessor oldNumDeclaredMembers(oldObj,"numDeclaredMembers");
		hkClassMemberAccessor newNumDeclaredMembers(newObj,"numDeclaredMembers");
		HK_ASSERT( 0x23f1b608, oldNumDeclaredMembers.asInt32() == newNumDeclaredMembers.asInt32() );
		int nmembers = oldNumDeclaredMembers.asInt32();
		hkClassMemberAccessor oldDeclaredMembers(oldObj,"declaredMembers");
		hkClassMemberAccessor newDeclaredMembers(newObj,"declaredMembers");
		void* oldMembers = oldDeclaredMembers.asPointer();
		void* newMembers = newDeclaredMembers.asPointer();
		hkVariant om; om.m_class = oldDeclaredMembers.getClassMember().getClass();
		hkVariant nm; nm.m_class = newDeclaredMembers.getClassMember().getClass();

		for( int i = 0; i < nmembers; ++i )
		{
			om.m_object = reinterpret_cast<void**>(oldMembers)[i];
			nm.m_object = reinterpret_cast<void**>(newMembers)[i];
			Update_hkClassMember( om, nm, tracker );
		}
	}

	static void Update_hkSerializedAgentNnEntry (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		HK_ASSERT2(0, false, "hkpSerializedAgentNnEntry update function is not implemented.");
	}

	static void ConvertUserDataFromUint32ToUlong (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		hkClassMemberAccessor oldMember( oldObj, "userData" );
		hkClassMemberAccessor newMember( newObj, "userData" );
		newMember.asUlong() = (hkUlong)oldMember.asUint32();
	}

	static void Update_hkMouseSpringAction (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		ConvertUserDataFromUint32ToUlong(oldObj, newObj, tracker);
	}

	static void ConvertKeyframedRigidMotion(hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		{
			hkClassMemberAccessor oldMember( oldObj, "savedMotion" );
			hkClassMemberAccessor newMember( newObj, "savedMotion" );
			newMember.asPointer() = oldMember.asPointer();
		}
		{
			hkClassMemberAccessor oldMember( oldObj, "savedQualityTypeIndex" );
			hkClassMemberAccessor newMember( newObj, "savedQualityTypeIndex" );
			newMember.asInt16() = (hkInt16)oldMember.asInt32();
		}
	}
	static void ConvertMotionState( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& )
	{
		{
			hkClassMemberAccessor oldMember( oldObj, "deactivationClass" );
			hkClassMemberAccessor newMember( newObj, "deactivationClass" );
			newMember.asInt8() = (hkInt8)oldMember.asInt16();
		}
		{
			hkClassMemberAccessor oldMember( oldObj, "maxLinearVelocity" );
			hkClassMemberAccessor newMember( newObj, "maxLinearVelocity" );
			hkUFloat8 vel = oldMember.asReal();
			newMember.asInt8() = vel.m_value;
		}
		{
			hkClassMemberAccessor oldMember( oldObj, "maxAngularVelocity" );
			hkClassMemberAccessor newMember( newObj, "maxAngularVelocity" );
			hkUFloat8 vel = oldMember.asReal();
			newMember.asInt8() = vel.m_value;
		}
	}

	static void _ConvertEmbeddedStruct( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker, const char* memberName, hkVersionUtil::VersionFunc versionFunc )
	{
		hkClassMemberAccessor oldMember( oldObj, memberName );
		hkClassMemberAccessor newMember( newObj, memberName );

		hkVariant old;  old.m_class  = &oldMember.object().getClass();  old.m_object  = oldMember.object().getAddress();
		hkVariant new0; new0.m_class = &newMember.object().getClass();  new0.m_object = newMember.object().getAddress();

		versionFunc( old, new0, tracker );
	}

	static void ConvertMotion(hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		_ConvertEmbeddedStruct( oldObj, newObj, tracker, "motionState", ConvertMotionState );
	}

	static void ConvertEntity( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		_ConvertEmbeddedStruct( oldObj, newObj, tracker, "motion", ConvertMotion );
	}

	static void Update_hkWorldObject (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		hkClassMemberAccessor oldMember( oldObj, "userData" );
		hkClassMemberAccessor newMember( newObj, "userData" );
		newMember.asUlong() = (hkUlong)oldMember.asPointer();
	}

	static void Update_hkShapePhantom (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		Update_hkWorldObject(oldObj, newObj, tracker);
		_ConvertEmbeddedStruct( oldObj, newObj, tracker, "motionState", ConvertMotionState );
	}

	static void Update_hkAabbPhantom (hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker)
	{
		Update_hkWorldObject(oldObj, newObj, tracker);
	}

	static void Update_hkbBlendingTransitionEffect( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		// the type on endMode changed so I need to manually copy it
		hkClassMemberAccessor oldMember( oldObj, "endMode" );
		hkClassMemberAccessor newMember( newObj, "endMode" );

		newMember.asInt8() = oldMember.asInt8();
	}

	static void Update_hkbRigidBodyRagdollModifier( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		// The struct in the controlDataPalette array now has one fewer reals, and is of a completely different type,
		// although they are nearly identical.  We'll just copy the old values over.
		// The missing one was at the end of the struct so it is easy.

		hkClassMemberAccessor oldMember( oldObj, "controlDataPalette" );
		hkClassMemberAccessor newMember( newObj, "controlDataPalette" );

		// cast the address of the member to an array
		hkArray<hkReal>* oldArrayPtr = static_cast<hkArray<hkReal>*>(oldMember.getAddress());
		hkArray<hkReal>* newArrayPtr = static_cast<hkArray<hkReal>*>(newMember.getAddress());

		int count = oldArrayPtr->getSize();
		hkReal* oldData = &(*oldArrayPtr)[0];
		hkReal* newData = &(*newArrayPtr)[0];
		int oldStride = oldMember.getClassMember().getStructClass().getObjectSize();
		int newStride = newMember.getClassMember().getStructClass().getObjectSize();

		for( int i = 0; i < count; i++ )
		{
			hkString::memCpy( newData, oldData, newStride ); // the new size determines how much to copy
			oldData += oldStride;
			newData += newStride;
		}
	}

	static void Update_hkbStateMachineTransitionInfoInternal( hkVariant& oldObj, hkVariant& newObj, bool isLocalWildcard, hkObjectUpdateTracker& tracker )
	{
		hkClassMemberAccessor oldFlag( oldObj, "flags" );
		hkClassMemberAccessor newFlag( newObj, "flags" );

		newFlag.asInt16() = oldFlag.asInt16();

		if( isLocalWildcard )
		{
			// If the transitions are from the list of global transitions then we need
			// set the local wildcard flag
			newFlag.asInt16() |= 0x800;
		}
	}

	static void Update_TransitionInfoArray( hkVariant& oldObj, hkVariant& newObj, const char* memberName, bool areLocalWildcards, hkObjectUpdateTracker& tracker )
	{
		hkClassMemberAccessor oldTransitions( oldObj, memberName );
		hkClassMemberAccessor newTransitions( newObj, memberName );

		const int numTransitions = oldTransitions.asSimpleArray().size;

		hkVariant oldTransitionInfoVariant;
		hkVariant newTransitionInfoVariant;

		oldTransitionInfoVariant.m_class = &oldTransitions.object().getClass();
		newTransitionInfoVariant.m_class = &newTransitions.object().getClass();

		int oldTransitionInfoStride = oldTransitions.getClassMember().getStructClass().getObjectSize();
		int newTransitionInfoStride = newTransitions.getClassMember().getStructClass().getObjectSize();

		for( int i = 0; i < numTransitions; ++i )
		{
			oldTransitionInfoVariant.m_object = static_cast<char*>(oldTransitions.asSimpleArray().data) + i * oldTransitionInfoStride;
			newTransitionInfoVariant.m_object = static_cast<char*>(newTransitions.asSimpleArray().data) + i * newTransitionInfoStride;

			Update_hkbStateMachineTransitionInfoInternal( oldTransitionInfoVariant, newTransitionInfoVariant, areLocalWildcards, tracker );
		}
	}

	static void Update_hkbStateMachine( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		Update_TransitionInfoArray( oldObj, newObj, "globalTransitions", true, tracker );
	}

	static void Update_hkbStateMachineStateInfo( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		Update_TransitionInfoArray( oldObj, newObj, "transitions", false, tracker );
	}

	static void Update_hkbStateMachineTransitionInfo( hkVariant& oldObj, hkVariant& newObj, hkObjectUpdateTracker& tracker )
	{
		HK_ERROR( 0x29d6a3f5, "This function should never be called." );
	}

	extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;

	static void Update_hkRootLevelContainerNamedVariant(
		hkVariant& oldObj,
		hkVariant& newObj,
		hkObjectUpdateTracker& tracker )
	{
		hkClassMemberAccessor oldClassName(oldObj, "className");
		hkClassMemberAccessor newClassName(newObj, "className");

		if (oldClassName.isOk() && newClassName.isOk())
		{
			const char* oldName = oldClassName.asCstring();
			for( int i = 0; hkVersionUpdateDescription.renames[i].newName != HK_NULL; ++i )
			{
				if( hkString::strCmp(oldName, hkVersionUpdateDescription.renames[i].oldName) == 0 )
				{
					char* newName = hkString::strDup(hkVersionUpdateDescription.renames[i].newName);
					tracker.addAllocation(newName);
					newClassName.asCstring() = newName;
					break;
				}
			}
		}
		else
		{
			HK_ASSERT2(0xad7d77de, false, "member not found");
		}
	}

	static void Update_hkRootLevelContainer(
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
				Update_hkRootLevelContainerNamedVariant( oldVariant, newVariant, tracker );
			}
		}
		else
		{
			HK_ASSERT2( 0xad7d77de, false, "member not found" );
		}
	}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

static hkVersionUtil::ClassAction UpdateActions[] =
{
	// common
	{ 0x8bdd3e9a, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0xf598a34e, 0xf598a34e, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_MANUAL, "hkRootLevelContainer", Update_hkRootLevelContainer },
	{ 0x853a899c, 0x853a899c, hkVersionUtil::VERSION_VARIANT | hkVersionUtil::VERSION_MANUAL, "hkRootLevelContainerNamedVariant", Update_hkRootLevelContainerNamedVariant },
	{ 0xf2ec0c9c, 0xf2ec0c9c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x1667c01c, 0x1667c01c, hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL },
	{ 0x06af1b5a, 0x06af1b5a, hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL },
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },
	{ 0x72e8e849, 0x72e8e849, hkVersionUtil::VERSION_VARIANT, "hkxMesh", HK_NULL },
	{ 0x912c8863, 0x912c8863, hkVersionUtil::VERSION_VARIANT, "hkxMeshSection", HK_NULL },
	{ 0x64e9a03c, 0x64e9a03c, hkVersionUtil::VERSION_VARIANT, "hkxMeshUserChannelInfo", HK_NULL },
	{ 0x445a443a, 0x445a443a, hkVersionUtil::VERSION_VARIANT, "hkxAttributeHolder", HK_NULL },

	// hkbase
	{ 0x9617a10c, 0x528ce1e5, hkVersionUtil::VERSION_COPY, "hkClassEnum", HK_NULL }, // added support for custom attributes, HVK-3709
	{ 0xe0747dde, 0xe96acec5, hkVersionUtil::VERSION_COPY, "hkClassMember", Update_hkClassMember }, // added support for custom attributes, HVK-3709
	{ 0x731c1b21, 0x0b11a993, hkVersionUtil::VERSION_COPY, "hkClass", Update_hkClass }, // added support for custom attributes, HVK-3709

	REMOVED("hkWorldMemoryWatchDog"),

	// physics

	{ 0xae76398e, 0x500c3e30, hkVersionUtil::VERSION_COPY, "hkAabbPhantom", Update_hkAabbPhantom }, // TYPE_ZERO changes + changes in parent hkpWorldObject
	{ 0x32c862d8, 0x1fac7738, hkVersionUtil::VERSION_COPY, "hkShapePhantom",		Update_hkShapePhantom }, // changes in parent hkpWorldObject
	{ 0x39ee6bd6, 0xaa0ade1a, hkVersionUtil::VERSION_COPY, "hkPhantom", Update_hkAabbPhantom }, // TYPE_ZERO changes + changes in parent hkpWorldObject
	{ 0x06602a50, 0xfb086d6b, hkVersionUtil::VERSION_COPY, "hkWorldCinfo",			HK_NULL },	// old style deactivation flag removed
	{ 0x24ff1c3e, 0xfa798537, hkVersionUtil::VERSION_COPY, "hkEntity",				ConvertEntity },
	{ 0xd5491c20, 0x8b0a2dbf, hkVersionUtil::VERSION_COPY, "hkKeyframedRigidMotion",ConvertKeyframedRigidMotion },
	{ 0xb891f43f, 0x141abdc9, hkVersionUtil::VERSION_COPY, "hkMotion",				ConvertMotion },
	{ 0xc9c72e9e, 0x064e7ce4, hkVersionUtil::VERSION_COPY, "hkMotionState",			ConvertMotionState },
	{ 0xf1805598, 0x5879a2c3, hkVersionUtil::VERSION_COPY, "hkCollidable",			HK_NULL },
	{ 0x241c63f1, 0xd2c2de00, hkVersionUtil::VERSION_COPY, "hkMouseSpringAction",	Update_hkMouseSpringAction }, // added m_shapeKey and m_applyCallbacks, changes in parent hkpAction
	{ 0x95f58619, 0xb6966e59, hkVersionUtil::VERSION_COPY, "hkAction",				ConvertUserDataFromUint32ToUlong }, // HVK-3555 m_userData: hkUint32 -> hkUlong
	BINARY_IDENTICAL(0xfb1093dc, 0x11fd6f6c, "hkGenericConstraintDataScheme"), // TYPE_ZERO changes
	{ 0x4fef2f8b, 0x4a9bffad, hkVersionUtil::VERSION_COPY, "hkGenericConstraintData",ConvertUserDataFromUint32ToUlong }, // HVK-3555 m_userData: hkUint32 -> hkUlong
	{ 0xf28ab3b7, 0xf9515b8a, hkVersionUtil::VERSION_COPY, "hkConstraintData",		ConvertUserDataFromUint32ToUlong }, // HVK-3555 m_userData: hkUint32 -> hkUlong
	{ 0xf0612556, 0x2033b565, hkVersionUtil::VERSION_COPY, "hkConstraintInstance",	ConvertUserDataFromUint32ToUlong }, // HVK-3555 m_userData: hkUint32 -> hkUlong

	BINARY_IDENTICAL(0x3610a32e, 0x250ee68f, "hkCollisionFilter"), // added enums, HVK-3192
	{ 0xcbeca93e, 0x79de6a0b, hkVersionUtil::VERSION_COPY, "hkSerializedAgentNnEntry",	Update_hkSerializedAgentNnEntry }, // m_properties replaced with m_propertiesStream

	REMOVED("hkSerializedContactPointPropertiesBlock"),

	{ 0x2efdea58, 0xd96b1149, hkVersionUtil::VERSION_COPY, "hkMoppEmbeddedShape",	HK_NULL },
	{ 0xeb33369b, 0xdbba3c29, hkVersionUtil::VERSION_COPY, "hkMoppBvTreeShape",	HK_NULL },

	// hkanimation

	BINARY_IDENTICAL(0xd97d1004, 0x5b9ff2db, "hkSkeletalAnimation"), // added HK_MIRRORED_ANIMATION enum

	// hkscenedata
	{ 0x1c6f8636, 0x1fb22361, hkVersionUtil::VERSION_COPY, "hkxScene", HK_NULL },

	BINARY_IDENTICAL(0x88f9319c, 0xcdb31e0c, "hkMeshBinding"), // renamed transform member to correct name, HKA-703
	{ 0x8fd02839, 0xafcd79ad, hkVersionUtil::VERSION_MANUAL, "hkCallbackConstraintMotor", NoActionTaken }, // HVK-3555 m_userData0,1,2: void* -> hkUlong
	{ 0x3ace2c22, 0x1b58f0ef, hkVersionUtil::VERSION_MANUAL, "hkPhysicsSystem",	NoActionTaken }, // HVK-3555 m_userData: void* -> hkUlong, serialize m_userData
	{ 0x2ec055b9, 0xce5e4f30, hkVersionUtil::VERSION_MANUAL, "hkContactPointMaterial",	NoActionTaken }, // HVK-3555 m_userData: void* -> hkUlong, serialize m_userData
	{ 0x0582a274, 0x50f6ee9f, hkVersionUtil::VERSION_COPY, "hkWorldObject", Update_hkWorldObject }, // HVK-3555 m_userData: void* -> hkUlong, m_multithreadLock replaced with m_multiThreadCheck

	// hkconstraintsolver
	{ 0x3ab70056, 0x371b03fa, hkVersionUtil::VERSION_COPY, "hkSimpleContactConstraintAtom", HK_NULL }, // new members

	// hkbehavior


	{ 0xcde24544, 0x2cf42b86, hkVersionUtil::VERSION_COPY, "hkbAttachmentModifier", HK_NULL },
	{ 0x915b6c96, 0xda11d903, hkVersionUtil::VERSION_COPY, "hkbAttachmentModifierAttachmentProperties", HK_NULL },
	{ 0x1253cd4e, 0x4cce6ed9, hkVersionUtil::VERSION_COPY, "hkbAttachmentSetup", HK_NULL },
	{ 0x563dba83, 0x294881d1, hkVersionUtil::VERSION_COPY, "hkbBehavior", HK_NULL }, // added m_isActive
	{ 0x93ff2b59, 0xe9a1a032, hkVersionUtil::VERSION_COPY, "hkbBlenderGenerator", HK_NULL },
	BINARY_IDENTICAL( 0xc6656965, 0xbba34f99, "hkbBlenderGeneratorChild" ),
	{ 0x6f02f92a, 0xd52c6d90, hkVersionUtil::VERSION_COPY, "hkbBlendingTransitionEffect", Update_hkbBlendingTransitionEffect },
	{ 0x08f29bb1, 0x24816b59, hkVersionUtil::VERSION_COPY, "hkbClipGenerator", HK_NULL }, // added new members, HKF-59
	{ 0xd713d8cf, 0xbbd4f75d, hkVersionUtil::VERSION_COPY, "hkbGeneratorTransitionEffect", HK_NULL },
	{ 0x9589e4fc, 0x44d86267, hkVersionUtil::VERSION_COPY, "hkbGeneratorOutput", HK_NULL },
	{ 0x4f62762a, 0x978d2a63, hkVersionUtil::VERSION_COPY, "hkbGeneratorOutputGeneratorOutputTrack", HK_NULL },
	{ 0xb21f476c, 0xac0f445b, hkVersionUtil::VERSION_COPY, "hkbFootIkModifier", HK_NULL },
	{ 0x70fdd734, 0xc66a997a, hkVersionUtil::VERSION_COPY, "hkbFootIkModifierInternalLegData", HK_NULL },
	BINARY_IDENTICAL( 0x3526c7c9, 0x1e0bc068, "hkbRigidBodyRagdollControlData" ),
	BINARY_IDENTICAL( 0xd378741c, 0xd5756d8e, "hkbRigidBodyRagdollControlsModifier" ),
	{ 0x32aab156, 0x6ada7bd9, hkVersionUtil::VERSION_COPY, "hkbRigidBodyRagdollModifier", Update_hkbRigidBodyRagdollModifier },
	{ 0xb5cd4e89, 0xe9bbd108, hkVersionUtil::VERSION_COPY, "hkbStateMachine",Update_hkbStateMachine },
	{ 0x20cc25f6, 0xda4e5ab8, hkVersionUtil::VERSION_COPY, "hkbStateMachineActiveTransitionInfo", HK_NULL },
	{ 0xfea091e8, 0xe2b1c2f3, hkVersionUtil::VERSION_COPY, "hkbStateMachineStateInfo", Update_hkbStateMachineStateInfo },
	{ 0x35f9d035, 0xac31d210, hkVersionUtil::VERSION_COPY, "hkbStateMachineTransitionInfo", Update_hkbStateMachineTransitionInfo },
	{ 0xefef656e, 0xc9a38829, hkVersionUtil::VERSION_COPY, "hkbTransitionEffect", HK_NULL },

	// FX
	REMOVED("hkFxBaseBehavior"),
	REMOVED("hkFxClothBodySubsystemCollection"),
	REMOVED("hkFxClothBodySystemHingeLink"),
	REMOVED("hkFxClothBodySystemLink"),
	REMOVED("hkFxHeightMapShapeRep"),
	REMOVED("hkFxHeightMapShapeRepHeightMapData"),
	REMOVED("hkFxMoppShapeRep"),
	REMOVED("hkFxMoppShapeRepTriangle"),
	REMOVED("hkFxParticleBodySubSystemCollection"),
	REMOVED("hkFxParticleBodySystemCinfo"),
	REMOVED("hkFxParticle"),
	REMOVED("hkFxPhysicsCollection"),
	REMOVED("hkFxPhysicsCollisionInfo"),
	REMOVED("hkFxRigidBody"),
	REMOVED("hkFxRigidBodyIntegrationInfo"),
	REMOVED("hkFxRigidBodySubSystemCollection"),
	REMOVED("hkFxRigidBodySystemCinfo"),
	REMOVED("hkFxShapeBodyData"),
	REMOVED("hkFxShape"),
	REMOVED("hkFxShapeRep"),

	{ 0, 0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	{ "hkbGeneratorOutputGeneratorOutputTrack", "hkbGeneratorOutputTrack" },
	{ "hkbBoolVariableSequencedDataBoolVariableSample", "hkbBoolVariableSequencedDataSample" },
	{ "hkbIntVariableSequencedDataIntVariableSample", "hkbIntVariableSequencedDataSample" },
	{ "hkbRealVariableSequencedDataRealVariableSample", "hkbRealVariableSequencedDataSample" },

	{ "hkAnimatedReferenceFrame", "hkaAnimatedReferenceFrame" },
	{ "hkSkeletalAnimation", "hkaSkeletalAnimation" },
	{ "hkDefaultAnimatedReferenceFrame", "hkaDefaultAnimatedReferenceFrame" },
	{ "hkDeltaCompressedSkeletalAnimation", "hkaDeltaCompressedSkeletalAnimation" },
	{ "hkInterleavedSkeletalAnimation", "hkaInterleavedSkeletalAnimation" },
	{ "hkSkeletonMapper", "hkaSkeletonMapper" },
	{ "hkWaveletSkeletalAnimation", "hkaWaveletSkeletalAnimation" },
	{ "hkAnimationBinding", "hkaAnimationBinding" },
	{ "hkAnimationContainer", "hkaAnimationContainer" },
	{ "hkAnnotationTrack", "hkaAnnotationTrack" },
	{ "hkAnnotationTrackAnnotation", "hkaAnnotationTrackAnnotation" },
	{ "hkBone", "hkaBone" },
	{ "hkBoneAttachment", "hkaBoneAttachment" },
	{ "hkDeltaCompressedSkeletalAnimationQuantizationFormat", "hkaDeltaCompressedSkeletalAnimationQuantizationFormat" },
	{ "hkMeshBinding", "hkaMeshBinding" },
	{ "hkMeshBindingMapping", "hkaMeshBindingMapping" },
	{ "hkSkeleton", "hkaSkeleton" },
	{ "hkSkeletonMapperData", "hkaSkeletonMapperData" },
	{ "hkSkeletonMapperDataChainMapping", "hkaSkeletonMapperDataChainMapping" },
	{ "hkSkeletonMapperDataSimpleMapping", "hkaSkeletonMapperDataSimpleMapping" },
	{ "hkWaveletSkeletalAnimationCompressionParams", "hkaWaveletSkeletalAnimationCompressionParams" },
	{ "hkWaveletSkeletalAnimationQuantizationFormat", "hkaWaveletSkeletalAnimationQuantizationFormat" },
	{ "hkRagdollInstance", "hkaRagdollInstance" },
	{ "hkKeyFrameHierarchyUtility", "hkaKeyFrameHierarchyUtility" },
	{ "hkKeyFrameHierarchyUtilityControlData", "hkaKeyFrameHierarchyUtilityControlData" },
	{ "hkBvTreeShape", "hkpBvTreeShape" },
	{ "hkCollidableCollidableFilter", "hkpCollidableCollidableFilter" },
	{ "hkCollisionFilter", "hkpCollisionFilter" },
	{ "hkConvexListFilter", "hkpConvexListFilter" },
	{ "hkConvexShape", "hkpConvexShape" },
	{ "hkHeightFieldShape", "hkpHeightFieldShape" },
	{ "hkPhantomCallbackShape", "hkpPhantomCallbackShape" },
	{ "hkRayCollidableFilter", "hkpRayCollidableFilter" },
	{ "hkRayShapeCollectionFilter", "hkpRayShapeCollectionFilter" },
	{ "hkSampledHeightFieldShape", "hkpSampledHeightFieldShape" },
	{ "hkShape", "hkpShape" },
	{ "hkShapeCollection", "hkpShapeCollection" },
	{ "hkShapeCollectionFilter", "hkpShapeCollectionFilter" },
	{ "hkShapeContainer", "hkpShapeContainer" },
	{ "hkSphereRepShape", "hkpSphereRepShape" },
	{ "hkBoxShape", "hkpBoxShape" },
	{ "hkBvShape", "hkpBvShape" },
	{ "hkCapsuleShape", "hkpCapsuleShape" },
	{ "hkCollisionFilterList", "hkpCollisionFilterList" },
	{ "hkConvexListShape", "hkpConvexListShape" },
	{ "hkConvexPieceMeshShape", "hkpConvexPieceMeshShape" },
	{ "hkConvexTransformShape", "hkpConvexTransformShape" },
	{ "hkConvexTranslateShape", "hkpConvexTranslateShape" },
	{ "hkConvexVerticesShape", "hkpConvexVerticesShape" },
	{ "hkCylinderShape", "hkpCylinderShape" },
	{ "hkDefaultConvexListFilter", "hkpDefaultConvexListFilter" },
	{ "hkExtendedMeshShape", "hkpExtendedMeshShape" },
	{ "hkFastMeshShape", "hkpFastMeshShape" },
	{ "hkGroupFilter", "hkpGroupFilter" },
	{ "hkListShape", "hkpListShape" },
	{ "hkMeshShape", "hkpMeshShape" },
	{ "hkMoppBvTreeShape", "hkpMoppBvTreeShape" },
	{ "hkMoppEmbeddedShape", "hkpMoppEmbeddedShape" },
	{ "hkMultiRayShape", "hkpMultiRayShape" },
	{ "hkMultiSphereShape", "hkpMultiSphereShape" },
	{ "hkNullCollisionFilter", "hkpNullCollisionFilter" },
	{ "hkPackedConvexVerticesShape", "hkpPackedConvexVerticesShape" },
	{ "hkPlaneShape", "hkpPlaneShape" },
	{ "hkRemoveTerminalsMoppModifier", "hkpRemoveTerminalsMoppModifier" },
	{ "hkSimpleMeshShape", "hkpSimpleMeshShape" },
	{ "hkSingleShapeContainer", "hkpSingleShapeContainer" },
	{ "hkSphereShape", "hkpSphereShape" },
	{ "hkStorageExtendedMeshShape", "hkpStorageExtendedMeshShape" },
	{ "hkStorageExtendedMeshShapeMeshSubpartStorage", "hkpStorageExtendedMeshShapeMeshSubpartStorage" },
	{ "hkStorageExtendedMeshShapeShapeSubpartStorage", "hkpStorageExtendedMeshShapeShapeSubpartStorage" },
	{ "hkStorageMeshShape", "hkpStorageMeshShape" },
	{ "hkStorageMeshShapeSubpartStorage", "hkpStorageMeshShapeSubpartStorage" },
	{ "hkStorageSampledHeightFieldShape", "hkpStorageSampledHeightFieldShape" },
	{ "hkTransformShape", "hkpTransformShape" },
	{ "hkTriSampledHeightFieldBvTreeShape", "hkpTriSampledHeightFieldBvTreeShape" },
	{ "hkTriSampledHeightFieldCollection", "hkpTriSampledHeightFieldCollection" },
	{ "hkTriangleShape", "hkpTriangleShape" },
	{ "hkCdBody", "hkpCdBody" },
	{ "hkCollidable", "hkpCollidable" },
	{ "hkCollidableBoundingVolumeData", "hkpCollidableBoundingVolumeData" },
	{ "hkConvexVerticesShapeFourVectors", "hkpConvexVerticesShapeFourVectors" },
	{ "hkExtendedMeshShapeShapesSubpart", "hkpExtendedMeshShapeShapesSubpart" },
	{ "hkExtendedMeshShapeSubpart", "hkpExtendedMeshShapeSubpart" },
	{ "hkExtendedMeshShapeTrianglesSubpart", "hkpExtendedMeshShapeTrianglesSubpart" },
	{ "hkListShapeChildInfo", "hkpListShapeChildInfo" },
	{ "hkMeshMaterial", "hkpMeshMaterial" },
	{ "hkMeshShapeSubpart", "hkpMeshShapeSubpart" },
	{ "hkMultiRayShapeRay", "hkpMultiRayShapeRay" },
	{ "hkPackedConvexVerticesShapeFourVectors", "hkpPackedConvexVerticesShapeFourVectors" },
	{ "hkPackedConvexVerticesShapeVector4IntW", "hkpPackedConvexVerticesShapeVector4IntW" },
	{ "hkShapeRayCastInput", "hkpShapeRayCastInput" },
	{ "hkSimpleMeshShapeTriangle", "hkpSimpleMeshShapeTriangle" },
	{ "hkTypedBroadPhaseHandle", "hkpTypedBroadPhaseHandle" },
	{ "hkWeldingUtility", "hkpWeldingUtility" },
	{ "hk2dAngConstraintAtom", "hkp2dAngConstraintAtom" },
	{ "hkAngConstraintAtom", "hkpAngConstraintAtom" },
	{ "hkAngFrictionConstraintAtom", "hkpAngFrictionConstraintAtom" },
	{ "hkAngLimitConstraintAtom", "hkpAngLimitConstraintAtom" },
	{ "hkAngMotorConstraintAtom", "hkpAngMotorConstraintAtom" },
	{ "hkBallSocketConstraintAtom", "hkpBallSocketConstraintAtom" },
	{ "hkBridgeAtoms", "hkpBridgeAtoms" },
	{ "hkBridgeConstraintAtom", "hkpBridgeConstraintAtom" },
	{ "hkConeLimitConstraintAtom", "hkpConeLimitConstraintAtom" },
	{ "hkConstraintAtom", "hkpConstraintAtom" },
	{ "hkLinConstraintAtom", "hkpLinConstraintAtom" },
	{ "hkLinFrictionConstraintAtom", "hkpLinFrictionConstraintAtom" },
	{ "hkLinLimitConstraintAtom", "hkpLinLimitConstraintAtom" },
	{ "hkLinMotorConstraintAtom", "hkpLinMotorConstraintAtom" },
	{ "hkLinSoftConstraintAtom", "hkpLinSoftConstraintAtom" },
	{ "hkMassChangerModifierConstraintAtom", "hkpMassChangerModifierConstraintAtom" },
	{ "hkModifierConstraintAtom", "hkpModifierConstraintAtom" },
	{ "hkMovingSurfaceModifierConstraintAtom", "hkpMovingSurfaceModifierConstraintAtom" },
	{ "hkOverwritePivotConstraintAtom", "hkpOverwritePivotConstraintAtom" },
	{ "hkPulleyConstraintAtom", "hkpPulleyConstraintAtom" },
	{ "hkRagdollMotorConstraintAtom", "hkpRagdollMotorConstraintAtom" },
	{ "hkSetLocalRotationsConstraintAtom", "hkpSetLocalRotationsConstraintAtom" },
	{ "hkSetLocalTransformsConstraintAtom", "hkpSetLocalTransformsConstraintAtom" },
	{ "hkSetLocalTranslationsConstraintAtom", "hkpSetLocalTranslationsConstraintAtom" },
	{ "hkSimpleContactConstraintAtom", "hkpSimpleContactConstraintAtom" },
	{ "hkSimpleContactConstraintDataInfo", "hkpSimpleContactConstraintDataInfo" },
	{ "hkSoftContactModifierConstraintAtom", "hkpSoftContactModifierConstraintAtom" },
	{ "hkStiffSpringConstraintAtom", "hkpStiffSpringConstraintAtom" },
	{ "hkTwistLimitConstraintAtom", "hkpTwistLimitConstraintAtom" },
	{ "hkViscousSurfaceModifierConstraintAtom", "hkpViscousSurfaceModifierConstraintAtom" },
	{ "hk2dAngConstraintAtom", "hkp2dAngConstraintAtom" },
	{ "hkAngConstraintAtom", "hkpAngConstraintAtom" },
	{ "hkAngFrictionConstraintAtom", "hkpAngFrictionConstraintAtom" },
	{ "hkAngLimitConstraintAtom", "hkpAngLimitConstraintAtom" },
	{ "hkAngMotorConstraintAtom", "hkpAngMotorConstraintAtom" },
	{ "hkBallSocketConstraintAtom", "hkpBallSocketConstraintAtom" },
	{ "hkBridgeAtoms", "hkpBridgeAtoms" },
	{ "hkBridgeConstraintAtom", "hkpBridgeConstraintAtom" },
	{ "hkConeLimitConstraintAtom", "hkpConeLimitConstraintAtom" },
	{ "hkConstraintAtom", "hkpConstraintAtom" },
	{ "hkLinConstraintAtom", "hkpLinConstraintAtom" },
	{ "hkLinFrictionConstraintAtom", "hkpLinFrictionConstraintAtom" },
	{ "hkLinLimitConstraintAtom", "hkpLinLimitConstraintAtom" },
	{ "hkLinMotorConstraintAtom", "hkpLinMotorConstraintAtom" },
	{ "hkLinSoftConstraintAtom", "hkpLinSoftConstraintAtom" },
	{ "hkMassChangerModifierConstraintAtom", "hkpMassChangerModifierConstraintAtom" },
	{ "hkModifierConstraintAtom", "hkpModifierConstraintAtom" },
	{ "hkMovingSurfaceModifierConstraintAtom", "hkpMovingSurfaceModifierConstraintAtom" },
	{ "hkOverwritePivotConstraintAtom", "hkpOverwritePivotConstraintAtom" },
	{ "hkPulleyConstraintAtom", "hkpPulleyConstraintAtom" },
	{ "hkRagdollMotorConstraintAtom", "hkpRagdollMotorConstraintAtom" },
	{ "hkSetLocalRotationsConstraintAtom", "hkpSetLocalRotationsConstraintAtom" },
	{ "hkSetLocalTransformsConstraintAtom", "hkpSetLocalTransformsConstraintAtom" },
	{ "hkSetLocalTranslationsConstraintAtom", "hkpSetLocalTranslationsConstraintAtom" },
	{ "hkSoftContactModifierConstraintAtom", "hkpSoftContactModifierConstraintAtom" },
	{ "hkStiffSpringConstraintAtom", "hkpStiffSpringConstraintAtom" },
	{ "hkTwistLimitConstraintAtom", "hkpTwistLimitConstraintAtom" },
	{ "hkViscousSurfaceModifierConstraintAtom", "hkpViscousSurfaceModifierConstraintAtom" },
	{ "hkAction", "hkpAction" },
	{ "hkArrayAction", "hkpArrayAction" },
	{ "hkBinaryAction", "hkpBinaryAction" },
	{ "hkConstraintChainData", "hkpConstraintChainData" },
	{ "hkConstraintData", "hkpConstraintData" },
	{ "hkConstraintMotor", "hkpConstraintMotor" },
	{ "hkEntityDeactivator", "hkpEntityDeactivator" },
	{ "hkLimitedForceConstraintMotor", "hkpLimitedForceConstraintMotor" },
	{ "hkMotion", "hkpMotion" },
	{ "hkParametricCurve", "hkpParametricCurve" },
	{ "hkPhantom", "hkpPhantom" },
	{ "hkRigidBodyDeactivator", "hkpRigidBodyDeactivator" },
	{ "hkShapePhantom", "hkpShapePhantom" },
	{ "hkUnaryAction", "hkpUnaryAction" },
	{ "hkWorldObject", "hkpWorldObject" },
	{ "hkAabbPhantom", "hkpAabbPhantom" },
	{ "hkBallAndSocketConstraintData", "hkpBallAndSocketConstraintData" },
	{ "hkBallSocketChainData", "hkpBallSocketChainData" },
	{ "hkBoxMotion", "hkpBoxMotion" },
	{ "hkBreakableConstraintData", "hkpBreakableConstraintData" },
	{ "hkCachingShapePhantom", "hkpCachingShapePhantom" },
	{ "hkCallbackConstraintMotor", "hkpCallbackConstraintMotor" },
	{ "hkCharacterMotion", "hkpCharacterMotion" },
	{ "hkConstraintChainInstance", "hkpConstraintChainInstance" },
	{ "hkConstraintChainInstanceAction", "hkpConstraintChainInstanceAction" },
	{ "hkConstraintInstance", "hkpConstraintInstance" },
	{ "hkEntity", "hkpEntity" },
	{ "hkFakeRigidBodyDeactivator", "hkpFakeRigidBodyDeactivator" },
	{ "hkFixedRigidMotion", "hkpFixedRigidMotion" },
	{ "hkGenericConstraintData", "hkpGenericConstraintData" },
	{ "hkHingeConstraintData", "hkpHingeConstraintData" },
	{ "hkHingeLimitsData", "hkpHingeLimitsData" },
	{ "hkKeyframedRigidMotion", "hkpKeyframedRigidMotion" },
	{ "hkLimitedHingeConstraintData", "hkpLimitedHingeConstraintData" },
	{ "hkLinearParametricCurve", "hkpLinearParametricCurve" },
	{ "hkMalleableConstraintData", "hkpMalleableConstraintData" },
	{ "hkMaxSizeMotion", "hkpMaxSizeMotion" },
	{ "hkPhysicsSystem", "hkpPhysicsSystem" },
	{ "hkPointToPathConstraintData", "hkpPointToPathConstraintData" },
	{ "hkPointToPlaneConstraintData", "hkpPointToPlaneConstraintData" },
	{ "hkPositionConstraintMotor", "hkpPositionConstraintMotor" },
	{ "hkPoweredChainData", "hkpPoweredChainData" },
	{ "hkPrismaticConstraintData", "hkpPrismaticConstraintData" },
	{ "hkPulleyConstraintData", "hkpPulleyConstraintData" },
	{ "hkRagdollConstraintData", "hkpRagdollConstraintData" },
	{ "hkRagdollLimitsData", "hkpRagdollLimitsData" },
	{ "hkRigidBody", "hkpRigidBody" },
	{ "hkRotationalConstraintData", "hkpRotationalConstraintData" },
	{ "hkSimpleShapePhantom", "hkpSimpleShapePhantom" },
	{ "hkSimulation", "hkpSimulation" },
	{ "hkSpatialRigidBodyDeactivator", "hkpSpatialRigidBodyDeactivator" },
	{ "hkSphereMotion", "hkpSphereMotion" },
	{ "hkSpringDamperConstraintMotor", "hkpSpringDamperConstraintMotor" },
	{ "hkStabilizedBoxMotion", "hkpStabilizedBoxMotion" },
	{ "hkStabilizedSphereMotion", "hkpStabilizedSphereMotion" },
	{ "hkStiffSpringChainData", "hkpStiffSpringChainData" },
	{ "hkStiffSpringConstraintData", "hkpStiffSpringConstraintData" },
	{ "hkThinBoxMotion", "hkpThinBoxMotion" },
	{ "hkVelocityConstraintMotor", "hkpVelocityConstraintMotor" },
	{ "hkWheelConstraintData", "hkpWheelConstraintData" },
	{ "hkWorld", "hkpWorld" },
	{ "hkWorldCinfo", "hkpWorldCinfo" },
	{ "hkBallAndSocketConstraintDataAtoms", "hkpBallAndSocketConstraintDataAtoms" },
	{ "hkBallSocketChainDataConstraintInfo", "hkpBallSocketChainDataConstraintInfo" },
	{ "hkEntityExtendedListeners", "hkpEntityExtendedListeners" },
	{ "hkEntitySmallArraySerializeOverrideType", "hkpEntitySmallArraySerializeOverrideType" },
	{ "hkEntitySpuCollisionCallback", "hkpEntitySpuCollisionCallback" },
	{ "hkGenericConstraintDataScheme", "hkpGenericConstraintDataScheme" },
	{ "hkGenericConstraintDataSchemeConstraintInfo", "hkpGenericConstraintDataSchemeConstraintInfo" },
	{ "hkHingeConstraintDataAtoms", "hkpHingeConstraintDataAtoms" },
	{ "hkHingeLimitsDataAtoms", "hkpHingeLimitsDataAtoms" },
	{ "hkLimitedHingeConstraintDataAtoms", "hkpLimitedHingeConstraintDataAtoms" },
	{ "hkMaterial", "hkpMaterial" },
	{ "hkPointToPlaneConstraintDataAtoms", "hkpPointToPlaneConstraintDataAtoms" },
	{ "hkPoweredChainDataConstraintInfo", "hkpPoweredChainDataConstraintInfo" },
	{ "hkPrismaticConstraintDataAtoms", "hkpPrismaticConstraintDataAtoms" },
	{ "hkProperty", "hkpProperty" },
	{ "hkPropertyValue", "hkpPropertyValue" },
	{ "hkPulleyConstraintDataAtoms", "hkpPulleyConstraintDataAtoms" },
	{ "hkRagdollConstraintDataAtoms", "hkpRagdollConstraintDataAtoms" },
	{ "hkRagdollLimitsDataAtoms", "hkpRagdollLimitsDataAtoms" },
	{ "hkRotationalConstraintDataAtoms", "hkpRotationalConstraintDataAtoms" },
	{ "hkSimpleShapePhantomCollisionDetail", "hkpSimpleShapePhantomCollisionDetail" },
	{ "hkSpatialRigidBodyDeactivatorSample", "hkpSpatialRigidBodyDeactivatorSample" },
	{ "hkStiffSpringChainDataConstraintInfo", "hkpStiffSpringChainDataConstraintInfo" },
	{ "hkStiffSpringConstraintDataAtoms", "hkpStiffSpringConstraintDataAtoms" },
	{ "hkWheelConstraintDataAtoms", "hkpWheelConstraintDataAtoms" },
	{ "hkConvexPieceStreamData", "hkpConvexPieceStreamData" },
	{ "hkMoppCode", "hkpMoppCode" },
	{ "hkAgent1nSector", "hkpAgent1nSector" },
	{ "hkBroadPhaseHandle", "hkpBroadPhaseHandle" },
	{ "hkLinkedCollidable", "hkpLinkedCollidable" },
	{ "hkMoppCodeCodeInfo", "hkpMoppCodeCodeInfo" },
	{ "hkMoppCodeReindexedTerminal", "hkpMoppCodeReindexedTerminal" },
	{ "hkAngularDashpotAction", "hkpAngularDashpotAction" },
	{ "hkConstrainedSystemFilter", "hkpConstrainedSystemFilter" },
	{ "hkDashpotAction", "hkpDashpotAction" },
	{ "hkDisableEntityCollisionFilter", "hkpDisableEntityCollisionFilter" },
	{ "hkGroupCollisionFilter", "hkpGroupCollisionFilter" },
	{ "hkMotorAction", "hkpMotorAction" },
	{ "hkMouseSpringAction", "hkpMouseSpringAction" },
	{ "hkPairwiseCollisionFilter", "hkpPairwiseCollisionFilter" },
	{ "hkPhysicsData", "hkpPhysicsData" },
	{ "hkPhysicsSystemWithContacts", "hkpPhysicsSystemWithContacts" },
	{ "hkPoweredChainMapper", "hkpPoweredChainMapper" },
	{ "hkReorientAction", "hkpReorientAction" },
	{ "hkSerializedAgentNnEntry", "hkpSerializedAgentNnEntry" },
	{ "hkSerializedDisplayMarker", "hkpSerializedDisplayMarker" },
	{ "hkSerializedDisplayMarkerList", "hkpSerializedDisplayMarkerList" },
	{ "hkSerializedDisplayRbTransforms", "hkpSerializedDisplayRbTransforms" },
	{ "hkSpringAction", "hkpSpringAction" },
	{ "hkCharacterProxyCinfo", "hkpCharacterProxyCinfo" },
	{ "hkDisplayBindingData", "hkpDisplayBindingData" },
	{ "hkPairwiseCollisionFilterCollisionPair", "hkpPairwiseCollisionFilterCollisionPair" },
	{ "hkPhysicsSystemDisplayBinding", "hkpPhysicsSystemDisplayBinding" },
	{ "hkPoweredChainMapperLinkInfo", "hkpPoweredChainMapperLinkInfo" },
	{ "hkPoweredChainMapperTarget", "hkpPoweredChainMapperTarget" },
	{ "hkRigidBodyDisplayBinding", "hkpRigidBodyDisplayBinding" },
	{ "hkSerializedDisplayRbTransformsDisplayTransformPair", "hkpSerializedDisplayRbTransformsDisplayTransformPair" },
	{ "hkSerializedSubTrack1nInfo", "hkpSerializedSubTrack1nInfo" },
	{ "hkSerializedTrack1nInfo", "hkpSerializedTrack1nInfo" },
	{ "hkVehicleAerodynamics", "hkpVehicleAerodynamics" },
	{ "hkVehicleBrake", "hkpVehicleBrake" },
	{ "hkVehicleDriverInput", "hkpVehicleDriverInput" },
	{ "hkVehicleDriverInputStatus", "hkpVehicleDriverInputStatus" },
	{ "hkVehicleEngine", "hkpVehicleEngine" },
	{ "hkVehicleSteering", "hkpVehicleSteering" },
	{ "hkVehicleSuspension", "hkpVehicleSuspension" },
	{ "hkVehicleTransmission", "hkpVehicleTransmission" },
	{ "hkVehicleVelocityDamper", "hkpVehicleVelocityDamper" },
	{ "hkVehicleWheelCollide", "hkpVehicleWheelCollide" },
	{ "hkRejectRayChassisListener", "hkpRejectRayChassisListener" },
	{ "hkTyremarksInfo", "hkpTyremarksInfo" },
	{ "hkTyremarksWheel", "hkpTyremarksWheel" },
	{ "hkVehicleData", "hkpVehicleData" },
	{ "hkVehicleDefaultAerodynamics", "hkpVehicleDefaultAerodynamics" },
	{ "hkVehicleDefaultAnalogDriverInput", "hkpVehicleDefaultAnalogDriverInput" },
	{ "hkVehicleDefaultBrake", "hkpVehicleDefaultBrake" },
	{ "hkVehicleDefaultEngine", "hkpVehicleDefaultEngine" },
	{ "hkVehicleDefaultSteering", "hkpVehicleDefaultSteering" },
	{ "hkVehicleDefaultSuspension", "hkpVehicleDefaultSuspension" },
	{ "hkVehicleDefaultTransmission", "hkpVehicleDefaultTransmission" },
	{ "hkVehicleDefaultVelocityDamper", "hkpVehicleDefaultVelocityDamper" },
	{ "hkVehicleDriverInputAnalogStatus", "hkpVehicleDriverInputAnalogStatus" },
	{ "hkVehicleInstance", "hkpVehicleInstance" },
	{ "hkVehicleRaycastWheelCollide", "hkpVehicleRaycastWheelCollide" },
	{ "hkTyremarkPoint", "hkpTyremarkPoint" },
	{ "hkVehicleDataWheelComponentParams", "hkpVehicleDataWheelComponentParams" },
	{ "hkVehicleDefaultBrakeWheelBrakingProperties", "hkpVehicleDefaultBrakeWheelBrakingProperties" },
	{ "hkVehicleDefaultSuspensionWheelSpringSuspensionParameters", "hkpVehicleDefaultSuspensionWheelSpringSuspensionParameters" },
	{ "hkVehicleFrictionDescription", "hkpVehicleFrictionDescription" },
	{ "hkVehicleFrictionDescriptionAxisDescription", "hkpVehicleFrictionDescriptionAxisDescription" },
	{ "hkVehicleFrictionStatus", "hkpVehicleFrictionStatus" },
	{ "hkVehicleFrictionStatusAxisStatus", "hkpVehicleFrictionStatusAxisStatus" },
	{ "hkVehicleInstanceWheelInfo", "hkpVehicleInstanceWheelInfo" },
	{ "hkVehicleSuspensionSuspensionWheelParameters", "hkpVehicleSuspensionSuspensionWheelParameters" },

	{ HK_NULL, HK_NULL }
};

const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&hkHavok500b1ClassList
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
	hkHavok461r1Classes::VersionString,
	hkHavok500b1Classes::VersionString,
	update
};

} // namespace hkCompat_hk461r1_hk500b1

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
