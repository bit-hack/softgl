#include "context.h"
#include "surface.h"
#include "matrix.h"
#include "gdi_hook.h"


void gl_context_t::on_flush() {
#if 0
  // get viewport center offset
  const float vp_x = state.viewport.w * .5f;
  const float vp_y = state.viewport.h * .5f;
  // for all pending vertices
  for (auto v : vertex.vertices) {
    // homogenous perspective divide
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
    // cull points
    if (v.x < -1.f || v.x >  1.f || v.y < -1.f ||
        v.y >  1.f || v.z < -1.f || v.z >  1.f) {
      continue;
    }
    // ndc -> dc coordinate
    const float2 p{
      vp_x + .5f * v.x * state.viewport.w,
      vp_y + .5f * v.y * state.viewport.h};
    // plot point
    buffer.surface().wuplot(p, 0xffffff);
  }
  // clear pending vertices
  vertex.clear();
#else
  auto transform = [this](float4 v) -> float2 {
    // get viewport center offset
    const float vp_x = state.viewport.w * .5f;
    const float vp_y = state.viewport.h * .5f;
    // homogenous perspective divide
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
    // ndc -> dc coordinate
    return float2{vp_x + .5f * v.x * state.viewport.w,
                  vp_y + .5f * v.y * state.viewport.h};
  };

  for (const auto &t : primative.triangles()) {
    const std::array<float2, 3> c{
        transform(t.vert[0].coord),
        transform(t.vert[1].coord),
        transform(t.vert[2].coord),
    };

    buffer.surface().line(c[0], c[1], 0xffffff);
    buffer.surface().line(c[1], c[2], 0xffffff);
    buffer.surface().line(c[2], c[0], 0xffffff);
  }
  primative.clear_triangles();
#endif
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
