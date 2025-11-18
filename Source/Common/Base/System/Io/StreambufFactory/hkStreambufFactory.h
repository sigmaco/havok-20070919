/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKSTREAMBUFSOURCE_H
#define HKBASE_HKSTREAMBUFSOURCE_H

class hkStreamReader;
class hkStreamWriter;

/// Interface for hkStreamReader/hkStreamWriter creation.
/// When streams and archives are given a resource to open by name, they
/// ask the streambuf factory to open it for them. The user may wish to
/// replace the default factory with one which reads from packed files
/// or searches in several locations for instance.
class hkStreambufFactory : public hkSingleton<hkStreambufFactory>
{
	public:

		hkStreambufFactory() {}
			/// Havok has two 'standard' console streams - stdout and stderr.
		enum StdStream { STDOUT=1, STDERR };

			/// Returns a streambuf for file 'name' or null if unable.
		virtual hkStreamReader* openReader(const char* name) = 0;

			/// Returns a streambuf for file 'name' or null if unable.
		virtual hkStreamWriter* openWriter(const char* name) = 0;
};

#endif // HKBASE_HKSTREAMBUFSOURCE_H

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
