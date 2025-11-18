/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/Types/hkBaseTypes.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.h>



hkCheckDeterminismUtil* g_checkDeterminismUtil;
// put these into a structure
static HK_THREAD_LOCAL(hkIstream*) m_inputStream;
static HK_THREAD_LOCAL(hkOstream*) m_outputStream;
static HK_THREAD_LOCAL(void*)     m_jobInfoIdx;
static HK_THREAD_LOCAL(void*)     m_isPrimaryWorkerThread;


hkCheckDeterminismUtil::hkCheckDeterminismUtil()
{
	m_inSingleThreadedCode = true;
	m_shared = new hkCriticalSection();

	m_sharedInputStream  = HK_NULL;
	m_sharedOutputStream = HK_NULL;
	HK_THREAD_LOCAL_SET(m_inputStream, m_sharedInputStream);
	HK_THREAD_LOCAL_SET(m_outputStream, m_sharedOutputStream);
	m_primaryWorkerThreadInputStream = HK_NULL;
	m_primaryWorkerThreadOutputStream = HK_NULL;


	// Debug flag
	m_writingStFromWorker = false;
}


hkCheckDeterminismUtil::~hkCheckDeterminismUtil()
{
	HK_ASSERT2(0xad876dda, m_sharedInputStream == HK_THREAD_LOCAL_GET(m_inputStream), "Upon destruction, the thread-local streams are expected to be set to the shared streams (i.e. working in single-threaded mode)." );
	HK_ASSERT2(0xad876dda, m_sharedOutputStream == HK_THREAD_LOCAL_GET(m_outputStream), "Upon destruction, the thread-local streams are expected to be set to the shared streams (i.e. working in single-threaded mode)." );

	finish();
	delete m_shared;

	// Thread local structures
	HK_THREAD_LOCAL_SET(m_inputStream, HK_NULL);
	HK_THREAD_LOCAL_SET(m_outputStream, HK_NULL);
	HK_THREAD_LOCAL_SET(m_jobInfoIdx, HK_NULL);
	HK_THREAD_LOCAL_SET(m_isPrimaryWorkerThread, HK_NULL);
}


hkCheckDeterminismUtil::Fuid& hkCheckDeterminismUtil::Fuid::getZeroFuid()
{
	static Fuid fuid;
	fuid.m_0 = hkUint32(-1);
	fuid.m_1 = 0;
	fuid.m_2 = 0;
	fuid.m_3 = 0;
	return fuid;
}


void hkCheckDeterminismUtil::startWriteMode(const char* filename)
{
#if defined (HK_ENABLE_DETERMINISM_CHECKS)
	HK_ASSERT2(0xaf36affe, !m_sharedOutputStream, "You cannot switch to READ mode without calling finish() first.");
	m_sharedOutputStream = new hkOstream(filename);
	HK_ASSERT2(0xaf36affd, m_sharedOutputStream->isOk(), "Output file could not be opened.");

	m_mode = MODE_WRITE;

	HK_THREAD_LOCAL_SET(m_inputStream, m_sharedInputStream);
	HK_THREAD_LOCAL_SET(m_outputStream, m_sharedOutputStream);
#endif
}


void hkCheckDeterminismUtil::startCheckMode(const char* filename)
{
#if defined (HK_ENABLE_DETERMINISM_CHECKS)
	HK_ASSERT2(0xaf36affe, !m_sharedOutputStream, "You cannot switch to READ mode without calling finish() first.");

	m_sharedInputStream = new hkIstream(filename);

	if ( !m_sharedInputStream->isOk() )
	{
		HK_ASSERT2(0xaf36affe, false, "Input file not found.");
		finish();
	}
	else
	{
		m_mode = MODE_COMPARE;
	}

	HK_THREAD_LOCAL_SET(m_inputStream, m_sharedInputStream);
	HK_THREAD_LOCAL_SET(m_outputStream, m_sharedOutputStream);
#endif
}

void hkCheckDeterminismUtil::finish()
{
	if ( m_sharedInputStream )
	{
		// check whether we reached the end of the file
		{
			char tmpBuffer[4];	m_sharedInputStream->read(tmpBuffer, 1);
			HK_ASSERT(0xad87b754, !m_sharedInputStream->isOk());
		}

		delete m_sharedInputStream;
		m_sharedInputStream = HK_NULL;
	}
	else if ( m_sharedOutputStream )
	{
		m_sharedOutputStream->flush();
		delete m_sharedOutputStream;
		m_sharedOutputStream = HK_NULL;
	}

	HK_THREAD_LOCAL_SET(m_inputStream, m_sharedInputStream);
	HK_THREAD_LOCAL_SET(m_outputStream, m_sharedOutputStream);
}


