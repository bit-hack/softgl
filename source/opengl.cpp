#include <cassert>
#include <stdint.h>

#include "wgl.h"
#include "exports.h"
#include "GL.h"
#include "context.h"

void __stdcall glAccum(GLenum op, GLfloat value) {
  //
}

void __stdcall glAlphaFunc(GLenum func, GLclampf ref) {
  //
}

GLboolean __stdcall glAreTexturesResident(GLsizei n, const GLuint *textures,
                                          GLboolean *residences) {
  //
  return GL_FALSE;
}

void __stdcall glArrayElement(GLint i) {
  //
}

void __stdcall glBegin(GLenum mode) {
  //
}

void __stdcall glBindTexture(GLenum target, GLuint texture) {
  //
}

void __stdcall glBitmap(GLsizei width, GLsizei height, GLfloat xorig,
                        GLfloat yorig, GLfloat xmove, GLfloat ymove,
                        const GLubyte *bitmap) {
  //
}

void __stdcall glBlendFunc(GLenum sfactor, GLenum dfactor) {
  //
}

void __stdcall glCallList(GLuint list) {
  //
}

void __stdcall glCallLists(GLsizei n, GLenum type, const GLvoid *lists) {
  //
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
    frame.pixels[i] = xorshift32();
  }

}

void __stdcall glClearAccum(GLfloat red, GLfloat green, GLfloat blue,
                            GLfloat alpha) {
  //
}

void __stdcall glClearColor(GLclampf red, GLclampf green, GLclampf blue,
                            GLclampf alpha) {
  //
}

void __stdcall glClearDepth(GLclampd depth) {
  //
}

void __stdcall glClearIndex(GLfloat c) {
  //
}

void __stdcall glClearStencil(GLint s) {
  //
}

void __stdcall glClipPlane(GLenum plane, const GLdouble *equation) {
  //
}

void __stdcall glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
  //
}

void __stdcall glColor3bv(const GLbyte *v) {
  //
}

void __stdcall glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
  //
}

void __stdcall glColor3dv(const GLdouble *v) {
  //
}

void __stdcall glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
  //
}

void __stdcall glColor3fv(const GLfloat *v) {
  //
}

void __stdcall glColor3i(GLint red, GLint green, GLint blue) {
  //
}

void __stdcall glColor3iv(const GLint *v) {
  //
}

void __stdcall glColor3s(GLshort red, GLshort green, GLshort blue) {
  //
}

void __stdcall glColor3sv(const GLshort *v) {
  //
}

void __stdcall glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
  //
}

void __stdcall glColor3ubv(const GLubyte *v) {
  //
}

void __stdcall glColor3ui(GLuint red, GLuint green, GLuint blue) {
  //
}

void __stdcall glColor3uiv(const GLuint *v) {
  //
}

void __stdcall glColor3us(GLushort red, GLushort green, GLushort blue) {
  //
}

void __stdcall glColor3usv(const GLushort *v) {
  //
}

void __stdcall glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
  //
}

void __stdcall glColor4bv(const GLbyte *v) {
  //
}

void __stdcall glColor4d(GLdouble red, GLdouble green, GLdouble blue,
                         GLdouble alpha) {
  //
}

void __stdcall glColor4dv(const GLdouble *v) {
  //
}

void __stdcall glColor4f(GLfloat red, GLfloat green, GLfloat blue,
                         GLfloat alpha) {
  //
}

void __stdcall glColor4fv(const GLfloat *v) {
  //
}

void __stdcall glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
  //
}

void __stdcall glColor4iv(const GLint *v) {
  //
}

void __stdcall glColor4s(GLshort red, GLshort green, GLshort blue,
                         GLshort alpha) {
  //
}

void __stdcall glColor4sv(const GLshort *v) {
  //
}

void __stdcall glColor4ub(GLubyte red, GLubyte green, GLubyte blue,
                          GLubyte alpha) {
  //
}

void __stdcall glColor4ubv(const GLubyte *v) {
  //
}

void __stdcall glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
  //
}

void __stdcall glColor4uiv(const GLuint *v) {
  //
}

void __stdcall glColor4us(GLushort red, GLushort green, GLushort blue,
                          GLushort alpha) {
  //
}

void __stdcall glColor4usv(const GLushort *v) {
  //
}

void __stdcall glColorMask(GLboolean red, GLboolean green, GLboolean blue,
                           GLboolean alpha) {
  //
}

void __stdcall glColorMaterial(GLenum face, GLenum mode) {
  //
}

