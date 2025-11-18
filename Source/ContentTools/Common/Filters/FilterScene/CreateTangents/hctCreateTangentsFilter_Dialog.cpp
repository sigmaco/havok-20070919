/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/CreateTangents/hctCreateTangentsFilter.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Skin/hkxSkinBinding.h>

extern HINSTANCE hInstance;

struct __MyDlgInfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT, __MyDlgInfo);
	const hkRootLevelContainer* m_originalContents;
	hctCreateTangentsFilter* m_filter;
};

hkxNode* _findFirstNodeRef( hkxNode* n, void* obj )
{
	if (n)
	{
		if (n->m_object.m_object && (n->m_object.m_object == obj) )
		{
			return n;
		}

		// Detect meshes referenced through a skin binding
		if (n->m_object.m_object && n->m_object.m_class && (hkString::strCmp(n->m_object.m_class->getName(), "hkxSkinBinding")==0) )
		{
			hkxSkinBinding* skinBinding = (hkxSkinBinding*) n->m_object.m_object;
			if (obj==skinBinding->m_mesh)
			{
				return n;
			}
		}

		for (int i=0; i < n->m_numChildren; ++i)
		{
			hkxNode* v = _findFirstNodeRef( n->m_children[i], obj );
			if (v) return v;
		}
	}
	return HK_NULL;
}

// Tree view manager implementation
class _hkFilterTexturesTreeViewManager : public hctTreeViewManager
{
	public:

		_hkFilterTexturesTreeViewManager( const hkVariant* root, const hctFilterClassRegistry* reg ) : hctTreeViewManager( root, reg ) {}

		/*virtual*/ bool isViewable( const hkClass& klass )
		{
			if( hkString::strCmp( klass.getName(), hkxNodeClass.getName() ) == 0 ) return true;
			if( hkString::strCmp( klass.getName(), hkxMeshClass.getName() ) == 0 ) return true;
			if( hkString::strCmp( klass.getName(), hkxSkinBindingClass.getName() ) == 0 ) return true;
			return false;
		}

		/*virtual*/ bool isSelectable( const hkClass& klass )
		{
			if( hkString::strCmp( klass.getName(), hkxMeshClass.getName() ) == 0 ) return true;
			return false;
		}
};

