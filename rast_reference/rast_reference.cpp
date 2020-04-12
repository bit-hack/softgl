#pragma once
#include <algorithm>
#include <cstdint>
#include <array>

#include <intrin.h>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"
#include "../source/texture.h"

struct triangle_setup_t {

  enum {
    slot_w0,  // triangle weight 0
    slot_w1,  // triangle weight 1
    slot_iw,  // inverse w
    slot_z,   // z / w
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

  std::array<float3, 3> edge;

  recti_t bound;
  uint32_t mip_level;
};

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

// ~log3.75 (should be log4 but this looks nice)
static const std::array<uint8_t, 128> mip_log_table = {
    0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
};

static inline uint32_t get_mip_level(float tri_area,
                                     float uv_area) {
  const float factor = abs(uv_area * 0.99f) / abs(tri_area);
  uint32_t ifactor = uint32_t(factor);
  return mip_log_table[
    std::min(ifactor, mip_log_table.size() - 1)];
}

static inline float triangle_area(const float2 &v0,
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
static inline float evaluate(const float2 &normal,
                             const float2 &poe) {
  return normal.x * poe.x + normal.y * poe.y;
}

static inline __m128 step_x(float v, float vx) {
  return _mm_set_ps(v + vx * 3.f,
                    v + vx * 2.f,
                    v + vx * 1.f,
                    v + vx * 0.f);
}

static const int32_t BLOCK_SIZE = 16;
static const int32_t BLOCK_MASK = ~(BLOCK_SIZE - 1);

static inline void draw_wi_depth(
  const triangle_setup_t &s,
  const texture_t &,
  const float2 origin,
  uint32_t *color,
  float *depth,
  uint32_t pitch) {

  float v0 = (s.vx[s.slot_w0] * origin.x + s.vy[s.slot_w0] * origin.y) - s.v[s.slot_w0];
  float v1 = (s.vx[s.slot_w1] * origin.x + s.vy[s.slot_w1] * origin.y) - s.v[s.slot_w1];
  float iw = (s.vx[s.slot_iw] * origin.x + s.vy[s.slot_iw] * origin.y) - s.v[s.slot_iw];
  float z  = (s.vx[s.slot_z ] * origin.x + s.vy[s.slot_z ] * origin.y) - s.v[s.slot_z ];

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    float v0_ = v0;
    float v1_ = v1;
    float iw_ = iw;
    float z_  = z;

    for (int x = 0; x < BLOCK_SIZE; ++x) {

      // third edge coefficient
      const float v2_ = 1.f - (v0_ + v1_);

      // triangle edge test
      if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {

        // depth test
        const float zed = z_;
        if (zed <= depth[x]) {

          // depth write
          depth[x] = zed;

          // color write
          const uint8_t r = uint8_t(128 + zed * 127);
          const uint8_t g = r;
          const uint8_t b = r;
          color[x] = (r << 16) | (g << 8) | b;
        }
      }

      // x-axis step
      v0_ += s.vx[s.slot_w0];
      v1_ += s.vx[s.slot_w1];
      iw_ += s.vx[s.slot_iw];
      z_  += s.vx[s.slot_z];
    }

    // y-axis step
    v0 += s.vy[s.slot_w0];
    v1 += s.vy[s.slot_w1];
    iw += s.vy[s.slot_iw];
    z  += s.vy[s.slot_z];
    // framebuffer step
    color += pitch;
    depth += pitch;
  }
}

static inline void draw_wi_depth_sse(
  const triangle_setup_t &s,
  const texture_t &,
  const float2 origin,
  uint32_t *color,
  float *depth,
  uint32_t pitch) {

  const float v0 = (s.vx[s.slot_w0] * origin.x + s.vy[s.slot_w0] * origin.y) - s.v[s.slot_w0];
  const float v1 = (s.vx[s.slot_w1] * origin.x + s.vy[s.slot_w1] * origin.y) - s.v[s.slot_w1];
  const float iw = (s.vx[s.slot_iw] * origin.x + s.vy[s.slot_iw] * origin.y) - s.v[s.slot_iw];
  const float z  = (s.vx[s.slot_z ] * origin.x + s.vy[s.slot_z ] * origin.y) - s.v[s.slot_z ];

  __m128 Sv0x = _mm_set1_ps(s.vx[s.slot_w0] * 4.f);
  __m128 Sv0y = _mm_set1_ps(s.vy[s.slot_w0]);
  __m128 Sv0 = step_x(v0, s.vx[s.slot_w0]);

  __m128 Sv1x = _mm_set1_ps(s.vx[s.slot_w1] * 4.f);
  __m128 Sv1y = _mm_set1_ps(s.vy[s.slot_w1]);
  __m128 Sv1  = step_x(v1, s.vx[s.slot_w1]);

  __m128 Siwx = _mm_set1_ps(s.vx[s.slot_iw] * 4.f);
  __m128 Siwy = _mm_set1_ps(s.vy[s.slot_iw]);
  __m128 Siw  = step_x(iw, s.vx[s.slot_iw]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz  = step_x(z, s.vx[s.slot_z]);

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    __m128 Sv0_ = Sv0;
    __m128 Sv1_ = Sv1;
    __m128 Siw_ = Siw;
    __m128 Sz_  = Sz;

    for (int x = 0; x < BLOCK_SIZE; x += 4) {

      // third edge coefficient
      // const float v2_ = 1.f - (v0_ + v1_);
      __m128 Sv2_ = _mm_sub_ps(_mm_set_ps1(1.f), _mm_add_ps(Sv0_, Sv1_));

      // load depth values
      __m128 zbuf = _mm_load_ps(depth + x);

      // triangle edge test
      // if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {
      __m128 m0 = _mm_cmpge_ps(Sv0_, _mm_setzero_ps());
      __m128 m1 = _mm_cmpge_ps(Sv1_, _mm_setzero_ps());
      __m128 m2 = _mm_cmpge_ps(Sv2_, _mm_setzero_ps());

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
      __m128 keep = _mm_and_ps(_mm_and_ps(m0, _mm_cmple_ps(Sz_, zbuf)),
                               _mm_and_ps(m1, m2));

      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);

      // color write
      __m128  rgb1 = _mm_add_ps(_mm_set_ps1(128.f), _mm_mul_ps(Sz_, _mm_set_ps1(127.f)));
      __m128i rgb2 = _mm_cvtps_epi32(rgb1);
      __m128i rgb3 = _mm_or_si128(_mm_slli_epi32(rgb2, 8),
                                  _mm_or_si128(_mm_slli_epi32(rgb2, 16),
                                               rgb2));
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), rgb3);

