#pragma once
#include <memory>
#include <cstdint>

#include "surface.h"


struct buffer_manager_t {

  void resize(int32_t w, int32_t h);

  uint32_t width() const {
    return _width;
  }

  uint32_t height() const {
    return _height;
  }

  uint32_t *pixels() const {
    return _pixels.get();
  }

  float *depth() const {
    return _depth.get();
  }

  surface_t &surface() {
    return _surface;
  }

protected:
  uint32_t _width, _height;
  std::unique_ptr<uint32_t[]> _pixels;
  std::unique_ptr<float[]> _depth;
  surface_t _surface;
};
