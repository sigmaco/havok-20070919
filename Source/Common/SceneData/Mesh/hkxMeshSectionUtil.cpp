/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Mesh/hkxMeshSectionUtil.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>


inline void _NormalizeWeights( hkUint8* weights )
{
	hkUint32 total = weights[0] + weights[1] + weights[2] + weights[3];
	hkUint8 qDif = static_cast<hkUint8>( ((255 * 4) - total) / 4 );
	weights[0] = hkUint8(weights[0] + qDif); // get a += for int warning here.. could change to = 
	weights[1] = hkUint8(weights[1] + qDif);
	weights[2] = hkUint8(weights[2] + qDif);
	weights[3] = hkUint8(weights[3] + qDif);
}

void hkxMeshSectionUtil::computeLimitedBoneSection(const hkxMeshSection& si, 
	hkUint32 indexedBoneLimit, hkCreateIndexBuffer indexFunc, hkCreateVertexBuffer vertexFunc,
	hkxMeshSection& newSection, hkArray<hkBoneRemapping*>& boneMatrixMap )
{
	const hkxVertexFormat& vFormat = *si.m_vertexBuffer->m_format;
	const hkxVertexBuffer& sourceVertBuf = *si.m_vertexBuffer;
	const hkUint8* sourceBones = (hkUint8*)( (char*)sourceVertBuf.m_vertexData + + vFormat.m_boneIndexOffset );
	const hkUint8* sourceWeights = (hkUint8*)( (char*)sourceVertBuf.m_vertexData + + vFormat.m_boneWeightOffset ); // so that we can ignore 0 weighted bones

	HK_ASSERT( 0x57a67d46, (vFormat.m_boneIndexOffset > 0) && (vFormat.m_numBonesPerVertex > 0) );

	hkUint8 consideredBone[256];
	boneMatrixMap.reserve(si.m_numIndexBuffers);

	hkArray<hkxIndexBuffer*> newIndexBufferArray;
	hkArray<hkUint16> currentTriListSet;

	int maxReferencedBone = -1;

	//
	// Make a list of index buffers (and split some if need be)
	// that can fit inside the bone limit criteria.
	//
	int weightLimit = 0;
	for (int cib=0; cib< si.m_numIndexBuffers; ++cib)
	{
		hkString::memSet((void*)&consideredBone[0], 0, 256);

		hkBoneRemapping* boneMapping = new hkBoneRemapping; // just an array;
		boneMapping->reserve(indexedBoneLimit);

//		const hkxIndexBuffer* sourceIndexBuffer = si.m_indexBuffers[cib];
		const hkxIndexBuffer& buf = *si.m_indexBuffers[cib];
		if (buf.m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST) 
		{
			int numI = buf.m_length;
			currentTriListSet.reserve(numI); 
			currentTriListSet.setSize(0);

			int nt = numI / 3;
			for (int ti=0; ti < nt; ++ti)
			{
				hkUint32 index[3];
				if (buf.m_indices16)
				{
					index[0] = buf.m_indices16[ti*3];
					index[1] = buf.m_indices16[ti*3 + 1];
					index[2] = buf.m_indices16[ti*3 + 2];
				}
				else // assume we have 32 bit ones then.
				{
					HK_ASSERT2( 0x57a67d47, buf.m_indices32, "Mesh must have full index buffers");
					index[0] = buf.m_indices32[ti*3];
					index[1] = buf.m_indices32[ti*3 + 1];
					index[2] = buf.m_indices32[ti*3 + 2];
				}

				const hkUint8* boneSet[3];
				const hkUint8* weightSet[3]; //XX assumes weight is a uint8
				boneSet[0] = (const hkUint8*)(sourceBones + index[0]*vFormat.m_stride);
				weightSet[0] = (const hkUint8*)(sourceWeights + index[0]*vFormat.m_stride);
				boneSet[1] = (const hkUint8*)(sourceBones + index[1]*vFormat.m_stride);
				weightSet[1] = (const hkUint8*)(sourceWeights + index[1]*vFormat.m_stride);
				boneSet[2] = (const hkUint8*)(sourceBones + index[2]*vFormat.m_stride);
				weightSet[2] = (const hkUint8*)(sourceWeights + index[2]*vFormat.m_stride);
			
				// for all bones that matter, ie have non zero weights,
				// ( there are potentially 12 bones used, but that would be very rare..)
				bool haveHitLimit= false;
				bool haveHitLimitPreviously;
				do {
					haveHitLimitPreviously = haveHitLimit;
					haveHitLimit = false;
					for (int bs=0; bs < 3; ++bs)
					{
						for (int sbs=0; sbs < 4; ++sbs)
						{
							if ( weightSet[bs][sbs] > weightLimit ) //XX assumes weight is a uint8
							{
								// valid bone to worry about
								hkUint8 boneNum = boneSet[bs][sbs];
								if (!consideredBone[boneNum])
								{
									if (maxReferencedBone < boneNum)
										maxReferencedBone = boneNum;
								
									if (boneMapping->getSize() == (hkInt32)indexedBoneLimit)
									{	
										// tipped over the edge, batch up what we have for tris
										if ( haveHitLimitPreviously )
										{
											//HK_WARN(0x576b7d47, "Going around in circles, skipping a triangle that can't be accomodated (more bones than there are slots).");
											// fix up the tri set.. increase the weight limit and try again;
											weightLimit += 2; 
											haveHitLimitPreviously = false; // should all be fine now.. or eventually anyway.
										}
										else 
										// make a set with what we have already in the currentTriListSet.
										{
											if (currentTriListSet.getSize() > 0)
											{
												hkxIndexBuffer* newIndexBuffer = indexFunc( currentTriListSet.getSize(), false, buf.m_indexType);
												boneMatrixMap.pushBack( boneMapping ); // our current bone mapping
												// copy the data as is, assume we have a proper format
												hkString::memCpy( newIndexBuffer->m_indices16,  currentTriListSet.begin(), currentTriListSet.getSize() * sizeof(hkUint16) );
												newIndexBufferArray.pushBack( newIndexBuffer );
												
												boneMapping = new hkBoneRemapping; // just an array;
											}
											
											// start a new tri list (and reiterate this triangle again)
											currentTriListSet.setSize(0);
											hkString::memSet((void*)&consideredBone[0], 0, 256);

											boneMapping->setSize(0);
											boneMapping->reserve(indexedBoneLimit);

											weightLimit = 0;
										}

										haveHitLimit = true;	
										break; // either an error tri (too comlex bone connections, caused double batch) or a normal batch and have to just reconsider this tri.									
									}
									else // bone able to be added
									{
										consideredBone[boneNum] = 1;
										boneMapping->pushBack( boneNum ); // make the new matrix pallete mapping
									}
								} // considered bone
							} // if weight > 0
						} // for all sbs

						if (haveHitLimit) 
						{
							break; // end this for loop
						}
					} // for all bs
				} while (haveHitLimit /*&& !haveHitLimitPreviously*/); // while we need to do another trip around on this tri

				// if !errorTri, then the current tri is valid in the current set, so add it and continue:
			//	bool errorTri = haveHitLimit && haveHitLimitPreviously; // double batch on a triangle.
			//	if (!errorTri)
				{
					currentTriListSet.pushBack( (hkUint16) index[0] );
					currentTriListSet.pushBack( (hkUint16) index[1] );
					currentTriListSet.pushBack( (hkUint16) index[2] );
				}
			} // next tri
		}	
		else
		{
			HK_WARN( 0x5a6b7d45, "INDEX_TYPE_TRI_STRIP or FAN not supported in reoder just yet.");
		}

		// if we have comeout of the above, we either have a full (the same index buffer) 
		// or a remainer after the last ibuf create, so need to clean up:
		if (currentTriListSet.getSize() > 0)
		{
			hkxIndexBuffer* newIndexBuffer = indexFunc( currentTriListSet.getSize(), false, buf.m_indexType);
			boneMatrixMap.pushBack( boneMapping ); // our current bone mapping
			// copy the data as is, assume we have a proper format
			hkString::memCpy( newIndexBuffer->m_indices16,  currentTriListSet.begin(), currentTriListSet.getSize() * sizeof(hkUint16) );
			newIndexBufferArray.pushBack( newIndexBuffer );
		}

	} // next orig buffer

	//
	// We now have a list of (possibly new) index buffers and corresponding bone mappings.
	// We need to find vertices that are shared across these index buffers
	// and break that connection as the bone indices will have to change on a per
	// index buffer basis to match the new palletes.
	//
	hkArray<hkUint8> vertCrossIBUsage;
	hkArray<hkUint32> newVertsAdded;

	int numVerts = si.m_vertexBuffer->m_numVertexData;
	vertCrossIBUsage.setSize( numVerts );
	hkString::memSet( vertCrossIBUsage.begin(), 0, numVerts * sizeof(hkUint8) );

	int numNewIBuf = newIndexBufferArray.getSize();
	int nib; 
	for (nib = 0; nib < (numNewIBuf-1); ++nib)
	{
		hkxIndexBuffer& buf = *newIndexBufferArray[nib];
		// for each vert in ib, check other ibs > cur ib
		// if that vert is used across IB boundaries:
	
//		const hkxIndexBuffer& buf = ib->getBuffer();
		if (buf.m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST) 
		{
			unsigned int numI = buf.m_length;
			for (hkUint32 ti=0; ti < numI; ++ti)
			{
				hkUint32 curIndex;
				if (buf.m_indices16)
				{
					curIndex = buf.m_indices16[ti];
				}
				else
				{
					curIndex = buf.m_indices32[ti];
				}

				// check curIndex for membership in all the next index bufs
				for (int nibNext = (nib + 1); nibNext < numNewIBuf; ++nibNext)
				{
					const hkxIndexBuffer& otherBuf = *newIndexBufferArray[nibNext];
					if (otherBuf.m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST) 
					{
						for (hkUint32 ti2=0; ti2 < otherBuf.m_length; ++ti2)
						{
							hkUint32 otherIndex;
							if (otherBuf.m_indices16)
							{
								otherIndex = otherBuf.m_indices16[ti2];
							}
							else
							{
								otherIndex = otherBuf.m_indices32[ti2];
							}

							if (otherIndex == curIndex)
							{
								vertCrossIBUsage[curIndex]++;
								newVertsAdded.pushBack(curIndex); // clone it later (in this order)
								int proposedNewIndex = newVertsAdded.getSize() + numVerts - 1;
								// change the vertindex in anticipation that the vert will be cloned and added again.
								if (otherBuf.m_indices16)
								{
									otherBuf.m_indices16[ti2] = (hkUint16) proposedNewIndex;
								}
								else
								{
									otherBuf.m_indices32[ti2] = (hkUint32) proposedNewIndex;
								}
							}
						}
					}
				}
			}
		}
		// else TRI or FAN, have already warned about that 
	}

	//
	// We have a cross ib usage index and have redone the index bufs,
	// Now we just need a new vert buffer to store any the new verts 
	
	//XXX As we usually have some unused bones in the mix, we remap the verts
	// down anyway and so have to redo the vert buf again anyway.

	hkxVertexBuffer* newVb = HK_NULL;
//	if (newVertsAdded.getSize() > 0)
//	{
		int numTotalVerts = sourceVertBuf.m_numVertexData + newVertsAdded.getSize();
		newVb = vertexFunc( numTotalVerts, sourceVertBuf.m_format, sourceVertBuf.m_vertexDataClass );
		// copy old verts
		hkString::memCpy( newVb->m_vertexData, sourceVertBuf.m_vertexData, sourceVertBuf.m_numVertexData * vFormat.m_stride);
		// clone other verts
		int newV = sourceVertBuf.m_numVertexData;
		for (int vc=0; vc < newVertsAdded.getSize(); ++vc)
		{
			int vToClone = newVertsAdded[vc];
			void* toPtr = (char*)newVb->m_vertexData + ((newV + vc)*vFormat.m_stride);
			void* fromPtr = (char*)sourceVertBuf.m_vertexData + (vToClone*vFormat.m_stride);
			hkString::memCpy( toPtr, fromPtr, vFormat.m_stride); // clone the vert, index bufs affected will be pointing at this index already.
		}
//	}
//	else
//	{
//		newVb = si.m_vertexBuffer;
//	}

	//
	// Finally, run through on a per index buffer basis and 
	// for each index buf used vert, redo the bone index to match the remapped bones:
	// Do each vert once and only once.
	//

	int finalNumVerts = newVb->m_numVertexData;
	vertCrossIBUsage.setSize(finalNumVerts);
	hkString::memSet( vertCrossIBUsage.begin(), 0 , finalNumVerts * sizeof(hkUint8) );
	
	hkBoneRemapping inverseBoneRemap;
	inverseBoneRemap.setSize(256); // assume 256 bones the max.

	int newVbStride = vFormat.m_stride;
	int newVbMatIndexOffset = vFormat.m_boneIndexOffset;
	int newVbMatWeightOffset = vFormat.m_boneWeightOffset;
	hkInt8* indexBase = (hkInt8*)newVb->m_vertexData + newVbMatIndexOffset;
	hkInt8* weightBase = (hkInt8*)newVb->m_vertexData + newVbMatWeightOffset;

	for (nib = 0; nib < numNewIBuf; ++nib)
	{
		const hkxIndexBuffer& buf = *newIndexBufferArray[nib];
		
		// compute inverse mapping
		hkString::memSet( inverseBoneRemap.begin(), -1, 256 * sizeof (hkInt16) ); // any non assigned or weight==0 bones will go to -1 and get a weight of 0 in the end.
		hkBoneRemapping* boneRemap = boneMatrixMap[nib];
		for (int bri=0; bri < boneRemap->getSize(); ++bri)
		{
			inverseBoneRemap[ (*boneRemap)[bri] ] = (hkInt16) bri;
		}

		// using the inverse bone remap, set the new indices
		if (buf.m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST) 
		{
			unsigned int numI = buf.m_length;
			for (hkUint32 ti=0; ti < numI; ++ti)
			{
				hkUint32 curIndex;
				if (buf.m_indices16)
				{
					curIndex = buf.m_indices16[ti];
				}
				else
				{
					curIndex = buf.m_indices32[ti];
				}

				if (vertCrossIBUsage[curIndex] == 0)
				{
					hkUint8* boneIndices = (hkUint8*)( indexBase + curIndex*newVbStride );  
					hkUint8* boneWeights = (hkUint8*)( weightBase + curIndex*newVbStride );  
					boneIndices[0] = (hkUint8)inverseBoneRemap[boneIndices[0]];
					boneIndices[1] = (hkUint8)inverseBoneRemap[boneIndices[1]];
					boneIndices[2] = (hkUint8)inverseBoneRemap[boneIndices[2]];
					boneIndices[3] = (hkUint8)inverseBoneRemap[boneIndices[3]];

					bool alteredWeights = false;
					for (int bic=0; bic <4; ++bic)
					{
						if (boneIndices[bic] == 255)
						{
							boneIndices[bic] = 0;
							boneWeights[bic] = 0;
						}
					}
					if (alteredWeights)
					{
						_NormalizeWeights(boneWeights);
					}

					HK_ASSERT( 0x7a6c7d46, 
						   ( boneIndices[0] < indexedBoneLimit )
						&& ( boneIndices[1] < indexedBoneLimit )
						&& ( boneIndices[2] < indexedBoneLimit )
						&& ( boneIndices[3] < indexedBoneLimit ) );
					vertCrossIBUsage[curIndex] = 1; // used / done
				}
			}
		}
	}

	//
	// Make the new section for it all:
	//
	newSection.m_numIndexBuffers = newIndexBufferArray.getSize();
	newSection.m_indexBuffers = hkAllocate<hkxIndexBuffer*>( newSection.m_numIndexBuffers, HK_MEMORY_CLASS_ANIMATION );

	hkArray<hkxIndexBuffer*>::copy(newSection.m_indexBuffers, newIndexBufferArray.begin(), newIndexBufferArray.getSize());
	newSection.m_vertexBuffer = newVb;
	newSection.m_material = si.m_material;

	return;
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
