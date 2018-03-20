#include <cassert>
#include <cstdbool>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <set>

#include <Windows.h>

#include "exports.h"
#include "game_id.h"
#include "gdi_hook.h"

struct wgl_context_t {
  HDC hdc;
  gdi_hook_t gdi_hook;
};

struct hdc_info_t {
  tagPIXELFORMATDESCRIPTOR pfd;
};

struct wgl_state_t {
  game_id_t game_id;
  std::mutex mutex;
  std::vector<tagPIXELFORMATDESCRIPTOR> pixel_formats;
  std::map<HDC, hdc_info_t> hdc_map;
  std::set<wgl_context_t*> contexts;
} wgl;

static thread_local wgl_context_t *context = nullptr;

HGLRC __stdcall wglCreateContext_imp(HDC hdc) {
  std::lock_guard<std::mutex> guard{wgl.mutex};
  // lookup the hdc to get the pixel format
  auto itt = wgl.hdc_map.find(hdc);
  if (itt == wgl.hdc_map.end()) {
    return nullptr;
  }
  hdc_info_t &info = itt->second;
  // create a new context
  context = new wgl_context_t;
  wgl.contexts.insert(context);
  // fill out context
  context->hdc = hdc;
  HWND hwnd = WindowFromDC(hdc);
  if (hwnd) {
    context->gdi_hook.hook(hwnd);
  }
  return HGLRC(context);
}

BOOL __stdcall wglSwapBuffers_imp(HDC a) {

  auto xorshift32 = []() {
    static uint32_t x = 12345;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
  };

  std::lock_guard<std::mutex> guard{wgl.mutex};
  if (context) {
    gdi_hook_t::lock_info_t lock;
    if (context->gdi_hook.lock(&lock)) {
      for (uint32_t i = 0; i < lock.width * lock.height; ++i) {
          lock.pixels[i] = xorshift32();
      }
    }
    context->gdi_hook.invalidate();
    return TRUE;
  }
  return FALSE;
}

BOOL __stdcall wglDeleteContext_imp(HGLRC a) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  if (context) {
    // erase the context
    auto itt = wgl.contexts.find((wgl_context_t*)a);
    delete *itt;
    wgl.contexts.erase(itt);

    context = nullptr;
  }
  return TRUE;
}

HGLRC __stdcall wglGetCurrentContext_imp(VOID) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  return (HGLRC)context;
}

HDC __stdcall wglGetCurrentDC_imp(VOID) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  return context ? context->hdc : nullptr;
}

PROC __stdcall wglGetProcAddress_imp(LPCSTR a) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  return 0;
}

BOOL __stdcall wglMakeCurrent_imp(HDC a, HGLRC b) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  return FALSE;
}

// The SetPixelFormat function sets the pixel format of the specified device
// context to the format specified by the iPixelFormat index.
//
// If the function succeeds, the return value is TRUE.
BOOL __stdcall wglSetPixelFormat_imp(HDC hdc,
                                 int iPixelFormat,
                                 const struct PIXELFORMATDESCRIPTOR *ppfd)
{
  std::lock_guard<std::mutex> guard{wgl.mutex};
  if (iPixelFormat <= 0 || size_t(iPixelFormat) > wgl.pixel_formats.size())
    return FALSE;
  // lookup the requested format
  const tagPIXELFORMATDESCRIPTOR &pfmt = wgl.pixel_formats[iPixelFormat - 1];

  // have we seen this hdc before
  hdc_info_t *info = nullptr;
  auto itt = wgl.hdc_map.find(hdc);
  if (itt == wgl.hdc_map.end()) {
    wgl.hdc_map[hdc] = hdc_info_t{};
    info = &wgl.hdc_map.at(hdc);
  }
  else {
    info = &itt->second;
  }
  assert(info);

  // map pixel format to this hdc
  info->pfd = pfmt;

  // pretend we set the pixel format
  return TRUE;
}

// The ChoosePixelFormat function attempts to match an appropriate pixel format
// supported by a device context to a given pixel format specification.
// 
// If the function succeeds, the return value is a pixel format index
// (one-based) that is the closest match to the given pixel format descriptor.
int __stdcall wglChoosePixelFormat_imp(HDC hdc, const PPIXELFORMATDESCRIPTOR ppfd)
{
  std::lock_guard<std::mutex> guard{wgl.mutex};
  if (!ppfd)
    return 0;
  // add pixel format to our list of requested formats
  wgl.pixel_formats.push_back(*ppfd);
  return wgl.pixel_formats.size();
}

BOOL __stdcall wglCopyContext_imp(HGLRC a, HGLRC b, UINT c) {
  __debugbreak();
  std::lock_guard<std::mutex> guard{wgl.mutex};
  return FALSE;
}

BOOL __stdcall wglShareLists_imp(HGLRC a, HGLRC b) {
  __debugbreak();
  return FALSE;
}

HGLRC __stdcall wglCreateLayerContext_imp(HDC a, int b) {
  __debugbreak();
  return 0;
}

BOOL __stdcall wglUseFontBitmapsA_imp(HDC a, DWORD b, DWORD c, DWORD d) {
  __debugbreak();
  return FALSE;
}

BOOL __stdcall wglUseFontBitmapsW_imp(HDC a, DWORD b, DWORD c, DWORD d) {
  __debugbreak();
  return FALSE;
}

BOOL __stdcall wglUseFontOutlinesA_imp(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e,
                                  FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
  __debugbreak();
  return FALSE;
}

BOOL __stdcall wglUseFontOutlinesW_imp(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e,
                                  FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
  __debugbreak();
  return FALSE;
}

BOOL __stdcall wglDescribeLayerPlane_imp(HDC a, int b, int c, UINT d,
                                    LPLAYERPLANEDESCRIPTOR e) {
  __debugbreak();
  return FALSE;
}

int __stdcall wglSetLayerPaletteEntries_imp(HDC a, int b, int c, int d,
                                       CONST COLORREF *e) {
  __debugbreak();
  return 0;
}

int __stdcall wglGetLayerPaletteEntries_imp(HDC a, int b, int c, int d,
                                       COLORREF *e) {
  __debugbreak();
  return 0;
}

BOOL __stdcall wglRealizeLayerPalette_imp(HDC a, int b, BOOL c) {
  return FALSE;
}

BOOL __stdcall wglSwapLayerBuffers_imp(HDC a, UINT b) {
  __debugbreak();
  return FALSE;
}

DWORD __stdcall wglSwapMultipleBuffers_imp(UINT a, CONST WGLSWAP *b) {
  __debugbreak();
  return 0;
}
