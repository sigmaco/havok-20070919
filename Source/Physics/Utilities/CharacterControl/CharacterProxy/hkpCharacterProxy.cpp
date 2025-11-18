/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/DebugUtil/StatisticsCollector/Simple/hkSimpleStatisticsCollector.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/ConstraintSolver/Simplex/hkpSimplexSolver.h>
#include <Physics/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxy.h>
#include <Physics/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxyCinfo.h>
#include <Physics/Dynamics/Phantom/hkpShapePhantom.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h>
#include <Physics/Collide/Query/CastUtil/hkpLinearCastInput.h> 
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/ConstraintSolver/Simplex/hkpSimplexSolver.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

// Enable this to see manifold planes.
#ifdef HK_DEBUG
#define DEBUG_CHARACTER_CONTROLLER
#endif

hkpCharacterProxy::hkpCharacterProxy(const hkpCharacterProxyCinfo& info)
	: m_shapePhantom(HK_NULL)
{
	updateFromCinfo( info );
}

void hkpCharacterProxy::getCinfo(hkpCharacterProxyCinfo& info) const
{
	info.m_position = getPosition();
	info.m_velocity = m_velocity;
	info.m_shapePhantom = m_shapePhantom;
	info.m_dynamicFriction = m_dynamicFriction;
	info.m_staticFriction = m_staticFriction;
	info.m_keepContactTolerance = m_keepContactTolerance;
	info.m_up = m_up;
	info.m_extraUpStaticFriction = m_extraUpStaticFriction;
	info.m_extraDownStaticFriction = m_extraDownStaticFriction;
	info.m_keepDistance = m_keepDistance;
	info.m_contactAngleSensitivity = m_contactAngleSensitivity;
	info.m_userPlanes = m_userPlanes;
	info.m_maxCharacterSpeedForSolver = m_maxCharacterSpeedForSolver;
	info.m_characterStrength = m_characterStrength;
	info.m_characterMass = m_characterMass;
	info.m_maxSlope = hkMath::acos(m_maxSlopeCosine);
	info.m_penetrationRecoverySpeed = m_penetrationRecoverySpeed;
	info.m_maxCastIterations = m_maxCastIterations;
	info.m_refreshManifoldInCheckSupport = m_refreshManifoldInCheckSupport;
}


void hkpCharacterProxy::updateFromCinfo( const hkpCharacterProxyCinfo& info )
{
	HK_ASSERT2(0x1e81f814, info.m_shapePhantom != HK_NULL, "Shape phantom can not be NULL");

	info.m_shapePhantom->addReference();
	if (m_shapePhantom)
	{
		m_shapePhantom->removeReference();
	}

	m_velocity = info.m_velocity;
	m_dynamicFriction = info.m_dynamicFriction;
	m_staticFriction = info.m_staticFriction;
	m_keepContactTolerance = info.m_keepContactTolerance;
	m_extraUpStaticFriction = info.m_extraUpStaticFriction;
	m_extraDownStaticFriction = info.m_extraDownStaticFriction;
	m_keepDistance = info.m_keepDistance;
	m_shapePhantom = info.m_shapePhantom;
	m_contactAngleSensitivity = info.m_contactAngleSensitivity;
	m_userPlanes = info.m_userPlanes;
	m_maxCharacterSpeedForSolver = info.m_maxCharacterSpeedForSolver;
	m_characterStrength = info.m_characterStrength;
	m_characterMass = info.m_characterMass;
	m_maxSlopeCosine = hkMath::cos( info.m_maxSlope );
	m_penetrationRecoverySpeed = info.m_penetrationRecoverySpeed;
	m_maxCastIterations = info.m_maxCastIterations;
	m_refreshManifoldInCheckSupport = info.m_refreshManifoldInCheckSupport;

	m_up = info.m_up;
	m_up.normalize3();

	// On construction we cannot guarantee that the phantom
	// has been added to the world already.
	// This often depends on the users specific toolchain
	if (m_shapePhantom->getWorld() != HK_NULL)
	{
		setPosition(info.m_position);
	}
	else
	{
		HK_WARN(0x6cee9071, "Shape phantom has not yet been added to the world. Initial position has been ignored");
	}

	m_oldDisplacement.setZero4();

	{
		for (int i=0; i< m_bodies.getSize(); i++)
		{
			m_bodies[i]->removeEntityListener(this);
		}
		m_bodies.clear();

		for (int j=0; j< m_phantoms.getSize(); j++)
		{
			m_phantoms[j]->removePhantomListener(this);
		}
		m_phantoms.clear();
	}

	m_manifold.clear();

	// Add a property that allows us to identify this as a character proxy later
	if ( !m_shapePhantom->hasProperty(HK_PROPERTY_CHARACTER_PROXY) )
	{
		m_shapePhantom->addProperty(HK_PROPERTY_CHARACTER_PROXY, this);
	}
}

/*
#include <stdio.h>
static void printManifold(hkArray<hkpRootCdPoint>& manifold)
{
	printf("\nManifold: \n");
	for (int i = 0; i < manifold.getSize(); ++i)
	{
		printf("position = %f %f %f \nnormal = %f %f %f\ndist = %f\n",	manifold[i].m_contact.getPosition()(0), 
																		manifold[i].m_contact.getPosition()(1), 
																		manifold[i].m_contact.getPosition()(2),
																		manifold[i].m_contact.getSeparatingNormal()(0),
																		manifold[i].m_contact.getSeparatingNormal()(1),
																		manifold[i].m_contact.getSeparatingNormal()(2),
																		manifold[i].m_contact.getSeparatingNormal()(3) );
	}
}
//*/

hkpCharacterProxy::~hkpCharacterProxy()
{
	for (int i=0; i< m_bodies.getSize(); i++)
	{
		m_bodies[i]->removeEntityListener(this);
	}
	m_bodies.clear();

	for (int j=0; j< m_phantoms.getSize(); j++)
	{
		m_phantoms[j]->removePhantomListener(this);
	}
	m_phantoms.clear();

	m_shapePhantom->removeProperty(HK_PROPERTY_CHARACTER_PROXY);
	m_shapePhantom->removeReference();
}

// Planes in this colour are passed directly to the simplex solver
// These planes actually restrict character movement
const hkInt32 HK_DEBUG_CLEAN_SIMPLEX_MANIFOLD_COLOR = hkColor::GREEN;

