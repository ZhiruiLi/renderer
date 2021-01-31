#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>

#include "math.h"

namespace sren {

struct Vector2f {
  float x{};
  float y{};
  Vector2f() = default;
  Vector2f(Vector2f const& v) : x{v.x}, y{v.y} {}
  Vector2f(float vx, float vy) : x{vx}, y{vy} {}

  void Set(float vx, float vy) {
    x = vx;
    y = vy;
  }

  void SetZero() {
    x = 0.0f;
    y = 0.0f;
  }

  float* GetPtr() { return &x; }

  float const* GetPtr() const { return &x; }

  float& operator[](int i) {
    assert(i >= 0 && i <= 1);
    return GetPtr()[i];
  }

  float const& operator[](int i) const {
    assert(i >= 0 && i <= 1);
    return GetPtr()[i];
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

  friend Vector2f operator+(Vector2f const& l, Vector2f const& r) {
    return Vector2f(l.x + r.x, l.y + r.y);
  }

  friend Vector2f operator-(Vector2f const& l, Vector2f const& r) {
    return Vector2f(l.x - r.x, l.y - r.y);
  }

  friend Vector2f operator*(Vector2f const& l, Vector2f const& r) {
    return Vector2f(l.x * r.x, l.y * r.y);
  }

  friend Vector2f operator*(Vector2f const& v, float f) {
    return Vector2f(v.x * f, v.y * f);
  }

  friend Vector2f operator*(float f, Vector2f const& v) {
    return Vector2f(v.x * f, v.y * f);
  }

  friend Vector2f operator/(Vector2f const& l, Vector2f const& r) {
    return Vector2f(l.x / r.x, l.y / r.y);
  }

  friend Vector2f operator/(Vector2f const& v, float f) {
    return Vector2f(v.x / f, v.y / f);
  }

  static const Vector2f infinity;
  static const Vector2f zero;
  static const Vector2f one;
  static const Vector2f xAxis;
  static const Vector2f yAxis;
};

inline Vector2f Inverse(Vector2f const& v) {
  return Vector2f(1.0f / v.x, 1.0f / v.y);
}

inline float Dot(Vector2f const& l, Vector2f const& r) {
  return l.x * r.x + l.y * r.y;
}

inline Vector2f Abs(Vector2f const& v) {
  return Vector2f(std::fabs(v.x), std::fabs(v.y));
}

inline float SquareMagnitude(Vector2f const& v) { return Dot(v, v); }

inline float Magnitude(Vector2f const& v) { return std::sqrtf(Dot(v, v)); }

inline float Angle(Vector2f const& l, Vector2f const& r) {
  return std::acos(std::min(1.0f, Dot(l, r) / (Magnitude(l) * Magnitude(r))));
}

inline Vector2f Normalize(const Vector2f& inV) { return inV / Magnitude(inV); }

inline Vector2f NormalizeSafe(const Vector2f& v,
                              const Vector2f& defaultV = Vector2f::zero);

}  // namespace sren
