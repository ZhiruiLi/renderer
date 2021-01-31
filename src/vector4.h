#pragma once

#include <cassert>
#include <cstddef>

#include "math.h"

namespace sren {

struct Vector2f {
  float x{};
  float y{};
  Vector2f() = default;
  Vector2f(Vector2f const& v) : x{v.x}, y{v.y} {}
  Vector2f(float vx, float vy) : x{vx}, y{vy} {}

  void Set(float inX, float inY) {
    x = inX;
    y = inY;
  }
  void SetZero() {
    x = 0.0f;
    y = 0.0f;
  }

  float* GetPtr() { return &x; }

  float const* GetPtr() const { return &x; }

  float& operator[](int i) {
    assert(i >= 0 && i <= 1);
    return (&x)[i];
  }

  float const& operator[](int i) const {
    assert(i >= 0 && i <= 1);
    return (&x)[i];
  }

  Vector2f& operator+=(Vector2f const& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vector2f& operator-=(Vector2f const& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vector2f& operator=(Vector2f const& inV) {
    x = inV.x;
    y = inV.y;
    return *this;
  }

  Vector2f& operator*=(float t) {
    x *= t;
    y *= t;
    return *this;
  }

  Vector2f& operator/=(float t) {
    assert(!AlmostEqual(t, 0.0f));
    x /= t;
    y /= t;
    return *this;
  }

  bool operator==(Vector2f const& v) {
    return AlmostEqual(x, v.x) && AlmostEqual(y, v.y);
  }

  bool operator!=(Vector2f const& v) { return !(*this == v); }

  Vector2f operator-() const { return Vector2f(-x, -y); }

  Vector2f& Scale(Vector2f const inV) {
    x *= inV.x;
    y *= inV.y;
    return *this;
  }

  friend Vector2f operator+(Vector2f const &l, Vector2f const &r) {
    return Vector2f(l.x + r.x, l.y + r.y);
  }

  friend Vector2f operator-(Vector2f const &l, Vector2f const &r) {
    return Vector2f(l.x - r.x, l.y - r.y);
  }

  friend Vector2f operator*(Vector2f const &l, Vector2f const &r) {
    return Vector2f(l.x * r.x, l.y * r.y);
  }

  friend Vector2f operator/(Vector2f const &l, Vector2f const &r) {
    return Vector2f(l.x / r.x, l.y / r.y);
  }
};

struct Vector3f {
  float x{};
  float y{};
  float z{};
  Vector3f() = default;
  Vector3f(Vector3f const& v) : x{v.x}, y{v.y}, z{v.z} {}
  Vector3f(float vx, float vy, float vz) : x{vx}, y{vy}, z{vz} {}
};

struct Vector4f {
  int x{};
  int y{};
  int z{};
  int w{};
  Vector4f() = default;
  Vector4f(Vector4f const& v) : x{v.x}, y{v.y}, z{v.z}, w{v.w} {}
  Vector4f(int vx, int vy, int vz, int vw) : x{vx}, y{vy}, z{vz}, w{vw} {}
};

}  // namespace sren
