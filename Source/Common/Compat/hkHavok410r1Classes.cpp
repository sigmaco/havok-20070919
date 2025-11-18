/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Compat/hkCompat.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>

#include <Common/Compat/hkHavokAllClasses.h>

namespace hkHavok410r1Classes
{
	const char VersionString[] = "Havok-4.1.0-r1";

	extern hkClass hk2dAngConstraintAtomClass;
	extern hkClass hkAabbClass;
	extern hkClass hkAabbPhantomClass;
	extern hkClass hkActionClass;
	extern hkClass hkAngConstraintAtomClass;
	extern hkClass hkAngFrictionConstraintAtomClass;
	extern hkClass hkAngLimitConstraintAtomClass;
	extern hkClass hkAngMotorConstraintAtomClass;
	extern hkClass hkAngularDashpotActionClass;
	extern hkClass hkAnimatedReferenceFrameClass;
	extern hkClass hkAnimationBindingClass;
	extern hkClass hkAnimationContainerClass;
	extern hkClass hkAnnotationTrackAnnotationClass;
	extern hkClass hkAnnotationTrackClass;
	extern hkClass hkArrayActionClass;
	extern hkClass hkBallAndSocketConstraintDataAtomsClass;
	extern hkClass hkBallAndSocketConstraintDataClass;
	extern hkClass hkBallSocketChainDataClass;
	extern hkClass hkBallSocketChainDataConstraintInfoClass;
	extern hkClass hkBallSocketConstraintAtomClass;
	extern hkClass hkBaseObjectClass;
	extern hkClass hkBinaryActionClass;
	extern hkClass hkBitFieldClass;
	extern hkClass hkBoneAttachmentClass;
	extern hkClass hkBoneClass;
	extern hkClass hkBoxMotionClass;
	extern hkClass hkBoxShapeClass;
	extern hkClass hkBreakableConstraintDataClass;
	extern hkClass hkBridgeAtomsClass;
	extern hkClass hkBridgeConstraintAtomClass;
	extern hkClass hkBroadPhaseHandleClass;
	extern hkClass hkBvShapeClass;
	extern hkClass hkBvTreeShapeClass;
	extern hkClass hkCachingShapePhantomClass;
	extern hkClass hkCapsuleShapeClass;
	extern hkClass hkCdBodyClass;
	extern hkClass hkCharacterProxyCinfoClass;
	extern hkClass hkClassClass;
	extern hkClass hkClassEnumClass;
	extern hkClass hkClassEnumItemClass;
	extern hkClass hkClassMemberClass;
	extern hkClass hkCollidableClass;
	extern hkClass hkCollidableCollidableFilterClass;
	extern hkClass hkCollisionFilterClass;
	extern hkClass hkCollisionFilterListClass;
	extern hkClass hkConeLimitConstraintAtomClass;
	extern hkClass hkConstrainedSystemFilterClass;
	extern hkClass hkConstraintAtomClass;
	extern hkClass hkConstraintChainDataClass;
	extern hkClass hkConstraintChainInstanceActionClass;
	extern hkClass hkConstraintChainInstanceClass;
	extern hkClass hkConstraintDataClass;
	extern hkClass hkConstraintInfoClass;
	extern hkClass hkConstraintInstanceClass;
	extern hkClass hkConstraintMotorClass;
	extern hkClass hkContactPointClass;
	extern hkClass hkContactPointMaterialClass;
	extern hkClass hkConvexListFilterClass;
	extern hkClass hkConvexListShapeClass;
	extern hkClass hkConvexPieceMeshShapeClass;
	extern hkClass hkConvexPieceStreamDataClass;
	extern hkClass hkConvexShapeClass;
	extern hkClass hkConvexTransformShapeClass;
	extern hkClass hkConvexTranslateShapeClass;
	extern hkClass hkConvexVerticesShapeClass;
	extern hkClass hkConvexVerticesShapeFourVectorsClass;
	extern hkClass hkCylinderShapeClass;
	extern hkClass hkDashpotActionClass;
	extern hkClass hkDefaultAnimatedReferenceFrameClass;
	extern hkClass hkDefaultConvexListFilterClass;
	extern hkClass hkDeltaCompressedSkeletalAnimationClass;
	extern hkClass hkDeltaCompressedSkeletalAnimationQuantizationFormatClass;
	extern hkClass hkDisableEntityCollisionFilterClass;
	extern hkClass hkDisplayBindingDataClass;
	extern hkClass hkEntityClass;
	extern hkClass hkEntityDeactivatorClass;
	extern hkClass hkExtendedMeshShapeClass;
	extern hkClass hkExtendedMeshShapeShapesSubpartClass;
	extern hkClass hkExtendedMeshShapeSubpartClass;
	extern hkClass hkExtendedMeshShapeTrianglesSubpartClass;
	extern hkClass hkFakeRigidBodyDeactivatorClass;
	extern hkClass hkFastMeshShapeClass;
	extern hkClass hkFixedRigidMotionClass;
	extern hkClass hkGenericConstraintDataClass;
	extern hkClass hkGenericConstraintDataSchemeClass;
	extern hkClass hkGroupCollisionFilterClass;
	extern hkClass hkGroupFilterClass;
	extern hkClass hkHeightFieldShapeClass;
	extern hkClass hkHingeConstraintDataAtomsClass;
	extern hkClass hkHingeConstraintDataClass;
	extern hkClass hkHingeLimitsDataAtomsClass;
	extern hkClass hkHingeLimitsDataClass;
	extern hkClass hkInterleavedSkeletalAnimationClass;
	extern hkClass hkKeyframedRigidMotionClass;
	extern hkClass hkLimitedForceConstraintMotorClass;
	extern hkClass hkLimitedHingeConstraintDataAtomsClass;
	extern hkClass hkLimitedHingeConstraintDataClass;
	extern hkClass hkLinConstraintAtomClass;
	extern hkClass hkLinFrictionConstraintAtomClass;
	extern hkClass hkLinLimitConstraintAtomClass;
	extern hkClass hkLinMotorConstraintAtomClass;
	extern hkClass hkLinSoftConstraintAtomClass;
	extern hkClass hkLinearParametricCurveClass;
	extern hkClass hkLinkedCollidableClass;
	extern hkClass hkListShapeChildInfoClass;
	extern hkClass hkListShapeClass;
	extern hkClass hkMalleableConstraintDataClass;
	extern hkClass hkMassChangerModifierConstraintAtomClass;
	extern hkClass hkMaterialClass;
	extern hkClass hkMaxSizeMotionClass;
	extern hkClass hkMeshBindingClass;
	extern hkClass hkMeshBindingMappingClass;
	extern hkClass hkMeshMaterialClass;
	extern hkClass hkMeshShapeClass;
	extern hkClass hkMeshShapeSubpartClass;
	extern hkClass hkModifierConstraintAtomClass;
	extern hkClass hkMonitorStreamFrameInfoClass;
	extern hkClass hkMonitorStreamStringMapClass;
	extern hkClass hkMonitorStreamStringMapStringMapClass;
	extern hkClass hkMoppBvTreeShapeClass;
	extern hkClass hkMoppCodeClass;
	extern hkClass hkMoppCodeCodeInfoClass;
	extern hkClass hkMotionClass;
	extern hkClass hkMotionStateClass;
	extern hkClass hkMotorActionClass;
	extern hkClass hkMouseSpringActionClass;
	extern hkClass hkMovingSurfaceModifierConstraintAtomClass;
	extern hkClass hkMultiRayShapeClass;
	extern hkClass hkMultiRayShapeRayClass;
	extern hkClass hkMultiSphereShapeClass;
	extern hkClass hkMultiThreadLockClass;
	extern hkClass hkNullCollisionFilterClass;
	extern hkClass hkOverwritePivotConstraintAtomClass;
	extern hkClass hkPackfileHeaderClass;
	extern hkClass hkPackfileSectionHeaderClass;
	extern hkClass hkPairwiseCollisionFilterClass;
	extern hkClass hkPairwiseCollisionFilterCollisionPairClass;
	extern hkClass hkParametricCurveClass;
	extern hkClass hkPhantomCallbackShapeClass;
	extern hkClass hkPhantomClass;
	extern hkClass hkPhysicsDataClass;
	extern hkClass hkPhysicsSystemClass;
	extern hkClass hkPhysicsSystemDisplayBindingClass;
	extern hkClass hkPlaneShapeClass;
	extern hkClass hkPointToPathConstraintDataClass;
	extern hkClass hkPointToPlaneConstraintDataAtomsClass;
	extern hkClass hkPointToPlaneConstraintDataClass;
	extern hkClass hkPositionConstraintMotorClass;
	extern hkClass hkPoweredChainDataClass;
	extern hkClass hkPoweredChainDataConstraintInfoClass;
	extern hkClass hkPoweredChainMapperClass;
	extern hkClass hkPoweredChainMapperLinkInfoClass;
	extern hkClass hkPoweredChainMapperTargetClass;
	extern hkClass hkPrismaticConstraintDataAtomsClass;
	extern hkClass hkPrismaticConstraintDataClass;
	extern hkClass hkPropertyClass;
	extern hkClass hkPropertyValueClass;
	extern hkClass hkPulleyConstraintAtomClass;
	extern hkClass hkPulleyConstraintDataAtomsClass;
	extern hkClass hkPulleyConstraintDataClass;
	extern hkClass hkRagdollConstraintDataAtomsClass;
	extern hkClass hkRagdollConstraintDataClass;
	extern hkClass hkRagdollInstanceClass;
	extern hkClass hkRagdollLimitsDataAtomsClass;
	extern hkClass hkRagdollLimitsDataClass;
	extern hkClass hkRagdollMotorConstraintAtomClass;
	extern hkClass hkRayCollidableFilterClass;
	extern hkClass hkRayShapeCollectionFilterClass;
	extern hkClass hkReferencedObjectClass;
	extern hkClass hkRejectRayChassisListenerClass;
	extern hkClass hkReorientActionClass;
	extern hkClass hkRigidBodyClass;
	extern hkClass hkRigidBodyDeactivatorClass;
	extern hkClass hkRigidBodyDisplayBindingClass;
	extern hkClass hkRootLevelContainerClass;
	extern hkClass hkRootLevelContainerNamedVariantClass;
	extern hkClass hkSampledHeightFieldShapeClass;
	extern hkClass hkSerializedDisplayMarkerClass;
	extern hkClass hkSerializedDisplayMarkerListClass;
	extern hkClass hkSerializedDisplayRbTransformsClass;
	extern hkClass hkSerializedDisplayRbTransformsDisplayTransformPairClass;
	extern hkClass hkSetLocalRotationsConstraintAtomClass;
	extern hkClass hkSetLocalTransformsConstraintAtomClass;
	extern hkClass hkSetLocalTranslationsConstraintAtomClass;
	extern hkClass hkShapeClass;
	extern hkClass hkShapeCollectionClass;
	extern hkClass hkShapeCollectionFilterClass;
	extern hkClass hkShapeContainerClass;
	extern hkClass hkShapePhantomClass;
	extern hkClass hkShapeRayCastInputClass;
	extern hkClass hkSimpleMeshShapeClass;
	extern hkClass hkSimpleMeshShapeTriangleClass;
	extern hkClass hkSimpleShapePhantomClass;
	extern hkClass hkSingleShapeContainerClass;
	extern hkClass hkSkeletalAnimationClass;
	extern hkClass hkSkeletonClass;
	extern hkClass hkSkeletonMapperClass;
	extern hkClass hkSkeletonMapperDataChainMappingClass;
	extern hkClass hkSkeletonMapperDataClass;
	extern hkClass hkSkeletonMapperDataSimpleMappingClass;
	extern hkClass hkSoftContactModifierConstraintAtomClass;
	extern hkClass hkSpatialRigidBodyDeactivatorClass;
	extern hkClass hkSpatialRigidBodyDeactivatorSampleClass;
	extern hkClass hkSphereClass;
	extern hkClass hkSphereMotionClass;
	extern hkClass hkSphereRepShapeClass;
	extern hkClass hkSphereShapeClass;
	extern hkClass hkSpringActionClass;
	extern hkClass hkSpringDamperConstraintMotorClass;
	extern hkClass hkStabilizedBoxMotionClass;
	extern hkClass hkStabilizedSphereMotionClass;
	extern hkClass hkStiffSpringChainDataClass;
	extern hkClass hkStiffSpringChainDataConstraintInfoClass;
	extern hkClass hkStiffSpringConstraintAtomClass;
	extern hkClass hkStiffSpringConstraintDataAtomsClass;
	extern hkClass hkStiffSpringConstraintDataClass;
	extern hkClass hkStorageMeshShapeClass;
	extern hkClass hkStorageMeshShapeSubpartStorageClass;
	extern hkClass hkStorageSampledHeightFieldShapeClass;
	extern hkClass hkSweptTransformClass;
	extern hkClass hkThinBoxMotionClass;
	extern hkClass hkTransformShapeClass;
	extern hkClass hkTriSampledHeightFieldBvTreeShapeClass;
	extern hkClass hkTriSampledHeightFieldCollectionClass;
	extern hkClass hkTriangleShapeClass;
	extern hkClass hkTwistLimitConstraintAtomClass;
	extern hkClass hkTypedBroadPhaseHandleClass;
	extern hkClass hkTyremarkPointClass;
	extern hkClass hkTyremarksInfoClass;
	extern hkClass hkTyremarksWheelClass;
	extern hkClass hkUnaryActionClass;
	extern hkClass hkVehicleAerodynamicsClass;
	extern hkClass hkVehicleBrakeClass;
	extern hkClass hkVehicleDataClass;
	extern hkClass hkVehicleDataWheelComponentParamsClass;
	extern hkClass hkVehicleDefaultAerodynamicsClass;
	extern hkClass hkVehicleDefaultAnalogDriverInputClass;
	extern hkClass hkVehicleDefaultBrakeClass;
	extern hkClass hkVehicleDefaultBrakeWheelBrakingPropertiesClass;
	extern hkClass hkVehicleDefaultEngineClass;
	extern hkClass hkVehicleDefaultSteeringClass;
	extern hkClass hkVehicleDefaultSuspensionClass;
	extern hkClass hkVehicleDefaultSuspensionWheelSpringSuspensionParametersClass;
	extern hkClass hkVehicleDefaultTransmissionClass;
	extern hkClass hkVehicleDefaultVelocityDamperClass;
	extern hkClass hkVehicleDriverInputAnalogStatusClass;
	extern hkClass hkVehicleDriverInputClass;
	extern hkClass hkVehicleDriverInputStatusClass;
	extern hkClass hkVehicleEngineClass;
	extern hkClass hkVehicleFrictionDescriptionAxisDescriptionClass;
	extern hkClass hkVehicleFrictionDescriptionClass;
	extern hkClass hkVehicleFrictionStatusAxisStatusClass;
	extern hkClass hkVehicleFrictionStatusClass;
	extern hkClass hkVehicleInstanceClass;
	extern hkClass hkVehicleInstanceWheelInfoClass;
	extern hkClass hkVehicleRaycastWheelCollideClass;
	extern hkClass hkVehicleSteeringClass;
	extern hkClass hkVehicleSuspensionClass;
	extern hkClass hkVehicleSuspensionSuspensionWheelParametersClass;
	extern hkClass hkVehicleTransmissionClass;
	extern hkClass hkVehicleVelocityDamperClass;
	extern hkClass hkVehicleWheelCollideClass;
	extern hkClass hkVelocityConstraintMotorClass;
	extern hkClass hkVersioningExceptionsArrayClass;
	extern hkClass hkVersioningExceptionsArrayVersioningExceptionClass;
	extern hkClass hkViscousSurfaceModifierConstraintAtomClass;
	extern hkClass hkWaveletSkeletalAnimationClass;
	extern hkClass hkWaveletSkeletalAnimationQuantizationFormatClass;
	extern hkClass hkWheelConstraintDataAtomsClass;
	extern hkClass hkWheelConstraintDataClass;
	extern hkClass hkWorldCinfoClass;
	extern hkClass hkWorldMemoryWatchDogClass;
	extern hkClass hkWorldObjectClass;
	extern hkClass hkbAdditiveBinaryBlenderGeneratorClass;
	extern hkClass hkbAttributeModifierClass;
	extern hkClass hkbBehaviorClass;
	extern hkClass hkbBinaryBlenderGeneratorClass;
	extern hkClass hkbBlenderGeneratorChildClass;
	extern hkClass hkbBlenderGeneratorClass;
	extern hkClass hkbBlendingTransitionEffectClass;
	extern hkClass hkbCharacterBoneInfoClass;
	extern hkClass hkbCharacterSetupClass;
	extern hkClass hkbClipGeneratorClass;
	extern hkClass hkbClipTriggerClass;
	extern hkClass hkbControlLookAtModifierClass;
	extern hkClass hkbEventClass;
	extern hkClass hkbFootIkControlDataClass;
	extern hkClass hkbFootIkControlsModifierClass;
	extern hkClass hkbFootIkGainsClass;
	extern hkClass hkbFootIkModifierClass;
	extern hkClass hkbGeneratorClass;
	extern hkClass hkbGetUpModifierClass;
	extern hkClass hkbHandIkModifierClass;
	extern hkClass hkbKeyframeDataClass;
	extern hkClass hkbLookAtModifierClass;
	extern hkClass hkbModifierClass;
	extern hkClass hkbModifierGeneratorClass;
	extern hkClass hkbModifierSequenceClass;
	extern hkClass hkbNodeClass;
	extern hkClass hkbPoseMatchingModifierClass;
	extern hkClass hkbPoweredRagdollControlDataClass;
	extern hkClass hkbPoweredRagdollControlsModifierClass;
	extern hkClass hkbPoweredRagdollModifierClass;
	extern hkClass hkbPredicateClass;
	extern hkClass hkbRagdollDriverModifierClass;
	extern hkClass hkbReachModifierClass;
	extern hkClass hkbReferencePoseGeneratorClass;
	extern hkClass hkbRigidBodyRagdollControlDataClass;
	extern hkClass hkbRigidBodyRagdollControlsModifierClass;
	extern hkClass hkbRigidBodyRagdollModifierClass;
	extern hkClass hkbStateMachineClass;
	extern hkClass hkbStateMachineIntervalClass;
	extern hkClass hkbStateMachineStateInfoClass;
	extern hkClass hkbStateMachineTransitionInfoClass;
	extern hkClass hkbStringPredicateClass;
	extern hkClass hkbTransitionEffectClass;
	extern hkClass hkbVariableSetClass;
	extern hkClass hkbVariableSetTargetClass;
	extern hkClass hkbVariableSetVariableClass;
	extern hkClass hkxAnimatedFloatClass;
	extern hkClass hkxAnimatedMatrixClass;
	extern hkClass hkxAnimatedQuaternionClass;
	extern hkClass hkxAnimatedVectorClass;
	extern hkClass hkxAttributeClass;
	extern hkClass hkxAttributeGroupClass;
	extern hkClass hkxCameraClass;
	extern hkClass hkxEnvironmentClass;
	extern hkClass hkxEnvironmentVariableClass;
	extern hkClass hkxIndexBufferClass;
	extern hkClass hkxLightClass;
	extern hkClass hkxMaterialClass;
	extern hkClass hkxMaterialEffectClass;
	extern hkClass hkxMaterialTextureStageClass;
	extern hkClass hkxMeshClass;
	extern hkClass hkxMeshSectionClass;
	extern hkClass hkxNodeAnnotationDataClass;
	extern hkClass hkxNodeClass;
	extern hkClass hkxSceneClass;
	extern hkClass hkxSkinBindingClass;
	extern hkClass hkxSparselyAnimatedBoolClass;
	extern hkClass hkxSparselyAnimatedEnumClass;
	extern hkClass hkxSparselyAnimatedIntClass;
	extern hkClass hkxSparselyAnimatedStringClass;
	extern hkClass hkxSparselyAnimatedStringStringTypeClass;
	extern hkClass hkxTextureFileClass;
	extern hkClass hkxTextureInplaceClass;
	extern hkClass hkxVertexBufferClass;
	extern hkClass hkxVertexFormatClass;
	extern hkClass hkxVertexP4N4C1T2Class;
	extern hkClass hkxVertexP4N4T4B4C1T2Class;
	extern hkClass hkxVertexP4N4T4B4W4I4C1Q2Class;
	extern hkClass hkxVertexP4N4T4B4W4I4Q4Class;
	extern hkClass hkxVertexP4N4W4I4C1Q2Class;