void __stdcall glColorPointer(GLint size, GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  //
}

void __stdcall glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum type) {
  //
}

void __stdcall glCopyTexImage1D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLint border) {
  //
}

void __stdcall glCopyTexImage2D(GLenum target, GLint level,
                                GLenum internalFormat, GLint x, GLint y,
                                GLsizei width, GLsizei height, GLint border) {
  //
}

void __stdcall glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                                   GLint x, GLint y, GLsizei width) {
  //
}

void __stdcall glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                                   GLint yoffset, GLint x, GLint y,
                                   GLsizei width, GLsizei height) {
  //
}

void __stdcall glCullFace(GLenum mode) {
  //
}

void __stdcall glDebugEntry(void) {
  //
}

void __stdcall glDeleteLists(GLuint list, GLsizei range) {
  //
}

void __stdcall glDeleteTextures(GLsizei n, const GLuint *textures) {
  //
}

void __stdcall glDepthFunc(GLenum func) {
  //
}

void __stdcall glDepthMask(GLboolean flag) {
  //
}

void __stdcall glDepthRange(GLclampd zNear, GLclampd zFar) {
  //
}

void __stdcall glDisable(GLenum cap) {
  //
}

void __stdcall glDisableClientState(GLenum array) {
  //
}

void __stdcall glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  //
}

void __stdcall glDrawBuffer(GLenum mode) {
  //
}

void __stdcall glDrawElements(GLenum mode, GLsizei count, GLenum type,
                              const GLvoid *indices) {
  //
}

void __stdcall glDrawPixels(GLsizei width, GLsizei height, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
}

void __stdcall glEdgeFlag(GLboolean flag) {
  //
}

void __stdcall glEdgeFlagPointer(GLsizei stride, const GLvoid *pointer) {
  //
}

void __stdcall glEdgeFlagv(const GLboolean *flag) {
  //
}

void __stdcall glEnable(GLenum cap) {
  //
}

void __stdcall glEnableClientState(GLenum array) {
  //
}

void __stdcall glEnd(void) {
  //
}

void __stdcall glEndList(void) {
  //
}

void __stdcall glEvalCoord1d(GLdouble u) {
  //
}

void __stdcall glEvalCoord1dv(const GLdouble *u) {
  //
}

void __stdcall glEvalCoord1f(GLfloat u) {
  //
}

void __stdcall glEvalCoord1fv(const GLfloat *u) {
  //
}

void __stdcall glEvalCoord2d(GLdouble u, GLdouble v) {
  //
}

void __stdcall glEvalCoord2dv(const GLdouble *u) {
  //
}

void __stdcall glEvalCoord2f(GLfloat u, GLfloat v) {
  //
}

void __stdcall glEvalCoord2fv(const GLfloat *u) {
  //
}

void __stdcall glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
  //
}

void __stdcall glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1,
                           GLint j2) {
  //
}

void __stdcall glEvalPoint1(GLint i) {
  //
}

void __stdcall glEvalPoint2(GLint i, GLint j) {
  //
}

void __stdcall glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer) {
  //
}

void __stdcall glFinish(void) {
  //
}

void __stdcall glFlush(void) {
  //
}

void __stdcall glFogf(GLenum pname, GLfloat param) {
  //
}

void __stdcall glFogfv(GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glFogi(GLenum pname, GLint param) {
  //
}

void __stdcall glFogiv(GLenum pname, const GLint *params) {
  //
}

void __stdcall glFrontFace(GLenum mode) {
  //
}

void __stdcall glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
                         GLdouble top, GLdouble zNear, GLdouble zFar) {
  //
}

GLuint __stdcall glGenLists(GLsizei range) {
  //
  return 0;
}

void __stdcall glGenTextures(GLsizei n, GLuint *textures) {
  //
}

void __stdcall glGetBooleanv(GLenum pname, GLboolean *params) {
  //
}

void __stdcall glGetClipPlane(GLenum plane, GLdouble *equation) {
  //
}

void __stdcall glGetDoublev(GLenum pname, GLdouble *params) {
  //
}

GLenum __stdcall glGetError(void) {
  //
  return 0;
}

