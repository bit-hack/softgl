#pragma once
#include <array>
#include <vector>

#include "GL.h"
#include "math.h"

struct gl_context_t;

#pragma pack( push, 1 )
struct vertex_t {
  float4 coord;
  float4 rgba;
  float2 tex;
};

#pragma pack( push, 1 )
struct triangle_t {
  vertex_t vert[3];
};

struct primative_manager_t {

  primative_manager_t(gl_context_t &cxt)
    : _cxt(cxt)
    , _mode(GL_TRIANGLES)
    , _begin_count(0) {}

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

  void glDrawArrays(GLenum mode, GLint first, GLsizei count);

  void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count,
                           GLenum type, const void *indices);

protected:
  void _push_vertex(const vertex_t &v);

  void _asm_quads();
  void _asm_triangles();
  void _asm_triangle_strip();
  void _asm_triangle_fan();
  void _asm_quad_strip();
  void _asm_polygon();

  struct array_t {

    array_t()
      : _type(0)
      , _stride(0)
      , _size(0)
      , _pointer(nullptr)
    {
    }

    GLenum _type;
    GLsizei _stride;
    GLint _size;
    const void *_pointer;
  };

  gl_context_t &_cxt;

  array_t _array_vertex;
  array_t _array_color;
  array_t _array_tex_coord;

  GLenum _mode;
  int32_t _begin_count;
  float2 _latch_uv;
  float4 _latch_argb;

  std::vector<vertex_t> _vertex;
  std::vector<triangle_t> _triangles;
};