	static hkInternalClassMember hkAnimationContainerClass_Members[] =
	{
		{ "skeletons", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "animations", &hkSkeletalAnimationClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "bindings", &hkAnimationBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "attachments", &hkBoneAttachmentClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "skins", &hkMeshBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnimationContainerClass(
		"hkAnimationContainer",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnimationContainerClass_Members),
		int(sizeof(hkAnimationContainerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkAnimationBindingBlendHintEnumItems[] =
	{
		{0, "NORMAL"},
		{1, "ADDITIVE"},
	};
	static const hkInternalClassEnum hkAnimationBindingEnums[] = {
		{"BlendHint", hkAnimationBindingBlendHintEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkAnimationBindingBlendHintEnum = reinterpret_cast<const hkClassEnum*>(&hkAnimationBindingEnums[0]);
	static hkInternalClassMember hkAnimationBindingClass_Members[] =
	{
		{ "animation", &hkSkeletalAnimationClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "animationTrackToBoneIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "blendHint", HK_NULL, hkAnimationBindingBlendHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	namespace
	{
		struct hkAnimationBinding_DefaultStruct
		{
			int s_defaultOffsets[3];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkInt8 /* enum BlendHint */ m_blendHint;
		};
		const hkAnimationBinding_DefaultStruct hkAnimationBinding_Default =
		{
			{-1,-1,HK_OFFSET_OF(hkAnimationBinding_DefaultStruct,m_blendHint)},
			0
		};
	}
	hkClass hkAnimationBindingClass(
		"hkAnimationBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkAnimationBindingEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkAnimationBindingClass_Members),
		int(sizeof(hkAnimationBindingClass_Members)/sizeof(hkInternalClassMember)),
		&hkAnimationBinding_Default
		);
	static hkInternalClassMember hkAnnotationTrack_AnnotationClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "text", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnnotationTrackAnnotationClass(
		"hkAnnotationTrackAnnotation",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnnotationTrack_AnnotationClass_Members),
		int(sizeof(hkAnnotationTrack_AnnotationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAnnotationTrackClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "annotations", &hkAnnotationTrackAnnotationClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnnotationTrackClass(
		"hkAnnotationTrack",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnnotationTrackClass_Members),
		int(sizeof(hkAnnotationTrackClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	extern const hkClassEnum* hkSkeletalAnimationTypeEnum;
	static const hkInternalClassEnumItem hkSkeletalAnimationTypeEnumItems[] =
	{
		{0, "HK_UNKNOWN_ANIMATION"},
		{1, "HK_INTERLEAVED_ANIMATION"},
		{2, "HK_DELTA_COMPRESSED_ANIMATION"},
		{3, "HK_WAVELET_COMPRESSED_ANIMATION"},
	};
	static const hkInternalClassEnum hkSkeletalAnimationEnums[] = {
		{"Type", hkSkeletalAnimationTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkSkeletalAnimationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkSkeletalAnimationEnums[0]);
	static hkInternalClassMember hkSkeletalAnimationClass_Members[] =
	{
		{ "type", HK_NULL, hkSkeletalAnimationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_32, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numberOfTracks", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extractedMotion", &hkAnimatedReferenceFrameClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "annotationTracks", &hkAnnotationTrackClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletalAnimationClass(
		"hkSkeletalAnimation",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkSkeletalAnimationEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkSkeletalAnimationClass_Members),
		int(sizeof(hkSkeletalAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members[] =
	{
		{ "maxBitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numD", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaleIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bitWidthIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkDeltaCompressedSkeletalAnimationQuantizationFormatClass(
		"hkDeltaCompressedSkeletalAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members),
		int(sizeof(hkDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDeltaCompressedSkeletalAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkDeltaCompressedSkeletalAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticMaskIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticMaskSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticDOFsIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticDOFsSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "totalBlockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lastBlockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dataBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkDeltaCompressedSkeletalAnimationClass(
		"hkDeltaCompressedSkeletalAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDeltaCompressedSkeletalAnimationClass_Members),
		int(sizeof(hkDeltaCompressedSkeletalAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkInterleavedSkeletalAnimationClass_Members[] =
	{
		{ "transforms", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkInterleavedSkeletalAnimationClass(
		"hkInterleavedSkeletalAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkInterleavedSkeletalAnimationClass_Members),
		int(sizeof(hkInterleavedSkeletalAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWaveletSkeletalAnimation_QuantizationFormatClass_Members[] =
	{
		{ "maxBitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numD", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaleIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bitWidthIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWaveletSkeletalAnimationQuantizationFormatClass(
		"hkWaveletSkeletalAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWaveletSkeletalAnimation_QuantizationFormatClass_Members),
		int(sizeof(hkWaveletSkeletalAnimation_QuantizationFormatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWaveletSkeletalAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkWaveletSkeletalAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticMaskIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticDOFsIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockIndexIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockIndexSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dataBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkWaveletSkeletalAnimationClass(
		"hkWaveletSkeletalAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWaveletSkeletalAnimationClass_Members),
		int(sizeof(hkWaveletSkeletalAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMeshBinding_MappingClass_Members[] =
	{
		{ "mapping", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkMeshBindingMappingClass(
		"hkMeshBindingMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMeshBinding_MappingClass_Members),
		int(sizeof(hkMeshBinding_MappingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMeshBindingClass_Members[] =
	{
		{ "mesh", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skeleton", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mappings", &hkMeshBindingMappingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "inverseWorldBindPose", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_TRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkMeshBindingClass(
		"hkMeshBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMeshBindingClass_Members),
		int(sizeof(hkMeshBindingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkSkeletonMapperConstraintSourceEnumItems[] =
	{
		{0, "NO_CONSTRAINTS"},
		{1, "REFERENCE_POSE"},
		{2, "CURRENT_POSE"},
	};
	static const hkInternalClassEnum hkSkeletonMapperEnums[] = {
		{"ConstraintSource", hkSkeletonMapperConstraintSourceEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkSkeletonMapperConstraintSourceEnum = reinterpret_cast<const hkClassEnum*>(&hkSkeletonMapperEnums[0]);
	static hkInternalClassMember hkSkeletonMapperClass_Members[] =
	{
		{ "mapping", &hkSkeletonMapperDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletonMapperClass(
		"hkSkeletonMapper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkSkeletonMapperEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkSkeletonMapperClass_Members),
		int(sizeof(hkSkeletonMapperClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSkeletonMapperData_SimpleMappingClass_Members[] =
	{
		{ "boneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletonMapperDataSimpleMappingClass(
		"hkSkeletonMapperDataSimpleMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSkeletonMapperData_SimpleMappingClass_Members),
		int(sizeof(hkSkeletonMapperData_SimpleMappingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSkeletonMapperData_ChainMappingClass_Members[] =
	{
		{ "startBoneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endBoneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startBoneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endBoneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startAFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endAFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletonMapperDataChainMappingClass(
		"hkSkeletonMapperDataChainMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSkeletonMapperData_ChainMappingClass_Members),
		int(sizeof(hkSkeletonMapperData_ChainMappingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSkeletonMapperDataClass_Members[] =
	{
		{ "skeletonA", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skeletonB", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "simpleMappings", &hkSkeletonMapperDataSimpleMappingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "chainMappings", &hkSkeletonMapperDataChainMappingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "unmappedBones", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "keepUnmappedLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletonMapperDataClass(
		"hkSkeletonMapperData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSkeletonMapperDataClass_Members),
		int(sizeof(hkSkeletonMapperDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkAnimatedReferenceFrameClass(
		"hkAnimatedReferenceFrame",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkDefaultAnimatedReferenceFrameClass_Members[] =
	{
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forward", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "referenceFrameSamples", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkDefaultAnimatedReferenceFrameClass(
		"hkDefaultAnimatedReferenceFrame",
		&hkAnimatedReferenceFrameClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDefaultAnimatedReferenceFrameClass_Members),
		int(sizeof(hkDefaultAnimatedReferenceFrameClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBoneClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lockTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBoneClass(
		"hkBone",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBoneClass_Members),
		int(sizeof(hkBoneClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBoneAttachmentClass_Members[] =
	{
		{ "boneFromAttachment", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachment", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBoneAttachmentClass(
		"hkBoneAttachment",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBoneAttachmentClass_Members),
		int(sizeof(hkBoneAttachmentClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSkeletonClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parentIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "bones", &hkBoneClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "referencePose", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletonClass(
		"hkSkeleton",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSkeletonClass_Members),
		int(sizeof(hkSkeletonClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbBehaviorClass_Members[] =
	{
		{ "rootGenerator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableSet", &hkbVariableSetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "isClone", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "activeNodes", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "activeNodeToIndexMap", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBehaviorClass(
		"hkbBehavior",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBehaviorClass_Members),
		int(sizeof(hkbBehaviorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbCharacterBoneInfoWhichLimbEnumItems[] =
	{
		{0, "FIRST_LIMB"},
		{0, "LIMB_LEFT"},
		{1, "LIMB_RIGHT"},
		{2, "NUM_LIMBS"},
	};
	static const hkInternalClassEnum hkbCharacterBoneInfoEnums[] = {
		{"WhichLimb", hkbCharacterBoneInfoWhichLimbEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbCharacterBoneInfoWhichLimbEnum = reinterpret_cast<const hkClassEnum*>(&hkbCharacterBoneInfoEnums[0]);
	static hkInternalClassMember hkbCharacterBoneInfoClass_Members[] =
	{
		{ "clavicleIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "shoulderIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "elbowIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "wristIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "hipIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "kneeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "ankleIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "pelvisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "neckIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "headIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spineIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCharacterBoneInfoClass(
		"hkbCharacterBoneInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbCharacterBoneInfoEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbCharacterBoneInfoClass_Members),
		int(sizeof(hkbCharacterBoneInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbCharacterSetupClass_Members[] =
	{
		{ "animationSkeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "animationBoneInfo", &hkbCharacterBoneInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelUpMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelForwardMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelRightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attributeDefaults", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "ragdollSkeleton", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "ragdollToAnimationSkeletonMapper", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "animationToRagdollSkeletonMapper", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "ragdollBoneInfo", &hkbCharacterBoneInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingUtility", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbCharacterSetup_DefaultStruct
		{
			int s_defaultOffsets[11];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			const class hkSkeleton* m_animationSkeleton;
			class hkSkeletonMapper* m_ragdollToAnimationSkeletonMapper;
			class hkSkeletonMapper* m_animationToRagdollSkeletonMapper;
			class hkPoseMatchingUtility* m_poseMatchingUtility;
		};
		const hkbCharacterSetup_DefaultStruct hkbCharacterSetup_Default =
		{
			{HK_OFFSET_OF(hkbCharacterSetup_DefaultStruct,m_animationSkeleton),-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbCharacterSetup_DefaultStruct,m_ragdollToAnimationSkeletonMapper),HK_OFFSET_OF(hkbCharacterSetup_DefaultStruct,m_animationToRagdollSkeletonMapper),-1,HK_OFFSET_OF(hkbCharacterSetup_DefaultStruct,m_poseMatchingUtility)},
			HK_NULL,HK_NULL,HK_NULL,HK_NULL
		};
	}
	hkClass hkbCharacterSetupClass(
		"hkbCharacterSetup",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacterSetupClass_Members),
		int(sizeof(hkbCharacterSetupClass_Members)/sizeof(hkInternalClassMember)),
		&hkbCharacterSetup_Default
		);
	static const hkInternalClassEnumItem hkbEventSystemEventIdsEnumItems[] =
	{
		{-1, "NULL_EVENT"},
	};
	static const hkInternalClassEnum hkbEventEnums[] = {
		{"SystemEventIds", hkbEventSystemEventIdsEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbEventSystemEventIdsEnum = reinterpret_cast<const hkClassEnum*>(&hkbEventEnums[0]);
	static hkInternalClassMember hkbEventClass_Members[] =
	{
		{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "payload", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbEventClass(
		"hkbEvent",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbEventEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbEventClass_Members),
		int(sizeof(hkbEventClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkbGeneratorClass(
		"hkbGenerator",
		&hkbNodeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkbBinaryBlenderGeneratorClass_Members[] =
	{
		{ "blendWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialBlendWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sync", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfSyncMasterChild", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBinaryBlenderGenerator_DefaultStruct
		{
			int s_defaultOffsets[7];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_blendWeight;
			hkReal m_initialBlendWeight;
			_hkBool m_sync;
			hkInt8 m_indexOfSyncMasterChild;
			hkReal m_frequency;
		};
		const hkbBinaryBlenderGenerator_DefaultStruct hkbBinaryBlenderGenerator_Default =
		{
			{HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_blendWeight),HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_initialBlendWeight),HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_sync),HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_indexOfSyncMasterChild),-1,-1,HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_frequency)},
			0.0f,-1.0f,false,-1,0.0f
		};
	}
	hkClass hkbBinaryBlenderGeneratorClass(
		"hkbBinaryBlenderGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBinaryBlenderGeneratorClass_Members),
		int(sizeof(hkbBinaryBlenderGeneratorClass_Members)/sizeof(hkInternalClassMember)),
		&hkbBinaryBlenderGenerator_Default
		);
	hkClass hkbAdditiveBinaryBlenderGeneratorClass(
		"hkbAdditiveBinaryBlenderGenerator",
		&hkbBinaryBlenderGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkbBlenderGeneratorChildClass_Members[] =
	{
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "weight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneWeights", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBlenderGeneratorChildClass(
		"hkbBlenderGeneratorChild",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBlenderGeneratorChildClass_Members),
		int(sizeof(hkbBlenderGeneratorChildClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbBlenderGeneratorClass_Members[] =
	{
		{ "referencePoseWeightThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfSyncMasterChild", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "autoComputeSecondGeneratorWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sync", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "children", &hkbBlenderGeneratorChildClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "numChildFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBlenderGenerator_DefaultStruct
		{
			int s_defaultOffsets[8];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_referencePoseWeightThreshold;
			hkInt16 m_indexOfSyncMasterChild;
			_hkBool m_autoComputeSecondGeneratorWeight;
			_hkBool m_sync;
		};
		const hkbBlenderGenerator_DefaultStruct hkbBlenderGenerator_Default =
		{
			{HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_referencePoseWeightThreshold),HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_indexOfSyncMasterChild),HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_autoComputeSecondGeneratorWeight),HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_sync),-1,-1,-1,-1},
			0.0f,-1,false,false
		};
	}
	hkClass hkbBlenderGeneratorClass(
		"hkbBlenderGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBlenderGeneratorClass_Members),
		int(sizeof(hkbBlenderGeneratorClass_Members)/sizeof(hkInternalClassMember)),
		&hkbBlenderGenerator_Default
		);
	static hkInternalClassMember hkbClipTriggerClass_Members[] =
	{
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "event", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "relativeToEndOfClip", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbClipTriggerClass(
		"hkbClipTrigger",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbClipTriggerClass_Members),
		int(sizeof(hkbClipTriggerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbClipGeneratorPlaybackModeEnumItems[] =
	{
		{0, "MODE_SINGLE_PLAY"},
		{1, "MODE_LOOPING"},
		{2, "MODE_USER_CONTROLLED"},
		{3, "MODE_COUNT"},
	};
	static const hkInternalClassEnum hkbClipGeneratorEnums[] = {
		{"PlaybackMode", hkbClipGeneratorPlaybackModeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbClipGeneratorPlaybackModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbClipGeneratorEnums[0]);
	static hkInternalClassMember hkbClipGeneratorClass_Members[] =
	{
		{ "mode", HK_NULL, hkbClipGeneratorPlaybackModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "cropStartAmountLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cropEndAmountLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "playbackSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enforcedDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "continueMotionAtEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userControlledTimeFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "filename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triggers", &hkbClipTriggerClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "animationControl", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "atEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "extractedMotion", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL },
		{ "ignoreStartTime", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "echos", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbClipGenerator_DefaultStruct
		{
			int s_defaultOffsets[15];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_enforcedDuration;
		};
		const hkbClipGenerator_DefaultStruct hkbClipGenerator_Default =
		{
			{-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbClipGenerator_DefaultStruct,m_enforcedDuration),-1,-1,-1,-1,-1,-1,-1,-1,-1},
			0.0f
		};
	}
	hkClass hkbClipGeneratorClass(
		"hkbClipGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbClipGeneratorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbClipGeneratorClass_Members),
		int(sizeof(hkbClipGeneratorClass_Members)/sizeof(hkInternalClassMember)),
		&hkbClipGenerator_Default
		);
	static hkInternalClassMember hkbModifierGeneratorClass_Members[] =
	{
		{ "modifier", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbModifierGeneratorClass(
		"hkbModifierGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbModifierGeneratorClass_Members),
		int(sizeof(hkbModifierGeneratorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbReferencePoseGeneratorClass_Members[] =
	{
		{ "skeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkbReferencePoseGeneratorClass(
		"hkbReferencePoseGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbReferencePoseGeneratorClass_Members),
		int(sizeof(hkbReferencePoseGeneratorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkbModifierClass(
		"hkbModifier",
		&hkbNodeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkbAttributeModifierClass_Members[] =
	{
		{ "attributes", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "attributeIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkbAttributeModifierClass(
		"hkbAttributeModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbAttributeModifierClass_Members),
		int(sizeof(hkbAttributeModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbFootIkGainsClass_Members[] =
	{
		{ "onOffGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ascendingGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "standAscendingGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "descendingGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbFootIkGainsClass(
		"hkbFootIkGains",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkGainsClass_Members),
		int(sizeof(hkbFootIkGainsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbFootIkControlDataClass_Members[] =
	{
		{ "isFootIkEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gains", &hkbFootIkGainsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbFootIkControlDataClass(
		"hkbFootIkControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkControlDataClass_Members),
		int(sizeof(hkbFootIkControlDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbFootIkModifierClass_Members[] =
	{
		{ "gains", &hkbFootIkGainsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFootHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minFootHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isStanding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isFootOnAir", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "originalFootMsIsSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "originalFootMS", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "originalGroundHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "kneeAxisLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useTrackData", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isSetUp", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "raycastInterface", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "leftFootIkSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "rightFootIkSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "error", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "prevIsFootIkEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbFootIkModifier_DefaultStruct
		{
			int s_defaultOffsets[16];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkBool m_isSetUp;
			class hkRaycastInterface* m_raycastInterface;
			hkReal m_prevIsFootIkEnabled;
		};
		const hkbFootIkModifier_DefaultStruct hkbFootIkModifier_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_isSetUp),HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_raycastInterface),-1,-1,-1,HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_prevIsFootIkEnabled)},
			false,HK_NULL,0.0f
		};
	}
	hkClass hkbFootIkModifierClass(
		"hkbFootIkModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkModifierClass_Members),
		int(sizeof(hkbFootIkModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbFootIkModifier_Default
		);
	static hkInternalClassMember hkbFootIkControlsModifierClass_Members[] =
	{
		{ "controlData", &hkbFootIkControlDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbFootIkControlsModifierClass(
		"hkbFootIkControlsModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkControlsModifierClass_Members),
		int(sizeof(hkbFootIkControlsModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbGetUpModifierClass_Members[] =
	{
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initNextModify", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "timeSinceBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "timeStep", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbGetUpModifier_DefaultStruct
		{
			int s_defaultOffsets[4];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_duration;
			_hkBool m_initNextModify;
			hkReal m_timeSinceBegin;
			hkReal m_timeStep;
		};
		const hkbGetUpModifier_DefaultStruct hkbGetUpModifier_Default =
		{
			{HK_OFFSET_OF(hkbGetUpModifier_DefaultStruct,m_duration),HK_OFFSET_OF(hkbGetUpModifier_DefaultStruct,m_initNextModify),HK_OFFSET_OF(hkbGetUpModifier_DefaultStruct,m_timeSinceBegin),HK_OFFSET_OF(hkbGetUpModifier_DefaultStruct,m_timeStep)},
			1.0f,false,0.0f,0.0f
		};
	}
	hkClass hkbGetUpModifierClass(
		"hkbGetUpModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbGetUpModifierClass_Members),
		int(sizeof(hkbGetUpModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbGetUpModifier_Default
		);
	static hkInternalClassMember hkbHandIkModifierClass_Members[] =
	{
		{ "previousReachPointWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "previousNormalWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "radarLocationRS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "elbowAxisLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "backHandNormalInHandSpace", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachReferenceBoneIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachStopped", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "hasBeenSetup", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkbHandIkModifierClass(
		"hkbHandIkModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbHandIkModifierClass_Members),
		int(sizeof(hkbHandIkModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbLookAtModifierClass_Members[] =
	{
		{ "targetGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookAtGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookAtLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookUp", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookUpAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "headForwardHS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "headRightHS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isOn", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookAtLastTargetWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lookAtWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbLookAtModifierClass(
		"hkbLookAtModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbLookAtModifierClass_Members),
		int(sizeof(hkbLookAtModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbControlLookAtModifierClass_Members[] =
	{
		{ "lookAtMod", &hkbLookAtModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "isOn", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbControlLookAtModifierClass(
		"hkbControlLookAtModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbControlLookAtModifierClass_Members),
		int(sizeof(hkbControlLookAtModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbPoseMatchingModifierModePMAMEnumItems[] =
	{
		{0, "MODE_MATCH"},
		{1, "MODE_PLAY"},
	};
	static const hkInternalClassEnum hkbPoseMatchingModifierEnums[] = {
		{"ModePMAM", hkbPoseMatchingModifierModePMAMEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbPoseMatchingModifierModePMAMEnum = reinterpret_cast<const hkClassEnum*>(&hkbPoseMatchingModifierEnums[0]);
	static hkInternalClassMember hkbPoseMatchingModifierClass_Members[] =
	{
		{ "hysteresis", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blendSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "playbackSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "doneEventLeadTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mode", HK_NULL, hkbPoseMatchingModifierModePMAMEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "annotationName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "donePlayingEvent", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "animations", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "animatedSkeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "matchingPoseControl", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "matchingPose", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "currentMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bestMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timeSinceBetterMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "getUpControl", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "error", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "motionTimestep", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbPoseMatchingModifier_DefaultStruct
		{
			int s_defaultOffsets[17];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			class hkAnimatedSkeleton* m_animatedSkeleton;
			class PoseMatchingAnimationMixerControl* m_matchingPoseControl;
			class PoseMatchingAnimationMixerSkeletalAnimation* m_matchingPose;
			class hkDefaultAnimationControl* m_getUpControl;
			hkReal m_error;
			hkReal m_motionTimestep;
		};
		const hkbPoseMatchingModifier_DefaultStruct hkbPoseMatchingModifier_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_animatedSkeleton),HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_matchingPoseControl),HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_matchingPose),-1,-1,-1,HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_getUpControl),HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_error),HK_OFFSET_OF(hkbPoseMatchingModifier_DefaultStruct,m_motionTimestep)},
			HK_NULL,HK_NULL,HK_NULL,HK_NULL,3.40282e+38f,0.0f
		};
	}
	hkClass hkbPoseMatchingModifierClass(
		"hkbPoseMatchingModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbPoseMatchingModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbPoseMatchingModifierClass_Members),
		int(sizeof(hkbPoseMatchingModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbPoseMatchingModifier_Default
		);
	static hkInternalClassMember hkbKeyframeDataClass_Members[] =
	{
		{ "isDataInitialized", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "keyframeData", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbKeyframeData_DefaultStruct
		{
			int s_defaultOffsets[2];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkBool m_isDataInitialized;
		};
		const hkbKeyframeData_DefaultStruct hkbKeyframeData_Default =
		{
			{HK_OFFSET_OF(hkbKeyframeData_DefaultStruct,m_isDataInitialized),-1},
			false
		};
	}
	hkClass hkbKeyframeDataClass(
		"hkbKeyframeData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbKeyframeDataClass_Members),
		int(sizeof(hkbKeyframeDataClass_Members)/sizeof(hkInternalClassMember)),
		&hkbKeyframeData_Default
		);
	static hkInternalClassMember hkbPoweredRagdollControlDataClass_Members[] =
	{
		{ "weight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proportionalRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constantRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbPoweredRagdollControlDataClass(
		"hkbPoweredRagdollControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbPoweredRagdollControlDataClass_Members),
		int(sizeof(hkbPoweredRagdollControlDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbPoweredRagdollModifierComputeWorldFromModelModeEnumItems[] =
	{
		{0, "WORLD_FROM_MODEL_MODE_COMPUTE"},
		{1, "WORLD_FROM_MODEL_MODE_USE_INOUT"},
		{2, "WORLD_FROM_MODEL_MODE_USE_INPUT"},
	};
	static const hkInternalClassEnum hkbPoweredRagdollModifierEnums[] = {
		{"ComputeWorldFromModelMode", hkbPoweredRagdollModifierComputeWorldFromModelModeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbPoweredRagdollModifierComputeWorldFromModelModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbPoweredRagdollModifierEnums[0]);
	static hkInternalClassMember hkbPoweredRagdollModifierClass_Members[] =
	{
		{ "floorRaycastLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "controls", &hkbPoweredRagdollControlDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blendInTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "computeWorldFromModelMode", HK_NULL, hkbPoweredRagdollModifierComputeWorldFromModelModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "fixConstraintsTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useLocking", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timeActive", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "keyframedBones", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "keyframeData", &hkbKeyframeDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "boneWeights", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbPoweredRagdollModifier_DefaultStruct
		{
			int s_defaultOffsets[11];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_timeActive;
			hkReal m_timeSinceLastModify;
		};
		const hkbPoweredRagdollModifier_DefaultStruct hkbPoweredRagdollModifier_Default =
		{
			{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbPoweredRagdollModifier_DefaultStruct,m_timeActive),HK_OFFSET_OF(hkbPoweredRagdollModifier_DefaultStruct,m_timeSinceLastModify),-1,-1,-1},
			0,0.0f
		};
	}
	hkClass hkbPoweredRagdollModifierClass(
		"hkbPoweredRagdollModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbPoweredRagdollModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbPoweredRagdollModifierClass_Members),
		int(sizeof(hkbPoweredRagdollModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbPoweredRagdollModifier_Default
		);
	static hkInternalClassMember hkbPoweredRagdollControlsModifierClass_Members[] =
	{
		{ "controlData", &hkbPoweredRagdollControlDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneWeights", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkbPoweredRagdollControlsModifierClass(
		"hkbPoweredRagdollControlsModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbPoweredRagdollControlsModifierClass_Members),
		int(sizeof(hkbPoweredRagdollControlsModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbRagdollDriverModifierClass_Members[] =
	{
		{ "addRagdollToWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "removeRagdollFromWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poweredRagdollModifier", &hkbPoweredRagdollModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rigidBodyRagdollModifier", &hkbRigidBodyRagdollModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "activeModifier", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "doSetup", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRagdollDriverModifier_DefaultStruct
		{
			int s_defaultOffsets[6];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkBool m_addRagdollToWorld;
			_hkBool m_removeRagdollFromWorld;
			class hkbModifier* m_activeModifier;
			_hkBool m_doSetup;
		};
		const hkbRagdollDriverModifier_DefaultStruct hkbRagdollDriverModifier_Default =
		{
			{HK_OFFSET_OF(hkbRagdollDriverModifier_DefaultStruct,m_addRagdollToWorld),HK_OFFSET_OF(hkbRagdollDriverModifier_DefaultStruct,m_removeRagdollFromWorld),-1,-1,HK_OFFSET_OF(hkbRagdollDriverModifier_DefaultStruct,m_activeModifier),HK_OFFSET_OF(hkbRagdollDriverModifier_DefaultStruct,m_doSetup)},
			false,false,HK_NULL,true
		};
	}
	hkClass hkbRagdollDriverModifierClass(
		"hkbRagdollDriverModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRagdollDriverModifierClass_Members),
		int(sizeof(hkbRagdollDriverModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbRagdollDriverModifier_Default
		);
	static hkInternalClassMember hkbRigidBodyRagdollControlDataClass_Members[] =
	{
		{ "weight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hierarchyGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocityDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "accelerationGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocityGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionMaxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapMaxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapMaxLinearDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapMaxAngularDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "durationToBlend", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRigidBodyRagdollControlDataClass(
		"hkbRigidBodyRagdollControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRigidBodyRagdollControlDataClass_Members),
		int(sizeof(hkbRigidBodyRagdollControlDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbRigidBodyRagdollModifierClass_Members[] =
	{
		{ "controlDataPalette", &hkbRigidBodyRagdollControlDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "bodyIndexToPaletteIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "fixLegs", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowerBodyBones", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "rigidBodyController", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "doSetupNextEvaluate", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "timeSinceBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRigidBodyRagdollModifier_DefaultStruct
		{
			int s_defaultOffsets[8];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			class hkRagdollRigidBodyController* m_rigidBodyController;
			_hkBool m_doSetupNextEvaluate;
			hkReal m_timeSinceLastModify;
			hkReal m_timeSinceBegin;
		};
		const hkbRigidBodyRagdollModifier_DefaultStruct hkbRigidBodyRagdollModifier_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkbRigidBodyRagdollModifier_DefaultStruct,m_rigidBodyController),HK_OFFSET_OF(hkbRigidBodyRagdollModifier_DefaultStruct,m_doSetupNextEvaluate),HK_OFFSET_OF(hkbRigidBodyRagdollModifier_DefaultStruct,m_timeSinceLastModify),HK_OFFSET_OF(hkbRigidBodyRagdollModifier_DefaultStruct,m_timeSinceBegin)},
			HK_NULL,true,0.0f,0.0f
		};
	}
	hkClass hkbRigidBodyRagdollModifierClass(
		"hkbRigidBodyRagdollModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRigidBodyRagdollModifierClass_Members),
		int(sizeof(hkbRigidBodyRagdollModifierClass_Members)/sizeof(hkInternalClassMember)),
		&hkbRigidBodyRagdollModifier_Default
		);
	static hkInternalClassMember hkbRigidBodyRagdollControlsModifierClass_Members[] =
	{
		{ "controlData", &hkbRigidBodyRagdollControlDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRigidBodyRagdollControlsModifierClass(
		"hkbRigidBodyRagdollControlsModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRigidBodyRagdollControlsModifierClass_Members),
		int(sizeof(hkbRigidBodyRagdollControlsModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbReachModifierClass_Members[] =
	{
		{ "raycastInterface", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "reachWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "moveGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "leaveGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "raycastLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbReachModifierClass(
		"hkbReachModifier",
		&hkbHandIkModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbReachModifierClass_Members),
		int(sizeof(hkbReachModifierClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbModifierSequenceClass_Members[] =
	{
		{ "modifiers", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkbModifierSequenceClass(
		"hkbModifierSequence",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbModifierSequenceClass_Members),
		int(sizeof(hkbModifierSequenceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbNodeGetChildrenFlagBitsEnumItems[] =
	{
		{0x1, "FLAG_ACTIVE_ONLY"},
		{0x2, "FLAG_GENERATORS_ONLY"},
		{0x4, "FLAG_COMPUTE_CHILD_SPEEDS"},
	};
	static const hkInternalClassEnum hkbNodeEnums[] = {
		{"GetChildrenFlagBits", hkbNodeGetChildrenFlagBitsEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbNodeGetChildrenFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbNodeEnums[0]);
	static hkInternalClassMember hkbNodeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbNodeClass(
		"hkbNode",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbNodeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbNodeClass_Members),
		int(sizeof(hkbNodeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkbPredicateClass(
		"hkbPredicate",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkbStringPredicateClass_Members[] =
	{
		{ "predicateString", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStringPredicateClass(
		"hkbStringPredicate",
		&hkbPredicateClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStringPredicateClass_Members),
		int(sizeof(hkbStringPredicateClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbStateMachine_IntervalClass_Members[] =
	{
		{ "startEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateMachineIntervalClass(
		"hkbStateMachineInterval",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_IntervalClass_Members),
		int(sizeof(hkbStateMachine_IntervalClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbStateMachineTransitionInfoTransitionInfoFlagBitsEnumItems[] =
	{
		{0x1, "FLAG_USE_EVENT_INTERVAL"},
		{0x2, "FLAG_USE_BEGIN_INTERVAL"},
		{0x4, "FLAG_UNINTERRUPTIBLE_WHILE_PLAYING"},
		{0x8, "FLAG_UNINTERRUPTIBLE_WHILE_DELAYED"},
		{0x10, "FLAG_DELAY_STATE_CHANGE"},
		{0x20, "FLAG_DISABLED"},
		{0x40, "FLAG_DISALLOW_RETURN_TO_PREVIOUS_STATE"},
		{0x80, "FLAG_DISALLOW_RANDOM_TRANSITION"},
		{0x100, "FLAG_DISABLE_PREDICATE"},
		{0x4000, "FLAG_INTERNAL_IN_EVENT_INTERVAL"},
		{0x8000, "FLAG_INTERNAL_IN_BEGIN_INTERVAL"},
	};
	static const hkInternalClassEnum hkbStateMachineTransitionInfoEnums[] = {
		{"TransitionInfoFlagBits", hkbStateMachineTransitionInfoTransitionInfoFlagBitsEnumItems, 11, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbStateMachineTransitionInfoTransitionInfoFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbStateMachineTransitionInfoEnums[0]);
	static hkInternalClassMember hkbStateMachine_TransitionInfoClass_Members[] =
	{
		{ "eventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toState", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transition", &hkbTransitionEffectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "predicate", &hkbPredicateClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "eventInterval", &hkbStateMachineIntervalClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "beginInterval", &hkbStateMachineIntervalClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "priority", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbStateMachineTransitionInfo_DefaultStruct
		{
			int s_defaultOffsets[8];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkInt16 m_priority;
			hkUint16 m_flags;
		};
		const hkbStateMachineTransitionInfo_DefaultStruct hkbStateMachineTransitionInfo_Default =
		{
			{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbStateMachineTransitionInfo_DefaultStruct,m_priority),HK_OFFSET_OF(hkbStateMachineTransitionInfo_DefaultStruct,m_flags)},
			0,0
		};
	}
	hkClass hkbStateMachineTransitionInfoClass(
		"hkbStateMachineTransitionInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbStateMachineTransitionInfoEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_TransitionInfoClass_Members),
		int(sizeof(hkbStateMachine_TransitionInfoClass_Members)/sizeof(hkInternalClassMember)),
		&hkbStateMachineTransitionInfo_Default
		);
	static hkInternalClassMember hkbStateMachine_StateInfoClass_Members[] =
	{
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transitions", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateMachineStateInfoClass(
		"hkbStateMachineStateInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_StateInfoClass_Members),
		int(sizeof(hkbStateMachine_StateInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbStateMachineClass_Members[] =
	{
		{ "eventToSendWhenStateOrTransitionChanges", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startState", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "returnToPreviousStateEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "randomTransitionEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enterStartStateOnBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "randomStartState", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSimultaneousTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "states", &hkbStateMachineStateInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "globalTransitions", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "activeTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "state", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "delayedTransition", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "stateOrTransitionChanged", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "timeInState", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "previousState", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbStateMachine_DefaultStruct
		{
			int s_defaultOffsets[16];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkInt32 m_returnToPreviousStateEventId;
			hkInt32 m_randomTransitionEventId;
			_hkBool m_randomStartState;
			hkInt8 m_maxSimultaneousTransitions;
			hkReal m_timeInState;
		};
		const hkbStateMachine_DefaultStruct hkbStateMachine_Default =
		{
			{-1,-1,HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_returnToPreviousStateEventId),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_randomTransitionEventId),-1,HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_randomStartState),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_maxSimultaneousTransitions),-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_timeInState),-1},
			-1,-1,false,32,0.0f
		};
	}
	hkClass hkbStateMachineClass(
		"hkbStateMachine",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachineClass_Members),
		int(sizeof(hkbStateMachineClass_Members)/sizeof(hkInternalClassMember)),
		&hkbStateMachine_Default
		);
	hkClass hkbTransitionEffectClass(
		"hkbTransitionEffect",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static const hkInternalClassEnumItem hkbBlendingTransitionEffectFlagsBTBitsEnumItems[] =
	{
		{0x0, "FLAG_NONE"},
		{0x1, "FLAG_IGNORE_FROM_WORLD_FROM_MODEL"},
		{0x2, "FLAG_SYNC"},
	};
	static const hkInternalClassEnumItem hkbBlendingTransitionEffectEndModeBTEnumItems[] =
	{
		{0, "END_MODE_NONE"},
		{1, "END_MODE_TRANSITION_UNTIL_END_OF_FROM_GENERATOR"},
		{2, "END_MODE_CAP_DURATION_AT_END_OF_FROM_GENERATOR"},
	};
	static const hkInternalClassEnum hkbBlendingTransitionEffectEnums[] = {
		{"FlagsBTBits", hkbBlendingTransitionEffectFlagsBTBitsEnumItems, 3, HK_NULL, 0 },
		{"EndModeBT", hkbBlendingTransitionEffectEndModeBTEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbBlendingTransitionEffectFlagsBTBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlendingTransitionEffectEnums[0]);
	extern const hkClassEnum* hkbBlendingTransitionEffectEndModeBTEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlendingTransitionEffectEnums[1]);
	static hkInternalClassMember hkbBlendingTransitionEffectClass_Members[] =
	{
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toGeneratorStartTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endMode", HK_NULL, hkbBlendingTransitionEffectEndModeBTEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "fromGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "toGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "timeRemaining", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "timeInTransition", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "isClone", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBlendingTransitionEffect_DefaultStruct
		{
			int s_defaultOffsets[12];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_toGeneratorStartTime;
			hkInt8 /* enum EndModeBT */ m_endMode;
		};
		const hkbBlendingTransitionEffect_DefaultStruct hkbBlendingTransitionEffect_Default =
		{
			{-1,HK_OFFSET_OF(hkbBlendingTransitionEffect_DefaultStruct,m_toGeneratorStartTime),-1,HK_OFFSET_OF(hkbBlendingTransitionEffect_DefaultStruct,m_endMode),-1,-1,-1,-1,-1,-1,-1,-1},
			0.0f,0
		};
	}
	hkClass hkbBlendingTransitionEffectClass(
		"hkbBlendingTransitionEffect",
		&hkbTransitionEffectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbBlendingTransitionEffectEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbBlendingTransitionEffectClass_Members),
		int(sizeof(hkbBlendingTransitionEffectClass_Members)/sizeof(hkInternalClassMember)),
		&hkbBlendingTransitionEffect_Default
		);
	static const hkInternalClassEnumItem hkbVariableSetVariableTypeEnumItems[] =
	{
		{-1, "VARIABLE_TYPE_INVALID"},
		{0, "VARIABLE_TYPE_REAL"},
		{1, "VARIABLE_TYPE_BOOL"},
	};
	static const hkInternalClassEnum hkbVariableSetEnums[] = {
		{"VariableType", hkbVariableSetVariableTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbVariableSetVariableTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkbVariableSetEnums[0]);
	static hkInternalClassMember hkbVariableSet_TargetClass_Members[] =
	{
		{ "object", &hkReferencedObjectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "memberName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "arrayIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "memberIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbVariableSetTarget_DefaultStruct
		{
			int s_defaultOffsets[4];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			int m_memberIndex;
		};
		const hkbVariableSetTarget_DefaultStruct hkbVariableSetTarget_Default =
		{
			{-1,-1,-1,HK_OFFSET_OF(hkbVariableSetTarget_DefaultStruct,m_memberIndex)},
			-1
		};
	}
	hkClass hkbVariableSetTargetClass(
		"hkbVariableSetTarget",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableSet_TargetClass_Members),
		int(sizeof(hkbVariableSet_TargetClass_Members)/sizeof(hkInternalClassMember)),
		&hkbVariableSetTarget_Default
		);
	static hkInternalClassMember hkbVariableSet_VariableClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targets", &hkbVariableSetTargetClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbVariableSetVariableClass(
		"hkbVariableSetVariable",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableSet_VariableClass_Members),
		int(sizeof(hkbVariableSet_VariableClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkbVariableSetClass_Members[] =
	{
		{ "variables", &hkbVariableSetVariableClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbVariableSetClass(
		"hkbVariableSet",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbVariableSetEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbVariableSetClass_Members),
		int(sizeof(hkbVariableSetClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkBaseObjectClass(
		"hkBaseObject",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkReferencedObjectClass_Members[] =
	{
		{ "memSizeAndFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "referenceCount", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkReferencedObjectClass(
		"hkReferencedObject",
		&hkBaseObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkReferencedObjectClass_Members),
		int(sizeof(hkReferencedObjectClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkClassSignatureFlagsEnumItems[] =
	{
		{1, "SIGNATURE_LOCAL"},
	};
	static const hkInternalClassEnum hkClassEnums[] = {
		{"SignatureFlags", hkClassSignatureFlagsEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkClassSignatureFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnums[0]);
	static hkInternalClassMember hkClassClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parent", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "declaredEnums", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "declaredMembers", &hkClassMemberClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "defaults", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassClass(
		"hkClass",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkClassEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkClassClass_Members),
		int(sizeof(hkClassClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkClassEnum_ItemClass_Members[] =
	{
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassEnumItemClass(
		"hkClassEnumItem",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkClassEnum_ItemClass_Members),
		int(sizeof(hkClassEnum_ItemClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkClassEnumClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "items", &hkClassEnumItemClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassEnumClass(
		"hkClassEnum",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkClassEnumClass_Members),
		int(sizeof(hkClassEnumClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkClassMemberTypeEnumItems[] =
	{
		{0, "TYPE_VOID"},
		{1, "TYPE_BOOL"},
		{2, "TYPE_CHAR"},
		{3, "TYPE_INT8"},
		{4, "TYPE_UINT8"},
		{5, "TYPE_INT16"},
		{6, "TYPE_UINT16"},
		{7, "TYPE_INT32"},
		{8, "TYPE_UINT32"},
		{9, "TYPE_INT64"},
		{10, "TYPE_UINT64"},
		{11, "TYPE_REAL"},
		{12, "TYPE_VECTOR4"},
		{13, "TYPE_QUATERNION"},
		{14, "TYPE_MATRIX3"},
		{15, "TYPE_ROTATION"},
		{16, "TYPE_QSTRANSFORM"},
		{17, "TYPE_MATRIX4"},
		{18, "TYPE_TRANSFORM"},
		{19, "TYPE_ZERO"},
		{20, "TYPE_POINTER"},
		{21, "TYPE_FUNCTIONPOINTER"},
		{22, "TYPE_ARRAY"},
		{23, "TYPE_INPLACEARRAY"},
		{24, "TYPE_ENUM"},
		{25, "TYPE_STRUCT"},
		{26, "TYPE_SIMPLEARRAY"},
		{27, "TYPE_HOMOGENEOUSARRAY"},
		{28, "TYPE_VARIANT"},
		{29, "TYPE_CSTRING"},
		{30, "TYPE_ULONG"},
		{31, "TYPE_MAX"},
	};
	static const hkInternalClassEnumItem hkClassMemberFlagsEnumItems[] =
	{
		{1, "POINTER_OPTIONAL"},
		{2, "POINTER_VOIDSTAR"},
		{8, "ENUM_8"},
		{16, "ENUM_16"},
		{32, "ENUM_32"},
		{64, "ARRAY_RAWDATA"},
	};
	static const hkInternalClassEnumItem hkClassMemberRangeEnumItems[] =
	{
		{0, "INVALID"},
		{1, "DEFAULT"},
		{2, "ABS_MIN"},
		{4, "ABS_MAX"},
		{8, "SOFT_MIN"},
		{16, "SOFT_MAX"},
		{32, "RANGE_MAX"},
	};
	static const hkInternalClassEnum hkClassMemberEnums[] = {
		{"Type", hkClassMemberTypeEnumItems, 32, HK_NULL, 0 },
		{"Flags", hkClassMemberFlagsEnumItems, 6, HK_NULL, 0 },
		{"Range", hkClassMemberRangeEnumItems, 7, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkClassMemberTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[0]);
	extern const hkClassEnum* hkClassMemberFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[1]);
	extern const hkClassEnum* hkClassMemberRangeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[2]);
	static hkInternalClassMember hkClassMemberClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "class", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "enum", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, hkClassMemberTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "subtype", HK_NULL, hkClassMemberTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "cArraySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassMemberClass(
		"hkClassMember",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkClassMemberEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkClassMemberClass_Members),
		int(sizeof(hkClassMemberClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBitFieldClass_Members[] =
	{
		{ "words", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkBitFieldClass(
		"hkBitField",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBitFieldClass_Members),
		int(sizeof(hkBitFieldClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMonitorStreamStringMap_StringMapClass_Members[] =
	{
		{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "string", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMonitorStreamStringMapStringMapClass(
		"hkMonitorStreamStringMapStringMap",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMonitorStreamStringMap_StringMapClass_Members),
		int(sizeof(hkMonitorStreamStringMap_StringMapClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMonitorStreamStringMapClass_Members[] =
	{
		{ "map", &hkMonitorStreamStringMapStringMapClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkMonitorStreamStringMapClass(
		"hkMonitorStreamStringMap",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMonitorStreamStringMapClass_Members),
		int(sizeof(hkMonitorStreamStringMapClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkMonitorStreamFrameInfoAbsoluteTimeCounterEnumItems[] =
	{
		{0, "ABSOLUTE_TIME_TIMER_0"},
		{1, "ABSOLUTE_TIME_TIMER_1"},
		{0xffffffff, "ABSOLUTE_TIME_NOT_TIMED"},
	};
	static const hkInternalClassEnum hkMonitorStreamFrameInfoEnums[] = {
		{"AbsoluteTimeCounter", hkMonitorStreamFrameInfoAbsoluteTimeCounterEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMonitorStreamFrameInfoAbsoluteTimeCounterEnum = reinterpret_cast<const hkClassEnum*>(&hkMonitorStreamFrameInfoEnums[0]);
	static hkInternalClassMember hkMonitorStreamFrameInfoClass_Members[] =
	{
		{ "heading", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfTimer0", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfTimer1", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "absoluteTimeCounter", HK_NULL, hkMonitorStreamFrameInfoAbsoluteTimeCounterEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_32, 0, HK_NULL },
		{ "timerFactor0", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timerFactor1", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMonitorStreamFrameInfoClass(
		"hkMonitorStreamFrameInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMonitorStreamFrameInfoEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkMonitorStreamFrameInfoClass_Members),
		int(sizeof(hkMonitorStreamFrameInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkMultiThreadLockAccessTypeEnumItems[] =
	{
		{0, "HK_ACCESS_IGNORE"},
		{1, "HK_ACCESS_RO"},
		{2, "HK_ACCESS_RW"},
	};
	static const hkInternalClassEnumItem hkMultiThreadLockReadModeEnumItems[] =
	{
		{0, "THIS_OBJECT_ONLY"},
		{1, "RECURSIVE"},
	};
	static const hkInternalClassEnum hkMultiThreadLockEnums[] = {
		{"AccessType", hkMultiThreadLockAccessTypeEnumItems, 3, HK_NULL, 0 },
		{"ReadMode", hkMultiThreadLockReadModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMultiThreadLockAccessTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadLockEnums[0]);
	extern const hkClassEnum* hkMultiThreadLockReadModeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadLockEnums[1]);
	static hkInternalClassMember hkMultiThreadLockClass_Members[] =
	{
		{ "threadId", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "lockCount", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "lockBitStack", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkMultiThreadLockClass(
		"hkMultiThreadLock",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMultiThreadLockEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkMultiThreadLockClass_Members),
		int(sizeof(hkMultiThreadLockClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAabbClass_Members[] =
	{
		{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAabbClass(
		"hkAabb",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAabbClass_Members),
		int(sizeof(hkAabbClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkContactPointClass_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "separatingNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkContactPointClass(
		"hkContactPoint",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkContactPointClass_Members),
		int(sizeof(hkContactPointClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkContactPointMaterialFlagEnumEnumItems[] =
	{
		{1, "CONTACT_IS_NEW_AND_POTENTIAL"},
		{2, "CONTACT_USES_SOLVER_PATH2"},
	};
	static const hkInternalClassEnum hkContactPointMaterialEnums[] = {
		{"FlagEnum", hkContactPointMaterialFlagEnumEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkContactPointMaterialFlagEnumEnum = reinterpret_cast<const hkClassEnum*>(&hkContactPointMaterialEnums[0]);
	static hkInternalClassMember hkContactPointMaterialClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "restitution", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkContactPointMaterialClass(
		"hkContactPointMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkContactPointMaterialEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkContactPointMaterialClass_Members),
		int(sizeof(hkContactPointMaterialClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMotionStateClass_Members[] =
	{
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sweptTransform", &hkSweptTransformClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deltaAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationClass", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationRefOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkMotionStateClass(
		"hkMotionState",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMotionStateClass_Members),
		int(sizeof(hkMotionStateClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSphereClass_Members[] =
	{
		{ "pos", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSphereClass(
		"hkSphere",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSphereClass_Members),
		int(sizeof(hkSphereClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSweptTransformClass_Members[] =
	{
		{ "centerOfMass0", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "centerOfMass1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotation0", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotation1", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "centerOfMassLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSweptTransformClass(
		"hkSweptTransform",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSweptTransformClass_Members),
		int(sizeof(hkSweptTransformClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedFloatClass_Members[] =
	{
		{ "floats", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	hkClass hkxAnimatedFloatClass(
		"hkxAnimatedFloat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAnimatedFloatClass_Members),
		int(sizeof(hkxAnimatedFloatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedMatrixClass_Members[] =
	{
		{ "matrices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	hkClass hkxAnimatedMatrixClass(
		"hkxAnimatedMatrix",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAnimatedMatrixClass_Members),
		int(sizeof(hkxAnimatedMatrixClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxAnimatedQuaternionClass_Members[] =
	{
		{ "quaternions", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QUATERNION, 0, 0, 0, HK_NULL }
	};
	hkClass hkxAnimatedQuaternionClass(
		"hkxAnimatedQuaternion",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAnimatedQuaternionClass_Members),
		int(sizeof(hkxAnimatedQuaternionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedVectorClass_Members[] =
	{
		{ "vectors", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	hkClass hkxAnimatedVectorClass(
		"hkxAnimatedVector",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAnimatedVectorClass_Members),
		int(sizeof(hkxAnimatedVectorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkxAttributeHintEnumItems[] =
	{
		{0, "HINT_NONE"},
		{1, "HINT_IGNORE"},
		{2, "HINT_TRANSFORM"},
		{4, "HINT_SCALE"},
		{6, "HINT_TRANSFORM_AND_SCALE"},
		{8, "HINT_FLIP"},
	};
	static const hkInternalClassEnum hkxAttributeEnums[] = {
		{"Hint", hkxAttributeHintEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkxAttributeHintEnum = reinterpret_cast<const hkClassEnum*>(&hkxAttributeEnums[0]);
	static hkInternalClassMember hkxAttributeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxAttributeClass(
		"hkxAttribute",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxAttributeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxAttributeClass_Members),
		int(sizeof(hkxAttributeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxAttributeGroupClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attributes", &hkxAttributeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxAttributeGroupClass(
		"hkxAttributeGroup",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAttributeGroupClass_Members),
		int(sizeof(hkxAttributeGroupClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSparselyAnimatedBoolClass_Members[] =
	{
		{ "bools", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "times", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSparselyAnimatedBoolClass(
		"hkxSparselyAnimatedBool",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedBoolClass_Members),
		int(sizeof(hkxSparselyAnimatedBoolClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSparselyAnimatedEnumClass_Members[] =
	{
		{ "type", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSparselyAnimatedEnumClass(
		"hkxSparselyAnimatedEnum",
		&hkxSparselyAnimatedIntClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedEnumClass_Members),
		int(sizeof(hkxSparselyAnimatedEnumClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSparselyAnimatedIntClass_Members[] =
	{
		{ "ints", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "times", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSparselyAnimatedIntClass(
		"hkxSparselyAnimatedInt",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedIntClass_Members),
		int(sizeof(hkxSparselyAnimatedIntClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSparselyAnimatedString_StringTypeClass_Members[] =
	{
		{ "string", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSparselyAnimatedStringStringTypeClass(
		"hkxSparselyAnimatedStringStringType",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedString_StringTypeClass_Members),
		int(sizeof(hkxSparselyAnimatedString_StringTypeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSparselyAnimatedStringClass_Members[] =
	{
		{ "strings", &hkxSparselyAnimatedStringStringTypeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "times", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSparselyAnimatedStringClass(
		"hkxSparselyAnimatedString",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedStringClass_Members),
		int(sizeof(hkxSparselyAnimatedStringClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxCameraClass_Members[] =
	{
		{ "from", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "focus", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fov", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "far", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "near", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "leftHanded", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxCameraClass(
		"hkxCamera",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxCameraClass_Members),
		int(sizeof(hkxCameraClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxEnvironment_VariableClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxEnvironmentVariableClass(
		"hkxEnvironmentVariable",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxEnvironment_VariableClass_Members),
		int(sizeof(hkxEnvironment_VariableClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxEnvironmentClass_Members[] =
	{
		{ "variables", &hkxEnvironmentVariableClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxEnvironmentClass(
		"hkxEnvironment",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxEnvironmentClass_Members),
		int(sizeof(hkxEnvironmentClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxNode_AnnotationDataClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "description", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxNodeAnnotationDataClass(
		"hkxNodeAnnotationData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxNode_AnnotationDataClass_Members),
		int(sizeof(hkxNode_AnnotationDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxNodeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "object", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keyFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "children", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "annotations", &hkxNodeAnnotationDataClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "userProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "selected", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attributeGroups", &hkxAttributeGroupClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxNodeClass(
		"hkxNode",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxNodeClass_Members),
		int(sizeof(hkxNodeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkxLightLightTypeEnumItems[] =
	{
		{0, "POINT_LIGHT"},
		{1, "DIRECTIONAL_LIGHT"},
		{2, "SPOT_LIGHT"},
	};
	static const hkInternalClassEnum hkxLightEnums[] = {
		{"LightType", hkxLightLightTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkxLightLightTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxLightEnums[0]);
	static hkInternalClassMember hkxLightClass_Members[] =
	{
		{ "type", HK_NULL, hkxLightLightTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "direction", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "color", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxLightClass(
		"hkxLight",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxLightEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxLightClass_Members),
		int(sizeof(hkxLightClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkxMaterialTextureTypeEnumItems[] =
	{
		{0, "TEX_UNKNOWN"},
		{1, "TEX_DIFFUSE"},
		{2, "TEX_REFLECTION"},
		{3, "TEX_BUMP"},
		{4, "TEX_NORMAL"},
		{5, "TEX_DISPLACEMENT"},
	};
	static const hkInternalClassEnum hkxMaterialEnums[] = {
		{"TextureType", hkxMaterialTextureTypeEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkxMaterialTextureTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxMaterialEnums[0]);
	static hkInternalClassMember hkxMaterial_TextureStageClass_Members[] =
	{
		{ "texture", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "usageHint", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMaterialTextureStageClass(
		"hkxMaterialTextureStage",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxMaterial_TextureStageClass_Members),
		int(sizeof(hkxMaterial_TextureStageClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxMaterialClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stages", &hkxMaterialTextureStageClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "diffuseColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ambientColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "specularColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "emissiveColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "subMaterials", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "extraData", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMaterialClass(
		"hkxMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxMaterialEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxMaterialClass_Members),
		int(sizeof(hkxMaterialClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkxMaterialEffectEffectTypeEnumItems[] =
	{
		{0, "EFFECT_TYPE_INVALID"},
		{1, "EFFECT_TYPE_UNKNOWN"},
		{2, "EFFECT_TYPE_HLSL_FX"},
		{3, "EFFECT_TYPE_CG_FX"},
		{4, "EFFECT_TYPE_MAX_ID"},
	};
	static const hkInternalClassEnum hkxMaterialEffectEnums[] = {
		{"EffectType", hkxMaterialEffectEffectTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkxMaterialEffectEffectTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxMaterialEffectEnums[0]);
	static hkInternalClassMember hkxMaterialEffectClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, hkxMaterialEffectEffectTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMaterialEffectClass(
		"hkxMaterialEffect",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxMaterialEffectEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxMaterialEffectClass_Members),
		int(sizeof(hkxMaterialEffectClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxTextureFileClass_Members[] =
	{
		{ "filename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxTextureFileClass(
		"hkxTextureFile",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxTextureFileClass_Members),
		int(sizeof(hkxTextureFileClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxTextureInplaceClass_Members[] =
	{
		{ "fileType", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkxTextureInplaceClass(
		"hkxTextureInplace",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxTextureInplaceClass_Members),
		int(sizeof(hkxTextureInplaceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkxIndexBufferIndexTypeEnumItems[] =
	{
		{0, "INDEX_TYPE_INVALID"},
		{1, "INDEX_TYPE_TRI_LIST"},
		{2, "INDEX_TYPE_TRI_STRIP"},
		{3, "INDEX_TYPE_TRI_FAN"},
		{4, "INDEX_TYPE_MAX_ID"},
	};
	static const hkInternalClassEnum hkxIndexBufferEnums[] = {
		{"IndexType", hkxIndexBufferIndexTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkxIndexBufferIndexTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxIndexBufferEnums[0]);
	static hkInternalClassMember hkxIndexBufferClass_Members[] =
	{
		{ "indexType", HK_NULL, hkxIndexBufferIndexTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "vertexBaseOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxIndexBufferClass(
		"hkxIndexBuffer",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxIndexBufferEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxIndexBufferClass_Members),
		int(sizeof(hkxIndexBufferClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxMeshClass_Members[] =
	{
		{ "sections", &hkxMeshSectionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMeshClass(
		"hkxMesh",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxMeshClass_Members),
		int(sizeof(hkxMeshClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxMeshSectionClass_Members[] =
	{
		{ "vertexBuffer", &hkxVertexBufferClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "indexBuffers", &hkxIndexBufferClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "material", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMeshSectionClass(
		"hkxMeshSection",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxMeshSectionClass_Members),
		int(sizeof(hkxMeshSectionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexBufferClass_Members[] =
	{
		{ "vertexData", HK_NULL, HK_NULL, hkClassMember::TYPE_HOMOGENEOUSARRAY, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "format", &hkxVertexFormatClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexBufferClass(
		"hkxVertexBuffer",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexBufferClass_Members),
		int(sizeof(hkxVertexBufferClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexFormatClass_Members[] =
	{
		{ "stride", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normalOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tangentOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "binormalOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numBonesPerVertex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneIndexOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneWeightOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numTextureChannels", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tFloatCoordOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tQuantizedCoordOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "colorOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexFormatClass(
		"hkxVertexFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexFormatClass_Members),
		int(sizeof(hkxVertexFormatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexP4N4C1T2Class_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "diffuse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "u", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "v", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "padding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexP4N4C1T2Class(
		"hkxVertexP4N4C1T2",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexP4N4C1T2Class_Members),
		int(sizeof(hkxVertexP4N4C1T2Class_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexP4N4T4B4C1T2Class_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tangent", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "binormal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "diffuse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "u", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "v", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "padding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexP4N4T4B4C1T2Class(
		"hkxVertexP4N4T4B4C1T2",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexP4N4T4B4C1T2Class_Members),
		int(sizeof(hkxVertexP4N4T4B4C1T2Class_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexP4N4T4B4W4I4C1Q2Class_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tangent", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "binormal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weights", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indices", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "diffuse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qu", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qv", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexP4N4T4B4W4I4C1Q2Class(
		"hkxVertexP4N4T4B4W4I4C1Q2",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexP4N4T4B4W4I4C1Q2Class_Members),
		int(sizeof(hkxVertexP4N4T4B4W4I4C1Q2Class_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexP4N4T4B4W4I4Q4Class_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tangent", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "binormal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weights", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indices", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qu0", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "qu1", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkxVertexP4N4T4B4W4I4Q4Class(
		"hkxVertexP4N4T4B4W4I4Q4",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexP4N4T4B4W4I4Q4Class_Members),
		int(sizeof(hkxVertexP4N4T4B4W4I4Q4Class_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxVertexP4N4W4I4C1Q2Class_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weights", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indices", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "diffuse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qu", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qv", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexP4N4W4I4C1Q2Class(
		"hkxVertexP4N4W4I4C1Q2",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexP4N4W4I4C1Q2Class_Members),
		int(sizeof(hkxVertexP4N4W4I4C1Q2Class_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkxSceneClass_Members[] =
	{
		{ "modeller", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "asset", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sceneLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rootNode", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "cameras", &hkxCameraClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "lights", &hkxLightClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "meshes", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materials", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "inplaceTextures", &hkxTextureInplaceClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "externalTextures", &hkxTextureFileClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "skinBindings", &hkxSkinBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "appliedTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkxScene_DefaultStruct
		{
			int s_defaultOffsets[12];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkMatrix3 m_appliedTransform;
		};
		const hkxScene_DefaultStruct hkxScene_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkxScene_DefaultStruct,m_appliedTransform)},
			{1,0,0,0,0,1,0,0,0,0,1,0}
		};
	}
	hkClass hkxSceneClass(
		"hkxScene",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSceneClass_Members),
		int(sizeof(hkxSceneClass_Members)/sizeof(hkInternalClassMember)),
		&hkxScene_Default
		);
	static hkInternalClassMember hkxSkinBindingClass_Members[] =
	{
		{ "mesh", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mapping", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "bindPose", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "initSkinTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxSkinBindingClass(
		"hkxSkinBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxSkinBindingClass_Members),
		int(sizeof(hkxSkinBindingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPackfileHeaderClass_Members[] =
	{
		{ "magic", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "userTag", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fileVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "layoutRules", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "numSections", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsSectionIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsSectionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsClassNameSectionIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsClassNameSectionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 16, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkPackfileHeaderClass(
		"hkPackfileHeader",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPackfileHeaderClass_Members),
		int(sizeof(hkPackfileHeaderClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPackfileSectionHeaderClass_Members[] =
	{
		{ "sectionTag", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 19, 0, 0, HK_NULL },
		{ "nullByte", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "absoluteDataStart", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "localFixupsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "globalFixupsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "virtualFixupsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "exportsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "importsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPackfileSectionHeaderClass(
		"hkPackfileSectionHeader",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPackfileSectionHeaderClass_Members),
		int(sizeof(hkPackfileSectionHeaderClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRootLevelContainer_NamedVariantClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "className", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "variant", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRootLevelContainerNamedVariantClass(
		"hkRootLevelContainerNamedVariant",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRootLevelContainer_NamedVariantClass_Members),
		int(sizeof(hkRootLevelContainer_NamedVariantClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRootLevelContainerClass_Members[] =
	{
		{ "namedVariants", &hkRootLevelContainerNamedVariantClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkRootLevelContainerClass(
		"hkRootLevelContainer",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRootLevelContainerClass_Members),
		int(sizeof(hkRootLevelContainerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVersioningExceptionsArray_VersioningExceptionClass_Members[] =
	{
		{ "className", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "oldSignature", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "newSignature", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVersioningExceptionsArrayVersioningExceptionClass(
		"hkVersioningExceptionsArrayVersioningException",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVersioningExceptionsArray_VersioningExceptionClass_Members),
		int(sizeof(hkVersioningExceptionsArray_VersioningExceptionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVersioningExceptionsArrayClass_Members[] =
	{
		{ "exceptions", &hkVersioningExceptionsArrayVersioningExceptionClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkVersioningExceptionsArrayClass(
		"hkVersioningExceptionsArray",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVersioningExceptionsArrayClass_Members),
		int(sizeof(hkVersioningExceptionsArrayClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollInstanceClass_Members[] =
	{
		{ "rigidBodies", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "constraints", &hkConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "skeleton", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollInstanceClass(
		"hkRagdollInstance",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollInstanceClass_Members),
		int(sizeof(hkRagdollInstanceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkCdBodyClass_Members[] =
	{
		{ "shape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "shapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motion", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "parent", &hkCdBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkCdBodyClass(
		"hkCdBody",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCdBodyClass_Members),
		int(sizeof(hkCdBodyClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkCollidableClass_Members[] =
	{
		{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseHandle", &hkTypedBroadPhaseHandleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "allowedPenetrationDepth", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkCollidableClass(
		"hkCollidable",
		&hkCdBodyClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCollidableClass_Members),
		int(sizeof(hkCollidableClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkShapeCollectionFilterClass(
		"hkShapeCollectionFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkTypedBroadPhaseHandleClass_Members[] =
	{
		{ "type", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectQualityType", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTypedBroadPhaseHandleClass(
		"hkTypedBroadPhaseHandle",
		&hkBroadPhaseHandleClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTypedBroadPhaseHandleClass_Members),
		int(sizeof(hkTypedBroadPhaseHandleClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkCollidableCollidableFilterClass(
		"hkCollidableCollidableFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkCollisionFilterClass(
		"hkCollisionFilter",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		4,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static const hkInternalClassEnumItem hkConvexListFilterConvexListCollisionTypeEnumItems[] =
	{
		{0, "TREAT_CONVEX_LIST_AS_NORMAL"},
		{1, "TREAT_CONVEX_LIST_AS_LIST"},
		{2, "TREAT_CONVEX_LIST_AS_CONVEX"},
	};
	static const hkInternalClassEnum hkConvexListFilterEnums[] = {
		{"ConvexListCollisionType", hkConvexListFilterConvexListCollisionTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConvexListFilterConvexListCollisionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkConvexListFilterEnums[0]);
	hkClass hkConvexListFilterClass(
		"hkConvexListFilter",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConvexListFilterEnums),
		1,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkRayCollidableFilterClass(
		"hkRayCollidableFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkDefaultConvexListFilterClass(
		"hkDefaultConvexListFilter",
		&hkConvexListFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkGroupFilterClass_Members[] =
	{
		{ "nextFreeSystemGroup", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionLookupTable", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 32, 0, 0, HK_NULL }
	};
	hkClass hkGroupFilterClass(
		"hkGroupFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkGroupFilterClass_Members),
		int(sizeof(hkGroupFilterClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkCollisionFilterListClass_Members[] =
	{
		{ "collisionFilters", &hkCollisionFilterClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkCollisionFilterListClass(
		"hkCollisionFilterList",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCollisionFilterListClass_Members),
		int(sizeof(hkCollisionFilterListClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkNullCollisionFilterClass(
		"hkNullCollisionFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkRayShapeCollectionFilterClass(
		"hkRayShapeCollectionFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkShapeClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkShapeClass(
		"hkShape",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkShapeClass_Members),
		int(sizeof(hkShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkShapeContainerClass(
		"hkShapeContainer",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkSingleShapeContainerClass_Members[] =
	{
		{ "childShape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkSingleShapeContainerClass(
		"hkSingleShapeContainer",
		&hkShapeContainerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSingleShapeContainerClass_Members),
		int(sizeof(hkSingleShapeContainerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkShapeRayCastInputClass_Members[] =
	{
		{ "from", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "to", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "filterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rayShapeCollectionFilter", &hkRayShapeCollectionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkShapeRayCastInputClass(
		"hkShapeRayCastInput",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkShapeRayCastInputClass_Members),
		int(sizeof(hkShapeRayCastInputClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBoxShapeClass_Members[] =
	{
		{ "halfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBoxShapeClass(
		"hkBoxShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBoxShapeClass_Members),
		int(sizeof(hkBoxShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBvShapeClass_Members[] =
	{
		{ "boundingVolumeShape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "childShape", &hkSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBvShapeClass(
		"hkBvShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBvShapeClass_Members),
		int(sizeof(hkBvShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBvTreeShapeClass_Members[] =
	{
		{ "child", &hkSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBvTreeShapeClass(
		"hkBvTreeShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBvTreeShapeClass_Members),
		int(sizeof(hkBvTreeShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkCapsuleShapeRayHitTypeEnumItems[] =
	{
		{0, "HIT_CAP0"},
		{1, "HIT_CAP1"},
		{2, "HIT_BODY"},
	};
	static const hkInternalClassEnum hkCapsuleShapeEnums[] = {
		{"RayHitType", hkCapsuleShapeRayHitTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkCapsuleShapeRayHitTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkCapsuleShapeEnums[0]);
	static hkInternalClassMember hkCapsuleShapeClass_Members[] =
	{
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkCapsuleShapeClass(
		"hkCapsuleShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkCapsuleShapeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkCapsuleShapeClass_Members),
		int(sizeof(hkCapsuleShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkShapeCollectionClass_Members[] =
	{
		{ "disableWelding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkShapeCollectionClass(
		"hkShapeCollection",
		&hkShapeClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkShapeCollectionClass_Members),
		int(sizeof(hkShapeCollectionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexShapeClass_Members[] =
	{
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexShapeClass(
		"hkConvexShape",
		&hkSphereRepShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexShapeClass_Members),
		int(sizeof(hkConvexShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexListShapeClass_Members[] =
	{
		{ "minDistanceToUseConvexHullForGetClosestPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useCachedAabb", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childShapes", &hkConvexShapeClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkConvexListShape_DefaultStruct
		{
			int s_defaultOffsets[5];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			bool m_useCachedAabb;
		};
		const hkConvexListShape_DefaultStruct hkConvexListShape_Default =
		{
			{-1,-1,-1,HK_OFFSET_OF(hkConvexListShape_DefaultStruct,m_useCachedAabb),-1},
			false
		};
	}
	hkClass hkConvexListShapeClass(
		"hkConvexListShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexListShapeClass_Members),
		int(sizeof(hkConvexListShapeClass_Members)/sizeof(hkInternalClassMember)),
		&hkConvexListShape_Default
		);
	static hkInternalClassMember hkConvexPieceMeshShapeClass_Members[] =
	{
		{ "convexPieceStream", &hkConvexPieceStreamDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "displayMesh", &hkShapeCollectionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexPieceMeshShapeClass(
		"hkConvexPieceMeshShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexPieceMeshShapeClass_Members),
		int(sizeof(hkConvexPieceMeshShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexTransformShapeClass_Members[] =
	{
		{ "childShape", &hkSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexTransformShapeClass(
		"hkConvexTransformShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexTransformShapeClass_Members),
		int(sizeof(hkConvexTransformShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexTranslateShapeClass_Members[] =
	{
		{ "childShape", &hkSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "translation", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexTranslateShapeClass(
		"hkConvexTranslateShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexTranslateShapeClass_Members),
		int(sizeof(hkConvexTranslateShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexVerticesShape_FourVectorsClass_Members[] =
	{
		{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexVerticesShapeFourVectorsClass(
		"hkConvexVerticesShapeFourVectors",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexVerticesShape_FourVectorsClass_Members),
		int(sizeof(hkConvexVerticesShape_FourVectorsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexVerticesShapeClass_Members[] =
	{
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotatedVertices", &hkConvexVerticesShapeFourVectorsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeEquations", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexVerticesShapeClass(
		"hkConvexVerticesShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexVerticesShapeClass_Members),
		int(sizeof(hkConvexVerticesShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkCylinderShapeVertexIdEncodingEnumItems[] =
	{
		{7, "VERTEX_ID_ENCODING_IS_BASE_A_SHIFT"},
		{6, "VERTEX_ID_ENCODING_SIN_SIGN_SHIFT"},
		{5, "VERTEX_ID_ENCODING_COS_SIGN_SHIFT"},
		{4, "VERTEX_ID_ENCODING_IS_SIN_LESSER_SHIFT"},
		{0x0f, "VERTEX_ID_ENCODING_VALUE_MASK"},
	};
	static const hkInternalClassEnum hkCylinderShapeEnums[] = {
		{"VertexIdEncoding", hkCylinderShapeVertexIdEncodingEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkCylinderShapeVertexIdEncodingEnum = reinterpret_cast<const hkClassEnum*>(&hkCylinderShapeEnums[0]);
	static hkInternalClassMember hkCylinderShapeClass_Members[] =
	{
		{ "cylRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cylBaseRadiusFactorForHeightFieldCollisions", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpendicular1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpendicular2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkCylinderShape_DefaultStruct
		{
			int s_defaultOffsets[6];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_cylBaseRadiusFactorForHeightFieldCollisions;
		};
		const hkCylinderShape_DefaultStruct hkCylinderShape_Default =
		{
			{-1,HK_OFFSET_OF(hkCylinderShape_DefaultStruct,m_cylBaseRadiusFactorForHeightFieldCollisions),-1,-1,-1,-1},
			0.8f
		};
	}
	hkClass hkCylinderShapeClass(
		"hkCylinderShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkCylinderShapeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkCylinderShapeClass_Members),
		int(sizeof(hkCylinderShapeClass_Members)/sizeof(hkInternalClassMember)),
		&hkCylinderShape_Default
		);
	static const hkInternalClassEnumItem hkExtendedMeshShapeIndexStridingTypeEnumItems[] =
	{
		{0, "INDICES_INVALID"},
		{1, "INDICES_INT16"},
		{2, "INDICES_INT32"},
		{3, "INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkExtendedMeshShapeMaterialIndexStridingTypeEnumItems[] =
	{
		{0, "MATERIAL_INDICES_INVALID"},
		{1, "MATERIAL_INDICES_INT8"},
		{2, "MATERIAL_INDICES_INT16"},
		{3, "MATERIAL_INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkExtendedMeshShapeSubpartTypeEnumItems[] =
	{
		{0, "SUBPART_TRIANGLES"},
		{1, "SUBPART_SHAPE"},
	};
	static const hkInternalClassEnum hkExtendedMeshShapeEnums[] = {
		{"IndexStridingType", hkExtendedMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"MaterialIndexStridingType", hkExtendedMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"SubpartType", hkExtendedMeshShapeSubpartTypeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkExtendedMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkExtendedMeshShapeEnums[0]);
	extern const hkClassEnum* hkExtendedMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkExtendedMeshShapeEnums[1]);
	extern const hkClassEnum* hkExtendedMeshShapeSubpartTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkExtendedMeshShapeEnums[2]);
	static hkInternalClassMember hkExtendedMeshShape_SubpartClass_Members[] =
	{
		{ "type", HK_NULL, hkExtendedMeshShapeSubpartTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "materialIndexStridingType", HK_NULL, hkExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkExtendedMeshShapeSubpartClass(
		"hkExtendedMeshShapeSubpart",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkExtendedMeshShape_SubpartClass_Members),
		int(sizeof(hkExtendedMeshShape_SubpartClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkExtendedMeshShape_TrianglesSubpartClass_Members[] =
	{
		{ "numTriangleShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "stridingType", HK_NULL, hkExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkExtendedMeshShapeTrianglesSubpartClass(
		"hkExtendedMeshShapeTrianglesSubpart",
		&hkExtendedMeshShapeSubpartClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkExtendedMeshShape_TrianglesSubpartClass_Members),
		int(sizeof(hkExtendedMeshShape_TrianglesSubpartClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkExtendedMeshShape_ShapesSubpartClass_Members[] =
	{
		{ "childShapes", &hkConvexShapeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "offsetSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkExtendedMeshShapeShapesSubpartClass(
		"hkExtendedMeshShapeShapesSubpart",
		&hkExtendedMeshShapeSubpartClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkExtendedMeshShape_ShapesSubpartClass_Members),
		int(sizeof(hkExtendedMeshShape_ShapesSubpartClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkExtendedMeshShapeClass_Members[] =
	{
		{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "trianglesSubparts", &hkExtendedMeshShapeTrianglesSubpartClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "shapesSubparts", &hkExtendedMeshShapeShapesSubpartClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL }
	};
	hkClass hkExtendedMeshShapeClass(
		"hkExtendedMeshShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkExtendedMeshShapeEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkExtendedMeshShapeClass_Members),
		int(sizeof(hkExtendedMeshShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkFastMeshShapeClass(
		"hkFastMeshShape",
		&hkMeshShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkHeightFieldShapeClass(
		"hkHeightFieldShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkListShape_ChildInfoClass_Members[] =
	{
		{ "shape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkListShapeChildInfoClass(
		"hkListShapeChildInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkListShape_ChildInfoClass_Members),
		int(sizeof(hkListShape_ChildInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkListShapeClass_Members[] =
	{
		{ "childInfo", &hkListShapeChildInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkListShapeClass(
		"hkListShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkListShapeClass_Members),
		int(sizeof(hkListShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMeshMaterialClass_Members[] =
	{
		{ "filterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMeshMaterialClass(
		"hkMeshMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMeshMaterialClass_Members),
		int(sizeof(hkMeshMaterialClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkMeshShapeIndexStridingTypeEnumItems[] =
	{
		{0, "INDICES_INVALID"},
		{1, "INDICES_INT16"},
		{2, "INDICES_INT32"},
		{3, "INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkMeshShapeMaterialIndexStridingTypeEnumItems[] =
	{
		{0, "MATERIAL_INDICES_INVALID"},
		{1, "MATERIAL_INDICES_INT8"},
		{2, "MATERIAL_INDICES_INT16"},
		{3, "MATERIAL_INDICES_MAX_ID"},
	};
	static const hkInternalClassEnum hkMeshShapeEnums[] = {
		{"IndexStridingType", hkMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"MaterialIndexStridingType", hkMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMeshShapeEnums[0]);
	extern const hkClassEnum* hkMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMeshShapeEnums[1]);
	static hkInternalClassMember hkMeshShape_SubpartClass_Members[] =
	{
		{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "stridingType", HK_NULL, hkMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "materialIndexStridingType", HK_NULL, hkMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMeshShapeSubpartClass(
		"hkMeshShapeSubpart",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMeshShape_SubpartClass_Members),
		int(sizeof(hkMeshShape_SubpartClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMeshShapeClass_Members[] =
	{
		{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "subparts", &hkMeshShapeSubpartClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL }
	};
	hkClass hkMeshShapeClass(
		"hkMeshShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMeshShapeEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkMeshShapeClass_Members),
		int(sizeof(hkMeshShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMoppBvTreeShapeClass_Members[] =
	{
		{ "code", &hkMoppCodeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkMoppBvTreeShapeClass(
		"hkMoppBvTreeShape",
		&hkBvTreeShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMoppBvTreeShapeClass_Members),
		int(sizeof(hkMoppBvTreeShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMultiRayShape_RayClass_Members[] =
	{
		{ "start", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "end", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMultiRayShapeRayClass(
		"hkMultiRayShapeRay",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMultiRayShape_RayClass_Members),
		int(sizeof(hkMultiRayShape_RayClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMultiRayShapeClass_Members[] =
	{
		{ "rays", &hkMultiRayShapeRayClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rayPenetrationDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMultiRayShapeClass(
		"hkMultiRayShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMultiRayShapeClass_Members),
		int(sizeof(hkMultiRayShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMultiSphereShapeClass_Members[] =
	{
		{ "numSpheres", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spheres", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 8, 0, 0, HK_NULL }
	};
	hkClass hkMultiSphereShapeClass(
		"hkMultiSphereShape",
		&hkSphereRepShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMultiSphereShapeClass_Members),
		int(sizeof(hkMultiSphereShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkPhantomCallbackShapeClass(
		"hkPhantomCallbackShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkPlaneShapeClass_Members[] =
	{
		{ "plane", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPlaneShapeClass(
		"hkPlaneShape",
		&hkHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPlaneShapeClass_Members),
		int(sizeof(hkPlaneShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSampledHeightFieldShapeClass_Members[] =
	{
		{ "xRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "zRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "heightCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "intToFloatScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntOffsetFloorCorrected", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSampledHeightFieldShapeClass(
		"hkSampledHeightFieldShape",
		&hkHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSampledHeightFieldShapeClass_Members),
		int(sizeof(hkSampledHeightFieldShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSimpleMeshShape_TriangleClass_Members[] =
	{
		{ "a", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "b", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "c", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSimpleMeshShapeTriangleClass(
		"hkSimpleMeshShapeTriangle",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSimpleMeshShape_TriangleClass_Members),
		int(sizeof(hkSimpleMeshShape_TriangleClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSimpleMeshShapeClass_Members[] =
	{
		{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "triangles", &hkSimpleMeshShapeTriangleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSimpleMeshShapeClass(
		"hkSimpleMeshShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSimpleMeshShapeClass_Members),
		int(sizeof(hkSimpleMeshShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkSphereShapeClass(
		"hkSphereShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkSphereRepShapeClass(
		"hkSphereRepShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkStorageMeshShape_SubpartStorageClass_Members[] =
	{
		{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkStorageMeshShapeSubpartStorageClass(
		"hkStorageMeshShapeSubpartStorage",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStorageMeshShape_SubpartStorageClass_Members),
		int(sizeof(hkStorageMeshShape_SubpartStorageClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStorageMeshShapeClass_Members[] =
	{
		{ "storage", &hkStorageMeshShapeSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkStorageMeshShapeClass(
		"hkStorageMeshShape",
		&hkMeshShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStorageMeshShapeClass_Members),
		int(sizeof(hkStorageMeshShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStorageSampledHeightFieldShapeClass_Members[] =
	{
		{ "storage", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "triangleFlip", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStorageSampledHeightFieldShapeClass(
		"hkStorageSampledHeightFieldShape",
		&hkSampledHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStorageSampledHeightFieldShapeClass_Members),
		int(sizeof(hkStorageSampledHeightFieldShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTransformShapeClass_Members[] =
	{
		{ "childShape", &hkSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTransformShapeClass(
		"hkTransformShape",
		&hkShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTransformShapeClass_Members),
		int(sizeof(hkTransformShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTriangleShapeClass_Members[] =
	{
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexC", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTriangleShapeClass(
		"hkTriangleShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTriangleShapeClass_Members),
		int(sizeof(hkTriangleShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTriSampledHeightFieldBvTreeShapeClass_Members[] =
	{
		{ "wantAabbRejectionTest", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTriSampledHeightFieldBvTreeShapeClass(
		"hkTriSampledHeightFieldBvTreeShape",
		&hkBvTreeShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTriSampledHeightFieldBvTreeShapeClass_Members),
		int(sizeof(hkTriSampledHeightFieldBvTreeShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTriSampledHeightFieldCollectionClass_Members[] =
	{
		{ "heightfield", &hkSampledHeightFieldShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTriSampledHeightFieldCollectionClass(
		"hkTriSampledHeightFieldCollection",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTriSampledHeightFieldCollectionClass_Members),
		int(sizeof(hkTriSampledHeightFieldCollectionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkConstraintAtomAtomTypeEnumItems[] =
	{
		{0, "TYPE_INVALID"},
		{1, "TYPE_BRIDGE"},
		{2, "TYPE_SET_LOCAL_TRANSFORMS"},
		{3, "TYPE_SET_LOCAL_TRANSLATIONS"},
		{4, "TYPE_SET_LOCAL_ROTATIONS"},
		{5, "TYPE_BALL_SOCKET"},
		{6, "TYPE_STIFF_SPRING"},
		{7, "TYPE_LIN"},
		{8, "TYPE_LIN_SOFT"},
		{9, "TYPE_LIN_LIMIT"},
		{10, "TYPE_LIN_FRICTION"},
		{11, "TYPE_LIN_MOTOR"},
		{12, "TYPE_2D_ANG"},
		{13, "TYPE_ANG"},
		{14, "TYPE_ANG_LIMIT"},
		{15, "TYPE_TWIST_LIMIT"},
		{16, "TYPE_CONE_LIMIT"},
		{17, "TYPE_ANG_FRICTION"},
		{18, "TYPE_ANG_MOTOR"},
		{19, "TYPE_RAGDOLL_MOTOR"},
		{20, "TYPE_PULLEY"},
		{21, "TYPE_OVERWRITE_PIVOT"},
		{22, "TYPE_CONTACT"},
		{23, "TYPE_MODIFIER_SOFT_CONTACT"},
		{24, "TYPE_MODIFIER_MASS_CHANGER"},
		{25, "TYPE_MODIFIER_VISCOUS_SURFACE"},
		{26, "TYPE_MODIFIER_MOVING_SURFACE"},
		{27, "TYPE_MAX"},
	};
	static const hkInternalClassEnumItem hkConstraintAtomCallbackRequestEnumItems[] =
	{
		{0, "CALLBACK_REQUEST_NONE"},
		{1, "CALLBACK_REQUEST_CONTACT_POINT"},
		{2, "CALLBACK_REQUEST_SETUP_PPU_ONLY"},
	};
	static const hkInternalClassEnum hkConstraintAtomEnums[] = {
		{"AtomType", hkConstraintAtomAtomTypeEnumItems, 28, HK_NULL, 0 },
		{"CallbackRequest", hkConstraintAtomCallbackRequestEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintAtomAtomTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintAtomEnums[0]);
	extern const hkClassEnum* hkConstraintAtomCallbackRequestEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintAtomEnums[1]);
	static hkInternalClassMember hkConstraintAtomClass_Members[] =
	{
		{ "type", HK_NULL, hkConstraintAtomAtomTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_16, 0, HK_NULL }
	};
	hkClass hkConstraintAtomClass(
		"hkConstraintAtom",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConstraintAtomEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkConstraintAtomClass_Members),
		int(sizeof(hkConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBridgeConstraintAtomClass_Members[] =
	{
		{ "buildJacobianFunc", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "constraintData", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkBridgeConstraintAtomClass(
		"hkBridgeConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBridgeConstraintAtomClass_Members),
		int(sizeof(hkBridgeConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBridgeAtomsClass_Members[] =
	{
		{ "bridgeAtom", &hkBridgeConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBridgeAtomsClass(
		"hkBridgeAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBridgeAtomsClass_Members),
		int(sizeof(hkBridgeAtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkBallSocketConstraintAtomClass(
		"hkBallSocketConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkStiffSpringConstraintAtomClass_Members[] =
	{
		{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStiffSpringConstraintAtomClass(
		"hkStiffSpringConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStiffSpringConstraintAtomClass_Members),
		int(sizeof(hkStiffSpringConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSetLocalTransformsConstraintAtomClass_Members[] =
	{
		{ "transformA", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transformB", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSetLocalTransformsConstraintAtomClass(
		"hkSetLocalTransformsConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSetLocalTransformsConstraintAtomClass_Members),
		int(sizeof(hkSetLocalTransformsConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSetLocalTranslationsConstraintAtomClass_Members[] =
	{
		{ "translationA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "translationB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSetLocalTranslationsConstraintAtomClass(
		"hkSetLocalTranslationsConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSetLocalTranslationsConstraintAtomClass_Members),
		int(sizeof(hkSetLocalTranslationsConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSetLocalRotationsConstraintAtomClass_Members[] =
	{
		{ "rotationA", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationB", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSetLocalRotationsConstraintAtomClass(
		"hkSetLocalRotationsConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSetLocalRotationsConstraintAtomClass_Members),
		int(sizeof(hkSetLocalRotationsConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkOverwritePivotConstraintAtomClass_Members[] =
	{
		{ "copyToPivotBFromPivotA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkOverwritePivotConstraintAtomClass(
		"hkOverwritePivotConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkOverwritePivotConstraintAtomClass_Members),
		int(sizeof(hkOverwritePivotConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinConstraintAtomClass(
		"hkLinConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinConstraintAtomClass_Members),
		int(sizeof(hkLinConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinSoftConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinSoftConstraintAtomClass(
		"hkLinSoftConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinSoftConstraintAtomClass_Members),
		int(sizeof(hkLinSoftConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinLimitConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinLimitConstraintAtomClass(
		"hkLinLimitConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinLimitConstraintAtomClass_Members),
		int(sizeof(hkLinLimitConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hk2dAngConstraintAtomClass_Members[] =
	{
		{ "freeRotationAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hk2dAngConstraintAtomClass(
		"hk2dAngConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hk2dAngConstraintAtomClass_Members),
		int(sizeof(hk2dAngConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAngConstraintAtomClass_Members[] =
	{
		{ "firstConstrainedAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numConstrainedAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAngConstraintAtomClass(
		"hkAngConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAngConstraintAtomClass_Members),
		int(sizeof(hkAngConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAngLimitConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "limitAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkAngLimitConstraintAtom_DefaultStruct
		{
			int s_defaultOffsets[5];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_angularLimitsTauFactor;
		};
		const hkAngLimitConstraintAtom_DefaultStruct hkAngLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkAngLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1.0
		};
	}
	hkClass hkAngLimitConstraintAtomClass(
		"hkAngLimitConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAngLimitConstraintAtomClass_Members),
		int(sizeof(hkAngLimitConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		&hkAngLimitConstraintAtom_Default
		);
	static hkInternalClassMember hkTwistLimitConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkTwistLimitConstraintAtom_DefaultStruct
		{
			int s_defaultOffsets[6];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_angularLimitsTauFactor;
		};
		const hkTwistLimitConstraintAtom_DefaultStruct hkTwistLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,-1,HK_OFFSET_OF(hkTwistLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1.0
		};
	}
	hkClass hkTwistLimitConstraintAtomClass(
		"hkTwistLimitConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTwistLimitConstraintAtomClass_Members),
		int(sizeof(hkTwistLimitConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		&hkTwistLimitConstraintAtom_Default
		);
	static const hkInternalClassEnumItem hkConeLimitConstraintAtomMeasurementModeEnumItems[] =
	{
		{0, "ZERO_WHEN_VECTORS_ALIGNED"},
		{1, "ZERO_WHEN_VECTORS_PERPENDICULAR"},
	};
	static const hkInternalClassEnum hkConeLimitConstraintAtomEnums[] = {
		{"MeasurementMode", hkConeLimitConstraintAtomMeasurementModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConeLimitConstraintAtomMeasurementModeEnum = reinterpret_cast<const hkClassEnum*>(&hkConeLimitConstraintAtomEnums[0]);
	static hkInternalClassMember hkConeLimitConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistAxisInA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angleMeasurementMode", HK_NULL, hkConeLimitConstraintAtomMeasurementModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkConeLimitConstraintAtom_DefaultStruct
		{
			int s_defaultOffsets[7];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_angularLimitsTauFactor;
		};
		const hkConeLimitConstraintAtom_DefaultStruct hkConeLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkConeLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1.0
		};
	}
	hkClass hkConeLimitConstraintAtomClass(
		"hkConeLimitConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConeLimitConstraintAtomEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkConeLimitConstraintAtomClass_Members),
		int(sizeof(hkConeLimitConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		&hkConeLimitConstraintAtom_Default
		);
	static hkInternalClassMember hkAngFrictionConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "firstFrictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numFrictionAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAngFrictionConstraintAtomClass(
		"hkAngFrictionConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAngFrictionConstraintAtomClass_Members),
		int(sizeof(hkAngFrictionConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAngMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetAngleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "correspondingAngLimitSolverResultOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkAngMotorConstraintAtomClass(
		"hkAngMotorConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAngMotorConstraintAtomClass_Members),
		int(sizeof(hkAngMotorConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetAnglesOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetFrameAinB", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motors", &hkConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, 0, HK_NULL }
	};
	hkClass hkRagdollMotorConstraintAtomClass(
		"hkRagdollMotorConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollMotorConstraintAtomClass_Members),
		int(sizeof(hkRagdollMotorConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinFrictionConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinFrictionConstraintAtomClass(
		"hkLinFrictionConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinFrictionConstraintAtomClass_Members),
		int(sizeof(hkLinFrictionConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetPositionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinMotorConstraintAtomClass(
		"hkLinMotorConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinMotorConstraintAtomClass_Members),
		int(sizeof(hkLinMotorConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPulleyConstraintAtomClass_Members[] =
	{
		{ "fixedPivotAinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fixedPivotBinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ropeLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "leverageOnBodyB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPulleyConstraintAtomClass(
		"hkPulleyConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPulleyConstraintAtomClass_Members),
		int(sizeof(hkPulleyConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkModifierConstraintAtomClass_Members[] =
	{
		{ "modifierAtomSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "child", &hkConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkModifierConstraintAtomClass(
		"hkModifierConstraintAtom",
		&hkConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkModifierConstraintAtomClass_Members),
		int(sizeof(hkModifierConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSoftContactModifierConstraintAtomClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAcceleration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSoftContactModifierConstraintAtomClass(
		"hkSoftContactModifierConstraintAtom",
		&hkModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSoftContactModifierConstraintAtomClass_Members),
		int(sizeof(hkSoftContactModifierConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMassChangerModifierConstraintAtomClass_Members[] =
	{
		{ "factorA", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "factorB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMassChangerModifierConstraintAtomClass(
		"hkMassChangerModifierConstraintAtom",
		&hkModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMassChangerModifierConstraintAtomClass_Members),
		int(sizeof(hkMassChangerModifierConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkViscousSurfaceModifierConstraintAtomClass(
		"hkViscousSurfaceModifierConstraintAtom",
		&hkModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkMovingSurfaceModifierConstraintAtomClass_Members[] =
	{
		{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMovingSurfaceModifierConstraintAtomClass(
		"hkMovingSurfaceModifierConstraintAtom",
		&hkModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMovingSurfaceModifierConstraintAtomClass_Members),
		int(sizeof(hkMovingSurfaceModifierConstraintAtomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkActionClass_Members[] =
	{
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "island", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkActionClass(
		"hkAction",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkActionClass_Members),
		int(sizeof(hkActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkArrayActionClass_Members[] =
	{
		{ "entities", &hkEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkArrayActionClass(
		"hkArrayAction",
		&hkActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkArrayActionClass_Members),
		int(sizeof(hkArrayActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBinaryActionClass_Members[] =
	{
		{ "entityA", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "entityB", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkBinaryActionClass(
		"hkBinaryAction",
		&hkActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBinaryActionClass_Members),
		int(sizeof(hkBinaryActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkUnaryActionClass_Members[] =
	{
		{ "entity", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkUnaryActionClass(
		"hkUnaryAction",
		&hkActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkUnaryActionClass_Members),
		int(sizeof(hkUnaryActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkMaterialResponseTypeEnumItems[] =
	{
		{0, "RESPONSE_INVALID"},
		{1, "RESPONSE_SIMPLE_CONTACT"},
		{2, "RESPONSE_REPORTING"},
		{3, "RESPONSE_NONE"},
		{4, "RESPONSE_MAX_ID"},
	};
	static const hkInternalClassEnum hkMaterialEnums[] = {
		{"ResponseType", hkMaterialResponseTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMaterialResponseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMaterialEnums[0]);
	static hkInternalClassMember hkMaterialClass_Members[] =
	{
		{ "responseType", HK_NULL, hkMaterialResponseTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "restitution", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMaterialClass(
		"hkMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMaterialEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkMaterialClass_Members),
		int(sizeof(hkMaterialClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPropertyValueClass_Members[] =
	{
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPropertyValueClass(
		"hkPropertyValue",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPropertyValueClass_Members),
		int(sizeof(hkPropertyValueClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPropertyClass_Members[] =
	{
		{ "key", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignmentPadding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", &hkPropertyValueClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPropertyClass(
		"hkProperty",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPropertyClass_Members),
		int(sizeof(hkPropertyClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkConstraintDataConstraintTypeEnumItems[] =
	{
		{0, "CONSTRAINT_TYPE_BALLANDSOCKET"},
		{1, "CONSTRAINT_TYPE_HINGE"},
		{2, "CONSTRAINT_TYPE_LIMITEDHINGE"},
		{3, "CONSTRAINT_TYPE_POINTTOPATH"},
		{6, "CONSTRAINT_TYPE_PRISMATIC"},
		{7, "CONSTRAINT_TYPE_RAGDOLL"},
		{8, "CONSTRAINT_TYPE_STIFFSPRING"},
		{9, "CONSTRAINT_TYPE_WHEEL"},
		{10, "CONSTRAINT_TYPE_GENERIC"},
		{11, "CONSTRAINT_TYPE_CONTACT"},
		{12, "CONSTRAINT_TYPE_BREAKABLE"},
		{13, "CONSTRAINT_TYPE_MALLEABLE"},
		{14, "CONSTRAINT_TYPE_POINTTOPLANE"},
		{15, "CONSTRAINT_TYPE_PULLEY"},
		{18, "CONSTRAINT_TYPE_HINGE_LIMITS"},
		{19, "CONSTRAINT_TYPE_RAGDOLL_LIMITS"},
		{100, "BEGIN_CONSTRAINT_CHAIN_TYPES"},
		{100, "CONSTRAINT_TYPE_STIFF_SPRING_CHAIN"},
		{101, "CONSTRAINT_TYPE_BALL_SOCKET_CHAIN"},
		{102, "CONSTRAINT_TYPE_POWERED_CHAIN"},
	};
	static const hkInternalClassEnum hkConstraintDataEnums[] = {
		{"ConstraintType", hkConstraintDataConstraintTypeEnumItems, 20, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintDataConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintDataEnums[0]);
	static hkInternalClassMember hkConstraintDataClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstraintDataClass(
		"hkConstraintData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkConstraintDataClass_Members),
		int(sizeof(hkConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConstraintInfoClass_Members[] =
	{
		{ "maxSizeOfJacobians", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sizeOfJacobians", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sizeOfSchemas", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstraintInfoClass(
		"hkConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConstraintInfoClass_Members),
		int(sizeof(hkConstraintInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	extern const hkClassEnum* hkConstraintInstanceConstraintPriorityEnum;
	static const hkInternalClassEnumItem hkConstraintInstanceConstraintPriorityEnumItems[] =
	{
		{0, "PRIORITY_INVALID"},
		{1, "PRIORITY_PSI"},
		{2, "PRIORITY_TOI"},
		{3, "PRIORITY_TOI_HIGHER"},
		{4, "PRIORITY_TOI_FORCED"},
	};
	static const hkInternalClassEnumItem hkConstraintInstanceInstanceTypeEnumItems[] =
	{
		{0, "TYPE_NORMAL"},
		{1, "TYPE_CHAIN"},
	};
	static const hkInternalClassEnumItem hkConstraintInstanceAddReferencesEnumItems[] =
	{
		{0, "DO_NOT_ADD_REFERENCES"},
		{1, "DO_ADD_REFERENCES"},
	};
	static const hkInternalClassEnum hkConstraintInstanceEnums[] = {
		{"ConstraintPriority", hkConstraintInstanceConstraintPriorityEnumItems, 5, HK_NULL, 0 },
		{"InstanceType", hkConstraintInstanceInstanceTypeEnumItems, 2, HK_NULL, 0 },
		{"AddReferences", hkConstraintInstanceAddReferencesEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintInstanceConstraintPriorityEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintInstanceEnums[0]);
	extern const hkClassEnum* hkConstraintInstanceInstanceTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintInstanceEnums[1]);
	extern const hkClassEnum* hkConstraintInstanceAddReferencesEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintInstanceEnums[2]);
	static hkInternalClassMember hkConstraintInstanceClass_Members[] =
	{
		{ "owner", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "data", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "constraintModifiers", &hkModifierConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "entities", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, 0, HK_NULL },
		{ "priority", HK_NULL, hkConstraintInstanceConstraintPriorityEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "wantRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "internal", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstraintInstanceClass(
		"hkConstraintInstance",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConstraintInstanceEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkConstraintInstanceClass_Members),
		int(sizeof(hkConstraintInstanceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBallAndSocketConstraintData_AtomsClass_Members[] =
	{
		{ "pivots", &hkSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBallAndSocketConstraintDataAtomsClass(
		"hkBallAndSocketConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBallAndSocketConstraintData_AtomsClass_Members),
		int(sizeof(hkBallAndSocketConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBallAndSocketConstraintDataClass_Members[] =
	{
		{ "atoms", &hkBallAndSocketConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBallAndSocketConstraintDataClass(
		"hkBallAndSocketConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBallAndSocketConstraintDataClass_Members),
		int(sizeof(hkBallAndSocketConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkHingeConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
	};
	static const hkInternalClassEnum hkHingeConstraintDataAtomsEnums[] = {
		{"Axis", hkHingeConstraintDataAtomsAxisEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkHingeConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkHingeConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkHingeConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hk2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeConstraintDataAtomsClass(
		"hkHingeConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkHingeConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkHingeConstraintData_AtomsClass_Members),
		int(sizeof(hkHingeConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkHingeConstraintDataClass_Members[] =
	{
		{ "atoms", &hkHingeConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeConstraintDataClass(
		"hkHingeConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkHingeConstraintDataClass_Members),
		int(sizeof(hkHingeConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkLimitedHingeConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
		{1, "AXIS_PERP_TO_AXLE_1"},
		{2, "AXIS_PERP_TO_AXLE_2"},
	};
	static const hkInternalClassEnum hkLimitedHingeConstraintDataAtomsEnums[] = {
		{"Axis", hkLimitedHingeConstraintDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkLimitedHingeConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkLimitedHingeConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkLimitedHingeConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angMotor", &hkAngMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angFriction", &hkAngFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angLimit", &hkAngLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hk2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLimitedHingeConstraintDataAtomsClass(
		"hkLimitedHingeConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkLimitedHingeConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkLimitedHingeConstraintData_AtomsClass_Members),
		int(sizeof(hkLimitedHingeConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLimitedHingeConstraintDataClass_Members[] =
	{
		{ "atoms", &hkLimitedHingeConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLimitedHingeConstraintDataClass(
		"hkLimitedHingeConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLimitedHingeConstraintDataClass_Members),
		int(sizeof(hkLimitedHingeConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinearParametricCurveClass_Members[] =
	{
		{ "smoothingFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "closedLoop", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dirNotParallelToTangentAlongWholePath", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "points", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "distance", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinearParametricCurveClass(
		"hkLinearParametricCurve",
		&hkParametricCurveClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinearParametricCurveClass_Members),
		int(sizeof(hkLinearParametricCurveClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkParametricCurveClass(
		"hkParametricCurve",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static const hkInternalClassEnumItem hkPointToPathConstraintDataOrientationConstraintTypeEnumItems[] =
	{
		{0, "CONSTRAIN_ORIENTATION_INVALID"},
		{1, "CONSTRAIN_ORIENTATION_NONE"},
		{2, "CONSTRAIN_ORIENTATION_ALLOW_SPIN"},
		{3, "CONSTRAIN_ORIENTATION_TO_PATH"},
		{4, "CONSTRAIN_ORIENTATION_MAX_ID"},
	};
	static const hkInternalClassEnum hkPointToPathConstraintDataEnums[] = {
		{"OrientationConstraintType", hkPointToPathConstraintDataOrientationConstraintTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkPointToPathConstraintDataOrientationConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkPointToPathConstraintDataEnums[0]);
	static hkInternalClassMember hkPointToPathConstraintDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "path", &hkParametricCurveClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularConstrainedDOF", HK_NULL, hkPointToPathConstraintDataOrientationConstraintTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "transform_OS_KS", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkPointToPathConstraintDataClass(
		"hkPointToPathConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkPointToPathConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkPointToPathConstraintDataClass_Members),
		int(sizeof(hkPointToPathConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPointToPlaneConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin", &hkLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPointToPlaneConstraintDataAtomsClass(
		"hkPointToPlaneConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPointToPlaneConstraintData_AtomsClass_Members),
		int(sizeof(hkPointToPlaneConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPointToPlaneConstraintDataClass_Members[] =
	{
		{ "atoms", &hkPointToPlaneConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPointToPlaneConstraintDataClass(
		"hkPointToPlaneConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPointToPlaneConstraintDataClass_Members),
		int(sizeof(hkPointToPlaneConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkPrismaticConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_SHAFT"},
		{1, "AXIS_PERP_TO_SHAFT"},
	};
	static const hkInternalClassEnum hkPrismaticConstraintDataAtomsEnums[] = {
		{"Axis", hkPrismaticConstraintDataAtomsAxisEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkPrismaticConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkPrismaticConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkPrismaticConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkLinMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "friction", &hkLinFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ang", &hkAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0", &hkLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin1", &hkLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linLimit", &hkLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPrismaticConstraintDataAtomsClass(
		"hkPrismaticConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkPrismaticConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkPrismaticConstraintData_AtomsClass_Members),
		int(sizeof(hkPrismaticConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPrismaticConstraintDataClass_Members[] =
	{
		{ "atoms", &hkPrismaticConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPrismaticConstraintDataClass(
		"hkPrismaticConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPrismaticConstraintDataClass_Members),
		int(sizeof(hkPrismaticConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStiffSpringConstraintData_AtomsClass_Members[] =
	{
		{ "pivots", &hkSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spring", &hkStiffSpringConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStiffSpringConstraintDataAtomsClass(
		"hkStiffSpringConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStiffSpringConstraintData_AtomsClass_Members),
		int(sizeof(hkStiffSpringConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStiffSpringConstraintDataClass_Members[] =
	{
		{ "atoms", &hkStiffSpringConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStiffSpringConstraintDataClass(
		"hkStiffSpringConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStiffSpringConstraintDataClass_Members),
		int(sizeof(hkStiffSpringConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkWheelConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_SUSPENSION"},
		{1, "AXIS_PERP_SUSPENSION"},
		{0, "AXIS_AXLE"},
		{1, "AXIS_STEERING"},
	};
	static const hkInternalClassEnum hkWheelConstraintDataAtomsEnums[] = {
		{"Axis", hkWheelConstraintDataAtomsAxisEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkWheelConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkWheelConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkWheelConstraintData_AtomsClass_Members[] =
	{
		{ "suspensionBase", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0Limit", &hkLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0Soft", &hkLinSoftConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin1", &hkLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin2", &hkLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "steeringBase", &hkSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hk2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWheelConstraintDataAtomsClass(
		"hkWheelConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkWheelConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkWheelConstraintData_AtomsClass_Members),
		int(sizeof(hkWheelConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWheelConstraintDataClass_Members[] =
	{
		{ "atoms", &hkWheelConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialAxleInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialSteeringAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWheelConstraintDataClass(
		"hkWheelConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWheelConstraintDataClass_Members),
		int(sizeof(hkWheelConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBreakableConstraintDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constraintData", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "childRuntimeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childNumSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "solverResultLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "removeWhenBroken", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "revertBackVelocityOnBreak", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "listener", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkBreakableConstraintDataClass(
		"hkBreakableConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBreakableConstraintDataClass_Members),
		int(sizeof(hkBreakableConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkConstraintChainDataClass(
		"hkConstraintChainData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkConstraintChainInstanceClass_Members[] =
	{
		{ "chainedEntities", &hkEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "action", &hkConstraintChainInstanceActionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstraintChainInstanceClass(
		"hkConstraintChainInstance",
		&hkConstraintInstanceClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConstraintChainInstanceClass_Members),
		int(sizeof(hkConstraintChainInstanceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConstraintChainInstanceActionClass_Members[] =
	{
		{ "constraintInstance", &hkConstraintChainInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstraintChainInstanceActionClass(
		"hkConstraintChainInstanceAction",
		&hkActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConstraintChainInstanceActionClass_Members),
		int(sizeof(hkConstraintChainInstanceActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBallSocketChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBallSocketChainDataConstraintInfoClass(
		"hkBallSocketChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBallSocketChainData_ConstraintInfoClass_Members),
		int(sizeof(hkBallSocketChainData_ConstraintInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBallSocketChainDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkBallSocketChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxErrorDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBallSocketChainDataClass(
		"hkBallSocketChainData",
		&hkConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBallSocketChainDataClass_Members),
		int(sizeof(hkBallSocketChainDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkHingeLimitsDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
		{1, "AXIS_PERP_TO_AXLE_1"},
		{2, "AXIS_PERP_TO_AXLE_2"},
	};
	static const hkInternalClassEnum hkHingeLimitsDataAtomsEnums[] = {
		{"Axis", hkHingeLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkHingeLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkHingeLimitsDataAtomsEnums[0]);
	static hkInternalClassMember hkHingeLimitsData_AtomsClass_Members[] =
	{
		{ "rotations", &hkSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angLimit", &hkAngLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hk2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeLimitsDataAtomsClass(
		"hkHingeLimitsDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkHingeLimitsDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkHingeLimitsData_AtomsClass_Members),
		int(sizeof(hkHingeLimitsData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkHingeLimitsDataClass_Members[] =
	{
		{ "atoms", &hkHingeLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeLimitsDataClass(
		"hkHingeLimitsData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkHingeLimitsDataClass_Members),
		int(sizeof(hkHingeLimitsDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motors", &hkConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, 0, HK_NULL },
		{ "switchBodies", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredChainDataConstraintInfoClass(
		"hkPoweredChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredChainData_ConstraintInfoClass_Members),
		int(sizeof(hkPoweredChainData_ConstraintInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredChainDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkPoweredChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfmLinAdd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfmLinMul", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfmAngAdd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfmAngMul", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxErrorDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkPoweredChainData_DefaultStruct
		{
			int s_defaultOffsets[9];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_cfmLinAdd;
			hkReal m_cfmLinMul;
			hkReal m_cfmAngAdd;
			hkReal m_cfmAngMul;
		};
		const hkPoweredChainData_DefaultStruct hkPoweredChainData_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkPoweredChainData_DefaultStruct,m_cfmLinAdd),HK_OFFSET_OF(hkPoweredChainData_DefaultStruct,m_cfmLinMul),HK_OFFSET_OF(hkPoweredChainData_DefaultStruct,m_cfmAngAdd),HK_OFFSET_OF(hkPoweredChainData_DefaultStruct,m_cfmAngMul),-1},
			0.1f*1.19209290e-07f,1.0f,0.1f*1.19209290e-07F,1.0f
		};
	}
	hkClass hkPoweredChainDataClass(
		"hkPoweredChainData",
		&hkConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredChainDataClass_Members),
		int(sizeof(hkPoweredChainDataClass_Members)/sizeof(hkInternalClassMember)),
		&hkPoweredChainData_Default
		);
	static hkInternalClassMember hkStiffSpringChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStiffSpringChainDataConstraintInfoClass(
		"hkStiffSpringChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStiffSpringChainData_ConstraintInfoClass_Members),
		int(sizeof(hkStiffSpringChainData_ConstraintInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStiffSpringChainDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkStiffSpringChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStiffSpringChainDataClass(
		"hkStiffSpringChainData",
		&hkConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStiffSpringChainDataClass_Members),
		int(sizeof(hkStiffSpringChainDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkGenericConstraintDataClass_Members[] =
	{
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scheme", &hkGenericConstraintDataSchemeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkGenericConstraintDataClass(
		"hkGenericConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkGenericConstraintDataClass_Members),
		int(sizeof(hkGenericConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkGenericConstraintDataSchemeClass_Members[] =
	{
		{ "info", &hkConstraintInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "commands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "modifiers", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "motors", &hkConstraintMotorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkGenericConstraintDataSchemeClass(
		"hkGenericConstraintDataScheme",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkGenericConstraintDataSchemeClass_Members),
		int(sizeof(hkGenericConstraintDataSchemeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMalleableConstraintDataClass_Members[] =
	{
		{ "constraintData", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "atoms", &hkBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMalleableConstraintDataClass(
		"hkMalleableConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMalleableConstraintDataClass_Members),
		int(sizeof(hkMalleableConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkConstraintMotorMotorTypeEnumItems[] =
	{
		{0, "TYPE_INVALID"},
		{1, "TYPE_POSITION"},
		{2, "TYPE_VELOCITY"},
		{3, "TYPE_SPRING_DAMPER"},
		{4, "TYPE_MAX"},
	};
	static const hkInternalClassEnum hkConstraintMotorEnums[] = {
		{"MotorType", hkConstraintMotorMotorTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintMotorMotorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintMotorEnums[0]);
	static hkInternalClassMember hkConstraintMotorClass_Members[] =
	{
		{ "type", HK_NULL, hkConstraintMotorMotorTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	hkClass hkConstraintMotorClass(
		"hkConstraintMotor",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkConstraintMotorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkConstraintMotorClass_Members),
		int(sizeof(hkConstraintMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLimitedForceConstraintMotorClass_Members[] =
	{
		{ "minForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLimitedForceConstraintMotorClass(
		"hkLimitedForceConstraintMotor",
		&hkConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLimitedForceConstraintMotorClass_Members),
		int(sizeof(hkLimitedForceConstraintMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPositionConstraintMotorClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proportionalRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constantRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPositionConstraintMotorClass(
		"hkPositionConstraintMotor",
		&hkLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPositionConstraintMotorClass_Members),
		int(sizeof(hkPositionConstraintMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSpringDamperConstraintMotorClass_Members[] =
	{
		{ "springConstant", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSpringDamperConstraintMotorClass(
		"hkSpringDamperConstraintMotor",
		&hkLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSpringDamperConstraintMotorClass_Members),
		int(sizeof(hkSpringDamperConstraintMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVelocityConstraintMotorClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocityTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useVelocityTargetFromConstraintTargets", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVelocityConstraintMotorClass(
		"hkVelocityConstraintMotor",
		&hkLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVelocityConstraintMotorClass_Members),
		int(sizeof(hkVelocityConstraintMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPulleyConstraintData_AtomsClass_Members[] =
	{
		{ "translations", &hkSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pulley", &hkPulleyConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPulleyConstraintDataAtomsClass(
		"hkPulleyConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPulleyConstraintData_AtomsClass_Members),
		int(sizeof(hkPulleyConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPulleyConstraintDataClass_Members[] =
	{
		{ "atoms", &hkPulleyConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPulleyConstraintDataClass(
		"hkPulleyConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPulleyConstraintDataClass_Members),
		int(sizeof(hkPulleyConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkEntityClass_Members[] =
	{
		{ "simulationIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "material", &hkMaterialClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivator", &hkEntityDeactivatorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "constraintsMaster", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "constraintsSlave", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "constraintRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "storageIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "processContactCallbackDelay", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "autoRemoveLevel", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "uid", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motion", &hkMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "activationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "entityListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "actions", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkEntity_DefaultStruct
		{
			int s_defaultOffsets[16];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkUint32 m_uid;
		};
		const hkEntity_DefaultStruct hkEntity_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkEntity_DefaultStruct,m_uid),-1,-1,-1,-1,-1},
			0xffffffff
		};
	}
	hkClass hkEntityClass(
		"hkEntity",
		&hkWorldObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkEntityClass_Members),
		int(sizeof(hkEntityClass_Members)/sizeof(hkInternalClassMember)),
		&hkEntity_Default
		);
	hkClass hkEntityDeactivatorClass(
		"hkEntityDeactivator",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkFakeRigidBodyDeactivatorClass(
		"hkFakeRigidBodyDeactivator",
		&hkRigidBodyDeactivatorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkRigidBodyClass(
		"hkRigidBody",
		&hkEntityClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static const hkInternalClassEnumItem hkRigidBodyDeactivatorDeactivatorTypeEnumItems[] =
	{
		{0, "DEACTIVATOR_INVALID"},
		{1, "DEACTIVATOR_NEVER"},
		{2, "DEACTIVATOR_SPATIAL"},
		{3, "DEACTIVATOR_MAX_ID"},
	};
	static const hkInternalClassEnum hkRigidBodyDeactivatorEnums[] = {
		{"DeactivatorType", hkRigidBodyDeactivatorDeactivatorTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkRigidBodyDeactivatorDeactivatorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkRigidBodyDeactivatorEnums[0]);
	hkClass hkRigidBodyDeactivatorClass(
		"hkRigidBodyDeactivator",
		&hkEntityDeactivatorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkRigidBodyDeactivatorEnums),
		1,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkSpatialRigidBodyDeactivator_SampleClass_Members[] =
	{
		{ "refPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSpatialRigidBodyDeactivatorSampleClass(
		"hkSpatialRigidBodyDeactivatorSample",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSpatialRigidBodyDeactivator_SampleClass_Members),
		int(sizeof(hkSpatialRigidBodyDeactivator_SampleClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSpatialRigidBodyDeactivatorClass_Members[] =
	{
		{ "highFrequencySample", &hkSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencySample", &hkSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radiusSqrd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minHighFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minHighFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minLowFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minLowFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSpatialRigidBodyDeactivatorClass(
		"hkSpatialRigidBodyDeactivator",
		&hkRigidBodyDeactivatorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSpatialRigidBodyDeactivatorClass_Members),
		int(sizeof(hkSpatialRigidBodyDeactivatorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkMotionMotionTypeEnumItems[] =
	{
		{0, "MOTION_INVALID"},
		{1, "MOTION_DYNAMIC"},
		{2, "MOTION_SPHERE_INERTIA"},
		{3, "MOTION_STABILIZED_SPHERE_INERTIA"},
		{4, "MOTION_BOX_INERTIA"},
		{5, "MOTION_STABILIZED_BOX_INERTIA"},
		{6, "MOTION_KEYFRAMED"},
		{7, "MOTION_FIXED"},
		{8, "MOTION_THIN_BOX_INERTIA"},
		{9, "MOTION_MAX_ID"},
	};
	static const hkInternalClassEnum hkMotionEnums[] = {
		{"MotionType", hkMotionMotionTypeEnumItems, 10, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMotionMotionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMotionEnums[0]);
	static hkInternalClassMember hkMotionClass_Members[] =
	{
		{ "type", HK_NULL, hkMotionMotionTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "deactivationIntegrateCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationNumInactiveFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "inertiaAndMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationRefPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkMotionClass(
		"hkMotion",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMotionEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkMotionClass_Members),
		int(sizeof(hkMotionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkBoxMotionClass(
		"hkBoxMotion",
		&hkMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkFixedRigidMotionClass(
		"hkFixedRigidMotion",
		&hkKeyframedRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkKeyframedRigidMotionClass_Members[] =
	{
		{ "savedMotion", &hkMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "savedQualityTypeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkKeyframedRigidMotionClass(
		"hkKeyframedRigidMotion",
		&hkMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkKeyframedRigidMotionClass_Members),
		int(sizeof(hkKeyframedRigidMotionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkMaxSizeMotionClass(
		"hkMaxSizeMotion",
		&hkKeyframedRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkSphereMotionClass(
		"hkSphereMotion",
		&hkMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkStabilizedBoxMotionClass(
		"hkStabilizedBoxMotion",
		&hkBoxMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkStabilizedSphereMotionClass(
		"hkStabilizedSphereMotion",
		&hkSphereMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkThinBoxMotionClass(
		"hkThinBoxMotion",
		&hkBoxMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkAabbPhantomClass_Members[] =
	{
		{ "aabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "overlappingCollidables", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	hkClass hkAabbPhantomClass(
		"hkAabbPhantom",
		&hkPhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAabbPhantomClass_Members),
		int(sizeof(hkAabbPhantomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkCachingShapePhantomClass_Members[] =
	{
		{ "collisionDetails", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	hkClass hkCachingShapePhantomClass(
		"hkCachingShapePhantom",
		&hkShapePhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCachingShapePhantomClass_Members),
		int(sizeof(hkCachingShapePhantomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPhantomClass_Members[] =
	{
		{ "overlapListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "phantomListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	hkClass hkPhantomClass(
		"hkPhantom",
		&hkWorldObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPhantomClass_Members),
		int(sizeof(hkPhantomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkShapePhantomClass_Members[] =
	{
		{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkShapePhantomClass(
		"hkShapePhantom",
		&hkPhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkShapePhantomClass_Members),
		int(sizeof(hkShapePhantomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSimpleShapePhantomClass_Members[] =
	{
		{ "collisionDetails", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	hkClass hkSimpleShapePhantomClass(
		"hkSimpleShapePhantom",
		&hkShapePhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSimpleShapePhantomClass_Members),
		int(sizeof(hkSimpleShapePhantomClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPhysicsSystemClass_Members[] =
	{
		{ "rigidBodies", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "constraints", &hkConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "actions", &hkActionClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "phantoms", &hkPhantomClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "active", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkPhysicsSystem_DefaultStruct
		{
			int s_defaultOffsets[7];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkBool m_active;
		};
		const hkPhysicsSystem_DefaultStruct hkPhysicsSystem_Default =
		{
			{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkPhysicsSystem_DefaultStruct,m_active)},
			true
		};
	}
	hkClass hkPhysicsSystemClass(
		"hkPhysicsSystem",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPhysicsSystemClass_Members),
		int(sizeof(hkPhysicsSystemClass_Members)/sizeof(hkInternalClassMember)),
		&hkPhysicsSystem_Default
		);
	static const hkInternalClassEnumItem hkWorldCinfoSolverTypeEnumItems[] =
	{
		{0, "SOLVER_TYPE_INVALID"},
		{1, "SOLVER_TYPE_2ITERS_SOFT"},
		{2, "SOLVER_TYPE_2ITERS_MEDIUM"},
		{3, "SOLVER_TYPE_2ITERS_HARD"},
		{4, "SOLVER_TYPE_4ITERS_SOFT"},
		{5, "SOLVER_TYPE_4ITERS_MEDIUM"},
		{6, "SOLVER_TYPE_4ITERS_HARD"},
		{7, "SOLVER_TYPE_8ITERS_SOFT"},
		{8, "SOLVER_TYPE_8ITERS_MEDIUM"},
		{9, "SOLVER_TYPE_8ITERS_HARD"},
		{10, "SOLVER_TYPE_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkWorldCinfoSimulationTypeEnumItems[] =
	{
		{0, "SIMULATION_TYPE_INVALID"},
		{1, "SIMULATION_TYPE_DISCRETE"},
		{2, "SIMULATION_TYPE_CONTINUOUS"},
		{3, "SIMULATION_TYPE_MULTITHREADED"},
	};
	static const hkInternalClassEnumItem hkWorldCinfoContactPointGenerationEnumItems[] =
	{
		{0, "CONTACT_POINT_ACCEPT_ALWAYS"},
		{1, "CONTACT_POINT_REJECT_DUBIOUS"},
		{2, "CONTACT_POINT_REJECT_MANY"},
	};
	static const hkInternalClassEnumItem hkWorldCinfoBroadPhaseBorderBehaviourEnumItems[] =
	{
		{0, "BROADPHASE_BORDER_ASSERT"},
		{1, "BROADPHASE_BORDER_FIX_ENTITY"},
		{2, "BROADPHASE_BORDER_REMOVE_ENTITY"},
		{3, "BROADPHASE_BORDER_DO_NOTHING"},
	};
	static const hkInternalClassEnum hkWorldCinfoEnums[] = {
		{"SolverType", hkWorldCinfoSolverTypeEnumItems, 11, HK_NULL, 0 },
		{"SimulationType", hkWorldCinfoSimulationTypeEnumItems, 4, HK_NULL, 0 },
		{"ContactPointGeneration", hkWorldCinfoContactPointGenerationEnumItems, 3, HK_NULL, 0 },
		{"BroadPhaseBorderBehaviour", hkWorldCinfoBroadPhaseBorderBehaviourEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkWorldCinfoSolverTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[0]);
	extern const hkClassEnum* hkWorldCinfoSimulationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[1]);
	extern const hkClassEnum* hkWorldCinfoContactPointGenerationEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[2]);
	extern const hkClassEnum* hkWorldCinfoBroadPhaseBorderBehaviourEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[3]);
	static hkInternalClassMember hkWorldCinfoClass_Members[] =
	{
		{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactRestingVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseBorderBehaviour", HK_NULL, hkWorldCinfoBroadPhaseBorderBehaviourEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "broadPhaseWorldAabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionFilter", &hkCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "convexListFilter", &hkConvexListFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "expectedMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "expectedMinPsiDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "memoryWatchDog", &hkWorldMemoryWatchDogClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactPointGeneration", HK_NULL, hkWorldCinfoContactPointGenerationEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "solverTau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverDamp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverMicrosteps", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastEarlyOutDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastMaxIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wantOldStyleDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationReferenceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "simulationType", HK_NULL, hkWorldCinfoSimulationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "enableSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minDesiredIslandSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "processActionsInSingleThread", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameMarkerPsiSnap", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkWorldCinfo_DefaultStruct
		{
			int s_defaultOffsets[31];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkVector4 m_gravity;
			hkInt32 m_broadPhaseQuerySize;
			hkReal m_collisionTolerance;
			hkReal m_expectedMaxLinearVelocity;
			hkReal m_expectedMinPsiDeltaTime;
			hkReal m_solverDamp;
			hkInt32 m_solverIterations;
			hkInt32 m_solverMicrosteps;
			hkReal m_iterativeLinearCastEarlyOutDistance;
			hkInt32 m_iterativeLinearCastMaxIterations;
			hkReal m_highFrequencyDeactivationPeriod;
			hkReal m_lowFrequencyDeactivationPeriod;
			_hkBool m_shouldActivateOnRigidBodyTransformChange;
			hkReal m_deactivationReferenceDistance;
			hkReal m_toiCollisionResponseRotateNormal;
			_hkBool m_enableDeactivation;
			_hkBool m_enableSimulationIslands;
			hkUint32 m_minDesiredIslandSize;
			_hkBool m_processActionsInSingleThread;
			hkReal m_frameMarkerPsiSnap;
		};
		const hkWorldCinfo_DefaultStruct hkWorldCinfo_Default =
		{
			{HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_gravity),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_broadPhaseQuerySize),-1,-1,-1,HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_collisionTolerance),-1,-1,HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_expectedMaxLinearVelocity),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_expectedMinPsiDeltaTime),-1,-1,-1,-1,HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_solverDamp),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_solverIterations),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_solverMicrosteps),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_iterativeLinearCastEarlyOutDistance),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_iterativeLinearCastMaxIterations),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_highFrequencyDeactivationPeriod),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_lowFrequencyDeactivationPeriod),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_shouldActivateOnRigidBodyTransformChange),-1,HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_deactivationReferenceDistance),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_toiCollisionResponseRotateNormal),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_enableDeactivation),-1,HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_enableSimulationIslands),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_minDesiredIslandSize),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_processActionsInSingleThread),HK_OFFSET_OF(hkWorldCinfo_DefaultStruct,m_frameMarkerPsiSnap)},
			{0,-9.8f,0},1024,.1f,200,1.0f/30.0f,.6f,4,1,.01f,20,.2f,10,true,0.02f,0.2f,true,true,64,true,.0001f
		};
	}
	hkClass hkWorldCinfoClass(
		"hkWorldCinfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkWorldCinfoEnums),
		4,
		reinterpret_cast<const hkClassMember*>(hkWorldCinfoClass_Members),
		int(sizeof(hkWorldCinfoClass_Members)/sizeof(hkInternalClassMember)),
		&hkWorldCinfo_Default
		);
	static const hkInternalClassEnumItem hkWorldObjectBroadPhaseTypeEnumItems[] =
	{
		{0, "BROAD_PHASE_INVALID"},
		{1, "BROAD_PHASE_ENTITY"},
		{2, "BROAD_PHASE_PHANTOM"},
		{3, "BROAD_PHASE_BORDER"},
		{4, "BROAD_PHASE_MAX_ID"},
	};
	static const hkInternalClassEnum hkWorldObjectEnums[] = {
		{"BroadPhaseType", hkWorldObjectBroadPhaseTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkWorldObjectBroadPhaseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldObjectEnums[0]);
	static hkInternalClassMember hkWorldObjectClass_Members[] =
	{
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "multithreadLock", &hkMultiThreadLockClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collidable", &hkLinkedCollidableClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "properties", &hkPropertyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkWorldObjectClass(
		"hkWorldObject",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkWorldObjectEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkWorldObjectClass_Members),
		int(sizeof(hkWorldObjectClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWorldMemoryWatchDogClass_Members[] =
	{
		{ "memoryLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWorldMemoryWatchDogClass(
		"hkWorldMemoryWatchDog",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWorldMemoryWatchDogClass_Members),
		int(sizeof(hkWorldMemoryWatchDogClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLinkedCollidableClass_Members[] =
	{
		{ "collisionEntries", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
	hkClass hkLinkedCollidableClass(
		"hkLinkedCollidable",
		&hkCollidableClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLinkedCollidableClass_Members),
		int(sizeof(hkLinkedCollidableClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBroadPhaseHandleClass_Members[] =
	{
		{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBroadPhaseHandleClass(
		"hkBroadPhaseHandle",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBroadPhaseHandleClass_Members),
		int(sizeof(hkBroadPhaseHandleClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkConvexPieceStreamDataClass_Members[] =
	{
		{ "convexPieceStream", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "convexPieceOffsets", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "convexPieceSingleTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexPieceStreamDataClass(
		"hkConvexPieceStreamData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexPieceStreamDataClass_Members),
		int(sizeof(hkConvexPieceStreamDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMoppCode_CodeInfoClass_Members[] =
	{
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMoppCodeCodeInfoClass(
		"hkMoppCodeCodeInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMoppCode_CodeInfoClass_Members),
		int(sizeof(hkMoppCode_CodeInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMoppCodeClass_Members[] =
	{
		{ "info", &hkMoppCodeCodeInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkMoppCodeClass(
		"hkMoppCode",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMoppCodeClass_Members),
		int(sizeof(hkMoppCodeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkRagdollConstraintDataMotorIndexEnumItems[] =
	{
		{0, "MOTOR_TWIST"},
		{1, "MOTOR_PLANE"},
		{2, "MOTOR_CONE"},
	};
	static const hkInternalClassEnum hkRagdollConstraintDataEnums[] = {
		{"MotorIndex", hkRagdollConstraintDataMotorIndexEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkRagdollConstraintDataMotorIndexEnum = reinterpret_cast<const hkClassEnum*>(&hkRagdollConstraintDataEnums[0]);
	static const hkInternalClassEnumItem hkRagdollConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_TWIST"},
		{1, "AXIS_PLANES"},
		{2, "AXIS_CROSS_PRODUCT"},
	};
	static const hkInternalClassEnum hkRagdollConstraintDataAtomsEnums[] = {
		{"Axis", hkRagdollConstraintDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkRagdollConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkRagdollConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkRagdollConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollMotors", &hkRagdollMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angFriction", &hkAngFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistLimit", &hkTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "coneLimit", &hkConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planesLimit", &hkConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollConstraintDataAtomsClass(
		"hkRagdollConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkRagdollConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkRagdollConstraintData_AtomsClass_Members),
		int(sizeof(hkRagdollConstraintData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollConstraintDataClass_Members[] =
	{
		{ "atoms", &hkRagdollConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollConstraintDataClass(
		"hkRagdollConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkRagdollConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkRagdollConstraintDataClass_Members),
		int(sizeof(hkRagdollConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkRagdollLimitsDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_TWIST"},
		{1, "AXIS_PLANES"},
		{2, "AXIS_CROSS_PRODUCT"},
	};
	static const hkInternalClassEnum hkRagdollLimitsDataAtomsEnums[] = {
		{"Axis", hkRagdollLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkRagdollLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkRagdollLimitsDataAtomsEnums[0]);
	static hkInternalClassMember hkRagdollLimitsData_AtomsClass_Members[] =
	{
		{ "rotations", &hkSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistLimit", &hkTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "coneLimit", &hkConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planesLimit", &hkConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollLimitsDataAtomsClass(
		"hkRagdollLimitsDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkRagdollLimitsDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkRagdollLimitsData_AtomsClass_Members),
		int(sizeof(hkRagdollLimitsData_AtomsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollLimitsDataClass_Members[] =
	{
		{ "atoms", &hkRagdollLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollLimitsDataClass(
		"hkRagdollLimitsData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollLimitsDataClass_Members),
		int(sizeof(hkRagdollLimitsDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAngularDashpotActionClass_Members[] =
	{
		{ "rotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAngularDashpotActionClass(
		"hkAngularDashpotAction",
		&hkBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAngularDashpotActionClass_Members),
		int(sizeof(hkAngularDashpotActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDashpotActionClass_Members[] =
	{
		{ "point", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "impulse", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkDashpotActionClass(
		"hkDashpotAction",
		&hkBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDashpotActionClass_Members),
		int(sizeof(hkDashpotActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMotorActionClass_Members[] =
	{
		{ "axis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinRate", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "active", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMotorActionClass(
		"hkMotorAction",
		&hkUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMotorActionClass_Members),
		int(sizeof(hkMotorActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkReorientActionClass_Members[] =
	{
		{ "rotationAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "upAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkReorientActionClass(
		"hkReorientAction",
		&hkUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkReorientActionClass_Members),
		int(sizeof(hkReorientActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSpringActionClass_Members[] =
	{
		{ "lastForce", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionAinA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionBinB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "restLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "onCompression", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "onExtension", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSpringActionClass(
		"hkSpringAction",
		&hkBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSpringActionClass_Members),
		int(sizeof(hkSpringActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkCharacterProxyCinfoClass_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dynamicFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keepContactTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraUpStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraDownStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapePhantom", &hkShapePhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "keepDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactAngleSensitivity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userPlanes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxCharacterSpeedForSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "characterStrength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "characterMass", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "penetrationRecoverySpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxCastIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refreshManifoldInCheckSupport", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkCharacterProxyCinfo_DefaultStruct
		{
			int s_defaultOffsets[19];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_contactAngleSensitivity;
			int m_maxCastIterations;
			bool m_refreshManifoldInCheckSupport;
		};
		const hkCharacterProxyCinfo_DefaultStruct hkCharacterProxyCinfo_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkCharacterProxyCinfo_DefaultStruct,m_contactAngleSensitivity),-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkCharacterProxyCinfo_DefaultStruct,m_maxCastIterations),HK_OFFSET_OF(hkCharacterProxyCinfo_DefaultStruct,m_refreshManifoldInCheckSupport)},
			10,10,false
		};
	}
	hkClass hkCharacterProxyCinfoClass(
		"hkCharacterProxyCinfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCharacterProxyCinfoClass_Members),
		int(sizeof(hkCharacterProxyCinfoClass_Members)/sizeof(hkInternalClassMember)),
		&hkCharacterProxyCinfo_Default
		);
	static hkInternalClassMember hkConstrainedSystemFilterClass_Members[] =
	{
		{ "otherFilter", &hkCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkConstrainedSystemFilterClass(
		"hkConstrainedSystemFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConstrainedSystemFilterClass_Members),
		int(sizeof(hkConstrainedSystemFilterClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDisableEntityCollisionFilterClass_Members[] =
	{
		{ "disabledEntities", &hkEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkDisableEntityCollisionFilterClass(
		"hkDisableEntityCollisionFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDisableEntityCollisionFilterClass_Members),
		int(sizeof(hkDisableEntityCollisionFilterClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkGroupCollisionFilterClass_Members[] =
	{
		{ "noGroupCollisionEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionGroups", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 32, 0, 0, HK_NULL }
	};
	hkClass hkGroupCollisionFilterClass(
		"hkGroupCollisionFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkGroupCollisionFilterClass_Members),
		int(sizeof(hkGroupCollisionFilterClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPairwiseCollisionFilter_CollisionPairClass_Members[] =
	{
		{ "a", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "b", &hkEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPairwiseCollisionFilterCollisionPairClass(
		"hkPairwiseCollisionFilterCollisionPair",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPairwiseCollisionFilter_CollisionPairClass_Members),
		int(sizeof(hkPairwiseCollisionFilter_CollisionPairClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPairwiseCollisionFilterClass_Members[] =
	{
		{ "disabledPairs", &hkPairwiseCollisionFilterCollisionPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPairwiseCollisionFilterClass(
		"hkPairwiseCollisionFilter",
		&hkCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPairwiseCollisionFilterClass_Members),
		int(sizeof(hkPairwiseCollisionFilterClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredChainMapper_TargetClass_Members[] =
	{
		{ "chain", &hkPoweredChainDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "infoIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredChainMapperTargetClass(
		"hkPoweredChainMapperTarget",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredChainMapper_TargetClass_Members),
		int(sizeof(hkPoweredChainMapper_TargetClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredChainMapper_LinkInfoClass_Members[] =
	{
		{ "firstTargetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numTargets", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "limitConstraint", &hkConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredChainMapperLinkInfoClass(
		"hkPoweredChainMapperLinkInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredChainMapper_LinkInfoClass_Members),
		int(sizeof(hkPoweredChainMapper_LinkInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredChainMapperClass_Members[] =
	{
		{ "links", &hkPoweredChainMapperLinkInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "targets", &hkPoweredChainMapperTargetClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "chains", &hkConstraintChainInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredChainMapperClass(
		"hkPoweredChainMapper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredChainMapperClass_Members),
		int(sizeof(hkPoweredChainMapperClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMouseSpringActionClass_Members[] =
	{
		{ "positionInRbLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mousePositionInWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springElasticity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxRelativeForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMouseSpringActionClass(
		"hkMouseSpringAction",
		&hkUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMouseSpringActionClass_Members),
		int(sizeof(hkMouseSpringActionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRigidBodyDisplayBindingClass_Members[] =
	{
		{ "rigidBody", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "displayObject", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rigidBodyFromDisplayObjectTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRigidBodyDisplayBindingClass(
		"hkRigidBodyDisplayBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRigidBodyDisplayBindingClass_Members),
		int(sizeof(hkRigidBodyDisplayBindingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPhysicsSystemDisplayBindingClass_Members[] =
	{
		{ "bindings", &hkRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "system", &hkPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPhysicsSystemDisplayBindingClass(
		"hkPhysicsSystemDisplayBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPhysicsSystemDisplayBindingClass_Members),
		int(sizeof(hkPhysicsSystemDisplayBindingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDisplayBindingDataClass_Members[] =
	{
		{ "rigidBodyBindings", &hkRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "physicsSystemBindings", &hkPhysicsSystemDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkDisplayBindingDataClass(
		"hkDisplayBindingData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDisplayBindingDataClass_Members),
		int(sizeof(hkDisplayBindingDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPhysicsDataClass_Members[] =
	{
		{ "worldCinfo", &hkWorldCinfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "systems", &hkPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkPhysicsDataClass(
		"hkPhysicsData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPhysicsDataClass_Members),
		int(sizeof(hkPhysicsDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSerializedDisplayMarkerClass_Members[] =
	{
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSerializedDisplayMarkerClass(
		"hkSerializedDisplayMarker",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSerializedDisplayMarkerClass_Members),
		int(sizeof(hkSerializedDisplayMarkerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSerializedDisplayMarkerListClass_Members[] =
	{
		{ "markers", &hkSerializedDisplayMarkerClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkSerializedDisplayMarkerListClass(
		"hkSerializedDisplayMarkerList",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSerializedDisplayMarkerListClass_Members),
		int(sizeof(hkSerializedDisplayMarkerListClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSerializedDisplayRbTransforms_DisplayTransformPairClass_Members[] =
	{
		{ "rb", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "localToDisplay", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSerializedDisplayRbTransformsDisplayTransformPairClass(
		"hkSerializedDisplayRbTransformsDisplayTransformPair",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSerializedDisplayRbTransforms_DisplayTransformPairClass_Members),
		int(sizeof(hkSerializedDisplayRbTransforms_DisplayTransformPairClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSerializedDisplayRbTransformsClass_Members[] =
	{
		{ "transforms", &hkSerializedDisplayRbTransformsDisplayTransformPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkSerializedDisplayRbTransformsClass(
		"hkSerializedDisplayRbTransforms",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSerializedDisplayRbTransformsClass_Members),
		int(sizeof(hkSerializedDisplayRbTransformsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleData_WheelComponentParamsClass_Members[] =
	{
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mass", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "width", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "viscosityFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "slipAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forceFeedbackMultiplier", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxContactBodyAcceleration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDataWheelComponentParamsClass(
		"hkVehicleDataWheelComponentParams",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleData_WheelComponentParamsClass_Members),
		int(sizeof(hkVehicleData_WheelComponentParamsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDataClass_Members[] =
	{
		{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numWheels", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torqueRollFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torquePitchFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torqueYawFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraTorqueFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxVelocityForPositionalFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisUnitInertiaYaw", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisUnitInertiaRoll", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisUnitInertiaPitch", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frictionEqualizer", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "normalClippingAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelParams", &hkVehicleDataWheelComponentParamsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "numWheelsPerAxle", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "frictionDescription", &hkVehicleFrictionDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisFrictionInertiaInvDiag", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alreadyInitialised", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDataClass(
		"hkVehicleData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDataClass_Members),
		int(sizeof(hkVehicleDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleInstance_WheelInfoClass_Members[] =
	{
		{ "contactPoint", &hkContactPointClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactBody", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "contactShapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hardPointWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rayEndPointWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentSuspensionLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionDirectionWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinAxisCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinAxisWs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "steeringOrientationCs", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "skidEnergyDensity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sideForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forwardSlipVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sideSlipVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleInstanceWheelInfoClass(
		"hkVehicleInstanceWheelInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleInstance_WheelInfoClass_Members),
		int(sizeof(hkVehicleInstance_WheelInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleInstanceClass_Members[] =
	{
		{ "data", &hkVehicleDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "driverInput", &hkVehicleDriverInputClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "steering", &hkVehicleSteeringClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "engine", &hkVehicleEngineClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "transmission", &hkVehicleTransmissionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "brake", &hkVehicleBrakeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "suspension", &hkVehicleSuspensionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "aerodynamics", &hkVehicleAerodynamicsClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelCollide", &hkVehicleWheelCollideClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tyreMarks", &hkTyremarksInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "velocityDamper", &hkVehicleVelocityDamperClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelsInfo", &hkVehicleInstanceWheelInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "frictionStatus", &hkVehicleFrictionStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deviceStatus", &hkVehicleDriverInputStatusClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "isFixed", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "wheelsTimeSinceMaxPedalInput", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tryingToReverse", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rpm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mainSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelsSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "isReversing", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentGear", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "delayed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "clutchDelayCountdown", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleInstanceClass(
		"hkVehicleInstance",
		&hkUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleInstanceClass_Members),
		int(sizeof(hkVehicleInstanceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleAerodynamicsClass(
		"hkVehicleAerodynamics",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultAerodynamicsClass_Members[] =
	{
		{ "airDensity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frontalArea", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dragCoefficient", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "liftCoefficient", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraGravityws", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultAerodynamicsClass(
		"hkVehicleDefaultAerodynamics",
		&hkVehicleAerodynamicsClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultAerodynamicsClass_Members),
		int(sizeof(hkVehicleDefaultAerodynamicsClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleBrakeClass(
		"hkVehicleBrake",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultBrake_WheelBrakingPropertiesClass_Members[] =
	{
		{ "maxBreakingTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minPedalInputToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isConnectedToHandbrake", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultBrakeWheelBrakingPropertiesClass(
		"hkVehicleDefaultBrakeWheelBrakingProperties",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultBrake_WheelBrakingPropertiesClass_Members),
		int(sizeof(hkVehicleDefaultBrake_WheelBrakingPropertiesClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultBrakeClass_Members[] =
	{
		{ "wheelBrakingProperties", &hkVehicleDefaultBrakeWheelBrakingPropertiesClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelsMinTimeToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultBrakeClass(
		"hkVehicleDefaultBrake",
		&hkVehicleBrakeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultBrakeClass_Members),
		int(sizeof(hkVehicleDefaultBrakeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleDriverInputStatusClass(
		"hkVehicleDriverInputStatus",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	hkClass hkVehicleDriverInputClass(
		"hkVehicleDriverInput",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDriverInputAnalogStatusClass_Members[] =
	{
		{ "positionX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionY", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handbrakeButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reverseButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDriverInputAnalogStatusClass(
		"hkVehicleDriverInputAnalogStatus",
		&hkVehicleDriverInputStatusClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDriverInputAnalogStatusClass_Members),
		int(sizeof(hkVehicleDriverInputAnalogStatusClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultAnalogDriverInputClass_Members[] =
	{
		{ "slopeChangePointX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deadZone", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "autoReverse", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultAnalogDriverInputClass(
		"hkVehicleDefaultAnalogDriverInput",
		&hkVehicleDriverInputClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultAnalogDriverInputClass_Members),
		int(sizeof(hkVehicleDefaultAnalogDriverInputClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleEngineClass(
		"hkVehicleEngine",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultEngineClass_Members[] =
	{
		{ "minRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "optRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torqueFactorAtMinRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "torqueFactorAtMaxRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "resistanceFactorAtMinRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "resistanceFactorAtOptRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "resistanceFactorAtMaxRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "clutchSlipRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultEngineClass(
		"hkVehicleDefaultEngine",
		&hkVehicleEngineClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultEngineClass_Members),
		int(sizeof(hkVehicleDefaultEngineClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleFrictionDescription_AxisDescriptionClass_Members[] =
	{
		{ "frictionCircleYtab", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 16, 0, 0, HK_NULL },
		{ "xStep", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "xStart", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelSurfaceInertia", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelSurfaceInertiaInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelChassisMassRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelRadiusInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelDownForceFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelDownForceSumFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleFrictionDescriptionAxisDescriptionClass(
		"hkVehicleFrictionDescriptionAxisDescription",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleFrictionDescription_AxisDescriptionClass_Members),
		int(sizeof(hkVehicleFrictionDescription_AxisDescriptionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleFrictionDescriptionClass_Members[] =
	{
		{ "wheelDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axleDescr", &hkVehicleFrictionDescriptionAxisDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkVehicleFrictionDescriptionClass(
		"hkVehicleFrictionDescription",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleFrictionDescriptionClass_Members),
		int(sizeof(hkVehicleFrictionDescriptionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleFrictionStatus_AxisStatusClass_Members[] =
	{
		{ "forward_slip_velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "side_slip_velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "skid_energy_density", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "side_force", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "delayed_forward_impulse", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sideRhs", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forwardRhs", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "relativeSideForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "relativeForwardForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleFrictionStatusAxisStatusClass(
		"hkVehicleFrictionStatusAxisStatus",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleFrictionStatus_AxisStatusClass_Members),
		int(sizeof(hkVehicleFrictionStatus_AxisStatusClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleFrictionStatusClass_Members[] =
	{
		{ "axis", &hkVehicleFrictionStatusAxisStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkVehicleFrictionStatusClass(
		"hkVehicleFrictionStatus",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleFrictionStatusClass_Members),
		int(sizeof(hkVehicleFrictionStatusClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleSteeringClass(
		"hkVehicleSteering",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultSteeringClass_Members[] =
	{
		{ "maxSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSpeedFullSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "doesWheelSteer", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultSteeringClass(
		"hkVehicleDefaultSteering",
		&hkVehicleSteeringClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultSteeringClass_Members),
		int(sizeof(hkVehicleDefaultSteeringClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleSuspension_SuspensionWheelParametersClass_Members[] =
	{
		{ "hardpointCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "directionCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleSuspensionSuspensionWheelParametersClass(
		"hkVehicleSuspensionSuspensionWheelParameters",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleSuspension_SuspensionWheelParametersClass_Members),
		int(sizeof(hkVehicleSuspension_SuspensionWheelParametersClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleSuspensionClass_Members[] =
	{
		{ "wheelParams", &hkVehicleSuspensionSuspensionWheelParametersClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleSuspensionClass(
		"hkVehicleSuspension",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleSuspensionClass_Members),
		int(sizeof(hkVehicleSuspensionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members[] =
	{
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dampingCompression", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dampingRelaxation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultSuspensionWheelSpringSuspensionParametersClass(
		"hkVehicleDefaultSuspensionWheelSpringSuspensionParameters",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members),
		int(sizeof(hkVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultSuspensionClass_Members[] =
	{
		{ "wheelSpringParams", &hkVehicleDefaultSuspensionWheelSpringSuspensionParametersClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultSuspensionClass(
		"hkVehicleDefaultSuspension",
		&hkVehicleSuspensionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultSuspensionClass_Members),
		int(sizeof(hkVehicleDefaultSuspensionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleTransmissionClass(
		"hkVehicleTransmission",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultTransmissionClass_Members[] =
	{
		{ "downshiftRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "upshiftRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "primaryTransmissionRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "clutchDelayTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reverseGearRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gearsRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "wheelsTorqueRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultTransmissionClass(
		"hkVehicleDefaultTransmission",
		&hkVehicleTransmissionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultTransmissionClass_Members),
		int(sizeof(hkVehicleDefaultTransmissionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTyremarkPointClass_Members[] =
	{
		{ "pointLeft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pointRight", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTyremarkPointClass(
		"hkTyremarkPoint",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTyremarkPointClass_Members),
		int(sizeof(hkTyremarkPointClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTyremarksWheelClass_Members[] =
	{
		{ "currentPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tyremarkPoints", &hkTyremarkPointClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkTyremarksWheelClass(
		"hkTyremarksWheel",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTyremarksWheelClass_Members),
		int(sizeof(hkTyremarksWheelClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkTyremarksInfoClass_Members[] =
	{
		{ "minTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tyremarksWheel", &hkTyremarksWheelClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkTyremarksInfoClass(
		"hkTyremarksInfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTyremarksInfoClass_Members),
		int(sizeof(hkTyremarksInfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkVehicleVelocityDamperClass(
		"hkVehicleVelocityDamper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL
		);
	static hkInternalClassMember hkVehicleDefaultVelocityDamperClass_Members[] =
	{
		{ "normalSpinDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionSpinDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleDefaultVelocityDamperClass(
		"hkVehicleDefaultVelocityDamper",
		&hkVehicleVelocityDamperClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleDefaultVelocityDamperClass_Members),
		int(sizeof(hkVehicleDefaultVelocityDamperClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleWheelCollideClass_Members[] =
	{
		{ "alreadyUsed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleWheelCollideClass(
		"hkVehicleWheelCollide",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleWheelCollideClass_Members),
		int(sizeof(hkVehicleWheelCollideClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRejectRayChassisListenerClass_Members[] =
	{
		{ "chassis", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkRejectRayChassisListenerClass(
		"hkRejectRayChassisListener",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRejectRayChassisListenerClass_Members),
		int(sizeof(hkRejectRayChassisListenerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVehicleRaycastWheelCollideClass_Members[] =
	{
		{ "wheelCollisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "phantom", &hkAabbPhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rejectRayChassisListener", &hkRejectRayChassisListenerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVehicleRaycastWheelCollideClass(
		"hkVehicleRaycastWheelCollide",
		&hkVehicleWheelCollideClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVehicleRaycastWheelCollideClass_Members),
		int(sizeof(hkVehicleRaycastWheelCollideClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);

	hkClass* const Classes[] =
	{
		&hk2dAngConstraintAtomClass,
		&hkAabbClass,
		&hkAabbPhantomClass,
		&hkActionClass,
		&hkAngConstraintAtomClass,
		&hkAngFrictionConstraintAtomClass,
		&hkAngLimitConstraintAtomClass,
		&hkAngMotorConstraintAtomClass,
		&hkAngularDashpotActionClass,
		&hkAnimatedReferenceFrameClass,
		&hkAnimationBindingClass,
		&hkAnimationContainerClass,
		&hkAnnotationTrackAnnotationClass,
		&hkAnnotationTrackClass,
		&hkArrayActionClass,
		&hkBallAndSocketConstraintDataAtomsClass,
		&hkBallAndSocketConstraintDataClass,
		&hkBallSocketChainDataClass,
		&hkBallSocketChainDataConstraintInfoClass,
		&hkBallSocketConstraintAtomClass,
		&hkBaseObjectClass,
		&hkBinaryActionClass,
		&hkBitFieldClass,
		&hkBoneAttachmentClass,
		&hkBoneClass,
		&hkBoxMotionClass,
		&hkBoxShapeClass,
		&hkBreakableConstraintDataClass,
		&hkBridgeAtomsClass,
		&hkBridgeConstraintAtomClass,
		&hkBroadPhaseHandleClass,
		&hkBvShapeClass,
		&hkBvTreeShapeClass,
		&hkCachingShapePhantomClass,
		&hkCapsuleShapeClass,
		&hkCdBodyClass,
		&hkCharacterProxyCinfoClass,
		&hkClassClass,
		&hkClassEnumClass,
		&hkClassEnumItemClass,
		&hkClassMemberClass,
		&hkCollidableClass,
		&hkCollidableCollidableFilterClass,
		&hkCollisionFilterClass,
		&hkCollisionFilterListClass,
		&hkConeLimitConstraintAtomClass,
		&hkConstrainedSystemFilterClass,
		&hkConstraintAtomClass,
		&hkConstraintChainDataClass,
		&hkConstraintChainInstanceActionClass,
		&hkConstraintChainInstanceClass,
		&hkConstraintDataClass,
		&hkConstraintInfoClass,
		&hkConstraintInstanceClass,
		&hkConstraintMotorClass,
		&hkContactPointClass,
		&hkContactPointMaterialClass,
		&hkConvexListFilterClass,
		&hkConvexListShapeClass,
		&hkConvexPieceMeshShapeClass,
		&hkConvexPieceStreamDataClass,
		&hkConvexShapeClass,
		&hkConvexTransformShapeClass,
		&hkConvexTranslateShapeClass,
		&hkConvexVerticesShapeClass,
		&hkConvexVerticesShapeFourVectorsClass,
		&hkCylinderShapeClass,
		&hkDashpotActionClass,
		&hkDefaultAnimatedReferenceFrameClass,
		&hkDefaultConvexListFilterClass,
		&hkDeltaCompressedSkeletalAnimationClass,
		&hkDeltaCompressedSkeletalAnimationQuantizationFormatClass,
		&hkDisableEntityCollisionFilterClass,
		&hkDisplayBindingDataClass,
		&hkEntityClass,
		&hkEntityDeactivatorClass,
		&hkExtendedMeshShapeClass,
		&hkExtendedMeshShapeShapesSubpartClass,
		&hkExtendedMeshShapeSubpartClass,
		&hkExtendedMeshShapeTrianglesSubpartClass,
		&hkFakeRigidBodyDeactivatorClass,
		&hkFastMeshShapeClass,
		&hkFixedRigidMotionClass,
		&hkGenericConstraintDataClass,
		&hkGenericConstraintDataSchemeClass,
		&hkGroupCollisionFilterClass,
		&hkGroupFilterClass,
		&hkHeightFieldShapeClass,
		&hkHingeConstraintDataAtomsClass,
		&hkHingeConstraintDataClass,
		&hkHingeLimitsDataAtomsClass,
		&hkHingeLimitsDataClass,
		&hkInterleavedSkeletalAnimationClass,
		&hkKeyframedRigidMotionClass,
		&hkLimitedForceConstraintMotorClass,
		&hkLimitedHingeConstraintDataAtomsClass,
		&hkLimitedHingeConstraintDataClass,
		&hkLinConstraintAtomClass,
		&hkLinFrictionConstraintAtomClass,
		&hkLinLimitConstraintAtomClass,
		&hkLinMotorConstraintAtomClass,
		&hkLinSoftConstraintAtomClass,
		&hkLinearParametricCurveClass,
		&hkLinkedCollidableClass,
		&hkListShapeChildInfoClass,
		&hkListShapeClass,
		&hkMalleableConstraintDataClass,
		&hkMassChangerModifierConstraintAtomClass,
		&hkMaterialClass,
		&hkMaxSizeMotionClass,
		&hkMeshBindingClass,
		&hkMeshBindingMappingClass,
		&hkMeshMaterialClass,
		&hkMeshShapeClass,
		&hkMeshShapeSubpartClass,
		&hkModifierConstraintAtomClass,
		&hkMonitorStreamFrameInfoClass,
		&hkMonitorStreamStringMapClass,
		&hkMonitorStreamStringMapStringMapClass,
		&hkMoppBvTreeShapeClass,
		&hkMoppCodeClass,
		&hkMoppCodeCodeInfoClass,
		&hkMotionClass,
		&hkMotionStateClass,
		&hkMotorActionClass,
		&hkMouseSpringActionClass,
		&hkMovingSurfaceModifierConstraintAtomClass,
		&hkMultiRayShapeClass,
		&hkMultiRayShapeRayClass,
		&hkMultiSphereShapeClass,
		&hkMultiThreadLockClass,
		&hkNullCollisionFilterClass,
		&hkOverwritePivotConstraintAtomClass,
		&hkPackfileHeaderClass,
		&hkPackfileSectionHeaderClass,
		&hkPairwiseCollisionFilterClass,
		&hkPairwiseCollisionFilterCollisionPairClass,
		&hkParametricCurveClass,
		&hkPhantomCallbackShapeClass,
		&hkPhantomClass,
		&hkPhysicsDataClass,
		&hkPhysicsSystemClass,
		&hkPhysicsSystemDisplayBindingClass,
		&hkPlaneShapeClass,
		&hkPointToPathConstraintDataClass,
		&hkPointToPlaneConstraintDataAtomsClass,
		&hkPointToPlaneConstraintDataClass,
		&hkPositionConstraintMotorClass,
		&hkPoweredChainDataClass,
		&hkPoweredChainDataConstraintInfoClass,
		&hkPoweredChainMapperClass,
		&hkPoweredChainMapperLinkInfoClass,
		&hkPoweredChainMapperTargetClass,
		&hkPrismaticConstraintDataAtomsClass,
		&hkPrismaticConstraintDataClass,
		&hkPropertyClass,
		&hkPropertyValueClass,
		&hkPulleyConstraintAtomClass,
		&hkPulleyConstraintDataAtomsClass,
		&hkPulleyConstraintDataClass,
		&hkRagdollConstraintDataAtomsClass,
		&hkRagdollConstraintDataClass,
		&hkRagdollInstanceClass,
		&hkRagdollLimitsDataAtomsClass,
		&hkRagdollLimitsDataClass,
		&hkRagdollMotorConstraintAtomClass,
		&hkRayCollidableFilterClass,
		&hkRayShapeCollectionFilterClass,
		&hkReferencedObjectClass,
		&hkRejectRayChassisListenerClass,
		&hkReorientActionClass,
		&hkRigidBodyClass,
		&hkRigidBodyDeactivatorClass,
		&hkRigidBodyDisplayBindingClass,
		&hkRootLevelContainerClass,
		&hkRootLevelContainerNamedVariantClass,
		&hkSampledHeightFieldShapeClass,
		&hkSerializedDisplayMarkerClass,
		&hkSerializedDisplayMarkerListClass,
		&hkSerializedDisplayRbTransformsClass,
		&hkSerializedDisplayRbTransformsDisplayTransformPairClass,
		&hkSetLocalRotationsConstraintAtomClass,
		&hkSetLocalTransformsConstraintAtomClass,
		&hkSetLocalTranslationsConstraintAtomClass,
		&hkShapeClass,
		&hkShapeCollectionClass,
		&hkShapeCollectionFilterClass,
		&hkShapeContainerClass,
		&hkShapePhantomClass,
		&hkShapeRayCastInputClass,
		&hkSimpleMeshShapeClass,
		&hkSimpleMeshShapeTriangleClass,
		&hkSimpleShapePhantomClass,
		&hkSingleShapeContainerClass,
		&hkSkeletalAnimationClass,
		&hkSkeletonClass,
		&hkSkeletonMapperClass,
		&hkSkeletonMapperDataChainMappingClass,
		&hkSkeletonMapperDataClass,
		&hkSkeletonMapperDataSimpleMappingClass,
		&hkSoftContactModifierConstraintAtomClass,
		&hkSpatialRigidBodyDeactivatorClass,
		&hkSpatialRigidBodyDeactivatorSampleClass,
		&hkSphereClass,
		&hkSphereMotionClass,
		&hkSphereRepShapeClass,
		&hkSphereShapeClass,
		&hkSpringActionClass,
		&hkSpringDamperConstraintMotorClass,
		&hkStabilizedBoxMotionClass,
		&hkStabilizedSphereMotionClass,
		&hkStiffSpringChainDataClass,
		&hkStiffSpringChainDataConstraintInfoClass,
		&hkStiffSpringConstraintAtomClass,
		&hkStiffSpringConstraintDataAtomsClass,
		&hkStiffSpringConstraintDataClass,
		&hkStorageMeshShapeClass,
		&hkStorageMeshShapeSubpartStorageClass,
		&hkStorageSampledHeightFieldShapeClass,
		&hkSweptTransformClass,
		&hkThinBoxMotionClass,
		&hkTransformShapeClass,
		&hkTriSampledHeightFieldBvTreeShapeClass,
		&hkTriSampledHeightFieldCollectionClass,
		&hkTriangleShapeClass,
		&hkTwistLimitConstraintAtomClass,
		&hkTypedBroadPhaseHandleClass,
		&hkTyremarkPointClass,
		&hkTyremarksInfoClass,
		&hkTyremarksWheelClass,
		&hkUnaryActionClass,
		&hkVehicleAerodynamicsClass,
		&hkVehicleBrakeClass,
		&hkVehicleDataClass,
		&hkVehicleDataWheelComponentParamsClass,
		&hkVehicleDefaultAerodynamicsClass,
		&hkVehicleDefaultAnalogDriverInputClass,
		&hkVehicleDefaultBrakeClass,
		&hkVehicleDefaultBrakeWheelBrakingPropertiesClass,
		&hkVehicleDefaultEngineClass,
		&hkVehicleDefaultSteeringClass,
		&hkVehicleDefaultSuspensionClass,
		&hkVehicleDefaultSuspensionWheelSpringSuspensionParametersClass,
		&hkVehicleDefaultTransmissionClass,
		&hkVehicleDefaultVelocityDamperClass,
		&hkVehicleDriverInputAnalogStatusClass,
		&hkVehicleDriverInputClass,
		&hkVehicleDriverInputStatusClass,
		&hkVehicleEngineClass,
		&hkVehicleFrictionDescriptionAxisDescriptionClass,
		&hkVehicleFrictionDescriptionClass,
		&hkVehicleFrictionStatusAxisStatusClass,
		&hkVehicleFrictionStatusClass,
		&hkVehicleInstanceClass,
		&hkVehicleInstanceWheelInfoClass,
		&hkVehicleRaycastWheelCollideClass,
		&hkVehicleSteeringClass,
		&hkVehicleSuspensionClass,
		&hkVehicleSuspensionSuspensionWheelParametersClass,
		&hkVehicleTransmissionClass,
		&hkVehicleVelocityDamperClass,
		&hkVehicleWheelCollideClass,
		&hkVelocityConstraintMotorClass,
		&hkVersioningExceptionsArrayClass,
		&hkVersioningExceptionsArrayVersioningExceptionClass,
		&hkViscousSurfaceModifierConstraintAtomClass,
		&hkWaveletSkeletalAnimationClass,
		&hkWaveletSkeletalAnimationQuantizationFormatClass,
		&hkWheelConstraintDataAtomsClass,
		&hkWheelConstraintDataClass,
		&hkWorldCinfoClass,
		&hkWorldMemoryWatchDogClass,
		&hkWorldObjectClass,
		&hkbAdditiveBinaryBlenderGeneratorClass,
		&hkbAttributeModifierClass,
		&hkbBehaviorClass,
		&hkbBinaryBlenderGeneratorClass,
		&hkbBlenderGeneratorChildClass,
		&hkbBlenderGeneratorClass,
		&hkbBlendingTransitionEffectClass,
		&hkbCharacterBoneInfoClass,
		&hkbCharacterSetupClass,
		&hkbClipGeneratorClass,
		&hkbClipTriggerClass,
		&hkbControlLookAtModifierClass,
		&hkbEventClass,
		&hkbFootIkControlDataClass,
		&hkbFootIkControlsModifierClass,
		&hkbFootIkGainsClass,
		&hkbFootIkModifierClass,
		&hkbGeneratorClass,
		&hkbGetUpModifierClass,
		&hkbHandIkModifierClass,
		&hkbKeyframeDataClass,
		&hkbLookAtModifierClass,
		&hkbModifierClass,
		&hkbModifierGeneratorClass,
		&hkbModifierSequenceClass,
		&hkbNodeClass,
		&hkbPoseMatchingModifierClass,
		&hkbPoweredRagdollControlDataClass,
		&hkbPoweredRagdollControlsModifierClass,
		&hkbPoweredRagdollModifierClass,
		&hkbPredicateClass,
		&hkbRagdollDriverModifierClass,
		&hkbReachModifierClass,
		&hkbReferencePoseGeneratorClass,
		&hkbRigidBodyRagdollControlDataClass,
		&hkbRigidBodyRagdollControlsModifierClass,
		&hkbRigidBodyRagdollModifierClass,
		&hkbStateMachineClass,
		&hkbStateMachineIntervalClass,
		&hkbStateMachineStateInfoClass,
		&hkbStateMachineTransitionInfoClass,
		&hkbStringPredicateClass,
		&hkbTransitionEffectClass,
		&hkbVariableSetClass,
		&hkbVariableSetTargetClass,
		&hkbVariableSetVariableClass,
		&hkxAnimatedFloatClass,
		&hkxAnimatedMatrixClass,
		&hkxAnimatedQuaternionClass,
		&hkxAnimatedVectorClass,
		&hkxAttributeClass,
		&hkxAttributeGroupClass,
		&hkxCameraClass,
		&hkxEnvironmentClass,
		&hkxEnvironmentVariableClass,
		&hkxIndexBufferClass,
		&hkxLightClass,
		&hkxMaterialClass,
		&hkxMaterialEffectClass,
		&hkxMaterialTextureStageClass,
		&hkxMeshClass,
		&hkxMeshSectionClass,
		&hkxNodeAnnotationDataClass,
		&hkxNodeClass,
		&hkxSceneClass,
		&hkxSkinBindingClass,
		&hkxSparselyAnimatedBoolClass,
		&hkxSparselyAnimatedEnumClass,
		&hkxSparselyAnimatedIntClass,
		&hkxSparselyAnimatedStringClass,
		&hkxSparselyAnimatedStringStringTypeClass,
		&hkxTextureFileClass,
		&hkxTextureInplaceClass,
		&hkxVertexBufferClass,
		&hkxVertexFormatClass,
		&hkxVertexP4N4C1T2Class,
		&hkxVertexP4N4T4B4C1T2Class,
		&hkxVertexP4N4T4B4W4I4C1Q2Class,
		&hkxVertexP4N4T4B4W4I4Q4Class,
		&hkxVertexP4N4W4I4C1Q2Class,
		HK_NULL
	}; 

} // namespace hkHavok410r1Classes


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
