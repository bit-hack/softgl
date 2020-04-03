#pragma once
#include <vector>

#include "forward.h"

struct profile_t {

  virtual void on_end_frame() {};

  virtual void on_triangles(const std::vector<triangle_t> &t) {};
};

profile_t *profile_create();
