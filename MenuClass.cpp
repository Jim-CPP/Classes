// MenuClass.cpp

#include "MenuClass.h"

Menu::Menu()
{
	// Initialise member variables
	ZeroMemory( &m_hMenu, sizeof( m_hMenu ) );

} // End of function Menu::Menu

Menu::~Menu()
{
	// Clear member variables
	ZeroMemory( &m_hMenu, sizeof( m_hMenu ) );

} // End of function Menu::~Menu

Menu& Menu::operator = ( HMENU hMenu )
{
	// Update member variables
	m_hMenu = hMenu;

	return *this;

} // End of function Menu::operator =

BOOL Menu::operator == ( HMENU hMenu )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hMenu == m_hMenu )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Menu::operator ==

BOOL Menu::operator != ( HMENU hMenu )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hMenu != m_hMenu )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Menu::operator !=

Menu::operator HMENU()
{
	return m_hMenu;

} // End of function Menu::operator HMENU()

BOOL Menu::EnableItem( UINT uWhichItem, BOOL bEnable )
{
	BOOL bResult = FALSE;

	// See if item is to be enabled
	if( bEnable )
	{
		// Item is to be enabled

		// Enable item
		bResult = ::EnableMenuItem( m_hMenu, uWhichItem, MF_ENABLED );

	} // End of item is to be enabled
	else
	{
		// Item is to be disabled

		// Disable item
		bResult = ::EnableMenuItem( m_hMenu, uWhichItem, MF_DISABLED );

	} // End of item is to be disabled

	return bResult;

} // End of function Menu::

BOOL Menu::InsertItem( UINT uPosition, LPCTSTR lpszItemText, UINT uID, UINT uFlags )
{
	// Insert item
	return InsertMenu( m_hMenu, uPosition, uFlags, uID, lpszItemText );

} // End of function Menu::InsertItem

BOOL Menu::InsertSeparator( UINT uPosition )
{
	// Insert separator
	return InsertMenu( m_hMenu, uPosition, MENU_CLASS_SEPARATOR_FLAGS, 0, NULL );

} // End of function Menu::InsertSeparator

BOOL Menu::Load( LPCTSTR lpszMenuName, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load menu
	m_hMenu = LoadMenu( hInstance, lpszMenuName );

	// Ensure that menu was loaded
	if( m_hMenu )
	{
		// Successfully loaded menu

		// Update return value
		bResult = TRUE;

	} // End of successfully loaded menu

	return bResult;

} // End of function Menu::Load

BOOL Menu::TrackPopupMenu( int nWhichSubMenu, HWND hWndParent, LPARAM lParam, UINT uFlags )
{
	// Track popup menu
	return ::TrackPopupMenu( GetSubMenu( m_hMenu, nWhichSubMenu ), uFlags, LOWORD( lParam ), HIWORD( lParam ), 0, hWndParent, NULL );

} // End of function Menu::TrackPopupMenu

/*
Menu::
{
} // End of function Menu::
*/
