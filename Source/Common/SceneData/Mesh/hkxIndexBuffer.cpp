/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>


/// Returns the number of triangles
int hkxIndexBuffer::getNumTriangles () const
{
    HK_ASSERT ( 0x3e2a6b13, m_indices16 != HK_NULL ||  m_indices32 != HK_NULL );

    int numIndices = m_indices16 ? m_numIndices16 : m_numIndices32;

    //currently assume only TRI_LIST encountered

    switch ( m_indexType )
    {
        case hkxIndexBuffer::INDEX_TYPE_TRI_LIST:
        {
            return numIndices/3;
        }

        default:
            break;
    }

    return 0;
}

void hkxIndexBuffer::getTriangleIndices (hkUint32 triIndex, hkUint32& indexAOut, hkUint32& indexBOut, hkUint32& indexCOut)
{
    if ( m_indices16 )
    {
        // 16 bit indices
        hkUint16 triIndex16 = (hkUint16)triIndex;
        switch ( m_indexType )
        {
            case hkxIndexBuffer::INDEX_TYPE_TRI_LIST:
            {
                indexAOut = (hkUint32)m_indices16[triIndex16*3];
                indexBOut = (hkUint32)m_indices16[triIndex16*3+1];
                indexCOut = (hkUint32)m_indices16[triIndex16*3+2];
                break;
            }

            default:
                break;
        }
    }

    else
    {
        // 32 bit indices
        HK_ASSERT( 0x3e2a6b13, m_indices32 != HK_NULL );
        switch ( m_indexType )
        {
            case hkxIndexBuffer::INDEX_TYPE_TRI_LIST:
            {
                indexAOut = m_indices32[triIndex*3];
                indexBOut = m_indices32[triIndex*3+1];
                indexCOut = m_indices32[triIndex*3+2];
                break;
            }

            default:
                break;
        }
    }

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
