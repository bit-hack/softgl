#pragma once
#include <cstdint>
#include <map>

#include "GL.h"
#include "common.h"

struct state_manager_t {

  state_manager_t() {
    memset(this, 0, sizeof(*this));
    clearColor = 0x101010;
  }

  GLenum beginMode;
  uint32_t clearColor;
  GLenum cullMode;
  rectf_t viewport;
  GLfloat clearDepth;
  rectf_t scissor;

  bool testAlpha;   // GL_ALPHA_TEST
  bool testDepth;   // GL_DEPTH_TEST
  bool cullFace;    // GL_CULL_FACE
  bool blendFrag;   // GL_BLEND
  bool testScissor; // GL_SCISSOR_TEST
  bool testStencil; // GL_STENCIL_TEST

  bool texture1D;   // GL_TEXTURE_1D
  bool texture2D;   // GL_TEXTURE_2D
};
