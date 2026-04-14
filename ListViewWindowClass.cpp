// ListViewWindowClass.cpp

#include "ListViewWindowClass.h"

ListViewWindow::ListViewWindow()
{
	// Initialise global variables
	m_nColumnCount = 0;

} // End of function ListViewWindow::ListViewWindow

ListViewWindow::~ListViewWindow()
{
} // End of function ListViewWindow::~ListViewWindow

int ListViewWindow::AddColumn( LPCTSTR lpszColumnTitle, int nColumnWidth )
{
	int nResult = 0;

	LVCOLUMN lvColumn;

	// Clear list view column structure
	ZeroMemory( &lvColumn, sizeof( lvColumn ) );

	// Initialise list view column structure
	lvColumn.mask		= ( LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM );
	lvColumn.cx			= nColumnWidth;
	lvColumn.pszText	= ( LPTSTR )lpszColumnTitle;

	// Add column to list view window
	nResult = ::SendMessage( m_hWnd, LVM_INSERTCOLUMN, ( WPARAM )m_nColumnCount, ( LPARAM )&lvColumn );

	// Ensure that column was added to list view window
	if( nResult >= 0 )
	{
		// Successfully added column to list view window

		// Update column count
		m_nColumnCount ++;

	} // End of successfully added column to list view window

	return nResult;

} // End of function ListViewWindow::AddColumn

int ListViewWindow::AddItem( LPCTSTR lpszItemText, DWORD dwTextMax )
{
	int nResult = 0;

	LVITEM lvItem;
	int nItemCount;

	// Count items on list view window
	nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= dwTextMax;
	lvItem.iItem		= nItemCount;
	lvItem.iSubItem		= 0;
	lvItem.pszText		= ( LPTSTR )lpszItemText;

	// Add item to list view window
	nResult = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )&lvItem );

	return nResult;

} // End of function ListViewWindow::AddItem

int ListViewWindow::AutoSizeAllColumns()
{
	int nResult = 0;

	int nWhichColumn;

	// Loop through all columns
	for( nWhichColumn = 0; nWhichColumn < m_nColumnCount; nWhichColumn ++ )
	{
		// Auto-size current column
		if( ::SendMessage( m_hWnd, LVM_SETCOLUMNWIDTH, ( WPARAM )nWhichColumn, ( LPARAM )LVSCW_AUTOSIZE_USEHEADER ) )
		{
			// Successfully auto-sized current column

			// Update return value
			nResult ++;

		} // End of successfully auto-sized current column

	}; // End of loop through all columns

	return nResult;

} // End of function ListViewWindow::AutoSizeAllColumns

BOOL ListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create list view window
	if( Window::Create( LIST_VIEW_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
	{
		// Successfully created list view window

		// Set extended list view window style
		::SendMessage( m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, ( WPARAM )0, ( LPARAM )dwExStyle );

		// Update return value
		bResult = TRUE;

	} // End of successfully created list view window

	return bResult;

} // End of function ListViewWindow::Create

BOOL ListViewWindow::GetItemText( int nWhichItem, int nWhichSubItem, LPTSTR lpszItemText, DWORD dwTextMax )
{
	BOOL bResult = FALSE;

	LVITEM lvItem;

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= dwTextMax;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= nWhichSubItem;
	lvItem.pszText		= lpszItemText;

	// Add item to list view window
	bResult = ::SendMessage( m_hWnd, LVM_GETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem );

	return bResult;

} // End of function ListViewWindow::SetItemText

LRESULT ListViewWindow::HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ) )
{
	LRESULT lr = 0;

	// Select list view window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A list view window double click notification code
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

		} // End of a list view window double click notification code
		case LBN_SELCHANGE:
		{
			// A list view window selection change notification code
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

		} // End of a list view window selection change notification code
		default:
		{
			// Default list view window notification code

			// Call default procedure
			lr = DefWindowProc( hWndMain, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default list view window notification code

	}; // End of selection for list view window notification code

	return lr;

} // End of function ListViewWindow::HandleCommandMessage

BOOL ListViewWindow::SetItemText( int nWhichItem, int nWhichSubItem, LPCTSTR lpszItemText, DWORD dwTextMax )
{
	BOOL bResult = FALSE;

	LVITEM lvItem;

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= dwTextMax;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= nWhichSubItem;
	lvItem.pszText		= ( LPTSTR )lpszItemText;

	// Add item to list view window
	bResult = ::SendMessage( m_hWnd, LVM_SETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem );

	return bResult;

} // End of function ListViewWindow::SetItemText

/*
ListViewWindow::
{
} // End of function ListViewWindow::
*/
