#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <mutex>
#include <set>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "context.h"

#define GdiHook gdi_hook_t::inst()

struct gdi_hook_t {

  bool hook(gl_context_t &cxt);
  bool unhook(gl_context_t &cxt);

  bool invalidate(HWND hwnd);

  LRESULT CALLBACK dispatch(HWND hwnd, uint32_t msg, WPARAM w, LPARAM l);

  static gdi_hook_t &inst() {
    static gdi_hook_t self;
    return self;
  }

protected:
  // context map
  std::map<HWND, gl_context_t *> context;

  // screen buffer info
  std::map<HWND, BITMAPINFO> bmpInfoMap;
  std::map<HWND, WNDPROC> procMap;
  std::set<HWND> hwndMap;

  //  std::mutex mutex;

  // repaint the current window (WM_PAINT)
  LRESULT redraw(gl_context_t &cxt);

  // prepare a back buffer of a specific size
  bool screenPrepare(gl_context_t &cxt);
};