// Planes in this color are additional planes the user had added 
// Typically these are added in the processConstraintsCallback
// These planes actually restrict character movement
const hkInt32 HK_DEBUG_USER_SIMPLEX_MANIFOLD_COLOR = 0xffffdf00;

// Planes in this color are additional vertical planes added to restrict
// character movement up steep slopes
const hkInt32 HK_DEBUG_VERTICAL_SIMPLEX_MANIFOLD_COLOR = hkColor::CYAN;


// Planes in this color show the results of the start point collector
// These planes are filtered by the character proxy
const hkInt32 HK_DEBUG_STARTPOINT_HIT_POSITION_COLOR = hkColor::WHITE;

// Planes in this color show the results of the cast collector
// These planes are filtered by the character proxy
const hkInt32 HK_DEBUG_CASTPOINT_HIT_POSITION_COLOR = hkColor::WHITE;

// Planes in this color show the +ve distance returned by the start point collector
// These planes are filtered by the character proxy
const hkInt32 HK_DEBUG_NONPENETRATING_STARTPOINT_DIST_COLOR = hkColor::BLUE;

// Planes in this color show the -ve distance returned by the start point collector
// These planes are filtered by the character proxy
const hkInt32 HK_DEBUG_PENETRATING_STARTPOINT_DIST_COLOR = hkColor::RED;

// Planes in this color show the distance returned by the cast collector
// These planes are filtered by the character proxy
const hkInt32 HK_DEBUG_CASTPOINT_DIST_COLOR = hkColor::MAGENTA;

static void debugCast(const hkpAllCdPointCollector& startPointCollector, const hkpAllCdPointCollector& castCollector)
{
	{
		for (int h=0; h < startPointCollector.getHits().getSize(); h++)
		{
			const hkpRootCdPoint& hit = startPointCollector.getHits()[h];
			hkVector4 plane = hit.m_contact.getNormal();
			plane(3) = 0.0f;
			hkVector4 pos = hit.m_contact.getPosition();
			HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_STARTPOINT_HIT_POSITION_COLOR);
			pos.addMul4(hit.m_contact.getDistance(), hit.m_contact.getNormal());

				if (hit.m_contact.getDistance() < 0.0f)
				{
					HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_PENETRATING_STARTPOINT_DIST_COLOR);
				}
				else
				{
					HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_NONPENETRATING_STARTPOINT_DIST_COLOR);
				}
			}
		}

	// Add castCollector plane
	{
		for (int h=0; h < castCollector.getHits().getSize(); h++)
			{
			const hkpRootCdPoint& hit = castCollector.getHits()[h];
			hkVector4 plane = hit.m_contact.getNormal();
			plane(3) = 0.0f;
			hkVector4 pos = hit.m_contact.getPosition();
			HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_CASTPOINT_HIT_POSITION_COLOR);
			pos.addMul4(hit.m_contact.getDistance(), hit.m_contact.getNormal());
			HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_CASTPOINT_DIST_COLOR);
		}
	}
}

void hkpCharacterProxy::convertFractionToDistance( const hkpRootCdPoint* cHit, int numHits, const hkVector4& displacement ) const
{
	hkpRootCdPoint* hit = const_cast<hkpRootCdPoint*>(cHit);
	for (int i = numHits-1; i>=0; i--)
	{
		hkReal fraction = hit->m_contact.getDistance();
		hit->m_contact.getPosition()(3) = fraction;
		hkReal projLength = displacement.dot3(hit->m_contact.getNormal());
		hit->m_contact.setDistance( fraction * -projLength );
		hit++;
	}
}

void hkpCharacterProxy::integrate( const hkStepInfo& stepInfo, const hkVector4& worldGravity )
{
	hkpAllCdPointCollector castCollector;
	hkpAllCdPointCollector startPointCollector;
	integrateWithCollectors(stepInfo, worldGravity, castCollector, startPointCollector);
}

static bool addMaxSlopePlane( hkReal maxSlopeCos, const hkVector4& up, int index, hkArray<hkpSurfaceConstraintInfo>& surfaceConstraintsInOut)
{
	const hkReal surfaceVerticalComponent = surfaceConstraintsInOut[index].m_plane.dot3(up);

	if ( surfaceVerticalComponent > 0.01f && surfaceVerticalComponent < maxSlopeCos )
	{
		// Add an additional vertical plane at the end of the constraints array
		hkpSurfaceConstraintInfo& newConstraint = surfaceConstraintsInOut.expandOne();

		// Copy original info
		newConstraint = surfaceConstraintsInOut[index];

		// Reorient this new plane so it is vertical
		newConstraint.m_plane.addMul4( -surfaceVerticalComponent, up );
		newConstraint.m_plane.normalize3();
		return true;
	}

	// No plane added
	return false;
}

