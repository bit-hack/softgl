#include <cassert>
#include <stdint.h>

#include "common.h"
#include "GL.h"
#include "context.h"
#include "exports.h"
#include "wgl.h"
#include "matrix.h"
#include "log.h"


#if 0
#define TRACE() { log_t::printf("%s\n", __func__); }
#define TRACE_FMT(...) { log_t::printf(__VA_ARGS__); }
#else
#define TRACE() {}
#define TRACE_FMT(...)
#endif

void __stdcall glAccum(GLenum op, GLfloat value) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glActiveTexture(GLenum texture) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glAlphaFunc(GLenum func, GLclampf ref) {
  TRACE();
  //
}

GLboolean __stdcall glAreTexturesResident(GLsizei n, const GLuint *textures,
                                          GLboolean *residences) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    return cxt->texture.glAreTexturesResident(n, textures, residences);
  }
  return GL_FALSE;
}

void __stdcall glArrayElement(GLint i) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glArrayElement(i);
  }
}

void __stdcall glBegin(GLenum mode) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glBegin(mode);
  }
}

void __stdcall glBindTexture(GLenum target, GLuint texture) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glBindTexture(target, texture);
  }
}

void __stdcall glBitmap(GLsizei width, GLsizei height, GLfloat xorig,
                        GLfloat yorig, GLfloat xmove, GLfloat ymove,
                        const GLubyte *bitmap) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glBlendFunc(GLenum sfactor, GLenum dfactor) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->state.blendFuncSrc = sfactor;
    cxt->state.blendFuncDst = dfactor;
  }
}

void __stdcall glCallList(GLuint list) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glCallLists(GLsizei n, GLenum type, const GLvoid *lists) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glClear(GLbitfield mask) {
  TRACE();
  if (gl_context_t *cxt = Context) {

    const bool color   = (0 != (mask & GL_COLOR_BUFFER_BIT));
    const bool depth   = (0 != (mask & GL_DEPTH_BUFFER_BIT));
    const bool stencil = (0 != (mask & GL_STENCIL_BUFFER_BIT));

    if (cxt->raster.inst) {
      cxt->raster.inst->framebuffer_clear(
        color, depth, stencil, 0x202020, 1000.f, 0);
    }
  }
}

void __stdcall glClearAccum(GLfloat red, GLfloat green, GLfloat blue,
                            GLfloat alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
  TRACE();
  int cr = 0xff & int(r * 255.f);
  int cg = 0xff & int(g * 255.f);
  int cb = 0xff & int(b * 255.f);
  int ca = 0xff & int(a * 255.f);
  auto &cc = Context->state.clearColor;
  cc = ca << 24 | cr << 16 | cg << 8 | cb;
}

void __stdcall glClearDepth(GLclampd depth) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->state.clearDepth = GLfloat(depth);
  }
}

void __stdcall glClearIndex(GLfloat c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glClearStencil(GLint s) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glClipPlane(GLenum plane, const GLdouble *equation) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3bv(const GLbyte *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_argb(float4{0.f, red, green, blue});
  }
}

void __stdcall glColor3fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_argb(float4{0.f, v[0], v[1], v[2]});
  }
}

void __stdcall glColor3i(GLint red, GLint green, GLint blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3s(GLshort red, GLshort green, GLshort blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3ubv(const GLubyte *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_argb(
      float4{
        0.f,
        float(v[0]) / 256.f,
        float(v[1]) / 256.f,
        float(v[2]) / 256.f}
    );
  }
}

void __stdcall glColor3ui(GLuint red, GLuint green, GLuint blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3uiv(const GLuint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3us(GLushort red, GLushort green, GLushort blue) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor3usv(const GLushort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4bv(const GLbyte *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4d(GLdouble red, GLdouble green, GLdouble blue,
                         GLdouble alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4f(GLfloat red, GLfloat green, GLfloat blue,
                         GLfloat alpha) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_argb(float4{alpha, red, green, blue});
  }
}

void __stdcall glColor4fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_argb(float4{v[3], v[0], v[1], v[2]});
  }
}

void __stdcall glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4s(GLshort red, GLshort green, GLshort blue,
                         GLshort alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4ub(GLubyte red, GLubyte green, GLubyte blue,
                          GLubyte alpha) {
  TRACE();
  //
}

void __stdcall glColor4ubv(const GLubyte *v) {
  TRACE();
  //
}

void __stdcall glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4uiv(const GLuint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4us(GLushort red, GLushort green, GLushort blue,
                          GLushort alpha) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColor4usv(const GLushort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColorMask(GLboolean red, GLboolean green, GLboolean blue,
                           GLboolean alpha) {
  TRACE();
  //
}

void __stdcall glColorMaterial(GLenum face, GLenum mode) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glColorPointer(GLint size, GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glColorPointer(size, type, stride, pointer);
  }
}

void __stdcall glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum type) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glCopyTexImage1D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLint border) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glCopyTexImage1D(target, level, internalFormat, x, y, width,
                                      border);
  }
}

