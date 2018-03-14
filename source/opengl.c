#define ATTRIB 
#define APIENTRY __stdcall
#define WINAPI __stdcall
#define WINGDIAPI
#include "GL.h"

#include <assert.h>

#include "gl_func_enum.h"

extern void *gl_func_table[];

ATTRIB
void APIENTRY glAccum(GLenum op, GLfloat value) {
    typedef void (WINAPI * glAccum_t)(GLenum, GLfloat);
    glAccum_t thunk = (glAccum_t)gl_func_table[e_glAccum];
    assert(thunk);
    thunk(op, value);
}

ATTRIB
void APIENTRY glAlphaFunc(GLenum func, GLclampf ref) {
    typedef void (WINAPI * glAlphaFunc_t)(GLenum, GLclampf);
    glAlphaFunc_t thunk = (glAlphaFunc_t)gl_func_table[e_glAlphaFunc];
    assert(thunk);
    thunk(func, ref);
}

ATTRIB
GLboolean APIENTRY glAreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences) {
    typedef GLboolean (WINAPI * glAreTexturesResident_t)(GLsizei, const GLuint *, GLboolean *);
    glAreTexturesResident_t thunk = (glAreTexturesResident_t)gl_func_table[e_glAreTexturesResident];
    assert(thunk);
    return thunk(n, textures, residences);
}

ATTRIB
void APIENTRY glArrayElement(GLint i) {
    typedef void (WINAPI * glArrayElement_t)(GLint);
    glArrayElement_t thunk = (glArrayElement_t)gl_func_table[e_glArrayElement];
    assert(thunk);
    thunk(i);
}

ATTRIB
void APIENTRY glBegin(GLenum mode) {
    typedef void (WINAPI * glBegin_t)(GLenum);
    glBegin_t thunk = (glBegin_t)gl_func_table[e_glBegin];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glBindTexture(GLenum target, GLuint texture) {
    typedef void (WINAPI * glBindTexture_t)(GLenum, GLuint);
    glBindTexture_t thunk = (glBindTexture_t)gl_func_table[e_glBindTexture];
    assert(thunk);
    thunk(target, texture);
}

ATTRIB
void APIENTRY glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap) {
    typedef void (WINAPI * glBitmap_t)(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte *);
    glBitmap_t thunk = (glBitmap_t)gl_func_table[e_glBitmap];
    assert(thunk);
    thunk(width, height, xorig, yorig, xmove, ymove, bitmap);
}

ATTRIB
void APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor) {
    typedef void (WINAPI * glBlendFunc_t)(GLenum, GLenum);
    glBlendFunc_t thunk = (glBlendFunc_t)gl_func_table[e_glBlendFunc];
    assert(thunk);
    thunk(sfactor, dfactor);
}

ATTRIB
void APIENTRY glCallList(GLuint list) {
    typedef void (WINAPI * glCallList_t)(GLuint);
    glCallList_t thunk = (glCallList_t)gl_func_table[e_glCallList];
    assert(thunk);
    thunk(list);
}

ATTRIB
void APIENTRY glCallLists(GLsizei n, GLenum type, const GLvoid * lists) {
    typedef void (WINAPI * glCallLists_t)(GLsizei, GLenum, const GLvoid *);
    glCallLists_t thunk = (glCallLists_t)gl_func_table[e_glCallLists];
    assert(thunk);
    thunk(n, type, lists);
}

