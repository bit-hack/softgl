#pragma once
#include <cstdint>
#include <map>

#include "GL.h"
#include "common.h"

struct state_manager_t {

  state_manager_t() {
    memset(this, 0, sizeof(*this));
    clearColor = 0x101010;

    array_vertex = true;
    cullMode = GL_BACK;
    cullFace = true;

    frontFace = GL_CCW;

    depthRangeNear = 0.f;
    depthRangeFar = 1.f;
  }

  // set by glDepthRange
  // this used by quake3 when drawing the sky
  GLfloat depthRangeNear;
  GLfloat depthRangeFar;

  GLenum beginMode;
  uint32_t clearColor;
  GLenum cullMode;
  rectf_t viewport;
  GLfloat clearDepth;
  rectf_t scissor;

  GLenum blendFuncSrc;
  GLenum blendFuncDst;
  GLenum depthFunc;

  GLenum frontFace; // defaults to GL_CCW

  bool testAlpha;   // GL_ALPHA_TEST
  bool testDepth;   // GL_DEPTH_TEST
  bool cullFace;    // GL_CULL_FACE
  bool blendFrag;   // GL_BLEND
  bool testScissor; // GL_SCISSOR_TEST
  bool testStencil; // GL_STENCIL_TEST

  bool texture1D;   // GL_TEXTURE_1D
  bool texture2D;   // GL_TEXTURE_2D

  bool array_color;
  bool array_vertex;
  bool array_tex_coord;
};
