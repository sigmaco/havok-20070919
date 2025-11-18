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

namespace hkHavok300Classes
{
	const char VersionString[] = "Havok-3.0.0";

	extern hkClass hkAabbClass;
	extern hkClass hkAabbPhantomClass;
	extern hkClass hkActionClass;
	extern hkClass hkAngularDashpotActionClass;
	extern hkClass hkAnimationBindingClass;
	extern hkClass hkAnimationContainerClass;
	extern hkClass hkAnimationTrackAnnotationClass;
	extern hkClass hkAnimationTrackClass;
	extern hkClass hkArrayActionClass;
	extern hkClass hkBallAndSocketConstraintDataClass;
	extern hkClass hkBaseObjectClass;
	extern hkClass hkBinaryActionClass;
	extern hkClass hkBlendingMotorClass;
	extern hkClass hkBoneAttachmentClass;
	extern hkClass hkBoneClass;
	extern hkClass hkBoxMotionClass;
	extern hkClass hkBoxShapeClass;
	extern hkClass hkBreakableConstraintDataClass;
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
	extern hkClass hkConstrainedSystemFilterClass;
	extern hkClass hkConstraintDataClass;
	extern hkClass hkConstraintInfoClass;
	extern hkClass hkConstraintInstanceClass;
	extern hkClass hkContactPointClass;
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
	extern hkClass hkDefaultExtractedMotionClass;
	extern hkClass hkDeltaCompressedAnimationClass;
	extern hkClass hkDeltaCompressedAnimationQuantizationFormatClass;
	extern hkClass hkDisableEntityCollisionFilterClass;
	extern hkClass hkEntityClass;
	extern hkClass hkEntityDeactivatorClass;
	extern hkClass hkExtractedMotionClass;
	extern hkClass hkFakeRigidBodyDeactivatorClass;
	extern hkClass hkFastMeshShapeClass;
	extern hkClass hkFixedRigidMotionClass;
	extern hkClass hkGenericConstraintDataClass;
	extern hkClass hkGenericConstraintDataSchemeClass;
	extern hkClass hkGroupCollisionFilterClass;
	extern hkClass hkGroupFilterClass;
	extern hkClass hkHeightFieldShapeClass;
	extern hkClass hkHingeConstraintDataClass;
	extern hkClass hkHingeConstraintDataConstraintBasisAClass;
	extern hkClass hkHingeConstraintDataConstraintBasisBClass;
	extern hkClass hkInterleavedAnimationClass;
	extern hkClass hkKeyframedRigidMotionClass;
	extern hkClass hkLimitedHingeConstraintDataClass;
	extern hkClass hkLimitedHingeConstraintDataConstraintBasisAClass;
	extern hkClass hkLimitedHingeConstraintDataConstraintBasisBClass;
	extern hkClass hkLinearParametricCurveClass;
	extern hkClass hkLinkedCollidableClass;
	extern hkClass hkListShapeChildInfoClass;
	extern hkClass hkListShapeClass;
	extern hkClass hkMalleableConstraintDataClass;
	extern hkClass hkMaterialClass;
	extern hkClass hkMeshBindingClass;
	extern hkClass hkMeshMaterialClass;
	extern hkClass hkMeshShapeClass;
	extern hkClass hkMeshShapeSubpartClass;
	extern hkClass hkMoppBvTreeShapeClass;
	extern hkClass hkMoppCodeClass;
	extern hkClass hkMoppCodeCodeInfoClass;
	extern hkClass hkMotionClass;
	extern hkClass hkMotionStateClass;
	extern hkClass hkMotorActionClass;
	extern hkClass hkMotorControllerClass;
	extern hkClass hkMouseSpringActionClass;
	extern hkClass hkMultiRayShapeClass;
	extern hkClass hkMultiRayShapeRayClass;
	extern hkClass hkMultiSphereShapeClass;
	extern hkClass hkNullCollisionFilterClass;
	extern hkClass hkPackfileHeaderClass;
	extern hkClass hkPackfileSectionHeaderClass;
	extern hkClass hkPairwiseCollisionFilterClass;
	extern hkClass hkPairwiseCollisionFilterCollisionPairClass;
	extern hkClass hkParametricCurveClass;
	extern hkClass hkPhantomCallbackShapeClass;
	extern hkClass hkPhantomClass;
	extern hkClass hkPhysicsDataClass;
	extern hkClass hkPhysicsSystemClass;
	extern hkClass hkPlaneShapeClass;
	extern hkClass hkPointToPathConstraintDataClass;
	extern hkClass hkPointToPlaneConstraintDataClass;
	extern hkClass hkPoweredHingeConstraintDataClass;
	extern hkClass hkPoweredRagdollConstraintDataClass;
	extern hkClass hkPrismaticConstraintDataClass;
	extern hkClass hkPrismaticConstraintDataConstraintBasisAClass;
	extern hkClass hkPrismaticConstraintDataConstraintBasisBClass;
	extern hkClass hkPropertyClass;
	extern hkClass hkPropertyValueClass;
	extern hkClass hkRagdollConstraintDataClass;
	extern hkClass hkRagdollConstraintDataConstraintBasisAClass;
	extern hkClass hkRagdollConstraintDataConstraintBasisBClass;
	extern hkClass hkRagdollInstanceClass;
	extern hkClass hkRayCollidableFilterClass;
	extern hkClass hkRayShapeCollectionFilterClass;
	extern hkClass hkReferencedObjectClass;
	extern hkClass hkRejectRayChassisListenerClass;
	extern hkClass hkReorientActionClass;
	extern hkClass hkRigidAccumulatorClass;
	extern hkClass hkRigidBodyClass;
	extern hkClass hkRigidBodyDeactivatorClass;
	extern hkClass hkRigidMotionClass;
	extern hkClass hkRootLevelContainerClass;
	extern hkClass hkRootLevelContainerNamedVariantClass;
	extern hkClass hkSampledHeightFieldBaseClass;
	extern hkClass hkSerializedDisplayMarkerClass;
	extern hkClass hkSerializedDisplayMarkerListClass;
	extern hkClass hkSerializedDisplayRbTransformsClass;
	extern hkClass hkSerializedDisplayRbTransformsDisplayTransformPairClass;
	extern hkClass hkShapeClass;
	extern hkClass hkShapeCollectionClass;
	extern hkClass hkShapeCollectionFilterClass;
	extern hkClass hkShapePhantomClass;
	extern hkClass hkShapeRayCastInputClass;
	extern hkClass hkSimpleMeshShapeClass;
	extern hkClass hkSimpleMeshShapeTriangleClass;
	extern hkClass hkSimpleShapePhantomClass;
	extern hkClass hkSkeletalAnimationClass;
	extern hkClass hkSkeletonClass;
	extern hkClass hkSolverResultsClass;
	extern hkClass hkSpatialRigidBodyDeactivatorClass;
	extern hkClass hkSpatialRigidBodyDeactivatorSampleClass;
	extern hkClass hkSphereClass;
	extern hkClass hkSphereMotionClass;
	extern hkClass hkSphereRepShapeClass;
	extern hkClass hkSphereShapeClass;
	extern hkClass hkSpringActionClass;
	extern hkClass hkSpringDamperMotorClass;
	extern hkClass hkStabilizedBoxMotionClass;
	extern hkClass hkStabilizedSphereMotionClass;
	extern hkClass hkStiffSpringConstraintDataClass;
	extern hkClass hkStorageMeshShapeClass;
	extern hkClass hkStorageMeshShapeSubpartStorageClass;
	extern hkClass hkStrongestMotorClass;
	extern hkClass hkSweptTransformClass;
	extern hkClass hkTransformShapeClass;
	extern hkClass hkTriPatchTriangleClass;
	extern hkClass hkTriSampledHeightFieldBvTreeShapeClass;
	extern hkClass hkTriSampledHeightFieldCollectionClass;
	extern hkClass hkTriangleShapeClass;
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
	extern hkClass hkVelocityAccumulatorClass;
	extern hkClass hkVelocityMotorClass;
	extern hkClass hkWaveletCompressedAnimationClass;
	extern hkClass hkWaveletCompressedAnimationQuantizationFormatClass;
	extern hkClass hkWheelConstraintDataClass;
	extern hkClass hkWheelConstraintDataConstraintBasisAClass;
	extern hkClass hkWheelConstraintDataConstraintBasisBClass;
	extern hkClass hkWorldCinfoClass;
	extern hkClass hkWorldMemoryWatchDogClass;
	extern hkClass hkWorldObjectClass;
	extern hkClass hkxCameraClass;
	extern hkClass hkxIndexBufferClass;
	extern hkClass hkxLightClass;
	extern hkClass hkxMaterialClass;
	extern hkClass hkxMaterialTextureStageClass;
	extern hkClass hkxMeshClass;
	extern hkClass hkxMeshSectionClass;
	extern hkClass hkxNodeAnnotationDataClass;
	extern hkClass hkxNodeClass;
	extern hkClass hkxSceneClass;
	extern hkClass hkxSkinBindingClass;
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
	static hkInternalClassMember hkAnimationBindingClass_Members[] =
	{
		{ "animation", &hkSkeletalAnimationClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mapping", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnimationBindingClass(
		"hkAnimationBinding",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnimationBindingClass_Members),
		int(sizeof(hkAnimationBindingClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAnimationTrack_AnnotationClass_Members[] =
	{
		{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "text", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnimationTrackAnnotationClass(
		"hkAnimationTrackAnnotation",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnimationTrack_AnnotationClass_Members),
		int(sizeof(hkAnimationTrack_AnnotationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkAnimationTrackClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "annotations", &hkAnimationTrackAnnotationClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkAnimationTrackClass(
		"hkAnimationTrack",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkAnimationTrackClass_Members),
		int(sizeof(hkAnimationTrackClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSkeletalAnimationClass_Members[] =
	{
		{ "period", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numberOfBoneTracks", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extractedMotion", &hkExtractedMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "animationTracks", &hkAnimationTrackClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
	hkClass hkSkeletalAnimationClass(
		"hkSkeletalAnimation",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSkeletalAnimationClass_Members),
		int(sizeof(hkSkeletalAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDeltaCompressedAnimation_QuantizationFormatClass_Members[] =
	{
		{ "bitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "scale", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkDeltaCompressedAnimationQuantizationFormatClass(
		"hkDeltaCompressedAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDeltaCompressedAnimation_QuantizationFormatClass_Members),
		int(sizeof(hkDeltaCompressedAnimation_QuantizationFormatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkDeltaCompressedAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkDeltaCompressedAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedData", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "staticMask", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "staticDOFs", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkDeltaCompressedAnimationClass(
		"hkDeltaCompressedAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDeltaCompressedAnimationClass_Members),
		int(sizeof(hkDeltaCompressedAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkInterleavedAnimationClass_Members[] =
	{
		{ "poses", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_QSTRANSFORM, 0, 0, 0, HK_NULL }
	};
	hkClass hkInterleavedAnimationClass(
		"hkInterleavedAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkInterleavedAnimationClass_Members),
		int(sizeof(hkInterleavedAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWaveletCompressedAnimation_QuantizationFormatClass_Members[] =
	{
		{ "bitWidth", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "preserved", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "scale", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL }
	};
	hkClass hkWaveletCompressedAnimationQuantizationFormatClass(
		"hkWaveletCompressedAnimationQuantizationFormat",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWaveletCompressedAnimation_QuantizationFormatClass_Members),
		int(sizeof(hkWaveletCompressedAnimation_QuantizationFormatClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWaveletCompressedAnimationClass_Members[] =
	{
		{ "numberOfPoses", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "blockSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "qFormat", &hkWaveletCompressedAnimationQuantizationFormatClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "quantizedData", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "staticMask", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, 0, HK_NULL },
		{ "staticDOFs", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, 0, HK_NULL },
		{ "blockIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkWaveletCompressedAnimationClass(
		"hkWaveletCompressedAnimation",
		&hkSkeletalAnimationClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWaveletCompressedAnimationClass_Members),
		int(sizeof(hkWaveletCompressedAnimationClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMeshBindingClass_Members[] =
	{
		{ "mesh", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "skeleton", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "mapping", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
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
	hkClass hkExtractedMotionClass(
		"hkExtractedMotion",
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
	static hkInternalClassMember hkDefaultExtractedMotionClass_Members[] =
	{
		{ "period", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "forward", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "timeSlice", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motionTrack", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, 0, HK_NULL }
	};
	hkClass hkDefaultExtractedMotionClass(
		"hkDefaultExtractedMotion",
		&hkExtractedMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkDefaultExtractedMotionClass_Members),
		int(sizeof(hkDefaultExtractedMotionClass_Members)/sizeof(hkInternalClassMember)),
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
	static hkInternalClassMember hkClassClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parent", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "declaredEnums", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "declaredMembers", &hkClassMemberClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "hasVtable", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkClassClass(
		"hkClass",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
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
		{29, "TYPE_MAX"},
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
		{"Type", hkClassMemberTypeEnumItems, 30, HK_NULL, 0 },
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
	static hkInternalClassMember hkMotionStateClass_Members[] =
	{
		{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "sweptTransform", &hkSweptTransformClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deltaAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "objectRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationClass", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkxCameraClass_Members[] =
	{
		{ "from", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "focus", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fov", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "far", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "near", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "keys", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, 0, HK_NULL },
		{ "children", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "annotations", &hkxNodeAnnotationDataClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "userProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "selected", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "stages", &hkxMaterialTextureStageClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "diffuseColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ambientColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "specularColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "emissiveColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "subMaterials", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkBoneClass_Members[] =
	{
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "initialTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_QSTRANSFORM, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
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
		{ "skeleton", &hkSkeletonClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "boneIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "parentWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "attachment", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "hierarchy", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT16, 0, 0, 0, HK_NULL },
		{ "bones", &hkBoneClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
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
		{ "skinBindings", &hkxSkinBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
	};
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
		HK_NULL
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
		{ "contentsSectionOffest", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsClassSectionIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contentsClassSectionOffest", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 6, 0, 0, HK_NULL }
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
		{ "externalFixupsOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "endOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "spare", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "childShape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		{ "shapeCollection", &hkShapeCollectionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
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
		HK_NULL,
		0,
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
		0,
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
		{ "minDistanceToUseConvexHullForGetClosestPoints", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkConvexListShapeClass(
		"hkConvexListShape",
		&hkListShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkConvexListShapeClass_Members),
		int(sizeof(hkConvexListShapeClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
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
		{ "childShape", &hkConvexShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		{ "childShape", &hkConvexShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
	static hkInternalClassMember hkCylinderShapeClass_Members[] =
	{
		{ "cylRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpendicular1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpendicular2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkCylinderShapeClass(
		"hkCylinderShape",
		&hkConvexShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkCylinderShapeClass_Members),
		int(sizeof(hkCylinderShapeClass_Members)/sizeof(hkInternalClassMember)),
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
	static const hkInternalClassEnum hkMeshShapeEnums[] = {
		{"IndexStridingType", hkMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMeshShapeEnums[0]);
	static hkInternalClassMember hkMeshShape_SubpartClass_Members[] =
	{
		{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "stridingType", HK_NULL, hkMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
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
		{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMeshShapeClass(
		"hkMeshShape",
		&hkShapeCollectionClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkMeshShapeEnums),
		1,
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
	static const hkInternalClassEnumItem hkMultiSphereShapetestEnumItems[] =
	{
		{8, "MAX_SPHERES"},
	};
	static const hkInternalClassEnum hkMultiSphereShapeEnums[] = {
		{"test", hkMultiSphereShapetestEnumItems, 1, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMultiSphereShapetestEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiSphereShapeEnums[0]);
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
		reinterpret_cast<const hkClassEnum*>(hkMultiSphereShapeEnums),
		1,
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
	static hkInternalClassMember hkSampledHeightFieldBaseClass_Members[] =
	{
		{ "xRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "zRes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "triangleFlip", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "heightCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "intToFloatScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntScale", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "floatToIntOffsetFloorCorrected", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSampledHeightFieldBaseClass(
		"hkSampledHeightFieldBase",
		&hkHeightFieldShapeClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSampledHeightFieldBaseClass_Members),
		int(sizeof(hkSampledHeightFieldBaseClass_Members)/sizeof(hkInternalClassMember)),
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
		{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, 0, HK_NULL }
	};
	hkClass hkStorageMeshShapeSubpartStorageClass(
		"hkStorageMeshShapeSubpartStorage",
		HK_NULL,
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
	static hkInternalClassMember hkTransformShapeClass_Members[] =
	{
		{ "childShape", &hkShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
	static hkInternalClassMember hkTriPatchTriangleClass_Members[] =
	{
		{ "neighbours", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, 0, HK_NULL },
		{ "shapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "referenceCountAndConnectivity", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkTriPatchTriangleClass(
		"hkTriPatchTriangle",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkTriPatchTriangleClass_Members),
		int(sizeof(hkTriPatchTriangleClass_Members)/sizeof(hkInternalClassMember)),
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
		{ "heightfield", &hkSampledHeightFieldBaseClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
	static hkInternalClassMember hkRigidAccumulatorClass_Members[] =
	{
		{ "deactivationCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivationClass", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "matrixIsIdentity", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearVel", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularVel", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "invMasses", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scratch0", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scratch1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scratch2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "scratch3", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRigidAccumulatorClass(
		"hkRigidAccumulator",
		&hkVelocityAccumulatorClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRigidAccumulatorClass_Members),
		int(sizeof(hkRigidAccumulatorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkVelocityAccumulatorhkAccumulatorTypeEnumItems[] =
	{
		{0, "HK_RIGID_BODY"},
		{1, "HK_KEYFRAMED_RIGID_BODY"},
		{2, "HK_END"},
	};
	static const hkInternalClassEnum hkVelocityAccumulatorEnums[] = {
		{"hkAccumulatorType", hkVelocityAccumulatorhkAccumulatorTypeEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkVelocityAccumulatorhkAccumulatorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkVelocityAccumulatorEnums[0]);
	static hkInternalClassMember hkVelocityAccumulatorClass_Members[] =
	{
		{ "type", HK_NULL, hkVelocityAccumulatorhkAccumulatorTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL }
	};
	hkClass hkVelocityAccumulatorClass(
		"hkVelocityAccumulator",
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkVelocityAccumulatorEnums),
		1,
		reinterpret_cast<const hkClassMember*>(hkVelocityAccumulatorClass_Members),
		int(sizeof(hkVelocityAccumulatorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSolverResultsClass_Members[] =
	{
		{ "impulseApplied", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "internalSolverData", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSolverResultsClass(
		"hkSolverResults",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSolverResultsClass_Members),
		int(sizeof(hkSolverResultsClass_Members)/sizeof(hkInternalClassMember)),
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
		{ "forwardRhs", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static const hkInternalClassEnumItem hkdynamics_constraint_hkConstraintDatahkConstraintTypeEnumItems[] =
	{
		{0, "HK_CONSTRAINT_TYPE_BALLANDSOCKET"},
		{1, "HK_CONSTRAINT_TYPE_HINGE"},
		{2, "HK_CONSTRAINT_TYPE_LIMITEDHINGE"},
		{3, "HK_CONSTRAINT_TYPE_POINTTOPATH"},
		{4, "HK_CONSTRAINT_TYPE_POWEREDHINGE"},
		{5, "HK_CONSTRAINT_TYPE_POWEREDRAGDOLL"},
		{6, "HK_CONSTRAINT_TYPE_PRISMATIC"},
		{7, "HK_CONSTRAINT_TYPE_RAGDOLL"},
		{8, "HK_CONSTRAINT_TYPE_STIFFSPRING"},
		{9, "HK_CONSTRAINT_TYPE_WHEEL"},
		{10, "HK_CONSTRAINT_TYPE_GENERIC"},
		{11, "HK_CONSTRAINT_TYPE_CONTACT"},
		{12, "HK_CONSTRAINT_TYPE_BREAKABLE"},
		{13, "HK_CONSTRAINT_TYPE_MALLEABLE"},
		{14, "HK_CONSTRAINT_TYPE_POINTTOPLANE"},
	};
	static const hkInternalClassEnum hkdynamics_constraint_hkConstraintDataEnums[] = {
		{"hkConstraintType", hkdynamics_constraint_hkConstraintDatahkConstraintTypeEnumItems, 15, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkdynamics_constraint_hkConstraintDataEnums[0]);
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
		HK_NULL,
		0,
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
	};
	static const hkInternalClassEnum hkConstraintInstanceEnums[] = {
		{"ConstraintPriority", hkConstraintInstanceConstraintPriorityEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkConstraintInstanceConstraintPriorityEnum = reinterpret_cast<const hkClassEnum*>(&hkConstraintInstanceEnums[0]);
	static hkInternalClassMember hkConstraintInstanceClass_Members[] =
	{
		{ "owner", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "data", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		1,
		reinterpret_cast<const hkClassMember*>(hkConstraintInstanceClass_Members),
		int(sizeof(hkConstraintInstanceClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkBallAndSocketConstraintDataClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkHingeConstraintData_ConstraintBasisAClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToAxle1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToAxle2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeConstraintDataConstraintBasisAClass(
		"hkHingeConstraintDataConstraintBasisA",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkHingeConstraintData_ConstraintBasisAClass_Members),
		int(sizeof(hkHingeConstraintData_ConstraintBasisAClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkHingeConstraintData_ConstraintBasisBClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkHingeConstraintDataConstraintBasisBClass(
		"hkHingeConstraintDataConstraintBasisB",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkHingeConstraintData_ConstraintBasisBClass_Members),
		int(sizeof(hkHingeConstraintData_ConstraintBasisBClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkHingeConstraintDataClass_Members[] =
	{
		{ "basisA", &hkHingeConstraintDataConstraintBasisAClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisB", &hkHingeConstraintDataConstraintBasisBClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkLimitedHingeConstraintData_ConstraintBasisAClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToAxle1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToAxle2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLimitedHingeConstraintDataConstraintBasisAClass(
		"hkLimitedHingeConstraintDataConstraintBasisA",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLimitedHingeConstraintData_ConstraintBasisAClass_Members),
		int(sizeof(hkLimitedHingeConstraintData_ConstraintBasisAClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLimitedHingeConstraintData_ConstraintBasisBClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perp2FreeAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkLimitedHingeConstraintDataConstraintBasisBClass(
		"hkLimitedHingeConstraintDataConstraintBasisB",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkLimitedHingeConstraintData_ConstraintBasisBClass_Members),
		int(sizeof(hkLimitedHingeConstraintData_ConstraintBasisBClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkLimitedHingeConstraintDataClass_Members[] =
	{
		{ "minAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisA", &hkLimitedHingeConstraintDataConstraintBasisAClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisB", &hkLimitedHingeConstraintDataConstraintBasisBClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkBlendingMotorClass_Members[] =
	{
		{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "invSpringConstant", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBlendingMotorClass(
		"hkBlendingMotor",
		&hkMotorControllerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBlendingMotorClass_Members),
		int(sizeof(hkBlendingMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkMotorControllerClass_Members[] =
	{
		{ "masterWeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkMotorControllerClass(
		"hkMotorController",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkMotorControllerClass_Members),
		int(sizeof(hkMotorControllerClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkSpringDamperMotorClass_Members[] =
	{
		{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "invSpringConstant", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkSpringDamperMotorClass(
		"hkSpringDamperMotor",
		&hkMotorControllerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkSpringDamperMotorClass_Members),
		int(sizeof(hkSpringDamperMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStrongestMotorClass_Members[] =
	{
		{ "targetPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkStrongestMotorClass(
		"hkStrongestMotor",
		&hkMotorControllerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkStrongestMotorClass_Members),
		int(sizeof(hkStrongestMotorClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkVelocityMotorClass_Members[] =
	{
		{ "velocityTarget", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkVelocityMotorClass(
		"hkVelocityMotor",
		&hkMotorControllerClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkVelocityMotorClass_Members),
		int(sizeof(hkVelocityMotorClass_Members)/sizeof(hkInternalClassMember)),
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
	static hkInternalClassMember hkPointToPlaneConstraintDataClass_Members[] =
	{
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeNormalA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkPoweredHingeConstraintDataClass_Members[] =
	{
		{ "motorActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "ignoreLimits", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "motor", &hkMotorControllerClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredHingeConstraintDataClass(
		"hkPoweredHingeConstraintData",
		&hkLimitedHingeConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredHingeConstraintDataClass_Members),
		int(sizeof(hkPoweredHingeConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPoweredRagdollConstraintDataClass_Members[] =
	{
		{ "motorsActive", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "targetFrameAinB", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistMotor", &hkMotorControllerClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "coneMotor", &hkMotorControllerClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "planeMotor", &hkMotorControllerClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkPoweredRagdollConstraintDataClass(
		"hkPoweredRagdollConstraintData",
		&hkRagdollConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPoweredRagdollConstraintDataClass_Members),
		int(sizeof(hkPoweredRagdollConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPrismaticConstraintData_ConstraintBasisAClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shaft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "BtoAoffsetRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_ROTATION, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPrismaticConstraintDataConstraintBasisAClass(
		"hkPrismaticConstraintDataConstraintBasisA",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPrismaticConstraintData_ConstraintBasisAClass_Members),
		int(sizeof(hkPrismaticConstraintData_ConstraintBasisAClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPrismaticConstraintData_ConstraintBasisBClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shaft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToShaft", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkPrismaticConstraintDataConstraintBasisBClass(
		"hkPrismaticConstraintDataConstraintBasisB",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkPrismaticConstraintData_ConstraintBasisBClass_Members),
		int(sizeof(hkPrismaticConstraintData_ConstraintBasisBClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkPrismaticConstraintDataClass_Members[] =
	{
		{ "basisA", &hkPrismaticConstraintDataConstraintBasisAClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisB", &hkPrismaticConstraintDataConstraintBasisBClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "minLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkRagdollConstraintData_ConstraintBasisAClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollConstraintDataConstraintBasisAClass(
		"hkRagdollConstraintDataConstraintBasisA",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollConstraintData_ConstraintBasisAClass_Members),
		int(sizeof(hkRagdollConstraintData_ConstraintBasisAClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollConstraintData_ConstraintBasisBClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollConstraintDataConstraintBasisBClass(
		"hkRagdollConstraintDataConstraintBasisB",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollConstraintData_ConstraintBasisBClass_Members),
		int(sizeof(hkRagdollConstraintData_ConstraintBasisBClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRagdollConstraintDataClass_Members[] =
	{
		{ "basisA", &hkRagdollConstraintDataConstraintBasisAClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisB", &hkRagdollConstraintDataConstraintBasisBClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "coneMinAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeMinAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "planeMaxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistMinAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "twistMaxAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "maxFrictionTorque", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRagdollConstraintDataClass(
		"hkRagdollConstraintData",
		&hkConstraintDataClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRagdollConstraintDataClass_Members),
		int(sizeof(hkRagdollConstraintDataClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkStiffSpringConstraintDataClass_Members[] =
	{
		{ "springLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkWheelConstraintData_ConstraintBasisAClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "axle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWheelConstraintDataConstraintBasisAClass(
		"hkWheelConstraintDataConstraintBasisA",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWheelConstraintData_ConstraintBasisAClass_Members),
		int(sizeof(hkWheelConstraintData_ConstraintBasisAClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWheelConstraintData_ConstraintBasisBClass_Members[] =
	{
		{ "pivot", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "steeringAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToSteeringAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "perpToSuspensionAxis", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "referenceAxle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWheelConstraintDataConstraintBasisBClass(
		"hkWheelConstraintDataConstraintBasisB",
		HK_NULL,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkWheelConstraintData_ConstraintBasisBClass_Members),
		int(sizeof(hkWheelConstraintData_ConstraintBasisBClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkWheelConstraintDataClass_Members[] =
	{
		{ "basisA", &hkWheelConstraintDataConstraintBasisAClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "basisB", &hkWheelConstraintDataConstraintBasisBClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionMinLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionMaxLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionStrength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "suspensionDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
		{ "constraintData", &hkConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "solverResultLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isBroken", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "removeWhenBroken", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "breakNonRemovedInstances", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
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
	static hkInternalClassMember hkGenericConstraintDataClass_Members[] =
	{
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
		{ "motors", &hkMotorControllerClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
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
		{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkEntityClass_Members[] =
	{
		{ "motion", &hkMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "simulationIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "material", &hkMaterialClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "deactivator", &hkEntityDeactivatorClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "constraintsMaster", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "constraintsSlave", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "constraintRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, 0, HK_NULL },
		{ "storageIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "processContactCallbackDelay", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "autoRemoveLevel", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "fixed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "isFixedOrKeyframed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "internalCollideFlag", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "activationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "entityListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL },
		{ "actions", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_ARRAY, 0, 0, 0, HK_NULL }
	};
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
		HK_NULL
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
		{8, "MOTION_MAX_ID"},
	};
	static const hkInternalClassEnum hkMotionEnums[] = {
		{"MotionType", hkMotionMotionTypeEnumItems, 9, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkMotionMotionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMotionEnums[0]);
	static hkInternalClassMember hkMotionClass_Members[] =
	{
		{ "solverData", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
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
	static hkInternalClassMember hkBoxMotionClass_Members[] =
	{
		{ "inertiaAndMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkBoxMotionClass(
		"hkBoxMotion",
		&hkRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkBoxMotionClass_Members),
		int(sizeof(hkBoxMotionClass_Members)/sizeof(hkInternalClassMember)),
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
		{ "savedMotion", &hkRigidMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
	};
	hkClass hkKeyframedRigidMotionClass(
		"hkKeyframedRigidMotion",
		&hkRigidMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkKeyframedRigidMotionClass_Members),
		int(sizeof(hkKeyframedRigidMotionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static hkInternalClassMember hkRigidMotionClass_Members[] =
	{
		{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "massInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "particleMinInertiaDiagInv", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "linearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "angularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkRigidMotionClass(
		"hkRigidMotion",
		&hkMotionClass,
		0,
		HK_NULL,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassMember*>(hkRigidMotionClass_Members),
		int(sizeof(hkRigidMotionClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	hkClass hkSphereMotionClass(
		"hkSphereMotion",
		&hkRigidMotionClass,
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
	static hkInternalClassMember hkAabbPhantomClass_Members[] =
	{
		{ "aabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "overlappingCollidables", &hkCollidableClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL }
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
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
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
		HK_NULL
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
		{2, "SIMULATION_TYPE_ASYNCHRONOUS"},
		{3, "SIMULATION_TYPE_HALFSTEP"},
		{4, "SIMULATION_TYPE_CONTINUOUS"},
	};
	static const hkInternalClassEnumItem hkWorldCinfoContactPointGenerationEnumItems[] =
	{
		{0, "CONTACT_POINT_ACCEPT_ALWAYS"},
		{1, "CONTACT_POINT_REJECT_DUBIOUS"},
		{2, "CONTACT_POINT_REJECT_MANY"},
	};
	static const hkInternalClassEnum hkWorldCinfoEnums[] = {
		{"SolverType", hkWorldCinfoSolverTypeEnumItems, 11, HK_NULL, 0 },
		{"SimulationType", hkWorldCinfoSimulationTypeEnumItems, 5, HK_NULL, 0 },
		{"ContactPointGeneration", hkWorldCinfoContactPointGenerationEnumItems, 3, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkWorldCinfoSolverTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[0]);
	extern const hkClassEnum* hkWorldCinfoSimulationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[1]);
	extern const hkClassEnum* hkWorldCinfoContactPointGenerationEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldCinfoEnums[2]);
	static hkInternalClassMember hkWorldCinfoClass_Members[] =
	{
		{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "broadPhaseWorldAabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "collisionFilter", &hkCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "expectedMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "expectedMinPsiDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "memoryWatchDog", &hkWorldMemoryWatchDogClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "contactPointGeneration", HK_NULL, hkWorldCinfoContactPointGenerationEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "solverTau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverDamp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "solverIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "boxBoxUseAggresiveCompletion", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastEarlyOutDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "iterativeLinearCastMaxIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "enableDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "simulationType", HK_NULL, hkWorldCinfoSimulationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_VOID, 0, hkClassMember::DEPRECATED_ENUM_8, 0, HK_NULL },
		{ "enableSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
	hkClass hkWorldCinfoClass(
		"hkWorldCinfo",
		&hkReferencedObjectClass,
		0,
		HK_NULL,
		0,
		reinterpret_cast<const hkClassEnum*>(hkWorldCinfoEnums),
		3,
		reinterpret_cast<const hkClassMember*>(hkWorldCinfoClass_Members),
		int(sizeof(hkWorldCinfoClass_Members)/sizeof(hkInternalClassMember)),
		HK_NULL
		);
	static const hkInternalClassEnumItem hkWorldObjectBroadPhaseTypeEnumItems[] =
	{
		{0, "BROAD_PHASE_INVALID"},
		{1, "BROAD_PHASE_ENTITY"},
		{2, "BROAD_PHASE_PHANTOM"},
		{3, "BROAD_PHASE_MAX_ID"},
	};
	static const hkInternalClassEnum hkWorldObjectEnums[] = {
		{"BroadPhaseType", hkWorldObjectBroadPhaseTypeEnumItems, 4, HK_NULL, 0 }
	};
	extern const hkClassEnum* hkWorldObjectBroadPhaseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkWorldObjectEnums[0]);
	static hkInternalClassMember hkWorldObjectClass_Members[] =
	{
		{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_ZERO, hkClassMember::TYPE_POINTER, 0, 0, 0, HK_NULL },
		{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
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
		HK_NULL,
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
		{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraUpStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "extraDownStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "shapePhantom", &hkShapePhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
		{ "keepDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "characterRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "userPlanes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL },
		{ "conservativeWalking", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, 0, HK_NULL }
	};
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
		HK_NULL
		);
	hkClass hkConstrainedSystemFilterClass(
		"hkConstrainedSystemFilter",
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
	static hkInternalClassMember hkRagdollInstanceClass_Members[] =
	{
		{ "physicsSystem", &hkPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		{ "contactBody", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		{ "chassis", &hkRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
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
		&hkWorldObjectClass,
		&hkAabbClass,
		&hkAabbPhantomClass,
		&hkActionClass,
		&hkAngularDashpotActionClass,
		&hkAnimationBindingClass,
		&hkAnimationContainerClass,
		&hkAnimationTrackAnnotationClass,
		&hkAnimationTrackClass,
		&hkArrayActionClass,
		&hkBallAndSocketConstraintDataClass,
		&hkBaseObjectClass,
		&hkBinaryActionClass,
		&hkBlendingMotorClass,
		&hkBoneAttachmentClass,
		&hkBoneClass,
		&hkBoxMotionClass,
		&hkBoxShapeClass,
		&hkBreakableConstraintDataClass,
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
		&hkConstrainedSystemFilterClass,
		&hkConstraintDataClass,
		&hkConstraintInfoClass,
		&hkConstraintInstanceClass,
		&hkContactPointClass,
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
		&hkDefaultExtractedMotionClass,
		&hkDeltaCompressedAnimationClass,
		&hkDeltaCompressedAnimationQuantizationFormatClass,
		&hkDisableEntityCollisionFilterClass,
		&hkEntityClass,
		&hkEntityDeactivatorClass,
		&hkExtractedMotionClass,
		&hkFakeRigidBodyDeactivatorClass,
		&hkFastMeshShapeClass,
		&hkFixedRigidMotionClass,
		&hkGenericConstraintDataClass,
		&hkGenericConstraintDataSchemeClass,
		&hkGroupCollisionFilterClass,
		&hkGroupFilterClass,
		&hkHeightFieldShapeClass,
		&hkHingeConstraintDataClass,
		&hkHingeConstraintDataConstraintBasisAClass,
		&hkHingeConstraintDataConstraintBasisBClass,
		&hkInterleavedAnimationClass,
		&hkKeyframedRigidMotionClass,
		&hkLimitedHingeConstraintDataClass,
		&hkLimitedHingeConstraintDataConstraintBasisAClass,
		&hkLimitedHingeConstraintDataConstraintBasisBClass,
		&hkLinearParametricCurveClass,
		&hkLinkedCollidableClass,
		&hkListShapeChildInfoClass,
		&hkListShapeClass,
		&hkMalleableConstraintDataClass,
		&hkMaterialClass,
		&hkMeshBindingClass,
		&hkMeshMaterialClass,
		&hkMeshShapeClass,
		&hkMeshShapeSubpartClass,
		&hkMoppBvTreeShapeClass,
		&hkMoppCodeClass,
		&hkMoppCodeCodeInfoClass,
		&hkMotionClass,
		&hkMotionStateClass,
		&hkMotorActionClass,
		&hkMotorControllerClass,
		&hkMouseSpringActionClass,
		&hkMultiRayShapeClass,
		&hkMultiRayShapeRayClass,
		&hkMultiSphereShapeClass,
		&hkNullCollisionFilterClass,
		&hkPackfileHeaderClass,
		&hkPackfileSectionHeaderClass,
		&hkPairwiseCollisionFilterClass,
		&hkPairwiseCollisionFilterCollisionPairClass,
		&hkParametricCurveClass,
		&hkPhantomCallbackShapeClass,
		&hkPhantomClass,
		&hkPhysicsDataClass,
		&hkPhysicsSystemClass,
		&hkPlaneShapeClass,
		&hkPointToPathConstraintDataClass,
		&hkPointToPlaneConstraintDataClass,
		&hkPoweredHingeConstraintDataClass,
		&hkPoweredRagdollConstraintDataClass,
		&hkPrismaticConstraintDataClass,
		&hkPrismaticConstraintDataConstraintBasisAClass,
		&hkPrismaticConstraintDataConstraintBasisBClass,
		&hkPropertyClass,
		&hkPropertyValueClass,
		&hkRagdollConstraintDataClass,
		&hkRagdollConstraintDataConstraintBasisAClass,
		&hkRagdollConstraintDataConstraintBasisBClass,
		&hkRagdollInstanceClass,
		&hkRayCollidableFilterClass,
		&hkRayShapeCollectionFilterClass,
		&hkReferencedObjectClass,
		&hkRejectRayChassisListenerClass,
		&hkReorientActionClass,
		&hkRigidAccumulatorClass,
		&hkRigidBodyClass,
		&hkRigidBodyDeactivatorClass,
		&hkRigidMotionClass,
		&hkRootLevelContainerClass,
		&hkRootLevelContainerNamedVariantClass,
		&hkSampledHeightFieldBaseClass,
		&hkSerializedDisplayMarkerClass,
		&hkSerializedDisplayMarkerListClass,
		&hkSerializedDisplayRbTransformsClass,
		&hkSerializedDisplayRbTransformsDisplayTransformPairClass,
		&hkShapeClass,
		&hkShapeCollectionClass,
		&hkShapeCollectionFilterClass,
		&hkShapePhantomClass,
		&hkShapeRayCastInputClass,
		&hkSimpleMeshShapeClass,
		&hkSimpleMeshShapeTriangleClass,
		&hkSimpleShapePhantomClass,
		&hkSkeletalAnimationClass,
		&hkSkeletonClass,
		&hkSolverResultsClass,
		&hkSpatialRigidBodyDeactivatorClass,
		&hkSpatialRigidBodyDeactivatorSampleClass,
		&hkSphereClass,
		&hkSphereMotionClass,
		&hkSphereRepShapeClass,
		&hkSphereShapeClass,
		&hkSpringActionClass,
		&hkSpringDamperMotorClass,
		&hkStabilizedBoxMotionClass,
		&hkStabilizedSphereMotionClass,
		&hkStiffSpringConstraintDataClass,
		&hkStorageMeshShapeClass,
		&hkStorageMeshShapeSubpartStorageClass,
		&hkStrongestMotorClass,
		&hkSweptTransformClass,
		&hkTransformShapeClass,
		&hkTriPatchTriangleClass,
		&hkTriSampledHeightFieldBvTreeShapeClass,
		&hkTriSampledHeightFieldCollectionClass,
		&hkTriangleShapeClass,
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
		&hkVelocityAccumulatorClass,
		&hkVelocityMotorClass,
		&hkWaveletCompressedAnimationClass,
		&hkWaveletCompressedAnimationQuantizationFormatClass,
		&hkWheelConstraintDataClass,
		&hkWheelConstraintDataConstraintBasisAClass,
		&hkWheelConstraintDataConstraintBasisBClass,
		&hkWorldCinfoClass,
		&hkWorldMemoryWatchDogClass,
		
		&hkxCameraClass,
		&hkxIndexBufferClass,
		&hkxLightClass,
		&hkxMaterialClass,
		&hkxMaterialTextureStageClass,
		&hkxMeshClass,
		&hkxMeshSectionClass,
		&hkxNodeAnnotationDataClass,
		&hkxNodeClass,
		&hkxSceneClass,
		&hkxSkinBindingClass,
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

} // namespace hkHavok300Classes


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
