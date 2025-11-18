/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKSCENEDATA_MESH_HKXVERTEXFORMAT_XML_H
#define HKSCENEDATA_MESH_HKXVERTEXFORMAT_XML_H

#define HK_VFMT_NOT_PRESENT 255

/// hkxVertexFormat meta information
extern const class hkClass hkxVertexFormatClass;

/// This structure describes the memory layout and format of a vertex buffer.
class hkxVertexFormat
{
	public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxVertexFormat );
	HK_DECLARE_REFLECTION();

			/// Default constructor
	hkxVertexFormat();
		
		//
		// Members
		//
	public:
		
			/// The byte offsets between two consecutive vertices (at least 12, usually more)
		hkUint8 m_stride;
		
			/// The byte offset for the first float representing position. Set to
			/// HK_VFMT_NOT_PRESENT if this vertex format has no position component
		hkUint8 m_positionOffset;
		
			/// The byte offset for the first float representing the vertex normal. Set to
			/// HK_VFMT_NOT_PRESENT if this vertex format has no vertex normals.
		hkUint8 m_normalOffset;
		
			/// The byte offset for the first float representing the vertex tangent. Set to
			/// HK_VFMT_NOT_PRESENT if this vertex format has no vertex tangent.
		hkUint8 m_tangentOffset;
		
			/// The byte offset for the first float representing the vertex binormal. Set to
			/// HK_VFMT_NOT_PRESENT if this vertex format has no vertex binormal.
		hkUint8 m_binormalOffset;
		
			/// The number of bones each vertex is bound to. Values > 1 imply this mesh is
			/// suitable for skinning
		hkUint8 m_numBonesPerVertex;
		
			/// The byte offset for the first vertex bone index. We assume these indices are 8
			/// bit indices. The number of indices is given by numBonesPerVertex. Set to
			/// HK_VFMT_NOT_PRESENT if the bone indices are not used.
		hkUint8 m_boneIndexOffset;
		
			/// The byte offset for the first vertex weight. The number of weights is given by
			/// numBonesPerVertex. We assume these weights are signed 8 bit values which are
			/// normalized later. Set to HK_VFMT_NOT_PRESENT if skinning is not used.
		hkUint8 m_boneWeightOffset;
		
			/// The number of texture coordinate sets (assumed each 2D). 1 is default, but 2 to
			/// 4 is common. Assumed to follow each other contiguously.
		hkUint8 m_numTextureChannels;
		
			/// The byte offset for the floating point texture coords. Set to
			/// HK_VFMT_NOT_PRESENT if this vertex format has no floating point texture
			/// coordinates.
		hkUint8 m_tFloatCoordOffset;
		
			/// The byte offset for quantized 16 bit texture coords. Set to HK_VFMT_NOT_PRESENT
			/// if this vertex format has no 16 bit texture coordinates.
		hkUint8 m_tQuantizedCoordOffset;
		
			/// The byte offset for a 32 bit colour value. Set to HK_VFMT_NOT_PRESENT if this
			/// vertex format has no colour information.
		hkUint8 m_colorOffset;
};

#include <Common/SceneData/Mesh/hkxVertexFormat.inl>

#endif // HKSCENEDATA_MESH_HKXVERTEXFORMAT_XML_H

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
