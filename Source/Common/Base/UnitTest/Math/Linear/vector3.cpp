/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Linear/hkMathStream.h>

#define DOUT(A) hkcout << #A " = " << A << '\n'

extern void ___1(void*p=0);

static void constructors_equals()
{
	{
		hkVector4 x; x.set(5,2,1,3);
		HK_TEST(x(0)==5);
		HK_TEST(x(1)==2);
		HK_TEST(x(2)==1);
		HK_TEST(x(3)==3);
	}

	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(0,0,0,0);
		hkVector4 z; z.set(5,2,1,9);
		hkVector4 w; w.set(5,3,2,3);

		hkBool32 check = x.equals3(y);
		HK_TEST( !check );

		HK_TEST( !x.equals4(y));
		HK_TEST(  x.equals3(z));
		HK_TEST( !x.equals4(z));
		HK_TEST( !x.equals3(w));
		HK_TEST( !x.equals4(w));

		HK_TEST( !y.equals3(z));
		HK_TEST( !y.equals4(z));
		HK_TEST( !y.equals3(w));
		HK_TEST( !y.equals4(w));

		HK_TEST( !z.equals3(w));
		HK_TEST( !z.equals4(w));
	}

	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(92,4,2,-1);
		y = x;
		HK_TEST(x.equals4(y));
	}

	{
		hkVector4 x;
		x.set(5,2,1,3);
		HK_TEST(x(0)==5);
		HK_TEST(x(1)==2);
		HK_TEST(x(2)==1);
		HK_TEST(x(3)==3);
	}
	{
		hkVector4 x;
		x.setAll(93);
		HK_TEST(x(0)==93);
		HK_TEST(x(1)==93);
		HK_TEST(x(2)==93);
		HK_TEST(x(3)==93);
	}
	{
		hkVector4 x;
		x.setAll(94);
		HK_TEST(x(0)==94);
		HK_TEST(x(1)==94);
		HK_TEST(x(2)==94);
	}
	{
		hkVector4 x;
		x.setZero4();
		HK_TEST(x(0)==0);
		HK_TEST(x(1)==0);
		HK_TEST(x(2)==0);
		HK_TEST(x(3)==0);
	}

	{
		hkVector4 x;
		x.setZero4();
		HK_TEST(x(0)==0);
		HK_TEST(x(1)==0);
		HK_TEST(x(2)==0);
		HK_TEST(x(3)==0);
	}
	{
		hkVector4 x;
		x.set(5,2,1,3);
		HK_TEST(x(0)==5);
		HK_TEST(x(1)==2);
		HK_TEST(x(2)==1);
		HK_TEST(x(3)==3);
	}
}

static void getset_int24w()
{
#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

	hkVector4 x; x.setZero4();
	hkVector4 zero; zero.setZero4();

	for (int i = 0; i < 0xf0000; i++)
	{
		x.setInt24W(i);
		volatile hkReal f = x(3);
		x(3) = f;
		x.add3clobberW(zero);
		HK_TEST( x.getInt24W() == i);
	}
}

