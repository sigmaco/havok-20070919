/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4W4I4C1Q2_HKCLASS_H
#define HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4W4I4C1Q2_HKCLASS_H

/// hkxVertexP4N4W4I4C1Q2 meta information
extern const class hkClass hkxVertexP4N4W4I4C1Q2Class;

/// This structure describes the memory layout for heavy weight vertex buffer in
/// P4W4I4N4C1T2 format, with quantized texture coords (hence the Q instead of T).
class hkxVertexP4N4W4I4C1Q2
{
	public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxVertexP4N4W4I4C1Q2 );
	HK_DECLARE_REFLECTION();
	
		//
		// Members
		//
	public:
		
			/// 
		hkVector4 m_position;
		
			/// 
		hkVector4 m_normal;
		
			/// 4 * 8 bit weights
		hkUint32 m_weights;
		
			/// 4 * 8 bit bone indices
		hkUint32 m_indices;
		
			/// 32 bit color value (ARGB)
		hkUint32 m_diffuse;
		
			/// Texture U coordinate: divide by 3276.8f (so -10 -> +10 uv range) to get actual
			/// float value. This is for 16 byte alignment that we don't store full float.
			/// Could put in w of pos and norm.
		hkInt16 m_qu;
		
			/// Texture V coordinate: divide by 3276.8f (so -10 -> +10 uv range) to get actual
			/// float value. This is for 16 byte alignment that we don't store full float.
			/// Could put in w of pos and norm.
		hkInt16 m_qv;
};

#endif // HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4W4I4C1Q2_HKCLASS_H

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
