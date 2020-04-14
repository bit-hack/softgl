#pragma once
#include <algorithm>
#include <cstdint>
#include <array>

#include <intrin.h>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"
#include "../source/texture.h"

#include "kernel.h"

typedef void (draw_func_t)(
  const frame_t &f,
  const triangle_setup_t &s,
  const texture_t &tex);

draw_func_t rast_tex_one_zero;
draw_func_t rast_tex_one_one;
draw_func_t rast_tex_dst_src;
draw_func_t rast_tex_sa_msa;
draw_func_t rast_tex_dst_zero;

// ~log3.75 (should be log4 but this looks nice)
const std::array<uint8_t, 128> mip_log_table = {
    0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
};

static inline constexpr uint32_t blend_code(GLenum mode) {
  return 
    (mode == GL_ZERO) ? 0x0 :
    (mode == GL_ONE) ? 0x1 :
    (mode == GL_DST_COLOR) ? 0x2 :
    (mode == GL_SRC_COLOR) ? 0x3 :
    (mode == GL_ONE_MINUS_DST_COLOR) ? 0x4 :
    (mode == GL_ONE_MINUS_SRC_COLOR) ? 0x5 :
    (mode == GL_SRC_ALPHA) ? 0x6 :
    (mode == GL_ONE_MINUS_SRC_ALPHA) ? 0x7 :
    (mode == GL_DST_ALPHA) ? 0x8 :
    (mode == GL_ONE_MINUS_DST_ALPHA) ? 0x9 :
    (mode == GL_SRC_ALPHA_SATURATE) ? 0xa : 0x0;
}

static inline constexpr uint32_t blend_code(GLenum src, GLenum dst) {
  return (blend_code(src) << 4) | blend_code(dst);
}

struct rast_reference_t : public raster_t {

  rast_reference_t() {
    _cxt = nullptr;
    _frame._pixels = nullptr;
    _tex = nullptr;
    _draw_func = nullptr;
  }

  void framebuffer_clear(
    bool color,
    bool depth,
    bool stencil,
    uint32_t clear_color,
    float clear_depth,
    uint32_t clear_stencil) override {
    if (_cxt) {
      if (color) {
        _cxt->buffer.clear_colour(0x202020);
      }
      if (depth) {
        _cxt->buffer.clear_depth(clear_depth);
      }
    }
  }

  void framebuffer_release() override {
    _frame._pixels = nullptr;
  }

  void framebuffer_aquire() override {
    _frame._pixels = _cxt->buffer.pixels();
    _frame._depth  = _cxt->buffer.depth();
    _frame._width  = _cxt->buffer.width();
    _frame._height = _cxt->buffer.height();
  }

  bool start(gl_context_t &cxt) override {
    _cxt = &cxt;
    return true;
  }

  void stop() override {
    _cxt = nullptr;
  }

  void push_triangles(const std::vector<triangle_t> &triangles,
                      const texture_t *tex,
                      const state_manager_t &state) override;

  void flush() override {}

  void present() override {}

protected:

  draw_func_t *find_draw_func(const state_manager_t &state);

  draw_func_t *_draw_func;

  bool setup_triangle(const triangle_t &t,
                      triangle_setup_t &s);

  const texture_t *_tex;
  gl_context_t *_cxt;
  frame_t _frame;
};

draw_func_t *rast_reference_t::find_draw_func(const state_manager_t &state) {
  if (state.blendFrag) {
    switch (blend_code(state.blendFuncSrc, state.blendFuncDst)) {
    case blend_code(GL_ONE, GL_ZERO):
      return rast_tex_one_zero;
    case blend_code(GL_ONE, GL_ONE):
      return rast_tex_one_zero;
    case blend_code(GL_DST_COLOR, GL_SRC_COLOR):
      return rast_tex_dst_src;
    case blend_code(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA):
      return rast_tex_sa_msa;
    case blend_code(GL_DST_COLOR, GL_ZERO):
      return rast_tex_dst_zero;
    default:
      DEBUG_BREAK;
      break;
    }
  }
  return rast_tex_one_zero;
}

