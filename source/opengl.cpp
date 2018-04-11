#include <cassert>
#include <stdint.h>

#include "GL.h"
#include "context.h"
#include "exports.h"
#include "wgl.h"

void __stdcall glAccum(GLenum op, GLfloat value) {
  //
  __debugbreak();
}

void __stdcall glAlphaFunc(GLenum func, GLclampf ref) {
  //
  __debugbreak();
}

GLboolean __stdcall glAreTexturesResident(GLsizei n, const GLuint *textures,
                                          GLboolean *residences) {
  //
  __debugbreak();
  return GL_FALSE;
}

void __stdcall glArrayElement(GLint i) {
  //
  __debugbreak();
}

void __stdcall glBegin(GLenum mode) {
  assert(Context);
  auto &cxt = *Context;
  // save primative mode
  cxt.glState.beginMode = mode;
  __debugbreak();
}

void __stdcall glBindTexture(GLenum target, GLuint texture) {
  //
  __debugbreak();
}

void __stdcall glBitmap(GLsizei width, GLsizei height, GLfloat xorig,
                        GLfloat yorig, GLfloat xmove, GLfloat ymove,
                        const GLubyte *bitmap) {
  //
  __debugbreak();
}

void __stdcall glBlendFunc(GLenum sfactor, GLenum dfactor) {
  //
  __debugbreak();
}

void __stdcall glCallList(GLuint list) {
  //
  __debugbreak();
}

void __stdcall glCallLists(GLsizei n, GLenum type, const GLvoid *lists) {
  //
  __debugbreak();
}

void __stdcall glClear(GLbitfield mask) {

  auto xorshift32 = []() {
    static uint32_t x = 12345;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
  };

  auto &frame = Context->frame();
  for (uint32_t i = 0; i < frame.width * frame.height; ++i) {
    frame.pixels[i] = xorshift32() & 0x1f1f1f;
  }
}

void __stdcall glClearAccum(GLfloat red, GLfloat green, GLfloat blue,
                            GLfloat alpha) {
  //
  __debugbreak();
}

void __stdcall glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
  int cr = 0xff & int(r * 255.f);
  int cg = 0xff & int(g * 255.f);
  int cb = 0xff & int(b * 255.f);
  int ca = 0xff & int(a * 255.f);
  auto &cc = getContext()->glState.clearColor;
  cc = ca << 24 | cr << 16 | cg << 8 | cb;
}

void __stdcall glClearDepth(GLclampd depth) {
  //
  __debugbreak();
}

void __stdcall glClearIndex(GLfloat c) {
  //
  __debugbreak();
}

void __stdcall glClearStencil(GLint s) {
  //
  __debugbreak();
}

void __stdcall glClipPlane(GLenum plane, const GLdouble *equation) {
  //
  __debugbreak();
}

void __stdcall glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
  //
  __debugbreak();
}

void __stdcall glColor3bv(const GLbyte *v) {
  //
  __debugbreak();
}

void __stdcall glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
  //
  __debugbreak();
}

void __stdcall glColor3dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
  //
  __debugbreak();
}

void __stdcall glColor3fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glColor3i(GLint red, GLint green, GLint blue) {
  //
  __debugbreak();
}

void __stdcall glColor3iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glColor3s(GLshort red, GLshort green, GLshort blue) {
  //
  __debugbreak();
}

void __stdcall glColor3sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
  //
  __debugbreak();
}

void __stdcall glColor3ubv(const GLubyte *v) {
  //
  __debugbreak();
}

void __stdcall glColor3ui(GLuint red, GLuint green, GLuint blue) {
  //
  __debugbreak();
}

void __stdcall glColor3uiv(const GLuint *v) {
  //
  __debugbreak();
}

void __stdcall glColor3us(GLushort red, GLushort green, GLushort blue) {
  //
  __debugbreak();
}

void __stdcall glColor3usv(const GLushort *v) {
  //
  __debugbreak();
}

void __stdcall glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4bv(const GLbyte *v) {
  //
  __debugbreak();
}

