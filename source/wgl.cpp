#include <cassert>
#include <cstdbool>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <set>

#include "windows.h"

#include "common.h"
#include "wgl.h"
#include "game_id.h"
#include "gdi_hook.h"
#include "log.h"


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

BOOL __stdcall wglSwapBuffers_imp(HDC a) {
  if (!gl_context)
    return FALSE;
  Context->on_flush();
  if (Context->profile) {
    Context->profile->on_end_frame();
  }
  GdiHook.invalidate(gl_context->window.getHwnd());
  Context->buffer.clear_colour(0x202020);
  Context->buffer.clear_depth();
  return TRUE;
}

HGLRC __stdcall wglCreateContext_imp(HDC hdc) {
  log_t::printf("%s(%p)\n", __FUNCTION__, (void*)(hdc));

  // lookup the hdc to get the pixel format
  auto itt = wgl.hdcMap.find(hdc);
  if (itt == wgl.hdcMap.end())
    return nullptr;

  const hdc_info_t &info = itt->second;
  HWND hwnd = WindowFromDC(hdc);
  // create a new context
  gl_context_t *cxt = new gl_context_t(hwnd, hdc);
  if (!cxt->on_create()) {
    //XXX: bad news
    return nullptr;
  }
  log_t::printf("new context created -> %p\n", (void*)cxt);;
  // insert into the context map
  wgl.contexts.insert(cxt);
  return HGLRC(cxt);
}

BOOL __stdcall wglDeleteContext_imp(HGLRC a) {
  log_t::printf("%s(%p)\n", __FUNCTION__, (void*)(a));

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
  if (itt != wgl.contexts.end()) {
    log_t::printf("context deleted -> %p\n", (void*)*itt);
    delete *itt;
    wgl.contexts.erase(itt);
  }
  return TRUE;
}

BOOL __stdcall wglMakeCurrent_imp(HDC a, HGLRC b) {
  log_t::printf("%s(%p, %p)\n", __FUNCTION__, (void*)a, (void*)b);

  gl_context_t *cxt = (gl_context_t*)b;
  if (b != nullptr) {
    // make the global context
    gl_context = cxt;
    if (cxt->window.getHdc() != a) {
      __debugbreak();
    }
    gl_context->on_make_current();
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

int __stdcall wglDescribePixelFormat_imp(HDC hdc, int iPixelFormat, UINT nBytes,
                                         LPPIXELFORMATDESCRIPTOR ppfd) {
  if (iPixelFormat <= 0 || iPixelFormat > int(wgl.pixelFormats.size())) {
    return 0;
  }
  if (ppfd) {
    const auto &fmt = wgl.pixelFormats.at(iPixelFormat-1);
    nBytes = std::min<size_t>(nBytes, sizeof(tagPIXELFORMATDESCRIPTOR));
    memcpy(ppfd, &fmt, nBytes);
    ppfd->nSize = sizeof(*ppfd);
    ppfd->nVersion = 1;
    if (!ppfd->dwFlags)
      ppfd->dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    ppfd->iPixelType = PFD_TYPE_RGBA;
#if 1
    if (!ppfd->cColorBits)
      ppfd->cColorBits = 32; // some games may want 24 here
    if (!ppfd->cDepthBits)
      ppfd->cDepthBits = 24;
#endif
    ppfd->cAccumBits = 0;
    ppfd->cAccumAlphaBits = 8;
    ppfd->cStencilBits = 8;
    ppfd->cRedBits = 8;
    ppfd->cRedShift = 0;
    ppfd->cGreenBits = 8;
    ppfd->cGreenShift = 8;
    ppfd->cBlueBits = 8;
    ppfd->cBlueShift = 16;
    ppfd->cAlphaBits = 8;
    ppfd->cAlphaShift = 24;
    if (!ppfd->cStencilBits)
      ppfd->cStencilBits = 8;
    if (!ppfd->cAuxBuffers)
      ppfd->cAuxBuffers = 4;
    if (!ppfd->iPixelType)
      ppfd->iPixelType = PFD_TYPE_RGBA;
  }
  return wgl.pixelFormats.size();
}

HDC __stdcall wglGetCurrentDC_imp(VOID) {
  return gl_context ? gl_context->window.getHdc() : nullptr;
}

PROC __stdcall wglGetProcAddress_imp(LPCSTR a) {
  PROC proc = (PROC)GetProcAddress(GetModuleHandleA("opengl32.dll"), a);
  return proc;
}

HGLRC __stdcall wglGetCurrentContext_imp(VOID) {
  DEBUG_BREAK;
  return (HGLRC)gl_context;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 

BOOL __stdcall wglCopyContext_imp(HGLRC a, HGLRC b, UINT c) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglShareLists_imp(HGLRC a, HGLRC b) {
  // note: UnrealGold expects this to return true
  return TRUE;
}

HGLRC __stdcall wglCreateLayerContext_imp(HDC a, int b) {
  DEBUG_BREAK;
  return 0;
}

BOOL __stdcall wglUseFontBitmapsA_imp(HDC a, DWORD b, DWORD c, DWORD d) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglUseFontBitmapsW_imp(HDC a, DWORD b, DWORD c, DWORD d) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglUseFontOutlinesA_imp(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e,
                                  FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglUseFontOutlinesW_imp(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e,
                                  FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglDescribeLayerPlane_imp(HDC a, int b, int c, UINT d,
                                    LPLAYERPLANEDESCRIPTOR e) {
  DEBUG_BREAK;
  return FALSE;
}

int __stdcall wglSetLayerPaletteEntries_imp(HDC a, int b, int c, int d,
                                       CONST COLORREF *e) {
  DEBUG_BREAK;
  return 0;
}

int __stdcall wglGetLayerPaletteEntries_imp(HDC a, int b, int c, int d,
                                       COLORREF *e) {
  DEBUG_BREAK;
  return 0;
}

BOOL __stdcall wglRealizeLayerPalette_imp(HDC a, int b, BOOL c) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglSwapLayerBuffers_imp(HDC a, UINT b) {
  DEBUG_BREAK;
  return FALSE;
}

DWORD __stdcall wglSwapMultipleBuffers_imp(UINT a, CONST WGLSWAP *b) {
  DEBUG_BREAK;
  return 0;
}

const char * __stdcall wglGetExtensionsStringARB_imp(HDC hdc) {
  return "";
}
