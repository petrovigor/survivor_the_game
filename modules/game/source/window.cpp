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
  std::cout << (click ? "click " : "release ") << x << " " << y << std::endl;
}

void WindowCallback::OnMouseMove(int x, int y) {
  std::cout << "move " << x << " " << y << std::endl;
}

void WindowCallback::OnKeyboard(int key, bool press) {
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
  if(_cb) _cb->OnCreate();
}

void Window::OnDestroy() {
  if(_cb) _cb->OnDestroy();
}

void Window::OnMouseClick(int x, int y, bool click) {
  if(_cb) _cb->OnMouseClick(x,y,click);
}

void Window::OnMouseMove(int x, int y) {
  if(_cb) _cb->OnMouseMove(x,y);
}

void Window::OnKeyboard(int key, bool press) {
  if(_cb) _cb->OnKeyboard(key,press);
}
