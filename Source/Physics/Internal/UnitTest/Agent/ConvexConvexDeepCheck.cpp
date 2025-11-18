/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
 // Large include

#include <Common/Base/Types/Physics/MotionState/hkMotionState.h>

#include <Physics/Internal/UnitTest/Agent/Gjk/hkpGjkConvexConvexAgent.h>

#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>


#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>


#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Collide/Agent/Collidable/hkpCdPoint.h>
#include <Physics/Collide/Agent/hkpCollisionInput.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpGskfAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpPredGskfAgent.h>

#include <Physics/Collide/Agent/Util/Null/hkpNullAgent.h>
#include <Physics/Collide/Agent/Query/hkpLinearCastCollisionInput.h>
#include <Physics/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Physics/Collide/Agent/hkpCollisionAgentConfig.h>

#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>

#include <Physics/Dynamics/Constraint/hkpConstraintOwner.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Dispatch/ContactMgr/hkpNullContactMgrFactory.h>

#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <Physics/Collide/Query/Collector/BodyPairCollector/hkpFlagCdBodyPairCollector.h>


#include <Physics/Utilities/Collide/hkpShapeGenerator.h>



const int TIMER_STRING_SIZE = 10000;
#define FILE_NAME "ConvexConvexStats.txt"


class EmptyContactCollector: public hkpCdPointCollector
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO, EmptyContactCollector);
		EmptyContactCollector(){ m_earlyOutDistance = 0.0f; }
	private:
		virtual void addCdPoint( const hkpCdPoint& cdPoint ){ }
};