void hkCheckDeterminismUtil::checkImpl(const void* object, int size)
{
	if (!size)
	{
		return;
	}
	const char* sourceObject = (const char*)object;

	if ( HK_THREAD_LOCAL_GET(m_outputStream) )
	{
		HK_THREAD_LOCAL_GET(m_outputStream)->write(sourceObject, size);
		HK_ASSERT( 0xf0323446, HK_THREAD_LOCAL_GET(m_outputStream)->isOk() );
	}
	else if ( HK_THREAD_LOCAL_GET(m_inputStream) )
	{
		hkInplaceArray<char, 256> readBuffer;
		readBuffer.setSize(size);
		HK_THREAD_LOCAL_GET(m_inputStream)->read(readBuffer.begin(), size);
		HK_ASSERT( 0xf0323445, HK_THREAD_LOCAL_GET(m_inputStream)->isOk() );

			// some variables helping debugging
		const hkReal* of = (const hkReal*)object; of = of;
		const hkReal* cf = (const hkReal*)readBuffer.begin(); cf = cf;
		const void*const* oh = (const void*const*)object; oh = oh;
		const void*const* ch = (const void*const*)readBuffer.begin(); ch = ch;

		{
			for (int i=0; i<size; i++)
			{
				HK_ASSERT(0xaf335142, sourceObject[i] == readBuffer[i]);
#				if ! defined (HK_DEBUG)
					if (sourceObject[i] != readBuffer[i])
					{
						int* nullInt = 0;
						*nullInt = 0;
					}
#				endif
			}
		}
	}
	else
	{
		HK_ASSERT2(0xad7655dd, false, "Neither stream exists.");
	}
}




//////////////////////////////////////////////////////////////////////////
//
// Registration functions used at the beginning and end of each hkpDynamicsJob, and multi-threading registration functions.
//
///////////////////////////////////////////////////mp///////////////////////


void hkCheckDeterminismUtil::initThreadImpl()
{
}

void hkCheckDeterminismUtil::quitThreadImpl()
{
	HK_THREAD_LOCAL_SET(m_inputStream, HK_NULL);
	HK_THREAD_LOCAL_SET(m_outputStream, HK_NULL);
	HK_THREAD_LOCAL_SET(m_jobInfoIdx, HK_NULL);
	HK_THREAD_LOCAL_SET(m_isPrimaryWorkerThread, HK_NULL);
}

void hkCheckDeterminismUtil::workerThreadStartFrameImpl(hkBool isPrimaryWorkerThread)
{
	{
		hkUlong tmp = isPrimaryWorkerThread;
		HK_THREAD_LOCAL_SET(m_isPrimaryWorkerThread, reinterpret_cast<void*&>(tmp));
	}

	if (isPrimaryWorkerThread)
	{
		HK_ASSERT(0XAD876716, !m_writingStFromWorker);
		m_writingStFromWorker = true;

		HK_ASSERT(0xad8766dd, m_primaryWorkerThreadInputStream == HK_NULL);
		HK_ASSERT(0xad8766dd, m_primaryWorkerThreadOutputStream == HK_NULL);

		// Create streams for single-threaded sections.
		registerAndStartJobImpl( Fuid::getZeroFuid() );

		void* tmp = HK_THREAD_LOCAL_GET(m_jobInfoIdx);
		m_primaryWorkerThreadJobInfoIdx = reinterpret_cast<int&>(tmp);
		m_primaryWorkerThreadInputStream = HK_THREAD_LOCAL_GET(m_inputStream);
		m_primaryWorkerThreadOutputStream = HK_THREAD_LOCAL_GET(m_outputStream);

	}
	else
	{
		HK_THREAD_LOCAL_SET(m_inputStream, HK_NULL);
		HK_THREAD_LOCAL_SET(m_outputStream, HK_NULL);
	}
}

void hkCheckDeterminismUtil::workerThreadFinishFrameImpl()
{
	if (HK_THREAD_LOCAL_GET(m_isPrimaryWorkerThread))
	{
		m_primaryWorkerThreadInputStream = HK_NULL;
		m_primaryWorkerThreadOutputStream = HK_NULL;

		HK_THREAD_LOCAL_SET(m_jobInfoIdx, reinterpret_cast<void*&>(m_primaryWorkerThreadJobInfoIdx));
		finishJob( Fuid::getZeroFuid() );

		HK_ASSERT(0XAD876, m_writingStFromWorker);
		m_writingStFromWorker = false;
	}
}

