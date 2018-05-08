#pragma once
#include <cstdint>


static const float pi1 = 3.14159265359f;
static const float pi2 = 3.14159265359f * 2.f;

template <typename type_t>
struct vec4_t {

  type_t x, y, z, w;

  vec4_t operator + (const vec4_t &v) const {
    return vec4_t {
      this->x + v.x,
      this->y + v.y,
      this->z + v.z,
      this->w + v.w,
    };
  }

  vec4_t operator + (const type_t &v) const {
    return vec4_t {
      this->x + v,
      this->y + v,
      this->z + v,
      this->w + v,
    };
  }

  vec4_t operator - (const vec4_t &v) const {
    return vec4_t {
      this->x - v.x,
      this->y - v.y,
      this->z - v.z,
      this->w - v.w,
    };
  }

  vec4_t operator - (const type_t &v) const {
    return vec4_t {
      this->x - v,
      this->y - v,
      this->z - v,
      this->w - v,
    };
  }

  vec4_t operator * (const vec4_t &v) const {
    return vec4_t {
      this->x * v.x,
      this->y * v.y,
      this->z * v.z,
      this->w * v.w,
    };
  }

  vec4_t operator * (const type_t &v) const {
    return vec4_t {
      this->x * v,
      this->y * v,
      this->z * v,
      this->w * v,
    };
  }

  vec4_t operator / (const vec4_t &v) const {
    return vec4_t {
      this->x / v.x,
      this->y / v.y,
      this->z / v.z,
      this->w / v.w,
    };
  }

  vec4_t operator / (const type_t &v) const {
    return vec4_t {
      this->x / v,
      this->y / v,
      this->z / v,
      this->w / v,
    };
  }

  void operator += (const vec4_t &v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;
  }

  void operator += (const type_t &v) {
    this->x += v;
    this->y += v;
    this->z += v;
    this->w += v;
  }

  void operator -= (const vec4_t &v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;
  }

  void operator -= (const type_t &v) {
    this->x -= v;
    this->y -= v;
    this->z -= v;
    this->w -= v;
  }

  void operator *= (const vec4_t &v) {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    this->w *= v.w;
  }

  void operator *= (const type_t &v) {
    this->x *= v;
    this->y *= v;
    this->z *= v;
    this->w *= v;
  }

  void operator /= (const vec4_t &v) {
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
    this->w /= v.w;
  }

  void operator /= (const type_t &v) {
    this->x /= v;
    this->y /= v;
    this->z /= v;
    this->w /= v;
  }

  static type_t dot(const vec4_t &a, const vec4_t &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }

  static vec4_t set(const type_t &v) {
    return vec4_t { v, v, v, v };
  }

  static vec4_t set(const type_t &x, const type_t &y, const type_t &z, const type_t &w) {
    return vec4_t { x, y, z, w };
  }

  static vec4_t lerp(const vec4_t &a, const vec4_t &b, float t) {
    return vec4_t{
      a.x + (b.x - a.x) * t,
      a.y + (b.y - a.y) * t,
      a.z + (b.z - a.z) * t,
      a.w + (b.w - a.w) * t};
  }

};  // vec4_t


template <typename type_t>
struct vec3_t {

  type_t x, y, z;

  vec3_t operator + (const vec3_t &v) const {
    return vec3_t {
      this->x + v.x,
      this->y + v.y,
      this->z + v.z,
    };
  }

  vec3_t operator + (const type_t &v) const {
    return vec3_t {
      this->x + v,
      this->y + v,
      this->z + v,
    };
  }

  vec3_t operator - (const vec3_t &v) const {
    return vec3_t {
      this->x - v.x,
      this->y - v.y,
      this->z - v.z,
    };
  }

  vec3_t operator - (const type_t &v) const {
    return vec3_t {
      this->x - v,
      this->y - v,
      this->z - v,
    };
  }

  vec3_t operator * (const vec3_t &v) const {
    return vec3_t {
      this->x * v.x,
      this->y * v.y,
      this->z * v.z,
    };
  }

