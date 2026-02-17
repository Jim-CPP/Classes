// FontClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Font
{
public:
	Font();
	~Font();

	Font& operator = ( HFONT hFont );

	BOOL operator == ( HFONT hFont );

	BOOL operator != ( HFONT hFont );

	operator HFONT();

	BOOL Get( int nStockObject );

protected:
	HFONT m_hFont;

}; // End of class Font
