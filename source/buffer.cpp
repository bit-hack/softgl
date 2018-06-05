#include "buffer.h"
#include "context.h"

buffer_manager_t::buffer_manager_t()
    : _width(0), _height(0), _pixels(nullptr), _depth(nullptr) {}

void buffer_manager_t::_release() {
  if (_pixels) {
    _aligned_free(_pixels);
    _pixels = nullptr;
  }
  if (_depth) {
    _aligned_free(_depth);
    _depth = nullptr;
  }
}

void buffer_manager_t::resize(int32_t w, int32_t h) {
  _width = w;
  _height = h;

  if (_pixels || _depth) {
    _release();
  }

  _pixels = (uint32_t *)_aligned_malloc(w * h * sizeof(uint32_t), 16);
  _depth = (float *)_aligned_malloc(w * h * sizeof(float), 16);
  // notify context of resize
  if (Context) {
    Context->on_resize();
  }
}
