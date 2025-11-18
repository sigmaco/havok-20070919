/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/ConstraintSolver/Simplex/hkpSimplexSolver.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Common/Base/Math/Linear/hkMathStream.h>

#define RANDOM_TRANSLATION	// Add in Random translation when performing the tests
#define RANDOM_ROTATION		// Add in Random rotation when performing the tests
#define RANDOM_VELOCITY		// Add in Random velocity when performing the tests
 

hkBool SingleSimplexTest( const hkpSimplexSolverInput& input, hkpSimplexSolverOutput& output, hkReal posX, hkReal posY, hkReal posZ, hkReal velX, hkReal velY, hkReal velZ, const char* errorString , hkPseudoRandomGenerator& randomGen, hkBool checkPenetration = true)
{
	hkVector4 testVelocity; testVelocity.set( velX, velY, velZ );
	hkVector4 testPosition; testPosition.set( posX, posY, posZ );
	hkBool success = true;

	//
	// Randomize the input so we solve at a random position and orientation
	//
#ifdef RANDOM_ROTATION
	hkQuaternion randOrient;
	randomGen.getRandomRotation(randOrient);
#endif

#ifdef RANDOM_TRANSLATION
	hkVector4 randPos;
	randomGen.getRandomVector11(randPos);
	randPos.mul4(50.0f);
#endif

#ifdef RANDOM_VELOCITY
	hkVector4 randVel;
	randomGen.getRandomVector11(randVel);
#endif

	//
	//	Map the input constraints to the new random space and normalize
	//
	const int maxNumConstraints = 100;
	HK_ALIGN16( hkpSurfaceConstraintInfo copyConstraints[ maxNumConstraints ] );

	hkpSimplexSolverInput currentInput = input;
	{
		for (int i = 0; i < currentInput.m_numConstraints; i++ )
		{
			hkpSurfaceConstraintInfo sci = currentInput.m_constraints[i];
			output.m_planeInteractions[i].m_touched = false;
			
			hkReal offset = sci.m_plane(3);
			sci.m_plane.normalize3();
			sci.m_plane(3) = 0;

#ifdef RANDOM_ROTATION
			sci.m_plane.setRotatedDir(randOrient, sci.m_plane);
			sci.m_velocity.setRotatedDir(randOrient, sci.m_velocity);
#endif
			sci.m_plane(3) = offset;
			
#ifdef RANDOM_TRANSLATION
			hkReal randOffset = randPos.dot3(sci.m_plane);
			sci.m_plane(3) -= randOffset;
#endif

#ifdef RANDOM_VELOCITY
			sci.m_velocity.add4(randVel);
#endif
			copyConstraints[i] = sci;
		}
	}

	currentInput.m_constraints = copyConstraints;

#ifdef RANDOM_ROTATION
	currentInput.m_position.setRotatedDir(randOrient, input.m_position);
	currentInput.m_velocity.setRotatedDir(randOrient, input.m_velocity);
#endif
#ifdef RANDOM_TRANSLATION
	currentInput.m_position.add4(randPos);
#endif

#ifdef RANDOM_VELOCITY
	currentInput.m_velocity.add4(randVel);
#endif

	//
	// Call the simplex iterating as we normally would to complete the timestep.
	//
	do {
		
		hkSimplexSolverSolve( currentInput, output );
		currentInput.m_position = output.m_position;
		currentInput.m_velocity = output.m_velocity;
		currentInput.m_deltaTime -= output.m_deltaTime;

		// Integrate the planes 
		{
			for (int i=0; i< currentInput.m_numConstraints; i++ )
			{
				hkpSurfaceConstraintInfo& sci = const_cast<hkpSurfaceConstraintInfo&>(currentInput.m_constraints[i]);
				sci.m_plane(3) -= hkReal(sci.m_plane.dot3(sci.m_velocity)) * (output.m_deltaTime);
			}
		}

	} while ( (currentInput.m_deltaTime > HK_REAL_EPSILON) && (output.m_deltaTime > HK_REAL_EPSILON) );

	//
	//	Check correctness of output in general
	//
	if (checkPenetration)
	{
		for ( int i = 0; i < currentInput.m_numConstraints; i++ )
		{
			const hkpSurfaceConstraintInfo& c = currentInput.m_constraints[i];

			hkReal dist = c.m_plane.dot4xyz1( output.m_position );
			if ( dist < -0.001f )
			{
				HK_TEST2( 0, errorString << ": Penetration not solved (" << dist << ")");
				success = false;
			}

			if ( output.m_planeInteractions[i].m_touched )
			{
				hkVector4 relVel; relVel.setSub4( output.m_velocity, c.m_velocity );
				hkReal relProjectedVel = relVel.dot3( c.m_plane );
				if ( relProjectedVel < -0.001f )
				{
					HK_TEST2( false, errorString << ": Simplex did not solve the velocity problem, still approaching" );
					success = false;
				}
			}
		}
	}

	// Remap results back
#ifdef RANDOM_VELOCITY
	output.m_velocity.sub4(randVel);
	output.m_position.addMul4( -input.m_deltaTime, randVel);
#endif

#ifdef RANDOM_TRANSLATION
	output.m_position.sub4(randPos);
#endif

#ifdef RANDOM_ROTATION
	output.m_position.setRotatedInverseDir(randOrient, output.m_position);
	output.m_velocity.setRotatedInverseDir(randOrient, output.m_velocity);
#endif

	//
	//	Check this very special test
	//
	if ( !testPosition.equals3( output.m_position ) )
	{
		HK_TEST2( 0, errorString << ": CurrentPos " << output.m_position << " does not match targetPos " << testPosition );
		success = false;
	}

	if ( !testVelocity.equals3( output.m_velocity ) )
	{
		HK_TEST2( 0, errorString << ": CurrentVelocity " << output.m_velocity << " does not match targetVel " << testVelocity );
		success = false;
	}


	return success;
};


