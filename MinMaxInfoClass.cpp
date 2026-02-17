// MinMaxInfoClass.cpp

#include "MinMaxInfoClass.h"

MinMaxInfo::MinMaxInfo()
{
	// Initialise member variables
	ZeroMemory( &m_lpMinMaxInfo, sizeof( m_lpMinMaxInfo ) );

} // End of function MinMaxInfo::MinMaxInfo

MinMaxInfo::~MinMaxInfo()
{
	// Clear member variables
	ZeroMemory( &m_lpMinMaxInfo, sizeof( m_lpMinMaxInfo ) );

} // End of function MinMaxInfo::~MinMaxInfo

MinMaxInfo& MinMaxInfo::operator = ( MINMAXINFO FAR *lpMinMaxInfo )
{
	// Update member variables
	m_lpMinMaxInfo = lpMinMaxInfo;

	return *this;

} // End of function MinMaxInfo::operator =

BOOL MinMaxInfo::operator == ( MINMAXINFO FAR *lpMinMaxInfo )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( lpMinMaxInfo == m_lpMinMaxInfo )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function MinMaxInfo::operator ==

BOOL MinMaxInfo::operator != ( MINMAXINFO FAR *lpMinMaxInfo )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( lpMinMaxInfo != m_lpMinMaxInfo )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function MinMaxInfo::operator !=

MinMaxInfo::operator MINMAXINFO FAR *()
{
	return m_lpMinMaxInfo;

} // End of function MinMaxInfo::operator MINMAXINFO FAR *()

void MinMaxInfo::Update( LPARAM lParam, LONG lMinimumWidth, LONG lMinimumHeight )
{
	// Get min max info structure
	m_lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

	// Update min max info structure
	m_lpMinMaxInfo->ptMinTrackSize.x = lMinimumWidth;
	m_lpMinMaxInfo->ptMinTrackSize.y = lMinimumHeight;

} // End of function MinMaxInfo::Update

/*
MinMaxInfo::
{
} // End of function MinMaxInfo::
*/
