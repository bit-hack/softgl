#pragma once
#include <algorithm>
#include <cstdint>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"

#include "clip.h"

namespace {

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

template <int32_t R>
constexpr int32_t roundup(int32_t v) {
  return ((v - 1) | (R - 1)) + 1;
}

recti_t boundTri(const recti_t &r, const float4 &v0, const float4 &v1,
                const float4 &v2) {
  recti_t out;
  // Compute triangle bounding box
  out.x0 = std::min({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y0 = std::min({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  out.x1 = std::max({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y1 = std::max({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  // Clip against screen bounds
  out.x0 = std::max(out.x0, r.x0);
  out.y0 = std::max(out.y0, r.y0);
  out.x1 = std::min(out.x1, r.x1 - 1);
  out.y1 = std::min(out.y1, r.y1 - 1);
  return out;
}

// rasterize in a rect with edge clipping
template <int ACC>
void raster_block_imp(frame_t &surf,
                      const tri_setup_t<float4> &tri,
                      const int2 &r /* top left */)
{
  // evaluate at rect origin
  std::array<float, 3> jy = tri.eval(float2{float(r.x), float(r.y)});
  // triangle steps
  const std::array<float2, 3> step = tri.step();

  uint32_t *p = surf._pixels;
  p += r.x + r.y * surf._width;

  // y itterations
  for (float y = 0; y < 16; ++y) {
    std::array<float, 3> jx = jy;
    // x itterations
    for (uint32_t x = 0; x < 16; ++x) {
      // note: clip test needed here
      if (((ACC & 2) || (jx[0] > 0.f)) &&
          ((ACC & 1) || (jx[1] > 0.f)) &&
          ((ACC & 4) || (jx[2] > 0.f)))
      {
        const int cr = 0xff & int(jx[0] * 255.f);
        const int cg = 0xff & int(jx[1] * 255.f);
        const int cb = 0xff & int(jx[2] * 255.f);
//        p[x] = (ACC0 << 23) | (ACC1 << 15) | (ACC2 << 7);
        p[x] = (cr << 16) | (cg << 8) | cb;
      }
      // advance x step
      jx[0] += step[0].x;
      jx[1] += step[1].x;
      jx[2] += step[2].x;
    }
    // advance y step
    p += surf._width;
    jy[0] += step[0].y;
    jy[1] += step[1].y;
    jy[2] += step[2].y;
  }
}

void raster_block(frame_t &surf,
                  tri_setup_t<float4> tri,
                  const rectf_t &r,
                  const int2 &p) {
  const uint32_t i = tri.trivial_in(r);
#if 0
  switch (i) {
  case 0: raster_rect<0, 0, 0>(surf, tri, r); break;
  case 1: raster_rect<1, 0, 0>(surf, tri, r); break;
  case 2: raster_rect<0, 1, 0>(surf, tri, r); break;
  case 3: raster_rect<1, 1, 0>(surf, tri, r); break;
  case 4: raster_rect<0, 0, 1>(surf, tri, r); break;
  case 5: raster_rect<1, 0, 1>(surf, tri, r); break;
  case 6: raster_rect<0, 1, 1>(surf, tri, r); break;
  case 7: raster_rect<1, 1, 1>(surf, tri, r); break;
  }
#else
  switch (i) {
  // trivial accept tile
  case 0:                raster_block_imp<0>(surf, tri, p); break; // 0 0 0
  // one edge test
  case 1:                raster_block_imp<1>(surf, tri, p); break; // 1 0 0
  case 2: tri.rotate2(); raster_block_imp<1>(surf, tri, p); break; // 0 1 0
  case 4: tri.rotate1(); raster_block_imp<1>(surf, tri, p); break; // 0 0 1
  // two edge test
  case 3:                raster_block_imp<3>(surf, tri, p); break; // 1 1 0
  case 5: tri.rotate1(); raster_block_imp<3>(surf, tri, p); break; // 1 0 1
  case 6: tri.rotate2(); raster_block_imp<3>(surf, tri, p); break; // 0 1 1
  // three edge test
  case 7:                raster_block_imp<7>(surf, tri, p); break; // 1 1 1
  default:              __assume(false);
  }
#endif
}

void raster_descent_16(frame_t &surf,
                       tri_setup_t<float4> &tri,
                       const rectf_t r,
                       const int2 & p) {
  if (!tri.trivial_out(r)) {
    raster_block(surf, tri, r, p);
  }
}

void raster_descent_32(frame_t &surf,
                       tri_setup_t<float4> &tri,
                       const rectf_t r,
                       const int2 & p) {
  if (!tri.trivial_out(r)) {
    // mid point
    const float mx = (r.x0 + r.x1) / 2;
    const float my = (r.y0 + r.y1) / 2;
    // visit each quadrant
    const auto r0 = rectf_t{r.x0, r.y0, mx, my};
    raster_descent_16(surf, tri, r0, p);
    const auto r1 = rectf_t{mx, r.y0, r.x1, my};
    raster_descent_16(surf, tri, r1, p + int2{ 16, 0 });
    const auto r2 = rectf_t{r.x0, my, mx, r.y1};
    raster_descent_16(surf, tri, r2, p + int2{ 0, 16 });
    const auto r3 = rectf_t{mx, my, r.x1, r.y1};
    raster_descent_16(surf, tri, r3, p + int2{ 16, 16 });
  }
}

void raster_descent_64(frame_t &surf,
                       tri_setup_t<float4> &tri,
                       const rectf_t r,
                       const int2 & p) {
  if (!tri.trivial_out(r)) {
    // mid point
    const float mx = (r.x0 + r.x1) / 2;
    const float my = (r.y0 + r.y1) / 2;
    // visit each quadrant
    const auto r0 = rectf_t{r.x0, r.y0, mx, my};
    raster_descent_32(surf, tri, r0, p);
    const auto r1 = rectf_t{mx, r.y0, r.x1, my};
    raster_descent_32(surf, tri, r1, p + int2{ 32, 0 });
    const auto r2 = rectf_t{r.x0, my, mx, r.y1};
    raster_descent_32(surf, tri, r2, p + int2{ 0, 32 });
    const auto r3 = rectf_t{mx, my, r.x1, r.y1};
    raster_descent_32(surf, tri, r3, p + int2{ 32, 32 });
  }
}

void raster_descent(frame_t &surf,
                    tri_setup_t<float4> &tri,
                    const recti_t r) {
  // find triangle boundary
  const auto &v = tri.vertices();
  const auto &b = boundTri(r, v[0], v[1], v[2]);
  // if 64x64 stamp fits on screen
  if (roundup<64>(b.x1) < r.x1 &&
      roundup<64>(b.y1) < r.y1) {
    // stamp is 64x64
    const int32_t B = 64, Bm = ~63;
    for (int32_t y = b.y0 & Bm; y < b.y1; y += B) {
      for (int32_t x = b.x0 & Bm; x < b.x1; x += B) {
        const rectf_t block = {float(x), float(y), float(x + B), float(y + B)};
        raster_descent_64(surf, tri, block, int2{x, y});
      }
    }
  }
  else {
    // stamp is 32x32
    const int32_t B = 32, Bm = ~31;
    for (int32_t y = b.y0 & Bm; y < b.y1; y += B) {
      for (int32_t x = b.x0 & Bm; x < b.x1; x += B) {
        const rectf_t block = {float(x), float(y), float(x + B), float(y + B)};
        raster_descent_32(surf, tri, block, int2{x, y});
      }
    }
  }
}

} // namespace

void drawTri(frame_t &frame,
             const float4 &v0, 
             const float4 &v1,
             const float4 &v2) {
  // Compute triangle bounding box
  const recti_t r{0, 0, frame._width, frame._height};
  const recti_t rect = boundTri(r, v0, v1, v2);
  //
  tri_setup_t<float4> triangle{v0, v1, v2};
  //
  raster_descent(frame, triangle, rect);
}

struct rast_reference_t : public raster_t {

  void framebuffer_release() override {}

  void framebuffer_aquire() override {}

  void start(gl_context_t &cxt) override { _cxt = &cxt; }

  void stop() override {}

  void push_triangles(const std::vector<triangle_t> &triangles,
                      const texture_t *tex,
                      const state_manager_t &state) override {

    frame_t frame;
    frame._pixels = _cxt->buffer.pixels();
    frame._depth  = _cxt->buffer.depth();
    frame._width  = _cxt->buffer.width();
    frame._height = _cxt->buffer.height();

    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped so discard
        continue;
      }

      // XXX: why are these flipped?
      drawTri(frame, t.vert[0].coord, t.vert[2].coord, t.vert[1].coord);
    }
  }

  void flush() override {}

  void present() override {}

protected:
  gl_context_t *_cxt;
};

extern "C" {
__declspec(dllexport) raster_t *raster_create() { return new rast_reference_t; }

__declspec(dllexport) void raster_release(raster_t *r) { delete r; }
};
