// ArgumentListClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define ARGUMENT_LIST_CLASS_FIRST_ARGUMENT_POSITION								1

class ArgumentList
{
public:
	ArgumentList();
	~ArgumentList();

	ArgumentList& operator = ( LPWSTR *lpszArgumentList );

	BOOL operator == ( LPWSTR *lpszArgumentList );

	BOOL operator != ( LPWSTR *lpszArgumentList );

	operator LPWSTR *();

	BOOL Get();

	int GetArgumentCount();

	BOOL GetFirstArgument( LPTSTR lpszFirstArgument );

	int ProcessArguments( BOOL( *lpArgumentFunction )( LPCTSTR lpszArgument ) );

protected:
	LPWSTR * m_lpszArgumentList;
	int m_nArgumentCount;

}; // End of class ArgumentList
