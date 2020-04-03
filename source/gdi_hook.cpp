#include <mutex>
#include <map>

#include "context.h"
#include "gdi_hook.h"
#include "log.h"


namespace {
LRESULT CALLBACK trampoline(HWND hwnd, uint32_t msg, WPARAM w, LPARAM l) {
  return GdiHook.dispatch(hwnd, msg, w, l);
}
} // namespace

bool gdi_hook_t::unhook(gl_context_t &cxt) {
  log_t::printf("Unhooking context %p\n", &cxt);
  {
    auto itt = procMap.find(cxt.window.getHwnd());
    if (itt != procMap.end()) {
      WNDPROC proc = procMap.at(cxt.window.getHwnd());
      SetWindowLongPtrA(cxt.window.getHwnd(), GWL_WNDPROC, (LONG)proc);
      procMap.erase(itt);
      log_t::printf("Context was unhooked %p\n", &cxt);
    }
  }
  {
    for (auto itt = context.begin(); itt != context.end();) {
      if (itt->second == &cxt) {
        itt = context.erase(itt);
      }
      else {
        ++itt;
      }
    }
  }
  return true;
}

bool gdi_hook_t::hook(gl_context_t &cxt) {

  log_t::printf("Hooking context %p\n", &cxt);

  // check if context already hooked
  for (const auto itt : context) {
    if (&cxt == itt.second) {
      // context already hooked
      return true;
    }
  }

  // save the context
  HWND hwnd = cxt.window.getHwnd();
  context.emplace(hwnd, &cxt);

  // save window handle
  hwndMap.insert(hwnd);
  // create screen buffer
  screenPrepare(cxt);
  // get all the orig window data
  WNDPROC proc = (WNDPROC)GetWindowLongPtrA(hwnd, GWL_WNDPROC);
  if (!proc)
    return false;
  // insert into the proc map
  procMap.emplace(hwnd, proc);
  // hook the window proc
  SetWindowLongPtrA(hwnd, GWL_WNDPROC, (LONG)trampoline);
  return true;
}

bool gdi_hook_t::invalidate(HWND hwnd) {
  // invalidate entire window
  InvalidateRect(hwnd, NULL, FALSE);
  return UpdateWindow(hwnd) == TRUE;
}

// dispatch window messages to the right wndproc
LRESULT CALLBACK gdi_hook_t::dispatch(HWND hwnd, uint32_t msg, WPARAM w,
                                      LPARAM l) {

  auto itt = procMap.find(hwnd);
  if (itt == procMap.end())
    return DefWindowProcA(hwnd, msg, w, l);

  gl_context_t *cxt = context.at(hwnd);

  switch (msg) {
  case WM_PAINT:
    return redraw(*cxt);
  default: {
    // note: Some window procs are not valid pointers but rather handles
    //       and must be called via a proxy function.  This is the case
    //       for unreal tournament 99.
    auto proc = itt->second;
    return CallWindowProcA(proc, hwnd, msg, w, l);
  }
  }
}

// repaint the current window (WM_PAINT)
LRESULT gdi_hook_t::redraw(gl_context_t &cxt) {
//  std::lock_guard<std::mutex> guard(mutex);

  HWND hwnd = cxt.window.getHwnd();

  // blit buffer to screen
  HDC dc = GetDC(hwnd);
  if (dc == NULL)
    return 0;

  // get the frame from the context
  const auto &buffer = cxt.buffer;

  auto bmpItt = bmpInfoMap.find(hwnd);
  if (bmpItt == bmpInfoMap.end())
    return 0;

  // grab bitmap info header
  BITMAPINFOHEADER &bih = bmpItt->second.bmiHeader;
  bih.biWidth = buffer.width();
  bih.biHeight = buffer.height();

  // do the bit blit
  const int r =
      StretchDIBits(dc,
                    // src
                    0, 0, int(buffer.width()), int(buffer.height()),
                    // dst
                    0, 0, bih.biWidth, bih.biHeight,
                    // pixels
                    buffer.pixels(),
                    &(bmpItt->second),
                    DIB_RGB_COLORS, SRCCOPY);
  if (r == 0)
    return 0;

  // finished WM_PAINT
  ReleaseDC(hwnd, dc);
  ValidateRect(hwnd, NULL);
  return 0;
}

// create a back buffer of a specific size
bool gdi_hook_t::screenPrepare(gl_context_t &cxt) {
//  std::lock_guard<std::mutex> guard(mutex);

  HWND hwnd = cxt.window.getHwnd();

  // get the screen size
  RECT rect = {0};
  if (!GetClientRect(hwnd, &rect)) {
    DEBUG_BREAK;
  }
  const uint32_t w = rect.right;
  const uint32_t h = rect.bottom;

  bmpInfoMap.emplace(hwnd, BITMAPINFO{});
  BITMAPINFO &bmpInfo = bmpInfoMap.at(hwnd);

  // create preliminary bitmap info
  ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
  BITMAPINFOHEADER &b = bmpInfo.bmiHeader;
  b.biSize = sizeof(BITMAPINFOHEADER);
  b.biBitCount = 32;
  b.biWidth = w;
  b.biHeight = h;
  b.biPlanes = 1;
  b.biCompression = BI_RGB;

  // tell the context to resize
  cxt.buffer.resize(w, h);

  // success
  return true;
}
