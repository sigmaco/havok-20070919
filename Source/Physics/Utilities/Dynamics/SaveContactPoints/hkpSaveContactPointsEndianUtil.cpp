/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSaveContactPointsEndianUtil.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSaveContactPointsUtil.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpPhysicsSystemWithContacts.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSerializedAgentNnEntry.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Agent/CompoundAgent/BvTreeStream/hkpBvTreeStreamAgent.h>
#include <Physics/Internal/Collide/Agent3/BoxBox/hkpBoxBoxAgent3.h>
#include <Physics/Internal/Collide/Agent3/CapsuleTriangle/hkpCapsuleTriangleAgent3.h>
#include <Physics/Internal/Collide/Agent3/PredGskAgent3/hkpPredGskAgent3.h>
#include <Physics/Internal/Collide/Agent3/PredGskCylinderAgent3/hkpPredGskCylinderAgent3.h>
#include <Physics/Internal/Collide/Agent3/List3/hkpListAgent3.h>
#include <Physics/Internal/Collide/Agent3/ConvexList3/hkpConvexListAgent3.h>
#include <Physics/Internal/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h>
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>
#include <Physics/Dynamics/World/Util/hkpWorldCallbackUtil.h>
#include <Physics/Dynamics/Entity/Util/hkpEntityCallbackUtil.h>


#include <Common/Base/Container/PointerMap/hkPointerMapBase.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

// Needed for endian switching
#include <Physics/Collide/Agent/ConvexAgent/BoxBox/hkpBoxBoxManifold.h>
#include <Physics/Internal/Collide/Util/hkpCollideTriangleUtil.h>
#include <Physics/Internal/Collide/Gjk/hkpGskCache.h>
#include <Physics/Internal/Collide/Gjk/GskManifold/hkpGskManifold.h>

#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h>
#include <Physics/Internal/Collide/Agent3/Machine/1n/hkpAgent1nTrack.h>


HK_COMPILE_TIME_ASSERT( sizeof(hkUint32) == sizeof(hkpContactPointProperties::UserData) );


/////////////////////////////////////////////////////////////////////////
//
//  Helper functions
//
//////////////////////////////////////////////////////////////////////////



// Base endian swapping func
inline void hkpSaveContactPointsEndianUtil::reverseBytes(void* start, int count)
{
	hkUint8* front = (hkUint8*)start;
	hkUint8* back  = (hkUint8*)hkAddByteOffset(start, count-1);
	for (int i = 0; i < count / 2; i++)
	{
		hkAlgorithm::swap(*(front++), *(back--));
	}
}

// Basic types swapping
inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkUint16& uint16) { reverseBytes(&uint16, sizeof(uint16)); }
inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkUint32& uint32) { reverseBytes(&uint32, sizeof(uint32)); }
inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkReal& real)     { reverseBytes(&real, sizeof(real)); }
inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkVector4& vec4)  { for (int i = 0; i < 4; i++) { swapEndianType(vec4(i)); } }


//
// Agent entry swapping
//
inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpAgentNnMachineTimEntry* entry)
{
	swapEndianType(entry->m_timeOfSeparatingNormal);
	swapEndianType(entry->m_separatingNormal);
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpAgentNnMachinePaddedEntry* entry) 
{
	// nothing here but padding
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpAgent1nMachineTimEntry* entry)
{
	swapEndianType(entry->m_shapeKeyPair.m_shapeKeyA);
	swapEndianType(entry->m_shapeKeyPair.m_shapeKeyB);
	swapEndianType(entry->m_timeOfSeparatingNormal);
	swapEndianType(entry->m_separatingNormal);
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpAgent1nMachinePaddedEntry* entry)
{
	swapEndianType(entry->m_shapeKeyPair.m_shapeKeyA);
	swapEndianType(entry->m_shapeKeyPair.m_shapeKeyB);
}


//
// Agent data swaping
//

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpBoxBoxManifold* manifold)
{
	for (int i = 0; i < manifold->m_numPoints; i++)
	{
		swapEndianType(manifold->m_contactPoints[i].m_contactPointId);
	}
	swapEndianType(manifold->m_manifoldNormalA);
	swapEndianType(manifold->m_manifoldNormalB);
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpCapsuleTriangleCache3* cache)
{
	for (int i = 0; i < 3; i++)
	{
		swapEndianType(cache->m_contactPointId[i]);
		swapEndianType(cache->m_triangleCache.m_invEdgeLen[i]);
	}
	swapEndianType(cache->m_triangleCache.m_invNormalLen);
	swapEndianType(cache->m_triangleCache.m_normalLen);
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpGskCache* cache)
{
	for (int i = 0; i < 4; i++)
	{
		swapEndianType( cache->m_vertices[i] );
	}
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpGskManifold* manifold)
{
	for (int i = 0; i < manifold->m_numContactPoints; i++)
	{
		swapEndianType( manifold->m_contactPoints[i].m_id );
	}

	const int numVertIds = manifold->m_numVertsA + manifold->m_numVertsB;
	hkpGskManifold::VertexId* vertIds = manifold->getVertexIds();
	for (int i = 0; i < numVertIds; i++)
	{
		swapEndianType( vertIds[i] );
	}
}