      // x-axis step
      Sv0_ = _mm_add_ps(Sv0_, Sv0x);
      Sv1_ = _mm_add_ps(Sv1_, Sv1x);
      Siw_ = _mm_add_ps(Siw_, Siwx);
      Sz_  = _mm_add_ps(Sz_ , Szx );
    }

    // y-axis step
    Sv0 = _mm_add_ps(Sv0, Sv0y);
    Sv1 = _mm_add_ps(Sv1, Sv1y);
    Siw = _mm_add_ps(Siw, Siwy);
    Sz  = _mm_add_ps(Sz , Szy );

    // framebuffer step
    color += pitch;
    depth += pitch;
  }
}

static inline void draw_wi_texture(
  const triangle_setup_t &s,
  const texture_t &tex,
  const float2 origin,
  uint32_t *color,
  float *depth,
  uint32_t pitch) {

  const float v0 = (s.vx[s.slot_w0] * origin.x + s.vy[s.slot_w0] * origin.y) - s.v[s.slot_w0];
  const float v1 = (s.vx[s.slot_w1] * origin.x + s.vy[s.slot_w1] * origin.y) - s.v[s.slot_w1];
  const float iw = (s.vx[s.slot_iw] * origin.x + s.vy[s.slot_iw] * origin.y) - s.v[s.slot_iw];
  const float z  = (s.vx[s.slot_z ] * origin.x + s.vy[s.slot_z ] * origin.y) - s.v[s.slot_z ];
  const float u  = (s.vx[s.slot_u ] * origin.x + s.vy[s.slot_u ] * origin.y) - s.v[s.slot_u ];
  const float v  = (s.vx[s.slot_v ] * origin.x + s.vy[s.slot_v ] * origin.y) - s.v[s.slot_v ];

  __m128 Sv0x = _mm_set1_ps(s.vx[s.slot_w0] * 4.f);
  __m128 Sv0y = _mm_set1_ps(s.vy[s.slot_w0]);
  __m128 Sv0 = step_x(v0, s.vx[s.slot_w0]);

  __m128 Sv1x = _mm_set1_ps(s.vx[s.slot_w1] * 4.f);
  __m128 Sv1y = _mm_set1_ps(s.vy[s.slot_w1]);
  __m128 Sv1  = step_x(v1, s.vx[s.slot_w1]);

  __m128 Siwx = _mm_set1_ps(s.vx[s.slot_iw] * 4.f);
  __m128 Siwy = _mm_set1_ps(s.vy[s.slot_iw]);
  __m128 Siw  = step_x(iw, s.vx[s.slot_iw]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz  = step_x(z, s.vx[s.slot_z]);

  const int32_t tw = tex._width >> s.mip_level;
  const int32_t twm = tw - 1;
  __m128 Sux = _mm_set1_ps(s.vx[s.slot_u] * 4.f * tw);
  __m128 Suy = _mm_set1_ps(s.vy[s.slot_u]       * tw);
  __m128 Su  = step_x(u * tw, s.vx[s.slot_u]    * tw);
  __m128i Stwm = _mm_set_epi32(twm, twm, twm, twm);

  const int32_t th = tex._height >> s.mip_level;
  const int32_t thm = th - 1;
  __m128 Svx = _mm_set1_ps(s.vx[s.slot_v] * 4.f * th);
  __m128 Svy = _mm_set1_ps(s.vy[s.slot_v]       * th);
  __m128 Sv  = step_x(v * th,   s.vx[s.slot_v]  * th);
  __m128i Sthm = _mm_set_epi32(thm, thm, thm, thm);

  const uint32_t wshift = tex._wshift - s.mip_level;
  const uint32_t *texel = tex._pixels[s.mip_level];

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    __m128 Sv0_ = Sv0;
    __m128 Sv1_ = Sv1;
    __m128 Siw_ = Siw;
    __m128 Sz_  = Sz;
    __m128 Su_  = Su;
    __m128 Sv_  = Sv;

    for (int x = 0; x < BLOCK_SIZE; x += 4) {

      // third edge coefficient
      // const float v2_ = 1.f - (v0_ + v1_);
      __m128 Sv2_ = _mm_sub_ps(_mm_set_ps1(1.f), _mm_add_ps(Sv0_, Sv1_));

      // load depth values
      __m128 zbuf = _mm_load_ps(depth + x);

      // triangle edge test
      // if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {
      __m128 m0 = _mm_cmpge_ps(Sv0_, _mm_setzero_ps());
      __m128 m1 = _mm_cmpge_ps(Sv1_, _mm_setzero_ps());
      __m128 m2 = _mm_cmpge_ps(Sv2_, _mm_setzero_ps());

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
      // XXX: should be cmple
      __m128 keep = _mm_and_ps(_mm_and_ps(m0, _mm_cmplt_ps(Sz_, zbuf)),
                               _mm_and_ps(m1, m2));

      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);

      // find 1 / (1/w)
      __m128  rw = _mm_rcp_ps(Siw_);
      
      // u / (1/w),  v / (1/w)
      // ((int32_t(u/iw)&twm) +
      //  (int32_t(u/iw)&twm) << tex._wshift)
      __m128i tu  = _mm_and_si128(_mm_cvtps_epi32(_mm_div_ps(Su_, Siw_)), Stwm);
      __m128i tv  = _mm_and_si128(_mm_cvtps_epi32(_mm_div_ps(Sv_, Siw_)), Sthm);
      __m128i ti  = _mm_add_epi32(tu, _mm_slli_epi32(tv, wshift));

      // extract texture indices
      uint32_t ti0 = _mm_extract_epi32(ti, 0);
      uint32_t ti1 = _mm_extract_epi32(ti, 1);
      uint32_t ti2 = _mm_extract_epi32(ti, 2);
      uint32_t ti3 = _mm_extract_epi32(ti, 3);

      // load from the texture
      uint32_t tc0 = texel[ti0];
      uint32_t tc1 = texel[ti1];
      uint32_t tc2 = texel[ti2];
      uint32_t tc3 = texel[ti3];

      // color write
      __m128i rgb = _mm_set_epi32(tc3, tc2, tc1, tc0);
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), rgb);

      // x-axis step
      Sv0_ = _mm_add_ps(Sv0_, Sv0x);
      Sv1_ = _mm_add_ps(Sv1_, Sv1x);
      Siw_ = _mm_add_ps(Siw_, Siwx);
      Sz_  = _mm_add_ps(Sz_ , Szx );
      Su_  = _mm_add_ps(Su_ , Sux );
      Sv_  = _mm_add_ps(Sv_ , Svx );
    }

    // y-axis step
    Sv0 = _mm_add_ps(Sv0, Sv0y);
    Sv1 = _mm_add_ps(Sv1, Sv1y);
    Siw = _mm_add_ps(Siw, Siwy);
    Sz  = _mm_add_ps(Sz , Szy );
    Su  = _mm_add_ps(Su , Suy );
    Sv  = _mm_add_ps(Sv , Svy );

    // framebuffer step
    color += pitch;
    depth += pitch;
  }
}