void __stdcall glColor4d(GLdouble red, GLdouble green, GLdouble blue,
                         GLdouble alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glColor4f(GLfloat red, GLfloat green, GLfloat blue,
                         GLfloat alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glColor4s(GLshort red, GLshort green, GLshort blue,
                         GLshort alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glColor4ub(GLubyte red, GLubyte green, GLubyte blue,
                          GLubyte alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4ubv(const GLubyte *v) {
  //
  __debugbreak();
}

void __stdcall glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4uiv(const GLuint *v) {
  //
  __debugbreak();
}

void __stdcall glColor4us(GLushort red, GLushort green, GLushort blue,
                          GLushort alpha) {
  //
  __debugbreak();
}

void __stdcall glColor4usv(const GLushort *v) {
  //
  __debugbreak();
}

void __stdcall glColorMask(GLboolean red, GLboolean green, GLboolean blue,
                           GLboolean alpha) {
  //
  __debugbreak();
}

void __stdcall glColorMaterial(GLenum face, GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glColorPointer(GLint size, GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum type) {
  //
  __debugbreak();
}

void __stdcall glCopyTexImage1D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLint border) {
  //
  __debugbreak();
}

void __stdcall glCopyTexImage2D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLsizei height, GLint border) {
  //
  __debugbreak();
}

void __stdcall glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                                   GLint x, GLint y, GLsizei width) {
  //
  __debugbreak();
}

void __stdcall glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                                   GLint yoffset, GLint x, GLint y,
                                   GLsizei width, GLsizei height) {
  //
  __debugbreak();
}

void __stdcall glCullFace(GLenum mode) {
  getContext()->glState.cullMode = mode;
}

void __stdcall glDebugEntry(void) {
  //
  __debugbreak();
}

void __stdcall glDeleteLists(GLuint list, GLsizei range) {
  //
  __debugbreak();
}

void __stdcall glDeleteTextures(GLsizei n, const GLuint *textures) {
  //
  __debugbreak();
}

void __stdcall glDepthFunc(GLenum func) {
  //
  __debugbreak();
}

void __stdcall glDepthMask(GLboolean flag) {
  //
  __debugbreak();
}

void __stdcall glDepthRange(GLclampd zNear, GLclampd zFar) {
  //
  __debugbreak();
}

void __stdcall glDisable(GLenum cap) {
  switch (cap) {
  case GL_CULL_FACE:
  case GL_DEPTH_TEST:
  case GL_BLEND:
  case GL_ALPHA_TEST:
    break;
  default:
    __debugbreak();
  }
}

void __stdcall glDisableClientState(GLenum array) {
  //
  __debugbreak();
}

void __stdcall glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  //
  __debugbreak();
}

void __stdcall glDrawBuffer(GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glDrawElements(GLenum mode, GLsizei count, GLenum type,
                              const GLvoid *indices) {
  //
  __debugbreak();
}

void __stdcall glDrawPixels(GLsizei width, GLsizei height, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glEdgeFlag(GLboolean flag) {
  //
  __debugbreak();
}

void __stdcall glEdgeFlagPointer(GLsizei stride, const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glEdgeFlagv(const GLboolean *flag) {
  //
  __debugbreak();
}

void __stdcall glEnable(GLenum cap) {
  switch (cap) {
  case GL_TEXTURE_2D:
  case GL_ALPHA_TEST:
    break;
  default:
    __debugbreak();
  }
}

void __stdcall glEnableClientState(GLenum array) {
  //
  __debugbreak();
}

void __stdcall glEnd(void) {
  //
  __debugbreak();
}

void __stdcall glEndList(void) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord1d(GLdouble u) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord1dv(const GLdouble *u) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord1f(GLfloat u) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord1fv(const GLfloat *u) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord2d(GLdouble u, GLdouble v) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord2dv(const GLdouble *u) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord2f(GLfloat u, GLfloat v) {
  //
  __debugbreak();
}

void __stdcall glEvalCoord2fv(const GLfloat *u) {
  //
  __debugbreak();
}

void __stdcall glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
  //
  __debugbreak();
}

void __stdcall glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1,
                           GLint j2) {
  //
  __debugbreak();
}

void __stdcall glEvalPoint1(GLint i) {
  //
  __debugbreak();
}

void __stdcall glEvalPoint2(GLint i, GLint j) {
  //
  __debugbreak();
}

void __stdcall glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer) {
  //
  __debugbreak();
}

