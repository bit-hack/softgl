#include "context.h"
#include "draw.h"
#include "matrix.h"
#include "vertex.h"


void gl_context_t::resize(uint32_t w, uint32_t h) {
  buffer.width = w;
  buffer.height = h;
  // create buffers
  buffer.pixels = std::make_unique<uint32_t[]>(w * h);
  buffer.depth = std::make_unique<float[]>(w * h);
  // attach a draw surface
  surface = surface_t{buffer.pixels.get(), w, h, w};
  // set defaul viewport
  viewport = rectf_t{0, 0, float(w), float(h)};
}

void gl_context_t::flush() {

  const auto m0 = Context->matrix().modelview();
  const auto m1 = Context->matrix().projection();

  const int32_t vp_x = (viewport.w) / 2;
  const int32_t vp_y = (viewport.h) / 2;

  auto &pipe = Context->vertex();

  for (auto v : pipe.vertices) {

    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;

    if (v.x < -1.f || v.x > 1.f || v.y < -1.f || v.y > 1.f || v.z < -1.f || v.z > 1.f) {
      continue;
    }

    const float2 p{
      vp_x + .5f * v.x * viewport.w,
      vp_y + .5f * v.y * viewport.h};

    Context->surf().wuplot(p, 0xffffff);
  }

  //
  pipe.clear();
}

surface_t &gl_context_t::surf() {
  return surface;
}

matrix_manager_t &gl_context_t::matrix() {
  return matrix_manager;
}

vertex_manager_t &gl_context_t::vertex() {
  return vertex_manager;
}
