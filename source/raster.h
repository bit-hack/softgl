#pragma once
#include "windows.h"
#include "buffer.h"
#include "primative.h"
#include "texture.h"

struct gl_context_t;

struct raster_t {

  // stop any use of old framebuffer
  virtual void framebuffer_release() = 0;

  // attach new framebuffer
  virtual void framebuffer_aquire() = 0;

  // spin up the rasterizer
  virtual void start(gl_context_t &cxt) = 0;

  // kill the rasterizer
  virtual void stop() = 0;

  // push triangles to the rasterizer
  virtual void push_triangles(const std::vector<triangle_t> &triangles,
                              const texture_t *tex) = 0;

  // pipeline is being flushed
  virtual void flush() = 0;

  // present screen buffer
  virtual void present() = 0;
};

typedef raster_t *(*rast_create_t)();
typedef void (*rast_release_t)(raster_t *);

struct raster_module_t {

  raster_module_t()
      : handle(nullptr), create(nullptr), release(nullptr), inst(nullptr) {}

  HMODULE handle;
  rast_create_t create;
  rast_release_t release;
  raster_t *inst;
};

// load a rasterization dll
bool raster_load(raster_module_t &dll, gl_context_t &cxt);