// Main character update loop:
//	Loop until timestep complete
//		Collect information about my current position
//		update the manifold
//		solve the simplex to find new position and velocity
//		cast to new desired position
//		if (hit)
//			jump to hit position
//		else
//			jump to new desired position
//	grab velocity from simplex
void hkpCharacterProxy::integrateWithCollectors(const hkStepInfo& stepInfo, const hkVector4& worldGravity, hkpAllCdPointCollector& castCollector, hkpAllCdPointCollector& startPointCollector)
{
	HK_TIMER_BEGIN_LIST("updateCharacter", "Cast");

	// Setup initial variables
	hkVector4 position(getPosition());
	hkReal remainingTime = stepInfo.m_deltaTime;
	hkpLinearCastInput castInput;
	{
		castInput.m_startPointTolerance = m_keepDistance + m_keepContactTolerance; 
		castInput.m_maxExtraPenetration = 0.01f;
	}
	hkpSimplexSolverOutput output;

	for ( int iter = 0; (remainingTime > HK_REAL_EPSILON) && (iter < m_maxCastIterations) ; iter++ )
	{
		HK_TIMER_SPLIT_LIST("InitialCast");
		//
		//	Cast in a direction, hopefully the right one.
		//  We actually only really need the start point collector information.
		//  That means we are free to use any direction as a cast direction
		//  For optimizations, we cast into the direction of the old displacement
		//  (just a guess). That means we might be able to avoid a second cast;
		//  see below.
		//
		{
			castInput.m_to.setAdd4( position, m_oldDisplacement );

			castCollector.reset();
			startPointCollector.reset();
			//	Call the caster
			m_shapePhantom->setPositionAndLinearCast( position, castInput, castCollector, &startPointCollector );

			// Change the hit point so it reflects the a real distance rather than a fraction
			if (castCollector.hasHit())
			{
				castCollector.sortHits();
				convertFractionToDistance( castCollector.getHits().begin(), castCollector.getHits().getSize(), m_oldDisplacement);
			}
		}

		//
		// Maintain the internal manifold of contact points
		// See the method for detailed rules
		//
		HK_TIMER_SPLIT_LIST("UpdateManifold");
		updateManifold(startPointCollector, castCollector);

#if defined DEBUG_CHARACTER_CONTROLLER 
		debugCast(startPointCollector, castCollector);
#endif 

		//
		// Convert manifold points to plane equations
		//
		hkLocalArray<hkpSurfaceConstraintInfo> surfaceConstraints(m_manifold.getSize() + m_userPlanes + 10);
		surfaceConstraints.setSizeUnchecked(m_manifold.getSize()); 
		{
			for (int i=0; i < m_manifold.getSize() ; i++)
			{
				extractSurfaceConstraintInfo(m_manifold[i], surfaceConstraints[i], stepInfo.m_deltaTime - remainingTime );
				addMaxSlopePlane( m_maxSlopeCosine, m_up, i, surfaceConstraints);
			}

			#if defined DEBUG_CHARACTER_CONTROLLER
			for (int j=0; j < surfaceConstraints.getSize() ; j++)
			{
				HK_DISPLAY_PLANE(surfaceConstraints[j].m_plane, position , 0.5f, (j < m_manifold.getSize()) ? HK_DEBUG_CLEAN_SIMPLEX_MANIFOLD_COLOR : HK_DEBUG_VERTICAL_SIMPLEX_MANIFOLD_COLOR);
			}
			#endif
		}

		// Resize array if it is now too small to accomodate the user planes.
		if (surfaceConstraints.getCapacity() - surfaceConstraints.getSize() < m_userPlanes )
		{
			surfaceConstraints.reserve(surfaceConstraints.getSize() + m_userPlanes);
		}

		//
		// Solve the simplex
		//
		HK_TIMER_SPLIT_LIST("SlexMove");
		hkpSimplexSolverInput input;

		hkLocalArray<hkpSurfaceConstraintInteraction> surfaceInteractions(surfaceConstraints.getSize() + m_userPlanes);
		surfaceInteractions.setSizeUnchecked(surfaceConstraints.getSize() + m_userPlanes);
		{
			input.m_constraints = surfaceConstraints.begin();
			input.m_numConstraints = surfaceConstraints.getSize();
			input.m_velocity = m_velocity;
			input.m_deltaTime = remainingTime;
			if( m_velocity.lengthSquared3() == 0.0f )
			{
				input.m_minDeltaTime = 0.0f;
			}
			else 
			{
				input.m_minDeltaTime = 0.5f * (m_keepDistance * hkReal(m_velocity.lengthInverse3()));
			}
			input.m_position.setZero4();
			input.m_upVector = m_up;
			input.m_maxSurfaceVelocity.setAll3( m_maxCharacterSpeedForSolver );

			//
			// Allow the user to do whatever they wish with the surface constraints
			//
			fireConstraintsProcessed( m_manifold, input );

			output.m_planeInteractions = surfaceInteractions.begin();

			// Solve Simplex
			hkSimplexSolverSolve( input, output );
		}

#if defined DEBUG_CHARACTER_CONTROLLER 
		{
			int extraConstraints = input.m_numConstraints - surfaceConstraints.getSize();
			// Display user planes at the centre of the character shape
			for (int i = 0; i < extraConstraints; i++)
			{
				HK_DISPLAY_PLANE(input.m_constraints[m_manifold.getSize()+i].m_plane, position , 0.5f, HK_DEBUG_USER_SIMPLEX_MANIFOLD_COLOR);
			}
		}
#endif

		//
		// Apply forces - e.g. Character hits dynamic objects 
		//
		HK_TIMER_SPLIT_LIST("ApplySurf");
		applySurfaceInteractions( stepInfo, worldGravity );

		//
		// Check whether we can walk to the new position the simplex has suggested
		// 

		HK_TIMER_SPLIT_LIST("CastMove");
		{
			hkBool32 simplexResultOk = m_oldDisplacement.equals3(output.m_position);

			// If the simplex has given an output direction different from the cast guess
			// we re-cast to check we can move there. There is no need to get the start points again.
			if( simplexResultOk == false )
			{
				castInput.m_to.setAdd4( position, output.m_position);
				HK_ON_DEBUG( HK_DISPLAY_LINE(position, castInput.m_to, hkColor::CYAN) );

				castCollector.reset();
				m_shapePhantom->setPositionAndLinearCast( position, castInput, castCollector, HK_NULL );

				if ( castCollector.hasHit() )
				{
					castCollector.sortHits();
					convertFractionToDistance( castCollector.getHits().begin(), castCollector.getHits().getSize(), output.m_position );

					//
					// If the new cast hit something we have to check if this is a new
					// surface, or one we have already passed to the simplex
					//

					// Did we already have this plane?
					while (findSurface(castCollector.getHits()[0]) != -1)
					{
						// We found it, so the simplex already took it into account
						// We ignore this point and test the others
						castCollector.getHits().removeAtAndCopy(0);
						if ( !castCollector.hasHit() )
						{
							// There are no more hits left so we can walk to where the simplex wants
							simplexResultOk = true;
							break;
						}
					}

					// If there is a new point found that was not already in the manifold, add it to the manifold
					if (castCollector.getHits().getSize() > 0)
					{
						const hkpRootCdPoint& surface = castCollector.getHits()[0];
						fireContactAdded( surface );
						m_manifold.pushBack( surface );

						// If we are not refreshing the manifold in check support, we need 
						// to add the new phantom or entity as a listener if it is
						// not already in the manifold.
						if ( !m_refreshManifoldInCheckSupport)
						{
							hkpRigidBody* body =  hkGetRigidBody(surface.m_rootCollidableB);
							if ( body && ( m_bodies.indexOf(body) == -1 ) )
							{
								body->addEntityListener(this);
								m_bodies.pushBack(body);
							}

							hkpPhantom* phantom = hkGetPhantom( surface.m_rootCollidableB );
							if (phantom && (m_phantoms.indexOf(phantom) == -1) )
							{
								phantom->addPhantomListener( this );
								m_phantoms.pushBack(phantom);
							}
						}
					}
				}
				else
				{
					simplexResultOk = true;
				}
			}
			if( simplexResultOk )
			{
				position.add4(output.m_position);
				remainingTime -= output.m_deltaTime; 
			}
			else
			{
				remainingTime -= moveToLinearCastHitPosition(output, castCollector, castInput, position);
			}

			m_oldDisplacement = output.m_position;
		}
	}

	// Update with the output velocity from the simplex.
	m_velocity = output.m_velocity;


	// Update the phantom with the new position
	m_shapePhantom->setPosition(position, castInput.m_startPointTolerance);

	HK_TIMER_END_LIST();
}

