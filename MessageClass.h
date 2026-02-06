// MessageClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Message
{
public:
	Message();
	~Message();

	Message& operator = ( MSG msg );

	operator int();

	operator MSG();

	LRESULT Dispatch();

	BOOL Get( HWND hWnd = NULL, UINT uMsgFilterMin = 0, UINT uMsgFilterMax = 0 );

	BOOL Translate();

protected:
	MSG m_msg;

}; // End of class Message
