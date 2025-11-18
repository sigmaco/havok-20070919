/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


//
// includes
//
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshShape.h>

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>


//
// definitions for the hkpMeshShape
//
#define NUM_VERTICES 4
#define NUM_TRIANGLES 2
#define NUM_DEGENERATE_TRIANGLES 2
#define WRAP_IN_MOPP true


//
// createMeshShape
//
hkpShape* createMeshShape( hkVector4* vertices, hkUint16 numVertices, hkUint16* indices, hkUint16 numIndices )
{
	// create vertices
	vertices[0].set( 1.0f, 0.0f, 1.0f );
	vertices[1].set(-1.0f, 0.0f, 1.0f );
	vertices[2].set( 1.0f, 0.0f,-1.0f );
	vertices[3].set(-1.0f, 0.0f,-1.0f );

	// create the first non-degenerate triangle (0,1,2)
	indices[0] = 0;	
	indices[1] = 1;	
	indices[2] = 2;	

	// create a degenerate triangle (1,2,2)
	indices[3] = 2;	
	
	// create a degenerate triangle (2,2,1)
	indices[4] = 1;

	// create the second non-degenerate triangle (2,1,3)
	indices[5] = 3;	
	
	// create shapes
	hkpMeshShape* meshShape = new hkpMeshShape();
	{
		hkVector4 tmp; tmp.set(20.0f, 20.0f, 20.0f);
		meshShape->setScaling( tmp );
	}
	{
		hkpMeshShape::Subpart part;

		part.m_vertexBase = &(vertices[0](0));
		part.m_vertexStriding = sizeof(hkVector4);
		part.m_numVertices = NUM_VERTICES;

		part.m_indexBase = indices;
		part.m_indexStriding = sizeof( hkUint16 );
		part.m_numTriangles = NUM_TRIANGLES + NUM_DEGENERATE_TRIANGLES;
		part.m_stridingType = hkpMeshShape::INDICES_INT16;

		meshShape->addSubpart( part );
	}

	if ( WRAP_IN_MOPP )
	{		
		
		
		hkpMoppCompilerInput mci;

		// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
		bool wasEnabled = hkError::getInstance().isEnabled(0x6e8d163b); 
		hkError::getInstance().setEnabled(0x6e8d163b, false); // hkpMoppUtility.cpp:18
		hkpMoppCode* code = hkpMoppUtility::buildCode( meshShape , mci);
		hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled);

		

		hkpMoppBvTreeShape* moppShape = new hkpMoppBvTreeShape(meshShape, code);
		code->removeReference();
		meshShape->removeReference();

		return moppShape;
	}
	else
	{
		return meshShape;
	}
}


//
// hkpMeshShape degenerate triangle test
//
int hkMeshShape_degenerate_test()
{
	hkpWorld::IgnoreForceMultithreadedSimulation ignoreForceMultithreaded;

	//
	// Create the world
	//
	hkpWorldCinfo info;
	info.setupSolverInfo( hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM ); 
	info.setBroadPhaseWorldSize( 1000.0f );
	hkpWorld* world = new hkpWorld( info );
	world->lock();

	//
	// Register the agents
	//
	{
		hkpAgentRegisterUtil::registerAllAgents(world->getCollisionDispatcher() );
	}

	//
	// Create the Mesh Shape with the degenerate triangles in it
	//
	const hkUint16 numVertices = NUM_VERTICES;
	hkVector4	vertices[numVertices];
	
	const hkUint16 numIndices = NUM_TRIANGLES + NUM_DEGENERATE_TRIANGLES + 2;
	hkUint16	indices[numIndices];
	{
		hkpRigidBodyCinfo groundInfo;
		groundInfo.m_shape = createMeshShape( vertices, NUM_VERTICES, indices, numIndices );
		groundInfo.m_position.set( 0.0f, -2.0f, 0.0f );
		groundInfo.m_motionType = hkpMotion::MOTION_FIXED;
		hkpRigidBody* groundbody = new hkpRigidBody( groundInfo );
		world->addEntity(groundbody);
		groundbody->removeReference();
		groundInfo.m_shape->removeReference();
	}

    //
	// Create the moving objects
	//
	
	// Box shape (shared between all 10 dynamic boxes)
	hkVector4 boxSize; boxSize.set( 1.0f ,1.0f ,1.0f );
	hkpBoxShape* boxShape = new hkpBoxShape( boxSize , 0 );

	// Sphere shape (shared between all 10 dynamic spheres)
	hkpSphereShape* sphereShape = new hkpSphereShape( 1.0f );
	
	for ( unsigned int i = 0; i < 20; i++ )
	{
		// Compute the box inertia tensor
		hkpMassProperties massProperties;
		hkpInertiaTensorComputer::computeBoxVolumeMassProperties( boxSize, 1.0f, massProperties );

		// Set up the construction info parameters for the box
		hkpRigidBodyCinfo rinfo;

		if ( i % 2 )
		{
			rinfo.m_shape = boxShape;
		}
		else
		{
			rinfo.m_shape = sphereShape;
		}

		rinfo.m_mass  = 1.0f;
		rinfo.m_inertiaTensor = massProperties.m_inertiaTensor;
		rinfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

		rinfo.m_position.set( (hkReal)i, 10.0f * (hkReal)i, (hkReal)i );
		
		// Create a box
		hkpRigidBody* box = new hkpRigidBody(rinfo);
		world->addEntity(box);
		box->removeReference();
	}

	//
	// Remove references from shapes
	//
	boxShape->removeReference();
	sphereShape->removeReference();

	world->unlock();

	//
	// step the world for 5 seconds
	//
	for ( int j = 0; j < ( 60 * 5 ); j++ )
	{
		world->stepDeltaTime( 0.0167f );
	}

	//
	// add a dummy test for test output display in demo framework
	// (the actualy test is that it does not assert)
	//
	HK_TEST( true );

	//
	// clean up
	//
	world->markForWrite();
	world->removeReference();

	return 0;
}


//
// test registration
//
#if defined( HK_COMPILER_MWERKS )
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER( hkMeshShape_degenerate_test , "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
