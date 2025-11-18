/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkcstdlib.h>

class hkLinuxSystemClock : public hkSystemClock
{
	public:

		virtual hkUint64 getTickCounter()
		{
			hkUint64 ticks;
			__asm__ __volatile__ (	"rdtsc\n\t"
									"movl %%eax,  (%0)\n\t"
									"movl %%edx, 4(%0)\n\t"
										: /* no output regs */
										: "D" (&ticks)
										: "%eax", "%edx");
			return ticks;
		}

		virtual hkUint64 getTicksPerSecond()
		{
			static hkUint64 freq = 0;

			if(freq==0)
			{
				FILE* fin = fopen("/proc/cpuinfo", "r");
				if( fin )
				{
					const int bufsize = 1024;
					char buf[bufsize];
					int buflen = fread(buf, 1, bufsize, fin);
					if( buflen > 0 )
					{
						const char marker[] = "cpu MHz\t\t:";
						const char* mhz = hkString::strStr(buf, marker);
						if( mhz != HK_NULL )
						{
							freq = static_cast<hkUint64>( 1000000 * atof(mhz + sizeof(marker)));
						}
					}
				}

				if( freq == 0 )
				{
					// fallback assumes 500 MHz
					HK_WARN(0x1da6abe3, "Unable to detect cpu speed. Do you have /proc kernel support?");
					freq = 500000000;
				}
			}
			return freq;
		}
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
