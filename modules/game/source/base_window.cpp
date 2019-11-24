#include "base_window.h"
#include "defines.h"
#include <stdexcept>
#include <iostream> //debug

BaseWindow::BaseWindow()
  : _hWnd(nullptr)
{ }

BaseWindow::BaseWindow(int width, int height)
  : _hWnd(nullptr)
{
  if(!createWindow(width, height)) {
    throw std::runtime_error("Can't create window properly");
  }
}

BaseWindow::~BaseWindow() {
  destroyWindow();
}

LRESULT __stdcall BaseWindow::WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  BaseWindow* wptr = nullptr;

  if(msg == WM_NCDESTROY) {
    SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
    return DefWindowProc(hWnd, msg, wParam, lParam);
  } else if(msg == WM_NCCREATE) {
    const LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
    wptr = (BaseWindow*)cs->lpCreateParams;
    wptr->_hWnd = hWnd;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)wptr);
  } else {
    wptr = (BaseWindow*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
  }

  if(wptr) {
    return wptr->WindProc( msg, wParam, lParam );
  } else {
    return DefWindowProc( hWnd, msg, wParam, lParam );
  }
}

bool BaseWindow::createWindow( int W, int H ) {
	const WNDCLASS wc = { CS_OWNDC, WindProc, NULL, NULL, 0, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), NULL, NULL, CLASS_NAME };
	RegisterClass(&wc);

	int height, width, left, top;
	width = W + ( (GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXEDGE) ) << 1) + 3;
	height = H + GetSystemMetrics(SM_CYCAPTION) + ( (GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CXEDGE) ) << 1) + 3;
	left = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
	top = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

	HWND hWnd = CreateWindow( CLASS_NAME, NULL, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, left, top, width, height, NULL, NULL, 0, (void*)this );
  if( !hWnd ) {
    return false;
  }

	ShowWindow( hWnd, SW_SHOW );
  return (bool)hWnd;
}

LRESULT BaseWindow::WindProc(UINT msg, WPARAM wParam, LPARAM lParam) {
  switch(msg) {
    case WM_CREATE:      OnCreate();                                          break;
    case WM_DESTROY:     OnDestroy();                                         break;
    case WM_LBUTTONDOWN: OnMouseClick(LOWORD(lParam), HIWORD(lParam), true);  break;
    case WM_LBUTTONUP:   OnMouseClick(LOWORD(lParam), HIWORD(lParam), false); break;
    case WM_MOUSEMOVE:   OnMouseMove(LOWORD(lParam), HIWORD(lParam));         break;
    case WM_KEYDOWN:     OnKeyboard(static_cast<int>(wParam), true);          break;
    case WM_KEYUP:       OnKeyboard(static_cast<int>(wParam), false);         break;

    default: return DefWindowProc(_hWnd, msg, wParam, lParam);
  }
}

#if 0



