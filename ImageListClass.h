// ImageListClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class ImageList
{
public:
	ImageList();
	~ImageList();

	ImageList& operator = ( HIMAGELIST hImageList );

	BOOL operator == ( HIMAGELIST hImageList );

	BOOL operator != ( HIMAGELIST hImageList );

	operator HIMAGELIST();

	BOOL GetSystem();

protected:
	HIMAGELIST m_hImageList;

}; // End of class ImageList
