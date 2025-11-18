/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// Default constructor
inline hkxVertexFormat::hkxVertexFormat() 
{
	m_stride = 0;
	m_positionOffset = HK_VFMT_NOT_PRESENT;
	m_normalOffset = HK_VFMT_NOT_PRESENT;
	m_tangentOffset = HK_VFMT_NOT_PRESENT;
	m_binormalOffset = HK_VFMT_NOT_PRESENT;
	m_numBonesPerVertex = 0;
	m_boneIndexOffset = HK_VFMT_NOT_PRESENT;
	m_boneWeightOffset = HK_VFMT_NOT_PRESENT;
	m_numTextureChannels = 1;
	m_tFloatCoordOffset = HK_VFMT_NOT_PRESENT;
	m_tQuantizedCoordOffset = HK_VFMT_NOT_PRESENT;
	m_colorOffset = HK_VFMT_NOT_PRESENT;
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
