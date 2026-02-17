// MinMaxInfoClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define MIN_MAX_INFO_CLASS_DEFAULT_MINIMUM_WIDTH								320
#define MIN_MAX_INFO_CLASS_DEFAULT_MINIMUM_HEIGHT								200

class MinMaxInfo
{
public:
	MinMaxInfo();
	~MinMaxInfo();

	MinMaxInfo& operator = ( MINMAXINFO FAR *lpMinMaxInfo );

	BOOL operator == ( MINMAXINFO FAR *lpMinMaxInfo );

	BOOL operator != ( MINMAXINFO FAR *lpMinMaxInfo );

	operator MINMAXINFO FAR *();

	void Update( LPARAM lParam, LONG lMinimumWidth = MIN_MAX_INFO_CLASS_DEFAULT_MINIMUM_WIDTH, LONG lMinimumHeight = MIN_MAX_INFO_CLASS_DEFAULT_MINIMUM_HEIGHT );

protected:
	MINMAXINFO FAR * m_lpMinMaxInfo;

}; // End of class MinMaxInfo
