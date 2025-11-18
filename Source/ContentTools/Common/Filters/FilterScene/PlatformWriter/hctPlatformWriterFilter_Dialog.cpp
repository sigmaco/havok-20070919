/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterFilter.h>

#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>

#include <Common/SceneData/Scene/hkxSceneUtils.h>
#include <Common/SceneData/Graph/hkxNode.h>

#include <Common/SceneData/Environment/hkxEnvironment.h>

#include <shlwapi.h>
#include <tchar.h>
#include <stdio.h>


LPWSTR ConvertMBToWide( TCHAR* tStr )
{
	int len = MultiByteToWideChar( CP_ACP, 0, tStr, -1, 0, 0);
	WCHAR* res = hkAllocate<WCHAR>( len, HK_MEMORY_CLASS_EXPORT );
	MultiByteToWideChar(CP_ACP, 0, tStr, -1, res, len);
	return res;
}
TCHAR* ConvertWideToMB( LPCWSTR wideStr )
{
	int len = WideCharToMultiByte( CP_ACP, 0, wideStr, -1, 0, 0 , 0, 0 );
	TCHAR* res = hkAllocate<TCHAR>( len, HK_MEMORY_CLASS_EXPORT );
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, res, len, 0, 0);
	return res;
}

extern HINSTANCE hInstance;


void _fillCombo( HWND combo )
{
	for (int i=0; i < hctPlatformWriterFilter::m_optionToLayoutTableSize; ++i)
	{
		hctPlatformWriterFilter::OptionToLayoutEntry& e = hctPlatformWriterFilter::m_optionToLayoutTable[i];
		SendMessage( combo, CB_ADDSTRING, 0, (LPARAM)e.label);
	}
}

void _enableAllCustom( HWND dlg, bool enabled)
{
	EnableWindow(GetDlgItem(dlg, IDC_EDIT_PTR_BYTES), enabled);
	EnableWindow(GetDlgItem(dlg, IDC_LITTLE_ENDIAN), enabled);
	EnableWindow(GetDlgItem(dlg, IDC_REUSE_PADDING_OPT), enabled);
	EnableWindow(GetDlgItem(dlg, IDC_EMPTYBASE_CLASS_OPT), enabled);
	EnableWindow(GetDlgItem(dlg, IDC_STATIC_BYTESINPTR), enabled);
}

void _reflectCurrentPlatform( HWND hWnd, const hctPlatformWriterFilter::OptionToLayoutEntry& curEntry )
{
	const hkStructureLayout::LayoutRules* rules = curEntry.layout;
	if ( rules )
	{
		TCHAR text[1024]; _stprintf(text, "%d", rules->m_bytesInPointer);
		SetWindowText( GetDlgItem(hWnd, IDC_EDIT_PTR_BYTES), text);
		CheckDlgButton(hWnd, IDC_LITTLE_ENDIAN, rules->m_littleEndian);
		CheckDlgButton(hWnd, IDC_REUSE_PADDING_OPT, rules->m_reusePaddingOptimization);
		CheckDlgButton(hWnd, IDC_EMPTYBASE_CLASS_OPT, rules->m_emptyBaseClassOptimization);
	}
	else
	{
		SetWindowText( GetDlgItem(hWnd, IDC_EDIT_PTR_BYTES), "0");
		CheckDlgButton(hWnd, IDC_LITTLE_ENDIAN, FALSE);
		CheckDlgButton(hWnd, IDC_REUSE_PADDING_OPT, FALSE);
		CheckDlgButton(hWnd, IDC_EMPTYBASE_CLASS_OPT, FALSE);
		_enableAllCustom(hWnd, false);
	}
}

