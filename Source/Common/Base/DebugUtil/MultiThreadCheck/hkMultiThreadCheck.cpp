/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Thread/hkThreadLocalData.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

hkCriticalSection* hkMultiThreadCheck::m_criticalSection = HK_NULL;

void hkMultiThreadCheck::staticInit()
{
	m_criticalSection = new hkCriticalSection(1000);
}

void hkMultiThreadCheck::staticQuit()
{
	if ( m_criticalSection )
	{
		delete m_criticalSection;
		m_criticalSection = HK_NULL;
	}
}


void hkMultiThreadCheck::markForReadImpl(ReadMode mode )
{
	switch ( m_threadId )
	{
		case hkUint32(DISABLED):	return;

		case hkUint32(MARKED_RO_SELF_ONLY):
			{
				HK_ASSERT2( 0xf032df30, mode != RECURSIVE, "You cannot turn a multithread mark from a read only non recursive mark to a recursive mark" );
			}

		case hkUint32(UNMARKED):
		case hkUint32(MARKED_RO):
			{
				m_criticalSection->enter();
				m_threadId = (mode == RECURSIVE)? hkUint32(MARKED_RO) : hkUint32( MARKED_RO_SELF_ONLY );
				break;
			}

		default:
			{
				m_criticalSection->enter();
				HK_ON_DEBUG( hkUint32 threadId = (hkUint32)( hkThread::getMyThreadId() & 0xffffffff ));
				HK_ASSERT2( 0xf02132df, threadId == m_threadId, "Your object is already marked for write by another thread, you have to create a critical section around the havok object to avoid conflicts");
			}
	}

	// Push a read bit onto the stack
	{
		m_markBitStack <<= 1;
		m_markCount++;
		HK_ON_DEBUG(const hkInt32 maxDepth = 8 * sizeof(m_markBitStack));
		HK_ASSERT2( 0x63280484, m_markCount <= maxDepth, "Mark nesting too deep. Marks can only be nested up to a maximum depth of " << maxDepth);
	}

	m_criticalSection->leave();
}

void hkMultiThreadCheck::markForWriteImpl( )
{
	if ( m_threadId == (hkUint32)DISABLED )
	{
		return;
	}

	hkCriticalSectionLock lock( m_criticalSection );

	HK_ASSERT2( 0xf02de43e, m_threadId != (hkUint32)MARKED_RO && m_threadId != (hkUint32)MARKED_RO_SELF_ONLY, "You cannot turn a markForRead into a markForWrite" );

	const hkUint32 threadId = (hkUint32)( hkThread::getMyThreadId() & 0xffffffff );

	// Push a write mark onto the stack
	{
		m_markBitStack = (m_markBitStack<<1) | 1;
		m_markCount++;
		HK_ON_DEBUG(const hkInt32 maxDepth = 8 * sizeof(m_markBitStack));
		HK_ASSERT2( 0x54479d9c, m_markCount  <= maxDepth, "Mark nesting too deep. Marks can only be nested up to a maximum depth of " << maxDepth);
	}

	if ( m_threadId == (hkUint32)UNMARKED )
	{
		m_threadId = threadId;
	}
	else
	{
		HK_ASSERT2( 0xf02132ff, threadId == m_threadId, "Your object is already marked for write by another thread, you have to create a critical section around the havok object to avoid conflicts");
	}
}

bool hkMultiThreadCheck::isMarkedForWriteImpl( )
{
	if ( m_threadId == (hkUint32)DISABLED )
	{
		return true;
	}

	hkCriticalSectionLock lock( m_criticalSection );

	const hkUint32 threadId = (hkUint32)( hkThread::getMyThreadId() & 0xffffffff );

	if ( m_threadId == threadId )
	{
		return true;
	}
	return false;
}

void hkMultiThreadCheck::unmarkForReadImpl( )
{
	if ( m_threadId == (hkUint32)DISABLED )
	{
		return;
	}
	hkCriticalSectionLock lock( m_criticalSection );


	// Pop a lock from the top of the stack and ensure that it is a read lock.
	{
		HK_ASSERT2( 0xf043d534, m_markCount > 0, "Unbalanced mark/unmark: Missing markForRead.  Make sure HK_DEBUG_MULTI_THREADING is defined if mixing Release and Debug libs. See hkMultiThreadCheck.h for more info.");
		HK_ASSERT2( 0x54006467, (m_markBitStack & 1) == 0, "Calling unmark for read on a write mark.");
		m_markCount--;
		m_markBitStack >>= 1;
	}

	if ( m_markCount == 0)
	{
		HK_ASSERT2( 0xf02e32df, hkUint32(MARKED_RO) == m_threadId || hkUint32(MARKED_RO_SELF_ONLY) == m_threadId, "Your object was marked by a different thread");
		m_threadId = (hkUint32)UNMARKED;
	}
}

