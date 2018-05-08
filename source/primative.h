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
    , _begin_count(0)
  {}

  void glBegin(GLenum mode);

  void glEnd();

  void add_vertex(const float4 v);

  void clear_triangles() {
    _triangles.clear();
  }

  const std::vector<triangle_t> & triangles() const {
    return _triangles;
  }

protected:

  vertex_t _make_vertex(float4 v);

  void _asm_quads();
  void _asm_triangles();
  void _asm_triangle_strip();
  void _asm_triangle_fan();
  void _asm_quad_strip();
  void _asm_polygon();

  GLenum _mode;
  uint32_t _head;
  int32_t _begin_count;
  std::vector<vertex_t> _vertex;
  std::vector<triangle_t> _triangles;
};
