/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Util/hkMathUtil.h>

void HK_CALL hkMathUtil::decomposeMatrix (const class hkMatrix4& matrixIn, Decomposition& decompOut)
{
	decompose4x4ColTransform((const hkReal*) &matrixIn, decompOut);
}

void HK_CALL hkMathUtil::decomposeMatrix (const hkMatrix3& matrixIn, Decomposition& decompOut)
{
	// We copy into a temporary matrix4
	hkMatrix4 matrix4;
	matrix4.setCols(matrixIn.getColumn(0), matrixIn.getColumn(1), matrixIn.getColumn(2), hkVector4::getZero());

	decomposeMatrix (matrix4, decompOut);
}

void HK_CALL hkMathUtil::decompose4x4ColTransform (const hkReal* matrixIn, hkMathUtil::Decomposition& decompOut)
{
	// Change this if you change the tolerance
	const int maxNumIterations = 30; // Usually around 7
	const hkReal tolerance = HK_REAL_EPSILON;

	hkTransform t;
	t.set4x4ColumnMajor(matrixIn);

	// Translation
	{
		decompOut.m_translation = t.getTranslation();
	}

	// Basis (rotation matrix)
	{
		hkRotation qCur, qNext, qInvT;

		int numIterations = 0;

		qNext = t.getRotation();
		do
		{
			qCur = qNext;

			qInvT = qCur;
			qInvT.invert(tolerance);
			qInvT.transpose();

			hkMatrix3 temp;
			temp = qCur;
			temp.add(qInvT);
			qNext.setMul( 0.5f, temp );	

			numIterations++;
		} while((numIterations<maxNumIterations) && (!qNext.isApproximatelyEqual( qCur, tolerance )));

		decompOut.m_basis = qNext;
	}

	// Quaternion + "flips" flag
	{
		hkVector4 c1 = decompOut.m_basis.getColumn(0);
		c1.normalize3();
		hkVector4 c2 = decompOut.m_basis.getColumn(1);
		c2.normalize3();
		hkVector4 c3 = decompOut.m_basis.getColumn(2);
		c3.normalize3();

		hkVector4 r0; r0.setCross( c2, c3 );
		const hkSimdReal determinant = c1.dot3(r0);

		if (determinant < 0.0f )
		{
			// The rotation is a change of hand-ness
			// Switch one of the columns
			// The scale component should counter-act this
			c1.mul4(-1.0f);

		}

		decompOut.m_flips = (determinant<0.0f);

		// Rotation quaternion
		{
			hkRotation rot;
			rot.setCols( c1, c2, c3 );
			decompOut.m_rotation = hkQuaternion(rot);
			decompOut.m_rotation.normalize();
		}

	}


	// Scale and Skew
	{
		hkQuaternion rotInvQ; rotInvQ.setInverse(decompOut.m_rotation);
		hkRotation rotInvM; rotInvM.set (rotInvQ);

		decompOut.m_scaleAndSkew.setMul(rotInvM, t.getRotation());
	}
	
	// Scale
	{

		// Diagonal
		decompOut.m_scale.set( decompOut.m_scaleAndSkew(0,0), decompOut.m_scaleAndSkew(1,1), decompOut.m_scaleAndSkew(2,2) );

		hkVector4 one; one.setAll(1.0f);
		decompOut.m_hasScale = ! decompOut.m_scale.equals3( one );
	}

	// Skew
	{
		// scale and skew = scale * skew
		// skew = inv(scale) * scaleAndSkew
		hkMatrix3 scaleInv; scaleInv.setDiagonal(1.0f/decompOut.m_scale(0), 1.0f/decompOut.m_scale(1), 1.0f/decompOut.m_scale(2));
		decompOut.m_skew.setMul(scaleInv, decompOut.m_scaleAndSkew);
		
		decompOut.m_hasSkew = !decompOut.m_skew.isApproximatelyEqual(hkTransform::getIdentity().getRotation());
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
