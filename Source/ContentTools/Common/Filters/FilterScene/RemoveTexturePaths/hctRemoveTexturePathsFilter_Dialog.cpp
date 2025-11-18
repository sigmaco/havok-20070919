/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <ContentTools/Common/Filters/FilterScene/RemoveTexturePaths/hctRemoveTexturePathsFilter.h>

#include <shlobj.h>


extern HINSTANCE hInstance;

BOOL CALLBACK hkFilterTextureRemovePathsDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{	
	hctRemoveTexturePathsFilter *tpr = reinterpret_cast<hctRemoveTexturePathsFilter*>( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA) ); 

	switch(message) 
	{
		case WM_INITDIALOG:
		{	
			HWND pathWnd = GetDlgItem(hWnd, IDC_TRP_PATHS);
			tpr = (hctRemoveTexturePathsFilter*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later

			SendMessage(pathWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT); // Set style
	
			// Text item
			LVITEM LvItem;
            memset(&LvItem,0,sizeof(LvItem)); // Reset Item Struct
			LvItem.mask=LVIF_TEXT;   // Text Style
			LvItem.cchTextMax = 260; // Max size of test
			int i=0,j=0,k=0;
			const char* paths = tpr->m_paths.cString();
			while (paths[j])
			{
				i = j;
				while (paths[i] && (paths[i] != ';'))
					++i;

				if ((i - j) > 0)
				{
					hkString str(&paths[j], i-j);
					LvItem.iItem = k++; 
					LvItem.pszText = const_cast<TCHAR*>( TEXT( str.cString() ) );
					ListView_InsertItem(pathWnd, &LvItem);
				}				
				j = paths[i] ? i + 1 : i;
			}
		}
		return TRUE;

		case WM_COMMAND:
			switch ( LOWORD(wParam) ) 
			{
				case IDC_TRP_MODIFY:
					{
						HWND pathWnd = GetDlgItem(hWnd, IDC_TRP_PATHS); 

						// Get the first selected path, which is the one we'll modify.
						int selectedItem = ListView_GetNextItem( pathWnd, -1, LVNI_SELECTED );

						if ( selectedItem != -1 )
						{
							// Deselect all other selected paths so the user can see which one is being modified.
							int curItem = ListView_GetNextItem( pathWnd, selectedItem, LVNI_SELECTED );
							while ( curItem != -1 )
							{
								ListView_SetItemState( pathWnd, curItem, 0x00, 0xFF );
								curItem = ListView_GetNextItem( pathWnd, curItem, LVNI_SELECTED );
							}

							// Open a browser so the user can choose a new path to replace the selected one.
							char displayName[MAX_PATH];

							LPMALLOC pMalloc;
							SHGetMalloc(&pMalloc);

							BROWSEINFO pbi;
							hkString::memSet( &pbi, 0, sizeof(pbi));
							pbi.hwndOwner = pathWnd;
							pbi.lpszTitle = TEXT("Please select a texture path");
							pbi.ulFlags = BIF_USENEWUI;
							pbi.pszDisplayName = displayName;

							LPITEMIDLIST folders = SHBrowseForFolder(&pbi);
							if (folders && SHGetPathFromIDList(folders, displayName) )
							{
								int dnl = hkString::strLen( displayName );
								if (dnl < MAX_PATH-1)
								{
									if ((dnl > 0) && (displayName[dnl-1] != '\\'))
										displayName[dnl] = '\\'; // add a backslash to the end 
									displayName[dnl+1] = '\0';
								}
								// Rename the selected item.
								ListView_SetItemText( pathWnd, selectedItem, 0, displayName );
							}
							pMalloc->Free(folders);
							pMalloc->Release();
						}
					}
					break;
				case IDC_TRP_ADD:
					{
						HWND pathWnd = GetDlgItem(hWnd, IDC_TRP_PATHS); 
			
						char displayName[MAX_PATH];
	
						LPMALLOC pMalloc;
					    SHGetMalloc(&pMalloc);

						BROWSEINFO pbi;
						hkString::memSet( &pbi, 0, sizeof(pbi));
						pbi.hwndOwner = pathWnd;
						pbi.lpszTitle = TEXT("Please select a texture path");
						pbi.ulFlags = BIF_USENEWUI;
						pbi.pszDisplayName = displayName;

						LPITEMIDLIST folders = SHBrowseForFolder(&pbi);
						if (folders && SHGetPathFromIDList(folders, displayName) )
						{
							int dnl = hkString::strLen( displayName );
							if (dnl < MAX_PATH-1)
							{
								if ((dnl > 0) && (displayName[dnl-1] != '\\'))
									displayName[dnl] = '\\'; // add a backslash to the end 
								displayName[dnl+1] = '\0';
							}

							int toIndex = ListView_GetItemCount(pathWnd);
							LVITEM LvSetItem;
							memset(&LvSetItem,0,sizeof(LvSetItem)); // Reset Item Struct
							LvSetItem.mask=LVIF_TEXT;   // Text Style with param index number
							LvSetItem.cchTextMax = MAX_PATH; // Max size of test
							LvSetItem.iItem = toIndex;
							LvSetItem.pszText = displayName;

							ListView_InsertItem(pathWnd, &LvSetItem);
						}
						pMalloc->Free(folders);
						pMalloc->Release();
					}
					break;
				case IDC_TRP_DELETE:
					{
						HWND pathWnd = GetDlgItem(hWnd, IDC_TRP_PATHS); 
						INT ni = ListView_GetSelectionMark( pathWnd );
						while( ni >= 0 )
						{
							ListView_DeleteItem(pathWnd, ni); 
							ni = ListView_GetNextItem( pathWnd, -1, LVNI_SELECTED);
						}
					}	
					break;
			}
			break;
		
		default:
			return FALSE;
	}
	return TRUE;
}	

void hctRemoveTexturePathsFilter::updateOptions()
{
	if (m_optionsDialog)
	{
		char tBuf[MAX_PATH];
		LVITEM LvItem;
		memset(&LvItem,0,sizeof(LvItem)); 
		LvItem.mask=LVIF_TEXT;  
		LvItem.cchTextMax = MAX_PATH; 
		LvItem.pszText = tBuf;
		LvItem.iSubItem = 0;
		HWND pathWnd = GetDlgItem(m_optionsDialog, IDC_TRP_PATHS); 
		int ni = ListView_GetItemCount(pathWnd);
		m_paths = "";
		for (int i=0; i < ni; ++i)
		{
			LvItem.iItem = i;
			ListView_GetItem(pathWnd, &LvItem);

			const char* path = (const char*)( LvItem.pszText ); // not TCHAR friendly..
			if (i > 0) m_paths += ";";
			m_paths += path;
		}
	}
}
	
void hctRemoveTexturePathsFilter::hideOptions()
{
	updateOptions();
	if (m_optionsDialog)
		DestroyWindow(m_optionsDialog);
	m_optionsDialog = NULL;
}

HWND hctRemoveTexturePathsFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
		hideOptions();

	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_TPR_DIALOG),
		owner, hkFilterTextureRemovePathsDialogProc, (LPARAM)this );
	
	return m_optionsDialog;
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
