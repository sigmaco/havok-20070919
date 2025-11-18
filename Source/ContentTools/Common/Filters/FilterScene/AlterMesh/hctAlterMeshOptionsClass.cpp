/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/Filters/FilterScene/AlterMesh/hctAlterMeshOptions.h'
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/Filters/FilterScene/AlterMesh/hctAlterMeshOptions.h>



//
// Class hctAlterMeshOptions
//
HK_REFLECTION_DEFINE_SIMPLE(hctAlterMeshOptions);
static const hkInternalClassMember hctAlterMeshOptionsClass_Members[] =
{
	{ "removeIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAlterMeshOptions,m_removeIndices), HK_NULL }
};
namespace
{
	struct hctAlterMeshOptions_DefaultStruct
	{
		int s_defaultOffsets[1];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		_hkBool m_removeIndices;
	};
	const hctAlterMeshOptions_DefaultStruct hctAlterMeshOptions_Default =
	{
		{HK_OFFSET_OF(hctAlterMeshOptions_DefaultStruct,m_removeIndices)},
		true
	};
}
extern const hkClass hctAlterMeshOptionsClass;
const hkClass hctAlterMeshOptionsClass(
	"hctAlterMeshOptions",
	HK_NULL, // parent
	sizeof(hctAlterMeshOptions),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctAlterMeshOptionsClass_Members),
	HK_COUNT_OF(hctAlterMeshOptionsClass_Members),
	&hctAlterMeshOptions_Default,
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