void hkMultiThreadCheck::unmarkForWriteImpl( )
{
	if ( m_threadId == (hkUint32)DISABLED )
	{
		return;
	}
	hkCriticalSectionLock lock( m_criticalSection );


	// Pop a lock from the stack, and ensure that it is a write lock.
	{
		HK_ASSERT2( 0xf043d534, m_markCount > 0, "Unbalanced mark/unmark: Missing markForWrite.  Make sure HK_DEBUG_MULTI_THREADING is defined if mixing Release and Debug libs. See hkMultiThreadCheck.h for more info.");
		HK_ASSERT2( 0x717c3b1d, (m_markBitStack & 1) != 0, "Calling unmark for write on a read mark.");
		m_markCount--;
		m_markBitStack >>= 1;
	}

	HK_ASSERT2( 0xf02e32df,  ( ((hkUint32)( hkThread::getMyThreadId() & 0xffffffff )) == m_threadId ), "Your object was marked by a different thread");
	if ( m_markCount == 0)
	{
		m_threadId = (hkUint32)UNMARKED;
	}
}

void hkMultiThreadCheck::accessCheck( AccessType type ) const
{
	const hkMultiThreadCheck& lock = *this;
	hkUint32 threadid = lock.m_threadId;
	if ( type == HK_ACCESS_IGNORE || threadid == (hkUint32)DISABLED)
	{
		return;
	}

	// Note we do not need locking in this case
	HK_ASSERT2( 0xf043d534, threadid != (hkUint32)UNMARKED, "MarkForRead MarkForWrite missing. Make sure HK_DEBUG_MULTI_THREADING is defined if mixing Release and Debug libs. See hkMultiThreadCheck.h for more info."  );

	if ( threadid == (hkUint32)MARKED_RO || threadid == (hkUint32)MARKED_RO_SELF_ONLY)
	{
		HK_ASSERT2( 0xf043d534, type == HK_ACCESS_RO, "Requesting a write access to a read only mark. Make sure HK_DEBUG_MULTI_THREADING is defined if mixing Release and Debug libs. See hkMultiThreadCheck.h for more info."  );
	}
	else
	{
		// now we have a read write lock
		HK_ASSERT2( 0xf02e32df, ((hkUint32)( hkThread::getMyThreadId() & 0xffffffff )) == threadid, "Your object was write marked by a different thread");
	}
}

void HK_CALL hkMultiThreadCheck::accessCheckWithParent( const hkMultiThreadCheck* parentLock, AccessType parentType, const hkMultiThreadCheck& lock, AccessType type )
{
	//
	//	Check the parent
	//
	if ( parentLock == HK_NULL)
	{
		// if there is no parent the entity is not added to the physics system yet
		return;
	}

	hkUint32 parentId = parentLock->m_threadId;
	if ( parentId == (hkUint32)DISABLED )
	{
		return;
	}

	if ( parentId != (hkUint32)MARKED_RO_SELF_ONLY )
	{
		parentLock->accessCheck( parentType );

		//
		//	Check if the parent already includes the child lock
		//
		if ( parentType >= type )
		{
			return;
		}
	}


		// check for parent
	while(1)
	{
		if ( type == HK_ACCESS_IGNORE )		break;
		if ( parentId == (hkUint32)DISABLED) break;
		if ( parentId == (hkUint32)UNMARKED) break;
		if ( parentId == (hkUint32)MARKED_RO_SELF_ONLY ) break;
		if ( parentId == (hkUint32)MARKED_RO )
		{
			// now we have a read lock in the parent
			if ( type == HK_ACCESS_RO )
			{
				return;	// have read lock, requesting read lock -> ok
			}
			break;
		}
		// now we have a read write lock in the parent
		HK_ASSERT2( 0xf02e32df, ((hkUint32)( hkThread::getMyThreadId() & 0xffffffff )) == parentId, "Your object was write markeded by a different thread");
		return;
	}

	//
	// Check the child
	//
	lock.accessCheck( type );
}


void hkMultiThreadCheck::disableChecks()
{
	m_threadId = (hkUint32)DISABLED;
}

void hkMultiThreadCheck::enableChecks()
{
	if (m_threadId != (hkUint32)DISABLED)
	{
		return;
	}
	m_threadId = (hkUint32)UNMARKED;
	m_markCount = 0;
}

bool hkMultiThreadCheck::isCheckingEnabled() const
{
	return m_threadId != (hkUint32)DISABLED;
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
