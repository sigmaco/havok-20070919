/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <ContentTools/Common/Filters/FilterScene/SceneTransform/hctSceneTransformFilter.h>

extern HINSTANCE hInstance;

void hkInitPreset(hctSceneTransformOptions& opts)
{
	hkMatrix4& trans = opts.m_matrix;
	
	switch(opts.m_preset)
	{
		case hctSceneTransformOptions::IDENTITY:
		{
			trans.setIdentity();
		}
		break;
		case hctSceneTransformOptions::MIRROR_X:
		{
			trans.setIdentity();
			trans.getColumn(0).set(-1,0,0,0);
		}
		break;
		case hctSceneTransformOptions::MIRROR_Y:
		{
			trans.setIdentity();
			trans.getColumn(1).set(0,-1,0,0);
		}
		break;
		case hctSceneTransformOptions::MIRROR_Z:
		{
			trans.setIdentity();
			trans.getColumn(2).set(0,0,-1,0);
		}
		break;
		case hctSceneTransformOptions::SCALE_FEET_TO_METERS:
		{
			trans.setIdentity();

			const hkReal s = 1.0f / 3.2808399f; 
			trans.getColumn(0).set(s,0,0,0);
			trans.getColumn(1).set(0,s,0,0);
			trans.getColumn(2).set(0,0,s,0);
		}
		break;
		case hctSceneTransformOptions::SCALE_INCHES_TO_METERS:
		{
			trans.setIdentity();

			const hkReal s = 1.0f / 39.3700787f;
			trans.getColumn(0).set(s,0,0,0);
			trans.getColumn(1).set(0,s,0,0);
			trans.getColumn(2).set(0,0,s,0);
		}
		break;
		case hctSceneTransformOptions::SCALE_CMS_TO_METERS:
		{
			trans.setIdentity();

			const hkReal s = 1.0f / 100.0f;
			trans.getColumn(0).set(s,0,0,0);
			trans.getColumn(1).set(0,s,0,0);
			trans.getColumn(2).set(0,0,s,0);
		}
		break;
		default:
			// Custom leaves things unchanged
		break;
	}
}

void hctSceneTransformFilter::setDataFromControls()
{
	// Preset Combo
	{
		HWND hwndCombo = GetDlgItem(m_optionsDialog, IDC_PRESET_COMBO);
		LRESULT ir = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
		m_options.m_preset = hctSceneTransformOptions::Preset(ir);
	}

	// Application
	{
		m_options.m_applyToNodes = IsDlgButtonChecked(m_optionsDialog, IDC_NODE_CHECK) != FALSE;
		m_options.m_applyToBuffers = IsDlgButtonChecked(m_optionsDialog, IDC_BUFFERS_CHECK) != FALSE;
		m_options.m_applyToLights = IsDlgButtonChecked(m_optionsDialog, IDC_LIGHTS_CHECK) != FALSE;
		m_options.m_applyToCameras = IsDlgButtonChecked(m_optionsDialog, IDC_CAMERAS_CHECK) != FALSE;
		m_options.m_flipWinding = IsDlgButtonChecked(m_optionsDialog, IDC_WINDING_CHECK) != FALSE;
	}

	// Matrix
	{
		char val[50];
		for (int i=0; i < 9; i++)
		{
			//int idx = (i/3)*4 + (i%3);
			GetDlgItemText( m_optionsDialog, IDC_EDIT_MAT00 + i, val, 45);
			m_options.m_matrix(i%3, i/3) = hkString::atof(val);
		}
	}

	// Update controls again
	setControlsFromData();
}

void hctSceneTransformFilter::setControlsFromData()
{
	hkInitPreset(m_options);

	m_fillingControls = true;

	// Preset Combo
	{
		HWND hwndCombo = GetDlgItem(m_optionsDialog, IDC_PRESET_COMBO);
		SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM)m_options.m_preset, 0);
	}

	// Application
	{
		CheckDlgButton(m_optionsDialog, IDC_NODE_CHECK, m_options.m_applyToNodes);
		CheckDlgButton(m_optionsDialog, IDC_BUFFERS_CHECK, m_options.m_applyToBuffers);
		CheckDlgButton(m_optionsDialog, IDC_LIGHTS_CHECK, m_options.m_applyToLights);
		CheckDlgButton(m_optionsDialog, IDC_CAMERAS_CHECK, m_options.m_applyToCameras);
		CheckDlgButton(m_optionsDialog, IDC_WINDING_CHECK, m_options.m_flipWinding);
	}


	if (!m_doNotRefreshEdit)
	{
		// Matrix
		{
			for (int i=0; i < 9; i++)
			{
				//int idx = (i/3)*4 + (i%3);
				char val[50];
				hkString::sprintf(val, "%.3f", m_options.m_matrix(i%3, i/3));
				SetDlgItemText( m_optionsDialog, IDC_EDIT_MAT00 + i, val);
			}
		}
	}

	BOOL custom = m_options.m_preset == hctSceneTransformOptions::CUSTOM;

	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT00), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT01), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT02), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT10), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT11), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT12), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT20), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT21), custom);
	EnableWindow(GetDlgItem(m_optionsDialog, IDC_EDIT_MAT22), custom);

	m_fillingControls = false;
}


BOOL CALLBACK hkFilterSceneTransformDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{	
	hctSceneTransformFilter* filter = reinterpret_cast<hctSceneTransformFilter*> ( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA)) ; 

	switch(message) 
	{
		case WM_INITDIALOG:
		{	
			filter = (hctSceneTransformFilter*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later
			filter->m_optionsDialog = hWnd;
			
			// Preset Combo
			{
				const hkClassEnum& presetEnum =  hctSceneTransformOptionsClass.getEnum(0);

				HWND hwndCombo = GetDlgItem(hWnd, IDC_PRESET_COMBO);
				for (int i=0 ; i < presetEnum.getNumItems()-1; i++)
				{
					SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)presetEnum.getItem(i).getName());
				}
			}

			// Init options
			filter->setControlsFromData();

			return TRUE; // did handle it
		}
		case WM_COMMAND: // UI Changes
		{
			// Avoid recursion
			if (!filter->m_fillingControls)
			{
				if ((LOWORD(wParam)>=IDC_EDIT_MAT00) && (LOWORD(wParam)<=IDC_EDIT_MAT22))
				{
					filter->m_doNotRefreshEdit = true;
				}
				filter->setDataFromControls();
				filter->m_doNotRefreshEdit = false;
			}
		}
	}
	return FALSE; //didn't handle it / didn't do much with it
}	

HWND hctSceneTransformFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
		hideOptions();
	
	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_TRANSFORM_DIALOG),
		owner, hkFilterSceneTransformDialogProc, (LPARAM) this );

	return m_optionsDialog;
}


void hctSceneTransformFilter::hideOptions()
{
	setDataFromControls();

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
