#include "common.h"
#include "context.h"
#include "primative.h"


namespace {

size_t getGLTypeSize(GLenum type) {
  switch (type) {
  case GL_FLOAT:
  case GL_INT:
  case GL_UNSIGNED_INT:   return 4;
  case GL_SHORT:
  case GL_UNSIGNED_SHORT: return 2;
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:  return 1;
  default:
    DEBUG_BREAK;
    return 0;
  }
}

} // namespace {}


void primative_manager_t::_push_vertex(const vertex_t &v) {
  _vertex.emplace_back(v);
  _vertex.back().coord = Context->matrix.transform(v.coord);
}

void primative_manager_t::glBegin(GLenum mode) {
  if (++_begin_count != 1) {
    DEBUG_BREAK;
  }
  _mode = mode;
  _vertex.clear();
}

void primative_manager_t::glEnd() {
  switch (_mode) {
  case GL_TRIANGLES:
    _asm_triangles();
    break;
  case GL_TRIANGLE_FAN:
    _asm_triangle_fan();
    break;
  case GL_TRIANGLE_STRIP:
    // note: used almost exclusively by quake3
    _asm_triangle_strip();
    break;
  case GL_QUADS:            // untested
    _asm_quads();
    break;
  case GL_QUAD_STRIP:       // untested
//    _asm_quad_strip();
    break;
  case GL_POLYGON:
    _asm_polygon();
    break;
  case GL_LINE_STRIP:       // untested
    break;
  default:
    DEBUG_BREAK;
    break;
  }
  if (--_begin_count != 0) {
    DEBUG_BREAK;
  }
  _vertex.clear();

  Context->on_flush();
}

void primative_manager_t::add_vertex(const float4 v) {
  _push_vertex(vertex_t{v, _latch_uv, _latch_argb});
}

void primative_manager_t::_asm_triangles() {
  for (size_t i = 2; i < _vertex.size(); i += 3) {
    const triangle_t tri = {
      _vertex[i - 2],
      _vertex[i - 1],
      _vertex[i - 0]};
    _triangles.push_back(tri);
  }
  _vertex.clear();
}

void primative_manager_t::_asm_triangle_strip() {
  for (size_t i = 2; i < _vertex.size(); i += 1) {
      const int32_t b = (i & 1);
      const triangle_t tri = {
        _vertex[i - 2],
        _vertex[i - (1 ^ b)],
        _vertex[i - (0 ^ b)]};
      _triangles.push_back(tri);
  }
  _vertex.clear();
}

void primative_manager_t::_asm_triangle_fan() {
  for (size_t i = 2; i < _vertex.size(); i += 1) {
    const triangle_t tri = {
      _vertex[0],
      _vertex[i - 1],
      _vertex[i - 0]};
    _triangles.push_back(tri);
  }
  _vertex.clear();
}

void primative_manager_t::_asm_quads() {
  for (size_t i = 3; i < _vertex.size(); i += 4) {
    const triangle_t t1 = {
      _vertex[i - 0],
      _vertex[i - 1],
      _vertex[i - 2]
    };
    _triangles.push_back(t1);
    const triangle_t t2 = {
      _vertex[i - 0],
      _vertex[i - 2],
      _vertex[i - 3]
    };
    _triangles.push_back(t2);
  }
  _vertex.clear();
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
  _vertex.clear();
}

static bool _is_backfacing(const float4 & a, const float4 & b, const float4 & c) {
  // test z componant of cross product
  return ( (c.x-a.x)*(c.y-b.y) - (c.x-b.x)*(c.y-a.y) ) > 0.f;
}

void primative_manager_t::clip_triangles() {

  if (_triangles.empty()) {
    return;
  }

  std::array<vertex_t, 8> vert;
  memset(&vert, 0, sizeof(vert));
  uint32_t head = 0;

  const auto clip_edge = [&vert, &head](
      const vertex_t &v0,
      const vertex_t &v1,
      const uint32_t c0,
      const uint32_t c1) {

    // if v0 is inside frustum
    if (c0 == 0) {
      vert[head++] = vertex_t{v0};
    }

    const float4 p0 = v0.coord, p1 = v1.coord;
    const float2 t0 = v0.tex,   t1 = v1.tex;
    const float4 r0 = v0.rgba,  r1 = v1.rgba;

    // the equality that we are trying to solve:
    //   (z0 + (z1 - z0) * t)  ==  (-w0 + (-w1 - -w0) * t)
    //   to find z == -w intersection point
    //
    // or when our 3d coordinate is:
    //   z / w = -1
    //
    //   t = (z0 + w0) / ((w0 - w1) - (z1 - z0))
    //
    const float   nom = (p0.z + p0.w);
    const float denom = (p0.w - p1.w) - (p1.z - p0.z);
    const float t = nom / denom;
    if (denom == 0.f) {
      DEBUG_BREAK;
      vert[head++] = vertex_t{v1};
      return;
    }

    if (t < 0.f || t > 1.f) {
      DEBUG_BREAK;
    }

    const float4 midPos = float4::lerp(p0, p1, t);
    const float2 midTex = float2::lerp(t0, t1, t);
    const float4 midCol = float4::lerp(r0, r1, t);
    vert[head++] = vertex_t{midPos, midTex, midCol};
  };

  uint32_t cutoff = _triangles.size();
  while (cutoff) {

    auto &t = _triangles[--cutoff];
    const auto &v0 = t.vert[0];
    const auto &v1 = t.vert[1];
    const auto &v2 = t.vert[2];

#if 0
    if (_is_backfacing(v0.coord, v1.coord, v2.coord)) {
      // discard backfacing triangle
      memset(&t, 0, sizeof(t));
      continue;
    }
#endif

    // bit positive when behind near plane
    const int32_t c0 = (v0.coord.z <= -v0.coord.w) << 0;  // 1
    const int32_t c1 = (v1.coord.z <= -v1.coord.w) << 1;  // 2
    const int32_t c2 = (v2.coord.z <= -v2.coord.w) << 2;  // 4
    const uint32_t cc = c0 | c1 | c2;

    if (cc == 0) {
      // keep, fully in front of near plane
      continue;
    }

    if (cc == 7) {
      // discard, fully behind near plane
      memset(&t, 0, sizeof(t));
      continue;
    }

    head = 0;

    // edge v0 -> v1
    if ((c0 | c1) == 0)             // fully in
      vert[head++] = v0;
    else if ((c0 | c1) != 3)        // spanning
      clip_edge(v0, v1, c0, c1);

    // edge v1 -> v2
    if ((c1 | c2) == 0)             // fully in
      vert[head++] = v1;
    else if ((c1 | c2) != 6)        // spanning
      clip_edge(v1, v2, c1, c2);

    // edge v2 -> v0
    if ((c2 | c0) == 0)             // fully in
      vert[head++] = v2;
    else if ((c2 | c0) != 5)        // spanning
      clip_edge(v2, v0, c2, c0);

    assert(head <= 4);

    // re-assemble primative
    if (head >= 3)
      // replace current triangle
      t = triangle_t{vert[0], vert[1], vert[2]};
    if (head >= 4)
      // append extra triangle
      _triangles.push_back(triangle_t{vert[0], vert[2], vert[3]});
  }
}

