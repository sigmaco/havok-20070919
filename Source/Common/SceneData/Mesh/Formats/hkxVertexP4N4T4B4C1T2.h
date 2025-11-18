/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4T4B4C1T2_HKCLASS_H
#define HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4T4B4C1T2_HKCLASS_H

/// hkxVertexP4N4T4B4C1T2 meta information
extern const class hkClass hkxVertexP4N4T4B4C1T2Class;

/// This structure describes the memory layout for non blended, textured vertex
/// buffer (with tangents) in P4N4T4B4C1T2 format.
class hkxVertexP4N4T4B4C1T2
{
	public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxVertexP4N4T4B4C1T2 );
	HK_DECLARE_REFLECTION();
		
		//
		// Members
		//
	public:
		
			/// 
		hkVector4 m_position;
		
			/// 
		hkVector4 m_normal;
		
			/// 
		hkVector4 m_tangent;
		
			/// 
		hkVector4 m_binormal;
		
			/// 32 bit color value (ARGB)
		hkUint32 m_diffuse;
		
			/// Texture U coordinate as 32bit float.
		hkReal m_u;
		
			/// Texture V coordinate as 32bit float.
		hkReal m_v;
		
			/// Padding to make the struct hkVector4 aligned.
		hkUint32 m_padding;
};

#endif // HKSCENEDATA_MESH_FORMATS_HKXVERTEXP4N4T4B4C1T2_HKCLASS_H

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
