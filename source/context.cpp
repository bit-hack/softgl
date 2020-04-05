#include "context.h"
#include "gdi_hook.h"
#include "log.h"
#include "matrix.h"

gl_context_t::gl_context_t(HWND hwnd, HDC hdc)
  : window(hwnd, hdc) {
}

bool gl_context_t::on_create() {
  // load the softgl config
  if (!config.load("softgl.cfg")) {
    // XXX: we need some defaults or something
  }
  // create a profiler
  profile.reset(profile_create());
  // create a framebuffer
  buffer.resize(window.width(), window.height());
  // initalize the raster device
  if (!raster_load(raster, *this)) {
    // cant load a rasterizer
    return false;
  }
  raster.inst->start(*this);
  return true;
}

void gl_context_t::on_flush() {
  if (!primative.triangles().empty()) {
    primative.clip_triangles();
    primative.convert_to_dc();
    if (profile) {
      profile->on_triangles(primative.triangles());
    }
    if (raster.inst) {
      const texture_t *tex = texture.boundTexture2d();
      raster.inst->push_triangles(primative.triangles(), tex, state);
    }
    primative.clear_triangles();
  }
  raster.inst->flush();
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
