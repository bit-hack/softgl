#pragma once
#include <cstdint>
#include <cassert>

#include "math.h"


struct surface_t {

  surface_t() = default;

  surface_t(uint32_t *pixels, uint32_t width, uint32_t height, uint32_t pitch)
    : _pixels(pixels)
    , _width(width)
    , _height(height)
    , _pitch(pitch)
  {
    assert(pixels && width && height && pitch);
  }

  uint32_t width() const {
    return _width;
  }

  uint32_t height() const {
    return _height;
  }

  uint32_t pitch() const {
    return _pitch;
  }

  uint32_t *pixels() {
    return _pixels;
  }

  const uint32_t *pixels() const {
    return _pixels;
  }

  void plot(const float2 &a, uint32_t rgb);
  void wuplot(const float2 &a, uint32_t rgb);

  void line(float2 a, float2 b, uint32_t rgb);
  void wuline(float2 a, float2 b, uint32_t rgb);

  void fill(uint32_t rgb);

protected:
  bool line_clip(float2 &a, float2 &b);

  uint32_t *_pixels;
  uint32_t _pitch;
  uint32_t _width;
  uint32_t _height;
};