struct _FilterInfo
{
	hctPlatformWriterFilter* m_filter;
	const hkRootLevelContainer* m_originalContents;
};
BOOL CALLBACK hkFilterPlatformWriterDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	_FilterInfo* filterInfo = reinterpret_cast<_FilterInfo*> ( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA));

	switch(message)
	{
		case WM_INITDIALOG:
		{
			filterInfo = (_FilterInfo*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later
			filterInfo->m_filter->m_optionsDialog = hWnd;

			// If no filename has been set, display the default.
			if ( filterInfo->m_filter->m_filename.getLength() == 0 )
			{
				filterInfo->m_filter->m_filename = hkString( ".\\$(asset)_$(configuration).hkx" );
			}
			SetDlgItemText(hWnd, IDC_EDIT_FILENAME, filterInfo->m_filter->m_filename.cString());

			// Custom data
			TCHAR text[1024]; _stprintf(text, "%d", filterInfo->m_filter->m_options.m_bytesInPointer);
			SetWindowText( GetDlgItem(hWnd, IDC_EDIT_PTR_BYTES), text);
			CheckDlgButton(hWnd, IDC_LITTLE_ENDIAN, filterInfo->m_filter->m_options.m_littleEndian);
			CheckDlgButton(hWnd, IDC_REUSE_PADDING_OPT, filterInfo->m_filter->m_options.m_reusePaddingOptimized);
			CheckDlgButton(hWnd, IDC_EMPTYBASE_CLASS_OPT, filterInfo->m_filter->m_options.m_emptyBaseClassOptimized);

			// Combo box
			HWND hwndCombo = GetDlgItem(hWnd, IDC_PLATFORM_PRESET_COMBO);
			_fillCombo( hwndCombo );
			// Set cur sel
			int curPresetIndex = hctPlatformWriterFilter::findPreset( filterInfo->m_filter->m_options.m_preset );
			SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM)curPresetIndex, 0 );

			bool isCustom = filterInfo->m_filter->m_options.m_preset == OPTTYPE::CUSTOM;
			_enableAllCustom( hWnd, isCustom );
			if (isCustom)
			{
				TCHAR text[1024]; _stprintf(text, "%d", filterInfo->m_filter->m_options.m_bytesInPointer);
				SetWindowText( GetDlgItem(hWnd, IDC_EDIT_PTR_BYTES), text);
				CheckDlgButton(hWnd, IDC_LITTLE_ENDIAN, filterInfo->m_filter->m_options.m_littleEndian);
				CheckDlgButton(hWnd, IDC_REUSE_PADDING_OPT, filterInfo->m_filter->m_options.m_reusePaddingOptimized);
				CheckDlgButton(hWnd, IDC_EMPTYBASE_CLASS_OPT, filterInfo->m_filter->m_options.m_emptyBaseClassOptimized);
			}
			else
			{
				_reflectCurrentPlatform(hWnd, hctPlatformWriterFilter::m_optionToLayoutTable[curPresetIndex]);
			}

			// User tag only available in Binary output
			const BOOL isXml = !isCustom && (curPresetIndex == 0);
			EnableWindow(GetDlgItem(hWnd, IDC_ED_USER_TAG), !isXml);

			CheckDlgButton(hWnd, IDC_CB_REMOVE_METADATA, filterInfo->m_filter->m_options.m_removeMetadata);
			CheckDlgButton(hWnd, IDC_CB_SAVE_ENVIRONMENT, filterInfo->m_filter->m_options.m_saveEnvironmentData);

			_stprintf(text, "%d", filterInfo->m_filter->m_options.m_userTag);
			SetWindowText ( GetDlgItem(hWnd, IDC_ED_USER_TAG), text);

			return TRUE; // did handle it
		}
		case WM_COMMAND: // UI Changes
		{
			switch (LOWORD(wParam))
			{
				case IDC_PLATFORM_PRESET_COMBO:
				{
					HWND hwndCombo = GetDlgItem(hWnd, IDC_PLATFORM_PRESET_COMBO);
					LRESULT ir = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
					bool isCustom = hctPlatformWriterFilter::m_optionToLayoutTable[ir].preset == OPTTYPE::CUSTOM;
					_enableAllCustom( hWnd, isCustom);
					if (!isCustom) // leave as is (just enabled)
					{
						_reflectCurrentPlatform( hWnd, hctPlatformWriterFilter::m_optionToLayoutTable[ir] );
					}

					const BOOL isXml = !isCustom && (ir == 0);
					EnableWindow(GetDlgItem(hWnd, IDC_ED_USER_TAG), !isXml);

					break;
				}
				case IDC_BROWSE_FILENAME:
				{
					TCHAR filename[2048];
					filename[0] = '\0';

					// Get the filename from the edit control.
					if ( GetDlgItemText( hWnd, IDC_EDIT_FILENAME, filename, 2048 ) > 0 )
					{
						filterInfo->m_filter->m_filename = filename;
						filterInfo->m_filter->m_filename = filterInfo->m_filter->m_filename.replace( '/', '\\' );

						// Check whether m_filename is relative or not.
						if( PathIsRelative( filterInfo->m_filter->m_filename.cString() ) )
						{
							// It's relative to the asset, so append the asset path in order to open the dialog in the correct location.
							hkString fullFileName = filterInfo->m_filter->m_assetFolder + filterInfo->m_filter->m_filename;
							strncpy( filename, fullFileName.cString(), 2048);
						}
						else
						{
							// It's absolute, so copy it back into the filename buffer as is (to update any '/'->'\' changes).
							strncpy( filename, filterInfo->m_filter->m_filename.cString(), 2048);
						}
					}

					OPENFILENAME op;
					hkString::memSet( &op, 0, sizeof(OPENFILENAME) );
					op.lStructSize = sizeof(OPENFILENAME);
					op.hwndOwner = hWnd;
					op.lpstrFilter = "Havok Scene Files (*.HKX)\0*.HKX\0All Files (*.*)\0*.*\0\0";
					if ( PathIsRoot( filename ) )
					{
						op.lpstrInitialDir = filename;
					}
					else
					{
						op.lpstrInitialDir = filterInfo->m_filter->m_assetFolder.cString();
						op.lpstrFile = filename;
					}
					op.lpstrDefExt = ".hkx";
					op.nMaxFile = 2048;
					op.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_NOREADONLYRETURN | OFN_PATHMUSTEXIST;
					if ( GetSaveFileName(&op) )
					{
						hctFilterUtils::getReducedFilename( op.lpstrFile, filterInfo->m_filter->m_assetFolder, filterInfo->m_filter->m_filename );
						SetDlgItemText(hWnd, IDC_EDIT_FILENAME, filterInfo->m_filter->m_filename.cString() );
					}
				}
			}
			break;
		}
		case WM_DESTROY:
			{
				if (filterInfo) delete filterInfo;
			}
	}
	return FALSE; //didn't handle it / didn't do much with it
}


