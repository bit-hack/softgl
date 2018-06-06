#pragma once
#include <array>
#include <vector>

#include "GL.h"
#include "math.h"

struct vertex_t {
  float4 coord;
  float2 tex;
};

struct triangle_t {
  std::array<vertex_t, 3> vert;
};

struct primative_manager_t {

  primative_manager_t() : _mode(GL_TRIANGLES), _head(0), _begin_count(0) {}

  void glBegin(GLenum mode);

  void glEnd();

  void add_vertex(const float4 v);

  void clear_triangles() { _triangles.clear(); }

  const std::vector<triangle_t> &triangles() const { return _triangles; }

  void clip_triangles();
  void convert_to_dc();

  void latch_uv(float2 t) { _latch_uv = t; }

  // int4 intead?
  void latch_argb(float4 c) { _latch_argb = c; }

  void glVertexPointer(GLint size, GLenum type, GLsizei stride,
                       const GLvoid *pointer);

  void glColorPointer(GLint size, GLenum type, GLsizei stride,
                      const GLvoid *pointer);

  void glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                         const GLvoid *pointer);

  void glDrawElements(GLenum mode, GLsizei count, GLenum type,
                      const GLvoid *indices);

  void glArrayElement(GLint i);

protected:
  void _push_vertex(const vertex_t &v);

  void _asm_quads();
  void _asm_triangles();
  void _asm_triangle_strip();
  void _asm_triangle_fan();
  void _asm_quad_strip();
  void _asm_polygon();

  struct array_t {
    GLenum _type;
    GLsizei _stride;
    GLint _size;
    const void *_pointer;
  };

  array_t _array_vertex;
  array_t _array_color;
  array_t _array_tex_coord;

  GLenum _mode;
  int32_t _begin_count;
  float2 _latch_uv;
  float4 _latch_argb;

  uint32_t _head;
  std::vector<vertex_t> _vertex;
  std::vector<triangle_t> _triangles;
};
