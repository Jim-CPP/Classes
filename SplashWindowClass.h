// SplashWindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "MessageClass.h"
#include "WindowClass.h"
#include "WindowClassClass.h"

#define SPLASH_WINDOW_CLASS_NAME												"Splash Window Class"
#define SPLASH_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define SPLASH_WINDOW_CLASS_DEFAULT_MENU										NULL
#define SPLASH_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE								WS_EX_TOPMOST
#define SPLASH_WINDOW_CLASS_DEFAULT_STYLE										( WS_POPUP | WS_VISIBLE )
#define SPLASH_WINDOW_CLASS_DEFAULT_LEFT										0
#define SPLASH_WINDOW_CLASS_DEFAULT_TOP											0
#define SPLASH_WINDOW_CLASS_DEFAULT_WIDTH										100
#define SPLASH_WINDOW_CLASS_DEFAULT_HEIGHT										100
#define SPLASH_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

#define SPLASH_WINDOW_CLASS_TIMER_ID											WM_USER
#define SPLASH_WINDOW_CLASS_MILLISECONDS										2000
#define SPLASH_WINDOW_CLASS_BORDER_SIZE											10
#define SPLASH_WINDOW_CLASS_START_RED											0xCC
#define SPLASH_WINDOW_CLASS_START_GREEN											0xCC
#define SPLASH_WINDOW_CLASS_START_BLUE											0xFF
#define SPLASH_WINDOW_CLASS_END_RED												0xFF
#define SPLASH_WINDOW_CLASS_END_GREEN											0xFF
#define SPLASH_WINDOW_CLASS_END_BLUE											0xFF

class SplashWindow : public Window
{
public:
	SplashWindow();
	~SplashWindow();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle = SPLASH_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = SPLASH_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = SPLASH_WINDOW_CLASS_DEFAULT_LEFT, int nTop = SPLASH_WINDOW_CLASS_DEFAULT_TOP, int nWidth = SPLASH_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = SPLASH_WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = SPLASH_WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = SPLASH_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL Show( HINSTANCE hInstance, LPCTSTR lpszText );

protected:

}; // End of class SplashWindow
