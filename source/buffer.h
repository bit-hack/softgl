#pragma once
#include <memory>
#include <cstdint>

#include "surface.h"

struct buffer_manager_t {

  buffer_manager_t();

  ~buffer_manager_t() { _release(); }

  void resize(int32_t w, int32_t h);

  uint32_t width() const { return _width; }

  uint32_t height() const { return _height; }

  uint32_t *pixels() const { return _pixels; }

  float *depth() const {
    assert(_depth);
    return _depth;
  }

  surface_t &surface() {
    assert(_pixels);
    return _surface;
  }

  void clear_depth() {
    const int32_t area = _width * _height;
    const float *end = _depth + area;
    float *ptr = _depth;
    for (; ptr != end; ++ptr) {
      *ptr = 0.f;
    }
  }

protected:
  void _release();

  uint32_t _width, _height;
  uint32_t *_pixels;
  float *_depth;
  surface_t _surface;
};
