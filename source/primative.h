#pragma once
#include <array>
#include <vector>

#include "GL.h"

#include "math.h"


struct triangle_t {
  float4 coord;
};


struct primative_manager_t {

  primative_manager_t()
    : _mode(GL_TRIANGLES)
  {}

  void glBegin(GLenum mode) {
    _mode = mode;
  }

  void glEnd() {
  }

  void vertex(const float4 v) {
    triangle_t t = _make_tri(v);
    switch (_mode) {
    case GL_TRIANGLES:
      _do_triangles(t);
      break;
    case GL_TRIANGLE_STRIP:
      _do_triangle_strip(t);
      break;
    case GL_TRIANGLE_FAN:
      _do_triangle_fan(t);
      break;
    case GL_QUADS:
      _do_quads(t);
      break;
    }
  }

protected:

  GLenum _mode;
  std::vector<triangle_t> _tri_list;

  triangle_t _make_tri(float4 t) {
    return triangle_t{};
  }

  void _do_quads(triangle_t t) {
  }

  void _do_triangles(triangle_t t) {
  }

  void _do_triangle_strip(triangle_t t) {
  }

  void _do_triangle_fan(triangle_t t) {
  }

  std::array<triangle_t, 3> _prev;
};
