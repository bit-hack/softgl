#pragma once
#include <vector>

#include "math.h"


struct vertex_manager_t {

  void push(const float4 &f);

  void clear();

  std::vector<float4> vertices;
};