// this function subtracts the keep distance (projected onto the cast vector) from the cast output.
hkReal hkpCharacterProxy::moveToLinearCastHitPosition(const hkpSimplexSolverOutput& output, 
											const hkpAllCdPointCollector& castCollector, 
											const hkpLinearCastInput& castInput,
											hkVector4& position)
{
	// Only walk as far as the cast allows.
	const hkVector4& displacement = output.m_position;
	const hkReal displacementLength = displacement.length3();
	const hkContactPoint& firstContact = castCollector.getHits()[0].m_contact;
	
	const hkReal angleBetweenMovementAndSurface = hkReal(displacement.dot3( firstContact.getNormal() )) / displacementLength;
	const hkReal keepDistanceAlongMovement = m_keepDistance / -angleBetweenMovementAndSurface;
	hkReal fraction = firstContact.getPosition()(3) - (keepDistanceAlongMovement / displacementLength);
	// If an object is within m_keepDistance e.g. embedded in the character,
	// then we can't move forward but we also do not wish the character to
	// move backwards.
	fraction = hkMath::max2( 0.0f, hkMath::min2( fraction, 1.0f ) );

	position.setInterpolate4( position, castInput.m_to, fraction );

	hkReal timeTravelled = output.m_deltaTime * fraction;
	return timeTravelled;
}

const hkArray<hkpRootCdPoint>& hkpCharacterProxy::getManifold() const
{
	return m_manifold;
}

// Extract velocity information from the contact point.
void hkpCharacterProxy::extractSurfaceVelocity(const hkpRootCdPoint& hit, hkVector4& velocityOut) const
{
	velocityOut.setZero4();

	// Grab body information // Body A is always the shapePhantom
	hkpRigidBody* body = hkGetRigidBody(hit.m_rootCollidableB);

	if (body)
	{
		// Extract velocity at point on surface
		body->getPointVelocity(hit.m_contact.getPosition(), velocityOut);
	}
}

void hkpCharacterProxy::refreshManifold( hkpAllCdPointCollector& startPointCollector )
{
	// Update the start point collector
	{
		startPointCollector.reset();
		hkpWorld* world = m_shapePhantom->getWorld();
		HK_ASSERT2(0x54e32e12, world, "Character proxy must be added to world before calling refreshManifold");

		hkpCollisionInput input = *world->getCollisionInput();
		input.m_tolerance = input.m_tolerance + (m_keepDistance + m_keepContactTolerance);
		m_shapePhantom->getClosestPoints(startPointCollector, &input);
	}

	// Update the manifold so that it is correct, so that checkSupport() returns the correct answer.
	hkpAllCdPointCollector castCollector;
	updateManifold(startPointCollector, castCollector );
}

void hkpCharacterProxy::checkSupport(const hkVector4& direction, hkpSurfaceInfo& ground)
{
	hkpAllCdPointCollector startPointCollector;
	checkSupportWithCollector(direction, ground, startPointCollector);
}

void hkpCharacterProxy::checkSupportWithCollector(const hkVector4& direction, hkpSurfaceInfo& ground, hkpAllCdPointCollector& startPointCollector)
{
	HK_ASSERT2(0x79d57ec9,  hkMath::equal(direction.length3(), 1.0f), "checkSupport Direction should be normalized");
	HK_TIMER_BEGIN("checkSupport", HK_NULL);

	if (m_refreshManifoldInCheckSupport)
	{
		refreshManifold( startPointCollector );
	}

	hkLocalArray<hkpSurfaceConstraintInfo> constraints(m_manifold.getSize() + m_userPlanes + 10);
	constraints.setSizeUnchecked(m_manifold.getSize());
	{
		for (int i=0; i < m_manifold.getSize() ; i++)
		{
			extractSurfaceConstraintInfo(m_manifold[i], constraints[i], 0);
			addMaxSlopePlane( m_maxSlopeCosine, m_up, i, constraints);
		}
	}
	// Resize array if it is now too small to accomodate the user planes.
	if (constraints.getCapacity() - constraints.getSize() < m_userPlanes )
	{
		constraints.reserve(constraints.getSize() + m_userPlanes);
	}

	// Interactions array - this is the output of the simplex solver
	hkLocalArray<hkpSurfaceConstraintInteraction> interactions(constraints.getSize() + m_userPlanes);

	// Stored velocities - used to remember surface velocities to give the correct output surface velocity
	hkLocalArray<hkVector4> storedVelocities( constraints.getSize() + m_userPlanes );

	//
	//	Test Direction
	//
	hkpSimplexSolverInput input;
	hkpSimplexSolverOutput output;
	{
		input.m_position.setZero4();
		input.m_constraints = constraints.begin();
		input.m_numConstraints = constraints.getSize();
		input.m_velocity = direction;
		input.m_deltaTime = 1.0f / 60.0f; 
		input.m_minDeltaTime = 1.0f / 60.0f;
		input.m_upVector = m_up;

		input.m_maxSurfaceVelocity.setAll( m_maxCharacterSpeedForSolver );
		output.m_planeInteractions = interactions.begin();

		//
		// Allow the user to do whatever they wish with the surface constraints
		//
		fireConstraintsProcessed( m_manifold, input );

		// Set the sizes of the arrays to be correct
		storedVelocities.setSize(input.m_numConstraints);
		interactions.setSize(input.m_numConstraints);
		constraints.setSize(input.m_numConstraints);

		// Remove velocities and friction to make this a query of the static geometry
		for (int i = 0; i < input.m_numConstraints; ++i )
		{
			storedVelocities[i] = constraints[i].m_velocity;
			constraints[i].m_velocity.setZero4();
		}

		hkSimplexSolverSolve( input, output );
	}

	ground.m_surfaceVelocity.setZero4();
	ground.m_surfaceNormal.setZero4();

	if ( output.m_velocity.equals3( direction ) )
	{
		ground.m_supportedState = hkpSurfaceInfo::UNSUPPORTED;
	}
	else 
	{
		if ( output.m_velocity.lengthSquared3() < .001f )
		{
			ground.m_supportedState = hkpSurfaceInfo::SUPPORTED;
		}
		else
		{
			output.m_velocity.normalize3();
			hkReal angleSin = output.m_velocity.dot3(direction);
			
			hkReal cosSqr = 1 - angleSin * angleSin;

			if (cosSqr < m_maxSlopeCosine * m_maxSlopeCosine )
			{
				ground.m_supportedState = hkpSurfaceInfo::SLIDING;
			}
			else
			{
				ground.m_supportedState = hkpSurfaceInfo::SUPPORTED;
			}
		}
	}

	if ( ground.m_supportedState != hkpSurfaceInfo::UNSUPPORTED )
	{
		int numTouching = 0;

		for (int i=0; i < input.m_numConstraints; i++)
		{
			// If we touched this plane and it supports our direction
			if ((interactions[i].m_touched) && hkReal(constraints[i].m_plane.dot3(direction)) < -0.08f)
			{
				ground.m_surfaceNormal.add4( constraints[i].m_plane );
				ground.m_surfaceVelocity.add4( storedVelocities[i] );
				numTouching++;
			}
		}

		#ifdef DEBUG_CHARACTER_CONTROLLER
			HK_DISPLAY_ARROW(getPosition(),ground.m_surfaceNormal, 0xffffffff);
		#endif

		if (numTouching > 0)
		{
			ground.m_surfaceNormal.normalize3();
			ground.m_surfaceVelocity.mul4(1.f / numTouching);
		}
		else
		{
			ground.m_supportedState = hkpSurfaceInfo::UNSUPPORTED;
		}
	}

	HK_TIMER_END();
}


