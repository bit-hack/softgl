#pragma once
#include <cstdint>
#include <memory>

#include "GL.h"
#include "windows.h"

#include "buffer.h"
#include "matrix.h"
#include "state.h"
#include "texture.h"
#include "window.h"
#include "primative.h"
#include "raster.h"


struct gl_context_t {

  void *operator new(size_t request) {
    // note: operator required for aligned alloc
    assert(request);
    size_t alignment = alignof(gl_context_t);
    return _aligned_malloc(request, alignment);
  }

  void operator delete(void *ptr) {
    // note: operator required for aligned alloc
    assert(ptr);
    _aligned_free(ptr);
  }

  gl_context_t(HWND hwnd, HDC hdc);

  buffer_manager_t buffer;
  window_manager_t window;
  matrix_manager_t matrix;
  texture_manager_t texture;
  state_manager_t state;
  primative_manager_t primative;
  raster_module_t raster;

  void on_flush();
  void on_resize();
  void on_make_current();

protected:
  gl_context_t(const gl_context_t &) = delete;
};

// context accessor
gl_context_t *getContext();
#define Context getContext()
