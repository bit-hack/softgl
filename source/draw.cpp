#include <algorithm>
#include <math.h>

#include "draw.h"
#include "math.h"

namespace {

//
// faster packed 4 x 8bit fixed point multiply
//
uint32_t alpha(uint32_t a, uint32_t b, uint8_t i) {
#if 0
    const uint32_t t0 = ((a & 0xff00ff) + ((b & 0xff00ff) - (a & 0xff00ff)) * i) >> 8;
    const uint32_t t1 = ((a & 0x00ff00) + ((b & 0x00ff00) - (a & 0x00ff00)) * i) >> 8;
    return (t0 & 0xff00ff) | (t1 & 0x00ff00);
#else
    // pixel a
    const uint32_t a0 = ((a & 0xff00ff) * ~i) >> 8;
    const uint32_t a1 = ((a & 0x00ff00) * ~i) >> 8;
    // pixel b
    const uint32_t b0 = ((b & 0xff00ff) *  i) >> 8;
    const uint32_t b1 = ((b & 0x00ff00) *  i) >> 8;
    // mix results
    return ((a0 & 0xff00ff) | (a1 & 0xff00)) +
           ((b0 & 0xff00ff) | (b1 & 0xff00));
#endif
}

} // namespace {}

// return true  - all out
//        false - inside or partial in
bool surface_t::line_clip(float2 &a, float2 &b) {

  enum {
    CLIP_X_LO = 1,
    CLIP_X_HI = 2,
    CLIP_Y_LO = 4,
    CLIP_Y_HI = 8,
  };

  const float min_x = 1.f;
  const float min_y = 1.f;
  const float max_x = float(_width)  - 2;
  const float max_y = float(_height) - 2;

  static const auto classify_x = [=](const float2 &p) -> int {
    return (p.x < min_x ? CLIP_X_LO : 0) | (p.x > max_x ? CLIP_X_HI : 0);
  };

  static const auto classify_y = [=](const float2 &p) -> int {
    return (p.y < min_y ? CLIP_Y_LO : 0) | (p.y > max_y ? CLIP_Y_HI : 0);
  };

  static const auto classify = [=](const float2 &p) -> int {
    return classify_x(p) | classify_y(p);
  };

  static const auto clip_y_lo = [=](int cl, float2 &va, const float2 &vb) {
    if (cl & CLIP_Y_LO) {
      const float dx = (vb.x - va.x) / (vb.y - va.y);
      va.x += dx * (min_y - va.y);
      va.y = min_y;
    }
  };

  static const auto clip_y_hi = [=](int cl, float2 &va, const float2 &vb) {
    if (cl & CLIP_Y_HI) {
      const float dx = (vb.x - va.x) / (vb.y - va.y);
      va.x -= dx * (va.y - max_y);
      va.y = max_y;
    }
  };

  static const auto clip_x_lo = [=](int cl, float2 &va, const float2 &vb) {
    if (cl & CLIP_X_LO) {
      const float dy = (vb.y - va.y) / (vb.x - va.x);
      va.y += dy * (min_x - va.x);
      va.x = min_x;
    }
  };

  static const auto clip_x_hi = [=](int cl, float2 &va, const float2 &vb) {
    if (cl & CLIP_X_HI) {
      const float dy = (vb.y - va.y) / (vb.x - va.x);
      va.y -= dy * (va.x - max_x);
      va.x = max_x;
    }
  };

  for (uint32_t i = 0;; ++i) {

    if ((fabs(b.x - a.x) + fabs(b.y - a.y)) < 1.f) {
      // remove ultra tiny points
      return true;
    }

    const int ca = classify(a);
    const int cb = classify(b);

    if (0 == (ca | cb)) {
      // all in center, no clipping
      return false;
    }

    const int code = ca & cb;
    if ((code & CLIP_X_LO) || (code & CLIP_X_HI) ||
        (code & CLIP_Y_LO) || (code & CLIP_Y_HI)) {
      // all outside one plane
      return true;
    }

    // todo: clip longest axis first?

    switch (i) {
    case 0:
      clip_x_lo(ca, a, b);
      clip_x_hi(ca, a, b);
      clip_x_lo(cb, b, a);
      clip_x_hi(cb, b, a);
      break;
    case 1:
      clip_y_lo(ca, a, b);
      clip_y_hi(ca, a, b);
      clip_y_lo(cb, b, a);
      clip_y_hi(cb, b, a);
      break;
    default:
      assert(!"bad clip");
    }
  }

  return false;
}

