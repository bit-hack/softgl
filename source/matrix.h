#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <intrin.h>

#include "GL.h"
#include "math.h"

enum matrix_mode_t {
  GL_MATRIXMODE_MODELVIEW,
  GL_MATRIXMODE_PROJECTION,
};

struct matrix_t {

  // array index layout:
  //   0   4   8   c
  //   1   5   9   d
  //   2   6   a   e
  //   3   7   b   f

  //   c = x, d = y, e = z

  __m128 row_get(const int32_t y) const {
    return _mm_loadu_ps(e.data() + y * 4);
  }

  void row_set(const int32_t y, __m128 v) {
    _mm_storeu_ps(e.data() + y * 4, v);
  }

  const float & operator () (int32_t x, int32_t y) const {
    return e[x * 4 + y];
  }

  float & operator () (int32_t x, int32_t y) {
    return e[x * 4 + y];
  }

  const float & operator [] (int32_t i) const {
    return e[i];
  }

  float & operator [] (int32_t i) {
    return e[i];
  }

  float *data() {
    return e.data();
  }

  const float *data() const {
    return e.data();
  }

  void identity() {
    e.fill(0.f);
    operator()(0, 0) = 1.f;
    operator()(1, 1) = 1.f;
    operator()(2, 2) = 1.f;
    operator()(3, 3) = 1.f;
  }

  void _multiply_fpu(const matrix_t &b) {
    matrix_t &a = *this;
    matrix_t r;
    for (uint32_t i = 0; i < 16; i+=4) {
      r[i + 0]  = b[i + 0] * a[0x0] + b[i + 1] * a[0x4] + b[i + 2] * a[0x8] + b[i + 3] * a[0xc];
      r[i + 1]  = b[i + 0] * a[0x1] + b[i + 1] * a[0x5] + b[i + 2] * a[0x9] + b[i + 3] * a[0xd];
      r[i + 2]  = b[i + 0] * a[0x2] + b[i + 1] * a[0x6] + b[i + 2] * a[0xa] + b[i + 3] * a[0xe];
      r[i + 3]  = b[i + 0] * a[0x3] + b[i + 1] * a[0x7] + b[i + 2] * a[0xb] + b[i + 3] * a[0xf];
    }
    e = r.e;
  }

  static inline __m128 _lincomb_sse(const __m128 &a, const matrix_t &b)
  {
    // linear combination:
    // a[0] * b.row[0] + a[1] * b.row[1] + a[2] * b.row[2] + a[3] * b.row[3]
    __m128 result;
    result = _mm_mul_ps(                   _mm_shuffle_ps(a, a, 0x00), b.row_get(0));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0x55), b.row_get(1)));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xaa), b.row_get(2)));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xff), b.row_get(3)));
    return result;
  }

  void _multiply_sse(const matrix_t &b) {
    const __m128 out0x = _lincomb_sse(b.row_get(0), *this);
    const __m128 out1x = _lincomb_sse(b.row_get(1), *this);
    const __m128 out2x = _lincomb_sse(b.row_get(2), *this);
    const __m128 out3x = _lincomb_sse(b.row_get(3), *this);
    row_set(0, out0x);
    row_set(1, out1x);
    row_set(2, out2x);
    row_set(3, out3x);
  }
  
  template <bool use_sse=true>
  void multiply(const matrix_t &b) {
    use_sse ? _multiply_sse(b) : _multiply_fpu(b);
  }

  __declspec(align(16)) std::array<float, 16> e;
};


struct matrix_stack_t {

  matrix_stack_t(matrix_mode_t mode): _mode(mode), _head(0) {
    top().identity();
  }

  void glPushMatrix() {
    assert(can_push());
    ++_head;
    _stack[_head] = _stack[_head - 1];
  }

  void glPopMatrix() {
    assert(_head > 0);
    --_head;
  }

  void glOrtho(float l,
               float r,
               float b,
               float t,
               float n,
               float f) {
    matrix_t m;

    m(0, 0) = 2.f / (r - l);
    m(1, 0) = 0.f;
    m(2, 0) = 0.f;
    m(3, 0) = -(r + l) / (r - l);

    m(0, 1) = 0.f;
    m(1, 1) = 2.f / (t - b);
    m(2, 1) = 0.f;
    m(3, 1) = -(t + b) / (t - b);

    m(0, 2) = 0.f;
    m(1, 2) = 0.f;
    m(2, 2) = -2.f / (f - n);
    m(3, 2) = -(f + n) / (f - n);

    m(0, 3) = 0.f;
    m(1, 3) = 0.f;
    m(2, 3) = 0.f;
    m(3, 3) = 1.f;

    top().multiply(m);
  }

  void glRotatef(float angle, float x, float y, float z) {
    const float RAD = 3.14159265359f / 180.f;

    const float l = 1.f / sqrtf( x*x + y*y + z*z );
    x *= l; y *= l; z *= l;

    const float r = angle * RAD;
    const float c = cosf( r );
    const float s = sinf( r );
    const float t = 1-c;

    matrix_t m;
    m(0, 0) = x*x*t+c;
    m(1, 0) = x*y*t-z*s;
    m(2, 0) = x*z*t+y*s;
    m(3, 0) = 0.f;

    m(0, 1) = y*x*t+z*s;
    m(1, 1) = y*y*t+c;
    m(2, 1) = y*z*t-x*s;
    m(3, 1) = 0.f;

    m(0, 2) = x*z*t-y*s;
    m(1, 2) = y*z*t+x*s;
    m(2, 2) = z*z*t+c;
    m(3, 2) = 0.f;

    m(0, 3) = 0.f;
    m(1, 3) = 0.f;
    m(2, 3) = 0.f;
    m(3, 3) = 1.f;

    top().multiply(m);
  }

