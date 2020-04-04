#include <cassert>
#include <memory>

#include "common.h"
#include "texture.h"
#include "log.h"
#include "context.h"

namespace {

bool isPowerOfTwo(uint32_t x) {
  return (x & (x - 1)) == 0;
}

static uint32_t targetToIndex(GLenum e) {
  switch (e) {
  case GL_TEXTURE_1D: return 0;
  case GL_TEXTURE_2D: return 1;
  default:            return 2;
  }
}

// required number of texels for root image and mipchain where levels is the
// number of mip levels
uint32_t texture_space_req(const uint32_t width, const uint32_t height, uint32_t levels) {
  uint32_t space = 0;
  for (uint32_t i = 0; i < levels; ++i) {
    const uint32_t w = std::max(1u, width >> i);
    const uint32_t h = std::max(1u, height >> i);
    space += w * h;
  }
  return space;
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

  if (!isPowerOfTwo(width) || !isPowerOfTwo(height)) {
    DEBUG_BREAK;
  }
  if (std::max(width, height) >= texture_t::max_size) {
    DEBUG_BREAK;
  }
  if (level >= texture_t::mip_levels) {
    DEBUG_BREAK;
  }

  texture_t *t = boundTexture2d();
  if (!t) {
    return;
  }

  // if this is the root level then allocate the image
  if (level == 0) {

    if (t->_pixels[0]) {
      t->release();
      t->_pixels.fill(nullptr);
    }

    t->_width  = width;
    t->_height = height;
    t->_wshift = int32_t(log2(width));

    size_t mem_size =
      texture_space_req(width, height, texture_t::mip_levels) * sizeof(uint32_t);
    t->_pixels[0] = (uint32_t *)_aligned_malloc(mem_size, 16);
    memset(t->_pixels[0], 0xFF, mem_size);

    // alloc all of the other mip levels
    for (int i = 0; i < texture_t::mip_levels - 1; ++i) {
      uint32_t advance = std::max<uint32_t>(1u, (width >> i) * (height >> i));
      t->_pixels[i + 1] = t->_pixels[i] + advance;
    }
  }
  else {
    // check our mip level is a submultiple
    if (width  != std::max(1u, t->_width  >> level) ||
        height != std::max(1u, t->_height >> level)) {
      DEBUG_BREAK;
    }
  }

  // load texture from the source
  t->load(level, format, type, pixels);

  // XXX: lets fudge in some mip levels for now
  if (level == 0) {
    t->generateMipLevels();
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

texture_t::texture_t()
  : _format(e_argb)
  , _width(0)
  , _height(0)
{
  _pixels.fill(nullptr);
}

void texture_t::generateMipLevels() {
  for (int i = 1; i < mip_levels; ++i) {

    const uint32_t *src = _pixels[i - 1];
          uint32_t *dst = _pixels[i - 0];

    // destination with and height
    const uint32_t dw = std::max(1u, _width  >>  i   );
    const uint32_t dh = std::max(1u, _height >>  i   );

    // source width height
    const uint32_t sw = std::max(1u, _width  >> (i-1));
    const uint32_t sh = std::max(1u, _height >> (i-1));

    for (uint32_t y = 0; y < dh; ++y) {
      for (uint32_t x = 0; x < dw; ++x) {
        dst[x + y * dw] = src[(x * 2) + (y * 2) * sw];
      }
    }
  }
}

void texture_t::release() {
  if (_pixels[0]) {
    _aligned_free(_pixels[0]);
  }
  _width = 0;
  _height = 0;
  _pixels.fill(nullptr);
}

void texture_t::load(uint32_t level, GLenum format, GLenum type, const void *src) {

  assert(level < mip_levels);
  assert(_pixels[level]);

  switch (type) {
  case GL_UNSIGNED_BYTE:
    switch (format) {
    case GL_RGBA:      load_rgba_8(level, src); break;
    case GL_BGR_EXT:   load_bgr_8 (level, src); break;
    case GL_RGB:       load_rgb_8 (level, src); break;
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

void texture_t::load_rgba_8(uint32_t level, const void *src) {

  const uint32_t swidth  = std::max(1u, _width  >> level);
  const uint32_t sheight = std::max(1u, _height >> level);

  const uint8_t  *srcy = (const uint8_t *)src;
        uint32_t *dsty = _pixels[level];
  assert(dsty && srcy);

  for (uint32_t y = 0; y < sheight; ++y) {
    const uint8_t  *srcx = srcy;
          uint32_t *dstx = dsty;
    for (uint32_t x = 0; x < swidth; ++x) {
      *dstx = packARGB(
        0, 
        (x * 255) / swidth,
        (y * 255) / sheight,
        0);
      *dstx = packARGB(
        srcx[3],
        srcx[0],
        srcx[1],
        srcx[2]);
      srcx += 4;
      dstx += 1;
    }
    srcy += swidth * 4;
    dsty += swidth;
  }
}

void texture_t::load_bgr_8(uint32_t level, const void *src) {

  const uint32_t swidth  = std::max(1u, _width  >> level);
  const uint32_t sheight = std::max(1u, _height >> level);

  const uint8_t  *srcy = (const uint8_t *)src;
        uint32_t *dsty = _pixels[level];
  assert(dsty && srcy);

  for (uint32_t y = 0; y < sheight; ++y) {
    const uint8_t *srcx = srcy;
    uint32_t *dstx = dsty;
    for (uint32_t x = 0; x < swidth; ++x) {
      *dstx = packARGB(0, srcx[2], srcx[1], srcx[0]);
      srcx += 3;
      dstx += 1;
    }
    srcy += swidth * 3;
    dsty += swidth;
  }
}

void texture_t::load_rgb_8(uint32_t level, const void *src) {

  const uint32_t swidth  = std::max(1u, _width  >> level);
  const uint32_t sheight = std::max(1u, _height >> level);

  const uint8_t  *srcy = (const uint8_t *)src;
        uint32_t *dsty = _pixels[level];
  assert(dsty && srcy);

  for (uint32_t y = 0; y < sheight; ++y) {
    const uint8_t *srcx = srcy;
    uint32_t *dstx = dsty;
    for (uint32_t x = 0; x < swidth; ++x) {
      *dstx = packARGB(0, srcx[0], srcx[1], srcx[2]);
      srcx += 3;
      dstx += 1;
    }
    srcy += swidth * 3;
    dsty += swidth;
  }
}