static void vector3_ops()
{
	// +
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		x.add4( y );
		hkVector4 twoy; twoy.setMul4(2, y);
		HK_TEST( x.equals3(twoy));
		HK_TEST( x.equals4(twoy));
	}

	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		x.setAdd4( x, y );
		hkVector4 twoy; twoy.setMul4(2, y);
		HK_TEST( x.equals3(twoy));
		HK_TEST( x.equals4(twoy));
	}

	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		x.add3clobberW( y );
		hkVector4 twoy; twoy.setMul4(2, y);
		HK_TEST( x.equals3(twoy));
	}

	// -
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		x.sub4( y );
		y.setZero4();
		HK_TEST(y.equals4(x));
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(1,2,3,4);
		x.sub3clobberW( y );
		hkVector4 a; a.set(4,0,-2,-1);
		HK_TEST(x.equals3(a));
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		x.setSub4( x, y );
		y.setZero4();
		HK_TEST(y.equals4(x));
	}

	// * vec
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(9,8,7,6);
		x.mul4( y );
		HK_TEST(x(0)==45);
		HK_TEST(x(1)==16);
		HK_TEST(x(2)== 7);
		HK_TEST(x(3)==18);
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(9,8,7,6);
		x.setMul4( x,y );
		HK_TEST(x(0)==45);
		HK_TEST(x(1)==16);
		HK_TEST(x(2)== 7);
		HK_TEST(x(3)==18);
	}


	// * real
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		hkSimdReal r = .5f;
		x.mul4( r );
		HK_TEST( hkMath::equal( 2.0f*hkReal(x.length4()), y.length4() ) );
		hkVector4 z; z.setAdd4(x,x);
		HK_TEST( z.equals4(y) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		hkSimdReal r = .5f;
		x.setMul4( r, y );
		HK_TEST( hkMath::equal( 2.0f*hkReal(x.length4()), y.length4() ) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		hkSimdReal r = 3.0f;
		x.addMul4( r, y );
		HK_TEST( hkMath::equal( x.length4(), 4.0f * hkReal(y.length4()) ) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(7,3,2,1);
		hkVector4 z; z.set(1,4,2,6);
		x.addMul4( y, z );
		hkVector4 a; a.set(5+7*1, 2+3*4, 1+2*2, 3+1*6);
		HK_TEST( a.equals4(x) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y = x;
		hkSimdReal r = 3.0f;
		x.subMul4( r, y );
		HK_TEST( hkMath::equal( x.length4(), 2.0f * hkReal(y.length4()) ) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(1,2,3,4);
		hkSimdReal r = 3.0f;
		hkVector4 z; z.setAddMul4( x, y, r );
		hkVector4 a; a.set(8,8,10,15);
		HK_TEST( z.equals4(a) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(1,2,3,4);
		hkVector4 z; z.set(10,20,30,40);
		hkVector4 w; w.setAddMul4( x, y, z );
		hkVector4 a; a.set(5+1*10, 2+2*20, 1+3*30, 3+4*40);
		HK_TEST( w.equals4(a) );
	}

	// cross, interpolate
	{
		hkVector4 x; x.set(1,0,0);
		hkVector4 y; y.set(0,1,0);
		hkVector4 z;
		z.setCross( x, y );

		HK_TEST( hkMath::equal( z(0), 0 ) );
		HK_TEST( hkMath::equal( z(1), 0 ) );
		HK_TEST( hkMath::equal( z(2), 1 ) );
	}
	{
		hkVector4 y; y.set(0,1,0);
		hkVector4 z; z.set(0,0,1);
		hkVector4 x;
		x.setCross( y, z );

		HK_TEST( hkMath::equal( x(0), 1 ) );
		HK_TEST( hkMath::equal( x(1), 0 ) );
		HK_TEST( hkMath::equal( x(2), 0 ) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(-2,6,9,7);
		x.normalize3();
		y.normalize3();

		hkVector4 z;
		z.setCross( x, y );

		HK_TEST( hkMath::equal( z.dot3(x), 0 ) );
		HK_TEST( hkMath::equal( z.dot3(y), 0 ) );
		HK_TEST( hkMath::equal( z.dot3fpu(x), 0 ) );
		HK_TEST( hkMath::equal( z.dot3fpu(y), 0 ) );
		
		/*
		hkReal me1 = x.length3(); 
		hkReal me2 = y.length3();
		hkReal me21 = x.dot3(y);
		hkReal me22 = 1.0f - hkReal(x.dot3(y)*x.dot3(y));
		hkReal me222 = 1.0f - hkReal(me21*me21);		
		hkReal me3 = hkMath::sqrt(me22);
		hkReal me4 = me1*me2*me3;
		*/
		
		hkReal area = hkReal(x.length3() * y.length3()) * hkMath::sqrt(1.0f- hkReal(x.dot3(y)*x.dot3(y)));
		hkReal zlen = z.length3();
		//DOUT(area); DOUT(zlen);
		HK_TEST( hkMath::equal(area, zlen ) );
	}
	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y; y.set(-2,6,9,7);
		hkVector4 z;

		z.setInterpolate4( x, y, 0);
		HK_TEST( z.equals4(x) );

		z.setInterpolate4( x, y, 1);
		HK_TEST( z.equals4(y) );

		z.setInterpolate4( x, y, 0.3f);
		hkVector4 w;
		w.setMul4( 0.3f, y);
		w.addMul4( 0.7f, x);
		HK_TEST( z.equals4(w) );
	}
}

static void vector3_misc()
{
	{
		hkVector4 x; x.set(1,2,6,9);
		hkVector4 y; y.set(1,2,6,99);
		HK_TEST( x.equals3(y) );
		HK_TEST( ! x.equals4(y) );
	}
	{
		hkVector4 x; x.set(1,2,6,9);
		hkVector4 y; y.set(1,2,6,99);
		HK_TEST( x.equals3(y) );
		HK_TEST( ! x.equals4(y) );
	}

	{
		hkVector4 x; x.set(1,-2,-0,99);
		hkVector4 y; y.set(-1,-2,10,-99);
		int mx = x.compareLessThanZero4().getMask();
		int my = y.compareLessThanZero4().getMask();
		HK_TEST( mx == hkVector4Comparison::MASK_Y );
		HK_TEST( my == hkVector4Comparison::MASK_XYW );
	}

	{
		hkVector4 x; x.set( 1, 5,-3,99);
		hkVector4 y; y.set(-1, 5,0,100);
		int cle = x.compareLessThanEqual4( y ).getMask();
		HK_TEST( (cle & hkVector4Comparison::MASK_X) != hkVector4Comparison::MASK_X );
		HK_TEST( (cle & hkVector4Comparison::MASK_Y) == hkVector4Comparison::MASK_Y );
		HK_TEST( (cle & hkVector4Comparison::MASK_ZW) == hkVector4Comparison::MASK_ZW );

		int clt = x.compareLessThan4( y ).getMask();
		HK_TEST( (clt & hkVector4Comparison::MASK_X) != hkVector4Comparison::MASK_X );
		HK_TEST( (clt & hkVector4Comparison::MASK_Y) != hkVector4Comparison::MASK_Y );
		HK_TEST( (clt & hkVector4Comparison::MASK_ZW) == hkVector4Comparison::MASK_ZW );
	}

	{
		hkVector4 x; x.set(1,-2,-0,99);
		hkVector4 y; y.set(-1,-2,10,-99);
		hkVector4Comparison mx = x.compareLessThanZero4();
		hkVector4Comparison my = y.compareLessThanZero4();
		HK_TEST( mx.allAreSet() == 0 );
		HK_TEST( mx.allAreSet(hkVector4Comparison::MASK_Y)  );
		HK_TEST( mx.allAreSet(hkVector4Comparison::MASK_X) == 0 );
		HK_TEST( mx.allAreSet(hkVector4Comparison::MASK_XW) == 0 );
		HK_TEST( mx.anyIsSet(hkVector4Comparison::MASK_Y) );
		HK_TEST( mx.anyIsSet(hkVector4Comparison::MASK_XYZW) );
		HK_TEST( mx.anyIsSet(hkVector4Comparison::MASK_XW) == 0 );
	}

	{
		hkVector4 x; x.set(5,2,1,3);
		hkVector4 y;
		y.setNeg3(x);

		hkVector4 a; a.setSub4(x,y);
		hkVector4 b; b.setAdd4(x,x);
		HK_TEST( b.equals3(a) );
		hkVector4 c; c.setAdd4(x,y);
		HK_TEST( hkMath::equal( c.length3(), 0 ) );
	}

	{
		hkVector4 x; x.set(-1,2,6,-9);
		hkVector4 y;
		y.setNeg4(x);
		hkVector4 z;
		z.setMul4(-1.0f, x);
		HK_TEST( z.equals4(y) );
		HK_TEST( ! x.equals4(y) );
	}

	{
		hkVector4 x; x.set(-1,2,-6,9);
		hkVector4 y;
		y.setAbs4(x);
		HK_TEST(y(0)==1);
		HK_TEST(y(1)==2);
		HK_TEST(y(2)==6);
		HK_TEST(y(3)==9);
	}

	{
		hkVector4 a; a.set(-1,2,-6,9);
		hkVector4 b; b.set(-100, 555, 0, 1e5f);
		hkVector4 c;
		c.setMin4(a,b);
		HK_TEST(c(0)==-100);
		HK_TEST(c(1)==2);
		HK_TEST(c(2)==-6);
		HK_TEST(c(3)==9);
	}

	{
		hkVector4 a; a.set(-1,2,-6,9);
		hkVector4 b; b.set(-100, 555, 0, 1e5f);
		hkVector4 c;
		c.setMax4(a,b);
		HK_TEST(c(0)==-1);
		HK_TEST(c(1)==555);
		HK_TEST(c(2)==0);
		HK_TEST(c(3)==1e5f);
	}
    {
		hkVector4 a; a.set(-1,2,-6,9);
        hkSimdReal s = a(1);
		hkVector4 b; b.set(-100, 555, 0, 1e5f);
		hkVector4 c = b;
        c.addMul4(s, a);
        HK_TEST(c(0)==b(0)+a(1)*a(0));
        HK_TEST(c(1)==b(1)+a(1)*a(1));
        HK_TEST(c(2)==b(2)+a(1)*a(2));
        HK_TEST(c(3)==b(3)+a(1)*a(3));
    }
    
    {
    	hkVector4 a; a.set( 1,2,3,4 );
    	a.zeroElement(0);
    	HK_TEST( a(0) == 0 && a(1) == 2 && a(2) ==3 && a(3) == 4 );
    	a.zeroElement(1);
    	HK_TEST( a(0) == 0 && a(1) == 0 && a(2) ==3 && a(3) == 4 );
    	a.zeroElement(2);
    	HK_TEST( a(0) == 0 && a(1) == 0 && a(2) ==0 && a(3) == 4 );
    	a.zeroElement(3);
    	HK_TEST( a(0) == 0 && a(1) == 0 && a(2) ==0 && a(3) == 0 );
    }
}

static void matrix3_transform_quaternion()
{
	{
		hkVector4 c0; c0.set(4,1,7);
		hkVector4 c1; c1.set(9,5,2);
		hkVector4 c2; c2.set(8,6,4);
		hkMatrix3 m;
		m.setCols(c0,c1,c2);
		hkVector4 v0; v0.set(1,2,3);
		
		hkVector4 v1;
		v1.setMul3(m,v0);

		HK_TEST( v1(0)==46 );
		HK_TEST( v1(1)==29 );
		HK_TEST( v1(2)==23 );
		//hkcout << v0 << '\n' << m << '\n' << v1 << '\n';
	}

	{
		hkRotation r;
		hkVector4 axis; axis.set(5,2,-4);
		axis.normalize3();
		r.setAxisAngle( axis, 0.62f);
		hkVector4 v0; v0.set(2,3,4);

		hkVector4 v1;
		v1.setRotatedDir(r,v0);
		HK_TEST( !v0.equals3(v1) );

		hkVector4 v2;
		v2._setRotatedInverseDir(r,v1); // inline to see code
		HK_TEST( v0.equals3(v2) );
//		hkcout << v0 << '\n' << r << '\n' << v1 << '\n' << v2 << hkendl;
	}

	{
		hkVector4 axis; axis.set(5,2,-4);
		axis.normalize3();
		hkRotation r;
		r.setAxisAngle(axis, 0.62f);
		hkTransform t;
		t.setRotation(r);
		hkVector4 t0; t0.set(-20,-30,-40);
		t.setTranslation(t0);

		hkVector4 v0; v0.set(2,3,4);
		hkVector4 v1;
		v1.setTransformedPos(t,v0);
		HK_TEST( !v0.equals3(v1) );
		hkVector4 v2;
		v2._setTransformedInversePos(t,v1);
		HK_TEST( v0.equals3(v2) );
		//hkcout << v0 << '\n' << t << '\n' << v1 << '\n' << v2 << '\n';
	}

	{
		hkVector4 axis; axis.set(5,2,-4);
		hkReal angle = 0.3f;
		axis.normalize3();

		hkQuaternion q( axis, angle);
		hkRotation r;
		r.setAxisAngle(axis, angle);

		hkQuaternion q2;
		q2.set( r );

		//DOUT(q2);

		hkVector4 x; x.set(4,2,6,1);
		hkVector4 yq;
		yq.setRotatedDir(q,x);
		hkVector4 yr;
		yr.setRotatedDir(r,x);

		HK_TEST(yq.equals3(yr));
		//DOUT(q); DOUT(r); DOUT(x); DOUT(yq); DOUT(yr);
	}

	{
		hkVector4 axis; axis.set(5,2,-4);
		hkReal angle = 0.3f;
		axis.normalize3();

		hkQuaternion q( axis, angle);
		hkRotation r;
		r.setAxisAngle(axis, angle);

		hkQuaternion q2;
		q2.set( r );

		//DOUT(q2);

		hkVector4 x; x.set(4,2,6,1);
		hkVector4 yq;
		yq.setRotatedInverseDir(q,x);
		hkVector4 yr;
		yr.setRotatedInverseDir(r,x);

		HK_TEST(yq.equals3(yr));
//		DOUT(q); DOUT(r); DOUT(x); DOUT(yq); DOUT(yr);
	}

	// composition of rotations
	{
		hkVector4 axis; axis.set(5,2,-4);
		hkReal angle = 0.3f;
		axis.normalize3();

		hkQuaternion q1( axis, angle);
		hkRotation r1;
		r1.setAxisAngle(axis, angle);

		hkVector4 axis2; axis2.set(2,-1,4);
		hkReal angle2 = 0.3f;
		axis2.normalize3();

		hkQuaternion q2( axis2, angle2);
		hkRotation r2;
		r2.setAxisAngle(axis2, angle2);

		hkQuaternion q12;
		q12.setMul( q1, q2 );

		hkRotation r12;
		r12.setMul( r1, r2 );

		hkVector4 x; x.set( 4,2,6,1 );
		hkVector4 yq;
		yq.setRotatedDir(q12,x);
		hkVector4 yr;
		yr.setRotatedDir(r12,x);

		HK_TEST(yq.equals3(yr));
	}

	{
		hkVector4 c0; c0.set(-4, 1,-7,-2);
		hkVector4 c1; c1.set( 9,-5, 2,-3);
		hkVector4 c2; c2.set( 8, 6, 4,-4);
		hkTransform t;
		t.getRotation().setCols(c0,c1,c2);
		t.getTranslation().set(0,3,-1,-5);

		hkVector4 v0; v0.set(1,2,3,-1000);
		hkVector4 v1; v1._setMul4xyz1(t,v0);

		HK_TEST( v1(0)== 38 );
		HK_TEST( v1(1)== 12 );
		HK_TEST( v1(2)==  8 );
		HK_TEST( v1(3)==-25 );
		//hkcout << v0 << '\n' << m << '\n' << v1 << '\n';
	}
}

static void dots_lengths()
{
	{
		hkVector4 a; a.set(5,2,-4);
		hkVector4 b; b.set(9,1,3);
		hkReal r = a.dot3(b);
		HK_TEST( hkMath::equal(r, 45+2-12) );
	}
	{
		hkVector4 a; a.set(5,2,-4,-8);
		hkVector4 b; b.set(9,1,3,10);
		hkReal r = a.dot4(b);
		HK_TEST( hkMath::equal(r, 45+2-12-80) );
	}
	{
		hkVector4 x; x.set( 1,2,3,4 );
		hkVector4 y; y.set( 3,5,7,11 );

		hkReal result = hkReal( x.dot4xyz1( y ) );

		HK_TEST( hkMath::equal( 38, result) );
	}
	{
		hkVector4 x; x.set( 1,5,9,21 );
		HK_TEST( hkMath::equal( x.horizontalAdd3(), 1+5+9) );
		HK_TEST( hkMath::equal( x.horizontalAdd4(), 1+5+9+21) );
	}
	{
		hkVector4 a; a.set(5,2,-4,-8);
		hkVector4 b;
		b.setAdd4(a,a);
		HK_TEST( hkMath::equal( hkSimdReal(2.0f)*a.length3(), b.length3() ) );
		HK_TEST( hkMath::equal( a.lengthInverse3(), hkSimdReal(2.0f)*b.lengthInverse3() ) );
		HK_TEST( hkMath::equal( a.length3()*a.length3(), a.lengthSquared3(), 1e-4f ) );
		HK_TEST( hkMath::equal( hkSimdReal(2.0f)*a.length4(), b.length4() ) );
		HK_TEST( hkMath::equal( a.lengthInverse4(), hkSimdReal(2.0f)*b.lengthInverse4() ) );
		HK_TEST( hkMath::equal( a.length4()*a.length4(), a.lengthSquared4(), 1e-4f ) );
	}

	{
		hkVector4 a; a.set(5,2,-4,-8);
		hkVector4 b = a;
		b.normalize4();
		HK_TEST( hkMath::equal( b.length4(), 1.0f ) );

		hkReal alen = a.length4();
		hkVector4 c = a;
		HK_TEST( hkMath::equal( c.normalizeWithLength4(), alen ) );
		HK_TEST( hkMath::equal( c.length4(), 1.0f ) );
	}

	{
		hkVector4 a; a.set(5,2,-4,-8);
		hkVector4 b = a;
		b.normalize3();
		HK_TEST( hkMath::equal( b.length3(), 1.0f ) );

		hkReal alen = a.length3();
		hkVector4 c = a;
		HK_TEST( hkMath::equal( c.normalizeWithLength3(), alen ) );
		HK_TEST( hkMath::equal( c.length3(), 1.0f ) );
	}

	{
		hkVector4 a; a.set(5,2,-4,-8);
		hkVector4 b = a;
		b.fastNormalize3();
		HK_TEST( hkMath::equal( b.length3(), 1.0f, 2e-04f ) );

		hkReal alen = a.length3();
		hkVector4 c = a;
		HK_TEST( hkMath::equal( c.fastNormalizeWithLength3(), alen, 11e-04f ) );
		HK_TEST( hkMath::equal( c.length3(), 1.0f, 2e-04f ) );
	}

	{
		hkVector4 c; c.set(0,0,0,1);
		hkSimdReal cl3 = c.length3();
		hkSimdReal cl4 = c.length4();
		HK_TEST( hkMath::equal( 0.0f, cl3, 1e-04f ) );
		HK_TEST( hkMath::equal( 1.0f, cl4, 1e-04f ) );

		hkVector4 d; d.set(0,0,0,0);
		hkSimdReal dl3 = d.length3();
		hkSimdReal dl4 = d.length4();
		HK_TEST( hkMath::equal( 0.0f, dl3, 1e-04f ) );
		HK_TEST( hkMath::equal( 0.0f, dl4, 1e-04f ) );
	}
}

static void inv_square_roots()
{
	hkVector4 a; a.set(4, 9, 16, 25);
	hkVector4 b; b.setSqrtInverse4(a);

	hkVector4 c; c.set(1.0f/2.0f, 1.0f/3.0f, 1.0f/4.0f, 1.0f/5.0f);
	HK_TEST( b.equals4(c) );
}

static void broadcast_etc()
{
	{
		hkVector4 a; a.set(5,2,-4,9);
		HK_TEST( a(0) == hkReal( a.getSimdAt(0) ) );
		HK_TEST( a(1) == hkReal( a.getSimdAt(1) ) );
		HK_TEST( a(2) == hkReal( a.getSimdAt(2) ) );
		HK_TEST( a(3) == hkReal( a.getSimdAt(3) ) );
	}
	{
		hkVector4 x; x.set( 5, 2,-4, 9);
		hkVector4 y; y.set(-3, 1, 8, 2);
		hkVector4 z; z.set(-1, 7, 6, 3);
		for( int i = 0; i < 4; ++i )
		{
			hkVector4 a = x;
			a.broadcast(i);
			HK_TEST( a(0) == a(i) );
			HK_TEST( a(1) == a(i) );
			HK_TEST( a(2) == a(i) );
			HK_TEST( a(3) == a(i) );

			hkVector4 b;
			b.setBroadcast(y,i);
			HK_TEST( b(0) == b(i) );
			HK_TEST( b(1) == b(i) );
			HK_TEST( b(2) == b(i) );
			HK_TEST( b(3) == b(i) );

			hkVector4 c;
			c.setBroadcast3clobberW(z,i);
			HK_TEST( c(0) == c(i) );
			HK_TEST( c(1) == c(i) );
			HK_TEST( c(2) == c(i) );
		}
	}
	{
		hkVector4 a; a.set(.9f,.8f,.8f);
		HK_TEST( a.getMajorAxis() == 0 );
		hkVector4 b; b.set(.8f,.9f,.8f);
		HK_TEST( b.getMajorAxis() == 1 );
		hkVector4 c; c.set(.8f,.8f,.9f);
		HK_TEST( c.getMajorAxis() == 2 );
	}
	{

	}
}

int vector3_main()
{
	// Test function order matches hkVector4 order
	{
		constructors_equals();
		vector3_ops();
		vector3_misc();
		getset_int24w();
		matrix3_transform_quaternion();
		dots_lengths();
		inv_square_roots();
		broadcast_etc();
		//foo_bar();
		//random();
	
	}
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(vector3_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
