/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxyCinfo.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxyCinfo.h>



// External pointer and enum types
extern const hkClass hkpShapePhantomClass;

//
// Class hkpCharacterProxyCinfo
//
HK_REFLECTION_DEFINE_SIMPLE(hkpCharacterProxyCinfo);
static const hkInternalClassMember hkpCharacterProxyCinfoClass_Members[] =
{
	{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_position), HK_NULL },
	{ "velocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_velocity), HK_NULL },
	{ "dynamicFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_dynamicFriction), HK_NULL },
	{ "staticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_staticFriction), HK_NULL },
	{ "keepContactTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_keepContactTolerance), HK_NULL },
	{ "up", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_up), HK_NULL },
	{ "extraUpStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_extraUpStaticFriction), HK_NULL },
	{ "extraDownStaticFriction", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_extraDownStaticFriction), HK_NULL },
	{ "shapePhantom", &hkpShapePhantomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_shapePhantom), HK_NULL },
	{ "keepDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_keepDistance), HK_NULL },
	{ "contactAngleSensitivity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_contactAngleSensitivity), HK_NULL },
	{ "userPlanes", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_userPlanes), HK_NULL },
	{ "maxCharacterSpeedForSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_maxCharacterSpeedForSolver), HK_NULL },
	{ "characterStrength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_characterStrength), HK_NULL },
	{ "characterMass", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_characterMass), HK_NULL },
	{ "maxSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_maxSlope), HK_NULL },
	{ "penetrationRecoverySpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_penetrationRecoverySpeed), HK_NULL },
	{ "maxCastIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_maxCastIterations), HK_NULL },
	{ "refreshManifoldInCheckSupport", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCharacterProxyCinfo,m_refreshManifoldInCheckSupport), HK_NULL }
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
extern const hkClass hkpCharacterProxyCinfoClass;
const hkClass hkpCharacterProxyCinfoClass(
	"hkpCharacterProxyCinfo",
	HK_NULL, // parent
	sizeof(hkpCharacterProxyCinfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpCharacterProxyCinfoClass_Members),
	HK_COUNT_OF(hkpCharacterProxyCinfoClass_Members),
	&hkpCharacterProxyCinfo_Default,
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
