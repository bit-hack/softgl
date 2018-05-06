#pragma once
#include <cstdint>

#include "GL.h"


struct rectf_t {
  float x, y, w, h;
};

struct state_manager_t {
  GLenum beginMode;
  uint32_t clearColor;
  GLenum cullMode;
  rectf_t viewport;
  GLfloat clearDepth;
  rectf_t scissor;
};