LRESULT __stdcall WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	double cx = RESOLUTION_X / 2;
	double cy = RESOLUTION_Y / 2;
	double dx,dy;

	switch(msg) {
	case WM_MOUSEMOVE:
		pointer->cursor.move(LOWORD(lParam), HIWORD(lParam));

		if(ATTACH_CAMERA_TO_CURSOR) {
			//dx = dbc(cx, 
			dx = (cx - pointer->cursor.getX())  /CAMERA_DISTANCE_RATE   /*/3*/;
			dy = (cy - pointer->cursor.getY())  /CAMERA_DISTANCE_RATE/*/3*/;

			pointer->camera.setXY(dx, dy);
			pointer->physicsMan.setCameraOffsetValue(dx, dy);
			//pointer->physicsMan.deposeGameObjectsFromCenter();
			pointer->player.faceTo(pointer->cursor.getX() - dx, pointer->cursor.getY() - dy);
		} else {
			pointer->player.faceTo(LOWORD(lParam), HIWORD(lParam));
		}

		break;

	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		pointer->drawFrame();
		EndPaint(hWnd, &ps);
		break;

	case WM_RBUTTONDOWN:
		pointer->keys.rightMouseButtonDown();
		break;

	case WM_RBUTTONUP:
		pointer->keys.rightMouseButtonUp();
		break;

	case WM_LBUTTONDOWN:
		pointer->keys.leftMouseButtonDown();
		break;

	case WM_LBUTTONUP:
		pointer->keys.leftMouseButtonUp();
		break;

	case WM_KEYDOWN:
		if(wParam == 27) {
			PostMessage(hWnd, WM_QUIT, 0, 0);
		}

		pointer->keys.keyDown(toupper(LOWORD(wParam)));
		break;

	case WM_KEYUP:
		pointer->keys.keyUp(toupper(LOWORD(wParam)));
		break;

	case WM_CREATE:
		brushWhite = CreateSolidBrush(RGB(255,255,255));
		brushBlack = CreateSolidBrush(RGB(0,0,0));
		penBlack = CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));

		hdc = GetDC(hWnd);
		break;

	case WM_DESTROY:
		if(brushWhite) DeleteObject(brushWhite);
		if(brushBlack) DeleteObject(brushBlack);
		if(penBlack) DeleteObject(penBlack);

		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}


#endif //0

#if 0
	double cx = RESOLUTION_X / 2;
	double cy = RESOLUTION_Y / 2;
	double dx,dy;

	switch(msg) {
	case WM_MOUSEMOVE:
		pointer->cursor.move(LOWORD(lParam), HIWORD(lParam));

		if(ATTACH_CAMERA_TO_CURSOR) {
			//dx = dbc(cx, 
			dx = (cx - pointer->cursor.getX())  /CAMERA_DISTANCE_RATE   /*/3*/;
			dy = (cy - pointer->cursor.getY())  /CAMERA_DISTANCE_RATE/*/3*/;

			pointer->camera.setXY(dx, dy);
			pointer->physicsMan.setCameraOffsetValue(dx, dy);
			//pointer->physicsMan.deposeGameObjectsFromCenter();
			pointer->player.faceTo(pointer->cursor.getX() - dx, pointer->cursor.getY() - dy);
		} else {
			pointer->player.faceTo(LOWORD(lParam), HIWORD(lParam));
		}

		break;

	case WM_PAINT:
#if 0
		BeginPaint(hWnd, &ps);
		pointer->drawFrame();
		EndPaint(hWnd, &ps);
#endif //0
		break;

	case WM_RBUTTONDOWN:
		pointer->keys.rightMouseButtonDown();
		break;

	case WM_RBUTTONUP:
		pointer->keys.rightMouseButtonUp();
		break;

	case WM_LBUTTONDOWN:
		pointer->keys.leftMouseButtonDown();
		break;

	case WM_LBUTTONUP:
		pointer->keys.leftMouseButtonUp();
		break;

	case WM_KEYDOWN:
		if(wParam == 27) {
			PostMessage(hWnd, WM_QUIT, 0, 0);
		}

		pointer->keys.keyDown(toupper(LOWORD(wParam)));
		break;

	case WM_KEYUP:
		pointer->keys.keyUp(toupper(LOWORD(wParam)));
		break;

	case WM_CREATE:
		brushWhite = CreateSolidBrush(RGB(255,255,255));
		brushBlack = CreateSolidBrush(RGB(0,0,0));
		penBlack = CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));

		hdc = GetDC(hWnd);
		break;

	case WM_DESTROY:
		if(brushWhite) DeleteObject(brushWhite);
		if(brushBlack) DeleteObject(brushBlack);
		if(penBlack) DeleteObject(penBlack);

		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
#endif //0

void BaseWindow::destroyWindow() {
  if(_hWnd) {
    SetWindowLongPtr(_hWnd, GWLP_USERDATA, 0);
    DestroyWindow(_hWnd);
  }
  SendMessage(_hWnd, WM_QUIT, 0, 0);
}


