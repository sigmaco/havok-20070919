/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// OS X framework headers
#include <CoreServices/CoreServices.h>
#include <Kernel/mach/mach_time.h>

// AbsoluteTime/Nanoseconds are structures equivalent to hkUint64

class hkMacSystemClock : public hkSystemClock
{
	public:
		
		hkMacSystemClock()
		{
			uint64_t nano = 1000000000;
			Nanoseconds oneSecondInNano =  *(Nanoseconds *) &nano;
			AbsoluteTime oneSecondInAbsolute = NanosecondsToAbsolute( oneSecondInNano );
			m_ticksPerSecond = *(hkUint64 *) &oneSecondInAbsolute;
		}
		
		virtual hkUint64 getTickCounter()
		{
			return (hkUint64) mach_absolute_time();
		}
		
		virtual hkUint64 getTicksPerSecond()
		{
			return m_ticksPerSecond;
		}
		
	private:
		
		hkUint64 m_ticksPerSecond;
};

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
