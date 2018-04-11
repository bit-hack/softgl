#include "context.h"

void gl_context_t::resize(uint32_t w, uint32_t h) {
  buffer.width = w;
  buffer.height = h;
  // create buffers
  buffer.pixels = std::make_unique<uint32_t[]>(w * h);
  buffer.depth = std::make_unique<float[]>(w * h);
}
