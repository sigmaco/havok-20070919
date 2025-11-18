/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Serialize/Util/hkVersioningExceptionsArray.h>

/*
hkBool hkVersioningExceptionsArray::hasException( const char* className, unsigned oldSignature, unsigned newSignature ) const
{
	for ( int eIdx=0; eIdx < m_exceptions.getSize(); eIdx++ )
	{
		const hkVersioningExceptionsArray::VersioningException& except = m_exceptions[ eIdx ];
		if ( (hkString::strCmp(className, except.m_className)==0) && 
			( except.m_oldSignature == oldSignature) && 
			(except.m_newSignature == newSignature) )
		{
			return true;
		}
	}
	return false;
}*/

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
