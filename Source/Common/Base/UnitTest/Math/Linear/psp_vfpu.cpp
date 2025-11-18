/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

#if defined(HK_PLATFORM_PSP)
// psp
#include <psptypes.h>
#include <kernel.h>
#include <stdio.h>

// compare fpu / vfpu performance
#define PERFORM_FPU_VFPU_COMPARISON

// number of iterations
#define NUM_ITERATIONS 1000

//
// FPU implementations for comparison
//

// hkMatrix3
inline void hkMatrix3SetZero( hkMatrix3* matrix );
inline void hkMatrix3SetIdentity( hkMatrix3* matrix );
inline void hkMatrix3SetDiagonal( hkMatrix3* matrix, hkReal m00, hkReal m11, hkReal m22 );

// hkVector4
inline void hkVector4SetCross( hkVector4& vector, hkVector4& v1, hkVector4& v2 );
inline void hkVector4SetMin4( hkVector4& vector, hkVector4& a, hkVector4& b );
inline void hkVector4SetMax4( hkVector4& vector, hkVector4& a, hkVector4& b );
inline void hkVector4InlineSetMul3( hkVector4& vector, hkMatrix3& r, hkVector4& v );
inline void hkVector4InlineSetMul4( hkVector4& vector, hkMatrix3& t, hkVector4& v );
inline void hkVector4InlineSetMul4xyz1( hkVector4& vector, hkTransform& t, hkVector4& v );
inline void hkVector4InlineSetRotatedInverseDir( hkVector4& vector, hkRotation& r, hkVector4& v );
inline void hkVector4InlineSetTransformedInversePos( hkVector4& vector, hkTransform& t, hkVector4& v );

inline hkSimdReal hkVector4InlineLength3( hkVector4& vector );
inline hkSimdReal hkVector4InlineLengthInverse3( hkVector4& vector );
inline hkSimdReal hkVector4InlineLength4( hkVector4& vector );
inline hkSimdReal hkVector4InlineLengthInverse4( hkVector4& vector );

inline void hkVector4InlineNormalize3( hkVector4& vector );
inline hkSimdReal hkVector4InlineNormalizeWithLength3( hkVector4& vector );
inline void hkVector4InlineNormalize4( hkVector4& vector );
inline hkSimdReal hkVector4InlineNormalizeWithLength4( hkVector4& vector );

// additional
hkReal hkFloorFpu( hkReal r );
int hkFloorToIntFpu( hkReal r );
int hkFloatToIntFpu(hkReal r);

inline void hkVector4UtilInlineTransformPoints( const hkTransform& t, const hkVector4* vectorsIn, int numVectors, hkVector4* vectorsOut );


