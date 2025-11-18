/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeDescription.h>


// Constructor, sets defaults.
hctAttributeDescription::hctAttributeDescription()
:
	m_name (HK_NULL),
	m_forcedType (LEAVE),
	m_enum (HK_NULL),
	m_hint (HINT_NONE),
	m_floatScale (1.0f),
	m_clearHints (false)
{
}


hctAttributeDescription* hctAttributeGroupDescription::findAttributeDescriptionByName(const char* name) const
{
	for (int a=0; a < m_numAttributeDescriptions; ++a)
	{
		if ( m_attributeDescriptions[a].m_name && (hkString::strCasecmp(m_attributeDescriptions[a].m_name, name)==0) )
		{
			return &m_attributeDescriptions[a];
		}
	}
	return HK_NULL;
}

hctAttributeGroupDescription* hctAttributeDescriptionDatabase::findAttributeDescriptionGroupByName(const char* name) const
{
	for (int i=0; i < m_numGroupDescriptions; ++i)
	{
		hctAttributeGroupDescription& desc = m_groupDescriptions[i];
		if (hkString::strCasecmp(desc.m_name, name)==0)
		{
			return &desc;
		}
	}

	return HK_NULL;
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
