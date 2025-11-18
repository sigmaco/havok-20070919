/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics/Collide/Shape/HeightField/Plane/hkpPlaneShape.h>
#include <Physics/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h>

//
// raycast_tests method, actually does the ray tests
//
static void HK_CALL sphereCast_tests( const hkpHeightFieldShape* shape, const char* desciption )
{
	HK_ALIGN16( hkpHeightFieldShape::hkpSphereCastInput input );

	hkpClosestRayHitCollector collector;
	hkpCollidable cdBody(HK_NULL, &hkTransform::getIdentity());

	//
	// test parallel ray on the surface
	//
	{
		input.m_from.set( 1.0f, 0.0f, 1.0f);
		input.m_to.set( 3.0f, 0.0f, 3.0f);
		input.m_radius = 0.0f;
		input.m_maxExtraPenetration = 0.1f;
		collector.reset();
		shape->castSphere( input, cdBody, collector );
		HK_TEST2( collector.hasHit() == false, desciption );
	}

	//
	// test penetrating ray leaving the surface
	//
	{
		input.m_from.set( 1.0f, -0.1f, 1.0f);
		input.m_to.set( 3.0f, 0.0f, 3.0f);
		input.m_radius = 0.0f;
		input.m_maxExtraPenetration = 0.1f;
		collector.reset();
		shape->castSphere( input, cdBody, collector );
		HK_TEST2( collector.hasHit() == false, desciption );
	}

	//
	// test penetrating ray nearly parallel (only slightly coming closer), no hit
	//
	{
		input.m_from.set( 1.0f, -0.1f, 1.0f);
		input.m_to.set( 3.0f, -0.2f, 3.0f);
		input.m_radius = 0.0f;
		input.m_maxExtraPenetration = 0.12f;
		collector.reset();
		shape->castSphere( input, cdBody, collector );
		HK_TEST2( collector.hasHit() == false, desciption );
	}

	//
	// test penetrating ray nearly parallel (only slightly coming closer), hit
	//
	{
		input.m_from.set( 1.0f, -0.1f, 1.0f);
		input.m_to.set( 3.0f, -0.2f, 3.0f);
		input.m_radius = 0.0f;
		input.m_maxExtraPenetration = 0.08f;
		collector.reset();
		shape->castSphere( input, cdBody, collector );
		HK_TEST2( collector.hasHit() == true, desciption );
	}
}




class SphereTestFieldShape : public hkpSampledHeightFieldShape
{
public:

	SphereTestFieldShape( const hkpSampledHeightFieldBaseCinfo& ci )
		: hkpSampledHeightFieldShape(ci)
	{
	}

	HK_FORCE_INLINE hkReal getHeightAt( int x, int z ) const
	{
		return 0.0f;
	}

	HK_FORCE_INLINE hkBool getTriangleFlip() const
	{	
		return false;
	}

	virtual void collideSpheres( const CollideSpheresInput& input, SphereCollisionOutput* outputArray) const
	{
		hkSampledHeightFieldShape_collideSpheres(*this, input, outputArray);
	}
};


//
// Havok2 raycast test
//
int SphereCast_test()
{
	hkpHeightFieldShape* planeShape;
	{
		hkAabb aabb;
		aabb.m_min.set( -8, -8, -8);
		aabb.m_max.set(  8,  8,  8);
		hkVector4 plane; plane.set( 0.0f, 1.0f, 0.0f, 0.0f);
		planeShape = new hkpPlaneShape( plane, aabb );
	}

	hkpHeightFieldShape* hfShape;
	{
		hkpSampledHeightFieldBaseCinfo ci;
		ci.m_xRes = 8;
		ci.m_zRes = 8;
		hfShape = new SphereTestFieldShape( ci );
	}

	sphereCast_tests( planeShape, "PlaneShape" );
	sphereCast_tests( hfShape, "HeightField" );

	hfShape->removeReference();
	planeShape->removeReference();
	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(SphereCast_test, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
