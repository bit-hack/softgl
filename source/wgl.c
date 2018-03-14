#include "gl_func_enum.h"
#include <stdbool.h>
#include <assert.h>

#define APIENTRY __stdcall
#define WINAPI __stdcall
#define ATTRIB 

#define FALSE 0
#define TRUE 1

#define BOOL long
#define HGLRC void *
#define UINT unsigned int
#define VOID void
#define LPCSTR char *
#define HDC void *
#define PROC void *
#define DWORD long
#define FLOAT float
#define LPGLYPHMETRICSFLOAT struct GLYPHMETRICSFLOAT*
#define LPLAYERPLANEDESCRIPTOR struct LAYERPLANEDESCRIPTOR*
#define CONST const
typedef DWORD COLORREF;

typedef struct _WGLSWAP {
    HDC hdc;
    UINT uiFlags;
} WGLSWAP;

extern bool init_gl_func_table();

ATTRIB
BOOL APIENTRY wglCopyContext(HGLRC a, HGLRC b, UINT c) {
    typedef BOOL (WINAPI * wglCopyContext_t)(HGLRC, HGLRC, UINT);
    wglCopyContext_t thunk = (wglCopyContext_t)gl_func_table[e_wglCopyContext];
    assert(thunk);
    return thunk(a, b, c);
}

ATTRIB
HGLRC APIENTRY wglCreateContext(HDC a) {
    if (!init_gl_func_table()) {
      // error
    }
    typedef HGLRC (WINAPI * wglCreateContext_t)(HDC);
    wglCreateContext_t thunk = (wglCreateContext_t)gl_func_table[e_wglCreateContext];
    assert(thunk);
    return thunk(a);
}

ATTRIB
BOOL APIENTRY wglDeleteContext(HGLRC a) {
    typedef BOOL (WINAPI * wglDeleteContext_t)(HGLRC);
    wglDeleteContext_t thunk = (wglDeleteContext_t)gl_func_table[e_wglDeleteContext];
    assert(thunk);
    return thunk(a);
}

ATTRIB
HGLRC APIENTRY wglGetCurrentContext(VOID) {
    typedef HGLRC (WINAPI * wglGetCurrentContext_t)();
    wglGetCurrentContext_t thunk = (wglGetCurrentContext_t)gl_func_table[e_wglGetCurrentContext];
    assert(thunk);
    return thunk();
}

ATTRIB
HDC APIENTRY wglGetCurrentDC(VOID) {
    typedef HDC (WINAPI * wglGetCurrentDC_t)();
    wglGetCurrentDC_t thunk = (wglGetCurrentDC_t)gl_func_table[e_wglGetCurrentDC];
    assert(thunk);
    return thunk();
}

ATTRIB
PROC APIENTRY wglGetProcAddress(LPCSTR a) {
    typedef PROC (WINAPI * wglGetProcAddress_t)(LPCSTR);
    wglGetProcAddress_t thunk = (wglGetProcAddress_t)gl_func_table[e_wglGetProcAddress];
    assert(thunk);
    const PROC out = thunk(a);
    return out;
}

ATTRIB
BOOL APIENTRY wglMakeCurrent(HDC a, HGLRC b) {
    typedef BOOL (WINAPI * wglMakeCurrent_t)(HDC, HGLRC);
    wglMakeCurrent_t thunk = (wglMakeCurrent_t)gl_func_table[e_wglMakeCurrent];
    assert(thunk);
    return thunk(a, b);
}

ATTRIB
BOOL APIENTRY wglShareLists(HGLRC a, HGLRC b) {
    typedef BOOL (WINAPI * wglShareLists_t)(HGLRC, HGLRC);
    wglShareLists_t thunk = (wglShareLists_t)gl_func_table[e_wglShareLists];
    assert(thunk);
    return thunk(a, b);
}

ATTRIB
HGLRC APIENTRY wglCreateLayerContext(HDC a, int b) {
    typedef HGLRC (WINAPI * wglCreateLayerContext_t)(HDC, int);
    wglCreateLayerContext_t thunk = (wglCreateLayerContext_t)gl_func_table[e_wglCreateLayerContext];
    assert(thunk);
    return thunk(a, b);
}

ATTRIB
BOOL APIENTRY wglUseFontBitmapsA(HDC a, DWORD b, DWORD c, DWORD d) {
    typedef BOOL (WINAPI * wglUseFontBitmapsA_t)(HDC, DWORD, DWORD, DWORD);
    wglUseFontBitmapsA_t thunk = (wglUseFontBitmapsA_t)gl_func_table[e_wglUseFontBitmapsA];
    assert(thunk);
    return thunk(a, b, c, d);
}

