/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/Filters/hctFilterProcessingUtil.h> 
#include <ContentTools/Common/SceneExport/Memory/hctSceneExportMemory.h> 
#include <ContentTools/Common/SceneExport/Error/hctSceneExportError.h> 

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

#include <stdlib.h> // for getenv


hctFilterProcessingUtil::hctFilterProcessingUtil( void* ownerWindowHandle )
:
	m_filterManagerDll(HK_NULL),
	m_filterManager(HK_NULL)
{
}

const char* hctFilterProcessingUtil::getFilterManagerPath() const
{
	return m_filterManagerPath.cString();
}

/// Get the path used to load attribute descriptions (for processing)
const char* hctFilterProcessingUtil::getAttributeProcessingPath() const
{
	m_attributeProcessingPath = m_filterManagerPath+"\\attributeProcessing";
	return m_attributeProcessingPath.cString();
}

/// Get the path used to load attribute selections
const char* hctFilterProcessingUtil::getAttributeSelectionPath() const
{
	m_attributeSelectionPath = m_filterManagerPath+"\\attributeSelection";
	return m_attributeSelectionPath.cString();
}

hkBool hctFilterProcessingUtil::load( const char* havokPath )
{
	if (m_filterManagerDll)
	{
		unload();
	}

	m_filterManagerPath = havokPath;
	hkString managerPath = m_filterManagerPath + "\\hctFilterManager.dll";
	HMODULE dllHandle = LoadLibrary( managerPath.cString() );

	// If we've found the DLL we can use it.
	if (dllHandle)
	{
		hkGetFilterManagerDllFunc getFilterManagerDllFunc = (hkGetFilterManagerDllFunc) GetProcAddress( dllHandle, "getFilterManagerDll");
		
		if( getFilterManagerDllFunc )
		{		
			m_filterManagerDll = getFilterManagerDllFunc (dllHandle);

			unsigned int dllVersion = m_filterManagerDll->getDllVersion();
			unsigned int currentDllVersion = hctBaseDll::getCurrentDllVersion();

			if ( HCT_IS_MINOR_COMPATIBLE( currentDllVersion, dllVersion ) ) // same version (ignoring patch)
			{
				// Init the shared mem system.
				hctBaseDll::BaseSystemInfo baseSystemInfo;
				hkSceneExportMemory::getBaseSystemInfo(baseSystemInfo);

				m_filterManagerDll->initDll(&baseSystemInfo);

				// Create a manager
				m_filterManager = m_filterManagerDll->createFilterManager();

				if (m_filterManager)
				{
					return true;
				}
			}
		}
		
		unload();
		
		MessageBox( NULL, "The Havok Filter Manager DLL could not be loaded.\nYou may need to reinstall the Havok Content Tools package.\0", "Warning: Load failed", MB_OK | MB_ICONWARNING | MB_TASKMODAL | MB_TOPMOST );
	}
	else
	{
		char buf[500];
		hkString::sprintf( buf, "The Havok Filter Manager DLL was not found in the expected location:\n%s.\n\nYou may need to reinstall the Havok Content Tools package.\0", havokPath );
		MessageBox( NULL, buf, "Warning: Missing DLL", MB_OK | MB_ICONWARNING | MB_TASKMODAL | MB_TOPMOST );
	}

	return false;
}

hkBool hctFilterProcessingUtil::unload()
{
	if (m_filterManager)
	{
		m_filterManagerDll->deleteFilterManager(m_filterManager);
		m_filterManager = HK_NULL;
	}

	// Release the manager DLL
	if (m_filterManagerDll)
	{
		m_filterManagerDll->quitDll();

		FreeLibrary( m_filterManagerDll->getDllModule() );

		m_filterManagerDll = HK_NULL;
	}

	return true;
}


void hctFilterProcessingUtil::openFilterManager(hkRootLevelContainer& data, hkBool& shouldSaveConfigOut)
{
	if ( m_filterManager )
	{
		// EXP-698
		hctFilterClassRegistry& filterRegistry = m_filterManager->accessFilterClassRegistry();
		registerSceneTypes(filterRegistry);

		// EXP-841
		registerDefaultThreadCallback();

		m_filterManager->openFilterManager( (HWND) m_ownerHwnd, data, shouldSaveConfigOut );
	}
	else
	{
		shouldSaveConfigOut = false;
	}
}

