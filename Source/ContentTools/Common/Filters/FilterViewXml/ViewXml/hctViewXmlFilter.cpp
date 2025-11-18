/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterViewXml/hctFilterViewXml.h>
#include <ContentTools/Common/Filters/FilterViewXml/ViewXml/hctViewXmlFilter.h>

#include <ContentTools/Common/SceneExport/Utils/hctSceneExportUtils.h>
#include <Common/Serialize/Serialize/Xml/hkXmlObjectWriter.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>
#include <tchar.h>
#include <richedit.h>

#include <Common/SceneData/Environment/hkxEnvironment.h>

hctViewXmlFilterDesc g_viewXmlDesc;
extern HINSTANCE hInstance;


/// Simply returns the address of a pointer as a string
struct ViewXmlNameFromAddress : public hkXmlObjectWriter::NameFromAddress
{
	/*virtual*/ int nameFromAddress( const void* addr, char* buf, int bufSize )
	{
		return hkString::snprintf(buf, bufSize, "0x%x", addr);
	}
};


hctViewXmlFilter::hctViewXmlFilter(const hctFilterManagerInterface* owner)
:	hctModelessFilter (owner), m_closeRequested(false), m_optionsDialog (NULL)
{
	m_options.m_executeModally = false;
}

hctViewXmlFilter::~hctViewXmlFilter()
{
}

/*virtual*/ hctModelessFilterDescriptor& hctViewXmlFilter::getDescriptor() const
{
	return g_viewXmlDesc;
}

/*virtual*/ void hctViewXmlFilter::tryToClose()
{
	m_closeRequested = true;
}

// This filter is very fast closing down so we report we are never "closing down"
/*virtual*/ bool hctViewXmlFilter::isClosingDown () const
{
	return false;
}

/*virtual*/ bool hctViewXmlFilter::behaveAsModal () const
{
	return m_options.m_executeModally;
}

struct _DialogData
{
	hctTreeViewManager* m_treeViewManager;
	hctViewXmlFilter* m_filter;
	hkRootLevelContainer* m_contents;
};