// trivial in case
static inline void draw_wi_texture_ti(
  const triangle_setup_t &s,
  const texture_t &tex,
  const float2 origin,
  uint32_t *color,
  float *depth,
  uint32_t pitch) {

  const float iw = (s.vx[s.slot_iw] * origin.x + s.vy[s.slot_iw] * origin.y) - s.v[s.slot_iw];
  const float z  = (s.vx[s.slot_z ] * origin.x + s.vy[s.slot_z ] * origin.y) - s.v[s.slot_z ];
  const float u  = (s.vx[s.slot_u ] * origin.x + s.vy[s.slot_u ] * origin.y) - s.v[s.slot_u ];
  const float v  = (s.vx[s.slot_v ] * origin.x + s.vy[s.slot_v ] * origin.y) - s.v[s.slot_v ];

  __m128 Siwx = _mm_set1_ps(s.vx[s.slot_iw] * 4.f);
  __m128 Siwy = _mm_set1_ps(s.vy[s.slot_iw]);
  __m128 Siw  = step_x(iw, s.vx[s.slot_iw]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz  = step_x(z, s.vx[s.slot_z]);

  const int32_t tw = tex._width >> s.mip_level;
  const int32_t twm = tw - 1;
  __m128 Sux = _mm_set1_ps(s.vx[s.slot_u] * 4.f * tw);
  __m128 Suy = _mm_set1_ps(s.vy[s.slot_u]       * tw);
  __m128 Su  = step_x(u * tw, s.vx[s.slot_u]    * tw);
  __m128i Stwm = _mm_set_epi32(twm, twm, twm, twm);

  const int32_t th = tex._height >> s.mip_level;
  const int32_t thm = th - 1;
  __m128 Svx = _mm_set1_ps(s.vx[s.slot_v] * 4.f * th);
  __m128 Svy = _mm_set1_ps(s.vy[s.slot_v]       * th);
  __m128 Sv  = step_x(v * th,   s.vx[s.slot_v]  * th);
  __m128i Sthm = _mm_set_epi32(thm, thm, thm, thm);

  const uint32_t wshift = tex._wshift - s.mip_level;
  const uint32_t *texel = tex._pixels[s.mip_level];

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    __m128 Siw_ = Siw;
    __m128 Sz_  = Sz;
    __m128 Su_  = Su;
    __m128 Sv_  = Sv;

    for (int x = 0; x < BLOCK_SIZE; x += 4) {

      // load depth values
      __m128 zbuf = _mm_load_ps(depth + x);

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
      // XXX: should be cmple
      __m128 keep = _mm_cmplt_ps(Sz_, zbuf);

      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);

      // find 1 / (1/w)
      __m128  rw = _mm_rcp_ps(Siw_);
      
      // u / (1/w),  v / (1/w)
      // ((int32_t(u/iw)&twm) +
      //  (int32_t(u/iw)&twm) << tex._wshift)
      __m128i tu  = _mm_and_si128(_mm_cvtps_epi32(_mm_div_ps(Su_, Siw_)), Stwm);
      __m128i tv  = _mm_and_si128(_mm_cvtps_epi32(_mm_div_ps(Sv_, Siw_)), Sthm);
      __m128i ti  = _mm_add_epi32(tu, _mm_slli_epi32(tv, wshift));

      // extract texture indices
      uint32_t ti0 = _mm_extract_epi32(ti, 0);
      uint32_t ti1 = _mm_extract_epi32(ti, 1);
      uint32_t ti2 = _mm_extract_epi32(ti, 2);
      uint32_t ti3 = _mm_extract_epi32(ti, 3);

      // load from the texture
      uint32_t tc0 = texel[ti0];
      uint32_t tc1 = texel[ti1];
      uint32_t tc2 = texel[ti2];
      uint32_t tc3 = texel[ti3];

      // color write
      __m128i rgb = _mm_set_epi32(tc3, tc2, tc1, tc0);
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), rgb);

      // x-axis step
      Siw_ = _mm_add_ps(Siw_, Siwx);
      Sz_  = _mm_add_ps(Sz_ , Szx );
      Su_  = _mm_add_ps(Su_ , Sux );
      Sv_  = _mm_add_ps(Sv_ , Svx );
    }

    // y-axis step
    Siw = _mm_add_ps(Siw, Siwy);
    Sz  = _mm_add_ps(Sz , Szy );
    Su  = _mm_add_ps(Su , Suy );
    Sv  = _mm_add_ps(Sv , Svy );

    // framebuffer step
    color += pitch;
    depth += pitch;
  }
}