void __stdcall glFinish(void) {
  //
  __debugbreak();
}

void __stdcall glFlush(void) {
  //
  __debugbreak();
}

void __stdcall glFogf(GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glFogfv(GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glFogi(GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glFogiv(GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glFrontFace(GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
                         GLdouble top, GLdouble zNear, GLdouble zFar) {
  //
  __debugbreak();
}

GLuint __stdcall glGenLists(GLsizei range) {
  //
  __debugbreak();
  return 0;
}

void __stdcall glGenTextures(GLsizei n, GLuint *textures) {
  //
  __debugbreak();
}

void __stdcall glGetBooleanv(GLenum pname, GLboolean *params) {
  //
  __debugbreak();
}

void __stdcall glGetClipPlane(GLenum plane, GLdouble *equation) {
  //
  __debugbreak();
}

void __stdcall glGetDoublev(GLenum pname, GLdouble *params) {
  //
  __debugbreak();
}

GLenum __stdcall glGetError(void) {
  //
  __debugbreak();
  return 0;
}

void __stdcall glGetFloatv(GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetIntegerv(GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetLightfv(GLenum light, GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetLightiv(GLenum light, GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetMapdv(GLenum target, GLenum query, GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glGetMapfv(GLenum target, GLenum query, GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glGetMapiv(GLenum target, GLenum query, GLint *v) {
  //
  __debugbreak();
}

void __stdcall glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetMaterialiv(GLenum face, GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetPixelMapfv(GLenum map, GLfloat *values) {
  //
  __debugbreak();
}

void __stdcall glGetPixelMapuiv(GLenum map, GLuint *values) {
  //
  __debugbreak();
}

void __stdcall glGetPixelMapusv(GLenum map, GLushort *values) {
  //
  __debugbreak();
}

void __stdcall glGetPointerv(GLenum pname, GLvoid **params) {
  //
  __debugbreak();
}

void __stdcall glGetPolygonStipple(GLubyte *mask) {
  //
  __debugbreak();
}

const GLubyte *__stdcall glGetString(GLenum name) {
  //
  switch (name) {
  case GL_VENDOR:
    return (GLubyte *)"8BitPimp";
  case GL_RENDERER:
    return (GLubyte *)"nanogl";
  case GL_VERSION:
    return (GLubyte *)"v0.01";
  case GL_EXTENSIONS:
    return (GLubyte *)"";
  default:
    return (GLubyte *)"";
  }
}

void __stdcall glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexEnviv(GLenum target, GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexGeniv(GLenum coord, GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexImage(GLenum target, GLint level, GLenum format,
                             GLenum type, GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glGetTexLevelParameterfv(GLenum target, GLint level,
                                        GLenum pname, GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexLevelParameteriv(GLenum target, GLint level,
                                        GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexParameterfv(GLenum target, GLenum pname,
                                   GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {
  //
  __debugbreak();
}

void __stdcall glHint(GLenum target, GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glIndexMask(GLuint mask) {
  //
  __debugbreak();
}

void __stdcall glIndexPointer(GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glIndexd(GLdouble c) {
  //
  __debugbreak();
}

void __stdcall glIndexdv(const GLdouble *c) {
  //
  __debugbreak();
}

void __stdcall glIndexf(GLfloat c) {
  //
  __debugbreak();
}

void __stdcall glIndexfv(const GLfloat *c) {
  //
  __debugbreak();
}

void __stdcall glIndexi(GLint c) {
  //
  __debugbreak();
}

void __stdcall glIndexiv(const GLint *c) {
  //
  __debugbreak();
}

void __stdcall glIndexs(GLshort c) {
  //
  __debugbreak();
}

void __stdcall glIndexsv(const GLshort *c) {
  //
  __debugbreak();
}

void __stdcall glIndexub(GLubyte c) {
  //
  __debugbreak();
}

void __stdcall glIndexubv(const GLubyte *c) {
  //
  __debugbreak();
}

void __stdcall glInitNames(void) {
  //
  __debugbreak();
}

void __stdcall glInterleavedArrays(GLenum format, GLsizei stride,
                                   const GLvoid *pointer) {
  //
  __debugbreak();
}

GLboolean __stdcall glIsEnabled(GLenum cap) {
  //
  __debugbreak();
  return GL_FALSE;
}

GLboolean __stdcall glIsList(GLuint list) {
  //
  __debugbreak();
  return GL_FALSE;
}

GLboolean __stdcall glIsTexture(GLuint texture) {
  //
  __debugbreak();
  return GL_FALSE;
}

void __stdcall glLightModelf(GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glLightModelfv(GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glLightModeli(GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glLightModeliv(GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glLightf(GLenum light, GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glLightfv(GLenum light, GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glLighti(GLenum light, GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glLightiv(GLenum light, GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glLineStipple(GLint factor, GLushort pattern) {
  //
  __debugbreak();
}

void __stdcall glLineWidth(GLfloat width) {
  //
  __debugbreak();
}

void __stdcall glListBase(GLuint base) {
  //
  __debugbreak();
}

void __stdcall glLoadIdentity(void) {
  //
  __debugbreak();
}

void __stdcall glLoadMatrixd(const GLdouble *m) {
  //
  __debugbreak();
}

void __stdcall glLoadMatrixf(const GLfloat *m) {
  //
  __debugbreak();
}

void __stdcall glLoadName(GLuint name) {
  //
  __debugbreak();
}

void __stdcall glLogicOp(GLenum opcode) {
  //
  __debugbreak();
}

void __stdcall glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride,
                       GLint order, const GLdouble *points) {
  //
  __debugbreak();
}

void __stdcall glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride,
                       GLint order, const GLfloat *points) {
  //
  __debugbreak();
}

void __stdcall glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride,
                       GLint uorder, GLdouble v1, GLdouble v2, GLint vstride,
                       GLint vorder, const GLdouble *points) {
  //
  __debugbreak();
}

void __stdcall glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride,
                       GLint uorder, GLfloat v1, GLfloat v2, GLint vstride,
                       GLint vorder, const GLfloat *points) {
  //
  __debugbreak();
}

void __stdcall glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
  //
  __debugbreak();
}

void __stdcall glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
  //
  __debugbreak();
}

void __stdcall glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn,
                           GLdouble v1, GLdouble v2) {
  //
  __debugbreak();
}

void __stdcall glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn,
                           GLfloat v1, GLfloat v2) {
  //
  __debugbreak();
}

void __stdcall glMaterialf(GLenum face, GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glMaterialfv(GLenum face, GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glMateriali(GLenum face, GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glMaterialiv(GLenum face, GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glMatrixMode(GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glMultMatrixd(const GLdouble *m) {
  //
  __debugbreak();
}

void __stdcall glMultMatrixf(const GLfloat *m) {
  //
  __debugbreak();
}

void __stdcall glNewList(GLuint list, GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
  //
  __debugbreak();
}

void __stdcall glNormal3bv(const GLbyte *v) {
  //
  __debugbreak();
}

void __stdcall glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
  //
  __debugbreak();
}

void __stdcall glNormal3dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
  //
  __debugbreak();
}

void __stdcall glNormal3fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glNormal3i(GLint nx, GLint ny, GLint nz) {
  //
  __debugbreak();
}

void __stdcall glNormal3iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
  //
  __debugbreak();
}

void __stdcall glNormal3sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glNormalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glOrtho(GLdouble left, GLdouble right, GLdouble bottom,
                       GLdouble top, GLdouble zNear, GLdouble zFar) {
  //
  __debugbreak();
}

void __stdcall glPassThrough(GLfloat token) {
  //
  __debugbreak();
}

void __stdcall glPixelMapfv(GLenum map, GLsizei mapsize,
                            const GLfloat *values) {
  //
  __debugbreak();
}

void __stdcall glPixelMapuiv(GLenum map, GLsizei mapsize,
                             const GLuint *values) {
  //
  __debugbreak();
}

void __stdcall glPixelMapusv(GLenum map, GLsizei mapsize,
                             const GLushort *values) {
  //
  __debugbreak();
}

void __stdcall glPixelStoref(GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glPixelStorei(GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glPixelTransferf(GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glPixelTransferi(GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
  //
  __debugbreak();
}

void __stdcall glPointSize(GLfloat size) {
  //
  __debugbreak();
}

void __stdcall glPolygonMode(GLenum face, GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glPolygonOffset(GLfloat factor, GLfloat units) {
  //
  __debugbreak();
}

void __stdcall glPolygonStipple(const GLubyte *mask) {
  //
  __debugbreak();
}

void __stdcall glPop(void) {
  //
  __debugbreak();
}

void __stdcall glPopClient(void) {
  //
  __debugbreak();
}

void __stdcall glPopMatrix(void) {
  //
  __debugbreak();
}

void __stdcall glPopName(void) {
  //
  __debugbreak();
}

void __stdcall glPrioritizeTextures(GLsizei n, const GLuint *textures,
                                    const GLclampf *priorities) {
  //
  __debugbreak();
}

void __stdcall glPush(GLbitfield mask) {
  //
  __debugbreak();
}

void __stdcall glPushClient(GLbitfield mask) {
  //
  __debugbreak();
}

void __stdcall glPushMatrix(void) {
  //
  __debugbreak();
}

void __stdcall glPushName(GLuint name) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2d(GLdouble x, GLdouble y) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2f(GLfloat x, GLfloat y) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2i(GLint x, GLint y) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2s(GLshort x, GLshort y) {
  //
  __debugbreak();
}

void __stdcall glRasterPos2sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3i(GLint x, GLint y, GLint z) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3s(GLshort x, GLshort y, GLshort z) {
  //
  __debugbreak();
}

void __stdcall glRasterPos3sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
  __debugbreak();
}

void __stdcall glRasterPos4sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glReadBuffer(GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  //
  __debugbreak();
}

void __stdcall glRectdv(const GLdouble *v1, const GLdouble *v2) {
  //
  __debugbreak();
}

void __stdcall glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
  //
  __debugbreak();
}

void __stdcall glRectfv(const GLfloat *v1, const GLfloat *v2) {
  //
  __debugbreak();
}

void __stdcall glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
  //
  __debugbreak();
}

void __stdcall glRectiv(const GLint *v1, const GLint *v2) {
  //
  __debugbreak();
}

void __stdcall glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
  //
  __debugbreak();
}

void __stdcall glRectsv(const GLshort *v1, const GLshort *v2) {
  //
  __debugbreak();
}

GLint __stdcall glRenderMode(GLenum mode) {
  //
  __debugbreak();
  return 0;
}

void __stdcall glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
  //
  __debugbreak();
}

void __stdcall glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  //
  __debugbreak();
}

void __stdcall glScaled(GLdouble x, GLdouble y, GLdouble z) {
  //
  __debugbreak();
}

void __stdcall glScalef(GLfloat x, GLfloat y, GLfloat z) {
  //
  __debugbreak();
}

void __stdcall glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
  //
  __debugbreak();
}

void __stdcall glSelectBuffer(GLsizei size, GLuint *buffer) {
  //
  __debugbreak();
}

void __stdcall glShadeModel(GLenum mode) {
  //
  __debugbreak();
}

void __stdcall glStencilFunc(GLenum func, GLint ref, GLuint mask) {
  //
  __debugbreak();
}

void __stdcall glStencilMask(GLuint mask) {
  //
  __debugbreak();
}

void __stdcall glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1d(GLdouble s) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1f(GLfloat s) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1i(GLint s) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1s(GLshort s) {
  //
  __debugbreak();
}

void __stdcall glTexCoord1sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2d(GLdouble s, GLdouble t) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2f(GLfloat s, GLfloat t) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2i(GLint s, GLint t) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2s(GLshort s, GLshort t) {
  //
  __debugbreak();
}

void __stdcall glTexCoord2sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3i(GLint s, GLint t, GLint r) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3s(GLshort s, GLshort t, GLshort r) {
  //
  __debugbreak();
}

void __stdcall glTexCoord3sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
  //
  __debugbreak();
}

void __stdcall glTexCoord4sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                 const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glTexEnvi(GLenum target, GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glTexEnviv(GLenum target, GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glTexGend(GLenum coord, GLenum pname, GLdouble param) {
  //
  __debugbreak();
}

void __stdcall glTexGendv(GLenum coord, GLenum pname, const GLdouble *params) {
  //
  __debugbreak();
}

void __stdcall glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glTexGeni(GLenum coord, GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glTexGeniv(GLenum coord, GLenum pname, const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glTexImage1D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLint border, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glTexImage2D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLsizei height, GLint border,
                            GLenum format, GLenum type, const GLvoid *pixels) {
  // XXX: Save these out to disk, hash pixels ...
  __debugbreak();
}

void __stdcall glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
  //
  __debugbreak();
}

void __stdcall glTexParameterfv(GLenum target, GLenum pname,
                                const GLfloat *params) {
  //
  __debugbreak();
}

void __stdcall glTexParameteri(GLenum target, GLenum pname, GLint param) {
  //
  __debugbreak();
}

void __stdcall glTexParameteriv(GLenum target, GLenum pname,
                                const GLint *params) {
  //
  __debugbreak();
}

void __stdcall glTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                               GLsizei width, GLenum format, GLenum type,
                               const GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                               GLint yoffset, GLsizei width, GLsizei height,
                               GLenum format, GLenum type,
                               const GLvoid *pixels) {
  //
  __debugbreak();
}

void __stdcall glTranslated(GLdouble x, GLdouble y, GLdouble z) {
  //
  __debugbreak();
}

void __stdcall glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
  //
  __debugbreak();
}

void __stdcall glVertex2d(GLdouble x, GLdouble y) {
  //
  __debugbreak();
}

void __stdcall glVertex2dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glVertex2f(GLfloat x, GLfloat y) {
  //
  __debugbreak();
}

void __stdcall glVertex2fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glVertex2i(GLint x, GLint y) {
  //
  __debugbreak();
}

void __stdcall glVertex2iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glVertex2s(GLshort x, GLshort y) {
  //
  __debugbreak();
}

void __stdcall glVertex2sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
  //
  __debugbreak();
}

void __stdcall glVertex3dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
  //
  __debugbreak();
}

void __stdcall glVertex3fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glVertex3i(GLint x, GLint y, GLint z) {
  //
  __debugbreak();
}

void __stdcall glVertex3iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glVertex3s(GLshort x, GLshort y, GLshort z) {
  //
  __debugbreak();
}

void __stdcall glVertex3sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
  __debugbreak();
}

void __stdcall glVertex4dv(const GLdouble *v) {
  //
  __debugbreak();
}

void __stdcall glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  //
  __debugbreak();
}

void __stdcall glVertex4fv(const GLfloat *v) {
  //
  __debugbreak();
}

void __stdcall glVertex4i(GLint x, GLint y, GLint z, GLint w) {
  //
  __debugbreak();
}

void __stdcall glVertex4iv(const GLint *v) {
  //
  __debugbreak();
}

void __stdcall glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
  __debugbreak();
}

void __stdcall glVertex4sv(const GLshort *v) {
  //
  __debugbreak();
}

void __stdcall glVertexPointer(GLint size, GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  //
  __debugbreak();
}

void __stdcall glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
  //
  __debugbreak();
}

void __stdcall glPushAttrib(GLbitfield mask) {
  //
  __debugbreak();
}

void __stdcall glPopAttrib(void) {
  //
  __debugbreak();
}

void __stdcall glPushClientAttrib(GLbitfield mask) {
  //
  __debugbreak();
}

void __stdcall glPopClientAttrib(void) {
  //
  __debugbreak();
}
