// WindowClassClass.cpp

#include "WindowClassClass.h"

WindowClass::WindowClass()
{
	// Initialise member variables
	ZeroMemory( &m_wc, sizeof( m_wc ) );

} // End of function WindowClass::WindowClass

WindowClass::~WindowClass()
{
	// Clear member variables
	ZeroMemory( &m_wc, sizeof( m_wc ) );

} // End of function WindowClass::~WindowClass

WindowClass& WindowClass::operator = ( WNDCLASSEX wc )
{
	// Update member variables
	m_wc = wc;

	return *this;

} // End of function WindowClass::operator =

WindowClass::operator WNDCLASSEX()
{
	return m_wc;

} // End of function WindowClass::operator WNDCLASSEX()

void WindowClass::Init( LPCSTR lpszClassName, WNDPROC lpfnWndProc, HINSTANCE hInstance, LPCSTR lpszMenuName, HBRUSH hbrBackground, UINT uStyle, HICON hIcon, HCURSOR hCursor, HICON hIconSmall, int nCbClsExtra, int nCbWndExtra )
{
	// Clear window class structure
	ZeroMemory( &m_wc, sizeof( m_wc ) );

	// Initialise window class structure
	m_wc.cbSize			= sizeof( WNDCLASSEX );
	m_wc.style			= uStyle;
	m_wc.lpfnWndProc	= lpfnWndProc;
	m_wc.cbClsExtra		= nCbClsExtra;
	m_wc.cbWndExtra		= nCbWndExtra;
	m_wc.hInstance		= hInstance;
	m_wc.hIcon			= hIcon;
	m_wc.hCursor		= hCursor;
	m_wc.hbrBackground	= hbrBackground;
	m_wc.lpszMenuName	= lpszMenuName;
	m_wc.lpszClassName	= lpszClassName;
	m_wc.hIconSm		= hIconSmall;

} // End of function WindowClass::Init

ATOM WindowClass::Register()
{
	// Register window class
	return RegisterClassEx( &m_wc );

} // End of function WindowClass::Register


/*
WindowClass::
{
} // End of function WindowClass::
*/