int psp_vfpu_main()
{
	// hkMatrix3 VFPU tests
	{
		// setZero
		{
			hkMatrix3 matrixA, matrixB;
			matrixA.setIdentity();
			matrixB.setIdentity();

			hkMatrix3SetZero( &matrixA );
			matrixB.setZero();

			for( int i = 0; i < 3; i++ )
			{
				hkVector4 a = matrixA.getColumn( i );
				hkVector4 b = matrixB.getColumn( i );

				HK_TEST( a.equals4( b ) );
			}
		}

		// setIdentity
		{
			hkMatrix3 matrixA, matrixB;
			matrixA.setZero();
			matrixB.setZero();

			hkMatrix3SetIdentity( &matrixA );
			matrixB.setIdentity();

			for( int i = 0; i < 3; i++ )
			{
				hkVector4 a = matrixA.getColumn( i );
				hkVector4 b = matrixB.getColumn( i );

				HK_TEST( a.equals4( b ) );
			}

		}

		// setDiagonal
		{
			hkMatrix3 matrixA, matrixB;
			matrixA.setZero();
			matrixB.setZero();

			hkMatrix3SetDiagonal( &matrixA, 1.0f, 2.0f, 3.0f );
			matrixB.setDiagonal( 1.0f, 2.0f, 3.0f );

			for( int i = 0; i < 3; i++ )
			{
				hkVector4 a = matrixA.getColumn( i );
				hkVector4 b = matrixB.getColumn( i );

				HK_TEST( a.equals4( b ) );

				if( !a.equals4( b ) )
				{
					printf("a[%i] : ( %f, %f, %f )\n", i, a(0), a(1), a(2) );
					printf("b[%i] : ( %f, %f, %f )\n\n", i, b(0), b(1), b(2) );
				}

			}
		}

	}

	// hkVector4 VFPU tests
	{
		// setCross
		{
			hkVector4 x( 1.0f, 0.0f, 0.0f );
			hkVector4 y( 0.0f, 1.0f, 0.0f );

			hkVector4 u, v;
			hkVector4SetCross( u, x, y );
			v.setCross( x, y );

			HK_TEST( u.equals4( v ) );

			HK_TEST( hkMath::equal( u(0), 0.0f ) );
			HK_TEST( hkMath::equal( u(1), 0.0f ) );
			HK_TEST( hkMath::equal( u(2), 1.0f ) );
		}

		// setMin4
		{
			hkVector4 a( -1, 2, -6, 9 );
			hkVector4 b( -100, 555, 0, 1e5f );

			hkVector4 c, d;
			hkVector4SetMin4( c, a, b );
			d.setMin4( a, b );

			HK_TEST( c.equals4( d ) );

			HK_TEST( c(0) == -100 );
			HK_TEST( c(1) == 2 );
			HK_TEST( c(2) == -6 );
			HK_TEST( c(3) == 9 );

		}

		// setMax4
		{
			hkVector4 a( -1, 2, -6, 9 );
			hkVector4 b( -100, 555, 0, 1e5f );

			hkVector4 c, d;
			hkVector4SetMax4( c, a, b );
			d.setMax4( a, b );

			HK_TEST( c.equals4( d ) );

			HK_TEST( c(0) == -1 );
			HK_TEST( c(1) == 555 );
			HK_TEST( c(2) == 0 );
			HK_TEST( c(3) == 1e5f );

		}

		// _setMul3
		{
			hkVector4 c0( 4, 1, 7 );
			hkVector4 c1( 9, 5, 2 );
			hkVector4 c2( 8, 6, 4 );

			hkMatrix3 m;
			m.setCols( c0, c1, c2 );
			hkVector4 v0( 1, 2, 3 );
			
			hkVector4 v1, v2;
			hkVector4InlineSetMul3( v1, m, v0 );
			v2._setMul3( m, v0 );

			HK_TEST( v1.equals4( v2 ) );

			HK_TEST( v1(0) == 46 );
			HK_TEST( v1(1) == 29 );
			HK_TEST( v1(2) == 23 );

		}

		// _setMul4
		{
			hkVector4 c0( 4, 1, 7, 1 );
			hkVector4 c1( 9, 5, 2, 2 );
			hkVector4 c2( 8, 6, 4, 3 );

			hkMatrix3 m;
			m.setCols( c0, c1, c2 );
			hkVector4 v0( 1, 2, 3, 4 );
			
			hkVector4 v1, v2;
			hkVector4InlineSetMul4( v1, m, v0 );
			v2._setMul4( m, v0 );

			HK_TEST( v1.equals4( v2 ) );

			HK_TEST( v1(0) == 46 );
			HK_TEST( v1(1) == 29 );
			HK_TEST( v1(2) == 23 );
			HK_TEST( v1(3) == 14 );

		}

		// _setMul4xyz1
		{
			hkMatrix3 m;
			hkVector4 c0( 4, 1, 7 );
			hkVector4 c1( 9, 5, 2 );
			hkVector4 c2( 8, 6, 4 );
			m.setCols( c0, c1, c2 );
		
			hkRotation r;
			hkVector4 axis( 1.0f, 0.0f, 0.0f );
			r.setAxisAngle( axis, 0.5f );

			hkVector4 v( 1, 2, 3, 4 );			
			hkTransform t( r, v );

			hkVector4 v0( 1, 2, 1, 2 );
			hkVector4 v1, v2;
			hkVector4InlineSetMul4xyz1( v1, t, v0 );
			v2._setMul4xyz1( t, v0 );

			HK_TEST( v1.equals4( v2 ) );

		}

		// _setRotatedInverseDir
		{
			hkRotation r;
			hkVector4 axis( 1.0f, 0.0f, 0.0f );
			r.setAxisAngle( axis, 0.5f );
			
			hkVector4 v0( 1, 2, 3 );
			hkVector4 v1, v2;
			hkVector4InlineSetRotatedInverseDir( v1, r, v0 );
			v2._setRotatedInverseDir( r, v0 );

			HK_TEST( v1.equals4( v2 ) );

		}

		// _setTransformedInversePos
		{
			hkMatrix3 m;
			hkVector4 c0( 4, 1, 7 );
			hkVector4 c1( 9, 5, 2 );
			hkVector4 c2( 8, 6, 4 );
			m.setCols( c0, c1, c2 );
		
			hkRotation r;
			hkVector4 axis( 1.0f, 0.0f, 0.0f );
			r.setAxisAngle( axis, 0.5f );

			hkVector4 v( 1, 2, 3, 4 );			
			hkTransform t( r, v );

			hkVector4 v0( 1, 2, 1, 5 );
			hkVector4 v1, v2;
			hkVector4InlineSetTransformedInversePos( v1, t, v0 );
			v2._setTransformedInversePos( t, v0 );

			HK_TEST( v1.equals4( v2 ) );

		}

		// length3
		{
			hkVector4 v( 3.4f, 7.2f, 8.9f );

			hkSimdReal lengthA = hkVector4InlineLength3( v );
			hkSimdReal lengthB = v.length3();

			HK_TEST( lengthA == lengthB );

			if( lengthA != lengthB )
			{
				printf( "\nlength3 failed.\n" );
				printf( "lengthA: %f  -  lengthB: %f (vfpu)\n\n", lengthA, lengthB );
			}
		}

		// lengthInverse3
		{
			hkVector4 v( 3.4f, 7.2f, 8.9f );

			hkSimdReal invLengthA = hkVector4InlineLengthInverse3( v );
			hkSimdReal invLengthB = v.lengthInverse3();

			HK_TEST( invLengthA == invLengthB );

			if( invLengthA != invLengthB )
			{
				printf( "\nlengthInverse3 failed.\n" );
				printf( "\nvLengthA: %f  -  invLengthB: %f (vfpu)\n\n", invLengthA, invLengthB );
			}
		}

		// length4
		{
			hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

			hkSimdReal lengthA = hkVector4InlineLength4( v );
			hkSimdReal lengthB = v.length4();

			HK_TEST( lengthA == lengthB );

			if( lengthA != lengthB )
			{
				printf( "\nlength4 failed.\n" );
				printf( "lengthA: %f  -  lengthB: %f (vfpu)\n\n", lengthA, lengthB );
			}
		}

		// lengthInverse4
		{
			hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

			hkSimdReal invLengthA = hkVector4InlineLengthInverse4( v );
			hkSimdReal invLengthB = v.lengthInverse4();

			HK_TEST( invLengthA == invLengthB );

			if( invLengthA != invLengthB )
			{
				printf( "\nlengthInverse4 failed.\n" );
				printf( "invLengthA: %f  -  invLengthB: %f (vfpu)\n\n", invLengthA, invLengthB );
			}
		}

		// normalize3
		{
			hkVector4 vectorA( 5.6f, 8.1f, 7.6f, 2.3f );
			hkVector4 vectorB( 5.6f, 8.1f, 7.6f, 2.3f );

			hkVector4InlineNormalize3( vectorA );
			vectorB.normalize3();

			HK_TEST( vectorA.equals4( vectorB ) );

			if( !vectorA.equals4( vectorB ) )
			{
				printf( "\nnormalize3 failed.\n" );
				printf( "vectorA: ( %f, %f, %f )\n", vectorA(0), vectorA(1), vectorA(2) );
				printf( "vectorB: ( %f, %f, %f ) (vfpu)\n", vectorB(0), vectorB(1), vectorB(2) );
			}
		}

		// normalizeWithLength3
		{
			hkVector4 vectorA( 5.6f, 8.1f, 7.6f, 2.3f );
			hkVector4 vectorB( 5.6f, 8.1f, 7.6f, 2.3f );

			hkSimdReal normalisedA = hkVector4InlineNormalizeWithLength3( vectorA );
			hkSimdReal normalisedB = vectorB.normalizeWithLength3();

			HK_TEST( normalisedA == normalisedB );
			HK_TEST( vectorA.equals4( vectorB ) );

			if( ( !vectorA.equals4( vectorB ) ) || ( normalisedA != normalisedB ) )
			{
				printf( "\nnormalizeWithLength3 failed.\n" );
				printf( "normalisedA: %f  -  normalisedB: %f\n", normalisedA, normalisedB );
				printf( "vectorA: ( %f, %f, %f )\n", vectorA(0), vectorA(1), vectorA(2) );
				printf( "vectorB: ( %f, %f, %f ) (vfpu)\n", vectorB(0), vectorB(1), vectorB(2) );
			}
		}

		// normalize4
		{
			hkVector4 vectorA( 5.6f, 8.1f, 7.6f, 2.3f );
			hkVector4 vectorB( 5.6f, 8.1f, 7.6f, 2.3f );

			hkVector4InlineNormalize4( vectorA );
			vectorB.normalize4();

			HK_TEST( vectorA.equals4( vectorB ) );

			if( !vectorA.equals4( vectorB ) )
			{
				printf( "\nnormalize4 failed.\n" );
				printf( "vectorA: ( %f, %f, %f )\n", vectorA(0), vectorA(1), vectorA(2) );
				printf( "vectorB: ( %f, %f, %f ) (vfpu)\n", vectorB(0), vectorB(1), vectorB(2) );
			}
		}

		// normalizeWithLength4
		{
			hkVector4 vectorA( 5.6f, 8.1f, 7.6f, 2.3f );
			hkVector4 vectorB( 5.6f, 8.1f, 7.6f, 2.3f );

			hkSimdReal normalisedA = hkVector4InlineNormalizeWithLength4( vectorA );
			hkSimdReal normalisedB = vectorB.normalizeWithLength4();

			HK_TEST( normalisedA == normalisedB );
			HK_TEST( vectorA.equals4( vectorB ) );

			if( ( !vectorA.equals4( vectorB ) ) || ( normalisedA != normalisedB ) )
			{
				printf( "\nnormalizeWithLength4 failed.\n" );
				printf( "normalisedA: %f  -  normalisedB: %f\n", normalisedA, normalisedB );
				printf( "vectorA: ( %f, %f, %f )\n", vectorA(0), vectorA(1), vectorA(2) );
				printf( "vectorB: ( %f, %f, %f ) (vfpu)\n", vectorB(0), vectorB(1), vectorB(2) );
			}
		}

	}

	// additional VFPU tests
	{
		// sqrt
		{
			hkReal r = 0.456f;

			hkReal sqrtA = ::sqrtf( r );
			hkReal sqrtB = hkMath::sqrt( r );
	
			HK_TEST( sqrtA == sqrtB );

			if( sqrtA != sqrtB )
			{
				printf( "\nsqrt failed.\n" );
				printf( "sqrtA: %f  -  sqrtB: %f\n\n", sqrtA, sqrtB );
			}
		}

		// sqrtInverse
		{
			hkReal r = 0.456f;

			hkReal invSqrtA = 1.0f / ( ::sqrtf( r ) );
			hkReal invSqrtB = hkMath::sqrtInverse( r );
	
			HK_TEST( invSqrtA == invSqrtB );

			if( invSqrtA != invSqrtB )
			{
				printf( "\nsqrtInverse failed.\n" );
				printf( "invSqrtA: %f  -  invSqrtB: %f\n\n", invSqrtA, invSqrtB );
			}
		}

		// sin
		{
			hkReal r = 0.768f;

			hkReal sinA = ::sinf( r );
			hkReal sinB = hkMath::sin( r );

			HK_TEST( sinA == sinB );

			if( sinA != sinB )
			{
				printf( "\nsin failed.\n" );
				printf( "sinA: %f  -  sinB: %f\n\n", sinA, sinB );
			}

		}

		// cos
		{
			hkReal r = 0.768f;

			hkReal cosA = ::cosf( r );
			hkReal cosB = hkMath::cos( r );

			HK_TEST( cosA == cosB );

			if( cosA != cosB )
			{
				printf( "\ncos failed.\n" );
				printf( "cosA: %f  -  cosB: %f\n\n", cosA, cosB );
			}

		}

		// asin
		{
			hkReal r = 0.768f;

			hkReal asinA = ::asinf( r );
			hkReal asinB = hkMath::asin( r );

			HK_TEST( asinA == asinB );

			if( asinA != asinB ) 
			{
				printf( "\nasin failed.\n" );
				printf( "asinA: %f  -  asinB: %f\n\n", asinA, asinB );
			}

		}

		// acos
		{
			hkReal r = 0.768f;

			hkReal acosA = ::acosf( r );
			hkReal acosB = hkMath::acos( r );

			HK_TEST( acosA == acosB );

			if( acosA != acosB )
			{
				printf( "\nacos failed.\n" );
				printf( "acosA: %f  -  acosB: %f\n\n", acosA, acosB );
			}
		}

		// floor
		{
			hkReal v = 11.234f;

			hkReal floorA = ::floorf( v );
			hkReal floorB = hkMath::floor( v );

			HK_TEST( floorA == floorB );

			if( floorA != floorB )
			{
				printf( "\nfloor failed.\n" );
				printf( "floorA: %f  -  floorB: %f\n\n", floorA, floorB );
			}
		}

		// hkFloor
		{
			hkReal v = 11.234f;

			hkReal hkFloorA = hkFloorFpu( v );
			hkReal hkFloorB = hkMath::hkFloor( v ); 

			HK_TEST( hkFloorA == hkFloorB );

			if( hkFloorA != hkFloorB )
			{
				printf( "\nhkFloor failed.\n" );
				printf( "hkFloorA: %f  -  hkFloorB: %f\n\n", hkFloorA, hkFloorB );
			}

		}

		// hkFloorToInt
		{
			hkReal v = 11.234f;

			int hkFloorToIntA = hkFloorToIntFpu( v );
			int hkFloorToIntB = hkMath::hkFloorToInt( v ); 

			HK_TEST( hkFloorToIntA == hkFloorToIntB );

			if( hkFloorToIntA != hkFloorToIntB )
			{
				printf( "\nhkFloorToInt failed.\n" );
				printf( "hkFloorToIntA: %i  -  hkFloorToIntB: %i\n\n", hkFloorToIntA, hkFloorToIntB );
			}

		}

		// hkFloatToInt
		{
			hkReal v = 11.234f;

			int hkFloatToIntA = hkFloatToIntFpu( v );
			int hkFloatToIntB = hkMath::hkFloatToInt( v ); 

			HK_TEST( hkFloatToIntA == hkFloatToIntB );

			if( hkFloatToIntA != hkFloatToIntB )
			{
				printf( "\nhkFloatToInt failed.\n" );
				printf( "hkFloatToIntA: %i  -  hkFloatToIntB: %i\n\n", hkFloatToIntA, hkFloatToIntB );
			}
		}

		// transform points
		{
			hkPseudoRandomGenerator random(11);
			for ( int i= 0; i < 4; i++ )
			{
				hkVector4 in;
				random.getRandomVector11( in );
				
				hkTransform t;
				hkRotation& r = t.getRotation();
				random.getRandomRotation( r );
				random.getRandomVector11( t.getTranslation() );

				hkVector4 tpA, tpB;
				hkVector4Util::transformPoints( t, &in, 1, &tpA );
				hkVector4UtilInlineTransformPoints( t, &in, 1, &tpB );

				HK_TEST( tpA.equals4( tpB ) );

			}			

		}

	}

// compare fpu / vfpu performance? 
#if defined( PERFORM_FPU_VFPU_COMPARISON )

	// iteration
	int i = 0;

	// start / end time, difference
	hkUint32 startTimeA, endTimeA;
	hkUint32 startTimeB, endTimeB;
	hkUint32 diffA, diffB;

	printf( "\n\nFunction\t\t\t| FPU (us)\t| Vector FPU (us)\n" );
	printf( "-----------------------------------------------------------------\n" );

	// setZero
	{
		hkMatrix3 matrixA, matrixB;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkMatrix3SetZero( &matrixA );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			matrixB.setZero();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "setZero\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// setIdentity
	{
		hkMatrix3 matrixA, matrixB;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkMatrix3SetIdentity( &matrixA );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			matrixB.setIdentity();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "setIdentity\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// setCross
	{
		hkVector4 x( 1.0f, 0.0f, 0.0f );
		hkVector4 y( 0.0f, 1.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4SetCross( y, x, y );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			y.setCross( x, y );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "setCross\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// setMin4
	{
		hkVector4 a( -1, 2, -6, 9 );
		hkVector4 b( -100, 555, 0, 1e5f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4SetMin4( b, a, b );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			b.setMin4( a, b );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "setMin4\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// setMax4
	{
		hkVector4 a( -1, 2, -6, 9 );
		hkVector4 b( -100, 555, 0, 1e5f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4SetMax4( b, a, b );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			b.setMax4( a, b );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "setMax4\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// _setMul3
	{
		hkVector4 c0( 4, 1, 7 );
		hkVector4 c1( 9, 5, 2 );
		hkVector4 c2( 8, 6, 4 );

		hkMatrix3 m;
		m.setCols( c0, c1, c2 );
		
		hkVector4 v1( 0.0f, 0.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineSetMul3( v1, m, v1 );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v1._setMul3( m, v1 );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "_setMul3\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// _setMul4
	{
		hkVector4 c0( 4, 1, 7, 1 );
		hkVector4 c1( 9, 5, 2, 2 );
		hkVector4 c2( 8, 6, 4, 3 );

		hkMatrix3 m;
		m.setCols( c0, c1, c2 );
		
		hkVector4 v1( 0.0f, 0.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineSetMul4( v1, m, v1 );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v1._setMul4( m, v1 );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "_setMul4\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// _setMul4xyz1
	{
		hkMatrix3 m;
		hkVector4 c0( 4, 1, 7 );
		hkVector4 c1( 9, 5, 2 );
		hkVector4 c2( 8, 6, 4 );
		m.setCols( c0, c1, c2 );

		hkRotation r;
		hkVector4 axis( 1.0f, 0.0f, 0.0f );
		r.setAxisAngle( axis, 0.5f );

		hkVector4 v( 1, 2, 3, 4 );			
		hkTransform t( r, v );

		hkVector4 v1( 0.0f, 0.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineSetMul4xyz1( v1, t, v1 );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v1._setMul4xyz1( t, v1 );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "_setMul4xyz1\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// _setRotatedInverseDir
	{
		hkRotation r;
		hkVector4 axis( 1.0f, 0.0f, 0.0f );
		r.setAxisAngle( axis, 0.5f );

		hkVector4 v1( 0.0f, 0.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineSetRotatedInverseDir( v1, r, v1 );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v1._setRotatedInverseDir( r, v1 );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "_setRotatedInverseDir\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	// _setTransformedInversePos
	{
		hkMatrix3 m;
		hkVector4 c0( 4, 1, 7 );
		hkVector4 c1( 9, 5, 2 );
		hkVector4 c2( 8, 6, 4 );
		m.setCols( c0, c1, c2 );
	
		hkRotation r;
		hkVector4 axis( 1.0f, 0.0f, 0.0f );
		r.setAxisAngle( axis, 0.5f );

		hkVector4 v( 1, 2, 3, 4 );			
		hkTransform t( r, v );


		hkVector4 v1( 0.0f, 0.0f, 0.0f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineSetTransformedInversePos( v1, t, v1 );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v1._setTransformedInversePos( t, v1 );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "_setTransformedInversePos\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// length3
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		hkSimdReal length = 1.0f;

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = hkVector4InlineLength3( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = v.length3();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "length3\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// lengthInverse3
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		hkSimdReal length = 1.0f;

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = hkVector4InlineLengthInverse3( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = v.lengthInverse3();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "lengthInverse3\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// length4
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		hkSimdReal length = 1.0f;

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = hkVector4InlineLength4( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = v.length4();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "length4\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// lengthInverse4
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		hkSimdReal length = 1.0f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = hkVector4InlineLengthInverse4( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			length = v.lengthInverse4();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "lengthInverse4\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// normalize3
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineNormalize3( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v.normalize3();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "normalize3\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// normalizeWithLength3
	{
		hkSimdReal normalised = 0.0f;
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			normalised = hkVector4InlineNormalizeWithLength3( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v.normalizeWithLength3();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "normalizeWithLength3\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// normalize4
	{
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			hkVector4InlineNormalize4( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v.normalize4();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "normalize4\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// normalizeWithLength4
	{
		hkSimdReal normalised = 0.0f;
		hkVector4 v( 3.4f, 7.2f, 8.9f, 11.1f );

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			normalised = hkVector4InlineNormalizeWithLength4( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v.normalizeWithLength4();
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "normalizeWithLength4\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// sqrt
	{
		hkReal r = 1234567.89f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = ::sqrtf( r );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 1234567.89f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::sqrt( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "sqrt\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// sqrtInverse
	{
		hkReal r = 1234567.89f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = 1.0f / ( ::sqrtf( r ) );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 1234567.89f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::sqrtInverse( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "sqrtInverse\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// sin
	{
		hkReal r = 0.768f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = ::sinf( r );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 0.768f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::sin( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "sin\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// cos
	{
		hkReal r = 0.768f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = ::cosf( r );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 0.768f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::cos( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "cos\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// asin
	{
		hkReal r = 0.768f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = ::asinf( r );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 0.768f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::asin( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "asin\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// acos
	{
		hkReal r = 0.768f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = ::acosf( r );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset r
		r = 0.768f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			r = hkMath::acos( r );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "acos\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// floor
	{
		hkReal v = 11.234f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = ::floorf( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset v
		v = 11.234f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkMath::floor( v );
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "floor\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// hkFloor
	{
		hkReal v = 11.234f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkFloorFpu( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset v
		v = 11.234f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkMath::hkFloor( v ); 
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "hkFloor\t\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// hkFloorToInt
	{
		hkReal v = 11.234f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkFloorToIntFpu( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset v
		v = 11.234f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkMath::hkFloorToInt( v ); 
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "hkFloorToInt\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// hkFloatToInt
	{
		hkReal v = 11.234f;

		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkFloatToIntFpu( v );
		}

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// reset v
		v = 11.234f;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		for( i = 0; i < NUM_ITERATIONS; i++ )
		{
			v = hkMath::hkFloatToInt( v ); 
		}

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "hkFloatToInt\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}


	// transform points
	{
		hkPseudoRandomGenerator random(1);
		hkVector4 vIn[NUM_ITERATIONS];
		hkVector4 vOut[NUM_ITERATIONS];

		for( int i = 0; i < NUM_ITERATIONS; i++ )
		{
			random.getRandomVector11( vIn[i] );
		}

		hkTransform t;
		hkRotation& r = t.getRotation();
		random.getRandomRotation( r );
		random.getRandomVector11( t.getTranslation() );


		// get the system start time
		startTimeA = sceKernelGetSystemTimeLow();

		// transform the points
		hkVector4UtilInlineTransformPoints( t, &vIn[0], NUM_ITERATIONS, &vOut[0] );

		// get the system end time
		endTimeA = sceKernelGetSystemTimeLow();

		diffA = endTimeA - startTimeA;

		// get the system start time
		startTimeB = sceKernelGetSystemTimeLow();

		// transform the points
		hkVector4Util::transformPoints( t, &vIn[0], NUM_ITERATIONS, &vOut[0] );

		// get the system end time
		endTimeB = sceKernelGetSystemTimeLow();

		diffB = endTimeB - startTimeB;

		printf( "TransformPoints\t\t\t|  %i\t\t|  %i\n", diffA, diffB );

	}

	printf( "\n" );
	
#endif

	return 0;
}


//
// FPU implementations
//

// hkMatrix3
inline void hkMatrix3SetZero( hkMatrix3* matrix )
{
	hkVector4 zero; 
	zero.setZero4();

	matrix->getColumn(0) = zero;
	matrix->getColumn(1) = zero;
	matrix->getColumn(2) = zero;
}


inline void hkMatrix3SetIdentity( hkMatrix3* matrix )
{
	hkVector4 zero;
	zero.setZero4();

	matrix->getColumn(0) = zero;
	matrix->getColumn(1) = zero;
	matrix->getColumn(2) = zero;

	hkReal one = 1.0f;
	(*matrix)(0,0) = one;
	(*matrix)(1,1) = one;
	(*matrix)(2,2) = one;
}


inline void hkMatrix3SetDiagonal( hkMatrix3* matrix, hkReal m00, hkReal m11, hkReal m22 )
{
	matrix->setZero();
	(*matrix)(0,0) = m00;
	(*matrix)(1,1) = m11;
	(*matrix)(2,2) = m22;
}


// hkVector4
inline void hkVector4SetCross( hkVector4& vector, hkVector4& v1, hkVector4& v2 )
{
	const hkReal nx = v1(1)*v2(2) - v1(2)*v2(1);
	const hkReal ny = v1(2)*v2(0) - v1(0)*v2(2);
	const hkReal nz = v1(0)*v2(1) - v1(1)*v2(0);

	vector.set( nx, ny, nz , 0.0f );
}


inline void hkVector4SetMin4( hkVector4& vector, hkVector4& a, hkVector4& b )
{
	vector(0) = a(0) < b(0) ? a(0) : b(0);
	vector(1) = a(1) < b(1) ? a(1) : b(1);
	vector(2) = a(2) < b(2) ? a(2) : b(2);
	vector(3) = a(3) < b(3) ? a(3) : b(3);
}


inline void hkVector4SetMax4( hkVector4& vector, hkVector4& a, hkVector4& b )
{
	vector(0) = a(0) > b(0) ? a(0) : b(0);
	vector(1) = a(1) > b(1) ? a(1) : b(1);
	vector(2) = a(2) > b(2) ? a(2) : b(2);
	vector(3) = a(3) > b(3) ? a(3) : b(3);
}

 
inline void hkVector4InlineSetMul3( hkVector4& vector, hkMatrix3& r, hkVector4& v )
{
	hkReal v0 = v(0);
	hkReal v1 = v(1);
	hkReal v2 = v(2);

	vector(0) = r(0,0)*v0 + r(0,1)*v1 + r(0,2)*v2;
	vector(1) = r(1,0)*v0 + r(1,1)*v1 + r(1,2)*v2;
	vector(2) = r(2,0)*v0 + r(2,1)*v1 + r(2,2)*v2;
	vector(3) = 0;
}


inline void hkVector4InlineSetMul4( hkVector4& vector, hkMatrix3& t, hkVector4& v )
{
	hkReal v0 = v(0);
	hkReal v1 = v(1);
	hkReal v2 = v(2);

	vector(0) = t(0,0)*v0 + t(0,1)*v1 + t(0,2)*v2;
	vector(1) = t(1,0)*v0 + t(1,1)*v1 + t(1,2)*v2;
	vector(2) = t(2,0)*v0 + t(2,1)*v1 + t(2,2)*v2;
	vector(3) = t(3,0)*v0 + t(3,1)*v1 + t(3,2)*v2;
}


inline void hkVector4InlineSetMul4xyz1( hkVector4& vector, hkTransform& t, hkVector4& v )
{
	hkReal v0 = v(0);
	hkReal v1 = v(1);
	hkReal v2 = v(2);

	vector(0) = t(0,0)*v0 + t(0,1)*v1 + t(0,2)*v2 + t(0,3);
	vector(1) = t(1,0)*v0 + t(1,1)*v1 + t(1,2)*v2 + t(1,3);
	vector(2) = t(2,0)*v0 + t(2,1)*v1 + t(2,2)*v2 + t(2,3);
	vector(3) = t(3,0)*v0 + t(3,1)*v1 + t(3,2)*v2 + t(3,3);
}


inline void hkVector4InlineSetRotatedInverseDir( hkVector4& vector, hkRotation& r, hkVector4& v )
{
	hkReal v0 = v(0);
	hkReal v1 = v(1);
	hkReal v2 = v(2);

	vector(0) = r(0,0)*v0 + r(1,0)*v1 + r(2,0)*v2;
	vector(1) = r(0,1)*v0 + r(1,1)*v1 + r(2,1)*v2;
	vector(2) = r(0,2)*v0 + r(1,2)*v1 + r(2,2)*v2;
	vector(3) = 0;
}


inline void hkVector4InlineSetTransformedInversePos( hkVector4& vector, hkTransform& t, hkVector4& v )
{
	hkReal v0 = v(0) - t(0,3);
	hkReal v1 = v(1) - t(1,3);
	hkReal v2 = v(2) - t(2,3);

	vector(0) = t(0,0)*v0 + t(1,0)*v1 + t(2,0)*v2;
	vector(1) = t(0,1)*v0 + t(1,1)*v1 + t(2,1)*v2;
	vector(2) = t(0,2)*v0 + t(1,2)*v1 + t(2,2)*v2;
	vector(3) = 0.0f;
}


inline hkSimdReal hkVector4InlineLength3( hkVector4& vector )
{
	return hkMath::sqrt( ( vector(0) * vector(0) ) + ( vector(1) * vector(1) ) + ( vector(2) * vector(2) ) );
}


inline hkSimdReal hkVector4InlineLengthInverse3( hkVector4& vector )
{
	hkReal l2 = ( vector(0) * vector(0) ) + ( vector(1) * vector(1) ) + ( vector(2) * vector(2) );
	return l2 ? hkMath::sqrtInverse(l2) : 0;
}


inline hkSimdReal hkVector4InlineLength4( hkVector4& vector )
{
	return hkMath::sqrt( ( vector(0) * vector(0) ) + ( vector(1) * vector(1) ) + ( vector(2) * vector(2) ) + ( vector(3) * vector(3) ) );
}


inline hkSimdReal hkVector4InlineLengthInverse4( hkVector4& vector )
{
	hkReal l2 = ( vector(0) * vector(0) ) + ( vector(1) * vector(1) ) + ( vector(2) * vector(2) ) + ( vector(3) * vector(3) );
	return l2 ? hkMath::sqrtInverse(l2) : 0;
}


inline void hkVector4InlineNormalize3( hkVector4& vector )
{
	vector.mul4( vector.lengthInverse3() );
}


inline hkSimdReal hkVector4InlineNormalizeWithLength3( hkVector4& vector )
{
	hkReal len = vector.length3();
	vector.mul4( (1.0f)/len );
	return len;
}


inline void hkVector4InlineNormalize4( hkVector4& vector )
{
	vector.mul4( vector.lengthInverse4() );
}


inline hkSimdReal hkVector4InlineNormalizeWithLength4( hkVector4& vector )
{
	hkReal len = vector.length4();
	vector.mul4( (1.0f)/len );
	return len;
}


//
// additional
//

// hkFloor
hkReal hkFloorFpu( hkReal r )
{
	union fi
	{
		float f;
		int i;
		unsigned u;
	};

	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//rshift is used to shift the fracmask (down to the fractional part)
	int rshift = 0x17 - int(exp);

	//if the exponent is greater than 0x17 (23 bits), then we don't need a
	//frackmask (there is no fractional part, not enough bits to store it)
	//i.e. if rshift >= 0, then leave alone, otherwise set rshift to zero
	int sign = ~(rshift >> 0x01f);
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//shift down to the fractional part
	//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
	//and preserves with an OR (and vice versa). In the case of sign preserving
	//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	int addMask = 0x00800000;

	//if the number is negative AND NOT whole
	//we increase it's magnitude, this is due
	//to the definition of floor
	addMask >>= int(exp);
	//if negative, do the addition (broadcast with sign)
	addMask &= sign;
	//check to see if there was anything in the fractional part
	addMask &= ~((convert.i & (~fracMask)) - 1);
	convert.i += addMask;

	convert.i &= fracMask;

	//if the exponent is negative AND the number is positive
	//then the number is less than 1.0f and floor sets it to 0.0f
	//if it is negative, it gets set to -1.0f
	nexp = int(exp);
	nexp = nexp >> 0x01f;
	//note: 0xbf800000 is -1.0f - which we need to assign in (easier than calculating)
	exp = (0xbf800000 & nexp) & sign;
	convert.i &= ~nexp;
	convert.u |= exp;

	return convert.f;
}


// hkFloorToInt
int hkFloorToIntFpu( hkReal r )
{
	union fi
	{
		float f;
		int i;
		unsigned u;
	};

	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//now split the exp into two shift magnitudes, a left
	//shift and a right shift, one of which must be 0
	int lshift = int(exp) - 0x17;
	int rshift = 0x17 - int(exp);

	//if lshift is <=0, then set to zero, otherwise set rshift to zero
	int sign = (lshift-1) >> 0x01f;
	lshift &= ~sign;
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//move the fraction mask to the correct place
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	//floor increases the magnitude of negative numbers
	int addMask = 0x00800000;

	//if the number is negative AND NOT whole
	//we increase it's magnitude, this is due
	//to the definition of floor
	addMask >>= int(exp);
	addMask &= sign;
	addMask &= ~((convert.i & (~fracMask)) - 1);

	//if the exponent is negative AND the number is positive
	//then the number is less than 1.0f and floor sets it to 0.0f
	//if it is negative, it gets set to -1.0f (or at least what that
	//would be if we had gotten this far in the function)
	nexp = int(exp);
	nexp = nexp >> 0x01f;
	exp = unsigned((0x00800000 & nexp) & sign);
	convert.i &= ~nexp;

	convert.i += addMask;

	//get rid of the exponent and sign
	convert.i &= 0x007fffff;
	//insert the 1 that is assumed in the floating point standard
	//UNLESS the exponent is negative
	convert.i |= (0x00800000 & ~nexp);
	//if the exponent is negative AND the sign is negative
	//then it is set to -1, otherwise 0
	convert.u |= exp;

	//truncate
	convert.i &= fracMask;

	//if the sign is negative, convert to 2's complement
	//otherwise leave untouched (ie subtract x from 0 or
	//subtract from x from 2x -> -x or x)
	int temp = 0x0;
	temp = (convert.i << 0x01) - 1;
	temp |= sign;
	convert.i = (temp - convert.i) + 1;

	//shift mantissa to correct place
	convert.i >>= rshift;
	convert.i <<= lshift;

	return convert.i;
}


// hkFloatToInt
int hkFloatToIntFpu(hkReal r)
{
	union fi
	{
		float f;
		int i;
		unsigned u;
	};

	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned int exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//now split the exp into two shift magnitudes, a left
	//shift and a right shift, one of which must be 0
	int lshift = int(exp) - 0x17;
	int rshift = 0x17 - int(exp);

	//if lshift is <=0, then set to zero, otherwise set rshift to zero
	int sign = (lshift-1) >> 0x01f;
	lshift &= ~sign;
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//shift down to the fractional part
	//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
	//and preserves with an OR (and vice versa). In the case of sign preserving
	//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	//get rid of the exponent and sign
	convert.i &= 0x007fffff;
	//insert the 1 that is assumed in the floating point standard
	convert.i |= 0x00800000;

	//truncate
	convert.i &= fracMask;

	//if the sign is negative, convert to 2's complement
	//otherwise leave untouched (ie subtract x from 0 or
	//subtract from x from 2x => -x or x)
	int temp = 0x0;
	temp = (convert.i << 0x01) - 1;
	temp |= sign;
	convert.i = (temp - convert.i) + 1;

	//if the exponent is negative, then the number is less than 1.0f
	//and float to int truncates that to 0
	nexp = int(exp);
	nexp = ~(nexp >> 0x1f);
	convert.i &= nexp;

	//shift mantissa to correct place (one of these will be zero)
	convert.i >>= rshift;
	convert.i <<= lshift;

	return convert.i;
}


inline void hkVector4UtilInlineTransformPoints( const hkTransform& t, const hkVector4* vectorsIn, int numVectors, hkVector4* vectorsOut )
{
	HK_ASSERT2( 0xf0237abd, numVectors > 0, "At least one element required");
	do
	{
		vectorsOut->_setTransformedPos( t, *vectorsIn );
		vectorsOut++;
		vectorsIn++;
	}
	while ( --numVectors > 0 );
}

#else //HK_PLATFORM_PSP

int psp_vfpu_main()
{
	return 0;
}
#endif

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(psp_vfpu_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
