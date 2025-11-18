/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


HK_FORCE_INLINE hkp3AxisSweep* hkpSpuBroadPhaseUtil::getBroadPhaseFromPpu(const hkp3AxisSweep* broadphaseOnPpu, int dmaGroup, void *broadphaseBufferOnSpu)
{
	hkp3AxisSweep* broadphase = reinterpret_cast<hkp3AxisSweep*>( broadphaseBufferOnSpu );
	hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion(broadphase, broadphaseOnPpu, sizeof(hkp3AxisSweep), hkSpuDmaManager::READ_COPY, dmaGroup);
	broadphaseBufferOnSpu = hkAddByteOffset(broadphaseBufferOnSpu, HK_NEXT_MULTIPLE_OF(128, sizeof(hkp3AxisSweep)));

	//
	// bring in broadphase's 'nodes' array from ppu
	//
	int sizeNodesArray = HK_NEXT_MULTIPLE_OF(128, broadphase->m_nodes.getSize() * sizeof(hkp3AxisSweep::hkpBpNode));
	hkp3AxisSweep::hkpBpNode*			arrayBpNodes		= reinterpret_cast<hkp3AxisSweep::hkpBpNode*>( broadphaseBufferOnSpu );
	const hkp3AxisSweep::hkpBpNode*	arrayBpNodesOnPpu	= broadphase->m_nodes.begin();
	hkSpuDmaManager::getFromMainMemory(arrayBpNodes, arrayBpNodesOnPpu, sizeNodesArray, hkSpuDmaManager::READ_COPY, dmaGroup);
	new (&broadphase->m_nodes) hkArray<hkp3AxisSweep::hkpBpNode>(arrayBpNodes, broadphase->m_nodes.getSize(), broadphase->m_nodes.getCapacity());
	broadphaseBufferOnSpu = hkAddByteOffset(broadphaseBufferOnSpu, sizeNodesArray);

	//
	// bring in the endpoints for all 3 axes
	//
	{
		for (int i=0; i<3; i++)
		{
			int sizeAxisEndPointsArray = HK_NEXT_MULTIPLE_OF(128, broadphase->m_axis[i].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
			hkp3AxisSweep::hkpBpEndPoint*			arrayAxisEndPoints		= reinterpret_cast<hkp3AxisSweep::hkpBpEndPoint*>( broadphaseBufferOnSpu );
			const hkp3AxisSweep::hkpBpEndPoint*	arrayAxisEndPointsPpu	= broadphase->m_axis[i].m_endPoints.begin();
			hkSpuDmaManager::getFromMainMemory(arrayAxisEndPoints, arrayAxisEndPointsPpu, sizeAxisEndPointsArray, hkSpuDmaManager::READ_COPY, dmaGroup);
			new (&broadphase->m_axis[i].m_endPoints) hkArray<hkp3AxisSweep::hkpBpEndPoint>(arrayAxisEndPoints, broadphase->m_axis[i].m_endPoints.getSize(), broadphase->m_axis[i].m_endPoints.getCapacity());
			broadphaseBufferOnSpu = hkAddByteOffset(broadphaseBufferOnSpu, sizeAxisEndPointsArray);
		}
	}

	return broadphase;
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
