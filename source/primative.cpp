#include "context.h"

#include "primative.h"


void primative_manager_t::add_vertex(const float4 v) {

  const float4 tv = Context->matrix.transform(v);

  vertex_t vert = _make_vertex(tv);

  switch (_mode) {
  case GL_TRIANGLES:
    _do_triangles(vert);
    break;
  case GL_TRIANGLE_STRIP:
    _do_triangle_strip(vert);
    break;
  case GL_TRIANGLE_FAN:
    _do_triangle_fan(vert);
    break;
  case GL_QUADS:
    _do_quads(vert);
    break;
  default:
    __debugbreak();
  }
}

void primative_manager_t::_do_triangles(vertex_t v) {
  _vertex.push_back(v);
  if (_vertex.size() >= 3) {
    const triangle_t tri = {
      _vertex[0],
      _vertex[1],
      _vertex[2]
    };
    _triangles.push_back(tri);
    _vertex.clear();
  }
}

void primative_manager_t::_do_triangle_strip(vertex_t v) {

}

void primative_manager_t::_do_triangle_fan(vertex_t v) {

}

void primative_manager_t::_do_quads(vertex_t v) {

}
