#include <unordered_set>

#include "../source/raster.h"
#include "../source/context.h"
#include "surface.h"


struct line_t {
  float2 a, b;

  line_t(float2 i, float2 j) : a(i), b(j) {}
};


struct raster_wire_t : public raster_t {

  raster_wire_t()
    : _cxt(nullptr)
  {}

  void framebuffer_release() override {}

  void framebuffer_aquire() override {}

  void framebuffer_clear(
    bool color,
    bool depth,
    bool stencil,
    uint32_t clear_color,
    float clear_depth,
    uint32_t clear_stencil) override {
    if (_cxt) {
      _cxt->buffer.clear_colour(0x202020);
      if (depth) {
        _cxt->buffer.clear_depth(0.f);
      }
    }
  }

  bool start(gl_context_t &cxt) override {
    _cxt = &cxt;
    return true;
  }

  void stop() override {}

  void push_triangles(const std::vector<triangle_t> &triangles,
                      const texture_t *tex,
                      const state_manager_t &state) override {

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

  void flush() override {}

  void present() override {}

protected:
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
