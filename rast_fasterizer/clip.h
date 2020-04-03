#pragma once
#include "../source/math.h"


template <typename vec_t>
struct edge_t {

  // note: normals face 'inwards' for triangles
  //       positive may be inside triangle, negative is always outside

  // return normal {-dy, dx} * s, where s is chosen so the normal extends to reach p
  static const float2 scale_normal(const vec_t &a, const vec_t &b, const vec_t &p) {
    // find edges
    // note: (a - b) as we want an inward facing normal
    const float2 edge = vec2(a) - vec2(b);
    // edge normal {-dy, dx}
    const float2 normal = float2::cross(edge);
    // distance between edge and opposite vertex
    // note: dist should always be > 0.f for a forward facing triangle
    const float dist = float2::dot(normal, vec2(p - a));
    // normalize to get interpolants
    return normal / dist;
  }

  edge_t(const vec_t &a, const vec_t &b)
    : _n(float2::cross(a - b))  // {-dy, dx}
    , _d(float2::dot(a, _n)) {  // distance of edge to origin
    // note: normal cant be used for attribute interpolation
  }

  edge_t(const vec_t &a, const vec_t &b, const vec_t &p)
    : _n(scale_normal(a, b, p)) // {-dy, dx} * s
    , _d(dot(a, _n))    // distance of edge to origin
  {
  }

  // evaluate the edge equation at a given point
  float eval(const float2 & p) const {
    // distance from edge
    return float2::dot(p, _n);
  }

  // test if a point falls on negative side of edge
  // point on negative side is 'out'
  bool test_out(const vec_t &p) const {
    return (p.x * _n.x + p.y * _n.y) < _d;
  }

  // test if a point falls on positive side of edge
  // point on positive side is 'in'
  bool test_in(const vec_t &p) const {
    return (p.x * _n.x + p.y * _n.y) >= _d;
  }

  // return normal sign code
  int normal_quadrant() const {
    return (_n.x > 0.f) | ((_n.y > 0.f) << 1);
  }

  // trivial rejection based on edge normal and closest box vertex
  bool trivial_out(const rectf_t &r) const {
    //note: remember edge normals face inward for triangles
    switch (normal_quadrant()) {
    case 3: return test_out(vec_t{r.x1, r.y1}); // (+,+) -> box (-, -)
    case 2: return test_out(vec_t{r.x0, r.y1}); // (-,+) -> box (+, -)
    case 1: return test_out(vec_t{r.x1, r.y0}); // (+,-) -> box (-, +)
    case 0: return test_out(vec_t{r.x0, r.y0}); // (-,-) -> box (+, +)
    default: __assume(false);
    }
  }

  // trivial inclusion based on edge normal and closest box vertex
  bool trivial_in(const rectf_t &r) const {
    //note: remember edge normals face inward for triangles
    switch (normal_quadrant()) {
    case 3: return test_in(vec_t{r.x0, r.y0}); // (+,+) -> box (+, +)
    case 2: return test_in(vec_t{r.x1, r.y0}); // (-,+) -> box (-, +)
    case 1: return test_in(vec_t{r.x0, r.y1}); // (+,-) -> box (+, -)
    case 0: return test_in(vec_t{r.x1, r.y1}); // (-,-) -> box (-, -)
    default: __assume(false);
    }
  }

  const float2 &normal() const {
    return _n;
  }

protected:
  float2 _n;
  float _d;
};


template <typename vec_t>
struct tri_setup_t {

  // constructor
  tri_setup_t(const vec_t &v0, const vec_t &v1, const vec_t &v2)
    : _e{edge_t<vec_t>(v0, v1, v2),  // e01
         edge_t<vec_t>(v1, v2, v0),  // e12
         edge_t<vec_t>(v2, v0, v1)}  // e20
    , _v{v0, v1, v2}
  {}

  // signed triangle area
  float area() const {
    // todo: make this area the same as the one below
    return (_v[1].x - _v[0].x) * (_v[2].y - _v[0].y) -
           (_v[2].x - _v[0].x) * (_v[1].y - _v[0].y);
  }

  // clockwise edge rotation by 1
  void rotate1() {
    // rotate by 1
    _v = rotate1(_v);
    _e = rotate1(_e);
  }