ATTRIB
BOOL APIENTRY wglUseFontBitmapsW(HDC a, DWORD b, DWORD c, DWORD d) {
    typedef BOOL (WINAPI * wglUseFontBitmapsW_t)(HDC, DWORD, DWORD, DWORD);
    wglUseFontBitmapsW_t thunk = (wglUseFontBitmapsW_t)gl_func_table[e_wglUseFontBitmapsW];
    assert(thunk);
    return thunk(a, b, c, d);
}

ATTRIB
BOOL APIENTRY wglSwapBuffers(HDC a) {
    typedef BOOL (WINAPI * wglSwapBuffers_t)(HDC);
    wglSwapBuffers_t thunk = (wglSwapBuffers_t)gl_func_table[e_wglSwapBuffers];
    assert(thunk);
    return thunk(a);
}

ATTRIB
BOOL APIENTRY wglUseFontOutlinesA(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e, FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
    typedef BOOL (WINAPI * wglUseFontOutlinesA_t)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int, LPGLYPHMETRICSFLOAT);
    wglUseFontOutlinesA_t thunk = (wglUseFontOutlinesA_t)gl_func_table[e_wglUseFontOutlinesA];
    assert(thunk);
    return thunk(a, b, c, d, e, f, g, h);
}

ATTRIB
BOOL APIENTRY wglUseFontOutlinesW(HDC a, DWORD b, DWORD c, DWORD d, FLOAT e, FLOAT f, int g, LPGLYPHMETRICSFLOAT h) {
    typedef BOOL (WINAPI * wglUseFontOutlinesW_t)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int, LPGLYPHMETRICSFLOAT);
    wglUseFontOutlinesW_t thunk = (wglUseFontOutlinesW_t)gl_func_table[e_wglUseFontOutlinesW];
    assert(thunk);
    return thunk(a, b, c, d, e, f, g, h);
}

ATTRIB
BOOL APIENTRY wglDescribeLayerPlane(HDC a, int b, int c, UINT d, LPLAYERPLANEDESCRIPTOR e) {
    typedef BOOL (WINAPI * wglDescribeLayerPlane_t)(HDC, int, int, UINT, LPLAYERPLANEDESCRIPTOR);
    wglDescribeLayerPlane_t thunk = (wglDescribeLayerPlane_t)gl_func_table[e_wglDescribeLayerPlane];
    assert(thunk);
    return thunk(a, b, c, d, e);
}

ATTRIB
int APIENTRY wglSetLayerPaletteEntries(HDC a, int b, int c, int d, CONST COLORREF * e) {
    typedef int (WINAPI * wglSetLayerPaletteEntries_t)(HDC, int, int, int, CONST COLORREF *);
    wglSetLayerPaletteEntries_t thunk = (wglSetLayerPaletteEntries_t)gl_func_table[e_wglSetLayerPaletteEntries];
    assert(thunk);
    return thunk(a, b, c, d, e);
}

ATTRIB
int APIENTRY wglGetLayerPaletteEntries(HDC a, int b, int c, int d, COLORREF * e) {
    typedef int (WINAPI * wglGetLayerPaletteEntries_t)(HDC, int, int, int, COLORREF *);
    wglGetLayerPaletteEntries_t thunk = (wglGetLayerPaletteEntries_t)gl_func_table[e_wglGetLayerPaletteEntries];
    assert(thunk);
    return thunk(a, b, c, d, e);
}

ATTRIB
BOOL APIENTRY wglRealizeLayerPalette(HDC a, int b, BOOL c) {
    typedef BOOL (WINAPI * wglRealizeLayerPalette_t)(HDC, int, BOOL);
    wglRealizeLayerPalette_t thunk = (wglRealizeLayerPalette_t)gl_func_table[e_wglRealizeLayerPalette];
    assert(thunk);
    return thunk(a, b, c);
}

ATTRIB
BOOL APIENTRY wglSwapLayerBuffers(HDC a, UINT b) {
    typedef BOOL (WINAPI * wglSwapLayerBuffers_t)(HDC, UINT);
    wglSwapLayerBuffers_t thunk = (wglSwapLayerBuffers_t)gl_func_table[e_wglSwapLayerBuffers];
    assert(thunk);
    return thunk(a, b);
}

ATTRIB
DWORD APIENTRY wglSwapMultipleBuffers(UINT a, CONST WGLSWAP * b) {
    typedef DWORD (WINAPI * wglSwapMultipleBuffers_t)(UINT, CONST WGLSWAP *);
    wglSwapMultipleBuffers_t thunk = (wglSwapMultipleBuffers_t)gl_func_table[e_wglSwapMultipleBuffers];
    assert(thunk);
    return thunk(a, b);
}