class Checker: public hkpCdPointCollector
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO, Checker);

		hkVector4 m_hitNormal;
		hkVector4 m_hitPoint;
		hkReal m_distance;
		char errorString[1024];
		char *errorPtr;
		char* type;
		char* nativeType;
		int m_numHits;
		hkBool m_checkNormal;

		void reset()
		{
			m_checkNormal = true;
			m_numHits = 0;
			errorString[0] = 0;
			errorPtr = &errorString[0];
			m_hitNormal.setZero4();
			m_hitPoint.setZero4();
			m_distance = 0.0f;
		}

		void resetErrorString()
		{
			errorString[0] = 0;
			errorPtr = &errorString[0];
		}

		void addCdPoint( const hkpCdPoint& ev )
		{
			hkpCdPoint cdPoint = ev;
			const hkpCollidable* rootA = ev.m_cdBodyA.getRootCollidable();
			const hkpCollidable* rootB = ev.m_cdBodyB.getRootCollidable();


			//
			// Check normal
			//
			{
				if ( !ev.m_contact.getNormal().isNormalized3() )
				{
					hkReal len = ev.m_contact.getNormal().length3();
						hkString::sprintf( errorPtr, "Normal not normalized: length %s=%f    ",
							this->type,  len);
						errorPtr += hkString::strLen( errorPtr );
				}
			}

			//
			// Verify results by raycaster
			//
			{
				const hkReal longDist = hkMath::max2( 2.0f, cdPoint.m_contact.getDistance() * 1.5f );

				//
				// raycast A
				//
				hkBool hitA;
				hkVector4 hitPointA;hitPointA.setZero4();
				hkReal normalDotHitNormalA = 0.f;

				{
					const hkTransform& aToWorld = rootA->getTransform();
					hkVector4 hitPointinA;  hitPointinA.setTransformedInversePos( aToWorld, cdPoint.m_contact.getPosition() );
					hkVector4 hitNormalinA; hitNormalinA.setRotatedInverseDir(    aToWorld.getRotation(), cdPoint.m_contact.getNormal() );

					hkpShapeRayCastInput ray;
					ray.m_from.setAddMul4( hitPointinA, hitNormalinA, -longDist );
					ray.m_to.setAddMul4( hitPointinA, hitNormalinA,  longDist );

					hkpShapeRayCastOutput output;
					hitA = rootA->getShape()->castRay( ray, output );
					if ( hitA )
					{
						hkVector4 pos; pos.setInterpolate4( ray.m_from, ray.m_to, output.m_hitFraction );
						hitPointA.setTransformedPos( aToWorld, pos );
						normalDotHitNormalA = hitNormalinA.dot3( output.m_normal );
					}
				}

				//
				// raycast B
				//
				hkBool hitB;
				hkVector4 hitPointB; hitPointB.setZero4();
				hkReal normalDotHitNormalB = 0.f;
				{
					const hkTransform& bToWorld = rootB->getTransform();
					hkVector4 hitPointinB;  hitPointinB.setTransformedInversePos( bToWorld, cdPoint.m_contact.getPosition() );
					hkVector4 hitNormalinB; hitNormalinB.setRotatedInverseDir(    bToWorld.getRotation(), cdPoint.m_contact.getNormal() );

					
					hkpShapeRayCastInput ray;
					ray.m_from.setAddMul4( hitPointinB, hitNormalinB, longDist );
					ray.m_to  .setAddMul4( hitPointinB, hitNormalinB, -longDist );

					hkpShapeRayCastOutput output;
					hitB = rootB->getShape()->castRay( ray , output );
					if ( hitB )
					{
						hkVector4 pos; pos.setInterpolate4( ray.m_from, ray.m_to, output.m_hitFraction );
						hitPointB.setTransformedPos( bToWorld, pos );
						normalDotHitNormalB = hitNormalinB.dot3( output.m_normal );
					}
				}

				if( !hitB || !hitA )
				{
					// report error, however do not return
					//hkString::sprintf( errorPtr, "%s Raycast did not hit, dist = %f: hitA %i, hitB %i", this->type, cdPoint.m_contact.getDistance(), hitA, hitB  );
					//errorPtr += hkString::strLen( errorPtr );
				}
				else
				{
					//
					//	Check distance
					//
					hkVector4 delta; delta.setSub4( hitPointB, hitPointA );
					hkReal rayDist = delta.dot3(cdPoint.m_contact.getNormal());
					rayDist = - rayDist;

					//
					//	Correct by radius
					//
					if ( rootA->getShape()->getType() != HK_SHAPE_SPHERE && rootA->getShape()->getType() != HK_SHAPE_CAPSULE)
					{
						rayDist -= static_cast<const hkpConvexShape*>(rootA->getShape())->getRadius();
					}
					if ( rootB->getShape()->getType() != HK_SHAPE_SPHERE  && rootB->getShape()->getType() != HK_SHAPE_CAPSULE )
					{
						rayDist -= static_cast<const hkpConvexShape*>(rootB->getShape())->getRadius();
					}

					const hkReal distance = cdPoint.m_contact.getDistance();
					const hkReal errorScale = 1.0f / hkMath::fabs(normalDotHitNormalA) + 1.0f / hkMath::fabs(normalDotHitNormalB);

					if ( !hkMath::equal( rayDist, distance, errorScale * 0.001f ) )
					{
						hkString::sprintf( errorPtr, "Raycast reports other distance: Distance %s=%f  Raycast=%f   ->delta=%f    ",
							this->type, distance, rayDist, distance - rayDist );
						errorPtr += hkString::strLen( errorPtr );
					}
				}

			}

			//
			// If first call, initialize
			//
			if ( !m_numHits )
			{
				m_numHits = 1;
				m_hitNormal = cdPoint.m_contact.getNormal();
				m_hitPoint = cdPoint.m_contact.getPosition();
				m_distance = cdPoint.m_contact.getDistance();
				return;
			}
			else
			{
				m_numHits ++;
			}

			//
			//	Check distance: allow bigger error for penetrating distances
			//
			const hkReal maxDistanceError = (m_distance>0)? 0.001f : 0.002f;
			if ( !hkMath::equal(m_distance, cdPoint.m_contact.getDistance(), maxDistanceError ) )
			{
				hkString::sprintf( errorPtr, "Distance  %s=%f  %s=%f   Delta=%f    ",
					this->nativeType, m_distance, this->type, cdPoint.m_contact.getDistance(), m_distance - cdPoint.m_contact.getDistance() );
				errorPtr += hkString::strLen( errorPtr );
			}

			//
			//	Check normal
			//
			if (m_checkNormal)
			{
				if ( ! m_hitNormal.equals3(cdPoint.m_contact.getNormal(), 0.02f ) )
				{
					const hkVector4& n = cdPoint.m_contact.getNormal(); 
					hkString::sprintf( errorPtr, "Normal: %s=(%f,%f,%f,d:%f)  %s=(%f,%f,%f,d:%f)       ",
						this->nativeType,	m_hitNormal(0),m_hitNormal(1),m_hitNormal(2), m_distance,
						this->type, 		n(0), n(1), n(2),		cdPoint.m_contact.getDistance() );
					errorPtr += hkString::strLen( errorPtr );
				}
			}

			//
			// check hit point;
			//
			if (0)
			{
				if ( ! m_hitPoint.equals3(cdPoint.m_contact.getPosition(), 0.01f ) )
				{
					hkString::sprintf( errorPtr, "m_hitPoint differs (%f,%f,%f) != (%f,%f,%f) ",
						m_hitPoint(0),m_hitPoint(1),m_hitPoint(2),
						cdPoint.m_contact.getPosition()(0),cdPoint.m_contact.getPosition()(1),cdPoint.m_contact.getPosition()(2) );
					errorPtr += hkString::strLen( errorPtr );
					return;
				}
			}
			return;
		}
};


class ConvexConvexCheck 
{

