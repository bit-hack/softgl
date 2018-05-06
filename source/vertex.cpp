#include "context.h"
#include "vertex.h"


void vertex_manager_t::pushCoord(const float4 &f) {
  const float4 v = Context->matrix.transform(f);
#if 0
  Context->primative.vertex(v);
#else
  vertices.push_back(v);
#endif
}

void vertex_manager_t::clear() {
  vertices.clear();
}
