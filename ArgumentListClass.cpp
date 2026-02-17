// ArgumentListClass.cpp

#include "ArgumentListClass.h"

ArgumentList::ArgumentList()
{
	// Initialise member variables
	m_nArgumentCount = 0;
	m_lpszArgumentList = NULL;

} // End of function ArgumentList::ArgumentList

ArgumentList::~ArgumentList()
{
	// Clear member variables
	ZeroMemory( &m_lpszArgumentList, sizeof( m_lpszArgumentList ) );

} // End of function ArgumentList::~ArgumentList

ArgumentList& ArgumentList::operator = ( LPWSTR *lpszArgumentList )
{
	// Update member variables
	m_lpszArgumentList = lpszArgumentList;

	return *this;

} // End of function ArgumentList::operator =

BOOL ArgumentList::operator == ( LPWSTR *lpszArgumentList )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( lpszArgumentList == m_lpszArgumentList )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function ArgumentList::operator ==

BOOL ArgumentList::operator != ( LPWSTR *lpszArgumentList )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( lpszArgumentList != m_lpszArgumentList )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function ArgumentList::operator !=

ArgumentList::operator LPWSTR *()
{
	return m_lpszArgumentList;

} // End of function ArgumentList::operator LPWSTR *()

BOOL ArgumentList::Get()
{
	BOOL bResult = FALSE;

	// Get argument list
	m_lpszArgumentList = CommandLineToArgvW( GetCommandLineW(), &m_nArgumentCount );

	// Ensure that argument list was got
	if( m_lpszArgumentList )
	{
		// Successfully got argument list

		// Update return value
		bResult = TRUE;

	} // End of successfully got argument list

	return bResult;

} // End of function ArgumentList::Get

int ArgumentList::GetArgumentCount()
{
	// Return argument count
	return m_nArgumentCount;

} // End of function ArgumentList::GetArgumentCount

int ArgumentList::ProcessArguments( BOOL( *lpArgumentFunction )( LPCTSTR lpszArgument ) )
{
	int nResult = 0;

	int nWhichArgument;
	int nSizeNeeded;
	int nWideArgumentLength;

	// Allocate string memory
	LPTSTR lpszArgument = new char[ STRING_LENGTH ];

	// Loop through arguments
	for( nWhichArgument = 1; nWhichArgument < m_nArgumentCount; nWhichArgument ++ )
	{
		// Get wide argument length
		nWideArgumentLength = lstrlenW( m_lpszArgumentList[ nWhichArgument ] );

		// Get size required for argument
		nSizeNeeded = WideCharToMultiByte( CP_UTF8, 0, m_lpszArgumentList[ nWhichArgument ], nWideArgumentLength, NULL, 0, NULL, NULL );

		// Convert argument to ansi
		WideCharToMultiByte( CP_UTF8, 0, m_lpszArgumentList[ nWhichArgument ], nWideArgumentLength, lpszArgument, nSizeNeeded, NULL, NULL );

		// Terminate argument
		lpszArgument[ nSizeNeeded ] = ( char )NULL;

		// Process argument
		if( ( *lpArgumentFunction )( lpszArgument ) )
		{
			// Successfully processed argument

			// Update return value
			nResult ++;

		} // End of successfully processed argument

	}; // End of loop through arguments

	// Free string memory
	delete [] lpszArgument;

	return nResult;

} // End of function ArgumentList::ProcessArguments

/*
ArgumentList::
{
} // End of function ArgumentList::
*/