void hkCheckDeterminismUtil::registerAndStartJobImpl(Fuid& jobFuid)
{
	m_shared->enter();

	if (HK_THREAD_LOCAL_GET(m_isPrimaryWorkerThread))
	{
		HK_ASSERT(0XAD98666D, HK_THREAD_LOCAL_GET(m_inputStream) == m_primaryWorkerThreadInputStream);
		HK_ASSERT(0XAD98666D, HK_THREAD_LOCAL_GET(m_outputStream) == m_primaryWorkerThreadOutputStream);

		HK_ASSERT(0XAD876, m_writingStFromWorker);
	}
	else
	{
		HK_ASSERT(0XAD98666D, HK_THREAD_LOCAL_GET(m_inputStream) == HK_NULL);
		HK_ASSERT(0XAD98666D, HK_THREAD_LOCAL_GET(m_outputStream) == HK_NULL);
	}

	// add/find entry to/in the shared list
	int i;
	for (i = 0; (i < m_registeredJobs.getSize()) && (m_registeredJobs[i].m_jobFuid != jobFuid); i++) {}

	// create local stream
	if (m_mode == MODE_WRITE)
	{
		// make sure it is unique
		HK_ASSERT2(0xad9877da, i == m_registeredJobs.getSize(), "Internal error: Fuid is not frame-unique !!!");
		int tmp = m_registeredJobs.getSize();
		HK_THREAD_LOCAL_SET(m_jobInfoIdx, reinterpret_cast<void*&>(tmp));
		JobInfo& info = m_registeredJobs.expandOne();
		info.m_jobFuid = jobFuid;
		info.m_isOpen = true;
		info.m_data = new hkArray<char>;
		HK_THREAD_LOCAL_SET(m_outputStream, new hkOstream(*info.m_data));
	}
	else
	{
		HK_ASSERT2(0xad9877da, i < m_registeredJobs.getSize(), "Internal error: Fuid is not found !!!");
		HK_THREAD_LOCAL_SET(m_jobInfoIdx, reinterpret_cast<void*&>(i));
		// continue till the end of fthe m_registeredJobs, to ensure there is only one matching entry
		int j;
		for (j = i+1; (j < m_registeredJobs.getSize()) && (m_registeredJobs[j].m_jobFuid != jobFuid); j++) {}
		HK_ASSERT2(0xad9877da, j == m_registeredJobs.getSize(), "Internal error: Fuid is not frame-unique !!!");

		JobInfo& info = m_registeredJobs[i];
		HK_ASSERT2(0xad9877da, !info.m_isOpen, "Internal error: Fuid is not frame-unique !!!");
		info.m_isOpen = true;
		HK_THREAD_LOCAL_SET(m_inputStream, new hkIstream(info.m_data->begin(), info.m_data->getSize()) );
	}

	hkCheckDeterminismUtil::checkMt(0xacacacacul);

	m_shared->leave();
}

void hkCheckDeterminismUtil::finishJobImpl(Fuid& jobFuid)
{
	m_shared->enter();
	// destroy local stream

	hkCheckDeterminismUtil::checkMt(0xbcbcbcbcul);

	void* tmp = HK_THREAD_LOCAL_GET(m_jobInfoIdx);
	JobInfo& info = m_registeredJobs[reinterpret_cast<int&>(tmp)];
	HK_ASSERT2(0xad986dda, jobFuid == info.m_jobFuid, "Fuid inconsistency.");
	HK_ASSERT2(0xad9877db, info.m_isOpen, "Internal error: Fuid is not frame-unique !!!");
	info.m_isOpen = false;

	delete HK_THREAD_LOCAL_GET(m_inputStream);
	delete HK_THREAD_LOCAL_GET(m_outputStream);

	if (HK_THREAD_LOCAL_GET(m_isPrimaryWorkerThread))
	{
		HK_THREAD_LOCAL_SET(m_inputStream, m_primaryWorkerThreadInputStream);
		HK_THREAD_LOCAL_SET(m_outputStream, m_primaryWorkerThreadOutputStream);

		HK_ASSERT(0XAD876, m_writingStFromWorker);
	}
	else
	{
		HK_THREAD_LOCAL_SET(m_inputStream, HK_NULL);
		HK_THREAD_LOCAL_SET(m_outputStream, HK_NULL);
	}

	m_shared->leave();
}



