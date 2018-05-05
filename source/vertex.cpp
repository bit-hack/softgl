#include "context.h"
#include "vertex.h"


void vertex_manager_t::push(const float4 &f) {
  const float4 v = Context->matrix().transform(f);
  vertices.push_back(v);
}

void vertex_manager_t::clear() {
  vertices.clear();
}
