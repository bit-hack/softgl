#pragma once
#include "primative.h"
#include "buffer.h"

struct context_t;


struct i_raster_t {

  // stop any use of old framebuffer
  virtual void framebuffer_release() = 0;

  // attach new framebuffer
  virtual void framebuffer_aquire() = 0;

  // spin up the rasterizer
  virtual void start(context_t &cxt) = 0;

  // kill the rasterizer
  virtual void stop() = 0;

  virtual void push_triangles(const std::vector<triangle_t> &triangles) = 0;

  // flip screen buffer
  virtual void flip() = 0;
};

i_raster_t * raster_create();
