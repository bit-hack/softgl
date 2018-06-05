#include <cassert>
#include <stdint.h>

#include "common.h"
#include "GL.h"
#include "context.h"
#include "exports.h"
#include "wgl.h"
#include "matrix.h"


void __stdcall glAccum(GLenum op, GLfloat value) {
  //
  DEBUG_BREAK;
}

void __stdcall glActiveTexture(GLenum texture) {
  //
  DEBUG_BREAK;
}

void __stdcall glAlphaFunc(GLenum func, GLclampf ref) {
  //
//  DEBUG_BREAK;
}

GLboolean __stdcall glAreTexturesResident(GLsizei n, const GLuint *textures,
                                          GLboolean *residences) {
  return Context->texture.glAreTexturesResident(n, textures, residences);
}

void __stdcall glArrayElement(GLint i) {
  Context->primative.glArrayElement(i);
}

void __stdcall glBegin(GLenum mode) {
  assert(Context);
  auto &cxt = *Context;
  // save primative mode
  Context->primative.glBegin(mode);
}

void __stdcall glBindTexture(GLenum target, GLuint texture) {
  Context->texture.glBindTexture(target, texture);
}

void __stdcall glBitmap(GLsizei width, GLsizei height, GLfloat xorig,
                        GLfloat yorig, GLfloat xmove, GLfloat ymove,
                        const GLubyte *bitmap) {
  //
  DEBUG_BREAK;
}

void __stdcall glBlendFunc(GLenum sfactor, GLenum dfactor) {
  //
//  DEBUG_BREAK;
}

void __stdcall glCallList(GLuint list) {
  //
  DEBUG_BREAK;
}

void __stdcall glCallLists(GLsizei n, GLenum type, const GLvoid *lists) {
  //
  DEBUG_BREAK;
}

void __stdcall glClear(GLbitfield mask) {
  if (mask & GL_COLOR_BUFFER_BIT) {
    Context->buffer.clear_colour(0x202020);
  }
  if (mask & GL_DEPTH_BUFFER_BIT) {
    Context->buffer.clear_depth();
  }
}

void __stdcall glClearAccum(GLfloat red, GLfloat green, GLfloat blue,
                            GLfloat alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
  int cr = 0xff & int(r * 255.f);
  int cg = 0xff & int(g * 255.f);
  int cb = 0xff & int(b * 255.f);
  int ca = 0xff & int(a * 255.f);
  auto &cc = Context->state.clearColor;
  cc = ca << 24 | cr << 16 | cg << 8 | cb;
}

void __stdcall glClearDepth(GLclampd depth) {
  Context->state.clearDepth = GLfloat(depth);
}

void __stdcall glClearIndex(GLfloat c) {
  //
  DEBUG_BREAK;
}

void __stdcall glClearStencil(GLint s) {
  //
  DEBUG_BREAK;
}

void __stdcall glClipPlane(GLenum plane, const GLdouble *equation) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3bv(const GLbyte *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
  Context->primative.latch_argb(float4{0.f, red, green, blue});
}

void __stdcall glColor3fv(const GLfloat *v) {
  Context->primative.latch_argb(float4{0.f, v[0], v[1], v[2]});
}

