// FileClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class File
{
public:
	File();
	~File();

	File& operator = ( HANDLE hFile );

	BOOL operator == ( HANDLE hFile );

	BOOL operator != ( HANDLE hFile );

	operator HANDLE();

	BOOL Close();

	BOOL Create( LPCTSTR lpszFileName );

	DWORD GetSize( LPDWORD lpFileSizeHigh = NULL );

	BOOL Open( LPCTSTR lpszFileName );

	BOOL Read( LPVOID lpBuffer, DWORD dwNumberOfBytesToRead );

	BOOL Write( LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite );

protected:
	HANDLE m_hFile;

}; // End of class File
