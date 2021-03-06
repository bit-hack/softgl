#pragma once
#include <algorithm>
#include <cstdint>
#include <array>

#include <intrin.h>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"
#include "../source/texture.h"


static const int32_t BLOCK_SIZE = 16;
static const int32_t BLOCK_MASK = ~(BLOCK_SIZE - 1);

struct triangle_setup_t {

  enum {
    slot_w0,  // triangle weight 0
    slot_w1,  // triangle weight 1
    slot_iw,  // inverse w
    slot_z,   // z / w

    slot_a,   // a / w
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

  bool affine;
  recti_t bound;
  uint32_t mip_level;
};

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

extern const std::array<uint8_t, 128> mip_log_table;

static inline uint32_t get_mip_level(float tri_area,
                                     float uv_area) {
  const float factor = fabsf(uv_area) / fabsf(tri_area);
  uint32_t ifactor = uint32_t(factor);
  uint32_t max = mip_log_table.size() - 1;
  uint32_t index = std::min(ifactor, max);
  return mip_log_table[index];
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

static inline bool affine_heuristic(const recti_t &r) {
  // heuristic decides if this is a small triangle using
  // the square of the max edge to avoid slim triangles being
  // flagged
  const int32_t max = std::max<int32_t>(r.dx(), r.dy());
  return (max * max) < (64 * 64);
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

template <GLenum mode>
static __forceinline __m128i blend_factor(__m128i src, __m128i dst) {

  // Input layout:
  //   ARGB colour layout

  switch (mode) {
  case GL_ZERO:
    return _mm_setzero_si128();
  case GL_ONE:
    return _mm_set1_epi8((char)0xff);
  case GL_DST_COLOR:
    return dst;
  case GL_SRC_COLOR:
    return src;
  case GL_ONE_MINUS_DST_COLOR:
    return _mm_sub_epi8(_mm_set1_epi8((char)0xff), dst);
  case GL_ONE_MINUS_SRC_COLOR:
    return _mm_sub_epi8(_mm_set1_epi8((char)0xff), src);
  case GL_SRC_ALPHA: {
    const __m128i a = _mm_and_si128(src, _mm_set1_epi32(0x000000ff));
    const __m128i b = _mm_or_si128(a, _mm_slli_epi32(a, 16));
    return _mm_or_si128(b, _mm_slli_epi32(b, 8));
  }
  case GL_ONE_MINUS_SRC_ALPHA: {
    const __m128i a = _mm_and_si128(src, _mm_set1_epi32(0x000000ff));
    const __m128i b = _mm_or_si128(a, _mm_slli_epi32(a, 16));
    const __m128i c = _mm_or_si128(b, _mm_slli_epi32(b, 8));
    return _mm_sub_epi8(_mm_set1_epi32(0xffffffff), c);
  }
  case GL_DST_ALPHA: {
    const __m128i a = _mm_and_si128(dst, _mm_set1_epi32(0x000000ff));
    const __m128i b = _mm_or_si128(a, _mm_slli_epi32(a, 16));
    return _mm_or_si128(b, _mm_slli_epi32(b, 8));
  }
  case GL_ONE_MINUS_DST_ALPHA: {
    const __m128i a = _mm_and_si128(dst, _mm_set1_epi32(0x000000ff));
    const __m128i b = _mm_or_si128(a, _mm_slli_epi32(a, 16));
    const __m128i c = _mm_or_si128(b, _mm_slli_epi32(b, 8));
    return _mm_sub_epi8(_mm_set1_epi32(0xffffffff), c);
  }
  case GL_SRC_ALPHA_SATURATE:
    return _mm_setzero_si128(); // TODO
  default:
    __assume(0);
  }
}

// multiply packed 8 bit unsigned bytes
static __forceinline __m128i _mm_mulhi_epi8( __m128i x, __m128i y ) {
#if 0
    // unpack and multiply
    __m128i dst_even = _mm_mullo_epi16(x, y);
    __m128i dst_odd = _mm_mullo_epi16(_mm_srli_epi16(x, 8),
                                      _mm_srli_epi16(y, 8));
    // repack
    return _mm_or_si128(_mm_slli_epi16(dst_odd, 8),
                        _mm_srli_epi16(_mm_slli_epi16(dst_even,8), 8));
#else
    const __m128i zero = _mm_setzero_si128();

    // unpack 8 bits into 16 bits
    __m128i xlo = _mm_unpacklo_epi8( x, zero );
    __m128i ylo = _mm_unpacklo_epi8( y, zero );
    __m128i xhi = _mm_unpackhi_epi8( x, zero );
    __m128i yhi = _mm_unpackhi_epi8( y, zero );

    // x * y
    xlo = _mm_mullo_epi16( xlo, ylo );
    xhi = _mm_mullo_epi16( xhi, yhi );

    // >> 8
    xlo = _mm_srli_epi16( xlo, 8 );
    xhi = _mm_srli_epi16( xhi, 8 );

    // saturate and repack into 8 bits
    return _mm_packus_epi16( xlo, xhi );
#endif
}

// saturate(src * src_factor + dst * dst_factor)
template <GLenum srcf, GLenum dstf>
static __forceinline __m128i blend_sum(__m128i src, __m128i dst) {
  const __m128i sf = blend_factor<srcf>(src, dst);
  const __m128i df = blend_factor<dstf>(src, dst);
  return _mm_adds_epu8(_mm_mulhi_epi8(src, sf),
                       _mm_mulhi_epi8(dst, df));
}
