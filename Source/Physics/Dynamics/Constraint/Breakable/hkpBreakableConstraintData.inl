/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//
// breakable constraint methods 
//
inline void hkpBreakableConstraintData::setThreshold(hkReal thresh)
{
	m_solverResultLimit = thresh;
}

inline hkReal hkpBreakableConstraintData::getThreshold()
{
	return m_solverResultLimit;
}

inline void hkpBreakableConstraintData::setRemoveWhenBroken(hkBool tf)
{
	m_removeWhenBroken = tf;
}

inline hkBool hkpBreakableConstraintData::getRemoveWhenBroken()
{
	return m_removeWhenBroken;
}

inline void hkpBreakableConstraintData::setRevertBackVelocityOnBreak( hkBool b )
{
	m_revertBackVelocityOnBreak = b;
}


inline hkBool hkpBreakableConstraintData::getRevertBackVelocityOnBreak()
{
	return m_revertBackVelocityOnBreak;
}


inline hkpBreakableConstraintData::Runtime* hkpBreakableConstraintData::getRuntime( hkpConstraintRuntime* runtime )
{
	return reinterpret_cast<Runtime*>( hkAddByteOffset(runtime, m_childRuntimeSize)); 
}

inline hkBool hkpBreakableConstraintData::getIsBroken(hkpConstraintInstance* instance)
{
	Runtime* runtime = getRuntime( instance->getRuntime() );
	return runtime->m_isBroken;
}

inline void hkpBreakableConstraintData::setBreakableListener(hkpBreakableListener* blistener)
{
	m_listener = blistener;	
}

inline hkpConstraintData* hkpBreakableConstraintData::getWrappedConstraintData()
{
	return m_constraintData;
}

inline const hkpConstraintData* hkpBreakableConstraintData::getWrappedConstraintData() const
{
	return m_constraintData;
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
