#if NEW_GEN

#include "baseWindow.h"

BaseWindow::BaseWindow() : hWnd(0), hDC(0), iScreenWidth(0), iScreenHeight(0) { }
BaseWindow::~BaseWindow() { }

void BaseWindow::SetWndHandle( HWND _hWnd ) { hWnd = _hWnd; }

LRESULT __stdcall BaseWindow::WindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	BaseWindow * ptr = nullptr;

	if( msg == WM_NCCREATE ) {
		LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT) lParam;

		ptr = (BaseWindow *) lpCreateStruct->lpCreateParams;
		ptr->SetWndHandle( hWnd );

		SetWindowLongPtr( hWnd, GWLP_USERDATA, (LONG_PTR) ptr );
	} else {
		ptr = (BaseWindow *) GetWindowLongPtr( hWnd, GWLP_USERDATA );
	}

	if( ptr ) {
		return ptr->OwnWindowProc( msg, wParam, lParam );
	} else {
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
}

LRESULT BaseWindow::OwnWindowProc( UINT msg, WPARAM wParam, LPARAM lParam ) {
	switch( msg ) {
		case WM_NCDESTROY:
			SetWindowLongPtr( hWnd, GWLP_USERDATA, 0 );
			return DefWindowProc( hWnd, msg, wParam, lParam );

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

bool BaseWindow::InitWindow( wchar_t * lpwsClassName, wchar_t * lpwsWindowName, DWORD dwStyle, int iPosX, int iPosY, int iWidth, int iHeight, bool bAlignCenter ) {
	WNDCLASS ws;
	ZeroMemory( &ws, sizeof( ws ) );

	ws.lpfnWndProc = WindowProc;
	ws.hCursor = LoadCursor( 0, IDC_ARROW );
	ws.hIcon = LoadIcon( 0, IDI_APPLICATION );
	ws.lpszClassName = lpwsClassName;
	ws.style = CS_HREDRAW | CS_VREDRAW;

	if( !RegisterClass( &ws ) ) {
		return false;
	}

	RECT rect = { 0, 0, iWidth, iHeight };
	AdjustWindowRect( &rect, dwStyle, FALSE );

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int x, y;

	iScreenWidth = GetSystemMetrics( SM_CXSCREEN );
	iScreenHeight = GetSystemMetrics( SM_CYSCREEN );

	if( bAlignCenter ) {
		x = ( iScreenWidth - width ) / 2;
		y = ( iScreenHeight - height ) / 2;
	} else {
		x = iPosX;
		y = iPosY;
	}

	HWND _hWnd = CreateWindow( lpwsClassName, lpwsWindowName, dwStyle, x, y, width, height, 0, 0, 0, this );
	if( !_hWnd ) {
		return false;
	}

	ShowWindow( _hWnd, SW_SHOW );
	return true;
}

void BaseWindow::Run( ) {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while( true ) {
		if( PeekMessage( &msg, 0, 0, 0, PM_NOREMOVE ) ) {
			if( GetMessage( &msg, 0, 0, 0 ) ) {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			} else {
				break;
			}
		} else {

		}
	}
}

#endif //#if NEW_GEN