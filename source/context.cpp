#include "context.h"
#include "surface.h"
#include "matrix.h"
#include "vertex.h"
#include "gdi_hook.h"


void gl_context_t::on_flush() {
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
