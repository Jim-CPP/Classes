// TemplateWindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "WindowClass.h"

#define TEMPLATE_WINDOW_CLASS_NAME												WC_LISTBOX
#define TEMPLATE_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define TEMPLATE_WINDOW_CLASS_DEFAULT_MENU										NULL
#define TEMPLATE_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_STYLE										( WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define TEMPLATE_WINDOW_CLASS_DEFAULT_LEFT										0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_TOP										0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_WIDTH										100
#define TEMPLATE_WINDOW_CLASS_DEFAULT_HEIGHT									100
#define TEMPLATE_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class TemplateWindow : public Window
{
public:
	TemplateWindow();
	~TemplateWindow();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle = TEMPLATE_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = TEMPLATE_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = TEMPLATE_WINDOW_CLASS_DEFAULT_LEFT, int nTop = TEMPLATE_WINDOW_CLASS_DEFAULT_TOP, int nWidth = TEMPLATE_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = TEMPLATE_WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = TEMPLATE_WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = TEMPLATE_WINDOW_CLASS_DEFAULT_LP_PARAM );

	LRESULT HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ) );

protected:

}; // End of class TemplateWindow
