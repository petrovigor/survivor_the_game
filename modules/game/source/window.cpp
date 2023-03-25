#include "window.h"
#include "engine.h"
#include "controller.h"
#include "point.h"
#include "game_object.h"

#include <iostream>
#include <Windows.h>

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

  auto& keyboard = Controller::instance();

  click ? keyboard.leftMouseButtonDown( ) :
          keyboard.leftMouseButtonUp( );

  auto& phys = PhysicsManager::instance();
  phys.left_mouse_click();

  //std::cout << (click ? "click " : "release ") << x << " " << y << std::endl;
}

void WindowCallback::OnMouseMove(int x, int y) {
  const screenPoint screenPoint { x, y };

  auto& phys = PhysicsManager::instance();

  const float view_distance = 1.0f;
  const float cx = 800.f / 2.f;
  const float cy = 600.f / 2.f;
  const float dx = (cx - x) / view_distance;
  const float dy = (cy - y) / view_distance;
  phys.setCameraOffset(dx, dy);

  const worldPoint playerPos = phys.getPlayerPos();
  const worldPoint wp = phys.screenToWorld(screenPoint, playerPos, 800, 600);

  //std::cout << "Screen x = " << screenPoint.p.x << " / y = " << screenPoint.p.y << " Player x " << playerPos.p.x << " y = " << playerPos.p.y << " World x " << wp.p.x << " y = " << wp.p.y << std::endl;
  phys.moveMouseWorldSpace(wp);
}

void WindowCallback::OnKeyboard(int key, bool press) {
  if(!_engine) return;

  auto& keyboard = Controller::instance();

  press ? keyboard.keyDown( key ) :
          keyboard.keyUp( key );

  //std::cout << "key " << (press ? " pressed " : " released ") << key << std::endl;

  if( key == 27 ) {
    _engine->closeApp( );
  }
}

Window::Window() : _cb(nullptr) { }
Window::~Window() = default;

void Window::SetCallback( WindowCallback* ptr ) {
  _cb = ptr;
}

// struct GDIRelease {
//   typedef HDC *pointer;

//   void operator()(HDC *p) {
//     ReleaseDC(0, p);
//   }
// };

        //struct ReleaseDCFunctor {
        //  using my_hdc = void*;
        //  void operator()(my_hdc hdc) {
        //    ReleaseDC(0, static_cast<HDC>(hdc));
        //  }
        //};

//using Gdi_Smart_Pointer = std::unique_ptr<HDC, ReleaseDCFunctor>();

// template <typename GDIObj>
// void ReleaseHDC(GDIObj obj_ptr) {
//   std::cout << "Releasing DC: " << ReleaseDC(0, static_cast<GDIObj>(obj_ptr)) << std::endl;
// }



void Window::OnCreate() {

  _hDC = GetDC(_hWnd);

  auto my = GetDC(0);


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
