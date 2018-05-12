#pragma once
#include <cstdint>
#include <algorithm>

#include "raster.h"
#include "math.h"
#include "context.h"


namespace {

struct frame_t {
  uint32_t *_pixels;
  float *_depth;
  int32_t _width;
  int32_t _height;
};

constexpr float edgeEval(const float4 &a, const float4 &b, const float2 &c) {
  return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

struct rect_t {
  int32_t x0, y0;
  int32_t x1, y1;
};

rect_t boundTri(const frame_t &frame,
                const float4 &v0,
                const float4 &v1,
                const float4 &v2) {
  rect_t out;
  // Compute triangle bounding box
  out.x0 = std::min({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y0 = std::min({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  out.x1 = std::max({int32_t(v0.x), int32_t(v1.x), int32_t(v2.x)});
  out.y1 = std::max({int32_t(v0.y), int32_t(v1.y), int32_t(v2.y)});
  // Clip against screen bounds
  out.x0 = std::max(out.x0, 0);
  out.y0 = std::max(out.y0, 0);
  out.x1 = std::min(out.x1, frame._width - 1);
  out.y1 = std::min(out.y1, frame._height - 1);
  return out;
}

} // namespace

void drawTri(const frame_t &frame,
             const float4 &v0,
             const float4 &v1,
             const float4 &v2) {
  // Compute triangle bounding box
  const rect_t rect = boundTri(frame, v0, v1, v2);

  // the signed triangle area
  const float area =
      1.f / ((v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y));
  if (area <= 0.f) {
    return;
  }

  // Triangle setup
  const float sx01 = (v0.y - v1.y) * area;
  const float sy01 = (v1.x - v0.x) * area;
  const float sx12 = (v1.y - v2.y) * area;
  const float sy12 = (v2.x - v1.x) * area;
  const float sx20 = (v2.y - v0.y) * area;
  const float sy20 = (v0.x - v2.x) * area;

  // Barycentric coordinates at minX/minY corner
  const float2 p{float(rect.x0), float(rect.y0)};
  float w0y = edgeEval(v1, v2, p) * area;
  float w1y = edgeEval(v2, v0, p) * area;
  float w2y = edgeEval(v0, v1, p) * area;

  const float iw0 = 1.f / v0.w;
  const float iw1 = 1.f / v1.w;
  const float iw2 = 1.f / v2.w;

        float iw  = w0y  * iw0 + w1y  * iw1 + w2y  * iw2;
  const float iwx = sx12 * iw0 + sx20 * iw1 + sx01 * iw2;
  const float iwy = sy12 * iw0 + sy20 * iw1 + sy01 * iw2;

  // pointer to upper left corner
  uint32_t *dst = frame._pixels + rect.y0 * frame._width;
  float *zbf = frame._depth + rect.y0 * frame._width;

  // Rasterize
  for (int32_t y = rect.y0; y <= rect.y1; y++) {

    // Barycentric coordinates at start of row
    float w0x = w0y;
    float w1x = w1y;
    float w2x = w2y;
    float w = iw;

    for (int32_t x = rect.x0; x <= rect.x1; x++) {

      // If p is on or inside all edges, render pixel.
      if (w0x > 0.f && w1x > 0.f && w2x > 0.f) {

        if (w > zbf[x]) {

          zbf[x] = w;

          const uint32_t c = std::min(255, int32_t(w * 64 * 255));

          // renderPixel(p, w0, w1, w2);
          dst[x] = (c << 16) | (c << 8) | (c);
        }
      }

      w0x += sx12;
      w1x += sx20;
      w2x += sx01;
      w += iwx;
    }

    // One row step
    w0y += sy12;
    w1y += sy20;
    w2y += sy01;
    iw += iwy;

    // step y axis
    dst += frame._width;
    zbf += frame._width;
  }
}


struct raster_imp_t : public i_raster_t {

  // stop any use of old framebuffer
  void framebuffer_release() override {}

  // attach new framebuffer
  void framebuffer_aquire() override {}

  // spin up the rasterizer
  void start(context_t &cxt) override {}

  // kill the rasterizer
  void stop() override {}

  void push_triangles(const std::vector<triangle_t> &triangles) override {
    frame_t frame;
    frame._pixels = Context->buffer.pixels();
    frame._depth = Context->buffer.depth();
    frame._width = Context->buffer.width();
    frame._height = Context->buffer.height();

    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped vertex so discard
        continue;
      }

      drawTri(frame, t.vert[0].coord, t.vert[2].coord, t.vert[1].coord);
    }
  }

  // flip screen buffer
  void flip() override {}
};


struct raster_wire_t : public i_raster_t {

  // stop any use of old framebuffer
  void framebuffer_release() override {}

  // attach new framebuffer
  void framebuffer_aquire() override {}

  // spin up the rasterizer
  void start(context_t &cxt) override {}

  // kill the rasterizer
  void stop() override {}

  void push_triangles(const std::vector<triangle_t> &triangles) override {
    frame_t frame;
    frame._pixels = Context->buffer.pixels();
    frame._depth = Context->buffer.depth();
    frame._width = Context->buffer.width();
    frame._height = Context->buffer.height();

    for (const auto &t : triangles) {
      if (t.vert[0].coord.w == 0.f) {
        // signals fully clipped vertex so discard
        continue;
      }

      const std::array<float2, 3> c{
          float2{t.vert[0].coord.x, t.vert[0].coord.y},
          float2{t.vert[1].coord.x, t.vert[1].coord.y},
          float2{t.vert[2].coord.x, t.vert[2].coord.y},
      };

      Context->buffer.surface().wuline(c[0], c[1], 0xffffff);
      Context->buffer.surface().wuline(c[1], c[2], 0xffffff);
      Context->buffer.surface().wuline(c[2], c[0], 0xffffff);
    }
  }

  // flip screen buffer
  void flip() override {}
};


i_raster_t * raster_create() {
#if 1
  return new raster_imp_t;
#else
  return new raster_wire_t;
#endif
}