	public:
		ConvexConvexCheck();

		~ConvexConvexCheck()
		{
			m_environment.m_dispatcher->removeReference();
		}

	public:
		void check();

	protected:
		void flushDataCash();
		void flushInstructionCache();

		void beginTimer( const char* prefix, const char* name );


			/// Time a single shape combination
		void timeSingleCombination( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB );

			/// check a single shape combination
		void checkSingleCombination( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB, hkBool nativeAgentAvailable );

			/// check a single shape cast
		void checkSingleShapeCast( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB, hkBool nativeAgentAvailable );

		hkBool isTestEnabled( int testCounter );

	private:
		hkPseudoRandomGenerator m_rand;
		hkpConvexShape* shapesA[ hkpShapeGenerator::SHAPE_MAX ];
		hkpConvexShape* shapesB[ hkpShapeGenerator::SHAPE_MAX ];

		/// a static variable to hold all our timer names. It has to be static, as the timers get examined after the game is deleted
		static char m_timerStringBuffer[TIMER_STRING_SIZE];
		char *m_buffer;

		hkpCollisionAgentConfig m_config;
		hkpLinearCastCollisionInput m_environment;
		int						m_testCounter;
		hkArray<int>			m_disabledTests;
};

ConvexConvexCheck::ConvexConvexCheck() : m_rand(2)
{
	m_buffer = &m_timerStringBuffer[0];
	hkpContactMgrFactory* defaultCmFactory = new hkpNullContactMgrFactory( );
	m_environment.m_dispatcher = new hkpCollisionDispatcher(hkpNullAgent::createNullAgent, defaultCmFactory);
	m_environment.m_createPredictiveAgents = false;
	defaultCmFactory->removeReference();

	m_testCounter = 0;

	m_environment.setTolerance( 100.0f );
	m_environment.m_config = & m_config;

	m_disabledTests.pushBack(51461);	// perfect penetration, so normal is random
	m_disabledTests.pushBack(67908);	// GJK having slightly rotated normal, means this is a GJK failure case
	m_disabledTests.pushBack(111474);	// GJK having slightly rotated normal, means this is a GJK failure case

	m_disabledTests.pushBack( 190765 ); // GJK calculates wrong normal
	m_disabledTests.pushBack( 193769 ); // a deeply penetrating object has to solutions for GSK normal

	hkpAgentRegisterUtil::registerAllAgents( m_environment.m_dispatcher );
}

hkBool ConvexConvexCheck::isTestEnabled( int test )
{
	return m_disabledTests.indexOf( test ) < 0;
}


void ConvexConvexCheck::flushDataCash()
{
#ifdef HK_PS2
	const int cacheSize = 32000;
#else
	const int cacheSize = 512000;
#endif
	hkLocalArray<char> bufferStore(cacheSize+1);
	char* buffer = bufferStore.begin();
	hkString::memCpy( buffer, buffer+1, cacheSize );
	//
	// flush in timers
	//
	if ( hkMonitorStream::getInstance().memoryAvailable() )
	{
		 char *h = hkMonitorStream::getInstance().getEnd();
		 static char x;
		 x = h[0];
	}
}

void ConvexConvexCheck::flushInstructionCache()
{
	//
	// use qhull + mopp to flush instruciton cache
	// ( at least on PS2 that should kill it )
	//
	float x[21] = { 1,2,3,7,3,7,34,24,3,7,3,26,78,4,45,4,34,56,23,12,99 };

	hkLocalArray<hkVector4> planeEquations(20);
	hkGeometry geom;
	hkStridedVertices stridedVerts;
	{
		{
			stridedVerts.m_numVertices = 8;
			stridedVerts.m_striding = sizeof(float);
			stridedVerts.m_vertices = x;
		}
		// Usually plane equations should be precomputed off line. We disable the performance warning
		bool wasEnabled = hkError::getInstance().isEnabled(0x34df5494);
		hkError::getInstance().setEnabled(0x34df5494, false); //hkpGeometryUtility.cpp:26
		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
		hkError::getInstance().setEnabled(0x34df5494, wasEnabled); //hkpGeometryUtility.cpp:26

		{
			stridedVerts.m_numVertices = 8;
			stridedVerts.m_striding = sizeof(float);
			stridedVerts.m_vertices = x;
		}
	}
	hkpConvexVerticesShape cv(stridedVerts, planeEquations);
	
	hkpShape* sa[2]; sa[0] = &cv; sa[1] = &cv;
	hkpListShape ls( sa,2 );

	hkpMoppCompilerInput mci;
	mci.m_enableInterleavedBuilding = false;
	mci.m_enableChunkSubdivision = true;
	// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
	bool wasEnabled = hkError::getInstance().isEnabled(0x6e8d163b); // hkpMoppUtility.cpp:18
	hkError::getInstance().setEnabled(0x6e8d163b, false);
	hkpMoppCode* code = hkpMoppUtility::buildCode( &ls, mci );
	hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled);
	code->removeReference();
}