static inline int32_t normal_quadrant(const float3 &edge) {
    return (edge.x > 0.f) | ((edge.y > 0.f) << 1);
}

static inline bool test_out(const float3 &edge,
                            const float2 &p) {
  return (p.x * edge.x + p.y * edge.y) < edge.z;
}

static inline bool test_in(const float3 &edge,
                            const float2 &p) {
  return (p.x * edge.x + p.y * edge.y) > edge.z;
}

static inline bool trivial_out(const float3 &e,
                               const float2 &min,
                               const float2 & max) {
  switch (normal_quadrant( e )) {
  case 3: return test_out(e, float2{max.x, max.y}); // (+,+) -> box (-, -)
  case 2: return test_out(e, float2{min.x, max.y}); // (-,+) -> box (+, -)
  case 1: return test_out(e, float2{max.x, min.y}); // (+,-) -> box (-, +)
  case 0: return test_out(e, float2{min.x, min.y}); // (-,-) -> box (+, +)
  default: __assume(false);
  }
  return false;
}

static inline bool trivial_in(const float3 &e,
                              const float2 &min,
                              const float2 & max) {
  switch (normal_quadrant( e )) {
  case 3: return test_in(e, float2{min.x, min.y}); // (+,+) -> box (+, +)
  case 2: return test_in(e, float2{max.x, min.y}); // (-,+) -> box (-, +)
  case 1: return test_in(e, float2{min.x, max.y}); // (+,-) -> box (+, -)
  case 0: return test_in(e, float2{max.x, max.y}); // (-,-) -> box (-, -)
  default: __assume(false);
  }
  return false;
}

