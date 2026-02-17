// MenuClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define MENU_CLASS_DEFAULT_ITEM_FLAGS											MF_BYPOSITION
#define MENU_CLASS_DEFAULT_TRACK_POPUP_FLAGS									( TPM_LEFTALIGN | TPM_LEFTBUTTON )
#define MENU_CLASS_SEPARATOR_FLAGS												( MF_BYPOSITION | MF_SEPARATOR )

#define MENU_CLASS_SYSTEM_MENU_SEPARATOR_ITEM_POSITION							5
#define MENU_CLASS_SYSTEM_MENU_ABOUT_ITEM_POSITION								6
#define MENU_CLASS_SYSTEM_MENU_ABOUT_ITEM_TEXT									"About"

class Menu
{
public:
	Menu();
	~Menu();

	Menu& operator = ( HMENU hMenu );

	BOOL operator == ( HMENU hMenu );

	BOOL operator != ( HMENU hMenu );

	operator HMENU();

	BOOL InsertItem( UINT uPosition, LPCTSTR lpszItemText, UINT uID, UINT uFlags = MENU_CLASS_DEFAULT_ITEM_FLAGS );

	BOOL InsertSeparator( UINT uPosition );

	BOOL Load( LPCTSTR lpszMenuName, HINSTANCE hInstance = NULL );

	BOOL TrackPopupMenu( int nWhichSubMenu, HWND hWndParent, LPARAM lParam, UINT uFlags = MENU_CLASS_DEFAULT_TRACK_POPUP_FLAGS );

protected:
	HMENU m_hMenu;

}; // End of class Menu