void ConvexConvexCheck::beginTimer( const char* a, const char* b )
{
	hkMonitorStream& stream = hkMonitorStream::getInstance();
	if ( stream.memoryAvailable() )		
	{
		hkString::sprintf( m_buffer, "Tt%s%s", a, b);

		 hkMonitorStream::TimerCommand* h = reinterpret_cast<hkMonitorStream::TimerCommand*>(stream.getEnd());
		 h->m_commandAndMonitor = m_buffer;
		 m_buffer += hkString::strLen( m_buffer ) + 1;
		 HK_ASSERT(0x678c568b,  m_buffer - m_timerStringBuffer < TIMER_STRING_SIZE );
		 h->setTime();						
		 stream.setEnd( (char*)(h+1) );
	}
}

void ConvexConvexCheck::timeSingleCombination( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB )
{
	hkMotionState motionA;
	hkMotionState motionB;

	hkpCollidable collA( shapesA[typeA], &motionA, 0 );
	hkpCollidable collB( shapesB[typeB], &motionB, 0 );

	{
		motionA.getTransform().setIdentity();
		motionB.getTransform().setIdentity();

		m_rand.setSeed( 100 );
		m_rand.getRandomRotation( motionA.getTransform().getRotation() );
		m_rand.getRandomRotation( motionB.getTransform().getRotation() );

		motionB.getTransform().getTranslation().set( 10,0,0);
	}

	EmptyContactCollector emptyResult;

	flushInstructionCache();
	flushDataCash();

	beginTimer( hkpShapeGenerator::getShapeTypeName( typeA), hkpShapeGenerator::getShapeTypeName( typeB ) );
	{

		hkpCollisionAgent* nativeA;
		hkpCollisionAgent* nativeB;
		//
		//	Check the time it takes to create an agent, do it twice to see the effect of
		//  instruction cache misses
		//
		{
			HK_TIMER_BEGIN( "Create AgentA", HK_NULL );
			nativeA = m_environment.m_dispatcher->getNewCollisionAgent( collA, collB, m_environment, HK_NULL );
			HK_TIMER_END();

			HK_TIMER_BEGIN( "Create AgentB", HK_NULL );
			nativeB = m_environment.m_dispatcher->getNewCollisionAgent( collA, collB, m_environment, HK_NULL );
			HK_TIMER_END();
		}

		{
			hkVector4 path;
			path.setSub4( collA.getTransform().getTranslation(), collB.getTransform().getTranslation() );
			m_environment.setPathAndTolerance( path, 0.1f );
		}

		{
			HK_TIMER_BEGIN( "FlushCaches", HK_NULL );
			flushInstructionCache();
			flushDataCash();
			HK_TIMER_END();
		}


		//
		// Check the first call, no hit's should be reported as objects are too far away
		//
		//
		{
			HK_TIMER_BEGIN( "LinearCast NoHit AgA", HK_NULL );
			nativeA->linearCast( collA, collB, m_environment, emptyResult, HK_NULL );
			HK_TIMER_END();

			HK_TIMER_BEGIN( "LinearCast NoHit AgB", HK_NULL );
			nativeB->linearCast( collA, collB, m_environment, emptyResult, HK_NULL );
			HK_TIMER_END();
		}

		//
		// Check the second call (to see frame coherency)
		//
		{
			HK_TIMER_BEGIN( "Repeat NoHit AgA", HK_NULL );
			nativeA->linearCast( collA, collB, m_environment, emptyResult, HK_NULL );
			HK_TIMER_END();

			HK_TIMER_BEGIN( "Repeat NoHit AgB", HK_NULL );
			nativeB->linearCast( collA, collB, m_environment, emptyResult, HK_NULL );
			HK_TIMER_END();
		}

		//
		//	Check the hit cost for the start point collecter
		//
		{
			m_environment.setTolerance(100.0f);
			HK_TIMER_BEGIN( "LinearCast StartHit AgA", HK_NULL );
			nativeA->linearCast( collA, collB, m_environment, emptyResult, &emptyResult );
			HK_TIMER_END();

			HK_TIMER_BEGIN( "LinearCast StartHit AgB", HK_NULL );
			nativeB->linearCast( collA, collB, m_environment, emptyResult, &emptyResult );
			HK_TIMER_END();
		}

		//
		//	Check the cast cost
		//
		{
			hkpClosestCdPointCollector minDist;
			
			hkVector4 path;
			path.setSub4( collB.getTransform().getTranslation(), collA.getTransform().getTranslation() );

			m_environment.setPathAndTolerance( path, 100.0f );

			HK_TIMER_BEGIN( "LinearCast FullHit AgentA", HK_NULL );
			nativeA->linearCast( collA, collB, m_environment, minDist, HK_NULL );
			HK_TIMER_END();

			minDist.reset();

			HK_TIMER_BEGIN( "LinearCast FullHit AgentB", HK_NULL );
			nativeB->linearCast( collA, collB, m_environment, minDist, HK_NULL );
			HK_TIMER_END();
		}

		//
		//	Check the penetration cost (first iteration
		//
		{
			motionB.getTransform().getTranslation().set( 0,0,0);

			HK_TIMER_BEGIN( "Penetrating AgA", HK_NULL );
			nativeA->linearCast( collA, collB, m_environment, emptyResult, &emptyResult );
			HK_TIMER_END();

			HK_TIMER_BEGIN( "Penetrating AgB", HK_NULL );
			nativeB->linearCast( collA, collB, m_environment, emptyResult, &emptyResult );
			HK_TIMER_END();
		}




		//
		//	Check the time it takes to delete an agent, do it twice to see the effect of
		//  instruction cache misses
		//
		{
			hkpConstraintOwner constraintOwner;
			HK_TIMER_BEGIN( "Delete AgA", HK_NULL );
			nativeA->cleanup(constraintOwner);
			HK_TIMER_END();

			HK_TIMER_BEGIN( "Delete AgB", HK_NULL );
			nativeB->cleanup(constraintOwner);
			HK_TIMER_END();
		}
	}
	HK_TIMER_END();
}


