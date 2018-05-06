#pragma once
#include <vector>

#include "math.h"


struct vertex_manager_t {

  void pushUV(const float2 &f);

  void pushColor(const float4 &f);

  void pushCoord(const float4 &f);

  void polygonMode(GLenum mode);

  void clear();

  std::vector<float4> vertices;
};
