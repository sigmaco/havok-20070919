/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


/*
	If you are suing PMC_SETUP_OVERVIEW_PB0T0 setup (so only thread 0 is timed), then the counter regs are:
	[ 0] CPB_IU_PFM_EVENT_IL1_MISS_CYCLES (.. L1 Cache Miss)
	[ 1] EPB_IU_PFM_EVENT_INSTR_FLUSHED
	[ 2] CPB_IU_PFM_EVENT_INSTR_STALL 
	[ 3] CPB_IU_PFM_EVENT_INSTR_DEP_STALL
	[ 4] CPB_PFM_EVENT_T0_PPC_COMMIT (.. Instructions computed, needs * 2 to get actual count)
	[ 5] SPB_XU_PFM_EVENT_LOAD_MISS
	[ 6] SPB_XU_PFM_EVENT_LOAD_MISS_LHS  (.. Load-Hit-Store)
	[ 7] SPB_XU_PFM_EVENT_DERAT_MISS
	[ 8] EL2 P2 d miss(D/3-4)
	[ 9] EL2 P0 d hit(D/3-5)
	[10] EL2 P1 d hit(D/3-6)
	[11] EL2 P2 d hit(D/3-7)
	[12] CAll RC busy(D/3-0)
	[13] CRC disp due to dload,iload,dcbt,st(D/3-1)
	[14] EL2 P0 d miss(D/3-2)  (.. L2 DCache Miss)
	[15] EL2 P1 d miss(D/3-3)
*/

#		define HK_HvxGetPRVAddr(x) (((hkUlong)0x8FFF1000) + (x))
#		define HK_HvxGetPRVFromAddr(x) (*((unsigned __int64*)(x)))
#		define HK_HvxGetPRV32FromAddr(sprAddr) ((unsigned long)((HK_HvxGetPRVFromAddr(sprAddr)>>32)&0xFFFFFFFF))
#		define HK_PFM_COUNTER_0_REG_ADDR 0x200
#		define HK_PFM_CPT_CYCLES_REG_ADDR 0x1E0

extern hkUlong g_hkXbox360PerfSampleRegAddr; // set this to whatever reg (0..15, values below) you want to grab into the second timer stream slot. Defaults to 6
inline hkUlong hkGetXbox360PerfRegAddr( hkUint32 reg /*0..15*/ )
{
	return HK_HvxGetPRVAddr( (reg*8) + HK_PFM_COUNTER_0_REG_ADDR ); // 0x8FFF1200 == reg0 0x8FFF1208 == reg1, etc.
}
inline void hkSetXbox360PerfReg( hkUint32 reg /*0..15*/ )
{
	g_hkXbox360PerfSampleRegAddr = HK_HvxGetPRVAddr( (reg*8) + HK_PFM_COUNTER_0_REG_ADDR ); // 0x8FFF1200 == reg0 0x8FFF1208 == reg1, etc.
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