static BOOL CALLBACK hkFilterTexturesDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{	
	switch(message) 
	{
	case WM_INITDIALOG:
		{	
			__MyDlgInfo* data = (__MyDlgInfo*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later

			// Fill in the list box of forced hkNode names
			HWND nodeWnd = GetDlgItem(hWnd, IDC_MESH_LIST);
			ListView_SetExtendedListViewStyle(nodeWnd, LVS_EX_FULLROWSELECT); // Set style

			// Text item
			
			LVITEM LvItem;
			memset(&LvItem,0,sizeof(LvItem)); // Reset Item Struct
			LvItem.mask=LVIF_TEXT;   // Text Style
			LvItem.cchTextMax = 260; // Max size of test
			for (int fni=0; fni < data->m_filter->m_meshList.getSize(); ++fni)
			{
				LvItem.iItem = fni; 
				LvItem.pszText = const_cast<TCHAR*>( TEXT( data->m_filter->m_meshList[fni].cString() ) );
				ListView_InsertItem(nodeWnd, &LvItem);
			}		

			CheckDlgButton(hWnd, IDC_CB_SplitVertices, data->m_filter->m_splitVertices);

		}
		break;
	
	case WM_NOTIFY: 
	{
		int idCtrl = (int)wParam; 
		LPNMHDR pnmh = (LPNMHDR) lParam; 
		HWND nodeWnd = GetDlgItem(hWnd, IDC_MESH_LIST);

		switch (idCtrl)
		{
			case IDC_MESH_LIST: // list of nodes
			{
				switch (pnmh->code)
				{
					case LVN_KEYDOWN:
					{
						LPNMLVKEYDOWN lpnmc = (LPNMLVKEYDOWN) lParam;
						if (VK_DELETE == lpnmc->wVKey)
						{
							INT ni = ListView_GetSelectionMark( nodeWnd );
							while( ni >= 0 )
							{
								ListView_DeleteItem(nodeWnd, ni); 
								ni = ListView_GetNextItem( nodeWnd, -1, LVNI_SELECTED);
							}
						}
						break;
					}
					case NM_CLICK:
					{
						SetFocus( nodeWnd);
						return FALSE;
					}
				}
			}
			break;
		}
		break;
	}

	case WM_COMMAND: 
		
		switch ( LOWORD(wParam) ) 
		{
			case IDC_ADD_MESH_FROM_SCENE:
			{
				__MyDlgInfo* data = reinterpret_cast<__MyDlgInfo*>( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA) ); 
				
				// Require a scene root
				hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data->m_originalContents->findObjectByType( hkxSceneClass.getName() ) );
				if( !scenePtr || !scenePtr->m_rootNode )
				{
					break;
				}
				
				hkVariant rootNodeVar;
				rootNodeVar.m_object = (void*)scenePtr->m_rootNode;
				rootNodeVar.m_class = &hkxNodeClass;
				
				// Bring up a selection dialog, using our tree manager
				hkVariant selected;
				_hkFilterTexturesTreeViewManager tvManager( &rootNodeVar, HK_NULL );
				if( !data->m_filter->getFilterManager()->selectObjectFromTree( hWnd, "Select Mesh", &tvManager, selected ) )
				{
					break;	// cancelled
				}
				HK_ASSERT( 0x0, hkString::strCmp( selected.m_class->getName(), hkxMeshClass.getName() ) == 0 );
				
				// Update mesh list, using the node name that first references the selected mesh
				hkxNode* node = _findFirstNodeRef( scenePtr->m_rootNode, selected.m_object );
				if (node && node->m_name && (hkString::strLen( node->m_name ) > 0) )
				{
					HWND nodeWnd = GetDlgItem(hWnd, IDC_MESH_LIST);
					LVITEM LvItem;
					LvItem.mask = LVIF_TEXT;   // Text Style
					LvItem.cchTextMax = 260; // Max size of test
					int numItems = ListView_GetItemCount( nodeWnd );
					LvItem.iItem = numItems;
					LvItem.iSubItem = 0;
					LvItem.pszText = const_cast<TCHAR*>( TEXT( node->m_name ) );
					ListView_InsertItem( nodeWnd, &LvItem);
				}
			}
			break;
		}
		break;

	case WM_DESTROY:
		{
			__MyDlgInfo* data = reinterpret_cast<__MyDlgInfo*>( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA) ); 
			delete data; // delete the info ptr we are using.

			SetWindowLongPtr(hWnd, GWLP_USERDATA, 0); // To avoid errors

			break;
		}

	default:
		return FALSE;
	}
	return TRUE;
}	


void hctCreateTangentsFilter::updateOptions()
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
		HWND nodeWnd = GetDlgItem(m_optionsDialog, IDC_MESH_LIST); 
		int ni = ListView_GetItemCount(nodeWnd);
		m_meshList.setSize(ni);
		for (int i=0; i < ni; ++i)
		{
			LvItem.iItem = i;
			ListView_GetItem(nodeWnd, &LvItem);
			m_meshList[i] = (const char*)( LvItem.pszText ); // not TCHAR friendly..
		}

		m_splitVertices = IsDlgButtonChecked(m_optionsDialog, IDC_CB_SplitVertices) != FALSE;
	}
}
	
void hctCreateTangentsFilter::hideOptions()
{
	updateOptions();
	if (m_optionsDialog)
		DestroyWindow(m_optionsDialog);
	m_optionsDialog = NULL;
}

HWND hctCreateTangentsFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
		hideOptions();

	m_optionsDialog = HK_NULL;

	__MyDlgInfo* info = new __MyDlgInfo; // newd as it is a modless dlg. Will be deleted on destroy.
	info->m_originalContents = getFilterManager()->getOriginalContents();
	info->m_filter = this;
	
	// Global Options
	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_TANGENT_OPTIONS),
		owner, hkFilterTexturesDialogProc, (LPARAM) info);

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
