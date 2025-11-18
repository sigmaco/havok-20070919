/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_hkSpuPortManager_H
#define HK_BASE_hkSpuPortManager_H

	/// Manages spu port to event queue connections.
	/// Note that some event ports (hkSpuHelperThread::HelpType) are
	/// hardcoded and not managed.
class hkSpuPortManager
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuPortManager );

		enum { PORT_AUTO=hkUint32(-1), PORT_UNALLOCATED=hkUint32(-1) };

		hkSpuPortManager();
		~hkSpuPortManager();

			/// Set the target event queue.
		void setEventQueue(hkUint32 eventQueue);
		
			/// Get the target event queue.
		hkUint32 getEventQueue() const { return m_eventQueue; }

			/// Get the spu port.
		hkUint32 getSpuPort() const;

			/// Get the head of the managed list.
			/// The constructor puts itself on this list so you can get a list
			/// of all managed ports in combination with getNext().
		static hkSpuPortManager* getFirst();

			/// Get the next element of the managed list.
			/// See also getFirst()
		hkSpuPortManager* getNext() const { return m_next; }

			/// Initially the only unusable ports are the ones in hkSpuHelperThread.
			/// You will need to call this early, before any ports have been allocated.
			/// Each bit set in the mask corresponds to a reserved port.
		static hkResult dontUsePorts( hkUint64 mask );

			/// Debuggging aid.
			/// New ports cannot be created after the spus have started.
		static void setSpuStarted( hkBool32 started );

	private:

		hkUint32 allocateSpuPort(hkUint32 spuPort=PORT_AUTO);

	private:

		hkUint32 m_eventQueue;
		hkUint32 m_spuPort;
		hkSpuPortManager* m_next;
};

#endif // HK_BASE_hkSpuPortManager_H

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
