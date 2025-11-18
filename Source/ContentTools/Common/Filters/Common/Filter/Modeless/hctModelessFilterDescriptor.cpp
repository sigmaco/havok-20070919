/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>


hctModelessFilterDescriptor::hctModelessFilterDescriptor()
{

}


void hctModelessFilterDescriptor::createMutexIfNecessary() const
{
	if (m_activeFiltersMutex) return;

	// Note, if this is called from the destructor, the local version of getShortName() is called.
	const char* mutexName = getShortName();

	m_activeFiltersMutex = CreateMutex( NULL, // no security attributes
		FALSE, // initially not owned
		mutexName);  // name of mutex
}


hctModelessFilterDescriptor::~hctModelessFilterDescriptor()
{
	createMutexIfNecessary();

	DWORD dwWaitResult = WaitForSingleObject( 
		m_activeFiltersMutex,   // handle to mutex
		10000L);   //10 second time-out 

	// We would expect that all filters are closed - but just in case
	switch (dwWaitResult) 
	{
			// The thread got mutex ownership.
		case WAIT_OBJECT_0: 
			{
				// Add to list:
				while (m_activeFilterList)
				{
					m_activeFilterList->m_activeFilter->removeReference();
					ActiveFilterList* next = m_activeFilterList->m_next;
					delete m_activeFilterList;
					m_activeFilterList = next;
				}
			}
			break;

			// Cannot get mutex ownership due to time-out...
		case WAIT_TIMEOUT: 
			// Got ownership of the abandoned mutex object.
		case WAIT_ABANDONED: 
			break;
	}

	// Release the mutext for good
	ReleaseMutex(m_activeFiltersMutex);
	CloseHandle(m_activeFiltersMutex);
}

/*virtual*/ int hctModelessFilterDescriptor::countModelessFilters (int& numActiveOut, int& numClosingout) const
{
	numActiveOut = 0;
	numClosingout = 0;

	createMutexIfNecessary();

	// get the handle to inspect the active list
	DWORD dwWaitResult = WaitForSingleObject( 
		m_activeFiltersMutex,   // handle to mutex
		INFINITE);   

	switch (dwWaitResult) 
	{
		// The thread got mutex ownership.
	case WAIT_OBJECT_0: 
		{
			ActiveFilterList* cur = m_activeFilterList;
			while (cur) 
			{
				// It's active but may be closing down
				if (cur->m_activeFilter->isClosingDown())
				{
					++numClosingout;
				}
				else
				{
					++numActiveOut;
				}
				cur = cur->m_next;
			}
		}
		break;
	}

	ReleaseMutex(m_activeFiltersMutex);

	return numActiveOut + numClosingout;
}

/*virtual*/ void hctModelessFilterDescriptor::askModelessFiltersToClose () const
{
	createMutexIfNecessary();

	if (!m_activeFiltersMutex)
	{
		return; // No active filters
	}

	// get the handle to inspect the active list
	DWORD dwWaitResult = WaitForSingleObject( 
		m_activeFiltersMutex,   // handle to mutex
		INFINITE);   //10 second time-out 

	switch (dwWaitResult) 
	{
		// The thread got mutex ownership.
		case WAIT_OBJECT_0: 
			{

				ActiveFilterList* cur = m_activeFilterList;
				while (cur) 
				{
					if (cur->m_activeFilter)
					{
						cur->m_activeFilter->tryToClose();
					}
					cur = cur->m_next;
				}
			}
			break;
	}

	ReleaseMutex(m_activeFiltersMutex);
}

void hctModelessFilterDescriptor::removeFilterFromActiveList (hctModelessFilter* filter)
{
	createMutexIfNecessary();

	if (m_activeFiltersMutex)
	{
		// Grab the mutex:
		DWORD dwWaitResult = WaitForSingleObject( 
			m_activeFiltersMutex,   // handle to mutex
			10000L);   //10 second time-out 

		switch (dwWaitResult) 
		{
			// The thread got mutex ownership.
		case WAIT_OBJECT_0: 
			{
				// Remove from list:
				ActiveFilterList* curFilterNode = m_activeFilterList; 
				ActiveFilterList* lastFilterNode = NULL;
				while (curFilterNode)
				{
					if (curFilterNode->m_activeFilter == filter)
					{

						if (lastFilterNode)
						{
							lastFilterNode->m_next = curFilterNode->m_next;
						}
						else
						{
							m_activeFilterList = curFilterNode->m_next;
						}

						curFilterNode->m_activeFilter->removeReference();
						delete curFilterNode; // delete the list entry

						break;
					}
					lastFilterNode = curFilterNode;
					curFilterNode = curFilterNode->m_next;
				}
			}
			break;

			// Cannot get mutex ownership due to time-out...
		case WAIT_TIMEOUT: 
			// Got ownership of the abandoned mutex object.
		case WAIT_ABANDONED: 
			break;
		}

		ReleaseMutex(m_activeFiltersMutex); 
	}

}

void hctModelessFilterDescriptor::addFilterToActiveList (hctModelessFilter* filter)
{
	createMutexIfNecessary();

	// we need to add ourselves to the active list
	if (m_activeFiltersMutex)
	{
		// Grab the mutex:
		DWORD dwWaitResult = WaitForSingleObject( 
			m_activeFiltersMutex,   // handle to mutex
			10000L);   //10 second time-out 

		switch (dwWaitResult) 
		{
			// The thread got mutex ownership.
		case WAIT_OBJECT_0: 
			{

				// Add to list:
				ActiveFilterList* ne = new ActiveFilterList;
				ne->m_activeFilter = filter;
				ne->m_next = m_activeFilterList;
				m_activeFilterList = ne;
				filter->addReference();
			}
			break;

			// Cannot get mutex ownership due to time-out.
		case WAIT_TIMEOUT: 
			// Got ownership of the abandoned mutex object.
		case WAIT_ABANDONED: 
			break;
		}

		ReleaseMutex(m_activeFiltersMutex); 
	}
}

/// Returns the i-th filter inthe list
hctModelessFilter* hctModelessFilterDescriptor::getActiveFilter (int i) const
{
	createMutexIfNecessary();

	hctModelessFilter* result = HK_NULL;

	// we need to add ourselves to the active list
	if (m_activeFiltersMutex)
	{
		// Grab the mutex:
		DWORD dwWaitResult = WaitForSingleObject( 
			m_activeFiltersMutex,   // handle to mutex
			10000L);   //10 second time-out 

		switch (dwWaitResult) 
		{
			// The thread got mutex ownership.
		case WAIT_OBJECT_0: 
			{
				int count=0;
				ActiveFilterList* curFilterNode = m_activeFilterList; 
				while (curFilterNode && (count<i))
				{
					count++;
					curFilterNode = curFilterNode->m_next;
				}

				if (curFilterNode)
				{
					result = curFilterNode->m_activeFilter;
				}

			}
			break;

			// Cannot get mutex ownership due to time-out.
		case WAIT_TIMEOUT: 
			// Got ownership of the abandoned mutex object.
		case WAIT_ABANDONED: 
			break;
		}

		ReleaseMutex(m_activeFiltersMutex); 
	}

	return result;
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