  void glScalef(float x, float y, float z) {

    matrix_t m = {
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1
    };

    top().multiply(m);
  }

  void glTranslatef(float x, float y, float z) {

    matrix_t m = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      x, y, z, 1
    };

    top().multiply(m);
  }

  void glFrustum(const float l,
                 const float r,
                 const float b,
                 const float t,
                 const float n,
                 const float f) {
    matrix_t m;

    if (n < 0.f || f < 0.f)
      return;

    const float m00 = 2.f * n       / (r - l);
    const float m11 = 2.f * n       / (t - b);
    const float m02 = (r + l)       / (r - l);
    const float m12 = (t + b)       / (t - b);
    const float m22 =-(f + n)       / (f - n);
    const float m23 =-(2.f * f * n) / (f - n);

    m(0, 0) = m00; m(1, 0) = 0;   m(2, 0) = m02;  m(3, 0) = 0;
    m(0, 1) = 0;   m(1, 1) = m11; m(2, 1) = m12;  m(3, 1) = 0;
    m(0, 2) = 0;   m(1, 2) = 0;   m(2, 2) = m22;  m(3, 2) = m23;
    m(0, 3) = 0;   m(1, 3) = 0;   m(2, 3) = -1.f; m(3, 3) = 0;

    top().multiply(m);
  }

  void glMultMatrixf(const float *v) {
    matrix_t m;
    for (uint32_t i = 0; i < 16; ++i)
      m[i] = v[i];
    top().multiply(m);
  }

  matrix_t & top() {
    return _stack[_head];
  }

  const matrix_t & top() const {
    return _stack[_head];
  }

  void glLoadIdentity() {
    top().identity();
  }

  bool can_pop() const {
    return _head > 0;
  }

  bool can_push() const {
    return (_head + 1) < _stack.size();
  }

  void clear() {
    _head = 0;
    top().identity();
  }

protected:
  const matrix_mode_t _mode;
  uint32_t _head;
  std::array<matrix_t, 32> _stack;
};


struct matrix_manager_t {

  matrix_manager_t()
    : _modelview(GL_MATRIXMODE_MODELVIEW)
    , _projection(GL_MATRIXMODE_PROJECTION)
    , _current(&_modelview)
    , _dirty(true)
  {
    _modelview.glLoadIdentity();
    _projection.glLoadIdentity();
  }

  void glMatrixMode(GLenum mode) {
    _mode = mode;
    switch (mode) {
    case GL_MODELVIEW:
      _current = &_modelview;
      break;
    case GL_PROJECTION:
      _current = &_projection;
      break;
    default:
      __debugbreak();
    }
  }

  GLenum getMatrixMode() {
    if (_current == &_modelview) {
      return GL_MODELVIEW;
    }
    if (_current == &_projection) {
      return GL_PROJECTION;
    }
    return GL_INVALID_ENUM;
  }

  void glOrtho(float l,
               float r,
               float b,
               float t,
               float n,
               float f) {
    _dirty = true;
    _current->glOrtho(l, r, b, t, n, f);
  }

  void glRotatef(float angle, float x, float y, float z) {
    _dirty = true;
    _current->glRotatef(angle, x, y, z);
  }

  void glScalef(float x, float y, float z) {
    _dirty = true;
    _current->glScalef(x, y, z);
  }

  void glTranslatef(float x, float y, float z) {
    _dirty = true;
    _current->glTranslatef(x, y, z);
  }

  void glFrustum(const float l,
                 const float r,
                 const float b,
                 const float t,
                 const float n,
                 const float f) {
    _dirty = true;
    _current->glFrustum(l, r, b, t, n, f);
  }

  void glMultMatrixf(const float *v) {
    _dirty = true;
    _current->glMultMatrixf(v);
  }

  void glLoadMatrixf(const float *v) {
    _dirty = true;
    matrix_t &m = _current->top();
    for (uint32_t i = 0; i < 16; ++i) {
      m.e[i] = v[i];
    }
  }

  void glLoadIdentity() {
    _dirty = true;
    _current->glLoadIdentity();
  }

  void glPushMatrix() {
    _dirty = true;
    _current->glPushMatrix();
  }

  void glPopMatrix() {
    _dirty = true;
    _current->glPopMatrix();
  }

  matrix_t &modelview() {
    return _modelview.top();
  }

  matrix_t &projection() {
    return _projection.top();
  }

  bool can_pop() const {
    return _current->can_pop();
  }

  bool can_push() const {
    return _current->can_push();
  }

  const matrix_t &top() const {
    return _current->top();
  }

  float4 transform(float4 v) {
    if (_dirty) {
      _memo = _projection.top();
      _memo.multiply(_modelview.top());
      _dirty = false;
    }
    const matrix_t &m = _memo;
    return float4{
      m(0, 0) * v.x + m(1, 0) * v.y + m(2, 0) * v.z + m(3, 0) * v.w,
      m(0, 1) * v.x + m(1, 1) * v.y + m(2, 1) * v.z + m(3, 1) * v.w,
      m(0, 2) * v.x + m(1, 2) * v.y + m(2, 2) * v.z + m(3, 2) * v.w,
      m(0, 3) * v.x + m(1, 3) * v.y + m(2, 3) * v.z + m(3, 3) * v.w
    };
  }

protected:
  matrix_stack_t _modelview, _projection;
  matrix_stack_t *_current;
  GLenum _mode;

  bool _dirty;
  matrix_t _memo;
};
