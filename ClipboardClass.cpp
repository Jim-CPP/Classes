// ClipboardClass.cpp

#include "ClipboardClass.h"

Clipboard::Clipboard()
{
	// Initialise member variables

} // End of function Clipboard::Clipboard

Clipboard::~Clipboard()
{
	// Clear member variables

} // End of function Clipboard::~Clipboard

BOOL Clipboard::Close()
{
	// Close clipboard
	return ::CloseClipboard();

} // End of function Clipboard::Close

BOOL Clipboard::GetText( LPTSTR lpszText, UINT uFormat )
{
	BOOL bResult = FALSE;

	HANDLE hClipboard;

	// Get clipboard data
	hClipboard = ::GetClipboardData( uFormat );

	// Ensure that clipboard data was got
	if( hClipboard )
	{
		// Successfully got clipboard data

		// Update text
		::lstrcpy( lpszText, ( ( LPTSTR )hClipboard ) );

		// Update return value
		bResult = TRUE;

	} // End of successfully got clipboard data

	return bResult;

} // End of function Clipboard::GetTextLength

DWORD Clipboard::GetTextLength( UINT uFormat )
{
	DWORD dwResult = 0;

	HANDLE hClipboard;

	// Get clipboard data
	hClipboard = ::GetClipboardData( uFormat );

	// Ensure that clipboard data was got
	if( hClipboard )
	{
		// Successfully got clipboard data

		// Get text length
		dwResult = ::lstrlen( ( LPTSTR )hClipboard );

	} // End of successfully got clipboard data

	return dwResult;

} // End of function Clipboard::GetText

BOOL Clipboard::Open( HWND hWndNewOwner )
{
	// Open clipboard
	return ::OpenClipboard( hWndNewOwner );

} // End of function Clipboard::Open

BOOL Clipboard::SetText( LPCTSTR lpszText, UINT uFormat )
{
	BOOL bResult = FALSE;

	HGLOBAL hGlobal;
	DWORD dwBufferLength;

	// Calculate buffer length
	dwBufferLength = ( ::lstrlen( lpszText ) + sizeof( char ) );

	// Empty clipboard
	::EmptyClipboard();

	// Allocate global memory
	hGlobal = ::GlobalAlloc( GMEM_MOVEABLE, dwBufferLength );

	// Ensure that global memory was allocated
	if( hGlobal )
	{
		// Successfully allocated global memory

		// Copy text into global memory
		::memcpy( ::GlobalLock( hGlobal ), lpszText, dwBufferLength );

		// Unlock global memory
		::GlobalUnlock( hGlobal );

		// Update clipboard
		::SetClipboardData( uFormat, hGlobal );

		// Free global memory
		::GlobalFree( hGlobal );

	} // End of successfully allocated global memory

	return bResult;

} // End of function Clipboard::SetText

/*
Clipboard::
{
} // End of function Clipboard::
*/