void hctFilterProcessingUtil::processBatch( hkRootLevelContainer& data, hctFilterMemoryTracker* tracker )
{
	if (!m_filterManager)
	{
		return;
	}

	// Process all configurations (by setting the configurationIndex param to -1)
	hctFilterMemoryTracker* _tracker = tracker ? tracker : new hctFilterMemoryTracker;
	
	// EXP-698
	hctFilterClassRegistry& filterRegistry = m_filterManager->accessFilterClassRegistry();
	registerSceneTypes(filterRegistry);

	// EXP-841
	registerDefaultThreadCallback();

	m_filterManager->processBatch( (HWND)m_ownerHwnd, data, *_tracker );

	// no processes should still be active at this stage

	if (_tracker != tracker)
	{
		_tracker->deallocateAll();
		delete _tracker;
	}
}

unsigned int hctFilterProcessingUtil::getCurrentOptionsVersion () const
{
	if (m_filterManager)
	{
		return m_filterManager->getFilterManagerVersion();
	}
	return 0;
}

int hctFilterProcessingUtil::getOptionsSize() const
{
	if (m_filterManager)
	{
		return m_filterManager->getConfigurationSet( HK_NULL );
	}
	return 0;
}

void hctFilterProcessingUtil::getOptions(void* buf) const
{
	if (m_filterManager)
	{
		m_filterManager->getConfigurationSet(buf);
	}
}

void hctFilterProcessingUtil::setOptions(const void* buf, int bufSize)
{
	if (m_filterManager)
	{
		m_filterManager->setConfigurationSet( buf, bufSize );
	}
}

void hctFilterProcessingUtil::registerThreadCallback( const hctFilterThreadCallback* cb )
{
	if (m_filterManager)
	{
		m_filterManager->registerThreadCallback(cb);
	}
}

void hctFilterProcessingUtil::mergeRegistry (const hctFilterClassRegistry& otherRegistry)
{
	HK_ASSERT2(0x238d782a, m_filterManager, "You can't call mergeRegistry until the filter manager is loaded");

	m_filterManager->accessFilterClassRegistry().merge(otherRegistry);
}

void hctFilterProcessingUtil::mergeErrors (const hctSceneExportError* otherHandler)
{
	hctSceneExportError* handler = m_filterManager->getErrorHandler();
	if( handler )
	{
		handler->merge( otherHandler );
	}
}

class DefaultThreadCallback : public hctFilterThreadCallback
{
	public:

		/*virtual*/ void newThreadCreated (hkThreadMemory* threadMemory) const
		{
			hkBaseSystem::initThread(threadMemory);
		}
};

// EXP-841
void hctFilterProcessingUtil::registerDefaultThreadCallback ()
{
	static DefaultThreadCallback g_defaultThreadCallback;
	m_filterManager->registerThreadCallback(&g_defaultThreadCallback);
}


/*static*/ void hctFilterProcessingUtil::registerSceneTypes (class hctFilterClassRegistry& classReg)
{
	// EXP-698
	#define HK_ABSTRACT_CLASS(A)

	#define HK_STRUCT(S) \
		static const hkTypeInfo S##TypeInfo(#S,HK_NULL,HK_NULL,HK_NULL); \
		extern const hkClass S##Class;							\
		classReg.registerClass( &(S##TypeInfo), &(S##Class) );	

	#define HK_CLASS(C) \
		extern const hkTypeInfo C##TypeInfo;					\
		extern const hkClass C##Class;							\
		classReg.registerClass( &(C##TypeInfo), &(C##Class) );	

	#include <Common/Base/Classes/hkBaseClasses.h>
	#include <Common/Serialize/Classes/hkSerializeClasses.h>
	#include <Common/SceneData/Classes/hkSceneDataClasses.h>
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
