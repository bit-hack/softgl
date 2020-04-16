#pragma once

static inline void stamp_affine(
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
  __m128 Sv1 = step_x(v1, s.vx[s.slot_w1]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz = step_x(z, s.vx[s.slot_z]);

  const int32_t tw = tex._width >> s.mip_level;
  const int32_t twm = tw - 1;
  __m128 Sux = _mm_set1_ps(s.vx[s.slot_u] * 4.f * tw);
  __m128 Suy = _mm_set1_ps(s.vy[s.slot_u] * tw);
  __m128 Su = step_x(u * tw, s.vx[s.slot_u] * tw);
  __m128i Stwm = _mm_set_epi32(twm, twm, twm, twm);

  const int32_t th = tex._height >> s.mip_level;
  const int32_t thm = th - 1;
  __m128 Svx = _mm_set1_ps(s.vx[s.slot_v] * 4.f * th);
  __m128 Svy = _mm_set1_ps(s.vy[s.slot_v] * th);
  __m128 Sv = step_x(v * th, s.vx[s.slot_v] * th);
  __m128i Sthm = _mm_set_epi32(thm, thm, thm, thm);

  const int32_t wshift = std::max<int32_t>(0, int32_t(tex._wshift) - int32_t(s.mip_level));
  const uint32_t *texel = tex._pixels[s.mip_level];

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    __m128 Sv0_ = Sv0;
    __m128 Sv1_ = Sv1;
    __m128 Sz_  = Sz;
    __m128 Su_  = Su;
    __m128 Sv_  = Sv;

    for (int x = 0; x < BLOCK_SIZE; x += 4) {

      // third edge coefficient
      // const float v2_ = 1.f - (v0_ + v1_);
      __m128 Sv2_ = _mm_sub_ps(_mm_set_ps1(1.f), _mm_add_ps(Sv0_, Sv1_));

      // load depth values
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      __m128 zbuf = _mm_load_ps(depth + x);
#endif

      // triangle edge test
      // if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {
      __m128 m0 = _mm_cmpge_ps(Sv0_, _mm_setzero_ps());
      __m128 m1 = _mm_cmpge_ps(Sv1_, _mm_setzero_ps());
      __m128 m2 = _mm_cmpge_ps(Sv2_, _mm_setzero_ps());

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      __m128 keep = _mm_and_ps(_mm_and_ps(m0, DEPTH_CMP(Sz_, zbuf)),
                               _mm_and_ps(m1, m2));
#else
      __m128 keep = _mm_and_ps(m0, _mm_and_ps(m1, m2));
#endif

#if DEPTH_WRITE
      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);
#endif

#if COLOR_WRITE
      // u / (1/w),  v / (1/w)
      // ((int32_t(u/iw)&twm) +
      //  (int32_t(u/iw)&twm) << tex._wshift)
      const __m128i tu  = _mm_and_si128(_mm_cvtps_epi32(Su_), Stwm);
      const __m128i tv  = _mm_and_si128(_mm_cvtps_epi32(Sv_), Sthm);
      const __m128i ti  = _mm_add_epi32(tu, _mm_slli_epi32(tv, wshift));

      // extract texture indices
      const uint32_t ti0 = _mm_extract_epi32(ti, 0);
      const uint32_t ti1 = _mm_extract_epi32(ti, 1);
      const uint32_t ti2 = _mm_extract_epi32(ti, 2);
      const uint32_t ti3 = _mm_extract_epi32(ti, 3);

      // load from the texture
      const uint32_t tc0 = texel[ti0];
      const uint32_t tc1 = texel[ti1];
      const uint32_t tc2 = texel[ti2];
      const uint32_t tc3 = texel[ti3];

      // blend equation
#if (SRC_BLEND == GL_ONE) && (DST_BLEND == GL_ZERO)
      // special case for one and zero since out is directly our source
      const __m128i out = _mm_set_epi32(tc3, tc2, tc1, tc0);
#else
      // generic case where we have an arbitary blending equation
      const __m128i src = _mm_set_epi32(tc3, tc2, tc1, tc0);
      const __m128i dst = _mm_load_si128((__m128i*)(color + x));
      const __m128i out = blend_sum<SRC_BLEND, DST_BLEND>(src, dst);
#endif

      // color write
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), out);
#endif

      // x-axis step
      Sv0_ = _mm_add_ps(Sv0_, Sv0x);
      Sv1_ = _mm_add_ps(Sv1_, Sv1x);
      Sz_  = _mm_add_ps(Sz_ , Szx );
      Su_  = _mm_add_ps(Su_ , Sux );
      Sv_  = _mm_add_ps(Sv_ , Svx );
    }

    // y-axis step
    Sv0 = _mm_add_ps(Sv0, Sv0y);
    Sv1 = _mm_add_ps(Sv1, Sv1y);
    Sz  = _mm_add_ps(Sz , Szy );
    Su  = _mm_add_ps(Su , Suy );
    Sv  = _mm_add_ps(Sv , Svy );

    // framebuffer step
    color += pitch;
    depth += pitch;
  }
}