HWND hctPlatformWriterFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
		hideOptions();

	// Try to guess where is the "main" folder for the asset, from the environment or scene data objects
	hctFilterUtils::getAssetFolder(*m_filterManager->getOriginalContents(), m_assetFolder);

	_FilterInfo* fi = new _FilterInfo;
	fi->m_originalContents = getFilterManager()->getOriginalContents();
	fi->m_filter = this;

	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PLATFORM_WRITER_DIALOG),
		owner, hkFilterPlatformWriterDialogProc, (LPARAM) fi );

	return m_optionsDialog;
}

void hctPlatformWriterFilter::updateOptions()
{
	if (m_optionsDialog)
	{
		HWND hwndCombo = GetDlgItem(m_optionsDialog, IDC_PLATFORM_PRESET_COMBO);
		LRESULT ir = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
		m_options.m_preset = hctPlatformWriterFilter::m_optionToLayoutTable[ir].preset;
		m_options.m_littleEndian = IsDlgButtonChecked(m_optionsDialog, IDC_LITTLE_ENDIAN) != FALSE;
		m_options.m_reusePaddingOptimized = IsDlgButtonChecked(m_optionsDialog, IDC_REUSE_PADDING_OPT) != FALSE;
		m_options.m_emptyBaseClassOptimized = IsDlgButtonChecked(m_optionsDialog, IDC_EMPTYBASE_CLASS_OPT) != FALSE;
		m_options.m_removeMetadata = IsDlgButtonChecked(m_optionsDialog, IDC_CB_REMOVE_METADATA) != FALSE;
		m_options.m_saveEnvironmentData = IsDlgButtonChecked(m_optionsDialog, IDC_CB_SAVE_ENVIRONMENT) != FALSE;
		TCHAR text[2048];
		GetDlgItemText(m_optionsDialog, IDC_EDIT_PTR_BYTES, text, 2048);
		m_options.m_bytesInPointer = (hkInt8)atoi(text);
		if (m_options.m_bytesInPointer < 4) m_options.m_bytesInPointer = 4;
		else if (m_options.m_bytesInPointer > 16) m_options.m_bytesInPointer = 16;

		GetDlgItemText(m_optionsDialog, IDC_ED_USER_TAG, text, 2048);
		m_options.m_userTag = (hkUint32)atoi(text);

		GetDlgItemText(m_optionsDialog, IDC_EDIT_FILENAME, text, 2048);
		hctFilterUtils::getReducedFilename( text, m_assetFolder, m_filename );
	}
}

void hctPlatformWriterFilter::hideOptions()
{
	updateOptions();
	if (m_optionsDialog)
	{
		DestroyWindow(m_optionsDialog);
	}
	m_optionsDialog = NULL;
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
