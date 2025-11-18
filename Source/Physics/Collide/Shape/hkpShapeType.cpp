/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

	
void HK_CALL hkRegisterAlternateShapeTypes( hkpCollisionDispatcher* dis )
{
	//
	//	Warning: order is important, later entries override earlier entries
	//
	dis->registerAlternateShapeType( HK_SHAPE_SPHERE,					HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_TRIANGLE,					HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_BOX,						HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CAPSULE,					HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CYLINDER,					HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CONVEX_VERTICES,			HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_PACKED_CONVEX_VERTICES,	HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CONVEX_TRANSLATE,			HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CONVEX_TRANSFORM,			HK_SHAPE_CONVEX );
	dis->registerAlternateShapeType( HK_SHAPE_CONVEX_PIECE,				HK_SHAPE_CONVEX );

	dis->registerAlternateShapeType( HK_SHAPE_TRIANGLE_COLLECTION,	HK_SHAPE_COLLECTION );
	dis->registerAlternateShapeType( HK_SHAPE_LIST,			        HK_SHAPE_COLLECTION );
	dis->registerAlternateShapeType( HK_SHAPE_EXTENDED_MESH,		HK_SHAPE_COLLECTION );

	dis->registerAlternateShapeType( HK_SHAPE_MOPP,			        HK_SHAPE_BV_TREE );
	dis->registerAlternateShapeType( HK_SHAPE_MOPP_EMBEDDED,	    HK_SHAPE_BV_TREE );

	dis->registerAlternateShapeType( HK_SHAPE_CONVEX,		        HK_SHAPE_SPHERE_REP );

	dis->registerAlternateShapeType( HK_SHAPE_PLANE,		        HK_SHAPE_HEIGHT_FIELD );
	dis->registerAlternateShapeType( HK_SHAPE_SAMPLED_HEIGHT_FIELD, HK_SHAPE_HEIGHT_FIELD );
}
	
const char* HK_CALL hkGetShapeTypeName( hkpShapeType type )
{
#define X(a) case a: return #a; break
	switch(type)
	{
		X(HK_SHAPE_INVALID);
		X(HK_SHAPE_ALL);
		X(HK_SHAPE_CONVEX);
		X(HK_SHAPE_COLLECTION);
		X(HK_SHAPE_BV_TREE);
		X(HK_SHAPE_SPHERE);
		X(HK_SHAPE_TRIANGLE);
		X(HK_SHAPE_BOX);

		X(HK_SHAPE_CAPSULE);
		X(HK_SHAPE_CYLINDER);
		X(HK_SHAPE_CONVEX_VERTICES);
		X(HK_SHAPE_PACKED_CONVEX_VERTICES);		
		X(HK_SHAPE_CONVEX_PIECE);
		
		X(HK_SHAPE_MULTI_SPHERE);
		X(HK_SHAPE_LIST);
		X(HK_SHAPE_MOPP_EMBEDDED);
		X(HK_SHAPE_CONVEX_LIST);
		X(HK_SHAPE_TRIANGLE_COLLECTION);
		X(HK_SHAPE_MULTI_RAY);
		X(HK_SHAPE_HEIGHT_FIELD);
		X(HK_SHAPE_SAMPLED_HEIGHT_FIELD);
		X(HK_SHAPE_SPHERE_REP);
		X(HK_SHAPE_BV);
		X(HK_SHAPE_PLANE);
		X(HK_SHAPE_MOPP);
		X(HK_SHAPE_TRANSFORM);
		X(HK_SHAPE_CONVEX_TRANSLATE);
		X(HK_SHAPE_CONVEX_TRANSFORM);
		X(HK_SHAPE_EXTENDED_MESH);
		X(HK_SHAPE_MAX_ID_SPU);
		X(HK_SHAPE_PHANTOM_CALLBACK);

		X(HK_SHAPE_USER0);
		X(HK_SHAPE_USER1);
		X(HK_SHAPE_USER2);

		default: return HK_NULL;
	}
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