// Check and see if the character is supported in the give direction
void hkpCharacterProxy::checkSupportDeprecated(const hkVector4& direction, hkpSurfaceInfoDeprecated& ground) const
{
	HK_ASSERT2(0x79d57ec9,  hkMath::equal(direction.length3(), 1.0f), "checkSupport Direction should be normalized");
	HK_TIMER_BEGIN("checkSupport", HK_NULL);

	// We zero the velocity of all the planes, making this call a static geometric query
	hkLocalArray<hkpSurfaceConstraintInfo> constraints(m_manifold.getSize() + m_userPlanes + 10);
	constraints.setSizeUnchecked(m_manifold.getSize());
	{
		for (int i=0; i < m_manifold.getSize() ; i++)
		{
			extractSurfaceConstraintInfo(m_manifold[i], constraints[i], 0);
			addMaxSlopePlane( m_maxSlopeCosine, m_up, i, constraints);
		}
	}

	// Resize array if it is now too small to accomodate the user planes.
	if (constraints.getCapacity() - constraints.getSize() < m_userPlanes )
	{
		constraints.reserve(constraints.getSize() + m_userPlanes);
	}

	// Magnitude of our velocity in the current direction
	// ToDo: Work with our current velocity
	hkLocalArray<hkpSurfaceConstraintInteraction> interactions(constraints.getSize() + m_userPlanes);
	interactions.setSize(constraints.getSize() + m_userPlanes);


	//
	//	Test Direction
	//
	hkpSimplexSolverInput input;
	hkpSimplexSolverOutput output;
	{
		input.m_position.setZero4();
		input.m_constraints = constraints.begin();
		input.m_numConstraints = m_manifold.getSize();
		input.m_velocity.setAdd4(m_velocity,direction);
		input.m_deltaTime = 1.0f / 60.0f; 
		input.m_minDeltaTime = 1.0f / 60.0f;
		input.m_upVector = m_up;

		input.m_maxSurfaceVelocity.setAll( m_maxCharacterSpeedForSolver );
		output.m_planeInteractions = interactions.begin();

		//
		// Allow the user to do whatever they wish with the surface constraints
		//
		fireConstraintsProcessed( m_manifold, input );

		hkSimplexSolverSolve( input, output );
	}

	output.m_velocity.sub4(m_velocity);

	hkReal projectedVelocity = output.m_velocity.dot3(direction);

	// If our velocity was reduced then we hit something 
	// HVK-2402
	ground.m_isSupported = projectedVelocity < .99f;

	hkVector4 resultant;
	resultant.setAddMul4(output.m_velocity, direction, -projectedVelocity);
	ground.m_isSliding = resultant.lengthSquared3() > 0.01f;

	ground.m_surfaceVelocity.setZero4();
	ground.m_surfaceNormal.setZero4();

	int numTouching = 0;

	for (int i=0; i < input.m_numConstraints; i++)
	{
		// If we touched this plane and it supports our direction
		if ((interactions[i].m_touched) && hkReal(constraints[i].m_plane.dot3(direction)) < -0.08f)
		{
			ground.m_surfaceNormal.add4( constraints[i].m_plane );
			ground.m_surfaceVelocity.add4( constraints[i].m_velocity );
			numTouching++;
		}
	}

	if (numTouching > 0)
	{
		ground.m_surfaceNormal.normalize3();
		ground.m_surfaceVelocity.mul4(1.f / numTouching);
	}
	else
	{
		ground.m_isSupported = false;
	}

	HK_TIMER_END();
}

