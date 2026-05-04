// FileFindClass.cpp

#include "FileFindClass.h"

FileFind::FileFind()
{
	// Allocate string memory
	m_lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear parent folder path
	m_lpszParentFolderPath[ 0 ] = ( char )NULL;

	// Initialise member variables
	ZeroMemory( &m_hFileFind, sizeof( m_hFileFind ) );

} // End of function FileFind::FileFind

FileFind::~FileFind()
{
	// Clear member variables
	ZeroMemory( &m_hFileFind, sizeof( m_hFileFind ) );

	// Free string memory
	delete [] m_lpszParentFolderPath;

} // End of function FileFind::~FileFind

FileFind& FileFind::operator = ( HANDLE hFileFind )
{
	// Update member variables
	m_hFileFind = hFileFind;

	return *this;

} // End of function FileFind::operator =

BOOL FileFind::operator == ( HANDLE hFileFind )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hFileFind == m_hFileFind )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function FileFind::operator ==

BOOL FileFind::operator != ( HANDLE hFileFind )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hFileFind != m_hFileFind )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function FileFind::operator !=

FileFind::operator HANDLE()
{
	return m_hFileFind;

} // End of function FileFind::operator HANDLE()

BOOL FileFind::Close()
{
	// Close file find
	return ::CloseHandle( m_hFileFind );

} // End of function FileFind::Close

BOOL FileFind::First( LPCTSTR lpszParentFolderPath, LPCTSTR lpszFileFilter )
{
	BOOL bResult = FALSE;

	// Allocate string memory
	LPTSTR lpszParentFolderPath2 = new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszFullSearchPattern = new char[ STRING_LENGTH + sizeof( char ) ];

	// Store parent folder path
	lstrcpy( lpszParentFolderPath2, lpszParentFolderPath );
	// Note that the parent folder path input parameter is a constant, which can't be modified
	// Therefore a copy needs to be created

	// Ensure that current folder path ends with a back-slash
	if( lpszParentFolderPath2[ lstrlen( lpszParentFolderPath2 ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
	{
		// Current folder path does not end with a back-slash

		// Append back-slash onto current folder path
		lstrcat( lpszParentFolderPath2, ASCII_BACK_SLASH_STRING );

	} // End of current folder path does not end with a back-slash

	// Copy current folder path into full search pattern
	lstrcpy( lpszFullSearchPattern, lpszParentFolderPath2 );

	// Append all files filter onto full search pattern
	lstrcat( lpszFullSearchPattern, lpszFileFilter );

	// Find first item
	m_hFileFind= FindFirstFile( lpszFullSearchPattern, &m_wfd );

	// Ensure that first item was found
	if( m_hFileFind != INVALID_HANDLE_VALUE )
	{
		// Successfully found first item

		// Update parent folder path
		lstrcpy( m_lpszParentFolderPath, lpszParentFolderPath2 );

		// Update return value
		bResult = TRUE;

	} // End of successfully found first item

	// Free string memory
	delete [] lpszParentFolderPath2;
	delete [] lpszFullSearchPattern;

	return bResult;

} // End of function FileFind::First

LPTSTR FileFind::GetFileName( LPTSTR lpszFileName )
{
	// Get file name
	return ::lstrcpy( lpszFileName, m_wfd.cFileName );

} // End of function FileFind::GetFileName

LPTSTR FileFind::GetParentFolderPath( LPTSTR lpszParentFolderPath )
{
	// Get parent folder path
	return lstrcpy( lpszParentFolderPath, m_lpszParentFolderPath );

} // End of function FileFind::GetParentFolderPath

BOOL FileFind::GetModifiedTime( LPTSTR lpszModifiedTime )
{
	BOOL bResult = FALSE;

	SYSTEMTIME stModified;

	// Convert modified file time to system time
	if( FileTimeToSystemTime( ( &( m_wfd.ftLastWriteTime ) ), &stModified ) )
	{
		// Successfully converted modified file time to system time

		// Format modified time
		wsprintf( lpszModifiedTime, FILE_FIND_CLASS_MODIFIED_TIME_FORMAT_STRING, stModified.wYear, stModified.wMonth, stModified.wDay, stModified.wHour, stModified.wMinute, stModified.wSecond );

		// Update return value
		bResult = TRUE;

	} // End of successfully converted modified file time to system time

	return bResult;

} // End of function FileFind::GetModifiedTime

BOOL FileFind::IsDots()
{
	BOOL bResult = FALSE;

	// See if found item is dots
	if( m_wfd.cFileName[ 0 ] == ASCII_FULL_STOP_CHARACTER )
	{
		// Found item is dots

		// Update return value
		bResult = TRUE;

	} // End of found item is dots

	return bResult;

} // End of function FileFind::IsDots

BOOL FileFind::IsFolder()
{
	BOOL bResult = FALSE;

	// See if found item is a folder
	if( m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		// Found item is a folder

		// Update return value
		bResult = TRUE;

	} // End of found item is a folder

	return bResult;

} // End of function FileFind::IsFolder

BOOL FileFind::Next()
{
	// Find next file
	return ::FindNextFile( m_hFileFind, &m_wfd );

} // End of function FileFind::Next


/*
FileFind::
{
} // End of function FileFind::
*/