void __stdcall glColor3i(GLint red, GLint green, GLint blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3s(GLshort red, GLshort green, GLshort blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3ubv(const GLubyte *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3ui(GLuint red, GLuint green, GLuint blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3uiv(const GLuint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3us(GLushort red, GLushort green, GLushort blue) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor3usv(const GLushort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4bv(const GLbyte *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4d(GLdouble red, GLdouble green, GLdouble blue,
                         GLdouble alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4f(GLfloat red, GLfloat green, GLfloat blue,
                         GLfloat alpha) {
  Context->primative.latch_argb(float4{alpha, red, green, blue});
}

void __stdcall glColor4fv(const GLfloat *v) {
  Context->primative.latch_argb(float4{v[3], v[0], v[1], v[2]});
}

void __stdcall glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4s(GLshort red, GLshort green, GLshort blue,
                         GLshort alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4ub(GLubyte red, GLubyte green, GLubyte blue,
                          GLubyte alpha) {
  //
//  DEBUG_BREAK;
}

void __stdcall glColor4ubv(const GLubyte *v) {
  //
//  DEBUG_BREAK;
}

void __stdcall glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4uiv(const GLuint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4us(GLushort red, GLushort green, GLushort blue,
                          GLushort alpha) {
  //
  DEBUG_BREAK;
}

void __stdcall glColor4usv(const GLushort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glColorMask(GLboolean red, GLboolean green, GLboolean blue,
                           GLboolean alpha) {
  //
//  DEBUG_BREAK;
}

void __stdcall glColorMaterial(GLenum face, GLenum mode) {
  //
  DEBUG_BREAK;
}

void __stdcall glColorPointer(GLint size, GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  Context->primative.glColorPointer(size, type, stride, pointer);
}

void __stdcall glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum type) {
  //
  DEBUG_BREAK;
}

void __stdcall glCopyTexImage1D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLint border) {
  Context->texture.glCopyTexImage1D(target, level, internalFormat, x, y, width,
                                    border);
}

void __stdcall glCopyTexImage2D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLsizei height, GLint border) {
  Context->texture.glCopyTexImage2D(target, level, internalFormat, x, y, width,
                                    height, border);
}

void __stdcall glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                                   GLint x, GLint y, GLsizei width) {
  Context->texture.glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void __stdcall glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                                   GLint yoffset, GLint x, GLint y,
                                   GLsizei width, GLsizei height) {
  Context->texture.glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y,
                                       width, height);
}

void __stdcall glCullFace(GLenum mode) {
  getContext()->state.cullMode = mode;
}

void __stdcall glDebugEntry(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glDeleteLists(GLuint list, GLsizei range) {
  //
  DEBUG_BREAK;
}

void __stdcall glDeleteTextures(GLsizei n, const GLuint *textures) {
  Context->texture.glDeleteTextures(n, textures);
}

void __stdcall glDepthFunc(GLenum func) {
  //
//  DEBUG_BREAK;
}

void __stdcall glDepthMask(GLboolean flag) {
  //
//  DEBUG_BREAK;
}

void __stdcall glDepthRange(GLclampd zNear, GLclampd zFar) {
  //
//  DEBUG_BREAK;
}

void __stdcall glDisable(GLenum cap) {
  switch (cap) {
  case GL_CULL_FACE:
  case GL_DEPTH_TEST:
  case GL_BLEND:
  case GL_ALPHA_TEST:
    break;
  default:
//    DEBUG_BREAK;
    break;
  }
}

void __stdcall glDisableClientState(GLenum array) {
  //
  DEBUG_BREAK;
}

void __stdcall glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  //
  DEBUG_BREAK;
}

void __stdcall glDrawBuffer(GLenum mode) {
  //
//  DEBUG_BREAK;
}

void __stdcall glDrawElements(GLenum mode, GLsizei count, GLenum type,
                              const GLvoid *indices) {
  Context->primative.glDrawElements(mode, count, type, indices);
}

void __stdcall glDrawPixels(GLsizei width, GLsizei height, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlag(GLboolean flag) {
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlagPointer(GLsizei stride, const GLvoid *pointer) {
  //
  DEBUG_BREAK;
}

void __stdcall glEdgeFlagv(const GLboolean *flag) {
  //
  DEBUG_BREAK;
}

void __stdcall glEnable(GLenum cap) {
  switch (cap) {
  case GL_TEXTURE_2D:
  case GL_ALPHA_TEST:
  case GL_CULL_FACE:
    break;
  default:
//    DEBUG_BREAK;
    break;
  }
}

void __stdcall glEnableClientState(GLenum array) {
  //
//  DEBUG_BREAK;
}

void __stdcall glEnd(void) {
  //
  Context->primative.glEnd();
}

void __stdcall glEndList(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1d(GLdouble u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1dv(const GLdouble *u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1f(GLfloat u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord1fv(const GLfloat *u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2d(GLdouble u, GLdouble v) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2dv(const GLdouble *u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2f(GLfloat u, GLfloat v) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalCoord2fv(const GLfloat *u) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1,
                           GLint j2) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalPoint1(GLint i) {
  //
  DEBUG_BREAK;
}

void __stdcall glEvalPoint2(GLint i, GLint j) {
  //
  DEBUG_BREAK;
}

void __stdcall glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer) {
  //
  DEBUG_BREAK;
}

void __stdcall glFinish(void) {
  //
  Context->on_flush();
}

void __stdcall glFlush(void) {
  //
  Context->on_flush();
}

void __stdcall glFogf(GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glFogfv(GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glFogi(GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glFogiv(GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glFrontFace(GLenum mode) {
  //
  DEBUG_BREAK;
}

void __stdcall glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
                         GLdouble top, GLdouble zNear, GLdouble zFar) {
  Context->matrix.glFrustum(
    float(left),
    float(right),
    float(bottom),
    float(top),
    float(zNear),
    float(zFar));
}

GLuint __stdcall glGenLists(GLsizei range) {
  //
  DEBUG_BREAK;
  return 0;
}

void __stdcall glGenTextures(GLsizei n, GLuint *textures) {
  Context->texture.glGenTextures(n, textures);
}

void __stdcall glGetBooleanv(GLenum pname, GLboolean *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetClipPlane(GLenum plane, GLdouble *equation) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetDoublev(GLenum pname, GLdouble *params) {
  //
  DEBUG_BREAK;
}

GLenum __stdcall glGetError(void) {
  //
//  DEBUG_BREAK;
  return 0;
}

void __stdcall glGetFloatv(GLenum pname, GLfloat *params) {
  switch (pname) {
  case GL_MODELVIEW_MATRIX: {
    const matrix_t &m = Context->matrix.modelview();
    memcpy(params, m.e.data(), sizeof(GLfloat) * 16);
    break;
  }
  case GL_PROJECTION_MATRIX: {
    const matrix_t &m = Context->matrix.projection();
    memcpy(params, m.e.data(), sizeof(GLfloat) * 16);
    break;
  }
  default:
    DEBUG_BREAK;
  }
}

void __stdcall glGetIntegerv(GLenum pname, GLint *params) {
  switch (pname) {
  case GL_MAX_TEXTURE_SIZE:
    *params = 512;
    break;
  case GL_VIEWPORT:
    params[0] = GLint(Context->state.viewport.x);
    params[1] = GLint(Context->state.viewport.y);
    params[2] = GLint(Context->state.viewport.w);
    params[3] = GLint(Context->state.viewport.h);
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
  default:
    DEBUG_BREAK;
  }
}

void __stdcall glGetLightfv(GLenum light, GLenum pname, GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetLightiv(GLenum light, GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapdv(GLenum target, GLenum query, GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapfv(GLenum target, GLenum query, GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetMapiv(GLenum target, GLenum query, GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetMaterialiv(GLenum face, GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapfv(GLenum map, GLfloat *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapuiv(GLenum map, GLuint *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetPixelMapusv(GLenum map, GLushort *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetPointerv(GLenum pname, GLvoid **params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetPolygonStipple(GLubyte *mask) {
  //
  DEBUG_BREAK;
}

const GLubyte *__stdcall glGetString(GLenum name) {
  //
  switch (name) {
  case GL_VENDOR:
    return (GLubyte *)"8BitPimp";
  case GL_RENDERER:
    return (GLubyte *)"SoftGL";
  case GL_VERSION: // specifies opengl version
    return (GLubyte *)"2.0";
  case GL_EXTENSIONS: // space-separated list of supported extensions
    return (const GLubyte *)"GL_EXT_bgra GL_EXT_abgr";
  default:
    return (GLubyte *)"";
  }
}

void __stdcall glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexEnviv(GLenum target, GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexGeniv(GLenum coord, GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexImage(GLenum target, GLint level, GLenum format,
                             GLenum type, GLvoid *pixels) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexLevelParameterfv(GLenum target, GLint level,
                                        GLenum pname, GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexLevelParameteriv(GLenum target, GLint level,
                                        GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexParameterfv(GLenum target, GLenum pname,
                                   GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glHint(GLenum target, GLenum mode) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexMask(GLuint mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexPointer(GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexd(GLdouble c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexdv(const GLdouble *c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexf(GLfloat c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexfv(const GLfloat *c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexi(GLint c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexiv(const GLint *c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexs(GLshort c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexsv(const GLshort *c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexub(GLubyte c) {
  //
  DEBUG_BREAK;
}

void __stdcall glIndexubv(const GLubyte *c) {
  //
  DEBUG_BREAK;
}

void __stdcall glInitNames(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glInterleavedArrays(GLenum format, GLsizei stride,
                                   const GLvoid *pointer) {
  //
  DEBUG_BREAK;
}

GLboolean __stdcall glIsEnabled(GLenum cap) {
  //
  DEBUG_BREAK;
  return GL_FALSE;
}

GLboolean __stdcall glIsList(GLuint list) {
  //
  DEBUG_BREAK;
  return GL_FALSE;
}

GLboolean __stdcall glIsTexture(GLuint texture) {
  //
  DEBUG_BREAK;
  return GL_FALSE;
}

void __stdcall glLightModelf(GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightModelfv(GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightModeli(GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightModeliv(GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightf(GLenum light, GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightfv(GLenum light, GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glLighti(GLenum light, GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glLightiv(GLenum light, GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glLineStipple(GLint factor, GLushort pattern) {
  //
  DEBUG_BREAK;
}

void __stdcall glLineWidth(GLfloat width) {
  //
  DEBUG_BREAK;
}

void __stdcall glListBase(GLuint base) {
  //
  DEBUG_BREAK;
}

void __stdcall glLoadIdentity(void) {
  Context->matrix.glLoadIdentity();
}

void __stdcall glLoadMatrixd(const GLdouble *m) {
  //
  DEBUG_BREAK;
}

void __stdcall glLoadMatrixf(const GLfloat *m) {
  Context->matrix.glLoadMatrixf(m);
}

void __stdcall glLoadName(GLuint name) {
  //
  DEBUG_BREAK;
}

void __stdcall glLogicOp(GLenum opcode) {
  //
  DEBUG_BREAK;
}

void __stdcall glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride,
                       GLint order, const GLdouble *points) {
  //
  DEBUG_BREAK;
}

void __stdcall glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride,
                       GLint order, const GLfloat *points) {
  //
  DEBUG_BREAK;
}

void __stdcall glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride,
                       GLint uorder, GLdouble v1, GLdouble v2, GLint vstride,
                       GLint vorder, const GLdouble *points) {
  //
  DEBUG_BREAK;
}

void __stdcall glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride,
                       GLint uorder, GLfloat v1, GLfloat v2, GLint vstride,
                       GLint vorder, const GLfloat *points) {
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn,
                           GLdouble v1, GLdouble v2) {
  //
  DEBUG_BREAK;
}

void __stdcall glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn,
                           GLfloat v1, GLfloat v2) {
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialf(GLenum face, GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialfv(GLenum face, GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glMateriali(GLenum face, GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glMaterialiv(GLenum face, GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glMatrixMode(GLenum mode) {
  Context->matrix.glMatrixMode(mode);
}

void __stdcall glMultMatrixd(const GLdouble *m) {
  //
  DEBUG_BREAK;
}

void __stdcall glMultMatrixf(const GLfloat *m) {
  Context->matrix.glMultMatrixf(m);
}

void __stdcall glNewList(GLuint list, GLenum mode) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3bv(const GLbyte *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3i(GLint nx, GLint ny, GLint nz) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormal3sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glNormalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  //
  DEBUG_BREAK;
}

void __stdcall glOrtho(GLdouble left, GLdouble right, GLdouble bottom,
                       GLdouble top, GLdouble zNear, GLdouble zFar) {
  Context->matrix.glOrtho(
    float(left),
    float(right),
    float(bottom),
    float(top),
    float(zNear),
    float(zFar));
}

void __stdcall glPassThrough(GLfloat token) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapfv(GLenum map, GLsizei mapsize,
                            const GLfloat *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapuiv(GLenum map, GLsizei mapsize,
                             const GLuint *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelMapusv(GLenum map, GLsizei mapsize,
                             const GLushort *values) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelStoref(GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelStorei(GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelTransferf(GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelTransferi(GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
  //
  DEBUG_BREAK;
}

void __stdcall glPointSize(GLfloat size) {
  //
  DEBUG_BREAK;
}

void __stdcall glPolygonMode(GLenum face, GLenum mode) {
  //
//  DEBUG_BREAK;
}

void __stdcall glPolygonOffset(GLfloat factor, GLfloat units) {
  //
//  DEBUG_BREAK;
}

void __stdcall glPolygonStipple(const GLubyte *mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glPop(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glPopClient(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glPopMatrix(void) {
  Context->matrix.glPopMatrix();
}

void __stdcall glPopName(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glPrioritizeTextures(GLsizei n, const GLuint *textures,
                                    const GLclampf *priorities) {
  //
  DEBUG_BREAK;
}

void __stdcall glPush(GLbitfield mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glPushClient(GLbitfield mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glPushMatrix(void) {
  Context->matrix.glPushMatrix();
}

void __stdcall glPushName(GLuint name) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2d(GLdouble x, GLdouble y) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2f(GLfloat x, GLfloat y) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2i(GLint x, GLint y) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2s(GLshort x, GLshort y) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos2sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3i(GLint x, GLint y, GLint z) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3s(GLshort x, GLshort y, GLshort z) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos3sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
  DEBUG_BREAK;
}

void __stdcall glRasterPos4sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glReadBuffer(GLenum mode) {
  //
  DEBUG_BREAK;
}

void __stdcall glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectdv(const GLdouble *v1, const GLdouble *v2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectfv(const GLfloat *v1, const GLfloat *v2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectiv(const GLint *v1, const GLint *v2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
  //
  DEBUG_BREAK;
}

void __stdcall glRectsv(const GLshort *v1, const GLshort *v2) {
  //
  DEBUG_BREAK;
}

GLint __stdcall glRenderMode(GLenum mode) {
  //
  DEBUG_BREAK;
  return 0;
}

void __stdcall glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
  Context->matrix.glRotatef(float(angle), float(x), float(y), float(z));
}

void __stdcall glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  Context->matrix.glRotatef(angle, x, y, z);
}

void __stdcall glScaled(GLdouble x, GLdouble y, GLdouble z) {
  Context->matrix.glScalef(float(x), float(y), float(z));
}

void __stdcall glScalef(GLfloat x, GLfloat y, GLfloat z) {
  Context->matrix.glScalef(x, y, z);
}

void __stdcall glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
  Context->state.scissor = rectf_t{
    float(x),
    float(y),
    float(width),
    float(height)};
}

void __stdcall glSelectBuffer(GLsizei size, GLuint *buffer) {
  //
  DEBUG_BREAK;
}

void __stdcall glShadeModel(GLenum mode) {
  //
//  DEBUG_BREAK;
}

void __stdcall glStencilFunc(GLenum func, GLint ref, GLuint mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glStencilMask(GLuint mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1d(GLdouble s) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1f(GLfloat s) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1i(GLint s) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1s(GLshort s) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord1sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2d(GLdouble s, GLdouble t) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2f(GLfloat s, GLfloat t) {
  Context->primative.latch_uv(float2{s, t});
}

void __stdcall glTexCoord2fv(const GLfloat *v) {
  Context->primative.latch_uv(float2{v[0], v[1]});
}

void __stdcall glTexCoord2i(GLint s, GLint t) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2s(GLshort s, GLshort t) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord2sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3i(GLint s, GLint t, GLint r) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3s(GLshort s, GLshort t, GLshort r) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord3sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4fv(const GLfloat *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoord4sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                 const GLvoid *pointer) {
  Context->primative.glTexCoordPointer(size, type, stride, pointer);
}

void __stdcall glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
  //
//  DEBUG_BREAK;
}

void __stdcall glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexEnvi(GLenum target, GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexEnviv(GLenum target, GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGend(GLenum coord, GLenum pname, GLdouble param) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGendv(GLenum coord, GLenum pname, const GLdouble *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGeni(GLenum coord, GLenum pname, GLint param) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexGeniv(GLenum coord, GLenum pname, const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexImage1D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLint border, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexImage2D(GLenum target, GLint level, GLint internalFormat,
                            GLsizei width, GLsizei height, GLint border,
                            GLenum format, GLenum type, const GLvoid *pixels) {
  Context->texture.glTexImage2D(target, level, internalFormat, width,
                                height, border, format, type, pixels);
}

void __stdcall glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
  //
//  DEBUG_BREAK;
}

void __stdcall glTexParameterfv(GLenum target, GLenum pname,
                                const GLfloat *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexParameteri(GLenum target, GLenum pname, GLint param) {
  //
//  DEBUG_BREAK;
}

void __stdcall glTexParameteriv(GLenum target, GLenum pname,
                                const GLint *params) {
  //
  DEBUG_BREAK;
}

void __stdcall glTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                               GLsizei width, GLenum format, GLenum type,
                               const GLvoid *pixels) {
  Context->texture.glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void __stdcall glTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                               GLint yoffset, GLsizei width, GLsizei height,
                               GLenum format, GLenum type,
                               const GLvoid *pixels) {
  //
//  DEBUG_BREAK;
}

void __stdcall glTranslated(GLdouble x, GLdouble y, GLdouble z) {
  //
  DEBUG_BREAK;
}

void __stdcall glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
  Context->matrix.glTranslatef(x, y, z);
}

void __stdcall glVertex2d(GLdouble x, GLdouble y) {
  DEBUG_BREAK;
}

void __stdcall glVertex2dv(const GLdouble *v) {
  DEBUG_BREAK;
}

void __stdcall glVertex2f(GLfloat x, GLfloat y) {
  Context->primative.add_vertex(float4{x, y, 0, 1.f});
}

void __stdcall glVertex2fv(const GLfloat *v) {
  Context->primative.add_vertex(float4{v[0], v[1], 0, 1.f});
}

void __stdcall glVertex2i(GLint x, GLint y) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2s(GLshort x, GLshort y) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex2sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
  Context->primative.add_vertex(float4{x, y, z, 1.f});
}

void __stdcall glVertex3fv(const GLfloat *v) {
  Context->primative.add_vertex(float4{v[0], v[1], v[2], 1.f});
}

void __stdcall glVertex3i(GLint x, GLint y, GLint z) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3s(GLshort x, GLshort y, GLshort z) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex3sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4dv(const GLdouble *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  Context->primative.add_vertex(float4{x, y, z, w});
}

void __stdcall glVertex4fv(const GLfloat *v) {
  Context->primative.add_vertex(float4{v[0], v[1], v[2], v[3]});
}

void __stdcall glVertex4i(GLint x, GLint y, GLint z, GLint w) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4iv(const GLint *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertex4sv(const GLshort *v) {
  //
  DEBUG_BREAK;
}

void __stdcall glVertexPointer(GLint size, GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  Context->primative.glVertexPointer(size, type, stride, pointer);
}

void __stdcall glViewport(GLint x, GLint y, GLsizei w, GLsizei h) {
  Context->on_flush();
  Context->state.viewport = rectf_t{float(x), float(y), float(w), float(h)};
}

void __stdcall glPushAttrib(GLbitfield mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glPopAttrib(void) {
  //
  DEBUG_BREAK;
}

void __stdcall glPushClientAttrib(GLbitfield mask) {
  //
  DEBUG_BREAK;
}

void __stdcall glPopClientAttrib(void) {
  //
  DEBUG_BREAK;
}
