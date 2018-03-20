#pragma once

#include <cassert>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct gdi_hook_t {

  struct lock_info_t {
    uint32_t *pixels;
    uint32_t width, pitch;
    uint32_t height;
  };

  gdi_hook_t();

  ~gdi_hook_t();

  bool hook(HWND hwnd);

  bool invalidate();

  bool lock(lock_info_t *info);

  LRESULT CALLBACK handler(HWND hwnd, uint32_t msg, WPARAM w, LPARAM l);

protected:

  // screen buffer info
  struct {
    BITMAPINFO bmp;
    std::unique_ptr<uint32_t[]> data;
  } screen;

  WNDPROC origProc;
  HWND handle;

  // repaint the current window (WM_PAINT)
  LRESULT redraw(HWND hwnd);

  // create a back buffer of a specific size
  bool screenCreate(HWND hwnd);
};
