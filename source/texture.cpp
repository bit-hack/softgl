#include <cassert>
#include <memory>

#include "common.h"
#include "texture.h"
#include "log.h"
#include "context.h"

namespace {

bool isPowerOfTwo(uint32_t x)
{
    return (x & (x - 1)) == 0;
}

static uint32_t targetToIndex(GLenum e) {
  switch (e) {
  case GL_TEXTURE_1D: return 0;
  case GL_TEXTURE_2D: return 1;
  default:            return 2;
  }
}

void fillTexture(uint32_t *pix, uint32_t w, uint32_t h) {
  for (uint32_t y = 0; y < h; ++y) {
    for (uint32_t x = 0; x < w; ++x) {
      pix[x + y * w] = ((x ^ y) & 1) ? 0x101010 : 0x90b0d0;
    }
  }
}

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
  if (level != 0) {
    return;
  }

  if (!isPowerOfTwo(width) || !isPowerOfTwo(height)) {
    DEBUG_BREAK;
  }

  texture_t *t = boundTexture2d();
  if (t) {
    assert(t);
    t->release();
    t->pixels =
      (uint32_t *)_aligned_malloc(width * height * sizeof(uint32_t), 16);
    assert(t->pixels);
    t->width = width;
    t->height = height;
    // load texture from the source
    t->load(format, type, pixels);
  }
}

void texture_manager_t::glCopyTexImage1D(GLenum target, GLint level,
                                         GLenum internalFormat, GLint x,
                                         GLint y, GLsizei width, GLint border) {
  auto itt = _tex_map.find(_bound[targetToIndex(target)]);
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
  auto itt = _tex_map.find(_bound[targetToIndex(target)]);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
    DEBUG_BREAK;
  }
  DEBUG_BREAK;
}

void texture_manager_t::glTexSubImage1D(GLenum target, GLint level,
                                        GLint xoffset, GLsizei width,
                                        GLenum format, GLenum type,
                                        const GLvoid *pixels) {
  auto itt = _tex_map.find(_bound[targetToIndex(target)]);
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
  auto itt = _tex_map.find(_bound[targetToIndex(target)]);
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
  auto itt = _tex_map.find(_bound[targetToIndex(target)]);
  if (itt != _tex_map.end()) {
    auto *t = itt->second;
    assert(t);
  }
}

void texture_manager_t::glBindTexture(GLenum target, GLuint texture) {
  if (target != GL_TEXTURE_2D) {
    DEBUG_BREAK;
  }

  // if the bound texture is changed
  if (_bound[targetToIndex(target)] != texture) {
    // flush the pipeline
    Context->on_flush();
  }

  texture_t *tex = getOrCreateTexture(texture);
  assert(tex);
  (void)tex;
  _bound[targetToIndex(target)] = texture;
}

GLboolean texture_manager_t::glAreTexturesResident(GLsizei n,
                                                   const GLuint *textures,
                                                   GLboolean *residences) {
  // determine if textures are loaded in texture memory
  DEBUG_BREAK;
  return false;
}

void texture_manager_t::glDeleteTextures(GLsizei n, const GLuint *textures) {

  // flush the pipeline
  // XXX: only do if it was the bound texture
    Context->on_flush();

  for (GLsizei i = 0; i < n; ++i) {
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

texture_t *texture_manager_t::getTexture(uint32_t x) {
  // return texture if it exists
  auto itt = _tex_map.find(x);
  if (itt != _tex_map.end()) {
    return itt->second;
  }
  return nullptr;
}

texture_t *texture_manager_t::getOrCreateTexture(uint32_t x) {
  // return texture if it exists
  if (texture_t *t = getTexture(x)) {
    return t;
  }
  // create new texture
  auto tex = std::make_unique<texture_t>();
  memset(tex.get(), 0, sizeof(texture_t));
  // insert into the tex map
  texture_t *t = tex.release();
  _tex_map[x] = t;
  return t;
}

void texture_manager_t::glGenTextures(GLsizei n, GLuint *textures) {
  for (GLsizei i = 0; i < n; ++i) {
    // check texture is not already registered
    uint32_t x = ++_uuid;
    auto itt = _tex_map.find(x);
    if (itt != _tex_map.end()) {
      continue;
    }
    texture_t *tex = getOrCreateTexture(x);
    (void)tex;
    // return texture id to caller
    textures[i] = x;
  }
}

GLboolean texture_manager_t::glIsTexture(GLuint texture) {
  DEBUG_BREAK;
  return GL_FALSE;
}

texture_t *texture_manager_t::boundTexture2d() {
  const uint32_t index = _bound[targetToIndex(GL_TEXTURE_2D)];
  auto itt = _tex_map.find(index);
  if (itt != _tex_map.end()) {
    return itt->second;
  }
  return nullptr;
}

void texture_t::release() {
  if (pixels) {
    _aligned_free(pixels);
    pixels = nullptr;
  }
}

void texture_t::load(GLenum format, GLenum type, const void *src) {
  switch (type) {
  case GL_UNSIGNED_BYTE:
    switch (format) {
    case GL_RGBA:
      load_rgba_8(src);
      break;
    case GL_BGR_EXT:
      load_bgr_8(src);
      break;
    case GL_RGB:
      load_rgb_8(src);
      break;
    default:
      DEBUG_BREAK;
    }
    break;
  default:
    DEBUG_BREAK;
  }
}

static inline uint32_t packARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return (r << 24) | (g << 16) | (b << 8) | a;
}

void texture_t::load_rgba_8(const void *src) {

  const uint8_t *srcy = (const uint8_t *)src;
  uint32_t *dsty = pixels;
  for (uint32_t y = 0; y < height; ++y) {
    const uint8_t *srcx = srcy;
    uint32_t *dstx = dsty;
    for (uint32_t x = 0; x < width; ++x) {
      *dstx = packARGB(srcx[3], srcx[0], srcx[1], srcx[2]);
      srcx += 4;
      dstx += 1;
    }
    srcy += width * 4;
    dsty += width;
  }
}

void texture_t::load_bgr_8(const void *src) {

  const uint8_t  *srcy = (const uint8_t *)src;
        uint32_t *dsty = pixels;

  for (uint32_t y = 0; y < height; ++y) {

    const uint8_t *srcx = srcy;
    uint32_t *dstx = dsty;

    for (uint32_t x = 0; x < width; ++x) {

      *dstx = packARGB(0, srcx[2], srcx[1], srcx[0]);

      srcx += 3;
      dstx += 1;
    }

    srcy += width * 3;
    dsty += width;
  }
}

void texture_t::load_rgb_8(const void *src) {
  const uint8_t  *srcy = (const uint8_t *)src;
        uint32_t *dsty = pixels;
  for (uint32_t y = 0; y < height; ++y) {
    const uint8_t *srcx = srcy;
    uint32_t *dstx = dsty;
    for (uint32_t x = 0; x < width; ++x) {
      *dstx = packARGB(0, srcx[0], srcx[1], srcx[2]);
      srcx += 3;
      dstx += 1;
    }
    srcy += width * 3;
    dsty += width;
  }
}
