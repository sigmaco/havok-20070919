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

namespace hkHavok500r1Classes
{
	const char VersionString[] = "Havok-5.0.0-r1";

	extern hkClass hkAabbClass;
	extern hkClass hkAabbUint32Class;
	extern hkClass hkBaseObjectClass;
	extern hkClass hkBitFieldClass;
	extern hkClass hkClassClass;
	extern hkClass hkClassEnumClass;
	extern hkClass hkClassEnumItemClass;
	extern hkClass hkClassMemberClass;
	extern hkClass hkContactPointClass;
	extern hkClass hkContactPointMaterialClass;
	extern hkClass hkCustomAttributesAttributeClass;
	extern hkClass hkCustomAttributesClass;
	extern hkClass hkMonitorStreamFrameInfoClass;
	extern hkClass hkMonitorStreamStringMapClass;
	extern hkClass hkMonitorStreamStringMapStringMapClass;
	extern hkClass hkMoppBvTreeShapeBaseClass;
	extern hkClass hkMotionStateClass;
	extern hkClass hkMultiThreadCheckClass;
	extern hkClass hkPackfileHeaderClass;
	extern hkClass hkPackfileSectionHeaderClass;
	extern hkClass hkReferencedObjectClass;
	extern hkClass hkRootLevelContainerClass;
	extern hkClass hkRootLevelContainerNamedVariantClass;
	extern hkClass hkSphereClass;
	extern hkClass hkSweptTransformClass;
	extern hkClass hkVariableTweakingHelperBoolVariableInfoClass;
	extern hkClass hkVariableTweakingHelperClass;
	extern hkClass hkVariableTweakingHelperIntVariableInfoClass;
	extern hkClass hkVariableTweakingHelperRealVariableInfoClass;
	extern hkClass hkWorldMemoryAvailableWatchDogClass;
	extern hkClass hkaAnimatedReferenceFrameClass;
	extern hkClass hkaAnimationBindingClass;
	extern hkClass hkaAnimationContainerClass;
	extern hkClass hkaAnnotationTrackAnnotationClass;
	extern hkClass hkaAnnotationTrackClass;
	extern hkClass hkaBoneAttachmentClass;
	extern hkClass hkaBoneClass;
	extern hkClass hkaDefaultAnimatedReferenceFrameClass;
	extern hkClass hkaDeltaCompressedSkeletalAnimationClass;
	extern hkClass hkaDeltaCompressedSkeletalAnimationQuantizationFormatClass;
	extern hkClass hkaInterleavedSkeletalAnimationClass;
	extern hkClass hkaKeyFrameHierarchyUtilityClass;
	extern hkClass hkaKeyFrameHierarchyUtilityControlDataClass;
	extern hkClass hkaMeshBindingClass;
	extern hkClass hkaMeshBindingMappingClass;
	extern hkClass hkaRagdollInstanceClass;
	extern hkClass hkaSkeletalAnimationClass;
	extern hkClass hkaSkeletonClass;
	extern hkClass hkaSkeletonMapperClass;
	extern hkClass hkaSkeletonMapperDataChainMappingClass;
	extern hkClass hkaSkeletonMapperDataClass;
	extern hkClass hkaSkeletonMapperDataSimpleMappingClass;
	extern hkClass hkaWaveletSkeletalAnimationClass;
	extern hkClass hkaWaveletSkeletalAnimationCompressionParamsClass;
	extern hkClass hkaWaveletSkeletalAnimationQuantizationFormatClass;
	extern hkClass hkbAdditiveBinaryBlenderGeneratorClass;
	extern hkClass hkbAlignBoneModifierClass;
	extern hkClass hkbAttachmentModifierAttachmentPropertiesClass;
	extern hkClass hkbAttachmentModifierClass;
	extern hkClass hkbAttachmentSetupClass;
	extern hkClass hkbAttributeModifierAssignmentClass;
	extern hkClass hkbAttributeModifierClass;
	extern hkClass hkbBalanceControllerModifierClass;
	extern hkClass hkbBalanceModifierClass;
	extern hkClass hkbBalanceModifierStepInfoClass;
	extern hkClass hkbBalanceRadialSelectorGeneratorClass;
	extern hkClass hkbBehaviorGraphClass;
	extern hkClass hkbBehaviorGraphDataClass;
	extern hkClass hkbBehaviorGraphStringDataClass;
	extern hkClass hkbBehaviorReferenceGeneratorClass;
	extern hkClass hkbBinaryBlenderGeneratorClass;
	extern hkClass hkbBlenderGeneratorChildClass;
	extern hkClass hkbBlenderGeneratorClass;
	extern hkClass hkbBlendingTransitionEffectClass;
	extern hkClass hkbBoolVariableSequencedDataClass;
	extern hkClass hkbBoolVariableSequencedDataSampleClass;
	extern hkClass hkbCatchFallModifierClass;
	extern hkClass hkbCharacterBoneInfoClass;
	extern hkClass hkbCharacterClass;
	extern hkClass hkbCharacterDataClass;
	extern hkClass hkbCharacterFakeQueueClass;
	extern hkClass hkbCharacterSetupClass;
	extern hkClass hkbCharacterStringDataClass;
	extern hkClass hkbCheckBalanceModifierClass;
	extern hkClass hkbCheckRagdollSpeedModifierClass;
	extern hkClass hkbClimbMountingPredicateClass;
	extern hkClass hkbClipGeneratorClass;
	extern hkClass hkbClipTriggerClass;
	extern hkClass hkbComputeWorldFromModelModifierClass;
	extern hkClass hkbConstrainRigidBodyModifierClass;
	extern hkClass hkbContextClass;
	extern hkClass hkbControlledReachModifierClass;
	extern hkClass hkbCustomTestGeneratorClass;
	extern hkClass hkbCustomTestGeneratorStruckClass;
	extern hkClass hkbDelayedModifierClass;
	extern hkClass hkbDemoConfigCharacterInfoClass;
	extern hkClass hkbDemoConfigClass;
	extern hkClass hkbDemoConfigStickVariableInfoClass;
	extern hkClass hkbDemoConfigTerrainInfoClass;
	extern hkClass hkbEventClass;
	extern hkClass hkbEventSequencedDataClass;
	extern hkClass hkbEventSequencedDataSequencedEventClass;
	extern hkClass hkbFaceTargetModifierClass;
	extern hkClass hkbFootIkControlDataClass;
	extern hkClass hkbFootIkControlsModifierClass;
	extern hkClass hkbFootIkGainsClass;
	extern hkClass hkbFootIkModifierClass;
	extern hkClass hkbFootIkModifierInternalLegDataClass;
	extern hkClass hkbFootIkModifierLegClass;
	extern hkClass hkbGeneratorClass;
	extern hkClass hkbGeneratorOutputClass;
	extern hkClass hkbGeneratorOutputTrackClass;
	extern hkClass hkbGeneratorTransitionEffectClass;
	extern hkClass hkbGetUpModifierClass;
	extern hkClass hkbHandIkControlDataClass;
	extern hkClass hkbHandIkModifierClass;
	extern hkClass hkbHandIkModifierHandClass;
	extern hkClass hkbHoldFromBlendingTransitionEffectClass;
	extern hkClass hkbIntVariableSequencedDataClass;
	extern hkClass hkbIntVariableSequencedDataSampleClass;
	extern hkClass hkbKeyframeBonesModifierClass;
	extern hkClass hkbKeyframeDataClass;
	extern hkClass hkbLookAtModifierClass;
	extern hkClass hkbManualSelectorGeneratorClass;
	extern hkClass hkbMirrorModifierClass;
	extern hkClass hkbMirroredSkeletonInfoClass;
	extern hkClass hkbModifierClass;
	extern hkClass hkbModifierGeneratorClass;
	extern hkClass hkbModifierSequenceClass;
	extern hkClass hkbMoveBoneTowardTargetModifierClass;
	extern hkClass hkbMoveCharacterModifierClass;
	extern hkClass hkbNodeClass;
	extern hkClass hkbPoseMatchingGeneratorClass;
	extern hkClass hkbPoweredRagdollControlDataClass;
	extern hkClass hkbPoweredRagdollControlsModifierClass;
	extern hkClass hkbPoweredRagdollModifierClass;
	extern hkClass hkbPredicateClass;
	extern hkClass hkbProjectDataClass;
	extern hkClass hkbProjectStringDataClass;
	extern hkClass hkbRadialSelectorGeneratorClass;
	extern hkClass hkbRadialSelectorGeneratorGeneratorInfoClass;
	extern hkClass hkbRadialSelectorGeneratorGeneratorPairClass;
	extern hkClass hkbRagdollDriverModifierClass;
	extern hkClass hkbRagdollForceModifierClass;
	extern hkClass hkbReachModifierClass;
	extern hkClass hkbReachTowardTargetModifierClass;
	extern hkClass hkbRealVariableSequencedDataClass;
	extern hkClass hkbRealVariableSequencedDataSampleClass;
	extern hkClass hkbReferencePoseGeneratorClass;
	extern hkClass hkbRigidBodyRagdollControlDataClass;
	extern hkClass hkbRigidBodyRagdollControlsModifierClass;
	extern hkClass hkbRigidBodyRagdollModifierClass;
	extern hkClass hkbRotateCharacterModifierClass;
	extern hkClass hkbSequenceClass;
	extern hkClass hkbSequenceStringDataClass;
	extern hkClass hkbSequencedDataClass;
	extern hkClass hkbStateDependentModifierClass;
	extern hkClass hkbStateMachineActiveTransitionInfoClass;
	extern hkClass hkbStateMachineClass;
	extern hkClass hkbStateMachineProspectiveTransitionInfoClass;
	extern hkClass hkbStateMachineStateInfoClass;
	extern hkClass hkbStateMachineTimeIntervalClass;
	extern hkClass hkbStateMachineTransitionInfoClass;
	extern hkClass hkbStringPredicateClass;
	extern hkClass hkbTargetClass;
	extern hkClass hkbTargetRigidBodyModifierClass;
	extern hkClass hkbTimerModifierClass;
	extern hkClass hkbTransitionEffectClass;
	extern hkClass hkbVariableBindingSetBindingClass;
	extern hkClass hkbVariableBindingSetClass;
	extern hkClass hkbVariableInfoClass;
	extern hkClass hkbVariableSetClass;
	extern hkClass hkbVariableSetTargetClass;
	extern hkClass hkbVariableSetVariableClass;
	extern hkClass hkbVariableValueClass;
	extern hkClass hkp2dAngConstraintAtomClass;
	extern hkClass hkpAabbPhantomClass;
	extern hkClass hkpActionClass;
	extern hkClass hkpAgent1nSectorClass;
	extern hkClass hkpAngConstraintAtomClass;
	extern hkClass hkpAngFrictionConstraintAtomClass;
	extern hkClass hkpAngLimitConstraintAtomClass;
	extern hkClass hkpAngMotorConstraintAtomClass;
	extern hkClass hkpAngularDashpotActionClass;
	extern hkClass hkpArrayActionClass;
	extern hkClass hkpBallAndSocketConstraintDataAtomsClass;
	extern hkClass hkpBallAndSocketConstraintDataClass;
	extern hkClass hkpBallSocketChainDataClass;
	extern hkClass hkpBallSocketChainDataConstraintInfoClass;
	extern hkClass hkpBallSocketConstraintAtomClass;
	extern hkClass hkpBinaryActionClass;
	extern hkClass hkpBoxMotionClass;
	extern hkClass hkpBoxShapeClass;
	extern hkClass hkpBreakableConstraintDataClass;
	extern hkClass hkpBridgeAtomsClass;
	extern hkClass hkpBridgeConstraintAtomClass;
	extern hkClass hkpBroadPhaseHandleClass;
	extern hkClass hkpBvShapeClass;
	extern hkClass hkpBvTreeShapeClass;
	extern hkClass hkpCachingShapePhantomClass;
	extern hkClass hkpCallbackConstraintMotorClass;
	extern hkClass hkpCapsuleShapeClass;
	extern hkClass hkpCdBodyClass;
	extern hkClass hkpCharacterMotionClass;
	extern hkClass hkpCharacterProxyCinfoClass;
	extern hkClass hkpCollidableBoundingVolumeDataClass;
	extern hkClass hkpCollidableClass;
	extern hkClass hkpCollidableCollidableFilterClass;
	extern hkClass hkpCollisionFilterClass;
	extern hkClass hkpCollisionFilterListClass;
	extern hkClass hkpConeLimitConstraintAtomClass;
	extern hkClass hkpConstrainedSystemFilterClass;
	extern hkClass hkpConstraintAtomClass;
	extern hkClass hkpConstraintChainDataClass;
	extern hkClass hkpConstraintChainInstanceActionClass;
	extern hkClass hkpConstraintChainInstanceClass;
	extern hkClass hkpConstraintDataClass;
	extern hkClass hkpConstraintInstanceClass;
	extern hkClass hkpConstraintMotorClass;
	extern hkClass hkpConvexListFilterClass;
	extern hkClass hkpConvexListShapeClass;
	extern hkClass hkpConvexPieceMeshShapeClass;
	extern hkClass hkpConvexPieceStreamDataClass;
	extern hkClass hkpConvexShapeClass;
	extern hkClass hkpConvexTransformShapeClass;
	extern hkClass hkpConvexTranslateShapeClass;
	extern hkClass hkpConvexVerticesShapeClass;
	extern hkClass hkpConvexVerticesShapeFourVectorsClass;
	extern hkClass hkpCylinderShapeClass;
	extern hkClass hkpDashpotActionClass;
	extern hkClass hkpDefaultConvexListFilterClass;
	extern hkClass hkpDisableEntityCollisionFilterClass;
	extern hkClass hkpDisplayBindingDataClass;
	extern hkClass hkpEntityClass;
	extern hkClass hkpEntityDeactivatorClass;
	extern hkClass hkpEntityExtendedListenersClass;
	extern hkClass hkpEntitySmallArraySerializeOverrideTypeClass;
	extern hkClass hkpEntitySpuCollisionCallbackClass;
	extern hkClass hkpExtendedMeshShapeClass;
	extern hkClass hkpExtendedMeshShapeShapesSubpartClass;
	extern hkClass hkpExtendedMeshShapeSubpartClass;
	extern hkClass hkpExtendedMeshShapeTrianglesSubpartClass;
	extern hkClass hkpFakeRigidBodyDeactivatorClass;
	extern hkClass hkpFastMeshShapeClass;
	extern hkClass hkpFixedRigidMotionClass;
	extern hkClass hkpGenericConstraintDataClass;
	extern hkClass hkpGenericConstraintDataSchemeClass;
	extern hkClass hkpGenericConstraintDataSchemeConstraintInfoClass;
	extern hkClass hkpGroupCollisionFilterClass;
	extern hkClass hkpGroupFilterClass;
	extern hkClass hkpHeightFieldShapeClass;
	extern hkClass hkpHingeConstraintDataAtomsClass;
	extern hkClass hkpHingeConstraintDataClass;
	extern hkClass hkpHingeLimitsDataAtomsClass;
	extern hkClass hkpHingeLimitsDataClass;
	extern hkClass hkpKeyframedRigidMotionClass;
	extern hkClass hkpLimitedForceConstraintMotorClass;
	extern hkClass hkpLimitedHingeConstraintDataAtomsClass;
	extern hkClass hkpLimitedHingeConstraintDataClass;
	extern hkClass hkpLinConstraintAtomClass;
	extern hkClass hkpLinFrictionConstraintAtomClass;
	extern hkClass hkpLinLimitConstraintAtomClass;
	extern hkClass hkpLinMotorConstraintAtomClass;
	extern hkClass hkpLinSoftConstraintAtomClass;
	extern hkClass hkpLinearParametricCurveClass;
	extern hkClass hkpLinkedCollidableClass;
	extern hkClass hkpListShapeChildInfoClass;
	extern hkClass hkpListShapeClass;
	extern hkClass hkpMalleableConstraintDataClass;
	extern hkClass hkpMassChangerModifierConstraintAtomClass;
	extern hkClass hkpMaterialClass;
	extern hkClass hkpMaxSizeMotionClass;
	extern hkClass hkpMeshMaterialClass;
	extern hkClass hkpMeshShapeClass;
	extern hkClass hkpMeshShapeSubpartClass;
	extern hkClass hkpModifierConstraintAtomClass;
	extern hkClass hkpMoppBvTreeShapeClass;
	extern hkClass hkpMoppCodeClass;
	extern hkClass hkpMoppCodeCodeInfoClass;
	extern hkClass hkpMoppCodeReindexedTerminalClass;
	extern hkClass hkpMoppEmbeddedShapeClass;
	extern hkClass hkpMotionClass;
	extern hkClass hkpMotorActionClass;
	extern hkClass hkpMouseSpringActionClass;
	extern hkClass hkpMovingSurfaceModifierConstraintAtomClass;
	extern hkClass hkpMultiRayShapeClass;
	extern hkClass hkpMultiRayShapeRayClass;
	extern hkClass hkpMultiSphereShapeClass;
	extern hkClass hkpNullCollisionFilterClass;
	extern hkClass hkpOverwritePivotConstraintAtomClass;
	extern hkClass hkpPackedConvexVerticesShapeClass;
	extern hkClass hkpPackedConvexVerticesShapeFourVectorsClass;
	extern hkClass hkpPackedConvexVerticesShapeVector4IntWClass;
	extern hkClass hkpPairwiseCollisionFilterClass;
	extern hkClass hkpPairwiseCollisionFilterCollisionPairClass;
	extern hkClass hkpParametricCurveClass;
	extern hkClass hkpPhantomCallbackShapeClass;
	extern hkClass hkpPhantomClass;
	extern hkClass hkpPhysicsDataClass;
	extern hkClass hkpPhysicsSystemClass;
	extern hkClass hkpPhysicsSystemDisplayBindingClass;
	extern hkClass hkpPhysicsSystemWithContactsClass;
	extern hkClass hkpPlaneShapeClass;
	extern hkClass hkpPointToPathConstraintDataClass;
	extern hkClass hkpPointToPlaneConstraintDataAtomsClass;
	extern hkClass hkpPointToPlaneConstraintDataClass;
	extern hkClass hkpPositionConstraintMotorClass;
	extern hkClass hkpPoweredChainDataClass;
	extern hkClass hkpPoweredChainDataConstraintInfoClass;
	extern hkClass hkpPoweredChainMapperClass;
	extern hkClass hkpPoweredChainMapperLinkInfoClass;
	extern hkClass hkpPoweredChainMapperTargetClass;
	extern hkClass hkpPrismaticConstraintDataAtomsClass;
	extern hkClass hkpPrismaticConstraintDataClass;
	extern hkClass hkpPropertyClass;
	extern hkClass hkpPropertyValueClass;
	extern hkClass hkpPulleyConstraintAtomClass;
	extern hkClass hkpPulleyConstraintDataAtomsClass;
	extern hkClass hkpPulleyConstraintDataClass;
	extern hkClass hkpRagdollConstraintDataAtomsClass;
	extern hkClass hkpRagdollConstraintDataClass;
	extern hkClass hkpRagdollLimitsDataAtomsClass;
	extern hkClass hkpRagdollLimitsDataClass;
	extern hkClass hkpRagdollMotorConstraintAtomClass;
	extern hkClass hkpRayCollidableFilterClass;
	extern hkClass hkpRayShapeCollectionFilterClass;
	extern hkClass hkpRejectRayChassisListenerClass;
	extern hkClass hkpRemoveTerminalsMoppModifierClass;
	extern hkClass hkpReorientActionClass;
	extern hkClass hkpRigidBodyClass;
	extern hkClass hkpRigidBodyDeactivatorClass;
	extern hkClass hkpRigidBodyDisplayBindingClass;
	extern hkClass hkpRotationalConstraintDataAtomsClass;
	extern hkClass hkpRotationalConstraintDataClass;
	extern hkClass hkpSampledHeightFieldShapeClass;
	extern hkClass hkpSerializedAgentNnEntryClass;
	extern hkClass hkpSerializedDisplayMarkerClass;
	extern hkClass hkpSerializedDisplayMarkerListClass;
	extern hkClass hkpSerializedDisplayRbTransformsClass;
	extern hkClass hkpSerializedDisplayRbTransformsDisplayTransformPairClass;
	extern hkClass hkpSerializedSubTrack1nInfoClass;
	extern hkClass hkpSerializedTrack1nInfoClass;
	extern hkClass hkpSetLocalRotationsConstraintAtomClass;
	extern hkClass hkpSetLocalTransformsConstraintAtomClass;
	extern hkClass hkpSetLocalTranslationsConstraintAtomClass;
	extern hkClass hkpShapeClass;
	extern hkClass hkpShapeCollectionClass;
	extern hkClass hkpShapeCollectionFilterClass;
	extern hkClass hkpShapeContainerClass;
	extern hkClass hkpShapePhantomClass;
	extern hkClass hkpShapeRayCastInputClass;
	extern hkClass hkpSimpleContactConstraintAtomClass;
	extern hkClass hkpSimpleContactConstraintDataInfoClass;
	extern hkClass hkpSimpleMeshShapeClass;
	extern hkClass hkpSimpleMeshShapeTriangleClass;
	extern hkClass hkpSimpleShapePhantomClass;
	extern hkClass hkpSimpleShapePhantomCollisionDetailClass;
	extern hkClass hkpSimulationClass;
	extern hkClass hkpSingleShapeContainerClass;
	extern hkClass hkpSoftContactModifierConstraintAtomClass;
	extern hkClass hkpSpatialRigidBodyDeactivatorClass;
	extern hkClass hkpSpatialRigidBodyDeactivatorSampleClass;
	extern hkClass hkpSphereMotionClass;
	extern hkClass hkpSphereRepShapeClass;
	extern hkClass hkpSphereShapeClass;
	extern hkClass hkpSpringActionClass;
	extern hkClass hkpSpringDamperConstraintMotorClass;
	extern hkClass hkpStabilizedBoxMotionClass;
	extern hkClass hkpStabilizedSphereMotionClass;
	extern hkClass hkpStiffSpringChainDataClass;
	extern hkClass hkpStiffSpringChainDataConstraintInfoClass;
	extern hkClass hkpStiffSpringConstraintAtomClass;
	extern hkClass hkpStiffSpringConstraintDataAtomsClass;
	extern hkClass hkpStiffSpringConstraintDataClass;
	extern hkClass hkpStorageExtendedMeshShapeClass;
	extern hkClass hkpStorageExtendedMeshShapeMeshSubpartStorageClass;
	extern hkClass hkpStorageExtendedMeshShapeShapeSubpartStorageClass;
	extern hkClass hkpStorageMeshShapeClass;
	extern hkClass hkpStorageMeshShapeSubpartStorageClass;
	extern hkClass hkpStorageSampledHeightFieldShapeClass;
	extern hkClass hkpThinBoxMotionClass;
	extern hkClass hkpTransformShapeClass;
	extern hkClass hkpTriSampledHeightFieldBvTreeShapeClass;
	extern hkClass hkpTriSampledHeightFieldCollectionClass;
	extern hkClass hkpTriangleShapeClass;
	extern hkClass hkpTwistLimitConstraintAtomClass;
	extern hkClass hkpTypedBroadPhaseHandleClass;
	extern hkClass hkpTyremarkPointClass;
	extern hkClass hkpTyremarksInfoClass;
	extern hkClass hkpTyremarksWheelClass;
	extern hkClass hkpUnaryActionClass;
	extern hkClass hkpVehicleAerodynamicsClass;
	extern hkClass hkpVehicleBrakeClass;
	extern hkClass hkpVehicleDataClass;
	extern hkClass hkpVehicleDataWheelComponentParamsClass;
	extern hkClass hkpVehicleDefaultAerodynamicsClass;
	extern hkClass hkpVehicleDefaultAnalogDriverInputClass;
	extern hkClass hkpVehicleDefaultBrakeClass;
	extern hkClass hkpVehicleDefaultBrakeWheelBrakingPropertiesClass;
	extern hkClass hkpVehicleDefaultEngineClass;
	extern hkClass hkpVehicleDefaultSteeringClass;
	extern hkClass hkpVehicleDefaultSuspensionClass;
	extern hkClass hkpVehicleDefaultSuspensionWheelSpringSuspensionParametersClass;
	extern hkClass hkpVehicleDefaultTransmissionClass;
	extern hkClass hkpVehicleDefaultVelocityDamperClass;
	extern hkClass hkpVehicleDriverInputAnalogStatusClass;
	extern hkClass hkpVehicleDriverInputClass;
	extern hkClass hkpVehicleDriverInputStatusClass;
	extern hkClass hkpVehicleEngineClass;
	extern hkClass hkpVehicleFrictionDescriptionAxisDescriptionClass;
	extern hkClass hkpVehicleFrictionDescriptionClass;
	extern hkClass hkpVehicleFrictionStatusAxisStatusClass;
	extern hkClass hkpVehicleFrictionStatusClass;
	extern hkClass hkpVehicleInstanceClass;
	extern hkClass hkpVehicleInstanceWheelInfoClass;
	extern hkClass hkpVehicleRaycastWheelCollideClass;
	extern hkClass hkpVehicleSteeringClass;
	extern hkClass hkpVehicleSuspensionClass;
	extern hkClass hkpVehicleSuspensionSuspensionWheelParametersClass;
	extern hkClass hkpVehicleTransmissionClass;
	extern hkClass hkpVehicleVelocityDamperClass;
	extern hkClass hkpVehicleWheelCollideClass;
	extern hkClass hkpVelocityConstraintMotorClass;
	extern hkClass hkpViscousSurfaceModifierConstraintAtomClass;
	extern hkClass hkpWeldingUtilityClass;
	extern hkClass hkpWheelConstraintDataAtomsClass;
	extern hkClass hkpWheelConstraintDataClass;
	extern hkClass hkpWorldCinfoClass;
	extern hkClass hkpWorldClass;
	extern hkClass hkpWorldObjectClass;
	extern hkClass hkxAnimatedFloatClass;
	extern hkClass hkxAnimatedMatrixClass;
	extern hkClass hkxAnimatedQuaternionClass;
	extern hkClass hkxAnimatedVectorClass;
	extern hkClass hkxAttributeClass;
	extern hkClass hkxAttributeGroupClass;
	extern hkClass hkxAttributeHolderClass;
	extern hkClass hkxCameraClass;
	extern hkClass hkxEdgeSelectionChannelClass;
	extern hkClass hkxEnvironmentClass;
	extern hkClass hkxEnvironmentVariableClass;
	extern hkClass hkxIndexBufferClass;
	extern hkClass hkxLightClass;
	extern hkClass hkxMaterialClass;
	extern hkClass hkxMaterialEffectClass;
	extern hkClass hkxMaterialTextureStageClass;
	extern hkClass hkxMeshClass;
	extern hkClass hkxMeshSectionClass;
	extern hkClass hkxMeshUserChannelInfoClass;
	extern hkClass hkxNodeAnnotationDataClass;
	extern hkClass hkxNodeClass;
	extern hkClass hkxNodeSelectionSetClass;
	extern hkClass hkxSceneClass;
	extern hkClass hkxSkinBindingClass;
	extern hkClass hkxSparselyAnimatedBoolClass;
	extern hkClass hkxSparselyAnimatedEnumClass;
	extern hkClass hkxSparselyAnimatedIntClass;
	extern hkClass hkxSparselyAnimatedStringClass;
	extern hkClass hkxSparselyAnimatedStringStringTypeClass;
	extern hkClass hkxTextureFileClass;
	extern hkClass hkxTextureInplaceClass;
	extern hkClass hkxTriangleSelectionChannelClass;
	extern hkClass hkxVertexBufferClass;
	extern hkClass hkxVertexFloatDataChannelClass;
	extern hkClass hkxVertexFormatClass;
	extern hkClass hkxVertexIntDataChannelClass;
	extern hkClass hkxVertexP4N4C1T2Class;
	extern hkClass hkxVertexP4N4T4B4C1T2Class;
	extern hkClass hkxVertexP4N4T4B4W4I4C1Q2Class;
	extern hkClass hkxVertexP4N4T4B4W4I4Q4Class;
	extern hkClass hkxVertexP4N4W4I4C1Q2Class;
	extern hkClass hkxVertexSelectionChannelClass;
	extern hkClass hkxVertexVectorDataChannelClass;

