// DropClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Drop
{
public:
	Drop();
	~Drop();

	Drop& operator = ( HDROP hDrop );

	BOOL operator == ( HDROP hDrop );

	BOOL operator != ( HDROP hDrop );

	operator HDROP();

	int ProcessAllFiles( void( *lpAllDroppedFilesFunction )( LPCTSTR lpszAllDroppedFilePaths ) );

	int ProcessFiles( BOOL( *lpDropFunction )( LPCTSTR lpszDroppedFilePath ) );

	int ProcessFiles( WPARAM wParam, BOOL( *lpDropFunction )( LPCTSTR lpszDroppedFilePath ) );

protected:
	HDROP m_hDrop;

}; // End of class Drop
