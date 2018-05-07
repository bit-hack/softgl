#pragma once
#include <array>
#include <vector>

#include "GL.h"

#include "math.h"


struct vertex_t {
  float4 coord;
};


struct triangle_t {
  std::array<vertex_t, 3> vert;
};


struct primative_manager_t {

  primative_manager_t()
    : _mode(GL_TRIANGLES)
    , _head(0)
  {}

  void glBegin(GLenum mode) {
    _mode = mode;
    _vertex.clear();
  }

  void glEnd() {
    _vertex.clear();
  }

  void add_vertex(const float4 v);

  void clear_triangles() {
    _triangles.clear();
  }

  const std::vector<triangle_t> & triangles() const {
    return _triangles;
  }

protected:

  vertex_t _make_vertex(float4 v) {
    return vertex_t{v};
  }

  void _do_quads(vertex_t t);

  void _do_triangles(vertex_t t);

  void _do_triangle_strip(vertex_t t);

  void _do_triangle_fan(vertex_t t);

  GLenum _mode;
  uint32_t _head;
  std::vector<vertex_t> _vertex;
  std::vector<triangle_t> _triangles;
};
