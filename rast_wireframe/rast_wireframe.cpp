#include "../source/raster.h"
#include "../source/context.h"
#include "surface.h"


struct raster_wire_t : public raster_t {

  raster_wire_t()
    : _cxt(nullptr)
  {}

  // stop any use of old framebuffer
  void framebuffer_release() override {}

  // attach new framebuffer
  void framebuffer_aquire() override {}

  // spin up the rasterizer
  void start(gl_context_t &cxt) override {
    _cxt = &cxt;
  }

  // kill the rasterizer
  void stop() override {}

  void push_triangles(const std::vector<triangle_t> &triangles) override {

    assert(_cxt);

    surface_t surf(_cxt->buffer.pixels(), _cxt->buffer.width(), _cxt->buffer.height(), _cxt->buffer.width());

    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped vertex so discard
        continue;
      }

      // XXX: insert edge into edge list to avoid redraw

      const std::array<float2, 3> c{
          float2{t.vert[0].coord.x, t.vert[0].coord.y},
          float2{t.vert[1].coord.x, t.vert[1].coord.y},
          float2{t.vert[2].coord.x, t.vert[2].coord.y},
      };

      surf.wuline(c[0], c[1], 0xffffff);
      surf.wuline(c[1], c[2], 0xffffff);
      surf.wuline(c[2], c[0], 0xffffff);
    }
  }

  // flip screen buffer
  void flip() override {}

  gl_context_t *_cxt;
};


extern "C" {

  __declspec(dllexport)
  raster_t *raster_create() {
    return new raster_wire_t;
  }

  __declspec(dllexport)
  void raster_release(raster_t *r) {
    delete r;
  }
};