void __stdcall glCopyTexImage2D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLsizei height, GLint border) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glCopyTexImage2D(target, level, internalFormat, x, y, width,
                                  height, border);
  }
}

void __stdcall glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                                   GLint x, GLint y, GLsizei width) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glCopyTexSubImage1D(target, level, xoffset, x, y, width);
  }
}

void __stdcall glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                                   GLint yoffset, GLint x, GLint y,
                                   GLsizei width, GLsizei height) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y,
                                     width, height);
  }
}

void __stdcall glCullFace(GLenum mode) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->state.cullMode = mode;
  }
}

void __stdcall glDebugEntry(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glDeleteLists(GLuint list, GLsizei range) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glDeleteTextures(GLsizei n, const GLuint *textures) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glDeleteTextures(n, textures);
  }
}

void __stdcall glDepthFunc(GLenum func) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->state.depthFunc = func;
  }
}

void __stdcall glDepthMask(GLboolean flag) {
  TRACE();
  //
}

void __stdcall glDepthRange(GLclampd zNear, GLclampd zFar) {
  TRACE();
  //
}

void __stdcall glDisable(GLenum cap) {
  TRACE_FMT("%s(0x%08x)\n", __func__, (int)cap);
  if (gl_context_t *cxt = Context) {
    auto &state = cxt->state;
    switch (cap) {
    case GL_TEXTURE_1D:   state.texture1D = false;    break;
    case GL_TEXTURE_2D:   state.texture2D = false;    break;
    case GL_ALPHA_TEST:   state.testAlpha = false;    break;
    case GL_DEPTH_TEST:   state.testDepth = false;    break;
    case GL_CULL_FACE:    state.cullFace = false;     break;
    case GL_BLEND:        state.blendFrag = false;    break;
    case GL_SCISSOR_TEST: state.testScissor = false;  break;
    case GL_STENCIL_TEST: state.testStencil = false;  break;
    default:
      break;
    }
  }
}

void __stdcall glDisableClientState(GLenum array) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glDrawBuffer(GLenum mode) {
  TRACE();
  //
}

void __stdcall glDrawElements(GLenum mode, GLsizei count, GLenum type,
                              const GLvoid *indices) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glDrawElements(mode, count, type, indices);
  }
}

