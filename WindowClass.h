// WindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define WINDOW_CLASS_DEFAULT_EXTENDED_STYLE										( WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES )
#define WINDOW_CLASS_DEFAULT_STYLE												WS_OVERLAPPEDWINDOW
#define WINDOW_CLASS_DEFAULT_LEFT												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_TOP												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_WIDTH												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_HEIGHT												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_MENU												( HMENU )NULL
#define WINDOW_CLASS_DEFAULT_LP_PARAM											NULL

#define WINDOW_CLASS_UNABLE_TO_CREATE_WINDOW_ERROR_MESSAGE						"Unable to Create Window"

class Window
{
public:
	Window();
	~Window();

	Window& operator = ( HWND hWnd );

	BOOL operator == ( HWND hWnd );

	BOOL operator != ( HWND hWnd );

	operator HWND();

	BOOL Create( LPCTSTR lpszClassName, HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle = WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = WINDOW_CLASS_DEFAULT_STYLE, int nLeft = WINDOW_CLASS_DEFAULT_LEFT, int nTop = WINDOW_CLASS_DEFAULT_TOP, int nWidth = WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL GetClientRect( LPRECT lpRect );

	HMENU GetSystemMenu( WINBOOL bRevert );

	int GetText( LPTSTR lpszText, int nMaxCount );

	int GetTextLength();

	BOOL GetWindowRect( LPRECT lpRect );

	BOOL Move( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

	HWND SetFocus();

	void SetFont( HFONT hFont, BOOL bRedraw = TRUE );

	BOOL SetText( LPCTSTR lpszText );

	BOOL Show( int nCmdShow );

	BOOL Update();

protected:
	HWND m_hWnd;

}; // End of class Window
