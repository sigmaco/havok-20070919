/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/SceneData/Mesh/hkxVertexFormatUtil.h>


hkUint32 hkxVertexFormatUtil::getVertexProperties( const hkxVertexFormat& format )
{
	hkUint32 props = HK_VERTEX_NONE;

	props |= (format.m_positionOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_POSITION;
	props |= (format.m_normalOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_NORMAL;
	props |= (format.m_tangentOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_TANGENT;
	props |= (format.m_binormalOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_BINORM;
	props |= (format.m_numBonesPerVertex >0) ? HK_VERTEX_BONES : HK_VERTEX_NONE;
	props |= (format.m_boneWeightOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_WEIGHTS;
	props |= (format.m_boneIndexOffset == HK_VFMT_NOT_PRESENT) ? HK_VERTEX_NONE : HK_VERTEX_INDICES;

	return props;
}

hkUlong hkxVertexFormatUtil::getAlignment(hkUlong addr)
{
	int align = 0;
	
	// Find lsb
	while ((addr) && ((addr & 0x1) == 0))
	{
		addr = addr >> 1;
		align++;
	}

	return (hkUlong)(1 << align);
}

hkUlong hkxVertexFormatUtil::getAlignment(hkUint32 property, const hkxVertexBuffer& buffer)
{
	const hkUlong baseAddr = reinterpret_cast<hkUlong>( buffer.m_vertexData );
	const hkUlong stride   = buffer.m_format->m_stride;

	if (property & HK_VERTEX_POSITION)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_positionOffset);
	}
	if (property & HK_VERTEX_NORMAL)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_normalOffset);
	}
	if (property & HK_VERTEX_TANGENT)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_tangentOffset);
	}
	if (property & HK_VERTEX_BINORM)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_binormalOffset);
	}
	if (property & HK_VERTEX_BONES)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_numBonesPerVertex);
	}
	if (property & HK_VERTEX_WEIGHTS)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_boneIndexOffset);
	}
	if (property & HK_VERTEX_INDICES)
	{
		return getAlignment( baseAddr + stride +  buffer.m_format->m_boneWeightOffset);
	}

	return 0;
}



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
