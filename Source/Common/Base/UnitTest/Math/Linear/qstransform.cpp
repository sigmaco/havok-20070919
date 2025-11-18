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
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Math/Linear/hkMathStream.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>


static int NUM_TEST = 100;

// Generates random qs transforms with no scale

static hkPseudoRandomGenerator rGen(12343);
static void buildRandomQsTransformNoScale (hkQsTransform& transformOut)
{
	rGen.getRandomRotation(transformOut.m_rotation);
	rGen.getRandomVector11(transformOut.m_translation);
	transformOut.m_translation.mul4(rGen.getRandRange(1.0f, 10.0f));
	transformOut.m_scale.setAll3(1.0f);
}

static void buildRandomQsTransform (hkQsTransform& transformOut)
{
	rGen.getRandomRotation(transformOut.m_rotation);
	rGen.getRandomVector11(transformOut.m_translation);
	transformOut.m_translation.mul4(rGen.getRandRange(1.0f, 10.0f));

	// Make sure we don't have any <=0 scale
	hkQuadRealUnion u;
	u.r[0] = rGen.getRandRange(0.01f,5.0f);
	u.r[1] = rGen.getRandRange(0.01f,5.0f);
	u.r[2] = rGen.getRandRange(0.01f,5.0f);
	transformOut.m_scale.getQuad() = u.q;
}

// TEST ONE : Inverses
static void check_one()
{

	const hkQsTransform QS_IDENTITY (hkQsTransform::IDENTITY);

	for (int i=0; i < NUM_TEST; ++i)
	{
		hkQsTransform transform;
		buildRandomQsTransform(transform);

		hkQsTransform inverse;
		inverse.setInverse(transform);

		hkQsTransform shouldBeIdentity;

		// T * Inv(T) = I
		shouldBeIdentity.setMul(transform, inverse);
		HK_TEST(shouldBeIdentity.isApproximatelyEqual(QS_IDENTITY));

		// Inv(T) * T = I
		shouldBeIdentity.setMul(inverse, transform);
		HK_TEST(shouldBeIdentity.isApproximatelyEqual(QS_IDENTITY));

	}

}


// TEST TWO : Equivalence of operations with hkTransform (NO SCALE)
static void check_two()
{

	for (int i=0; i < NUM_TEST; i++)
	{
		hkQsTransform qsTransform1;
		hkTransform transform1;
		buildRandomQsTransformNoScale(qsTransform1);
		qsTransform1.copyToTransform(transform1);

		hkQsTransform qsTransform2;
		hkTransform transform2;
		buildRandomQsTransformNoScale(qsTransform2);
		qsTransform2.copyToTransform(transform2);

		hkVector4 position;
		rGen.getRandomVector11(position);

		// Check symmetry of conversions
		{
			// T2QS (QS2T (qs)) = qs
			hkQsTransform test;
			test.setFromTransform(transform1);
			HK_TEST(test.isApproximatelyEqual(qsTransform1));
		}

		// Check inverses
		{
			hkTransform inverseT;
			inverseT.setInverse(transform1);
			hkQsTransform inverseQs;
			inverseQs.setInverse(qsTransform1);

			// T2QS ( Inv ( QS2T (qs) ) ) = Inv (qs)
			{
				hkQsTransform test;
				test.setFromTransform(inverseT);
				HK_TEST(test.isApproximatelyEqual(inverseQs));
			}

			// QS2T ( Inv (qs) ) = Inv ( QS2T (qs) )
			// (guaranteed by symmetry)
			{
				hkTransform test;
				inverseQs.copyToTransform(test);
				HK_TEST(test.isApproximatelyEqual(inverseT));
			}
		}

		// setMul
		{
			hkTransform mulmulT;
			hkQsTransform mulmulQs;

			mulmulT.setMul(transform1, transform2);
			mulmulQs.setMul(qsTransform1, qsTransform2);

			// T2QS ( QS2T(qs1) * QS2T (qs2) ) = qs1 * qs2
			{
				hkQsTransform test;
				test.setFromTransform(mulmulT);
				HK_TEST(test.isApproximatelyEqual(mulmulQs));
			}

			// QS2T ( qs1 * qs2 ) = QS2T (qs1) * QS2T(qs2)
			// (guaranteed by symmetry)
			{
				hkTransform test;
				mulmulQs.copyToTransform(test);
				HK_TEST(test.isApproximatelyEqual(mulmulT));
			}

		}

		// setMulEq
		{
			// t2 := t2 * t1 
			transform2.setMulEq(transform1);
			// qs2 := qs2 * qs1
			qsTransform2.setMulEq(qsTransform1);

			// QS2T (qs2) = t2
			{
				hkTransform test;
				qsTransform2.copyToTransform(test);
				HK_TEST(test.isApproximatelyEqual(transform2));
			}

			// T2QS (t2) = qs2
			{
				hkQsTransform test;
				test.setFromTransform(transform2);
				HK_TEST(test.isApproximatelyEqual(qsTransform2));
			}
		}

		// setMulInvMul 
		{
			hkTransform mulinvmulT;
			hkQsTransform mulinvmulQs;

			mulinvmulT.setMulInverseMul(transform1, transform2);
			mulinvmulQs.setMulInverseMul(qsTransform1, qsTransform2);

			// T2QS ( Inv(QS2T(qs1)) * QS2T (qs2) ) = Inv(qs1) * qs2
			{
				hkQsTransform test;
				test.setFromTransform(mulinvmulT);
				HK_TEST(test.isApproximatelyEqual(mulinvmulQs));
			}

			// QS2T ( Inv(qs1) * qs2 ) = Inv(QS2T (qs1)) * QS2T(qs2)
			// (guaranteed by symmetry)
			{
				hkTransform test;
				mulinvmulQs.copyToTransform(test);
				HK_TEST(test.isApproximatelyEqual(mulinvmulT));
			}

		}

		// setMulMulInv 
		{
			hkTransform mulmulinvT;
			hkQsTransform mulmulinvQs;

			mulmulinvT.setMulMulInverse(transform1, transform2);
			mulmulinvQs.setMulMulInverse(qsTransform1, qsTransform2);

			// T2QS ( QS2T(qs1) * Inv(QS2T (qs2)) ) = qs1 * Inv(qs2)
			{
				hkQsTransform test;
				test.setFromTransform(mulmulinvT);
				HK_TEST(test.isApproximatelyEqual(mulmulinvQs));
			}

			// QS2T ( qs1 * Inv(qs2) ) = QS2T (qs1) * Inv(QS2T(qs2))
			// (guaranteed by symmetry)
			{
				hkTransform test;
				mulmulinvQs.copyToTransform(test);
				HK_TEST(test.isApproximatelyEqual(mulmulinvT));
			}

		}

		// hkVector4 setTransformedPos / setTransformedInversePost
		{
			hkVector4 transformedQs;
			transformedQs.setTransformedPos(qsTransform1, position);
			hkVector4 transformedInvQs;
			transformedInvQs.setTransformedInversePos(qsTransform1, position);
			hkVector4 transformedT;
			transformedT.setTransformedPos(transform1, position);
			hkVector4 transformedInvT;
			transformedInvT.setTransformedInversePos(transform1, position);

			// TRANS (qs1, P) = TRANS (t1, P)   [ = TRANS (QS2T(qs1) , P) ]
			HK_TEST(transformedQs.equals3(transformedT));

			// TRANSINV (qs1, P) = TRANSINV (t1, P)   [ = TRANSINV (QS2T(qs1), P) ]
			HK_TEST(transformedInvQs.equals3(transformedInvT));

		}

		{
			// TRANSINV (qs1, P) = TRANS (Inv(qs1), P)  -> WORKS ONLY WHEN THERE IS NO SCALE (LIKE HERE)
			
			hkVector4 mulInv_qs;
			mulInv_qs.setTransformedInversePos(qsTransform1, position);

			hkQsTransform invQs;
			invQs.setInverse(qsTransform1);
			hkVector4 mul_invQs;
			mul_invQs.setTransformedPos(invQs, position);

			HK_TEST(mulInv_qs.equals3(mul_invQs));
		}

	}
}

