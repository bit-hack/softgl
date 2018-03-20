#include <mutex>
#include <map>

#include "gdi_hook.h"

namespace {
struct hwnd_map_t {
  std::mutex mutex;
  std::map<HWND, gdi_hook_t *> hook;
};

hwnd_map_t g_hwnd_map;

LRESULT CALLBACK trampoline(HWND hwnd, uint32_t msg, WPARAM w, LPARAM l) {
  gdi_hook_t *self = nullptr;
  {
    std::lock_guard<std::mutex> guard(g_hwnd_map.mutex);
    self = g_hwnd_map.hook.at(hwnd);
  }
  return self ? self->handler(hwnd, msg, w, l)
              : DefWindowProcA(hwnd, msg, w, l);
}
} // namespace

gdi_hook_t::gdi_hook_t() : screen{} {}

gdi_hook_t::~gdi_hook_t() {
  // remove this from the map
  std::lock_guard<std::mutex> guard(g_hwnd_map.mutex);
  auto &hook = g_hwnd_map.hook;
  for (auto itt = hook.begin(); itt != hook.end();) {
    if (itt->second == this) {
      itt = hook.erase(itt);
    } else {
      ++itt;
    }
  }
}

bool gdi_hook_t::hook(HWND hwnd) {
  // add this hwnd to the hwnd map
  {
    std::lock_guard<std::mutex> guard(g_hwnd_map.mutex);
    g_hwnd_map.hook[hwnd] = this;
  }
  handle = hwnd;
  // create screen buffer
  screenCreate(hwnd);
  // get all the orig window data
  origProc = (WNDPROC)GetWindowLongPtrA(hwnd, GWL_WNDPROC);
  if (!origProc) {
    return false;
  }
  // set all of the window data
  SetWindowLongPtrA(hwnd, GWL_WNDPROC, (LONG)trampoline);
  return true;
}

bool gdi_hook_t::invalidate() {
  // invalidate entire window
  InvalidateRect(handle, NULL, FALSE);
  return UpdateWindow(handle) == TRUE;
}

bool gdi_hook_t::lock(lock_info_t *info) {
  assert(info);
  info->pixels = screen.data.get();
  info->width = screen.bmp.bmiHeader.biWidth;
  info->height = screen.bmp.bmiHeader.biHeight;
  info->pitch = screen.bmp.bmiHeader.biWidth;
  return info->pixels != NULL;
}

LRESULT CALLBACK gdi_hook_t::handler(HWND hwnd, uint32_t msg, WPARAM w,
                                     LPARAM l) {
  if (msg == WM_PAINT) {
    return redraw(hwnd);
  } else {
    return origProc(hwnd, msg, w, l);
  }
}

// repaint the current window (WM_PAINT)
LRESULT gdi_hook_t::redraw(HWND hwnd) {
  if (!screen.data) {
    // no screen; hand back to default handler
    return DefWindowProcA(hwnd, WM_PAINT, 0, 0);
  }
  // blit buffer to screen
  HDC dc = GetDC(hwnd);
  if (dc == NULL) {
    return 0;
  }
  const BITMAPINFOHEADER &bih = screen.bmp.bmiHeader;
  // do the bit blit
  const int r =
      StretchDIBits(dc,
                    // src
                    0, 0, bih.biWidth, bih.biHeight,
                    // dst
                    0, 0, bih.biWidth, bih.biHeight, screen.data.get(),
                    &(screen.bmp), DIB_RGB_COLORS, SRCCOPY);
  if (r == 0) {
    return 0;
  }
  // finished WM_PAINT
  ReleaseDC(hwnd, dc);
  ValidateRect(hwnd, NULL);
  return 0;
}

// create a back buffer of a specific size
bool gdi_hook_t::screenCreate(HWND hwnd) {
  RECT rect;
  GetClientRect(hwnd, &rect);
  const uint32_t w = rect.right;
  const uint32_t h = rect.bottom;
  // create screen data
  screen.data = std::make_unique<uint32_t[]>(w * h);
  assert(screen.data);
  // create bitmap info
  ZeroMemory(&screen.bmp, sizeof(BITMAPINFO));
  BITMAPINFOHEADER &b = screen.bmp.bmiHeader;
  b.biSize = sizeof(BITMAPINFOHEADER);
  b.biBitCount = 32;
  b.biWidth = w;
  b.biHeight = h;
  b.biPlanes = 1;
  b.biCompression = BI_RGB;
  // success
  return true;
}