BOOL CALLBACK TextViewDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	_DialogData* data = reinterpret_cast<_DialogData*>( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA) );

	hctTreeViewManager* tvManager = data ? data->m_treeViewManager : NULL;
	
	// Mouse tracking
	static bool overSplitter = false;
	static bool capturing = false;
	static float splitterPos = 0.33f;
	static HCURSOR arrowCursor = LoadCursor( NULL, IDC_SIZEWE );
    
	// Close down if the users asked us to do so
	if (data && data->m_filter->m_closeRequested)
	{
		EndDialog(hWnd, 0);
		return TRUE;
	}

	switch(message)
	{
	case WM_INITDIALOG:
		{
			// Set the info ptr from lParam
			data = (_DialogData*) lParam;
			tvManager = data->m_treeViewManager;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later
			
			// Set window icon
			SendMessage( hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon( hInstance, MAKEINTRESOURCE(IDI_HAVOKLOGO) ) );
			
			// Set up the tree view
			HWND treeWnd = GetDlgItem(hWnd, IDC_SCENE_TREE);

			TreeView_SetBkColor( treeWnd, RGB(255,255,255) );			
			HIMAGELIST hTreeImageList = ImageList_LoadImage( hInstance, MAKEINTRESOURCE(IDB_SCENENODES), 16, 1, RGB(255,255,255), IMAGE_BITMAP, LR_CREATEDIBSECTION );
			TreeView_SetImageList( treeWnd, hTreeImageList, TVSIL_NORMAL /*TVSIL_STATE*/);

			tvManager->init( treeWnd );

			hkxEnvironment* env = (hkxEnvironment*) data->m_contents->findObjectByType("hkxEnvironment");
			if (env)
			{
				const char* config = env->getVariableValue("configuration");
				const char* slot = env->getVariableValue("slot");

				// Set the title
				hkString windowTitle = "View XML";
				if (config && slot)
				{

					windowTitle.printf("View XML : Configuration : %s ; Slot %s", config, slot);

				}
				SetWindowText(hWnd, windowTitle.cString());
			}

		}

		// FALL THROUGH to simulate resize event
	
	case WM_SIZE:
		{
			// Read dialog dimensions, ensure a minimum limit
			RECT dialogRect;
			GetClientRect( hWnd, (LPRECT)&dialogRect );
			
			// Calculate size of the two controls (proportions)
			const int margin = 10;
			const int butWidth = 80;
			const int butHeight = 30;

			const int usableWidth = dialogRect.right - (3 * margin); // margins and middle space
			const int treeWidth = int( splitterPos * usableWidth );
			const int treeHeight = dialogRect.bottom - (3 * margin) - butHeight; // margin + margin + maring + button
			const int treePosX = margin;
			const int treePosY = margin;

			const int textWidth = int( ( 1.0f - splitterPos ) * usableWidth );
			const int textHeight = dialogRect.bottom - (2 * margin) ;
			const int textPosX = margin + treeWidth + margin;
			const int textPosY = margin;

			const int butPosX = margin + (treeWidth / 2) - (butWidth / 2); // middle of tree control
			const int butPosY = margin + treeHeight + margin;

			// Resize each control in turn
			{
				// TREE
				HWND hwndTree = GetDlgItem( hWnd, IDC_SCENE_TREE );
				RECT treeRect;
				GetClientRect( hwndTree, (LPRECT)&treeRect );
				SetWindowPos( hwndTree, NULL, treePosX, treePosY, treeWidth, treeHeight, SWP_NOZORDER);
			}

			{
				// BUTTON
				HWND hwndButton = GetDlgItem( hWnd, IDOK );
				RECT buttonRect;
				GetClientRect( hwndButton, (LPRECT)&buttonRect );
				SetWindowPos( hwndButton, NULL, butPosX, butPosY, butWidth, butHeight, SWP_NOZORDER);
			}

			{
				// TEXT
				HWND hwndText = GetDlgItem( hWnd, IDC_XML_TEXT );
				RECT textRect;
				GetClientRect( hwndText, (LPRECT)&textRect );
				SetWindowPos( hwndText, NULL, textPosX, textPosY, textWidth, textHeight, SWP_NOZORDER);
			}

			SetForegroundWindow(hWnd);
			
			return TRUE; // TRUE if handled
		}
		break;

	case WM_MOUSEMOVE:
		{
			// Check if we are between the tree view and the xml view
			POINT p; GetCursorPos( &p );
			RECT treeViewRect;	GetWindowRect( GetDlgItem( hWnd, IDC_SCENE_TREE ), &treeViewRect );
			RECT xmlViewRect;	GetWindowRect( GetDlgItem( hWnd, IDC_XML_TEXT ), &xmlViewRect );
			
			overSplitter = ( p.x > treeViewRect.right && p.x < xmlViewRect.left &&
							p.y > treeViewRect.top && p.y > xmlViewRect.top &&
							p.y < treeViewRect.bottom && p.y < xmlViewRect.bottom );
			
			if( overSplitter || capturing )
			{
				SetCursor( arrowCursor );
			}
			
			if( capturing )
			{
				// Update splitter pos
				POINT p;		GetCursorPos( &p );
				RECT wndRect;	GetWindowRect( hWnd, &wndRect );
				splitterPos = float( p.x - wndRect.left ) / float( wndRect.right - wndRect.left );
				
				if( splitterPos < 0.2f )
				{
					splitterPos = 0.2f;
				}
				else if( splitterPos > 0.9f )
				{
					splitterPos = 0.9f;
				}
				
				// simulate resize
				TextViewDialogProc( hWnd, WM_SIZE, NULL, NULL );
			}
		}
		break;
	
	case WM_LBUTTONDOWN:
		{
			if( overSplitter )
			{
				SetCapture( hWnd );
				capturing = true;
			}
		}
		break;
	
	case WM_LBUTTONUP:
		{
			if( capturing )
			{
				ReleaseCapture();
				capturing = false;
			}
		}
		break;
	
	case WM_COMMAND:
		switch ( LOWORD(wParam) ) 
		{
		case IDCANCEL:
		case IDOK:
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;

	case WM_NOTIFY:
		{
			int idCtrl = (int)wParam; 
			LPNMHDR pnmh = (LPNMHDR) lParam; 

			switch (idCtrl)
			{
				case IDC_SCENE_TREE: // Tree View of the scene
				{
					if (pnmh->code == TVN_SELCHANGED)
					{
						hkVariant var;
						if( tvManager->getSelectedVariant( var ) )
						{
							hkString str;
							str.printf("<!-- %s @ 0x%x -->\n", var.m_class->getName(), var.m_object );
							
							hkArray<char> buf;
							hkArrayStreamWriter asw(&buf, hkArrayStreamWriter::ARRAY_BORROW);
							ViewXmlNameFromAddress namer;
							hkXmlObjectWriter xml(namer);
							xml.writeObjectWithElement(&asw, var.m_object, *(var.m_class), HK_NULL);
							str += buf.begin();
							
							SetWindowText( GetDlgItem(hWnd, IDC_XML_TEXT), str.cString() );
						}
					}
					else
					{
						return tvManager->handleNotification( pnmh );
					}
				}
				break;
			}
		}

	}

	return FALSE;
}


void hctViewXmlFilter::modalProcess ( hkRootLevelContainer& data )
{	
	// Prepare a tree view manager (use the default behaviour)
	hkVariant rootVar;
	rootVar.m_object = (void*)&data;
	rootVar.m_class = &hkRootLevelContainerClass;
	hctTreeViewManager tvManager( &rootVar, &m_filterManager->getFilterClassRegistry() );
	
	_DialogData dialogData;
	dialogData.m_treeViewManager = &tvManager;
	dialogData.m_filter = this;
	dialogData.m_contents = &data;

	// When executing modally, we want the dialog parented to the filter manager, otherwise we want it parented to the main application
	HWND owner;
	if (m_options.m_executeModally)
	{
		owner = m_filterManager->getMainWindowHandle();
	}
	else
	{
		owner = m_filterManager->getOwnerWindowHandle();
	}

	// Bring up the (modal) dialog
	DialogBoxParam( hInstance, MAKEINTRESOURCE(IDD_PREVIEW_XML), owner, TextViewDialogProc, (LPARAM)&dialogData);
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
