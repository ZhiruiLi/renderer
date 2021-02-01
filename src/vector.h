#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

#include "math.h"

namespace sren {

template <class T, std::size_t N,
          class = typename std::enable_if<!std::numeric_limits<T>::is_integer,
                                          void>::type>
struct Vector {
  Vector() = default;

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data[i];
  }

  T operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data[i];
  }

  T data[N] = {0};
};

template<class T>
struct Vector<T, 2> {
  Vector() = default;

  Vector(float vx, float vy): x{vx}, y{vy} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < 2);
    return ((T*)this)[i];
  }

  float operator[](std::size_t i) const {
    assert(i >= 0 && i < 2);
    return ((T*)this)[i];
  }

  T x{};
  T y{};
};

template<class T>
struct Vector<T, 3> {
  Vector() = default;

  Vector(float vx, float vy, float vz): x{vx}, y{vy}, z{vz} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < 3);
    return ((T*)this)[i];
  }

  float operator[](std::size_t i) const {
    assert(i >= 0 && i < 3);
    return ((T*)this)[i];
  }

  T x{};
  T y{};
  T z{};
};

template<class T>
struct Vector<T, 4> {
  Vector() = default;

  Vector(float vx, float vy, float vz, float vw): x{vx}, y{vy}, z{vz}, w{vw} {}

  Vector(Vector<T, 3> const& v) : x{v.x}, y{v.y}, z{v.z}, w{1.0f} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < 4);
    return ((T*)this)[i];
  }

  float operator[](std::size_t i) const {
    assert(i >= 0 && i < 4);
    return ((T*)this)[i];
  }

  T x{};
  T y{};
  T z{};
  T w{};
};

using Vector2D = Vector<float, 2>;
using Vector3D = Vector<float, 3>;
using Vector4D = Vector<float, 4>;

// 矢量比较
template <class T, std::size_t N>
Vector<T, N> operator==(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  for (int i = 0; i < N; i++) {
    if (!AlmostEqual(lhs[i], rhs[i])) { return false; }
  }
  return true;
}

// 矢量比较
template <class T, std::size_t N>
Vector<T, N> operator!=(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  return !(lhs == rhs);
}

// 矢量加法
template <class T, std::size_t N>
Vector<T, N> operator+(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  Vector<T, N> ret = lhs;
  for (int i = 0; i < N; i++) {
    ret[i] += rhs[i];
  }
  return ret;
}

// 矢量减法
template <class T, std::size_t N>
Vector<T, N> operator-(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  Vector<T, N> ret = lhs;
  for (int i = 0; i < N; i++) {
    ret[i] -= rhs[i];
  }
  return ret;
}

// 矢量对常量乘法
template <class T, std::size_t N>
Vector<T, N> operator*(T f, Vector<T, N> const& v) {
  Vector<T, N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] *= f;
  }
  return ret;
}

// 矢量对常量乘法
template <class T, std::size_t N>
Vector<T, N> operator*(Vector<T, N> const& v, T f) {
  Vector<T, N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] *= f;
  }
  return ret;
}

// 矢量对常量的除法
template <class T, std::size_t N>
Vector<T, N> operator/(Vector<T, N> const& v, T f) {
  Vector<T, N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] /= f;
  }
  return ret;
}

// 矢量点乘
template <class T, std::size_t N>
T operator*(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  T ret = 0;
  for (int i = 0; i < N; i++) {
    ret += lhs[i] * rhs[i];
  }
  return ret;
}

// 三维矢量叉乘
template <class T>
Vector<T, 3> operator^(Vector<T, 3> const& lhs, Vector<T, 3> const& rhs) {
  Vector<T, 3> v{};
  v.x = lhs.y * rhs.z - lhs.z * rhs.y;
  v.y = lhs.z * rhs.x - lhs.x * rhs.z;
  v.z = lhs.x * rhs.y - lhs.y * rhs.x;
  return v;
}

template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& v) {
  out << "(";
  if (N > 0) {
    out << v[0];
  }
  for (int i = 1; i < N; i++) {
    out << ", " << v[i];
  }
  out << ")";
  return out;
}

template <class T, std::size_t N>
inline T SquareMagnitude(Vector<T, N> const& v) { return v * v; }

template <class T, std::size_t N>
inline T Magnitude(Vector<T, N> const& v) {
  return std::sqrtf(SquareMagnitude(v));
}

template <class T, std::size_t N>
inline Vector<T, N> Inverse(Vector<T, N> const& v) {
  Vector<T, N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = 1.0f / ret[i];
  }
  return ret;
}

template <class T, std::size_t N>
inline Vector<T, N> Abs(Vector<T, N> const& v) {
  Vector<T, N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = std::abs(ret[i]);
  }
  return ret;
}

template <class T, std::size_t N>
inline T Angle(Vector<T, N> const& l, Vector<T, N> const& r) {
  return std::acos(std::min(1.0f, l * r / (Magnitude(l) * Magnitude(r))));
}

template <class T, std::size_t N>
inline Vector<T, N> Normalize(Vector<T, N> const & v) { return v / Magnitude(v); }

}  // namespace sren