void ConvexConvexCheck::checkSingleCombination( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB, hkBool nativeAgentAvailable )
{
	hkMotionState motionA;
	hkMotionState motionB;

	hkpCollidable collA( shapesA[typeA], &motionA, 0 );
	hkpCollidable collB( shapesB[typeB], &motionB, 0 );

 	collA.setOwner( (void*)hkAddByteOffset(&collA, 1) );
 	collB.setOwner( (void*)hkAddByteOffset(&collA, 2) );

	{
		motionA.getTransform().setIdentity();
		motionB.getTransform().setIdentity();

		m_rand.setSeed( 100 );
		m_rand.getRandomRotation( motionA.getTransform().getRotation() );
		m_rand.getRandomRotation( motionB.getTransform().getRotation() );

		m_rand.setSeed( 100 );
	}

	{
		hkpCollisionAgent* nativeA;
		hkpCollisionAgent* gskAgent;
		hkpCollisionAgent* gjkAgent;
		//
		//	Create the agents
		//
		{
			if ( nativeAgentAvailable )
			{
				gjkAgent = hkpGjkConvexConvexAgent::createConvexConvexAgent( collA, collB, m_environment, HK_NULL);
				gskAgent = hkpGskfAgent::createGskfAgent( collA, collB, m_environment, HK_NULL );
				nativeA  = m_environment.m_dispatcher->getNewCollisionAgent( collA, collB, m_environment, HK_NULL );
			}
			else
			{
				gjkAgent = hkpGjkConvexConvexAgent::createConvexConvexAgent( collA, collB, m_environment, HK_NULL);
				nativeA = hkpGskfAgent::createGskfAgent( collA, collB, m_environment, HK_NULL );
				gskAgent = HK_NULL;
			}
		}

		//
		//	Check the unrotated situation
		//
		{
			Checker checker;
			m_environment.setTolerance( 100.0f );

			const char* stypeA = hkpShapeGenerator::getShapeTypeName(typeA);
			const char* stypeB = hkpShapeGenerator::getShapeTypeName(typeB);

			for ( float x = -2.25f; x <= 2.25f; x += 0.25f )
			{
				for ( float y = -2.25f; y <= 2.25f; y += 0.25f )
				{
					for ( float z = -2.25f; z <= 2.25f; z += 0.25f )
					{
						checker.reset();
						motionB.getTransform().getTranslation().set( x,y,z);

						if ( !isTestEnabled( m_testCounter) )
						{
							continue;
						}


						//
						//	Run the native agent
						//
						if ( nativeAgentAvailable )
						{
							checker.nativeType = "NATIVE";
							checker.type = "NATIVE";
						}
						else
						{
							checker.nativeType = "GSK";
							checker.type = "GSK";
						}
						{
							nativeA->getClosestPoints ( collA, collB, m_environment, checker );
							if ( checker.m_numHits != 1 )
							{
								HK_TEST2( 0, stypeA << " vs " << stypeB << "(#" << m_testCounter <<"): missing hits in Native agent" );
								checker.resetErrorString();
							}
						}



						//
						//	Do some special early outs
						//
						{
							// box box collision return the wrong distance for non penetrating situations
							if ( typeA == hkpShapeGenerator::BOX && typeB == hkpShapeGenerator::BOX ) //&& checker.m_distance > 0.f)
							{
								continue;
							}

							/* do not check the thin triangles yet, too many errors
							if ( typeA == hkpShapeGenerator::THIN_TRIANGLE || typeB == hkpShapeGenerator::THIN_TRIANGLE ) 
							{
								continue;
							}
							*/

							hkBool isCenter = x ==0.0f && y == 0.0f && z == 0.0f;

							if (isCenter)
							{
								checker.m_checkNormal = false;
							}

						}

						//
						//	Check consistency with are penetrating
						//
						{
							hkpFlagCdBodyPairCollector getPenetrations;
							nativeA->getPenetrations( collA, collB, m_environment, getPenetrations );
							bool hasHit = getPenetrations.hasHit();
							bool shouldPenetrate = ( checker.m_distance < 0 );
							if ( hasHit != shouldPenetrate )
							{
								char errorString[256];
								hkString::sprintf(errorString, "getPenetrations() works incorrectly: returned %i distance %f", hasHit, checker.m_distance );
								HK_TEST2( 0, stypeA << " vs " << stypeB << "(" << m_testCounter <<"): " << errorString);			
							}
						}

						//
						//	Check against GJK and GSK
						//
						const hkBool temporarilyExcludeFromUnitTest = true;
						if (!temporarilyExcludeFromUnitTest && gjkAgent)
						{
							checker.type = "GJK"; gjkAgent->getClosestPoints( collA, collB, m_environment, checker );
							if ( checker.errorString[0] )
							{
								HK_TEST2( 0, stypeA << " vs " << stypeB << "(" << m_testCounter <<"): " << checker.errorString);			
								checker.resetErrorString();
							}
						}

						if ( gskAgent )
						{
							checker.type = "GSK"; gskAgent->getClosestPoints( collA, collB, m_environment, checker );

							if ( checker.errorString[0] )
							{
								HK_TEST2( 0, stypeA << " vs " << stypeB << "(" << m_testCounter <<"): " << checker.errorString);			
								checker.resetErrorString();
							}
						}

						//
						//	Check against the static version
						//
						{

							checker.type = "STATIC"; 
							m_environment.m_dispatcher->getGetClosestPointsFunc( collA.getShape()->getType(), collB.getShape()->getType()) ( collA, collB, m_environment, checker );

							if ( checker.errorString[0] )
							{
								HK_TEST2( 0, stypeA << " vs " << stypeB << "(" << m_testCounter <<"): " << checker.errorString);
								checker.resetErrorString();
							}
						}
					}
				}
			}
		}

		//
		//	Delete the agents
		//
		{
			hkpConstraintOwner constraintOwner;
			if ( gjkAgent) gjkAgent->cleanup(constraintOwner);
			if ( gskAgent) gskAgent->cleanup(constraintOwner);
			if ( nativeA) nativeA->cleanup(constraintOwner);
		}
	}
}



