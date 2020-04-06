#pragma once
#include <algorithm>
#include <cstdint>
#include <array>

#include <intrin.h>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"
#include "../source/texture.h"

namespace {

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

constexpr float edgeEval(const float4 &a, const float4 &b, const float2 &c) {
  return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

recti_t boundTri(const frame_t &frame,
                 const float4 &v0,
                 const float4 &v1,
                 const float4 &v2) {
  recti_t out;
  // Compute triangle bounding box
  out.x0 = std::min({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y0 = std::min({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  out.x1 = std::max({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y1 = std::max({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  // Clip against screen bounds
  out.x0 = std::max(out.x0, 0);
  out.y0 = std::max(out.y0, 0);
  out.x1 = std::min(out.x1, frame._width - 1);
  out.y1 = std::min(out.y1, frame._height - 1);
  return out;
}

// ~log3.75 (should be log4 but this looks nice)
static const std::array<uint8_t, 128> mip_log_table = {
    0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
};

uint32_t get_mip_level(float tri_area, float uv_area) {
  const float factor = abs(uv_area * 0.99f) / abs(tri_area);
  uint32_t ifactor = uint32_t(factor);
#if 1
  return mip_log_table[
    std::min(ifactor, mip_log_table.size() - 1)];
#else
  // note: / 2 because the each mip level is 4x information
  uint32_t level = (32 - __lzcnt(ifactor));
  return std::min<uint32_t>(level, texture_t::mip_levels - 1);
#endif
}

} // namespace

void drawTri(const frame_t &frame,
             const triangle_t &t) {

  auto v0 = t.vert[0].coord;
  auto v1 = t.vert[2].coord;
  auto v2 = t.vert[1].coord;

  // Compute triangle bounding box
  const recti_t rect = boundTri(frame, v0, v1, v2);

  // the signed triangle area
  const float area =
      1.f / ((v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y));
  if (area <= 0.f) {
//    return;
  }

  // Triangle setup
  const float sx01 = (v0.y - v1.y) * area;
  const float sy01 = (v1.x - v0.x) * area;
  const float sx12 = (v1.y - v2.y) * area;
  const float sy12 = (v2.x - v1.x) * area;
  const float sx20 = (v2.y - v0.y) * area;
  const float sy20 = (v0.x - v2.x) * area;

  // Barycentric coordinates at minX/minY corner
  const float2 p{float(rect.x0), float(rect.y0)};
  float w0y = edgeEval(v1, v2, p) * area;
  float w1y = edgeEval(v2, v0, p) * area;
  float w2y = edgeEval(v0, v1, p) * area;

  const float iw0 = 1.f / v0.w;
  const float iw1 = 1.f / v1.w;
  const float iw2 = 1.f / v2.w;

        float iw  = w0y  * iw0 + w1y  * iw1 + w2y  * iw2;
  const float iwx = sx12 * iw0 + sx20 * iw1 + sx01 * iw2;
  const float iwy = sy12 * iw0 + sy20 * iw1 + sy01 * iw2;

  // pointer to upper left corner
  uint32_t *dst = frame._pixels + rect.y0 * frame._width;
  float *zbf = frame._depth + rect.y0 * frame._width;

  // Rasterize
  for (int32_t y = rect.y0; y <= rect.y1; y++) {

    // Barycentric coordinates at start of row
    float w0x = w0y;
    float w1x = w1y;
    float w2x = w2y;
    float w   = iw;

    for (int32_t x = rect.x0; x <= rect.x1; x++) {

      // If p is on or inside all edges, render pixel.
      if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

        // depth test
        if (w > zbf[x]) {

          zbf[x] = w;

          const uint32_t c = std::min(255, int32_t(w * 64 * 255));

          // renderPixel(p, w0, w1, w2);
          dst[x] = (c << 16) | (c << 8) | (c);
        }
      }

      w0x += sx12;
      w1x += sx20;
      w2x += sx01;
      w   += iwx;
    }

    // One row step
    w0y += sy12;
    w1y += sy20;
    w2y += sy01;
    iw  += iwy;

    // step y axis
    dst += frame._width;
    zbf += frame._width;
  }
}

void drawTriUV(const frame_t &frame,
               const texture_t &tex,
               const triangle_t &t) {
  // position
  auto v0 = t.vert[0].coord;
  auto v1 = t.vert[2].coord;
  auto v2 = t.vert[1].coord;
  // texture coordinates
  auto t0 = t.vert[0].tex;
  auto t1 = t.vert[2].tex;
  auto t2 = t.vert[1].tex;

  // Compute triangle bounding box
  const recti_t rect = boundTri(frame, v0, v1, v2);

  // the signed triangle area (screen space)
  const float area =
      ((v1.x - v0.x) * (v2.y - v0.y) -
       (v2.x - v0.x) * (v1.y - v0.y));
  const float rarea = 1.f / area;
  if (area == 0.f) {
    return;
  }
  if (area <= 0.f) {
    // if its backfacing then discard it?
//    return;
  }

  // the signed area of the UVs (texel space)
  const float uvarea =
      (tex._width * tex._height) *
      ((t1.x - t0.x) * (t2.y - t0.y) -
       (t2.x - t0.x) * (t1.y - t0.y));

  // texel space area / screen space
  uint32_t mip_level = get_mip_level(area, uvarea);

  // Triangle setup
  const float sx01 = (v0.y - v1.y) * rarea;
  const float sy01 = (v1.x - v0.x) * rarea;
  const float sx12 = (v1.y - v2.y) * rarea;
  const float sy12 = (v2.x - v1.x) * rarea;
  const float sx20 = (v2.y - v0.y) * rarea;
  const float sy20 = (v0.x - v2.x) * rarea;

  // Barycentric coordinates at minX/minY corner
  const float2 p{float(rect.x0), float(rect.y0)};
  float w0y = edgeEval(v1, v2, p) * rarea;
  float w1y = edgeEval(v2, v0, p) * rarea;
  float w2y = edgeEval(v0, v1, p) * rarea;

  // interpolation coefficients
  const float iw0 = 1.f / v0.w;
  const float iw1 = 1.f / v1.w;
  const float iw2 = 1.f / v2.w;
  const std::array<float, 9> c = {
    w0y  * iw0, w1y  * iw1, w2y  * iw2,
    sx12 * iw0, sx20 * iw1, sx01 * iw2,
    sy12 * iw0, sy20 * iw1, sy01 * iw2,
  };

  // w interpolant
        float iw   = c[0] + c[1] + c[2];
  const float iwx  = c[3] + c[4] + c[5];
  const float iwy  = c[6] + c[7] + c[8];

  // tex uv interpolant
  const uint32_t wshift = tex._wshift - mip_level;
  const uint32_t texw   = tex._width  >> mip_level;
  const uint32_t texh   = tex._height >> mip_level;
  const uint32_t texum  = texw - 1;
  const uint32_t texvm  = texh - 1;
  const uint32_t *texel = tex._pixels[mip_level];
  const float2 tscale = {float(texw), float(texh)};
        float2 uv  = (c[0] * t0 + c[1] * t1 + c[2] * t2) * tscale;
  const float2 uvx = (c[3] * t0 + c[4] * t1 + c[5] * t2) * tscale;
  const float2 uvy = (c[6] * t0 + c[7] * t1 + c[8] * t2) * tscale;

  // pointer to upper left corner
  uint32_t *dst = frame._pixels + rect.y0 * frame._width;
     float *zbf = frame._depth  + rect.y0 * frame._width;

  // rasterize
  for (int32_t y = rect.y0; y <= rect.y1; y++) {

    // barycentric coordinates at start of row
    float  w0x = w0y;
    float  w1x = w1y;
    float  w2x = w2y;
    float  hw  = iw;
    float2 huv = uv;

    for (int32_t x = rect.x0; x <= rect.x1; x++) {

      // if p is on or inside all edges, render pixel.
      if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

        // depth test
        if (hw > zbf[x]) {

          const int32_t u = int32_t(huv.x / hw) & texum;
          const int32_t v = int32_t(huv.y / hw) & texvm;

          zbf[x] = hw;
          dst[x] = texel[u + (v << wshift)];
        }
      }

      // step in the x axis
      w0x += sx12;
      w1x += sx20;
      w2x += sx01;
      hw  += iwx;
      huv += uvx;
    }

    // step in the y axis
    w0y += sy12;
    w1y += sy20;
    w2y += sy01;
    iw  += iwy;
    uv  += uvy;

    // step the framebuffer
    dst += frame._width;
    zbf += frame._width;
  }
}

void drawTriUV2(const frame_t &frame,
                const texture_t &tex,
                const triangle_t &t) {
  // position
  auto v0 = t.vert[0].coord;
  auto v1 = t.vert[2].coord;
  auto v2 = t.vert[1].coord;
  // texture coordinates
  auto t0 = t.vert[0].tex;
  auto t1 = t.vert[2].tex;
  auto t2 = t.vert[1].tex;

  // Compute triangle bounding box
  const recti_t rect = boundTri(frame, v0, v1, v2);

  // the signed triangle area (screen space)
  const float area =
      ((v1.x - v0.x) * (v2.y - v0.y) -
       (v2.x - v0.x) * (v1.y - v0.y));
  const float rarea = 1.f / area;
  if (area == 0.f) {
    return;
  }
  if (area <= 0.f) {
    // if its backfacing then discard it?
//    return;
  }

  // the signed area of the UVs (texel space)
  const float uvarea =
      (tex._width * tex._height) *
      ((t1.x - t0.x) * (t2.y - t0.y) -
       (t2.x - t0.x) * (t1.y - t0.y));

  // texel space area / screen space
  uint32_t mip_level = get_mip_level(area, uvarea);

  // Triangle setup
  const float sx01 = (v0.y - v1.y) * rarea;
  const float sy01 = (v1.x - v0.x) * rarea;
  const float sx12 = (v1.y - v2.y) * rarea;
  const float sy12 = (v2.x - v1.x) * rarea;
  const float sx20 = (v2.y - v0.y) * rarea;
  const float sy20 = (v0.x - v2.x) * rarea;

  // Barycentric coordinates at minX/minY corner
  const float2 p{float(rect.x0), float(rect.y0)};
  float w0y = edgeEval(v1, v2, p) * rarea;
  float w1y = edgeEval(v2, v0, p) * rarea;
  float w2y = edgeEval(v0, v1, p) * rarea;

  // interpolation coefficients
  const float iw0 = 1.f / v0.w;
  const float iw1 = 1.f / v1.w;
  const float iw2 = 1.f / v2.w;
  const std::array<float, 9> c = {
    w0y  * iw0, w1y  * iw1, w2y  * iw2,
    sx12 * iw0, sx20 * iw1, sx01 * iw2,
    sy12 * iw0, sy20 * iw1, sy01 * iw2,
  };

  // w interpolant
        float iw   = c[0] + c[1] + c[2];
  const float iwx  = c[3] + c[4] + c[5];
  const float iwy  = c[6] + c[7] + c[8];

  // tex uv interpolant
  const uint32_t wshift = tex._wshift - mip_level;
  const uint32_t texw   = tex._width  >> mip_level;
  const uint32_t texh   = tex._height >> mip_level;
  const uint32_t texum  = texw - 1;
  const uint32_t texvm  = texh - 1;
  const uint32_t *texel = tex._pixels[mip_level];
  const float2 tscale = {float(texw), float(texh)};
        float2 uv  = (c[0] * t0 + c[1] * t1 + c[2] * t2) * tscale;
  const float2 uvx = (c[3] * t0 + c[4] * t1 + c[5] * t2) * tscale;
  const float2 uvy = (c[6] * t0 + c[7] * t1 + c[8] * t2) * tscale;

  // pointer to upper left corner
  uint32_t *dst = frame._pixels + rect.y0 * frame._width;
     float *zbf = frame._depth  + rect.y0 * frame._width;

  // rasterize
  for (int32_t y = rect.y0; y <= rect.y1; y++) {

    // barycentric coordinates at start of row
    float  w0x = w0y;
    float  w1x = w1y;
    float  w2x = w2y;
    float  hw  = iw;
    float2 huv = uv;

    for (int32_t x = rect.x0; x <= rect.x1;) {

      static const uint32_t stride = 16;

      // compute current uvs
      int32_t u0 = 65536 * huv.x / hw;
      int32_t v0 = 65536 * huv.y / hw;
      // compute uvs at end of span
      int32_t u1 = 65536 * (huv.x + uvx.x * stride) / (hw + iwx * stride);
      int32_t v1 = 65536 * (huv.y + uvx.y * stride) / (hw + iwx * stride);
      // compute uv deltas
      const int32_t udelta = (u1 - u0) / stride;
      const int32_t vdelta = (v1 - v0) / stride;

      // render the interpolated span
      int32_t nx = x + stride;
      for (; x < nx && x <= rect.x1; ++x) {

        // if p is on or inside all edges, render pixel.
        if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

          // depth test
          if (hw > zbf[x]) {

            const int32_t u = (u0 >> 16) & texum;
            const int32_t v = (v0 >> 16) & texvm;

            zbf[x] = hw;
            dst[x] = texel[u + (v << wshift)];
          }
        }

        // step the interpolated uvs
        u0 += udelta;
        v0 += vdelta;

        // step in the x axis
        w0x += sx12;  // edge interpolant
        w1x += sx20;  // edge interpolant
        w2x += sx01;  // edge interpolant
        hw  += iwx;   // 1/w
      }

      // step real uv/w
      huv += uvx * stride;
    }

    // step in the y axis
    w0y += sy12;
    w1y += sy20;
    w2y += sy01;
    iw  += iwy;
    uv  += uvy;

    // step the framebuffer
    dst += frame._width;
    zbf += frame._width;
  }
}

void drawTriARGB(const frame_t &frame,
                 const texture_t &tex,
                 const triangle_t &t) {
  // position
  const auto &v0 = t.vert[0].coord;
  const auto &v1 = t.vert[2].coord;
  const auto &v2 = t.vert[1].coord;
  // texture coordinates
  // ARGB layout
  const auto &t0 = t.vert[0].rgba;
  const auto &t1 = t.vert[2].rgba;
  const auto &t2 = t.vert[1].rgba;

  // Compute triangle bounding box
  const recti_t rect = boundTri(frame, v0, v1, v2);

  // the signed triangle area
  const float area =
      1.f / ((v1.x - v0.x) * (v2.y - v0.y) -
             (v2.x - v0.x) * (v1.y - v0.y));
  if (area <= 0.f) {
//    return;
  }

  // Triangle setup
  const float sx01 = (v0.y - v1.y) * area;
  const float sy01 = (v1.x - v0.x) * area;
  const float sx12 = (v1.y - v2.y) * area;
  const float sy12 = (v2.x - v1.x) * area;
  const float sx20 = (v2.y - v0.y) * area;
  const float sy20 = (v0.x - v2.x) * area;

  // Barycentric coordinates at minX/minY corner
  const float2 p{float(rect.x0), float(rect.y0)};
  float w0y = edgeEval(v1, v2, p) * area;
  float w1y = edgeEval(v2, v0, p) * area;
  float w2y = edgeEval(v0, v1, p) * area;

  // interpolation coefficients
  const float iw0 = 1.f / v0.w;
  const float iw1 = 1.f / v1.w;
  const float iw2 = 1.f / v2.w;
  const std::array<float, 9> c = {
    w0y  * iw0, w1y  * iw1, w2y  * iw2,
    sx12 * iw0, sx20 * iw1, sx01 * iw2,
    sy12 * iw0, sy20 * iw1, sy01 * iw2,
  };

  // w interpolant
        float iw   = c[0]      + c[1]      + c[2];
  const float iwx  = c[3]      + c[4]      + c[5];
  const float iwy  = c[6]      + c[7]      + c[8];

  // rgba uv interpolant
        float4 uv  = (c[0] * t0 + c[1] * t1 + c[2] * t2);
  const float4 uvx = (c[3] * t0 + c[4] * t1 + c[5] * t2);
  const float4 uvy = (c[6] * t0 + c[7] * t1 + c[8] * t2);

  // pointer to upper left corner
  uint32_t *dst = frame._pixels + rect.y0 * frame._width;
     float *zbf = frame._depth  + rect.y0 * frame._width;

  // Rasterize
  for (int32_t y = rect.y0; y <= rect.y1; y++) {

    // Barycentric coordinates at start of row
    float w0x = w0y;
    float w1x = w1y;
    float w2x = w2y;
    float hw = iw;
    float4 huv = uv;

    for (int32_t x = rect.x0; x <= rect.x1; x++) {

      // If p is on or inside all edges, render pixel.
      if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

        // depth test
        if (hw > zbf[x]) {

          const int32_t a = int32_t(255 * huv.x / hw);
          const int32_t r = int32_t(255 * huv.y / hw);
          const int32_t g = int32_t(255 * huv.z / hw);
          const int32_t b = int32_t(255 * huv.w / hw);

          zbf[x] = hw;

          dst[x] = (a << 24) | (r << 16) | (g << 8) | (b);
        }
      }

      // step in the x axis
      w0x += sx12;
      w1x += sx20;
      w2x += sx01;
      hw  += iwx;
      huv += uvx;
    }

    // step in the y axis
    w0y += sy12;
    w1y += sy20;
    w2y += sy01;
    iw  += iwy;
    uv  += uvy;

    // step the framebuffer
    dst += frame._width;
    zbf += frame._width;
  }
}

struct rast_reference_t : public raster_t {

  rast_reference_t() {
    _cxt = nullptr;
    _frame._pixels = nullptr;
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
                      const state_manager_t &state) override {

    if (!_cxt || !_frame._pixels) {
      return;
    }

    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped so discard
        continue;
      }

      if (state.blendFrag) {
#if 1
        if (state.blendFuncDst != GL_ZERO && state.blendFuncSrc != GL_ONE) {
          return;
        }
#else
        if (state.blendFuncDst == GL_ZERO && state.blendFuncSrc == GL_ONE) {
          return;
        }
#endif
      }

      if (tex) {
        drawTriUV2(_frame, *tex, t);
      }
      else {
        drawTriARGB(_frame, *tex, t);
      }
    }
  }

  void flush() override {}

  void present() override {}

protected:
  gl_context_t *_cxt;
  frame_t _frame;
};

extern "C" {
__declspec(dllexport) raster_t *raster_create() { return new rast_reference_t; }

__declspec(dllexport) void raster_release(raster_t *r) { delete r; }
};
