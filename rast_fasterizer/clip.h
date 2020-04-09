#pragma once
#include "../source/math.h"

struct edge_t {

  // note: normals face 'inwards' for triangles
  //       positive may be inside triangle, negative is always outside

  // return normal {-dy, dx} * s, where s is chosen so the normal extends to reach p
  static const float2 scale_normal(const float2 &a, const float2 &b, const float2 &p) {
    // find edges
    // note: (a - b) as we want an inward facing normal
    const float2 edge = float2(a) - float2(b);
    // edge normal {-dy, dx}
    const float2 normal = float2::cross(edge);
    // distance between edge and opposite vertex
    // note: dist should always be > 0.f for a forward facing triangle
    const float dist = float2::dot(normal, float2(p - a));
    // normalize to get interpolants
    return normal / dist;
  }

  edge_t(const float2 &a, const float2 &b)
    : _n(float2::cross(a - b))  // {-dy, dx}
    , _d(float2::dot(a, _n)) {  // distance of edge to origin
    // note: normal cant be used for attribute interpolation
  }

  edge_t(const float2 &a, const float2 &b, const float2 &p)
    : _n(scale_normal(a, b, p)) // {-dy, dx} * s
    , _d(float2::dot(a, _n))    // distance of edge to origin
  {
  }

  // evaluate the edge equation at a given point
  float eval(const float2 & p) const {
    // distance from edge
    return float2::dot(p, _n);
  }

  // test if a point falls on negative side of edge
  // point on negative side is 'out'
  bool test_out(const float2 &p) const {
    return (p.x * _n.x + p.y * _n.y) < _d;
  }

  // test if a point falls on positive side of edge
  // point on positive side is 'in'
  bool test_in(const float2 &p) const {
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
    case 3: return test_out(float2{r.x1, r.y1}); // (+,+) -> box (-, -)
    case 2: return test_out(float2{r.x0, r.y1}); // (-,+) -> box (+, -)
    case 1: return test_out(float2{r.x1, r.y0}); // (+,-) -> box (-, +)
    case 0: return test_out(float2{r.x0, r.y0}); // (-,-) -> box (+, +)
    default: __assume(false);
    }
  }

  // trivial inclusion based on edge normal and closest box vertex
  bool trivial_in(const rectf_t &r) const {
    //note: remember edge normals face inward for triangles
    switch (normal_quadrant()) {
    case 3: return test_in(float2{r.x0, r.y0}); // (+,+) -> box (+, +)
    case 2: return test_in(float2{r.x1, r.y0}); // (-,+) -> box (-, +)
    case 1: return test_in(float2{r.x0, r.y1}); // (+,-) -> box (+, -)
    case 0: return test_in(float2{r.x1, r.y1}); // (-,-) -> box (-, -)
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


struct tri_setup_t {

  // constructor
  tri_setup_t(const float2 &v0, const float2 &v1, const float2 &v2)
    : _e{edge_t(v0, v1, v2),  // e01
         edge_t(v1, v2, v0),  // e12
         edge_t(v2, v0, v1)}  // e20
  {}

  // test if 'r' is outside triangle via edge test
  bool trivial_out(const rectf_t &r) const {
      return _e[0].trivial_out(r) ||
             _e[1].trivial_out(r) ||
             _e[2].trivial_out(r);
  }

  // test if 'r' is inside triangle via edge test
  bool trivial_in(const rectf_t &r) const {
      return _e[0].trivial_in(r) &&
             _e[1].trivial_in(r) &&
             _e[2].trivial_in(r);
  }

protected:
  // edges {e01, e12, e20}
  std::array<edge_t, 3> _e;

}; // tri_setup_t
