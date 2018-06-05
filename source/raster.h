#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "primative.h"
#include "buffer.h"


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

  virtual void push_triangles(const std::vector<triangle_t> &triangles) = 0;

  // flip screen buffer
  virtual void flip() = 0;
};


typedef raster_t *(*rast_create_t)();
typedef void(*rast_release_t)(raster_t*);


struct raster_module_t {

  raster_module_t()
    : handle(nullptr)
    , create(nullptr)
    , release(nullptr)
    , inst(nullptr)
  {
  }

  HMODULE handle;
  rast_create_t create;
  rast_release_t release;
  raster_t *inst;
};


// load a rasterization dll
bool raster_load(raster_module_t &out);
