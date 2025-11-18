/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/StorageExtendedMesh/hkpStorageExtendedMeshShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/StorageExtendedMesh/hkpStorageExtendedMeshShape.h>



// External pointer and enum types
extern const hkClass hkpConvexShapeClass;
extern const hkClass hkpStorageExtendedMeshShapeMeshSubpartStorageClass;
extern const hkClass hkpStorageExtendedMeshShapeShapeSubpartStorageClass;

//
// Class hkpStorageExtendedMeshShape::MeshSubpartStorage
//
HK_REFLECTION_DEFINE_SCOPED_VIRTUAL(hkpStorageExtendedMeshShape,MeshSubpartStorage);
static const hkInternalClassMember hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members[] =
{
	{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_vertices), HK_NULL },
	{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_indices16), HK_NULL },
	{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_indices32), HK_NULL },
	{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_materialIndices), HK_NULL },
	{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_materials), HK_NULL },
	{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::MeshSubpartStorage,m_materialIndices16), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

const hkClass hkpStorageExtendedMeshShapeMeshSubpartStorageClass(
	"hkpStorageExtendedMeshShapeMeshSubpartStorage",
	&hkReferencedObjectClass, // parent
	sizeof(hkpStorageExtendedMeshShape::MeshSubpartStorage),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members),
	HK_COUNT_OF(hkpStorageExtendedMeshShape_MeshSubpartStorageClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStorageExtendedMeshShape::ShapeSubpartStorage
//
HK_REFLECTION_DEFINE_SCOPED_VIRTUAL(hkpStorageExtendedMeshShape,ShapeSubpartStorage);
static const hkInternalClassMember hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members[] =
{
	{ "shapes", &hkpConvexShapeClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::ShapeSubpartStorage,m_shapes), HK_NULL },
	{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::ShapeSubpartStorage,m_materialIndices), HK_NULL },
	{ "materials", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::ShapeSubpartStorage,m_materials), HK_NULL },
	{ "materialIndices16", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape::ShapeSubpartStorage,m_materialIndices16), HK_NULL }
};

const hkClass hkpStorageExtendedMeshShapeShapeSubpartStorageClass(
	"hkpStorageExtendedMeshShapeShapeSubpartStorage",
	&hkReferencedObjectClass, // parent
	sizeof(hkpStorageExtendedMeshShape::ShapeSubpartStorage),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members),
	HK_COUNT_OF(hkpStorageExtendedMeshShape_ShapeSubpartStorageClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStorageExtendedMeshShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpStorageExtendedMeshShape);
const hkInternalClassMember hkpStorageExtendedMeshShape::Members[] =
{
	{ "meshstorage", &hkpStorageExtendedMeshShapeMeshSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape,m_meshstorage), HK_NULL },
	{ "shapestorage", &hkpStorageExtendedMeshShapeShapeSubpartStorageClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpStorageExtendedMeshShape,m_shapestorage), HK_NULL }
};
extern const hkClass hkpExtendedMeshShapeClass;

extern const hkClass hkpStorageExtendedMeshShapeClass;
const hkClass hkpStorageExtendedMeshShapeClass(
	"hkpStorageExtendedMeshShape",
	&hkpExtendedMeshShapeClass, // parent
	sizeof(hkpStorageExtendedMeshShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStorageExtendedMeshShape::Members),
	HK_COUNT_OF(hkpStorageExtendedMeshShape::Members),
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
