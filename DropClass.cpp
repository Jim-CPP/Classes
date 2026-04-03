// DropClass.cpp

#include "DropClass.h"

Drop::Drop()
{
	// Initialise member variables
	ZeroMemory( &m_hDrop, sizeof( m_hDrop ) );

} // End of function Drop::Drop

Drop::~Drop()
{
	// Clear member variables
	ZeroMemory( &m_hDrop, sizeof( m_hDrop ) );

} // End of function Drop::~Drop

Drop& Drop::operator = ( HDROP hDrop )
{
	// Update member variables
	m_hDrop = hDrop;

	return *this;

} // End of function Drop::operator =

BOOL Drop::operator == ( HDROP hDrop )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hDrop == m_hDrop )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Drop::operator ==

BOOL Drop::operator != ( HDROP hDrop )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hDrop != m_hDrop )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Drop::operator !=

Drop::operator HDROP()
{
	return m_hDrop;

} // End of function Drop::operator HDROP()

int Drop::ProcessAllFiles( void( *lpAllDroppedFilesFunction )( LPCTSTR lpszAllDroppedFilePaths ) )
{
	int nResult = 0;

	UINT uFileCount;
	UINT uWhichFile;
	UINT uFileSize;
	LPTSTR lpszTemporary;
	DWORD dwAllDroppedFilesLength = sizeof( char );

	// Allocate string memory
	LPTSTR lpszAllDroppedFilePaths		= new char[ sizeof( char ) ];
	LPTSTR lpszCurrentDroppedFilePath	= new char[ STRING_LENGTH + sizeof( char ) ];

	// Count dropped files
	uFileCount = DragQueryFile( m_hDrop, ( UINT )-1, NULL, 0 );

	// Clear all dropped file paths
	lpszAllDroppedFilePaths[ 0 ] = ( char )NULL;

	// Loop through dropped files
	for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
	{
		// Get size of dropped file
		uFileSize = DragQueryFile( m_hDrop, uWhichFile, NULL, 0 );

		// Ensure that file size is valid
		if( uFileSize != 0 )
		{
			// File size is valid

			// Get current dropped file path
			if( DragQueryFile( m_hDrop, uWhichFile, lpszCurrentDroppedFilePath, ( uFileSize + sizeof( char ) ) ) )
			{
				// Successfully got current dropped file path

				// Allocate temporary memory
				lpszTemporary = new char[ dwAllDroppedFilesLength ];

				// Copy all dropped files into temporary
				lstrcpy( lpszTemporary, lpszAllDroppedFilePaths );

				// Free all dropped files memory
				delete [] lpszAllDroppedFilePaths;

				// Add length of current dropped file path to all dropped files length
				dwAllDroppedFilesLength += lstrlen( lpszCurrentDroppedFilePath );

				// Add length of new line text to all dropped files length
				dwAllDroppedFilesLength += lstrlen( NEW_LINE_TEXT );

				// Re-allocate all dropped files memory
				lpszAllDroppedFilePaths = new char[ dwAllDroppedFilesLength ];

				// Copy temporary string into all dropped files
				lstrcpy( lpszAllDroppedFilePaths, lpszTemporary );

				// Append current dropped file path onto all dropped files
				lstrcat( lpszAllDroppedFilePaths, lpszCurrentDroppedFilePath );

				// Append new line text onto all dropped files
				lstrcat( lpszAllDroppedFilePaths, NEW_LINE_TEXT );

				// Update return value
				nResult ++;

				// Free temporary memory
				delete [] lpszTemporary;

			} // End of successfully got file path

		} // End of file size is valid

	}; // End of loop through dropped files

	// Call dropped files function
	( *lpAllDroppedFilesFunction )( lpszAllDroppedFilePaths );

	return nResult;

} // End of function Drop::ProcessAllFiles()

int Drop::ProcessFiles( BOOL( *lpDropFunction )( LPCTSTR lpszDroppedFilePath ) )
{
	int nResult = 0;

	UINT uFileCount;
	UINT uWhichFile;
	UINT uFileSize;

	// Allocate string memory
	LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

	// Count dropped files
	uFileCount = DragQueryFile( m_hDrop, ( UINT )-1, NULL, 0 );

	// Loop through dropped files
	for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
	{
		// Get size of dropped file
		uFileSize = DragQueryFile( m_hDrop, uWhichFile, NULL, 0 );

		// Ensure that file size is valid
		if( uFileSize != 0 )
		{
			// File size is valid

			// Get file path
			if( DragQueryFile( m_hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
			{
				// Successfully got file path

				// Process file
				if( ( *lpDropFunction )( lpszFilePath ) )
				{
					// Successfully processed files

					// Update return value
					nResult ++;

				} // End of successfully processed files

			} // End of successfully got file path

		} // End of file size is valid

	}; // End of loop through dropped files

	// Free string memory
	delete [] lpszFilePath;

	return nResult;

} // End of function Drop::ProcessFiles

int Drop::ProcessFiles( WPARAM wParam, BOOL( *lpDropFunction )( LPCTSTR lpszDroppedFilePath ) )
{
	int nResult = 0;

	UINT uFileCount;
	UINT uWhichFile;
	UINT uFileSize;

	// Allocate string memory
	LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

	// Get drop handle
	m_hDrop = ( HDROP )wParam;

	// Count dropped files
	uFileCount = DragQueryFile( m_hDrop, ( UINT )-1, NULL, 0 );

	// Loop through dropped files
	for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
	{
		// Get size of dropped file
		uFileSize = DragQueryFile( m_hDrop, uWhichFile, NULL, 0 );

		// Ensure that file size is valid
		if( uFileSize != 0 )
		{
			// File size is valid

			// Get file path
			if( DragQueryFile( m_hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
			{
				// Successfully got file path

				// Process file
				if( ( *lpDropFunction )( lpszFilePath ) )
				{
					// Successfully processed files

					// Update return value
					nResult ++;

				} // End of successfully processed files

			} // End of successfully got file path

		} // End of file size is valid

	}; // End of loop through dropped files

	// Free string memory
	delete [] lpszFilePath;

	return nResult;

} // End of function Drop::ProcessFiles

/*
Drop::
{
} // End of function Drop::
*/
