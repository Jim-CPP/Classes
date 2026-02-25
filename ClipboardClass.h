// ClipboardClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define CLIPBOARD_CLASS_UNABLE_TO_OPEN_CLIPBOARD_ERROR_MESSAGE					"Unable to Open Clipboard"

class Clipboard
{
public:
	Clipboard();
	~Clipboard();

	BOOL Close();

	BOOL GetText( LPTSTR lpszText, UINT uFormat = CF_TEXT );

	DWORD GetTextLength( UINT uFormat = CF_TEXT );

	BOOL Open( HWND hWndNewOwner = NULL );

	BOOL SetText( LPCTSTR lpszText, UINT uFormat = CF_TEXT );

protected:

}; // End of class Clipboard