typedef void(*raster_func_t)(const triangle_setup_t &,
                             const texture_t &,
                             const float2,
                             uint32_t *,
                             float *,
                             uint32_t);

// render depth
template <raster_func_t func, raster_func_t func_ti>
static void draw_wg(const frame_t &f,
                    const triangle_setup_t &s,
                    const texture_t &tex) {
  const recti_t rect = { s.bound.x0                   & BLOCK_MASK,
                         s.bound.y0                   & BLOCK_MASK,
                        (s.bound.x1 + BLOCK_SIZE - 1) & BLOCK_MASK,
                        (s.bound.y1 + BLOCK_SIZE - 1) & BLOCK_MASK};
  const auto &e0 = s.edge[0];
  const auto &e1 = s.edge[1];
  const auto &e2 = s.edge[2];
  const uint32_t  pitch = f._width;
  uint32_t *color = f._pixels + (rect.y0 * pitch);
  float    *depth = f._depth  + (rect.y0 * pitch);
  for (int32_t y = rect.y0; y < rect.y1; y += BLOCK_SIZE) {
    for (int32_t x = rect.x0; x < rect.x1; x += BLOCK_SIZE) {
      const float2 min{ float(x             ), float(y             ) };
      const float2 max{ float(x + BLOCK_SIZE), float(y + BLOCK_SIZE) };
      if (trivial_out(e0, min, max)) continue;
      if (trivial_out(e1, min, max)) continue;
      if (trivial_out(e2, min, max)) continue;
      if (trivial_in(e0, min, max) &&
          trivial_in(e1, min, max) &&
          trivial_in(e2, min, max)) {
        func_ti(s, tex, min, color + x, depth + x, pitch);
      }
      else {
        func(s, tex, min, color + x, depth + x, pitch);
      }
    }
    // step the framebuffer
    color += pitch * BLOCK_SIZE;
    depth += pitch * BLOCK_SIZE;
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

      if (tex && tex->_pixels[0]) {
        draw_wg<draw_wi_texture, draw_wi_texture_ti>(_frame, setup, *tex);
      }
      else {
        draw_wg<draw_wi_depth_sse, draw_wi_depth_sse>(_frame, setup, *tex);
      }
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

  // the signed area of the UVs (texel space)
  if (_tex) {
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
    const float iw0 = t.vert[0].coord.w;
    const float iw1 = t.vert[1].coord.w;
    const float iw2 = t.vert[2].coord.w;

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

extern "C" {
__declspec(dllexport) raster_t *raster_create() {
  return new rast_reference_t;
}

__declspec(dllexport) void raster_release(raster_t *r) {
  delete r;
}
};
