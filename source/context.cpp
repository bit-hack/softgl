#include "context.h"
#include "gdi_hook.h"
#include "matrix.h"

gl_context_t::gl_context_t(HWND hwnd, HDC hdc) : window(hwnd, hdc) {}

bool gl_context_t::on_create() {
  // load the softgl config
  if (!config.load("softgl.cfg")) {
    // XXX: we need some defaults or something
  }
  // create a framebuffer
  buffer.resize(window.width(), window.height());
  // initalize the raster device
  if (!raster_load(raster, *this)) {
    // XXX: if we cant load a rasterize thats bad
  }
  raster.inst->start(*this);
  return true;
}

void gl_context_t::on_flush() {
  primative.clip_triangles();
  primative.convert_to_dc();
  if (raster.inst) {
    raster.inst->push_triangles(primative.triangles());
  }
  primative.clear_triangles();
  raster.inst->flush();
}

void gl_context_t::on_resize() {
  // set default viewport
  state.viewport = rectf_t{0, 0, float(buffer.width()), float(buffer.height())};
  // set default scissor
  state.scissor = rectf_t{0, 0, float(buffer.width()), float(buffer.height())};
}

void gl_context_t::on_make_current() { GdiHook.hook(*this); }