void __stdcall glGetFloatv(GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetIntegerv(GLenum pname, GLint *params) {
  //
}

void __stdcall glGetLightfv(GLenum light, GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetLightiv(GLenum light, GLenum pname, GLint *params) {
  //
}

void __stdcall glGetMapdv(GLenum target, GLenum query, GLdouble *v) {
  //
}

void __stdcall glGetMapfv(GLenum target, GLenum query, GLfloat *v) {
  //
}

void __stdcall glGetMapiv(GLenum target, GLenum query, GLint *v) {
  //
}

void __stdcall glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetMaterialiv(GLenum face, GLenum pname, GLint *params) {
  //
}

void __stdcall glGetPixelMapfv(GLenum map, GLfloat *values) {
  //
}

void __stdcall glGetPixelMapuiv(GLenum map, GLuint *values) {
  //
}

void __stdcall glGetPixelMapusv(GLenum map, GLushort *values) {
  //
}

void __stdcall glGetPointerv(GLenum pname, GLvoid **params) {
  //
}

void __stdcall glGetPolygonStipple(GLubyte *mask) {
  //
}

const GLubyte *__stdcall glGetString(GLenum name) {
  //
  return (GLubyte*)"";
}

void __stdcall glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetTexEnviv(GLenum target, GLenum pname, GLint *params) {
  //
}

void __stdcall glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params) {
  //
}

void __stdcall glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetTexGeniv(GLenum coord, GLenum pname, GLint *params) {
  //
}

void __stdcall glGetTexImage(GLenum target, GLint level, GLenum format,
                             GLenum type, GLvoid *pixels) {
  //
}

void __stdcall glGetTexLevelParameterfv(GLenum target, GLint level,
                                        GLenum pname, GLfloat *params) {
  //
}

void __stdcall glGetTexLevelParameteriv(GLenum target, GLint level,
                                        GLenum pname, GLint *params) {
  //
}

void __stdcall glGetTexParameterfv(GLenum target, GLenum pname,
                                   GLfloat *params) {
  //
}

void __stdcall glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {
  //
}

void __stdcall glHint(GLenum target, GLenum mode) {
  //
}

void __stdcall glIndexMask(GLuint mask) {
  //
}

void __stdcall glIndexPointer(GLenum type, GLsizei stride,
                              const GLvoid *pointer) {
  //
}

void __stdcall glIndexd(GLdouble c) {
  //
}

void __stdcall glIndexdv(const GLdouble *c) {
  //
}

void __stdcall glIndexf(GLfloat c) {
  //
}

void __stdcall glIndexfv(const GLfloat *c) {
  //
}

void __stdcall glIndexi(GLint c) {
  //
}

void __stdcall glIndexiv(const GLint *c) {
  //
}

void __stdcall glIndexs(GLshort c) {
  //
}

void __stdcall glIndexsv(const GLshort *c) {
  //
}

void __stdcall glIndexub(GLubyte c) {
  //
}

void __stdcall glIndexubv(const GLubyte *c) {
  //
}

void __stdcall glInitNames(void) {
  //
}

void __stdcall glInterleavedArrays(GLenum format, GLsizei stride,
                                   const GLvoid *pointer) {
  //
}

GLboolean __stdcall glIsEnabled(GLenum cap) {
  //
  return GL_FALSE;
}

GLboolean __stdcall glIsList(GLuint list) {
  //
  return GL_FALSE;
}

GLboolean __stdcall glIsTexture(GLuint texture) {
  //
  return GL_FALSE;
}

void __stdcall glLightModelf(GLenum pname, GLfloat param) {
  //
}

void __stdcall glLightModelfv(GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glLightModeli(GLenum pname, GLint param) {
  //
}

void __stdcall glLightModeliv(GLenum pname, const GLint *params) {
  //
}

void __stdcall glLightf(GLenum light, GLenum pname, GLfloat param) {
  //
}

void __stdcall glLightfv(GLenum light, GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glLighti(GLenum light, GLenum pname, GLint param) {
  //
}

void __stdcall glLightiv(GLenum light, GLenum pname, const GLint *params) {
  //
}

void __stdcall glLineStipple(GLint factor, GLushort pattern) {
  //
}

void __stdcall glLineWidth(GLfloat width) {
  //
}

void __stdcall glListBase(GLuint base) {
  //
}

void __stdcall glLoadIdentity(void) {
  //
}

void __stdcall glLoadMatrixd(const GLdouble *m) {
  //
}

void __stdcall glLoadMatrixf(const GLfloat *m) {
  //
}

void __stdcall glLoadName(GLuint name) {
  //
}

void __stdcall glLogicOp(GLenum opcode) {
  //
}

void __stdcall glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride,
                       GLint order, const GLdouble *points) {
  //
}

void __stdcall glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride,
                       GLint order, const GLfloat *points) {
  //
}

void __stdcall glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride,
                       GLint uorder, GLdouble v1, GLdouble v2, GLint vstride,
                       GLint vorder, const GLdouble *points) {
  //
}

