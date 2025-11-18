/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Dynamics/World/hkpWorld.h>


#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandle.h>
#include <Physics/Internal/Collide/BroadPhase/3AxisSweep/hkp3AxisSweep.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseDispatcher.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandlePair.h>

#include <Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h>




enum 
{
	MAX_OBJECTS = 80,
	MAX_ELEMS = MAX_OBJECTS * 6 + 6,
};


struct BroadphaseBatchAddUnitTest
{
	BroadphaseBatchAddUnitTest(const hkVector4& worldMin, const hkVector4& worldMax, int ldNumMarkers);
	~BroadphaseBatchAddUnitTest();

	hkReal getRandomNumber();
	void freeRandomNumbers( int num = 1 );

	hkp3AxisSweep m_broadphaseA;
	hkp3AxisSweep m_broadphaseB;
	hkPseudoRandomGenerator m_random;

	hkpBroadPhaseHandle m_objectsA[MAX_OBJECTS];
	hkpBroadPhaseHandle m_objectsB[MAX_OBJECTS];

	int m_allocatedNumbers;
	hkReal m_numbers[MAX_ELEMS];

	hkInplaceArray<hkAabb, MAX_OBJECTS> m_aabbs;
};

BroadphaseBatchAddUnitTest::BroadphaseBatchAddUnitTest(const hkVector4& worldMin, const hkVector4& worldMax, int ldNumMarkers):
		m_broadphaseA( worldMin, worldMax, ldNumMarkers), m_broadphaseB( worldMin, worldMax, ldNumMarkers), m_random(1)
{
	m_allocatedNumbers = 0;
	for (int i =0; i < MAX_ELEMS; i++){ m_numbers[i] = hkReal(i);	}
	for (int j =0; j < MAX_ELEMS*3;j++)
	{
		int a = m_random.getRand32() % MAX_ELEMS;
		int b = m_random.getRand32() % MAX_ELEMS;
		hkAlgorithm::swap( m_numbers[a], m_numbers[b] );
	}
}

BroadphaseBatchAddUnitTest::~BroadphaseBatchAddUnitTest()
{
	m_broadphaseA.markForWrite();
	m_broadphaseB.markForWrite();
}

hkReal BroadphaseBatchAddUnitTest::getRandomNumber()
{
	HK_ASSERT( 0x0, m_allocatedNumbers < MAX_ELEMS );
	return m_numbers[ m_allocatedNumbers ++];
}

void BroadphaseBatchAddUnitTest::freeRandomNumbers( int num )
{
	m_allocatedNumbers-= num;
}

void getRandomAabb( BroadphaseBatchAddUnitTest& data, hkAabb& aabb )
{
	hkVector4 a; a.setZero4();
	a(0) = data.getRandomNumber();
	a(1) = data.getRandomNumber();
	a(2) = data.getRandomNumber();
	hkVector4 b; b.setZero4();
	b(0) = data.getRandomNumber();
	b(1) = data.getRandomNumber();
	b(2) = data.getRandomNumber();

	aabb.m_min.setMin4( a, b );
	aabb.m_max.setMax4( a, b );
}


void compareLists( BroadphaseBatchAddUnitTest& data, hkArray<hkpBroadPhaseHandlePair>& listA, hkArray<hkpBroadPhaseHandlePair>& listB )
{
	//
	//	set replace objectB in listB by object As
	//
	{
		for (int i = 0; i < listB.getSize(); i++ )
		{
			hkpBroadPhaseHandlePair& pb = listB[i];
			pb.m_a = &data.m_objectsA[ pb.m_a - &data.m_objectsB[0] ];
			pb.m_b = &data.m_objectsA[ pb.m_b - &data.m_objectsB[0] ];
		}
	}

	hkpTypedBroadPhaseDispatcher::removeDuplicates( listA, listB );
	HK_TEST( listA.getSize() == 0);
	HK_TEST( listB.getSize() == 0);
}

void compareBroadPhases( BroadphaseBatchAddUnitTest& data, hkp3AxisSweep& bpA, hkp3AxisSweep& bpB )
{
	for (int axisIndex = 0; axisIndex < 3; axisIndex++)
	{
		hkp3AxisSweep::hkpBpAxis& axisA = bpA.m_axis[axisIndex];
		hkp3AxisSweep::hkpBpAxis& axisB = bpB.m_axis[axisIndex];

		int a = 1;
		int b = 1;

		while ( a < axisA.m_endPoints.getSize()-1 && b < axisA.m_endPoints.getSize()-1 )
		{
			const hkp3AxisSweep::hkpBpEndPoint& ea = axisA.m_endPoints[a];
			const hkp3AxisSweep::hkpBpEndPoint& eb = axisB.m_endPoints[b];
			const hkp3AxisSweep::hkpBpNode& na = bpA.m_nodes[ ea.m_nodeIndex];
			const hkp3AxisSweep::hkpBpNode& nb = bpB.m_nodes[ eb.m_nodeIndex];
			if ( na.isMarker() )
			{
				a++;
				if ( nb.isMarker() ){ b++; }
				continue;
			}
			if ( nb.isMarker() )
			{
				b++;
				continue;
			}

			hkUlong indexA = na.m_handle - &data.m_objectsA[0];
			hkUlong indexB = nb.m_handle - &data.m_objectsB[0];
			HK_TEST( indexA == indexB );
			HK_TEST( ea.m_value == eb.m_value );
			a++;
			b++;
		}
	}
}

