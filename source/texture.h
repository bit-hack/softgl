#pragma once
#include "GL.h"

#include <unordered_map>
#include <array>


struct texture_t {

  enum {
    max_size = 1024,
    mip_levels = 10  // log2(max_size)
  };

  enum format_t {
    e_argb
  };

  texture_t();

  format_t _format;


  uint32_t _width;
  uint32_t _wshift;  // log2(_width)

  uint32_t _height;
  std::array<uint32_t *, mip_levels> _pixels;

  void load(uint32_t level, GLenum format, GLenum type, const void *src);
  void load_rgba_8(uint32_t level, const void *src);
  void load_bgr_8(uint32_t level, const void *src);
  void load_rgb_8(uint32_t level, const void *src);

  void generateMipLevels();

  void release();
};


struct texture_manager_t {

  texture_manager_t() : _uuid(0) {
    _bound.fill(0);
  }

  //

  void glTexImage1D(GLenum target, GLint level, GLint internalformat,
                    GLsizei width, GLint border, GLenum format, GLenum type,
                    const GLvoid *pixels);

  void glTexImage2D(GLenum target, GLint level, GLint internalformat,
                    GLsizei width, GLsizei height, GLint border, GLenum format,
                    GLenum type, const GLvoid *pixels);

  //

  void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width,
                       GLenum format, GLenum type, const GLvoid *pixels);

  void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                       GLsizei width, GLsizei height, GLenum format,
                       GLenum type, const GLvoid *pixels);

  //

  void glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat,
                        GLint x, GLint y, GLsizei width, GLint border);

  void glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat,
                        GLint x, GLint y, GLsizei width, GLsizei height,
                        GLint border);

  //

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

  GLboolean glIsTexture(GLuint texture);

  texture_t *boundTexture2d();

protected:

  // get or create a texture object
  texture_t *getOrCreateTexture(uint32_t index);

  // get or create a texture object
  texture_t *getTexture(uint32_t index);

  std::array<uint32_t, 4> _bound;

  uint32_t _uuid;
  std::unordered_map<uint32_t, struct texture_t*> _tex_map;
};
