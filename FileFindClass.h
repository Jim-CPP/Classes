// FileFindClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class FileFind
{
public:
	FileFind();
	~FileFind();

	FileFind& operator = ( HANDLE hFileFind );

	BOOL operator == ( HANDLE hFileFind );

	BOOL operator != ( HANDLE hFileFind );

	operator HANDLE();

	BOOL Close();

	BOOL First( LPCTSTR lpszParentFolderPath, LPCTSTR lpszFileFilter );

	LPTSTR GetFileName( LPTSTR lpszFileName );

	BOOL IsDots();

	BOOL IsFolder();

	BOOL Next();

protected:
	HANDLE m_hFileFind;
	WIN32_FIND_DATA m_wfd;
	LPTSTR m_lpszParentFolderPath;

}; // End of class FileFind