void initializeInitialBroadPhase(BroadphaseBatchAddUnitTest& data)
{
	data.m_broadphaseA.lock();
	data.m_broadphaseB.lock();

	data.m_aabbs.setSizeUnchecked( MAX_OBJECTS );

	hkInplaceArray<hkpBroadPhaseHandlePair, 1024> newPairsA;
	hkInplaceArray<hkpBroadPhaseHandlePair, 1024> newPairsB;
	hkInplaceArray<hkpBroadPhaseHandle*, MAX_OBJECTS> objectsB;

	for (int i =0; i < MAX_OBJECTS; i++ )
	{
		getRandomAabb( data, data.m_aabbs[i] );
		data.m_broadphaseA.addObject( &data.m_objectsA[i], data.m_aabbs[i], newPairsA );
		objectsB.pushBackUnchecked( &data.m_objectsB[i] );
	}
	data.m_broadphaseB.addObjectBatch(objectsB, data.m_aabbs,  newPairsB );

	compareLists( data, newPairsA, newPairsB );
	compareBroadPhases( data, data.m_broadphaseA, data.m_broadphaseB );

	data.m_broadphaseB.unlock();
	data.m_broadphaseA.unlock();
}

void removeAndReaddBatch(BroadphaseBatchAddUnitTest& data)
{
	data.m_broadphaseA.lock();
	data.m_broadphaseB.lock();

	hkArray<hkpBroadPhaseHandlePair> pairsA; pairsA.reserve(1024);
	hkArray<hkpBroadPhaseHandlePair> pairsB; pairsB.reserve(1024);
	hkArray<hkpBroadPhaseHandle*> objectsA; objectsA.reserve(MAX_OBJECTS);
	hkArray<hkpBroadPhaseHandle*> objectsB; objectsB.reserve(MAX_OBJECTS);
	hkArray<hkAabb> aabbs; aabbs.reserve(MAX_OBJECTS);
	{
		for (int i =0; i < MAX_OBJECTS; i++ )
		{
			if ( data.m_random.getRandChar(256) < 128 )
			{
				continue;
			}
			data.m_broadphaseA.removeObject( &data.m_objectsA[i], pairsA );
			objectsA.pushBackUnchecked( &data.m_objectsA[i] );
			objectsB.pushBackUnchecked( &data.m_objectsB[i] );
			aabbs.pushBack( data.m_aabbs[i] );
		}
	}
	data.m_broadphaseB.removeObjectBatch( objectsB, pairsB );
	compareLists( data, pairsA, pairsB );
	compareBroadPhases( data, data.m_broadphaseA, data.m_broadphaseB );

	//
	//	Add everything again
	//

	{
		for ( int j = 0; j < objectsA.getSize(); j ++ )
		{
			data.m_broadphaseA.addObject( objectsA[j], aabbs[j], pairsA );
		}
	}
	data.m_broadphaseB.addObjectBatch(objectsB, aabbs,  pairsB );
	compareLists( data, pairsA, pairsB );
	compareBroadPhases( data, data.m_broadphaseA, data.m_broadphaseB );

	data.m_broadphaseB.unlock();
	data.m_broadphaseA.unlock();
}

	// special phantom, which is much more strict when objects are removed or added
class BroadphaseBatchAddUnitTestPhantom: public hkpSimpleShapePhantom
{
	public:
		BroadphaseBatchAddUnitTestPhantom( const hkpShape* shape, const hkTransform& t ): hkpSimpleShapePhantom( shape, t ){}

		void removeOverlappingCollidable( hkpCollidable* collidable )
		{
			for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
			{
				if ( m_collisionDetails[i].m_collidable == collidable )
				{
					m_collisionDetails.removeAt( i );
					return;
				}
			}
			HK_TEST(0);
		}

		void addOverlappingCollidable( hkpCollidable* collidable )
		{
			for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
			{
				HK_TEST ( m_collisionDetails[i].m_collidable != collidable );
			}

			CollisionDetail& det = m_collisionDetails.expandOne();
			det.m_collidable = collidable;
		}