void primative_manager_t::convert_to_dc() {

  auto &viewport = Context->state.viewport;
  // get viewport center offset
  const float vx = viewport.x0;
  const float vy = viewport.y0;
  const float vw = viewport.dx() * .5f;
  const float vh = viewport.dy() * .5f;

  auto transform = [vx, vy, vw, vh](float4 &v) {
    // homogenous perspective divide
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
    // ndc -> dc coordinate
    v.x = vx + (v.x * vw + vw);
    v.y = vy + (v.y * vh + vh);
  };

  for (auto &t : _triangles) {
    transform(t.vert[0].coord);
    transform(t.vert[1].coord);
    transform(t.vert[2].coord);
  }
}

void primative_manager_t::glVertexPointer(GLint size, GLenum type,
                                          GLsizei stride,
                                          const GLvoid *pointer) {
  _array_vertex._size = size;
  _array_vertex._type = type;
  _array_vertex._stride = stride ? stride : (getGLTypeSize(type) * size);
  _array_vertex._pointer = (const void *)pointer;
}

void primative_manager_t::glColorPointer(GLint size, GLenum type,
                                         GLsizei stride,
                                         const GLvoid *pointer) {
  _array_color._size = size;
  _array_color._type = type;
  _array_color._stride = stride ? stride : (getGLTypeSize(type) * size);
  _array_color._pointer = (const void *)pointer;
}

void primative_manager_t::glTexCoordPointer(GLint size, GLenum type,
                                            GLsizei stride,
                                            const GLvoid *pointer) {
  _array_tex_coord._size = size;
  _array_tex_coord._type = type;
  _array_tex_coord._stride = stride ? stride : (getGLTypeSize(type) * size);
  _array_tex_coord._pointer = (const void *)pointer;
}

void primative_manager_t::glArrayElement(GLint i) {

  // vertex coordinates
  float2 uv = {0.f, 0.f};
  if (_array_tex_coord._pointer) {
    if (_array_tex_coord._type != GL_FLOAT)
      DEBUG_BREAK;
    // find tex coord
    const uint8_t * t = (const uint8_t *)_array_tex_coord._pointer;
    t += i * _array_tex_coord._stride;
    const float *b = (const float *)t;
    uv = float2{b[0], b[1]};
  }

  // color
  float4 argb = {1.f, 1.f, 1.f, 1.f};
  if (_array_color._pointer) {
    if (_array_color._type != GL_UNSIGNED_BYTE)
      DEBUG_BREAK;
    const uint8_t *c = (const uint8_t *)_array_color._pointer;
    c += i * _array_color._stride;
    argb = {_array_color._size > 3 ? float(c[3] / 256.f) : 1.f,
            _array_color._size > 0 ? float(c[0] / 256.f) : 1.f,
            _array_color._size > 1 ? float(c[1] / 256.f) : 1.f,
            _array_color._size > 2 ? float(c[2] / 256.f) : 1.f};
  }

  if (!_array_vertex._pointer)
    return;
  // support gl float vertex element type
  if (_array_vertex._type != GL_FLOAT)
    DEBUG_BREAK;
  // find vertex
  const uint8_t *f = (const uint8_t *)_array_vertex._pointer;
  f += i * _array_vertex._stride;
  const float *a = (const float *)f;

  // form vertices
  const float4 v = {
    _array_vertex._size > 0 ? a[0] : 0.f,
    _array_vertex._size > 1 ? a[1] : 0.f,
    _array_vertex._size > 2 ? a[2] : 0.f,
    _array_vertex._size > 3 ? a[3] : 1.f
  };

  // push vertex
  _push_vertex(vertex_t{v, uv, argb});
}

void primative_manager_t::glDrawElements(GLenum mode, GLsizei count,
                                         GLenum type, const GLvoid *indices) {
  DEBUG_BREAK;
}
