/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <ContentTools/Common/Filters/FilterScene/ConvertTexturesToPng/hctConvertTexturesToPNGFilter.h>

extern HINSTANCE hInstance;

BOOL CALLBACK hkFilterTexturesToPNGDialogProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) 
{	
	hctConvertTexturesToPNGFilter* filter = reinterpret_cast<hctConvertTexturesToPNGFilter*>( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA)) ; 

	switch( message ) 
	{
		case WM_INITDIALOG:
		{	
			filter = (hctConvertTexturesToPNGFilter*)lParam;
			SetWindowLongPtr( hWnd, GWLP_USERDATA, (LONG)lParam ); // so that it can be retrieved later

			// Set the check boxes
			CheckDlgButton( hWnd, IDC_RESIZE_ENABLE, filter->m_options.m_enable );
			EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_U_VALUE ), filter->m_options.m_enable );
			EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_V_VALUE ), filter->m_options.m_enable );
			
			if( filter->m_options.m_u == 0 )
			{
				SetDlgItemText( hWnd, IDC_RESIZE_U_VALUE, "0" );
				SetDlgItemText( hWnd, IDC_RESIZE_V_VALUE, "0" );
			}

			else
			{
				SetDlgItemInt( hWnd, IDC_RESIZE_U_VALUE, filter->m_options.m_u, true );
				SetDlgItemInt( hWnd, IDC_RESIZE_V_VALUE, filter->m_options.m_v, true );
			}

			return TRUE; // did handle it
		}

		case WM_COMMAND: // UI Changes
		{
			switch ( LOWORD( wParam ) ) 
			{
				case IDC_RESIZE_ENABLE:
				{
					if( IsDlgButtonChecked( hWnd, IDC_RESIZE_ENABLE ) == TRUE )
					{
						filter->m_options.m_enable = true;

						SetDlgItemInt( hWnd, IDC_RESIZE_U_VALUE, filter->m_options.m_u, true );
						EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_U_VALUE ), TRUE);

						SetDlgItemInt( hWnd, IDC_RESIZE_V_VALUE, filter->m_options.m_v, true );
						EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_V_VALUE ), TRUE );
					}

					else
					{
						filter->m_options.m_enable = false;

						EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_U_VALUE ), FALSE );
						EnableWindow( GetDlgItem( hWnd,IDC_RESIZE_V_VALUE ), FALSE );
					}

					break;
				}

			}
		}

		default:
		{
			return FALSE;	//didn't handle it / didn't do much with it
		}

	}
}	

HWND hctConvertTexturesToPNGFilter::showOptions( HWND owner)
{
	if( m_optionsDialog )
	{
		hideOptions();
	}
	
	m_optionsDialog = CreateDialogParam( hInstance, MAKEINTRESOURCE( IDD_TEXTURE_RESIZE ),
		owner, hkFilterTexturesToPNGDialogProc, (LPARAM) this );

	return m_optionsDialog;
}

void hctConvertTexturesToPNGFilter::updateOptions()
{
	if( m_optionsDialog )
	{
		if( IsDlgButtonChecked(m_optionsDialog, IDC_RESIZE_ENABLE) == TRUE )
		{
			TCHAR buffer[20];

			GetDlgItemText( m_optionsDialog, IDC_RESIZE_U_VALUE, buffer, 15 );
			m_options.m_u = static_cast<hkInt16>( atoi( buffer ) );
			if( m_options.m_u < 0 )
			{
				m_options.m_u = 1;
				SetDlgItemText( m_optionsDialog, IDC_RESIZE_U_VALUE, "1" );
			}

			GetDlgItemText( m_optionsDialog, IDC_RESIZE_V_VALUE, buffer, 15 );
			m_options.m_v = static_cast<hkInt16>( atoi( buffer ) );
			if( m_options.m_v < 0 )
			{
				m_options.m_v = 1;
				SetDlgItemText( m_optionsDialog, IDC_RESIZE_V_VALUE, "1" );
			}
		}
	}
}

void hctConvertTexturesToPNGFilter::hideOptions()
{
	updateOptions();

	if( m_optionsDialog )
	{
		DestroyWindow( m_optionsDialog );
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
