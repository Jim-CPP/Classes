// MessageClass.cpp

#include "MessageClass.h"

Message::Message()
{
	// Initialise member variables
	ZeroMemory( &m_msg, sizeof( m_msg ) );

} // End of function Message::Message

Message::~Message()
{
	// Clear member variables
	ZeroMemory( &m_msg, sizeof( m_msg ) );

} // End of function Message::~Message

Message& Message::operator = ( MSG msg )
{
	// Update member variables
	m_msg = msg;

	return *this;

} // End of function Message::operator =

Message::operator int()
{
	return m_msg.wParam;

} // End of function Message::operator int()

Message::operator MSG()
{
	return m_msg;

} // End of function Message::operator MSG()

LRESULT Message::Dispatch()
{
	// Dispatch message
	return DispatchMessage( &m_msg );

} // End of function Message::Dispatch

BOOL Message::Get( HWND hWnd, UINT uMsgFilterMin, UINT uMsgFilterMax )
{
	// Get message
	return GetMessage( &m_msg, hWnd, uMsgFilterMin, uMsgFilterMax );

} // End of function Message::Get

BOOL Message::Translate()
{
	// Translate message
	return TranslateMessage( &m_msg );

} // End of function Message::Translate

/*
Message::
{
} // End of function Message::
*/
