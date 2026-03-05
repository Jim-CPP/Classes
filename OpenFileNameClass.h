// OpenFileNameClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define OPEN_FILE_NAME_CLASS_DEFAULT_OPEN_FLAGS									( OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY )
#define OPEN_FILE_NAME_CLASS_DEFAULT_SAVE_FLAGS									( OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT )

class OpenFileName
{
public:
	OpenFileName();
	~OpenFileName();

	OpenFileName& operator = ( OPENFILENAME ofn );

	operator OPENFILENAME();

	BOOL GetOpen( HWND hWndOwner, LPCTSTR lpszFilter, LPCTSTR lpszDefaultExtension, LPTSTR lpszFileName, DWORD dwFlags = OPEN_FILE_NAME_CLASS_DEFAULT_OPEN_FLAGS );

	BOOL GetSave( HWND hWndOwner, LPCTSTR lpszFilter, LPCTSTR lpszDefaultExtension, LPTSTR lpszFileName, DWORD dwFlags = OPEN_FILE_NAME_CLASS_DEFAULT_SAVE_FLAGS );

protected:
	OPENFILENAME m_ofn;

}; // End of class OpenFileName