#if 0

#include "base_window.h"
#include "defines.h"

#include <stdexcept>

#include <iostream> //debug

BaseWindow::BaseWindow()
  : _hWnd(nullptr)
{ }

BaseWindow::BaseWindow(int width, int height)
  : _hWnd(nullptr)
{
  if(!createWindow(width, height)) {
    throw std::runtime_error("Can't create window properly");
  }
}

BaseWindow::~BaseWindow() {
  destroyWindow();
}

LRESULT __stdcall BaseWindow::WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  BaseWindow* wptr = nullptr;

  if(msg == WM_NCDESTROY) {
    SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
    return DefWindowProc(hWnd, msg, wParam, lParam);
  } else if(msg == WM_NCCREATE) {
    const LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
    wptr = (BaseWindow*)cs->lpCreateParams;
    wptr->_hWnd = hWnd;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)wptr);
  } else {
    wptr = (BaseWindow*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
  }

  if(wptr) {
    return wptr->WindProc(msg, wParam, lParam);
  } else {
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }
}

bool BaseWindow::createWindow(int W, int H) {
	const WNDCLASS wc = { CS_OWNDC, WindProc, NULL, NULL, 0, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), NULL, NULL, CLASS_NAME };
	RegisterClass(&wc);

	int height, width, left, top;
	height = W + GetSystemMetrics(SM_CYCAPTION) + ((GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CXEDGE)) << 1) + 3;
	width = H + ((GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CXEDGE)) << 1) + 3;
	left = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
	top = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

	HWND hWnd = CreateWindow(CLASS_NAME, NULL, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, left, top, width, height, NULL, NULL, 0, (void*)this);
	ShowWindow(hWnd, SW_SHOW);

  return (bool)hWnd;
}

LRESULT BaseWindow::WindProc(UINT msg, WPARAM wParam, LPARAM lParam) {
  switch(msg) {
    case WM_CREATE:      OnCreate();                                          break;
    case WM_DESTROY:     OnDestroy();                                         break;
    case WM_LBUTTONDOWN: OnMouseClick(LOWORD(lParam), HIWORD(lParam), true);  break;
    case WM_LBUTTONUP:   OnMouseClick(LOWORD(lParam), HIWORD(lParam), false); break;
    case WM_MOUSEMOVE:   OnMouseMove(LOWORD(lParam), HIWORD(lParam));         break;
    case WM_KEYDOWN:     OnKeyboard(static_cast<int>(wParam), true);          break;
    case WM_KEYUP:       OnKeyboard(static_cast<int>(wParam), false);         break;

    default: return DefWindowProc(_hWnd, msg, wParam, lParam);
  }
}

#if 0



