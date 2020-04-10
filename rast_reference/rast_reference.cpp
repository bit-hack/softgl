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

  recti_t bound;
  uint32_t mip_level;
};

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

constexpr float edgeEval(const float4 &a, const float4 &b, const float2 &c) {
  return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

recti_t triangle_bound(const frame_t &frame,
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

inline float triangle_area(const float2 &v0,
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
inline float evaluate(const float2 &normal, const float2 &poe) {

  return normal.x * poe.x + normal.y * poe.y;
}

} // namespace

// render depth
void draw_tri_depth(const frame_t &f,
                    const texture_t &tex,
                    const triangle_setup_t &s) {

    float v0 = (s.vx[0] * s.bound.x0 + s.vy[0] * s.bound.y0) - s.v[0];
    float v1 = (s.vx[1] * s.bound.x0 + s.vy[1] * s.bound.y0) - s.v[1];
    float iw = (s.vx[2] * s.bound.x0 + s.vy[2] * s.bound.y0) - s.v[2];

    uint32_t fb_offset = s.bound.y0 * f._width;
    uint32_t *dst      = f._pixels + fb_offset;
    float    *depth    = f._depth + fb_offset;

    for (int y = s.bound.y0; y <= s.bound.y1; ++y) {

      float v0_ = v0;
      float v1_ = v1;
      float iw_ = iw;

      for (int x = s.bound.x0; x <= s.bound.x1; ++x) {

        const float v2_ = 1.f - (v0_ + v1_);

        const float w = iw_;

        // triangle edge test
        if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {

          // depth test
          if (w > depth[x]) {
            depth[x] = w;

            const uint8_t r = 255; //  std::min(255, std::max(0, int32_t(w * 32 * 255)));
            const uint8_t g = r;
            const uint8_t b = r;

            dst[x] = (r << 16) | (g << 8) | b;
          }

        }

        // x axis coefficient step
        v0_ += s.vx[0];
        v1_ += s.vx[1];
        iw_ += s.vx[2];
      }

      // y axis coefficient step
      v0 += s.vy[0];
      v1 += s.vy[1];
      iw += s.vy[2];

      // step the framebuffers
      dst   += f._width;
      depth += f._width;
    }
}

// render using texture
void draw_tri_tex_aprox(const frame_t &f,
                        const texture_t &tex,
                        const triangle_setup_t &s) {

  const uint32_t SW = triangle_setup_t::slot_iw;
  const uint32_t SU = triangle_setup_t::slot_u;
  const uint32_t SV = triangle_setup_t::slot_v;

  float v0 = (s.vx[0]  * s.bound.x0 + s.vy[0]  * s.bound.y0) - s.v[0];
  float v1 = (s.vx[1]  * s.bound.x0 + s.vy[1]  * s.bound.y0) - s.v[1];

  float iw = (s.vx[SW] * s.bound.x0 + s.vy[SW] * s.bound.y0) - s.v[SW];

  const uint32_t tex_w      = (tex._width  >> s.mip_level);
  const uint32_t tex_h      = (tex._height >> s.mip_level);
  const uint32_t tex_mask_u = tex_w - 1;
  const uint32_t tex_mask_v = tex_h - 1;
  const uint32_t tex_shift  = tex._wshift - s.mip_level;
  const uint32_t *texel     = tex._pixels[s.mip_level];

  const float sux = s.vx[SU] * tex_w;
  const float svx = s.vx[SV] * tex_h;
  const float suy = s.vy[SU] * tex_w;
  const float svy = s.vy[SV] * tex_h;
  float u = ((s.vx[SU] * s.bound.x0 + s.vy[SU] * s.bound.y0) - s.v[SU]) * tex_w;
  float v = ((s.vx[SV] * s.bound.x0 + s.vy[SV] * s.bound.y0) - s.v[SV]) * tex_h;

  const uint32_t fb_offset = s.bound.y0 * f._width;
  uint32_t *dst            = f._pixels + fb_offset;
  float    *depth          = f._depth  + fb_offset;

  for (int y = s.bound.y0; y <= s.bound.y1; ++y) {

    float v0_ = v0;
    float v1_ = v1;
    float iw_ = iw;
    float u_  = u;
    float v_  = v;

    for (int x = s.bound.x0; x <= s.bound.x1;) {

      static const int CHUNK_SIZE = 32;
      const int x_chunk_end = std::min<int>(s.bound.x1, x + CHUNK_SIZE - 1);

            float iw0  = iw_;
      const float iw1  = iw_ + s.vx[SW] * CHUNK_SIZE;

            float tu0  =  u_                     / iw0;
      const float tu1  = (u_ + sux * CHUNK_SIZE) / iw1;
      const float tudx = (tu1 - tu0) / CHUNK_SIZE;

      int32_t itu0  = int32_t(tu0  * float(0x8000));
      int32_t itudx = int32_t(tudx * float(0x8000));

            float tv0  =  v_                     / iw0;
      const float tv1  = (v_ + svx * CHUNK_SIZE) / iw1;
      const float tvdx = (tv1 - tv0) / CHUNK_SIZE;

      int32_t itv0  = int32_t(tv0  * float(0x8000));
      int32_t itvdx = int32_t(tvdx * float(0x8000));

      for (; x <= x_chunk_end ; ++x) {

        const float w = iw_;

        // triangle edge test
        const float v2_ = 1.f - (v0_ + v1_);
        if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {

          // depth test
          if (w > depth[x]) {
            depth[x] = w;

            const int32_t iu = (itu0 >> 15) & tex_mask_u;
            const int32_t iv = (itv0 >> 15) & tex_mask_v;

            dst[x] = texel[iu + (iv << tex_shift)];
          }
        }

        // x axis coefficient step
        v0_ += s.vx[0];
        v1_ += s.vx[1];
        iw_ += s.vx[SW];

        // x axis interpolation step
        itu0 += itudx;
        itv0 += itvdx;
      }

      // x chunk step
      u_ += sux * CHUNK_SIZE;
      v_ += svx * CHUNK_SIZE;
    }

    // y axis coefficient step
    v0 += s.vy[0];
    v1 += s.vy[1];
    iw += s.vy[SW];
    u  += suy;
    v  += svy;

    // step the framebuffers
    dst   += f._width;
    depth += f._width;
  }
}

// render using texture
void draw_tri_tex(const frame_t &f,
                  const texture_t &tex,
                  const triangle_setup_t &s) {

  const uint32_t SW = triangle_setup_t::slot_iw;
  const uint32_t SU = triangle_setup_t::slot_u;
  const uint32_t SV = triangle_setup_t::slot_v;

  float v0 = (s.vx[0]  * s.bound.x0 + s.vy[0]  * s.bound.y0) - s.v[0];
  float v1 = (s.vx[1]  * s.bound.x0 + s.vy[1]  * s.bound.y0) - s.v[1];

  float iw = (s.vx[SW] * s.bound.x0 + s.vy[SW] * s.bound.y0) - s.v[SW];

  const uint32_t tex_w      = (tex._width  >> s.mip_level);
  const uint32_t tex_h      = (tex._height >> s.mip_level);
  const uint32_t tex_mask_u = tex_w - 1;
  const uint32_t tex_mask_v = tex_h - 1;
  const uint32_t tex_shift  = tex._wshift - s.mip_level;
  const uint32_t *texel     = tex._pixels[s.mip_level];

  const float sux = s.vx[SU] * tex_w;
  const float svx = s.vx[SV] * tex_h;
  const float suy = s.vy[SU] * tex_w;
  const float svy = s.vy[SV] * tex_h;
  float u = ((s.vx[SU] * s.bound.x0 + s.vy[SU] * s.bound.y0) - s.v[SU]) * tex_w;
  float v = ((s.vx[SV] * s.bound.x0 + s.vy[SV] * s.bound.y0) - s.v[SV]) * tex_h;

  const uint32_t fb_offset = s.bound.y0 * f._width;
  uint32_t *dst            = f._pixels + fb_offset;
  float    *depth          = f._depth  + fb_offset;

  for (int y = s.bound.y0; y <= s.bound.y1; ++y) {

    float v0_ = v0;
    float v1_ = v1;
    float iw_ = iw;
    float u_  = u;
    float v_  = v;

    for (int x = s.bound.x0; x <= s.bound.x1; ++x) {

      const float v2_ = 1.f - (v0_ + v1_);

      const float w = iw_;

      // triangle edge test
      if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {

        // depth test
        if (w > depth[x]) {
          depth[x] = w;

          const int32_t iu = int32_t(u_ / iw_) & tex_mask_u;
          const int32_t iv = int32_t(v_ / iw_) & tex_mask_v;

          dst[x] = texel[iu + (iv << tex_shift)];
        }
      }

      // x axis coefficient step
      v0_ += s.vx[0];
      v1_ += s.vx[1];
      iw_ += s.vx[SW];
      u_  += sux;
      v_  += svx;
    }

    // y axis coefficient step
    v0 += s.vy[0];
    v1 += s.vy[1];
    iw += s.vy[SW];
    u  += suy;
    v  += svy;

    // step the framebuffers
    dst   += f._width;
    depth += f._width;
  }
}

void drawTri(const frame_t &frame,
             const triangle_t &t) {

  auto v0 = t.vert[0].coord;
  auto v1 = t.vert[2].coord;
  auto v2 = t.vert[1].coord;

  // Compute triangle bounding box
  const recti_t rect = triangle_bound(frame, v0, v1, v2);

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
  const recti_t rect = triangle_bound(frame, v0, v1, v2);

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
  const recti_t rect = triangle_bound(frame, v0, v1, v2);

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

        const float w2x = 1.f - (w0x + w1x);

        // if p is on or inside all edges, render pixel.
        if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

          // depth test
          if (hw >= zbf[x]) {

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
        hw  += iwx;   // 1/w
      }

      // step real uv/w
      huv += uvx * stride;
    }

    // step in the y axis
    w0y += sy12;
    w1y += sy20;
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
  const recti_t rect = triangle_bound(frame, v0, v1, v2);

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
    _tex = nullptr;
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
        _cxt->buffer.clear_depth(0.f);
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
                      const state_manager_t &state) override {

    if (!_cxt || !_frame._pixels) {
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

#if 0
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
#endif

#if 1
//      draw_tri_depth(_frame, *tex, setup);
      draw_tri_tex_aprox(_frame, *tex, setup);
#else
      if (tex) {
        drawTriUV2(_frame, *tex, t);
      }
      else {
        drawTriARGB(_frame, *tex, t);
      }
#endif
    }
  }

  void flush() override {}

  void present() override {}

protected:

  bool setup_triangle(const triangle_t &t,
                      triangle_setup_t &s);

  const texture_t *_tex;
  gl_context_t *_cxt;
  frame_t _frame;
};

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

  // remove backfaces
  if (area > 0) {
    return false;
  }

  // the signed area of the UVs (texel space)
  {
    const float2 &t0 = t.vert[0].tex;
    const float2 &t1 = t.vert[1].tex;
    const float2 &t2 = t.vert[2].tex;
    const float uv_area =
      (_tex->_width * _tex->_height) *
      ((t1.x - t0.x) * (t2.y - t0.y) - (t2.x - t0.x) * (t1.y - t0.y));
    s.mip_level = get_mip_level(area, uv_area);
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

#if 0
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
#endif

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

extern "C" {
__declspec(dllexport) raster_t *raster_create() { return new rast_reference_t; }

__declspec(dllexport) void raster_release(raster_t *r) { delete r; }
};