// TEST THREE : Other properties (scale included)
static void check_three()
{
	for (int i=0; i < NUM_TEST; i++)
	{
		hkQsTransform a;
		hkQsTransform b;
		hkQsTransform c;
		buildRandomQsTransform (a);
		buildRandomQsTransform (b);
		buildRandomQsTransform (c);
		hkVector4 position;
		rGen.getRandomVector11(position);


		hkQsTransform ab;
		ab.setMul(a,b);

		hkQsTransform bc;
		bc.setMul(b,c);

		hkQsTransform ba;
		ba.setMul(b,a);

		hkQsTransform inv_b;
		inv_b.setInverse(b);

		hkQsTransform inv_a;
		inv_a.setInverse(a);

		// Inv (a*b) = Inv (b) * Inv (a)
		{
			hkQsTransform left;
			left.setInverse(ab);

			hkQsTransform right;
			right.setMul(inv_b, inv_a);
			HK_TEST(left.isApproximatelyEqual(right));
		}

		// Associative : a*(b*c) = (a*b)*c
		{
			hkQsTransform left;
			left.setMul(a,bc);
			hkQsTransform right;
			right.setMul(ab,c);
			HK_TEST(left.isApproximatelyEqual(right));
		}

		// TRANSINV( a, TRANS ( a, P) ) = P
		// Also tests the TRANSINV operation is alias-safe
		{
			hkVector4 left;
			left.setTransformedPos(a, position);
			left.setTransformedInversePos(a, left); 
			HK_TEST(left.equals3(position));
		}

		// TRANS( a, TRANSINV ( a, P) ) = P
		// Also tests the TRANS operation is alias-safe
		{
			hkVector4 left;
			left.setTransformedInversePos(a, position);
			left.setTransformedPos(a, left);
			HK_TEST(left.equals3(position));
		}

	}

}

// TEST FOUR : Decomposition
static void check_four()
{
	static hkReal bufferOne[16];

	for (int i=0; i<NUM_TEST; i++)
	{
		hkQsTransform qstOne;
		buildRandomQsTransform(qstOne);

		qstOne.get4x4ColumnMajor(bufferOne);

		hkQsTransform test;
		const bool ok = test.set4x4ColumnMajor(bufferOne);

		HK_TEST(ok);
		HK_TEST(test.isApproximatelyEqual(qstOne));
	}

}


int qstransform_main()
{
	check_one(); // Inverses
	check_two(); // Equivalence with hkTransfrom (no scale)
	check_three(); // Other properties (scale included)
	check_four(); // Decomposition
	return 0;
}

//void ___1() { }
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(qstransform_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
