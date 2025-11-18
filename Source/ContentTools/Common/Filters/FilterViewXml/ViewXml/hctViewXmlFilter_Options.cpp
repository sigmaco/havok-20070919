/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterViewXml/hctFilterViewXml.h>
#include <ContentTools/Common/Filters/FilterViewXml/ViewXml/hctViewXmlFilter.h>

extern HINSTANCE hInstance;

BOOL CALLBACK _viewXmlOptionsDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{	
	// We store a pointer to the filter associated with this dialog using Get/SetWindowLongPtr() 
	hctViewXmlFilter* filter = reinterpret_cast<hctViewXmlFilter*> ( (hkUlong) GetWindowLongPtr(hWnd,GWLP_USERDATA)) ; 

	switch(message) 
	{
	case WM_INITDIALOG:
		{	
			filter = (hctViewXmlFilter*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)lParam); // so that it can be retrieved later

			CheckDlgButton(hWnd, IDC_CB_ExecuteModally, filter->m_options.m_executeModally);

			return TRUE; // did handle it
		}
	}
	return FALSE; //didn't handle it
}	

void hctViewXmlFilter::updateOptions()
{
	// Ensure the options we store match the options shown in the UI
	if (m_optionsDialog)
	{
		m_options.m_executeModally = IsDlgButtonChecked(m_optionsDialog, IDC_CB_ExecuteModally) == TRUE;
	}
}


HWND hctViewXmlFilter::showOptions(HWND owner)
{
	if (m_optionsDialog)
	{
		hideOptions();
	}

	m_optionsDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_VIEW_XML_DIALOG),
		owner, _viewXmlOptionsDialogProc, (LPARAM) this );

	return m_optionsDialog;
}

void hctViewXmlFilter::hideOptions()
{
	// Update any changes before we close UI
	updateOptions();

	if (m_optionsDialog)
	{
		DestroyWindow(m_optionsDialog);
	}

	m_optionsDialog = NULL;

}

void hctViewXmlFilter::setOptions(const void* optionData, int optionDataSize, unsigned int version ) 
{
	// Get the options from the XML data.
	if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctViewXmlOptionsClass ) == HK_SUCCESS )
	{
		hctViewXmlOptions* options = reinterpret_cast<hctViewXmlOptions*>( m_optionsBuf.begin() );

		m_options.m_executeModally = options->m_executeModally;
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba482b, "The XML for the " << g_viewXmlDesc.getShortName() << " option data could not be loaded." );
		return;
	}
}

int hctViewXmlFilter::getOptionsSize() const
{
	// We write the options to a temporary buffer and return the size of it. The buffer itself will be used
	// later on by getOptions().
	hctFilterUtils::writeOptionsXml( hctViewXmlOptionsClass, &m_options, m_optionsBuf, g_viewXmlDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctViewXmlFilter::getOptions(void* optionData) const
{
	// Get options is always called after getOptionsSize() - so we reuse the temporary buffer we used in getOptionsSize()
	hkString::memCpy( optionData, m_optionsBuf.begin(), m_optionsBuf.getSize() );	
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