void hkpCharacterProxy::extractSurfaceConstraintInfo(const hkpRootCdPoint& hit, hkpSurfaceConstraintInfo& surface, hkReal timeTravelled) const
{
	surface.m_plane = hit.m_contact.getSeparatingNormal();

	// Contract the planes by the keep distance
	surface.m_plane(3) -= m_keepDistance; 

	surface.m_staticFriction = m_staticFriction;
	surface.m_dynamicFriction = m_dynamicFriction;
	surface.m_extraUpStaticFriction = m_extraUpStaticFriction;
	surface.m_extraDownStaticFriction = m_extraDownStaticFriction; 

	// Assume the velocity of this surface is 0
	surface.m_velocity.setZero4();

	// Assume this is a low priority surface
	surface.m_priority = 0;

	// Grab body information
	hkpRigidBody* body = hkGetRigidBody(hit.m_rootCollidableB);
	if (body)
	{
		// Extract point velocity

		// HVK-1871. This code gets the point velocity at the collision, based on how far
		// the object actually travelled, rather than the velocity result of the constraint solver.
		// (i.e. the value got from getPointVelocity)
		// When a heavy force pushes a rigid body into a fixed rigid body these values can diverge,
		// which can cause the character controller to penetrate the moving rigid body, as it sees
		// an incorrectly moving plane.

		// Note, this means that velocities will be one frame behind, so for accelerating platforms
		// (HVK-1477) (i.e. For keyframed or fixed objects) we just take the velocity, to make sure the
		// character does not sink in.
		if (body->isFixedOrKeyframed())
		{
			body->getPointVelocity(hit.m_contact.getPosition(), surface.m_velocity);
		}
		else
		{
			hkVector4 linVel;
			hkVector4 angVel;
			hkSweptTransformUtil::getVelocity(*body->getRigidMotion()->getMotionState(), linVel, angVel);
			hkVector4 relPos; relPos.setSub4( hit.m_contact.getPosition(), body->getCenterOfMassInWorld() );
			surface.m_velocity.setCross( angVel, relPos);
			surface.m_velocity.add4( linVel );
		}


		// Move the plane by the velocity, based on the timeTravelled HVK-1477
		surface.m_plane(3) -= static_cast<hkReal>(surface.m_velocity.dot3(surface.m_plane)) * timeTravelled;


		// Extract priority
		// - Static objects have highest priority
		// - Then keyframed
		// - Then dynamic
		if (body->getMotionType() == hkpMotion::MOTION_FIXED)
		{
			// Increase the priority
			surface.m_priority = 2;
		}

		if (body->getMotionType() == hkpMotion::MOTION_KEYFRAMED)
		{
			// Increase the priority
			surface.m_priority = 1;
		}
	}

	// If penetrating we add extra velocity to push the character back out
	if ( surface.m_plane(3) < -HK_REAL_EPSILON)
	{
		HK_ON_DEBUG( HK_DISPLAY_ARROW(hit.m_contact.getPosition(),  hit.m_contact.getNormal(), hkColor::RED) );
		surface.m_velocity.addMul4(-surface.m_plane(3) * m_penetrationRecoverySpeed, hit.m_contact.getNormal());
		surface.m_plane(3) = 0.f;
	}

}

// Computes a metric to allow us to compare points for similarity.
//	Metric is based on:
//    - Angle between normals
//    - Contact Point Distances
//	  - Velocity
inline hkReal hkpCharacterProxy::surfaceDistance(const hkpRootCdPoint& p1, const hkpRootCdPoint& p2) const
{
	// Small angle approx (changed from cross product HVK-2184)
	hkReal angleSquared = 1 - static_cast<hkReal>(p1.m_contact.getNormal().dot3(p2.m_contact.getNormal())); 
	angleSquared *= m_contactAngleSensitivity * m_contactAngleSensitivity;

	

	hkReal planeDistanceSqrd = p1.m_contact.getDistance() - p2.m_contact.getDistance();
	planeDistanceSqrd *= planeDistanceSqrd;

	hkVector4 p1Vel, p2Vel;
	extractSurfaceVelocity(p1, p1Vel);
	extractSurfaceVelocity(p2, p2Vel);

	hkVector4 velDiff; velDiff.setSub4( p1Vel, p2Vel );
	hkReal velocityDiffSqrd = velDiff.lengthSquared3();

	return angleSquared * 10.0f + velocityDiffSqrd * 0.1f + planeDistanceSqrd;
}

// Verify that the surface info is not the same as one we previously
// have in the manifold.
int hkpCharacterProxy::findSurface(const hkpRootCdPoint& info) const
{
	int bestIndex = -1;
	hkReal minDistance = 0.1f;

	for (int i=0; i< m_manifold.getSize(); i++)
	{
		hkReal distance = surfaceDistance(info, m_manifold[i]);
		if ( distance < minDistance )
		{
			minDistance = distance;
			bestIndex = i;
		}
	}
	return bestIndex;
}

