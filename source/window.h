#pragma once
#include "windows.h"


struct window_manager_t {

  window_manager_t(HWND hwnd, HDC hdc)
    : _hwnd(hwnd)
    , _hdc(hdc)
  {
  }

  uint32_t width() const {
    RECT r;
    GetClientRect(_hwnd, &r);
    return r.right;
  }

  uint32_t height() const {
    RECT r;
    GetClientRect(_hwnd, &r);
    return r.bottom;
  }

  // get window data
  HWND getHwnd() const { return _hwnd; }
  HDC getHdc() const { return _hdc; }

protected:
  // window data info
  const HWND _hwnd;
  const HDC _hdc;
};
