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
#include "game_id.h"


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
#if 0
  log_t::printf("%s(%p)\n", __func__, (void*)a);
#endif

  if (!gl_context)
    return FALSE;
  Context->on_flush();
  if (Context->profile) {
    Context->profile->on_end_frame();
  }
  if (Context->raster.inst) {
    Context->raster.inst->present();
  }

  if (Context->user_cmds.screenshot) {
    Context->buffer.save_bmp();
    Context->user_cmds.screenshot = false;
  }

  GdiHook.invalidate(gl_context->window.getHwnd());

  switch (getGameId()) {
  case e_ut99_goty:
  case e_half_life_of_demo:
    if (Context->raster.inst) {
      Context->raster.inst->framebuffer_clear(false, true, false, 0x202020, 10000.f, 0);
    }
  }

  return TRUE;
}

HGLRC __stdcall wglCreateContext_imp(HDC hdc) {
  log_t::printf("%s(%p)\n", __func__, (void*)hdc);

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
  log_t::printf("%s(%p)\n", __func__, (void *)a);

  if (!a) {
    return false;
  }
  gl_context_t *cxt = (gl_context_t *)a;

  // erase the context
  auto itt = wgl.contexts.find(cxt);
  if (itt != wgl.contexts.end()) {

    if (gl_context == cxt) {
      // this is the current context
      gl_context = nullptr;
    }
    cxt->on_destroy();
    // unhook this window
    GdiHook.unhook(*cxt);

    log_t::printf("context deleted -> %p\n", (void *)*itt);
    delete *itt;
    wgl.contexts.erase(itt);
  }
  return TRUE;
}

BOOL __stdcall wglMakeCurrent_imp(HDC a, HGLRC b) {
  log_t::printf("%s(%p, %p)\n", __func__, (void*)a, (void*)b);

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
  log_t::printf("%s(%p, %d, %p)\n", __func__, (void*)hdc, iPixelFormat, (void*)ppfd);

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

void dump_pixel_format(const PPIXELFORMATDESCRIPTOR ppfd) {
  log_t::printf("  nSize          : %d\n", (int) ppfd->nSize            );
  log_t::printf("  nVersion       : %d\n", (int) ppfd->nVersion         );
  log_t::printf("  dwFlags        : %d\n", (int) ppfd->dwFlags          );
  log_t::printf("  iPixelType     : %d\n", (int) ppfd->iPixelType       );
  log_t::printf("  cColorBits     : %d\n", (int) ppfd->cColorBits       );
  log_t::printf("  cRedBits       : %d\n", (int) ppfd->cRedBits         );
  log_t::printf("  cRedShift      : %d\n", (int) ppfd->cRedShift        );
  log_t::printf("  cGreenBits     : %d\n", (int) ppfd->cGreenBits       );
  log_t::printf("  cGreenShift    : %d\n", (int) ppfd->cGreenShift      );
  log_t::printf("  cBlueBits      : %d\n", (int) ppfd->cBlueBits        );
  log_t::printf("  cBlueShift     : %d\n", (int) ppfd->cBlueShift       );
  log_t::printf("  cAlphaBits     : %d\n", (int) ppfd->cAlphaBits       );
  log_t::printf("  cAlphaShift    : %d\n", (int) ppfd->cAlphaShift      );
  log_t::printf("  cAccumBits     : %d\n", (int) ppfd->cAccumBits       );
  log_t::printf("  cAccumRedBits  : %d\n", (int) ppfd->cAccumRedBits    );
  log_t::printf("  cAccumGreenBits: %d\n", (int) ppfd->cAccumGreenBits  );
  log_t::printf("  cAccumBlueBits : %d\n", (int) ppfd->cAccumBlueBits   );
  log_t::printf("  cAccumAlphaBits: %d\n", (int) ppfd->cAccumAlphaBits  );
  log_t::printf("  cDepthBits     : %d\n", (int) ppfd->cDepthBits       );
  log_t::printf("  cStencilBits   : %d\n", (int) ppfd->cStencilBits     );
  log_t::printf("  cAuxBuffers    : %d\n", (int) ppfd->cAuxBuffers      );
  log_t::printf("  iLayerType     : %d\n", (int) ppfd->iLayerType       );
  log_t::printf("  bReserved      : %d\n", (int) ppfd->bReserved        );
  log_t::printf("  dwLayerMask    : %d\n", (int) ppfd->dwLayerMask      );
  log_t::printf("  dwVisibleMask  : %d\n", (int) ppfd->dwVisibleMask    );
  log_t::printf("  dwDamageMask   : %d\n", (int) ppfd->dwDamageMask     );
}

int __stdcall wglChoosePixelFormat_imp(HDC hdc, const PPIXELFORMATDESCRIPTOR ppfd)
{
  log_t::printf("%s(%p)\n", __func__, (void*)ppfd);
  if (!ppfd)
    return 0;
  dump_pixel_format(ppfd);
  // add pixel format to our list of requested formats
  wgl.pixelFormats.push_back(*ppfd);
  return wgl.pixelFormats.size();
}

int __stdcall wglDescribePixelFormat_imp(HDC hdc,
                                         int iPixelFormat,
                                         UINT nBytes,
                                         LPPIXELFORMATDESCRIPTOR ppfd) {
  log_t::printf("%s(%p, %d, %d, %p)\n", __func__, (void*)hdc, iPixelFormat, (int)nBytes, (void*)ppfd);

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
  log_t::printf("%s()\n", __func__);
  return gl_context ? gl_context->window.getHdc() : nullptr;
}

PROC __stdcall wglGetProcAddress_imp(LPCSTR a) {
  log_t::printf("%s(%s)\n", __func__, (char*)a);
  PROC proc = (PROC)GetProcAddress(GetModuleHandleA("opengl32.dll"), a);
  if (!proc) {
    log_t::printf("  not found!");
  }
  return proc;
}

HGLRC __stdcall wglGetCurrentContext_imp(VOID) {
  log_t::printf("%s()\n", __func__);
  DEBUG_BREAK;
  return (HGLRC)gl_context;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 

BOOL __stdcall wglCopyContext_imp(HGLRC a, HGLRC b, UINT c) {
  DEBUG_BREAK;
  return FALSE;
}

BOOL __stdcall wglShareLists_imp(HGLRC a, HGLRC b) {
  log_t::printf("%s()\n");
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
  log_t::printf("%s(%p)\n", __func__, hdc);
  return "";
}
