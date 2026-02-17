// ListBoxWindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "WindowClass.h"

#define LIST_BOX_WINDOW_CLASS_NAME												WC_LISTBOX
#define LIST_BOX_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define LIST_BOX_WINDOW_CLASS_DEFAULT_MENU										NULL
#define LIST_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define LIST_BOX_WINDOW_CLASS_DEFAULT_STYLE										( WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define LIST_BOX_WINDOW_CLASS_DEFAULT_LEFT										0
#define LIST_BOX_WINDOW_CLASS_DEFAULT_TOP										0
#define LIST_BOX_WINDOW_CLASS_DEFAULT_WIDTH										100
#define LIST_BOX_WINDOW_CLASS_DEFAULT_HEIGHT									100
#define LIST_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class ListBoxWindow : public Window
{
public:
	ListBoxWindow();
	~ListBoxWindow();

	int AddString( LPCTSTR lpszString );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle = LIST_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = LIST_BOX_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = LIST_BOX_WINDOW_CLASS_DEFAULT_LEFT, int nTop = LIST_BOX_WINDOW_CLASS_DEFAULT_TOP, int nWidth = LIST_BOX_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = LIST_BOX_WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = LIST_BOX_WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = LIST_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM );

	LRESULT HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ) );

protected:

}; // End of class ListBoxWindow