void ConvexConvexCheck::checkSingleShapeCast( hkpShapeGenerator::ShapeType typeA, hkpShapeGenerator::ShapeType typeB, hkBool nativeAgentAvailable )
{
	const char *stypeA = hkpShapeGenerator::getShapeTypeName(typeA);
	const char *stypeB = hkpShapeGenerator::getShapeTypeName(typeB);

	const char* agentName = (nativeAgentAvailable)? "Native" : "GSK";
#define TEST_PREFIX agentName << " : " << stypeA << " vs " << stypeB << "(" << counter2 <<"): "
	hkMotionState motionA;
	hkMotionState motionB;

	hkpCollidable collA( shapesA[typeA], &motionA, 0 );
	hkpCollidable collB( shapesB[typeB], &motionB, 0 );
 	collA.setOwner( (void*)hkAddByteOffset(&collA, 1) );
 	collB.setOwner( (void*)hkAddByteOffset(&collA, 2) );


	{
		motionA.getTransform().setIdentity();
		motionB.getTransform().setIdentity();

		m_rand.setSeed( 100 );
		m_rand.getRandomRotation( motionA.getTransform().getRotation() );
		m_rand.getRandomRotation( motionB.getTransform().getRotation() );

		m_rand.setSeed( 100 );
	}


	{
		//
		//	Create the agents
		//
		hkpCollisionAgent* nativeA = m_environment.m_dispatcher->getNewCollisionAgent( collA, collB, m_environment, HK_NULL );


		//
		//	Check the  situation
		//
		{
			hkpClosestCdPointCollector startCollector;
			hkpClosestCdPointCollector castCollector;

			m_environment.setTolerance( 100.0f );
			m_environment.m_config->m_iterativeLinearCastMaxIterations = 100;
			m_environment.m_config->m_iterativeLinearCastEarlyOutDistance = .0001f;


			for ( float x = -1.0f; x <= 1.0f; x += 0.25f )
			{
				for ( float y = -1.0; y <= 1.0f; y += 0.25f )
				{
					for ( float z = -1.0; z <= 1.0f; z += 0.25f )
					{
						hkVector4 from; from.set( x,y,z  );

						hkVector4 to; 
						m_rand.getRandomVector11( to );

						motionA.getTransform().setTranslation( from );

						static int counter2 = 0;
						if ( ++counter2 == 24080)
						{
							counter2 = counter2;
						}

						startCollector.reset();
						castCollector.reset();

						
						hkVector4 path; path.setSub4( to, from );
						m_environment.setPathAndTolerance( path, 100.0f );

						nativeA->linearCast( collA, collB, m_environment, castCollector, &startCollector );

						if ( typeA == hkpShapeGenerator::BOX && typeB == hkpShapeGenerator::BOX &&
							 startCollector.hasHit() && startCollector.getHit().m_contact.getDistance() < 0)
						{
							// do not check penetrating box box situations
							continue;
						}


						//
						//	Check for penetrating start points returning only zero cast distances
						//
						{
							if ( startCollector.hasHit() && startCollector.getHit().m_contact.getDistance() < 0.0f )
							{
								if ( castCollector.hasHit() && castCollector.getHit().m_contact.getDistance() != 0.0f )
								{
									HK_TEST2( 0, TEST_PREFIX << "Penetrating object has a cast distance != 0" );			
								}
							}
						}

						//
						//	Check the hit correctness
						//
						if ( castCollector.hasHit() )
						{
							const hkpRootCdPoint& castHit = castCollector.getHit();
							HK_TEST( castHit.m_contact.getDistance() >= 0.0f );
							HK_TEST( castHit.m_contact.getDistance() <= 1.0f );
							hkVector4 hitPosition; hitPosition.setInterpolate4( from, to , castHit.m_contact.getDistance() );

							motionA.getTransform().setTranslation( hitPosition );

							hkpClosestCdPointCollector checker;
							nativeA->getClosestPoints( collA, collB, m_environment, checker );

							if ( !checker.hasHit() )
							{
								HK_TEST2( 0, TEST_PREFIX << "shape caster returned cast hit, which cannot be verified" );
							}
							else
							{
								hkReal distanceAtHit = checker.getHit().m_contact.getDistance();
								const hkReal maxDist = (nativeAgentAvailable)? m_environment.m_config->m_iterativeLinearCastEarlyOutDistance * 2.0f : 0.012f;

								if ( hkMath::fabs( distanceAtHit ) > maxDist )
								{
									if ( startCollector.hasHit() && startCollector.getHit().m_contact.getDistance() < 0.0f )
									{
										// ok, we started with penetration
									}
									else
									{
										HK_TEST2( 0, TEST_PREFIX << "shape caster returned cast hit at distance: " << distanceAtHit );
									}
								}

							}
						}
					}
				}
			}
		}

		//
		//	Delete the agents
		//
		hkpConstraintOwner constraintOwner;
		nativeA->cleanup(constraintOwner);
	}
}