void __stdcall glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride,
                       GLint uorder, GLfloat v1, GLfloat v2, GLint vstride,
                       GLint vorder, const GLfloat *points) {
  //
}

void __stdcall glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
  //
}

void __stdcall glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
  //
}

void __stdcall glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn,
                           GLdouble v1, GLdouble v2) {
  //
}

void __stdcall glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn,
                           GLfloat v1, GLfloat v2) {
  //
}

void __stdcall glMaterialf(GLenum face, GLenum pname, GLfloat param) {
  //
}

void __stdcall glMaterialfv(GLenum face, GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glMateriali(GLenum face, GLenum pname, GLint param) {
  //
}

void __stdcall glMaterialiv(GLenum face, GLenum pname, const GLint *params) {
  //
}

void __stdcall glMatrixMode(GLenum mode) {
  //
}

void __stdcall glMultMatrixd(const GLdouble *m) {
  //
}

void __stdcall glMultMatrixf(const GLfloat *m) {
  //
}

void __stdcall glNewList(GLuint list, GLenum mode) {
  //
}

void __stdcall glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
  //
}

void __stdcall glNormal3bv(const GLbyte *v) {
  //
}

void __stdcall glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
  //
}

void __stdcall glNormal3dv(const GLdouble *v) {
  //
}

void __stdcall glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
  //
}

void __stdcall glNormal3fv(const GLfloat *v) {
  //
}

void __stdcall glNormal3i(GLint nx, GLint ny, GLint nz) {
  //
}

void __stdcall glNormal3iv(const GLint *v) {
  //
}

void __stdcall glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
  //
}

void __stdcall glNormal3sv(const GLshort *v) {
  //
}

void __stdcall glNormalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  //
}

void __stdcall glOrtho(GLdouble left, GLdouble right, GLdouble bottom,
                       GLdouble top, GLdouble zNear, GLdouble zFar) {
  //
}

void __stdcall glPassThrough(GLfloat token) {
  //
}

void __stdcall glPixelMapfv(GLenum map, GLsizei mapsize,
                            const GLfloat *values) {
  //
}

void __stdcall glPixelMapuiv(GLenum map, GLsizei mapsize,
                             const GLuint *values) {
  //
}

void __stdcall glPixelMapusv(GLenum map, GLsizei mapsize,
                             const GLushort *values) {
  //
}

void __stdcall glPixelStoref(GLenum pname, GLfloat param) {
  //
}

void __stdcall glPixelStorei(GLenum pname, GLint param) {
  //
}

void __stdcall glPixelTransferf(GLenum pname, GLfloat param) {
  //
}

void __stdcall glPixelTransferi(GLenum pname, GLint param) {
  //
}

void __stdcall glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
  //
}

void __stdcall glPointSize(GLfloat size) {
  //
}

void __stdcall glPolygonMode(GLenum face, GLenum mode) {
  //
}

void __stdcall glPolygonOffset(GLfloat factor, GLfloat units) {
  //
}

void __stdcall glPolygonStipple(const GLubyte *mask) {
  //
}

void __stdcall glPop(void) {
  //
}

void __stdcall glPopClient(void) {
  //
}

void __stdcall glPopMatrix(void) {
  //
}

void __stdcall glPopName(void) {
  //
}

void __stdcall glPrioritizeTextures(GLsizei n, const GLuint *textures,
                                    const GLclampf *priorities) {
  //
}

void __stdcall glPush(GLbitfield mask) {
  //
}

void __stdcall glPushClient(GLbitfield mask) {
  //
}

void __stdcall glPushMatrix(void) {
  //
}

void __stdcall glPushName(GLuint name) {
  //
}

void __stdcall glRasterPos2d(GLdouble x, GLdouble y) {
  //
}

void __stdcall glRasterPos2dv(const GLdouble *v) {
  //
}

void __stdcall glRasterPos2f(GLfloat x, GLfloat y) {
  //
}

void __stdcall glRasterPos2fv(const GLfloat *v) {
  //
}

void __stdcall glRasterPos2i(GLint x, GLint y) {
  //
}

void __stdcall glRasterPos2iv(const GLint *v) {
  //
}

