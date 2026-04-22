// FileListViewWindowClass.cpp

#include "FileListViewWindowClass.h"

FileListViewWindow::FileListViewWindow()
{
} // End of function FileListViewWindow::FileListViewWindow

FileListViewWindow::~FileListViewWindow()
{
} // End of function FileListViewWindow::~FileListViewWindow

BOOL FileListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create file list view window
	if( ListViewWindow::Create( hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
	{
		// Successfully created file list view window
		LPCTSTR lpszColumnTitles [] = FILE_LIST_VIEW_WINDOW_CLASS_COLUMN_TITLES;
		int nWhichColumn;

		// Loop through all columns
		for( nWhichColumn = 0; nWhichColumn < FILE_LIST_VIEW_WINDOW_CLASS_NUMBER_OF_COLUMNS; nWhichColumn ++ )
		{
			// Add column to file list view window
			AddColumn( lpszColumnTitles[ nWhichColumn ] );

		}; // End of loop through all columns

		// Update return value
		bResult = TRUE;

	} // End of successfully created file list view window

	return bResult;

} // End of function FileListViewWindow::Create

LRESULT FileListViewWindow::HandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), PFNLVCOMPARE pFnLvCompare )
{
	LRESULT lResult = 0;

	LPNMLISTVIEW lpNmListView;

	// Get list view notification message handler
	lpNmListView = ( LPNMLISTVIEW )lParam;

	// Select file list view window notification code
	switch( lpNmListView->hdr.code )
	{
		case LVN_COLUMNCLICK:
		{
			// A column click notify message

			// Sort the list view
			ListView_SortItemsEx( m_hWnd, pFnLvCompare, lpNmListView->iSubItem );

			// Break out of switch
			break;

		} // End of a column click notify message
		case LVN_ITEMCHANGED:
		{
			// A file list view window item changed notification code

			// See if selection has changed to selected
			if( ( lpNmListView->uNewState ^ lpNmListView->uOldState ) & LVIS_SELECTED )
			{
				// Selection has changed to selected

				// Allocate string memory
				LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item text
				if( GetItemText( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemText ) )
				{
					// Successfully got item text

					// Call selection changed function with item
					( *lpSelectionChangeFunction )( lpszItemText );

				} // End of successfully got item text

				// Free string memory
				delete [] lpszItemText;

			} // End of selection has changed to selected

			// Break out of switch
			break;

		} // End of a file list view window item changed notification code
		case NM_DBLCLK:
		{
			// A double click notification code

			// Allocate string memory
			LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get item text
			if( GetItemText( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemText ) )
			{
				// Successfully got item text

				// Call double click function with item
				( *lpDoubleClickFunction )( lpszItemText );

			} // End of successfully got item text

			// Free string memory
			delete [] lpszItemText;

			// Break out of switch
			break;

		} // End of a double click notification code
		default:
		{
			// Default file list view window notification code

			// Call default procedure
			lResult = DefWindowProc( hWndMain, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default file list view window notification code

	}; // End of selection for file list view window notification code

	return lResult;

} // End of function FileListViewWindow::HandleNotifyMessage

int FileListViewWindow::Populate()
{
	int nResult = 0;

	// Delete all items from file list view window
	DeleteAllItems();

	// Auto-size all file list view window columns
	AutoSizeAllColumns();

	// Update result
	nResult = GetItemCount();

	return nResult;

} // End of function FileListViewWindow::Populate

/*
FileListViewWindow::
{
} // End of function FileListViewWindow::
*/