void ConvexConvexCheck::check()
{
	HK_TIMER_BEGIN("CheckAllConvexCombinations", HK_NULL);
	hkpCollisionDispatcher* dispatcher = m_environment.m_dispatcher;

	hkpCollisionDispatcher::CreateFunc gjkCreate = hkpGjkConvexConvexAgent::createConvexConvexAgent;
	hkpCollisionDispatcher::CreateFunc gskCreate = hkpPredGskfAgent::createPredGskfAgent;

	//
	// create all shapes
	//
	{
		HK_TIMER_BEGIN("Create Shapes", HK_NULL);

		for (int a = hkpShapeGenerator::SPHERE; a < hkpShapeGenerator::SHAPE_MAX; a++ )
		{
			hkVector4 extents; extents.set( 1,1.1f,1.3f );
			beginTimer( "Create: ", hkpShapeGenerator::getShapeTypeName( hkpShapeGenerator::ShapeType(a) ) );
			shapesA[a] = hkpShapeGenerator::createConvexShape( extents, hkpShapeGenerator::ShapeType(a), &m_rand );
			HK_TIMER_END();

			beginTimer( "Create: ", hkpShapeGenerator::getShapeTypeName( hkpShapeGenerator::ShapeType(a) ) );
			shapesB[a] = hkpShapeGenerator::createConvexShape( extents, hkpShapeGenerator::ShapeType(a), &m_rand );
			HK_TIMER_END();
		}
		HK_TIMER_END();
	}

	//
	// time all combinations
	//
	{
		for (int a = hkpShapeGenerator::SPHERE; a < hkpShapeGenerator::SHAPE_MAX; a++ )
		{
			for (int b = hkpShapeGenerator::SPHERE; b <= a; b++ )
			{
				for (int s = 0; s < 2; s++ )
				{
					hkpCollisionDispatcher::CreateFunc f = dispatcher->getCollisionAgentCreationFunction( shapesA[a]->getType(), shapesA[b]->getType(), hkpCollisionDispatcher::IS_NOT_PREDICTIVE );
					if ( f == HK_NULL || f == gjkCreate || f == gskCreate )
					{
						// if convex, test both gjk and gsk
						HK_MONITOR_PUSH_DIR("GJK");
						//dispatcher->setCollisionAgentCreationFunctionAt( gjkCreate, HK_SHAPE_CONVEX, HK_SHAPE_CONVEX );
						timeSingleCombination( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b) );
						HK_MONITOR_POP_DIR();

						HK_MONITOR_PUSH_DIR("GSK");
						//dispatcher->setCollisionAgentCreationFunctionAt( gskCreate, HK_SHAPE_CONVEX, HK_SHAPE_CONVEX );
						timeSingleCombination( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b) );
						HK_MONITOR_POP_DIR();
					}
					else
					{
						HK_MONITOR_PUSH_DIR("Native");
						timeSingleCombination( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b) );
						HK_MONITOR_POP_DIR();
					}

					// swap a and b
					int h = a; a = b; b = h;
					if ( a == b )
					{
						break;
					}
				}
			}
		}
	}



	//
	// check all combinations
	//
	{
		//
		//	disable timers
		//
		hkMonitorStream& stream = hkMonitorStream::getInstance();
		char* oldTimerMem = stream.getEnd();
		stream.setEnd( stream.getCapacity() );

		//
		//	loop over all combinations
		//
		for (int a = hkpShapeGenerator::SPHERE; a < hkpShapeGenerator::SHAPE_MAX; a++ )
		{
			for (int b = hkpShapeGenerator::SPHERE; b < hkpShapeGenerator::SHAPE_MAX; b++ )
			{
				hkpCollisionDispatcher::CollisionAgentCreationFunction f = m_environment.m_dispatcher->getCollisionAgentCreationFunction( shapesA[a]->getType(), shapesA[b]->getType(), hkpCollisionDispatcher::IS_NOT_PREDICTIVE );
				if ( f == HK_NULL || f == gjkCreate || f == gskCreate )
				{
					// if convex, test both gjk and gsk
					checkSingleCombination( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b), false );
					checkSingleShapeCast( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b), false );
				}
				else
				{
					checkSingleCombination( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b), true );
					checkSingleShapeCast( hkpShapeGenerator::ShapeType(a), hkpShapeGenerator::ShapeType(b), true );
				}

			}
		}

		//
		// enable timers
		// 
		stream.setEnd( oldTimerMem );
	}
	//
	//	free all shapes
	//
	{
		HK_TIMER_BEGIN("Delete Shapes", HK_NULL);
		for (int a = hkpShapeGenerator::SPHERE; a < hkpShapeGenerator::SHAPE_MAX; a++ )
		{
			beginTimer( "Delete: ", hkpShapeGenerator::getShapeTypeName( hkpShapeGenerator::ShapeType(a) ) );
				shapesA[a]->removeReference();
			HK_TIMER_END();
			beginTimer( "Delete: ", hkpShapeGenerator::getShapeTypeName( hkpShapeGenerator::ShapeType(a) ) );
				shapesB[a]->removeReference();
			HK_TIMER_END();
		}
		HK_TIMER_END();
	}
	HK_TIMER_END();
}

char ConvexConvexCheck::m_timerStringBuffer[TIMER_STRING_SIZE];


	// Check various configurations, both penetrating and non-penetrating.
int ConvexConvexDeepCheck()
{
	ConvexConvexCheck check;

#ifdef HK_PS2 
	{
		check.check();
	}
#else
	if (0)
	{
		hkMonitorStreamAnalyzer streamUtility( 10000000 );
		hkMonitorStream& stream = hkMonitorStream::getInstance();
		stream.resize( 2000000 );	// 2 meg for timer info per frame
		stream.reset();

		check.check();

		hkMonitorStreamFrameInfo frameInfo;

		frameInfo.m_timerFactor0 = 1e6f / hkReal(hkStopwatch::getTicksPerSecond());
		frameInfo.m_heading = FILE_NAME "   Timers in usecs ";

		streamUtility.captureFrameDetails( stream.getStart(), stream.getEnd(), frameInfo);

		hkOstream ostr(FILE_NAME);
		streamUtility.writeStatistics( ostr );
		streamUtility.reset();
	}
#endif

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(ConvexConvexDeepCheck, "Slow", "Physics/Test/UnitTest/Internal/", __FILE__     );


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
