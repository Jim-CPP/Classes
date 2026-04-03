// SplashWindowClass.cpp

#include "SplashWindowClass.h"

// Global variables
LPTSTR g_lpszText;

LRESULT CALLBACK SplashWindowProcedure( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message

			// Initialise timer
			SetTimer( hWnd, SPLASH_WINDOW_CLASS_TIMER_ID, SPLASH_WINDOW_CLASS_MILLISECONDS, NULL );

			// Break out of switch
			break;

		} // End of a create message
		case WM_PAINT:
		{
			// A paint message
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rc;

			// Begin painting
			hdc = BeginPaint( hWnd, &ps );

			// Get client size
			GetClientRect( hWnd, &rc );

			// Draw border around window
			FrameRect( hdc, &rc, GetSysColorBrush( COLOR_WINDOWTEXT + 1 ) );

			// Remove borders from client size
			rc.left		+= SPLASH_WINDOW_CLASS_BORDER_SIZE;
			rc.right	-= SPLASH_WINDOW_CLASS_BORDER_SIZE;
			rc.top		+= SPLASH_WINDOW_CLASS_BORDER_SIZE;
			rc.bottom	-= SPLASH_WINDOW_CLASS_BORDER_SIZE;

			// Set text color
			SetTextColor( hdc, ( COLOR_WINDOWTEXT + 1 ) );

			// Set text background to transparent
			SetBkMode( hdc, TRANSPARENT );

			// Draw text
			DrawText( hdc, g_lpszText, -1, &rc, DT_CENTER );

			// End painting
			EndPaint( hWnd, &ps );

			// Break out of switch
			break;

		} // End of a paint message
		case WM_TIMER:
		{
			// A timer message

			// Destroy window
			DestroyWindow( hWnd );

			// Break out of switch
			break;

		} // End of a timer message
		case WM_ERASEBKGND:
		{
			// An erase background message
			HDC hdcWnd;
			RECT rcClient;
			RECT rcFill;
			HBRUSH hBrush;
			int nClientWidth;
			int nOffset;
			int nRed;
			int nGreen;
			int nBlue;
			int nStartRed	= SPLASH_WINDOW_CLASS_START_RED;
			int nStartGreen	= SPLASH_WINDOW_CLASS_START_GREEN;
			int nStartBlue	= SPLASH_WINDOW_CLASS_START_BLUE;
			int nEndRed		= SPLASH_WINDOW_CLASS_END_RED;
			int nEndGreen	= SPLASH_WINDOW_CLASS_END_GREEN;
			int nEndBlue	= SPLASH_WINDOW_CLASS_END_BLUE;

			// Get window dc
			hdcWnd = GetDC( hWnd );

			// Get window client size
			GetClientRect( hWnd, &rcClient );

			// Calculate client width
			nClientWidth = ( rcClient.right - rcClient.left );

			 // Create gradient
			for( nOffset =0; nOffset < nClientWidth; nOffset ++ )
			{
				// Calculate fill colors
				nRed	= ( nStartRed + ( nOffset * ( nEndRed -nStartRed ) / nClientWidth ) );
				nGreen	= ( nStartGreen + ( nOffset * ( nEndGreen -nStartGreen ) / nClientWidth ) );
				nBlue	= ( nStartBlue + ( nOffset * ( nEndBlue - nStartBlue ) / nClientWidth ) );

				// Initialise fill rect
				rcFill.left		= nOffset;
				rcFill.top		= 0;
				rcFill.right	= ( nOffset + 1 );
				rcFill.bottom	= rcClient.bottom;

				// Create solid brush
				hBrush = CreateSolidBrush( RGB( nRed, nGreen, nBlue ) );

				// Draw the rectangle
				FillRect( hdcWnd, &rcFill, hBrush );

			}; // End of loop to create gradient

			// Break out of switch
			break;

		} // End of an erase background message
		case WM_CLOSE:
		{
			// A close message

			// Destroy window
			DestroyWindow( hWnd );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default procedure
			lr = DefWindowProc( hWnd, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function SplashWindowProcedure

SplashWindow::SplashWindow()
{
} // End of function SplashWindow::SplashWindow

SplashWindow::~SplashWindow()
{
} // End of function SplashWindow::~SplashWindow

BOOL SplashWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create splash window
	if( Window::Create( SPLASH_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, hMenu, lpParam ) )
	{
		// Successfully created splash window

		// Update return value
		bResult = TRUE;

	} // End of successfully created splash window

	return bResult;

} // End of function SplashWindow::Create

BOOL SplashWindow::Show( HINSTANCE hInstance, LPCTSTR lpszText )
{
	BOOL bResult = FALSE;

	WindowClass windowClass;

	// Allocate string memory
	g_lpszText = new char[ STRING_LENGTH + sizeof( char ) ];

	// Copy text into global
	lstrcpy( g_lpszText, lpszText );

	// Initialise splash window class
	windowClass.Init( SPLASH_WINDOW_CLASS_NAME, SplashWindowProcedure, hInstance );

	// Register splash window class
	if( windowClass.Register() )
	{
		// Successfully registered splash window class

		// Create splash window
		if( Create( NULL, hInstance, NULL ) )
		{
			// Successfully created splash window
			Message message;
			int nSplashWindowLeft;
			int nSplashWindowTop;
			int nSplashWindowWidth;
			int nSplashWindowHeight;
			RECT rc;
			HDC hdc;

			// Get dc
			hdc = GetDC();

			// Use draw text to get the size of the text
			DrawText( hdc, g_lpszText, lstrlen( g_lpszText ), &rc, DT_CALCRECT );

			// Calculate splash window size
			nSplashWindowWidth	= ( ( rc.right - rc.left ) + ( SPLASH_WINDOW_CLASS_BORDER_SIZE * 2 ) );
			nSplashWindowHeight	= ( ( rc.bottom - rc.top ) + ( SPLASH_WINDOW_CLASS_BORDER_SIZE * 2 ) );

			// Calculate splash window position
			nSplashWindowLeft	= ( ( GetSystemMetrics( SM_CXSCREEN ) - nSplashWindowWidth ) / 2 );
			nSplashWindowTop	= ( ( GetSystemMetrics( SM_CYSCREEN ) - nSplashWindowHeight ) / 2 );

			// Move window
			Move( nSplashWindowLeft, nSplashWindowTop, nSplashWindowWidth, nSplashWindowHeight, TRUE );

			// Show splash window
			Window::Show( SW_SHOW );

			// Update splash window
			Update();

			// Message loop
			while( message.Get( NULL, 0, 0 ) > 0 )
			{
				// Translate message
				message.Translate();

				// Dispatch message
				message.Dispatch();

			}; // End of message loop

			// Update return value
			bResult = TRUE;

		} // End of successfully created splash window

	} // End of successfully registered splash window class

	// Free string memory
	delete [] g_lpszText;

	return bResult;

} // End of function SplashWindow::Show

/*
SplashWindow::
{
} // End of function SplashWindow::
*/