void hkCheckDeterminismUtil::combineRegisteredJobsImpl() // only used on write
{
	HK_ASSERT(0xad8666dd, m_registeredJobs[0].m_jobFuid == Fuid::getZeroFuid());

	m_shared->enter();

	HK_ASSERT(0XAD876, !m_writingStFromWorker);

	hkUint32 check = hkUint32(0xadadadad);
	m_sharedOutputStream->write((char*)&check, sizeof(check));

	// header; jobs count
	int numRegisteredJobs = m_registeredJobs.getSize();
	m_sharedOutputStream->write((char*)&numRegisteredJobs, sizeof(numRegisteredJobs));

	// combine streams from registered jobs
	for (int i = 0; i < m_registeredJobs.getSize(); i++)
	{
		JobInfo& info = m_registeredJobs[i];
		Fuid fuid = info.m_jobFuid;
		m_sharedOutputStream->write((char*)&fuid, sizeof(fuid));
		int dataSize = info.m_data->getSize();
		m_sharedOutputStream->write((char*)&dataSize, sizeof(dataSize));
		m_sharedOutputStream->write(info.m_data->begin(), dataSize);

		// create an info/dispatching section used later for comparison
	}

	check = hkUint32(0xbdbdbdbd);
	m_sharedOutputStream->write((char*)&check, sizeof(check));


	// clear all info & copied stream parts
	{
		HK_ASSERT(0XAD876, !m_writingStFromWorker);
		HK_ASSERT(0XAD876655, m_primaryWorkerThreadInputStream == HK_NULL);
		HK_ASSERT(0XAD876655, m_primaryWorkerThreadOutputStream == HK_NULL);

		// destroy streams from individual jobs
		for (int i = 0; i < m_registeredJobs.getSize(); i++)
		{
			JobInfo& info = m_registeredJobs[i];
			HK_ASSERT2(0XAD8765dd, !info.m_isOpen, "Job not finished.");
			delete info.m_data;
		}
		m_registeredJobs.clear();
		m_registeredJobs.reserveExactly(0);
	}

	HK_ASSERT(0XAD876, !m_writingStFromWorker);

	m_shared->leave();
}

void hkCheckDeterminismUtil::extractRegisteredJobsImpl() // only used for read
{
	m_shared->enter();

	HK_ASSERT(0XAD876, !m_writingStFromWorker);

	HK_ASSERT(0XAD876655, m_primaryWorkerThreadInputStream == HK_NULL);
	HK_ASSERT(0XAD876655, m_primaryWorkerThreadOutputStream == HK_NULL);

	hkUint32 check;
	m_sharedInputStream->read((char*)&check, sizeof(check));
	HK_ASSERT2(0xad8655dd, check == hkUint32(0xadadadad), "Stream inconsistent.");

	HK_ASSERT2(0xad87656d, m_registeredJobs.getSize() == 0, "Internal inconsistency.");

	int numRegisteredJobs;
	m_sharedInputStream->read((char*)&numRegisteredJobs, sizeof(numRegisteredJobs));

	for (int i = 0; i < numRegisteredJobs; i++)
	{
		JobInfo& info = m_registeredJobs.expandOne();
		info.m_isOpen = false;
		info.m_data = new hkArray<char>();

		Fuid fuid;
		m_sharedInputStream->read((char*)&fuid, sizeof(fuid));
		info.m_jobFuid = fuid;
		int dataSize;
		m_sharedInputStream->read((char*)&dataSize, sizeof(dataSize));
		info.m_data->setSize(dataSize);
		m_sharedInputStream->read(info.m_data->begin(), dataSize);
		}

	m_sharedInputStream->read((char*)&check, sizeof(check));
	HK_ASSERT2(0xad8655d1, check == hkUint32(0xbdbdbdbd), "Stream inconsistent.");

	HK_ASSERT(0XAD876, !m_writingStFromWorker);

	m_shared->leave();
}

void hkCheckDeterminismUtil::clearRegisteredJobsImpl()
{
	m_shared->enter();

	HK_ASSERT(0XAD876, !m_writingStFromWorker);
	HK_ASSERT(0XAD876655, m_primaryWorkerThreadInputStream == HK_NULL);
	HK_ASSERT(0XAD876655, m_primaryWorkerThreadOutputStream == HK_NULL);

	// destroy streams from individual jobs
	for (int i = 0; i < m_registeredJobs.getSize(); i++)
	{
		JobInfo& info = m_registeredJobs[i];
		HK_ASSERT2(0XAD8765dd, !info.m_isOpen, "Job not finished.");
		delete info.m_data;
	}
	m_registeredJobs.clear();
	m_registeredJobs.reserveExactly(0);

	m_shared->leave();

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