  vec3_t operator * (const type_t &v) const {
    return vec3_t {
      this->x * v,
      this->y * v,
      this->z * v,
    };
  }

  vec3_t operator / (const vec3_t &v) const {
    return vec3_t {
      this->x / v.x,
      this->y / v.y,
      this->z / v.z,
    };
  }

  vec3_t operator / (const type_t &v) const {
    return vec3_t {
      this->x / v,
      this->y / v,
      this->z / v,
    };
  }

  void operator += (const vec3_t &v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
  }

  void operator += (const type_t &v) {
    this->x += v;
    this->y += v;
    this->z += v;
  }

  void operator -= (const vec3_t &v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
  }

  void operator -= (const type_t &v) {
    this->x -= v;
    this->y -= v;
    this->z -= v;
  }

  void operator *= (const vec3_t &v) {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
  }

  void operator *= (const type_t &v) {
    this->x *= v;
    this->y *= v;
    this->z *= v;
  }

  void operator /= (const vec3_t &v) {
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
  }

  void operator /= (const type_t &v) {
    this->x /= v;
    this->y /= v;
    this->z /= v;
  }

  static type_t dot(const vec3_t &a, const vec3_t &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  static vec3_t set(const type_t &v) {
    return vec3_t { v, v, v };
  }

  static vec3_t set(const type_t &x, const type_t &y, const type_t &z) {
    return vec3_t { x, y, z };
  }

};  // vec3_t


template <typename type_t>
struct vec2_t {

  type_t x, y;

  vec2_t operator + (const vec2_t &v) const {
    return vec2_t {
      this->x + v.x,
      this->y + v.y,
    };
  }

  vec2_t operator + (const type_t &v) const {
    return vec2_t {
      this->x + v,
      this->y + v,
    };
  }

  vec2_t operator - (const vec2_t &v) const {
    return vec2_t {
      this->x - v.x,
      this->y - v.y,
    };
  }

  vec2_t operator - (const type_t &v) const {
    return vec2_t {
      this->x - v,
      this->y - v,
    };
  }

  vec2_t operator * (const vec2_t &v) const {
    return vec2_t {
      this->x * v.x,
      this->y * v.y,
    };
  }

  vec2_t operator * (const type_t &v) const {
    return vec2_t {
      this->x * v,
      this->y * v,
    };
  }

  vec2_t operator / (const vec2_t &v) const {
    return vec2_t {
      this->x / v.x,
      this->y / v.y,
    };
  }

  vec2_t operator / (const type_t &v) const {
    return vec2_t {
      this->x / v,
      this->y / v,
    };
  }

  void operator += (const vec2_t &v) {
    this->x += v.x;
    this->y += v.y;
  }

  void operator += (const type_t &v) {
    this->x += v;
    this->y += v;
  }

  void operator -= (const vec2_t &v) {
    this->x -= v.x;
    this->y -= v.y;
  }

  void operator -= (const type_t &v) {
    this->x -= v;
    this->y -= v;
  }

  void operator *= (const vec2_t &v) {
    this->x *= v.x;
    this->y *= v.y;
  }

  void operator *= (const type_t &v) {
    this->x *= v;
    this->y *= v;
  }

  void operator /= (const vec2_t &v) {
    this->x /= v.x;
    this->y /= v.y;
  }

  void operator /= (const type_t &v) {
    this->x /= v;
    this->y /= v;
  }

  static type_t dot(const vec2_t &a, const vec2_t &b) {
    return a.x * b.x + a.y * b.y;
  }

  static vec2_t set(const type_t &v) {
    return vec2_t { v, v };
  }

  static vec2_t set(const type_t &x, const type_t &y) {
    return vec2_t { x, y };
  }

};  // vec2_t

using int2 = vec2_t<int32_t>;
using int3 = vec3_t<int32_t>;
using int4 = vec4_t<int32_t>;
using float2 = vec2_t<float>;
using float3 = vec3_t<float>;
using float4 = vec4_t<float>;