//
// test the simplex
//
int simplex_main(  )
{
	if ( hkMath::sqrt(2) > 1 )
	{
		//hkBaseSystem::init();
	}
	hkReal sq2 = hkMath::sqrt(2);
	hkReal sqi2 = hkMath::sqrt(0.5f);

	hkPseudoRandomGenerator randomGen(428);

	
	const int maxNumConstraints = 100;
	HK_ALIGN16( hkpSurfaceConstraintInfo constraints[ maxNumConstraints ] );
	{
		for ( int i = 0; i < maxNumConstraints; i++ )
		{
			hkpSurfaceConstraintInfo& c = constraints[i];
			c.m_dynamicFriction = 0.0f;
			c.m_plane.setZero4();
			//c.m_restitution = 0.2f;
			c.m_staticFriction = 0.0f;
			c.m_velocity.setZero4();
			c.m_extraUpStaticFriction = 0.0f;
			c.m_extraDownStaticFriction = 0.0f;
		}
	}

	hkpSurfaceConstraintInteraction interactions[ maxNumConstraints ];

	HK_ALIGN16( hkpSimplexSolverInput input );

	input.m_constraints = constraints;
	input.m_numConstraints = maxNumConstraints;
	input.m_deltaTime = 1.f;
	input.m_velocity.set( 0.f, 0.f,  2.f );
	input.m_position.set( 0.f, 0.f, -1.f );
	input.m_upVector.set( 0.f, 0.f, -1.f );
	input.m_maxSurfaceVelocity.setAll3( 1000.0f );

	hkpSimplexSolverOutput output;
	output.m_planeInteractions = interactions;

	for (int iterations=0; iterations < 10; iterations++)
	{	

		//
		//	Check single plane velocity
		//
		{
			input.m_numConstraints = 1;
			constraints[0].m_plane.set   ( 0.0f, 0.0f, -1.0f , 0.0f);
			constraints[0].m_velocity.set( 0.0f, 0.5f,  0.0f );
			constraints[0].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction = 0.0f;
			SingleSimplexTest( input, output, 0,-0.78077f,0,  0,-1.56155f,0, "1D: velocity" ,randomGen);

			constraints[0].m_velocity.setZero4();
		}

		//
		//	Check one plane with friction
		//
		{
			input.m_numConstraints = 1;
			constraints[0].m_plane.set( 1.0f, 0.0f, -1.0f , 0.0f);

			constraints[0].m_staticFriction = 2.0f;
			SingleSimplexTest( input, output, 0,0,0,  0,0,0, "1D: 1Static_Friction" ,randomGen);

			constraints[0].m_staticFriction =  0.0f;
			constraints[0].m_dynamicFriction= 0.0f;
			SingleSimplexTest( input, output, sqi2,0,sqi2,  sq2,0,sq2, "1D: 0Static_0Dyn_Friction" ,randomGen);

			constraints[0].m_staticFriction =  0.0f;
			constraints[0].m_dynamicFriction= 1.0f;
			SingleSimplexTest( input, output, .5f,0,.5f,  1.f,0,1.f, "1D: 0Static_1Dyn_Friction" ,randomGen);
		}

		//
		//	Check one plane with friction
		//
		{
			input.m_velocity.set( 1.f, -0.1f, 0.f);
			input.m_position.set( 0.f, 0.f, 0.f );

			input.m_numConstraints = 1;
			constraints[0].m_plane.set( -1.f, 1.f, 0.f , 0.f);

			constraints[0].m_staticFriction =  0.5f;
			constraints[0].m_dynamicFriction = 1.f;
			SingleSimplexTest( input, output, 0.45f, 0.45f, 0, 0.45f, 0.45f, 0, "Static Friction Check" ,randomGen);

			input.m_velocity.set( 0.f, 0.f,  2.f );
			input.m_position.set( 0.f, 0.f, -1.f );

		}


		//
		//	Check two flat planes where only one is needed
		//
		{
			input.m_numConstraints = 2;
			constraints[0].m_plane.set( 1.f, 0.0f, -1.0f, 0.0f );
			constraints[1].m_plane.set( .5f, 0.0f, -1.0f, 0.25f );

			constraints[0].m_staticFriction = 0.0f;
			constraints[1].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 0.0f;
			SingleSimplexTest( input, output, 0.746337f,0,0.652677f,  1.78885f,0,0.894427f, "2D: sequentialPlanes", randomGen);

		}

		//
		//	Hit edge formed by two planes - should stop dead
		//
		{
			input.m_numConstraints = 2;
			constraints[0].m_plane.set   ( -.1f, 0.0f, -1.0f, 0.0f );
			constraints[1].m_plane.set   (  .1f, 0.0f, -1.0f, 0.0f );
			
			constraints[0].m_staticFriction = 0.0f;
			constraints[1].m_staticFriction = 0.0f;

			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 0.0f;

			SingleSimplexTest( input, output, 0,0,0, 0,0,0, "2Df: no Velocity" ,randomGen);
			constraints[0].m_velocity.setZero4();
		}

		//
		//	Hit same edge for moving planes
		//
		{
			hkVector4 randVec; randomGen.getRandomVector11(randVec);
			input.m_numConstraints = 2;
			constraints[0].m_plane.set   ( -.1f, 0.0f, -1.0f, 0.0f );
			constraints[1].m_plane.set   (  .1f, 0.0f, -1.0f, 0.0f );

			constraints[0].m_velocity = randVec;
			constraints[1].m_velocity = randVec;
		
			input.m_velocity.add4(randVec);
			constraints[0].m_staticFriction = 0.0f;
			constraints[1].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 0.0f;

			SingleSimplexTest( input, output, randVec(0), randVec(1), randVec(2), randVec(0), randVec(1), randVec(2), "2Df: no Velocity" ,randomGen);
			constraints[0].m_velocity.setZero4();
			constraints[1].m_velocity.setZero4();
			input.m_velocity.set(0.f, 0.f, 2.f);
		}

		//
		//	Check two flat planes with friction
		//
		{
			input.m_numConstraints = 2;
			constraints[0].m_plane.set( -.5f, 0.5f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  .5f, 0.5f, -1.0f, 0.0f );

			constraints[0].m_staticFriction =  2.0f;
			constraints[1].m_staticFriction =  2.0f;
			SingleSimplexTest( input, output, 0,0,0,  0,0,0, "2Df: 1Static_Friction", randomGen);

			constraints[0].m_staticFriction =  .0f;
			constraints[1].m_staticFriction =  .0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 0.0f;
			SingleSimplexTest( input, output, 0,0.894427f,0.447214f,  0, 1.78885f,0.894427f, "2Df: 0Static_0Dyn_Friction" ,randomGen);

			constraints[0].m_staticFriction =  0.0f;
			constraints[1].m_staticFriction =  0.0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 1.0f;
			SingleSimplexTest( input, output, 0,0.4f,0.2f,  0,0.8f,0.4f, "2Df: 0Static_1Dyn_Friction", randomGen);
		}

		//
		//	Check two flat planes with friction
		//
		{
			input.m_numConstraints = 2;
			constraints[0].m_plane.set(  0.0f, 1.0f, 0.0f, 0.0f );
			constraints[1].m_plane.set(  0.0f, 1.0f, -1.0f, 0.0f );

			constraints[0].m_staticFriction =  1.1f;
			constraints[1].m_staticFriction =  1.1f;
			SingleSimplexTest( input, output, 0,0,0,  0,0,0, "Static_Friction Test", randomGen);
		}


		//
		//	Check two steep planes with friction
		//
		{
			input.m_numConstraints = 2;
			constraints[0].m_plane.set( -3.0f, 0.5f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  3.0f, 0.5f, -1.0f, 0.0f );

			constraints[0].m_staticFriction = 4.0f;
			SingleSimplexTest( input, output, 0,0,0,  0,0,0, "2Ds: 1Static_Friction", randomGen);

			constraints[0].m_staticFriction =  .0f;
			constraints[1].m_staticFriction =  .0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 0.0f;
			SingleSimplexTest( input, output, 0,0.894427f,0.447214f,  0,1.78885f,0.894427f, "2Ds: 0Static_0Dyn_Friction", randomGen);

			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = 1.0f;
			SingleSimplexTest( input, output, 0,0.4f,0.2f,  0,0.8f,0.4f, "2Ds: 0Static_1Dyn_Friction", randomGen);
		}

		//
		//	Check three planes with no friction, which stop the character
		//
		{
			input.m_numConstraints = 3;
			constraints[0].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction = 0.0f;
			constraints[0].m_plane.set( -1.0f,  0.5f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  1.0f,  0.5f, -1.0f, 0.0f );
			constraints[2].m_plane.set(  0.0f, -0.5f, -1.0f, 0.0f );

			SingleSimplexTest( input, output, 0,0,0,  0,0,0, "Stop Character", randomGen);
		}

		//
		//	Check three flat planes with velocity
		//
		{
			input.m_numConstraints = 3;
			constraints[0].m_plane.set   ( -.1f, 0.1f, -1.0f, 0.07f );
			constraints[1].m_plane.set   (  .1f, 0.1f, -1.0f, 0.0f );
			constraints[2].m_plane.set   (  .0f, -.1f, -1.0f, 0.0f );

			constraints[0].m_velocity.set( -.0f, 0.0f, - .1f );

			constraints[0].m_staticFriction =  0.0f;
			constraints[1].m_staticFriction =  0.0f;
			constraints[2].m_staticFriction =  0.0f;

			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = constraints[2].m_dynamicFriction = 0.0f;

			SingleSimplexTest( input, output, 0.89412f,-0.436593f,-0.162375f,  1.78836f,-0.871162f,-0.365952f, "3Df: with Velocity", randomGen);
			constraints[0].m_velocity.setZero4();
		}

		//
		//	Check three planes with no friction, which do not stop the character
		//
		{
			input.m_numConstraints = 3;
			constraints[0].m_plane.set( -1.0f,  0.5f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  1.0f,  0.5f, -1.0f, 0.0f );
			constraints[2].m_plane.set(  0.0f,  0.001f, -1.0f, .2f );

			constraints[0].m_staticFriction =  0.0f;
			constraints[1].m_staticFriction =  0.0f;
			constraints[2].m_staticFriction =  0.0f;
			constraints[0].m_dynamicFriction= constraints[1].m_dynamicFriction = constraints[2].m_dynamicFriction = 0.0f;

			SingleSimplexTest( input, output, 0,0.952691f,0.200993f,  0,2.f,0.00214577f, "3Df: slide", randomGen);
		}

		
		//
		//	Check four planes, the first three stop the character, the last one kicks in a little later and lifts the character
		//
		{
			input.m_numConstraints = 4;
			for (int i =0; i < 4; i++)
			{
				constraints[i].m_staticFriction = 0.0f;
				constraints[i].m_dynamicFriction = 0.0f;
			}

			constraints[0].m_plane.set( -1.0f,  0.5f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  1.0f,  0.5f, -1.0f, 0.0f );
			constraints[2].m_plane.set(  0.0f,  -0.5f, -1.0f, 0.0f );
			constraints[3].m_plane.set(  0.0f,   0.0f, -1.0f, 0.7f );
			constraints[3].m_velocity.set( 0, 0, -1.0f );

			SingleSimplexTest( input, output, 0,0,-0.3f,  0,0,-1.f, "3planes, +1lift", randomGen);

			constraints[3].m_velocity.setZero4();
		}

		//
		//	Check squish 
		// The first 3 planes block the character in a corner - the last plane squashes
		//
		{
			input.m_numConstraints = 4;
			for (int i =0; i < 4; i++)
			{
				constraints[i].m_staticFriction = 0.0f;
				constraints[i].m_dynamicFriction = 0.0f;
			}

			constraints[0].m_plane.set( -1.0f,  0.0f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  1.0f,  0.0f, -1.0f, 0.0f );
			constraints[2].m_plane.set(  0.0f,  1.0f,  0.0f, 0.0f );
			constraints[3].m_plane.set(  0.0f,  0.0f,  1.0f, 1.1f );
			constraints[3].m_velocity.set( 0, 0, 2.0f );

			// ToDo : Decide on priority
			//SingleSimplexTest( input, output, 0,0,0, 0,0,0, "Squish", randomGen);

			constraints[3].m_velocity.setZero4();
		}

		// 
		// Penetration - 1 Plane
		{
			input.m_numConstraints = 1;
			constraints[0].m_plane.set(  0.0f,  0.0f, -1.0f, -1.1f );
			constraints[0].m_velocity.setZero4();
			constraints[0].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction= 0;

			// Test, but ignore penetration - we expect it here
			SingleSimplexTest( input, output, 0,0,-1,  0,0,0, "1: penetration", randomGen, false);
		}

		// 
		// Penetration - 1 Plane with velocity
		// Position should follow plane
		//
		{
			input.m_numConstraints = 1;
			constraints[0].m_plane.set(  0.0f,  0.0f, -1.0f, -1.1f );
			constraints[0].m_velocity.set(0,0,-1);
			constraints[0].m_staticFriction = 0.0f;
			constraints[0].m_dynamicFriction= 0;

			SingleSimplexTest( input, output, 0,0,-2.0f,  0,0,-1, "1: penetration with velocity", randomGen, false);
			constraints[0].m_velocity.setZero4();
		}

		//
		//	Check Penetration with static planes 
		// The first 3 planes block the character in a corner - the last plane squashes
		// We don't expect the character to take the velocity of the squashing plane as in the previous test
		//
		{
			input.m_numConstraints = 4;
			for (int i =0; i < 4; i++)
			{
				constraints[i].m_staticFriction = 0.0f;
				constraints[i].m_dynamicFriction = 0.0f;
			}

			constraints[0].m_plane.set( -1.0f,  0.0f, -1.0f, 0.0f );
			constraints[1].m_plane.set(  1.0f,  0.0f, -1.0f, 0.0f );
			constraints[2].m_plane.set(  0.0f,  1.0f,  0.0f, 0.0f );
			constraints[3].m_plane.set(  0.0f,  0.0f,  1.0f, 0.9f );
			constraints[3].m_velocity.set( 0, 0, 2.0f );

			// ToDo : Decide on priority
			//SingleSimplexTest( input, output, 0,0,0, 0,0,0, "Squish Fast", randomGen);

			constraints[3].m_velocity.setZero4();
		}

		//
		// Check random planes surrounding character with tiny epsilon
		//
		{
			input.m_position.setZero4();
			for (int testNr = 0; testNr < 10; testNr++ )
			{
				input.m_numConstraints = 6;
				for ( int i = 0; i < input.m_numConstraints; i++ )
				{
					hkpSurfaceConstraintInfo& c = constraints[i];
					c.m_dynamicFriction = 0.0f;
					c.m_staticFriction = 0.0f;

					// Create a box around the player
					c.m_plane.setZero4();
					c.m_plane(i/2) = (i%2) ? -1.f : 1.f;

					c.m_plane(3) = 0.0001f;
					c.m_plane.normalize3();
					c.m_velocity.setZero4();
				}
				SingleSimplexTest( input, output, input.m_position(0), input.m_position(1), input.m_position(2),  0,0,0, "Boxed in", randomGen);
			}
			input.m_position.set( 0.f, 0.f, -1.f );
		}

	}
	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(simplex_main, "Fast", "Physics/Test/UnitTest/Internal/", __FILE__     );

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