inline void hkpSaveContactPointsEndianUtil::swapEndianType(hkpContactPointProperties* p)
{
	swapEndianType(p->m_internalDataA);
	// in hkpSolverResults
	swapEndianType(p->m_impulseApplied);
	swapEndianType(p->m_internalSolverData);
	// in hkContactPointMaterial
	// user data ?
#if HK_POINTER_SIZE == 4
	swapEndianType(reinterpret_cast<hkUint32&>(p->m_userData));
#endif
}


// This function an only be run when deserializing an entry, because it requires access to the initialized collision dispatcher
void HK_CALL hkpSaveContactPointsEndianUtil::swapEndianTypeInCollisionEntry( const hkpProcessCollisionInput* input, hkpSerializedAgentNnEntry& serializedEntry )
{
	int sizeOfThisEntry;
	const hkBool nnEntry = true;
	bool dummyTrackUsed = false;
	swapEndianTypeInEntry(input, reinterpret_cast<hkpAgentEntry*>(serializedEntry.m_nnEntryData), serializedEntry.m_trackInfo, nnEntry, sizeOfThisEntry, dummyTrackUsed);
	serializedEntry.endianCheckUint32() = hkpSerializedAgentNnEntry::ENDIAN_CHECK_VALUE;

	int contactPropertiesStriding = serializedEntry.m_atom.getContactPointPropertiesStriding();
	int numPropertiesBlocks = serializedEntry.m_propertiesStream.getSize() / contactPropertiesStriding;
	for (int i = 0; i < numPropertiesBlocks; i++)
	{
		hkpContactPointProperties* properties = reinterpret_cast<hkpContactPointPropertiesStream*>(hkAddByteOffset(serializedEntry.m_propertiesStream.begin(), i * contactPropertiesStriding))->asProperties();
		swapEndianType(properties);
		// need to swap the remaining user datas too
		hkUint32* afterProp = reinterpret_cast<hkUint32*>(properties+1);
		for (int e = 0; e < serializedEntry.m_atom.m_numUserDatasForBodyA + serializedEntry.m_atom.m_numUserDatasForBodyA; e++)
		{
			swapEndianType(afterProp[e]);
		}
	}
}




