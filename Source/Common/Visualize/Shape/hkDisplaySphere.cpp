/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h> //PCH
#include <Common/Visualize/Shape/hkDisplaySphere.h>

hkDisplaySphere::hkDisplaySphere(const hkSphere& sphere, int xRes, int yRes) 
:  hkDisplayGeometry(HK_DISPLAY_SPHERE) , 
   m_sphere(sphere), m_xRes(xRes), m_yRes(yRes)
{

}


static void _subdivideRecursive( hkGeometry& geometry, int triIndex, const hkReal radius, hkReal recursionsLeft )
{
	if( recursionsLeft == 0 )
	{
		return;
	}
	
	// allocate space for new vertices and triangles
	int nV = geometry.m_vertices.getSize();
	int nT = geometry.m_triangles.getSize();
	geometry.m_vertices.expandBy( 3 );
	geometry.m_triangles.expandBy( 3 );
	
	hkGeometry::Triangle& t = geometry.m_triangles[ triIndex ];
	
	// set vertex data
	{
		hkVector4& v1 = geometry.m_vertices[ t.m_a ];
		hkVector4& v2 = geometry.m_vertices[ t.m_b ];
		hkVector4& v3 = geometry.m_vertices[ t.m_c ];
		hkVector4& v12 = geometry.m_vertices[ nV ];
		hkVector4& v23 = geometry.m_vertices[ nV+1 ];
		hkVector4& v31 = geometry.m_vertices[ nV+2 ];
		v12.setAdd4( v1, v2 ); v12.normalize3(); v12.mul4( radius );
		v23.setAdd4( v2, v3 ); v23.normalize3(); v23.mul4( radius );
		v31.setAdd4( v3, v1 ); v31.normalize3(); v31.mul4( radius );
	}
	
	// set triangle data
	{
		hkGeometry::Triangle& t1 = geometry.m_triangles[ nT ];
		hkGeometry::Triangle& t2 = geometry.m_triangles[ nT+1 ];
		hkGeometry::Triangle& t3 = geometry.m_triangles[ nT+2 ];
		t1.m_a = t.m_a;	t1.m_b = nV;	t1.m_c = nV+2;
		t2.m_a = nV;	t2.m_b = t.m_b;	t2.m_c = nV+1;
		t3.m_a = nV+2;	t3.m_b = nV+1;	t3.m_c = t.m_c;
		t.m_a = nV;		t.m_b = nV+1;	t.m_c = nV+2;
	}
	
	// recurse
	{
		_subdivideRecursive( geometry, nT, radius, recursionsLeft-1 );
		_subdivideRecursive( geometry, nT+1, radius, recursionsLeft-1 );
		_subdivideRecursive( geometry, nT+2, radius, recursionsLeft-1 );
		_subdivideRecursive( geometry, triIndex, radius, recursionsLeft-1 );
	}
}


void hkDisplaySphere::buildGeometry()
{
	m_geometry = new hkGeometry;
	hkReal r = m_sphere.getRadius();
	
	// Create an Icosahedron
	{
		hkReal x = r * 0.525731112119133606f;
		hkReal z = r * 0.850650808352039932f;
		int i;
		
		hkArray<hkVector4>& v = m_geometry->m_vertices;
		v.setSize( 12 );
		i=0;
		v[i++].set( -x, 0.0f, z );
		v[i++].set( x, 0.0, z );
		v[i++].set( -x, 0.0, -z );
		v[i++].set( x, 0.0, -z );    
		v[i++].set( 0.0, z, x );
		v[i++].set( 0.0, z, -x );
		v[i++].set( 0.0, -z, x );
		v[i++].set( 0.0, -z, -x );    
		v[i++].set( z, x, 0.0 );
		v[i++].set( -z, x, 0.0 );
		v[i++].set( z, -x, 0.0 );
		v[i++].set( -z, -x, 0.0 );
		
		hkArray<hkGeometry::Triangle>& t = m_geometry->m_triangles;
		t.setSize( 20 );
		i=0;
		t[i++].set( 1,4,0 );
		t[i++].set( 4,9,0 );
		t[i++].set( 4,5,9 );
		t[i++].set( 8,5,4 );
		t[i++].set( 1,8,4 );
		t[i++].set( 1,10,8 );
		t[i++].set( 10,3,8 );
		t[i++].set( 8,3,5 );
		t[i++].set( 3,2,5 );
		t[i++].set( 3,7,2 );
		t[i++].set( 3,10,7 );
		t[i++].set( 10,6,7 );
		t[i++].set( 6,11,7 );
		t[i++].set( 6,0,11 );
		t[i++].set( 6,1,0 );
		t[i++].set( 10,1,6 );
		t[i++].set( 11,0,9 );
		t[i++].set( 2,11,9 );
		t[i++].set( 5,2,9 );
		t[i++].set( 11,2,7 );
	}
	
	// Subdivide each triangle a bunch of times
	// (Ignores xRes and yRes for now)
	for( int i=0; i<20; ++i )
	{
		_subdivideRecursive( *m_geometry, i, r, 2 );
	}
}

void hkDisplaySphere::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	//TODO
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
