// FileListViewWindowClass.cpp

#include "FileListViewWindowClass.h"

FileListViewWindow::FileListViewWindow()
{
	// Allocate string memory
	m_lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear parent folder path
	m_lpszParentFolderPath [ 0 ] = ( char )NULL;

	// Initialise global variables
	m_nColumnCount = 0;

} // End of function FileListViewWindow::FileListViewWindow

FileListViewWindow::~FileListViewWindow()
{
	// Free string memory
	delete [] m_lpszParentFolderPath;

} // End of function FileListViewWindow::~FileListViewWindow

int FileListViewWindow::AddItem( LPCTSTR lpszItemText, DWORD dwTextMax )
{
	int nResult = 0;

	LVITEM lvItem;
	int nItemCount;
	SHFILEINFO shFileInfo;

	// Allocate string memory
	LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Copy parent folder path into file path
	lstrcpy( lpszItemPath, m_lpszParentFolderPath );

	// Append item text onto file path
	lstrcat( lpszItemPath, lpszItemText );

	// Get file information for item
	SHGetFileInfo( lpszItemPath, 0, &shFileInfo, sizeof( shFileInfo ), ( SHGFI_ICON | SHGFI_SMALLICON ) );

	// Count items on list view window
	nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= ( LVIF_TEXT | LVIF_IMAGE );
	lvItem.cchTextMax	= dwTextMax;
	lvItem.iItem		= nItemCount;
	lvItem.iSubItem		= 0;
	lvItem.pszText		= ( LPTSTR )lpszItemText;
	lvItem.iImage		= shFileInfo.iIcon;

	// Add item to list view window
	nResult = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )&lvItem );

	// Free string memory
	delete [] lpszItemPath;

	return nResult;

} // End of function FileListViewWindow::AddItem

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

BOOL FileListViewWindow::GetItemPath( int nWhichItem, LPTSTR lpszItemPath, DWORD dwTextMax )
{
	BOOL bResult = FALSE;

	LVITEM lvItem;

	// Allocate string memory
	LPTSTR lpszItemName = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= dwTextMax;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= FILE_LIST_VIEW_WINDOW_CLASS_NAME_COLUMN_ID;
	lvItem.pszText		= lpszItemName;

	// Get item name from list view window
	if( ::SendMessage( m_hWnd, LVM_GETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem ) )
	{
		// Successfully got item name from list view window

		// Copy parent folder path into item path
		lstrcpy( lpszItemPath, m_lpszParentFolderPath );

		// Append item name onto item path
		lstrcat( lpszItemPath, lpszItemName );

		// Update return value
		bResult = TRUE;

	} // End of successfully got item name from list view window

	// Free string memory
	return bResult;

} // End of function FileListViewWindow::GetItemPath

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
				LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item path
				if( GetItemPath( lpNmListView->iItem, lpszItemPath ) )
				{
					// Successfully got item path

					// Call selection changed function with item
					( *lpSelectionChangeFunction )( lpszItemPath );

				} // End of successfully got item path

				// Free string memory
				delete [] lpszItemPath;

			} // End of selection has changed to selected

			// Break out of switch
			break;

		} // End of a file list view window item changed notification code
		case NM_DBLCLK:
		{
			// A double click notification code

			// Allocate string memory
			LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get item path
			if( GetItemPath( lpNmListView->iItem, lpszItemPath ) )
			{
				// Successfully got item path

				// Call double click function with item
				( *lpDoubleClickFunction )( lpszItemPath );

			} // End of successfully got item path

			// Free string memory
			delete [] lpszItemPath;

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
	int nResult = -1;

	// Allocate string memory
	LPTSTR lpszCurrentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get current folder path
	if( GetCurrentDirectory( STRING_LENGTH, lpszCurrentFolderPath ) )
	{
		// Successfully got current folder path

		// Populate to current folder
		nResult = Populate( lpszCurrentFolderPath );

	} // End of successfully got current folder path

	// Free string memory
	delete [] lpszCurrentFolderPath;

	return nResult;

} // End of function FileListViewWindow::Populate

int FileListViewWindow::Populate( LPCTSTR lpszParentFolderPath )
{
	int nResult = -1;

	FileFind fileFind;

	// Find first item
	if( fileFind.First( lpszParentFolderPath, ALL_FILES_FILTER ) )
	{
		// Successfully found first item
		int nItem;

		// Allocate string memory
		LPTSTR lpszFileName	= new char[ STRING_LENGTH + sizeof( char ) ];
		LPTSTR lpszModified	= new char[ STRING_LENGTH + sizeof( char ) ];

		// Delete all items from file list view window
		DeleteAllItems();

		// Initialise return value
		nResult = 0;

		// Loop through all items
		do
		{
			// See if found item is a folder
			if( fileFind.IsFolder() )
			{
				// Found item is a folder

				// Ensure that found item is not dots
				if( !( fileFind.IsDots() ) )
				{
					// Found item is not dots

					// Get found item name
					fileFind.GetFileName( lpszFileName );

					// Add found item to list view window
					nItem = AddItem( lpszFileName );

					// Ensure that found item was added to list view window
					if( nItem >= 0 )
					{
						// Successfully added item to list view window

						// Update return value
						nResult ++;

					} // End of successfully added item to list view window

				} // End of found item is not dots

			} // End of found item is a folder
			else
			{
				// Found item is a file

				// Get found item name
				fileFind.GetFileName( lpszFileName );

				// Add found item to list view window
				nItem = AddItem( lpszFileName );

				// Ensure that found item was added to list view window
				if( nItem >= 0 )
				{
					// Successfully added item to list view window

					// Get modified time
					if( fileFind.GetModifiedTime( lpszModified ) )
					{
						// Successfully got modified time

						// Add modified time to list view window
						SetItemText( nItem, FILE_LIST_VIEW_WINDOW_CLASS_MODIFIED_COLUMN_ID, lpszModified );

						// Update return value
						nResult ++;

					} // End of successfully got modified time

				} // End of successfully added item to list view window

			} // End of found item is a file

		} while( fileFind.Next() ); // End of loop through all items

		// Close find file handle
		fileFind.Close( m_lpszParentFolderPath );

		// Auto-size all file list view window columns
		AutoSizeAllColumns();

		// Free string memory
		delete [] lpszFileName;
		delete [] lpszModified;

	} // End of successfully found first item

	return nResult;

} // End of function FileListViewWindow::Populate

HIMAGELIST FileListViewWindow::SetImageList( HIMAGELIST hImageList, int nWhichImageList )
{
	// Set image list
	return ( HIMAGELIST )::SendMessage( m_hWnd, LVM_SETIMAGELIST, ( WPARAM )nWhichImageList, ( LPARAM )hImageList );

} // End of function FileListViewWindow::SetImageList

/*
FileListViewWindow::
{
} // End of function FileListViewWindow::
*/