void __stdcall glDrawRangeElements(GLenum mode,
                                   GLuint start,
                                   GLuint end,
                                   GLsizei count,
                                   GLenum type,
                                   const void * indices) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glDrawPixels(GLsizei width, GLsizei height, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlag(GLboolean flag) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlagPointer(GLsizei stride, const GLvoid *pointer) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlagv(const GLboolean *flag) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEnable(GLenum cap) {
  TRACE_FMT("%s(0x%08x)\n", __func__, (int)cap);
  if (gl_context_t *cxt = Context) {
    auto &state = cxt->state;
    switch (cap) {
    case GL_TEXTURE_1D:   state.texture1D = true;     break;
    case GL_TEXTURE_2D:   state.texture2D = true;     break;
    case GL_ALPHA_TEST:   state.testAlpha = true;     break;
    case GL_DEPTH_TEST:   state.testDepth = true;     break;
    case GL_CULL_FACE:    state.cullFace = true;      break;
    case GL_BLEND:        state.blendFrag = true;     break;
    case GL_SCISSOR_TEST: state.testScissor = true;   break;
    case GL_STENCIL_TEST: state.testStencil = true;   break;
    default:
      break;
    }
  }
}

void __stdcall glEnableClientState(GLenum array) {
  TRACE_FMT("%s(0x%08x)\n", __func__, (int)array);
  //
}

void __stdcall glEnd(void) {
  TRACE();
  //
  if (gl_context_t *cxt = Context) {
    cxt->primative.glEnd();
  }
}

void __stdcall glEndList(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1d(GLdouble u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1dv(const GLdouble *u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1f(GLfloat u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1fv(const GLfloat *u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2d(GLdouble u, GLdouble v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2dv(const GLdouble *u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2f(GLfloat u, GLfloat v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2fv(const GLfloat *u) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1,
                           GLint j2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalPoint1(GLint i) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glEvalPoint2(GLint i, GLint j) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glFinish(void) {
  TRACE();
  //
  if (gl_context_t *cxt = Context) {
    cxt->on_flush();
  }
}

void __stdcall glFlush(void) {
  TRACE();
#ifndef NDEBUG
  Sleep(5);
#endif
  //
  if (gl_context_t *cxt = Context) {
    cxt->on_flush();
  }
}

void __stdcall glFogf(GLenum pname, GLfloat param) {
  TRACE();
  //
//  DEBUG_BREAK;
}

void __stdcall glFogfv(GLenum pname, const GLfloat *params) {
  TRACE();
  //
//  DEBUG_BREAK;
}

void __stdcall glFogi(GLenum pname, GLint param) {
  TRACE();
  //
//  DEBUG_BREAK;
}

void __stdcall glFogiv(GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glFrontFace(GLenum mode) {
  TRACE();
  //
//  DEBUG_BREAK;
}

void __stdcall glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
                         GLdouble top, GLdouble zNear, GLdouble zFar) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glFrustum(
      float(left),
      float(right),
      float(bottom),
      float(top),
      float(zNear),
      float(zFar));
  }
}

GLuint __stdcall glGenLists(GLsizei range) {
  TRACE();
  //
  DEBUG_BREAK;
  return 0;
}

void __stdcall glGenTextures(GLsizei n, GLuint *textures) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glGenTextures(n, textures);
  }
}

void __stdcall glGetBooleanv(GLenum pname, GLboolean *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetClipPlane(GLenum plane, GLdouble *equation) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetDoublev(GLenum pname, GLdouble *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

GLenum __stdcall glGetError(void) {
  TRACE();
  //
  return 0;
}

void __stdcall glGetFloatv(GLenum pname, GLfloat *params) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    switch (pname) {
    case GL_MODELVIEW_MATRIX:
    {
      const matrix_t &m = cxt->matrix.modelview();
      memcpy(params, m.e.data(), sizeof(GLfloat) * 16);
      break;
    }
    case GL_PROJECTION_MATRIX:
    {
      const matrix_t &m = cxt->matrix.projection();
      memcpy(params, m.e.data(), sizeof(GLfloat) * 16);
      break;
    }
    default:
      DEBUG_BREAK;
    }
  }
}

void __stdcall glGetIntegerv(GLenum pname, GLint *params) {
  TRACE_FMT("%s(0x%08x, %p)\n", __func__, (int)pname, (void*)params);

  #define GL_MAX_TEXTURE_UNITS 0x84E2

  if (gl_context_t *cxt = Context) {
    switch (pname) {
    case GL_MAX_TEXTURE_SIZE:
      *params = 512;
      break;
    case GL_VIEWPORT:
      params[0] = GLint(cxt->state.viewport.x0);
      params[1] = GLint(cxt->state.viewport.y0);
      params[2] = GLint(cxt->state.viewport.dx());
      params[3] = GLint(cxt->state.viewport.dy());
      break;
    case GL_DEPTH_BITS: // UT2003 wants this
      *params = 24;
      break;
    case GL_STENCIL_BITS: // UT2003 wants this
      *params = 8;
      break;
    case GL_RED_BITS:
    case GL_GREEN_BITS:
    case GL_BLUE_BITS:
    case GL_ALPHA_BITS:
      *params = 8;
      break;
    case GL_MAX_TEXTURE_UNITS: // UT2003 wants this
      *params = 8;
      break;
    default:
      DEBUG_BREAK;
    }
  }
  else {
    DEBUG_BREAK;
  }
}

void __stdcall glGetLightfv(GLenum light, GLenum pname, GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetLightiv(GLenum light, GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapdv(GLenum target, GLenum query, GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapfv(GLenum target, GLenum query, GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapiv(GLenum target, GLenum query, GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetMaterialiv(GLenum face, GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapfv(GLenum map, GLfloat *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapuiv(GLenum map, GLuint *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapusv(GLenum map, GLushort *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetPointerv(GLenum pname, GLvoid **params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetPolygonStipple(GLubyte *mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

const GLubyte *__stdcall glGetString(GLenum name) {
  TRACE_FMT("%s(0x%08x)\n", __func__, (int)name);
  //
  switch (name) {
  case GL_VENDOR:
    return (GLubyte *)"8BitPimp";
  case GL_RENDERER:
    return (GLubyte *)"SoftGL";
  case GL_VERSION: // specifies opengl version
    return (GLubyte *)"2.0";
  case GL_EXTENSIONS: // space-separated list of supported extensions
    return (const GLubyte *)"GL_EXT_bgra GL_EXT_abgr ARB_multitexture";
  default:
    return (GLubyte *)"";
  }
}

void __stdcall glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexEnviv(GLenum target, GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGeniv(GLenum coord, GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexImage(GLenum target, GLint level, GLenum format,
                             GLenum type, GLvoid *pixels) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexLevelParameterfv(GLenum target, GLint level,
                                        GLenum pname, GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexLevelParameteriv(GLenum target, GLint level,
                                        GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexParameterfv(GLenum target, GLenum pname,
                                   GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glHint(GLenum target, GLenum mode) {
  TRACE();
  //
//  DEBUG_BREAK;
}

void __stdcall glIndexMask(GLuint mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexPointer(GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexd(GLdouble c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexdv(const GLdouble *c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexf(GLfloat c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexfv(const GLfloat *c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexi(GLint c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexiv(const GLint *c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexs(GLshort c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexsv(const GLshort *c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexub(GLubyte c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glIndexubv(const GLubyte *c) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glInitNames(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glInterleavedArrays(GLenum format, GLsizei stride,
                                   const GLvoid *pointer) {
  TRACE();
  //
  DEBUG_BREAK;
}

GLboolean __stdcall glIsEnabled(GLenum cap) {
  TRACE();
  //
  DEBUG_BREAK;
  return GL_FALSE;
}

GLboolean __stdcall glIsList(GLuint list) {
  TRACE();
  //
  DEBUG_BREAK;
  return GL_FALSE;
}

GLboolean __stdcall glIsTexture(GLuint texture) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    return cxt->texture.glIsTexture(texture);
  }
  return GL_FALSE;
}

void __stdcall glLightModelf(GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightModelfv(GLenum pname, const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightModeli(GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightModeliv(GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightf(GLenum light, GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightfv(GLenum light, GLenum pname, const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLighti(GLenum light, GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLightiv(GLenum light, GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLineStipple(GLint factor, GLushort pattern) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLineWidth(GLfloat width) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glListBase(GLuint base) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLoadIdentity(void) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glLoadIdentity();
  }
}

void __stdcall glLoadMatrixd(const GLdouble *m) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLoadMatrixf(const GLfloat *m) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glLoadMatrixf(m);
  }
}

void __stdcall glLoadName(GLuint name) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glLogicOp(GLenum opcode) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride,
                       GLint order, const GLdouble *points) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride,
                       GLint order, const GLfloat *points) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride,
                       GLint uorder, GLdouble v1, GLdouble v2, GLint vstride,
                       GLint vorder, const GLdouble *points) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride,
                       GLint uorder, GLfloat v1, GLfloat v2, GLint vstride,
                       GLint vorder, const GLfloat *points) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn,
                           GLdouble v1, GLdouble v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn,
                           GLfloat v1, GLfloat v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialf(GLenum face, GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialfv(GLenum face, GLenum pname, const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMateriali(GLenum face, GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialiv(GLenum face, GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glMatrixMode(GLenum mode) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glMatrixMode(mode);
  }
}

void __stdcall glMultMatrixd(const GLdouble *m) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glMultMatrixd(m);
  }
}

void __stdcall glMultMatrixf(const GLfloat *m) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glMultMatrixf(m);
  }
}

void __stdcall glNewList(GLuint list, GLenum mode) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3bv(const GLbyte *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
  TRACE();
  //
  // DEBUG_BREAK;
}

void __stdcall glNormal3fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3i(GLint nx, GLint ny, GLint nz) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glNormalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glOrtho(GLdouble left, GLdouble right, GLdouble bottom,
                       GLdouble top, GLdouble zNear, GLdouble zFar) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glOrtho(
      float(left),
      float(right),
      float(bottom),
      float(top),
      float(zNear),
      float(zFar));
  }
}

void __stdcall glPassThrough(GLfloat token) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapfv(GLenum map, GLsizei mapsize,
                            const GLfloat *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapuiv(GLenum map, GLsizei mapsize,
                             const GLuint *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapusv(GLenum map, GLsizei mapsize,
                             const GLushort *values) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelStoref(GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelStorei(GLenum pname, GLint param) {
  TRACE();
  //
  // skip for now
//  DEBUG_BREAK;
}

void __stdcall glPixelTransferf(GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelTransferi(GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPointSize(GLfloat size) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPolygonMode(GLenum face, GLenum mode) {
  TRACE();
  //
}

void __stdcall glPolygonOffset(GLfloat factor, GLfloat units) {
  TRACE();
  //
}

void __stdcall glPolygonStipple(const GLubyte *mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPop(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPopClient(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPopMatrix(void) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glPopMatrix();
  }
}

void __stdcall glPopName(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPrioritizeTextures(GLsizei n, const GLuint *textures,
                                    const GLclampf *priorities) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPush(GLbitfield mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPushClient(GLbitfield mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPushMatrix(void) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glPushMatrix();
  }
}

void __stdcall glPushName(GLuint name) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2d(GLdouble x, GLdouble y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2f(GLfloat x, GLfloat y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2i(GLint x, GLint y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2s(GLshort x, GLshort y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3i(GLint x, GLint y, GLint z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3s(GLshort x, GLshort y, GLshort z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glReadBuffer(GLenum mode) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectdv(const GLdouble *v1, const GLdouble *v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectfv(const GLfloat *v1, const GLfloat *v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectiv(const GLint *v1, const GLint *v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glRectsv(const GLshort *v1, const GLshort *v2) {
  TRACE();
  //
  DEBUG_BREAK;
}

GLint __stdcall glRenderMode(GLenum mode) {
  TRACE();
  //
  DEBUG_BREAK;
  return 0;
}

void __stdcall glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glRotatef(float(angle), float(x), float(y), float(z));
  }
}

void __stdcall glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glRotatef(angle, x, y, z);
  }
}

void __stdcall glScaled(GLdouble x, GLdouble y, GLdouble z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glScalef(float(x), float(y), float(z));
  }
}

void __stdcall glScalef(GLfloat x, GLfloat y, GLfloat z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glScalef(x, y, z);
  }
}

void __stdcall glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->state.scissor = rectf_t{
      float(x),
      float(y),
      float(x + width),
      float(y + height)};
  }
}

void __stdcall glSelectBuffer(GLsizei size, GLuint *buffer) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glShadeModel(GLenum mode) {
  TRACE_FMT("%s(0x%08x)\n", __func__, (int)mode);
  //
}

void __stdcall glStencilFunc(GLenum func, GLint ref, GLuint mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glStencilMask(GLuint mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1d(GLdouble s) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1f(GLfloat s) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1i(GLint s) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1s(GLshort s) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2d(GLdouble s, GLdouble t) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2f(GLfloat s, GLfloat t) {
  TRACE();
  Context->primative.latch_uv(float2{s, t});
}

void __stdcall glTexCoord2fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.latch_uv(float2{v[0], v[1]});
  }
}

void __stdcall glTexCoord2i(GLint s, GLint t) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2s(GLshort s, GLshort t) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3i(GLint s, GLint t, GLint r) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3s(GLshort s, GLshort t, GLshort r) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4fv(const GLfloat *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                 const GLvoid *pointer) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glTexCoordPointer(size, type, stride, pointer);
  }
}

void __stdcall glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
  TRACE();
  //
}

void __stdcall glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexEnvi(GLenum target, GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexEnviv(GLenum target, GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGend(GLenum coord, GLenum pname, GLdouble param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGendv(GLenum coord, GLenum pname, const GLdouble *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGeni(GLenum coord, GLenum pname, GLint param) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexGeniv(GLenum coord, GLenum pname, const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexImage1D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLint border, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexImage2D(GLenum target, GLint level, GLint internalFormat,
                            GLsizei width, GLsizei height, GLint border,
                            GLenum format, GLenum type, const GLvoid *pixels) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glTexImage2D(target, level, internalFormat, width,
                              height, border, format, type, pixels);
  }
}

void __stdcall glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
  TRACE();
  //
}

void __stdcall glTexParameterfv(GLenum target, GLenum pname,
                                const GLfloat *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexParameteri(GLenum target, GLenum pname, GLint param) {
  TRACE();
  //
}

void __stdcall glTexParameteriv(GLenum target, GLenum pname,
                                const GLint *params) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                               GLsizei width, GLenum format, GLenum type,
                               const GLvoid *pixels) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->texture.glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
  }
}

void __stdcall glTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                               GLint yoffset, GLsizei width, GLsizei height,
                               GLenum format, GLenum type,
                               const GLvoid *pixels) {
  TRACE();
  //
}

void __stdcall glTranslated(GLdouble x, GLdouble y, GLdouble z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glTranslatef(float(x), float(y), float(z));
  }
}

void __stdcall glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->matrix.glTranslatef(x, y, z);
  }
}

void __stdcall glVertex2d(GLdouble x, GLdouble y) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glVertex2dv(const GLdouble *v) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glVertex2f(GLfloat x, GLfloat y) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(float4{x, y, 0, 1.f});
  }
}

void __stdcall glVertex2fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(float4{v[0], v[1], 0, 1.f});
  }
}

void __stdcall glVertex2i(GLint x, GLint y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2s(GLshort x, GLshort y) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(
      float4{x, y, z, 1.f});
  }
}

void __stdcall glVertex3fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(
      float4{v[0], v[1], v[2], 1.f});
  }
}

void __stdcall glVertex3i(GLint x, GLint y, GLint z) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(
      float4{float(x), float(y), float(z), 1.f});
  }
}

void __stdcall glVertex3iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3s(GLshort x, GLshort y, GLshort z) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4dv(const GLdouble *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(float4{x, y, z, w});
  }
}

void __stdcall glVertex4fv(const GLfloat *v) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.add_vertex(float4{v[0], v[1], v[2], v[3]});
  }
}

void __stdcall glVertex4i(GLint x, GLint y, GLint z, GLint w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4iv(const GLint *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4sv(const GLshort *v) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glVertexPointer(GLint size, GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->primative.glVertexPointer(size, type, stride, pointer);
  }
}

void __stdcall glViewport(GLint x, GLint y, GLsizei w, GLsizei h) {
  TRACE();
  if (gl_context_t *cxt = Context) {
    cxt->on_flush();
    cxt->state.viewport = rectf_t{float(x), float(y), float(x + w), float(y + h)};
  }
}

void __stdcall glPushAttrib(GLbitfield mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPopAttrib(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPushClientAttrib(GLbitfield mask) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glPopClientAttrib(void) {
  TRACE();
  //
  DEBUG_BREAK;
}

void __stdcall glCompressedTexSubImage2DARB(GLenum target, GLint level,
                                            GLint xoffset, GLint yoffset,
                                            GLsizei width, GLsizei height,
                                            GLenum format, GLsizei imageSize,
                                            GLvoid *data) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glCompressedTexImage2DARB(GLenum target, GLint level,
                                         GLint internalformat, GLsizei width,
                                         GLsizei height, GLint border,
                                         GLsizei imageSize, GLvoid *data) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord1dARB(GLenum target, GLdouble s) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord1fARB(GLenum target, GLfloat s) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord1iARB(GLenum target, GLint s) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord1sARB(GLenum target, GLshort s) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord2iARB(GLenum target, GLint s, GLint t) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t,
                                    GLdouble r) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t,
                                    GLfloat r) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t,
                                    GLshort r) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t,
                                    GLdouble r, GLdouble q) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t,
                                    GLfloat r, GLfloat q) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r,
                                    GLint q) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t,
                                    GLshort r, GLshort q) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glActiveTextureARB(GLenum texture) {
  TRACE();
  DEBUG_BREAK;
}

void __stdcall glClientActiveTextureARB(GLenum texture) {
  TRACE();
  DEBUG_BREAK;
}