// function body cloned from ::serializeEntry
void HK_CALL hkpSaveContactPointsEndianUtil::swapEndianTypeInEntry( const hkpProcessCollisionInput* input, hkpAgentEntry* entry, hkpSerializedTrack1nInfo& serializedTrack, hkBool isNnEntry, int& sizeOfThisEntryOut, bool& trackUsedOut )
{
	trackUsedOut = false;

	hkpAgentData* agentData;
	hkAgent3::StreamCommand command = static_cast<hkAgent3::StreamCommand>(entry->m_streamCommand);

	switch ( command )
	{
		// The non-stream agent should be removed
	case hkAgent3::STREAM_CALL_AGENT:
		{
			HK_ASSERT2(0xad7654dd, false, "Agent2 technology not supported by hkpSaveContactPointsUtil. Unregister agent2 agents, to save contact points between hkRigidBodies.");
		}
	case hkAgent3::STREAM_CALL_WITH_TIM_FLIPPED:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. NnEntry cannot be flipped.");
			// fall through
		}
	case hkAgent3::STREAM_CALL_WITH_TIM:
		{
			if (isNnEntry)
			{
				agentData = hkAddByteOffset( entry, hkSizeOf( hkpAgentNnMachineTimEntry ) ); 
				swapEndianType( static_cast<hkpAgentNnMachineTimEntry*>(entry) );
			}
			else
			{
				agentData = hkAddByteOffset( entry, hkSizeOf( hkpAgent1nMachineTimEntry ) ); 
				swapEndianType( static_cast<hkpAgent1nMachineTimEntry*>(entry) );
			}

			goto continueConvertEntryToSerialized;
		}
	case hkAgent3::STREAM_CALL_FLIPPED:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. NnEntry cannot be flipped.");
			// fall through
		}
	case hkAgent3::STREAM_CALL:
		{
			if (isNnEntry)
			{
				agentData = hkAddByteOffset( entry, hkSizeOf( hkpAgentNnMachinePaddedEntry ) );
				swapEndianType( static_cast<hkpAgentNnMachinePaddedEntry*>(entry) );
			}
			else
			{
				agentData = hkAddByteOffset( entry, hkSizeOf( hkpAgent1nMachinePaddedEntry ) );
				swapEndianType( static_cast<hkpAgent1nMachinePaddedEntry*>(entry) );
			}

continueConvertEntryToSerialized:

			hkAgent3::ProcessFunc func = input->m_dispatcher->getAgent3ProcessFunc( entry->m_agentType );
			hkpSerializedAgentNnEntry::SerializedAgentType agentType = hkpSaveContactPointsUtil::getSerializedAgentType(func);

			sizeOfThisEntryOut = entry->m_size; 

			switch(agentType)
			{
			case hkpSerializedAgentNnEntry::BOX_BOX_AGENT3:
				{
					swapEndianType( reinterpret_cast<hkpBoxBoxManifold*>(agentData) );
					break;
				}
			case hkpSerializedAgentNnEntry::CAPSULE_TRIANGLE_AGENT3:
				{
					swapEndianType( reinterpret_cast<hkpCapsuleTriangleCache3*>(agentData) );
					break;
				}
			case hkpSerializedAgentNnEntry::PRED_GSK_AGENT3:
			case hkpSerializedAgentNnEntry::PRED_GSK_CYLINDER_AGENT3:
				{
					hkpGskCache* gskCache = reinterpret_cast<hkpGskCache*>(agentData);
					hkpGskManifold* gskManifold = reinterpret_cast<hkpGskManifold*>( gskCache + 1 );
					swapEndianType( gskCache );
					swapEndianType( gskManifold );
					break;
				}
			case hkpSerializedAgentNnEntry::CONVEX_LIST_AGENT3:
				{
					if (hkPredGskAgent3::getGskFlag(agentData, hkpGskCache::GSK_FLAGS_CONVEX_LIST_IN_GSK_MODE))
					{
						hkpGskCache* gskCache = reinterpret_cast<hkpGskCache*>(agentData);
						hkpGskManifold* gskManifold = reinterpret_cast<hkpGskManifold*>( gskCache + 1 );
						swapEndianType( gskCache );
						swapEndianType( gskManifold );
					}
					else
					{
						swapEndianTypeIn1nTrack(input, serializedTrack);
						trackUsedOut = true;
					}
					break;
				}
			case hkpSerializedAgentNnEntry::LIST_AGENT3:
			case hkpSerializedAgentNnEntry::BV_TREE_AGENT3:
			case hkpSerializedAgentNnEntry::COLLECTION_COLLECTION_AGENT3:
				{
					swapEndianTypeIn1nTrack(input, serializedTrack);
					trackUsedOut = true;
					break;
				}
			default:
				{
					HK_ASSERT2(0xad54baa1, false, "Unsupported agent3 type. Unregister some agent3 agents.");
					break;
				}
			}
			break;
		}

	case hkAgent3::STREAM_NULL:
	case hkAgent3::STREAM_END:
		{
			HK_ASSERT2(0xad7644dd, !isNnEntry, "Internal error. Stream null & stream end commands not supported for NnEntries.");
			sizeOfThisEntryOut = sizeof( hkpAgent1nMachinePaddedEntry );
			break;
		}
	}
}


// function body cloned from ::serialized1nTrack
void HK_CALL hkpSaveContactPointsEndianUtil::swapEndianTypeIn1nTrack( const hkpProcessCollisionInput* input, hkpSerializedTrack1nInfo& serializedTrack )
{
	int currentSubTrackIdx;
	hkpSerializedSubTrack1nInfo* serializedSubTrack;

	if (serializedTrack.m_subTracks.getSize())
	{
		currentSubTrackIdx = 0;
		serializedSubTrack = serializedTrack.m_subTracks[0];
	}
	else
	{
		currentSubTrackIdx = -1;
		serializedSubTrack = HK_NULL;
	}

	bool trackUsed = false;
	for (int i = 0; i < serializedTrack.m_sectors.getSize(); ++i)
	{
		hkpAgent1nSector* readSector = serializedTrack.m_sectors[i];
		hkpAgentData* readData = readSector->getBegin();
		hkpAgentData* readEnd = readSector->getEnd();

		// Make sure the sector is ok
		while (readData < readEnd)
		{
			hkpAgentEntry* entry = reinterpret_cast<hkpAgentEntry*>(readData);
			const hkBool nonNnEntry = false;

			int sizeOfThisEntry = 0;
			if ( serializedSubTrack 
			  && ( serializedSubTrack->m_sectorIndex != i 
				|| hkUlong(serializedSubTrack->m_offsetInSector) < hkGetByteOffset(readSector->getBegin(), readData) )
				)
			{
				HK_ASSERT2(0XAD87555D, trackUsed , "Track has not been used." );
				trackUsed = false;

				if (currentSubTrackIdx+1 < serializedTrack.m_subTracks.getSize())
				{
					serializedSubTrack = serializedTrack.m_subTracks[++currentSubTrackIdx];
				}
				else
				{
					serializedSubTrack = HK_NULL;
				}
			}
			HK_ASSERT2(0XAD87555D, !trackUsed , "Track already used." );

			swapEndianTypeInEntry(input, entry, *serializedSubTrack, nonNnEntry, sizeOfThisEntry, trackUsed);
			readData = hkAddByteOffset(readData, sizeOfThisEntry );


		}
	}

	HK_ASSERT2(0XAD87555D, trackUsed || !serializedSubTrack, "Not all subTracks have their endianness swapped." );
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
