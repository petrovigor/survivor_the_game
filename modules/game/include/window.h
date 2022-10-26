#pragma once

#include "base_window.h"
#include <memory>

class Engine;

class WindowCallback {
public:
  WindowCallback();
  ~WindowCallback();

  void SetEngine(Engine* ptr);
  void OnCreate();
  void OnDestroy();
  void OnMouseClick(int x, int y, bool click);
  void OnMouseMove(int x, int y);
  void OnKeyboard(int key, bool press);

protected:
  Engine* _engine;

};

class Window final : public BaseWindow {
private:
  friend class Engine;

public:
  Window();
  ~Window();

  void SetCallback(WindowCallback* ptr);

  void OnCreate() override;
  void OnDestroy() override;
  void OnMouseClick(int x, int y, bool click) override;
  void OnMouseMove(int x, int y) override;
  void OnKeyboard(int key, bool press) override;

  HDC const& getDC() const noexcept { return _hDC; }
  HDC const& getMemDC() const noexcept { return _hMemDC; }
  HBITMAP const& getMemMap() const noexcept { return _hMemMap; }
  HBRUSH const& getBrush() const noexcept { return _brush; }
  HPEN const& getPen() const noexcept { return _pen; }
  RECT getClientRect() const noexcept { return _clientRect; }

private:
  WindowCallback* _cb;
  //std::unique_ptr<HDC>             _hDC;
  //std::unique_ptr<HDC>             _hMemDC;
  //std::unique_ptr<HBITMAP>         _hMemMap;
  //std::unique_ptr<HBRUSH>          _brush;
  //std::unique_ptr<HPEN>            _pen;
  HDC             _hDC;
  HDC             _hMemDC;
  HBITMAP         _hMemMap;
  HBRUSH          _brush;
  HPEN            _pen;
  RECT            _clientRect;

};
