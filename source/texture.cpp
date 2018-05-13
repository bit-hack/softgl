#include <cassert>
#include <memory>

#include "common.h"
#include "texture.h"

namespace {

} // namespace

void texture_manager_t::glTexImage1D(GLenum target, GLint level,
                                     GLint internalformat, GLsizei width,
                                     GLint border, GLenum format, GLenum type,
                                     const GLvoid *pixels) {
  DEBUG_BREAK;
}

void texture_manager_t::glTexImage2D(GLenum target, GLint level,
                                     GLint internalFormat, GLsizei width,
                                     GLsizei height, GLint border,
                                     GLenum format, GLenum type,
                                     const GLvoid *pixels) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
    t->release();
    t->pixels =
        (uint32_t *)_aligned_malloc(width * height * sizeof(uint32_t), 16);
  }
}

void texture_manager_t::glCopyTexImage1D(GLenum target, GLint level,
                                         GLenum internalFormat, GLint x,
                                         GLint y, GLsizei width, GLint border) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
    DEBUG_BREAK;
  }
}

void texture_manager_t::glCopyTexImage2D(GLenum target, GLint level,
                                         GLenum internalFormat, GLint x,
                                         GLint y, GLsizei width, GLsizei height,
                                         GLint border) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
    DEBUG_BREAK;
  }
}

void texture_manager_t::glTexSubImage1D(GLenum target, GLint level,
                                        GLint xoffset, GLsizei width,
                                        GLenum format, GLenum type,
                                        const GLvoid *pixels) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
  }
}

void texture_manager_t::glTexSubImage2D(GLenum target, GLint level,
                                        GLint xoffset, GLint yoffset,
                                        GLsizei width, GLsizei height,
                                        GLenum format, GLenum type,
                                        const GLvoid *pixels) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
  }
}

void texture_manager_t::glCopyTexSubImage1D(GLenum target, GLint level,
                                            GLint xoffset, GLint x, GLint y,
                                            GLsizei width) {
  DEBUG_BREAK;
}

void texture_manager_t::glCopyTexSubImage2D(GLenum target, GLint level,
                                            GLint xoffset, GLint yoffset,
                                            GLint x, GLint y, GLsizei width,
                                            GLsizei height) {
  auto itt = _tex_map.find(_bound);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
  }
}

void texture_manager_t::glBindTexture(GLenum target, GLuint texture) {
  if (target != GL_TEXTURE_2D) {
    DEBUG_BREAK;
  }
  auto itt = _tex_map.find(texture);
  if (itt == _tex_map.end()) {
    _bound = 0;
  } else {
    _bound = texture;
  }
}

GLboolean texture_manager_t::glAreTexturesResident(GLsizei n,
                                                   const GLuint *textures,
                                                   GLboolean *residences) {
  // determine if textures are loaded in texture memory
  DEBUG_BREAK;
  return false;
}

void texture_manager_t::glDeleteTextures(GLsizei n, const GLuint *textures) {
  for (uint32_t i = 0; i < n; ++i) {
    // locate texture
    auto itt = _tex_map.find(textures[i]);
    if (itt == _tex_map.end()) {
      continue;
    }
    // delete contents
    itt->second->release();
    // delete structure
    delete itt->second;
    // remove from texmap
    _tex_map.erase(itt);
  }
}

void texture_manager_t::glGenTextures(GLsizei n, GLuint *textures) {
  for (uint32_t i = 0; i < n; ++i) {
    // check texture is not already registered
    uint32_t x = ++_uuid;
    auto itt = _tex_map.find(x);
    if (itt != _tex_map.end()) {
      continue;
    }
    // create new texture
    auto tex = std::make_unique<texture_t>();
    memset(tex.get(), 0, sizeof(texture_t));
    // insert into the tex map
    _tex_map[x] = tex.release();
    // return to caller
    textures[i] = x;
  }
}

void texture_t::release() {
  if (pixels) {
    _aligned_free(pixels);
    pixels = nullptr;
  }
}
