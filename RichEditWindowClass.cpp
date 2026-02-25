// RichEditWindowClass.cpp

#include "RichEditWindowClass.h"

RichEditWindow::RichEditWindow()
{
} // End of function RichEditWindow::RichEditWindow

RichEditWindow::~RichEditWindow()
{
} // End of function RichEditWindow::~RichEditWindow

BOOL RichEditWindow::Copy()
{
	BOOL bResult = FALSE;

	DWORD dwStart;
	DWORD dwEnd;

	// Get selection
	::SendMessage( m_hWnd, EM_GETSEL, ( WPARAM )&dwStart, ( LPARAM )&dwEnd );

	// Ensure that some text is selected
	if( dwEnd > dwStart )
	{
		// Some text is selected
		DWORD dwBufferLength;

		// Calculate buffer length
		dwBufferLength = ( ( dwEnd - dwStart ) + sizeof( char ) );

		// Allocate string memory
		LPTSTR lpszSelectedText = new char[ dwBufferLength ];

		// Get selected text
		if( ::SendMessage( m_hWnd, EM_GETSELTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelectedText ) )
		{
			// Successfully got selected text
			Clipboard clipboard;

			// Open clipboard
			if( clipboard.Open() )
			{
				// Successfully opened clipboard

				// Set clipboard text
				bResult = clipboard.SetText( lpszSelectedText );

				// Update return value
				bResult = TRUE;

				// Close clipboard
				clipboard.Close();

			} // End of successfully opened clipboard
			else
			{
				// Unable to open clipboard

				// Display error message
				MessageBox( NULL, CLIPBOARD_CLASS_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to open clipboard

		} // End of successfully got selected text

		// Free string memory
		delete [] lpszSelectedText;

	} // End of some text is selected

	return bResult;

} // End of function RichEditWindow::Copy

BOOL RichEditWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Load rich edit library
	m_hModuleRichEditLibrary = LoadLibrary( RICH_EDIT_WINDOW_LIBRARY_NAME );

	// Ensure that rich edit library was opened
	if( m_hModuleRichEditLibrary )
	{
		// Successfully loaded rich edit library

		// Create rich edit window
		if( Window::Create( RICH_EDIT_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
		{
			// Successfully created rich edit window

			// Update return value
			bResult = TRUE;

		} // End of successfully created rich edit window

	} // End of successfully loaded rich edit library

	return bResult;

} // End of function RichEditWindow::Create

BOOL RichEditWindow::Cut()
{
	BOOL bResult = FALSE;

	// Copy text
	if( Copy() )
	{
		// Successfully copied text

		// Delete selected text
		::SendMessage( m_hWnd, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )NULL );

		// Update return value
		bResult = TRUE;

	} // End of successfully copied text

	return bResult;

} // End of function RichEditWindow::Cut

void RichEditWindow::Delete( BOOL bCanUndo )
{
	// Delete
	::SendMessage( m_hWnd, EM_REPLACESEL, ( WPARAM )bCanUndo, ( LPARAM )NULL );

} // End of function RichEditWindow::Delete

LRESULT RichEditWindow::HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ) )
{
	LRESULT lr = 0;

	// Select rich edit window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A rich edit window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = ::SendMessage( m_hWnd, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( ::SendMessage( m_hWnd, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Call double click function
				( *lpDoubleClickFunction )( lpszSelected );

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a rich edit window double click notification code
		case LBN_SELCHANGE:
		{
			// A rich edit window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = ::SendMessage( m_hWnd, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( ::SendMessage( m_hWnd, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Call selection change function
				( *lpSelectionChangeFunction )( lpszSelected );

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a rich edit window selection change notification code
		default:
		{
			// Default rich edit window notification code

			// Call default procedure
			lr = DefWindowProc( hWndMain, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default rich edit window notification code

	}; // End of selection for rich edit window notification code

	return lr;

} // End of function RichEditWindow::HandleCommandMessage

BOOL RichEditWindow::Paste()
{
	BOOL bResult = FALSE;

	Clipboard clipboard;

	// Open clipboard
	if( clipboard.Open() )
	{
		// Successfully opened clipboard
		DWORD dwClipboardTextLength;

		// Get clipboard text length
		dwClipboardTextLength = clipboard.GetTextLength();

		// Ensure that clipboard is not empty
		if( dwClipboardTextLength > 0 )
		{
			// Clipboard is not empty

			// Allocate string memory
			LPTSTR lpszClipboard = new char[ dwClipboardTextLength + sizeof( char ) ];

			// Get clipboard text
			if( clipboard.GetText( lpszClipboard ) )
			{
				// Successfully got clipboard text

				// Replace selected text
				::SendMessage( m_hWnd, EM_REPLACESEL, ( WPARAM )TRUE, ( LPARAM )lpszClipboard );

				// Update return value
				bResult = TRUE;

			} // End of successfully got clipboard text

			// Free string memory
			delete [] lpszClipboard;

		} // End of clipboard is not empty

		// Close clipboard
		clipboard.Close();

	} // End of successfully opened clipboard
	else
	{
		// Unable to open clipboard

		// Display error message
		MessageBox( NULL, CLIPBOARD_CLASS_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to open clipboard

	return bResult;

} // End of function RichEditWindow::Paste

void RichEditWindow::Select( int nStart, int nEnd )
{
	// Select text
	::SendMessage( m_hWnd, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function RichEditWindow::Select

BOOL RichEditWindow::SetTextMode( int nTextMode )
{
	BOOL bResult = FALSE;

	// Set text mode
	if( ::SendMessage( m_hWnd, EM_SETTEXTMODE, ( WPARAM )nTextMode, ( LPARAM )NULL ) == 0 )
	{
		// Successfully set text mode

		// Update return value
		bResult = TRUE;

	} // End of successfully set text mode

	return bResult;

} // End of function RichEditWindow::SetTextMode

BOOL RichEditWindow::Redo()
{
	// Redo
	return ::SendMessage( m_hWnd, EM_REDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindow::Redo

BOOL RichEditWindow::Undo()
{
	// Undo
	return ::SendMessage( m_hWnd, EM_UNDO, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function RichEditWindow::Undo

/*
RichEditWindow::
{
} // End of function RichEditWindow::
*/
