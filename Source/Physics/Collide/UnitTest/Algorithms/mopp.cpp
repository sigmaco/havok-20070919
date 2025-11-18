/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// This checks the mopp 
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

// We will need these shapes.
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>

#include <Physics/Collide/hkpCollide.h>
// Used to create the Mopp 'code' object
#include <Physics/Internal/Collide/Mopp/Machine/hkpMoppSphereVirtualMachine.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>

// A class that is used to create a very simple mopp
class MoppBoxMeshShape:public hkpShapeCollection
{
	hkAabb m_bounds;
	hkVector4 m_vertices[8];

	public:
		MoppBoxMeshShape(const hkVector4& min, const hkVector4& max): hkpShapeCollection( HK_SHAPE_COLLECTION ), m_bounds(min, max)
	{
		for (int i= 0; i<8; ++i)
		{
			m_vertices[i].set(!(i&1)?min(0):max(0), !(i&2)?min(1):max(1), !(i&4)?min(2):max(2));
		}
	}

	virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const
	{
		hkVector4 tolerance4;

		tolerance4.setAll(tolerance);

		out.m_min.setSub4(m_bounds.m_min, tolerance4);
		out.m_max.setAdd4(m_bounds.m_max, tolerance4);
	}

	virtual int getNumChildShapes() const
	{
		return 12;
	}

	virtual hkpShapeKey getFirstKey() const
	{
		return 0;
	}

	virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const
	{
		if ( oldKey < 11 )
		{
			return oldKey + 1;
		}
		else
		{
			return HK_INVALID_SHAPE_KEY;
		}
	}
	
	virtual const hkpShape* getChildShape(hkpShapeKey key, ShapeBuffer& buffer) const
	{
		const int vertex_indices[12][3]=
		{
			{0, 1, 2}, {3, 2, 1}, {5, 4, 7}, {6, 7, 4}, // xy
			{0, 4, 1}, {5, 1, 4}, {3, 7, 2}, {6, 2, 7}, // xz
			{0, 2, 4}, {6, 4, 2}, {3, 1, 7}, {5, 7, 1}  // yz
		};

		hkpTriangleShape *triangle_shape= new(buffer) hkpTriangleShape;

		triangle_shape->setVertex(0, m_vertices[vertex_indices[key][0]]);
		triangle_shape->setVertex(1, m_vertices[vertex_indices[key][1]]);
		triangle_shape->setVertex(2, m_vertices[vertex_indices[key][2]]);

		return triangle_shape;
	}
};


void check_negativeIDs()
{
	MoppBoxMeshShape *listShape;
	{
		hkVector4 v1, v2;
		v1.set(-10, -10, 0);
		v2.set(10, 10, 10);
		listShape = new MoppBoxMeshShape( v1, v2 );
	}
	hkpMoppCompilerInput moppInput;
	moppInput.setAbsoluteFitToleranceOfTriangles(0.1f);
	
	
	// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
	bool wasEnabled = hkError::getInstance().isEnabled(0x6e8d163b); // hkpMoppUtility.cpp:18
	hkError::getInstance().setEnabled(0x6e8d163b, false);
	hkpMoppCode* code = hkpMoppUtility::buildCode(listShape, moppInput);
	hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled);

	

	hkpMoppBvTreeShape* shape = new hkpMoppBvTreeShape(listShape, code);
		// Remove references since the MoppBvTreeShape now "owns" the listShape and code
	code->removeReference();
	listShape->removeReference();
	///////////////////////////////////////////////////////

	hkVector4 pos; pos.set( 0.0f, 0.0f, 0.0f, 100.0f );
	hkpMoppSphereVirtualMachine sm;
	hkArray<hkpMoppPrimitiveInfo> prims;
	hkSphere sphere;
	sphere.setPositionAndRadius(pos);

	sm.querySphere(code,sphere,&prims);

	/*
	for(int counter = 0; counter < prims.getSize()-1; counter++)
	{
		HK_TEST2( (prims[counter].properties[0] == (prims[counter].ID - 4)),"MOPP returning incorrect properties");
	}
	*/

	shape->removeReference();
}
	
int mopp_main()
{
	check_negativeIDs();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(mopp_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
