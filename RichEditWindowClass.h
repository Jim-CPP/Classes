// RichEditWindowClass.h

#pragma once

#include <windows.h>
#include <richedit.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "ClipboardClass.h"
#include "WindowClass.h"

#define RICH_EDIT_WINDOW_CLASS_NAME												RICHEDIT_CLASS
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_MENU										NULL
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_STYLE									( WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE )
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_LEFT										0
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_TOP										0
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_WIDTH									100
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_HEIGHT									100
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

#define RICH_EDIT_WINDOW_CLASS_DEFAULT_PLAIN_TEXT_MODE							(  TM_PLAINTEXT | TM_MULTILEVELUNDO | TM_MULTICODEPAGE )
#define RICH_EDIT_WINDOW_CLASS_DEFAULT_RICH_TEXT_MODE							(  TM_RICHTEXT | TM_MULTILEVELUNDO | TM_MULTICODEPAGE )

#define RICH_EDIT_WINDOW_CLASS_DEFAULT_EVENT_MASK								( ENM_SELCHANGE | ENM_UPDATE )

#define RICH_EDIT_WINDOW_LIBRARY_NAME											"riched20.dll"

class RichEditWindow : public Window
{
public:
	RichEditWindow();
	~RichEditWindow();

	BOOL Copy();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle = RICH_EDIT_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = RICH_EDIT_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = RICH_EDIT_WINDOW_CLASS_DEFAULT_LEFT, int nTop = RICH_EDIT_WINDOW_CLASS_DEFAULT_TOP, int nWidth = RICH_EDIT_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = RICH_EDIT_WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = RICH_EDIT_WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = RICH_EDIT_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL Cut();

	void Delete( BOOL bCanUndo = TRUE );

	LRESULT HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, void( *lpUpdateFunction )( BOOL bCanUndo, BOOL bCanRedo ) );

	LRESULT HandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( BOOL bIsTextSelected ) );

	BOOL Paste();

	void Select( int nStart = 0, int nEnd = -1 );

	int SetEventMask( int nNewEventMask = RICH_EDIT_WINDOW_CLASS_DEFAULT_EVENT_MASK );

	BOOL SetTextMode( int nTextMode );

	BOOL Redo();

	BOOL Undo();

protected:
	HMODULE m_hModuleRichEditLibrary;

}; // End of class RichEditWindow