void __stdcall glRasterPos2s(GLshort x, GLshort y) {
  //
}

void __stdcall glRasterPos2sv(const GLshort *v) {
  //
}

void __stdcall glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
  //
}

void __stdcall glRasterPos3dv(const GLdouble *v) {
  //
}

void __stdcall glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
  //
}

void __stdcall glRasterPos3fv(const GLfloat *v) {
  //
}

void __stdcall glRasterPos3i(GLint x, GLint y, GLint z) {
  //
}

void __stdcall glRasterPos3iv(const GLint *v) {
  //
}

void __stdcall glRasterPos3s(GLshort x, GLshort y, GLshort z) {
  //
}

void __stdcall glRasterPos3sv(const GLshort *v) {
  //
}

void __stdcall glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
}

void __stdcall glRasterPos4dv(const GLdouble *v) {
  //
}

void __stdcall glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  //
}

void __stdcall glRasterPos4fv(const GLfloat *v) {
  //
}

void __stdcall glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
  //
}

void __stdcall glRasterPos4iv(const GLint *v) {
  //
}

void __stdcall glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
}

void __stdcall glRasterPos4sv(const GLshort *v) {
  //
}

void __stdcall glReadBuffer(GLenum mode) {
  //
}

void __stdcall glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels) {
  //
}

void __stdcall glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
  //
}

void __stdcall glRectdv(const GLdouble *v1, const GLdouble *v2) {
  //
}

void __stdcall glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
  //
}

void __stdcall glRectfv(const GLfloat *v1, const GLfloat *v2) {
  //
}

void __stdcall glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
  //
}

void __stdcall glRectiv(const GLint *v1, const GLint *v2) {
  //
}

void __stdcall glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
  //
}

void __stdcall glRectsv(const GLshort *v1, const GLshort *v2) {
  //
}

GLint __stdcall glRenderMode(GLenum mode) {
  //
  return 0;
}

void __stdcall glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
  //
}

void __stdcall glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  //
}

void __stdcall glScaled(GLdouble x, GLdouble y, GLdouble z) {
  //
}

void __stdcall glScalef(GLfloat x, GLfloat y, GLfloat z) {
  //
}

void __stdcall glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
  //
}

void __stdcall glSelectBuffer(GLsizei size, GLuint *buffer) {
  //
}

void __stdcall glShadeModel(GLenum mode) {
  //
}

void __stdcall glStencilFunc(GLenum func, GLint ref, GLuint mask) {
  //
}

void __stdcall glStencilMask(GLuint mask) {
  //
}

void __stdcall glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
  //
}

void __stdcall glTexCoord1d(GLdouble s) {
  //
}

void __stdcall glTexCoord1dv(const GLdouble *v) {
  //
}

void __stdcall glTexCoord1f(GLfloat s) {
  //
}

void __stdcall glTexCoord1fv(const GLfloat *v) {
  //
}

void __stdcall glTexCoord1i(GLint s) {
  //
}

void __stdcall glTexCoord1iv(const GLint *v) {
  //
}

void __stdcall glTexCoord1s(GLshort s) {
  //
}

void __stdcall glTexCoord1sv(const GLshort *v) {
  //
}

void __stdcall glTexCoord2d(GLdouble s, GLdouble t) {
  //
}

void __stdcall glTexCoord2dv(const GLdouble *v) {
  //
}

void __stdcall glTexCoord2f(GLfloat s, GLfloat t) {
  //
}

void __stdcall glTexCoord2fv(const GLfloat *v) {
  //
}

void __stdcall glTexCoord2i(GLint s, GLint t) {
  //
}

void __stdcall glTexCoord2iv(const GLint *v) {
  //
}

void __stdcall glTexCoord2s(GLshort s, GLshort t) {
  //
}

void __stdcall glTexCoord2sv(const GLshort *v) {
  //
}

void __stdcall glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
  //
}

void __stdcall glTexCoord3dv(const GLdouble *v) {
  //
}

void __stdcall glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
  //
}

void __stdcall glTexCoord3fv(const GLfloat *v) {
  //
}

void __stdcall glTexCoord3i(GLint s, GLint t, GLint r) {
  //
}

void __stdcall glTexCoord3iv(const GLint *v) {
  //
}

void __stdcall glTexCoord3s(GLshort s, GLshort t, GLshort r) {
  //
}

void __stdcall glTexCoord3sv(const GLshort *v) {
  //
}

void __stdcall glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
  //
}