ATTRIB
void APIENTRY glClear(GLbitfield mask) {
    typedef void (WINAPI * glClear_t)(GLbitfield);
    glClear_t thunk = (glClear_t)gl_func_table[e_glClear];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    typedef void (WINAPI * glClearAccum_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glClearAccum_t thunk = (glClearAccum_t)gl_func_table[e_glClearAccum];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
    typedef void (WINAPI * glClearColor_t)(GLclampf, GLclampf, GLclampf, GLclampf);
    glClearColor_t thunk = (glClearColor_t)gl_func_table[e_glClearColor];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glClearDepth(GLclampd depth) {
    typedef void (WINAPI * glClearDepth_t)(GLclampd);
    glClearDepth_t thunk = (glClearDepth_t)gl_func_table[e_glClearDepth];
    assert(thunk);
    thunk(depth);
}

ATTRIB
void APIENTRY glClearIndex(GLfloat c) {
    typedef void (WINAPI * glClearIndex_t)(GLfloat);
    glClearIndex_t thunk = (glClearIndex_t)gl_func_table[e_glClearIndex];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glClearStencil(GLint s) {
    typedef void (WINAPI * glClearStencil_t)(GLint);
    glClearStencil_t thunk = (glClearStencil_t)gl_func_table[e_glClearStencil];
    assert(thunk);
    thunk(s);
}

ATTRIB
void APIENTRY glClipPlane(GLenum plane, const GLdouble * equation) {
    typedef void (WINAPI * glClipPlane_t)(GLenum, const GLdouble *);
    glClipPlane_t thunk = (glClipPlane_t)gl_func_table[e_glClipPlane];
    assert(thunk);
    thunk(plane, equation);
}

ATTRIB
void APIENTRY glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
    typedef void (WINAPI * glColor3b_t)(GLbyte, GLbyte, GLbyte);
    glColor3b_t thunk = (glColor3b_t)gl_func_table[e_glColor3b];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3bv(const GLbyte * v) {
    typedef void (WINAPI * glColor3bv_t)(const GLbyte *);
    glColor3bv_t thunk = (glColor3bv_t)gl_func_table[e_glColor3bv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
    typedef void (WINAPI * glColor3d_t)(GLdouble, GLdouble, GLdouble);
    glColor3d_t thunk = (glColor3d_t)gl_func_table[e_glColor3d];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3dv(const GLdouble * v) {
    typedef void (WINAPI * glColor3dv_t)(const GLdouble *);
    glColor3dv_t thunk = (glColor3dv_t)gl_func_table[e_glColor3dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    typedef void (WINAPI * glColor3f_t)(GLfloat, GLfloat, GLfloat);
    glColor3f_t thunk = (glColor3f_t)gl_func_table[e_glColor3f];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3fv(const GLfloat * v) {
    typedef void (WINAPI * glColor3fv_t)(const GLfloat *);
    glColor3fv_t thunk = (glColor3fv_t)gl_func_table[e_glColor3fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3i(GLint red, GLint green, GLint blue) {
    typedef void (WINAPI * glColor3i_t)(GLint, GLint, GLint);
    glColor3i_t thunk = (glColor3i_t)gl_func_table[e_glColor3i];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3iv(const GLint * v) {
    typedef void (WINAPI * glColor3iv_t)(const GLint *);
    glColor3iv_t thunk = (glColor3iv_t)gl_func_table[e_glColor3iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3s(GLshort red, GLshort green, GLshort blue) {
    typedef void (WINAPI * glColor3s_t)(GLshort, GLshort, GLshort);
    glColor3s_t thunk = (glColor3s_t)gl_func_table[e_glColor3s];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3sv(const GLshort * v) {
    typedef void (WINAPI * glColor3sv_t)(const GLshort *);
    glColor3sv_t thunk = (glColor3sv_t)gl_func_table[e_glColor3sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    typedef void (WINAPI * glColor3ub_t)(GLubyte, GLubyte, GLubyte);
    glColor3ub_t thunk = (glColor3ub_t)gl_func_table[e_glColor3ub];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3ubv(const GLubyte * v) {
    typedef void (WINAPI * glColor3ubv_t)(const GLubyte *);
    glColor3ubv_t thunk = (glColor3ubv_t)gl_func_table[e_glColor3ubv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3ui(GLuint red, GLuint green, GLuint blue) {
    typedef void (WINAPI * glColor3ui_t)(GLuint, GLuint, GLuint);
    glColor3ui_t thunk = (glColor3ui_t)gl_func_table[e_glColor3ui];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3uiv(const GLuint * v) {
    typedef void (WINAPI * glColor3uiv_t)(const GLuint *);
    glColor3uiv_t thunk = (glColor3uiv_t)gl_func_table[e_glColor3uiv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor3us(GLushort red, GLushort green, GLushort blue) {
    typedef void (WINAPI * glColor3us_t)(GLushort, GLushort, GLushort);
    glColor3us_t thunk = (glColor3us_t)gl_func_table[e_glColor3us];
    assert(thunk);
    thunk(red, green, blue);
}

ATTRIB
void APIENTRY glColor3usv(const GLushort * v) {
    typedef void (WINAPI * glColor3usv_t)(const GLushort *);
    glColor3usv_t thunk = (glColor3usv_t)gl_func_table[e_glColor3usv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
    typedef void (WINAPI * glColor4b_t)(GLbyte, GLbyte, GLbyte, GLbyte);
    glColor4b_t thunk = (glColor4b_t)gl_func_table[e_glColor4b];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4bv(const GLbyte * v) {
    typedef void (WINAPI * glColor4bv_t)(const GLbyte *);
    glColor4bv_t thunk = (glColor4bv_t)gl_func_table[e_glColor4bv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) {
    typedef void (WINAPI * glColor4d_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glColor4d_t thunk = (glColor4d_t)gl_func_table[e_glColor4d];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4dv(const GLdouble * v) {
    typedef void (WINAPI * glColor4dv_t)(const GLdouble *);
    glColor4dv_t thunk = (glColor4dv_t)gl_func_table[e_glColor4dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    typedef void (WINAPI * glColor4f_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glColor4f_t thunk = (glColor4f_t)gl_func_table[e_glColor4f];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4fv(const GLfloat * v) {
    typedef void (WINAPI * glColor4fv_t)(const GLfloat *);
    glColor4fv_t thunk = (glColor4fv_t)gl_func_table[e_glColor4fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
    typedef void (WINAPI * glColor4i_t)(GLint, GLint, GLint, GLint);
    glColor4i_t thunk = (glColor4i_t)gl_func_table[e_glColor4i];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4iv(const GLint * v) {
    typedef void (WINAPI * glColor4iv_t)(const GLint *);
    glColor4iv_t thunk = (glColor4iv_t)gl_func_table[e_glColor4iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) {
    typedef void (WINAPI * glColor4s_t)(GLshort, GLshort, GLshort, GLshort);
    glColor4s_t thunk = (glColor4s_t)gl_func_table[e_glColor4s];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4sv(const GLshort * v) {
    typedef void (WINAPI * glColor4sv_t)(const GLshort *);
    glColor4sv_t thunk = (glColor4sv_t)gl_func_table[e_glColor4sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    typedef void (WINAPI * glColor4ub_t)(GLubyte, GLubyte, GLubyte, GLubyte);
    glColor4ub_t thunk = (glColor4ub_t)gl_func_table[e_glColor4ub];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4ubv(const GLubyte * v) {
    typedef void (WINAPI * glColor4ubv_t)(const GLubyte *);
    glColor4ubv_t thunk = (glColor4ubv_t)gl_func_table[e_glColor4ubv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
    typedef void (WINAPI * glColor4ui_t)(GLuint, GLuint, GLuint, GLuint);
    glColor4ui_t thunk = (glColor4ui_t)gl_func_table[e_glColor4ui];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4uiv(const GLuint * v) {
    typedef void (WINAPI * glColor4uiv_t)(const GLuint *);
    glColor4uiv_t thunk = (glColor4uiv_t)gl_func_table[e_glColor4uiv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) {
    typedef void (WINAPI * glColor4us_t)(GLushort, GLushort, GLushort, GLushort);
    glColor4us_t thunk = (glColor4us_t)gl_func_table[e_glColor4us];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColor4usv(const GLushort * v) {
    typedef void (WINAPI * glColor4usv_t)(const GLushort *);
    glColor4usv_t thunk = (glColor4usv_t)gl_func_table[e_glColor4usv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    typedef void (WINAPI * glColorMask_t)(GLboolean, GLboolean, GLboolean, GLboolean);
    glColorMask_t thunk = (glColorMask_t)gl_func_table[e_glColorMask];
    assert(thunk);
    thunk(red, green, blue, alpha);
}

ATTRIB
void APIENTRY glColorMaterial(GLenum face, GLenum mode) {
    typedef void (WINAPI * glColorMaterial_t)(GLenum, GLenum);
    glColorMaterial_t thunk = (glColorMaterial_t)gl_func_table[e_glColorMaterial];
    assert(thunk);
    thunk(face, mode);
}

ATTRIB
void APIENTRY glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glColorPointer_t)(GLint, GLenum, GLsizei, const GLvoid *);
    glColorPointer_t thunk = (glColorPointer_t)gl_func_table[e_glColorPointer];
    assert(thunk);
    thunk(size, type, stride, pointer);
}

ATTRIB
void APIENTRY glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) {
    typedef void (WINAPI * glCopyPixels_t)(GLint, GLint, GLsizei, GLsizei, GLenum);
    glCopyPixels_t thunk = (glCopyPixels_t)gl_func_table[e_glCopyPixels];
    assert(thunk);
    thunk(x, y, width, height, type);
}

ATTRIB
void APIENTRY glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border) {
    typedef void (WINAPI * glCopyTexImage1D_t)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
    glCopyTexImage1D_t thunk = (glCopyTexImage1D_t)gl_func_table[e_glCopyTexImage1D];
    assert(thunk);
    thunk(target, level, internalFormat, x, y, width, border);
}

ATTRIB
void APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    typedef void (WINAPI * glCopyTexImage2D_t)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
    glCopyTexImage2D_t thunk = (glCopyTexImage2D_t)gl_func_table[e_glCopyTexImage2D];
    assert(thunk);
    thunk(target, level, internalFormat, x, y, width, height, border);
}

ATTRIB
void APIENTRY glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    typedef void (WINAPI * glCopyTexSubImage1D_t)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
    glCopyTexSubImage1D_t thunk = (glCopyTexSubImage1D_t)gl_func_table[e_glCopyTexSubImage1D];
    assert(thunk);
    thunk(target, level, xoffset, x, y, width);
}

ATTRIB
void APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    typedef void (WINAPI * glCopyTexSubImage2D_t)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
    glCopyTexSubImage2D_t thunk = (glCopyTexSubImage2D_t)gl_func_table[e_glCopyTexSubImage2D];
    assert(thunk);
    thunk(target, level, xoffset, yoffset, x, y, width, height);
}

ATTRIB
void APIENTRY glCullFace(GLenum mode) {
    typedef void (WINAPI * glCullFace_t)(GLenum);
    glCullFace_t thunk = (glCullFace_t)gl_func_table[e_glCullFace];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glDebugEntry(void) {
    typedef void (WINAPI * glDebugEntry_t)();
    glDebugEntry_t thunk = (glDebugEntry_t)gl_func_table[e_glDebugEntry];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glDeleteLists(GLuint list, GLsizei range) {
    typedef void (WINAPI * glDeleteLists_t)(GLuint, GLsizei);
    glDeleteLists_t thunk = (glDeleteLists_t)gl_func_table[e_glDeleteLists];
    assert(thunk);
    thunk(list, range);
}

ATTRIB
void APIENTRY glDeleteTextures(GLsizei n, const GLuint * textures) {
    typedef void (WINAPI * glDeleteTextures_t)(GLsizei, const GLuint *);
    glDeleteTextures_t thunk = (glDeleteTextures_t)gl_func_table[e_glDeleteTextures];
    assert(thunk);
    thunk(n, textures);
}

ATTRIB
void APIENTRY glDepthFunc(GLenum func) {
    typedef void (WINAPI * glDepthFunc_t)(GLenum);
    glDepthFunc_t thunk = (glDepthFunc_t)gl_func_table[e_glDepthFunc];
    assert(thunk);
    thunk(func);
}

ATTRIB
void APIENTRY glDepthMask(GLboolean flag) {
    typedef void (WINAPI * glDepthMask_t)(GLboolean);
    glDepthMask_t thunk = (glDepthMask_t)gl_func_table[e_glDepthMask];
    assert(thunk);
    thunk(flag);
}

ATTRIB
void APIENTRY glDepthRange(GLclampd zNear, GLclampd zFar) {
    typedef void (WINAPI * glDepthRange_t)(GLclampd, GLclampd);
    glDepthRange_t thunk = (glDepthRange_t)gl_func_table[e_glDepthRange];
    assert(thunk);
    thunk(zNear, zFar);
}

ATTRIB
void APIENTRY glDisable(GLenum cap) {
    typedef void (WINAPI * glDisable_t)(GLenum);
    glDisable_t thunk = (glDisable_t)gl_func_table[e_glDisable];
    assert(thunk);
    thunk(cap);
}

ATTRIB
void APIENTRY glDisableClientState(GLenum array) {
    typedef void (WINAPI * glDisableClientState_t)(GLenum);
    glDisableClientState_t thunk = (glDisableClientState_t)gl_func_table[e_glDisableClientState];
    assert(thunk);
    thunk(array);
}

ATTRIB
void APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    typedef void (WINAPI * glDrawArrays_t)(GLenum, GLint, GLsizei);
    glDrawArrays_t thunk = (glDrawArrays_t)gl_func_table[e_glDrawArrays];
    assert(thunk);
    thunk(mode, first, count);
}

ATTRIB
void APIENTRY glDrawBuffer(GLenum mode) {
    typedef void (WINAPI * glDrawBuffer_t)(GLenum);
    glDrawBuffer_t thunk = (glDrawBuffer_t)gl_func_table[e_glDrawBuffer];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) {
    typedef void (WINAPI * glDrawElements_t)(GLenum, GLsizei, GLenum, const GLvoid *);
    glDrawElements_t thunk = (glDrawElements_t)gl_func_table[e_glDrawElements];
    assert(thunk);
    thunk(mode, count, type, indices);
}

ATTRIB
void APIENTRY glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) {
    typedef void (WINAPI * glDrawPixels_t)(GLsizei, GLsizei, GLenum, GLenum, const GLvoid *);
    glDrawPixels_t thunk = (glDrawPixels_t)gl_func_table[e_glDrawPixels];
    assert(thunk);
    thunk(width, height, format, type, pixels);
}

ATTRIB
void APIENTRY glEdgeFlag(GLboolean flag) {
    typedef void (WINAPI * glEdgeFlag_t)(GLboolean);
    glEdgeFlag_t thunk = (glEdgeFlag_t)gl_func_table[e_glEdgeFlag];
    assert(thunk);
    thunk(flag);
}

ATTRIB
void APIENTRY glEdgeFlagPointer(GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glEdgeFlagPointer_t)(GLsizei, const GLvoid *);
    glEdgeFlagPointer_t thunk = (glEdgeFlagPointer_t)gl_func_table[e_glEdgeFlagPointer];
    assert(thunk);
    thunk(stride, pointer);
}

ATTRIB
void APIENTRY glEdgeFlagv(const GLboolean * flag) {
    typedef void (WINAPI * glEdgeFlagv_t)(const GLboolean *);
    glEdgeFlagv_t thunk = (glEdgeFlagv_t)gl_func_table[e_glEdgeFlagv];
    assert(thunk);
    thunk(flag);
}

ATTRIB
void APIENTRY glEnable(GLenum cap) {
    typedef void (WINAPI * glEnable_t)(GLenum);
    glEnable_t thunk = (glEnable_t)gl_func_table[e_glEnable];
    assert(thunk);
    thunk(cap);
}

ATTRIB
void APIENTRY glEnableClientState(GLenum array) {
    typedef void (WINAPI * glEnableClientState_t)(GLenum);
    glEnableClientState_t thunk = (glEnableClientState_t)gl_func_table[e_glEnableClientState];
    assert(thunk);
    thunk(array);
}

ATTRIB
void APIENTRY glEnd(void) {
    typedef void (WINAPI * glEnd_t)();
    glEnd_t thunk = (glEnd_t)gl_func_table[e_glEnd];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glEndList(void) {
    typedef void (WINAPI * glEndList_t)();
    glEndList_t thunk = (glEndList_t)gl_func_table[e_glEndList];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glEvalCoord1d(GLdouble u) {
    typedef void (WINAPI * glEvalCoord1d_t)(GLdouble);
    glEvalCoord1d_t thunk = (glEvalCoord1d_t)gl_func_table[e_glEvalCoord1d];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalCoord1dv(const GLdouble * u) {
    typedef void (WINAPI * glEvalCoord1dv_t)(const GLdouble *);
    glEvalCoord1dv_t thunk = (glEvalCoord1dv_t)gl_func_table[e_glEvalCoord1dv];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalCoord1f(GLfloat u) {
    typedef void (WINAPI * glEvalCoord1f_t)(GLfloat);
    glEvalCoord1f_t thunk = (glEvalCoord1f_t)gl_func_table[e_glEvalCoord1f];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalCoord1fv(const GLfloat * u) {
    typedef void (WINAPI * glEvalCoord1fv_t)(const GLfloat *);
    glEvalCoord1fv_t thunk = (glEvalCoord1fv_t)gl_func_table[e_glEvalCoord1fv];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalCoord2d(GLdouble u, GLdouble v) {
    typedef void (WINAPI * glEvalCoord2d_t)(GLdouble, GLdouble);
    glEvalCoord2d_t thunk = (glEvalCoord2d_t)gl_func_table[e_glEvalCoord2d];
    assert(thunk);
    thunk(u, v);
}

ATTRIB
void APIENTRY glEvalCoord2dv(const GLdouble * u) {
    typedef void (WINAPI * glEvalCoord2dv_t)(const GLdouble *);
    glEvalCoord2dv_t thunk = (glEvalCoord2dv_t)gl_func_table[e_glEvalCoord2dv];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalCoord2f(GLfloat u, GLfloat v) {
    typedef void (WINAPI * glEvalCoord2f_t)(GLfloat, GLfloat);
    glEvalCoord2f_t thunk = (glEvalCoord2f_t)gl_func_table[e_glEvalCoord2f];
    assert(thunk);
    thunk(u, v);
}

ATTRIB
void APIENTRY glEvalCoord2fv(const GLfloat * u) {
    typedef void (WINAPI * glEvalCoord2fv_t)(const GLfloat *);
    glEvalCoord2fv_t thunk = (glEvalCoord2fv_t)gl_func_table[e_glEvalCoord2fv];
    assert(thunk);
    thunk(u);
}

ATTRIB
void APIENTRY glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
    typedef void (WINAPI * glEvalMesh1_t)(GLenum, GLint, GLint);
    glEvalMesh1_t thunk = (glEvalMesh1_t)gl_func_table[e_glEvalMesh1];
    assert(thunk);
    thunk(mode, i1, i2);
}

ATTRIB
void APIENTRY glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
    typedef void (WINAPI * glEvalMesh2_t)(GLenum, GLint, GLint, GLint, GLint);
    glEvalMesh2_t thunk = (glEvalMesh2_t)gl_func_table[e_glEvalMesh2];
    assert(thunk);
    thunk(mode, i1, i2, j1, j2);
}

ATTRIB
void APIENTRY glEvalPoint1(GLint i) {
    typedef void (WINAPI * glEvalPoint1_t)(GLint);
    glEvalPoint1_t thunk = (glEvalPoint1_t)gl_func_table[e_glEvalPoint1];
    assert(thunk);
    thunk(i);
}

ATTRIB
void APIENTRY glEvalPoint2(GLint i, GLint j) {
    typedef void (WINAPI * glEvalPoint2_t)(GLint, GLint);
    glEvalPoint2_t thunk = (glEvalPoint2_t)gl_func_table[e_glEvalPoint2];
    assert(thunk);
    thunk(i, j);
}

ATTRIB
void APIENTRY glFeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer) {
    typedef void (WINAPI * glFeedbackBuffer_t)(GLsizei, GLenum, GLfloat *);
    glFeedbackBuffer_t thunk = (glFeedbackBuffer_t)gl_func_table[e_glFeedbackBuffer];
    assert(thunk);
    thunk(size, type, buffer);
}

ATTRIB
void APIENTRY glFinish(void) {
    typedef void (WINAPI * glFinish_t)();
    glFinish_t thunk = (glFinish_t)gl_func_table[e_glFinish];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glFlush(void) {
    typedef void (WINAPI * glFlush_t)();
    glFlush_t thunk = (glFlush_t)gl_func_table[e_glFlush];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glFogf(GLenum pname, GLfloat param) {
    typedef void (WINAPI * glFogf_t)(GLenum, GLfloat);
    glFogf_t thunk = (glFogf_t)gl_func_table[e_glFogf];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glFogfv(GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glFogfv_t)(GLenum, const GLfloat *);
    glFogfv_t thunk = (glFogfv_t)gl_func_table[e_glFogfv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glFogi(GLenum pname, GLint param) {
    typedef void (WINAPI * glFogi_t)(GLenum, GLint);
    glFogi_t thunk = (glFogi_t)gl_func_table[e_glFogi];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glFogiv(GLenum pname, const GLint * params) {
    typedef void (WINAPI * glFogiv_t)(GLenum, const GLint *);
    glFogiv_t thunk = (glFogiv_t)gl_func_table[e_glFogiv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glFrontFace(GLenum mode) {
    typedef void (WINAPI * glFrontFace_t)(GLenum);
    glFrontFace_t thunk = (glFrontFace_t)gl_func_table[e_glFrontFace];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    typedef void (WINAPI * glFrustum_t)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
    glFrustum_t thunk = (glFrustum_t)gl_func_table[e_glFrustum];
    assert(thunk);
    thunk(left, right, bottom, top, zNear, zFar);
}

ATTRIB
GLuint APIENTRY glGenLists(GLsizei range) {
    typedef GLuint (WINAPI * glGenLists_t)(GLsizei);
    glGenLists_t thunk = (glGenLists_t)gl_func_table[e_glGenLists];
    assert(thunk);
    return thunk(range);
}

ATTRIB
void APIENTRY glGenTextures(GLsizei n, GLuint * textures) {
    typedef void (WINAPI * glGenTextures_t)(GLsizei, GLuint *);
    glGenTextures_t thunk = (glGenTextures_t)gl_func_table[e_glGenTextures];
    assert(thunk);
    thunk(n, textures);
}

ATTRIB
void APIENTRY glGetBooleanv(GLenum pname, GLboolean * params) {
    typedef void (WINAPI * glGetBooleanv_t)(GLenum, GLboolean *);
    glGetBooleanv_t thunk = (glGetBooleanv_t)gl_func_table[e_glGetBooleanv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glGetClipPlane(GLenum plane, GLdouble * equation) {
    typedef void (WINAPI * glGetClipPlane_t)(GLenum, GLdouble *);
    glGetClipPlane_t thunk = (glGetClipPlane_t)gl_func_table[e_glGetClipPlane];
    assert(thunk);
    thunk(plane, equation);
}

ATTRIB
void APIENTRY glGetDoublev(GLenum pname, GLdouble * params) {
    typedef void (WINAPI * glGetDoublev_t)(GLenum, GLdouble *);
    glGetDoublev_t thunk = (glGetDoublev_t)gl_func_table[e_glGetDoublev];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
GLenum APIENTRY glGetError(void) {
    typedef GLenum (WINAPI * glGetError_t)();
    glGetError_t thunk = (glGetError_t)gl_func_table[e_glGetError];
    assert(thunk);
    return thunk();
}

ATTRIB
void APIENTRY glGetFloatv(GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetFloatv_t)(GLenum, GLfloat *);
    glGetFloatv_t thunk = (glGetFloatv_t)gl_func_table[e_glGetFloatv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glGetIntegerv(GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetIntegerv_t)(GLenum, GLint *);
    glGetIntegerv_t thunk = (glGetIntegerv_t)gl_func_table[e_glGetIntegerv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glGetLightfv(GLenum light, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetLightfv_t)(GLenum, GLenum, GLfloat *);
    glGetLightfv_t thunk = (glGetLightfv_t)gl_func_table[e_glGetLightfv];
    assert(thunk);
    thunk(light, pname, params);
}

ATTRIB
void APIENTRY glGetLightiv(GLenum light, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetLightiv_t)(GLenum, GLenum, GLint *);
    glGetLightiv_t thunk = (glGetLightiv_t)gl_func_table[e_glGetLightiv];
    assert(thunk);
    thunk(light, pname, params);
}

ATTRIB
void APIENTRY glGetMapdv(GLenum target, GLenum query, GLdouble * v) {
    typedef void (WINAPI * glGetMapdv_t)(GLenum, GLenum, GLdouble *);
    glGetMapdv_t thunk = (glGetMapdv_t)gl_func_table[e_glGetMapdv];
    assert(thunk);
    thunk(target, query, v);
}

ATTRIB
void APIENTRY glGetMapfv(GLenum target, GLenum query, GLfloat * v) {
    typedef void (WINAPI * glGetMapfv_t)(GLenum, GLenum, GLfloat *);
    glGetMapfv_t thunk = (glGetMapfv_t)gl_func_table[e_glGetMapfv];
    assert(thunk);
    thunk(target, query, v);
}

ATTRIB
void APIENTRY glGetMapiv(GLenum target, GLenum query, GLint * v) {
    typedef void (WINAPI * glGetMapiv_t)(GLenum, GLenum, GLint *);
    glGetMapiv_t thunk = (glGetMapiv_t)gl_func_table[e_glGetMapiv];
    assert(thunk);
    thunk(target, query, v);
}

ATTRIB
void APIENTRY glGetMaterialfv(GLenum face, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetMaterialfv_t)(GLenum, GLenum, GLfloat *);
    glGetMaterialfv_t thunk = (glGetMaterialfv_t)gl_func_table[e_glGetMaterialfv];
    assert(thunk);
    thunk(face, pname, params);
}

ATTRIB
void APIENTRY glGetMaterialiv(GLenum face, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetMaterialiv_t)(GLenum, GLenum, GLint *);
    glGetMaterialiv_t thunk = (glGetMaterialiv_t)gl_func_table[e_glGetMaterialiv];
    assert(thunk);
    thunk(face, pname, params);
}

ATTRIB
void APIENTRY glGetPixelMapfv(GLenum map, GLfloat * values) {
    typedef void (WINAPI * glGetPixelMapfv_t)(GLenum, GLfloat *);
    glGetPixelMapfv_t thunk = (glGetPixelMapfv_t)gl_func_table[e_glGetPixelMapfv];
    assert(thunk);
    thunk(map, values);
}

ATTRIB
void APIENTRY glGetPixelMapuiv(GLenum map, GLuint * values) {
    typedef void (WINAPI * glGetPixelMapuiv_t)(GLenum, GLuint *);
    glGetPixelMapuiv_t thunk = (glGetPixelMapuiv_t)gl_func_table[e_glGetPixelMapuiv];
    assert(thunk);
    thunk(map, values);
}

ATTRIB
void APIENTRY glGetPixelMapusv(GLenum map, GLushort * values) {
    typedef void (WINAPI * glGetPixelMapusv_t)(GLenum, GLushort *);
    glGetPixelMapusv_t thunk = (glGetPixelMapusv_t)gl_func_table[e_glGetPixelMapusv];
    assert(thunk);
    thunk(map, values);
}

ATTRIB
void APIENTRY glGetPointerv(GLenum pname, GLvoid ** params) {
    typedef void (WINAPI * glGetPointerv_t)(GLenum, GLvoid **);
    glGetPointerv_t thunk = (glGetPointerv_t)gl_func_table[e_glGetPointerv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glGetPolygonStipple(GLubyte * mask) {
    typedef void (WINAPI * glGetPolygonStipple_t)(GLubyte *);
    glGetPolygonStipple_t thunk = (glGetPolygonStipple_t)gl_func_table[e_glGetPolygonStipple];
    assert(thunk);
    thunk(mask);
}

ATTRIB
const GLubyte * APIENTRY glGetString(GLenum name) {
    typedef const GLubyte * (WINAPI * glGetString_t)(GLenum);
    glGetString_t thunk = (glGetString_t)gl_func_table[e_glGetString];
    assert(thunk);
    return thunk(name);
}

ATTRIB
void APIENTRY glGetTexEnvfv(GLenum target, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetTexEnvfv_t)(GLenum, GLenum, GLfloat *);
    glGetTexEnvfv_t thunk = (glGetTexEnvfv_t)gl_func_table[e_glGetTexEnvfv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glGetTexEnviv(GLenum target, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetTexEnviv_t)(GLenum, GLenum, GLint *);
    glGetTexEnviv_t thunk = (glGetTexEnviv_t)gl_func_table[e_glGetTexEnviv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glGetTexGendv(GLenum coord, GLenum pname, GLdouble * params) {
    typedef void (WINAPI * glGetTexGendv_t)(GLenum, GLenum, GLdouble *);
    glGetTexGendv_t thunk = (glGetTexGendv_t)gl_func_table[e_glGetTexGendv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glGetTexGenfv(GLenum coord, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetTexGenfv_t)(GLenum, GLenum, GLfloat *);
    glGetTexGenfv_t thunk = (glGetTexGenfv_t)gl_func_table[e_glGetTexGenfv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glGetTexGeniv(GLenum coord, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetTexGeniv_t)(GLenum, GLenum, GLint *);
    glGetTexGeniv_t thunk = (glGetTexGeniv_t)gl_func_table[e_glGetTexGeniv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels) {
    typedef void (WINAPI * glGetTexImage_t)(GLenum, GLint, GLenum, GLenum, GLvoid *);
    glGetTexImage_t thunk = (glGetTexImage_t)gl_func_table[e_glGetTexImage];
    assert(thunk);
    thunk(target, level, format, type, pixels);
}

ATTRIB
void APIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetTexLevelParameterfv_t)(GLenum, GLint, GLenum, GLfloat *);
    glGetTexLevelParameterfv_t thunk = (glGetTexLevelParameterfv_t)gl_func_table[e_glGetTexLevelParameterfv];
    assert(thunk);
    thunk(target, level, pname, params);
}

ATTRIB
void APIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetTexLevelParameteriv_t)(GLenum, GLint, GLenum, GLint *);
    glGetTexLevelParameteriv_t thunk = (glGetTexLevelParameteriv_t)gl_func_table[e_glGetTexLevelParameteriv];
    assert(thunk);
    thunk(target, level, pname, params);
}

ATTRIB
void APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    typedef void (WINAPI * glGetTexParameterfv_t)(GLenum, GLenum, GLfloat *);
    glGetTexParameterfv_t thunk = (glGetTexParameterfv_t)gl_func_table[e_glGetTexParameterfv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    typedef void (WINAPI * glGetTexParameteriv_t)(GLenum, GLenum, GLint *);
    glGetTexParameteriv_t thunk = (glGetTexParameteriv_t)gl_func_table[e_glGetTexParameteriv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glHint(GLenum target, GLenum mode) {
    typedef void (WINAPI * glHint_t)(GLenum, GLenum);
    glHint_t thunk = (glHint_t)gl_func_table[e_glHint];
    assert(thunk);
    thunk(target, mode);
}

ATTRIB
void APIENTRY glIndexMask(GLuint mask) {
    typedef void (WINAPI * glIndexMask_t)(GLuint);
    glIndexMask_t thunk = (glIndexMask_t)gl_func_table[e_glIndexMask];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glIndexPointer(GLenum type, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glIndexPointer_t)(GLenum, GLsizei, const GLvoid *);
    glIndexPointer_t thunk = (glIndexPointer_t)gl_func_table[e_glIndexPointer];
    assert(thunk);
    thunk(type, stride, pointer);
}

ATTRIB
void APIENTRY glIndexd(GLdouble c) {
    typedef void (WINAPI * glIndexd_t)(GLdouble);
    glIndexd_t thunk = (glIndexd_t)gl_func_table[e_glIndexd];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexdv(const GLdouble * c) {
    typedef void (WINAPI * glIndexdv_t)(const GLdouble *);
    glIndexdv_t thunk = (glIndexdv_t)gl_func_table[e_glIndexdv];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexf(GLfloat c) {
    typedef void (WINAPI * glIndexf_t)(GLfloat);
    glIndexf_t thunk = (glIndexf_t)gl_func_table[e_glIndexf];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexfv(const GLfloat * c) {
    typedef void (WINAPI * glIndexfv_t)(const GLfloat *);
    glIndexfv_t thunk = (glIndexfv_t)gl_func_table[e_glIndexfv];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexi(GLint c) {
    typedef void (WINAPI * glIndexi_t)(GLint);
    glIndexi_t thunk = (glIndexi_t)gl_func_table[e_glIndexi];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexiv(const GLint * c) {
    typedef void (WINAPI * glIndexiv_t)(const GLint *);
    glIndexiv_t thunk = (glIndexiv_t)gl_func_table[e_glIndexiv];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexs(GLshort c) {
    typedef void (WINAPI * glIndexs_t)(GLshort);
    glIndexs_t thunk = (glIndexs_t)gl_func_table[e_glIndexs];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexsv(const GLshort * c) {
    typedef void (WINAPI * glIndexsv_t)(const GLshort *);
    glIndexsv_t thunk = (glIndexsv_t)gl_func_table[e_glIndexsv];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexub(GLubyte c) {
    typedef void (WINAPI * glIndexub_t)(GLubyte);
    glIndexub_t thunk = (glIndexub_t)gl_func_table[e_glIndexub];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glIndexubv(const GLubyte * c) {
    typedef void (WINAPI * glIndexubv_t)(const GLubyte *);
    glIndexubv_t thunk = (glIndexubv_t)gl_func_table[e_glIndexubv];
    assert(thunk);
    thunk(c);
}

ATTRIB
void APIENTRY glInitNames(void) {
    typedef void (WINAPI * glInitNames_t)();
    glInitNames_t thunk = (glInitNames_t)gl_func_table[e_glInitNames];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glInterleavedArrays_t)(GLenum, GLsizei, const GLvoid *);
    glInterleavedArrays_t thunk = (glInterleavedArrays_t)gl_func_table[e_glInterleavedArrays];
    assert(thunk);
    thunk(format, stride, pointer);
}

ATTRIB
GLboolean APIENTRY glIsEnabled(GLenum cap) {
    typedef GLboolean (WINAPI * glIsEnabled_t)(GLenum);
    glIsEnabled_t thunk = (glIsEnabled_t)gl_func_table[e_glIsEnabled];
    assert(thunk);
    return thunk(cap);
}

ATTRIB
GLboolean APIENTRY glIsList(GLuint list) {
    typedef GLboolean (WINAPI * glIsList_t)(GLuint);
    glIsList_t thunk = (glIsList_t)gl_func_table[e_glIsList];
    assert(thunk);
    return thunk(list);
}

ATTRIB
GLboolean APIENTRY glIsTexture(GLuint texture) {
    typedef GLboolean (WINAPI * glIsTexture_t)(GLuint);
    glIsTexture_t thunk = (glIsTexture_t)gl_func_table[e_glIsTexture];
    assert(thunk);
    return thunk(texture);
}

ATTRIB
void APIENTRY glLightModelf(GLenum pname, GLfloat param) {
    typedef void (WINAPI * glLightModelf_t)(GLenum, GLfloat);
    glLightModelf_t thunk = (glLightModelf_t)gl_func_table[e_glLightModelf];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glLightModelfv(GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glLightModelfv_t)(GLenum, const GLfloat *);
    glLightModelfv_t thunk = (glLightModelfv_t)gl_func_table[e_glLightModelfv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glLightModeli(GLenum pname, GLint param) {
    typedef void (WINAPI * glLightModeli_t)(GLenum, GLint);
    glLightModeli_t thunk = (glLightModeli_t)gl_func_table[e_glLightModeli];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glLightModeliv(GLenum pname, const GLint * params) {
    typedef void (WINAPI * glLightModeliv_t)(GLenum, const GLint *);
    glLightModeliv_t thunk = (glLightModeliv_t)gl_func_table[e_glLightModeliv];
    assert(thunk);
    thunk(pname, params);
}

ATTRIB
void APIENTRY glLightf(GLenum light, GLenum pname, GLfloat param) {
    typedef void (WINAPI * glLightf_t)(GLenum, GLenum, GLfloat);
    glLightf_t thunk = (glLightf_t)gl_func_table[e_glLightf];
    assert(thunk);
    thunk(light, pname, param);
}

ATTRIB
void APIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glLightfv_t)(GLenum, GLenum, const GLfloat *);
    glLightfv_t thunk = (glLightfv_t)gl_func_table[e_glLightfv];
    assert(thunk);
    thunk(light, pname, params);
}

ATTRIB
void APIENTRY glLighti(GLenum light, GLenum pname, GLint param) {
    typedef void (WINAPI * glLighti_t)(GLenum, GLenum, GLint);
    glLighti_t thunk = (glLighti_t)gl_func_table[e_glLighti];
    assert(thunk);
    thunk(light, pname, param);
}

ATTRIB
void APIENTRY glLightiv(GLenum light, GLenum pname, const GLint * params) {
    typedef void (WINAPI * glLightiv_t)(GLenum, GLenum, const GLint *);
    glLightiv_t thunk = (glLightiv_t)gl_func_table[e_glLightiv];
    assert(thunk);
    thunk(light, pname, params);
}

ATTRIB
void APIENTRY glLineStipple(GLint factor, GLushort pattern) {
    typedef void (WINAPI * glLineStipple_t)(GLint, GLushort);
    glLineStipple_t thunk = (glLineStipple_t)gl_func_table[e_glLineStipple];
    assert(thunk);
    thunk(factor, pattern);
}

ATTRIB
void APIENTRY glLineWidth(GLfloat width) {
    typedef void (WINAPI * glLineWidth_t)(GLfloat);
    glLineWidth_t thunk = (glLineWidth_t)gl_func_table[e_glLineWidth];
    assert(thunk);
    thunk(width);
}

ATTRIB
void APIENTRY glListBase(GLuint base) {
    typedef void (WINAPI * glListBase_t)(GLuint);
    glListBase_t thunk = (glListBase_t)gl_func_table[e_glListBase];
    assert(thunk);
    thunk(base);
}

ATTRIB
void APIENTRY glLoadIdentity(void) {
    typedef void (WINAPI * glLoadIdentity_t)();
    glLoadIdentity_t thunk = (glLoadIdentity_t)gl_func_table[e_glLoadIdentity];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glLoadMatrixd(const GLdouble * m) {
    typedef void (WINAPI * glLoadMatrixd_t)(const GLdouble *);
    glLoadMatrixd_t thunk = (glLoadMatrixd_t)gl_func_table[e_glLoadMatrixd];
    assert(thunk);
    thunk(m);
}

ATTRIB
void APIENTRY glLoadMatrixf(const GLfloat * m) {
    typedef void (WINAPI * glLoadMatrixf_t)(const GLfloat *);
    glLoadMatrixf_t thunk = (glLoadMatrixf_t)gl_func_table[e_glLoadMatrixf];
    assert(thunk);
    thunk(m);
}

ATTRIB
void APIENTRY glLoadName(GLuint name) {
    typedef void (WINAPI * glLoadName_t)(GLuint);
    glLoadName_t thunk = (glLoadName_t)gl_func_table[e_glLoadName];
    assert(thunk);
    thunk(name);
}

ATTRIB
void APIENTRY glLogicOp(GLenum opcode) {
    typedef void (WINAPI * glLogicOp_t)(GLenum);
    glLogicOp_t thunk = (glLogicOp_t)gl_func_table[e_glLogicOp];
    assert(thunk);
    thunk(opcode);
}

ATTRIB
void APIENTRY glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points) {
    typedef void (WINAPI * glMap1d_t)(GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
    glMap1d_t thunk = (glMap1d_t)gl_func_table[e_glMap1d];
    assert(thunk);
    thunk(target, u1, u2, stride, order, points);
}

ATTRIB
void APIENTRY glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points) {
    typedef void (WINAPI * glMap1f_t)(GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
    glMap1f_t thunk = (glMap1f_t)gl_func_table[e_glMap1f];
    assert(thunk);
    thunk(target, u1, u2, stride, order, points);
}

ATTRIB
void APIENTRY glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points) {
    typedef void (WINAPI * glMap2d_t)(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
    glMap2d_t thunk = (glMap2d_t)gl_func_table[e_glMap2d];
    assert(thunk);
    thunk(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

ATTRIB
void APIENTRY glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points) {
    typedef void (WINAPI * glMap2f_t)(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
    glMap2f_t thunk = (glMap2f_t)gl_func_table[e_glMap2f];
    assert(thunk);
    thunk(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

ATTRIB
void APIENTRY glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
    typedef void (WINAPI * glMapGrid1d_t)(GLint, GLdouble, GLdouble);
    glMapGrid1d_t thunk = (glMapGrid1d_t)gl_func_table[e_glMapGrid1d];
    assert(thunk);
    thunk(un, u1, u2);
}

ATTRIB
void APIENTRY glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
    typedef void (WINAPI * glMapGrid1f_t)(GLint, GLfloat, GLfloat);
    glMapGrid1f_t thunk = (glMapGrid1f_t)gl_func_table[e_glMapGrid1f];
    assert(thunk);
    thunk(un, u1, u2);
}

ATTRIB
void APIENTRY glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) {
    typedef void (WINAPI * glMapGrid2d_t)(GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
    glMapGrid2d_t thunk = (glMapGrid2d_t)gl_func_table[e_glMapGrid2d];
    assert(thunk);
    thunk(un, u1, u2, vn, v1, v2);
}

ATTRIB
void APIENTRY glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
    typedef void (WINAPI * glMapGrid2f_t)(GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
    glMapGrid2f_t thunk = (glMapGrid2f_t)gl_func_table[e_glMapGrid2f];
    assert(thunk);
    thunk(un, u1, u2, vn, v1, v2);
}

ATTRIB
void APIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param) {
    typedef void (WINAPI * glMaterialf_t)(GLenum, GLenum, GLfloat);
    glMaterialf_t thunk = (glMaterialf_t)gl_func_table[e_glMaterialf];
    assert(thunk);
    thunk(face, pname, param);
}

ATTRIB
void APIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glMaterialfv_t)(GLenum, GLenum, const GLfloat *);
    glMaterialfv_t thunk = (glMaterialfv_t)gl_func_table[e_glMaterialfv];
    assert(thunk);
    thunk(face, pname, params);
}

ATTRIB
void APIENTRY glMateriali(GLenum face, GLenum pname, GLint param) {
    typedef void (WINAPI * glMateriali_t)(GLenum, GLenum, GLint);
    glMateriali_t thunk = (glMateriali_t)gl_func_table[e_glMateriali];
    assert(thunk);
    thunk(face, pname, param);
}

ATTRIB
void APIENTRY glMaterialiv(GLenum face, GLenum pname, const GLint * params) {
    typedef void (WINAPI * glMaterialiv_t)(GLenum, GLenum, const GLint *);
    glMaterialiv_t thunk = (glMaterialiv_t)gl_func_table[e_glMaterialiv];
    assert(thunk);
    thunk(face, pname, params);
}

ATTRIB
void APIENTRY glMatrixMode(GLenum mode) {
    typedef void (WINAPI * glMatrixMode_t)(GLenum);
    glMatrixMode_t thunk = (glMatrixMode_t)gl_func_table[e_glMatrixMode];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glMultMatrixd(const GLdouble * m) {
    typedef void (WINAPI * glMultMatrixd_t)(const GLdouble *);
    glMultMatrixd_t thunk = (glMultMatrixd_t)gl_func_table[e_glMultMatrixd];
    assert(thunk);
    thunk(m);
}

ATTRIB
void APIENTRY glMultMatrixf(const GLfloat * m) {
    typedef void (WINAPI * glMultMatrixf_t)(const GLfloat *);
    glMultMatrixf_t thunk = (glMultMatrixf_t)gl_func_table[e_glMultMatrixf];
    assert(thunk);
    thunk(m);
}

ATTRIB
void APIENTRY glNewList(GLuint list, GLenum mode) {
    typedef void (WINAPI * glNewList_t)(GLuint, GLenum);
    glNewList_t thunk = (glNewList_t)gl_func_table[e_glNewList];
    assert(thunk);
    thunk(list, mode);
}

ATTRIB
void APIENTRY glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
    typedef void (WINAPI * glNormal3b_t)(GLbyte, GLbyte, GLbyte);
    glNormal3b_t thunk = (glNormal3b_t)gl_func_table[e_glNormal3b];
    assert(thunk);
    thunk(nx, ny, nz);
}

ATTRIB
void APIENTRY glNormal3bv(const GLbyte * v) {
    typedef void (WINAPI * glNormal3bv_t)(const GLbyte *);
    glNormal3bv_t thunk = (glNormal3bv_t)gl_func_table[e_glNormal3bv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
    typedef void (WINAPI * glNormal3d_t)(GLdouble, GLdouble, GLdouble);
    glNormal3d_t thunk = (glNormal3d_t)gl_func_table[e_glNormal3d];
    assert(thunk);
    thunk(nx, ny, nz);
}

ATTRIB
void APIENTRY glNormal3dv(const GLdouble * v) {
    typedef void (WINAPI * glNormal3dv_t)(const GLdouble *);
    glNormal3dv_t thunk = (glNormal3dv_t)gl_func_table[e_glNormal3dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
    typedef void (WINAPI * glNormal3f_t)(GLfloat, GLfloat, GLfloat);
    glNormal3f_t thunk = (glNormal3f_t)gl_func_table[e_glNormal3f];
    assert(thunk);
    thunk(nx, ny, nz);
}

ATTRIB
void APIENTRY glNormal3fv(const GLfloat * v) {
    typedef void (WINAPI * glNormal3fv_t)(const GLfloat *);
    glNormal3fv_t thunk = (glNormal3fv_t)gl_func_table[e_glNormal3fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glNormal3i(GLint nx, GLint ny, GLint nz) {
    typedef void (WINAPI * glNormal3i_t)(GLint, GLint, GLint);
    glNormal3i_t thunk = (glNormal3i_t)gl_func_table[e_glNormal3i];
    assert(thunk);
    thunk(nx, ny, nz);
}

ATTRIB
void APIENTRY glNormal3iv(const GLint * v) {
    typedef void (WINAPI * glNormal3iv_t)(const GLint *);
    glNormal3iv_t thunk = (glNormal3iv_t)gl_func_table[e_glNormal3iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
    typedef void (WINAPI * glNormal3s_t)(GLshort, GLshort, GLshort);
    glNormal3s_t thunk = (glNormal3s_t)gl_func_table[e_glNormal3s];
    assert(thunk);
    thunk(nx, ny, nz);
}

ATTRIB
void APIENTRY glNormal3sv(const GLshort * v) {
    typedef void (WINAPI * glNormal3sv_t)(const GLshort *);
    glNormal3sv_t thunk = (glNormal3sv_t)gl_func_table[e_glNormal3sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glNormalPointer(GLenum type, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glNormalPointer_t)(GLenum, GLsizei, const GLvoid *);
    glNormalPointer_t thunk = (glNormalPointer_t)gl_func_table[e_glNormalPointer];
    assert(thunk);
    thunk(type, stride, pointer);
}

ATTRIB
void APIENTRY glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    typedef void (WINAPI * glOrtho_t)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
    glOrtho_t thunk = (glOrtho_t)gl_func_table[e_glOrtho];
    assert(thunk);
    thunk(left, right, bottom, top, zNear, zFar);
}

ATTRIB
void APIENTRY glPassThrough(GLfloat token) {
    typedef void (WINAPI * glPassThrough_t)(GLfloat);
    glPassThrough_t thunk = (glPassThrough_t)gl_func_table[e_glPassThrough];
    assert(thunk);
    thunk(token);
}

ATTRIB
void APIENTRY glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values) {
    typedef void (WINAPI * glPixelMapfv_t)(GLenum, GLsizei, const GLfloat *);
    glPixelMapfv_t thunk = (glPixelMapfv_t)gl_func_table[e_glPixelMapfv];
    assert(thunk);
    thunk(map, mapsize, values);
}

ATTRIB
void APIENTRY glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values) {
    typedef void (WINAPI * glPixelMapuiv_t)(GLenum, GLsizei, const GLuint *);
    glPixelMapuiv_t thunk = (glPixelMapuiv_t)gl_func_table[e_glPixelMapuiv];
    assert(thunk);
    thunk(map, mapsize, values);
}

ATTRIB
void APIENTRY glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values) {
    typedef void (WINAPI * glPixelMapusv_t)(GLenum, GLsizei, const GLushort *);
    glPixelMapusv_t thunk = (glPixelMapusv_t)gl_func_table[e_glPixelMapusv];
    assert(thunk);
    thunk(map, mapsize, values);
}

ATTRIB
void APIENTRY glPixelStoref(GLenum pname, GLfloat param) {
    typedef void (WINAPI * glPixelStoref_t)(GLenum, GLfloat);
    glPixelStoref_t thunk = (glPixelStoref_t)gl_func_table[e_glPixelStoref];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glPixelStorei(GLenum pname, GLint param) {
    typedef void (WINAPI * glPixelStorei_t)(GLenum, GLint);
    glPixelStorei_t thunk = (glPixelStorei_t)gl_func_table[e_glPixelStorei];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glPixelTransferf(GLenum pname, GLfloat param) {
    typedef void (WINAPI * glPixelTransferf_t)(GLenum, GLfloat);
    glPixelTransferf_t thunk = (glPixelTransferf_t)gl_func_table[e_glPixelTransferf];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glPixelTransferi(GLenum pname, GLint param) {
    typedef void (WINAPI * glPixelTransferi_t)(GLenum, GLint);
    glPixelTransferi_t thunk = (glPixelTransferi_t)gl_func_table[e_glPixelTransferi];
    assert(thunk);
    thunk(pname, param);
}

ATTRIB
void APIENTRY glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
    typedef void (WINAPI * glPixelZoom_t)(GLfloat, GLfloat);
    glPixelZoom_t thunk = (glPixelZoom_t)gl_func_table[e_glPixelZoom];
    assert(thunk);
    thunk(xfactor, yfactor);
}

ATTRIB
void APIENTRY glPointSize(GLfloat size) {
    typedef void (WINAPI * glPointSize_t)(GLfloat);
    glPointSize_t thunk = (glPointSize_t)gl_func_table[e_glPointSize];
    assert(thunk);
    thunk(size);
}

ATTRIB
void APIENTRY glPolygonMode(GLenum face, GLenum mode) {
    typedef void (WINAPI * glPolygonMode_t)(GLenum, GLenum);
    glPolygonMode_t thunk = (glPolygonMode_t)gl_func_table[e_glPolygonMode];
    assert(thunk);
    thunk(face, mode);
}

ATTRIB
void APIENTRY glPolygonOffset(GLfloat factor, GLfloat units) {
    typedef void (WINAPI * glPolygonOffset_t)(GLfloat, GLfloat);
    glPolygonOffset_t thunk = (glPolygonOffset_t)gl_func_table[e_glPolygonOffset];
    assert(thunk);
    thunk(factor, units);
}

ATTRIB
void APIENTRY glPolygonStipple(const GLubyte * mask) {
    typedef void (WINAPI * glPolygonStipple_t)(const GLubyte *);
    glPolygonStipple_t thunk = (glPolygonStipple_t)gl_func_table[e_glPolygonStipple];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glPopAttrib(void) {
    typedef void (WINAPI * glPopAttrib_t)();
    glPopAttrib_t thunk = (glPopAttrib_t)gl_func_table[e_glPopAttrib];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glPopClientAttrib(void) {
    typedef void (WINAPI * glPopClientAttrib_t)();
    glPopClientAttrib_t thunk = (glPopClientAttrib_t)gl_func_table[e_glPopClientAttrib];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glPopMatrix(void) {
    typedef void (WINAPI * glPopMatrix_t)();
    glPopMatrix_t thunk = (glPopMatrix_t)gl_func_table[e_glPopMatrix];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glPopName(void) {
    typedef void (WINAPI * glPopName_t)();
    glPopName_t thunk = (glPopName_t)gl_func_table[e_glPopName];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glPrioritizeTextures(GLsizei n, const GLuint * textures, const GLclampf * priorities) {
    typedef void (WINAPI * glPrioritizeTextures_t)(GLsizei, const GLuint *, const GLclampf *);
    glPrioritizeTextures_t thunk = (glPrioritizeTextures_t)gl_func_table[e_glPrioritizeTextures];
    assert(thunk);
    thunk(n, textures, priorities);
}

ATTRIB
void APIENTRY glPushAttrib(GLbitfield mask) {
    typedef void (WINAPI * glPushAttrib_t)(GLbitfield);
    glPushAttrib_t thunk = (glPushAttrib_t)gl_func_table[e_glPushAttrib];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glPushClientAttrib(GLbitfield mask) {
    typedef void (WINAPI * glPushClientAttrib_t)(GLbitfield);
    glPushClientAttrib_t thunk = (glPushClientAttrib_t)gl_func_table[e_glPushClientAttrib];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glPushMatrix(void) {
    typedef void (WINAPI * glPushMatrix_t)();
    glPushMatrix_t thunk = (glPushMatrix_t)gl_func_table[e_glPushMatrix];
    assert(thunk);
    thunk();
}

ATTRIB
void APIENTRY glPushName(GLuint name) {
    typedef void (WINAPI * glPushName_t)(GLuint);
    glPushName_t thunk = (glPushName_t)gl_func_table[e_glPushName];
    assert(thunk);
    thunk(name);
}

ATTRIB
void APIENTRY glRasterPos2d(GLdouble x, GLdouble y) {
    typedef void (WINAPI * glRasterPos2d_t)(GLdouble, GLdouble);
    glRasterPos2d_t thunk = (glRasterPos2d_t)gl_func_table[e_glRasterPos2d];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glRasterPos2dv(const GLdouble * v) {
    typedef void (WINAPI * glRasterPos2dv_t)(const GLdouble *);
    glRasterPos2dv_t thunk = (glRasterPos2dv_t)gl_func_table[e_glRasterPos2dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos2f(GLfloat x, GLfloat y) {
    typedef void (WINAPI * glRasterPos2f_t)(GLfloat, GLfloat);
    glRasterPos2f_t thunk = (glRasterPos2f_t)gl_func_table[e_glRasterPos2f];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glRasterPos2fv(const GLfloat * v) {
    typedef void (WINAPI * glRasterPos2fv_t)(const GLfloat *);
    glRasterPos2fv_t thunk = (glRasterPos2fv_t)gl_func_table[e_glRasterPos2fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos2i(GLint x, GLint y) {
    typedef void (WINAPI * glRasterPos2i_t)(GLint, GLint);
    glRasterPos2i_t thunk = (glRasterPos2i_t)gl_func_table[e_glRasterPos2i];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glRasterPos2iv(const GLint * v) {
    typedef void (WINAPI * glRasterPos2iv_t)(const GLint *);
    glRasterPos2iv_t thunk = (glRasterPos2iv_t)gl_func_table[e_glRasterPos2iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos2s(GLshort x, GLshort y) {
    typedef void (WINAPI * glRasterPos2s_t)(GLshort, GLshort);
    glRasterPos2s_t thunk = (glRasterPos2s_t)gl_func_table[e_glRasterPos2s];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glRasterPos2sv(const GLshort * v) {
    typedef void (WINAPI * glRasterPos2sv_t)(const GLshort *);
    glRasterPos2sv_t thunk = (glRasterPos2sv_t)gl_func_table[e_glRasterPos2sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
    typedef void (WINAPI * glRasterPos3d_t)(GLdouble, GLdouble, GLdouble);
    glRasterPos3d_t thunk = (glRasterPos3d_t)gl_func_table[e_glRasterPos3d];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glRasterPos3dv(const GLdouble * v) {
    typedef void (WINAPI * glRasterPos3dv_t)(const GLdouble *);
    glRasterPos3dv_t thunk = (glRasterPos3dv_t)gl_func_table[e_glRasterPos3dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
    typedef void (WINAPI * glRasterPos3f_t)(GLfloat, GLfloat, GLfloat);
    glRasterPos3f_t thunk = (glRasterPos3f_t)gl_func_table[e_glRasterPos3f];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glRasterPos3fv(const GLfloat * v) {
    typedef void (WINAPI * glRasterPos3fv_t)(const GLfloat *);
    glRasterPos3fv_t thunk = (glRasterPos3fv_t)gl_func_table[e_glRasterPos3fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos3i(GLint x, GLint y, GLint z) {
    typedef void (WINAPI * glRasterPos3i_t)(GLint, GLint, GLint);
    glRasterPos3i_t thunk = (glRasterPos3i_t)gl_func_table[e_glRasterPos3i];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glRasterPos3iv(const GLint * v) {
    typedef void (WINAPI * glRasterPos3iv_t)(const GLint *);
    glRasterPos3iv_t thunk = (glRasterPos3iv_t)gl_func_table[e_glRasterPos3iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos3s(GLshort x, GLshort y, GLshort z) {
    typedef void (WINAPI * glRasterPos3s_t)(GLshort, GLshort, GLshort);
    glRasterPos3s_t thunk = (glRasterPos3s_t)gl_func_table[e_glRasterPos3s];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glRasterPos3sv(const GLshort * v) {
    typedef void (WINAPI * glRasterPos3sv_t)(const GLshort *);
    glRasterPos3sv_t thunk = (glRasterPos3sv_t)gl_func_table[e_glRasterPos3sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    typedef void (WINAPI * glRasterPos4d_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glRasterPos4d_t thunk = (glRasterPos4d_t)gl_func_table[e_glRasterPos4d];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glRasterPos4dv(const GLdouble * v) {
    typedef void (WINAPI * glRasterPos4dv_t)(const GLdouble *);
    glRasterPos4dv_t thunk = (glRasterPos4dv_t)gl_func_table[e_glRasterPos4dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    typedef void (WINAPI * glRasterPos4f_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glRasterPos4f_t thunk = (glRasterPos4f_t)gl_func_table[e_glRasterPos4f];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glRasterPos4fv(const GLfloat * v) {
    typedef void (WINAPI * glRasterPos4fv_t)(const GLfloat *);
    glRasterPos4fv_t thunk = (glRasterPos4fv_t)gl_func_table[e_glRasterPos4fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
    typedef void (WINAPI * glRasterPos4i_t)(GLint, GLint, GLint, GLint);
    glRasterPos4i_t thunk = (glRasterPos4i_t)gl_func_table[e_glRasterPos4i];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glRasterPos4iv(const GLint * v) {
    typedef void (WINAPI * glRasterPos4iv_t)(const GLint *);
    glRasterPos4iv_t thunk = (glRasterPos4iv_t)gl_func_table[e_glRasterPos4iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    typedef void (WINAPI * glRasterPos4s_t)(GLshort, GLshort, GLshort, GLshort);
    glRasterPos4s_t thunk = (glRasterPos4s_t)gl_func_table[e_glRasterPos4s];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glRasterPos4sv(const GLshort * v) {
    typedef void (WINAPI * glRasterPos4sv_t)(const GLshort *);
    glRasterPos4sv_t thunk = (glRasterPos4sv_t)gl_func_table[e_glRasterPos4sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glReadBuffer(GLenum mode) {
    typedef void (WINAPI * glReadBuffer_t)(GLenum);
    glReadBuffer_t thunk = (glReadBuffer_t)gl_func_table[e_glReadBuffer];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels) {
    typedef void (WINAPI * glReadPixels_t)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid *);
    glReadPixels_t thunk = (glReadPixels_t)gl_func_table[e_glReadPixels];
    assert(thunk);
    thunk(x, y, width, height, format, type, pixels);
}

ATTRIB
void APIENTRY glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    typedef void (WINAPI * glRectd_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glRectd_t thunk = (glRectd_t)gl_func_table[e_glRectd];
    assert(thunk);
    thunk(x1, y1, x2, y2);
}

ATTRIB
void APIENTRY glRectdv(const GLdouble * v1, const GLdouble * v2) {
    typedef void (WINAPI * glRectdv_t)(const GLdouble *, const GLdouble *);
    glRectdv_t thunk = (glRectdv_t)gl_func_table[e_glRectdv];
    assert(thunk);
    thunk(v1, v2);
}

ATTRIB
void APIENTRY glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    typedef void (WINAPI * glRectf_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glRectf_t thunk = (glRectf_t)gl_func_table[e_glRectf];
    assert(thunk);
    thunk(x1, y1, x2, y2);
}

ATTRIB
void APIENTRY glRectfv(const GLfloat * v1, const GLfloat * v2) {
    typedef void (WINAPI * glRectfv_t)(const GLfloat *, const GLfloat *);
    glRectfv_t thunk = (glRectfv_t)gl_func_table[e_glRectfv];
    assert(thunk);
    thunk(v1, v2);
}

ATTRIB
void APIENTRY glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
    typedef void (WINAPI * glRecti_t)(GLint, GLint, GLint, GLint);
    glRecti_t thunk = (glRecti_t)gl_func_table[e_glRecti];
    assert(thunk);
    thunk(x1, y1, x2, y2);
}

ATTRIB
void APIENTRY glRectiv(const GLint * v1, const GLint * v2) {
    typedef void (WINAPI * glRectiv_t)(const GLint *, const GLint *);
    glRectiv_t thunk = (glRectiv_t)gl_func_table[e_glRectiv];
    assert(thunk);
    thunk(v1, v2);
}

ATTRIB
void APIENTRY glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
    typedef void (WINAPI * glRects_t)(GLshort, GLshort, GLshort, GLshort);
    glRects_t thunk = (glRects_t)gl_func_table[e_glRects];
    assert(thunk);
    thunk(x1, y1, x2, y2);
}

ATTRIB
void APIENTRY glRectsv(const GLshort * v1, const GLshort * v2) {
    typedef void (WINAPI * glRectsv_t)(const GLshort *, const GLshort *);
    glRectsv_t thunk = (glRectsv_t)gl_func_table[e_glRectsv];
    assert(thunk);
    thunk(v1, v2);
}

ATTRIB
GLint APIENTRY glRenderMode(GLenum mode) {
    typedef GLint (WINAPI * glRenderMode_t)(GLenum);
    glRenderMode_t thunk = (glRenderMode_t)gl_func_table[e_glRenderMode];
    assert(thunk);
    return thunk(mode);
}

ATTRIB
void APIENTRY glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
    typedef void (WINAPI * glRotated_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glRotated_t thunk = (glRotated_t)gl_func_table[e_glRotated];
    assert(thunk);
    thunk(angle, x, y, z);
}

ATTRIB
void APIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    typedef void (WINAPI * glRotatef_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glRotatef_t thunk = (glRotatef_t)gl_func_table[e_glRotatef];
    assert(thunk);
    thunk(angle, x, y, z);
}

ATTRIB
void APIENTRY glScaled(GLdouble x, GLdouble y, GLdouble z) {
    typedef void (WINAPI * glScaled_t)(GLdouble, GLdouble, GLdouble);
    glScaled_t thunk = (glScaled_t)gl_func_table[e_glScaled];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z) {
    typedef void (WINAPI * glScalef_t)(GLfloat, GLfloat, GLfloat);
    glScalef_t thunk = (glScalef_t)gl_func_table[e_glScalef];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    typedef void (WINAPI * glScissor_t)(GLint, GLint, GLsizei, GLsizei);
    glScissor_t thunk = (glScissor_t)gl_func_table[e_glScissor];
    assert(thunk);
    thunk(x, y, width, height);
}

ATTRIB
void APIENTRY glSelectBuffer(GLsizei size, GLuint * buffer) {
    typedef void (WINAPI * glSelectBuffer_t)(GLsizei, GLuint *);
    glSelectBuffer_t thunk = (glSelectBuffer_t)gl_func_table[e_glSelectBuffer];
    assert(thunk);
    thunk(size, buffer);
}

ATTRIB
void APIENTRY glShadeModel(GLenum mode) {
    typedef void (WINAPI * glShadeModel_t)(GLenum);
    glShadeModel_t thunk = (glShadeModel_t)gl_func_table[e_glShadeModel];
    assert(thunk);
    thunk(mode);
}

ATTRIB
void APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    typedef void (WINAPI * glStencilFunc_t)(GLenum, GLint, GLuint);
    glStencilFunc_t thunk = (glStencilFunc_t)gl_func_table[e_glStencilFunc];
    assert(thunk);
    thunk(func, ref, mask);
}

ATTRIB
void APIENTRY glStencilMask(GLuint mask) {
    typedef void (WINAPI * glStencilMask_t)(GLuint);
    glStencilMask_t thunk = (glStencilMask_t)gl_func_table[e_glStencilMask];
    assert(thunk);
    thunk(mask);
}

ATTRIB
void APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    typedef void (WINAPI * glStencilOp_t)(GLenum, GLenum, GLenum);
    glStencilOp_t thunk = (glStencilOp_t)gl_func_table[e_glStencilOp];
    assert(thunk);
    thunk(fail, zfail, zpass);
}

ATTRIB
void APIENTRY glTexCoord1d(GLdouble s) {
    typedef void (WINAPI * glTexCoord1d_t)(GLdouble);
    glTexCoord1d_t thunk = (glTexCoord1d_t)gl_func_table[e_glTexCoord1d];
    assert(thunk);
    thunk(s);
}

ATTRIB
void APIENTRY glTexCoord1dv(const GLdouble * v) {
    typedef void (WINAPI * glTexCoord1dv_t)(const GLdouble *);
    glTexCoord1dv_t thunk = (glTexCoord1dv_t)gl_func_table[e_glTexCoord1dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord1f(GLfloat s) {
    typedef void (WINAPI * glTexCoord1f_t)(GLfloat);
    glTexCoord1f_t thunk = (glTexCoord1f_t)gl_func_table[e_glTexCoord1f];
    assert(thunk);
    thunk(s);
}

ATTRIB
void APIENTRY glTexCoord1fv(const GLfloat * v) {
    typedef void (WINAPI * glTexCoord1fv_t)(const GLfloat *);
    glTexCoord1fv_t thunk = (glTexCoord1fv_t)gl_func_table[e_glTexCoord1fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord1i(GLint s) {
    typedef void (WINAPI * glTexCoord1i_t)(GLint);
    glTexCoord1i_t thunk = (glTexCoord1i_t)gl_func_table[e_glTexCoord1i];
    assert(thunk);
    thunk(s);
}

ATTRIB
void APIENTRY glTexCoord1iv(const GLint * v) {
    typedef void (WINAPI * glTexCoord1iv_t)(const GLint *);
    glTexCoord1iv_t thunk = (glTexCoord1iv_t)gl_func_table[e_glTexCoord1iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord1s(GLshort s) {
    typedef void (WINAPI * glTexCoord1s_t)(GLshort);
    glTexCoord1s_t thunk = (glTexCoord1s_t)gl_func_table[e_glTexCoord1s];
    assert(thunk);
    thunk(s);
}

ATTRIB
void APIENTRY glTexCoord1sv(const GLshort * v) {
    typedef void (WINAPI * glTexCoord1sv_t)(const GLshort *);
    glTexCoord1sv_t thunk = (glTexCoord1sv_t)gl_func_table[e_glTexCoord1sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord2d(GLdouble s, GLdouble t) {
    typedef void (WINAPI * glTexCoord2d_t)(GLdouble, GLdouble);
    glTexCoord2d_t thunk = (glTexCoord2d_t)gl_func_table[e_glTexCoord2d];
    assert(thunk);
    thunk(s, t);
}

ATTRIB
void APIENTRY glTexCoord2dv(const GLdouble * v) {
    typedef void (WINAPI * glTexCoord2dv_t)(const GLdouble *);
    glTexCoord2dv_t thunk = (glTexCoord2dv_t)gl_func_table[e_glTexCoord2dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord2f(GLfloat s, GLfloat t) {
    typedef void (WINAPI * glTexCoord2f_t)(GLfloat, GLfloat);
    glTexCoord2f_t thunk = (glTexCoord2f_t)gl_func_table[e_glTexCoord2f];
    assert(thunk);
    thunk(s, t);
}

ATTRIB
void APIENTRY glTexCoord2fv(const GLfloat * v) {
    typedef void (WINAPI * glTexCoord2fv_t)(const GLfloat *);
    glTexCoord2fv_t thunk = (glTexCoord2fv_t)gl_func_table[e_glTexCoord2fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord2i(GLint s, GLint t) {
    typedef void (WINAPI * glTexCoord2i_t)(GLint, GLint);
    glTexCoord2i_t thunk = (glTexCoord2i_t)gl_func_table[e_glTexCoord2i];
    assert(thunk);
    thunk(s, t);
}

ATTRIB
void APIENTRY glTexCoord2iv(const GLint * v) {
    typedef void (WINAPI * glTexCoord2iv_t)(const GLint *);
    glTexCoord2iv_t thunk = (glTexCoord2iv_t)gl_func_table[e_glTexCoord2iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord2s(GLshort s, GLshort t) {
    typedef void (WINAPI * glTexCoord2s_t)(GLshort, GLshort);
    glTexCoord2s_t thunk = (glTexCoord2s_t)gl_func_table[e_glTexCoord2s];
    assert(thunk);
    thunk(s, t);
}

ATTRIB
void APIENTRY glTexCoord2sv(const GLshort * v) {
    typedef void (WINAPI * glTexCoord2sv_t)(const GLshort *);
    glTexCoord2sv_t thunk = (glTexCoord2sv_t)gl_func_table[e_glTexCoord2sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
    typedef void (WINAPI * glTexCoord3d_t)(GLdouble, GLdouble, GLdouble);
    glTexCoord3d_t thunk = (glTexCoord3d_t)gl_func_table[e_glTexCoord3d];
    assert(thunk);
    thunk(s, t, r);
}

ATTRIB
void APIENTRY glTexCoord3dv(const GLdouble * v) {
    typedef void (WINAPI * glTexCoord3dv_t)(const GLdouble *);
    glTexCoord3dv_t thunk = (glTexCoord3dv_t)gl_func_table[e_glTexCoord3dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
    typedef void (WINAPI * glTexCoord3f_t)(GLfloat, GLfloat, GLfloat);
    glTexCoord3f_t thunk = (glTexCoord3f_t)gl_func_table[e_glTexCoord3f];
    assert(thunk);
    thunk(s, t, r);
}

ATTRIB
void APIENTRY glTexCoord3fv(const GLfloat * v) {
    typedef void (WINAPI * glTexCoord3fv_t)(const GLfloat *);
    glTexCoord3fv_t thunk = (glTexCoord3fv_t)gl_func_table[e_glTexCoord3fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord3i(GLint s, GLint t, GLint r) {
    typedef void (WINAPI * glTexCoord3i_t)(GLint, GLint, GLint);
    glTexCoord3i_t thunk = (glTexCoord3i_t)gl_func_table[e_glTexCoord3i];
    assert(thunk);
    thunk(s, t, r);
}

ATTRIB
void APIENTRY glTexCoord3iv(const GLint * v) {
    typedef void (WINAPI * glTexCoord3iv_t)(const GLint *);
    glTexCoord3iv_t thunk = (glTexCoord3iv_t)gl_func_table[e_glTexCoord3iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord3s(GLshort s, GLshort t, GLshort r) {
    typedef void (WINAPI * glTexCoord3s_t)(GLshort, GLshort, GLshort);
    glTexCoord3s_t thunk = (glTexCoord3s_t)gl_func_table[e_glTexCoord3s];
    assert(thunk);
    thunk(s, t, r);
}

ATTRIB
void APIENTRY glTexCoord3sv(const GLshort * v) {
    typedef void (WINAPI * glTexCoord3sv_t)(const GLshort *);
    glTexCoord3sv_t thunk = (glTexCoord3sv_t)gl_func_table[e_glTexCoord3sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    typedef void (WINAPI * glTexCoord4d_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glTexCoord4d_t thunk = (glTexCoord4d_t)gl_func_table[e_glTexCoord4d];
    assert(thunk);
    thunk(s, t, r, q);
}

ATTRIB
void APIENTRY glTexCoord4dv(const GLdouble * v) {
    typedef void (WINAPI * glTexCoord4dv_t)(const GLdouble *);
    glTexCoord4dv_t thunk = (glTexCoord4dv_t)gl_func_table[e_glTexCoord4dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    typedef void (WINAPI * glTexCoord4f_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glTexCoord4f_t thunk = (glTexCoord4f_t)gl_func_table[e_glTexCoord4f];
    assert(thunk);
    thunk(s, t, r, q);
}

ATTRIB
void APIENTRY glTexCoord4fv(const GLfloat * v) {
    typedef void (WINAPI * glTexCoord4fv_t)(const GLfloat *);
    glTexCoord4fv_t thunk = (glTexCoord4fv_t)gl_func_table[e_glTexCoord4fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
    typedef void (WINAPI * glTexCoord4i_t)(GLint, GLint, GLint, GLint);
    glTexCoord4i_t thunk = (glTexCoord4i_t)gl_func_table[e_glTexCoord4i];
    assert(thunk);
    thunk(s, t, r, q);
}

ATTRIB
void APIENTRY glTexCoord4iv(const GLint * v) {
    typedef void (WINAPI * glTexCoord4iv_t)(const GLint *);
    glTexCoord4iv_t thunk = (glTexCoord4iv_t)gl_func_table[e_glTexCoord4iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
    typedef void (WINAPI * glTexCoord4s_t)(GLshort, GLshort, GLshort, GLshort);
    glTexCoord4s_t thunk = (glTexCoord4s_t)gl_func_table[e_glTexCoord4s];
    assert(thunk);
    thunk(s, t, r, q);
}

ATTRIB
void APIENTRY glTexCoord4sv(const GLshort * v) {
    typedef void (WINAPI * glTexCoord4sv_t)(const GLshort *);
    glTexCoord4sv_t thunk = (glTexCoord4sv_t)gl_func_table[e_glTexCoord4sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glTexCoordPointer_t)(GLint, GLenum, GLsizei, const GLvoid *);
    glTexCoordPointer_t thunk = (glTexCoordPointer_t)gl_func_table[e_glTexCoordPointer];
    assert(thunk);
    thunk(size, type, stride, pointer);
}

ATTRIB
void APIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
    typedef void (WINAPI * glTexEnvf_t)(GLenum, GLenum, GLfloat);
    glTexEnvf_t thunk = (glTexEnvf_t)gl_func_table[e_glTexEnvf];
    assert(thunk);
    thunk(target, pname, param);
}

ATTRIB
void APIENTRY glTexEnvfv(GLenum target, GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glTexEnvfv_t)(GLenum, GLenum, const GLfloat *);
    glTexEnvfv_t thunk = (glTexEnvfv_t)gl_func_table[e_glTexEnvfv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param) {
    typedef void (WINAPI * glTexEnvi_t)(GLenum, GLenum, GLint);
    glTexEnvi_t thunk = (glTexEnvi_t)gl_func_table[e_glTexEnvi];
    assert(thunk);
    thunk(target, pname, param);
}

ATTRIB
void APIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint * params) {
    typedef void (WINAPI * glTexEnviv_t)(GLenum, GLenum, const GLint *);
    glTexEnviv_t thunk = (glTexEnviv_t)gl_func_table[e_glTexEnviv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glTexGend(GLenum coord, GLenum pname, GLdouble param) {
    typedef void (WINAPI * glTexGend_t)(GLenum, GLenum, GLdouble);
    glTexGend_t thunk = (glTexGend_t)gl_func_table[e_glTexGend];
    assert(thunk);
    thunk(coord, pname, param);
}

ATTRIB
void APIENTRY glTexGendv(GLenum coord, GLenum pname, const GLdouble * params) {
    typedef void (WINAPI * glTexGendv_t)(GLenum, GLenum, const GLdouble *);
    glTexGendv_t thunk = (glTexGendv_t)gl_func_table[e_glTexGendv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
    typedef void (WINAPI * glTexGenf_t)(GLenum, GLenum, GLfloat);
    glTexGenf_t thunk = (glTexGenf_t)gl_func_table[e_glTexGenf];
    assert(thunk);
    thunk(coord, pname, param);
}

ATTRIB
void APIENTRY glTexGenfv(GLenum coord, GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glTexGenfv_t)(GLenum, GLenum, const GLfloat *);
    glTexGenfv_t thunk = (glTexGenfv_t)gl_func_table[e_glTexGenfv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glTexGeni(GLenum coord, GLenum pname, GLint param) {
    typedef void (WINAPI * glTexGeni_t)(GLenum, GLenum, GLint);
    glTexGeni_t thunk = (glTexGeni_t)gl_func_table[e_glTexGeni];
    assert(thunk);
    thunk(coord, pname, param);
}

ATTRIB
void APIENTRY glTexGeniv(GLenum coord, GLenum pname, const GLint * params) {
    typedef void (WINAPI * glTexGeniv_t)(GLenum, GLenum, const GLint *);
    glTexGeniv_t thunk = (glTexGeniv_t)gl_func_table[e_glTexGeniv];
    assert(thunk);
    thunk(coord, pname, params);
}

ATTRIB
void APIENTRY glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels) {
    typedef void (WINAPI * glTexImage1D_t)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
    glTexImage1D_t thunk = (glTexImage1D_t)gl_func_table[e_glTexImage1D];
    assert(thunk);
    thunk(target, level, internalformat, width, border, format, type, pixels);
}

ATTRIB
void APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels) {
    typedef void (WINAPI * glTexImage2D_t)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
    glTexImage2D_t thunk = (glTexImage2D_t)gl_func_table[e_glTexImage2D];
    assert(thunk);
    thunk(target, level, internalformat, width, height, border, format, type, pixels);
}

ATTRIB
void APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    typedef void (WINAPI * glTexParameterf_t)(GLenum, GLenum, GLfloat);
    glTexParameterf_t thunk = (glTexParameterf_t)gl_func_table[e_glTexParameterf];
    assert(thunk);
    thunk(target, pname, param);
}

ATTRIB
void APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    typedef void (WINAPI * glTexParameterfv_t)(GLenum, GLenum, const GLfloat *);
    glTexParameterfv_t thunk = (glTexParameterfv_t)gl_func_table[e_glTexParameterfv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param) {
    typedef void (WINAPI * glTexParameteri_t)(GLenum, GLenum, GLint);
    glTexParameteri_t thunk = (glTexParameteri_t)gl_func_table[e_glTexParameteri];
    assert(thunk);
    thunk(target, pname, param);
}

ATTRIB
void APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    typedef void (WINAPI * glTexParameteriv_t)(GLenum, GLenum, const GLint *);
    glTexParameteriv_t thunk = (glTexParameteriv_t)gl_func_table[e_glTexParameteriv];
    assert(thunk);
    thunk(target, pname, params);
}

ATTRIB
void APIENTRY glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) {
    typedef void (WINAPI * glTexSubImage1D_t)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid *);
    glTexSubImage1D_t thunk = (glTexSubImage1D_t)gl_func_table[e_glTexSubImage1D];
    assert(thunk);
    thunk(target, level, xoffset, width, format, type, pixels);
}

ATTRIB
void APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) {
    typedef void (WINAPI * glTexSubImage2D_t)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *);
    glTexSubImage2D_t thunk = (glTexSubImage2D_t)gl_func_table[e_glTexSubImage2D];
    assert(thunk);
    thunk(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

ATTRIB
void APIENTRY glTranslated(GLdouble x, GLdouble y, GLdouble z) {
    typedef void (WINAPI * glTranslated_t)(GLdouble, GLdouble, GLdouble);
    glTranslated_t thunk = (glTranslated_t)gl_func_table[e_glTranslated];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    typedef void (WINAPI * glTranslatef_t)(GLfloat, GLfloat, GLfloat);
    glTranslatef_t thunk = (glTranslatef_t)gl_func_table[e_glTranslatef];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glVertex2d(GLdouble x, GLdouble y) {
    typedef void (WINAPI * glVertex2d_t)(GLdouble, GLdouble);
    glVertex2d_t thunk = (glVertex2d_t)gl_func_table[e_glVertex2d];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glVertex2dv(const GLdouble * v) {
    typedef void (WINAPI * glVertex2dv_t)(const GLdouble *);
    glVertex2dv_t thunk = (glVertex2dv_t)gl_func_table[e_glVertex2dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex2f(GLfloat x, GLfloat y) {
    typedef void (WINAPI * glVertex2f_t)(GLfloat, GLfloat);
    glVertex2f_t thunk = (glVertex2f_t)gl_func_table[e_glVertex2f];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glVertex2fv(const GLfloat * v) {
    typedef void (WINAPI * glVertex2fv_t)(const GLfloat *);
    glVertex2fv_t thunk = (glVertex2fv_t)gl_func_table[e_glVertex2fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex2i(GLint x, GLint y) {
    typedef void (WINAPI * glVertex2i_t)(GLint, GLint);
    glVertex2i_t thunk = (glVertex2i_t)gl_func_table[e_glVertex2i];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glVertex2iv(const GLint * v) {
    typedef void (WINAPI * glVertex2iv_t)(const GLint *);
    glVertex2iv_t thunk = (glVertex2iv_t)gl_func_table[e_glVertex2iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex2s(GLshort x, GLshort y) {
    typedef void (WINAPI * glVertex2s_t)(GLshort, GLshort);
    glVertex2s_t thunk = (glVertex2s_t)gl_func_table[e_glVertex2s];
    assert(thunk);
    thunk(x, y);
}

ATTRIB
void APIENTRY glVertex2sv(const GLshort * v) {
    typedef void (WINAPI * glVertex2sv_t)(const GLshort *);
    glVertex2sv_t thunk = (glVertex2sv_t)gl_func_table[e_glVertex2sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
    typedef void (WINAPI * glVertex3d_t)(GLdouble, GLdouble, GLdouble);
    glVertex3d_t thunk = (glVertex3d_t)gl_func_table[e_glVertex3d];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glVertex3dv(const GLdouble * v) {
    typedef void (WINAPI * glVertex3dv_t)(const GLdouble *);
    glVertex3dv_t thunk = (glVertex3dv_t)gl_func_table[e_glVertex3dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    typedef void (WINAPI * glVertex3f_t)(GLfloat, GLfloat, GLfloat);
    glVertex3f_t thunk = (glVertex3f_t)gl_func_table[e_glVertex3f];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glVertex3fv(const GLfloat * v) {
    typedef void (WINAPI * glVertex3fv_t)(const GLfloat *);
    glVertex3fv_t thunk = (glVertex3fv_t)gl_func_table[e_glVertex3fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex3i(GLint x, GLint y, GLint z) {
    typedef void (WINAPI * glVertex3i_t)(GLint, GLint, GLint);
    glVertex3i_t thunk = (glVertex3i_t)gl_func_table[e_glVertex3i];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glVertex3iv(const GLint * v) {
    typedef void (WINAPI * glVertex3iv_t)(const GLint *);
    glVertex3iv_t thunk = (glVertex3iv_t)gl_func_table[e_glVertex3iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex3s(GLshort x, GLshort y, GLshort z) {
    typedef void (WINAPI * glVertex3s_t)(GLshort, GLshort, GLshort);
    glVertex3s_t thunk = (glVertex3s_t)gl_func_table[e_glVertex3s];
    assert(thunk);
    thunk(x, y, z);
}

ATTRIB
void APIENTRY glVertex3sv(const GLshort * v) {
    typedef void (WINAPI * glVertex3sv_t)(const GLshort *);
    glVertex3sv_t thunk = (glVertex3sv_t)gl_func_table[e_glVertex3sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    typedef void (WINAPI * glVertex4d_t)(GLdouble, GLdouble, GLdouble, GLdouble);
    glVertex4d_t thunk = (glVertex4d_t)gl_func_table[e_glVertex4d];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glVertex4dv(const GLdouble * v) {
    typedef void (WINAPI * glVertex4dv_t)(const GLdouble *);
    glVertex4dv_t thunk = (glVertex4dv_t)gl_func_table[e_glVertex4dv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    typedef void (WINAPI * glVertex4f_t)(GLfloat, GLfloat, GLfloat, GLfloat);
    glVertex4f_t thunk = (glVertex4f_t)gl_func_table[e_glVertex4f];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glVertex4fv(const GLfloat * v) {
    typedef void (WINAPI * glVertex4fv_t)(const GLfloat *);
    glVertex4fv_t thunk = (glVertex4fv_t)gl_func_table[e_glVertex4fv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex4i(GLint x, GLint y, GLint z, GLint w) {
    typedef void (WINAPI * glVertex4i_t)(GLint, GLint, GLint, GLint);
    glVertex4i_t thunk = (glVertex4i_t)gl_func_table[e_glVertex4i];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glVertex4iv(const GLint * v) {
    typedef void (WINAPI * glVertex4iv_t)(const GLint *);
    glVertex4iv_t thunk = (glVertex4iv_t)gl_func_table[e_glVertex4iv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    typedef void (WINAPI * glVertex4s_t)(GLshort, GLshort, GLshort, GLshort);
    glVertex4s_t thunk = (glVertex4s_t)gl_func_table[e_glVertex4s];
    assert(thunk);
    thunk(x, y, z, w);
}

ATTRIB
void APIENTRY glVertex4sv(const GLshort * v) {
    typedef void (WINAPI * glVertex4sv_t)(const GLshort *);
    glVertex4sv_t thunk = (glVertex4sv_t)gl_func_table[e_glVertex4sv];
    assert(thunk);
    thunk(v);
}

ATTRIB
void APIENTRY glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {
    typedef void (WINAPI * glVertexPointer_t)(GLint, GLenum, GLsizei, const GLvoid *);
    glVertexPointer_t thunk = (glVertexPointer_t)gl_func_table[e_glVertexPointer];
    assert(thunk);
    thunk(size, type, stride, pointer);
}

ATTRIB
void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    typedef void (WINAPI * glViewport_t)(GLint, GLint, GLsizei, GLsizei);
    glViewport_t thunk = (glViewport_t)gl_func_table[e_glViewport];
    assert(thunk);
    thunk(x, y, width, height);
}
