// FontClass.cpp

#include "FontClass.h"

Font::Font()
{
	// Initialise member variables
	ZeroMemory( &m_hFont, sizeof( m_hFont ) );

} // End of function Font::Font

Font::~Font()
{
	// Clear member variables
	ZeroMemory( &m_hFont, sizeof( m_hFont ) );

} // End of function Font::~Font

Font& Font::operator = ( HFONT hFont )
{
	// Update member variables
	m_hFont = hFont;

	return *this;

} // End of function Font::operator =

BOOL Font::operator == ( HFONT hFont )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hFont == m_hFont )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Font::operator ==

BOOL Font::operator != ( HFONT hFont )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hFont != m_hFont )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Font::operator !=

Font::operator HFONT()
{
	return m_hFont;

} // End of function Font::operator HFONT()

BOOL Font::Get( int nStockObject )
{
	BOOL bResult = FALSE;

	// Get font
	m_hFont = ( HFONT )GetStockObject( nStockObject );

	// Ensure that font was got
	if( m_hFont )
	{
		// Successfully got font

		// Update return value
		bResult = TRUE;

	} // End of successfully got font

	return bResult;

} // End of function Font::Get
/*
Font::
{
} // End of function Font::
*/
