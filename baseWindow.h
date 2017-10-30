#if NEW_GEN

#pragma once

#ifndef __BASE_WINDOW_H__
#define __BASE_WINDOW_H__

#include <windows.h>

class BaseWindow {
protected:
	HWND hWnd;
	HDC hDC;

	int iScreenWidth;
	int iScreenHeight;

public:
	BaseWindow();
	virtual ~BaseWindow();

	static LRESULT __stdcall WindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	LRESULT OwnWindowProc( UINT msg, WPARAM wParam, LPARAM lParam );

	bool InitWindow( wchar_t * lpwsClassName, wchar_t * lpwsWindowName, DWORD dwStyle, int iPosX, int iPosY, int iWidth, int iHeight, bool bAlignCenter );
	virtual void Run( );

	void SetWndHandle( HWND _hWnd );
};

#endif //__BASE_WINDOW_H__

#endif