bool rast_reference_t::setup_triangle(const triangle_t &t,
                                      triangle_setup_t &s) {

  // isolate 2d coordinates
  const float2 v0{t.vert[0].coord.x, t.vert[0].coord.y};
  const float2 v1{t.vert[1].coord.x, t.vert[1].coord.y};
  const float2 v2{t.vert[2].coord.x, t.vert[2].coord.y};

  // compute triangle bounding box
  s.bound.x0 = std::min({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  s.bound.y0 = std::min({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  s.bound.x1 = std::max({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  s.bound.y1 = std::max({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});

  // reject if off screen
  if (s.bound.x1 < 0)              return false;
  if (s.bound.x0 > _frame._width)  return false;
  if (s.bound.y1 < 0)              return false;
  if (s.bound.y0 > _frame._height) return false;

  // clip against screen bounds
  s.bound.x0 = std::max(s.bound.x0, 0);
  s.bound.y0 = std::max(s.bound.y0, 0);
  s.bound.x1 = std::min(s.bound.x1, _frame._width - 1);
  s.bound.y1 = std::min(s.bound.y1, _frame._height - 1);

  // find the area of the triangle
  const float area = triangle_area(v0, v1, v2);

  // heuristic for if we should use affine mapping
  const bool affine = affine_heuristic(s.bound);
  s.affine = affine;

  // the signed area of the UVs (texel space)
  if (_tex) {
    const float2 &t0 = t.vert[0].tex;
    const float2 &t1 = t.vert[1].tex;
    const float2 &t2 = t.vert[2].tex;

    const float texture_area = _tex->_width * _tex->_height;
    const float uv_area =
      ((t1.x - t0.x) * (t2.y - t0.y) - (t2.x - t0.x) * (t1.y - t0.y));
    s.mip_level = get_mip_level(area, uv_area * texture_area);
  }

  // find edge vectors
  const float2 d01 = v1 - v0;
  const float2 d12 = v2 - v1;
  const float2 d20 = v0 - v2;

  // cross product gives us normals from the edges
  // which we 'normalize' to the area of the triangle
  const float2 n0 = float2::cross(d12) / area;
  const float2 n1 = float2::cross(d20) / area;
  const float2 n2 = float2::cross(d01) / area;

  // evaluate the starting position for each interpolant
  const float s0 = evaluate(n0, v1);
  const float s1 = evaluate(n1, v2);
  const float s2 = evaluate(n2, v0);

  // store edges
  s.edge[0] = float3{n0.x, n0.y, s0};
  s.edge[1] = float3{n1.x, n1.y, s1};
  s.edge[2] = float3{n2.x, n2.y, s2};

  // edge function interpolants
  {
    s. v[triangle_setup_t::slot_w0] = s0;
    s.vx[triangle_setup_t::slot_w0] = n0.x;
    s.vy[triangle_setup_t::slot_w0] = n0.y;

    s. v[triangle_setup_t::slot_w1] = s1;
    s.vx[triangle_setup_t::slot_w1] = n1.x;
    s.vy[triangle_setup_t::slot_w1] = n1.y;
  }

  // XXX: make this float3 and use dot products
  std::array<float, 9> c;

  const auto & state = _cxt->state;

  // 1/w interpolation
  {
    const float iw0 = affine ? 1.f : t.vert[0].coord.w;
    const float iw1 = affine ? 1.f : t.vert[1].coord.w;
    const float iw2 = affine ? 1.f : t.vert[2].coord.w;

    c[0] = s0   * iw0;  c[1] = s1   * iw1; c[2] = s2   * iw2;
    c[3] = n0.x * iw0;  c[4] = n1.x * iw1; c[5] = n2.x * iw2;
    c[6] = n0.y * iw0;  c[7] = n1.y * iw1; c[8] = n2.y * iw2;

    const uint32_t slot = triangle_setup_t::slot_iw;
    s.v [slot] = c[0] + c[1] + c[2];
    s.vx[slot] = c[3] + c[4] + c[5];
    s.vy[slot] = c[6] + c[7] + c[8];
  }

  // z
  {
    const uint32_t slot = triangle_setup_t::slot_z;
    const float a0 = t.vert[0].coord.z;
    const float a1 = t.vert[1].coord.z;
    const float a2 = t.vert[2].coord.z;
    s.v [slot] = s0   * a0 + s1   * a1 + s2   * a2;
    s.vx[slot] = n0.x * a0 + n1.x * a1 + n2.x * a2;
    s.vy[slot] = n0.y * a0 + n1.y * a1 + n2.y * a2;
  }

  // a
  {
    const uint32_t slot = triangle_setup_t::slot_a;
    const float a0 = t.vert[0].rgba.x;
    const float a1 = t.vert[1].rgba.x;
    const float a2 = t.vert[2].rgba.x;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  // r
  {
    const uint32_t slot = triangle_setup_t::slot_r;
    const float a0 = t.vert[0].rgba.w;
    const float a1 = t.vert[1].rgba.w;
    const float a2 = t.vert[2].rgba.w;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  // g
  {
    const uint32_t slot = triangle_setup_t::slot_g;
    const float a0 = t.vert[0].rgba.y;
    const float a1 = t.vert[1].rgba.y;
    const float a2 = t.vert[2].rgba.y;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  // b
  {
    const uint32_t slot = triangle_setup_t::slot_b;
    const float a0 = t.vert[0].rgba.z;
    const float a1 = t.vert[1].rgba.z;
    const float a2 = t.vert[2].rgba.z;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  // u
  {
    const uint32_t slot = triangle_setup_t::slot_u;
    const float a0 = t.vert[0].tex.x;
    const float a1 = t.vert[1].tex.x;
    const float a2 = t.vert[2].tex.x;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  // v
  {
    const uint32_t slot = triangle_setup_t::slot_v;
    const float a0 = t.vert[0].tex.y;
    const float a1 = t.vert[1].tex.y;
    const float a2 = t.vert[2].tex.y;
    s.v [slot] = c[0] * a0 + c[1] * a1 + c[2] * a2;
    s.vx[slot] = c[3] * a0 + c[4] * a1 + c[5] * a2;
    s.vy[slot] = c[6] * a0 + c[7] * a1 + c[8] * a2;
  }

  return true;
}

void rast_reference_t::push_triangles(const std::vector<triangle_t> &triangles,
                                      const texture_t *tex,
                                      const state_manager_t &state) {

  _draw_func = find_draw_func(state);

  if (!_cxt || !_frame._pixels || !_draw_func) {
    return;
  }

  _tex = tex;

  for (const auto &t : triangles) {
    if (t.vert[0].coord.w == 0.f) {
      // signals fully clipped so discard
      continue;
    }

    triangle_setup_t setup;
    if (!setup_triangle(t, setup)) {
      continue;
    }

    if (tex) {
      _draw_func(_frame, setup, *tex);
    }
    else {
      // TODO
    }
  }
}

extern "C" {
__declspec(dllexport) raster_t *raster_create() {
  return new rast_reference_t;
}

__declspec(dllexport) void raster_release(raster_t *r) {
  delete r;
}
};