// fast fixed point line drawing
void surface_t::line(float2 a, float2 b, uint32_t rgb) {

  // clip line to screen
  if (line_clip(a, b)) {
    // fully clipped
    return;
  }

  const float dx = b.x - a.x, dy = b.y - a.y;
  const float adx = fabsf(dx), ady = fabs(dy);

  static const float fract = float(1u << 16);

  // select the longest axis
  if (fabsf(dx) > fabsf(dy)) {

    // sort vertices in y axis
    if (b.x < a.x)
      std::swap(a, b);
    // compute dy/dx
    const float ndy = (b.y - a.y) / adx;
    // convert y itterator to fixed point
    const int32_t iy = int32_t(ndy * fract);
    int32_t y = int32_t(a.y * fract);

    // quantize start and end locations
    const int32_t iax = int32_t(a.x);
    const int32_t ibx = int32_t(b.x);
    // raster loop
    {
      for (int32_t x = iax; x < ibx; ++x, y += iy) {
        _pixels[x + (y >> 16) * _pitch] = rgb;
      }
    }
  } else {
    // sort vertices in y axis
    if (b.y < a.y)
      std::swap(a, b);
    // compute dx/dy
    const float ndx = (b.x - a.x) / ady;
    // convert x itterator to fixed point
    const int32_t ix = int32_t(ndx * fract);
    int32_t x = int32_t(a.x * fract);

    // quantize start and end locations
    const int32_t iay = int32_t(a.y);
    const int32_t iby = int32_t(b.y);
    // raster loop
    {
      uint32_t *pix = _pixels + (x >> 16) + iay * _pitch;
      int32_t xstep = ix > 0 ? 1 : -1;
      for (int32_t y = iay; y < iby; ++y, x += ix) {
        _pixels[(x >> 16) + y * _pitch] = rgb;
      }
    }
  }
}

// fast fixed point anti-aliased line drawing
void surface_t::wuline(float2 a, float2 b, uint32_t rgb) {

  // clip line to screen
  if (line_clip(a, b)) {
    // fully clipped
    return;
  }

  const float dx = b.x - a.x, dy = b.y - a.y;
  const float adx = fabsf(dx), ady = fabs(dy);

  static const float point = float(1u << 16);

  // select the longest axis
  if (fabsf(dx) > fabsf(dy)) {
    // sort vertices in x axis
    if (b.x < a.x)
      std::swap(a, b);
    // compute dy/dx
    const float ndy = (b.y - a.y) / adx;
    // convert y itterator to fixed point
    const int32_t iy = int32_t(ndy * point);
    int32_t y = int32_t(a.y * point);
    // quantize start and end locations
    const int32_t iax = int32_t(a.x);
    const int32_t ibx = int32_t(b.x);
    // raster loop
    {
      for (int32_t x = iax; x < ibx; ++x, y += iy) {
        const uint32_t fract = (y & 0xffff) >> 8;
        uint32_t &p0 = _pixels[x + (y >> 16) * _pitch];
        uint32_t &p1 = _pixels[x + (y >> 16) * _pitch + _pitch];
        p0 = alpha(rgb, p0, fract);
        p1 = alpha(rgb, p1, fract ^ 0xff);
      }
    }
  } else {
    // sort vertices in y axis
    if (b.y < a.y)
      std::swap(a, b);
    // compute dx/dy
    const float ndx = (b.x - a.x) / ady;
    // convert x itterator to fixed point
    const int32_t ix = int32_t(ndx * point);
    int32_t x = int32_t(a.x * point);
    // quantize start and end locations
    const int32_t iay = int32_t(a.y);
    const int32_t iby = int32_t(b.y);
    // raster loop
    {
      uint32_t *pix = _pixels + (x >> 16) + iay * _pitch;
      int32_t xstep = ix > 0 ? 1 : -1;
      for (int32_t y = iay; y < iby; ++y, x += ix) {
        const uint32_t fract = (x & 0xffff) >> 8;
        uint32_t &p0 = _pixels[(x >> 16) + y * _pitch];
        uint32_t &p1 = _pixels[(x >> 16) + y * _pitch + 1];
        p0 = alpha(rgb, p0, fract);
        p1 = alpha(rgb, p1, fract ^ 0xff);
      }
    }
  }
}

void surface_t::plot(const float2 &p, uint32_t rgb) {
  const int32_t x = int32_t(floorf(p.x));
  const int32_t y = int32_t(floorf(p.y));
  if (x < 0 || y < 0 || x >= int32_t(_width) || y >= int32_t(_height)) {
    return;
  }
  _pixels[x + y * _pitch] = rgb;
}

void surface_t::wuplot(const float2 &p, uint32_t rgb) {

  if (p.x < 0 || p.x >= int32_t(_width -1) ||
      p.y < 0 || p.y >= int32_t(_height-1)) {
    return;
  }

  const float ix = floorf(p.x);
  const float iy = floorf(p.y);

  const float fx = p.x - ix;
  const float fy = p.y - iy;

  const uint32_t bx = uint32_t(fx * 0xff);
  const uint32_t by = uint32_t(fy * 0xff);
  const uint32_t jx = bx ^ 0xff;
  const uint32_t jy = by ^ 0xff;

  uint32_t &p00 = _pixels[int32_t(ix + 0) + int32_t(iy + 0) * _pitch];
  uint32_t &p10 = _pixels[int32_t(ix + 1) + int32_t(iy + 0) * _pitch];
  uint32_t &p01 = _pixels[int32_t(ix + 0) + int32_t(iy + 1) * _pitch];
  uint32_t &p11 = _pixels[int32_t(ix + 1) + int32_t(iy + 1) * _pitch];

  p00 = alpha(rgb, p00, 0xff ^ ((jx * jy) >> 8));
  p10 = alpha(rgb, p10, 0xff ^ ((bx * jy) >> 8));
  p01 = alpha(rgb, p01, 0xff ^ ((jx * by) >> 8));
  p11 = alpha(rgb, p11, 0xff ^ ((bx * by) >> 8));
}

void surface_t::fill(uint32_t rgb) {
  const uint32_t len = _pitch * _height;
  for (uint32_t i = 0; i < len; ++i) {
    _pixels[i] = rgb;
  }
}
