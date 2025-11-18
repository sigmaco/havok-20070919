/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Entity/hkpSpatialRigidBodyDeactivator.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Entity/hkpSpatialRigidBodyDeactivator.h>



// External pointer and enum types
extern const hkClass hkpSpatialRigidBodyDeactivatorSampleClass;

//
// Class hkpSpatialRigidBodyDeactivator::Sample
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpSpatialRigidBodyDeactivator,Sample);
static const hkInternalClassMember hkpSpatialRigidBodyDeactivator_SampleClass_Members[] =
{
	{ "refPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator::Sample,m_refPosition), HK_NULL },
	{ "refRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_QUATERNION, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator::Sample,m_refRotation), HK_NULL }
};
const hkClass hkpSpatialRigidBodyDeactivatorSampleClass(
	"hkpSpatialRigidBodyDeactivatorSample",
	HK_NULL, // parent
	sizeof(hkpSpatialRigidBodyDeactivator::Sample),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSpatialRigidBodyDeactivator_SampleClass_Members),
	HK_COUNT_OF(hkpSpatialRigidBodyDeactivator_SampleClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSpatialRigidBodyDeactivator
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSpatialRigidBodyDeactivator);
const hkInternalClassMember hkpSpatialRigidBodyDeactivator::Members[] =
{
	{ "highFrequencySample", &hkpSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_highFrequencySample), HK_NULL },
	{ "lowFrequencySample", &hkpSpatialRigidBodyDeactivatorSampleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_lowFrequencySample), HK_NULL },
	{ "radiusSqrd", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_radiusSqrd), HK_NULL },
	{ "minHighFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_minHighFrequencyTranslation), HK_NULL },
	{ "minHighFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_minHighFrequencyRotation), HK_NULL },
	{ "minLowFrequencyTranslation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_minLowFrequencyTranslation), HK_NULL },
	{ "minLowFrequencyRotation", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSpatialRigidBodyDeactivator,m_minLowFrequencyRotation), HK_NULL }
};
extern const hkClass hkpRigidBodyDeactivatorClass;

extern const hkClass hkpSpatialRigidBodyDeactivatorClass;
const hkClass hkpSpatialRigidBodyDeactivatorClass(
	"hkpSpatialRigidBodyDeactivator",
	&hkpRigidBodyDeactivatorClass, // parent
	sizeof(hkpSpatialRigidBodyDeactivator),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSpatialRigidBodyDeactivator::Members),
	HK_COUNT_OF(hkpSpatialRigidBodyDeactivator::Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

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