static inline void stamp(
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
  __m128 Sv1 = step_x(v1, s.vx[s.slot_w1]);

  __m128 Siwx = _mm_set1_ps(s.vx[s.slot_iw] * 4.f);
  __m128 Siwy = _mm_set1_ps(s.vy[s.slot_iw]);
  __m128 Siw = step_x(iw, s.vx[s.slot_iw]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz = step_x(z, s.vx[s.slot_z]);

  const int32_t tw = tex._width >> s.mip_level;
  const int32_t twm = tw - 1;
  __m128 Sux = _mm_set1_ps(s.vx[s.slot_u] * 4.f * tw);
  __m128 Suy = _mm_set1_ps(s.vy[s.slot_u] * tw);
  __m128 Su = step_x(u * tw, s.vx[s.slot_u] * tw);
  __m128i Stwm = _mm_set_epi32(twm, twm, twm, twm);

  const int32_t th = tex._height >> s.mip_level;
  const int32_t thm = th - 1;
  __m128 Svx = _mm_set1_ps(s.vx[s.slot_v] * 4.f * th);
  __m128 Svy = _mm_set1_ps(s.vy[s.slot_v] * th);
  __m128 Sv = step_x(v * th, s.vx[s.slot_v] * th);
  __m128i Sthm = _mm_set_epi32(thm, thm, thm, thm);

  const int32_t wshift = std::max<int32_t>(0, int32_t(tex._wshift) - int32_t(s.mip_level));
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
      const __m128 Sv2_ = _mm_sub_ps(_mm_set_ps1(1.f), _mm_add_ps(Sv0_, Sv1_));

      // load depth values
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      const __m128 zbuf = _mm_load_ps(depth + x);
#endif

      // triangle edge test
      // if (v0_ > 0.f && v1_ > 0.f && v2_ > 0.f) {
      const __m128 m0 = _mm_cmpge_ps(Sv0_, _mm_setzero_ps());
      const __m128 m1 = _mm_cmpge_ps(Sv1_, _mm_setzero_ps());
      const __m128 m2 = _mm_cmpge_ps(Sv2_, _mm_setzero_ps());

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      const __m128 keep = _mm_and_ps(_mm_and_ps(m0, DEPTH_CMP(Sz_, zbuf)),
                               _mm_and_ps(m1, m2));
#else
      const __m128 keep = _mm_and_ps(m0, _mm_and_ps(m1, m2));
#endif

#if DEPTH_WRITE
      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);
#endif

#if COLOR_WRITE
      // find 1 / (1/w)
      const __m128 rw = _mm_rcp_ps(Siw_);

      // u / (1/w),  v / (1/w)
      // ((int32_t(u/iw)&twm) +
      //  (int32_t(u/iw)&twm) << tex._wshift)
      const __m128i tu  = _mm_and_si128(_mm_cvtps_epi32(_mm_mul_ps(Su_, rw)), Stwm);
      const __m128i tv  = _mm_and_si128(_mm_cvtps_epi32(_mm_mul_ps(Sv_, rw)), Sthm);
      const __m128i ti  = _mm_add_epi32(tu, _mm_slli_epi32(tv, wshift));

      // extract texture indices
      const uint32_t ti0 = _mm_extract_epi32(ti, 0);
      const uint32_t ti1 = _mm_extract_epi32(ti, 1);
      const uint32_t ti2 = _mm_extract_epi32(ti, 2);
      const uint32_t ti3 = _mm_extract_epi32(ti, 3);

      // load from the texture
      const uint32_t tc0 = texel[ti0];
      const uint32_t tc1 = texel[ti1];
      const uint32_t tc2 = texel[ti2];
      const uint32_t tc3 = texel[ti3];

      // blend equation
#if (SRC_BLEND == GL_ONE) && (DST_BLEND == GL_ZERO)
      // special case for one and zero since out is directly our source
      const __m128i out = _mm_set_epi32(tc3, tc2, tc1, tc0);
#else
      // generic case where we have an arbitary blending equation
      __m128i src = _mm_set_epi32(tc3, tc2, tc1, tc0);
      __m128i dst = _mm_load_si128((__m128i*)(color + x));
      __m128i out = blend_sum<SRC_BLEND, DST_BLEND>(src, dst);
#endif

      // color write
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), out);
#endif

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
static inline void stamp_ti(
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
  __m128 Siw = step_x(iw, s.vx[s.slot_iw]);

  __m128 Szx = _mm_set1_ps(s.vx[s.slot_z] * 4.f);
  __m128 Szy = _mm_set1_ps(s.vy[s.slot_z]);
  __m128 Sz = step_x(z, s.vx[s.slot_z]);

  const int32_t tw = tex._width >> s.mip_level;
  const int32_t twm = tw - 1;
  __m128 Sux = _mm_set1_ps(s.vx[s.slot_u] * 4.f * tw);
  __m128 Suy = _mm_set1_ps(s.vy[s.slot_u] * tw);
  __m128 Su = step_x(u * tw, s.vx[s.slot_u] * tw);
  __m128i Stwm = _mm_set_epi32(twm, twm, twm, twm);

  const int32_t th = tex._height >> s.mip_level;
  const int32_t thm = th - 1;
  __m128 Svx = _mm_set1_ps(s.vx[s.slot_v] * 4.f * th);
  __m128 Svy = _mm_set1_ps(s.vy[s.slot_v] * th);
  __m128 Sv = step_x(v * th, s.vx[s.slot_v] * th);
  __m128i Sthm = _mm_set_epi32(thm, thm, thm, thm);

  const int32_t wshift = std::max<int32_t>(0, int32_t(tex._wshift) - int32_t(s.mip_level));
  const uint32_t *texel = tex._pixels[s.mip_level];

  for (int y = 0; y < BLOCK_SIZE; ++y) {

    __m128 Siw_ = Siw;
    __m128 Sz_  = Sz;
    __m128 Su_  = Su;
    __m128 Sv_  = Sv;

    for (int x = 0; x < BLOCK_SIZE; x += 4) {

      // load depth values
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      const __m128 zbuf = _mm_load_ps(depth + x);
#endif

      // triangle edge test and depth (together)
      // if (zed <= depth[x]) {
#if DEPTH_TEST && (DEPTH_CMP != GL_ALWAYS) && (DEPTH_CMP != GL_NEVER)
      const __m128 keep = DEPTH_CMP(Sz_, zbuf);
#else
      const __m128 keep = _mm_castsi128_ps (_mm_set1_epi32(0xffffffff));
#endif

#if DEPTH_WRITE
      // depth write
      // depth[x] = zed;
      _mm_maskstore_ps(depth + x, _mm_castps_si128(keep), Sz_);
#endif

#if COLOR_WRITE
      // find 1 / (1/w)
      const __m128  rw = _mm_rcp_ps(Siw_);

      // u / (1/w),  v / (1/w)
      // ((int32_t(u/iw)&twm) +
      //  (int32_t(u/iw)&twm) << tex._wshift)
      const __m128i tu  = _mm_and_si128(_mm_cvtps_epi32(_mm_mul_ps(Su_, rw)), Stwm);
      const __m128i tv  = _mm_and_si128(_mm_cvtps_epi32(_mm_mul_ps(Sv_, rw)), Sthm);
      const __m128i ti  = _mm_add_epi32(tu, _mm_slli_epi32(tv, wshift));

      // extract texture indices
      const uint32_t ti0 = _mm_extract_epi32(ti, 0);
      const uint32_t ti1 = _mm_extract_epi32(ti, 1);
      const uint32_t ti2 = _mm_extract_epi32(ti, 2);
      const uint32_t ti3 = _mm_extract_epi32(ti, 3);

      // load from the texture
      const uint32_t tc0 = texel[ti0];
      const uint32_t tc1 = texel[ti1];
      const uint32_t tc2 = texel[ti2];
      const uint32_t tc3 = texel[ti3];

      // blend equation
#if (SRC_BLEND == GL_ONE) && (DST_BLEND == GL_ZERO)
      // special case for one and zero since out is directly our source
      const __m128i out = _mm_set_epi32(tc3, tc2, tc1, tc0);
#else
      // generic case where we have an arbitary blending equation
      const __m128i src = _mm_set_epi32(tc3, tc2, tc1, tc0);
      const __m128i dst = _mm_load_si128((__m128i*)(color + x));
      const __m128i out = blend_sum<SRC_BLEND, DST_BLEND>(src, dst);
#endif

      // color write
      _mm_maskstore_epi32((int*)color + x, _mm_castps_si128(keep), out);
#endif

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

void KERNEL_NAME (
    const frame_t &f,
    const triangle_setup_t &s,
    const texture_t &tex)
{
  const recti_t rect = { s.bound.x0                   & BLOCK_MASK,
                         s.bound.y0                   & BLOCK_MASK,
                        (s.bound.x1 + BLOCK_SIZE - 1) & BLOCK_MASK,
                        (s.bound.y1 + BLOCK_SIZE - 1) & BLOCK_MASK};
  const uint32_t  pitch = f._width;
  uint32_t *color = f._pixels + (rect.y0 * pitch);
  float    *depth = f._depth  + (rect.y0 * pitch);

  // for small triangles we can render them affine with out much visible
  // distortion giving us a speed boost.
  if (s.affine) {
    for (int32_t y = rect.y0; y < rect.y1; y += BLOCK_SIZE) {
      for (int32_t x = rect.x0; x < rect.x1; x += BLOCK_SIZE) {
        stamp_affine(s, tex, float2{float(x), float(y)}, color + x, depth + x, pitch);
      }
      // step the framebuffer
      color += pitch * BLOCK_SIZE;
      depth += pitch * BLOCK_SIZE;
    }
  }
  else {
    const auto &e0 = s.edge[0];
    const auto &e1 = s.edge[1];
    const auto &e2 = s.edge[2];
    for (int32_t y = rect.y0; y < rect.y1; y += BLOCK_SIZE) {
      for (int32_t x = rect.x0; x < rect.x1; x += BLOCK_SIZE) {
        const float2 min{float(x), float(y)};
        const float2 max{float(x + BLOCK_SIZE), float(y + BLOCK_SIZE)};

        // trivial out cases
        if (trivial_out(e0, min, max)) continue;
        if (trivial_out(e1, min, max)) continue;
        if (trivial_out(e2, min, max)) continue;

        // if we are fully inside the triangle we dont need to do any edge
        // tests so we special case the stamp
        if (trivial_in(e0, min, max) &&
            trivial_in(e1, min, max) &&
            trivial_in(e2, min, max)) {
          stamp_ti(s, tex, min, color + x, depth + x, pitch);
        } else {
          stamp(s, tex, min, color + x, depth + x, pitch);
        }
      }
      // step the framebuffer
      color += pitch * BLOCK_SIZE;
      depth += pitch * BLOCK_SIZE;
    }
  }
}
