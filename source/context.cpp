#include "context.h"
#include "surface.h"
#include "matrix.h"
#include "gdi_hook.h"


gl_context_t::gl_context_t(HWND hwnd, HDC hdc)
  : window(hwnd, hdc) {

  buffer.resize(window.width(),
                window.height());
  raster.reset(raster_create());
}

void gl_context_t::on_flush() {

  primative.clip_triangles();
  primative.convert_to_dc();
  raster->push_triangles(primative.triangles());
  primative.clear_triangles();
}

void gl_context_t::on_resize() {
  // set default viewport
  state.viewport = rectf_t{0, 0, float(buffer.width()), float(buffer.height())};
  // set default scissor
  state.scissor = rectf_t{0, 0, float(buffer.width()), float(buffer.height())};
}

void gl_context_t::on_make_current() {
  GdiHook.hook(*this);
}
