#include "buffer.h"
#include "context.h"

void buffer_manager_t::resize(int32_t w, int32_t h) {
  _width = w;
  _height = h;
  _pixels = std::make_unique<uint32_t[]>(w * h);
  _depth = std::make_unique<float[]>(w * h);
  // refresh drawing surface
  _surface = surface_t{_pixels.get(), uint32_t(w), uint32_t(h), uint32_t(w)};
  // notify context of resize
  if (Context) {
    Context->on_resize();
  }
}
