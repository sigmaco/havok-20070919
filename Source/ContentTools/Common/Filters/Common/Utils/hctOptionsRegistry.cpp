/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

hctOptionsRegistry::hctOptionsRegistry (const char* filterName)
{
	hkString keyPath = hkString("Software\\Havok\\hkFilters\\") + filterName;

	DWORD dispos;
	RegCreateKeyEx( HKEY_CURRENT_USER, keyPath.cString(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_registryKey, &dispos);
}

int hctOptionsRegistry::getIntWithDefault ( const char* option, int iDefault)
{
	DWORD v, vSize; 
	if (RegQueryValueEx( m_registryKey, TEXT(option), NULL, NULL, (LPBYTE)&v, &vSize ) == ERROR_SUCCESS )
	{
		return (int)v;
	}

	return iDefault;
}

void hctOptionsRegistry::setInt (const char* option, int val)
{
	DWORD v, vSize; 
	v = (DWORD)val;
	vSize = sizeof(DWORD);
	RegSetValueEx( m_registryKey, TEXT(option), NULL, REG_DWORD, (LPBYTE)&v, vSize );
}

bool hctOptionsRegistry::getBoolWithDefault (const char* option, bool bDefault)
{
	return getIntWithDefault(option, bDefault? 1 : 0) ? true : false;
}

void hctOptionsRegistry::setBool (const char* option, bool b)
{
	setInt(option, (int)b);
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
