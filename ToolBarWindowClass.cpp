// ToolBarWindowClass.cpp

#include "ToolBarWindowClass.h"

ToolBarWindow::ToolBarWindow()
{
} // End of function ToolBarWindow::ToolBarWindow

ToolBarWindow::~ToolBarWindow()
{
} // End of function ToolBarWindow::~ToolBarWindow

int ToolBarWindow::AddButton( int nBitmap, int nCommand )
{
	int nResult;

	static int s_nNextButtonID = 0;

	// Clear tool-bar button structure
	ZeroMemory( &( m_tbButtons[ s_nNextButtonID ] ), sizeof( TBBUTTON ) );

	// Initialise tool-bar button structure
	m_tbButtons[ s_nNextButtonID ].iBitmap		= nBitmap;
	m_tbButtons[ s_nNextButtonID ].idCommand	= nCommand;
	m_tbButtons[ s_nNextButtonID ].fsState		= TBSTATE_ENABLED;
	m_tbButtons[ s_nNextButtonID ].fsStyle		= TOOL_BAR_WINDOW_CLASS_STYLES;
	m_tbButtons[ s_nNextButtonID ].dwData		= { 0 };

	// Update return value
	nResult = s_nNextButtonID;

	// Update next button id
	s_nNextButtonID ++;

	return nResult;

} // End of function ToolBarWindow::AddButton

BOOL ToolBarWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create tool-bar window
	if( Window::Create( TOOL_BAR_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
	{
		// Successfully created tool-bar window

		// Create image list
		m_hImageList = ImageList_Create( TOOL_BAR_WINDOW_CLASS_BUTTON_SIZE, TOOL_BAR_WINDOW_CLASS_BUTTON_SIZE, TOOL_BAR_WINDOW_CLASS_FLAGS, TOOL_BAR_WINDOW_CLASS_NUMBER_OF_BUTTONS, TOOL_BAR_WINDOW_CLASS_GROW );

		// Assign image list to tool-bar window
		::SendMessage( m_hWnd, TB_SETIMAGELIST, ( WPARAM )TOOL_BAR_WINDOW_CLASS_IMAGE_LIST_ID, ( LPARAM )m_hImageList );

		// Load button images
		::SendMessage( m_hWnd, TB_LOADIMAGES, ( WPARAM )IDB_STD_SMALL_COLOR, ( LPARAM )HINST_COMMCTRL );

		// Add buttons to tool-bar window
		::SendMessage( m_hWnd, TB_BUTTONSTRUCTSIZE, ( WPARAM )sizeof(TBBUTTON), 0 );
		::SendMessage( m_hWnd, TB_ADDBUTTONS, ( WPARAM )TOOL_BAR_WINDOW_CLASS_NUMBER_OF_BUTTONS, (LPARAM )&m_tbButtons );

		// Resize tool-bar window
		::SendMessage( m_hWnd, TB_AUTOSIZE, ( WPARAM )NULL, ( LPARAM )NULL );

		// Show tool-bar window
		::ShowWindow( m_hWnd,  TRUE);

		// Update return value
		bResult = TRUE;

	} // End of successfully created tool-bar window

	return bResult;

} // End of function ToolBarWindow::Create

BOOL ToolBarWindow::EnableButton( int nCommand, BOOL bEnable )
{
	// Enable button
	return ::SendMessage( m_hWnd, TB_ENABLEBUTTON, ( WPARAM )nCommand, bEnable );

} // End of function ToolBarWindow::EnableButton

/*
ToolBarWindow::
{
} // End of function ToolBarWindow::
*/