  // clockwise edge rotation by 2
  void rotate2() {
    _v = rotate2(_v);
    _e = rotate2(_e);
  }

  // return true if a triangle is backfacing
  bool is_backface() const {
    const float v1 = _v[0].x - _v[1].x;
    const float v2 = _v[0].y - _v[1].y;
    const float w1 = _v[2].x - _v[1].x;
    const float w2 = _v[2].y - _v[1].y;
    return (v1 * w2 - v2 * w1) >= 0.f;
  }

  // classify 'p' against edges of 'r'
  static int classify(const rectf_t &r, const vec_t &p) {
    return (p.x < r.x0 ? 1 : 0) |
           (p.x > r.x1 ? 2 : 0) |
           (p.y < r.y0 ? 4 : 0) |
           (p.y > r.y1 ? 8 : 0);
  };

  // test if 'r' is outside triangle via edge test
  bool trivial_out(const rectf_t &r) const {
      return _e[0].trivial_out(r) ||
             _e[1].trivial_out(r) ||
             _e[2].trivial_out(r);
  }

  // test if 'r' is inside triangle via edge test
  int trivial_in(const rectf_t &r) const {
      return (_e[0].trivial_in(r) ? 1 : 0) |
             (_e[1].trivial_in(r) ? 2 : 0) |
             (_e[2].trivial_in(r) ? 4 : 0);
  }

  // test if point lies within this triangle
  bool inside(const float2 &p) const {
    return _e[0].test_in(p) &&
           _e[1].test_in(p) &&
           _e[2].test_in(p);
  }

  // return true if triangle aabb overlaps aabb 'r'
  // return false if fully outside aabb
  bool overlap_aabb(const rectf_t &r) const {
    // classify all vertices
    const int ca = classify(r, _v[0]),
              cb = classify(r, _v[1]),
              cc = classify(r, _v[2]);
    // test trivial aabb accept
    if (0 == (ca | cb | cc)) {
      // all in center, no clipping
      return true;
    }
    // test trivial aabb reject
    const int code = ca & cb & cc;
    if ((code & 1) || (code & 2) || (code & 4) || (code & 8)) {
      // all outside one plane
      return false;
    }
    // overlap but clipping
    return true;
  }

  // return true if a triangle intersects rectangle
  bool intersect(const rectf_t & r) const {
    // cohen-sutherland style trivial box clipping
    // note: as triangle area aproaches zero this test becomes important
    if (!overlap_aabb(r)) {
      return false;
    }
    // reject backfaces
#if 0
    // note: they mess up the plane equation test below with inverted normals
    if (is_backface()) {
      return false;
    }
#endif
    // test if aabb can be rejected by edge plane
    // note: this is important for large area triangles
    if (trivial_out(r)) {
      return false;
    }
    // in, but may need clipping
    return true;
  }

  // evaluate edge functions at point p
  std::array<float, 3> eval(const float2 &p) const {
    return std::array<float, 3> {
      _e[1].eval(p - vec2(_v[1])),
      _e[0].eval(p - vec2(_v[0])),
      _e[2].eval(p - vec2(_v[2]))};
  }

  // pixel stepping constants
  std::array<float2, 3> step() const {
    return std::array<float2, 3>{
      _e[1].normal(),
      _e[0].normal(),
      _e[2].normal()};
  }

  const auto &edges() const {
    return _e;
  }

  const auto &vertices() const {
    return _v;
  }

protected:
  // edges {e01, e12, e20}
  std::array<edge_t<vec_t>, 3> _e;
  // vertices {v0, v1, v2}
  std::array<vec_t, 3> _v;

  // rotate vertices clockwise 1 time
  template <typename type_t>
  static std::array<type_t, 3> rotate1(const std::array<type_t, 3> &v) {
    return std::array<type_t, 3> {v[2], v[0], v[1]};
  }

  // rotate vertices clockwise 2 times
  template <typename type_t>
  static std::array<type_t, 3> rotate2(const std::array<type_t, 3> &v) {
    return std::array<type_t, 3> {v[1], v[2], v[0]};
  }

}; // tri_setup_t
