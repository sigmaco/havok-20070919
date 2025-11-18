/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterPhysics/hctFilterPhysics.h>

#include <ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyFilter.h>

extern HINSTANCE hInstance;

BOOL CALLBACK _optimizeShapeHierarchyDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{	
	// We store a pointer to the filter associated with this dialog using Get/SetWindowLongPtr() 
	hctOptimizeShapeHierarchyFilter* filter = reinterpret_cast<hctOptimizeShapeHierarchyFilter*> ( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA)) ; 

	switch(message) 
	{
		case WM_INITDIALOG:
		{	
			filter = (hctOptimizeShapeHierarchyFilter*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later

			filter->m_optionsDialog = hWnd;

			filter->setControlsFromData();

			return TRUE; // did handle it
		}

		case WM_COMMAND: // UI Changes
			{
				filter->enableControls();
				break;
			}
	}
	return FALSE; //didn't handle it
}	



void hctOptimizeShapeHierarchyFilter::setDataFromControls()
{
	// Ensure the options we store match the options shown in the UI
	if (!m_optionsDialog) return;

	// Share shapes stuff
	{
		m_options.m_shareShapes = IsDlgButtonChecked(m_optionsDialog, IDC_CB_Share) == TRUE;		
		m_options.m_permuteDetect = IsDlgButtonChecked(m_optionsDialog, IDC_CB_Permute) == TRUE;

		TCHAR text[256];
		GetWindowText(GetDlgItem(m_optionsDialog, IDC_ED_TOLERANCE), text, 256);
		m_options.m_shareTolerance = (float)atof(text);

	}

	// Collapse transforms stuff
	{
		m_options.m_collapseTransforms = IsDlgButtonChecked(m_optionsDialog, IDC_CB_CollapseTransforms) == TRUE;

		m_options.m_collapseBehaviourType = hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_ALWAYS;

		if (IsDlgButtonChecked(m_optionsDialog, IDC_RB_AlwaysCollapse))
		{
			m_options.m_collapseBehaviourType = hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_ALWAYS;
		}
		else if (IsDlgButtonChecked(m_optionsDialog, IDC_RB_NeverCollapse))
		{
			m_options.m_collapseBehaviourType = hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_NEVER;			
		}
		else if (IsDlgButtonChecked(m_optionsDialog, IDC_RB_CollapseIfLessThan))
		{
			m_options.m_collapseBehaviourType = hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_THRESHOLD;			
		}

		TCHAR text[256];
		GetWindowText(GetDlgItem(m_optionsDialog, IDC_ED_THRESHOLDNUM), text, 256);
		m_options.m_collapseThreshold = atoi(text);

		m_options.m_propagate = IsDlgButtonChecked(m_optionsDialog, IDC_CB_Propagate) == TRUE;

	}	
}

void hctOptimizeShapeHierarchyFilter::setControlsFromData()
{
	if (!m_optionsDialog) return;


	// Share Shapes stuff
	{
		// Sharing behaviour
		CheckDlgButton(m_optionsDialog, IDC_CB_Share, m_options.m_shareShapes);
		CheckDlgButton(m_optionsDialog, IDC_CB_Permute, m_options.m_permuteDetect);

		// "tolerance" edit box
		hkString s;
		s.printf("%f", m_options.m_shareTolerance);
		SetDlgItemText(m_optionsDialog, IDC_ED_TOLERANCE, s.cString());

	}

	// Collapse transforms stuff
	{
		// Collapse behaviour
		CheckDlgButton(m_optionsDialog, IDC_CB_CollapseTransforms, m_options.m_collapseTransforms);
		// "threshold" edit box


		const int firstRB = IDC_RB_AlwaysCollapse;
		const int lastRB = IDC_RB_CollapseIfLessThan;
		BOOL res;
		switch (m_options.m_collapseBehaviourType)
		{
			case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_ALWAYS:
				res =CheckRadioButton(m_optionsDialog, firstRB, lastRB, IDC_RB_AlwaysCollapse);
				break;
			case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_NEVER:
				res =CheckRadioButton(m_optionsDialog, firstRB, lastRB, IDC_RB_NeverCollapse);
				break;
			case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_THRESHOLD:
				res = CheckRadioButton(m_optionsDialog, firstRB, lastRB, IDC_RB_CollapseIfLessThan);
				break;
		}

		hkString s;
		s.printf("%d", m_options.m_collapseThreshold);
		SetDlgItemText(m_optionsDialog, IDC_ED_THRESHOLDNUM, s.cString());

		CheckDlgButton(m_optionsDialog, IDC_CB_Propagate, m_options.m_propagate);		
	}

	enableControls();
}

void hctOptimizeShapeHierarchyFilter::enableControls()
{
	const BOOL shareEnabled = IsDlgButtonChecked(m_optionsDialog, IDC_CB_Share);
	{
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_LAB_Tolerance), shareEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_ED_TOLERANCE), shareEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_CB_Permute), shareEnabled);
	}

	const BOOL collapseEnabled = IsDlgButtonChecked(m_optionsDialog, IDC_CB_CollapseTransforms);
	const BOOL thresholdEnabled = IsDlgButtonChecked(m_optionsDialog,IDC_RB_CollapseIfLessThan);
	{
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_GB_SharedShapes), collapseEnabled);

		EnableWindow(GetDlgItem(m_optionsDialog, IDC_RB_AlwaysCollapse), collapseEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_RB_NeverCollapse), collapseEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_RB_CollapseIfLessThan), collapseEnabled);

		EnableWindow(GetDlgItem(m_optionsDialog, IDC_ED_THRESHOLDNUM), collapseEnabled && thresholdEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_CB_Propagate), collapseEnabled);
		EnableWindow(GetDlgItem(m_optionsDialog, IDC_LAB_References), collapseEnabled);
	}

}


HWND hctOptimizeShapeHierarchyFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
	{
		hideOptions();
	}

	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_OPTIMIZE_SHAPE_DIALOG),
						owner, _optimizeShapeHierarchyDialogProc, (LPARAM) this );

	return m_optionsDialog;
}

void hctOptimizeShapeHierarchyFilter::hideOptions()
{
	// Update any changes before we close UI
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