void __stdcall glTexCoord4dv(const GLdouble *v) {
  //
}

void __stdcall glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
  //
}

void __stdcall glTexCoord4fv(const GLfloat *v) {
  //
}

void __stdcall glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
  //
}

void __stdcall glTexCoord4iv(const GLint *v) {
  //
}

void __stdcall glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
  //
}

void __stdcall glTexCoord4sv(const GLshort *v) {
  //
}

void __stdcall glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                 const GLvoid *pointer) {
  //
}

void __stdcall glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
  //
}

void __stdcall glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glTexEnvi(GLenum target, GLenum pname, GLint param) {
  //
}

void __stdcall glTexEnviv(GLenum target, GLenum pname, const GLint *params) {
  //
}

void __stdcall glTexGend(GLenum coord, GLenum pname, GLdouble param) {
  //
}

void __stdcall glTexGendv(GLenum coord, GLenum pname, const GLdouble *params) {
  //
}

void __stdcall glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
  //
}

void __stdcall glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params) {
  //
}

void __stdcall glTexGeni(GLenum coord, GLenum pname, GLint param) {
  //
}

void __stdcall glTexGeniv(GLenum coord, GLenum pname, const GLint *params) {
  //
}

void __stdcall glTexImage1D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLint border, GLenum format,
                            GLenum type, const GLvoid *pixels) {
  //
}

void __stdcall glTexImage2D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLsizei height, GLint border,
                            GLenum format, GLenum type, const GLvoid *pixels) {
  //
}

void __stdcall glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
  //
}

void __stdcall glTexParameterfv(GLenum target, GLenum pname,
                                const GLfloat *params) {
  //
}

void __stdcall glTexParameteri(GLenum target, GLenum pname, GLint param) {
  //
}

void __stdcall glTexParameteriv(GLenum target, GLenum pname,
                                const GLint *params) {
  //
}

void __stdcall glTexSubImage1D(GLenum target, GLint level, GLint xoffset,
                               GLsizei width, GLenum format, GLenum type,
                               const GLvoid *pixels) {
  //
}

void __stdcall glTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                               GLint yoffset, GLsizei width, GLsizei height,
                               GLenum format, GLenum type,
                               const GLvoid *pixels) {
  //
}

void __stdcall glTranslated(GLdouble x, GLdouble y, GLdouble z) {
  //
}

void __stdcall glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
  //
}

void __stdcall glVertex2d(GLdouble x, GLdouble y) {
  //
}

void __stdcall glVertex2dv(const GLdouble *v) {
  //
}

void __stdcall glVertex2f(GLfloat x, GLfloat y) {
  //
}

void __stdcall glVertex2fv(const GLfloat *v) {
  //
}

void __stdcall glVertex2i(GLint x, GLint y) {
  //
}

void __stdcall glVertex2iv(const GLint *v) {
  //
}

void __stdcall glVertex2s(GLshort x, GLshort y) {
  //
}

void __stdcall glVertex2sv(const GLshort *v) {
  //
}

void __stdcall glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
  //
}

void __stdcall glVertex3dv(const GLdouble *v) {
  //
}

void __stdcall glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
  //
}

void __stdcall glVertex3fv(const GLfloat *v) {
  //
}

void __stdcall glVertex3i(GLint x, GLint y, GLint z) {
  //
}

void __stdcall glVertex3iv(const GLint *v) {
  //
}

void __stdcall glVertex3s(GLshort x, GLshort y, GLshort z) {
  //
}

void __stdcall glVertex3sv(const GLshort *v) {
  //
}

void __stdcall glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
  //
}

void __stdcall glVertex4dv(const GLdouble *v) {
  //
}

void __stdcall glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  //
}

void __stdcall glVertex4fv(const GLfloat *v) {
  //
}

void __stdcall glVertex4i(GLint x, GLint y, GLint z, GLint w) {
  //
}

void __stdcall glVertex4iv(const GLint *v) {
  //
}

void __stdcall glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
  //
}

void __stdcall glVertex4sv(const GLshort *v) {
  //
}

void __stdcall glVertexPointer(GLint size, GLenum type, GLsizei stride,
                               const GLvoid *pointer) {
  //
}

void __stdcall glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
  //
}

void __stdcall glPushAttrib(GLbitfield mask) {
}

void __stdcall glPopAttrib(void) {
}

void __stdcall glPushClientAttrib(GLbitfield mask) {
}

void __stdcall glPopClientAttrib(void) {
}
