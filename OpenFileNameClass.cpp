// OpenFileNameClass.cpp

#include "OpenFileNameClass.h"

OpenFileName::OpenFileName()
{
	// Initialise member variables
	::ZeroMemory( &m_ofn, sizeof( m_ofn ) );

} // End of function OpenFileName::OpenFileName

OpenFileName::~OpenFileName()
{
	// Clear member variables
	::ZeroMemory( &m_ofn, sizeof( m_ofn ) );

} // End of function OpenFileName::~OpenFileName

OpenFileName& OpenFileName::operator = ( OPENFILENAME ofn )
{
	// Update member variables
	m_ofn = ofn;

	return *this;

} // End of function OpenFileName::operator =

OpenFileName::operator OPENFILENAME()
{
	return m_ofn;

} // End of function OpenFileName::operator OPENFILENAME()

BOOL OpenFileName::GetOpen( HWND hWndOwner, LPCTSTR lpszFilter, LPCTSTR lpszDefaultExtension, LPTSTR lpszFileName, DWORD dwFlags )
{
	BOOL bResult = FALSE;

	// Clear open file name structure
	::ZeroMemory( &m_ofn, sizeof( m_ofn ) );

	// Initialise open file name structure
	m_ofn.lStructSize	= sizeof( m_ofn );
	m_ofn.hwndOwner		= hWndOwner;
	m_ofn.lpstrFilter	= lpszFilter;
	m_ofn.nMaxFile		= STRING_LENGTH;
	m_ofn.Flags			= dwFlags;
	m_ofn.lpstrFile		= lpszFileName;
	m_ofn.lpstrDefExt	= lpszDefaultExtension;

	// Clear file name
	lpszFileName[ 0 ] = ( char )NULL;

	// Get open file name
	if( ::GetOpenFileName( &m_ofn ) )
	{
		// Successfully got open file name

		// Update return value
		bResult = TRUE;

	} // End of successfully got open file name

	return bResult;

} // End of function OpenFileName::GetOpen

BOOL OpenFileName::GetSave( HWND hWndOwner, LPCTSTR lpszFilter, LPCTSTR lpszDefaultExtension, LPTSTR lpszFileName, DWORD dwFlags )
{
	BOOL bResult = FALSE;

	// Clear open file name structure
	::ZeroMemory( &m_ofn, sizeof( m_ofn ) );

	// Initialise open file name structure
	m_ofn.lStructSize	= sizeof( m_ofn );
	m_ofn.hwndOwner		= hWndOwner;
	m_ofn.lpstrFilter	= lpszFilter;
	m_ofn.lpstrFile		= lpszFileName;
	m_ofn.nMaxFile		= STRING_LENGTH;
	m_ofn.Flags			= dwFlags;
	m_ofn.lpstrDefExt	= lpszDefaultExtension;

	// Clear file name
	lpszFileName[ 0 ] = ( char )NULL;

	// Get save file name
	if( ::GetSaveFileName( &m_ofn ) )
	{
		// Successfully got save file name

		// Update return value
		bResult = TRUE;

	} // End of successfully got save file name

	return bResult;

} // End of function OpenFileName::GetSave

/*
OpenFileName::
{
} // End of function OpenFileName::
*/
