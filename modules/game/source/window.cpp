#include "window.h"
#include "engine.h"

#include <iostream>

WindowCallback::WindowCallback() : _engine(nullptr) { }
WindowCallback::~WindowCallback() { }

void WindowCallback::SetEngine(Engine* ptr) { _engine = ptr; }

void WindowCallback::OnCreate() {
  std::cout << "created" << std::endl;
}

void WindowCallback::OnDestroy() {
  std::cout << "destroyed" << std::endl;
  PostQuitMessage(0);
}

void WindowCallback::OnMouseClick(int x, int y, bool click) {
  if(!_engine) return;

  click ? _engine->getControlManager().leftMouseButtonDown( ) :
          _engine->getControlManager().leftMouseButtonUp( );

  std::cout << (click ? "click " : "release ") << x << " " << y << std::endl;
}

void WindowCallback::OnMouseMove(int x, int y) {
	float cx = RESOLUTION_X / 2;
	float cy = RESOLUTION_Y / 2;

  _engine->getCursor().setXY(x, y);

	if(ATTACH_CAMERA_TO_CURSOR) {
		int dx = (cx - x) / CAMERA_DISTANCE_RATE;
		int dy = (cy - y) / CAMERA_DISTANCE_RATE;

    _engine->getPhysicsManager().setCameraOffsetValue(dx, dy);

//		pointer->physicsMan.setCameraOffsetValue(dx, dy);
		//pointer->physicsMan.deposeGameObjectsFromCenter();
		//pointer->player.faceTo();
    _engine->getPlayer().faceTo(_engine->getCursor().getX() - dx, _engine->getCursor().getY() - dy);

	} else {
	  _engine->getPlayer().faceTo(x, y);
	}
}

void WindowCallback::OnKeyboard(int key, bool press) {
  if(!_engine) return;

  press ? _engine->getControlManager().keyDown( key ) :
          _engine->getControlManager().keyUp( key );

  std::cout << "key " << (press ? " pressed " : " released ") << key << std::endl;

  if( key == 27 ) {
    _engine->closeApp( );
  }
}

Window::Window() : _cb(nullptr) { }
Window::~Window() = default;

void Window::SetCallback( WindowCallback* ptr ) {
  _cb = ptr;
}

void Window::OnCreate() {
  _hDC = GetDC(_hWnd);
  _hMemDC = CreateCompatibleDC(_hDC);
  GetClientRect(_hWnd, &_clientRect);
  _hMemMap = CreateCompatibleBitmap(_hDC, _clientRect.right, _clientRect.bottom);
  SelectObject(_hMemDC, _hMemMap);

  _pen = CreatePen(PS_SOLID, 1, 0);
  _brush = CreateSolidBrush( RGB(255, 255, 255) );
  SelectObject(_hMemDC, _pen);
  SelectObject(_hMemDC, _brush);

  if(_cb) {
    _cb->OnCreate();
  }
}

void Window::OnDestroy() {
  if(_brush) {
    DeleteObject(_brush);
  }

  if(_pen) {
    DeleteObject(_pen);
  }

  if(_hMemMap) {
    DeleteObject(_hMemMap);
  }

  if(_hMemDC) {
    DeleteDC(_hMemDC);
  }

  if(_hDC) {
    ReleaseDC(_hWnd, _hDC);
  }

  if(_cb) {
    _cb->OnDestroy();
  }
}

void Window::OnMouseClick(int x, int y, bool click) {
  if(_cb) _cb->OnMouseClick(x, y, click);
}

void Window::OnMouseMove(int x, int y) {
  if(_cb) _cb->OnMouseMove(x, y);
}

void Window::OnKeyboard(int key, bool press) {
  if(_cb) _cb->OnKeyboard(key, press);
}