// Maintain the manifold of plane equations we pass on to the simple solver
// This forms the bridge between the collision detector and the simplex solver
//
// Manifold Rules:
//	- All moving planes found at start are kept.
// - All penetrating planes found at start are kept.
// - Cast Plane is always kept.
// - All other currently held planes must verify they are present in the start collector.
void hkpCharacterProxy::updateManifold(const hkpAllCdPointCollector& startPointCollector, const hkpAllCdPointCollector& castCollector )
{
	// Remove listener from all bodies and phantoms
	{
		for (int i=0 ; i < m_bodies.getSize(); i++)
		{
			m_bodies[i]->removeEntityListener(this);
		}
		m_bodies.clear();

		for (int j=0; j< m_phantoms.getSize(); j++)
		{
			m_phantoms[j]->removePhantomListener(this);
		}
		m_phantoms.clear();
	}


	// This is used to add the closest point always to the manifold.
	hkReal minimumPenetration = HK_REAL_MAX;

	//
	// Copy hits from start point collector
	//
	hkLocalArray<hkpRootCdPoint> startPointHits(startPointCollector.getHits().getSize());
	startPointHits.setSizeUnchecked(startPointCollector.getHits().getSize());

	for (int i=0; i< startPointHits.getSize(); i++) 
	{
		startPointHits[i] = startPointCollector.getHits()[i];

		// We only consider fixed or keyframed rigid bodies.
		if (startPointHits[i].m_contact.getDistance() < minimumPenetration )
		{
			minimumPenetration = startPointHits[i].m_contact.getDistance();
		}
	}

	//
	//	For each existing point in the manifold - 
	//		find it in the start point collector
	//		if found, copy the start point collector point over the manifold point
	//		otherwise drop the manifold point
	//
	{
		for (int s = m_manifold.getSize() - 1; s >= 0; s--)
		{
			int bestIndex = -1;
			hkReal minDistance = 1.1f;
			hkpRootCdPoint& current = m_manifold[s];

			// Find the best match for this plane
			for (int h=0; h < startPointHits.getSize(); h++)
			{
				hkpRootCdPoint& surface = startPointHits[h];

				hkReal distance = surfaceDistance( surface, current ); 
				if ( distance < minDistance )
				{
					minDistance = distance;
					bestIndex = h;
				}
			}

			// Plane already exists in manifold so we update and remove from the collector
			if ( bestIndex >= 0 )
			{
				hkpRootCdPoint& surface = startPointHits[bestIndex];
				if (surface.m_rootCollidableB != current.m_rootCollidableB)
				{
					fireContactRemoved(current);
					fireContactAdded(surface);
				}

				current = surface;
				startPointHits.removeAt( bestIndex );
			}
			else
			{
				//
				//	No matching plan in start point collector - we remove this from the manifold
				//
				fireContactRemoved( m_manifold[s] );
				m_manifold.removeAt(s);
			}
		}
	}

	//
	// Add the most penetrating point from the start point collector if it is still in the
	// collector (i.e. if it is not already in the manifold). This is safe, as the closest
	// point can never be an unwanted edge.
	//
	{
		for (int h=0; h < startPointHits.getSize(); h++)
		{
			hkpRootCdPoint& surface = startPointHits[h];
			// Keep the plane if it is the the most penetrating plane
			if ( (surface.m_contact.getDistance() ) == minimumPenetration )
			{
				//
				// Find existing plane
				//
				int index = findSurface( surface );
				if (index >= 0)
				{
					hkpRootCdPoint& current = m_manifold[index];
					if (surface.m_rootCollidableB != current.m_rootCollidableB)
					{
						fireContactRemoved(current);
						fireContactAdded(surface);
					}
				
					current = surface;
				}
				else
				{
					fireContactAdded( startPointHits[h] );
					m_manifold.pushBack( startPointHits[h] );
				}
			}
		}
	}

	//
	// Add castCollector plane
	//
	if (castCollector.hasHit())
	{
		const hkpRootCdPoint& surface = castCollector.getHits()[0];
		int index = findSurface(surface);
		if (index == -1)
		{
			fireContactAdded( surface );
			m_manifold.pushBack( surface );
		}

		// NOTE: We used to update the manifold with the new point from the cast collector here, but in fact this
		// is unnecessary and sometimes wrong. All points in the manifold have been correctly updated at this stage
		// by the start point collector so they do not need to be replaced here. If the points are penetrating, then
		// the cast collector will have a distance of 0, which is incorrect, and the negative distance picked up by
		// the start collector is the one that we want.
	}

	//
	// Cross check the manifold for clean planes
	// The simplex does not handle parallel planes
	//
	{
		for (int p1 = m_manifold.getSize()-1; p1 > 0; p1--)
		{
			hkBool remove = false;
			for (int p2 = p1-1; p2 >= 0; p2--)
			{
				// If p1 and p2 are the same then we should remove p1
				const hkReal minDistance = 0.1f;
				hkReal distance = surfaceDistance( m_manifold[p1], m_manifold[p2] );
				if ( distance < minDistance )
				{
					remove = true;
					break;
				}
			}
			if ( remove )
			{
				fireContactRemoved( m_manifold[p1] );
				m_manifold.removeAt( p1 );
			}
		}
	}

	// add entity listener to bodies in the manifold
	{
		for (int i=0 ; i < m_manifold.getSize(); i++)
		{
			hkpRigidBody* body =  hkGetRigidBody(m_manifold[i].m_rootCollidableB);
			if ( body && ( m_bodies.indexOf(body) == -1 ) )
			{
				body->addEntityListener(this);
				m_bodies.pushBack(body);
			}

			hkpPhantom* phantom = hkGetPhantom( m_manifold[i].m_rootCollidableB );
			if (phantom && (m_phantoms.indexOf(phantom) == -1) )
			{
				phantom->addPhantomListener( this );
				m_phantoms.pushBack(phantom);
			}
		}
	}
}


void hkpCharacterProxy::applySurfaceInteractions( const hkStepInfo& stepInfo, const hkVector4& worldGravity )
{
	hkpCharacterObjectInteractionEvent input;
	input.m_timestep = stepInfo.m_deltaTime;

	for (int s=0; s < m_manifold.getSize(); s++)
	{
		hkpWorldObject* object = hkGetWorldObject(m_manifold[s].m_rootCollidableB);

		//
		// Check if we have hit another character
		//
		if (object->hasProperty(HK_PROPERTY_CHARACTER_PROXY))
		{
			hkpPropertyValue val = object->getProperty(HK_PROPERTY_CHARACTER_PROXY);

			hkpCharacterProxy* otherChar = reinterpret_cast<hkpCharacterProxy*>( val.getPtr()) ;

			//
			// Callback to indicate characters have collided
			//
			{
				for ( int i = m_listeners.getSize()-1; i >= 0; i-- )
				{
					if (m_listeners[i] != HK_NULL)
					{
						m_listeners[i]->characterInteractionCallback( this, otherChar, m_manifold[s].m_contact );
					}
				}
			}
		}

		hkpRigidBody* body = hkGetRigidBody(m_manifold[s].m_rootCollidableB);

		//
		// Check if we have hit a rigid body
		//
		if ( ( body != HK_NULL ) && ( !body->isFixedOrKeyframed() ) )
		{

			//
			//	Some constants used
			//
			const hkReal recoveryTau = 0.4f;
			const hkReal dampFactor = 0.9f;
			input.m_position = m_manifold[s].m_contact.getPosition();
			input.m_position(3) = m_manifold[s].m_contact.getDistance();
			input.m_normal  = m_manifold[s].m_contact.getNormal();
			input.m_body = body;


			//
			//	Calculate required velocity change
			//
			hkReal deltaVelocity;
			{
				hkVector4 pointVel; body->getPointVelocity( input.m_position, pointVel );
				pointVel.sub4( m_velocity );

				input.m_projectedVelocity = pointVel.dot3( input.m_normal );

				deltaVelocity = - input.m_projectedVelocity * dampFactor;

				// Only apply an extra impulse if the collision is actually penetrating. HVK-1903
				if ( input.m_position(3) < 0)
				{
					deltaVelocity += input.m_position(3) * stepInfo.m_invDeltaTime * recoveryTau;
				}
			}

			//
			// Initialize the output result
			//
			hkpCharacterObjectInteractionResult output;
			output.m_impulsePosition = input.m_position;
			output.m_objectImpulse.setZero4();

			if (deltaVelocity < 0.0f)
			{
				//
				//	Calculate the impulse required
				//
				{
					hkMatrix3 inertiaInv;
					body->getInertiaInvWorld(inertiaInv);

					hkVector4 r; r.setSub4( input.m_position, body->getCenterOfMassInWorld() );
					hkVector4 jacAng; jacAng.setCross( r, input.m_normal );
					hkVector4 rc; rc.setMul3( inertiaInv, jacAng );

					input.m_objectMassInv = rc.dot3( jacAng );
					input.m_objectMassInv += body->getMassInv();
					input.m_objectImpulse = deltaVelocity / input.m_objectMassInv;
				}

				hkReal maxPushImpulse = - m_characterStrength * stepInfo.m_deltaTime;
				if (input.m_objectImpulse < maxPushImpulse)
				{
					input.m_objectImpulse = maxPushImpulse;
				}

				output.m_objectImpulse.setMul4( input.m_objectImpulse, input.m_normal );
			}
			else
			{
				input.m_objectImpulse = 0.0f;
				input.m_objectMassInv = body->getMassInv();
			}


			// Add gravity
			{
				hkReal deltaTime = stepInfo.m_deltaTime;
				hkVector4 charVelDown; charVelDown.setMul4(deltaTime, worldGravity);

				// Normal points from object to character
				hkReal relVel = charVelDown.dot3(input.m_normal);

				if (input.m_projectedVelocity < 0 ) // if objects are separating
				{
					relVel -= input.m_projectedVelocity;
				}

				if (relVel < -HK_REAL_EPSILON)
				{
					output.m_objectImpulse.addMul4(relVel * m_characterMass, input.m_normal);
				}
			}




			//
			// Callback to allow user to change impulse + use the info / play sounds
			//
			{
				for ( int i = m_listeners.getSize()-1; i >= 0; i-- )
				{
					if (m_listeners[i] != HK_NULL)
					{
						m_listeners[i]->objectInteractionCallback( this, input, output );
					}
				}
			}

			//
			//	Apply impulse based on callback result
			//
			{
				body->applyPointImpulse( output.m_objectImpulse, output.m_impulsePosition );
				HK_ON_DEBUG( HK_DISPLAY_ARROW(input.m_position, output.m_objectImpulse, 0xffffffff) );
			}
		}
	}
}

