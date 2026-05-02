// ImageListClass.cpp

#include "ImageListClass.h"

ImageList::ImageList()
{
	// Initialise member variables
	ZeroMemory( &m_hImageList, sizeof( m_hImageList ) );

} // End of function ImageList::ImageList

ImageList::~ImageList()
{
	// Clear member variables
	ZeroMemory( &m_hImageList, sizeof( m_hImageList ) );

} // End of function ImageList::~ImageList

ImageList& ImageList::operator = ( HIMAGELIST hImageList )
{
	// Update member variables
	m_hImageList = hImageList;

	return *this;

} // End of function ImageList::operator =

BOOL ImageList::operator == ( HIMAGELIST hImageList )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hImageList == m_hImageList )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function ImageList::operator ==

BOOL ImageList::operator != ( HIMAGELIST hImageList )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hImageList != m_hImageList )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function ImageList::operator !=

ImageList::operator HIMAGELIST()
{
	return m_hImageList;

} // End of function ImageList::operator HIMAGELIST()

BOOL ImageList::GetSystem()
{
	BOOL bResult = FALSE;

	SHFILEINFO shFileInfo;

	// Get system image list
	m_hImageList = ( HIMAGELIST )::SHGetFileInfo( NULL, 0, &shFileInfo, sizeof( shFileInfo ), ( SHGFI_SYSICONINDEX | SHGFI_SMALLICON ) );

	// Ensure that system image list was got
	if( m_hImageList )
	{
		// Successfully got system image list

		// Update return value
		bResult = TRUE;

	} // End of successfully got system image list

	return bResult;

} // End of function ImageList::GetSystem

/*
ImageList::
{
} // End of function ImageList::
*/
