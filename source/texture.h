#pragma once
#include "GL.h"

struct texture_manager_t {

  void glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat,
                        GLint x, GLint y, GLsizei width, GLint border);

  void glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat,
                        GLint x, GLint y, GLsizei width, GLsizei height,
                        GLint border);

  void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x,
                           GLint y, GLsizei width);

  void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset,
                           GLint yoffset, GLint x, GLint y, GLsizei width,
                           GLsizei height);

  void glBindTexture(GLenum target, GLuint texture);

  GLboolean glAreTexturesResident(GLsizei n, const GLuint *textures,
                                  GLboolean *residences);

  void glDeleteTextures(GLsizei n, const GLuint *textures);

  void glGenTextures(GLsizei n, GLuint *textures);
};
