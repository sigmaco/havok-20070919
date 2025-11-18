/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/StorageMesh/hkpStorageMeshShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/StorageMesh/hkpStorageMeshShape.h>



// External pointer and enum types
extern const hkClass hkpStorageMeshShapeSubpartStorageClass;

//
// Class hkpStorageMeshShape::SubpartStorage
//
HK_REFLECTION_DEFINE_SCOPED_VIRTUAL(hkpStorageMeshShape,SubpartStorage);
static const hkInternalClassMember hkpStorageMeshShape_SubpartStorageClass_Members[] =
{
	{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_REAL, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_vertices), HK_NULL },
	{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_indices16), HK_NULL },
	{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_indices32), HK_NULL },
	{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_materialIndices), HK_NULL },
	{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_materials), HK_NULL },
	{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape::SubpartStorage,m_materialIndices16), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

const hkClass hkpStorageMeshShapeSubpartStorageClass(
	"hkpStorageMeshShapeSubpartStorage",
	&hkReferencedObjectClass, // parent
	sizeof(hkpStorageMeshShape::SubpartStorage),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStorageMeshShape_SubpartStorageClass_Members),
	HK_COUNT_OF(hkpStorageMeshShape_SubpartStorageClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStorageMeshShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpStorageMeshShape);
const hkInternalClassMember hkpStorageMeshShape::Members[] =
{
	{ "storage", &hkpStorageMeshShapeSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpStorageMeshShape,m_storage), HK_NULL }
};
extern const hkClass hkpMeshShapeClass;

extern const hkClass hkpStorageMeshShapeClass;
const hkClass hkpStorageMeshShapeClass(
	"hkpStorageMeshShape",
	&hkpMeshShapeClass, // parent
	sizeof(hkpStorageMeshShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStorageMeshShape::Members),
	HK_COUNT_OF(hkpStorageMeshShape::Members),
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
