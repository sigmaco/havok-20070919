/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/Actions/MouseSpring/hkpMouseSpringAction.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/Actions/MouseSpring/hkpMouseSpringAction.h>



// External pointer and enum types
extern const hkClass hkpMouseSpringActionmouseSpringAppliedCallbackClass;

//
// Class hkpMouseSpringAction
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpMouseSpringAction);
static const hkInternalClassMember hkpMouseSpringActionClass_Members[] =
{
	{ "positionInRbLocal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_positionInRbLocal), HK_NULL },
	{ "mousePositionInWorld", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_mousePositionInWorld), HK_NULL },
	{ "springDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_springDamping), HK_NULL },
	{ "springElasticity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_springElasticity), HK_NULL },
	{ "maxRelativeForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_maxRelativeForce), HK_NULL },
	{ "objectDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_objectDamping), HK_NULL },
	{ "shapeKey", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMouseSpringAction,m_shapeKey), HK_NULL },
	{ "applyCallbacks", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMouseSpringAction,m_applyCallbacks), HK_NULL }
};
extern const hkClass hkpUnaryActionClass;

extern const hkClass hkpMouseSpringActionClass;
const hkClass hkpMouseSpringActionClass(
	"hkpMouseSpringAction",
	&hkpUnaryActionClass, // parent
	sizeof(hkpMouseSpringAction),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpMouseSpringActionClass_Members),
	HK_COUNT_OF(hkpMouseSpringActionClass_Members),
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