LRESULT __stdcall WindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	double cx = RESOLUTION_X / 2;
	double cy = RESOLUTION_Y / 2;
	double dx,dy;

	switch(msg) {
	case WM_MOUSEMOVE:
		pointer->cursor.move(LOWORD(lParam), HIWORD(lParam));

		if(ATTACH_CAMERA_TO_CURSOR) {
			//dx = dbc(cx, 
			dx = (cx - pointer->cursor.getX())  /CAMERA_DISTANCE_RATE   /*/3*/;
			dy = (cy - pointer->cursor.getY())  /CAMERA_DISTANCE_RATE/*/3*/;

			pointer->camera.setXY(dx, dy);
			pointer->physicsMan.setCameraOffsetValue(dx, dy);
			//pointer->physicsMan.deposeGameObjectsFromCenter();
			pointer->player.faceTo(pointer->cursor.getX() - dx, pointer->cursor.getY() - dy);
		} else {
			pointer->player.faceTo(LOWORD(lParam), HIWORD(lParam));
		}

		break;

	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		pointer->drawFrame();
		EndPaint(hWnd, &ps);
		break;

	case WM_RBUTTONDOWN:
		pointer->keys.rightMouseButtonDown();
		break;

	case WM_RBUTTONUP:
		pointer->keys.rightMouseButtonUp();
		break;

	case WM_LBUTTONDOWN:
		pointer->keys.leftMouseButtonDown();
		break;

	case WM_LBUTTONUP:
		pointer->keys.leftMouseButtonUp();
		break;

	case WM_KEYDOWN:
		if(wParam == 27) {
			PostMessage(hWnd, WM_QUIT, 0, 0);
		}

		pointer->keys.keyDown(toupper(LOWORD(wParam)));
		break;

	case WM_KEYUP:
		pointer->keys.keyUp(toupper(LOWORD(wParam)));
		break;

	case WM_CREATE:
		brushWhite = CreateSolidBrush(RGB(255,255,255));
		brushBlack = CreateSolidBrush(RGB(0,0,0));
		penBlack = CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));

		hdc = GetDC(hWnd);
		break;

	case WM_DESTROY:
		if(brushWhite) DeleteObject(brushWhite);
		if(brushBlack) DeleteObject(brushBlack);
		if(penBlack) DeleteObject(penBlack);

		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}


#endif //0

#if 0
	double cx = RESOLUTION_X / 2;
	double cy = RESOLUTION_Y / 2;
	double dx,dy;

	switch(msg) {
	case WM_MOUSEMOVE:
		pointer->cursor.move(LOWORD(lParam), HIWORD(lParam));

		if(ATTACH_CAMERA_TO_CURSOR) {
			//dx = dbc(cx, 
			dx = (cx - pointer->cursor.getX())  /CAMERA_DISTANCE_RATE   /*/3*/;
			dy = (cy - pointer->cursor.getY())  /CAMERA_DISTANCE_RATE/*/3*/;

			pointer->camera.setXY(dx, dy);
			pointer->physicsMan.setCameraOffsetValue(dx, dy);
			//pointer->physicsMan.deposeGameObjectsFromCenter();
			pointer->player.faceTo(pointer->cursor.getX() - dx, pointer->cursor.getY() - dy);
		} else {
			pointer->player.faceTo(LOWORD(lParam), HIWORD(lParam));
		}

		break;

	case WM_PAINT:
#if 0
		BeginPaint(hWnd, &ps);
		pointer->drawFrame();
		EndPaint(hWnd, &ps);
#endif //0
		break;

	case WM_RBUTTONDOWN:
		pointer->keys.rightMouseButtonDown();
		break;

	case WM_RBUTTONUP:
		pointer->keys.rightMouseButtonUp();
		break;

	case WM_LBUTTONDOWN:
		pointer->keys.leftMouseButtonDown();
		break;

	case WM_LBUTTONUP:
		pointer->keys.leftMouseButtonUp();
		break;

	case WM_KEYDOWN:
		if(wParam == 27) {
			PostMessage(hWnd, WM_QUIT, 0, 0);
		}

		pointer->keys.keyDown(toupper(LOWORD(wParam)));
		break;

	case WM_KEYUP:
		pointer->keys.keyUp(toupper(LOWORD(wParam)));
		break;

	case WM_CREATE:
		brushWhite = CreateSolidBrush(RGB(255,255,255));
		brushBlack = CreateSolidBrush(RGB(0,0,0));
		penBlack = CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));

		hdc = GetDC(hWnd);
		break;

	case WM_DESTROY:
		if(brushWhite) DeleteObject(brushWhite);
		if(brushBlack) DeleteObject(brushBlack);
		if(penBlack) DeleteObject(penBlack);

		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
#endif //0

void BaseWindow::destroyWindow() {
  if(_hWnd) {
    SetWindowLongPtr(_hWnd, GWLP_USERDATA, 0);
    DestroyWindow(_hWnd);
  }
}


#endif //0