	static hkInternalClassMember hkaAnimationContainerClass_Members[] =
	{
		{ "skeletons", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "animations", &hkaSkeletalAnimationClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "bindings", &hkaAnimationBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "attachments", &hkaBoneAttachmentClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "skins", &hkaMeshBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkaAnimationContainerClass(
		"hkaAnimationContainer",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaAnimationContainerClass_Members),
		HK_COUNT_OF(hkaAnimationContainerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkaAnimationBindingBlendHintEnumItems[] =
	{
		{0, "NORMAL"},
		{1, "ADDITIVE"},
	};
	static const hkInternalClassEnum hkaAnimationBindingEnums[] = {
		{"BlendHint", hkaAnimationBindingBlendHintEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkaAnimationBindingBlendHintEnum = reinterpret_cast<const hkClassEnum*>(&hkaAnimationBindingEnums[0]);
	static hkInternalClassMember hkaAnimationBindingClass_Members[] =
	{
		{ "animation", &hkaSkeletalAnimationClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "animationTrackToBoneIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "blendHint", HK_NULL, hkaAnimationBindingBlendHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkaAnimationBindingClass(
		"hkaAnimationBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkaAnimationBindingEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkaAnimationBindingClass_Members),
		HK_COUNT_OF(hkaAnimationBindingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaAnnotationTrack_AnnotationClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "text", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaAnnotationTrackAnnotationClass(
		"hkaAnnotationTrackAnnotation",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaAnnotationTrack_AnnotationClass_Members),
		HK_COUNT_OF(hkaAnnotationTrack_AnnotationClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaAnnotationTrackClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "annotations", &hkaAnnotationTrackAnnotationClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkaAnnotationTrackClass(
		"hkaAnnotationTrack",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaAnnotationTrackClass_Members),
		HK_COUNT_OF(hkaAnnotationTrackClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkaSkeletalAnimationAnimationTypeEnum;
	static const hkInternalClassEnumItem hkaSkeletalAnimationAnimationTypeEnumItems[] =
	{
		{0, "HK_UNKNOWN_ANIMATION"},
		{1, "HK_INTERLEAVED_ANIMATION"},
		{2, "HK_DELTA_COMPRESSED_ANIMATION"},
		{3, "HK_WAVELET_COMPRESSED_ANIMATION"},
		{4, "HK_MIRRORED_ANIMATION"},
	};
	static const hkInternalClassEnum hkaSkeletalAnimationEnums[] = {
		{"AnimationType", hkaSkeletalAnimationAnimationTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkaSkeletalAnimationAnimationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkaSkeletalAnimationEnums[0]);
	static hkInternalClassMember hkaSkeletalAnimationClass_Members[] =
	{
		{ "type", HK_NULL, hkaSkeletalAnimationAnimationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numberOfTracks", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extractedMotion", &hkaAnimatedReferenceFrameClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "annotationTracks", &hkaAnnotationTrackClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletalAnimationClass(
		"hkaSkeletalAnimation",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkaSkeletalAnimationEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkaSkeletalAnimationClass_Members),
		HK_COUNT_OF(hkaSkeletalAnimationClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members[] =
	{
		{ "maxBitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numD", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaleIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bitWidthIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaDeltaCompressedSkeletalAnimationQuantizationFormatClass(
		"hkaDeltaCompressedSkeletalAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members),
		HK_COUNT_OF(hkaDeltaCompressedSkeletalAnimation_QuantizationFormatClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaDeltaCompressedSkeletalAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkaDeltaCompressedSkeletalAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
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
	hkClass hkaDeltaCompressedSkeletalAnimationClass(
		"hkaDeltaCompressedSkeletalAnimation",
		&hkaSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaDeltaCompressedSkeletalAnimationClass_Members),
		HK_COUNT_OF(hkaDeltaCompressedSkeletalAnimationClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaInterleavedSkeletalAnimationClass_Members[] =
	{
		{ "transforms", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkaInterleavedSkeletalAnimationClass(
		"hkaInterleavedSkeletalAnimation",
		&hkaSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaInterleavedSkeletalAnimationClass_Members),
		HK_COUNT_OF(hkaInterleavedSkeletalAnimationClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaWaveletSkeletalAnimation_CompressionParamsClass_Members[] =
	{
		{ "quantizationBits", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserve", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "truncProp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useOldStyleTruncation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "absolutePositionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "relativePositionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaleTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaWaveletSkeletalAnimationCompressionParamsClass(
		"hkaWaveletSkeletalAnimationCompressionParams",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaWaveletSkeletalAnimation_CompressionParamsClass_Members),
		HK_COUNT_OF(hkaWaveletSkeletalAnimation_CompressionParamsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaWaveletSkeletalAnimation_QuantizationFormatClass_Members[] =
	{
		{ "maxBitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numD", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaleIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bitWidthIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaWaveletSkeletalAnimationQuantizationFormatClass(
		"hkaWaveletSkeletalAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaWaveletSkeletalAnimation_QuantizationFormatClass_Members),
		HK_COUNT_OF(hkaWaveletSkeletalAnimation_QuantizationFormatClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaWaveletSkeletalAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkaWaveletSkeletalAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticMaskIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticDOFsIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockIndexIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockIndexSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedDataSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dataBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkaWaveletSkeletalAnimationClass(
		"hkaWaveletSkeletalAnimation",
		&hkaSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaWaveletSkeletalAnimationClass_Members),
		HK_COUNT_OF(hkaWaveletSkeletalAnimationClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaMeshBinding_MappingClass_Members[] =
	{
		{ "mapping", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkaMeshBindingMappingClass(
		"hkaMeshBindingMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaMeshBinding_MappingClass_Members),
		HK_COUNT_OF(hkaMeshBinding_MappingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaMeshBindingClass_Members[] =
	{
		{ "mesh", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skeleton", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mappings", &hkaMeshBindingMappingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "boneFromSkinMeshTransforms", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_TRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkaMeshBindingClass(
		"hkaMeshBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaMeshBindingClass_Members),
		HK_COUNT_OF(hkaMeshBindingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkaSkeletonMapperConstraintSourceEnumItems[] =
	{
		{0, "NO_CONSTRAINTS"},
		{1, "REFERENCE_POSE"},
		{2, "CURRENT_POSE"},
	};
	static const hkInternalClassEnum hkaSkeletonMapperEnums[] = {
		{"ConstraintSource", hkaSkeletonMapperConstraintSourceEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkaSkeletonMapperConstraintSourceEnum = reinterpret_cast<const hkClassEnum*>(&hkaSkeletonMapperEnums[0]);
	static hkInternalClassMember hkaSkeletonMapperClass_Members[] =
	{
		{ "mapping", &hkaSkeletonMapperDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletonMapperClass(
		"hkaSkeletonMapper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkaSkeletonMapperEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkaSkeletonMapperClass_Members),
		HK_COUNT_OF(hkaSkeletonMapperClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaSkeletonMapperData_SimpleMappingClass_Members[] =
	{
		{ "boneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletonMapperDataSimpleMappingClass(
		"hkaSkeletonMapperDataSimpleMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaSkeletonMapperData_SimpleMappingClass_Members),
		HK_COUNT_OF(hkaSkeletonMapperData_SimpleMappingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaSkeletonMapperData_ChainMappingClass_Members[] =
	{
		{ "startBoneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endBoneA", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startBoneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endBoneB", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startAFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endAFromBTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletonMapperDataChainMappingClass(
		"hkaSkeletonMapperDataChainMapping",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaSkeletonMapperData_ChainMappingClass_Members),
		HK_COUNT_OF(hkaSkeletonMapperData_ChainMappingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaSkeletonMapperDataClass_Members[] =
	{
		{ "skeletonA", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skeletonB", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "simpleMappings", &hkaSkeletonMapperDataSimpleMappingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "chainMappings", &hkaSkeletonMapperDataChainMappingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "unmappedBones", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "keepUnmappedLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletonMapperDataClass(
		"hkaSkeletonMapperData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaSkeletonMapperDataClass_Members),
		HK_COUNT_OF(hkaSkeletonMapperDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkaAnimatedReferenceFrameClass(
		"hkaAnimatedReferenceFrame",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaDefaultAnimatedReferenceFrameClass_Members[] =
	{
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forward", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "referenceFrameSamples", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkaDefaultAnimatedReferenceFrameClass(
		"hkaDefaultAnimatedReferenceFrame",
		&hkaAnimatedReferenceFrameClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaDefaultAnimatedReferenceFrameClass_Members),
		HK_COUNT_OF(hkaDefaultAnimatedReferenceFrameClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaBoneClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lockTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaBoneClass(
		"hkaBone",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaBoneClass_Members),
		HK_COUNT_OF(hkaBoneClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaBoneAttachmentClass_Members[] =
	{
		{ "boneFromAttachment", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachment", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkaBoneAttachmentClass(
		"hkaBoneAttachment",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaBoneAttachmentClass_Members),
		HK_COUNT_OF(hkaBoneAttachmentClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaSkeletonClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parentIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "bones", &hkaBoneClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "referencePose", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkaSkeletonClass(
		"hkaSkeleton",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaSkeletonClass_Members),
		HK_COUNT_OF(hkaSkeletonClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaKeyFrameHierarchyUtility_ControlDataClass_Members[] =
	{
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
		{ "snapMaxAngularDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkaKeyFrameHierarchyUtilityControlData_DefaultStruct
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
			hkReal m_hierarchyGain;
			hkReal m_accelerationGain;
			hkReal m_velocityGain;
			hkReal m_positionGain;
			hkReal m_positionMaxLinearVelocity;
			hkReal m_positionMaxAngularVelocity;
			hkReal m_snapGain;
			hkReal m_snapMaxLinearVelocity;
			hkReal m_snapMaxAngularVelocity;
			hkReal m_snapMaxLinearDistance;
			hkReal m_snapMaxAngularDistance;
		};
		const hkaKeyFrameHierarchyUtilityControlData_DefaultStruct hkaKeyFrameHierarchyUtilityControlData_Default =
		{
			{HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_hierarchyGain),-1,HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_accelerationGain),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_velocityGain),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_positionGain),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_positionMaxLinearVelocity),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_positionMaxAngularVelocity),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_snapGain),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_snapMaxLinearVelocity),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_snapMaxAngularVelocity),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_snapMaxLinearDistance),HK_OFFSET_OF(hkaKeyFrameHierarchyUtilityControlData_DefaultStruct,m_snapMaxAngularDistance)},
			0.17f,1.0f,0.6f,0.05f,1.4f,1.8f,0.1f,0.3f,0.3f,0.03f,0.1f
		};
	}
	hkClass hkaKeyFrameHierarchyUtilityControlDataClass(
		"hkaKeyFrameHierarchyUtilityControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaKeyFrameHierarchyUtility_ControlDataClass_Members),
		HK_COUNT_OF(hkaKeyFrameHierarchyUtility_ControlDataClass_Members),
		&hkaKeyFrameHierarchyUtilityControlData_Default,
		HK_NULL,
		0
		);
	hkClass hkaKeyFrameHierarchyUtilityClass(
		"hkaKeyFrameHierarchyUtility",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkaRagdollInstanceClass_Members[] =
	{
		{ "rigidBodies", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "constraints", &hkpConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "boneToRigidBodyMap", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "skeleton", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkaRagdollInstanceClass(
		"hkaRagdollInstance",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkaRagdollInstanceClass_Members),
		HK_COUNT_OF(hkaRagdollInstanceClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbAttachmentSetupAttachmentTypeEnumItems[] =
	{
		{0, "ATTACHMENT_TYPE_KEYFRAME_RIGID_BODY"},
		{1, "ATTACHMENT_TYPE_BALL_SOCKET_CONSTRAINT"},
		{2, "ATTACHMENT_TYPE_RAGDOLL_CONSTRAINT"},
		{3, "ATTACHMENT_TYPE_SET_WORLD_FROM_MODEL"},
	};
	static const hkInternalClassEnum hkbAttachmentSetupEnums[] = {
		{"AttachmentType", hkbAttachmentSetupAttachmentTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbAttachmentSetupAttachmentTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkbAttachmentSetupEnums[0]);
	static hkInternalClassMember hkbAttachmentSetupClass_Members[] =
	{
		{ "translationLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationLS", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blendInTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "moveAttacherFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attacherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attacheeBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachmentType", HK_NULL, hkbAttachmentSetupAttachmentTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkbAttachmentSetupClass(
		"hkbAttachmentSetup",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbAttachmentSetupEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbAttachmentSetupClass_Members),
		HK_COUNT_OF(hkbAttachmentSetupClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbRoleAttributeRoleEnumItems[] =
	{
		{0, "ROLE_DEFAULT"},
		{1, "ROLE_FILE_NAME"},
		{2, "ROLE_BONE_WEIGHT_ARRAY"},
		{3, "ROLE_BONE_INDEX"},
		{4, "ROLE_BONE_INDEX_MAP"},
		{5, "ROLE_EVENT_ID"},
		{6, "ROLE_VECTOR3"},
	};
	static const hkInternalClassEnumItem hkbRoleAttributeFlagsEnumItems[] =
	{
		{0, "FLAG_NONE"},
		{1, "FLAG_RAGDOLL"},
		{2/*1<<1*/, "FLAG_NORMALIZED"},
		{4/*1<<2*/, "FLAG_NOT_VARIABLE"},
		{8/*1<<3*/, "FLAG_HIDDEN"},
	};
	static const hkInternalClassEnum hkbRoleAttributeEnums[] = {
		{"Role", hkbRoleAttributeRoleEnumItems, 7, HK_NULL, 0 },
		{"Flags", hkbRoleAttributeFlagsEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbRoleAttributeRoleEnum = reinterpret_cast<const hkClassEnum*>(&hkbRoleAttributeEnums[0]);
	extern const hkClassEnum* hkbRoleAttributeFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkbRoleAttributeEnums[1]);
	static const hkInternalClassEnumItem hkbBehaviorGraphVariableModeEnumItems[] =
	{
		{0, "VARIABLE_MODE_DISCARD_WHEN_INACTIVE"},
		{1, "VARIABLE_MODE_MAINTAIN_MEMORY_WHEN_INACTIVE"},
		{2, "VARIABLE_MODE_MAINTAIN_VALUES_WHEN_INACTIVE"},
	};
	static const hkInternalClassEnum hkbBehaviorGraphEnums[] = {
		{"VariableMode", hkbBehaviorGraphVariableModeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbBehaviorGraphVariableModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbBehaviorGraphEnums[0]);
	static hkInternalClassMember hkbBehaviorGraphClass_Members[] =
	{
		{ "variableMode", HK_NULL, hkbBehaviorGraphVariableModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "rootGenerator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "data", &hkbBehaviorGraphDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableSet", &hkbVariableSetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rootGeneratorClone", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "activeNodes", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "activeNodeToIndexMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "eventIdMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "attributeIdMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "variableIdMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "variableValues", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBehaviorGraphClass(
		"hkbBehaviorGraph",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbBehaviorGraphEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbBehaviorGraphClass_Members),
		HK_COUNT_OF(hkbBehaviorGraphClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBehaviorGraphDataClass_Members[] =
	{
		{ "attributeDefaults", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "variableInfos", &hkbVariableInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "stringData", &hkbBehaviorGraphStringDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBehaviorGraphDataClass(
		"hkbBehaviorGraphData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBehaviorGraphDataClass_Members),
		HK_COUNT_OF(hkbBehaviorGraphDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBehaviorGraphStringDataClass_Members[] =
	{
		{ "eventNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "attributeNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "variableNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBehaviorGraphStringDataClass(
		"hkbBehaviorGraphStringData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBehaviorGraphStringDataClass_Members),
		HK_COUNT_OF(hkbBehaviorGraphStringDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCharacter_FakeQueueClass_Members[] =
	{
		{ "p", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "i", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "s", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "b", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCharacterFakeQueueClass(
		"hkbCharacterFakeQueue",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacter_FakeQueueClass_Members),
		HK_COUNT_OF(hkbCharacter_FakeQueueClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCharacterClass_Members[] =
	{
		{ "eventQueue", &hkbCharacterFakeQueueClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "ragdollInstance", &hkaRagdollInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "setup", &hkbCharacterSetupClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "worldFromModel", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL },
		{ "poseLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL },
		{ "deleteWorldFromModel", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deletePoseLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCharacterClass(
		"hkbCharacter",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacterClass_Members),
		HK_COUNT_OF(hkbCharacterClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "clavicleIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "shoulderIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "elbowIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "wristIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "hipIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "kneeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "ankleIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "spineIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "pelvisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "neckIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "headIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingRootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingOtherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingAnotherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbCharacterBoneInfo_DefaultStruct
		{
			int s_defaultOffsets[14];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkInt16 m_poseMatchingRootBoneIndex;
			hkInt16 m_poseMatchingOtherBoneIndex;
			hkInt16 m_poseMatchingAnotherBoneIndex;
		};
		const hkbCharacterBoneInfo_DefaultStruct hkbCharacterBoneInfo_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbCharacterBoneInfo_DefaultStruct,m_poseMatchingRootBoneIndex),HK_OFFSET_OF(hkbCharacterBoneInfo_DefaultStruct,m_poseMatchingOtherBoneIndex),HK_OFFSET_OF(hkbCharacterBoneInfo_DefaultStruct,m_poseMatchingAnotherBoneIndex)},
			-1,-1,-1
		};
	}
	hkClass hkbCharacterBoneInfoClass(
		"hkbCharacterBoneInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbCharacterBoneInfoEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbCharacterBoneInfoClass_Members),
		HK_COUNT_OF(hkbCharacterBoneInfoClass_Members),
		&hkbCharacterBoneInfo_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbMirroredSkeletonInfoClass_Members[] =
	{
		{ "rootOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "nubOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mirrorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bonePairMap", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "mixed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbMirroredSkeletonInfo_DefaultStruct
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
			_hkQsTransform m_rootOrientation;
			_hkQsTransform m_childOrientation;
			_hkQsTransform m_nubOrientation;
			_hkVector4 m_mirrorAxis;
		};
		const hkbMirroredSkeletonInfo_DefaultStruct hkbMirroredSkeletonInfo_Default =
		{
			{HK_OFFSET_OF(hkbMirroredSkeletonInfo_DefaultStruct,m_rootOrientation),HK_OFFSET_OF(hkbMirroredSkeletonInfo_DefaultStruct,m_childOrientation),HK_OFFSET_OF(hkbMirroredSkeletonInfo_DefaultStruct,m_nubOrientation),HK_OFFSET_OF(hkbMirroredSkeletonInfo_DefaultStruct,m_mirrorAxis),-1,-1},
		{0,0,0,0,0,0,0,1,1,1,1,1},	{0,0,0,0,0,0,0,1,1,1,1,1},	{0,0,0,0,0,0,0,1,1,1,1,1},	{1,0,0,0}
		};
	}
	hkClass hkbMirroredSkeletonInfoClass(
		"hkbMirroredSkeletonInfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbMirroredSkeletonInfoClass_Members),
		HK_COUNT_OF(hkbMirroredSkeletonInfoClass_Members),
		&hkbMirroredSkeletonInfo_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCharacterDataClass_Members[] =
	{
		{ "animationBoneInfo", &hkbCharacterBoneInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollBoneInfo", &hkbCharacterBoneInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelUpMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelForwardMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelRightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stringData", &hkbCharacterStringDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mirroredSkeletonInfo", &hkbMirroredSkeletonInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCharacterDataClass(
		"hkbCharacterData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacterDataClass_Members),
		HK_COUNT_OF(hkbCharacterDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCharacterSetupClass_Members[] =
	{
		{ "animationSkeleton", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "ragdollSkeleton", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "ragdollToAnimationSkeletonMapper", &hkaSkeletonMapperClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "animationToRagdollSkeletonMapper", &hkaSkeletonMapperClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "data", &hkbCharacterDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mirroredSkeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbCharacterSetupClass(
		"hkbCharacterSetup",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacterSetupClass_Members),
		HK_COUNT_OF(hkbCharacterSetupClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCharacterStringDataClass_Members[] =
	{
		{ "deformableSkinNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "rigidSkinNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "animationNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "animationFilenames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rigName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCharacterStringDataClass(
		"hkbCharacterStringData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCharacterStringDataClass_Members),
		HK_COUNT_OF(hkbCharacterStringDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbContextClass_Members[] =
	{
		{ "character", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "rootBehavior", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "behavior", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "projectData", &hkbProjectDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "attachmentManager", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "animationCache", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbContextClass(
		"hkbContext",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbContextClass_Members),
		HK_COUNT_OF(hkbContextClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbEventSystemEventIdsEnumItems[] =
	{
		{-1, "EVENT_ID_NULL"},
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
		HK_COUNT_OF(hkbEventClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbGeneratorOutputStandardTracksEnumItems[] =
	{
		{0, "TRACK_WORLD_FROM_MODEL"},
		{1, "TRACK_POSE"},
		{2, "TRACK_RIGID_BODY_RAGDOLL_CONTROLS"},
		{3, "TRACK_POWERED_RAGDOLL_CONTROLS"},
		{4, "TRACK_POWERED_RAGDOLL_BONE_WEIGHTS"},
		{5, "TRACK_KEYFRAMED_RAGDOLL_BONES"},
		{6, "TRACK_ATTRIBUTES"},
		{7, "TRACK_FOOT_IK_CONTROLS"},
		{8, "TRACK_BONE_FORCES"},
		{9, "TRACK_HAND_IK_CONTROLS"},
		{10, "NUM_STANDARD_TRACKS"},
	};
	static const hkInternalClassEnumItem hkbGeneratorOutputTrackTypesEnumItems[] =
	{
		{0, "TRACK_TYPE_REAL"},
		{1, "TRACK_TYPE_QSTRANSFORM"},
	};
	static const hkInternalClassEnum hkbGeneratorOutputEnums[] = {
		{"StandardTracks", hkbGeneratorOutputStandardTracksEnumItems, 11, HK_NULL, 0 },
		{"TrackTypes", hkbGeneratorOutputTrackTypesEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbGeneratorOutputStandardTracksEnum = reinterpret_cast<const hkClassEnum*>(&hkbGeneratorOutputEnums[0]);
	extern const hkClassEnum* hkbGeneratorOutputTrackTypesEnum = reinterpret_cast<const hkClassEnum*>(&hkbGeneratorOutputEnums[1]);
	static hkInternalClassMember hkbGeneratorOutput_TrackClass_Members[] =
	{
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "onFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, hkbGeneratorOutputTrackTypesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkbGeneratorOutputTrackClass(
		"hkbGeneratorOutputTrack",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbGeneratorOutput_TrackClass_Members),
		HK_COUNT_OF(hkbGeneratorOutput_TrackClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbGeneratorOutputClass_Members[] =
	{
		{ "skeleton", &hkaSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tracks", &hkbGeneratorOutputTrackClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "trackBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkbGeneratorOutputClass(
		"hkbGeneratorOutput",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbGeneratorOutputEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbGeneratorOutputClass_Members),
		HK_COUNT_OF(hkbGeneratorOutputClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBehaviorReferenceGeneratorClass_Members[] =
	{
		{ "behaviorName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "behavior", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBehaviorReferenceGeneratorClass(
		"hkbBehaviorReferenceGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBehaviorReferenceGeneratorClass_Members),
		HK_COUNT_OF(hkbBehaviorReferenceGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBinaryBlenderGeneratorClass_Members[] =
	{
		{ "blendWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialBlendWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sync", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfSyncMasterChild", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
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
			hkReal m_initialBlendWeight;
			hkInt8 m_indexOfSyncMasterChild;
		};
		const hkbBinaryBlenderGenerator_DefaultStruct hkbBinaryBlenderGenerator_Default =
		{
			{-1,HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_initialBlendWeight),-1,HK_OFFSET_OF(hkbBinaryBlenderGenerator_DefaultStruct,m_indexOfSyncMasterChild),-1,-1,-1},
			-1.0,-1
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
		HK_COUNT_OF(hkbBinaryBlenderGeneratorClass_Members),
		&hkbBinaryBlenderGenerator_Default,
		HK_NULL,
		0
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
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbBlenderGeneratorChildOperandTypeEnumItems[] =
	{
		{0, "OPERAND_TYPE_BLEND"},
		{1, "OPERAND_TYPE_ADD"},
		{2, "OPERAND_TYPE_SUBTRACT"},
	};
	static const hkInternalClassEnum hkbBlenderGeneratorChildEnums[] = {
		{"OperandType", hkbBlenderGeneratorChildOperandTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbBlenderGeneratorChildOperandTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlenderGeneratorChildEnums[0]);
	static hkInternalClassMember hkbBlenderGeneratorChildClass_Members[] =
	{
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "weight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "worldFromModelWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boneWeights", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "operandType", HK_NULL, hkbBlenderGeneratorChildOperandTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "syncNextFrame", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBlenderGeneratorChild_DefaultStruct
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
			hkReal m_worldFromModelWeight;
		};
		const hkbBlenderGeneratorChild_DefaultStruct hkbBlenderGeneratorChild_Default =
		{
			{-1,-1,HK_OFFSET_OF(hkbBlenderGeneratorChild_DefaultStruct,m_worldFromModelWeight),-1,-1,-1,-1},
			1.0
		};
	}
	hkClass hkbBlenderGeneratorChildClass(
		"hkbBlenderGeneratorChild",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbBlenderGeneratorChildEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbBlenderGeneratorChildClass_Members),
		HK_COUNT_OF(hkbBlenderGeneratorChildClass_Members),
		&hkbBlenderGeneratorChild_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbBlenderGeneratorFlagBitsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_SYNC"},
		{4/*0x4*/, "FLAG_SMOOTH_GENERATOR_WEIGHTS"},
		{8/*0x8*/, "FLAG_DONT_DEACTIVATE_CHILDREN_WITH_ZERO_WEIGHTS"},
		{16/*0x10*/, "FLAG_PARAMETRIC_BLEND"},
		{32/*0x20*/, "FLAG_IS_PARAMETRIC_BLEND_CYCLIC"},
	};
	static const hkInternalClassEnum hkbBlenderGeneratorEnums[] = {
		{"FlagBits", hkbBlenderGeneratorFlagBitsEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbBlenderGeneratorFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlenderGeneratorEnums[0]);
	static hkInternalClassMember hkbBlenderGeneratorClass_Members[] =
	{
		{ "referencePoseWeightThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blendParameter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minCyclicBlendParameter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxCyclicBlendParameter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexOfSyncMasterChild", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "children", &hkbBlenderGeneratorChildClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "numChildFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "numActiveChildren", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "endIntervalWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "endIntervalIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBlenderGenerator_DefaultStruct
		{
			int s_defaultOffsets[14];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_maxCyclicBlendParameter;
			hkInt16 m_indexOfSyncMasterChild;
		};
		const hkbBlenderGenerator_DefaultStruct hkbBlenderGenerator_Default =
		{
			{-1,-1,-1,HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_maxCyclicBlendParameter),HK_OFFSET_OF(hkbBlenderGenerator_DefaultStruct,m_indexOfSyncMasterChild),-1,-1,-1,-1,-1,-1,-1,-1,-1},
			1.0,-1
		};
	}
	hkClass hkbBlenderGeneratorClass(
		"hkbBlenderGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbBlenderGeneratorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbBlenderGeneratorClass_Members),
		HK_COUNT_OF(hkbBlenderGeneratorClass_Members),
		&hkbBlenderGenerator_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbClipTriggerClass_Members[] =
	{
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "event", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "relativeToEndOfClip", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "acyclic", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkbClipTriggerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbClipGeneratorPlaybackModeEnumItems[] =
	{
		{0, "MODE_SINGLE_PLAY"},
		{1, "MODE_LOOPING"},
		{2, "MODE_USER_CONTROLLED"},
		{3, "MODE_PING_PONG"},
		{4, "MODE_COUNT"},
	};
	static const hkInternalClassEnumItem hkbClipGeneratorFlagsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_CONTINUE_MOTION_AT_END"},
		{2/*0x2*/, "FLAG_SYNC_HALF_CYCLE_IN_PING_PONG_MODE"},
		{4/*0x4*/, "FLAG_MIRROR"},
	};
	static const hkInternalClassEnum hkbClipGeneratorEnums[] = {
		{"PlaybackMode", hkbClipGeneratorPlaybackModeEnumItems, 5, HK_NULL, 0 },
		{"Flags", hkbClipGeneratorFlagsEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbClipGeneratorPlaybackModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbClipGeneratorEnums[0]);
	extern const hkClassEnum* hkbClipGeneratorFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkbClipGeneratorEnums[1]);
	static hkInternalClassMember hkbClipGeneratorClass_Members[] =
	{
		{ "mode", HK_NULL, hkbClipGeneratorPlaybackModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "cropStartAmountLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cropEndAmountLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "playbackSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enforcedDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userControlledTimeFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "animationName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triggers", &hkbClipTriggerClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extractedMotion", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "echos", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "animationControl", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "atEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "ignoreStartTime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "pingPongBackward", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbClipGeneratorClass(
		"hkbClipGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbClipGeneratorEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbClipGeneratorClass_Members),
		HK_COUNT_OF(hkbClipGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbModifierGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbPoseMatchingGeneratorModeEnumItems[] =
	{
		{0, "MODE_MATCH"},
		{1, "MODE_PLAY"},
	};
	static const hkInternalClassEnum hkbPoseMatchingGeneratorEnums[] = {
		{"Mode", hkbPoseMatchingGeneratorModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbPoseMatchingGeneratorModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbPoseMatchingGeneratorEnums[0]);
	static hkInternalClassMember hkbPoseMatchingGeneratorClass_Members[] =
	{
		{ "blendSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minSpeedToSwitch", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minSwitchTimeNoError", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minSwitchTimeFullError", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startPlayingEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "otherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "anotherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mode", HK_NULL, hkbPoseMatchingGeneratorModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "currentMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "bestMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceBetterMatch", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "error", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "poseMatchingUtility", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbPoseMatchingGenerator_DefaultStruct
		{
			int s_defaultOffsets[14];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_blendSpeed;
			hkReal m_minSpeedToSwitch;
			hkReal m_minSwitchTimeNoError;
			hkInt32 m_startPlayingEventId;
			hkInt16 m_rootBoneIndex;
			hkInt16 m_otherBoneIndex;
			hkInt16 m_anotherBoneIndex;
		};
		const hkbPoseMatchingGenerator_DefaultStruct hkbPoseMatchingGenerator_Default =
		{
			{HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_blendSpeed),HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_minSpeedToSwitch),HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_minSwitchTimeNoError),-1,HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_startPlayingEventId),HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_rootBoneIndex),HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_otherBoneIndex),HK_OFFSET_OF(hkbPoseMatchingGenerator_DefaultStruct,m_anotherBoneIndex),-1,-1,-1,-1,-1,-1},
			1.0f,0.2f,0.2f,-1,-1,-1,-1
		};
	}
	hkClass hkbPoseMatchingGeneratorClass(
		"hkbPoseMatchingGenerator",
		&hkbBlenderGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbPoseMatchingGeneratorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbPoseMatchingGeneratorClass_Members),
		HK_COUNT_OF(hkbPoseMatchingGeneratorClass_Members),
		&hkbPoseMatchingGenerator_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbReferencePoseGeneratorClass_Members[] =
	{
		{ "skeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
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
		HK_COUNT_OF(hkbReferencePoseGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbAttachmentModifier_AttachmentPropertiesClass_Members[] =
	{
		{ "attacheeName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensingRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachmentSetupIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "detachEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sendToAttacherOnAttach", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sendToAttacheeOnAttach", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sendToAttacherOnDetach", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sendToAttacheeOnDetach", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attacheePropertyKey", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensingLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attacheeLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensingRagdollBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbAttachmentModifierAttachmentProperties_DefaultStruct
		{
			int s_defaultOffsets[13];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkReal m_sensingRadius;
			hkInt32 m_attachEventId;
			hkInt32 m_detachEventId;
			hkInt32 m_sendToAttacherOnAttach;
			hkInt32 m_sendToAttacheeOnAttach;
			hkInt32 m_sendToAttacherOnDetach;
			hkInt32 m_sendToAttacheeOnDetach;
			hkInt32 m_sensingRagdollBoneIndex;
		};
		const hkbAttachmentModifierAttachmentProperties_DefaultStruct hkbAttachmentModifierAttachmentProperties_Default =
		{
			{-1,HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sensingRadius),-1,HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_attachEventId),HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_detachEventId),HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sendToAttacherOnAttach),HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sendToAttacheeOnAttach),HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sendToAttacherOnDetach),HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sendToAttacheeOnDetach),-1,-1,-1,HK_OFFSET_OF(hkbAttachmentModifierAttachmentProperties_DefaultStruct,m_sensingRagdollBoneIndex)},
			1.0f,-1,-1,-1,-1,-1,-1,-1
		};
	}
	hkClass hkbAttachmentModifierAttachmentPropertiesClass(
		"hkbAttachmentModifierAttachmentProperties",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbAttachmentModifier_AttachmentPropertiesClass_Members),
		HK_COUNT_OF(hkbAttachmentModifier_AttachmentPropertiesClass_Members),
		&hkbAttachmentModifierAttachmentProperties_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbAttachmentModifierClass_Members[] =
	{
		{ "attachmentProperties", &hkbAttachmentModifierAttachmentPropertiesClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "attachmentData", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbAttachmentModifierClass(
		"hkbAttachmentModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbAttachmentModifierClass_Members),
		HK_COUNT_OF(hkbAttachmentModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbAttributeModifier_AssignmentClass_Members[] =
	{
		{ "attributeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attributeValue", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbAttributeModifierAssignment_DefaultStruct
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
			int m_attributeIndex;
		};
		const hkbAttributeModifierAssignment_DefaultStruct hkbAttributeModifierAssignment_Default =
		{
			{HK_OFFSET_OF(hkbAttributeModifierAssignment_DefaultStruct,m_attributeIndex),-1},
			-1
		};
	}
	hkClass hkbAttributeModifierAssignmentClass(
		"hkbAttributeModifierAssignment",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbAttributeModifier_AssignmentClass_Members),
		HK_COUNT_OF(hkbAttributeModifier_AssignmentClass_Members),
		&hkbAttributeModifierAssignment_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbAttributeModifierClass_Members[] =
	{
		{ "assignments", &hkbAttributeModifierAssignmentClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkbAttributeModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFootIkControlDataClass_Members[] =
	{
		{ "gains", &hkbFootIkGainsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
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
		HK_COUNT_OF(hkbFootIkControlDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbFootIkControlsModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFootIkGainsClass_Members[] =
	{
		{ "onOffGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "groundAscendingGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "groundDescendingGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footPlantedGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footRaisedGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footUnlockGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pelvisFeedbackGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignWorldFromModelGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hipOrientationGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbFootIkGains_DefaultStruct
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
			hkReal m_onOffGain;
			hkReal m_groundAscendingGain;
			hkReal m_groundDescendingGain;
			hkReal m_footPlantedGain;
			hkReal m_footRaisedGain;
			hkReal m_footUnlockGain;
		};
		const hkbFootIkGains_DefaultStruct hkbFootIkGains_Default =
		{
			{HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_onOffGain),HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_groundAscendingGain),HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_groundDescendingGain),HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_footPlantedGain),HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_footRaisedGain),HK_OFFSET_OF(hkbFootIkGains_DefaultStruct,m_footUnlockGain),-1,-1,-1},
			0.2f,1.0f,1.0f,1.0f,1.0f,1.0f
		};
	}
	hkClass hkbFootIkGainsClass(
		"hkbFootIkGains",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkGainsClass_Members),
		HK_COUNT_OF(hkbFootIkGainsClass_Members),
		&hkbFootIkGains_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFootIkModifier_LegClass_Members[] =
	{
		{ "originalAnkleTransformMS", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "kneeAxisLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footEndLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footPlantedAnkleHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footRaisedAnkleHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAnkleHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minAnkleHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cosineMaxKneeAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cosineMinKneeAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "legIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hipIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "kneeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ankleIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isOriginalAnkleTransformMSSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbFootIkModifierLeg_DefaultStruct
		{
			int s_defaultOffsets[14];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			_hkQsTransform m_originalAnkleTransformMS;
			_hkVector4 m_kneeAxisLS;
			_hkVector4 m_footEndLS;
			hkReal m_maxAnkleHeightMS;
			hkReal m_minAnkleHeightMS;
			hkReal m_cosineMaxKneeAngle;
			hkReal m_cosineMinKneeAngle;
			hkInt16 m_legIndex;
			hkInt16 m_hipIndex;
			hkInt16 m_kneeIndex;
			hkInt16 m_ankleIndex;
		};
		const hkbFootIkModifierLeg_DefaultStruct hkbFootIkModifierLeg_Default =
		{
			{HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_originalAnkleTransformMS),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_kneeAxisLS),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_footEndLS),-1,-1,HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_maxAnkleHeightMS),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_minAnkleHeightMS),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_cosineMaxKneeAngle),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_cosineMinKneeAngle),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_legIndex),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_hipIndex),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_kneeIndex),HK_OFFSET_OF(hkbFootIkModifierLeg_DefaultStruct,m_ankleIndex),-1},
		{0,0,0,0,0,0,0,1,1,1,1,1},	{1,0,0},	{0,0,0},0.7f,-0.1f,-1,1,-1,-1,-1,-1
		};
	}
	hkClass hkbFootIkModifierLegClass(
		"hkbFootIkModifierLeg",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkModifier_LegClass_Members),
		HK_COUNT_OF(hkbFootIkModifier_LegClass_Members),
		&hkbFootIkModifierLeg_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFootIkModifier_InternalLegDataClass_Members[] =
	{
		{ "groundPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "footIkSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "verticalError", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hitSomething", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbFootIkModifierInternalLegDataClass(
		"hkbFootIkModifierInternalLegData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFootIkModifier_InternalLegDataClass_Members),
		HK_COUNT_OF(hkbFootIkModifier_InternalLegDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFootIkModifierClass_Members[] =
	{
		{ "gains", &hkbFootIkGainsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "legs", &hkbFootIkModifierLegClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "raycastDistanceUp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "raycastDistanceDown", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "originalGroundHeightMS", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useTrackData", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lockFeetWhenPlanted", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useCharacterUpVector", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isSetUp", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "raycastInterface", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "internalLegData", &hkbFootIkModifierInternalLegDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "prevIsFootIkEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbFootIkModifier_DefaultStruct
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
			hkReal m_raycastDistanceUp;
			hkReal m_raycastDistanceDown;
			_hkBool m_useTrackData;
		};
		const hkbFootIkModifier_DefaultStruct hkbFootIkModifier_Default =
		{
			{-1,-1,HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_raycastDistanceUp),HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_raycastDistanceDown),-1,HK_OFFSET_OF(hkbFootIkModifier_DefaultStruct,m_useTrackData),-1,-1,-1,-1,-1,-1},
			0.5f,0.8f,true
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
		HK_COUNT_OF(hkbFootIkModifierClass_Members),
		&hkbFootIkModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbGetUpModifierClass_Members[] =
	{
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initNextModify", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeStep", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
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
		};
		const hkbGetUpModifier_DefaultStruct hkbGetUpModifier_Default =
		{
			{HK_OFFSET_OF(hkbGetUpModifier_DefaultStruct,m_duration),-1,-1,-1},
			1.0
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
		HK_COUNT_OF(hkbGetUpModifierClass_Members),
		&hkbGetUpModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbHandIkControlDataClass_Members[] =
	{
		{ "targetPositionInWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetNormalInWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutPositionDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutNormalDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "onFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbHandIkControlDataClass(
		"hkbHandIkControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbHandIkControlDataClass_Members),
		HK_COUNT_OF(hkbHandIkControlDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbHandIkModifier_HandClass_Members[] =
	{
		{ "elbowAxisLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "backHandNormalInHandSpace", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cosineMaxElbowAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cosineMinElbowAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbHandIkModifierHand_DefaultStruct
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
			hkReal m_cosineMaxElbowAngle;
			hkReal m_cosineMinElbowAngle;
			hkInt16 m_handIndex;
		};
		const hkbHandIkModifierHand_DefaultStruct hkbHandIkModifierHand_Default =
		{
			{-1,-1,HK_OFFSET_OF(hkbHandIkModifierHand_DefaultStruct,m_cosineMaxElbowAngle),HK_OFFSET_OF(hkbHandIkModifierHand_DefaultStruct,m_cosineMinElbowAngle),HK_OFFSET_OF(hkbHandIkModifierHand_DefaultStruct,m_handIndex)},
			-1.0,1.0,-1
		};
	}
	hkClass hkbHandIkModifierHandClass(
		"hkbHandIkModifierHand",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbHandIkModifier_HandClass_Members),
		HK_COUNT_OF(hkbHandIkModifier_HandClass_Members),
		&hkbHandIkModifierHand_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbHandIkModifierClass_Members[] =
	{
		{ "hands", &hkbHandIkModifierHandClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "internalHandData", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
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
		HK_COUNT_OF(hkbHandIkModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbLookAtModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkbMirrorModifierClass(
		"hkbMirrorModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbKeyframeBonesModifierClass_Members[] =
	{
		{ "keyframedBones", &hkBitFieldClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbKeyframeBonesModifierClass(
		"hkbKeyframeBonesModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbKeyframeBonesModifierClass_Members),
		HK_COUNT_OF(hkbKeyframeBonesModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbKeyframeDataClass_Members[] =
	{
		{ "isDataInitialized", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "keyframeData", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbKeyframeDataClass(
		"hkbKeyframeData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbKeyframeDataClass_Members),
		HK_COUNT_OF(hkbKeyframeDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbPoweredRagdollControlDataClass_Members[] =
	{
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proportionalRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constantRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbPoweredRagdollControlData_DefaultStruct
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
			hkReal m_maxForce;
			hkReal m_tau;
			hkReal m_damping;
			hkReal m_proportionalRecoveryVelocity;
			hkReal m_constantRecoveryVelocity;
		};
		const hkbPoweredRagdollControlData_DefaultStruct hkbPoweredRagdollControlData_Default =
		{
			{HK_OFFSET_OF(hkbPoweredRagdollControlData_DefaultStruct,m_maxForce),HK_OFFSET_OF(hkbPoweredRagdollControlData_DefaultStruct,m_tau),HK_OFFSET_OF(hkbPoweredRagdollControlData_DefaultStruct,m_damping),HK_OFFSET_OF(hkbPoweredRagdollControlData_DefaultStruct,m_proportionalRecoveryVelocity),HK_OFFSET_OF(hkbPoweredRagdollControlData_DefaultStruct,m_constantRecoveryVelocity)},
			200.0f,0.8f,1.0f,2.0f,1.0f
		};
	}
	hkClass hkbPoweredRagdollControlDataClass(
		"hkbPoweredRagdollControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbPoweredRagdollControlDataClass_Members),
		HK_COUNT_OF(hkbPoweredRagdollControlDataClass_Members),
		&hkbPoweredRagdollControlData_Default,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbPoweredRagdollControlsModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "computeWorldFromModelMode", HK_NULL, hkbPoweredRagdollModifierComputeWorldFromModelModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "fixConstraintsTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useLocking", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timeActive", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "keyframedBones", &hkBitFieldClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keyframeData", &hkbKeyframeDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "boneWeights", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkbPoweredRagdollModifierClass(
		"hkbPoweredRagdollModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbPoweredRagdollModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbPoweredRagdollModifierClass_Members),
		HK_COUNT_OF(hkbPoweredRagdollModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRagdollDriverModifierClass_Members[] =
	{
		{ "addRagdollToWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "removeRagdollFromWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poweredRagdollModifier", &hkbPoweredRagdollModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rigidBodyRagdollModifier", &hkbRigidBodyRagdollModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "ragdollForceModifier", &hkbRagdollForceModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "activeModifier", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isRagdollForceModifierActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "doSetup", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRagdollDriverModifier_DefaultStruct
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
			_hkBool m_doSetup;
		};
		const hkbRagdollDriverModifier_DefaultStruct hkbRagdollDriverModifier_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbRagdollDriverModifier_DefaultStruct,m_doSetup)},
			true
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
		HK_COUNT_OF(hkbRagdollDriverModifierClass_Members),
		&hkbRagdollDriverModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRagdollForceModifierClass_Members[] =
	{
		{ "boneForces", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRagdollForceModifierClass(
		"hkbRagdollForceModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRagdollForceModifierClass_Members),
		HK_COUNT_OF(hkbRagdollForceModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRigidBodyRagdollControlDataClass_Members[] =
	{
		{ "keyFrameHierarchyControlData", &hkaKeyFrameHierarchyUtilityControlDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "durationToBlend", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRigidBodyRagdollControlData_DefaultStruct
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
			hkReal m_durationToBlend;
		};
		const hkbRigidBodyRagdollControlData_DefaultStruct hkbRigidBodyRagdollControlData_Default =
		{
			{-1,HK_OFFSET_OF(hkbRigidBodyRagdollControlData_DefaultStruct,m_durationToBlend)},
			1.0f
		};
	}
	hkClass hkbRigidBodyRagdollControlDataClass(
		"hkbRigidBodyRagdollControlData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRigidBodyRagdollControlDataClass_Members),
		HK_COUNT_OF(hkbRigidBodyRagdollControlDataClass_Members),
		&hkbRigidBodyRagdollControlData_Default,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbRigidBodyRagdollControlsModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRigidBodyRagdollModifierClass_Members[] =
	{
		{ "controlDataPalette", &hkaKeyFrameHierarchyUtilityControlDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "bodyIndexToPaletteIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "keyframedBones", &hkBitFieldClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rigidBodyController", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "doSetupNextEvaluate", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRigidBodyRagdollModifier_DefaultStruct
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
			_hkBool m_doSetupNextEvaluate;
		};
		const hkbRigidBodyRagdollModifier_DefaultStruct hkbRigidBodyRagdollModifier_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkbRigidBodyRagdollModifier_DefaultStruct,m_doSetupNextEvaluate),-1,-1},
			true
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
		HK_COUNT_OF(hkbRigidBodyRagdollModifierClass_Members),
		&hkbRigidBodyRagdollModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbReachModifierClass_Members[] =
	{
		{ "raycastInterface", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "reachWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "previousReachPointWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "previousNormalWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "radarLocationRS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "moveGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "leaveGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "raycastLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachReferenceBoneIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "handIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "isHandEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkbReachModifierClass(
		"hkbReachModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbReachModifierClass_Members),
		HK_COUNT_OF(hkbReachModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbModifierSequenceClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbNodeGetChildrenFlagBitsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_ACTIVE_ONLY"},
		{2/*0x2*/, "FLAG_GENERATORS_ONLY"},
		{4/*0x4*/, "FLAG_COMPUTE_CHILD_SPEEDS"},
	};
	static const hkInternalClassEnum hkbNodeEnums[] = {
		{"GetChildrenFlagBits", hkbNodeGetChildrenFlagBitsEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbNodeGetChildrenFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbNodeEnums[0]);
	static hkInternalClassMember hkbNodeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "variableBindingSet", &hkbVariableBindingSetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkbNodeClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbStringPredicateClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbProjectDataClass_Members[] =
	{
		{ "attachmentSetups", &hkbAttachmentSetupClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "worldUpWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stringData", &hkbProjectStringDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbProjectDataClass(
		"hkbProjectData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbProjectDataClass_Members),
		HK_COUNT_OF(hkbProjectDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbProjectStringDataClass_Members[] =
	{
		{ "animationPath", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "behaviorPath", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "characterPath", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "animationFilenames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "behaviorFilenames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "characterFilenames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "eventNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL }
	};
	hkClass hkbProjectStringDataClass(
		"hkbProjectStringData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbProjectStringDataClass_Members),
		HK_COUNT_OF(hkbProjectStringDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbSequenceClass_Members[] =
	{
		{ "sequencedData", &hkbSequencedDataClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "enableEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "disableEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stringData", &hkbSequenceStringDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableIdMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "eventIdMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbSequence_DefaultStruct
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
			hkInt32 m_enableEventId;
			hkInt32 m_disableEventId;
		};
		const hkbSequence_DefaultStruct hkbSequence_Default =
		{
			{-1,HK_OFFSET_OF(hkbSequence_DefaultStruct,m_enableEventId),HK_OFFSET_OF(hkbSequence_DefaultStruct,m_disableEventId),-1,-1,-1,-1,-1},
			-1,-1
		};
	}
	hkClass hkbSequenceClass(
		"hkbSequence",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbSequenceClass_Members),
		HK_COUNT_OF(hkbSequenceClass_Members),
		&hkbSequence_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbSequenceStringDataClass_Members[] =
	{
		{ "eventNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "variableNames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL }
	};
	hkClass hkbSequenceStringDataClass(
		"hkbSequenceStringData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbSequenceStringDataClass_Members),
		HK_COUNT_OF(hkbSequenceStringDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkbSequencedDataClass(
		"hkbSequencedData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbEventSequencedData_SequencedEventClass_Members[] =
	{
		{ "event", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbEventSequencedDataSequencedEventClass(
		"hkbEventSequencedDataSequencedEvent",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbEventSequencedData_SequencedEventClass_Members),
		HK_COUNT_OF(hkbEventSequencedData_SequencedEventClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbEventSequencedDataClass_Members[] =
	{
		{ "events", &hkbEventSequencedDataSequencedEventClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "nextEvent", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbEventSequencedDataClass(
		"hkbEventSequencedData",
		&hkbSequencedDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbEventSequencedDataClass_Members),
		HK_COUNT_OF(hkbEventSequencedDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRealVariableSequencedData_SampleClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRealVariableSequencedDataSampleClass(
		"hkbRealVariableSequencedDataSample",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRealVariableSequencedData_SampleClass_Members),
		HK_COUNT_OF(hkbRealVariableSequencedData_SampleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRealVariableSequencedDataClass_Members[] =
	{
		{ "samples", &hkbRealVariableSequencedDataSampleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "nextSample", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbRealVariableSequencedDataClass(
		"hkbRealVariableSequencedData",
		&hkbSequencedDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRealVariableSequencedDataClass_Members),
		HK_COUNT_OF(hkbRealVariableSequencedDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBoolVariableSequencedData_SampleClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBoolVariableSequencedDataSampleClass(
		"hkbBoolVariableSequencedDataSample",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBoolVariableSequencedData_SampleClass_Members),
		HK_COUNT_OF(hkbBoolVariableSequencedData_SampleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBoolVariableSequencedDataClass_Members[] =
	{
		{ "samples", &hkbBoolVariableSequencedDataSampleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "nextSample", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBoolVariableSequencedDataClass(
		"hkbBoolVariableSequencedData",
		&hkbSequencedDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBoolVariableSequencedDataClass_Members),
		HK_COUNT_OF(hkbBoolVariableSequencedDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbIntVariableSequencedData_SampleClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbIntVariableSequencedDataSampleClass(
		"hkbIntVariableSequencedDataSample",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbIntVariableSequencedData_SampleClass_Members),
		HK_COUNT_OF(hkbIntVariableSequencedData_SampleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbIntVariableSequencedDataClass_Members[] =
	{
		{ "samples", &hkbIntVariableSequencedDataSampleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "variableIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "nextSample", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbIntVariableSequencedDataClass(
		"hkbIntVariableSequencedData",
		&hkbSequencedDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbIntVariableSequencedDataClass_Members),
		HK_COUNT_OF(hkbIntVariableSequencedDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkbStateMachineTransitionInfoFlagBitsEnum;
	static const hkInternalClassEnumItem hkbStateMachineStartStateModeEnumItems[] =
	{
		{0, "START_STATE_MODE_SET_ON_ACTIVATE"},
		{1, "START_STATE_MODE_SET_ONCE"},
		{2, "START_STATE_MODE_SYNC"},
		{3, "START_STATE_MODE_RANDOM"},
	};
	static const hkInternalClassEnum hkbStateMachineEnums[] = {
		{"StartStateMode", hkbStateMachineStartStateModeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbStateMachineStartStateModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbStateMachineEnums[0]);
	static hkInternalClassMember hkbStateMachine_TimeIntervalClass_Members[] =
	{
		{ "enterEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "exitEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enterTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "exitTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateMachineTimeIntervalClass(
		"hkbStateMachineTimeInterval",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_TimeIntervalClass_Members),
		HK_COUNT_OF(hkbStateMachine_TimeIntervalClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbStateMachineTransitionInfoFlagBitsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_USE_TRIGGER_INTERVAL"},
		{2/*0x2*/, "FLAG_USE_INITIATE_INTERVAL"},
		{4/*0x4*/, "FLAG_UNINTERRUPTIBLE_WHILE_PLAYING"},
		{8/*0x8*/, "FLAG_UNINTERRUPTIBLE_WHILE_DELAYED"},
		{16/*0x10*/, "FLAG_DELAY_STATE_CHANGE"},
		{32/*0x20*/, "FLAG_DISABLED"},
		{64/*0x40*/, "FLAG_DISALLOW_RETURN_TO_PREVIOUS_STATE"},
		{128/*0x80*/, "FLAG_DISALLOW_RANDOM_TRANSITION"},
		{256/*0x100*/, "FLAG_DISABLE_PREDICATE"},
		{512/*0x200*/, "FLAG_ALLOW_SELF_TRANSITION_BY_TRANSITION_FROM_ANY_STATE"},
		{1024/*0x400*/, "FLAG_IS_GLOBAL_WILDCARD"},
		{2048/*0x800*/, "FLAG_IS_LOCAL_WILDCARD"},
		{4096/*0x1000*/, "FLAG_FROM_NESTED_STATE_ID_IS_VALID"},
		{8192/*0x2000*/, "FLAG_TO_NESTED_STATE_ID_IS_VALID"},
		{16384/*0x4000*/, "FLAG_ABUT_AT_END_OF_FROM_GENERATOR"},
	};
	static const hkInternalClassEnumItem hkbStateMachineTransitionInfoInternalFlagBitsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_INTERNAL_IN_TRIGGER_INTERVAL"},
		{2/*0x2*/, "FLAG_INTERNAL_IN_INITIATE_INTERVAL"},
	};
	static const hkInternalClassEnum hkbStateMachineTransitionInfoEnums[] = {
		{"FlagBits", hkbStateMachineTransitionInfoFlagBitsEnumItems, 15, HK_NULL, 0 },
		{"InternalFlagBits", hkbStateMachineTransitionInfoInternalFlagBitsEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbStateMachineTransitionInfoFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbStateMachineTransitionInfoEnums[0]);
	extern const hkClassEnum* hkbStateMachineTransitionInfoInternalFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbStateMachineTransitionInfoEnums[1]);
	static hkInternalClassMember hkbStateMachine_TransitionInfoClass_Members[] =
	{
		{ "triggerInterval", &hkbStateMachineTimeIntervalClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initiateInterval", &hkbStateMachineTimeIntervalClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transition", &hkbTransitionEffectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "predicate", &hkbPredicateClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "eventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fromNestedStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toNestedStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "priority", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, hkbStateMachineTransitionInfoFlagBitsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "internalFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbStateMachineTransitionInfoClass(
		"hkbStateMachineTransitionInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbStateMachineTransitionInfoEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_TransitionInfoClass_Members),
		HK_COUNT_OF(hkbStateMachine_TransitionInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbStateMachine_ActiveTransitionInfoClass_Members[] =
	{
		{ "transitionInfo", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "transitionEffect", &hkbTransitionEffectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "fromStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isReturnToPreviousState", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateMachineActiveTransitionInfoClass(
		"hkbStateMachineActiveTransitionInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_ActiveTransitionInfoClass_Members),
		HK_COUNT_OF(hkbStateMachine_ActiveTransitionInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbStateMachine_ProspectiveTransitionInfoClass_Members[] =
	{
		{ "transitionInfo", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "transitionEffect", &hkbTransitionEffectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "toStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isGlobalWildcard", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateMachineProspectiveTransitionInfoClass(
		"hkbStateMachineProspectiveTransitionInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateMachine_ProspectiveTransitionInfoClass_Members),
		HK_COUNT_OF(hkbStateMachine_ProspectiveTransitionInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbStateMachine_StateInfoClass_Members[] =
	{
		{ "enterNotifyEvent", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "exitNotifyEvent", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transitions", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "stateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "inPackfile", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkbStateMachine_StateInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbStateMachineClass_Members[] =
	{
		{ "eventToSendWhenStateOrTransitionChanges", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "returnToPreviousStateEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "randomTransitionEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transitionToNextHigherStateEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transitionToNextLowerStateEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "syncVariableIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wrapAroundStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSimultaneousTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startStateMode", HK_NULL, hkbStateMachineStartStateModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "enableGlobalTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableNestedTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "states", &hkbStateMachineStateInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "globalTransitions", &hkbStateMachineTransitionInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "activeTransitions", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "delayedTransition", &hkbStateMachineProspectiveTransitionInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "stateIdToIndexMap", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "eventQueue", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "nestedStateMachineData", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeInState", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "currentStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "previousStateId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "nextStartStateIndexOverride", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "stateOrTransitionChanged", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isDelayedTransitionReturnToPreviousState", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "resetLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "allowDelayedTransitionNextUpdate", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbStateMachine_DefaultStruct
		{
			int s_defaultOffsets[30];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			hkInt32 m_transitionToNextHigherStateEventId;
			hkInt32 m_transitionToNextLowerStateEventId;
			hkInt32 m_syncVariableIndex;
			_hkBool m_wrapAroundStateId;
			hkInt8 m_maxSimultaneousTransitions;
		};
		const hkbStateMachine_DefaultStruct hkbStateMachine_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_transitionToNextHigherStateEventId),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_transitionToNextLowerStateEventId),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_syncVariableIndex),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_wrapAroundStateId),HK_OFFSET_OF(hkbStateMachine_DefaultStruct,m_maxSimultaneousTransitions),-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			-1,-1,-1,true,32
		};
	}
	hkClass hkbStateMachineClass(
		"hkbStateMachine",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbStateMachineEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbStateMachineClass_Members),
		HK_COUNT_OF(hkbStateMachineClass_Members),
		&hkbStateMachine_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbTransitionEffectSelfTransitionModeEnumItems[] =
	{
		{0, "SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC"},
		{1, "SELF_TRANSITION_MODE_CONTINUE"},
		{2, "SELF_TRANSITION_MODE_RESET"},
		{3, "SELF_TRANSITION_MODE_BLEND"},
	};
	static const hkInternalClassEnumItem hkbTransitionEffectEventModeEnumItems[] =
	{
		{0, "EVENT_MODE_DEFAULT"},
		{1, "EVENT_MODE_PROCESS_ALL"},
		{2, "EVENT_MODE_IGNORE_FROM_GENERATOR"},
	};
	static const hkInternalClassEnum hkbTransitionEffectEnums[] = {
		{"SelfTransitionMode", hkbTransitionEffectSelfTransitionModeEnumItems, 4, HK_NULL, 0 },
		{"EventMode", hkbTransitionEffectEventModeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbTransitionEffectSelfTransitionModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbTransitionEffectEnums[0]);
	extern const hkClassEnum* hkbTransitionEffectEventModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbTransitionEffectEnums[1]);
	static hkInternalClassMember hkbTransitionEffectClass_Members[] =
	{
		{ "selfTransitionMode", HK_NULL, hkbTransitionEffectSelfTransitionModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "eventMode", HK_NULL, hkbTransitionEffectEventModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkbTransitionEffectClass(
		"hkbTransitionEffect",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbTransitionEffectEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbTransitionEffectClass_Members),
		HK_COUNT_OF(hkbTransitionEffectClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbBlendingTransitionEffectFlagBitsEnumItems[] =
	{
		{0/*0x0*/, "FLAG_NONE"},
		{1/*0x1*/, "FLAG_IGNORE_FROM_WORLD_FROM_MODEL"},
		{2/*0x2*/, "FLAG_SYNC"},
	};
	static const hkInternalClassEnumItem hkbBlendingTransitionEffectEndModeEnumItems[] =
	{
		{0, "END_MODE_NONE"},
		{1, "END_MODE_TRANSITION_UNTIL_END_OF_FROM_GENERATOR"},
		{2, "END_MODE_CAP_DURATION_AT_END_OF_FROM_GENERATOR"},
	};
	static const hkInternalClassEnum hkbBlendingTransitionEffectEnums[] = {
		{"FlagBits", hkbBlendingTransitionEffectFlagBitsEnumItems, 3, HK_NULL, 0 },
		{"EndMode", hkbBlendingTransitionEffectEndModeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbBlendingTransitionEffectFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlendingTransitionEffectEnums[0]);
	extern const hkClassEnum* hkbBlendingTransitionEffectEndModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbBlendingTransitionEffectEnums[1]);
	static hkInternalClassMember hkbBlendingTransitionEffectClass_Members[] =
	{
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toGeneratorStartTimeFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endMode", HK_NULL, hkbBlendingTransitionEffectEndModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "fromGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "toGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "childFrequencies", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "timeRemaining", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "localTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "frequency", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeInTransition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isClone", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBlendingTransitionEffectClass(
		"hkbBlendingTransitionEffect",
		&hkbTransitionEffectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbBlendingTransitionEffectEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbBlendingTransitionEffectClass_Members),
		HK_COUNT_OF(hkbBlendingTransitionEffectClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbGeneratorTransitionEffectClass_Members[] =
	{
		{ "transitionGenerator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "fromGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "toGenerator", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeInTransition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "setLocalTimeOfToGeneratorToThis", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "blendInDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blendOutDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isClone", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "hasToGeneratorBegun", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbGeneratorTransitionEffectClass(
		"hkbGeneratorTransitionEffect",
		&hkbTransitionEffectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbGeneratorTransitionEffectClass_Members),
		HK_COUNT_OF(hkbGeneratorTransitionEffectClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkClassMemberTypeEnum;
	static hkInternalClassMember hkbVariableBindingSet_BindingClass_Members[] =
	{
		{ "object", &hkReferencedObjectClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "memberPath", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "memberDataPtr", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "memberType", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "variableIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bitIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbVariableBindingSetBinding_DefaultStruct
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
			hkInt8 m_bitIndex;
		};
		const hkbVariableBindingSetBinding_DefaultStruct hkbVariableBindingSetBinding_Default =
		{
			{-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbVariableBindingSetBinding_DefaultStruct,m_bitIndex)},
			-1
		};
	}
	hkClass hkbVariableBindingSetBindingClass(
		"hkbVariableBindingSetBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableBindingSet_BindingClass_Members),
		HK_COUNT_OF(hkbVariableBindingSet_BindingClass_Members),
		&hkbVariableBindingSetBinding_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbVariableBindingSetClass_Members[] =
	{
		{ "bindings", &hkbVariableBindingSetBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbVariableBindingSetClass(
		"hkbVariableBindingSet",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableBindingSetClass_Members),
		HK_COUNT_OF(hkbVariableBindingSetClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbVariableInfoVariableTypeEnumItems[] =
	{
		{-1, "VARIABLE_TYPE_INVALID"},
		{0, "VARIABLE_TYPE_BOOL"},
		{1, "VARIABLE_TYPE_INT8"},
		{2, "VARIABLE_TYPE_INT16"},
		{3, "VARIABLE_TYPE_INT32"},
		{4, "VARIABLE_TYPE_REAL"},
	};
	static const hkInternalClassEnum hkbVariableInfoEnums[] = {
		{"VariableType", hkbVariableInfoVariableTypeEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbVariableInfoVariableTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkbVariableInfoEnums[0]);
	static hkInternalClassMember hkbVariableInfoClass_Members[] =
	{
		{ "initialValue", &hkbVariableValueClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, hkbVariableInfoVariableTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkbVariableInfoClass(
		"hkbVariableInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbVariableInfoEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbVariableInfoClass_Members),
		HK_COUNT_OF(hkbVariableInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "memberIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbVariableSetTargetClass(
		"hkbVariableSetTarget",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableSet_TargetClass_Members),
		HK_COUNT_OF(hkbVariableSet_TargetClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbVariableSet_VariableClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkbVariableSetClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbVariableValueClass_Members[] =
	{
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbVariableValueClass(
		"hkbVariableValue",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbVariableValueClass_Members),
		HK_COUNT_OF(hkbVariableValueClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbDemoConfigCharacterInfoClass_Members[] =
	{
		{ "rigFilename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "skinFilenames", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_CSTRING, 0, 0, 0, HK_NULL },
		{ "behaviorFilename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "characterDataFilename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachmentsFilename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modelUpAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollBoneLayers", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkbDemoConfigCharacterInfoClass(
		"hkbDemoConfigCharacterInfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbDemoConfigCharacterInfoClass_Members),
		HK_COUNT_OF(hkbDemoConfigCharacterInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbDemoConfig_TerrainInfoClass_Members[] =
	{
		{ "filename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "layer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "systemGroup", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "createDisplayObjects", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "terrainRigidBody", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbDemoConfigTerrainInfoClass(
		"hkbDemoConfigTerrainInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbDemoConfig_TerrainInfoClass_Members),
		HK_COUNT_OF(hkbDemoConfig_TerrainInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbDemoConfig_StickVariableInfoClass_Members[] =
	{
		{ "variableName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minValue", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxValue", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbDemoConfigStickVariableInfoClass(
		"hkbDemoConfigStickVariableInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbDemoConfig_StickVariableInfoClass_Members),
		HK_COUNT_OF(hkbDemoConfig_StickVariableInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbDemoConfigClass_Members[] =
	{
		{ "characterInfo", &hkbDemoConfigCharacterInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "terrainInfo", &hkbDemoConfigTerrainInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skinAttributeIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "buttonPressToEventMap", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 16, 0, 0, HK_NULL },
		{ "buttonReleaseToEventMap", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 16, 0, 0, HK_NULL },
		{ "worldUpAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proxyHeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proxyRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proxyOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rootPath", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "projectDataFilename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useAttachments", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useProxy", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useSkyBox", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useTrackingCamera", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "accumulateMotion", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stickVariables", &hkbDemoConfigStickVariableInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "gamePadToRotateTerrainAboutItsAxisMap", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 6, 0, 0, HK_NULL },
		{ "gamePadToAddRemoveCharacterMap", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "filter", &hkpGroupFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbDemoConfigClass(
		"hkbDemoConfig",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbDemoConfigClass_Members),
		HK_COUNT_OF(hkbDemoConfigClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbCustomTestGeneratorModesEnumItems[] =
	{
		{0, "MODE_ALA"},
		{1, "MODE_DEPECHE"},
		{5, "MODE_FURIOUS"},
	};
	static const hkInternalClassEnumItem hkbCustomTestGeneratorStrangeFlagsEnumItems[] =
	{
		{1/*0x1*/, "FLAG_UNO"},
		{2/*0x2*/, "FLAG_ZWEI"},
		{4/*0x4*/, "FLAG_SHI_OR_YON"},
		{240/*0xf0*/, "FLAG_LOTS_O_BITS"},
	};
	static const hkInternalClassEnum hkbCustomTestGeneratorEnums[] = {
		{"Modes", hkbCustomTestGeneratorModesEnumItems, 3, HK_NULL, 0 },
		{"StrangeFlags", hkbCustomTestGeneratorStrangeFlagsEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbCustomTestGeneratorModesEnum = reinterpret_cast<const hkClassEnum*>(&hkbCustomTestGeneratorEnums[0]);
	extern const hkClassEnum* hkbCustomTestGeneratorStrangeFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkbCustomTestGeneratorEnums[1]);
	static hkInternalClassMember hkbCustomTestGenerator_StruckClass_Members[] =
	{
		{ "hkBool", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "string", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "int", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt8", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt16", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt32", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint8", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint16", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint32", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkReal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mode_hkInt8", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "mode_hkInt16", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "mode_hkInt32", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "mode_hkUint8", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "mode_hkUint16", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "mode_hkUint32", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "flags_hkInt8", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "flags_hkInt16", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "flags_hkInt32", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "flags_hkUint8", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "flags_hkUint16", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "flags_hkUint32", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "generator1", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "generator2", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "modifier1", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "modifier2", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCustomTestGeneratorStruckClass(
		"hkbCustomTestGeneratorStruck",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCustomTestGenerator_StruckClass_Members),
		HK_COUNT_OF(hkbCustomTestGenerator_StruckClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCustomTestGeneratorClass_Members[] =
	{
		{ "hkBool", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "string", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "int", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt8", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt16", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkInt32", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint8", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint16", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkUint32", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "hkReal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mode_hkInt8", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "mode_hkInt16", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "mode_hkInt32", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "mode_hkUint8", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "mode_hkUint16", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "mode_hkUint32", HK_NULL, hkbCustomTestGeneratorModesEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "flags_hkInt8", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "flags_hkInt16", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "flags_hkInt32", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "flags_hkUint8", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "flags_hkUint16", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "flags_hkUint32", HK_NULL, hkbCustomTestGeneratorStrangeFlagsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "myInt", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "generator1", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "generator2", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "modifier1", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "modifier2", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "array_hkBool", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL },
		{ "array_int", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "array_hkInt8", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "array_hkInt16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "array_hkInt32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "array_hkUint8", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "array_hkUint16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "array_hkUint32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "array_hkReal", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "array_hkbGenerator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "array_hkbModifier", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "Struck", &hkbCustomTestGeneratorStruckClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "array_Struck", &hkbCustomTestGeneratorStruckClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCustomTestGeneratorClass(
		"hkbCustomTestGenerator",
		&hkbReferencePoseGeneratorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbCustomTestGeneratorEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbCustomTestGeneratorClass_Members),
		HK_COUNT_OF(hkbCustomTestGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbManualSelectorGeneratorClass_Members[] =
	{
		{ "generators", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "selectedGeneratorIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentGeneratorIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbManualSelectorGeneratorClass(
		"hkbManualSelectorGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbManualSelectorGeneratorClass_Members),
		HK_COUNT_OF(hkbManualSelectorGeneratorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRadialSelectorGenerator_GeneratorInfoClass_Members[] =
	{
		{ "generator", &hkbGeneratorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "angle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radialSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRadialSelectorGeneratorGeneratorInfoClass(
		"hkbRadialSelectorGeneratorGeneratorInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRadialSelectorGenerator_GeneratorInfoClass_Members),
		HK_COUNT_OF(hkbRadialSelectorGenerator_GeneratorInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRadialSelectorGenerator_GeneratorPairClass_Members[] =
	{
		{ "generators", &hkbRadialSelectorGeneratorGeneratorInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbRadialSelectorGeneratorGeneratorPairClass(
		"hkbRadialSelectorGeneratorGeneratorPair",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRadialSelectorGenerator_GeneratorPairClass_Members),
		HK_COUNT_OF(hkbRadialSelectorGenerator_GeneratorPairClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbRadialSelectorGeneratorClass_Members[] =
	{
		{ "generatorPairs", &hkbRadialSelectorGeneratorGeneratorPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "angle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentGeneratorPairIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "currentEndpointIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "currentFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "hasSetLocalTime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRadialSelectorGenerator_DefaultStruct
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
			int m_currentGeneratorPairIndex;
			int m_currentEndpointIndex;
		};
		const hkbRadialSelectorGenerator_DefaultStruct hkbRadialSelectorGenerator_Default =
		{
			{-1,-1,-1,HK_OFFSET_OF(hkbRadialSelectorGenerator_DefaultStruct,m_currentGeneratorPairIndex),HK_OFFSET_OF(hkbRadialSelectorGenerator_DefaultStruct,m_currentEndpointIndex),-1,-1},
			-1,-1
		};
	}
	hkClass hkbRadialSelectorGeneratorClass(
		"hkbRadialSelectorGenerator",
		&hkbGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbRadialSelectorGeneratorClass_Members),
		HK_COUNT_OF(hkbRadialSelectorGeneratorClass_Members),
		&hkbRadialSelectorGenerator_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBalanceRadialSelectorGeneratorClass_Members[] =
	{
		{ "xAxisMS", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "yAxisMS", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "checkBalanceModifier", &hkbCheckBalanceModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbBalanceRadialSelectorGenerator_DefaultStruct
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
			int m_yAxisMS;
		};
		const hkbBalanceRadialSelectorGenerator_DefaultStruct hkbBalanceRadialSelectorGenerator_Default =
		{
			{-1,HK_OFFSET_OF(hkbBalanceRadialSelectorGenerator_DefaultStruct,m_yAxisMS),-1},
			1
		};
	}
	hkClass hkbBalanceRadialSelectorGeneratorClass(
		"hkbBalanceRadialSelectorGenerator",
		&hkbRadialSelectorGeneratorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBalanceRadialSelectorGeneratorClass_Members),
		HK_COUNT_OF(hkbBalanceRadialSelectorGeneratorClass_Members),
		&hkbBalanceRadialSelectorGenerator_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbAlignBoneModifierAlignModeABAMEnumItems[] =
	{
		{0, "ALIGN_MODE_CHARACTER_WORLD_FROM_MODEL"},
		{1, "ALIGN_MODE_ANIMATION_SKELETON_BONE"},
	};
	static const hkInternalClassEnumItem hkbAlignBoneModifierAlignTargetModeEnumItems[] =
	{
		{0, "ALIGN_TARGET_MODE_CHARACTER_WORLD_FROM_MODEL"},
		{1, "ALIGN_TARGET_MODE_RAGDOLL_SKELETON_BONE"},
		{2, "ALIGN_TARGET_MODE_ANIMATION_SKELETON_BONE"},
		{3, "ALIGN_TARGET_MODE_USER_SPECIFIED_FRAME_OF_REFERENCE"},
	};
	static const hkInternalClassEnum hkbAlignBoneModifierEnums[] = {
		{"AlignModeABAM", hkbAlignBoneModifierAlignModeABAMEnumItems, 2, HK_NULL, 0 },
		{"AlignTargetMode", hkbAlignBoneModifierAlignTargetModeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbAlignBoneModifierAlignModeABAMEnum = reinterpret_cast<const hkClassEnum*>(&hkbAlignBoneModifierEnums[0]);
	extern const hkClassEnum* hkbAlignBoneModifierAlignTargetModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbAlignBoneModifierEnums[1]);
	static hkInternalClassMember hkbAlignBoneModifierClass_Members[] =
	{
		{ "alignMode", HK_NULL, hkbAlignBoneModifierAlignModeABAMEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "alignTargetMode", HK_NULL, hkbAlignBoneModifierAlignTargetModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "alignSingleAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignTargetAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameOfReference", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignModeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignTargetModeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbAlignBoneModifierClass(
		"hkbAlignBoneModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbAlignBoneModifierEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbAlignBoneModifierClass_Members),
		HK_COUNT_OF(hkbAlignBoneModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBalanceControllerModifierClass_Members[] =
	{
		{ "proportionalGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "derivativeGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "integralGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "checkBalanceModifier", &hkbCheckBalanceModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "boneForces", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "timestep", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "previousErrorMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "accumulatedErrorMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBalanceControllerModifierClass(
		"hkbBalanceControllerModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBalanceControllerModifierClass_Members),
		HK_COUNT_OF(hkbBalanceControllerModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBalanceModifier_StepInfoClass_Members[] =
	{
		{ "boneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fractionOfSolution", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbBalanceModifierStepInfoClass(
		"hkbBalanceModifierStepInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBalanceModifier_StepInfoClass_Members),
		HK_COUNT_OF(hkbBalanceModifier_StepInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbBalanceModifierClass_Members[] =
	{
		{ "giveUp", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "comDistThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "passThrough", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollLeftFootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollRightFootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "balanceOnAnklesFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "upAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeInTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "comBiasX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stepInfo", &hkbBalanceModifierStepInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "timeLapsed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbBalanceModifierClass(
		"hkbBalanceModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbBalanceModifierClass_Members),
		HK_COUNT_OF(hkbBalanceModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCheckBalanceModifierClass_Members[] =
	{
		{ "ragdollLeftFootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollRightFootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "balanceOnAnklesFraction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventToSendWhenOffBalance", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offBalanceEventThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "worldUpAxisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "comBiasX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extractRagdollPose", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mass", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "comWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "desiredComWS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "offBalanceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "errorMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbCheckBalanceModifierClass(
		"hkbCheckBalanceModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCheckBalanceModifierClass_Members),
		HK_COUNT_OF(hkbCheckBalanceModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbCatchFallModifierFadeStateEnumItems[] =
	{
		{0, "FADE_IN"},
		{1, "FADE_OUT"},
	};
	static const hkInternalClassEnum hkbCatchFallModifierEnums[] = {
		{"FadeState", hkbCatchFallModifierFadeStateEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbCatchFallModifierFadeStateEnum = reinterpret_cast<const hkClassEnum*>(&hkbCatchFallModifierEnums[0]);
	static hkInternalClassMember hkbCatchFallModifierClass_Members[] =
	{
		{ "catchFallDoneEvent", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollBoneForwardLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollBoneRightLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollBoneUpLS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spreadHandsMultiplier", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radarRange", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetBlendWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handsBendLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxReachDistanceForward", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxReachDistanceBackward", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeInReachGainSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutReachGainSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeInTwistSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutTwistSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "raycastLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocityRagdollBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "orientHands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "catchFallDirectionRagdollBone", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeState", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "catchFallPosInBS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "currentReachGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentTwistGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentTwistDirection", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "catchFallPosIsValid", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "catchFallBegin", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "catchFallEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbCatchFallModifierClass(
		"hkbCatchFallModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbCatchFallModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbCatchFallModifierClass_Members),
		HK_COUNT_OF(hkbCatchFallModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbCheckRagdollSpeedModifierClass_Members[] =
	{
		{ "minSpeedThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSpeedThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventToSend", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbCheckRagdollSpeedModifierClass(
		"hkbCheckRagdollSpeedModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbCheckRagdollSpeedModifierClass_Members),
		HK_COUNT_OF(hkbCheckRagdollSpeedModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbComputeWorldFromModelModifierClass_Members[] =
	{
		{ "poseMatchingRootBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingOtherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "poseMatchingAnotherBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkbComputeWorldFromModelModifier_DefaultStruct
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
			hkInt16 m_poseMatchingRootBoneIndex;
			hkInt16 m_poseMatchingOtherBoneIndex;
			hkInt16 m_poseMatchingAnotherBoneIndex;
		};
		const hkbComputeWorldFromModelModifier_DefaultStruct hkbComputeWorldFromModelModifier_Default =
		{
			{HK_OFFSET_OF(hkbComputeWorldFromModelModifier_DefaultStruct,m_poseMatchingRootBoneIndex),HK_OFFSET_OF(hkbComputeWorldFromModelModifier_DefaultStruct,m_poseMatchingOtherBoneIndex),HK_OFFSET_OF(hkbComputeWorldFromModelModifier_DefaultStruct,m_poseMatchingAnotherBoneIndex)},
			-1,-1,-1
		};
	}
	hkClass hkbComputeWorldFromModelModifierClass(
		"hkbComputeWorldFromModelModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbComputeWorldFromModelModifierClass_Members),
		HK_COUNT_OF(hkbComputeWorldFromModelModifierClass_Members),
		&hkbComputeWorldFromModelModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbDelayedModifierClass_Members[] =
	{
		{ "delaySeconds", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isFinite", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "durationSeconds", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modifier", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "secondsElapsed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbDelayedModifierClass(
		"hkbDelayedModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbDelayedModifierClass_Members),
		HK_COUNT_OF(hkbDelayedModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbMoveCharacterModifierClass_Members[] =
	{
		{ "offsetPerSecondMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startTimeSeconds", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endTimeSeconds", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "secondsElapsed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbMoveCharacterModifierClass(
		"hkbMoveCharacterModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbMoveCharacterModifierClass_Members),
		HK_COUNT_OF(hkbMoveCharacterModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbRotateCharacterModifierRotationStateEnumItems[] =
	{
		{0, "ROTATION_STATE_STATIONARY"},
		{1, "ROTATION_STATE_CLOCKWISE"},
		{2, "ROTATION_STATE_COUNTER_CLOCKWISE"},
	};
	static const hkInternalClassEnum hkbRotateCharacterModifierEnums[] = {
		{"RotationState", hkbRotateCharacterModifierRotationStateEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbRotateCharacterModifierRotationStateEnum = reinterpret_cast<const hkClassEnum*>(&hkbRotateCharacterModifierEnums[0]);
	static hkInternalClassMember hkbRotateCharacterModifierClass_Members[] =
	{
		{ "startRotatingClockwiseEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "startRotatingCounterClockwiseEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stopRotatingEventId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radiansPerSecond", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axisOfRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationState", HK_NULL, hkbRotateCharacterModifierRotationStateEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "angle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbRotateCharacterModifier_DefaultStruct
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
			int m_startRotatingClockwiseEventId;
			int m_startRotatingCounterClockwiseEventId;
			int m_stopRotatingEventId;
			hkReal m_radiansPerSecond;
			_hkVector4 m_axisOfRotation;
		};
		const hkbRotateCharacterModifier_DefaultStruct hkbRotateCharacterModifier_Default =
		{
			{HK_OFFSET_OF(hkbRotateCharacterModifier_DefaultStruct,m_startRotatingClockwiseEventId),HK_OFFSET_OF(hkbRotateCharacterModifier_DefaultStruct,m_startRotatingCounterClockwiseEventId),HK_OFFSET_OF(hkbRotateCharacterModifier_DefaultStruct,m_stopRotatingEventId),HK_OFFSET_OF(hkbRotateCharacterModifier_DefaultStruct,m_radiansPerSecond),HK_OFFSET_OF(hkbRotateCharacterModifier_DefaultStruct,m_axisOfRotation),-1,-1},
		-1,-1,-1,1.0f,	{1,0,0}
		};
	}
	hkClass hkbRotateCharacterModifierClass(
		"hkbRotateCharacterModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbRotateCharacterModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbRotateCharacterModifierClass_Members),
		HK_COUNT_OF(hkbRotateCharacterModifierClass_Members),
		&hkbRotateCharacterModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbStateDependentModifierClass_Members[] =
	{
		{ "applyModifierDuringTransition", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stateIds", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "modifier", &hkbModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stateMachine", &hkbStateMachineClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbStateDependentModifierClass(
		"hkbStateDependentModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbStateDependentModifierClass_Members),
		HK_COUNT_OF(hkbStateDependentModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbConstrainRigidBodyModifierPivotPlacementEnumItems[] =
	{
		{0, "PIVOT_MIDWAY_BETWEEN_CENTROIDS"},
		{1, "PIVOT_AT_TARGET_CONTACT_POINT"},
		{2, "PIVOT_MIDWAY_BETWEEN_TARGET_SHAPE_CENTROID_AND_BODY_TO_CONSTRAIN_CENTROID"},
	};
	static const hkInternalClassEnum hkbConstrainRigidBodyModifierEnums[] = {
		{"PivotPlacement", hkbConstrainRigidBodyModifierPivotPlacementEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbConstrainRigidBodyModifierPivotPlacementEnum = reinterpret_cast<const hkClassEnum*>(&hkbConstrainRigidBodyModifierEnums[0]);
	static hkInternalClassMember hkbConstrainRigidBodyModifierClass_Members[] =
	{
		{ "ragdollBoneToConstrain", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "breakable", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "breakThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotPlacement", HK_NULL, hkbConstrainRigidBodyModifierPivotPlacementEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "constraintType", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constraint", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "behaviorTarget", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbConstrainRigidBodyModifierClass(
		"hkbConstrainRigidBodyModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbConstrainRigidBodyModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbConstrainRigidBodyModifierClass_Members),
		HK_COUNT_OF(hkbConstrainRigidBodyModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbControlledReachModifierClass_Members[] =
	{
		{ "target", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "fadeInStart", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeInEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutStart", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensorAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "isHandEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkbControlledReachModifierClass(
		"hkbControlledReachModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbControlledReachModifierClass_Members),
		HK_COUNT_OF(hkbControlledReachModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbFaceTargetModifierClass_Members[] =
	{
		{ "offsetAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "onlyOnce", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "behaviorTarget", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "done", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbFaceTargetModifierClass(
		"hkbFaceTargetModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbFaceTargetModifierClass_Members),
		HK_COUNT_OF(hkbFaceTargetModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbMoveBoneTowardTargetModifierTargetModeMBTTEnumItems[] =
	{
		{0, "TARGET_POSITION"},
		{1, "TARGET_COM"},
		{2, "TARGET_CONTACT_POINT"},
		{3, "TARGET_SHAPE_CENTROID"},
	};
	static const hkInternalClassEnumItem hkbMoveBoneTowardTargetModifierAlignModeBitsEnumItems[] =
	{
		{1/*0x1*/, "ALIGN_AXES"},
		{2/*0x2*/, "ALIGN_BONE_AXIS_WITH_CONTACT_NORMAL"},
		{4/*0x4*/, "ALIGN_WITH_CHARACTER_FORWARD"},
	};
	static const hkInternalClassEnum hkbMoveBoneTowardTargetModifierEnums[] = {
		{"TargetModeMBTT", hkbMoveBoneTowardTargetModifierTargetModeMBTTEnumItems, 4, HK_NULL, 0 },
		{"AlignModeBits", hkbMoveBoneTowardTargetModifierAlignModeBitsEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbMoveBoneTowardTargetModifierTargetModeMBTTEnum = reinterpret_cast<const hkClassEnum*>(&hkbMoveBoneTowardTargetModifierEnums[0]);
	extern const hkClassEnum* hkbMoveBoneTowardTargetModifierAlignModeBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkbMoveBoneTowardTargetModifierEnums[1]);
	static hkInternalClassMember hkbMoveBoneTowardTargetModifierClass_Members[] =
	{
		{ "target", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "targetPointTS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetMode", HK_NULL, hkbMoveBoneTowardTargetModifierTargetModeMBTTEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "ragdollBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "animationBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "duration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetInBoneSpace", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignMode", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignAxisBS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetAlignAxisTS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignWithCharacterForwardBS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keyframedDataContainer", &hkbKeyframeDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "eventToSendWhenTargetReached", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useVelocityPrediction", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "behaviorTarget", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "lastAnimBonePositionMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "finalAnimBonePositionMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialAnimBonePositionMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "finalAnimBoneOrientationMS", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "animationFromRagdoll", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "totalMotion", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "accumulatedMotion", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useAnimationData", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbMoveBoneTowardTargetModifierClass(
		"hkbMoveBoneTowardTargetModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbMoveBoneTowardTargetModifierEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkbMoveBoneTowardTargetModifierClass_Members),
		HK_COUNT_OF(hkbMoveBoneTowardTargetModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbReachTowardTargetModifierFadeStateEnumItems[] =
	{
		{0, "FADE_IN"},
		{1, "FADE_OUT"},
	};
	static const hkInternalClassEnum hkbReachTowardTargetModifierEnums[] = {
		{"FadeState", hkbReachTowardTargetModifierFadeStateEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbReachTowardTargetModifierFadeStateEnum = reinterpret_cast<const hkClassEnum*>(&hkbReachTowardTargetModifierEnums[0]);
	static hkInternalClassMember hkbReachTowardTargetModifierClass_Members[] =
	{
		{ "behaviorTarget", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "target", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "prevTargetInMS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "currentGain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "distanceBetweenHands", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeInGainSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutGainSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fadeOutDuration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetChangeSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "holdTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reachPastTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "giveUpIfNoTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "isHandEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "fadeState", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "haveGivenUp", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isTherePrevTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbReachTowardTargetModifier_DefaultStruct
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
			hkReal m_fadeInGainSpeed;
			hkReal m_fadeOutGainSpeed;
			hkReal m_targetChangeSpeed;
		};
		const hkbReachTowardTargetModifier_DefaultStruct hkbReachTowardTargetModifier_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkbReachTowardTargetModifier_DefaultStruct,m_fadeInGainSpeed),HK_OFFSET_OF(hkbReachTowardTargetModifier_DefaultStruct,m_fadeOutGainSpeed),-1,HK_OFFSET_OF(hkbReachTowardTargetModifier_DefaultStruct,m_targetChangeSpeed),-1,-1,-1,-1,-1,-1,-1,-1},
			1.0f,1.0f,1.0f
		};
	}
	hkClass hkbReachTowardTargetModifierClass(
		"hkbReachTowardTargetModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbReachTowardTargetModifierEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkbReachTowardTargetModifierClass_Members),
		HK_COUNT_OF(hkbReachTowardTargetModifierClass_Members),
		&hkbReachTowardTargetModifier_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbTargetClass_Members[] =
	{
		{ "target", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "contactPointTS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "contactNormalTS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "shapeCentroidTS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbTargetClass(
		"hkbTarget",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbTargetClass_Members),
		HK_COUNT_OF(hkbTargetClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkbTargetRigidBodyModifierEventModeTRBAMEnumItems[] =
	{
		{0, "EVENT_MODE_DO_NOT_SEND"},
		{1, "EVENT_MODE_SEND_ONCE"},
		{2, "EVENT_MODE_RESEND"},
	};
	static const hkInternalClassEnumItem hkbTargetRigidBodyModifierTargetModeEnumItems[] =
	{
		{0, "TARGET_MODE_CONE_AROUND_CHARACTER_FORWARD"},
		{1, "TARGET_MODE_CONE_AROUND_LOCAL_AXIS"},
		{2, "TARGET_MODE_RAYCAST_ALONG_CHARACTER_FORWARD"},
		{3, "TARGET_MODE_RAYCAST_ALONG_LOCAL_AXIS"},
		{4, "TARGET_MODE_ANY_DIRECTION"},
	};
	static const hkInternalClassEnumItem hkbTargetRigidBodyModifierComputeTargetAngleModeEnumItems[] =
	{
		{0, "COMPUTE_ANGLE_USING_TARGET_COM"},
		{1, "COMPUTE_ANGLE_USING_TARGET_CONTACT_POINT"},
	};
	static const hkInternalClassEnum hkbTargetRigidBodyModifierEnums[] = {
		{"EventModeTRBAM", hkbTargetRigidBodyModifierEventModeTRBAMEnumItems, 3, HK_NULL, 0 },
		{"TargetMode", hkbTargetRigidBodyModifierTargetModeEnumItems, 5, HK_NULL, 0 },
		{"ComputeTargetAngleMode", hkbTargetRigidBodyModifierComputeTargetAngleModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkbTargetRigidBodyModifierEventModeTRBAMEnum = reinterpret_cast<const hkClassEnum*>(&hkbTargetRigidBodyModifierEnums[0]);
	extern const hkClassEnum* hkbTargetRigidBodyModifierTargetModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbTargetRigidBodyModifierEnums[1]);
	extern const hkClassEnum* hkbTargetRigidBodyModifierComputeTargetAngleModeEnum = reinterpret_cast<const hkClassEnum*>(&hkbTargetRigidBodyModifierEnums[2]);
	static hkInternalClassMember hkbTargetRigidBodyModifierClass_Members[] =
	{
		{ "targetMode", HK_NULL, hkbTargetRigidBodyModifierTargetModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "sensingLayer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetOnlyOnce", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ignoreMySystemGroup", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxTargetDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxTargetHeightAboveSensor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetAngleMode", HK_NULL, hkbTargetRigidBodyModifierComputeTargetAngleModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "maxAngleToTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensorBoneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "senseFromRagdollBone", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensorOffsetInBoneSpace", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensorDirectionBS", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventMode", HK_NULL, hkbTargetRigidBodyModifierEventModeTRBAMEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "sensingPropertyKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sensorInWS", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventToSend", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventToSendToTarget", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useVelocityPrediction", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "behaviorTarget", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "timeSinceLastModify", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "eventHasBeenSent", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkbTargetRigidBodyModifierClass(
		"hkbTargetRigidBodyModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkbTargetRigidBodyModifierEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkbTargetRigidBodyModifierClass_Members),
		HK_COUNT_OF(hkbTargetRigidBodyModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbTimerModifierClass_Members[] =
	{
		{ "alarmTimeSeconds", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "eventToSend", &hkbEventClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "secondsElapsed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkbTimerModifierClass(
		"hkbTimerModifier",
		&hkbModifierClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbTimerModifierClass_Members),
		HK_COUNT_OF(hkbTimerModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbClimbMountingPredicateClass_Members[] =
	{
		{ "sensingForLeftHand", &hkbTargetRigidBodyModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "sensingForRightHand", &hkbTargetRigidBodyModifierClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "targetForLeftHand", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "targetForRightHand", &hkbTargetClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkbClimbMountingPredicateClass(
		"hkbClimbMountingPredicate",
		&hkbPredicateClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbClimbMountingPredicateClass_Members),
		HK_COUNT_OF(hkbClimbMountingPredicateClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkbHoldFromBlendingTransitionEffectClass_Members[] =
	{
		{ "heldFromPose", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "heldFromPoseSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "heldWorldFromModel", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "heldFromSkeleton", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "isFromGeneratorActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkbHoldFromBlendingTransitionEffect_DefaultStruct
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
			_hkBool m_isFromGeneratorActive;
		};
		const hkbHoldFromBlendingTransitionEffect_DefaultStruct hkbHoldFromBlendingTransitionEffect_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkbHoldFromBlendingTransitionEffect_DefaultStruct,m_isFromGeneratorActive)},
			true
		};
	}
	hkClass hkbHoldFromBlendingTransitionEffectClass(
		"hkbHoldFromBlendingTransitionEffect",
		&hkbBlendingTransitionEffectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkbHoldFromBlendingTransitionEffectClass_Members),
		HK_COUNT_OF(hkbHoldFromBlendingTransitionEffectClass_Members),
		&hkbHoldFromBlendingTransitionEffect_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkVariableTweakingHelper_BoolVariableInfoClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tweakOn", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVariableTweakingHelperBoolVariableInfoClass(
		"hkVariableTweakingHelperBoolVariableInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVariableTweakingHelper_BoolVariableInfoClass_Members),
		HK_COUNT_OF(hkVariableTweakingHelper_BoolVariableInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkVariableTweakingHelper_IntVariableInfoClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tweakOn", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVariableTweakingHelperIntVariableInfoClass(
		"hkVariableTweakingHelperIntVariableInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVariableTweakingHelper_IntVariableInfoClass_Members),
		HK_COUNT_OF(hkVariableTweakingHelper_IntVariableInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkVariableTweakingHelper_RealVariableInfoClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tweakOn", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVariableTweakingHelperRealVariableInfoClass(
		"hkVariableTweakingHelperRealVariableInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVariableTweakingHelper_RealVariableInfoClass_Members),
		HK_COUNT_OF(hkVariableTweakingHelper_RealVariableInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkVariableTweakingHelperClass_Members[] =
	{
		{ "boolVariableInfo", &hkVariableTweakingHelperBoolVariableInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "intVariableInfo", &hkVariableTweakingHelperIntVariableInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "realVariableInfo", &hkVariableTweakingHelperRealVariableInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "behavior", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "boolIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "intIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "realIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkVariableTweakingHelperClass(
		"hkVariableTweakingHelper",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVariableTweakingHelperClass_Members),
		HK_COUNT_OF(hkVariableTweakingHelperClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkBitFieldClass_Members[] =
	{
		{ "words", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "numBitsAndFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkBitFieldClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkMultiThreadCheckAccessTypeEnumItems[] =
	{
		{0, "HK_ACCESS_IGNORE"},
		{1, "HK_ACCESS_RO"},
		{2, "HK_ACCESS_RW"},
	};
	static const hkInternalClassEnumItem hkMultiThreadCheckReadModeEnumItems[] =
	{
		{0, "THIS_OBJECT_ONLY"},
		{1, "RECURSIVE"},
	};
	static const hkInternalClassEnum hkMultiThreadCheckEnums[] = {
		{"AccessType", hkMultiThreadCheckAccessTypeEnumItems, 3, HK_NULL, 0 },
		{"ReadMode", hkMultiThreadCheckReadModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMultiThreadCheckAccessTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadCheckEnums[0]);
	extern const hkClassEnum* hkMultiThreadCheckReadModeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadCheckEnums[1]);
	static hkInternalClassMember hkMultiThreadCheckClass_Members[] =
	{
		{ "threadId", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "markCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "markBitStack", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkMultiThreadCheckClass(
		"hkMultiThreadCheck",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMultiThreadCheckEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkMultiThreadCheckClass_Members),
		HK_COUNT_OF(hkMultiThreadCheckClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkSweptTransformClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkMonitorStreamStringMap_StringMapClass_Members[] =
	{
		{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_8, 0, HK_NULL },
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
		HK_COUNT_OF(hkMonitorStreamStringMap_StringMapClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkMonitorStreamStringMapClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkMonitorStreamFrameInfoAbsoluteTimeCounterEnumItems[] =
	{
		{0, "ABSOLUTE_TIME_TIMER_0"},
		{1, "ABSOLUTE_TIME_TIMER_1"},
		{4294967295/*0xffffffff*/, "ABSOLUTE_TIME_NOT_TIMED"},
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
		{ "absoluteTimeCounter", HK_NULL, hkMonitorStreamFrameInfoAbsoluteTimeCounterEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "timerFactor0", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timerFactor1", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "threadId", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameStreamStart", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameStreamEnd", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkMonitorStreamFrameInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkReferencedObjectClass_Members[] =
	{
		{ "memSizeAndFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "referenceCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
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
		HK_COUNT_OF(hkReferencedObjectClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkClassSignatureFlagsEnumItems[] =
	{
		{1, "SIGNATURE_LOCAL"},
	};
	static const hkInternalClassEnumItem hkClassFlagValuesEnumItems[] =
	{
		{0, "FLAGS_NONE"},
		{1, "FLAGS_NOT_SERIALIZABLE"},
	};
	static const hkInternalClassEnum hkClassEnums[] = {
		{"SignatureFlags", hkClassSignatureFlagsEnumItems, 1, HK_NULL, 0 },
		{"FlagValues", hkClassFlagValuesEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkClassSignatureFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnums[0]);
	extern const hkClassEnum* hkClassFlagValuesEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnums[1]);
	static hkInternalClassMember hkClassClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parent", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "declaredEnums", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "declaredMembers", &hkClassMemberClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "defaults", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "attributes", &hkCustomAttributesClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "flags", HK_NULL, hkClassFlagValuesEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "describedVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassClass(
		"hkClass",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkClassEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkClassClass_Members),
		HK_COUNT_OF(hkClassClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkClassEnumFlagValuesEnumItems[] =
	{
		{0, "FLAGS_NONE"},
	};
	static const hkInternalClassEnum hkClassEnumEnums[] = {
		{"FlagValues", hkClassEnumFlagValuesEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkClassEnumFlagValuesEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnumEnums[0]);
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
		HK_COUNT_OF(hkClassEnum_ItemClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkClassEnumClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "items", &hkClassEnumItemClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "attributes", &hkCustomAttributesClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, hkClassEnumFlagValuesEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassEnumClass(
		"hkClassEnum",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkClassEnumEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkClassEnumClass_Members),
		HK_COUNT_OF(hkClassEnumClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkClassMemberTypeEnum;
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
		{31, "TYPE_FLAGS"},
		{32, "TYPE_MAX"},
	};
	static const hkInternalClassEnumItem hkClassMemberFlagValuesEnumItems[] =
	{
		{0, "FLAGS_NONE"},
		{128, "ALIGN_8"},
		{256, "ALIGN_16"},
		{512, "NOT_OWNED"},
		{1024, "SERIALIZE_IGNORED"},
	};
	static const hkInternalClassEnumItem hkClassMemberDeprecatedFlagValuesEnumItems[] =
	{
		{8, "DEPRECATED_SIZE_8"},
		{8, "DEPRECATED_ENUM_8"},
		{16, "DEPRECATED_SIZE_16"},
		{16, "DEPRECATED_ENUM_16"},
		{32, "DEPRECATED_SIZE_32"},
		{32, "DEPRECATED_ENUM_32"},
	};
	static const hkInternalClassEnum hkClassMemberEnums[] = {
		{"Type", hkClassMemberTypeEnumItems, 33, HK_NULL, 0 },
		{"FlagValues", hkClassMemberFlagValuesEnumItems, 5, HK_NULL, 0 },
		{"DeprecatedFlagValues", hkClassMemberDeprecatedFlagValuesEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkClassMemberTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[0]);
	extern const hkClassEnum* hkClassMemberFlagValuesEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[1]);
	extern const hkClassEnum* hkClassMemberDeprecatedFlagValuesEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberEnums[2]);
	static hkInternalClassMember hkClassMemberClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "class", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "enum", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, hkClassMemberTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "subtype", HK_NULL, hkClassMemberTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "cArraySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flags", HK_NULL, hkClassMemberFlagValuesEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attributes", &hkCustomAttributesClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkClassMemberClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkCustomAttributes_AttributeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkCustomAttributesAttributeClass(
		"hkCustomAttributesAttribute",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCustomAttributes_AttributeClass_Members),
		HK_COUNT_OF(hkCustomAttributes_AttributeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkCustomAttributesClass_Members[] =
	{
		{ "attributes", &hkCustomAttributesAttributeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkCustomAttributesClass(
		"hkCustomAttributes",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCustomAttributesClass_Members),
		HK_COUNT_OF(hkCustomAttributesClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkAabbClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkAabbUint32Class_Members[] =
	{
		{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "expansionMin", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "expansionShift", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "expansionMax", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "sortIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAabbUint32Class(
		"hkAabbUint32",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAabbUint32Class_Members),
		HK_COUNT_OF(hkAabbUint32Class_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkSphereClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkContactPointClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkContactPointMaterialFlagEnumEnumItems[] =
	{
		{1, "CONTACT_IS_NEW_AND_POTENTIAL"},
		{2, "CONTACT_USES_SOLVER_PATH2"},
		{4, "CONTACT_BREAKOFF_OBJECT_ID"},
	};
	static const hkInternalClassEnum hkContactPointMaterialEnums[] = {
		{"FlagEnum", hkContactPointMaterialFlagEnumEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkContactPointMaterialFlagEnumEnum = reinterpret_cast<const hkClassEnum*>(&hkContactPointMaterialEnums[0]);
	static hkInternalClassMember hkContactPointMaterialClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "restitution", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxImpulse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
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
		HK_COUNT_OF(hkContactPointMaterialClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkMotionStateClass_Members[] =
	{
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sweptTransform", &hkSweptTransformClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deltaAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationClass", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkMotionStateClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedFloatClass_Members[] =
	{
		{ "floats", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkxAnimatedFloatClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedMatrixClass_Members[] =
	{
		{ "matrices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkxAnimatedMatrixClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxAnimatedQuaternionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkxAttributeHintEnum;
	static hkInternalClassMember hkxAnimatedVectorClass_Members[] =
	{
		{ "vectors", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "hint", HK_NULL, hkxAttributeHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkxAnimatedVectorClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxAttributeClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxAttributeGroupClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxAttributeHolderClass_Members[] =
	{
		{ "attributeGroups", &hkxAttributeGroupClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkxAttributeHolderClass(
		"hkxAttributeHolder",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxAttributeHolderClass_Members),
		HK_COUNT_OF(hkxAttributeHolderClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSparselyAnimatedBoolClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSparselyAnimatedEnumClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSparselyAnimatedIntClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSparselyAnimatedString_StringTypeClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSparselyAnimatedStringClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxCameraClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxEnvironment_VariableClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxEnvironmentClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxNode_AnnotationDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxNodeClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "object", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keyFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "children", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "annotations", &hkxNodeAnnotationDataClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "userProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "selected", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxNodeClass(
		"hkxNode",
		&hkxAttributeHolderClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxNodeClass_Members),
		HK_COUNT_OF(hkxNodeClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "type", HK_NULL, hkxLightLightTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
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
		HK_COUNT_OF(hkxLightClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxMaterial_TextureStageClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		&hkxAttributeHolderClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkxMaterialEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkxMaterialClass_Members),
		HK_COUNT_OF(hkxMaterialClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "type", HK_NULL, hkxMaterialEffectEffectTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
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
		HK_COUNT_OF(hkxMaterialEffectClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxTextureFileClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxTextureInplaceClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		{ "indexType", HK_NULL, hkxIndexBufferIndexTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
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
		HK_COUNT_OF(hkxIndexBufferClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxMesh_UserChannelInfoClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "className", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxMeshUserChannelInfoClass(
		"hkxMeshUserChannelInfo",
		&hkxAttributeHolderClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxMesh_UserChannelInfoClass_Members),
		HK_COUNT_OF(hkxMesh_UserChannelInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxMeshClass_Members[] =
	{
		{ "sections", &hkxMeshSectionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "userChannelInfos", &hkxMeshUserChannelInfoClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkxMeshClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxMeshSectionClass_Members[] =
	{
		{ "vertexBuffer", &hkxVertexBufferClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "indexBuffers", &hkxIndexBufferClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "material", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "userChannels", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VARIANT, 0, 0, 0, HK_NULL }
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
		HK_COUNT_OF(hkxMeshSectionClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexBufferClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexFormatClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxEdgeSelectionChannelClass_Members[] =
	{
		{ "selectedEdges", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkxEdgeSelectionChannelClass(
		"hkxEdgeSelectionChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxEdgeSelectionChannelClass_Members),
		HK_COUNT_OF(hkxEdgeSelectionChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxTriangleSelectionChannelClass_Members[] =
	{
		{ "selectedTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkxTriangleSelectionChannelClass(
		"hkxTriangleSelectionChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxTriangleSelectionChannelClass_Members),
		HK_COUNT_OF(hkxTriangleSelectionChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxVertexFloatDataChannelClass_Members[] =
	{
		{ "perVertexFloats", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexFloatDataChannelClass(
		"hkxVertexFloatDataChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexFloatDataChannelClass_Members),
		HK_COUNT_OF(hkxVertexFloatDataChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxVertexIntDataChannelClass_Members[] =
	{
		{ "perVertexInts", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexIntDataChannelClass(
		"hkxVertexIntDataChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexIntDataChannelClass_Members),
		HK_COUNT_OF(hkxVertexIntDataChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxVertexSelectionChannelClass_Members[] =
	{
		{ "selectedVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexSelectionChannelClass(
		"hkxVertexSelectionChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexSelectionChannelClass_Members),
		HK_COUNT_OF(hkxVertexSelectionChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxVertexVectorDataChannelClass_Members[] =
	{
		{ "perVertexVectors", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkxVertexVectorDataChannelClass(
		"hkxVertexVectorDataChannel",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxVertexVectorDataChannelClass_Members),
		HK_COUNT_OF(hkxVertexVectorDataChannelClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexP4N4C1T2Class_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexP4N4T4B4C1T2Class_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexP4N4T4B4W4I4C1Q2Class_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexP4N4T4B4W4I4Q4Class_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxVertexP4N4W4I4C1Q2Class_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxSceneClass_Members[] =
	{
		{ "modeller", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "asset", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sceneLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rootNode", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "selectionSets", &hkxNodeSelectionSetClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
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
			int s_defaultOffsets[13];
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
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkxScene_DefaultStruct,m_appliedTransform)},
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
		HK_COUNT_OF(hkxSceneClass_Members),
		&hkxScene_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkxNodeSelectionSetClass_Members[] =
	{
		{ "selectedNodes", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkxNodeSelectionSetClass(
		"hkxNodeSelectionSet",
		&hkxAttributeHolderClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkxNodeSelectionSetClass_Members),
		HK_COUNT_OF(hkxNodeSelectionSetClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkxSkinBindingClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkPackfileHeaderClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkPackfileSectionHeaderClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkRootLevelContainer_NamedVariantClass_Members),
		HK_NULL,
		HK_NULL,
		0
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
		HK_COUNT_OF(hkRootLevelContainerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpCdBodyClass_Members[] =
	{
		{ "shape", &hkpShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "shapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motion", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "parent", &hkpCdBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCdBodyClass(
		"hkpCdBody",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpCdBodyClass_Members),
		HK_COUNT_OF(hkpCdBodyClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpCollidableForceCollideOntoPpuReasonsEnumItems[] =
	{
		{1, "FORCE_PPU_USER_REQUEST"},
		{2, "FORCE_PPU_SHAPE_REQUEST"},
		{4, "FORCE_PPU_MODIFIER_REQUEST"},
	};
	static const hkInternalClassEnum hkpCollidableEnums[] = {
		{"ForceCollideOntoPpuReasons", hkpCollidableForceCollideOntoPpuReasonsEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpCollidableForceCollideOntoPpuReasonsEnum = reinterpret_cast<const hkClassEnum*>(&hkpCollidableEnums[0]);
	static hkInternalClassMember hkpCollidable_BoundingVolumeDataClass_Members[] =
	{
		{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "expansionMin", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "expansionShift", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "expansionMax", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "padding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numChildShapeAabbs", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childShapeAabbs", &hkAabbUint32Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCollidableBoundingVolumeDataClass(
		"hkpCollidableBoundingVolumeData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpCollidable_BoundingVolumeDataClass_Members),
		HK_COUNT_OF(hkpCollidable_BoundingVolumeDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpCollidableClass_Members[] =
	{
		{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "forceCollideOntoPpu", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapeSizeOnSpu", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhaseHandle", &hkpTypedBroadPhaseHandleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boundingVolumeData", &hkpCollidableBoundingVolumeDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "allowedPenetrationDepth", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCollidableClass(
		"hkpCollidable",
		&hkpCdBodyClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpCollidableEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpCollidableClass_Members),
		HK_COUNT_OF(hkpCollidableClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTypedBroadPhaseHandleClass_Members[] =
	{
		{ "type", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "objectQualityType", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTypedBroadPhaseHandleClass(
		"hkpTypedBroadPhaseHandle",
		&hkpBroadPhaseHandleClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTypedBroadPhaseHandleClass_Members),
		HK_COUNT_OF(hkpTypedBroadPhaseHandleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpCollidableCollidableFilterClass(
		"hkpCollidableCollidableFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpCollisionFilterhkpFilterTypeEnumItems[] =
	{
		{0, "HK_FILTER_UNKNOWN"},
		{1, "HK_FILTER_NULL"},
		{2, "HK_FILTER_GROUP"},
		{3, "HK_FILTER_LIST"},
		{4, "HK_FILTER_CUSTOM"},
		{5, "HK_FILTER_PAIR"},
		{6, "HK_FILTER_CONSTRAINT"},
	};
	static const hkInternalClassEnum hkpCollisionFilterEnums[] = {
		{"hkpFilterType", hkpCollisionFilterhkpFilterTypeEnumItems, 7, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpCollisionFilterhkpFilterTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpCollisionFilterEnums[0]);
	static hkInternalClassMember hkpCollisionFilterClass_Members[] =
	{
		{ "type", HK_NULL, hkpCollisionFilterhkpFilterTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL }
	};
	hkClass hkpCollisionFilterClass(
		"hkpCollisionFilter",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		4,
		reinterpret_cast<const hkClassEnum*>(hkpCollisionFilterEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpCollisionFilterClass_Members),
		HK_COUNT_OF(hkpCollisionFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConvexListFilterConvexListCollisionTypeEnumItems[] =
	{
		{0, "TREAT_CONVEX_LIST_AS_NORMAL"},
		{1, "TREAT_CONVEX_LIST_AS_LIST"},
		{2, "TREAT_CONVEX_LIST_AS_CONVEX"},
	};
	static const hkInternalClassEnum hkpConvexListFilterEnums[] = {
		{"ConvexListCollisionType", hkpConvexListFilterConvexListCollisionTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConvexListFilterConvexListCollisionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConvexListFilterEnums[0]);
	hkClass hkpConvexListFilterClass(
		"hkpConvexListFilter",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConvexListFilterEnums),
		1,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpRayCollidableFilterClass(
		"hkpRayCollidableFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpShapeCollectionFilterClass(
		"hkpShapeCollectionFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpDefaultConvexListFilterClass(
		"hkpDefaultConvexListFilter",
		&hkpConvexListFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpGroupFilterClass_Members[] =
	{
		{ "nextFreeSystemGroup", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionLookupTable", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 32, 0, 0, HK_NULL },
		{ "pad256", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL }
	};
	hkClass hkpGroupFilterClass(
		"hkpGroupFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpGroupFilterClass_Members),
		HK_COUNT_OF(hkpGroupFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpCollisionFilterListClass_Members[] =
	{
		{ "collisionFilters", &hkpCollisionFilterClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCollisionFilterListClass(
		"hkpCollisionFilterList",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpCollisionFilterListClass_Members),
		HK_COUNT_OF(hkpCollisionFilterListClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpNullCollisionFilterClass(
		"hkpNullCollisionFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpShapeTypeEnum;
	static hkInternalClassMember hkpShapeClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "type", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpShapeClass(
		"hkpShape",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpShapeClass_Members),
		HK_COUNT_OF(hkpShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpShapeContainerClass(
		"hkpShapeContainer",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSingleShapeContainerClass_Members[] =
	{
		{ "childShape", &hkpShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSingleShapeContainerClass(
		"hkpSingleShapeContainer",
		&hkpShapeContainerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSingleShapeContainerClass_Members),
		HK_COUNT_OF(hkpSingleShapeContainerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpShapeCollectionClass_Members[] =
	{
		{ "disableWelding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpShapeCollectionClass(
		"hkpShapeCollection",
		&hkpShapeClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpShapeCollectionClass_Members),
		HK_COUNT_OF(hkpShapeCollectionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexPieceMeshShapeClass_Members[] =
	{
		{ "convexPieceStream", &hkpConvexPieceStreamDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "displayMesh", &hkpShapeCollectionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexPieceMeshShapeClass(
		"hkpConvexPieceMeshShape",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexPieceMeshShapeClass_Members),
		HK_COUNT_OF(hkpConvexPieceMeshShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;
	static const hkInternalClassEnumItem hkpExtendedMeshShapeIndexStridingTypeEnumItems[] =
	{
		{0, "INDICES_INVALID"},
		{1, "INDICES_INT16"},
		{2, "INDICES_INT32"},
		{3, "INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkpExtendedMeshShapeMaterialIndexStridingTypeEnumItems[] =
	{
		{0, "MATERIAL_INDICES_INVALID"},
		{1, "MATERIAL_INDICES_INT8"},
		{2, "MATERIAL_INDICES_INT16"},
		{3, "MATERIAL_INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkpExtendedMeshShapeSubpartTypeEnumItems[] =
	{
		{0, "SUBPART_TRIANGLES"},
		{1, "SUBPART_SHAPE"},
	};
	static const hkInternalClassEnum hkpExtendedMeshShapeEnums[] = {
		{"IndexStridingType", hkpExtendedMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"MaterialIndexStridingType", hkpExtendedMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"SubpartType", hkpExtendedMeshShapeSubpartTypeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpExtendedMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[0]);
	extern const hkClassEnum* hkpExtendedMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[1]);
	extern const hkClassEnum* hkpExtendedMeshShapeSubpartTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[2]);
	static hkInternalClassMember hkpExtendedMeshShape_SubpartClass_Members[] =
	{
		{ "type", HK_NULL, hkpExtendedMeshShapeSubpartTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "materialIndexStridingType", HK_NULL, hkpExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpExtendedMeshShapeSubpartClass(
		"hkpExtendedMeshShapeSubpart",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_SubpartClass_Members),
		HK_COUNT_OF(hkpExtendedMeshShape_SubpartClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpExtendedMeshShape_TrianglesSubpartClass_Members[] =
	{
		{ "numTriangleShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "stridingType", HK_NULL, hkpExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "flipAlternateTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triangleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct
		{
			int s_defaultOffsets[10];
			typedef hkInt8 _hkBool;
			typedef hkReal _hkVector4[4];
			typedef hkReal _hkQuaternion[4];
			typedef hkReal _hkMatrix3[12];
			typedef hkReal _hkRotation[12];
			typedef hkReal _hkQsTransform[12];
			typedef hkReal _hkMatrix4[16];
			typedef hkReal _hkTransform[16];
			int m_triangleOffset;
		};
		const hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct hkpExtendedMeshShapeTrianglesSubpart_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct,m_triangleOffset)},
			-1
		};
	}
	hkClass hkpExtendedMeshShapeTrianglesSubpartClass(
		"hkpExtendedMeshShapeTrianglesSubpart",
		&hkpExtendedMeshShapeSubpartClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_TrianglesSubpartClass_Members),
		HK_COUNT_OF(hkpExtendedMeshShape_TrianglesSubpartClass_Members),
		&hkpExtendedMeshShapeTrianglesSubpart_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpExtendedMeshShape_ShapesSubpartClass_Members[] =
	{
		{ "childShapes", &hkpConvexShapeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "offsetSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 8, 0, 0, HK_NULL }
	};
	hkClass hkpExtendedMeshShapeShapesSubpartClass(
		"hkpExtendedMeshShapeShapesSubpart",
		&hkpExtendedMeshShapeSubpartClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_ShapesSubpartClass_Members),
		HK_COUNT_OF(hkpExtendedMeshShape_ShapesSubpartClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpExtendedMeshShapeClass_Members[] =
	{
		{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "trianglesSubparts", &hkpExtendedMeshShapeTrianglesSubpartClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "shapesSubparts", &hkpExtendedMeshShapeShapesSubpartClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "embeddedTrianglesSubpart", &hkpExtendedMeshShapeTrianglesSubpartClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triangleRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad16", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkpExtendedMeshShape_DefaultStruct
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
			hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
		};
		const hkpExtendedMeshShape_DefaultStruct hkpExtendedMeshShape_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpExtendedMeshShape_DefaultStruct,m_weldingType),-1,-1,-1},
			6
		};
	}
	hkClass hkpExtendedMeshShapeClass(
		"hkpExtendedMeshShape",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpExtendedMeshShapeEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShapeClass_Members),
		HK_COUNT_OF(hkpExtendedMeshShapeClass_Members),
		&hkpExtendedMeshShape_Default,
		HK_NULL,
		0
		);
	hkClass hkpFastMeshShapeClass(
		"hkpFastMeshShape",
		&hkpMeshShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpListShape_ChildInfoClass_Members[] =
	{
		{ "shape", &hkpShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "numChildShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpListShapeChildInfoClass(
		"hkpListShapeChildInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpListShape_ChildInfoClass_Members),
		HK_COUNT_OF(hkpListShape_ChildInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpListShapeClass_Members[] =
	{
		{ "childInfo", &hkpListShapeChildInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enabledChildren", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 8, 0, 0, HK_NULL }
	};
	hkClass hkpListShapeClass(
		"hkpListShape",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpListShapeClass_Members),
		HK_COUNT_OF(hkpListShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMeshMaterialClass_Members[] =
	{
		{ "filterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMeshMaterialClass(
		"hkpMeshMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMeshMaterialClass_Members),
		HK_COUNT_OF(hkpMeshMaterialClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;
	static const hkInternalClassEnumItem hkpMeshShapeIndexStridingTypeEnumItems[] =
	{
		{0, "INDICES_INVALID"},
		{1, "INDICES_INT16"},
		{2, "INDICES_INT32"},
		{3, "INDICES_MAX_ID"},
	};
	static const hkInternalClassEnumItem hkpMeshShapeMaterialIndexStridingTypeEnumItems[] =
	{
		{0, "MATERIAL_INDICES_INVALID"},
		{1, "MATERIAL_INDICES_INT8"},
		{2, "MATERIAL_INDICES_INT16"},
		{3, "MATERIAL_INDICES_MAX_ID"},
	};
	static const hkInternalClassEnum hkpMeshShapeEnums[] = {
		{"IndexStridingType", hkpMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
		{"MaterialIndexStridingType", hkpMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMeshShapeEnums[0]);
	extern const hkClassEnum* hkpMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMeshShapeEnums[1]);
	static hkInternalClassMember hkpMeshShape_SubpartClass_Members[] =
	{
		{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "stridingType", HK_NULL, hkpMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "materialIndexStridingType", HK_NULL, hkpMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "flipAlternateTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triangleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpMeshShapeSubpart_DefaultStruct
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
			int m_triangleOffset;
		};
		const hkpMeshShapeSubpart_DefaultStruct hkpMeshShapeSubpart_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpMeshShapeSubpart_DefaultStruct,m_triangleOffset)},
			-1
		};
	}
	hkClass hkpMeshShapeSubpartClass(
		"hkpMeshShapeSubpart",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMeshShape_SubpartClass_Members),
		HK_COUNT_OF(hkpMeshShape_SubpartClass_Members),
		&hkpMeshShapeSubpart_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMeshShapeClass_Members[] =
	{
		{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "subparts", &hkpMeshShapeSubpartClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpMeshShape_DefaultStruct
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
			hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
		};
		const hkpMeshShape_DefaultStruct hkpMeshShape_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpMeshShape_DefaultStruct,m_weldingType),-1,-1},
			6
		};
	}
	hkClass hkpMeshShapeClass(
		"hkpMeshShape",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpMeshShapeEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkpMeshShapeClass_Members),
		HK_COUNT_OF(hkpMeshShapeClass_Members),
		&hkpMeshShape_Default,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;
	static hkInternalClassMember hkpSimpleMeshShape_TriangleClass_Members[] =
	{
		{ "a", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "b", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "c", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSimpleMeshShapeTriangleClass(
		"hkpSimpleMeshShapeTriangle",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleMeshShape_TriangleClass_Members),
		HK_COUNT_OF(hkpSimpleMeshShape_TriangleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSimpleMeshShapeClass_Members[] =
	{
		{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "triangles", &hkpSimpleMeshShapeTriangleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpSimpleMeshShape_DefaultStruct
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
			hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
		};
		const hkpSimpleMeshShape_DefaultStruct hkpSimpleMeshShape_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpSimpleMeshShape_DefaultStruct,m_weldingType)},
			6
		};
	}
	hkClass hkpSimpleMeshShapeClass(
		"hkpSimpleMeshShape",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleMeshShapeClass_Members),
		HK_COUNT_OF(hkpSimpleMeshShapeClass_Members),
		&hkpSimpleMeshShape_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members[] =
	{
		{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageExtendedMeshShapeMeshSubpartStorageClass(
		"hkpStorageExtendedMeshShapeMeshSubpartStorage",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members),
		HK_COUNT_OF(hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members[] =
	{
		{ "shapes", &hkpConvexShapeClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageExtendedMeshShapeShapeSubpartStorageClass(
		"hkpStorageExtendedMeshShapeShapeSubpartStorage",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members),
		HK_COUNT_OF(hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageExtendedMeshShapeClass_Members[] =
	{
		{ "meshstorage", &hkpStorageExtendedMeshShapeMeshSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "shapestorage", &hkpStorageExtendedMeshShapeShapeSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageExtendedMeshShapeClass(
		"hkpStorageExtendedMeshShape",
		&hkpExtendedMeshShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShapeClass_Members),
		HK_COUNT_OF(hkpStorageExtendedMeshShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageMeshShape_SubpartStorageClass_Members[] =
	{
		{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageMeshShapeSubpartStorageClass(
		"hkpStorageMeshShapeSubpartStorage",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageMeshShape_SubpartStorageClass_Members),
		HK_COUNT_OF(hkpStorageMeshShape_SubpartStorageClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageMeshShapeClass_Members[] =
	{
		{ "storage", &hkpStorageMeshShapeSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageMeshShapeClass(
		"hkpStorageMeshShape",
		&hkpMeshShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageMeshShapeClass_Members),
		HK_COUNT_OF(hkpStorageMeshShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpBvTreeShapeClass(
		"hkpBvTreeShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkMoppBvTreeShapeBaseClass_Members[] =
	{
		{ "code", &hkpMoppCodeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "moppData", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "moppDataSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "codeInfoCopy", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkMoppBvTreeShapeBaseClass(
		"hkMoppBvTreeShapeBase",
		&hkpBvTreeShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMoppBvTreeShapeBaseClass_Members),
		HK_COUNT_OF(hkMoppBvTreeShapeBaseClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMoppBvTreeShapeClass_Members[] =
	{
		{ "child", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpMoppBvTreeShapeClass(
		"hkpMoppBvTreeShape",
		&hkMoppBvTreeShapeBaseClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMoppBvTreeShapeClass_Members),
		HK_COUNT_OF(hkpMoppBvTreeShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;
	static hkInternalClassMember hkpMoppEmbeddedShapeClass_Members[] =
	{
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triangleExtrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reindexedTerminals", &hkpMoppCodeReindexedTerminalClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpMoppEmbeddedShape_DefaultStruct
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
			hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
		};
		const hkpMoppEmbeddedShape_DefaultStruct hkpMoppEmbeddedShape_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpMoppEmbeddedShape_DefaultStruct,m_weldingType),-1,-1,-1,-1},
			6
		};
	}
	hkClass hkpMoppEmbeddedShapeClass(
		"hkpMoppEmbeddedShape",
		&hkMoppBvTreeShapeBaseClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMoppEmbeddedShapeClass_Members),
		HK_COUNT_OF(hkpMoppEmbeddedShapeClass_Members),
		&hkpMoppEmbeddedShape_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRemoveTerminalsMoppModifierClass_Members[] =
	{
		{ "removeInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "tempShapesToRemove", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpRemoveTerminalsMoppModifierClass(
		"hkpRemoveTerminalsMoppModifier",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRemoveTerminalsMoppModifierClass_Members),
		HK_COUNT_OF(hkpRemoveTerminalsMoppModifierClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConvexShapeWeldResultEnumItems[] =
	{
		{0, "WELD_RESULT_REJECT_CONTACT_POINT"},
		{1, "WELD_RESULT_ACCEPT_CONTACT_POINT_MODIFIED"},
		{2, "WELD_RESULT_ACCEPT_CONTACT_POINT_UNMODIFIED"},
	};
	static const hkInternalClassEnum hkpConvexShapeEnums[] = {
		{"WeldResult", hkpConvexShapeWeldResultEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConvexShapeWeldResultEnum = reinterpret_cast<const hkClassEnum*>(&hkpConvexShapeEnums[0]);
	static hkInternalClassMember hkpConvexShapeClass_Members[] =
	{
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexShapeClass(
		"hkpConvexShape",
		&hkpSphereRepShapeClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConvexShapeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpConvexShapeClass_Members),
		HK_COUNT_OF(hkpConvexShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBoxShapeClass_Members[] =
	{
		{ "halfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBoxShapeClass(
		"hkpBoxShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBoxShapeClass_Members),
		HK_COUNT_OF(hkpBoxShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpCapsuleShapeRayHitTypeEnumItems[] =
	{
		{0, "HIT_CAP0"},
		{1, "HIT_CAP1"},
		{2, "HIT_BODY"},
	};
	static const hkInternalClassEnum hkpCapsuleShapeEnums[] = {
		{"RayHitType", hkpCapsuleShapeRayHitTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpCapsuleShapeRayHitTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpCapsuleShapeEnums[0]);
	static hkInternalClassMember hkpCapsuleShapeClass_Members[] =
	{
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCapsuleShapeClass(
		"hkpCapsuleShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpCapsuleShapeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpCapsuleShapeClass_Members),
		HK_COUNT_OF(hkpCapsuleShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexTransformShapeClass_Members[] =
	{
		{ "childShape", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childShapeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexTransformShapeClass(
		"hkpConvexTransformShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexTransformShapeClass_Members),
		HK_COUNT_OF(hkpConvexTransformShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexTranslateShapeClass_Members[] =
	{
		{ "childShape", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childShapeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "translation", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexTranslateShapeClass(
		"hkpConvexTranslateShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexTranslateShapeClass_Members),
		HK_COUNT_OF(hkpConvexTranslateShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexVerticesShape_FourVectorsClass_Members[] =
	{
		{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexVerticesShapeFourVectorsClass(
		"hkpConvexVerticesShapeFourVectors",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexVerticesShape_FourVectorsClass_Members),
		HK_COUNT_OF(hkpConvexVerticesShape_FourVectorsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexVerticesShapeClass_Members[] =
	{
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotatedVertices", &hkpConvexVerticesShapeFourVectorsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeEquations", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexVerticesShapeClass(
		"hkpConvexVerticesShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexVerticesShapeClass_Members),
		HK_COUNT_OF(hkpConvexVerticesShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpCylinderShapeVertexIdEncodingEnumItems[] =
	{
		{7, "VERTEX_ID_ENCODING_IS_BASE_A_SHIFT"},
		{6, "VERTEX_ID_ENCODING_SIN_SIGN_SHIFT"},
		{5, "VERTEX_ID_ENCODING_COS_SIGN_SHIFT"},
		{4, "VERTEX_ID_ENCODING_IS_SIN_LESSER_SHIFT"},
		{15/*0x0f*/, "VERTEX_ID_ENCODING_VALUE_MASK"},
	};
	static const hkInternalClassEnum hkpCylinderShapeEnums[] = {
		{"VertexIdEncoding", hkpCylinderShapeVertexIdEncodingEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpCylinderShapeVertexIdEncodingEnum = reinterpret_cast<const hkClassEnum*>(&hkpCylinderShapeEnums[0]);
	static hkInternalClassMember hkpCylinderShapeClass_Members[] =
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
		struct hkpCylinderShape_DefaultStruct
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
		const hkpCylinderShape_DefaultStruct hkpCylinderShape_Default =
		{
			{-1,HK_OFFSET_OF(hkpCylinderShape_DefaultStruct,m_cylBaseRadiusFactorForHeightFieldCollisions),-1,-1,-1,-1},
			0.8f
		};
	}
	hkClass hkpCylinderShapeClass(
		"hkpCylinderShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpCylinderShapeEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpCylinderShapeClass_Members),
		HK_COUNT_OF(hkpCylinderShapeClass_Members),
		&hkpCylinderShape_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPackedConvexVerticesShape_FourVectorsClass_Members[] =
	{
		{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL }
	};
	hkClass hkpPackedConvexVerticesShapeFourVectorsClass(
		"hkpPackedConvexVerticesShapeFourVectors",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShape_FourVectorsClass_Members),
		HK_COUNT_OF(hkpPackedConvexVerticesShape_FourVectorsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPackedConvexVerticesShape_Vector4IntWClass_Members[] =
	{
		{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "w", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPackedConvexVerticesShapeVector4IntWClass(
		"hkpPackedConvexVerticesShapeVector4IntW",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShape_Vector4IntWClass_Members),
		HK_COUNT_OF(hkpPackedConvexVerticesShape_Vector4IntWClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPackedConvexVerticesShapeClass_Members[] =
	{
		{ "planeEquations", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "aabbMin", &hkpPackedConvexVerticesShapeVector4IntWClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertices", &hkpPackedConvexVerticesShapeFourVectorsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 16, 0, 0, HK_NULL }
	};
	hkClass hkpPackedConvexVerticesShapeClass(
		"hkpPackedConvexVerticesShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShapeClass_Members),
		HK_COUNT_OF(hkpPackedConvexVerticesShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSphereShapeClass_Members[] =
	{
		{ "pad16", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpSphereShapeClass(
		"hkpSphereShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSphereShapeClass_Members),
		HK_COUNT_OF(hkpSphereShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;
	static hkInternalClassMember hkpTriangleShapeClass_Members[] =
	{
		{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "isExtruded", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexC", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpTriangleShape_DefaultStruct
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
			hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
		};
		const hkpTriangleShape_DefaultStruct hkpTriangleShape_Default =
		{
			{-1,HK_OFFSET_OF(hkpTriangleShape_DefaultStruct,m_weldingType),-1,-1,-1,-1,-1},
			6
		};
	}
	hkClass hkpTriangleShapeClass(
		"hkpTriangleShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTriangleShapeClass_Members),
		HK_COUNT_OF(hkpTriangleShapeClass_Members),
		&hkpTriangleShape_Default,
		HK_NULL,
		0
		);
	hkClass hkpHeightFieldShapeClass(
		"hkpHeightFieldShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpSphereRepShapeClass(
		"hkpSphereRepShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPlaneShapeClass_Members[] =
	{
		{ "plane", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPlaneShapeClass(
		"hkpPlaneShape",
		&hkpHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPlaneShapeClass_Members),
		HK_COUNT_OF(hkpPlaneShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSampledHeightFieldShapeClass_Members[] =
	{
		{ "xRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "zRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "heightCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useProjectionBasedHeight", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "intToFloatScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntOffsetFloorCorrected", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSampledHeightFieldShapeClass(
		"hkpSampledHeightFieldShape",
		&hkpHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSampledHeightFieldShapeClass_Members),
		HK_COUNT_OF(hkpSampledHeightFieldShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStorageSampledHeightFieldShapeClass_Members[] =
	{
		{ "storage", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "triangleFlip", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStorageSampledHeightFieldShapeClass(
		"hkpStorageSampledHeightFieldShape",
		&hkpSampledHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStorageSampledHeightFieldShapeClass_Members),
		HK_COUNT_OF(hkpStorageSampledHeightFieldShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTriSampledHeightFieldBvTreeShapeClass_Members[] =
	{
		{ "child", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wantAabbRejectionTest", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTriSampledHeightFieldBvTreeShapeClass(
		"hkpTriSampledHeightFieldBvTreeShape",
		&hkpBvTreeShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTriSampledHeightFieldBvTreeShapeClass_Members),
		HK_COUNT_OF(hkpTriSampledHeightFieldBvTreeShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTriSampledHeightFieldCollectionClass_Members[] =
	{
		{ "heightfield", &hkpSampledHeightFieldShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTriSampledHeightFieldCollectionClass(
		"hkpTriSampledHeightFieldCollection",
		&hkpShapeCollectionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTriSampledHeightFieldCollectionClass_Members),
		HK_COUNT_OF(hkpTriSampledHeightFieldCollectionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBvShapeClass_Members[] =
	{
		{ "boundingVolumeShape", &hkpShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "childShape", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBvShapeClass(
		"hkpBvShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBvShapeClass_Members),
		HK_COUNT_OF(hkpBvShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexListShapeClass_Members[] =
	{
		{ "minDistanceToUseConvexHullForGetClosestPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useCachedAabb", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childShapes", &hkpConvexShapeClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexListShapeClass(
		"hkpConvexListShape",
		&hkpConvexShapeClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexListShapeClass_Members),
		HK_COUNT_OF(hkpConvexListShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMultiRayShape_RayClass_Members[] =
	{
		{ "start", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "end", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMultiRayShapeRayClass(
		"hkpMultiRayShapeRay",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMultiRayShape_RayClass_Members),
		HK_COUNT_OF(hkpMultiRayShape_RayClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMultiRayShapeClass_Members[] =
	{
		{ "rays", &hkpMultiRayShapeRayClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rayPenetrationDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMultiRayShapeClass(
		"hkpMultiRayShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMultiRayShapeClass_Members),
		HK_COUNT_OF(hkpMultiRayShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMultiSphereShapeClass_Members[] =
	{
		{ "numSpheres", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spheres", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 8, 0, 0, HK_NULL }
	};
	hkClass hkpMultiSphereShapeClass(
		"hkpMultiSphereShape",
		&hkpSphereRepShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMultiSphereShapeClass_Members),
		HK_COUNT_OF(hkpMultiSphereShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpPhantomCallbackShapeClass(
		"hkpPhantomCallbackShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTransformShapeClass_Members[] =
	{
		{ "childShape", &hkpSingleShapeContainerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTransformShapeClass(
		"hkpTransformShape",
		&hkpShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTransformShapeClass_Members),
		HK_COUNT_OF(hkpTransformShapeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpRayShapeCollectionFilterClass(
		"hkpRayShapeCollectionFilter",
		HK_NULL,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpShapeRayCastInputClass_Members[] =
	{
		{ "from", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "to", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "filterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rayShapeCollectionFilter", &hkpRayShapeCollectionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpShapeRayCastInputClass(
		"hkpShapeRayCastInput",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpShapeRayCastInputClass_Members),
		HK_COUNT_OF(hkpShapeRayCastInputClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpWeldingUtilityWeldingTypeEnumItems[] =
	{
		{0, "WELDING_TYPE_ANTICLOCKWISE"},
		{4, "WELDING_TYPE_CLOCKWISE"},
		{5, "WELDING_TYPE_TWO_SIDED"},
		{6, "WELDING_TYPE_NONE"},
	};
	static const hkInternalClassEnumItem hkpWeldingUtilitySectorTypeEnumItems[] =
	{
		{1, "ACCEPT_0"},
		{0, "SNAP_0"},
		{2, "REJECT"},
		{4, "SNAP_1"},
		{3, "ACCEPT_1"},
	};
	static const hkInternalClassEnumItem hkpWeldingUtilityNumAnglesEnumItems[] =
	{
		{31, "NUM_ANGLES"},
	};
	static const hkInternalClassEnum hkpWeldingUtilityEnums[] = {
		{"WeldingType", hkpWeldingUtilityWeldingTypeEnumItems, 4, HK_NULL, 0 },
		{"SectorType", hkpWeldingUtilitySectorTypeEnumItems, 5, HK_NULL, 0 },
		{"NumAngles", hkpWeldingUtilityNumAnglesEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[0]);
	extern const hkClassEnum* hkpWeldingUtilitySectorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[1]);
	extern const hkClassEnum* hkpWeldingUtilityNumAnglesEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[2]);
	hkClass hkpWeldingUtilityClass(
		"hkpWeldingUtility",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpWeldingUtilityEnums),
		3,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConstraintAtomAtomTypeEnumItems[] =
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
	static const hkInternalClassEnumItem hkpConstraintAtomCallbackRequestEnumItems[] =
	{
		{0, "CALLBACK_REQUEST_NONE"},
		{1, "CALLBACK_REQUEST_NEW_CONTACT_POINT"},
		{2, "CALLBACK_REQUEST_SETUP_PPU_ONLY"},
		{4, "CALLBACK_REQUEST_SETUP_CALLBACK"},
	};
	static const hkInternalClassEnum hkpConstraintAtomEnums[] = {
		{"AtomType", hkpConstraintAtomAtomTypeEnumItems, 28, HK_NULL, 0 },
		{"CallbackRequest", hkpConstraintAtomCallbackRequestEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConstraintAtomAtomTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintAtomEnums[0]);
	extern const hkClassEnum* hkpConstraintAtomCallbackRequestEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintAtomEnums[1]);
	static hkInternalClassMember hkpConstraintAtomClass_Members[] =
	{
		{ "type", HK_NULL, hkpConstraintAtomAtomTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstraintAtomClass(
		"hkpConstraintAtom",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConstraintAtomEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkpConstraintAtomClass_Members),
		HK_COUNT_OF(hkpConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBridgeConstraintAtomClass_Members[] =
	{
		{ "buildJacobianFunc", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "constraintData", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBridgeConstraintAtomClass(
		"hkpBridgeConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBridgeConstraintAtomClass_Members),
		HK_COUNT_OF(hkpBridgeConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBridgeAtomsClass_Members[] =
	{
		{ "bridgeAtom", &hkpBridgeConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBridgeAtomsClass(
		"hkpBridgeAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBridgeAtomsClass_Members),
		HK_COUNT_OF(hkpBridgeAtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSimpleContactConstraintAtomClass_Members[] =
	{
		{ "sizeOfAllAtoms", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numReservedContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numUserDatasForBodyA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numUserDatasForBodyB", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxNumContactPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "info", &hkpSimpleContactConstraintDataInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpSimpleContactConstraintAtomClass(
		"hkpSimpleContactConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleContactConstraintAtomClass_Members),
		HK_COUNT_OF(hkpSimpleContactConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpBallSocketConstraintAtomClass(
		"hkpBallSocketConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStiffSpringConstraintAtomClass_Members[] =
	{
		{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStiffSpringConstraintAtomClass(
		"hkpStiffSpringConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintAtomClass_Members),
		HK_COUNT_OF(hkpStiffSpringConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSetLocalTransformsConstraintAtomClass_Members[] =
	{
		{ "transformA", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "transformB", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSetLocalTransformsConstraintAtomClass(
		"hkpSetLocalTransformsConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSetLocalTransformsConstraintAtomClass_Members),
		HK_COUNT_OF(hkpSetLocalTransformsConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSetLocalTranslationsConstraintAtomClass_Members[] =
	{
		{ "translationA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "translationB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSetLocalTranslationsConstraintAtomClass(
		"hkpSetLocalTranslationsConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSetLocalTranslationsConstraintAtomClass_Members),
		HK_COUNT_OF(hkpSetLocalTranslationsConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSetLocalRotationsConstraintAtomClass_Members[] =
	{
		{ "rotationA", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "rotationB", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSetLocalRotationsConstraintAtomClass(
		"hkpSetLocalRotationsConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSetLocalRotationsConstraintAtomClass_Members),
		HK_COUNT_OF(hkpSetLocalRotationsConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpOverwritePivotConstraintAtomClass_Members[] =
	{
		{ "copyToPivotBFromPivotA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpOverwritePivotConstraintAtomClass(
		"hkpOverwritePivotConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpOverwritePivotConstraintAtomClass_Members),
		HK_COUNT_OF(hkpOverwritePivotConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinConstraintAtomClass(
		"hkpLinConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinConstraintAtomClass_Members),
		HK_COUNT_OF(hkpLinConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinSoftConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinSoftConstraintAtomClass(
		"hkpLinSoftConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinSoftConstraintAtomClass_Members),
		HK_COUNT_OF(hkpLinSoftConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinLimitConstraintAtomClass_Members[] =
	{
		{ "axisIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinLimitConstraintAtomClass(
		"hkpLinLimitConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinLimitConstraintAtomClass_Members),
		HK_COUNT_OF(hkpLinLimitConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkp2dAngConstraintAtomClass_Members[] =
	{
		{ "freeRotationAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkp2dAngConstraintAtomClass(
		"hkp2dAngConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkp2dAngConstraintAtomClass_Members),
		HK_COUNT_OF(hkp2dAngConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAngConstraintAtomClass_Members[] =
	{
		{ "firstConstrainedAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numConstrainedAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpAngConstraintAtomClass(
		"hkpAngConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAngConstraintAtomClass_Members),
		HK_COUNT_OF(hkpAngConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAngLimitConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "limitAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpAngLimitConstraintAtom_DefaultStruct
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
		const hkpAngLimitConstraintAtom_DefaultStruct hkpAngLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpAngLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1.0
		};
	}
	hkClass hkpAngLimitConstraintAtomClass(
		"hkpAngLimitConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAngLimitConstraintAtomClass_Members),
		HK_COUNT_OF(hkpAngLimitConstraintAtomClass_Members),
		&hkpAngLimitConstraintAtom_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTwistLimitConstraintAtomClass_Members[] =
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
		struct hkpTwistLimitConstraintAtom_DefaultStruct
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
		const hkpTwistLimitConstraintAtom_DefaultStruct hkpTwistLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpTwistLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1.0
		};
	}
	hkClass hkpTwistLimitConstraintAtomClass(
		"hkpTwistLimitConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTwistLimitConstraintAtomClass_Members),
		HK_COUNT_OF(hkpTwistLimitConstraintAtomClass_Members),
		&hkpTwistLimitConstraintAtom_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConeLimitConstraintAtomMeasurementModeEnumItems[] =
	{
		{0, "ZERO_WHEN_VECTORS_ALIGNED"},
		{1, "ZERO_WHEN_VECTORS_PERPENDICULAR"},
	};
	static const hkInternalClassEnum hkpConeLimitConstraintAtomEnums[] = {
		{"MeasurementMode", hkpConeLimitConstraintAtomMeasurementModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConeLimitConstraintAtomMeasurementModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConeLimitConstraintAtomEnums[0]);
	static hkInternalClassMember hkpConeLimitConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistAxisInA", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angleMeasurementMode", HK_NULL, hkpConeLimitConstraintAtomMeasurementModeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "memOffsetToAngleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularLimitsTauFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpConeLimitConstraintAtom_DefaultStruct
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
			hkUint8 m_memOffsetToAngleOffset;
			hkReal m_angularLimitsTauFactor;
		};
		const hkpConeLimitConstraintAtom_DefaultStruct hkpConeLimitConstraintAtom_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpConeLimitConstraintAtom_DefaultStruct,m_memOffsetToAngleOffset),-1,-1,HK_OFFSET_OF(hkpConeLimitConstraintAtom_DefaultStruct,m_angularLimitsTauFactor)},
			1,1.0
		};
	}
	hkClass hkpConeLimitConstraintAtomClass(
		"hkpConeLimitConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConeLimitConstraintAtomEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpConeLimitConstraintAtomClass_Members),
		HK_COUNT_OF(hkpConeLimitConstraintAtomClass_Members),
		&hkpConeLimitConstraintAtom_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAngFrictionConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "firstFrictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numFrictionAxes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpAngFrictionConstraintAtomClass(
		"hkpAngFrictionConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAngFrictionConstraintAtomClass_Members),
		HK_COUNT_OF(hkpAngFrictionConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAngMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetAngleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "correspondingAngLimitSolverResultOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpAngMotorConstraintAtomClass(
		"hkpAngMotorConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAngMotorConstraintAtomClass_Members),
		HK_COUNT_OF(hkpAngMotorConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRagdollMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetAnglesOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetFrameAinB", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, 0, HK_NULL }
	};
	hkClass hkpRagdollMotorConstraintAtomClass(
		"hkpRagdollMotorConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRagdollMotorConstraintAtomClass_Members),
		HK_COUNT_OF(hkpRagdollMotorConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinFrictionConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frictionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinFrictionConstraintAtomClass(
		"hkpLinFrictionConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinFrictionConstraintAtomClass_Members),
		HK_COUNT_OF(hkpLinFrictionConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinMotorConstraintAtomClass_Members[] =
	{
		{ "isEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motorAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initializedOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousTargetPositionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinMotorConstraintAtomClass(
		"hkpLinMotorConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinMotorConstraintAtomClass_Members),
		HK_COUNT_OF(hkpLinMotorConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPulleyConstraintAtomClass_Members[] =
	{
		{ "fixedPivotAinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fixedPivotBinWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ropeLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "leverageOnBodyB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPulleyConstraintAtomClass(
		"hkpPulleyConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintAtomClass_Members),
		HK_COUNT_OF(hkpPulleyConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpModifierConstraintAtomClass_Members[] =
	{
		{ "modifierAtomSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "childSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "child", &hkpConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkpModifierConstraintAtomClass(
		"hkpModifierConstraintAtom",
		&hkpConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpModifierConstraintAtomClass_Members),
		HK_COUNT_OF(hkpModifierConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSoftContactModifierConstraintAtomClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAcceleration", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSoftContactModifierConstraintAtomClass(
		"hkpSoftContactModifierConstraintAtom",
		&hkpModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSoftContactModifierConstraintAtomClass_Members),
		HK_COUNT_OF(hkpSoftContactModifierConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMassChangerModifierConstraintAtomClass_Members[] =
	{
		{ "factorA", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "factorB", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad16", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 2, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpMassChangerModifierConstraintAtomClass(
		"hkpMassChangerModifierConstraintAtom",
		&hkpModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMassChangerModifierConstraintAtomClass_Members),
		HK_COUNT_OF(hkpMassChangerModifierConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpViscousSurfaceModifierConstraintAtomClass(
		"hkpViscousSurfaceModifierConstraintAtom",
		&hkpModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMovingSurfaceModifierConstraintAtomClass_Members[] =
	{
		{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMovingSurfaceModifierConstraintAtomClass(
		"hkpMovingSurfaceModifierConstraintAtom",
		&hkpModifierConstraintAtomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMovingSurfaceModifierConstraintAtomClass_Members),
		HK_COUNT_OF(hkpMovingSurfaceModifierConstraintAtomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSimpleContactConstraintDataInfoClass_Members[] =
	{
		{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "index", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 7, 0, 0, HK_NULL }
	};
	hkClass hkpSimpleContactConstraintDataInfoClass(
		"hkpSimpleContactConstraintDataInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleContactConstraintDataInfoClass_Members),
		HK_COUNT_OF(hkpSimpleContactConstraintDataInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpActionClass_Members[] =
	{
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "island", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpActionClass(
		"hkpAction",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpActionClass_Members),
		HK_COUNT_OF(hkpActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpArrayActionClass_Members[] =
	{
		{ "entities", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpArrayActionClass(
		"hkpArrayAction",
		&hkpActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpArrayActionClass_Members),
		HK_COUNT_OF(hkpArrayActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBinaryActionClass_Members[] =
	{
		{ "entityA", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "entityB", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBinaryActionClass(
		"hkpBinaryAction",
		&hkpActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBinaryActionClass_Members),
		HK_COUNT_OF(hkpBinaryActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpUnaryActionClass_Members[] =
	{
		{ "entity", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpUnaryActionClass(
		"hkpUnaryAction",
		&hkpActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpUnaryActionClass_Members),
		HK_COUNT_OF(hkpUnaryActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpMaterialResponseTypeEnumItems[] =
	{
		{0, "RESPONSE_INVALID"},
		{1, "RESPONSE_SIMPLE_CONTACT"},
		{2, "RESPONSE_REPORTING"},
		{3, "RESPONSE_NONE"},
		{4, "RESPONSE_MAX_ID"},
	};
	static const hkInternalClassEnum hkpMaterialEnums[] = {
		{"ResponseType", hkpMaterialResponseTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpMaterialResponseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMaterialEnums[0]);
	static hkInternalClassMember hkpMaterialClass_Members[] =
	{
		{ "responseType", HK_NULL, hkpMaterialResponseTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "friction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "restitution", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMaterialClass(
		"hkpMaterial",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpMaterialEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpMaterialClass_Members),
		HK_COUNT_OF(hkpMaterialClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPropertyValueClass_Members[] =
	{
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPropertyValueClass(
		"hkpPropertyValue",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPropertyValueClass_Members),
		HK_COUNT_OF(hkpPropertyValueClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPropertyClass_Members[] =
	{
		{ "key", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alignmentPadding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "value", &hkpPropertyValueClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPropertyClass(
		"hkpProperty",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPropertyClass_Members),
		HK_COUNT_OF(hkpPropertyClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConstraintDataConstraintTypeEnumItems[] =
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
		{16, "CONSTRAINT_TYPE_ROTATIONAL"},
		{18, "CONSTRAINT_TYPE_HINGE_LIMITS"},
		{19, "CONSTRAINT_TYPE_RAGDOLL_LIMITS"},
		{100, "BEGIN_CONSTRAINT_CHAIN_TYPES"},
		{100, "CONSTRAINT_TYPE_STIFF_SPRING_CHAIN"},
		{101, "CONSTRAINT_TYPE_BALL_SOCKET_CHAIN"},
		{102, "CONSTRAINT_TYPE_POWERED_CHAIN"},
	};
	static const hkInternalClassEnum hkpConstraintDataEnums[] = {
		{"ConstraintType", hkpConstraintDataConstraintTypeEnumItems, 21, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConstraintDataConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintDataEnums[0]);
	static hkInternalClassMember hkpConstraintDataClass_Members[] =
	{
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstraintDataClass(
		"hkpConstraintData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpConstraintDataClass_Members),
		HK_COUNT_OF(hkpConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	extern const hkClassEnum* hkpConstraintInstanceConstraintPriorityEnum;
	static const hkInternalClassEnumItem hkpConstraintInstanceConstraintPriorityEnumItems[] =
	{
		{0, "PRIORITY_INVALID"},
		{1, "PRIORITY_PSI"},
		{2, "PRIORITY_TOI"},
		{3, "PRIORITY_TOI_HIGHER"},
		{4, "PRIORITY_TOI_FORCED"},
	};
	static const hkInternalClassEnumItem hkpConstraintInstanceInstanceTypeEnumItems[] =
	{
		{0, "TYPE_NORMAL"},
		{1, "TYPE_CHAIN"},
	};
	static const hkInternalClassEnumItem hkpConstraintInstanceAddReferencesEnumItems[] =
	{
		{0, "DO_NOT_ADD_REFERENCES"},
		{1, "DO_ADD_REFERENCES"},
	};
	static const hkInternalClassEnumItem hkpConstraintInstanceCloningModeEnumItems[] =
	{
		{0, "CLONE_INSTANCES_ONLY"},
		{1, "CLONE_DATAS_WITH_MOTORS"},
	};
	static const hkInternalClassEnum hkpConstraintInstanceEnums[] = {
		{"ConstraintPriority", hkpConstraintInstanceConstraintPriorityEnumItems, 5, HK_NULL, 0 },
		{"InstanceType", hkpConstraintInstanceInstanceTypeEnumItems, 2, HK_NULL, 0 },
		{"AddReferences", hkpConstraintInstanceAddReferencesEnumItems, 2, HK_NULL, 0 },
		{"CloningMode", hkpConstraintInstanceCloningModeEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConstraintInstanceConstraintPriorityEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[0]);
	extern const hkClassEnum* hkpConstraintInstanceInstanceTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[1]);
	extern const hkClassEnum* hkpConstraintInstanceAddReferencesEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[2]);
	extern const hkClassEnum* hkpConstraintInstanceCloningModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[3]);
	static hkInternalClassMember hkpConstraintInstanceClass_Members[] =
	{
		{ "owner", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "data", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "constraintModifiers", &hkpModifierConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "entities", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, 0, HK_NULL },
		{ "priority", HK_NULL, hkpConstraintInstanceConstraintPriorityEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "wantRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "internal", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpConstraintInstanceClass(
		"hkpConstraintInstance",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConstraintInstanceEnums),
		4,
		reinterpret_cast<const hkClassMember*>(hkpConstraintInstanceClass_Members),
		HK_COUNT_OF(hkpConstraintInstanceClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBallAndSocketConstraintData_AtomsClass_Members[] =
	{
		{ "pivots", &hkpSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkpBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBallAndSocketConstraintDataAtomsClass(
		"hkpBallAndSocketConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBallAndSocketConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpBallAndSocketConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBallAndSocketConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpBallAndSocketConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpBallAndSocketConstraintDataClass(
		"hkpBallAndSocketConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBallAndSocketConstraintDataClass_Members),
		HK_COUNT_OF(hkpBallAndSocketConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpHingeConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
	};
	static const hkInternalClassEnum hkpHingeConstraintDataAtomsEnums[] = {
		{"Axis", hkpHingeConstraintDataAtomsAxisEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpHingeConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpHingeConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkpHingeConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkpBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpHingeConstraintDataAtomsClass(
		"hkpHingeConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpHingeConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpHingeConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpHingeConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpHingeConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpHingeConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpHingeConstraintDataClass(
		"hkpHingeConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpHingeConstraintDataClass_Members),
		HK_COUNT_OF(hkpHingeConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpLimitedHingeConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
		{1, "AXIS_PERP_TO_AXLE_1"},
		{2, "AXIS_PERP_TO_AXLE_2"},
	};
	static const hkInternalClassEnum hkpLimitedHingeConstraintDataAtomsEnums[] = {
		{"Axis", hkpLimitedHingeConstraintDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpLimitedHingeConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpLimitedHingeConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkpLimitedHingeConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angMotor", &hkpAngMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angFriction", &hkpAngFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angLimit", &hkpAngLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkpBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLimitedHingeConstraintDataAtomsClass(
		"hkpLimitedHingeConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpLimitedHingeConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpLimitedHingeConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpLimitedHingeConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLimitedHingeConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpLimitedHingeConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpLimitedHingeConstraintDataClass(
		"hkpLimitedHingeConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLimitedHingeConstraintDataClass_Members),
		HK_COUNT_OF(hkpLimitedHingeConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinearParametricCurveClass_Members[] =
	{
		{ "smoothingFactor", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "closedLoop", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dirNotParallelToTangentAlongWholePath", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "points", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "distance", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLinearParametricCurveClass(
		"hkpLinearParametricCurve",
		&hkpParametricCurveClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinearParametricCurveClass_Members),
		HK_COUNT_OF(hkpLinearParametricCurveClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpParametricCurveClass(
		"hkpParametricCurve",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpPointToPathConstraintDataOrientationConstraintTypeEnumItems[] =
	{
		{0, "CONSTRAIN_ORIENTATION_INVALID"},
		{1, "CONSTRAIN_ORIENTATION_NONE"},
		{2, "CONSTRAIN_ORIENTATION_ALLOW_SPIN"},
		{3, "CONSTRAIN_ORIENTATION_TO_PATH"},
		{4, "CONSTRAIN_ORIENTATION_MAX_ID"},
	};
	static const hkInternalClassEnum hkpPointToPathConstraintDataEnums[] = {
		{"OrientationConstraintType", hkpPointToPathConstraintDataOrientationConstraintTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpPointToPathConstraintDataOrientationConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpPointToPathConstraintDataEnums[0]);
	static hkInternalClassMember hkpPointToPathConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "path", &hkpParametricCurveClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularConstrainedDOF", HK_NULL, hkpPointToPathConstraintDataOrientationConstraintTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "transform_OS_KS", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkpPointToPathConstraintDataClass(
		"hkpPointToPathConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpPointToPathConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpPointToPathConstraintDataClass_Members),
		HK_COUNT_OF(hkpPointToPathConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPointToPlaneConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPointToPlaneConstraintDataAtomsClass(
		"hkpPointToPlaneConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPointToPlaneConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpPointToPlaneConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPointToPlaneConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpPointToPlaneConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpPointToPlaneConstraintDataClass(
		"hkpPointToPlaneConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPointToPlaneConstraintDataClass_Members),
		HK_COUNT_OF(hkpPointToPlaneConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpPrismaticConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_SHAFT"},
		{1, "AXIS_PERP_TO_SHAFT"},
	};
	static const hkInternalClassEnum hkpPrismaticConstraintDataAtomsEnums[] = {
		{"Axis", hkpPrismaticConstraintDataAtomsAxisEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpPrismaticConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpPrismaticConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkpPrismaticConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkpLinMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "friction", &hkpLinFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ang", &hkpAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin1", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linLimit", &hkpLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPrismaticConstraintDataAtomsClass(
		"hkpPrismaticConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpPrismaticConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpPrismaticConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpPrismaticConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPrismaticConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpPrismaticConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpPrismaticConstraintDataClass(
		"hkpPrismaticConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPrismaticConstraintDataClass_Members),
		HK_COUNT_OF(hkpPrismaticConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpRagdollConstraintDataMotorIndexEnumItems[] =
	{
		{0, "MOTOR_TWIST"},
		{1, "MOTOR_PLANE"},
		{2, "MOTOR_CONE"},
	};
	static const hkInternalClassEnum hkpRagdollConstraintDataEnums[] = {
		{"MotorIndex", hkpRagdollConstraintDataMotorIndexEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpRagdollConstraintDataMotorIndexEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollConstraintDataEnums[0]);
	static const hkInternalClassEnumItem hkpRagdollConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_TWIST"},
		{1, "AXIS_PLANES"},
		{2, "AXIS_CROSS_PRODUCT"},
	};
	static const hkInternalClassEnum hkpRagdollConstraintDataAtomsEnums[] = {
		{"Axis", hkpRagdollConstraintDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpRagdollConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkpRagdollConstraintData_AtomsClass_Members[] =
	{
		{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ragdollMotors", &hkpRagdollMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angFriction", &hkpAngFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistLimit", &hkpTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "coneLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planesLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ballSocket", &hkpBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpRagdollConstraintDataAtomsClass(
		"hkpRagdollConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpRagdollConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpRagdollConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpRagdollConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRagdollConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpRagdollConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpRagdollConstraintDataClass(
		"hkpRagdollConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpRagdollConstraintDataEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpRagdollConstraintDataClass_Members),
		HK_COUNT_OF(hkpRagdollConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStiffSpringConstraintData_AtomsClass_Members[] =
	{
		{ "pivots", &hkpSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spring", &hkpStiffSpringConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStiffSpringConstraintDataAtomsClass(
		"hkpStiffSpringConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpStiffSpringConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStiffSpringConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpStiffSpringConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpStiffSpringConstraintDataClass(
		"hkpStiffSpringConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintDataClass_Members),
		HK_COUNT_OF(hkpStiffSpringConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpWheelConstraintDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_SUSPENSION"},
		{1, "AXIS_PERP_SUSPENSION"},
		{0, "AXIS_AXLE"},
		{1, "AXIS_STEERING"},
	};
	static const hkInternalClassEnum hkpWheelConstraintDataAtomsEnums[] = {
		{"Axis", hkpWheelConstraintDataAtomsAxisEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpWheelConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpWheelConstraintDataAtomsEnums[0]);
	static hkInternalClassMember hkpWheelConstraintData_AtomsClass_Members[] =
	{
		{ "suspensionBase", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0Limit", &hkpLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin0Soft", &hkpLinSoftConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin1", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lin2", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "steeringBase", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpWheelConstraintDataAtomsClass(
		"hkpWheelConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpWheelConstraintDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpWheelConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpWheelConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpWheelConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpWheelConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL },
		{ "initialAxleInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialSteeringAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpWheelConstraintDataClass(
		"hkpWheelConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpWheelConstraintDataClass_Members),
		HK_COUNT_OF(hkpWheelConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRotationalConstraintData_AtomsClass_Members[] =
	{
		{ "rotations", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ang", &hkpAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpRotationalConstraintDataAtomsClass(
		"hkpRotationalConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRotationalConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpRotationalConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRotationalConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpRotationalConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpRotationalConstraintDataClass(
		"hkpRotationalConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRotationalConstraintDataClass_Members),
		HK_COUNT_OF(hkpRotationalConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBreakableConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constraintData", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "childRuntimeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "childNumSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverResultLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "removeWhenBroken", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "revertBackVelocityOnBreak", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "listener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpBreakableConstraintDataClass(
		"hkpBreakableConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBreakableConstraintDataClass_Members),
		HK_COUNT_OF(hkpBreakableConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpConstraintChainDataClass(
		"hkpConstraintChainData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConstraintChainInstanceClass_Members[] =
	{
		{ "chainedEntities", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "action", &hkpConstraintChainInstanceActionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstraintChainInstanceClass(
		"hkpConstraintChainInstance",
		&hkpConstraintInstanceClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConstraintChainInstanceClass_Members),
		HK_COUNT_OF(hkpConstraintChainInstanceClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConstraintChainInstanceActionClass_Members[] =
	{
		{ "constraintInstance", &hkpConstraintChainInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstraintChainInstanceActionClass(
		"hkpConstraintChainInstanceAction",
		&hkpActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConstraintChainInstanceActionClass_Members),
		HK_COUNT_OF(hkpConstraintChainInstanceActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBallSocketChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBallSocketChainDataConstraintInfoClass(
		"hkpBallSocketChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBallSocketChainData_ConstraintInfoClass_Members),
		HK_COUNT_OF(hkpBallSocketChainData_ConstraintInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBallSocketChainDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkpBallSocketChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxErrorDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpBallSocketChainDataClass(
		"hkpBallSocketChainData",
		&hkpConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBallSocketChainDataClass_Members),
		HK_COUNT_OF(hkpBallSocketChainDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpHingeLimitsDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_AXLE"},
		{1, "AXIS_PERP_TO_AXLE_1"},
		{2, "AXIS_PERP_TO_AXLE_2"},
	};
	static const hkInternalClassEnum hkpHingeLimitsDataAtomsEnums[] = {
		{"Axis", hkpHingeLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpHingeLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpHingeLimitsDataAtomsEnums[0]);
	static hkInternalClassMember hkpHingeLimitsData_AtomsClass_Members[] =
	{
		{ "rotations", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angLimit", &hkpAngLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpHingeLimitsDataAtomsClass(
		"hkpHingeLimitsDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpHingeLimitsDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpHingeLimitsData_AtomsClass_Members),
		HK_COUNT_OF(hkpHingeLimitsData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpHingeLimitsDataClass_Members[] =
	{
		{ "atoms", &hkpHingeLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpHingeLimitsDataClass(
		"hkpHingeLimitsData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpHingeLimitsDataClass_Members),
		HK_COUNT_OF(hkpHingeLimitsDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPoweredChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "aTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bTc", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 3, 0, 0, HK_NULL },
		{ "switchBodies", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPoweredChainDataConstraintInfoClass(
		"hkpPoweredChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPoweredChainData_ConstraintInfoClass_Members),
		HK_COUNT_OF(hkpPoweredChainData_ConstraintInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPoweredChainDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkpPoweredChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		struct hkpPoweredChainData_DefaultStruct
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
		const hkpPoweredChainData_DefaultStruct hkpPoweredChainData_Default =
		{
			{-1,-1,-1,-1,HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmLinAdd),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmLinMul),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmAngAdd),HK_OFFSET_OF(hkpPoweredChainData_DefaultStruct,m_cfmAngMul),-1},
			0.1f*1.19209290e-07f,1.0f,0.1f*1.19209290e-07F,1.0f
		};
	}
	hkClass hkpPoweredChainDataClass(
		"hkpPoweredChainData",
		&hkpConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPoweredChainDataClass_Members),
		HK_COUNT_OF(hkpPoweredChainDataClass_Members),
		&hkpPoweredChainData_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpRagdollLimitsDataAtomsAxisEnumItems[] =
	{
		{0, "AXIS_TWIST"},
		{1, "AXIS_PLANES"},
		{2, "AXIS_CROSS_PRODUCT"},
	};
	static const hkInternalClassEnum hkpRagdollLimitsDataAtomsEnums[] = {
		{"Axis", hkpRagdollLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpRagdollLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollLimitsDataAtomsEnums[0]);
	static hkInternalClassMember hkpRagdollLimitsData_AtomsClass_Members[] =
	{
		{ "rotations", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistLimit", &hkpTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "coneLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planesLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpRagdollLimitsDataAtomsClass(
		"hkpRagdollLimitsDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpRagdollLimitsDataAtomsEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpRagdollLimitsData_AtomsClass_Members),
		HK_COUNT_OF(hkpRagdollLimitsData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRagdollLimitsDataClass_Members[] =
	{
		{ "atoms", &hkpRagdollLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpRagdollLimitsDataClass(
		"hkpRagdollLimitsData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRagdollLimitsDataClass_Members),
		HK_COUNT_OF(hkpRagdollLimitsDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStiffSpringChainData_ConstraintInfoClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStiffSpringChainDataConstraintInfoClass(
		"hkpStiffSpringChainDataConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStiffSpringChainData_ConstraintInfoClass_Members),
		HK_COUNT_OF(hkpStiffSpringChainData_ConstraintInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpStiffSpringChainDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "infos", &hkpStiffSpringChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpStiffSpringChainDataClass(
		"hkpStiffSpringChainData",
		&hkpConstraintChainDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpStiffSpringChainDataClass_Members),
		HK_COUNT_OF(hkpStiffSpringChainDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpGenericConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scheme", &hkpGenericConstraintDataSchemeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpGenericConstraintDataClass(
		"hkpGenericConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpGenericConstraintDataClass_Members),
		HK_COUNT_OF(hkpGenericConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpGenericConstraintDataScheme_ConstraintInfoClass_Members[] =
	{
		{ "maxSizeOfSchema", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sizeOfSchemas", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numSolverElemTemps", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpGenericConstraintDataSchemeConstraintInfoClass(
		"hkpGenericConstraintDataSchemeConstraintInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpGenericConstraintDataScheme_ConstraintInfoClass_Members),
		HK_COUNT_OF(hkpGenericConstraintDataScheme_ConstraintInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpGenericConstraintDataSchemeClass_Members[] =
	{
		{ "info", &hkpGenericConstraintDataSchemeConstraintInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL },
		{ "commands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT32, 0, 0, 0, HK_NULL },
		{ "modifiers", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "motors", &hkpConstraintMotorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpGenericConstraintDataSchemeClass(
		"hkpGenericConstraintDataScheme",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpGenericConstraintDataSchemeClass_Members),
		HK_COUNT_OF(hkpGenericConstraintDataSchemeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMalleableConstraintDataClass_Members[] =
	{
		{ "constraintData", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMalleableConstraintDataClass(
		"hkpMalleableConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMalleableConstraintDataClass_Members),
		HK_COUNT_OF(hkpMalleableConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpConstraintMotorMotorTypeEnumItems[] =
	{
		{0, "TYPE_INVALID"},
		{1, "TYPE_POSITION"},
		{2, "TYPE_VELOCITY"},
		{3, "TYPE_SPRING_DAMPER"},
		{4, "TYPE_CALLBACK"},
		{5, "TYPE_MAX"},
	};
	static const hkInternalClassEnum hkpConstraintMotorEnums[] = {
		{"MotorType", hkpConstraintMotorMotorTypeEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpConstraintMotorMotorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintMotorEnums[0]);
	static hkInternalClassMember hkpConstraintMotorClass_Members[] =
	{
		{ "type", HK_NULL, hkpConstraintMotorMotorTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstraintMotorClass(
		"hkpConstraintMotor",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpConstraintMotorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpConstraintMotorClass_Members),
		HK_COUNT_OF(hkpConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLimitedForceConstraintMotorClass_Members[] =
	{
		{ "minForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpLimitedForceConstraintMotorClass(
		"hkpLimitedForceConstraintMotor",
		&hkpConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLimitedForceConstraintMotorClass_Members),
		HK_COUNT_OF(hkpLimitedForceConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpCallbackConstraintMotorCallbackTypeEnumItems[] =
	{
		{0, "CALLBACK_MOTOR_TYPE_HAVOK_DEMO_SPRING_DAMPER"},
		{1, "CALLBACK_MOTOR_TYPE_USER_0"},
		{2, "CALLBACK_MOTOR_TYPE_USER_1"},
		{3, "CALLBACK_MOTOR_TYPE_USER_2"},
		{4, "CALLBACK_MOTOR_TYPE_USER_3"},
	};
	static const hkInternalClassEnum hkpCallbackConstraintMotorEnums[] = {
		{"CallbackType", hkpCallbackConstraintMotorCallbackTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpCallbackConstraintMotorCallbackTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpCallbackConstraintMotorEnums[0]);
	static hkInternalClassMember hkpCallbackConstraintMotorClass_Members[] =
	{
		{ "callbackFunc", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "callbackType", HK_NULL, hkpCallbackConstraintMotorCallbackTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "userData0", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData1", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData2", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpCallbackConstraintMotorClass(
		"hkpCallbackConstraintMotor",
		&hkpLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpCallbackConstraintMotorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpCallbackConstraintMotorClass_Members),
		HK_COUNT_OF(hkpCallbackConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPositionConstraintMotorClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "proportionalRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constantRecoveryVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPositionConstraintMotorClass(
		"hkpPositionConstraintMotor",
		&hkpLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPositionConstraintMotorClass_Members),
		HK_COUNT_OF(hkpPositionConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSpringDamperConstraintMotorClass_Members[] =
	{
		{ "springConstant", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSpringDamperConstraintMotorClass(
		"hkpSpringDamperConstraintMotor",
		&hkpLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSpringDamperConstraintMotorClass_Members),
		HK_COUNT_OF(hkpSpringDamperConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVelocityConstraintMotorClass_Members[] =
	{
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocityTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useVelocityTargetFromConstraintTargets", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVelocityConstraintMotorClass(
		"hkpVelocityConstraintMotor",
		&hkpLimitedForceConstraintMotorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVelocityConstraintMotorClass_Members),
		HK_COUNT_OF(hkpVelocityConstraintMotorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPulleyConstraintData_AtomsClass_Members[] =
	{
		{ "translations", &hkpSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pulley", &hkpPulleyConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPulleyConstraintDataAtomsClass(
		"hkpPulleyConstraintDataAtoms",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintData_AtomsClass_Members),
		HK_COUNT_OF(hkpPulleyConstraintData_AtomsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPulleyConstraintDataClass_Members[] =
	{
		{ "atoms", &hkpPulleyConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, 0, HK_NULL }
	};
	hkClass hkpPulleyConstraintDataClass(
		"hkpPulleyConstraintData",
		&hkpConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintDataClass_Members),
		HK_COUNT_OF(hkpPulleyConstraintDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpEntitySpuCollisionCallbackEventFilterEnumItems[] =
	{
		{0/*0x00*/, "SPU_SEND_NONE"},
		{1/*0x01*/, "SPU_SEND_CONTACT_POINT_ADDED"},
		{2/*0x02*/, "SPU_SEND_CONTACT_POINT_PROCESS"},
		{4/*0x04*/, "SPU_SEND_CONTACT_POINT_REMOVED"},
		{3/*SPU_SEND_CONTACT_POINT_ADDED|SPU_SEND_CONTACT_POINT_PROCESS*/, "SPU_SEND_CONTACT_POINT_ADDED_OR_PROCESS"},
	};
	static const hkInternalClassEnum hkpEntityEnums[] = {
		{"SpuCollisionCallbackEventFilter", hkpEntitySpuCollisionCallbackEventFilterEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpEntitySpuCollisionCallbackEventFilterEnum = reinterpret_cast<const hkClassEnum*>(&hkpEntityEnums[0]);
	static hkInternalClassMember hkpEntity_SmallArraySerializeOverrideTypeClass_Members[] =
	{
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "size", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "capacityAndFlags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpEntitySmallArraySerializeOverrideTypeClass(
		"hkpEntitySmallArraySerializeOverrideType",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpEntity_SmallArraySerializeOverrideTypeClass_Members),
		HK_COUNT_OF(hkpEntity_SmallArraySerializeOverrideTypeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpEntity_SpuCollisionCallbackClass_Members[] =
	{
		{ "util", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "capacity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "eventFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpEntitySpuCollisionCallbackClass(
		"hkpEntitySpuCollisionCallback",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpEntity_SpuCollisionCallbackClass_Members),
		HK_COUNT_OF(hkpEntity_SpuCollisionCallbackClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpEntity_ExtendedListenersClass_Members[] =
	{
		{ "activationListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "entityListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpEntityExtendedListenersClass(
		"hkpEntityExtendedListeners",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpEntity_ExtendedListenersClass_Members),
		HK_COUNT_OF(hkpEntity_ExtendedListenersClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpEntityClass_Members[] =
	{
		{ "material", &hkpMaterialClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "breakOffPartsUtil", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "solverData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "storageIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "processContactCallbackDelay", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "constraintsMaster", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "constraintsSlave", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "constraintRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "simulationIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "autoRemoveLevel", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numUserDatasInContactPointProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "uid", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spuCollisionCallback", &hkpEntitySpuCollisionCallbackClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extendedListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "motion", &hkpMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionListeners", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "actions", &hkpEntitySmallArraySerializeOverrideTypeClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	namespace
	{
		struct hkpEntity_DefaultStruct
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
			hkUint32 m_uid;
		};
		const hkpEntity_DefaultStruct hkpEntity_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpEntity_DefaultStruct,m_uid),-1,-1,-1,-1,-1},
			0xffffffff
		};
	}
	hkClass hkpEntityClass(
		"hkpEntity",
		&hkpWorldObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpEntityEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpEntityClass_Members),
		HK_COUNT_OF(hkpEntityClass_Members),
		&hkpEntity_Default,
		HK_NULL,
		0
		);
	hkClass hkpEntityDeactivatorClass(
		"hkpEntityDeactivator",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpFakeRigidBodyDeactivatorClass(
		"hkpFakeRigidBodyDeactivator",
		&hkpRigidBodyDeactivatorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpRigidBodyClass(
		"hkpRigidBody",
		&hkpEntityClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpRigidBodyDeactivatorDeactivatorTypeEnumItems[] =
	{
		{0, "DEACTIVATOR_INVALID"},
		{1, "DEACTIVATOR_NEVER"},
		{2, "DEACTIVATOR_SPATIAL"},
		{3, "DEACTIVATOR_MAX_ID"},
	};
	static const hkInternalClassEnum hkpRigidBodyDeactivatorEnums[] = {
		{"DeactivatorType", hkpRigidBodyDeactivatorDeactivatorTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpRigidBodyDeactivatorDeactivatorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpRigidBodyDeactivatorEnums[0]);
	hkClass hkpRigidBodyDeactivatorClass(
		"hkpRigidBodyDeactivator",
		&hkpEntityDeactivatorClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpRigidBodyDeactivatorEnums),
		1,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSpatialRigidBodyDeactivator_SampleClass_Members[] =
	{
		{ "refPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "refRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSpatialRigidBodyDeactivatorSampleClass(
		"hkpSpatialRigidBodyDeactivatorSample",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSpatialRigidBodyDeactivator_SampleClass_Members),
		HK_COUNT_OF(hkpSpatialRigidBodyDeactivator_SampleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSpatialRigidBodyDeactivatorClass_Members[] =
	{
		{ "highFrequencySample", &hkpSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencySample", &hkpSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "radiusSqrd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minHighFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minHighFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minLowFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minLowFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSpatialRigidBodyDeactivatorClass(
		"hkpSpatialRigidBodyDeactivator",
		&hkpRigidBodyDeactivatorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSpatialRigidBodyDeactivatorClass_Members),
		HK_COUNT_OF(hkpSpatialRigidBodyDeactivatorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpMotionMotionTypeEnumItems[] =
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
		{9, "MOTION_CHARACTER"},
		{10, "MOTION_MAX_ID"},
	};
	static const hkInternalClassEnum hkpMotionEnums[] = {
		{"MotionType", hkpMotionMotionTypeEnumItems, 11, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpMotionMotionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMotionEnums[0]);
	static hkInternalClassMember hkpMotionClass_Members[] =
	{
		{ "type", HK_NULL, hkpMotionMotionTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "deactivationIntegrateCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationNumInactiveFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "inertiaAndMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationRefPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "deactivationRefOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "savedMotion", &hkpMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "savedQualityTypeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMotionClass(
		"hkpMotion",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpMotionEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpMotionClass_Members),
		HK_COUNT_OF(hkpMotionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpBoxMotionClass(
		"hkpBoxMotion",
		&hkpMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpCharacterMotionClass(
		"hkpCharacterMotion",
		&hkpMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpFixedRigidMotionClass(
		"hkpFixedRigidMotion",
		&hkpKeyframedRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpKeyframedRigidMotionClass(
		"hkpKeyframedRigidMotion",
		&hkpMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpMaxSizeMotionClass(
		"hkpMaxSizeMotion",
		&hkpKeyframedRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpSphereMotionClass(
		"hkpSphereMotion",
		&hkpMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpStabilizedBoxMotionClass(
		"hkpStabilizedBoxMotion",
		&hkpBoxMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpStabilizedSphereMotionClass(
		"hkpStabilizedSphereMotion",
		&hkpSphereMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpThinBoxMotionClass(
		"hkpThinBoxMotion",
		&hkpBoxMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAabbPhantomClass_Members[] =
	{
		{ "aabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "overlappingCollidables", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpAabbPhantomClass(
		"hkpAabbPhantom",
		&hkpPhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAabbPhantomClass_Members),
		HK_COUNT_OF(hkpAabbPhantomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpCachingShapePhantomClass_Members[] =
	{
		{ "collisionDetails", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpCachingShapePhantomClass(
		"hkpCachingShapePhantom",
		&hkpShapePhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpCachingShapePhantomClass_Members),
		HK_COUNT_OF(hkpCachingShapePhantomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPhantomClass_Members[] =
	{
		{ "overlapListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "phantomListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpPhantomClass(
		"hkpPhantom",
		&hkpWorldObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPhantomClass_Members),
		HK_COUNT_OF(hkpPhantomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpShapePhantomClass_Members[] =
	{
		{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpShapePhantomClass(
		"hkpShapePhantom",
		&hkpPhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpShapePhantomClass_Members),
		HK_COUNT_OF(hkpShapePhantomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSimpleShapePhantom_CollisionDetailClass_Members[] =
	{
		{ "collidable", &hkpCollidableClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSimpleShapePhantomCollisionDetailClass(
		"hkpSimpleShapePhantomCollisionDetail",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleShapePhantom_CollisionDetailClass_Members),
		HK_COUNT_OF(hkpSimpleShapePhantom_CollisionDetailClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSimpleShapePhantomClass_Members[] =
	{
		{ "collisionDetails", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpSimpleShapePhantomClass(
		"hkpSimpleShapePhantom",
		&hkpShapePhantomClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSimpleShapePhantomClass_Members),
		HK_COUNT_OF(hkpSimpleShapePhantomClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPhysicsSystemClass_Members[] =
	{
		{ "rigidBodies", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "constraints", &hkpConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "actions", &hkpActionClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "phantoms", &hkpPhantomClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "active", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpPhysicsSystem_DefaultStruct
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
		const hkpPhysicsSystem_DefaultStruct hkpPhysicsSystem_Default =
		{
			{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpPhysicsSystem_DefaultStruct,m_active)},
			true
		};
	}
	hkClass hkpPhysicsSystemClass(
		"hkpPhysicsSystem",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPhysicsSystemClass_Members),
		HK_COUNT_OF(hkpPhysicsSystemClass_Members),
		&hkpPhysicsSystem_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnWorldModeEnumItems[] =
	{
		{0, "HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK"},
		{1, "HK_UPDATE_FILTER_ON_WORLD_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY"},
	};
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnEntityModeEnumItems[] =
	{
		{0, "HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK"},
		{1, "HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY"},
	};
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpEntityActivationEnumItems[] =
	{
		{0, "HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE"},
		{1, "HK_ENTITY_ACTIVATION_DO_ACTIVATE"},
	};
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollectionFilterModeEnumItems[] =
	{
		{0, "HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS"},
		{1, "HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS"},
	};
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpThreadTokenEnumItems[] =
	{
		{0, "HK_THREAD_TOKEN_FIRST"},
		{1, "HK_THREAD_TOKEN_SECOND"},
		{2, "HK_THREAD_TOKEN_THIRD"},
		{3, "HK_THREAD_TOKEN_FORTH"},
		{4, "HK_THREAD_TOKEN_FIFTH"},
		{5, "HK_THREAD_TOKEN_SIXTH"},
	};
	static const hkInternalClassEnum Physics_Dynamics_World_hkpWorldEnums[] = {
		{"hkpUpdateCollisionFilterOnWorldMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnWorldModeEnumItems, 2, HK_NULL, 0 },
		{"hkpUpdateCollisionFilterOnEntityMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnEntityModeEnumItems, 2, HK_NULL, 0 },
		{"hkpEntityActivation", Physics_Dynamics_World_hkpWorldhkpEntityActivationEnumItems, 2, HK_NULL, 0 },
		{"hkpUpdateCollectionFilterMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollectionFilterModeEnumItems, 2, HK_NULL, 0 },
		{"hkpThreadToken", Physics_Dynamics_World_hkpWorldhkpThreadTokenEnumItems, 6, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpUpdateCollisionFilterOnWorldModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[0]);
	extern const hkClassEnum* hkpUpdateCollisionFilterOnEntityModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[1]);
	extern const hkClassEnum* hkpEntityActivationEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[2]);
	extern const hkClassEnum* hkpUpdateCollectionFilterModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[3]);
	extern const hkClassEnum* hkpThreadTokenEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[4]);
	extern const hkClassEnum* hkpWorldCinfoContactPointGenerationEnum;
	extern const hkClassEnum* hkpWorldCinfoSimulationTypeEnum;
	static const hkInternalClassEnumItem hkpWorldReintegrationRecollideModeEnumItems[] =
	{
		{1, "RR_MODE_REINTEGRATE"},
		{2, "RR_MODE_RECOLLIDE_BROADPHASE"},
		{4, "RR_MODE_RECOLLIDE_NARROWPHASE"},
		{7, "RR_MODE_ALL"},
	};
	static const hkInternalClassEnumItem hkpWorldMtAccessCheckingEnumItems[] =
	{
		{0, "MT_ACCESS_CHECKING_ENABLED"},
		{1, "MT_ACCESS_CHECKING_DISABLED"},
	};
	static const hkInternalClassEnum hkpWorldEnums[] = {
		{"ReintegrationRecollideMode", hkpWorldReintegrationRecollideModeEnumItems, 4, HK_NULL, 0 },
		{"MtAccessChecking", hkpWorldMtAccessCheckingEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpWorldReintegrationRecollideModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldEnums[0]);
	extern const hkClassEnum* hkpWorldMtAccessCheckingEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldEnums[1]);
	static hkInternalClassMember hkpWorldClass_Members[] =
	{
		{ "simulation", &hkpSimulationClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fixedIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "fixedRigidBody", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "activeSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "inactiveSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "dirtySimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "maintenanceMgr", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "memoryWatchDog", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhaseDispatcher", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "phantomBroadPhaseListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "entityEntityBroadPhaseListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhaseBorderListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "multithreadedSimulationJobData", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "collisionInput", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "collisionFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "collisionDispatcher", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "convexListFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "pendingOperations", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "pendingOperationsCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "criticalOperationsLockCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "criticalOperationsLockCountForPhantoms", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockExecutingPendingOperations", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "criticalOperationsAllowed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pendingOperationQueues", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "pendingOperationQueueCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "multiThreadCheck", &hkMultiThreadCheckClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "processActionsInSingleThread", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minDesiredIslandSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "modifyConstraintCriticalSection", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "worldLock", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "islandDirtyListCriticalSection", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "propertyMasterLock", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "wantSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapCollisionToConvexEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapCollisionToConcaveEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableToiWeldRejection", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wantDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationReferenceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "simulationType", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "lastEntityUid", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "phantoms", &hkpPhantomClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "actionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "entityListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "phantomListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "constraintListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "worldDeletionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "islandActivationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "worldPostSimulationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "worldPostIntegrateListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "worldPostCollideListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "islandPostIntegrateListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "islandPostCollideListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "collisionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "contactImpulseLimitBreachedListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhaseBorder", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "broadPhaseExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sizeOfToiEventQueue", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseUpdateSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactPointGeneration", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpWorldClass(
		"hkpWorld",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpWorldEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkpWorldClass_Members),
		HK_COUNT_OF(hkpWorldClass_Members),
		HK_NULL,
		HK_NULL,
		hkClass::FLAGS_NOT_SERIALIZABLE
		);
	static const hkInternalClassEnumItem hkpWorldCinfoSolverTypeEnumItems[] =
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
	static const hkInternalClassEnumItem hkpWorldCinfoSimulationTypeEnumItems[] =
	{
		{0, "SIMULATION_TYPE_INVALID"},
		{1, "SIMULATION_TYPE_DISCRETE"},
		{2, "SIMULATION_TYPE_CONTINUOUS"},
		{3, "SIMULATION_TYPE_MULTITHREADED"},
	};
	static const hkInternalClassEnumItem hkpWorldCinfoContactPointGenerationEnumItems[] =
	{
		{0, "CONTACT_POINT_ACCEPT_ALWAYS"},
		{1, "CONTACT_POINT_REJECT_DUBIOUS"},
		{2, "CONTACT_POINT_REJECT_MANY"},
	};
	static const hkInternalClassEnumItem hkpWorldCinfoBroadPhaseBorderBehaviourEnumItems[] =
	{
		{0, "BROADPHASE_BORDER_ASSERT"},
		{1, "BROADPHASE_BORDER_FIX_ENTITY"},
		{2, "BROADPHASE_BORDER_REMOVE_ENTITY"},
		{3, "BROADPHASE_BORDER_DO_NOTHING"},
	};
	static const hkInternalClassEnum hkpWorldCinfoEnums[] = {
		{"SolverType", hkpWorldCinfoSolverTypeEnumItems, 11, HK_NULL, 0 },
		{"SimulationType", hkpWorldCinfoSimulationTypeEnumItems, 4, HK_NULL, 0 },
		{"ContactPointGeneration", hkpWorldCinfoContactPointGenerationEnumItems, 3, HK_NULL, 0 },
		{"BroadPhaseBorderBehaviour", hkpWorldCinfoBroadPhaseBorderBehaviourEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpWorldCinfoSolverTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[0]);
	extern const hkClassEnum* hkpWorldCinfoSimulationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[1]);
	extern const hkClassEnum* hkpWorldCinfoContactPointGenerationEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[2]);
	extern const hkClassEnum* hkpWorldCinfoBroadPhaseBorderBehaviourEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[3]);
	static hkInternalClassMember hkpWorldCinfoClass_Members[] =
	{
		{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactRestingVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseBorderBehaviour", HK_NULL, hkpWorldCinfoBroadPhaseBorderBehaviourEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "broadPhaseWorldAabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionFilter", &hkpCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "convexListFilter", &hkpConvexListFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "expectedMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sizeOfToiEventQueue", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "expectedMinPsiDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "memoryWatchDog", &hkWorldMemoryAvailableWatchDogClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactPointGeneration", HK_NULL, hkpWorldCinfoContactPointGenerationEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "solverTau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverDamp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverMicrosteps", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forceCoherentConstraintOrderingInSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapCollisionToConvexEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "snapCollisionToConcaveEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableToiWeldRejection", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableDeprecatedWelding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastEarlyOutDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastMaxIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationNumInactiveFramesSelectFlag0", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationNumInactiveFramesSelectFlag1", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationIntegrateCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationReferenceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "simulationType", HK_NULL, hkpWorldCinfoSimulationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "enableSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minDesiredIslandSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "processActionsInSingleThread", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameMarkerPsiSnap", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpWorldCinfo_DefaultStruct
		{
			int s_defaultOffsets[39];
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
			int m_sizeOfToiEventQueue;
			hkReal m_expectedMinPsiDeltaTime;
			hkReal m_solverDamp;
			hkInt32 m_solverIterations;
			hkInt32 m_solverMicrosteps;
			hkReal m_snapCollisionToConvexEdgeThreshold;
			hkReal m_snapCollisionToConcaveEdgeThreshold;
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
		const hkpWorldCinfo_DefaultStruct hkpWorldCinfo_Default =
		{
			{HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_gravity),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_broadPhaseQuerySize),-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_collisionTolerance),-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_expectedMaxLinearVelocity),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_sizeOfToiEventQueue),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_expectedMinPsiDeltaTime),-1,-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverDamp),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverIterations),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverMicrosteps),-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_snapCollisionToConvexEdgeThreshold),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_snapCollisionToConcaveEdgeThreshold),-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_iterativeLinearCastEarlyOutDistance),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_iterativeLinearCastMaxIterations),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_highFrequencyDeactivationPeriod),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_lowFrequencyDeactivationPeriod),-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_shouldActivateOnRigidBodyTransformChange),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_deactivationReferenceDistance),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_toiCollisionResponseRotateNormal),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_enableDeactivation),-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_enableSimulationIslands),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_minDesiredIslandSize),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_processActionsInSingleThread),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_frameMarkerPsiSnap)},
			{0,-9.8f,0},1024,.1f,200,250,1.0f/30.0f,.6f,4,1,.524f,0.698f,.01f,20,.2f,10,true,0.02f,0.2f,true,true,64,true,.0001f
		};
	}
	hkClass hkpWorldCinfoClass(
		"hkpWorldCinfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpWorldCinfoEnums),
		4,
		reinterpret_cast<const hkClassMember*>(hkpWorldCinfoClass_Members),
		HK_COUNT_OF(hkpWorldCinfoClass_Members),
		&hkpWorldCinfo_Default,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldObjectResultEnumItems[] =
	{
		{0, "POSTPONED"},
		{1, "DONE"},
	};
	static const hkInternalClassEnum Physics_Dynamics_World_hkpWorldObjectEnums[] = {
		{"Result", Physics_Dynamics_World_hkpWorldObjectResultEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* ResultEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldObjectEnums[0]);
	static const hkInternalClassEnumItem hkpWorldObjectBroadPhaseTypeEnumItems[] =
	{
		{0, "BROAD_PHASE_INVALID"},
		{1, "BROAD_PHASE_ENTITY"},
		{2, "BROAD_PHASE_PHANTOM"},
		{3, "BROAD_PHASE_BORDER"},
		{4, "BROAD_PHASE_MAX_ID"},
	};
	static const hkInternalClassEnum hkpWorldObjectEnums[] = {
		{"BroadPhaseType", hkpWorldObjectBroadPhaseTypeEnumItems, 5, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpWorldObjectBroadPhaseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldObjectEnums[0]);
	static hkInternalClassMember hkpWorldObjectClass_Members[] =
	{
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collidable", &hkpLinkedCollidableClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "multiThreadCheck", &hkMultiThreadCheckClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "properties", &hkpPropertyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpWorldObjectClass(
		"hkpWorldObject",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpWorldObjectEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpWorldObjectClass_Members),
		HK_COUNT_OF(hkpWorldObjectClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkWorldMemoryAvailableWatchDogClass_Members[] =
	{
		{ "minMemoryAvailable", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWorldMemoryAvailableWatchDogClass(
		"hkWorldMemoryAvailableWatchDog",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWorldMemoryAvailableWatchDogClass_Members),
		HK_COUNT_OF(hkWorldMemoryAvailableWatchDogClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem Physics_Dynamics_World_Simulation_hkpSimulationhkpStepResultEnumItems[] =
	{
		{0, "HK_STEP_RESULT_SUCCESS"},
		{1, "HK_STEP_RESULT_MEMORY_FAILURE_BEFORE_INTEGRATION"},
		{2, "HK_STEP_RESULT_MEMORY_FAILURE_DURING_COLLIDE"},
		{3, "HK_STEP_RESULT_MEMORY_FAILURE_DURING_TOI_SOLVE"},
	};
	static const hkInternalClassEnum Physics_Dynamics_World_Simulation_hkpSimulationEnums[] = {
		{"hkpStepResult", Physics_Dynamics_World_Simulation_hkpSimulationhkpStepResultEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpStepResultEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_Simulation_hkpSimulationEnums[0]);
	static const hkInternalClassEnumItem hkpSimulationFindContactsEnumItems[] =
	{
		{0, "FIND_CONTACTS_DEFAULT"},
		{1, "FIND_CONTACTS_EXTRA"},
	};
	static const hkInternalClassEnumItem hkpSimulationLastProcessingStepEnumItems[] =
	{
		{0, "INTEGRATE"},
		{1, "COLLIDE"},
	};
	static const hkInternalClassEnum hkpSimulationEnums[] = {
		{"FindContacts", hkpSimulationFindContactsEnumItems, 2, HK_NULL, 0 },
		{"LastProcessingStep", hkpSimulationLastProcessingStepEnumItems, 2, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpSimulationFindContactsEnum = reinterpret_cast<const hkClassEnum*>(&hkpSimulationEnums[0]);
	extern const hkClassEnum* hkpSimulationLastProcessingStepEnum = reinterpret_cast<const hkClassEnum*>(&hkpSimulationEnums[1]);
	static hkInternalClassMember hkpSimulationClass_Members[] =
	{
		{ "world", &hkpWorldClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "lastProcessingStep", HK_NULL, hkpSimulationLastProcessingStepEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "currentTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "currentPsiTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "physicsDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "simulateUntilTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frameMarkerPsiSnap", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "previousStepResult", HK_NULL, hkpStepResultEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSimulationClass(
		"hkpSimulation",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpSimulationEnums),
		2,
		reinterpret_cast<const hkClassMember*>(hkpSimulationClass_Members),
		HK_COUNT_OF(hkpSimulationClass_Members),
		HK_NULL,
		HK_NULL,
		hkClass::FLAGS_NOT_SERIALIZABLE
		);
	static hkInternalClassMember hkpAgent1nSectorClass_Members[] =
	{
		{ "bytesAllocated", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad0", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad1", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad2", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 512-16, 0, 0, HK_NULL }
	};
	hkClass hkpAgent1nSectorClass(
		"hkpAgent1nSector",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAgent1nSectorClass_Members),
		HK_COUNT_OF(hkpAgent1nSectorClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpLinkedCollidableClass_Members[] =
	{
		{ "collisionEntries", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpLinkedCollidableClass(
		"hkpLinkedCollidable",
		&hkpCollidableClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpLinkedCollidableClass_Members),
		HK_COUNT_OF(hkpLinkedCollidableClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpBroadPhaseHandleClass_Members[] =
	{
		{ "id", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpBroadPhaseHandleClass(
		"hkpBroadPhaseHandle",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpBroadPhaseHandleClass_Members),
		HK_COUNT_OF(hkpBroadPhaseHandleClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConvexPieceStreamDataClass_Members[] =
	{
		{ "convexPieceStream", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "convexPieceOffsets", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL },
		{ "convexPieceSingleTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConvexPieceStreamDataClass(
		"hkpConvexPieceStreamData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConvexPieceStreamDataClass_Members),
		HK_COUNT_OF(hkpConvexPieceStreamDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMoppCodeReindexedTerminalClass_Members[] =
	{
		{ "origShapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reindexedShapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMoppCodeReindexedTerminalClass(
		"hkpMoppCodeReindexedTerminal",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMoppCodeReindexedTerminalClass_Members),
		HK_COUNT_OF(hkpMoppCodeReindexedTerminalClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMoppCode_CodeInfoClass_Members[] =
	{
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMoppCodeCodeInfoClass(
		"hkpMoppCodeCodeInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMoppCode_CodeInfoClass_Members),
		HK_COUNT_OF(hkpMoppCode_CodeInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMoppCodeClass_Members[] =
	{
		{ "info", &hkpMoppCodeCodeInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMoppCodeClass(
		"hkpMoppCode",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMoppCodeClass_Members),
		HK_COUNT_OF(hkpMoppCodeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpAngularDashpotActionClass_Members[] =
	{
		{ "rotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpAngularDashpotActionClass(
		"hkpAngularDashpotAction",
		&hkpBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpAngularDashpotActionClass_Members),
		HK_COUNT_OF(hkpAngularDashpotActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpDashpotActionClass_Members[] =
	{
		{ "point", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "impulse", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpDashpotActionClass(
		"hkpDashpotAction",
		&hkpBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpDashpotActionClass_Members),
		HK_COUNT_OF(hkpDashpotActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMotorActionClass_Members[] =
	{
		{ "axis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spinRate", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gain", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "active", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpMotorActionClass(
		"hkpMotorAction",
		&hkpUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMotorActionClass_Members),
		HK_COUNT_OF(hkpMotorActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpMouseSpringActionClass_Members[] =
	{
		{ "positionInRbLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "mousePositionInWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "springElasticity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxRelativeForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "applyCallbacks", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpMouseSpringActionClass(
		"hkpMouseSpringAction",
		&hkpUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpMouseSpringActionClass_Members),
		HK_COUNT_OF(hkpMouseSpringActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpReorientActionClass_Members[] =
	{
		{ "rotationAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "upAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpReorientActionClass(
		"hkpReorientAction",
		&hkpUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpReorientActionClass_Members),
		HK_COUNT_OF(hkpReorientActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSpringActionClass_Members[] =
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
	hkClass hkpSpringActionClass(
		"hkpSpringAction",
		&hkpBinaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSpringActionClass_Members),
		HK_COUNT_OF(hkpSpringActionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpCharacterProxyCinfoClass_Members[] =
	{
		{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dynamicFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "staticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "keepContactTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraUpStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraDownStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapePhantom", &hkpShapePhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		struct hkpCharacterProxyCinfo_DefaultStruct
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
		};
		const hkpCharacterProxyCinfo_DefaultStruct hkpCharacterProxyCinfo_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpCharacterProxyCinfo_DefaultStruct,m_contactAngleSensitivity),-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpCharacterProxyCinfo_DefaultStruct,m_maxCastIterations),-1},
			10,10
		};
	}
	hkClass hkpCharacterProxyCinfoClass(
		"hkpCharacterProxyCinfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpCharacterProxyCinfoClass_Members),
		HK_COUNT_OF(hkpCharacterProxyCinfoClass_Members),
		&hkpCharacterProxyCinfo_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpConstrainedSystemFilterClass_Members[] =
	{
		{ "otherFilter", &hkpCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpConstrainedSystemFilterClass(
		"hkpConstrainedSystemFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpConstrainedSystemFilterClass_Members),
		HK_COUNT_OF(hkpConstrainedSystemFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPairwiseCollisionFilter_CollisionPairClass_Members[] =
	{
		{ "a", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "b", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPairwiseCollisionFilterCollisionPairClass(
		"hkpPairwiseCollisionFilterCollisionPair",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPairwiseCollisionFilter_CollisionPairClass_Members),
		HK_COUNT_OF(hkpPairwiseCollisionFilter_CollisionPairClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPairwiseCollisionFilterClass_Members[] =
	{
		{ "disabledPairs", &hkpPairwiseCollisionFilterCollisionPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPairwiseCollisionFilterClass(
		"hkpPairwiseCollisionFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPairwiseCollisionFilterClass_Members),
		HK_COUNT_OF(hkpPairwiseCollisionFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPoweredChainMapper_TargetClass_Members[] =
	{
		{ "chain", &hkpPoweredChainDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "infoIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPoweredChainMapperTargetClass(
		"hkpPoweredChainMapperTarget",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapper_TargetClass_Members),
		HK_COUNT_OF(hkpPoweredChainMapper_TargetClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPoweredChainMapper_LinkInfoClass_Members[] =
	{
		{ "firstTargetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numTargets", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "limitConstraint", &hkpConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPoweredChainMapperLinkInfoClass(
		"hkpPoweredChainMapperLinkInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapper_LinkInfoClass_Members),
		HK_COUNT_OF(hkpPoweredChainMapper_LinkInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPoweredChainMapperClass_Members[] =
	{
		{ "links", &hkpPoweredChainMapperLinkInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "targets", &hkpPoweredChainMapperTargetClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "chains", &hkpConstraintChainInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPoweredChainMapperClass(
		"hkpPoweredChainMapper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapperClass_Members),
		HK_COUNT_OF(hkpPoweredChainMapperClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpDisableEntityCollisionFilterClass_Members[] =
	{
		{ "disabledEntities", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpDisableEntityCollisionFilterClass(
		"hkpDisableEntityCollisionFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpDisableEntityCollisionFilterClass_Members),
		HK_COUNT_OF(hkpDisableEntityCollisionFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpGroupCollisionFilterClass_Members[] =
	{
		{ "noGroupCollisionEnabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionGroups", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 32, 0, 0, HK_NULL }
	};
	hkClass hkpGroupCollisionFilterClass(
		"hkpGroupCollisionFilter",
		&hkpCollisionFilterClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpGroupCollisionFilterClass_Members),
		HK_COUNT_OF(hkpGroupCollisionFilterClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPhysicsSystemWithContactsClass_Members[] =
	{
		{ "contacts", &hkpSerializedAgentNnEntryClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPhysicsSystemWithContactsClass(
		"hkpPhysicsSystemWithContacts",
		&hkpPhysicsSystemClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPhysicsSystemWithContactsClass_Members),
		HK_COUNT_OF(hkpPhysicsSystemWithContactsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedTrack1nInfoClass_Members[] =
	{
		{ "sectors", &hkpAgent1nSectorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "subTracks", &hkpSerializedSubTrack1nInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedTrack1nInfoClass(
		"hkpSerializedTrack1nInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedTrack1nInfoClass_Members),
		HK_COUNT_OF(hkpSerializedTrack1nInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedSubTrack1nInfoClass_Members[] =
	{
		{ "sectorIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offsetInSector", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedSubTrack1nInfoClass(
		"hkpSerializedSubTrack1nInfo",
		&hkpSerializedTrack1nInfoClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedSubTrack1nInfoClass_Members),
		HK_COUNT_OF(hkpSerializedSubTrack1nInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static const hkInternalClassEnumItem hkpSerializedAgentNnEntrySerializedAgentTypeEnumItems[] =
	{
		{0, "INVALID_AGENT_TYPE"},
		{1, "BOX_BOX_AGENT3"},
		{2, "CAPSULE_TRIANGLE_AGENT3"},
		{3, "PRED_GSK_AGENT3"},
		{4, "PRED_GSK_CYLINDER_AGENT3"},
		{5, "CONVEX_LIST_AGENT3"},
		{6, "LIST_AGENT3"},
		{7, "BV_TREE_AGENT3"},
		{8, "COLLECTION_COLLECTION_AGENT3"},
	};
	static const hkInternalClassEnum hkpSerializedAgentNnEntryEnums[] = {
		{"SerializedAgentType", hkpSerializedAgentNnEntrySerializedAgentTypeEnumItems, 9, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkpSerializedAgentNnEntrySerializedAgentTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpSerializedAgentNnEntryEnums[0]);
	static hkInternalClassMember hkpSerializedAgentNnEntryClass_Members[] =
	{
		{ "bodyA", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "bodyB", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "bodyAId", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "bodyBId", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "useEntityIds", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "agentType", HK_NULL, hkpSerializedAgentNnEntrySerializedAgentTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "atom", &hkpSimpleContactConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "propertiesStream", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "contactPoints", &hkContactPointClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "cpIdMgr", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "nnEntryData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 128, 0, 0, HK_NULL },
		{ "trackInfo", &hkpSerializedTrack1nInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endianCheckBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, 0, HK_NULL },
		{ "version", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedAgentNnEntryClass(
		"hkpSerializedAgentNnEntry",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkpSerializedAgentNnEntryEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkpSerializedAgentNnEntryClass_Members),
		HK_COUNT_OF(hkpSerializedAgentNnEntryClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRigidBodyDisplayBindingClass_Members[] =
	{
		{ "rigidBody", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "displayObject", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rigidBodyFromDisplayObjectTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpRigidBodyDisplayBindingClass(
		"hkpRigidBodyDisplayBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRigidBodyDisplayBindingClass_Members),
		HK_COUNT_OF(hkpRigidBodyDisplayBindingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPhysicsSystemDisplayBindingClass_Members[] =
	{
		{ "bindings", &hkpRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "system", &hkpPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPhysicsSystemDisplayBindingClass(
		"hkpPhysicsSystemDisplayBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPhysicsSystemDisplayBindingClass_Members),
		HK_COUNT_OF(hkpPhysicsSystemDisplayBindingClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpDisplayBindingDataClass_Members[] =
	{
		{ "rigidBodyBindings", &hkpRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "physicsSystemBindings", &hkpPhysicsSystemDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpDisplayBindingDataClass(
		"hkpDisplayBindingData",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpDisplayBindingDataClass_Members),
		HK_COUNT_OF(hkpDisplayBindingDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpPhysicsDataClass_Members[] =
	{
		{ "worldCinfo", &hkpWorldCinfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "systems", &hkpPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpPhysicsDataClass(
		"hkpPhysicsData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpPhysicsDataClass_Members),
		HK_COUNT_OF(hkpPhysicsDataClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedDisplayMarkerClass_Members[] =
	{
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedDisplayMarkerClass(
		"hkpSerializedDisplayMarker",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayMarkerClass_Members),
		HK_COUNT_OF(hkpSerializedDisplayMarkerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedDisplayMarkerListClass_Members[] =
	{
		{ "markers", &hkpSerializedDisplayMarkerClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedDisplayMarkerListClass(
		"hkpSerializedDisplayMarkerList",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayMarkerListClass_Members),
		HK_COUNT_OF(hkpSerializedDisplayMarkerListClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members[] =
	{
		{ "rb", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "localToDisplay", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedDisplayRbTransformsDisplayTransformPairClass(
		"hkpSerializedDisplayRbTransformsDisplayTransformPair",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members),
		HK_COUNT_OF(hkpSerializedDisplayRbTransforms_DisplayTransformPairClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpSerializedDisplayRbTransformsClass_Members[] =
	{
		{ "transforms", &hkpSerializedDisplayRbTransformsDisplayTransformPairClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpSerializedDisplayRbTransformsClass(
		"hkpSerializedDisplayRbTransforms",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpSerializedDisplayRbTransformsClass_Members),
		HK_COUNT_OF(hkpSerializedDisplayRbTransformsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleData_WheelComponentParamsClass_Members[] =
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
	hkClass hkpVehicleDataWheelComponentParamsClass(
		"hkpVehicleDataWheelComponentParams",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleData_WheelComponentParamsClass_Members),
		HK_COUNT_OF(hkpVehicleData_WheelComponentParamsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDataClass_Members[] =
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
		{ "maxFrictionSolverMassRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "wheelParams", &hkpVehicleDataWheelComponentParamsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "numWheelsPerAxle", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_INT8, 0, 0, 0, HK_NULL },
		{ "frictionDescription", &hkpVehicleFrictionDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisFrictionInertiaInvDiag", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "alreadyInitialised", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	namespace
	{
		struct hkpVehicleData_DefaultStruct
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
			hkReal m_maxFrictionSolverMassRatio;
		};
		const hkpVehicleData_DefaultStruct hkpVehicleData_Default =
		{
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpVehicleData_DefaultStruct,m_maxFrictionSolverMassRatio),-1,-1,-1,-1,-1},
			30.0
		};
	}
	hkClass hkpVehicleDataClass(
		"hkpVehicleData",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDataClass_Members),
		HK_COUNT_OF(hkpVehicleDataClass_Members),
		&hkpVehicleData_Default,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleInstance_WheelInfoClass_Members[] =
	{
		{ "contactPoint", &hkContactPointClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactBody", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL },
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
	hkClass hkpVehicleInstanceWheelInfoClass(
		"hkpVehicleInstanceWheelInfo",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleInstance_WheelInfoClass_Members),
		HK_COUNT_OF(hkpVehicleInstance_WheelInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleInstanceClass_Members[] =
	{
		{ "data", &hkpVehicleDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "driverInput", &hkpVehicleDriverInputClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "steering", &hkpVehicleSteeringClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "engine", &hkpVehicleEngineClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "transmission", &hkpVehicleTransmissionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "brake", &hkpVehicleBrakeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "suspension", &hkpVehicleSuspensionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "aerodynamics", &hkpVehicleAerodynamicsClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelCollide", &hkpVehicleWheelCollideClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "tyreMarks", &hkpTyremarksInfoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "velocityDamper", &hkpVehicleVelocityDamperClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelsInfo", &hkpVehicleInstanceWheelInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "frictionStatus", &hkpVehicleFrictionStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deviceStatus", &hkpVehicleDriverInputStatusClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
	hkClass hkpVehicleInstanceClass(
		"hkpVehicleInstance",
		&hkpUnaryActionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleInstanceClass_Members),
		HK_COUNT_OF(hkpVehicleInstanceClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleAerodynamicsClass(
		"hkpVehicleAerodynamics",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultAerodynamicsClass_Members[] =
	{
		{ "airDensity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "frontalArea", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dragCoefficient", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "liftCoefficient", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraGravityws", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultAerodynamicsClass(
		"hkpVehicleDefaultAerodynamics",
		&hkpVehicleAerodynamicsClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultAerodynamicsClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultAerodynamicsClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleBrakeClass(
		"hkpVehicleBrake",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members[] =
	{
		{ "maxBreakingTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minPedalInputToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isConnectedToHandbrake", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultBrakeWheelBrakingPropertiesClass(
		"hkpVehicleDefaultBrakeWheelBrakingProperties",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultBrake_WheelBrakingPropertiesClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultBrakeClass_Members[] =
	{
		{ "wheelBrakingProperties", &hkpVehicleDefaultBrakeWheelBrakingPropertiesClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "wheelsMinTimeToBlock", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultBrakeClass(
		"hkpVehicleDefaultBrake",
		&hkpVehicleBrakeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultBrakeClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultBrakeClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleDriverInputStatusClass(
		"hkpVehicleDriverInputStatus",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleDriverInputClass(
		"hkpVehicleDriverInput",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDriverInputAnalogStatusClass_Members[] =
	{
		{ "positionX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "positionY", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "handbrakeButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reverseButtonPressed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDriverInputAnalogStatusClass(
		"hkpVehicleDriverInputAnalogStatus",
		&hkpVehicleDriverInputStatusClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDriverInputAnalogStatusClass_Members),
		HK_COUNT_OF(hkpVehicleDriverInputAnalogStatusClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultAnalogDriverInputClass_Members[] =
	{
		{ "slopeChangePointX", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deadZone", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "autoReverse", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultAnalogDriverInputClass(
		"hkpVehicleDefaultAnalogDriverInput",
		&hkpVehicleDriverInputClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultAnalogDriverInputClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultAnalogDriverInputClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleEngineClass(
		"hkpVehicleEngine",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultEngineClass_Members[] =
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
	hkClass hkpVehicleDefaultEngineClass(
		"hkpVehicleDefaultEngine",
		&hkpVehicleEngineClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultEngineClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultEngineClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleFrictionDescription_AxisDescriptionClass_Members[] =
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
	hkClass hkpVehicleFrictionDescriptionAxisDescriptionClass(
		"hkpVehicleFrictionDescriptionAxisDescription",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionDescription_AxisDescriptionClass_Members),
		HK_COUNT_OF(hkpVehicleFrictionDescription_AxisDescriptionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleFrictionDescriptionClass_Members[] =
	{
		{ "wheelDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "chassisMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axleDescr", &hkpVehicleFrictionDescriptionAxisDescriptionClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleFrictionDescriptionClass(
		"hkpVehicleFrictionDescription",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionDescriptionClass_Members),
		HK_COUNT_OF(hkpVehicleFrictionDescriptionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleFrictionStatus_AxisStatusClass_Members[] =
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
	hkClass hkpVehicleFrictionStatusAxisStatusClass(
		"hkpVehicleFrictionStatusAxisStatus",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionStatus_AxisStatusClass_Members),
		HK_COUNT_OF(hkpVehicleFrictionStatus_AxisStatusClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleFrictionStatusClass_Members[] =
	{
		{ "axis", &hkpVehicleFrictionStatusAxisStatusClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 2, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleFrictionStatusClass(
		"hkpVehicleFrictionStatus",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleFrictionStatusClass_Members),
		HK_COUNT_OF(hkpVehicleFrictionStatusClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleSteeringClass(
		"hkpVehicleSteering",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultSteeringClass_Members[] =
	{
		{ "maxSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxSpeedFullSteeringAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "doesWheelSteer", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_BOOL, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultSteeringClass(
		"hkpVehicleDefaultSteering",
		&hkpVehicleSteeringClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultSteeringClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultSteeringClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleSuspension_SuspensionWheelParametersClass_Members[] =
	{
		{ "hardpointCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "directionCs", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleSuspensionSuspensionWheelParametersClass(
		"hkpVehicleSuspensionSuspensionWheelParameters",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleSuspension_SuspensionWheelParametersClass_Members),
		HK_COUNT_OF(hkpVehicleSuspension_SuspensionWheelParametersClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleSuspensionClass_Members[] =
	{
		{ "wheelParams", &hkpVehicleSuspensionSuspensionWheelParametersClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleSuspensionClass(
		"hkpVehicleSuspension",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleSuspensionClass_Members),
		HK_COUNT_OF(hkpVehicleSuspensionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members[] =
	{
		{ "strength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dampingCompression", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "dampingRelaxation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultSuspensionWheelSpringSuspensionParametersClass(
		"hkpVehicleDefaultSuspensionWheelSpringSuspensionParameters",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultSuspension_WheelSpringSuspensionParametersClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultSuspensionClass_Members[] =
	{
		{ "wheelSpringParams", &hkpVehicleDefaultSuspensionWheelSpringSuspensionParametersClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultSuspensionClass(
		"hkpVehicleDefaultSuspension",
		&hkpVehicleSuspensionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultSuspensionClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultSuspensionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleTransmissionClass(
		"hkpVehicleTransmission",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultTransmissionClass_Members[] =
	{
		{ "downshiftRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "upshiftRPM", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "primaryTransmissionRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "clutchDelayTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "reverseGearRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "gearsRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "wheelsTorqueRatio", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultTransmissionClass(
		"hkpVehicleDefaultTransmission",
		&hkpVehicleTransmissionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultTransmissionClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultTransmissionClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTyremarkPointClass_Members[] =
	{
		{ "pointLeft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pointRight", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTyremarkPointClass(
		"hkpTyremarkPoint",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTyremarkPointClass_Members),
		HK_COUNT_OF(hkpTyremarkPointClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTyremarksWheelClass_Members[] =
	{
		{ "currentPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tyremarkPoints", &hkpTyremarkPointClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTyremarksWheelClass(
		"hkpTyremarksWheel",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTyremarksWheelClass_Members),
		HK_COUNT_OF(hkpTyremarksWheelClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpTyremarksInfoClass_Members[] =
	{
		{ "minTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxTyremarkEnergy", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "tyremarksWheel", &hkpTyremarksWheelClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkpTyremarksInfoClass(
		"hkpTyremarksInfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpTyremarksInfoClass_Members),
		HK_COUNT_OF(hkpTyremarksInfoClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	hkClass hkpVehicleVelocityDamperClass(
		"hkpVehicleVelocityDamper",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleDefaultVelocityDamperClass_Members[] =
	{
		{ "normalSpinDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionSpinDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleDefaultVelocityDamperClass(
		"hkpVehicleDefaultVelocityDamper",
		&hkpVehicleVelocityDamperClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleDefaultVelocityDamperClass_Members),
		HK_COUNT_OF(hkpVehicleDefaultVelocityDamperClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleWheelCollideClass_Members[] =
	{
		{ "alreadyUsed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleWheelCollideClass(
		"hkpVehicleWheelCollide",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleWheelCollideClass_Members),
		HK_COUNT_OF(hkpVehicleWheelCollideClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpRejectRayChassisListenerClass_Members[] =
	{
		{ "chassis", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, 0, HK_NULL }
	};
	hkClass hkpRejectRayChassisListenerClass(
		"hkpRejectRayChassisListener",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		1,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpRejectRayChassisListenerClass_Members),
		HK_COUNT_OF(hkpRejectRayChassisListenerClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);
	static hkInternalClassMember hkpVehicleRaycastWheelCollideClass_Members[] =
	{
		{ "wheelCollisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "phantom", &hkpAabbPhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "rejectRayChassisListener", &hkpRejectRayChassisListenerClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkpVehicleRaycastWheelCollideClass(
		"hkpVehicleRaycastWheelCollide",
		&hkpVehicleWheelCollideClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkpVehicleRaycastWheelCollideClass_Members),
		HK_COUNT_OF(hkpVehicleRaycastWheelCollideClass_Members),
		HK_NULL,
		HK_NULL,
		0
		);

	hkClass* const Classes[] =
	{
		&hkAabbClass,
		&hkAabbUint32Class,
		&hkBaseObjectClass,
		&hkBitFieldClass,
		&hkClassClass,
		&hkClassEnumClass,
		&hkClassEnumItemClass,
		&hkClassMemberClass,
		&hkContactPointClass,
		&hkContactPointMaterialClass,
		&hkCustomAttributesAttributeClass,
		&hkCustomAttributesClass,
		&hkMonitorStreamFrameInfoClass,
		&hkMonitorStreamStringMapClass,
		&hkMonitorStreamStringMapStringMapClass,
		&hkMoppBvTreeShapeBaseClass,
		&hkMotionStateClass,
		&hkMultiThreadCheckClass,
		&hkPackfileHeaderClass,
		&hkPackfileSectionHeaderClass,
		&hkReferencedObjectClass,
		&hkRootLevelContainerClass,
		&hkRootLevelContainerNamedVariantClass,
		&hkSphereClass,
		&hkSweptTransformClass,
		&hkVariableTweakingHelperBoolVariableInfoClass,
		&hkVariableTweakingHelperClass,
		&hkVariableTweakingHelperIntVariableInfoClass,
		&hkVariableTweakingHelperRealVariableInfoClass,
		&hkWorldMemoryAvailableWatchDogClass,
		&hkaAnimatedReferenceFrameClass,
		&hkaAnimationBindingClass,
		&hkaAnimationContainerClass,
		&hkaAnnotationTrackAnnotationClass,
		&hkaAnnotationTrackClass,
		&hkaBoneAttachmentClass,
		&hkaBoneClass,
		&hkaDefaultAnimatedReferenceFrameClass,
		&hkaDeltaCompressedSkeletalAnimationClass,
		&hkaDeltaCompressedSkeletalAnimationQuantizationFormatClass,
		&hkaInterleavedSkeletalAnimationClass,
		&hkaKeyFrameHierarchyUtilityClass,
		&hkaKeyFrameHierarchyUtilityControlDataClass,
		&hkaMeshBindingClass,
		&hkaMeshBindingMappingClass,
		&hkaRagdollInstanceClass,
		&hkaSkeletalAnimationClass,
		&hkaSkeletonClass,
		&hkaSkeletonMapperClass,
		&hkaSkeletonMapperDataChainMappingClass,
		&hkaSkeletonMapperDataClass,
		&hkaSkeletonMapperDataSimpleMappingClass,
		&hkaWaveletSkeletalAnimationClass,
		&hkaWaveletSkeletalAnimationCompressionParamsClass,
		&hkaWaveletSkeletalAnimationQuantizationFormatClass,
		&hkbAdditiveBinaryBlenderGeneratorClass,
		&hkbAlignBoneModifierClass,
		&hkbAttachmentModifierAttachmentPropertiesClass,
		&hkbAttachmentModifierClass,
		&hkbAttachmentSetupClass,
		&hkbAttributeModifierAssignmentClass,
		&hkbAttributeModifierClass,
		&hkbBalanceControllerModifierClass,
		&hkbBalanceModifierClass,
		&hkbBalanceModifierStepInfoClass,
		&hkbBalanceRadialSelectorGeneratorClass,
		&hkbBehaviorGraphClass,
		&hkbBehaviorGraphDataClass,
		&hkbBehaviorGraphStringDataClass,
		&hkbBehaviorReferenceGeneratorClass,
		&hkbBinaryBlenderGeneratorClass,
		&hkbBlenderGeneratorChildClass,
		&hkbBlenderGeneratorClass,
		&hkbBlendingTransitionEffectClass,
		&hkbBoolVariableSequencedDataClass,
		&hkbBoolVariableSequencedDataSampleClass,
		&hkbCatchFallModifierClass,
		&hkbCharacterBoneInfoClass,
		&hkbCharacterClass,
		&hkbCharacterDataClass,
		&hkbCharacterFakeQueueClass,
		&hkbCharacterSetupClass,
		&hkbCharacterStringDataClass,
		&hkbCheckBalanceModifierClass,
		&hkbCheckRagdollSpeedModifierClass,
		&hkbClimbMountingPredicateClass,
		&hkbClipGeneratorClass,
		&hkbClipTriggerClass,
		&hkbComputeWorldFromModelModifierClass,
		&hkbConstrainRigidBodyModifierClass,
		&hkbContextClass,
		&hkbControlledReachModifierClass,
		&hkbCustomTestGeneratorClass,
		&hkbCustomTestGeneratorStruckClass,
		&hkbDelayedModifierClass,
		&hkbDemoConfigCharacterInfoClass,
		&hkbDemoConfigClass,
		&hkbDemoConfigStickVariableInfoClass,
		&hkbDemoConfigTerrainInfoClass,
		&hkbEventClass,
		&hkbEventSequencedDataClass,
		&hkbEventSequencedDataSequencedEventClass,
		&hkbFaceTargetModifierClass,
		&hkbFootIkControlDataClass,
		&hkbFootIkControlsModifierClass,
		&hkbFootIkGainsClass,
		&hkbFootIkModifierClass,
		&hkbFootIkModifierInternalLegDataClass,
		&hkbFootIkModifierLegClass,
		&hkbGeneratorClass,
		&hkbGeneratorOutputClass,
		&hkbGeneratorOutputTrackClass,
		&hkbGeneratorTransitionEffectClass,
		&hkbGetUpModifierClass,
		&hkbHandIkControlDataClass,
		&hkbHandIkModifierClass,
		&hkbHandIkModifierHandClass,
		&hkbHoldFromBlendingTransitionEffectClass,
		&hkbIntVariableSequencedDataClass,
		&hkbIntVariableSequencedDataSampleClass,
		&hkbKeyframeBonesModifierClass,
		&hkbKeyframeDataClass,
		&hkbLookAtModifierClass,
		&hkbManualSelectorGeneratorClass,
		&hkbMirrorModifierClass,
		&hkbMirroredSkeletonInfoClass,
		&hkbModifierClass,
		&hkbModifierGeneratorClass,
		&hkbModifierSequenceClass,
		&hkbMoveBoneTowardTargetModifierClass,
		&hkbMoveCharacterModifierClass,
		&hkbNodeClass,
		&hkbPoseMatchingGeneratorClass,
		&hkbPoweredRagdollControlDataClass,
		&hkbPoweredRagdollControlsModifierClass,
		&hkbPoweredRagdollModifierClass,
		&hkbPredicateClass,
		&hkbProjectDataClass,
		&hkbProjectStringDataClass,
		&hkbRadialSelectorGeneratorClass,
		&hkbRadialSelectorGeneratorGeneratorInfoClass,
		&hkbRadialSelectorGeneratorGeneratorPairClass,
		&hkbRagdollDriverModifierClass,
		&hkbRagdollForceModifierClass,
		&hkbReachModifierClass,
		&hkbReachTowardTargetModifierClass,
		&hkbRealVariableSequencedDataClass,
		&hkbRealVariableSequencedDataSampleClass,
		&hkbReferencePoseGeneratorClass,
		&hkbRigidBodyRagdollControlDataClass,
		&hkbRigidBodyRagdollControlsModifierClass,
		&hkbRigidBodyRagdollModifierClass,
		&hkbRotateCharacterModifierClass,
		&hkbSequenceClass,
		&hkbSequenceStringDataClass,
		&hkbSequencedDataClass,
		&hkbStateDependentModifierClass,
		&hkbStateMachineActiveTransitionInfoClass,
		&hkbStateMachineClass,
		&hkbStateMachineProspectiveTransitionInfoClass,
		&hkbStateMachineStateInfoClass,
		&hkbStateMachineTimeIntervalClass,
		&hkbStateMachineTransitionInfoClass,
		&hkbStringPredicateClass,
		&hkbTargetClass,
		&hkbTargetRigidBodyModifierClass,
		&hkbTimerModifierClass,
		&hkbTransitionEffectClass,
		&hkbVariableBindingSetBindingClass,
		&hkbVariableBindingSetClass,
		&hkbVariableInfoClass,
		&hkbVariableSetClass,
		&hkbVariableSetTargetClass,
		&hkbVariableSetVariableClass,
		&hkbVariableValueClass,
		&hkp2dAngConstraintAtomClass,
		&hkpAabbPhantomClass,
		&hkpActionClass,
		&hkpAgent1nSectorClass,
		&hkpAngConstraintAtomClass,
		&hkpAngFrictionConstraintAtomClass,
		&hkpAngLimitConstraintAtomClass,
		&hkpAngMotorConstraintAtomClass,
		&hkpAngularDashpotActionClass,
		&hkpArrayActionClass,
		&hkpBallAndSocketConstraintDataAtomsClass,
		&hkpBallAndSocketConstraintDataClass,
		&hkpBallSocketChainDataClass,
		&hkpBallSocketChainDataConstraintInfoClass,
		&hkpBallSocketConstraintAtomClass,
		&hkpBinaryActionClass,
		&hkpBoxMotionClass,
		&hkpBoxShapeClass,
		&hkpBreakableConstraintDataClass,
		&hkpBridgeAtomsClass,
		&hkpBridgeConstraintAtomClass,
		&hkpBroadPhaseHandleClass,
		&hkpBvShapeClass,
		&hkpBvTreeShapeClass,
		&hkpCachingShapePhantomClass,
		&hkpCallbackConstraintMotorClass,
		&hkpCapsuleShapeClass,
		&hkpCdBodyClass,
		&hkpCharacterMotionClass,
		&hkpCharacterProxyCinfoClass,
		&hkpCollidableBoundingVolumeDataClass,
		&hkpCollidableClass,
		&hkpCollidableCollidableFilterClass,
		&hkpCollisionFilterClass,
		&hkpCollisionFilterListClass,
		&hkpConeLimitConstraintAtomClass,
		&hkpConstrainedSystemFilterClass,
		&hkpConstraintAtomClass,
		&hkpConstraintChainDataClass,
		&hkpConstraintChainInstanceActionClass,
		&hkpConstraintChainInstanceClass,
		&hkpConstraintDataClass,
		&hkpConstraintInstanceClass,
		&hkpConstraintMotorClass,
		&hkpConvexListFilterClass,
		&hkpConvexListShapeClass,
		&hkpConvexPieceMeshShapeClass,
		&hkpConvexPieceStreamDataClass,
		&hkpConvexShapeClass,
		&hkpConvexTransformShapeClass,
		&hkpConvexTranslateShapeClass,
		&hkpConvexVerticesShapeClass,
		&hkpConvexVerticesShapeFourVectorsClass,
		&hkpCylinderShapeClass,
		&hkpDashpotActionClass,
		&hkpDefaultConvexListFilterClass,
		&hkpDisableEntityCollisionFilterClass,
		&hkpDisplayBindingDataClass,
		&hkpEntityClass,
		&hkpEntityDeactivatorClass,
		&hkpEntityExtendedListenersClass,
		&hkpEntitySmallArraySerializeOverrideTypeClass,
		&hkpEntitySpuCollisionCallbackClass,
		&hkpExtendedMeshShapeClass,
		&hkpExtendedMeshShapeShapesSubpartClass,
		&hkpExtendedMeshShapeSubpartClass,
		&hkpExtendedMeshShapeTrianglesSubpartClass,
		&hkpFakeRigidBodyDeactivatorClass,
		&hkpFastMeshShapeClass,
		&hkpFixedRigidMotionClass,
		&hkpGenericConstraintDataClass,
		&hkpGenericConstraintDataSchemeClass,
		&hkpGenericConstraintDataSchemeConstraintInfoClass,
		&hkpGroupCollisionFilterClass,
		&hkpGroupFilterClass,
		&hkpHeightFieldShapeClass,
		&hkpHingeConstraintDataAtomsClass,
		&hkpHingeConstraintDataClass,
		&hkpHingeLimitsDataAtomsClass,
		&hkpHingeLimitsDataClass,
		&hkpKeyframedRigidMotionClass,
		&hkpLimitedForceConstraintMotorClass,
		&hkpLimitedHingeConstraintDataAtomsClass,
		&hkpLimitedHingeConstraintDataClass,
		&hkpLinConstraintAtomClass,
		&hkpLinFrictionConstraintAtomClass,
		&hkpLinLimitConstraintAtomClass,
		&hkpLinMotorConstraintAtomClass,
		&hkpLinSoftConstraintAtomClass,
		&hkpLinearParametricCurveClass,
		&hkpLinkedCollidableClass,
		&hkpListShapeChildInfoClass,
		&hkpListShapeClass,
		&hkpMalleableConstraintDataClass,
		&hkpMassChangerModifierConstraintAtomClass,
		&hkpMaterialClass,
		&hkpMaxSizeMotionClass,
		&hkpMeshMaterialClass,
		&hkpMeshShapeClass,
		&hkpMeshShapeSubpartClass,
		&hkpModifierConstraintAtomClass,
		&hkpMoppBvTreeShapeClass,
		&hkpMoppCodeClass,
		&hkpMoppCodeCodeInfoClass,
		&hkpMoppCodeReindexedTerminalClass,
		&hkpMoppEmbeddedShapeClass,
		&hkpMotionClass,
		&hkpMotorActionClass,
		&hkpMouseSpringActionClass,
		&hkpMovingSurfaceModifierConstraintAtomClass,
		&hkpMultiRayShapeClass,
		&hkpMultiRayShapeRayClass,
		&hkpMultiSphereShapeClass,
		&hkpNullCollisionFilterClass,
		&hkpOverwritePivotConstraintAtomClass,
		&hkpPackedConvexVerticesShapeClass,
		&hkpPackedConvexVerticesShapeFourVectorsClass,
		&hkpPackedConvexVerticesShapeVector4IntWClass,
		&hkpPairwiseCollisionFilterClass,
		&hkpPairwiseCollisionFilterCollisionPairClass,
		&hkpParametricCurveClass,
		&hkpPhantomCallbackShapeClass,
		&hkpPhantomClass,
		&hkpPhysicsDataClass,
		&hkpPhysicsSystemClass,
		&hkpPhysicsSystemDisplayBindingClass,
		&hkpPhysicsSystemWithContactsClass,
		&hkpPlaneShapeClass,
		&hkpPointToPathConstraintDataClass,
		&hkpPointToPlaneConstraintDataAtomsClass,
		&hkpPointToPlaneConstraintDataClass,
		&hkpPositionConstraintMotorClass,
		&hkpPoweredChainDataClass,
		&hkpPoweredChainDataConstraintInfoClass,
		&hkpPoweredChainMapperClass,
		&hkpPoweredChainMapperLinkInfoClass,
		&hkpPoweredChainMapperTargetClass,
		&hkpPrismaticConstraintDataAtomsClass,
		&hkpPrismaticConstraintDataClass,
		&hkpPropertyClass,
		&hkpPropertyValueClass,
		&hkpPulleyConstraintAtomClass,
		&hkpPulleyConstraintDataAtomsClass,
		&hkpPulleyConstraintDataClass,
		&hkpRagdollConstraintDataAtomsClass,
		&hkpRagdollConstraintDataClass,
		&hkpRagdollLimitsDataAtomsClass,
		&hkpRagdollLimitsDataClass,
		&hkpRagdollMotorConstraintAtomClass,
		&hkpRayCollidableFilterClass,
		&hkpRayShapeCollectionFilterClass,
		&hkpRejectRayChassisListenerClass,
		&hkpRemoveTerminalsMoppModifierClass,
		&hkpReorientActionClass,
		&hkpRigidBodyClass,
		&hkpRigidBodyDeactivatorClass,
		&hkpRigidBodyDisplayBindingClass,
		&hkpRotationalConstraintDataAtomsClass,
		&hkpRotationalConstraintDataClass,
		&hkpSampledHeightFieldShapeClass,
		&hkpSerializedAgentNnEntryClass,
		&hkpSerializedDisplayMarkerClass,
		&hkpSerializedDisplayMarkerListClass,
		&hkpSerializedDisplayRbTransformsClass,
		&hkpSerializedDisplayRbTransformsDisplayTransformPairClass,
		&hkpSerializedSubTrack1nInfoClass,
		&hkpSerializedTrack1nInfoClass,
		&hkpSetLocalRotationsConstraintAtomClass,
		&hkpSetLocalTransformsConstraintAtomClass,
		&hkpSetLocalTranslationsConstraintAtomClass,
		&hkpShapeClass,
		&hkpShapeCollectionClass,
		&hkpShapeCollectionFilterClass,
		&hkpShapeContainerClass,
		&hkpShapePhantomClass,
		&hkpShapeRayCastInputClass,
		&hkpSimpleContactConstraintAtomClass,
		&hkpSimpleContactConstraintDataInfoClass,
		&hkpSimpleMeshShapeClass,
		&hkpSimpleMeshShapeTriangleClass,
		&hkpSimpleShapePhantomClass,
		&hkpSimpleShapePhantomCollisionDetailClass,
		&hkpSimulationClass,
		&hkpSingleShapeContainerClass,
		&hkpSoftContactModifierConstraintAtomClass,
		&hkpSpatialRigidBodyDeactivatorClass,
		&hkpSpatialRigidBodyDeactivatorSampleClass,
		&hkpSphereMotionClass,
		&hkpSphereRepShapeClass,
		&hkpSphereShapeClass,
		&hkpSpringActionClass,
		&hkpSpringDamperConstraintMotorClass,
		&hkpStabilizedBoxMotionClass,
		&hkpStabilizedSphereMotionClass,
		&hkpStiffSpringChainDataClass,
		&hkpStiffSpringChainDataConstraintInfoClass,
		&hkpStiffSpringConstraintAtomClass,
		&hkpStiffSpringConstraintDataAtomsClass,
		&hkpStiffSpringConstraintDataClass,
		&hkpStorageExtendedMeshShapeClass,
		&hkpStorageExtendedMeshShapeMeshSubpartStorageClass,
		&hkpStorageExtendedMeshShapeShapeSubpartStorageClass,
		&hkpStorageMeshShapeClass,
		&hkpStorageMeshShapeSubpartStorageClass,
		&hkpStorageSampledHeightFieldShapeClass,
		&hkpThinBoxMotionClass,
		&hkpTransformShapeClass,
		&hkpTriSampledHeightFieldBvTreeShapeClass,
		&hkpTriSampledHeightFieldCollectionClass,
		&hkpTriangleShapeClass,
		&hkpTwistLimitConstraintAtomClass,
		&hkpTypedBroadPhaseHandleClass,
		&hkpTyremarkPointClass,
		&hkpTyremarksInfoClass,
		&hkpTyremarksWheelClass,
		&hkpUnaryActionClass,
		&hkpVehicleAerodynamicsClass,
		&hkpVehicleBrakeClass,
		&hkpVehicleDataClass,
		&hkpVehicleDataWheelComponentParamsClass,
		&hkpVehicleDefaultAerodynamicsClass,
		&hkpVehicleDefaultAnalogDriverInputClass,
		&hkpVehicleDefaultBrakeClass,
		&hkpVehicleDefaultBrakeWheelBrakingPropertiesClass,
		&hkpVehicleDefaultEngineClass,
		&hkpVehicleDefaultSteeringClass,
		&hkpVehicleDefaultSuspensionClass,
		&hkpVehicleDefaultSuspensionWheelSpringSuspensionParametersClass,
		&hkpVehicleDefaultTransmissionClass,
		&hkpVehicleDefaultVelocityDamperClass,
		&hkpVehicleDriverInputAnalogStatusClass,
		&hkpVehicleDriverInputClass,
		&hkpVehicleDriverInputStatusClass,
		&hkpVehicleEngineClass,
		&hkpVehicleFrictionDescriptionAxisDescriptionClass,
		&hkpVehicleFrictionDescriptionClass,
		&hkpVehicleFrictionStatusAxisStatusClass,
		&hkpVehicleFrictionStatusClass,
		&hkpVehicleInstanceClass,
		&hkpVehicleInstanceWheelInfoClass,
		&hkpVehicleRaycastWheelCollideClass,
		&hkpVehicleSteeringClass,
		&hkpVehicleSuspensionClass,
		&hkpVehicleSuspensionSuspensionWheelParametersClass,
		&hkpVehicleTransmissionClass,
		&hkpVehicleVelocityDamperClass,
		&hkpVehicleWheelCollideClass,
		&hkpVelocityConstraintMotorClass,
		&hkpViscousSurfaceModifierConstraintAtomClass,
		&hkpWeldingUtilityClass,
		&hkpWheelConstraintDataAtomsClass,
		&hkpWheelConstraintDataClass,
		&hkpWorldCinfoClass,
		&hkpWorldClass,
		&hkpWorldObjectClass,
		&hkxAnimatedFloatClass,
		&hkxAnimatedMatrixClass,
		&hkxAnimatedQuaternionClass,
		&hkxAnimatedVectorClass,
		&hkxAttributeClass,
		&hkxAttributeGroupClass,
		&hkxAttributeHolderClass,
		&hkxCameraClass,
		&hkxEdgeSelectionChannelClass,
		&hkxEnvironmentClass,
		&hkxEnvironmentVariableClass,
		&hkxIndexBufferClass,
		&hkxLightClass,
		&hkxMaterialClass,
		&hkxMaterialEffectClass,
		&hkxMaterialTextureStageClass,
		&hkxMeshClass,
		&hkxMeshSectionClass,
		&hkxMeshUserChannelInfoClass,
		&hkxNodeAnnotationDataClass,
		&hkxNodeClass,
		&hkxNodeSelectionSetClass,
		&hkxSceneClass,
		&hkxSkinBindingClass,
		&hkxSparselyAnimatedBoolClass,
		&hkxSparselyAnimatedEnumClass,
		&hkxSparselyAnimatedIntClass,
		&hkxSparselyAnimatedStringClass,
		&hkxSparselyAnimatedStringStringTypeClass,
		&hkxTextureFileClass,
		&hkxTextureInplaceClass,
		&hkxTriangleSelectionChannelClass,
		&hkxVertexBufferClass,
		&hkxVertexFloatDataChannelClass,
		&hkxVertexFormatClass,
		&hkxVertexIntDataChannelClass,
		&hkxVertexP4N4C1T2Class,
		&hkxVertexP4N4T4B4C1T2Class,
		&hkxVertexP4N4T4B4W4I4C1Q2Class,
		&hkxVertexP4N4T4B4W4I4Q4Class,
		&hkxVertexP4N4W4I4C1Q2Class,
		&hkxVertexSelectionChannelClass,
		&hkxVertexVectorDataChannelClass,
		HK_NULL
	}; 

} // namespace hkHavok500r1Classes


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
