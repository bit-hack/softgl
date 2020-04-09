#pragma once
#include <algorithm>
#include <cstdint>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"

#include "clip.h"

namespace {

static const int32_t BLOCK_SIZE = 16;

struct triangle_setup_t {

  enum {
    slot_w0,  // triangle weight 0
    slot_w1,  // triangle weight 1
    slot_iw,  // inverse w
    slot_r,   // r / w
    slot_g,   // g / w
    slot_b,   // b / w
    slot_u,   // u / w
    slot_v,   // v / w
    _slot_count_
  };

  std::array<float, _slot_count_> v;
  std::array<float, _slot_count_> vx;
  std::array<float, _slot_count_> vy;

  float minz, maxz;
  uint32_t mip_level;
};

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
  int _blocks_in_x;
  int _blocks_in_y;
};

struct block_t {
  std::vector<uint32_t> _triangle_setup;

  // block bounding rect
  float2 _min, _max;

  // frame buffer pointers
  uint32_t *_fb_color;
  float *_fb_depth;
};

void bounds(const float4 &v0,
            const float4 &v1,
            const float4 &v2,
            recti_t &out) {
  // Compute triangle bounding box
  out.x0 = std::min({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y0 = std::min({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  out.x1 = std::max({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y1 = std::max({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
}

} // namespace

struct rast_fasterizer_t : public raster_t {

  void framebuffer_clear(
    bool color,
    bool depth,
    bool stencil,
    uint32_t clear_color,
    float clear_depth,
    uint32_t clear_stencil) override {

    if (clear_depth) {
      float *depth = _frame._depth;
      for (int y = 0; y < _frame._height; ++y) {
        for (int x = 0; x < _frame._width; ++x) {
          depth[x] = 1000.f;
        }
        depth += _frame._width;
      }
    }
  };

  void framebuffer_release() override {
    _blocks.clear();
  }

  void framebuffer_aquire() override {
    _blocks.clear();
    _frame._pixels = _cxt->buffer.pixels();
    _frame._depth  = _cxt->buffer.depth();
    _frame._width  = _cxt->buffer.width();
    _frame._height = _cxt->buffer.height();

    _frame._blocks_in_x = _frame._width / BLOCK_SIZE;
    _frame._blocks_in_y = _frame._height / BLOCK_SIZE;

    for (int y = 0; y < _frame._blocks_in_y; ++y) {
      for (int x = 0; x < _frame._blocks_in_x; ++x) {

        const int32_t ix = x * BLOCK_SIZE;
        const int32_t iy = y * BLOCK_SIZE;

        const int offset = ix + iy * _frame._width;

        block_t b;
        b._min = float2{float(ix), float(iy)};
        b._max = float2{float(ix + BLOCK_SIZE), float(iy + BLOCK_SIZE)};
        b._fb_color = _frame._pixels + offset;
        b._fb_depth = _frame._depth + offset;
        _blocks.push_back(b);
      }
    }

    assert(_blocks.size() == _frame._blocks_in_x * _frame._blocks_in_y);
  }

  bool start(gl_context_t &cxt) override {
    _cxt = &cxt;
    return true;
  }

  void stop() override {
  }

  void draw_block_fast(const block_t &block, const triangle_setup_t &s) {

    float iw = (s.vx[2] * (block._min.x) +
                s.vy[2] * (block._min.y)) - s.v[2];

    float u = (s.vx[3] * (block._min.x) +
               s.vy[3] * (block._min.y)) - s.v[3];

    uint32_t *dst = block._fb_color;
    float *depth = block._fb_depth;

    for (int y = 0; y < BLOCK_SIZE; ++y) {

      float iw_ = iw;

      const float u0 = (u) / iw;
      const float u1 = (u + s.vx[3] * BLOCK_SIZE) / iw;
      const float u_dx = (u1 - u0) / BLOCK_SIZE;
      float u_ = u0;

      for (int x = 0; x < BLOCK_SIZE; ++x) {

        const float w = 1.f / iw_;

        // depth test
        if (w <= depth[x]) {
          depth[x] = w;

          const uint8_t r = uint8_t(128 + w * 0.1f);
          const uint8_t g = uint8_t(128 + w * 0.1f);
          const uint8_t b = uint8_t(128 + w * 0.1f);

          dst[x] = (r << 16) | (g << 8) | b;
        }

        // x step interpolants
        iw_ += s.vx[2];
        u_  += u_dx;
      }

      // y step interpolants
      iw += s.vy[2];
      u  += s.vy[3];

      dst += _frame._width;
      depth += _frame._width;
    }
  }

  void draw_block(const block_t &block, const triangle_setup_t &s) {

    const float vx0 = s.vx[0];
    const float vy0 = s.vy[0];
    const float vx1 = s.vx[1];
    const float vy1 = s.vy[1];

    float v0 = (vx0 * block._min.x + vy0 * block._min.y) - s.v[0];
    float v1 = (vx1 * block._min.x + vy1 * block._min.y) - s.v[1];
    
    float iw = (s.vx[2] * (block._min.x) +
                s.vy[2] * (block._min.y)) - s.v[2];

    uint32_t *dst = block._fb_color;
    float *depth = block._fb_depth;

    for (int y = 0; y < BLOCK_SIZE; ++y) {

      float v0_ = v0;
      float v1_ = v1;

      float iw_ = iw;

      for (int x = 0; x < BLOCK_SIZE; ++x) {

        const float v2_ = 1.f - (v0_ + v1_);

        const float w = 1.f / iw_;

        // triangle edge test
        if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {

          // depth test
          if (w <= depth[x]) {
            depth[x] = w;

            const uint8_t r = uint8_t(128 + w * 0.1f);
            const uint8_t g = uint8_t(128 + w * 0.1f);
            const uint8_t b = uint8_t(128 + w * 0.1f);

            dst[x] = (r << 16) | (g << 8) | b;
          }

        }

        v0_ += vx0;
        v1_ += vx1;
        iw_ += s.vx[2];
      }

      v0 += vy0;
      v1 += vy1;
      iw += s.vy[2];

      dst += _frame._width;
      depth += _frame._width;
    }
  }

  void draw_block(const block_t &block) {
    for (uint32_t setup_index : block._triangle_setup) {

      bool trivial_in = 0 != (setup_index & 0x80000000);

      setup_index &= 0x7fffffff;

      const triangle_setup_t &s = _setup[setup_index];

      if (trivial_in) {
        draw_block_fast(block, s);
      }
      else {
        draw_block(block, s);
      }
    }
  }

  void insert_triangle(const triangle_t &t,
                       const triangle_setup_t &s,
                       uint32_t setup_index) {

    // find bounding rectangle of the triangle
    recti_t rect;
    bounds(t.vert[0].coord,
           t.vert[1].coord,
           t.vert[2].coord,
           rect);

    // clip the triangle if fully out of the frame
    if (rect.x1 < 0)              return;
    if (rect.y1 < 0)              return;
    if (rect.x0 > _frame._width)  return;
    if (rect.y0 > _frame._height) return;

    // clamp in block space
    const int32_t ix0 = std::max<int32_t>(rect.x0 / BLOCK_SIZE, 0);
    const int32_t iy0 = std::max<int32_t>(rect.y0 / BLOCK_SIZE, 0);
    const int32_t ix1 = std::min<int32_t>(rect.x1 / BLOCK_SIZE, _frame._blocks_in_x-1);
    const int32_t iy1 = std::min<int32_t>(rect.y1 / BLOCK_SIZE, _frame._blocks_in_y-1);

    // isolate 2d coordinates
    const float2 v0{t.vert[0].coord.x,
                    t.vert[0].coord.y};
    const float2 v1{t.vert[1].coord.x,
                    t.vert[1].coord.y};
    const float2 v2{t.vert[2].coord.x,
                    t.vert[2].coord.y};

    tri_setup_t clip{v0, v1, v2};

    // insert into blocks
    for (int y = iy0; y <= iy1; ++y) {
      for (int x = ix0; x <= ix1; ++x) {

        //XXX: only do these tests if the area is large
        // heuristic for a large triangle:
        //   area > (2 * (BLOCK_SIZE * BLOCK_SIZE));

        const rectf_t r{
          (x + 0) * BLOCK_SIZE,
          (y + 0) * BLOCK_SIZE,
          (x + 1) * BLOCK_SIZE,
          (y + 1) * BLOCK_SIZE};

        if (clip.trivial_out(r)) {
          continue;
        }

        // apply trivial in mask
        //XXX: trivial in seems broken
        const uint32_t mask = 0; //  clip.trivial_in(r) ? 0x80000000 : 0x00000000;

        // offset into the block list
        const uint32_t bo = x + y * _frame._blocks_in_x;

        assert(bo >= 0 && bo < _blocks.size());
        _blocks[bo]._triangle_setup.push_back(setup_index | mask);
      }
    }
  }

  float triangle_area(const float2 &v0,
                      const float2 &v1,
                      const float2 &v2) {

    // area is found using part of the vector product

    // x = a2 * b3 - a3 * b2
    // y = a1 * b3 - a3 * b1
    // z = a1 * b2 - a2 * b1

    // where a = v0 -> v1
    // where b = v0 -> v2

    // we only care about the z componant which contains the area of the
    // parallelogram formed. i'm unsure why we dont need to multiply by
    // 0.5f however when returning the result.

    return (v1.x - v0.x) * (v2.y - v0.y) -
           (v2.x - v0.x) * (v1.y - v0.y);
  }

  // evaluate the gradient field given the following:
  //  normal:   the normal for that edge
  //  poe:      a point on the edge
  //  point:    the location where to sample it
  float evaluate(const float2 &normal,
                 const float2 &poe) {
      return normal.x * poe.x + normal.y * poe.y;
  }

  bool setup_triangle(const triangle_t &t, triangle_setup_t &s) {

    // isolate 2d coordinates
    const float2 v0{t.vert[0].coord.x, t.vert[0].coord.y};
    const float2 v1{t.vert[1].coord.x, t.vert[1].coord.y};
    const float2 v2{t.vert[2].coord.x, t.vert[2].coord.y};

    // find the area of the triangle
    const float area = triangle_area(v0, v1, v2);

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

    // 1/w interpolation
    {
      const float iw0 = 1.f / t.vert[0].coord.w;
      const float iw1 = 1.f / t.vert[1].coord.w;
      const float iw2 = 1.f / t.vert[2].coord.w;

      c[0] = s0   * iw0;  c[1] = s1   * iw1; c[2] = s2   * iw2;
      c[3] = n0.x * iw0;  c[4] = n1.x * iw1; c[5] = n2.x * iw2;
      c[6] = n0.y * iw0;  c[7] = n1.y * iw1; c[8] = n2.y * iw2;

      const uint32_t slot = triangle_setup_t::slot_iw;
      s. v[slot] = c[0] + c[1] + c[2];
      s.vx[slot] = c[3] + c[4] + c[5];
      s.vy[slot] = c[6] + c[7] + c[8];
    }

    // r
    {
      const uint32_t slot = triangle_setup_t::slot_r;
      const float a0 = t.vert[0].rgba.x;
      const float a1 = t.vert[1].rgba.x;
      const float a2 = t.vert[2].rgba.x;
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

  void push_triangles(const std::vector<triangle_t> &triangles,
                      const texture_t *tex,
                      const state_manager_t &state) override {

    // insert all triangles into blocks
    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped so discard
        continue;
      }

      _setup.emplace_back();
      triangle_setup_t &s = _setup.back();
      if (!setup_triangle(t, s)) {
        _setup.pop_back();
        continue;
      }

      const uint32_t setup_index = (uint32_t)_setup.size() - 1u;

      insert_triangle(t, s, setup_index);
    }

    // draw all blocks
    for (block_t &b : _blocks) {
      draw_block(b);
      b._triangle_setup.clear();
    }

    // clear all of our triangle setup
    _setup.clear();
  }

  void flush() override {}

  void present() override {
  }

protected:

  std::vector<triangle_setup_t> _setup;

  frame_t _frame;
  std::vector<block_t> _blocks;
  gl_context_t *_cxt;
};

extern "C" {
__declspec(dllexport) raster_t *raster_create() {
  return new rast_fasterizer_t;
}

__declspec(dllexport) void raster_release(raster_t *r) {
  assert(r);
  delete r;
}
};
