// StatusBarWindowClass.cpp

#include "StatusBarWindowClass.h"

StatusBarWindow::StatusBarWindow()
{
} // End of function StatusBarWindow::StatusBarWindow

StatusBarWindow::~StatusBarWindow()
{
} // End of function StatusBarWindow::~StatusBarWindow

BOOL StatusBarWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create status bar window
	if( Window::Create( STATUS_BAR_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
	{
		// Successfully created status bar window

		// Update return value
		bResult = TRUE;

	} // End of successfully created status bar window

	return bResult;

} // End of function StatusBarWindow::Create

LRESULT StatusBarWindow::Size()
{
	// Size window
	return ::SendMessage( m_hWnd, WM_SIZE, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function StatusBarWindow::Size

BOOL StatusBarWindow::SetText( LPCTSTR lpszStatusText )
{
	// Set window text
	return ::SendMessage( m_hWnd, SB_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszStatusText );

} // End of function StatusBarWindow::SetText

/*
StatusBarWindow::
{
} // End of function StatusBarWindow::
*/
