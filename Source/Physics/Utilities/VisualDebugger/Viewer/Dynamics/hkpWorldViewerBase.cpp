	
/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>

hkpWorldViewerBase::hkpWorldViewerBase( const hkArray<hkProcessContext*>& contexts )
: hkProcess(true) /*all selectable*/ , m_context(HK_NULL)
{
	int nc = contexts.getSize();
	int i;
	for (i=0; i < nc; ++i)
	{
		if ( hkString::strCmp(HK_PHYSICS_CONTEXT_TYPE_STRING, contexts[i]->getType() ) ==0 )
		{
			m_context = static_cast<hkpPhysicsContext*>( contexts[i] );
			break;
		}
	}

	if (m_context)
	{
		m_context->addWorldAddedListener(this); // context is a world deletion listener and will pass it on
		m_context->addReference(); // so that it can't be deleted before us.
	}
}

hkpWorldViewerBase::~hkpWorldViewerBase()
{
	if (m_context)
	{
		m_context->removeWorldAddedListener(this);
		m_context->removeReference(); // let it go.
		m_context = HK_NULL;
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
