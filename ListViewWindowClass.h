// ListViewWindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "WindowClass.h"

#define LIST_VIEW_WINDOW_CLASS_NAME												WC_LISTVIEW
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU										NULL
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							LVS_EX_FULLROWSELECT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE									( WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT )
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT										0
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP										0
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH									100
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT									100
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

#define LIST_VIEW_WINDOW_CLASS_DEFAULT_COLUMN_WIDTH								100

class ListViewWindow : public Window
{
public:
	ListViewWindow();
	~ListViewWindow();

	int AddColumn( LPCTSTR lpszColumnTitle, int nColumnWidth = LIST_VIEW_WINDOW_CLASS_DEFAULT_COLUMN_WIDTH );

	int AddItem( LPCTSTR lpszItemText, DWORD dwTextMax = STRING_LENGTH );

	int AutoSizeAllColumns();

	int CALLBACK Compare( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT, DWORD dwExStyle = LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, HMENU hMenu = LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU, LPVOID lpParam = LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL GetItemText( int nWhichItem, int nWhichSubItem, LPTSTR lpszItemText, DWORD dwTextMax = STRING_LENGTH );

	LRESULT HandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam );

	LRESULT HandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectionChangeFunction )( LPCTSTR lpszItemText ), BOOL( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), PFNLVCOMPARE pFnLvCompare );

	BOOL SetItemText( int nWhichItem, int nWhichSubItem, LPCTSTR lpszItemText, DWORD dwTextMax = STRING_LENGTH );

protected:
	int m_nColumnCount;

}; // End of class ListViewWindow