const hkVector4& hkpCharacterProxy::getPosition() const
{
	return m_shapePhantom->getCollidable()->getTransform().getTranslation();
}


void hkpCharacterProxy::setPosition(const hkVector4& position)
{
	// Tolerance should be the same as the castInput.m_startPointTolerance used in integrateWithCollectors
	m_shapePhantom->setPosition(position, m_keepDistance + m_keepContactTolerance);
}

const hkVector4&	hkpCharacterProxy::getLinearVelocity() const
{
	return m_velocity ;
}

void hkpCharacterProxy::setLinearVelocity( const hkVector4& vel )
{
	m_velocity = vel;
}

hkpShapePhantom*	hkpCharacterProxy::getShapePhantom()
{
	return m_shapePhantom;
}

const hkpShapePhantom* hkpCharacterProxy::getShapePhantom() const
{
	return m_shapePhantom;
}

void hkpCharacterProxy::addCharacterProxyListener( hkpCharacterProxyListener* cpl)
{
	HK_ASSERT2(0x5efeeea3, m_listeners.indexOf( cpl ) < 0, "You tried to add  a character proxy listener listener twice" );
	m_listeners.pushBack( cpl );
}

void hkpCharacterProxy::removeCharacterProxyListener( hkpCharacterProxyListener* cpl)
{
	int i = m_listeners.indexOf( cpl );
	HK_ASSERT2(0x2c6b3925, i >= 0, "You tried to remove a character proxy listener, which was never added" );
	m_listeners.removeAt(i);
}

void hkpCharacterProxy::fireConstraintsProcessed( const hkArray<hkpRootCdPoint>& manifold, hkpSimplexSolverInput& input ) const
{
	for ( int i = m_listeners.getSize()-1; i >= 0; i-- )
	{
		m_listeners[i]->processConstraintsCallback( manifold, input );
	}
}

void hkpCharacterProxy::fireContactAdded(const hkpRootCdPoint& point) const
{
	for ( int i = m_listeners.getSize()-1; i >= 0; i-- )
	{
		m_listeners[i]->contactPointAddedCallback( point );
	}
}

void hkpCharacterProxy::fireContactRemoved(const hkpRootCdPoint& point) const
{
	for ( int i = m_listeners.getSize()-1; i >= 0; i-- )
	{
		m_listeners[i]->contactPointRemovedCallback( point );
	}
}

void hkpCharacterProxy::entityRemovedCallback( hkpEntity* entity )
{
	entity->removeEntityListener( this );

	const int size = m_manifold.getSize();
	for (int p1 = size-1; p1 >= 0; p1--)
	{
		hkpRigidBody* body =  hkGetRigidBody(m_manifold[p1].m_rootCollidableB);
		if (body == entity)
		{
			m_manifold.removeAt(p1);
		}
	}

	hkpRigidBody* oldBody = static_cast<hkpRigidBody*>(entity);
	HK_ASSERT2(0x49c85c9f, m_bodies.indexOf( oldBody )!=-1, "Could not find entity in manifold");
	m_bodies.removeAt( m_bodies.indexOf(oldBody) );
}

void hkpCharacterProxy::phantomRemovedCallback( hkpPhantom* phantom )
{
	phantom->removePhantomListener( this );

	const int size = m_manifold.getSize();
	for (int p1 = size-1; p1 >= 0; p1--)
	{
		hkpPhantom* manifoldPhantom =  hkGetPhantom(m_manifold[p1].m_rootCollidableB);
		if (manifoldPhantom == phantom)
		{
			m_manifold.removeAt(p1);
		}
	}

	hkpPhantom* oldPhantom = static_cast<hkpPhantom*>(phantom);
	HK_ASSERT2(0x49c85c8f, m_phantoms.indexOf( oldPhantom )!=-1, "Could not find phantom in manifold");
	m_phantoms.removeAt( m_phantoms.indexOf(oldPhantom) );
}

void hkpCharacterProxy::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->addArray("Manifold" , collector->MEMORY_RUNTIME, m_manifold );
	collector->addArray("OverlapsPntr" , collector->MEMORY_RUNTIME, m_bodies );
	collector->addArray("Manifold" , collector->MEMORY_RUNTIME, m_phantoms );
	collector->addArray("ListnrPntr" , collector->MEMORY_RUNTIME, m_listeners );
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