		void check(  )
		{
			hkpWorld* world = getWorld();
			if (! world)
			{
				HK_TEST( 0 == m_collisionDetails.getSize() );
				return;
			}
			hkInplaceArray<hkpBroadPhaseHandlePair, MAX_OBJECTS> pairs;
			world->getBroadPhase()->reQuerySingleObject( getCollidable()->getBroadPhaseHandle(), pairs );
			for (int p =0; p < pairs.getSize(); p++)
			{
				hkpTypedBroadPhaseHandlePair* pair = static_cast<hkpTypedBroadPhaseHandlePair*>(&pairs[p]);


				hkpCollidable* other = static_cast<hkpCollidable*>( pair->getElementB()->getOwner() );

				int i;
				for ( i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
				{

					CollisionDetail& detail = m_collisionDetails[i];

					if ( detail.m_collidable == other )
					{
						break;
					}
				}
				HK_TEST( i >=0 );
			}
		}
};

struct BroadphaseBatchAddUnitTest2
{
	BroadphaseBatchAddUnitTest2();
	~BroadphaseBatchAddUnitTest2();

	hkpWorld* m_world;
	hkPseudoRandomGenerator m_random;
	BroadphaseBatchAddUnitTestPhantom* m_objects[MAX_OBJECTS];
};

BroadphaseBatchAddUnitTest2::BroadphaseBatchAddUnitTest2(): m_random(1)
{
	hkpWorldCinfo winfo;
	winfo.setBroadPhaseWorldSize( 1000.0f );
	winfo.m_collisionTolerance = 0.1f;
	// NOTE: Disabling this until the marker crash issue is fixed.
	//winfo.m_broadPhaseNumMarkers = 32;

	m_world = new hkpWorld( winfo );

	hkpShape* shape = new hkpSphereShape( 0.1f );

	for ( int i=0; i < MAX_OBJECTS; i++ )
	{
		hkTransform t; t.setIdentity();
		m_random.getRandomVector11( t.getTranslation() );
		m_objects[i] = new BroadphaseBatchAddUnitTestPhantom( shape, t );
		m_world->lock();
		m_world->addPhantom(m_objects[i]);
		m_world->unlock();
	}

	shape->removeReference();
}

BroadphaseBatchAddUnitTest2::~BroadphaseBatchAddUnitTest2()
{
	m_world->lock();
	for ( int i=0; i < MAX_OBJECTS; i++ )
	{
		m_objects[i]->removeReference();
	}
	delete m_world;
}

static void batchAddAndRemoveAndVerify(BroadphaseBatchAddUnitTest2& data)
{
	data.m_world->lock();

	// grep some random objects
	hkInplaceArray<hkpPhantom*,MAX_OBJECTS> phantoms;
	{
		for (int i=0; i < MAX_OBJECTS; i++)
		{
			if ( data.m_random.getRandChar(255) < 128 )
			{
				phantoms.pushBackUnchecked( data.m_objects[i] );
			}
		}
	}
	
	// remove and check
	data.m_world->removePhantomBatch( phantoms.begin(), phantoms.getSize() );
	{
		for ( int i=0; i < MAX_OBJECTS; i++ )	{		data.m_objects[i]->check();	}
	}

	// move and check
	{
		hkVector4 pos;
		for ( int i=0; i < MAX_OBJECTS; i++ )
		{
			data.m_random.getRandomVector11( pos );
			data.m_objects[i]->setPosition( pos );
		}
	}
	{
		for ( int i=0; i < MAX_OBJECTS; i++ )	{		data.m_objects[i]->check();	}
	}


	// add and check
	data.m_world->addPhantomBatch( phantoms.begin(), phantoms.getSize() );
	{
		for ( int i=0; i < MAX_OBJECTS; i++ )	{		data.m_objects[i]->check();	}
	}

	data.m_world->unlock();
}


int broadphaseBatchAddTest_main()
{
	// In the second test, we randomly batch add and remove objects, store the results
	// and eventually verify the results using requireSingleObject
	{
		BroadphaseBatchAddUnitTest2 data;
		for ( int i =0; i < 10; i++)
		{
			batchAddAndRemoveAndVerify(data);
		}
	}

	// using a test where we directly compare two broadphases for identity
	//  - One broadphase is always accessed through single add and remove
	//  - One broadphase is always accessed through batchadd and remove
	// This test only works if there is no ambiguity in the way the broadphase should work
	// So we have to make sure that we do not create identical values for the extends of 
	// 2 different objects
	{
		hkVector4 worldMin; worldMin.setAll3( 0.0f );
		hkVector4 worldMax; worldMax.setAll3( hkReal( MAX_ELEMS)*1.01f );
		BroadphaseBatchAddUnitTest data( worldMin, worldMax, 4 );
		initializeInitialBroadPhase( data );

		for (int i =0; i<10; i++)
		{
			removeAndReaddBatch( data );
		}
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(broadphaseBatchAddTest_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
