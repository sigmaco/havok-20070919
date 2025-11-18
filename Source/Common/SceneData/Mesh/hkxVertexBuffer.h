/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKSCENEDATA_MESH_HKXVERTEXBUFFER_HKCLASS_H
#define HKSCENEDATA_MESH_HKXVERTEXBUFFER_HKCLASS_H

class hkxVertexFormat;

/// hkxVertexBuffer meta information
extern const class hkClass hkxVertexBufferClass;

/// The information needed to construct a vertex buffer. This structure binds a
/// chunk of memory to a vertex format
class hkxVertexBuffer
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxVertexBuffer );
        HK_DECLARE_REFLECTION();
	
			/// Default constructor
        hkxVertexBuffer() { }
		
		//
		// Members
		//
	public:
		
			/// The pointer to a generic vertex buffer
		const hkClass* m_vertexDataClass;
		void* m_vertexData;
		hkInt32 m_numVertexData;
		
			/// The pointer to the vertex format description.
		class hkxVertexFormat* m_format;
};

#endif // HKSCENEDATA_MESH_HKXVERTEXBUFFER_HKCLASS_H


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
