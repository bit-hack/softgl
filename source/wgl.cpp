#include <cassert>
#include <cstdbool>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <set>

#include <Windows.h>

#include "wgl.h"
#include "game_id.h"
#include "gdi_hook.h"

struct hdc_info_t {
  tagPIXELFORMATDESCRIPTOR pfd;
};

struct wgl_state_t {
  game_id_t gameId;
  std::vector<tagPIXELFORMATDESCRIPTOR> pixelFormats;
  std::map<HDC, hdc_info_t> hdcMap;
  std::set<gl_context_t*> contexts;
} wgl;

static thread_local gl_context_t *gl_context = nullptr;

gl_context_t *getContext() {
  return gl_context;
}

HGLRC __stdcall wglCreateContext_imp(HDC hdc) {
  // lookup the hdc to get the pixel format
  auto itt = wgl.hdcMap.find(hdc);
  if (itt == wgl.hdcMap.end())
    return nullptr;

  const hdc_info_t &info = itt->second;
  HWND hwnd = WindowFromDC(hdc);
  // create a new context
  gl_context_t *cxt = new gl_context_t(hwnd, hdc);
  // insert into the context map
  wgl.contexts.insert(cxt);
  // fill out context
  // XXX: Move this to context
  GdiHook.hook(*cxt);

  return HGLRC(cxt);
}

BOOL __stdcall wglSwapBuffers_imp(HDC a) {
  if (!gl_context)
    return FALSE;
  GdiHook.invalidate(gl_context->getHwnd());
  return TRUE;
}

BOOL __stdcall wglDeleteContext_imp(HGLRC a) {
  if (!a) {
    return false;
  }
  gl_context_t *cxt = (gl_context_t *)a;
  if (gl_context == cxt) {
    // this is the current context
    gl_context = nullptr;
  }
  // unhook this window
  GdiHook.unhook(*cxt);
  // erase the context
  auto itt = wgl.contexts.find(cxt);
  delete *itt;
  wgl.contexts.erase(itt);
  return TRUE;
}

HGLRC __stdcall wglGetCurrentContext_imp(VOID) {
  __debugbreak();
  return (HGLRC)gl_context;
}

HDC __stdcall wglGetCurrentDC_imp(VOID) {
  __debugbreak();
  return gl_context ? gl_context->getHdc() : nullptr;
}

PROC __stdcall wglGetProcAddress_imp(LPCSTR a) {
  PROC proc = (PROC)GetProcAddress(GetModuleHandleA("opengl32.dll"), a);
  return proc;
}

BOOL __stdcall wglMakeCurrent_imp(HDC a, HGLRC b) {
  gl_context_t *cxt = (gl_context_t*)b;
  if (b != nullptr) {
    // make the global context
    gl_context = cxt;
    if (cxt->getHdc() != a) {
      __debugbreak();
    }
  }
  return TRUE;
}

BOOL __stdcall wglSetPixelFormat_imp(HDC hdc,
                                 int iPixelFormat,
                                 const struct PIXELFORMATDESCRIPTOR *ppfd)
{
  if (iPixelFormat <= 0 || size_t(iPixelFormat) > wgl.pixelFormats.size())
    return FALSE;
  // lookup the requested format
  const tagPIXELFORMATDESCRIPTOR &pfmt = wgl.pixelFormats[iPixelFormat - 1];

  // have we seen this hdc before
  hdc_info_t *info = nullptr;
  auto itt = wgl.hdcMap.find(hdc);
  if (itt == wgl.hdcMap.end()) {
    wgl.hdcMap[hdc] = hdc_info_t{};
    info = &wgl.hdcMap.at(hdc);
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

int __stdcall wglChoosePixelFormat_imp(HDC hdc, const PPIXELFORMATDESCRIPTOR ppfd)
{
  if (!ppfd)
    return 0;
  // add pixel format to our list of requested formats
  wgl.pixelFormats.push_back(*ppfd);
  return wgl.pixelFormats.size();
}

BOOL __stdcall wglCopyContext_imp(HGLRC a, HGLRC b, UINT c) {
  __debugbreak();
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

const char *wglGetExtensionsStringARB_imp(HDC hdc) {
  return "";
}
