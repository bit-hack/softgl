#include "context.h"

#include "primative.h"

vertex_t primative_manager_t::_make_vertex(float4 f) {
  return vertex_t{f};
}

void primative_manager_t::glBegin(GLenum mode) {
  if (++_begin_count != 1) {
    __debugbreak();
  }
  _mode = mode;
  _vertex.clear();
}

void primative_manager_t::glEnd() {
  switch (_mode) {
  case GL_TRIANGLES:
    _asm_triangles();  // untested
    break;
  case GL_TRIANGLE_FAN:
    _asm_triangle_fan();
    break;
  case GL_TRIANGLE_STRIP:
    _asm_triangle_strip();  // untested
    break;
  case GL_QUADS:
    _asm_quads();  // untested
    break;
  case GL_QUAD_STRIP:
    _asm_quad_strip();  // untested
    break;
  case GL_POLYGON:  // untested
    _asm_polygon();
    break;
  default:
    __debugbreak();
    break;
  }
  if (--_begin_count != 0) {
    __debugbreak();
  }
  _vertex.clear();
}

void primative_manager_t::add_vertex(const float4 v) {
  const float4 tv = Context->matrix.transform(v);
  _vertex.push_back(_make_vertex(tv));
}

void primative_manager_t::_asm_triangles() {
  for (size_t i = 2; i < _vertex.size(); i += 3) {
    const triangle_t tri = {
      _vertex[i - 2],
      _vertex[i - 1],
      _vertex[i - 0]};
    _triangles.push_back(tri);
  }
}

void primative_manager_t::_asm_triangle_strip() {
  for (size_t i = 2; i < _vertex.size(); i += 1) {
    const triangle_t tri = {
      _vertex[i - 2 ^ (i & 1)],
      _vertex[i - 1 ^ (i & 1)],
      _vertex[i - 0]};
    _triangles.push_back(tri);
  }
}

void primative_manager_t::_asm_triangle_fan() {
  for (size_t i = 2; i < _vertex.size(); i += 1) {
    const triangle_t tri = {
      _vertex[i - 1],
      _vertex[i - 0],
      _vertex[0]
    };
    _triangles.push_back(tri);
  }
}

void primative_manager_t::_asm_quads() {
  for (size_t i = 4; i < _vertex.size(); i += 4) {
    const triangle_t t1 = {
      _vertex[i - 2],
      _vertex[i - 1],
      _vertex[i - 0]
    };
    _triangles.push_back(t1);
    const triangle_t t2 = {
      _vertex[i - 3],
      _vertex[i - 2],
      _vertex[i - 1]
    };
    _triangles.push_back(t2);
  }
}

void primative_manager_t::_asm_quad_strip() {
}

void primative_manager_t::_asm_polygon() {
  for (size_t i = 2; i < _vertex.size(); i += 1) {
    const triangle_t tri = {
      _vertex[i - 1],
      _vertex[i - 0],
      _vertex[0]
    };
    _triangles.push_back(tri);
  }
}
