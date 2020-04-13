#include "../kernel.h"


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
      __m128 keep = _mm_and_ps(_mm_and_ps(m0, _mm_cmplt_ps(Sz_, zbuf)),
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
